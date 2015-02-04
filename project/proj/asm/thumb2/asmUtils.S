.syntax unified
.cpu cortex-m4
.thumb
@ Author: Jacko Dirks
@ Description: Contains util functions that can only be implemented in assembly

    .global waitForInterrupt
    .global isInInterrupt
    .global __increaseLockObject
    .global __decreaseLockObject
    
waitForInterrupt:
    WFI             @Wait for interrupt
    MOV     PC, LR  @Return by moving the link register to the program counter

L3: 
    DMB                     @Make sure all memory operations are done before returning
    BX lr                   @Jump back where you came from

L4:
    MVN r0, #0              @Store a not(0x0) into r0, which is -1 in int.
    B L3

__increaseLockObject:  @params: address of object. 
    MOV r1, r0              @r1 = r0
    ADD r1, r1, #4          @increase the memaddr with 4. Memaddr is now &maxLockVal
    LDR r1, [r1]            @Deref r1, r1 is now maxLockVal 
    LDREX r2, [r0]          @Load exclusive the deref of r0, which is the lock
    CMP r1, r2              @Do a compare to set the flags
    BLE L4                  @If r1 (=maxval of the lock) is smaller then or equal to r2(=current value of the lock), jump to L4
    ADD r2, r2, #1          @r2++
    STREX r3, r2, [r0]      @Store-exclusive the value in r2 to the mem location pointed to by r0, store the result of the exclusive part to r3
    CMP r3, #1              @Test if the operation was successfull
    BEQ __increaseLockObject
    MOV r0, r2              @If successful, store the new lock value (r2) to r0
    B L3
    
__decreaseLockObject:  @params: address of object.
    MOV r1, r0              @r1 = r0
    ADD r1, r1, #4          @increase the memaddr with 4. Memaddr is now &maxLockVal
    LDR r1, [r1]            @Deref r1, r1 is now maxLockVal 
    LDREX r2, [r0]          @Load exclusive the deref of r0, which is the lock
    CMP r2, #0              @Do a compare to set the flags
    BLE L4                  @If r2 (=val of the lock) is smaller then or equal to 0, jump to L4
    SUB r2, r2, #1          @r2--
    STREX r3, r2, [r0]      @Store-exclusive the value in r2 to the mem location pointed to by r0, store the result of the exclusive part to r3
    CMP r3, #1              @Test if the operation was successfull
    BEQ __decreaseLockObject   @If not, jump back to the beginning
    MOV r0, r2              @If successful, store the new lock value (r2) to r0
    B L3

isInInterrupt:
    MRS r0, psr
    AND r0, r0, #0xFF      @PSR & 255 is the ISRNUM reg. If this is 0, then we are not in an interrupt
    BX lr                   @return
