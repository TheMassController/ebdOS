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
@ The idea of this function is that is writes bytes until it is aligned to 8 byte, then writes double words, as much as possible, then writes bytes until done
zeroFillSection:                @params: first addr, last addr. Last is exclusive
    push {lr}                   @ Push lr: more regs
    cmp r0, r1
    bcs endFunction             @ if r0 >= r1, return right here
    mov r12, #0                 @ r12 == 0
    bics r2, r0, #0x7           @ Align r0 to doubleword
    it ne                       @ If r0 was unaligned, 8 needs to be added
    addne r2, r2, #8
    bic r3, r1, #0x7            @ Align r1 to doubleword
startByteLoop:                  @ Write bytes until start is doubleword aligned
    cmp r0, r2
    beq doubleWordInit
    strb r12, [r0]
    add r0, r0, #1              @ increment r0
    b startByteLoop
doubleWordInit:                 @ Write doublewords until end of doubleword aligned section: init phase
    cmp r2, r3
    beq endByteLoop             @ if r0 = r1, skip writing double words
    mov lr, #0
doubleWordLoop:                 @ Loop phase
    strd r12, lr, [r2]          @ Write the doubleword
    add r2, r2, #8              @ increment r2
    cmp r2, r3
    bne doubleWordLoop
endByteLoop:                    @ Write bytes until done
    cmp r3, r1
    beq endFunction
    strb r12, [r3]
    add r3, r3, #1
    b endByteLoop
endFunction:
    pop {pc}                    @ Pop lr to pc to return
    nop                         @ Safety nop

isInSVCInterrupt:
    mrs r0, PSR                 @ Load the PSR register, this special reg contains the current interrupt code
    and r0, r0, #0xb            @ Clear all bits exept for 0xb, this set is all 1 if inside SVC
    cmp r0, #0xb                @ Test if r0 is exactly equal to  0xb
    it ne
    movne r0, 0                 @ If r0 != 0xb then r0 = 0
    bx lr                       @ return
