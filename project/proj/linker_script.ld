_stack_buffer = 128; /*128 byte buffer between HEAP and STACK*/

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

SECTIONS
{
    .kernel.text :
    {
        _kernel_text = .;
        KEEP(kernel.a(.isr_vector))
        kernel.a(.text*)
        kernel.a(.rodata*)
        _kernel_etext = .;
    } > FLASH

    .kernel.data : /*AT(ADDR(.text) + SIZEOF(.text))*/ /*contains initialized data*/
    {
        _kernel_data = .;
        kernel.a(vtable)
        kernel.a(.data*)
        _kernel_edata = .;
    } > SRAM AT > FLASH

    .kernel.bss : AT (ADDR(.kernel.data) + SIZEOF(.kernel.data)) /*contains unitialized data (should be set to all zero's)*/
    {
        _kernel_bss = .;
        kernel.a(.bss*)
        kernel.a(COMMON)
        _kernel_ebss = .;
    } > SRAM

    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : /*AT(ADDR(.text) + SIZEOF(.text))*/ /*contains initialized data*/
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM AT > FLASH

    .bss : AT (ADDR(.data) + SIZEOF(.data)) /*contains unitialized data (should be set to all zero's)*/
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
        _start_heap = .;
    } > SRAM

	_stack_top = ORIGIN(SRAM) + LENGTH(SRAM) - 1; /*The starting point of the stack, at the very bottom of the RAM*/
}
