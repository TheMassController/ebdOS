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
    WFI             @Wait for interrupt
    MOV     PC, LR  @Return by moving the link register to the program counter

L3: 
    DMB                         @Make sure all memory operations are done before returning
    BX lr                       @Jump back where you came from

L4:
    MVN r0, #0                  @Store a inverse 32-bit (0x0) into r0, which is -1 in int.
    B L3

__increaseLockObject:  @params: address of object. 
    MOV r1, r0                  @r1 = r0
    ADD r1, r1, #4              @increase the memaddr with 4. Memaddr is now &maxLockVal
    LDR r1, [r1]                @Deref r1, r1 is now maxLockVal 
    LDREX r2, [r0]              @Load exclusive the deref of r0, which is the lock
    CMP r1, r2                  @Do a compare to set the flags
    BLE L4                      @If r1 (=maxval of the lock) is smaller then or equal to r2(=current value of the lock), jump to L4
    ADD r2, r2, #1              @r2++
    STREX r3, r2, [r0]          @Store-exclusive the value in r2 to the mem location pointed to by r0, store the result of the exclusive part to r3
    CMP r3, #1                  @Test if the operation was successfull
    BEQ __increaseLockObject    @If not, jump back to start (this means that the value was read/written in the meantime)    
    MOV r0, r2                  @If successful, store the new lock value (r2) to r0
    B L3
    
__decreaseLockObject:           @params: address of object.
    MOV r1, r0                  @r1 = r0
    ADD r1, r1, #4              @increase the memaddr with 4. Memaddr is now &maxLockVal
    LDR r1, [r1]                @Deref r1, r1 is now maxLockVal 
    LDREX r2, [r0]              @Load exclusive the deref of r0, which is the lock
    CMP r2, #0                  @Do a compare to set the flags
    BLE L4                      @If r2 (=val of the lock) is smaller then or equal to 0, jump to L4
    SUB r2, r2, #1              @r2--
    STREX r3, r2, [r0]          @Store-exclusive the value in r2 to the mem location pointed to by r0, store the result of the exclusive part to r3
    CMP r3, #1                  @Test if the operation was successfull
    BEQ __decreaseLockObject    @If not, jump back to the beginning
    MOV r0, r2                  @If successful, store the new lock value (r2) to r0
    B L3

isInInterrupt:
    MRS r0, psr                 @Load the psr register via the load move special reg to reg instruction
    AND r0, r0, #0xFF           @PSR & 255 is the ISRNUM reg. If this is 0, then we are not in an interrupt
    BX lr                       @return

zeroFillSection:                @params: first address, last address. First address is inclusive, last address is exclusive. So r0 = start, r1 = end
                                @There is no guarantee about any alignment, so it happens in three parts. First: write bytes until aligned, then write words for as long as possible and then write bytes until finished.
    MOV r2, r0                  @Set r2 to r0
    ORN r0, r0, #0x3            @Allign r0 to 0xXXX100
    CMP r2, r0                  @Compare r2 to r0 to see if the last two bits were already zero
    IT NE                       @If not...
    ADDNE r0, r0, 4             @Add 4 to r0 to let r0 > r2
    CMP r0, r1                  @r0 now might be bigger then r1, which we do not want
    ITT HS                      @So if r0 >= r1
    MOVHS r0, r1                @r0 = r1
    MOVHS r12, r1               @r12 = r1
    BHS L5                      @And branch to L5
                                @If we get here, then we also need to cut off the lowest bytes from r1
    MOV r3, r1                  @Set r3 = r1
    ORN r1, r1, #0x3            @Cut off the last two bits from the end address (aligning that too)
                                @Right now r3 is higher then or equal to r1. But we do not care.
    MOV r12, #0                 @load r12 with zero
L5:                             @First part: write lose bytes                             
    CMP r2, r0                  @Compare r2 and r0
    IT LS                       @If r2 <= r0
    STRBLS r12, [r2], #1        @Write one byte to zero and then increase r2
    BLS L5                      @If less then, branch to L5
L6:                             @Second part: write whole words
    CMP r0, r1                  @Compare r0 and r1
    IT LS                       @Start IT block
    STRLS r12, [r0], #4         @Store word to r0 and increase r0 with four. R12 = 0, so *ro = 0
    BLS L6                      @If r0 <= r1, branch to L6
L7:                             @Third part: write last bytes
    CMP r1, r3                  @Compare r1 and r3
    IT LO                       @while r1 < r3
    STRBLO r12, [r1], #1        @Write only 1 byte to zero and then increase r1 with 1
    BLO L7                      @if r1 < r3, branch L7
    BX lr                       @return
    
