.syntax unified
@ Author: Jacko Dirks
@ Description: Contains functions that use the ARM instructions strex and ldrex to ensure thread-safety

    .global atomicIncreaseIntWithMax
    .global atomicDecreaseIntWithMax
    .global atomicIncreaseInt
    .global atomicDecreaseInt
    .global atomicSetInt

L2:                             @ Helper function to handle the case where a safe memset has failed
    MVN r0, #0                  @ Store a inverse 32-bit (0x0) into r0, which is -1 in int.
L1:                             @ Helper function to return from safe memory interactions
    DMB                         @ Make sure all memory operations are done before returning
    BX lr                       @ Jump back where you came from

atomicIncreaseIntWithMax:       @ Params: pointer to unsinged, maxval of unsigned.
    ldrex r2, [r0]              @ Load the current value, exclusive
    cmp r2, #0                  @ Compare the loaded value to zero
    blt L2                      @ If the passed parameter is smaller then 0, return.
    cmp r2, r1                  @ Compare the curval to the maxval
    bge L2                      @ if r2 is equal to or greater then r1, return -1
    add r2, r2, #1              @ r2++
    strex r3, r2, [r0]          @ try to store-exclusive the increased value of r2
    cmp r3, #1                  @ See if the store was successfull
    beq atomicIncreaseIntWithMax@ If the store was unsuccessful, try again
    mov r0, r2                  @ If the store was successfull, set the return value to the just-written value of given unsigned
    b L1                        @ Unconditional branch to L1

atomicDecreaseIntWithMax:       @ Params: pointer to unsinged
    ldrex r2, [r0]              @ Load the current value, exclusive
    cmp r2, #0                  @ Test if the param is bigger then zero
    ble L2                      @ if r2 is smaller then or equal to zero, return -1
    sub r2, r2, #1              @ r2--
    strex r3, r2, [r0]          @ try to store-exclusive the increased value of r2
    cmp r3, #1                  @ See if the store was successfull
    beq atomicDecreaseIntWithMax@ If the store was not successfull try again
    mov r0, r2                  @ If the store was successfull, set the return value to the just-written value of given unsigned
    b L1                        @ Unconditional branch to L1

atomicIncreaseInt:              @ Param: pointer to unsigned
    ldrex r1, [r0]              @ Deref the pointer, exclusive
    add r1, r1, #1              @ r1++
    strex r2, r1, [r0]          @ Store the value to the original memory location, exclusive
    cmp r2, #1                  @ Test if the store was successfull. If not: try again
    beq atomicIncreaseInt       @ Jump to try again
    mov r0, r1                  @ Store the written value to the return register
    b L1                        @ Jump to safe exit

atomicDecreaseInt:              @ Param: pointer to unsigned
    ldrex r1, [r0]              @ Deref the pointer, exclusive
    sub r1, r1, #1              @ r1--
    strex r2, r1, [r0]          @ Store the value to the original memory location, exclusive
    cmp r2, #1                  @ Test if the store was successfull. If not: try again
    beq atomicDecreaseInt       @ Jump to try again
    mov r0, r1                  @ Store the written value to the return register
    b L1                        @ Jump to safe exit

atomicSetInt:                   @ params pointer to signed int, newval, expcurval
    ldrex r3, [r0]              @ Deref the pointer, exclusive
    cmp r3, r2                  @ Compare, see if it equals
    bne L2                      @ if curval != expcurval, return -1
    strex r12, r1, [r0]         @ Store the value to the original memory location, exclusive
    cmp r12, #1                 @ Test if the store was successfull, if not: try again.
    beq atomicSetInt            @ Jump to try again
    mov r0, #1                  @ Write 1 to to return reg to indicate success.
    b L1                        @ Jump to safe exit
