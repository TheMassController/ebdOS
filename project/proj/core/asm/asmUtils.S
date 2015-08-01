.syntax unified
@ Author: Jacko Dirks
@ Description: Contains util functions that can only be implemented in assembly

    .global waitForInterrupt
    .global isInInterrupt
    .global zeroFillSection
    .global isInSVCInterrupt

waitForInterrupt:
    WFI                         @ Wait for interrupt
    BX lr                       @ return

isInInterrupt:                  @ Params: void. Tests if we are currently in an interrupt. Used to prevent interrupts from blocking while trying to get or release lockobjects
    MRS r0, psr                 @ Load the psr register via the load move special reg to reg instruction
    AND r0, r0, #0xFF           @ PSR & 255 is the ISRNUM reg. If this is 0, then we are not in an interrupt
    BX lr                       @ return

zeroFillSection:                @ params: first address, last address. First address is inclusive, last address is exclusive. So r0 = start, r1 = end
                                @ There is no guarantee about any alignment, so it happens in three parts. First: write bytes until aligned, then write words for as long as possible and then write bytes until finished.
    MOV r12, #0                 @ load r12 with zero
    MOV r2, r0                  @ Set r2 to r0
    BIC r0, r0, #0x3            @ Allign r0 to 0xXXX100
    CMP r2, r0                  @ Compare r2 to r0 to see if the last two bits were already zero
    IT NE                       @ If not... (r2 != r0)
    ADDNE r0, r0, 4             @ Add 4 (100 bin) to r0 to let r0 > r2
    CMP r0, r1                  @ r0 now might be bigger then r1, which we do not want
    ITT HS                      @ So if r0 >= r1
    MOVHS r0, r1                @ r0 = r1
    MOVHS r3, r1                @ r3 = r1
    BHS L1                      @ And branch to L1
                                @ If we get here, then we also need to cut off the lowest bytes from r1
    MOV r3, r1                  @ Set r3 = r1
    BIC r1, r1, #0x3            @ Cut off the last two bits from the end address (aligning that too)
L1:                             @ First part: write bytes
    CMP r2, r0                  @ Compare r2 and r0
    IT LO                       @ If r2 < r0
    STRBLO r12, [r2], #1        @ Write one byte to zero and then increase r2
    BLO L1                      @ If less then, branch to L1
L2:                             @ Second part: write whole words
    CMP r0, r1                  @ Compare r0 and r1
    IT LO                       @ Start IT block
    STRLO r12, [r0], #4         @ Store word to r0 and increase r0 with four. R12 = 0, so *ro = 0
    BLO L2                      @ If r0 < r1, branch to L2
L3:                             @ Third part: write bytes
    CMP r1, r3                  @ Compare r1 and r3
    IT LO                       @ while r1 < r3
    STRBLO r12, [r1], #1        @ Write only 1 byte to zero and then increase r1 with 1
    BLO L3                      @ if r1 < r3, branch L3
    BX lr                       @ return

isInSVCInterrupt:
    mrs r0, PSR                 @ Load the PSR register, this special reg contains the current interrupt code
    and r0, r0, #0xb            @ Clear all bits exept for 0xb, this set is all 1 if inside SVC
    cmp r0, #0xb                @ Test if r0 is exactly equal to  0xb
    it ne
    movne r0, 0                 @ If r0 != 0xb then r0 = 0
    bx lr                       @ return
