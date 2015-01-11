//The actual mutex functions
#include "mutex.h"
#include "stdlib.h"
#include "process.h"
#include "threadsafeCalls.h" 

extern struct Process* currentProcess;

struct Mutex* createMutex(void){
    struct Mutex* mutex = (struct Mutex*)malloc(sizeof(struct Mutex));
    if (mutex == NULL) return NULL;
    __initSingleLockObject(&(mutex->singleLockObject));
    mutex->ownerPid = 0;
    return mutex;
}

int __alreadyOwnsMutex(struct Mutex* mutex){
    //TODO act like it is already owned by given process when inside interrupt
    if (mutex->ownerPid == currentProcess->pid && __singleLockObjectIsLocked(&(mutex->singleLockObject))){
        return 1;
    }
    return 0;
}

void deleteMutex(struct Mutex* mutex){
    __cleanupSingleLockObject(&(mutex->singleLockObject));
    free(mutex);
}

void lockMutex(struct Mutex* mutex){
    if (__alreadyOwnsMutex(mutex)) return;
    __lockObjectBlock(&(mutex->singleLockObject));
    mutex->ownerPid = currentProcess->pid;
}

int lockMutexNoBlock(struct Mutex* mutex){
    if (__alreadyOwnsMutex(mutex)) return 1;
    int retCode = __lockObjectNoblock(&(mutex->singleLockObject));
    if (retCode){
        mutex->ownerPid = currentProcess->pid;
    }
    return retCode;
}

int lockMutexBlockWait(struct Mutex* mutex, unsigned msWaitTime){
    if (__alreadyOwnsMutex(mutex)) return 1;
    int retCode = __lockObjectBlockTimeout(&(mutex->singleLockObject), msWaitTime);
    if (retCode){
        mutex->ownerPid = currentProcess->pid;
    }
    return retCode;
}

void releaseMutex(struct Mutex* mutex){
    //TODO do not release when inside an interrupt
    if (!__alreadyOwnsMutex(mutex)) return;
    __releaseObject(&(mutex->singleLockObject));
    mutex->ownerPid = 0;
}

