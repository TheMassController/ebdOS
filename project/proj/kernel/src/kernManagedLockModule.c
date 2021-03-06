#include <errno.h>                  // Contains the macro's for the E* variables
#include <hw_types.h>               // Common types and macros for the TI libs
#include <timer.h>                  // Function prototypes for the timer module
#include <hw_memmap.h>              // Address of GPIO etc

#include "sysManagedLock.h"         // Declarations of functions defined here
#include "kernelPredefined.h"       // Contains the amount of managed locks that need to be allocated
#include "process.h"                // Contains the defenition of a proces
#include "systemClockManagement.h"  // Declares setHalfWTimerInterrupt
#include "abstrSysSleepFuncs.h"     // Declares translateSleepRequest
#include "waitModule.h"             // Contains the timeout function set
#include "kernMaintenanceQueue.h"   // releaseProcessToScheduler function

#ifdef DEBUG
#include "uartstdio.h"
#include "kernUtils.h"
#endif //DEBUG

struct ManagedLock {
    uintptr_t ownerPid;
    char taken;
    struct Process* waitinglist;
};

static struct ManagedLock lockPool[MANAGEDLOCKCOUNT];
static int waitModuleTranslationMap[MAXTOTALPROCESSES];

static void addToLockList(struct ManagedLock* lock, struct Process* proc){
    proc->nextProcess = NULL;
    proc->state = STATE_WAIT;
    if (lock->waitinglist == NULL){
        lock->waitinglist = proc;
    } else {
        struct Process* it = lock->waitinglist;
        while(it->nextProcess != NULL) it = it->nextProcess;
        it->nextProcess = proc;
    }
}

static void removeFromLockList(struct ManagedLock* lock, struct Process* proc){
#ifdef DEBUG
    int found = 0;
#endif //DEBUG
    struct Process* it = lock->waitinglist;
    if (it == proc) {
        lock->waitinglist = it->nextProcess;
        it->nextProcess = NULL;
#ifdef DEBUG
        found = 1;
#endif //DEBUG
    } else {
        struct Process* prev = it;
        it = it->nextProcess;
        while(it != NULL && it != proc){
            prev = it;
            it = it->nextProcess;
        }
        if (it != NULL){
#ifdef DEBUG
            found = 1;
#endif //DEBUG
            prev->nextProcess = it->nextProcess;
            it->nextProcess = NULL;
        }
    }
    if (waitModuleTranslationMap[proc->pid] != -1) removeWaiter(proc);
    proc->state = STATE_READY;
#ifdef DEBUG
    if (!found){
        UARTprintf("Race condition, file %s, file %s, line %d (function: %s).\n", __FILE__, __LINE__, __func__);
        generateCrash();
    }
#endif //DEBUG
}

static struct Process* popFromLockList(struct ManagedLock* lock){
    struct Process* proc = lock->waitinglist;
    if (proc != NULL){
        lock->waitinglist = proc->nextProcess;
        proc->nextProcess = NULL;
        if (waitModuleTranslationMap[proc->pid] != -1) removeWaiter(proc);
        proc->state = STATE_READY;
    }
    return proc;
}

static void removeWaiterCallback(struct Process* proc){
    size_t lockId = waitModuleTranslationMap[proc->pid];
    waitModuleTranslationMap[proc->pid] = -1;
    removeFromLockList(&lockPool[lockId], proc);
    releaseProcessToScheduler(proc, ETIMEDOUT);
}


int allocateManagedLock(size_t* lockId, uintptr_t owner){
    size_t i = 0;
    for ( ; i < MANAGEDLOCKCOUNT && lockPool[i].taken; ++i);
    if (i < MANAGEDLOCKCOUNT){
        *lockId = i;
        lockPool[i].taken = 1;
        lockPool[i].ownerPid = owner;
        return 0;
    }
    return ENOLCK;
}

int freeManagedLock(size_t lockId){
    if (lockId >= MANAGEDLOCKCOUNT || !lockPool[lockId].taken) return EINVAL;
    if (lockPool[lockId].waitinglist != NULL) return EDEADLK;
    lockPool[lockId].taken = 0;
    return 0;
}

int waitForManagedLock(size_t lockId, struct Process* proc){
    if (lockId >= MANAGEDLOCKCOUNT || !lockPool[lockId].taken) return EINVAL;
    addToLockList(&lockPool[lockId], proc);
    waitModuleTranslationMap[proc->pid] = -1;
    return 0;
}

int releaseManagedLock(size_t lockId, struct Process** procReady){
    if (lockId >= MANAGEDLOCKCOUNT || !lockPool[lockId].taken) return EINVAL;
    *procReady = popFromLockList(&lockPool[lockId]);
    return 0;
}

int timedWaitForManagedLock(size_t lockId, struct Process* proc, struct SleepRequest* slpReq){
    if (lockId >= MANAGEDLOCKCOUNT || !lockPool[lockId].taken) return EINVAL;
    if (addWaiter(removeWaiterCallback, proc, slpReq) == ETIMEDOUT){
        proc->state = STATE_READY;
        return ETIMEDOUT;
    }
    waitModuleTranslationMap[proc->pid] = lockId;
    addToLockList(&lockPool[lockId], proc);
    proc->state = STATE_WAIT_TIMEOUT;
    return 0;
}
