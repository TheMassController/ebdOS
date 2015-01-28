#include "threadsafeCalls.h" 
#include "process.h"
#include "supervisorCall.h"
#include "sleep.h"
#include "stdlib.h" 

extern struct Process* currentProcess;

//Returns 1 if successful, 0 otherwise
unsigned __lockSingleLockObject(SingleLockObject* addr);
void __unlockSingleLockObject(SingleLockObject* addr);

void __initSingleLockObject(SingleLockObject* object){
    object->lock = 0;
    object->processWaitingQueue = NULL;
}
void __cleanupSingleLockObject(SingleLockObject* object){
    if (object->lock != 0 || object->processWaitingQueue != NULL){
        //TODO raise hell (kernel panic?)
    }
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
    int retCode = __lockObjectNoblock(object);
     if (!retCode){
        currentProcess->state |= STATE_LOCKED;
        __sleepMSDelayBlock(msTimeout);
        currentProcess->blockAddress = object;
        CALLSUPERVISOR(SVC_lockAndSleep);
        __sleepDelayBlockWakeup();
    } else {
        return retCode;
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
