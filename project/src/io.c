#include "hw_memmap.h"      //Needed for GPIO Pins/UART base
#include "hw_types.h"       //Needed for SysTick Types
#include "rom.h"
#include "rom_map.h"

int _read(int file, char *ptr, int len)
{
    unsigned int i;
    for( i = 0; i < len; i++ ){
        ptr[i] = (char)MAP_UARTCharGet(UART0_BASE);
    }
    return len;
}

int _write(int file, char *ptr, unsigned int len)
{
    unsigned int i;
    for(i = 0; i < len; i++){
        MAP_UARTCharPut(UART0_BASE, ptr[i]);
    }
    return i;
}
