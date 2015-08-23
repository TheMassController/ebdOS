.syntax unified
@ Author: Jacko Dirks
@ Description: Contains functions that use the ARM instructions strex and ldrex to ensure thread-safety

    .global __increaseLockObject
    .global __decreaseLockObject
    .global incrIntegerTSMax
    .global decrIntegerTSMax

L2:                             @ Helper function to handle the case where a safe memset has failed
    MVN r0, #0                  @ Store a inverse 32-bit (0x0) into r0, which is -1 in int.
L1:                             @ Helper function to return from safe memory interactions
    DMB                         @ Make sure all memory operations are done before returning
    BX lr                       @ Jump back where you came from

@ DEPRECATED
__increaseLockObject:           @ params: address of object.
    MOV r1, r0                  @ r1 = r0
    ADD r1, r1, #4              @ increase the memaddr with 4. Memaddr is now &maxLockVal
    LDR r1, [r1]                @ Deref r1, r1 is now maxLockVal
    LDREX r2, [r0]              @ Load exclusive the deref of r0, which is the lock
    CMP r1, r2                  @ Do a compare to set the flags
    BLE L2                      @ If r1 (=maxval of the lock) is smaller then or equal to r2(=current value of the lock), jump to L2
    ADD r2, r2, #1              @ r2++
    STREX r3, r2, [r0]          @ Store-exclusive the value in r2 to the mem location pointed to by r0, store the result of the exclusive part to r3
    CMP r3, #1                  @ Test if the operation was successfull
    BEQ __increaseLockObject    @ If not, jump back to start (this means that the value was read/written in the meantime)
    MOV r0, r2                  @ If successful, store the new lock value (r2) to r0
    B L1                        @ Make sure all memory interaction is done and return

@ DEPRECATED
__decreaseLockObject:           @ params: address of object.
    MOV r1, r0                  @ r1 = r0
    ADD r1, r1, #4              @ increase the memaddr with 4. Memaddr is now &maxLockVal
    LDR r1, [r1]                @ Deref r1, r1 is now maxLockVal
    LDREX r2, [r0]              @ Load exclusive the deref of r0, which is the lock
    CMP r2, #0                  @ Do a compare to set the flags
    BLE L2                      @ If r2 (=val of the lock) is smaller then or equal to 0, jump to L2
    SUB r2, r2, #1              @ r2--
    STREX r3, r2, [r0]          @ Store-exclusive the value in r2 to the mem location pointed to by r0, store the result of the exclusive part to r3
    CMP r3, #1                  @ Test if the operation was successfull
    BEQ __decreaseLockObject    @ If not, jump back to the beginning
    MOV r0, r2                  @ If successful, store the new lock value (r2) to r0
    B L1                        @ Make sure all memory interaction is done and return

incrIntegerTSMax:                  @ Params: pointer to unsinged, maxval of unsigned.
    ldrex r2, [r0]              @ Load the current value, exclusive
    cmp r2, #0                  @ Compare the loaded value to zero
    blt L2                      @ If the passed parameter is smaller then 0, return.
    cmp r2, r1                  @ Compare the curval to the maxval
    bge L2                      @ if r2 is equal to or greater then r1, return -1
    add r2, r2, #1              @ r2++
    strex r3, r2, [r0]          @ try to store-exclusive the increased value of r2
    cmp r3, #1                  @ See if the store was successfull
    beq incrIntegerTSMax           @ If the store was unsuccessful, try again
    mov r0, r2                  @ If the store was successfull, set the return value to the just-written value of given unsigned
    b L1                        @ Unconditional branch to L1

decrIntegerTSMax:                  @ Params: pointer to unsinged
    ldrex r2, [r0]              @ Load the current value, exclusive
    cmp r2, #0                  @ Test if the param is bigger then zero
    ble L2                      @ if r2 is smaller then or equal to zero, return -1
    sub r2, r2, #1              @ r2--
    strex r3, r2, [r0]          @ try to store-exclusive the increased value of r2
    cmp r3, #1                  @ See if the store was successfull
    beq decrIntegerTSMax           @ If the store was not successfull try again
    mov r0, r2                  @ If the store was successfull, set the return value to the just-written value of given unsigned
    b L1                        @ Unconditional branch to L1
