//This is where a fault lands
#ifndef DEBUG
    #define DEBUG //For now
#endif //DEBUG
#ifdef DEBUG
#include <uartstdio.h>
#include <lm4f120h5qr.h>

#include "scheduler.h"
#include "core/inc/coreUtils.h"
#include "process.h"
#endif //DEBUG

static void dumpInformation(void){
    struct Process* currentProcess = getCurrentProcess();
    UARTprintf("HFAULTSTAT info:\r\n");
    UARTprintf("\tDebug Event: %d\r\n", (NVIC_HFAULT_STAT_R & NVIC_HFAULT_STAT_DBG) ? 1 : 0);
    UARTprintf("\tForced Hard Fault: %d\r\n", (NVIC_HFAULT_STAT_R & NVIC_HFAULT_STAT_FORCED) ? 1 : 0);
    UARTprintf("\tVector Table Read Fault: %d\r\n", (NVIC_HFAULT_STAT_R & NVIC_HFAULT_STAT_VECT) ? 1 : 0);
    UARTprintf("UFAULTSTAT info:\r\n");
    UARTprintf("\tDivide-by-Zero Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_DIV0) ? 1 : 0);
    UARTprintf("\tUnaligned Access Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_UNALIGN) ? 1 : 0);
    UARTprintf("\tNo Coprocessor Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_NOCP) ? 1 : 0);
    UARTprintf("\tInvalid PC Load Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_INVPC) ? 1 : 0);
    UARTprintf("\tInvalid State Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_INVSTAT) ? 1 : 0);
    UARTprintf("\tUndefined Instruction Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_UNDEF) ? 1 : 0);
    UARTprintf("\tMemory Management Fault Address Register Valid: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_MMARV) ? 1 : 0);
    UARTprintf("\tMemory Management Fault on Floating-Point Lazy State Preservation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_MLSPERR) ? 1 : 0);
    UARTprintf("\tStack Access Violation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_MSTKE) ? 1 : 0);
    UARTprintf("\tUnstack Access Violation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_MUSTKE) ? 1 : 0);
    UARTprintf("\tData Access Violation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_DERR) ? 1 : 0);
    UARTprintf("\tInstruction Access Violation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_IERR) ? 1 : 0);
    UARTprintf("\tBus Fault Address Register Valid: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_BFARV) ? 1 : 0);
    UARTprintf("\tBus Fault on Floating-Point Lazy State Preservation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_BLSPERR) ? 1 : 0);
    UARTprintf("\tStack Bus Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_BSTKE) ? 1 : 0);
    UARTprintf("\tUnstack Bus Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_BUSTKE) ? 1 : 0);
    UARTprintf("\tImprecise Data Bus Error: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_IMPRE) ? 1 : 0);
    UARTprintf("\tPrecise Data Bus Error: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_PRECISE) ? 1 : 0);
    UARTprintf("\tInstruction Bus Error: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_IBUS) ? 1 : 0);
    UARTprintf("\r\nBus Fault Address value: 0x%x\r\n", NVIC_FAULT_ADDR_R);
    UARTprintf("\tMMADDR value: 0x%X\r\n", NVIC_MM_ADDR_R);
    UARTprintf("\tCurrent process name: %s\r\n", currentProcess->name);
}


void faultISRHandler(void){
#ifdef DEBUG
    UARTprintf("Hard fault\r\nReset the device to continue...\r\n");
    dumpInformation();
#endif //DEBUG
    while(1) waitForInterrupt();
}

void NMIHandler(void){
#ifdef DEBUG
    UARTprintf("NMI fault\r\nReset the device to continue...\r\n");
    dumpInformation();
#endif //DEBUG
    while(1) waitForInterrupt();
}


void usageFaultHandler(void){
#ifdef DEBUG
    struct Process* currentProcess = getCurrentProcess();
    UARTprintf("Usage fault occured\r\n");
    UARTprintf("UFAULTSTAT info:\r\n");
    UARTprintf("\tDivide-by-Zero Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_DIV0) ? 1 : 0);
    UARTprintf("\tUnaligned Access Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_UNALIGN) ? 1 : 0);
    UARTprintf("\tNo Coprocessor Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_NOCP) ? 1 : 0);
    UARTprintf("\tInvalid PC Load Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_INVPC) ? 1 : 0);
    UARTprintf("\tInvalid State Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_INVSTAT) ? 1 : 0);
    UARTprintf("\tUndefined Instruction Usage Fault: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_UNDEF) ? 1 : 0);
    UARTprintf("\tCurrent process name: %s\r\n", currentProcess->name);
#endif //DEBUG
    while(1) waitForInterrupt();
}

void mpuFaultHandler(void){
#ifdef DEBUG
    struct Process* currentProcess = getCurrentProcess();
    UARTprintf("MPU fault occured\r\n");
    UARTprintf("UFAULTSTAT info:\r\n");
    UARTprintf("\tMemory Management Fault Address Register Valid: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_MMARV) ? 1 : 0);
    UARTprintf("\tMemory Management Fault on Floating-Point Lazy State Preservation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_MLSPERR) ? 1 : 0);
    UARTprintf("\tStack Access Violation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_MSTKE) ? 1 : 0);
    UARTprintf("\tUnstack Access Violation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_MUSTKE) ? 1 : 0);
    UARTprintf("\tData Access Violation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_DERR) ? 1 : 0);
    UARTprintf("\tInstruction Access Violation: %d\r\n", (NVIC_FAULT_STAT_R & NVIC_FAULT_STAT_IERR) ? 1 : 0);
    UARTprintf("\r\n\tMMADDR value: 0x%X\r\n", NVIC_MM_ADDR_R);
    UARTprintf("\tCurrent process name: %s\r\n", currentProcess->name);
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
