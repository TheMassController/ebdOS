_stack_size = 0x1000; /*4K*/

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

    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM

    .bss : AT (ADDR(.data) + SIZEOF(.data))
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM
    _heap_bottom = ORIGIN(SRAM) + LENGTH(SRAM) - 1; /*Heap Bottom is at the lowest part of the SRAM and grows up*/                                          
    _heap_top = ORIGIN(SRAM) + _stack_size - 1;     /*Origin SRAM + stack size is top of heap. Heap grows up*/ 

    _stack_bottom = ORIGIN(SRAM) + _stack_size - 1;
    _stack_top = ORIGIN(SRAM); /*Stack start is at the top of the SRAM*/	
}
