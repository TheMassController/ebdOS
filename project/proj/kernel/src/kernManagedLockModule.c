#include "sysManagedLock.h"     // Declarations of functions defined here
#include "kernelPredefined.h"   // Contains the amount of managed locks that need to be allocated
#include "process.h"            // Contains the defenition of a proces

#include <errno.h>              // Contains the macro's for the E* variables

struct ManagedLock {
    uintptr_t ownerPid;
    char taken;
    struct Process* waitinglist;
};

static struct ManagedLock lockPool[MANAGEDLOCKCOUNT];


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
