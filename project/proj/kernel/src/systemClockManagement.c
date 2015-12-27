#include <rom.h>            // Declare ROM addresses for rom funcs
#include <hw_types.h>       // Defines for TI libs
#include <timer.h>          // Function prototypes for timer hw interaction
#include <hw_memmap.h>      // address of GPIO etc

#include "systemClockManagement.h"
#include "kernEventNotifier.h"

void systemTimerInterrupt(void){
    passMessageToKernel(sysTimerOverflow);
}

void sleepTimerInterrupt(void){
    passMessageToKernel(sleepTimerExpired);
}

unsigned getSystemClockValue(void){
    return ROM_TimerValueGet(WTIMER0_BASE, TIMER_A);
}
