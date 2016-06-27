#include <stdint.h>                     // uint64_t

#include "process.h"                    // Contains information about the struct Process
#include "core/inc/sleep.h"                      // Contains information about the struct SleepRequest
#include "abstrSysSleepFuncs.h"         // Contains the signatures for the functions defined here
#include "systemClockManagement.h"      // Contains the function getCurrentSytemTimerValue and the constant EBD_SYSCLOCKMAXVAL

void translateSleepRequest(struct Process* proc, const struct SleepRequest* sleepRequest){
    struct SleepingProcessStruct* sleepStruct = &(proc->sleepObj);
    /* The systemClock runs from max to min. So if we want to sleep for x time, we want to wait until reftime - x
     * First of all: we need the total amount of us we are going to sleep. This is the delta.
     * */
    uint64_t sleepDelta = sleepRequest->uSec + sleepRequest->mSec * 1000 + sleepRequest->sec * 1000000;
    /* So now we need to find the overflow count.
     * We basically remove the max count of the sysclock from the wakeupMoment and add 1 to the overflow until wakeupMoment <= sleepRequest->reftime
     */
    sleepStruct->overflows = 0;
    if (sleepDelta <= sleepRequest->refTime){
        sleepStruct->sleepUntil = sleepRequest->refTime - sleepDelta;
    } else {
        sleepDelta -= sleepRequest->refTime;
        sleepStruct->overflows = 1;
        while ( sleepDelta >= EBD_SYSCLOCKMAXVAL ){
            sleepDelta -= EBD_SYSCLOCKMAXVAL;
            sleepStruct->overflows++;
        }
        sleepStruct->sleepUntil = EBD_SYSCLOCKMAXVAL- sleepDelta;
    }
    // compensate for a possibly missed interrupt
    unsigned curValWTA = getSystemClockValue();
    if (curValWTA > sleepRequest->refTime){
        if (sleepStruct->overflows > 0){
            sleepStruct->overflows--;
        } else {
            sleepStruct->sleepUntil = curValWTA;
        }
    }
}
