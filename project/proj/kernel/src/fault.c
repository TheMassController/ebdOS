//This is where a fault lands
#ifndef DEBUG
    #define DEBUG //For now
#endif //DEBUG
#ifdef DEBUG
#include "uartstdio.h"
#include "lm4f120h5qr.h"
#include "asmUtils.h"
#endif //DEBUG

void faultISRHandler(void){
#ifdef DEBUG
    UARTprintf("Hard fault\r\nReset the device to continue...\r\n");
#endif //DEBUG
    while(1) waitForInterrupt();
}

void usageFaultHandler(void){
#ifdef DEBUG
    UARTprintf("Usage fault occured\r\n");
    UARTprintf("UFAULTSTAT info:\r\n");
    UARTprintf("\tDivide-by-Zero Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_DIV0) ? 1 : 0);
    UARTprintf("\tUnaligned Access Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_UNALIGN) ? 1 : 0);
    UARTprintf("\tNo Coprocessor Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_NOCP) ? 1 : 0);
    UARTprintf("\tInvalid PC Load Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_INVPC) ? 1 : 0);
    UARTprintf("\tInvalid State Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_INVSTAT) ? 1 : 0);
    UARTprintf("\tUndefined Instruction Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_UNDEF) ? 1 : 0);
#endif //DEBUG
    while(1) waitForInterrupt();
}

void mpuFaultHandler(void){
#ifdef DEBUG
    UARTprintf("MPU fault occured\r\n");
#endif //DEBUG
    while(1) waitForInterrupt();
}

void busFaultHandler(void){
#ifdef DEBUG
    UARTprintf("Bus Fault\r\n");
    UARTprintf("BFAULTSTAT info\r\n");
    UARTprintf("\tBus Fault Address Register Valid: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_BFARV) ? 1 : 0);
    UARTprintf("\tBus Fault on Floating-Point Lazy State Preservation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_BLSPERR) ? 1 : 0);
    UARTprintf("\tStack Bus Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_BSTKE) ? 1 : 0);
    UARTprintf("\tUnstack Bus Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_BUSTKE) ? 1 : 0);
    UARTprintf("\tImprecise Data Bus Error: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_IMPRE) ? 1 : 0);
    UARTprintf("\tPrecise Data Bus Error: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_PRECISE) ? 1 : 0);
    UARTprintf("\tInstruction Bus Error: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_IBUS) ? 1 : 0);
    
    UARTprintf("\r\nBus Fault Address value: 0x%x\r\n", NVIC_FAULT_ADDR_R);
#endif //DEBUG
    while(1) waitForInterrupt();
}