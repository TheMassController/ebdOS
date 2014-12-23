#include "threadsafeCalls.h" 
#include "process.h"
#include "supervisorCall.h"
#include "sleep.h"
#include "stdlib.h" 

extern struct Process* currentProcess;

//Returns 1 if successful, 0 otherwise
unsigned __lockSingleLockObject(SingleLockObject* addr);
void __unlockSingleLockObject(SingleLockObject* addr);
//Returns new value of multilockobject, or -1 in case of failure
int __increaseMultiLockObject(MultiLockObject* addr);
int __decreaseMultiLockObject(MultiLockObject* addr);


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

MultiLockObject* __createMultiLockObject(int maxval){
    if (maxval <= 0) maxval = 1;
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

int __increaseMultiLockObjectBlock(MultiLockObject* object){
   int retCode;
   while((retCode = __increaseMultiLockObject(object)) == -1){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        CALLSUPERVISOR(SVC_multiObjectDecrease);
    } 
    return retCode;  
}
int __decreaseMultiLockObjectBlock(MultiLockObject* object){
   int retCode;
   while((retCode = __decreaseMultiLockObject(object)) == -1){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        CALLSUPERVISOR(SVC_multiObjectIncrease);
    } 
    return retCode;
}
int __increaseMultiLockObjectNoBlock(MultiLockObject* object){
    return __increaseMultiLockObject(object);
}
int __decreaseMultiLockObjectNoBlock(MultiLockObject* object){
    return __decreaseMultiLockObject(object);
}
//TODO
int __increaseMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout);
int __decreaseMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout);
unsigned __getMultiLockVal(MultiLockObject* object){
    return object->lock;
}

unsigned __getMultiLockMaxVal(MultiLockObject* object){
   return object->maxLockVal; 
}
