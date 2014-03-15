_stack_size = 0x3000; /*12K*/

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

    .data : /*AT(ADDR(.text) + SIZEOF(.text))*/
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM AT > FLASH

    .bss : AT (ADDR(.data) + SIZEOF(.data))
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM
	

	_heap_bottom = .;
	_heap_top = ORIGIN(SRAM) + LENGTH(SRAM) - _stack_size - 1;
	
	_stack_top = ORIGIN(SRAM) + LENGTH(SRAM) - 1;
	_stack_bottom = ORIGIN(SRAM) + LENGTH(SRAM) - 1 - _stack_size; 
}
