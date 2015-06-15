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

#include "sleep.h"
#include "process.h"
#include "stdlib.h"
#include "semaphore.h"
#include "sysCalls.h"

extern struct Process* currentProcess;

#define UNUSED(x) (void)(x) //To suppress compiler warning

struct Semaphore sem;

void prepareHardware(void){
    //F gate: button 2
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ROM_GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
    ROM_GPIOPinIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
    ROM_GPIOPinIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
    ROM_IntPrioritySet(INT_GPIOF, 200);
    ROM_IntEnable(INT_GPIOF);

    //B gate: 4 io's
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
    ROM_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_3);
    ROM_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
    ROM_GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_FALLING_EDGE);
    ROM_GPIOPinIntClear(GPIO_PORTB_BASE, GPIO_PIN_3);
    ROM_GPIOPinIntEnable(GPIO_PORTB_BASE, GPIO_PIN_3);
    ROM_IntPrioritySet(INT_GPIOB, 200);
    ROM_IntEnable(INT_GPIOB);

    //Onboard LED, F gate
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
}

void gpioBInterrup(void){
    ROM_GPIOPinIntClear(GPIO_PORTB_BASE, GPIO_PIN_3);
    increaseSemaphoreNonBlocking(&sem);
}

//void button2Interrupt(void){
//    ROM_GPIOPinIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
//    increaseSemaphoreNonBlocking(&sem);
//}

void printProcessInfo(void){
    UARTprintf("My name is: %s, my PID is %u, my mPid is: %u\r\n", currentProcess->name, currentProcess->pid, currentProcess->mPid);
}

void ledsFlicker(void){
    printProcessInfo();
    while(1){
        UARTprintf("Hoi\r\n");
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        decreaseSemaphoreBlocking(&sem);
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_2);
        decreaseSemaphoreBlocking(&sem);
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_3);
        decreaseSemaphoreBlocking(&sem);
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_1);
        decreaseSemaphoreBlocking(&sem);
    }
}

void ledsDance(void){
    printProcessInfo();
    if (createProcess(1024, "ledsFlicker", ledsFlicker, NULL, 20) != 0){
        UARTprintf("My child did not spawn :(\r\n");
    }
    while(1){
        ROM_GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0,GPIO_PIN_0);
        sleepMS(500);
        ROM_GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0,0);
        ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);
        sleepMS(500);
        ROM_GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1,0);
        ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2);
        sleepMS(500);
        ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);
        ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);
        sleepMS(500);
        ROM_GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1,0);
    }
}

void ledsDanceMain(void){
    printProcessInfo();
    prepareHardware();
    //initSemaphore(&sem, 1);
    //if(createProcess(1024, "ledsDance", ledsDance, NULL, 5) == 2){
    //    UARTprintf("FAILURE\r\n");
    //} else {
    //    UARTprintf("Leds Dance!!\r\n");
    //}

}
