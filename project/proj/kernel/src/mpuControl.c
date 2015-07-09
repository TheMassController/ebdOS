//Responsible for the MPU control
//System headers
#include <hw_types.h> //Contains the types
#include <rom_map.h> //Call functions directly from the ROM if available
#include <rom.h> //Declare ROM addresses for rom funcs
#include <mpu.h>
#include <hw_memmap.h>
#include <hw_nvic.h>
#include <hw_ints.h>
#include <uartstdio.h>
//User headers
#include "kernUtils.h"

//All of these are determined by the linker, see linker_script.ld
extern unsigned long _flash_start;
extern unsigned long _flash_end;
extern unsigned long _sram_start;
extern unsigned long _sram_end;
extern unsigned long _kernel_text;
extern unsigned long _core_text;
extern unsigned long _flash_text_data_end_aligned;

//Returns 0 if given param is not a power of 2
unsigned isPowerOfTwo(unsigned size){
    if ((size & (size - 1)) == 0) {
        return size;
    } else {
        return 0;
    }
}

//Returns 0 if everything went ok
//See proj/lib/inc/mpu.h for implementation of macro's and constraints
static unsigned setMPURegion(unsigned char regionNumber, unsigned baseAddr, unsigned size, unsigned settings){
    //Test the params for sanity. The ROM function does not return, so we have to catch errors here.
    if (!isPowerOfTwo(size) || (unsigned)baseAddr % size || size == 0 || size < 32 || regionNumber > 7 ){
        return 1;
    }
    //Find the position of the two.
    //Size calculation: log2(size) - 1 (see proj/lib/inc/mpu.h)
    //log2Size is four because we need to find log2(size)-1. Size cannot be below 32, so the first five pos are already shifted out. Then apply the -1 trick here to set log2Size to log2(size)-1
    size >>= 5;
    unsigned log2Size;
    for (log2Size = 4; !(size & 1); ++log2Size){
        size >>= 1;
    }
    log2Size <<= 1; //Again, see proj/lib/inc/mpu.h
    ROM_MPURegionSet(
            regionNumber,
            (unsigned)baseAddr,
            log2Size | settings
            );
    return 0;
}

void initializeMPU(void){
    //The sizes
    const unsigned FLASHSIZE = (unsigned)&_flash_end - (unsigned)&_flash_start;
    const unsigned KERNELFLASHSIZE = (unsigned)&_core_text - (unsigned)&_kernel_text;
    const unsigned PUBLICFLASHSIZE = (unsigned)&_flash_text_data_end_aligned - (unsigned)&_core_text;
    const unsigned SRAMSIZE = (unsigned)&_sram_end - (unsigned)&_sram_start;
    //The baseadresses
    const unsigned FLASHSTART = (unsigned long)&_flash_start;
    const unsigned KERNELFLASHSTART = (unsigned long)&_kernel_text;
    const unsigned PUBLICFLASHSTART = (unsigned long)&_core_text;
    const unsigned SRAMSTART = (unsigned long)&_sram_start;
    //Global flash region: the fallback region
    if (setMPURegion(0, FLASHSTART, FLASHSIZE, MPU_RGN_PERM_NOEXEC | MPU_RGN_PERM_PRV_RW_USR_RO | MPU_RGN_ENABLE)){
        UARTprintf("Setting up the default flash region failed\n");
        generateCrash();
    }
    //The kernelflash region: only readable for privilege
    if (setMPURegion(1, KERNELFLASHSTART, KERNELFLASHSIZE, MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_NO | MPU_RGN_ENABLE)){
        UARTprintf("Setting up the kernel flash region failed\n");
        generateCrash();
    }
    //The public region, readable for everyone
    if (setMPURegion(2, PUBLICFLASHSTART, PUBLICFLASHSIZE, MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_RO | MPU_RGN_ENABLE)){
        UARTprintf("Setting up the public flash region failed\n");
        generateCrash();
    }
    //The global SRAM region: the fallback region
    if (setMPURegion(3, SRAMSTART, SRAMSIZE,  MPU_RGN_PERM_NOEXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE)){
        UARTprintf("Setting up the global SRAM region failed\n");
        generateCrash();
    }
    //ROM region (datasheet pp 87)
    //TODO magic numbers
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
