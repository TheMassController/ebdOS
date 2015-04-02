_stack_buffer = 128; /*128 byte buffer between HEAP and STACK*/

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

SECTIONS
{
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
