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

struct SleepQueueElement {
    struct SleepQueueElement* nextElement;
    struct Process* proc;
    size_t managedLockID;
};

static struct ManagedLock lockPool[MANAGEDLOCKCOUNT];
static struct SleepQueueElement sleepQueuePool[MAXTOTALPROCESSES];
static struct SleepQueueElement* sleepQueueHead = NULL;

static void updateWaitTimer(unsigned curValWTA){
    if (sleepQueueHead == NULL || sleepQueueHead->proc->sleepObj.overflows > 0){
        setHalfWTimerInterrupt(0, WTIMER1_BASE, TIMER_A, 0, 0);
    } else if (sleepQueueHead->proc->sleepObj.overflows == 0 && sleepQueueHead->proc->sleepObj.sleepUntil >= curValWTA){
        return; // Let the timer interrupt handle this case, it will just shoot an event into the kernel that will fix the rest
    } else {
        setHalfWTimerInterrupt(1, WTIMER1_BASE, TIMER_A, curValWTA, sleepQueueHead->proc->sleepObj.sleepUntil);
    }
}

static int addLockWaiter(struct Process* proc, size_t managedLockId){
    unsigned curValWTA = getSystemClockValue();
    if (proc->sleepObj.overflows == 0 && proc->sleepObj.sleepUntil >= curValWTA) return ETIMEDOUT;
    struct SleepQueueElement* el = &sleepQueuePool[proc->pid];
    el->proc = proc;
    el->managedLockID = managedLockId;
    if (sleepQueueHead == NULL) {
        sleepQueueHead = el;
        el->nextElement = NULL;
        updateWaitTimer(curValWTA);
    } else {
        unsigned curOverflow = proc->sleepObj.overflows;
        unsigned curWaitUntil = proc->sleepObj.sleepUntil;
        struct SleepQueueElement* it = sleepQueueHead;
        unsigned itOverflow = it->proc->sleepObj.overflows;
        unsigned itWaitUntil = it->proc->sleepObj.sleepUntil;
        if (itOverflow > curOverflow || (itOverflow == curOverflow && curWaitUntil > itWaitUntil)){
            // Replaces the head
            el->nextElement = it;
            sleepQueueHead = el;
            updateWaitTimer(curValWTA);
        } else {
            // Head will not be replaced, find the place
            while (itOverflow < curOverflow && it->nextElement != NULL){
                it = it->nextElement;
                itOverflow = it->proc->sleepObj.overflows;
                itWaitUntil = it->proc->sleepObj.sleepUntil;
            }
            while (itWaitUntil > curWaitUntil && it->nextElement != NULL){
                it = it->nextElement;
                itOverflow = it->proc->sleepObj.overflows;
                itWaitUntil = it->proc->sleepObj.sleepUntil;
            }
            el->nextElement = it->nextElement;
            it->nextElement = el;
        }
    }
    return 0;
}

static void removeLockWaiter(struct Process* proc){
#ifdef DEBUG
    if (sleepQueueHead == NULL){
        UARTprintf("Race condition, file %s, file %s, line %d (function: %s).\n", __FILE__, __LINE__, __func__);
        generateCrash();
    }
#endif //DEBUG
    if (sleepQueueHead == NULL) return;
    struct SleepQueueElement* el = &sleepQueuePool[proc->pid];
    if (sleepQueueHead == el){
        sleepQueueHead = el->nextElement;
        el->nextElement = NULL;
    } else {
        struct SleepQueueElement* prev = sleepQueueHead;
        struct SleepQueueElement* cur = sleepQueueHead->nextElement;
        while(cur != NULL && cur != el) {
            prev = cur;
            cur = cur->nextElement;
        }
#ifdef DEBUG
        if (cur == NULL){
            UARTprintf("Race condition, file %s, file %s, line %d (function: %s).\n", __FILE__, __LINE__, __func__);
            generateCrash();
        }
#endif //DEBUG
        if (cur == NULL) return;
        prev->nextElement = cur->nextElement;
        cur->nextElement = NULL;
    }
}
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

struct Process* timedManagedLockTimeout(void){
    if (sleepQueueHead == NULL) {
        updateWaitTimer(getSystemClockValue());
        return NULL;
    }
    struct Process* ret = NULL;
    struct Process* in = NULL;
    unsigned curValWTA = getSystemClockValue();
    struct SleepQueueElement* it = sleepQueueHead;
    if (it->proc->sleepObj.overflows == 0 && it->proc->sleepObj.sleepUntil >= curValWTA){
        ret = it->proc;
        in = ret;
        in->state = STATE_READY;
        removeFromLockList(&lockPool[it->managedLockID], in);
        it = it->nextElement;
        while (it != NULL && it->proc->sleepObj.overflows == 0 && it->proc->sleepObj.sleepUntil >= curValWTA){
            in->nextProcess = it->proc;
            in = in->nextProcess;
            in->state = STATE_READY;
            removeFromLockList(&lockPool[it->managedLockID], in);
            it = it->nextElement;
        }
    }
    sleepQueueHead = it;
    updateWaitTimer(curValWTA);
    return ret;
}

struct Process* timedManagedLockSysTimerOverflow(void){
    if (sleepQueueHead == NULL) {
        updateWaitTimer(getSystemClockValue());
        return NULL;
    }
    struct Process* ret = NULL;
    struct Process* in = NULL;
    struct SleepQueueElement* it = sleepQueueHead;
    if (it->proc->sleepObj.overflows == 0){
        ret = it->proc;
        ret->state = STATE_READY;
        in = ret;
        removeFromLockList(&lockPool[it->managedLockID], in);
        it = it->nextElement;
        while (it != NULL && it->proc->sleepObj.overflows == 0){
            in->nextProcess = it->proc;
            in = in->nextProcess;
            in->state = STATE_READY;
            removeFromLockList(&lockPool[it->managedLockID], in);
            it = it->nextElement;
        }
    }
    while (it != NULL){
        it->proc->sleepObj.overflows -= 1;
        it = it->nextElement;
    }
    if (ret != NULL){
        in->nextProcess = timedManagedLockTimeout();
    } else {
        ret = timedManagedLockTimeout();
    }
    return ret;
}

