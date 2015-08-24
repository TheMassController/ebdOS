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

// SYSCTL_SETUP is PLL setup
// BASE_CLOCK_SPEED is global base clock speed after the PLL is set
// SLEEP_CLOCK_INCREASE_CYCLES the sleep clock increases every so many cycles of the main clock, is always equal to 1 us
#ifdef EBD_OS_CLOCK_40MHZ
    #define EBD_SYSCTL_SETUP (SYSCTL_SYSDIV_5| SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ)
    #define EBD_BASE_CLOCK_SPEED 40000000
    #define EBD_SLEEP_CLOCK_INCREASE_CYCLES 40
#elif EBD_OS_CLOCK_16MHZ
    #define EBD_SYSCTL_SETUP (SYSCTL_USE_OSC | SYSCTL_OSC_MAIN| SYSCTL_XTAL_16MHZ)
    #define EBD_BASE_CLOCK_SPEED 16000000
    #define EBD_SLEEP_CLOCK_INCREASE_CYCLES 16
#elif EBD_OS_CLOCK_10MHZ
    #define EBD_SYSCTL_SETUP (SYSCTL_SYSDIV_20| SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ)
    #define EBD_BASE_CLOCK_SPEED 10000000
    #define EBD_SLEEP_CLOCK_INCREASE_CYCLES 10
#else // Default is 80 Mhz
    #define EBD_SYSCTL_SETUP (SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ)
    #define EBD_BASE_CLOCK_SPEED 80000000
    #define EBD_SLEEP_CLOCK_INCREASE_CYCLES 80
#endif


#endif //CLOCKSETUP_H
