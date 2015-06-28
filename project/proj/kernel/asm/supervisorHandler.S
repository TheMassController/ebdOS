	.syntax unified
	.thumb
	.file	"supervisorInterrupt.c"
	.section	.text.svcHandler,"ax",%progbits
	.align	2
	.global	svcHandler
	.thumb
	.thumb_func
	.type	svcHandler, %function
svcHandler:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
    @ This piece of code loads the two arguments the supervisor needs: wether or not it is called from handler mode and what the given code was.
    TST lr, #4          @ Test which stack pointer was in use
    ITE eq              @ If bit 4 is high
    MRSEQ r0, MSP       @ MSP was in use
    MRSNE r0, PSP       @ Else PSP
    AND r1, lr, #0xF    @ Get the last halfbyte from the LR (test for handler mode coming up)
    cmp r1, #0x1        @ test if it is equal to 1. If it is, we just came from Handler mode. We are not testing the last bit, because the last halfword might also be 9, which implies thread mode
    it ne               @ If it is not equal
    movne r1, #0x0      @ Set r1 to zero
    ldr r0, [r0, #24]   @ TODO figure out why this works
    ldrb r0, [r0, #-2]  @ TODO see above
    nop                 @ TODO see above
    b svcHandler_main   @ Jump to svcHandlerMain
	.size	svcHandler, .-svcHandler
	.ident	"GCC: (GNU Tools for ARM Embedded Processors) 4.8.4 20140526 (release) [ARM/embedded-4_8-branch revision 211358]"
