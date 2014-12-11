#include "threadsafeCalls.h" 
#include "process.h"
#include "supervisorCall.h"
#include "sleep.h"
#include "stdlib.h" 

extern struct Process* currentProcess;

//Returns 1 if successful, 0 otherwise
unsigned __lockSingleLockObject(SingleLockObject* addr);
void __unlockSingleLockObject(SingleLockObject* addr);
unsigned __increaseMultiLockObject(MultiLockObject* addr);
unsigned __decreaseMultiLockObject(MultiLockObject* addr);


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
    return __lockSingleLockObject(object);
}

void __lockObjectBlock(SingleLockObject* object){
   while(!__lockSingleLockObject(object)){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
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
    __unlockSingleLockObject(object);
    currentProcess->blockAddress = object;
    CALLSUPERVISOR(SVC_objectRelease);
}

int __singleLockObjectIsLocked(SingleLockObject* object){
    return object->lock;
}

MultiLockObject* createMultiLockObject(unsigned maxval){
    if (maxval == 0) maxval = 1;
    MultiLockObject* object = (MultiLockObject*)malloc(sizeof(MultiLockObject));
    object->lock = 0;
    object->maxLockVal = maxval;
    object->processWaitingQueueIncrease = NULL;
    object->processWaitingQueueDecrease = NULL;
    return object;
}

void __deleteMultiLockObject(MultiLockObject* object){
    //TODO notify someone that this is happening
    free(object);
}

void __increaseMultiLockObjectBlock(MultiLockObject* object){
   while(!__increaseMultiLockObject(object)){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        CALLSUPERVISOR(SVC_multiObjectDecrease);
    } 
    
}
void __decreaseMultiLockObjectBlock(MultiLockObject* object){
   while(!__decreaseMultiLockObject(object)){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        CALLSUPERVISOR(SVC_multiObjectIncrease);
    } 
}
int __increaseMultiLockObjectNoBlock(MultiLockObject* object){
    return __increaseMultiLockObject(object);
}
int __decreaseMultiLockObjectNoBlock(MultiLockObject* object){
    return __decreaseMultiLockObject(object);
}
int __increaseMultiLockObjectBlockTimeout(MultiLockObject* object);
int __decreaseMultiLockObjectBlockTimeout(MultiLockObject* object);
unsigned __getMultiLockVal(MultiLockObject* object);

