//Responsible for the MPU control
#include "hw_types.h" //Contains the types
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include <mpu.h>
#include <hw_memmap.h>
#include <hw_nvic.h>
#include <hw_ints.h>

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
    ROM_MPUEnable(MPU_CONFIG_PRIV_DEFAULT);
    ROM_MPURegionSet(
            0, 
            (unsigned long)&_flash_start,
            MPU_RGN_SIZE_256K | MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_NO | MPU_RGN_ENABLE
            );
    unsigned long regLen = (unsigned long)&_core_text - (unsigned long)&_kernel_text; 
    if (!testRegionSize(regLen)){
#ifdef DEBUG
        UARTprintf("The region flash length is incorrect (region length: %u)\r\n", (unsigned)regLen);
#endif //DEBUG
    }
    ROM_MPURegionSet(
            1,
            (unsigned long)&_kernel_text,
            regLen |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_NO | MPU_RGN_ENABLE
            );
    ROM_MPURegionSet(
            2,
            (unsigned long)0x20000000,
            MPU_RGN_SIZE_32K |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
    ROM_MPURegionSet(
            7,
            (unsigned long)0x10000000,
            MPU_RGN_SIZE_32K |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
    ROM_MPURegionSet(
            6,
            (unsigned long)0x40000000,
            MPU_RGN_SIZE_4G |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
    //HWREG(0x100) = 0x12345678;
}
