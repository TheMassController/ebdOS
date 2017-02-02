    .syntax unified
    .thumb
    .file   "scheduling.c"
    .section    .text.pendSVHandler,"ax",%progbits
    .align  4
    .global pendSVHandler
    .thumb
    .thumb_func
    .type   pendSVHandler, %function
pendSVHandler:
    cpsid i                     @Disables all configurable interrupts: hard fault and NMI can still happen
    @ Check if we are inside the pendSV
    mrs r2, PSR                 @ Load the PSR into r2
    and r2, r2, #0xE            @ If we are in the pendsv then the last seven bits are equal to 0xe, see datasheet pp 76 - 79. So after this and, we are inside the pendSV if r2 == 0xe
    cmp r2, #0xE                @ The compare instruction
    bne .L3                     @ If not equal, jump to L3 (just exit the function)

    @ Load the currentProcess and the nextProcess, update the globalcontext
    sub sp, sp, #12             @ Create the stackspace we need
    str lr, [sp, #8]            @ Store the lr at the very bottom
    bl getCurrentProcess        @ Jump to getCurrentProcess. CurrentProcess will now be in r0
    str r0, [sp, #4]            @ Push currentProcess to the stack
    bl getNextActiveProcess     @ Jump to getNextActiveProcess. nextProcess will now be in r0
    str r0, [sp, #0]            @ Push nextProcess to the stack
    bl changeGlobalContext      @ Change the globalContext to the context related to the nextProcess
    pop {r0, r1, lr}            @ Pop all data back from the stack (stack is now back to before interrupt)

    @ At this point r0 should be nextProcess and r1 currentProcess. All other temp registers are unused, except for lr
    @ The r0, r1, r2, r3, r12, LR, PC and XPSR registers are already pushed to the currently active stack on interrupt.
    @ The first half of the FP regs (s0-s15) get pushed by lazy stacking: when the FP regs are used they are switched out automatically. See setup.c for more details
    @ This function pushes the other regs to the process control block.
    @ During the switch, if the FP regs have been used by this process s16-s31 are also written to the main memory.
    @ Then it loads the other regs from the process control block of the next process.
    @ The LR reg for example wether or not it was using the FPU. See datasheet p 106

    @ Actual context switch: switch out. Does not test for MSP usage: this should not change ever after init phase
    ldr r12, [r1, #8]           @ r12 = savedRegsPointer of currentProcess
    stmdb r12!, {r4-r11}        @ Move R4 to R11 to the mem r12 points to, while decreasing 12. Decrement before, so first decrement, then write, decrement, write etc
    ands lr, lr, #0x10          @ Test if the 5th bit is 0. If it is, then the FPU was activated
    bne .L1                     @ If the fpu was activated, we need to switch out the fpu regs. So test the Z HW flag again
    ldr r2, [r1, #12]           @ Load the current HW flags
    orr lr, r2, #0x10           @ Add the "using FP" flag to hwflags
    vstmdb.f32 r12!, {s16-s31}  @ Move FP regs to mem. Decrement before. Conditional execution. Triggers lazy stacking.
    str lr, [r1, #12]           @ write the new hw flags
.L1:
    str r12, [r1, #8]           @ Store the moved savedRegsPointer of the currentprocess to the mem of the currentprocess
    mrs r3, psp                 @ Move the PSP to R3
    str r3, [r1]                @ Save the stackpointer of currentProcess (currentProcess->stackPointer = r0)

    @ And switch in
    ldr r12, [r0, #12]          @ Load the hw flags
    and r3, r12, #0x1           @ Isolate the first bit, the privileged bit
    eor r3, r3, #1              @ Flip the lsb of r3: the CONTROL needs a 0 if privileged and a 1 if privileged. This is the inverse of the hw_flags lsb
    msr CONTROL, r3             @ Write the r3 to CONTROL to set the privilege
    ands r1, r12, #0x10         @ Isolate the FPU flag
    ldr r3, [r0, #8]            @ Deref r3 + 8 (r0 = processesReady->savedRegsPointer)
    it ne                       @ If the FP bit is set, so if the Z hw bit is unset
    vldmiane.f32 r3!, {s16-s31} @ Load the fp regs. Increment after.
    ldmia   r3! , {r4-r11}      @ Move from ram to regs while increasing R0. Increment after, so load, increment, load, increment etc
    str r3, [r0, #8]            @ Store the moved savedRegsPointer
    ldr r2, [r0]                @ Load the sp of the new process
    msr psp, r2                 @ push r2 (= new stackpointer) to psp

    @ Decide the returnvar and return. R12 is assumed to contain the entire HW flag param of nextProcess.
    @ Two decisions: MSP or PSP, privileged or unprivileged.
    @ This has been optimized by GCC, so its unclear at first sight why it works. It does work, though
    and r12, r12, #0x14         @ Test only the MSP, FP flags
    eor r12, r12, #0x14         @ Invert the loaded flags
    orn lr, r12, #0x16          @ Make lr = 0xFFFFFFE9 | r12, where r12 is 0x0, 0x10, 0x4 or 0x14.
.L3:
    cpsie i                     @ Reenable the configurable interrupts
    bx lr                       @ Branch to LR-addr, without linking
.L4:
    .size   pendSVHandler, .-pendSVHandler
