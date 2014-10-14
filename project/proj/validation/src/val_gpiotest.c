//tests the gpio and such..

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

#define LED_RED 0x2
#define LED_BLUE 0x4
#define LED_GREEN 0x8


int prepare(void){
     // enable PORT F GPIO peripheral
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOE;
    // set LED PORT F pins as outputs
    GPIO_PORTE_DIR_R = LED_RED|LED_BLUE|LED_GREEN|0x1;
    // enable digital for LED PORT F pins
    GPIO_PORTE_DEN_R = LED_RED|LED_BLUE|LED_GREEN|0x1;
    // clear all PORT F pins
    GPIO_PORTE_DATA_R = 0;
    //ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //volatile int i;
    //for (i = 0; i <10; ++i);
    //ROM_GPIODirModeSet(SYSCTL_PERIPH_GPIOF,255,GPIO_DIR_MODE_OUT);
    //return 0;
}

int testGPIO(void){
    UARTprintf("GPIO test\r\n");
    prepare();
    volatile unsigned i;
    while(1){
        GPIO_PORTE_DATA_R ^= LED_BLUE;
        for(i = 0; i < 1000000; i++);
    }
    return 1;
}
