//This is where a fault lands

#include "uartstdio.h"
#include "asmUtils.h"
#include "lm4f120h5qr.h"

void faultISRHandler(void){
    UARTprintf("Hard fault\r\nReset the device to continue...\r\n");
    while(1);
}

void usageFaultHandler(void){
    UARTprintf("Usage fault occured\r\n");
    UARTprintf("Usage fault status register: 0x%x\r\n",NVIC_FAULT_STAT_R);
    while(1);
}

void mpuFaultHandler(void){
    UARTprintf("MPU fault occured\r\n");
}

void busFaultHandler(void){
    UARTprintf("Bus Fault\r\n");
    UARTprintf("Bus Fault Address value: 0x%x\r\n", NVIC_FAULT_ADDR_R);
}
