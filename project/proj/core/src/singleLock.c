#include "threadsafeCalls.h" 
#include "process.h"
#include "supervisorCall.h"
#include "sleep.h"
#include "stdlib.h" 
#include "asmUtils.h"

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
        currentProcess->state |= STATE_LOCKED;
        currentProcess->blockAddress = object;
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

//Th purpose of this function is to become "interrupt-safe"
/**
    Interrupt introduces two new problems:
    -An interrupt is not a process, but it utializes the blockAddress of a process
    this might lead to a wrong block address in the process
    -Interrupts can be nested, and thus the wrong parameter can be passed to the supervisor

    This solution solves both, without the need for a seperate piece of code just for the interrupt
**/
void callForRelease(void* oldBlockAddr){
    CALLSUPERVISOR(SVC_objectRelease);
    currentProcess->blockAddress = oldBlockAddr;
}

void __releaseObject(SingleLockObject* object){
    __unlockSingleLockObject(object);
    if (isInInterrupt()){
        void* oldBlockAddress = currentProcess->blockAddress;
        currentProcess->blockAddress = object;
        callForRelease(oldBlockAddress);
    } else {
        currentProcess->blockAddress = object;
        CALLSUPERVISOR(SVC_objectRelease);
    }
}

int __singleLockObjectIsLocked(SingleLockObject* object){
    return object->lock;
}
