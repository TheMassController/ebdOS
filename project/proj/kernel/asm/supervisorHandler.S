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
    TST lr, #4          @Test which stack pointer was in use
    ITE eq              @If bit 4 is high
    MRSEQ r0, MSP       @MSP was in use
    MRSNE r0, PSP       @Else PSP
    AND r1, lr, #0xF    @Get the last halfbyte from the LR (test for handler mode coming up)
    cmp r1, #0x1        @test if it is equal to 1
    it ne
    movne r1, #0x0      
    ldr r0, [r0, #24]   
    ldrb r0, [r0, #-2]
    nop
	b svcHandler_main	
	.size	svcHandler, .-svcHandler
	.ident	"GCC: (GNU Tools for ARM Embedded Processors) 4.8.4 20140526 (release) [ARM/embedded-4_8-branch revision 211358]"
