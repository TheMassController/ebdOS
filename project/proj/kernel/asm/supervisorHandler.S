	.syntax unified
	.thumb
	.section	.text.svcHandler,"ax",%progbits
	.align	2
	.global	svcHandler
	.thumb
	.thumb_func
	.type	svcHandler, %function
svcHandler:
    @ Called when SVC interrupt happens. Bridges towards svcHandler_main. When done, r0 should not equal zero if the call came from handler mode and equal zero if it did.
    @ r1 should be equal to the value passed with the svc instruction

    @ One of the goals of this code is to get the code part of the svc instruction.
    @ This part of the instruction is igorned by the CPU, so in order to get this code we are going to have to load it from the actual instruction.
    @ Game plan: get the correct stackpointer, load its stacked PC and read the second halve of the last instruction executed.
    @ See datasheet page 105
    @ The processor is always in Thumb mode, which means 16 bit instructions. For SVC, the last 8 bit are for the immidiate.
    @ The PC always points to the next instruction that will be executed, in this case its the one after the SVC.
    @ So we want the byte PC-2

    @ This piece of code loads the two arguments the supervisor needs: wether or not it is called from handler mode and what the given code was.
    @ The first part checks if the call came from a PSP process or an MSP process.
    @ If the call came from an MSP process its either an interrupt or the kernel process, at this time.
    @ I decided not to use this information, because the entire kernel process is on the list for deprication and I have no clue what happens after that
    @ Its just convient that the SVC has no complicated context based checks.
    @ According to datasheet p106 the last byte of the lr reg contains all information we need
    @ If the MSP is active the last byte is E1 (1110 0001), E9 (1110 0101), F1 (1111 0001), F9 (1111 0101)
    @ If the PSP is active, the last byte is ED (1110 1101), FD (1111 1101)
    @ So we need to test the fourth bit. If it is 1, the PSP is active, else the MSP is active.
    TST lr, #4          @ Test which stack pointer was in use
    ITE eq              @ If bit 4 is high
    MRSEQ r0, MSP       @ MSP was in use, load its stackpointer to R0
    MRSNE r0, PSP       @ Else PSP was in use, load its stackpointer to R0
    @ second part, this part gets the value passed with the SVC. It depends on the right stack pointer being in r0
    ldr r0, [r0, #24]   @ Load PC (of earlier selected SP) to R0
    ldrb r0, [r0, #-2]  @ Load the second part of the SVC instruction
    @ This last part is about checking if the call came from handler mode or from thread mode.
    @ The call came from handler mode if the last byte of LR is E1 (1110 0001) or F1 (1110 0001)
    @ So we check if the very last bit is 1
    and r1, lr, #0xF    @ Isolate the last four bits
    sub r1, r1, #0x1    @ If r1 is zero now we are in handler mode. If not, we are in threadmode
    clz r1, r1          @ becomes 32 if r1 is zero, which is 2**5 (1 in sixth position)
    lsr r1, r1, #0x5    @ Shift 5 to the right, exactly 1 left if the value was 32, else the value is zero
    b svcHandler_main   @ Jump to svcHandlerMain
	.size	svcHandler, .-svcHandler
