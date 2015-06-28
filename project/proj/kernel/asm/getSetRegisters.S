.thumb
.syntax unified
.cpu cortex-m4
@ Author: Jacko Dirks
@ Description: Contains functions to get register values from the CPU

	.global getMSP
    .global setPSP

getMSP:
	MRS R0, msp 	@Move the stack pointer to the return register, R0
	MOV pc, lr		@Return by moving the link register to the program counter

setPSP:
    MSR psp, R0     @Move R0 to the PSP
    MOV pc, lr      @return
