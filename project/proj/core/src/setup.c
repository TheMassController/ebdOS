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

#include "asmUtils.h" //setpsp function
#include "process.h" //Everything related to the processes
#include "mutex.h" //Everything related to mutexes
#include "reentrantMutex.h" //Everything related to mutexes
#include "kernelQueue.h" //For the initialization of the kernelQueue

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

extern ReentrantMutex* mallocMutex;

void setupHardware(void){
    //Setup the PLL
    //Datasheet pp 217
    //Driver API pp 284
    //Sysclock = 80 Mhz (maxmimum)
    //PLL = 400, predivide = /2, 200/80 = 2.5, so we want to enable the default PLL setup and then divide by 2.5
    //                 Divide input by 2.5|Use the PLL |Use the main oscillator|Main oscillator is 16 Mhz
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL          |SYSCTL_OSC_MAIN        |SYSCTL_XTAL_16MHZ);

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
    //Reset both registers to all 0's
    NVIC_SYS_PRI2_R &= 0;
    NVIC_SYS_PRI3_R &= 0;     //Debug level is now 0.
    NVIC_SYS_PRI2_R |= 1<<29; //SVC gets 1 (lower is higher). Datasheet pp 166
    NVIC_SYS_PRI3_R |= 2<<29; //Systick gets 2. Datasheet pp 167
    NVIC_SYS_PRI3_R |= 3<<21; //pendSV gets 3. Datasheet pp 167

    //Enable all non-special interrupts
    ROM_IntMasterEnable();

    //Setup the sleep clock.    
    //The first 32 bit timer is the sleep clock. It counts slow and interrupts on overflow.
    //32-bit wide, one clock increase every 40000 cycles. At this point, the clock is 80.000.000 cycles per second. So this clock changes 2000 times per second
    //2 clocks is a ms, 2000 clocks is a second
    //The timer runs from high to low
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0); //Enable the timer
    ROM_TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC); //Setup wide timer 0, part A.
    ROM_TimerPrescaleSet(WTIMER0_BASE, TIMER_A, 40000); //Setup the pre-scaler
    ROM_TimerLoadSet(WTIMER0_BASE, TIMER_A, 4294967295); //Load it with initial value 0
    ROM_TimerMatchSet(WTIMER0_BASE, TIMER_A, 0); //Let it run until it reaches max
    ROM_TimerIntClear(WTIMER0_BASE, TIMER_TIMA_TIMEOUT); //Clear the correct interrupt
    ROM_TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT); //Enable the timeout interrupt
    ROM_IntEnable(INT_WTIMER0A);
    sleepClocksPerMS = 2;
 
    //Creat pid 1: the kernel
    currentProcess = (struct Process*)malloc(sizeof(struct Process));
    currentProcess->pid = 1;
    __createNewProcess(0, 67, "Kernel", NULL, NULL, 254);
    kernel = processesReady;
    setPSP(kernel->stackPointer);
    free(currentProcess);
    currentProcess = kernel;
    kernel->priority = 100;
    
    //Create the other two special processes: sleep and hibernate
    __createNewProcess(0, MINSTACKLEN, "SleepProcess", &__sleepProcessFunc, NULL, 255);
    __createNewProcess(0, MINSTACKLEN, "HibernateProcess", &__hibernateProcessFunc, NULL, 255);
    hibernateProcess = processesReady->nextProcess->nextProcess; //Order: kernel, sleepprocess, hibernateprocess
    processesReady->nextProcess->nextProcess = NULL;
    sleepProcess = processesReady->nextProcess;
    processesReady->nextProcess = NULL; 

    //Create the kernelQueue
    kernelQueue = (struct KernelQueue*)malloc(sizeof(struct KernelQueue));
    kernelQueue->existingItems = createSemaphore(255);
    kernelQueue->readyItems = createSemaphore(255);
    kernelQueue->listProtectionMutex = createMutex();
    kernelQueue->firstItem = NULL;

    //Initialize malloc mutex
    mallocMutex = createReentrantMutex();
}

//This is the last function to run before the scheduler starts. At this point everything is setup, including the main user processes. After this function the kernel will fall asleep and only wake up to handle requests from other processes
void finishBoot(void){
    ROM_TimerEnable(WTIMER0_BASE, TIMER_A); //Start the sleep timer     
    NVIC_ST_CTRL_R = 0x3; //Run from PIOSC, generate interrupt, start running (datasheet pp 133) 
    NVIC_INT_CTRL_R |= (1<<26); //Set the SysTick to pending: kick-off the scheduler
}
