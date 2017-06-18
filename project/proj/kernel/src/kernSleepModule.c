#include <stdlib.h>                     // NULL

#include "process.h"                    // Declares struct Process
#include "kernMaintenanceQueue.h"       // Declares releaseProcessToScheduler
#include "core/inc/sleep.h"             // Declares struct SleepRequest
#include "waitModule.h"                 // Basically what this thing wraps around

static void waitRemoveCallBack(struct Process* proc){
    releaseProcessToScheduler(proc, 0);
}

void addSleeper(struct Process* proc, const struct SleepRequest* sleepRequest){
    int retval = addWaiter(waitRemoveCallBack, proc, sleepRequest);
    if (retval != 0) waitRemoveCallBack(proc);
}

int removeSleeper(struct Process* proc){
    return removeWaiter(proc);
}

struct Process* refreshSleeplist(void){
    return NULL;
}

struct Process* sleepHandleSysTimerOverflow(void){
    return NULL;
}
