#ifndef CLOCKSETUP_H
#define CLOCKSETUP_H

#include <sysctl.h>
/**
 * @file clockSetup.h
 * @author Jacko Dirks
 * This file defines the clock speed and all its deratives and setttings, including PLL settings and ticks per us.
 * You cannot change the clock speed after compilation
 */

// Datasheet pp 217
// ROM api pp 182
// Base speed after PLL is 200 MHz. 80 is the max the CPU can handle

#define PC_BAUDRATE 115200
#define EDB_OS_CLOCK_80MHZ

// The next table defines the possible clock speeds
const unsigned CLOCKSPEEDS_SYSCTL[] = {
    (SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ),  // 80 Mhz
    (SYSCTL_SYSDIV_5| SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ),    // 40 Mhz
    (SYSCTL_USE_OSC | SYSCTL_OSC_MAIN| SYSCTL_XTAL_16MHZ),                  // 16 Mhz
    (SYSCTL_SYSDIV_20 | SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ)   // 10 Mhz
};

// SYSCTL_SETUP is PLL setup
// BASE_CLOCK_SPEED is global base clock speed after the PLL is set
// SLEEP_CLOCK_INCREASE_CYCLES the sleep clock increases every so many cycles of the main clock, is always equal to 1 us
#ifdef  EDB_OS_CLOCK_80MHZ
    #define EDB_SYSCTL_ENTRY 0
#elif   EBD_OS_CLOCK_40MHZ
    #define EDB_SYSCTL_ENTRY 1
#elif   EBD_OS_CLOCK_16MHZ
    #define EDB_SYSCTL_ENTRY 2
#elif   EBD_OS_CLOCK_10MHZ
    #define EDB_SYSCTL_ENTRY 3
#else
    #error "No clockspeed was defined!"
#endif


#endif //CLOCKSETUP_H
