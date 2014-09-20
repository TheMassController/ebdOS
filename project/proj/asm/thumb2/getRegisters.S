.thumb
.syntax unified
@ Author: Jacko Dirks
@ Description: Contains functions to get register values from the CPU

	.global getMSP
    .global getPSP
    .global getR7
	
getMSP:
	MRS 	R0 , msp 	@Move the stack pointer to the return register, R0
	MOV 	pc , lr		@Return by moving the link register to the program counter

getPSP:
	MRS 	R0 , psp 	@Move the stack pointer to the return register, R0
	MOV 	pc , lr		@Return by moving the link register to the program counter

getR7:
    MOV     R0, R7      @Move R7 to the return reg
	MOV 	pc , lr		@Return by moving the link register to the program counter
