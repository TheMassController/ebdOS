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

#define SLEEPTIMEMS 250

static void prepareHardware(void){
    //F gate: button 2
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //Onboard LED, F gate
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
}

void val_ledsFlicker(void){
    prepareHardware();
    while(1){
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_1);                    // Red
        sleepMS(SLEEPTIMEMS);
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_1 | GPIO_PIN_2);
        sleepMS(SLEEPTIMEMS);
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_2);                    // Blue
        sleepMS(SLEEPTIMEMS);
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_2 | GPIO_PIN_3);
        sleepMS(SLEEPTIMEMS);
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_3);                    // Green
        sleepMS(SLEEPTIMEMS);
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_3 | GPIO_PIN_1);
        sleepMS(SLEEPTIMEMS);
    }
}
