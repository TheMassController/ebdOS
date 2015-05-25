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

/*

   void initializeMPU(void){
//ROM_MPUEnable(MPU_CONFIG_PRIV_DEFAULT);
//Lets start with FLASH. 3 regions:
//1. Kernel code and data (only privileged read)
//2. Other code and data (everyone read)
//3. Unused FLASH (only privileged r/w, unprivileged no)
//Kernel code and data runs until _core_text

//Start with some tests. If the linker made mistakes, these cannot be compensated for here. So the kernel will crash.
if (! testRegionSize(FLASHSIZE)){
UARTprintf("The size of the region that is the flash itself is not a power of two. Region size is: 0x%x\n", FLASHSIZE);
generateCrash();
}
if (! testRegionSize(KERNELFLASHSIZE)){
UARTprintf("The region size of kernel_text and kernel_data is not a power of two. Region size is: 0x%x\n", (unsigned long)(&_core_text - &_kernel_text));
generateCrash();
}
if (! testRegionSize(PUBLICFLASHSIZE)){
UARTprintf("The region size of core text, core data, user text and user data is not a power of two. Region size is: 0x%x\n", (unsigned long)(&_flash_text_data_end_aligned - &_core_text));
generateCrash();
}
if ((FLASHSTART % FLASHSIZE)){
UARTprintf("The baseadress of the flash has to be aligned to 0x%x\n", FLASHSIZE);
generateCrash();
}
if ((KERNELFLASHSTART % KERNELFLASHSIZE)) {
UARTprintf("The baseadress of the kernel text has to be aligned to 0x%x\n", KERNELFLASHSIZE);
generateCrash();
} 
if ((PUBLICFLASHSTART % PUBLICFLASHSIZE)) {
UARTprintf("The baseaddress of the public .text has to be aligned to 0x%x\n", PUBLICFLASHSIZE);
generateCrash();
}
if ((SRAMSTART % SRAMSIZE)) {
UARTprintf("The baseaddress of the SRAM has to be algined to 0x%x\n", SRAMSIZE);
generateCrash();
}
//Tests have passed, setup the first three MPU regions: the flash regions
//TODO the data sections, how do we want to handle those?

//Global flash region, provides a set of base permissions for the flash
ROM_MPURegionSet(
0,
FLASHSTART,
FLASHSIZE |  MPU_RGN_PERM_NOEXEC | MPU_RGN_PERM_PRV_RW_USR_RO | MPU_RGN_ENABLE
);
//Talks purely about the kernel .text and .data sections
ROM_MPURegionSet(
1,
KERNELFLASHSTART,
KERNELFLASHSIZE |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_NO | MPU_RGN_ENABLE
);
//Talks about al other .text and .data sections
ROM_MPURegionSet (
2,
PUBLICFLASHSTART,
PUBLICFLASHSIZE | MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_RO | MPU_RGN_ENABLE
);

//End of flash, start of SRAM
//Global SRAM region, provides a set of default permissions for the SRAM
ROM_MPURegionSet (
3,
SRAMSTART,
SRAMSIZE | MPU_RGN_PERM_NOEXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
);

//EEPROM and regs
//TODO make them a bit more pretty
ROM_MPURegionSet(
        4,
        (unsigned long)0x10000000,
        MPU_RGN_SIZE_32K |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
        );
ROM_MPURegionSet(
        5,
        (unsigned long)0x40000000,
        MPU_RGN_SIZE_32K |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
        );
ROM_MPURegionDisable(6);
ROM_MPURegionDisable(7);
unsigned long pulAddr, pulFlags;
for (int i = 0; i < 8; ++i){
    ROM_MPURegionGet(i, &pulAddr, &pulFlags);
    UARTprintf("Region: %i\n\tpulAddr: 0x%x\n\tpulFlags:0x%x\n", i, pulAddr, pulFlags);
}
UARTprintf("%x\n", KERNELFLASHSTART);
UARTprintf("0x%x\n", FLASHSIZE |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE);
UARTprintf("0x%x\n", KERNELFLASHSIZE |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE);
}*/
