//The actual mutex functions
#include "mutex.h"
#include "stdlib.h"
#include "process.h"
#include "threadsafeCalls.h" 
#include "asmUtils.h"

extern struct Process* currentProcess;

void initMutex(struct Mutex* mutex){
    __initSingleLockObject(&(mutex->singleLockObject));
    mutex->ownerPid = 0;
}

void cleanupMutex(struct Mutex* mutex){
    __cleanupSingleLockObject(&(mutex->singleLockObject));
}

int ownsMutex(struct Mutex* mutex){
    //TODO act like it is already owned by given process when inside interrupt
    if ((mutex->ownerPid == currentProcess->pid && __singleLockObjectIsLocked(&(mutex->singleLockObject))) || isInInterrupt()){
        return 1;
    }
    return 0;
}

void lockMutexBlocking(struct Mutex* mutex){
    if (ownsMutex(mutex)){
        return;
    }
    __lockObjectBlock(&(mutex->singleLockObject));
    mutex->ownerPid = currentProcess->pid;
}

int lockMutexNoBlock(struct Mutex* mutex){
    if (ownsMutex(mutex)) return 0; //Return false immedeatly
    int retCode = __lockObjectNoblock(&(mutex->singleLockObject));
    if (retCode){
        mutex->ownerPid = currentProcess->pid;
    }
    return retCode;
}

int lockMutexBlockWait(struct Mutex* mutex, unsigned msWaitTime){
    if (ownsMutex(mutex)) return 0; //Return false immedeatly
    int retCode = __lockObjectBlockTimeout(&(mutex->singleLockObject), msWaitTime);
    if (retCode){
        mutex->ownerPid = currentProcess->pid;
    }
    return retCode;
}

void releaseMutex(struct Mutex* mutex){
    if (!ownsMutex(mutex) || isInInterrupt()) return;
    __releaseObject(&(mutex->singleLockObject));
    mutex->ownerPid = 0;
}
