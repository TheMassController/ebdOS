.syntax unified
.cpu cortex-m4
.thumb
@ Author: Jacko Dirks
@ Description: Contains functions to get register values from the CPU

	.global setMSP
    .global setPSP
    .global setR7
    .global notSetR7
	
setMSP:
	MSR 	msp,R0 	    @Move R0 (param0) to MSP
	MOV 	pc , lr		@Return by moving the link register to the program counter

setPSP:
	MSR 	psp , R0 	@Move R0 (param 0) to psp
	MOV 	pc , lr		@Return by moving the link register to the program counter

notSetR7:
    MOV     R4, R0      @Move R0 to R7
    MOV     R5, R0      @Move R0 to R7
    MOV     R6, R0      @Move R0 to R7
    MOV     R8, R0      @Move R0 to R7
    MOV     R9, R0      @Move R0 to R7
    MOV     R10, R0      @Move R0 to R7
    MOV     R11, R0      @Move R0 to R7
	MOV 	pc , lr		@Return by moving the link register to the program counter

setR7:
    MOV     R7, R0  
    MOV     pc, lr
