#include <hw_nvic.h>
#include <hw_types.h>

#include "uartstdio.h"
#include "core/inc/coreUtils.h"
#include "systemClockManagement.h"  // Contains all the timer interrupts

void ResetISR(void);
static void IntDefaultHandler(void);

//System stack start, defined in linker script
extern char _stack_top;

/* All sorts of declarations that we want to use here, but nowhere else.
 * So these functions are not declared in headers but here.
 */

// Declared in setup.c
#ifdef __GNUC__
void kernelStart(void) __attribute__ ((noreturn));
#else
void kernelStart(void);
#endif //__GNUC__

void pendSVHandler(void);           // Declared in contextSwitcher.S
void svcHandler(void);              // Declared in supervisorHandler.S
void sysTickHandler(void);          // Declared in scheduler.c
void usageFaultHandler(void);       // Declared in fault.c
void mpuFaultHandler(void);         // Declared in fault.c
void busFaultHandler(void);         // Declared in fault.c
void faultISRHandler(void);         // Declared in fault.c
void NMIHandler(void);              // Declared in fault.c

/* Temporary handlers, not here to stay */
void gpioBInterrup(void);

// The vector table, the linker script makes sure this one is placed at 0x0 (FLASH)
__attribute__ ((section(".isr_vector")))
void (* const gpFnVectors[])(void) =
{
	(void (*)(void))((unsigned long)(&_stack_top)), // The initial stack pointer
    ResetISR,                                       // The reset handler
    NMIHandler,                                     // The NMI handler
    faultISRHandler,                                // The hard fault handler
    mpuFaultHandler,                                // The MPU fault handler
    busFaultHandler,                                // The bus fault handler
    usageFaultHandler,                              // The usage fault handler
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    svcHandler,                                     // SVCall handler
    IntDefaultHandler,                              // Debug monitor handler
    0,                                              // Reserved
    pendSVHandler,                                  // The PendSV handler
    sysTickHandler,                                 // The SysTick handler
    IntDefaultHandler,                              // GPIO Port A
    gpioBInterrup,                                  // GPIO Port B
    IntDefaultHandler,                              // GPIO Port C
    IntDefaultHandler,                              // GPIO Port D
    IntDefaultHandler,                              // GPIO Port E
    IntDefaultHandler,                              // UART0 Rx and Tx
    IntDefaultHandler,                              // UART1 Rx and Tx
    IntDefaultHandler,                              // SSI0 Rx and Tx
    IntDefaultHandler,                              // I2C0 Master and Slave
    IntDefaultHandler,                              // PWM Fault
    IntDefaultHandler,                              // PWM Generator 0
    IntDefaultHandler,                              // PWM Generator 1
    IntDefaultHandler,                              // PWM Generator 2
    IntDefaultHandler,                              // Quadrature Encoder 0
    IntDefaultHandler,                              // ADC Sequence 0
    IntDefaultHandler,                              // ADC Sequence 1
    IntDefaultHandler,                              // ADC Sequence 2
    IntDefaultHandler,                              // ADC Sequence 3
    IntDefaultHandler,                              // Watchdog timer
    IntDefaultHandler,                              // Timer 0 subtimer A
    IntDefaultHandler,                              // Timer 0 subtimer B
    IntDefaultHandler,                              // Timer 1 subtimer A
    IntDefaultHandler,                              // Timer 1 subtimer B
    IntDefaultHandler,                              // Timer 2 subtimer A
    IntDefaultHandler,                              // Timer 2 subtimer B
    IntDefaultHandler,                              // Analog Comparator 0
    IntDefaultHandler,                              // Analog Comparator 1
    IntDefaultHandler,                              // Analog Comparator 2
    IntDefaultHandler,                              // System Control (PLL, OSC, BO)
    IntDefaultHandler,                              // FLASH Control
    IntDefaultHandler,                              // GPIO Port F
    IntDefaultHandler,                              // GPIO Port G
    IntDefaultHandler,                              // GPIO Port H
    IntDefaultHandler,                              // UART2 Rx and Tx
    IntDefaultHandler,                              // SSI1 Rx and Tx
    IntDefaultHandler,                              // Timer 3 subtimer A
    IntDefaultHandler,                              // Timer 3 subtimer B
    IntDefaultHandler,                              // I2C1 Master and Slave
    IntDefaultHandler,                              // Quadrature Encoder 1
    IntDefaultHandler,                              // CAN0
    IntDefaultHandler,                              // CAN1
    IntDefaultHandler,                              // CAN2
    IntDefaultHandler,                              // Ethernet
    IntDefaultHandler,                              // Hibernate
    IntDefaultHandler,                              // USB0
    IntDefaultHandler,                              // PWM Generator 3
    IntDefaultHandler,                              // uDMA Software Transfer
    IntDefaultHandler,                              // uDMA Error
    IntDefaultHandler,                              // ADC1 Sequence 0
    IntDefaultHandler,                              // ADC1 Sequence 1
    IntDefaultHandler,                              // ADC1 Sequence 2
    IntDefaultHandler,                              // ADC1 Sequence 3
    IntDefaultHandler,                              // I2S0
    IntDefaultHandler,                              // External Bus Interface 0
    IntDefaultHandler,                              // GPIO Port J
    IntDefaultHandler,                              // GPIO Port K
    IntDefaultHandler,                              // GPIO Port L
    IntDefaultHandler,                              // SSI2 Rx and Tx
    IntDefaultHandler,                              // SSI3 Rx and Tx
    IntDefaultHandler,                              // UART3 Rx and Tx
    IntDefaultHandler,                              // UART4 Rx and Tx
    IntDefaultHandler,                              // UART5 Rx and Tx
    IntDefaultHandler,                              // UART6 Rx and Tx
    IntDefaultHandler,                              // UART7 Rx and Tx
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    IntDefaultHandler,                              // I2C2 Master and Slave
    IntDefaultHandler,                              // I2C3 Master and Slave
    IntDefaultHandler,                              // Timer 4 subtimer A
    IntDefaultHandler,                              // Timer 4 subtimer B
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    IntDefaultHandler,                              // Timer 5 subtimer A
    IntDefaultHandler,                              // Timer 5 subtimer B
    systemTimerInterrupt,                           // Wide Timer 0 subtimer A
    sleepTimerInterrupt,                            // Wide Timer 0 subtimer B
    managedLockTimerInterrupt,                      // Wide Timer 1 subtimer A
    IntDefaultHandler,                              // Wide Timer 1 subtimer B
    IntDefaultHandler,                              // Wide Timer 2 subtimer A
    IntDefaultHandler,                              // Wide Timer 2 subtimer B
    IntDefaultHandler,                              // Wide Timer 3 subtimer A
    IntDefaultHandler,                              // Wide Timer 3 subtimer B
    IntDefaultHandler,                              // Wide Timer 4 subtimer A
    IntDefaultHandler,                              // Wide Timer 4 subtimer B
    IntDefaultHandler,                              // Wide Timer 5 subtimer A
    IntDefaultHandler,                              // Wide Timer 5 subtimer B
    IntDefaultHandler,                              // FPU
    IntDefaultHandler,                              // PECI 0
    IntDefaultHandler,                              // LPC 0
    IntDefaultHandler,                              // I2C4 Master and Slave
    IntDefaultHandler,                              // I2C5 Master and Slave
    IntDefaultHandler,                              // GPIO Port M
    IntDefaultHandler,                              // GPIO Port N
    IntDefaultHandler,                              // Quadrature Encoder 2
    IntDefaultHandler,                              // Fan 0
    0,                                              // Reserved
    IntDefaultHandler,                              // GPIO Port P (Summary or P0)
    IntDefaultHandler,                              // GPIO Port P1
    IntDefaultHandler,                              // GPIO Port P2
    IntDefaultHandler,                              // GPIO Port P3
    IntDefaultHandler,                              // GPIO Port P4
    IntDefaultHandler,                              // GPIO Port P5
    IntDefaultHandler,                              // GPIO Port P6
    IntDefaultHandler,                              // GPIO Port P7
    IntDefaultHandler,                              // GPIO Port Q (Summary or Q0)
    IntDefaultHandler,                              // GPIO Port Q1
    IntDefaultHandler,                              // GPIO Port Q2
    IntDefaultHandler,                              // GPIO Port Q3
    IntDefaultHandler,                              // GPIO Port Q4
    IntDefaultHandler,                              // GPIO Port Q5
    IntDefaultHandler,                              // GPIO Port Q6
    IntDefaultHandler,                              // GPIO Port Q7
    IntDefaultHandler,                              // GPIO Port R
    IntDefaultHandler,                              // GPIO Port S
    IntDefaultHandler,                              // PWM 1 Generator 0
    IntDefaultHandler,                              // PWM 1 Generator 1
    IntDefaultHandler,                              // PWM 1 Generator 2
    IntDefaultHandler,                              // PWM 1 Generator 3
    IntDefaultHandler                               // PWM 1 Fault
};

extern unsigned long _kernel_data;
extern unsigned long _kernel_edata;
extern unsigned long _kernel_bss;
extern unsigned long _kernel_ebss;

extern unsigned long _core_data;
extern unsigned long _core_edata;
extern unsigned long _core_bss;
extern unsigned long _core_ebss;

extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

extern unsigned long _kernel_flash_data;
extern unsigned long _core_flash_data;
extern unsigned long _flash_data;

void ResetISR(void)
{
    volatile unsigned long *pulSrc, *pulDest;

    // Copy the data segment initializers from flash to SRAM.
    pulSrc = &_kernel_flash_data;
    for(pulDest = &_kernel_data; pulDest < &_kernel_edata; )
    {
        *pulDest++ = *pulSrc++;
    }

    pulSrc = &_core_flash_data;
    for(pulDest = &_core_data; pulDest < &_core_edata; )
    {
        *pulDest++ = *pulSrc++;
    }

    pulSrc = &_flash_data;
    for(pulDest = &_data; pulDest < &_edata; )
    {
        *pulDest++ = *pulSrc++;
    }

    // Zero fill the bss segments.
    zeroFillSection(&_kernel_bss, &_kernel_ebss);
    zeroFillSection(&_core_bss, &_core_ebss);
    zeroFillSection(&_bss, &_ebss);

    //Jump to the software init
	kernelStart();
}

static void IntDefaultHandler(void)
{
    UARTprintf("Default interrupt handler called\r\n");
    while(1);
}
