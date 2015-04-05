.syntax unified
.cpu cortex-m4
.thumb
@ Author: Jacko Dirks
@ Description: Contains util functions that can only be implemented in assembly

    .global waitForInterrupt
    .global isInInterrupt
    .global zeroFillSection
    .global __increaseLockObject
    .global __decreaseLockObject
    
waitForInterrupt:
    WFI                         @Wait for interrupt
    BX lr                       @return

L1:                             @Helper function to return from safe memory interactions
    DMB                         @Make sure all memory operations are done before returning
    BX lr                       @Jump back where you came from
L2:                             @Helper function to handle the case where a safe memset has failed
    MVN r0, #0                  @Store a inverse 32-bit (0x0) into r0, which is -1 in int.
    B L1                        @Make sure all memory interaction is done and return

__increaseLockObject:           @params: address of object. 
    MOV r1, r0                  @r1 = r0
    ADD r1, r1, #4              @increase the memaddr with 4. Memaddr is now &maxLockVal
    LDR r1, [r1]                @Deref r1, r1 is now maxLockVal 
    LDREX r2, [r0]              @Load exclusive the deref of r0, which is the lock
    CMP r1, r2                  @Do a compare to set the flags
    BLE L2                      @If r1 (=maxval of the lock) is smaller then or equal to r2(=current value of the lock), jump to L2
    ADD r2, r2, #1              @r2++
    STREX r3, r2, [r0]          @Store-exclusive the value in r2 to the mem location pointed to by r0, store the result of the exclusive part to r3
    CMP r3, #1                  @Test if the operation was successfull
    BEQ __increaseLockObject    @If not, jump back to start (this means that the value was read/written in the meantime)    
    MOV r0, r2                  @If successful, store the new lock value (r2) to r0
    B L1                        @Make sure all memory interaction is done and return
    
__decreaseLockObject:           @params: address of object.
    MOV r1, r0                  @r1 = r0
    ADD r1, r1, #4              @increase the memaddr with 4. Memaddr is now &maxLockVal
    LDR r1, [r1]                @Deref r1, r1 is now maxLockVal 
    LDREX r2, [r0]              @Load exclusive the deref of r0, which is the lock
    CMP r2, #0                  @Do a compare to set the flags
    BLE L2                      @If r2 (=val of the lock) is smaller then or equal to 0, jump to L2
    SUB r2, r2, #1              @r2--
    STREX r3, r2, [r0]          @Store-exclusive the value in r2 to the mem location pointed to by r0, store the result of the exclusive part to r3
    CMP r3, #1                  @Test if the operation was successfull
    BEQ __decreaseLockObject    @If not, jump back to the beginning
    MOV r0, r2                  @If successful, store the new lock value (r2) to r0
    B L1                        @Make sure all memory interaction is done and return

isInInterrupt:                  @Params: void. Tests if we are currently in an interrupt. Used to prevent interrupts from blocking while trying to get or release lockobjects
    MRS r0, psr                 @Load the psr register via the load move special reg to reg instruction
    AND r0, r0, #0xFF           @PSR & 255 is the ISRNUM reg. If this is 0, then we are not in an interrupt
    BX lr                       @return

zeroFillSection:                @params: first address, last address. First address is inclusive, last address is exclusive. So r0 = start, r1 = end
                                @There is no guarantee about any alignment, so it happens in three parts. First: write bytes until aligned, then write words for as long as possible and then write bytes until finished.
    MOV r12, #0                 @load r12 with zero
    MOV r2, r0                  @Set r2 to r0
    ORN r0, r0, #0x3            @Allign r0 to 0xXXX100
    CMP r2, r0                  @Compare r2 to r0 to see if the last two bits were already zero
    IT NE                       @If not... (r2 != r0)
    ADDNE r0, r0, 4             @Add 4 (100 bin) to r0 to let r0 > r2
    CMP r0, r1                  @r0 now might be bigger then r1, which we do not want
    ITT HS                      @So if r0 >= r1
    MOVHS r0, r1                @r0 = r1
    MOVHS r3, r1                @r3 = r1
    BHS L3                      @And branch to L3
                                @If we get here, then we also need to cut off the lowest bytes from r1
    MOV r3, r1                  @Set r3 = r1
    ORN r1, r1, #0x3            @Cut off the last two bits from the end address (aligning that too)
L3:                             @First part: write bytes                             
    CMP r2, r0                  @Compare r2 and r0
    IT LO                       @If r2 < r0
    STRBLO r12, [r2], #1        @Write one byte to zero and then increase r2
    BLO L3                      @If less then, branch to L3
L4:                             @Second part: write whole words
    CMP r0, r1                  @Compare r0 and r1
    IT LO                       @Start IT block
    STRLO r12, [r0], #4         @Store word to r0 and increase r0 with four. R12 = 0, so *ro = 0
    BLO L4                      @If r0 < r1, branch to L4
L5:                             @Third part: write bytes
    CMP r1, r3                  @Compare r1 and r3
    IT LO                       @while r1 < r3
    STRBLO r12, [r1], #1        @Write only 1 byte to zero and then increase r1 with 1
    BLO L5                      @if r1 < r3, branch L5
    BX lr                       @return
