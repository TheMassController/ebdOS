// This file makes sure all the default settings are set
// System headers, provided by the libs
#include <hw_nvic.h>        // Macros for hardware interrupt setup
#include <hw_types.h>       // Contains the types
#include <sysctl.h>         // Contains defines for PLL regs
#include <rom_map.h>        // Call functions directly from the ROM if available
#include <rom.h>            // Declare ROM addresses for rom funcs
#include <hw_memmap.h>      // address of GPIO etc
#include <gpio.h>           // Address of GPIO stuff
#include <uart.h>           // UART addresses and stuff
#include <uartstdio.h>      // UART printf n stuff
#include <stdlib.h>         // Malloc & Free
#include <process.h>        // Process var
#include <lm4f120h5qr.h>    // Hardware regs
#include <timer.h>          // The subaddresses of timers
#include <hw_ints.h>        // Memory addresses of hw interrupts
#include <interrupt.h>      // Function prototypes for hardware interrupt setup
// System headers provided by kernel or core
#include "coreUtils.h"              // Core functions that need to be written in assembly
#include "process.h"                // Everything related to the processes
#include "mutex.h"                  // Everything related to mutexes
#include "reentrantMutex.h"         // Everything related to mutexes
#include "mpucontrol.h"             // Functions related to controlling the MPU
#include "getSetRegisters.h"        // Functions to interact with the registers directly
#include "supervisorCall.h"         // Defines what a supervisor call is
#include "clockSetup.h"             // Defines clock speed and related settings
#include "kernUtils.h"              // Contains the generateCrash function
#include "kernMaintenanceQueue.h"   // Contains kernRetQueuePush
// User headers
#include "validation.h"     // Contains all validation functions

#define SLEEPTIMERPRIORITY 0xc0 //11000000, lowest possible priority of major group, highest possible of subgroup

extern unsigned sleepClocksPerMS;
extern struct ReentrantMutex mallocMutex;
extern int initialized;

#ifdef __GNUC__
void kernelMain(void) __attribute__ ((noreturn));
#else
void kernelMain(void);
#endif //__GNUC__
void initializeProcesses(void);
void initScheduler(struct Process* currentProc);
void main(void);

void kernelStart(void){
    // Setup the PLL
    ROM_SysCtlClockSet(CLOCKSPEEDS_SYSCTL[EDB_SYSCTL_ENTRY]);

    // Enable all possible sys interrupts
    // Datasheet pp 168
    // Enable the usage fault
    NVIC_SYS_HND_CTRL_R |= 0x1<<18;
    // Enable the bus fault
    NVIC_SYS_HND_CTRL_R |= 0x1<<17;
    // Enable the mem fault
    NVIC_SYS_HND_CTRL_R |= 0x1<<16;

    // Enable the floating point unit
    // datasheet pp 190
    NVIC_CPAC_R |= 0x3 << 20; // Enable full access to coprocessor 10
    NVIC_CPAC_R |= 0x3 << 22; // Enable full access to coprocessor 11
    // Enable lazy stacking
    // Datasheet pp 191
    NVIC_FPCC_R |= 0x3 << 30; // Enables the ASPEN (automatic state preservation) bit and the LSPEN (Lazy stacking state preservation)

    // Setup the Debug UART out
    // Enable the correct interfaces: GPIOA for USB Debug, UART0 for USB Debug
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Setup GPIO A as UART
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
    UARTStdioInitExpClk(0, PC_BAUDRATE);

    // Setup the interrupt priorities. 0 is highest, 7 is lowest.
    NVIC_SYS_PRI1_R = 0x00202020;   // All faults are reset to 1. See datasheet pp 165
    NVIC_SYS_PRI2_R = 0;            // Implies that the SVC interrupt is now level 0.
    NVIC_SYS_PRI3_R = 0;            // All level 3 interrupt (= debug, pendsv, systick) are now zero.
    NVIC_SYS_PRI3_R |= 7<<21;       // pendSV gets 7. Datasheet pp 167.
    // The pendSV has this low priority so that context switches can be called from an interrupt (regset is in a wrong state when inside an interrupt)
    // The standard here is that all other interrupts get a prio higher then 7, excluding the system faults (those are fixed anyway).
    // So when you request a context switcher from an interrupt,
    // the context switch will happen after every currently running interrupt is finished and every higher level interrupt is handled.
    //
    // This has two advantages: first you actually can context switch (all stacks and the regset being in the right state and all),
    // second: the context switch can be called multiple times but will only run once per interrupt session
    // During the actual context switch all interupts are disabled (cpsi instruction)
    // Under the current construction errors can call the supervisor, which can subsequently call the kernel to handle the error.
    // This is because despite the fact that they are in a higher handler priority, their actual priority is lower.
    // For much of the same reason the systick handler is 0: we do not want any interrupt to override it, becuase the SVC and the systick cannot run at the same time.
    // One issue is that if the systick or the svc create an error it will immediately be escalated to a hard fault. But thats ok.

    // For scheduling: systick
    // It is connected to the PIOSC/4, which means that is it connected to a very precise 4 Mhz clock (see datasheet pp 118)
    // It only gets its interrupt enabled here, the scheduler will manage it further
    ROM_SysTickIntEnable();

    // Enable all non-special interrupts
    // With this thing disabled, the SVC, PendSV, Systick, busfault etc "exceptions" also wont run. Except Hard Fault and NMI, because they are badass like that.
    ROM_IntMasterEnable();

    // Setup the sleep clock.
    // The first 32 bit timer is the sleep clock. It counts slow and interrupts on overflow.
    // 32-bit wide, one clock increase every 40000 cycles. At this point, the clock is 80.000.000 cycles per second. So this clock changes 2000 times per second
    // 2 clocks is a ms, 2000 clocks is a second
    // The timer runs from high to low
    if (MAP_SysCtlClockGet() % 1000000){
        UARTprintf("The current clock speed is not high enough for the OS to function\n");
        generateCrash();
    }
    const unsigned ticksPerUs = MAP_SysCtlClockGet() / 1000000;
    sleepClocksPerMS = 2;
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0); // Enable the timer
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1); // Enable the timer
    ROM_TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC|TIMER_CFG_B_ONE_SHOT); // Part A wraps around and starts again, part B shoots once. Used for sleeping
    ROM_TimerConfigure(WTIMER1_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC); // Part A shoots once. Used for futex
    // Configure timer 0A, the system timer
    ROM_TimerPrescaleSet(WTIMER0_BASE, TIMER_A, ticksPerUs*500); // Setup the pre-scaler
    ROM_TimerLoadSet(WTIMER0_BASE, TIMER_A, 4294967295); // Load it with initial value unsigned32_max
    ROM_TimerMatchSet(WTIMER0_BASE, TIMER_A, 0); // Let it run until it reaches 0
    // Configure timer 0B, the sleep timer
    ROM_TimerPrescaleSet(WTIMER0_BASE, TIMER_B, ticksPerUs*500); // Setup the pre-scaler
    // Configure timer 1A, the futex timer
    ROM_TimerPrescaleSet(WTIMER1_BASE, TIMER_A, ticksPerUs*500); // Setup the pre-scaler
    // Enable all interrupts
    ROM_IntPrioritySet(INT_WTIMER0A, SLEEPTIMERPRIORITY);
    ROM_IntPrioritySet(INT_WTIMER0B, SLEEPTIMERPRIORITY);
    ROM_IntPrioritySet(INT_WTIMER1A, SLEEPTIMERPRIORITY);
    ROM_TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT); // Enable the timeout interrupt
    ROM_TimerIntClear(WTIMER0_BASE, TIMER_TIMA_TIMEOUT); // Clear the correct interrupt
    ROM_TimerIntEnable(WTIMER0_BASE, TIMER_TIMB_MATCH); // Enable the correct interrupt
    ROM_TimerIntClear(WTIMER0_BASE, TIMER_TIMB_MATCH); // Let it interrupt on match
    ROM_TimerIntEnable(WTIMER1_BASE, TIMER_TIMA_MATCH); // Enable the correct interrupt
    ROM_TimerIntClear(WTIMER1_BASE, TIMER_TIMA_MATCH); // Let it interrupt on match
    ROM_IntEnable(INT_WTIMER0A);
    ROM_IntEnable(INT_WTIMER0B);
    ROM_IntEnable(INT_WTIMER1A);

    // NVIC_PRI27_R |= 7<<5;
    // UARTprintf("%d\r\n",NVIC_PRI27_R);
#ifdef DEBUG
    // The following setting stalls both the sleep timers when the CPU is stopped for debugging.
    ROM_TimerControlStall(WTIMER0_BASE, TIMER_BOTH, 1);
#endif //DEBUG
    // Initialize the MPU
    // initializeMPU();
    // Initialize malloc mutex
    initReentrantMutex(&(mallocMutex));
    // Process initialization (after this function we are suddenly the kernel)
    initScheduler(&kernelStruct);
    initializeProcesses();

    kernRetQueuePush(__createNewProcess(256, "I seek to flicker", val_ledsFlicker, NULL, 80, 0, &kernelStruct));
    kernRetQueuePush(__createNewProcess(256, "I seek the truth", findNthPrimeNumber, (void*)50, 80, 0, &kernelStruct));
    kernRetQueuePush(__createNewProcess(256, "I seek the truth", findNthPrimeNumber, (void*)117, 80, 0, &kernelStruct));
    kernRetQueuePush(__createNewProcess(256, "I seek the truth", findNthPrimeNumber, (void*)500, 80, 0, &kernelStruct));
    kernRetQueuePush(__createNewProcess(256, "I seek the truth", findNthPrimeNumber, (void*)5000, 80, 0, &kernelStruct));
    kernRetQueuePush(__createNewProcess(256, "I seek the truth", findNthPrimeNumber, (void*)50000, 80, 0, &kernelStruct));
    ROM_TimerEnable(WTIMER0_BASE, TIMER_A); // Start the sleep timer
    CALLSUPERVISOR(SVC_serviced)
    kernelMain();
}
