//Responsible for the MPU control
#include "hw_types.h" //Contains the types
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include <mpu.h>
#include <hw_memmap.h>
#include <hw_nvic.h>
#include <hw_ints.h>

#include "uartstdio.h"
#include "utilFuncs.h"

//Flash addresses
extern unsigned long _flash_start;
extern unsigned long _flash_end;

//kernel code start
extern unsigned long _kernel_text;
//Core code start
extern unsigned long _core_text;
//Flash end
extern unsigned long _flash_text_data_end_aligned;

unsigned long testRegionSize(unsigned long regionLen){
    if ((regionLen & (regionLen - 1)) == 0) {
        return regionLen;
    } else {
        return 0;
    }
}

void initializeMPU(void){
    ROM_MPUEnable(MPU_CONFIG_PRIV_DEFAULT);
    //Lets start with FLASH. 3 regions:
    //1. Kernel code and data (only privileged read)
    //2. Other code and data (everyone read)
    //3. Unused FLASH (only privileged r/w)
    //Kernel code and data runs until _core_text
    //Because all three sizes need to be power of two's, we are going to exploit the overlapping mechanism of the MPU
    //
    //Start with some tests. If the linker made mistakes, these cannot be compensated for here. So the kernel will crash.
    if (! testRegionSize(&_core_text - &_kernel_text)){
        UARTprintf("The region size of kernel_text and kernel_data is not a power of two. Region size is: 0x%x\n", (unsigned long)(&_core_text - &_kernel_text));
        generateCrash();
    }
    if (
    //Region 3, for the unused flash
    ROM_MPURegionSet(
            0,
            (unsigned long)&_flash_start,
            MPU_RGN_SIZE_256K |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_NO | MPU_RGN_ENABLE
            );
    //Core and text run until flash_text_data_end
    ROM_MPURegionSet(
            1,
            (unsigned long)0x20000000,
            MPU_RGN_SIZE_32K |  MPU_RGN_PERM_NOEXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
    ROM_MPURegionSet(
            2,
            (unsigned long)0x10000000,
            MPU_RGN_SIZE_32K |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
    ROM_MPURegionSet(
            3,
            (unsigned long)0x40000000,
            MPU_RGN_SIZE_32K |  MPU_RGN_PERM_NOEXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
}
