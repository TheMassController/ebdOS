//Responsible for the MPU control
#include "hw_types.h" //Contains the types
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include <mpu.h>

#ifdef DEBUG
    #include "uartstdio.h"
#endif //DEBUG

//Flash addresses
extern unsigned long _flash_start;
extern unsigned long _flash_end;

//kernel code start
extern unsigned long _kernel_text;
//Core code start
extern unsigned long _core_text;

unsigned long testRegionSize(unsigned long regionLen){
    if ((regionLen & (regionLen - 1)) == 0) {
        return regionLen;
    } else {
        return 0;
    }
}

void initializeMPU(void){
    //Region 0 protects the entire SRAM, making it RO, RO
    unsigned long regLen = (unsigned long)&_flash_end - (unsigned long)&_flash_start; 
    if (!testRegionSize(regLen)){
#ifdef DEBUG
        UARTprintf("The region flash length is incorrect (region length: %u)", (unsigned)regLen);
#endif //DEBUG
    }
    ROM_MPURegionSet(
            0, 
            (unsigned long)&_flash_start,
            MPU_RGN_SIZE_256K | MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_RO | MPU_RGN_ENABLE
            );
    ROM_MPURegionEnable(0);
    ROM_MPUEnable(MPU_CONFIG_PRIV_DEFAULT);
}
