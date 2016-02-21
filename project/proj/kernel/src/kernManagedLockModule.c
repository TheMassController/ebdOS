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

static void removeFromLockList(struct ManagedLock* lock, struct Process* proc){
    struct Process* it = lock->waitinglist;
    for (;it->nextProcess != NULL && it != proc;it = it->nextProcess);
    if (it == proc){
        lock->waitinglist = it->nextProcess;
        it->nextProcess = NULL;
    }
}

int allocateManagedLock(size_t* lockId, uintptr_t owner){
    size_t iterator;
    for (iterator = 0; iterator < MANAGEDLOCKCOUNT && lockPool[iterator].taken; ++iterator);
    if (iterator < MANAGEDLOCKCOUNT){
        *lockId = iterator;
        lockPool[iterator].taken = 1;
        lockPool[iterator].ownerPid = owner;
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

int releaseManagedLock(size_t lockId, struct Process* procReady){
    if (lockId >= MANAGEDLOCKCOUNT || !lockPool[lockId].taken) return EINVAL;
    removeFromLockList(&lockPool[lockId], procReady);
    return 0;
}
