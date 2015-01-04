#include "threadsafeCalls.h" 
#include "process.h"
#include "supervisorCall.h"
#include "sleep.h"
#include "stdlib.h" 

extern struct Process* currentProcess;

//Returns 1 if successful, 0 otherwise
unsigned __lockSingleLockObject(SingleLockObject* addr);
void __unlockSingleLockObject(SingleLockObject* addr);

SingleLockObject* __createSingleLockObject(void){
    SingleLockObject* object = (SingleLockObject*)malloc(sizeof(SingleLockObject));
    object->lock = 0;
    object->processWaitingQueue = NULL;
    return object;
}

void __deleteSingleLockObject(SingleLockObject* object){
    //TODO notify supervisor that a singleLockObject will be cleaned up
    free(object);
}

int __lockObjectNoblock(SingleLockObject* object){
    return __lockSingleLockObject(object);
}

void __lockObjectBlock(SingleLockObject* object){
   while(!__lockSingleLockObject(object)){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_LOCKED;
        CALLSUPERVISOR(SVC_objectLock);
    } 
     //TODO maybe implement a way to increase the priority of the process that holds this mutex, if the prio of the current process is higher
}

int __lockObjectBlockTimeout(SingleLockObject* object, unsigned msTimeout){
     if (!__lockObjectNoblock(object)){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_LOCKED;
        __sleepMSDelayBlock(msTimeout);
        CALLSUPERVISOR(SVC_objectLock);
        __sleepDelayBlockWakeup();
    }
    return __lockObjectNoblock(object);
}

void __releaseObject(SingleLockObject* object){
    __unlockSingleLockObject(object);
    currentProcess->blockAddress = object;
    CALLSUPERVISOR(SVC_objectRelease);
}

int __singleLockObjectIsLocked(SingleLockObject* object){
    return object->lock;
}
