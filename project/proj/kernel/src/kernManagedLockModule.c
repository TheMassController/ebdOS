#include <errno.h>                  // Contains the macro's for the E* variables
#include <hw_types.h>               // Common types and macros for the TI libs
#include <timer.h>                  // Function prototypes for the timer module
#include <hw_memmap.h>              // Address of GPIO etc

#include "sysManagedLock.h"         // Declarations of functions defined here
#include "kernelPredefined.h"       // Contains the amount of managed locks that need to be allocated
#include "process.h"                // Contains the defenition of a proces
#include "systemClockManagement.h"  // Declares setHalfWTimerInterrupt
#include "abstrSysSleepFuncs.h"     // Declares translateSleepRequest

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
    if (proc->sleepObj.overflows == 0 && proc->sleepObj.sleepUntil >= curValWTA) return 0;
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
    return 1;
}

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
// Returns -1 if not found, 0 if found
static int removeFromLockList(struct ManagedLock* lock, struct Process* proc){
    struct Process* it = lock->waitinglist;
    for (;it->nextProcess != NULL && it != proc;it = it->nextProcess);
    if (it == proc){
        lock->waitinglist = it->nextProcess;
        it->nextProcess = NULL;
        it->state = STATE_READY;
        return 0;
    }
    return -1;
}

static struct Process* popFromLockList(struct ManagedLock* lock){
    struct Process* proc = lock->waitinglist;
    if (proc != NULL){
        lock->waitinglist = proc->nextProcess;
        proc->nextProcess = NULL;
        proc->state = STATE_READY;
    }
    return proc;
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
    return 0;
}

int releaseManagedLock(size_t lockId, struct Process** procReady){
    if (lockId >= MANAGEDLOCKCOUNT || !lockPool[lockId].taken) return EINVAL;
    *procReady = popFromLockList(&lockPool[lockId]);
    return 0;
}

int timedWaitForManagedLock(size_t lockId, struct Process* proc, struct SleepRequest* slpReq){
    if (lockId >= MANAGEDLOCKCOUNT || !lockPool[lockId].taken) return EINVAL;
    translateSleepRequest(proc, slpReq);
    addToLockList(&lockPool[lockId], proc);
    if (!addLockWaiter(proc, lockId)) return ETIMEDOUT;
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
        removeFromLockList(&lockPool[it->managedLockID], in);
        it = it->nextElement;
        while (it != NULL && it->proc->sleepObj.overflows == 0 && it->proc->sleepObj.sleepUntil >= curValWTA){
            in->nextProcess = it->proc;
            in = in->nextProcess;
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
        in = ret;
        removeFromLockList(&lockPool[it->managedLockID], in);
        it = it->nextElement;
        while (it != NULL && it->proc->sleepObj.overflows == 0){
            in->nextProcess = it->proc;
            in = in->nextProcess;
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

