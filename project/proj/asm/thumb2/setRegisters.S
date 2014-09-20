.syntax unified
@ Author: Jacko Dirks
@ Description: Contains functions to get register values from the CPU

	.global setMSP
    .global setPSP
    .global setR7
	
setMSP:
	MSR 	msp,R0 	    @Move R0 (param0) to MSP
	MOV 	pc , lr		@Return by moving the link register to the program counter

setPSP:
	MSR 	psp , R0 	@Move R0 (param 0) to psp
	MOV 	pc , lr		@Return by moving the link register to the program counter
