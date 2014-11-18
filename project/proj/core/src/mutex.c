//The actual mutex functions
#include "mutex.h"
#include "stdlib.h"
#include "process.h"
#include "threadsafeCalls.h" 

Mutex* firstMutex = NULL;
extern struct Process* currentProcess;

Mutex* createMutex(void){
    Mutex* mutex = (Mutex*)malloc(sizeof(Mutex));
    if (mutex == NULL) return NULL;
    mutex->singleLockObject = __createSingleLockObject();
    mutex->ownerPid = 0;
    if (firstMutex == NULL){
        firstMutex = mutex;
    } else {
        Mutex* mut;
        for(mut = firstMutex; mut->nextMutex == NULL; mut = mut->nextMutex);
        mut->nextMutex = mutex;
    }
    return mutex;
}

int __alreadyOwnsMutex(Mutex* mutex){
    //TODO act like it is already owned by given process when inside interrupt
    if (mutex->ownerPid == currentProcess->pid && __singleLockObjectIsLocked(mutex->singleLockObject)){
        return 1;
    }
    return 0;
}

void deleteMutex(Mutex* mutex){
    __deleteSingleLockObject(mutex->singleLockObject);
    free(mutex);
}

void lockMutex(Mutex* mutex){
    if (__alreadyOwnsMutex(mutex)) return;
    __lockObjectBlock(mutex->singleLockObject);
    mutex->ownerPid = currentProcess->pid;
}

int lockMutexNoBlock(Mutex* mutex){
    if (__alreadyOwnsMutex(mutex)) return 1;
    int retCode = __lockObjectNoblock(mutex->singleLockObject);
    if (retCode){
        mutex->ownerPid = currentProcess->pid;
    }
    return retCode;
}

int lockMutexBlockWait(Mutex* mutex, unsigned msWaitTime){
    if (__alreadyOwnsMutex(mutex)) return 1;
    int retCode = __lockObjectBlockTimeout(mutex->singleLockObject, msWaitTime);
    if (retCode){
        mutex->ownerPid = currentProcess->pid;
    }
    return retCode;
}

void releaseMutex(Mutex* mutex){
    //TODO do not release when inside an interrupt
    if (!__alreadyOwnsMutex(mutex)) return;
    __releaseObject(mutex->singleLockObject);
    mutex->ownerPid = 0;
}

