.syntax unified
.cpu cortex-m4
.thumb
@ Author: Jacko Dirks
@ Description: Contains functions to move the CPU regs between RAM and CPU

    .global saveRegistersToMSPAndMoveMSP
    .global loadRegistersFromMSPAndMoveMSP
    .global loadRegistersFromPSPAndMovePSP
    .global saveRegistersToPSPAndMovePSP
    
saveRegistersToMSPAndMoveMSP:
    MRS     R0, MSP         @Move the MSP to R0
    STMDB   R0! ,   {R4-R11}    @Move R4 to R11 to param R0, while decreasing R0
    MSR     MSP, R0         @Move R0 back to the MSP
    MOV     pc , LR         @Return by moving the link register to the program counter


loadRegistersFromMSPAndMoveMSP:
    MRS     R0, MSP         @Move the MSP to R0
    LDMFD   R0! , {R4-R11}      @Move from ram to regs while increasing R0
    MSR     MSP, R0         @Move R0 back to the MSP
    MOV     pc , LR         @Return by moving the link register to the program counter

saveRegistersToPSPAndMovePSP:
    MRS     R0, PSP         @Move the PSP to R0
    STMDB   R0! ,   {R4-R11}    @Move R4 to R11 to param R0, while decreasing R0
    MSR     PSP, R0         @Move R0 back to the PSP
    MOV     pc , LR         @Return by moving the link register to the program counter


loadRegistersFromPSPAndMovePSP:
    MRS     R0, PSP         @Move the PSP to R0
    LDMFD   R0! , {R4-R11}      @Move from ram to regs while increasing R0
    MSR     PSP, R0         @Move R0 back to the PSP
    MOV     pc , LR         @Return by moving the link register to the program counter
