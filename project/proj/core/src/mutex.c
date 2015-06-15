//The actual mutex functions
#include "mutex.h"
#include "stdlib.h"
#include "process.h"
#include "lockObject.h"
#include "coreUtils.h"

extern struct Process* currentProcess;

void initMutex(struct Mutex* mutex){
    __initLockObject(&(mutex->lockObject), 1);
    mutex->ownerPid = 0;
}

void cleanupMutex(struct Mutex* mutex){
    __cleanupLockObject(&(mutex->lockObject));
}

int ownsMutex(struct Mutex* mutex){
    return (mutex->ownerPid == currentProcess->pid || isInInterrupt());
}

void lockMutexBlocking(struct Mutex* mutex){
    if (ownsMutex(mutex)) return;
    __increaseLockObjectBlock(&(mutex->lockObject));
    mutex->ownerPid = currentProcess->pid;
}

int lockMutexNoBlock(struct Mutex* mutex){
    if (ownsMutex(mutex)) return 0;
    int retCode = __increaseLockObjectNoBlock(&(mutex->lockObject));
    if (retCode != -1){
        mutex->ownerPid = currentProcess->pid;
        return 1;
    } else {
        return 0;
    }
}

int lockMutexBlockWait(struct Mutex* mutex, unsigned msWaitTime){
    if (ownsMutex(mutex)) return 0; //Return false immedeatly
    int retCode = __increaseLockObjectBlockTimeout(&(mutex->lockObject), msWaitTime);
    if (retCode != -1){
        mutex->ownerPid = currentProcess->pid;
        return 1;
    } else {
        return 0;
    }
}

void releaseMutex(struct Mutex* mutex){
    if (!ownsMutex(mutex) || isInInterrupt()) return;
    __decreaseLockObjectNoBlock(&(mutex->lockObject));
    mutex->ownerPid = 0;
}

int takeMutex(struct Mutex* mutex, unsigned msTimeOut){
    if (msTimeOut == MAXWAITTIME){
        lockMutexBlocking(mutex);
        return 1;
    } else if (msTimeOut == 0){
        return lockMutexNoBlock(mutex);
    } else {
        return lockMutexBlockWait(mutex, msTimeOut);
    }
}
