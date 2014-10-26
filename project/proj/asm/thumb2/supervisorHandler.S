	.syntax unified
	.cpu cortex-m4
	.eabi_attribute 27, 3
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
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
    TST lr, #4
    IT eq
    MRSEQ r0, MSP
    it ne
    MRSNE r0, PSP
    ldr r0, [r0, #24]
    ldrb r0, [r0, #-2]
    nop
	b svcHandler_main	
	.size	svcHandler, .-svcHandler
	.ident	"GCC: (GNU Tools for ARM Embedded Processors) 4.8.4 20140526 (release) [ARM/embedded-4_8-branch revision 211358]"
