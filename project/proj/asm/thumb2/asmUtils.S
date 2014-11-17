.syntax unified
.cpu cortex-m4
.thumb
@ Author: Jacko Dirks
@ Description: Contains util functions that can only be implemented in assembly

    .global waitForInterrupt
    .global __lockMutex
    .global __unlockMutex
    
waitForInterrupt:
    WFI             @Wait for interrupt
    MOV     PC, LR  @Return by moving the link register to the program counter

__lockMutex:
    MOV r1, #1              @Load R1 to be value 1
L1:
    LDREX r2, [r0]          @Load exclusive    
    CMP r2, r1              @Test if the mutex value is 1 (= locked)
    BEQ L2                  @If equal, then the mutex is locked. Just return with a zero
    STREX r2, r1, [r0]      @Store-exclusive the value in r1 to the mem location pointed to by r0, store the result of the exclusive part to r2
    CMP r2, r1              @Test if the operation was successfull
    BEQ L1                  @If unsucsessful, try again
    MOV r0, r1              @If successful, store a 1 to R0
    B L3
L2: 
    MOV r0, #0              @Store a 0 in the return reg
L3: 
    DMB                     @Make sure all memory operations are done before returning
    BX lr                   @Jump back where you came from

__unlockMutex:
    MOV r1, #0             @Make r1 1 
    DMB                    @Wait for all previous memory interactions to be done to ensure correct storage
    STR r1, [r0]           @Store a zero to the memaddr, basically unlocking the mutex
    BX lr                  @return
