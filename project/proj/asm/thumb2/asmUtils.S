@ Syntax unified
@ Author: Jacko Dirks
@ Description: Contains util functions that can only be implemented in assembly

    .global waitForInterrupt
    
waitForInterrupt:
    WFI             @Wait for interrupt
    MOV     PC, LR  @Return by moving the link register to the program counter
    
forceManualReturn:
    MOV     lr, R0      @Move param0 to R7
	MOV 	pc , lr		@Return by moving the link register to the program counter
