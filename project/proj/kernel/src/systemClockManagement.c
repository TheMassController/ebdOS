#include <rom.h>            // Declare ROM addresses for rom funcs
#include <hw_types.h>       // Defines for TI libs
#include <timer.h>          // Function prototypes for timer hw interaction
#include <hw_memmap.h>      // address of GPIO etc

#include "systemClockManagement.h"
#include "kernEventNotifier.h"

void systemTimerInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE,  TIMER_CAPA_MATCH|TIMER_CAPA_EVENT|TIMER_TIMA_TIMEOUT);
    passMessageToKernel(sysTimerOverflow);
}

void sleepTimerInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE,  TIMER_TIMB_MATCH);
    passMessageToKernel(sleepTimerExpired);
}

unsigned getSystemClockValue(void){
    return ROM_TimerValueGet(WTIMER0_BASE, TIMER_A);
}
