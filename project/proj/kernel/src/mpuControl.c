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

unsigned long testRegionSize(unsigned long regionLen){
    if ((regionLen & (regionLen - 1)) == 0) {
        return regionLen;
    } else {
        return 0;
    }
}

void initializeMPU(void){
    ROM_MPUEnable(MPU_CONFIG_PRIV_DEFAULT);
    unsigned long pulAddr, pulFlags;
    for (int i = 0; i < 8; ++i){
        ROM_MPURegionGet(i, &pulAddr, &pulFlags);
        UARTprintf("Region: %i\n\tpulAddr: 0x%x\n\tpulFlags:0x%x\n", i, pulAddr, pulFlags);
    }
    //Lets start with FLASH. 3 regions:
    //1. Kernel code and data (only privileged read)
    //2. Other code and data (everyone read)
    //3. Unused FLASH (only privileged r/w, unprivileged no)
    //Kernel code and data runs until _core_text
    const unsigned long FLASHSIZE = &_flash_end - &_flash_start;
    const unsigned long KERNELFLASHSIZE = &_core_text - &_kernel_text;
    const unsigned long PUBLICFLASHSIZE = &_flash_text_data_end_aligned - &_core_text;
    const unsigned long SRAMSIZE = &_sram_end - &_sram_start;

    const unsigned long FLASHSTART = (unsigned long)&_flash_start;
    const unsigned long KERNELFLASHSTART = (unsigned long)&_kernel_text;
    const unsigned long PUBLICFLASHSTART = (unsigned long)&_core_text;
    const unsigned long SRAMSTART = (unsigned long)&_sram_start;

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
            FLASHSIZE |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
    //Talks purely about the kernel .text and .data sections
    ROM_MPURegionSet(
            1,
            KERNELFLASHSTART,
            KERNELFLASHSIZE |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
    //Talks about al other .text and .data sections
    ROM_MPURegionSet (
            2,
            PUBLICFLASHSTART,
            PUBLICFLASHSIZE | MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
            );
    
    //End of flash, start of SRAM
    //Global SRAM region, provides a set of default permissions for the SRAM
    ROM_MPURegionSet (
            3,
            SRAMSTART,
            SRAMSIZE | MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE
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
    for (int i = 0; i < 8; ++i){
        ROM_MPURegionGet(i, &pulAddr, &pulFlags);
        UARTprintf("Region: %i\n\tpulAddr: 0x%x\n\tpulFlags:0x%x\n", i, pulAddr, pulFlags);
    }
    UARTprintf("%x\n", KERNELFLASHSTART);
    UARTprintf("0x%x\n", FLASHSIZE |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE);
    UARTprintf("0x%x\n", KERNELFLASHSIZE |  MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RW_USR_RW | MPU_RGN_ENABLE);
}
