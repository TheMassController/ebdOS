#include "threadsafeCalls.h" 
#include "process.h"
#include "supervisorCall.h"
#include "sleep.h"
#include "stdlib.h" 

extern struct Process* currentProcess;

//Returns 1 if successful
unsigned __lockMutex(SingleLockObject* addr);
void __unlockMutex(SingleLockObject* addr);

SingleLockObject* __createSingleLockObject(void){
    SingleLockObject* object = (SingleLockObject*)malloc(sizeof(SingleLockObject));
    object->lock = 0;
    object->processWaitingQueue = NULL;
    return object;
}

void __deleteSingleLockObject(SingleLockObject* object){
    //TODO notify kernel that a singleLockObject will be cleaned up
    free(object);
}

int __lockObjectNoblock(SingleLockObject* object){
    return __lockMutex(object);
}

void __lockObjectBlock(SingleLockObject* object){
   while(!__lockMutex(object)){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        //TODO different interrupt
        CALLSUPERVISOR(SVC_objectLock);
    } 
     //TODO maybe implement a way to increase the priority of the process that holds this mutex, if the prio of the current process is higher
}

int __lockObjectBlockTimeout(SingleLockObject* object, unsigned timeout){
     if (!__lockObjectNoblock(object)){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        //TODO: find solution
        sleepMS(timeout);
    }
    return __lockObjectNoblock(object);
}

void __releaseObject(SingleLockObject* object){
    __unlockMutex(object);
    currentProcess->blockAddress = object;
    CALLSUPERVISOR(SVC_objectRelease);
}

int __singleLockObjectIsLocked(SingleLockObject* object){
    return object->lock;
}
