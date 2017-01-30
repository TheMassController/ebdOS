.syntax unified
@ Author: Jacko Dirks
@ Description: Contains util functions that can only be implemented in assembly

    .global waitForInterrupt
    .global isInInterrupt
    .global isInSVCInterrupt

waitForInterrupt:
    WFI                         @ Wait for interrupt
    BX lr                       @ return

isInInterrupt:                  @ Params: void. Tests if we are currently in an interrupt. Used to prevent interrupts from blocking while trying to get or release lockobjects
    MRS r0, psr                 @ Load the psr register via the load move special reg to reg instruction
    AND r0, r0, #0xFF           @ PSR & 255 is the ISRNUM reg. If this is 0, then we are not in an interrupt
    BX lr                       @ return
isInSVCInterrupt:
    mrs r0, PSR                 @ Load the PSR register, this special reg contains the current interrupt code
    and r0, r0, #0xFF           @ Clear all bits exept for the interrupt bits
    cmp r0, #0xb                @ Test if r0 is exactly equal to  0xb
    it ne
    movne r0, 0                 @ If r0 != 0xb then r0 = 0
    bx lr                       @ return
