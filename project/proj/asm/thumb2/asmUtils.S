.thumb
.syntax unified
@ Author: Jacko Dirks
@ Description: Contains util functions that can only be implemented in assembly

    .global waitForInterrupt
    .global forceManualReturn
    .global saveRegistersToMSP
    
waitForInterrupt:
    WFI             @Wait for interrupt
    MOV     PC, LR  @Return by moving the link register to the program counter
    
forceManualReturn:
    MOV     pc , R0     @Return by moving the R0 register (param 0) to the program counter

saveRegistersToMSPAndMoveMSP:
    MRS     R0, msp         @Move the MSP to R0
    STMDB   R0! ,   {r4-r11}    @Move R4 to R11 to param R0, while decreasing R0
    MSR     msp, R0         @Move R0 back to the MSP
    MOV     pc , LR         @Return by moving the link register to the program counter
