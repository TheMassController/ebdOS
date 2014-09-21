//This is where a fault lands

#include "uartstdio.h"
#include "asmUtils.h"

void faultISRHandler(unsigned int * hardfault_args){
    UARTprintf("Hard Fault occured\r\n");
    unsigned int stacked_r0;
    unsigned int stacked_r1;
    unsigned int stacked_r2;
    unsigned int stacked_r3;
    unsigned int stacked_r12;
    unsigned int stacked_lr;
    unsigned int stacked_pc;
    unsigned int stacked_psr;
   
    stacked_r0 = ((unsigned long) hardfault_args[0]);
    stacked_r1 = ((unsigned long) hardfault_args[1]);
    stacked_r2 = ((unsigned long) hardfault_args[2]);
    stacked_r3 = ((unsigned long) hardfault_args[3]);
   
    stacked_r12 = ((unsigned long) hardfault_args[4]);
    stacked_lr = ((unsigned long) hardfault_args[5]);
    stacked_pc = ((unsigned long) hardfault_args[6]);
    stacked_psr = ((unsigned long) hardfault_args[7]);
   
    UARTprintf ("\n\n[Hard fault handler - all numbers in hex]\n");
    UARTprintf ("R0 = %x\n", stacked_r0);
    UARTprintf ("R1 = %x\n", stacked_r1);
    UARTprintf ("R2 = %x\n", stacked_r2);
    UARTprintf ("R3 = %x\n", stacked_r3);
    UARTprintf ("R12 = %x\n", stacked_r12);
    UARTprintf ("LR [R14] = %x  subroutine call return address\n", stacked_lr);
    UARTprintf ("PC [R15] = %x  program counter\n", stacked_pc);
    UARTprintf ("PSR = %x\n", stacked_psr);
    UARTprintf ("BFAR = %x\n", (*((volatile unsigned long *)(0xE000ED38))));
    UARTprintf ("CFSR = %x\n", (*((volatile unsigned long *)(0xE000ED28))));
    UARTprintf ("HFSR = %x\n", (*((volatile unsigned long *)(0xE000ED2C))));
    UARTprintf ("DFSR = %x\n", (*((volatile unsigned long *)(0xE000ED30))));
    UARTprintf ("AFSR = %x\n", (*((volatile unsigned long *)(0xE000ED3C))));
    //UARTprintf ("SCB_SHCSR = %x\n", SCB->SHCSR);
    while(1){
        waitForInterrupt();
    }
}
