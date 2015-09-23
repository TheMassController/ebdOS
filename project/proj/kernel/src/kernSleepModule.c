#include <stdint.h>                     // uint64_t
#include <stdlib.h>                     // NULL

#include "supervisorCall.h"             // Contains the macro's necessary for making a supervisor call
#include "process.h"                    // Contains information about the struct Process
#include "sleep.h"                      // Contains information about the struct SleepRequest
#include "systemClockManagement.h"      // Contains information and functions about the main clock
#include "coreUtils.h"                  // For testing if inside SVC interrupt
#include "spinlock.h"                   // For the spinlock
#ifdef DEBUG
#include <uartstdio.h>
#include "kernUtils.h"                  // Generate crash
#endif //DEBUG

static struct Process* sleepList = NULL;
static struct Spinlock spinlock;
static volatile char intrTried;

static void generateSleepInterrupt(void){
    //TODO
}

static struct Process* internalAddSleeper(struct Process* proc){
    struct SleepingProcessStruct* sleepStruct = &(proc->sleepObj);
    if (sleepStruct->overflows == 0 && sleepStruct->sleepUntil <= getSystemclockValue()) return proc;
#ifdef DEBUG
    if (!tryLockSpinlock(&spinlock)){
        UARTprintf("internalAddSleeper: getting the spinlock failed!\n");
        generateCrash();
    }
#else
    while(!tryLockSpinlock(&spinlock));
#endif //DEBUG

    unlockSpinlock(&spinlock);
:x
    return NULL;
}

struct Process* addSleeper(struct Process* proc, struct SleepRequest* sleepRequest){
    //Usually called from kernel
    struct SleepingProcessStruct* sleepStruct = &(proc->sleepObj);
    sleepStruct->nextPtr = NULL;
    uint64_t wakeupMoment = sleepRequest->uSec + sleepRequest->mSec * 1000 + sleepRequest->sec * 1000000 + sleepRequest->refTime;
    sleepStruct->overflows = wakeupMoment / EBD_SYSCLOCKMAXVAL;
    sleepStruct->sleepUntil = wakeupMoment % EBD_SYSCLOCKMAXVAL;
    return internalAddSleeper(proc);
}
