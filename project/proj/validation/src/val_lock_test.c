#include "hw_types.h" //Contains the types
#include "sysctl.h"     //Contains defines for PLL regs
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include "hw_memmap.h" //address of GPIO etc
#include "gpio.h" //Address of GPIO stuff
#include "uart.h" //UART addresses and stuff
#include "uartstdio.h" //UART printf n stuff
#include "hw_ints.h" //Memory addresses of hw interrupts
#include "interrupt.h"

#include "binarySemaphore.h"
#include "mutex.h"
#include "sleep.h"
#include "coreUtils.h"

struct BinarySemaphore bSem;
struct Mutex mut;

extern struct Process* currentProcess;

void prepHardware(void){
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ROM_GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
    ROM_GPIOPinIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
    ROM_GPIOPinIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
    ROM_IntPrioritySet(INT_GPIOF, 200);
    ROM_IntEnable(INT_GPIOF);
}

void button2Interrupt(void){
    ROM_GPIOPinIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
    releaseBinarySemaphore(&bSem);
}

//Should run with elevated privileges
void mainProcessLocker(void){
    prepHardware();
    initBinarySemaphore(&bSem);
    initMutex(&mut);
    //while(1) waitForInterrupt();
    while(1){
        lockBinarySemaphoreBlocking(&bSem);
        UARTprintf("I gots it!\n");
    }

}

void mutPasser(void){
    while(1){
        lockMutexBlocking(&mut);
        UARTprintf("My name is %s and I have a mutex!\n", currentProcess->name);
        sleepS(2);
        releaseMutex(&mut);
        sleepS(2);
    }
}
