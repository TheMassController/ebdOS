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
        KEEP(kernel.a(_sbrk))
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
    
    /*TODO allign to be a bit nicer to the MPU */

    .core.text : AT (ADDR(.kernel.text) + SIZEOF(.kernel.text) + SIZEOF(.kernel.data))
    {
        _core_text = .;
        core.a(.text*)
        core.a(.rodata*)
        _core_etext = .;
    } > FLASH

    .core.data :
    {
        _core_data = .;
        core.a(vtable)
        core.a(.data*)
        _core_edata = .;
    } >SRAM AT > FLASH

    .core.bss :
    {
        _core_bss = .;
        core.a(.bss*)
        core.a(COMMON)
        _core_ebss = .;
    } > SRAM

    /*TODO allign to be a bit nicer to the MPU */

    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : 
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
