#include <stdint.h>                     // uint64_t
#include <stdlib.h>                     // NULL
#include <string.h>                     // strerror

#include "supervisorCall.h"             // Contains the macro's necessary for making a supervisor call
#include "process.h"                    // Contains information about the struct Process
#include "sleep.h"                      // Contains information about the struct SleepRequest
#include "systemClockManagement.h"      // Contains information and functions about the main clock
#include "coreUtils.h"                  // For testing if inside SVC interrupt
#include "spinlock.h"                   // For the spinlock
#ifdef DEBUG
#include <uartstdio.h>                  // Printfs etc.
#include "kernUtils.h"                  // Generate crash
#endif //DEBUG

static struct Process* sleepList = NULL;

static struct Process* internalAddSleeper(struct Process* proc){
    struct SleepingProcessStruct* sleepStruct = &(proc->sleepObj);
    if (sleepStruct->overflows == 0 && sleepStruct->sleepUntil <= getSystemclockValue()){
        return proc;
    }
    // Sort the process into the sleeplist
    if (sleepList == NULL){
        sleepList = proc;
        proc->nextProcess = NULL;
    } else {
        // The item needs to go in between prev and cur
        struct Process* prevNode = NULL;
        struct Process* curNode = sleepList;
        // First part of search: sort into the correct amount of overflows
         for (; curNode != NULL; curNode = curNode->nextProcess){
             if ((curNode->sleepObj).overflows >= (proc->sleepObj).overflows){
                 break;
             }
            prevNode = curNode;
         }
         // Then sort into the correct wakeup moment. Higher goes first
         for (; curNode != NULL; curNode = curNode->nextProcess){
             if ((curNode->sleepObj).sleepUntil < (proc->sleepObj).sleepUntil){
                 break;
             }
             prevNode = curNode;
         }
         if (prevNode == NULL){
             sleepList = proc;
             proc->nextProcess = curNode;
         } else {
             prevNode->nextProcess = proc;
             proc->nextProcess = curNode;
         }
    }
    return NULL;
}

struct Process* addSleeper(struct Process* proc, struct SleepRequest* sleepRequest){
    //Usually called from kernel
    struct SleepingProcessStruct* sleepStruct = &(proc->sleepObj);
    sleepStruct->nextPtr = NULL;
    /* The systemClock runs from max to min. So if we want to sleep for x time, we want to wait until reftime - x
     * First of all: we need the total amount of us we are going to sleep. */
    uint64_t wakeupMoment = sleepRequest->uSec + sleepRequest->mSec * 1000 + sleepRequest->sec * 1000000;
    /* So now we need to find the overflow count. We basically remove the max count of the sysclock from the wakeupMoment and add 1 to the overflow until wakeupMoment <= sleepRequest->reftime
     */
    sleepStruct->overflows = 0;
    for(; wakeupMoment > sleepRequest->refTime; wakeupMoment -= EBD_SYSCLOCKMAXVAL) {
        sleepStruct->overflows += 1;
    }
    sleepStruct->sleepUntil = sleepRequest->refTime - wakeupMoment;
    // This function does the actual addition.
    return internalAddSleeper(proc);
}
