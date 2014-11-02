//The actual mutex functions
#include "mutex.h"
#include "stdlib.h"
#include "process.h"
#include "supervisorCall.h"
#include "sleep.h"

Mutex* firstMutex = NULL;
extern struct Process* currentProcess;

unsigned __lockMutex(void* addr);
void __unlockMutex(void* addr);

Mutex* createMutex(void){
    Mutex* mutex = (Mutex*)malloc(sizeof(Mutex));
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
    while (!__lockMutex(mutex)){
        currentProcess->blockAddress = (void*)mutex;
        currentProcess->state |= STATE_WAIT;
        CALLSUPERVISOR(SVC_reschedule);
    }
    //TODO maybe implement a way to increase the priority of the process that holds this mutex, if the prio of the current process is higher
}

int lockMutexNoBlock(Mutex* mutex){
    if (__alreadyOwnsMutex(mutex)) return 1;
    return __lockMutex(mutex);
}

int lockMutexBlockWait(Mutex* mutex, unsigned msWaitTime){
    if (!lockMutexNoBlock(mutex)){
        currentProcess->blockAddress = (void*)mutex;
        currentProcess->state |= STATE_WAIT;
        sleepMS(msWaitTime);
    }
    return lockMutexNoBlock(mutex);
}

