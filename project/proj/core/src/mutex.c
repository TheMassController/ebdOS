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
    mutex->lock = 0;
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
    if (mutex->ownerPid == currentProcess->pid && mutex->lock){
        return 1;
    }
    return 0;
}

void deleteMutex(Mutex* mutex){
    //TODO call kernel to delete this mutex. If a resource was still waiting for it, kernel panic or some shit.
}

void lockMutex(Mutex* mutex){
    if (__alreadyOwnsMutex(mutex)) return;
    __lockObjectBlock((void*) mutex);
}

int lockMutexNoBlock(Mutex* mutex){
    if (__alreadyOwnsMutex(mutex)) return 1;
    return __lockObjectNoblock((void*)mutex);
}

int lockMutexBlockWait(Mutex* mutex, unsigned msWaitTime){
    if (__alreadyOwnsMutex(mutex)) return 1;
    return __lockObjectBlockTimeout((void*)mutex, msWaitTime);
}

void releaseMutex(Mutex* mutex){
    //TODO do not release when inside an interrupt
    if (!__alreadyOwnsMutex(mutex)) return;
    __releaseObject((void*)mutex);
}

