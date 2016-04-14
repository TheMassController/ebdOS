#include "sysManagedLock.h"     // Declarations of functions defined here
#include "kernelPredefined.h"   // Contains the amount of managed locks that need to be allocated
#include "process.h"            // Contains the defenition of a proces

#include <errno.h>              // Contains the macro's for the E* variables

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
//static struct SleepQueueElement sleepQueuePool[MAXTOTALPROCESSES];

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
        return 0;
    }
    return -1;
}

static struct Process* popFromLockList(struct ManagedLock* lock){
    struct Process* proc = lock->waitinglist;
    if (proc != NULL){
        lock->waitinglist = proc->nextProcess;
        proc->nextProcess = NULL;
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

int removeProcessFromManagedLock(size_t lockId, struct Process* proc){
    if (lockId >= MANAGEDLOCKCOUNT || !lockPool[lockId].taken) return EINVAL;
    if (removeFromLockList(&lockPool[lockId], proc) == -1) return EAGAIN;
    return 0;
}
