#include "hw_nvic.h"
#include "hw_types.h"
#include "uartstdio.h"
#include "timer.h"
#include "hw_memmap.h" //address of GPIO etc
#include "uartstdio.h"
#include "lm4f120h5qr.h" //Hardware regs
#include "hw_types.h" //Contains the special types
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs

//Used for unrecoverable errors
void generateNMI(void){
     NVIC_INT_CTRL_R |= (1<<31);
}
