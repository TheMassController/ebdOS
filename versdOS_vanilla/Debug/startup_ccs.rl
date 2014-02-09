L 1 "../startup_ccs.c"
N//*****************************************************************************
N//
N// startup_ccs.c - Startup code for use with TI's Code Composer Studio.
N//
N// Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
N// Software License Agreement
N// 
N// Texas Instruments (TI) is supplying this software for use solely and
N// exclusively on TI's microcontroller products. The software is owned by
N// TI and/or its suppliers, and is protected under applicable copyright
N// laws. You may not combine this software with "viral" open-source
N// software in order to form a larger program.
N// 
N// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
N// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
N// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
N// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
N// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
N// DAMAGES, FOR ANY REASON WHATSOEVER.
N// 
N// This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
N//
N//*****************************************************************************
N
N//*****************************************************************************
N//
N// Forward declaration of the default fault handlers.
N//
N//*****************************************************************************
Nvoid ResetISR(void);
Nstatic void NmiSR(void);
Nstatic void FaultISR(void);
Nstatic void IntDefaultHandler(void);
N
N//*****************************************************************************
N//
N// External declaration for the reset handler that is to be called when the
N// processor is started
N//
N//*****************************************************************************
Nextern void _c_int00(void);
N
N
N//*****************************************************************************
N//
N// Linker variable that marks the top of the stack.
N//
N//*****************************************************************************
Nextern unsigned long __STACK_TOP;
N
N
Nextern void SystickISR(void);
Nextern void PendSVISR(void);
N
N//*****************************************************************************
N//
N// The vector table.  Note that the proper constructs must be placed on this to
N// ensure that it ends up at physical address 0x0000.0000 or at the start of
N// the program if located at a start address other than 0.
N//
N//*****************************************************************************
N#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
Nvoid (* const g_pfnVectors[])(void) =
N{
N    (void (*)(void))((unsigned long)&__STACK_TOP),
N                                            // The initial stack pointer
N    ResetISR,                               // The reset handler
N    NmiSR,                                  // The NMI handler
N    FaultISR,                               // The hard fault handler
N    IntDefaultHandler,                      // The MPU fault handler
N    IntDefaultHandler,                      // The bus fault handler
N    IntDefaultHandler,                      // The usage fault handler
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    IntDefaultHandler,                      // SVCall handler
N    IntDefaultHandler,                      // Debug monitor handler
N    0,                                      // Reserved
N    PendSVISR,                      		// The PendSV handler
N    SystickISR,                      		// The SysTick handler
N    IntDefaultHandler,                      // GPIO Port A
N    IntDefaultHandler,                      // GPIO Port B
N    IntDefaultHandler,                      // GPIO Port C
N    IntDefaultHandler,                      // GPIO Port D
N    IntDefaultHandler,                      // GPIO Port E
N    IntDefaultHandler,                      // UART0 Rx and Tx
N    IntDefaultHandler,                      // UART1 Rx and Tx
N    IntDefaultHandler,                      // SSI0 Rx and Tx
N    IntDefaultHandler,                      // I2C0 Master and Slave
N    IntDefaultHandler,                      // PWM Fault
N    IntDefaultHandler,                      // PWM Generator 0
N    IntDefaultHandler,                      // PWM Generator 1
N    IntDefaultHandler,                      // PWM Generator 2
N    IntDefaultHandler,                      // Quadrature Encoder 0
N    IntDefaultHandler,                      // ADC Sequence 0
N    IntDefaultHandler,                      // ADC Sequence 1
N    IntDefaultHandler,                      // ADC Sequence 2
N    IntDefaultHandler,                      // ADC Sequence 3
N    IntDefaultHandler,                      // Watchdog timer
N    IntDefaultHandler,                      // Timer 0 subtimer A
N    IntDefaultHandler,                      // Timer 0 subtimer B
N    IntDefaultHandler,                      // Timer 1 subtimer A
N    IntDefaultHandler,                      // Timer 1 subtimer B
N    IntDefaultHandler,                      // Timer 2 subtimer A
N    IntDefaultHandler,                      // Timer 2 subtimer B
N    IntDefaultHandler,                      // Analog Comparator 0
N    IntDefaultHandler,                      // Analog Comparator 1
N    IntDefaultHandler,                      // Analog Comparator 2
N    IntDefaultHandler,                      // System Control (PLL, OSC, BO)
N    IntDefaultHandler,                      // FLASH Control
N    IntDefaultHandler,                      // GPIO Port F
N    IntDefaultHandler,                      // GPIO Port G
N    IntDefaultHandler,                      // GPIO Port H
N    IntDefaultHandler,                      // UART2 Rx and Tx
N    IntDefaultHandler,                      // SSI1 Rx and Tx
N    IntDefaultHandler,                      // Timer 3 subtimer A
N    IntDefaultHandler,                      // Timer 3 subtimer B
N    IntDefaultHandler,                      // I2C1 Master and Slave
N    IntDefaultHandler,                      // Quadrature Encoder 1
N    IntDefaultHandler,                      // CAN0
N    IntDefaultHandler,                      // CAN1
N    IntDefaultHandler,                      // CAN2
N    IntDefaultHandler,                      // Ethernet
N    IntDefaultHandler,                      // Hibernate
N    IntDefaultHandler,                      // USB0
N    IntDefaultHandler,                      // PWM Generator 3
N    IntDefaultHandler,                      // uDMA Software Transfer
N    IntDefaultHandler,                      // uDMA Error
N    IntDefaultHandler,                      // ADC1 Sequence 0
N    IntDefaultHandler,                      // ADC1 Sequence 1
N    IntDefaultHandler,                      // ADC1 Sequence 2
N    IntDefaultHandler,                      // ADC1 Sequence 3
N    IntDefaultHandler,                      // I2S0
N    IntDefaultHandler,                      // External Bus Interface 0
N    IntDefaultHandler,                      // GPIO Port J
N    IntDefaultHandler,                      // GPIO Port K
N    IntDefaultHandler,                      // GPIO Port L
N    IntDefaultHandler,                      // SSI2 Rx and Tx
N    IntDefaultHandler,                      // SSI3 Rx and Tx
N    IntDefaultHandler,                      // UART3 Rx and Tx
N    IntDefaultHandler,                      // UART4 Rx and Tx
N    IntDefaultHandler,                      // UART5 Rx and Tx
N    IntDefaultHandler,                      // UART6 Rx and Tx
N    IntDefaultHandler,                      // UART7 Rx and Tx
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    IntDefaultHandler,                      // I2C2 Master and Slave
N    IntDefaultHandler,                      // I2C3 Master and Slave
N    IntDefaultHandler,                      // Timer 4 subtimer A
N    IntDefaultHandler,                      // Timer 4 subtimer B
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    0,                                      // Reserved
N    IntDefaultHandler,                      // Timer 5 subtimer A
N    IntDefaultHandler,                      // Timer 5 subtimer B
N    IntDefaultHandler,                      // Wide Timer 0 subtimer A
N    IntDefaultHandler,                      // Wide Timer 0 subtimer B
N    IntDefaultHandler,                      // Wide Timer 1 subtimer A
N    IntDefaultHandler,                      // Wide Timer 1 subtimer B
N    IntDefaultHandler,                      // Wide Timer 2 subtimer A
N    IntDefaultHandler,                      // Wide Timer 2 subtimer B
N    IntDefaultHandler,                      // Wide Timer 3 subtimer A
N    IntDefaultHandler,                      // Wide Timer 3 subtimer B
N    IntDefaultHandler,                      // Wide Timer 4 subtimer A
N    IntDefaultHandler,                      // Wide Timer 4 subtimer B
N    IntDefaultHandler,                      // Wide Timer 5 subtimer A
N    IntDefaultHandler,                      // Wide Timer 5 subtimer B
N    IntDefaultHandler,                      // FPU
N    IntDefaultHandler,                      // PECI 0
N    IntDefaultHandler,                      // LPC 0
N    IntDefaultHandler,                      // I2C4 Master and Slave
N    IntDefaultHandler,                      // I2C5 Master and Slave
N    IntDefaultHandler,                      // GPIO Port M
N    IntDefaultHandler,                      // GPIO Port N
N    IntDefaultHandler,                      // Quadrature Encoder 2
N    IntDefaultHandler,                      // Fan 0
N    0,                                      // Reserved
N    IntDefaultHandler,                      // GPIO Port P (Summary or P0)
N    IntDefaultHandler,                      // GPIO Port P1
N    IntDefaultHandler,                      // GPIO Port P2
N    IntDefaultHandler,                      // GPIO Port P3
N    IntDefaultHandler,                      // GPIO Port P4
N    IntDefaultHandler,                      // GPIO Port P5
N    IntDefaultHandler,                      // GPIO Port P6
N    IntDefaultHandler,                      // GPIO Port P7
N    IntDefaultHandler,                      // GPIO Port Q (Summary or Q0)
N    IntDefaultHandler,                      // GPIO Port Q1
N    IntDefaultHandler,                      // GPIO Port Q2
N    IntDefaultHandler,                      // GPIO Port Q3
N    IntDefaultHandler,                      // GPIO Port Q4
N    IntDefaultHandler,                      // GPIO Port Q5
N    IntDefaultHandler,                      // GPIO Port Q6
N    IntDefaultHandler,                      // GPIO Port Q7
N    IntDefaultHandler,                      // GPIO Port R
N    IntDefaultHandler,                      // GPIO Port S
N    IntDefaultHandler,                      // PWM 1 Generator 0
N    IntDefaultHandler,                      // PWM 1 Generator 1
N    IntDefaultHandler,                      // PWM 1 Generator 2
N    IntDefaultHandler,                      // PWM 1 Generator 3
N    IntDefaultHandler                       // PWM 1 Fault
N};
N
N//*****************************************************************************
N//
N// This is the code that gets called when the processor first starts execution
N// following a reset event.  Only the absolutely necessary set is performed,
N// after which the application supplied entry() routine is called.  Any fancy
N// actions (such as making decisions based on the reset cause register, and
N// resetting the bits in that register) are left solely in the hands of the
N// application.
N//
N//*****************************************************************************
Nvoid
NResetISR(void)
N{
N    //
N    // Jump to the CCS C initialization routine.  This will enable the
N    // floating-point unit as well, so that does not need to be done here.
N    //
N    __asm("    .global _c_int00\n"
N          "    b.w     _c_int00");
N}
N
N//*****************************************************************************
N//
N// This is the code that gets called when the processor receives a NMI.  This
N// simply enters an infinite loop, preserving the system state for examination
N// by a debugger.
N//
N//*****************************************************************************
Nstatic void
NNmiSR(void)
N{
N    //
N    // Enter an infinite loop.
N    //
N    while(1)
N    {
N    }
N}
N
N//*****************************************************************************
N//
N// This is the code that gets called when the processor receives a fault
N// interrupt.  This simply enters an infinite loop, preserving the system state
N// for examination by a debugger.
N//
N//*****************************************************************************
Nstatic void
NFaultISR(void)
N{
N    //
N    // Enter an infinite loop.
N    //
N    while(1)
N    {
N    }
N}
N
N//*****************************************************************************
N//
N// This is the code that gets called when the processor receives an unexpected
N// interrupt.  This simply enters an infinite loop, preserving the system state
N// for examination by a debugger.
N//
N//*****************************************************************************
Nstatic void
NIntDefaultHandler(void)
N{
N    //
N    // Go into an infinite loop.
N    //
N    while(1)
N    {
N    }
N}
