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
        _kernel_flash_data = .;
    } > FLASH

    .kernel.data : /*AT(ADDR(.text) + SIZEOF(.text))*/ /*contains initialized data*/  /*This one is usually empty, which makes the linker misbehave.*/
    {
        _kernel_data = .;
        kernel.a(vtable)
        kernel.a(.data*)
        _kernel_edata = .;
    } > SRAM AT > FLASH

    .kernel.bss :
    {
        _kernel_bss = .;
        kernel.a(.bss*)
        kernel.a(COMMON)
        _kernel_ebss = .;
    } > SRAM

    .core.text : ALIGN(4096)  /*Aligned on 4096 */ /*Disputable wether or not alignment is useful here because rw and execute are different things: user can still execute code that it cannot read. */
    {
        _core_text = .;
        core.a(.text*)
        core.a(.rodata*)
        _core_etext = .;
        _core_flash_data = .;
    } > FLASH

    .core.bss :  /* Aligned on 2048*/
    {
        _core_bss = .;
        core.a(.bss*)
        core.a(COMMON)
        _core_ebss = .;
    } > SRAM

    .core.data : /*ALIGN(0x800) /*Only if .core.data size is not null this alignment is useful */
    {
        _core_data = .;
        core.a(vtable)
        core.a(.data*)
        _core_edata = .;
    } >SRAM AT > FLASH


    .text : /*ALIGN(0x1000) /*Aligned on 1024 */
    {
        _text = .;
        *(.text*)
        *(.rodata*)
        _etext = .;
        _flash_data = ALIGN(0x4);
    } > FLASH

    .data : /*ALIGN(0x400) */
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
        _start_heap = .;
    } > SRAM AT > FLASH

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM

    _flash_text_data_end = _etext +  SIZEOF(.data);
    _flash_text_data_end_aligned = (2 << LOG2CEIL( _etext +  SIZEOF(.data)));
    _data_size = SIZEOF(.data);
	_stack_top = ORIGIN(SRAM) + LENGTH(SRAM) - 1; /*The starting point of the stack, at the very bottom of the RAM*/
    _flash_start = ORIGIN(FLASH);
    _flash_end = ORIGIN(FLASH) + LENGTH(FLASH);
    _sram_start = ORIGIN(SRAM);
    _sram_end = ORIGIN(SRAM) + LENGTH(SRAM);
}
