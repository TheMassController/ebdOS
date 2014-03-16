.syntax unified
@ Author: Jacko Dirks
@ Description: Contains some functions necessary to this OS that cannot be implemented in C

	.global getSP
	
getSP:
	MOV 	R0 , sp 	@Move the stack pointer to the return register, R0
	MOV 	pc , lr		@Return by moving the link register to the program counter
