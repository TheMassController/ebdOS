#include "mainClockManagement.h"
#include "supervisorCall.h"

void systemTimerInterrupt(void){
    // ITS HAPPENING
    // Inform the supervisor
    CALLSUSUPERVISOR(SVC_mainClockInterrupt);
    // reset the system clock
}
