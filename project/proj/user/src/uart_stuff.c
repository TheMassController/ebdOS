#include <hw_types.h>       //Contains the types
#include <sysctl.h>         //Contains defines for PLL regs
#include <rom_map.h>        //Call functions directly from the ROM if available
#include <rom.h>            //Declare ROM addresses for rom funcs
#include <hw_memmap.h>      //address of GPIO etc
#include <gpio.h>           //Address of GPIO stuff
#include <uart.h>           //UART addresses and stuff
#include <uartstdio.h>      //UART printf n stuff

#include "sleep.h"
#include "sysCalls.h"
/**
 * UART1 is selected:
 * PC4 (J4.04) UART1Rx  (16)
 * PC5 (J4.05) UART1Tx  (15)
 * PC6 (J4.06) GPIO     (14)
 *
 * A reset signal has to be send to the FPGA from time to time. This will be done trough PC6/GPIO
 */

static void printReceive(void){
    if (ROM_UARTCharsAvail(UART1_BASE)){
        long c;
        while((c = ROM_UARTCharGetNonBlocking(UART1_BASE)) != -1){
            UARTprintf("Received from UART1: %d (masked: %d)\n", (int)c, ((int)c) & 255);
        }
    }
}

void numberPusher(void* things){
    (void)(things);
    // Toggle the reset for 1 s
    ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
    sleepS(1);
    ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
    while(1) {
        for (int i = 0; i < 256; ++i){
            printReceive();
            ROM_UARTCharPut(UART1_BASE, (char)i);
            sleepS(1);
        }
    }
}

int initNumberPusher(void){
    // First, enable the clock to C
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    // Enable the clock to UART 1
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    // Enable the pins
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    // Enable the UART chip
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5);
    // Setup the UART
    ROM_UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
    ROM_UARTConfigSetExpClk(UART1_BASE, 16000000, 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_EVEN);
    unsigned long pulBaud, pulConfig;
    ROM_UARTConfigGetExpClk(UART1_BASE, 16000000, &pulBaud, &pulConfig);
    UARTprintf("Config: %d\n", pulBaud);
    // Set up the reset pin
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
    int pid = createChildProcess(128, "numberPusher", numberPusher, NULL);
    if (pid == -1) return -1;
    return 0;
}
