#include <hw_nvic.h>        // Macros for NVIC
#include <hw_types.h>       // Defines for TI libs
#include <timer.h>          // Function prototypes for timer hw interaction
#include <lm4f120h5qr.h>    // Hardware regs

#include "systemClockManagement.h"
#include "supervisorCall.h"

void systemTimerInterrupt(void){
    CALLSUSUPERVISOR(SVC_mainClockInterrupt);
}

void getSystemClockValue(void){
    return ROM_TimerValueGet(WTIMER0_BASE, TIMER_A);
}
