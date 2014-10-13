//This file makes sure all the default settings are set
//The following things will be set:
//PLL: to maximum speed

//#include "hw_memmap.h"      //Contains the memory addresses needed
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

#define MINSTACKLEN 35 //32 byte for reg + 3 bit for possible allignment
#define BAUDRATE 115200

extern struct Process* kernel;
extern struct Process* currentProcess;
extern struct Process* sleepProcess;
extern struct Process* hibernateProcess;
extern struct Process* firstProcess;

extern void sleepProcessFunc(void);
extern void hibernateProcessFunc(void);

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
    //Initially configured as 1 tick per 500 us. (1/2 ms). This is equal to 2000 ticks on the 4 Mhz clock.
    NVIC_ST_RELOAD_R = 1999; //Fire every 2000 clocks (datasheet pp 135)
    NVIC_ST_CURRENT_R = 0; //Clear the register by writing to it with any value (datasheet pp 118, 136)
    
    //Hibernate setup
    //If the program finishes, we want to hibernate
    //This register setsup all the variables necessary to do that.
    //while (!(HIB_CTL_R & 1<<31)); //Wait until the write bit is clear
    //HIB_CTL_R = 320;    //Dont check battery when hibernating, Keep pinouts,
                        //dont check battery before hibernation, enable hib_clk, dont listen to pin, 
                        //dont listen to rtc, no hibernation request, no hibernation RTC module  
                        //Datasheet pp 470                        
 
    //Creat pid 0: the kernel
    kernel = (struct Process*)malloc(sizeof(struct Process));
    kernel->pid = 0;
    kernel->mPid = 0;
    kernel->name = "kernel";
    kernel->stack = (void*) malloc(MINSTACKLEN); 
    kernel->stackPointer = (void*)((((long)kernel->stack) + MINSTACKLEN - 4) & (long)0xFFFFFFFC );
    setPSP(kernel->stackPointer);
    kernel->state = WAIT;
    //These params will not be used
    kernel->nextProcess = NULL;

    currentProcess = kernel;
    
    //Create the other two special processes: sleep and hibernate
    __createNewProcess(0, MINSTACKLEN, "SleepProcess", (processFunc)&sleepProcessFunc, NULL, 255);
    __createNewProcess(0, MINSTACKLEN, "HibernateProcess", (processFunc)&hibernateProcessFunc, NULL, 255);
    hibernateProcess = firstProcess->nextProcess;
    firstProcess->nextProcess = NULL;
    sleepProcess = firstProcess;
    firstProcess = NULL; 

    //NVIC_ST_CTRL_R = 0x3; //Run from PIOSC, generate interrupt, start running (datasheet pp 133) 
}
