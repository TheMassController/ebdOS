//This file makes sure all the default settings are set

#include "hw_types.h" //Contains the types
#include "sysctl.h"     //Contains defines for PLL regs
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include "hw_memmap.h" //address of GPIO etc
#include "gpio.h" //Address of GPIO stuff
#include "uart.h" //UART addresses and stuff
#include "uartstdio.h" //UART printf n stuff
#include "stdlib.h" //Malloc & Free
#include "process.h" //Process var
#include "getSetRegisters.h"
#include "lm4f120h5qr.h" //Hardware regs
#include "timer.h" //The subaddresses of timers
#include "hw_ints.h" //Memory addresses of hw interrupts
#include "interrupt.h"

#include "asmUtils.h" //setpsp function
#include "process.h" //Everything related to the processes
#include "mutex.h" //Everything related to mutexes
#include "reentrantMutex.h" //Everything related to mutexes
#include "malloc.h"

#define SAVETEMPSTACKLEN 35 //8 regs, 32 bit (=4 byte) => 32 byte for reg + 3 byte for possible allignment.
#define MINSTACKLEN 100 //16 regs, 32 bit (=4 byte) => 64 byte for reg + 3 byte for possible allignment. The other bytes are so that I do not have to write the hibernate and sleep funcs in assemblye (the compiler will push more regs to stack)
#define BAUDRATE 115200 //Default baudrate, fastest possible

extern struct Process* currentProcess;
extern struct Process* sleepProcess;
extern struct Process* hibernateProcess;
extern struct Process* processesReady;
extern struct Process* kernel;
extern struct KernelQueue* kernelQueue;

extern void __sleepProcessFunc(void* param);
extern void __hibernateProcessFunc(void* param);

extern unsigned sleepClocksPerMS;

extern struct ReentrantMutex mallocMutex;
extern int initialized;

void initializeProcesses(void);
void initKernelQueue(void);

void setupHardware(void){
    //Setup the PLL
    //Datasheet pp 217
    //Driver API pp 284
    //Sysclock = 80 Mhz (maxmimum)
    //PLL = 400, predivide = /2, 200/80 = 2.5, so we want to enable the default PLL setup and then divide by 2.5
    //                 Divide input by 2.5|Use the PLL |Use the main oscillator|Main oscillator is 16 Mhz
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL          |SYSCTL_OSC_MAIN        |SYSCTL_XTAL_16MHZ);

    //Enable all possible sys interrupts
    //Datasheet pp 168
    //Enable the usage fault
    NVIC_SYS_HND_CTRL_R |= 0x1<<18;
    //Enable the bus fault
    NVIC_SYS_HND_CTRL_R |= 0x1<<17;
    //Enable the mem fault
    NVIC_SYS_HND_CTRL_R |= 0x1<<16;

    //Setup the Debug UART out
    //Enable the correct interfaces: GPIOA for USB Debug, UART0 for USB Debug
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    //Setup GPIO A as UART
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1); 
    //Start the UART0 with baud BAUD 
    UARTStdioInitExpClk(0,BAUDRATE);

    //For scheduling: systick
    //It is connected to the PIOSC/4, which means that is it connected to a very precise 4 Mhz clock
    //Initially configured as 1 tick per ms. This is equal to 4000 ticks on the 4 Mhz clock.
    NVIC_ST_RELOAD_R = 3999; //Fire every 4000 clocks (datasheet pp 135)
    NVIC_ST_CURRENT_R = 0; //Clear the register by writing to it with any value (datasheet pp 118, 136)
    
    //Hibernate setup
    //If the program finishes, we want to hibernate
    //This register setsup all the variables necessary to do that.
    while (!(HIB_CTL_R & 1<<31)); //Wait until the write bit is clear
    HIB_CTL_R = 320;    //Dont check battery when hibernating, Keep pinouts,
                        //dont check battery before hibernation, enable hib_clk, dont listen to pin, 
                        //dont listen to rtc, no hibernation request, no hibernation RTC module  
                        //Datasheet pp 470                        
    
    //Setup the interrupt priorities
    //System interrupt levels: debug, SVC, systick, pendSV
    //Reset both registers to all 0's
    NVIC_SYS_PRI2_R &= 0;
    NVIC_SYS_PRI3_R &= 0;     //Debug level is now 0.
    NVIC_SYS_PRI2_R |= 0<<29; //SVC gets 0 (lower is higher, 7 is lowest). Datasheet pp 166
    NVIC_SYS_PRI3_R |= 0<<29; //Systick gets 7. Datasheet pp 167
    NVIC_SYS_PRI3_R |= 7<<21; //pendSV gets 7. Datasheet pp 167.
    //The pendSV has this low priority so that context switches can be called from an interrupt (stack is in a wrong state when inside an interrupt)
    //Systick has a high priority because else the state of the processesReady list can not be guaranteed not to change during the run. If it gets changed during the run all sorts of nasty things can happen
    //So when you call the context switcher from an interrupt, the context switch will happen after every currently running interrupt is finished and every higher level interrupt is handled
    //During the actual context switch all interupts are disabled

    //Enable all non-special interrupts
    //With this thing disabled, the SVC, PendSV, Systick etc "faults" also wont run. Except Hard Fault and NMI, because they are badass like that. 
    ROM_IntMasterEnable();

    //Setup the sleep clock.    
    //The first 32 bit timer is the sleep clock. It counts slow and interrupts on overflow.
    //32-bit wide, one clock increase every 40000 cycles. At this point, the clock is 80.000.000 cycles per second. So this clock changes 2000 times per second
    //2 clocks is a ms, 2000 clocks is a second
    //The timer runs from high to low
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0); //Enable the timer
    ROM_TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC|TIMER_CFG_B_ONE_SHOT); //Setup wide timer 0, part A.
    ROM_TimerPrescaleSet(WTIMER0_BASE, TIMER_A, 40000); //Setup the pre-scaler
    ROM_TimerLoadSet(WTIMER0_BASE, TIMER_A, 4294967295); //Load it with initial value unsigned32_max
    ROM_TimerMatchSet(WTIMER0_BASE, TIMER_A, 0); //Let it run until it reaches 0
    ROM_TimerIntClear(WTIMER0_BASE, TIMER_TIMA_TIMEOUT); //Clear the correct interrupt
    ROM_TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT); //Enable the timeout interrupt
    ROM_IntEnable(INT_WTIMER0A);
    ROM_IntPrioritySet(INT_WTIMER0A, 200);
    
    sleepClocksPerMS = 2;

    //Configure timer B, the other vital timer in sleeping
    ROM_TimerPrescaleSet(WTIMER0_BASE, TIMER_B, 40000); //Setup the pre-scaler
    ROM_TimerIntClear(WTIMER0_BASE, TIMER_TIMB_MATCH); //Let it interrupt on match
    ROM_TimerIntEnable(WTIMER0_BASE, TIMER_TIMB_MATCH); //Enable the correct interrupt
    ROM_IntEnable(INT_WTIMER0B);
    ROM_IntPrioritySet(INT_WTIMER0B, 200);
    //NVIC_PRI27_R |= 7<<5;
    //UARTprintf("%d\r\n",NVIC_PRI27_R);

    //Initialize malloc mutex
    initReentrantMutex(&(mallocMutex));
    initializeProcesses();
    initKernelQueue();

    //Create the kernelQueue
    //kernelQueue = malloc(sizeof(struct KernelQueue));
    //kernelQueue->existingItems = createSemaphore(255);
    //kernelQueue->readyItems = createSemaphore(255);
    //kernelQueue->listProtectionMutex = createMutex();
    //kernelQueue->firstItem = NULL;

}

//This is the last function to run before the scheduler starts. At this point everything is setup, including the main user processes. After this function the kernel will fall asleep and only wake up to handle requests from other processes
void finishBoot(void){
    ROM_TimerEnable(WTIMER0_BASE, TIMER_A); //Start the sleep timer     
    NVIC_INT_CTRL_R |= (1<<28); //Set the pendSV to pending: kick-off the scheduler
}
