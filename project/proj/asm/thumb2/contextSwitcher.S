.syntax unified
.cpu cortex-m4
.thumb
@ Author: Jacko Dirks
@ Description: Contains the PendSV handler and thus the context switcher

.global pendSVHandler
.extern currentProcess
.extern nextProcess

pendSVHandler:
    LDR     R0,     =0xFF9
    MOV     PC,     R0
    @LDR     R0,     =nextProcess        @Load the PSP of the next process
    @LDR     R2,     =currentProcess     @Load the PSP of the next process
    @MRS     R1,     PSP                 @R1 = PSP
    @STMDB   R1!,   {R4-R11}             @Move R4 to R11 to param R0, while decreasing R0
    @STR     R1,     [R2]                @Store the moved PSP at currentProcess
    @MOV     R1,     R0                  @Move R0 to R1
    @LDMFD   R1!,    {R4-R11}            @Move from ram to regs while increasing R0
    @ADD     R0,     R0,     1           @Add 1 to R0
    @LDR     R0,     [R0]                @Load the content of the memaddr stored at R0 (the PID of currentProcess)
    @CBZ     R0,     continueFromMSP     @If the PID is zero, branch
    @LDR     PC,     =0xFFFFFFFD         @Load the correct value to continue from PSP to PC
@continueFromMSP:
    @LDR     PC,     =0xFFFFFFF9         @Load the corrent value to continue from MSP to PC
