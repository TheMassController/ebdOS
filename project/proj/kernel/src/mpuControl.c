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

//SRAM addresses
extern unsigned long _sram_start;
extern unsigned long _sram_end;

//kernel code start
extern unsigned long _kernel_text;
//Core code start
extern unsigned long _core_text;
//Flash end
extern unsigned long _flash_text_data_end_aligned;

//Datsheet pp 124
#define PRIV_NO_USR_NO 0
//      PRIV_NO_USR_RO      //These do not exist
//      PRIV_NO_USR_RW      //These do not exist
#define PRIV_RO_USR_NO 5    //101
#define PRIV_RO_USR_RO 7    //111
//      PRIV_RO_USR_RW      //These do not exist
#define PRIV_RW_USR_NO 1    //001
#define PRIV_RW_USR_RO 2    //010
#define PRIV_RW_USR_RW 3    //011



unsigned isPowerOfTwo(unsigned regionLen){
    if ((regionLen & (regionLen - 1)) == 0) {
        return regionLen;
    } else {
        return 0;
    }
}

//Returns 1 if everything went ok
unsigned setMPURegion(unsigned char regionNumber, unsigned baseAddr, unsigned size, unsigned settings){
    if (!isPowerOfTwo(size) || (unsigned)baseAddr % size || size == 0 || size < 32 || regionNumber > 7 ){
        return 0;
    }
    //Find the position of the two.
    size >>= 5;
    unsigned log2Size;
    //Size calculation: log2(size) - 1 (see proj/lib/inc/mpu.h)
    //The sizeCopy & 1 is to test if the correct pos has been found
    //log2Size is four because we need to find log2(size)-1. Size cannot be below 32, so the first five pos are already shifted out. Then apply the -1 trick here to set log2Size to log2(size)-1
    for (log2Size = 4; log2Size < 32 && !(size & 1); ++log2Size){
        size >>= 1;
    }
    log2Size <<= 1; //Again, see proj/lib/inc/mpu.h
    ROM_MPURegionSet(
            regionNumber,
            (unsigned)baseAddr,
            log2Size | settings
            );
    return 1;
}

void initializeMPU(void){
    //Region 0 protects the entire SRAM, making it RO, RO
    const unsigned FLASHSIZE = (unsigned)&_flash_end - (unsigned)&_flash_start;
    const unsigned KERNELFLASHSIZE = (unsigned)&_core_text - (unsigned)&_kernel_text;
    const unsigned PUBLICFLASHSIZE = (unsigned)&_flash_text_data_end_aligned - (unsigned)&_core_text;
    const unsigned SRAMSIZE = (unsigned)&_sram_end - (unsigned)&_sram_start;

    const unsigned FLASHSTART = (unsigned long)&_flash_start;
    const unsigned KERNELFLASHSTART = (unsigned long)&_kernel_text;
    const unsigned PUBLICFLASHSTART = (unsigned long)&_core_text;
    const unsigned SRAMSTART = (unsigned long)&_sram_start;


    if (!setMPURegion(0, FLASHSTART, FLASHSIZE, MPU_RGN_PERM_NOEXEC | MPU_RGN_PERM_PRV_RW_USR_NO | MPU_RGN_ENABLE)){
        UARTprintf("Setting up the default flash region failed\n");
        generateCrash();
    }
    if (!setMPURegion(1, KERNELFLASHSTART, KERNELFLASHSIZE, MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_NO | MPU_RGN_ENABLE)){
        UARTprintf("Setting up the kernel flash region failed\n");
        generateCrash();
    }
    if (!setMPURegion(2, PUBLICFLASHSTART, PUBLICFLASHSIZE, MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_RO | MPU_RGN_ENABLE)){
        UARTprintf("Setting up the public flash region failed\n");
        generateCrash();
    }
    if (!setMPURegion(3, SRAMSTART, SRAMSIZE,  MPU_RGN_PERM_NOEXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE)){
        UARTprintf("Setting up the global SRAM region failed\n");
        generateCrash();
    }
    //ROM region (datasheet pp 87)
    ROM_MPURegionSet(
            7,
            (unsigned long)0x01000000,
            MPU_RGN_SIZE_16M |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_RO | MPU_RGN_ENABLE
            );
    //Peripherals region (datasheet pp 87)
    ROM_MPURegionSet(
            6,
            (unsigned long)0x40000000,
            MPU_RGN_SIZE_64M |  MPU_RGN_PERM_NOEXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
    ROM_MPUEnable(MPU_CONFIG_PRIV_DEFAULT);
}
