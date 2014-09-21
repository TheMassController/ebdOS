.syntax unified
.cpu cortex-m4
.thumb
@ Author: Jacko Dirks
@ Description: Contains util functions that can only be implemented in assembly

    .global waitForInterrupt
    .global forceManualReturn
    
waitForInterrupt:
    WFI             @Wait for interrupt
    MOV     PC, LR  @Return by moving the link register to the program counter
    
forceManualReturn:
    MOV     pc , R0     @Return by moving the R0 register (param 0) to the program counter
