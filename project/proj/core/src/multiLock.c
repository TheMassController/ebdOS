#include "threadsafeCalls.h"
#include "process.h"
#include "supervisorCall.h"
#include "sleep.h"
#include "stdlib.h"

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

int increaseMultiLock(MultiLockObject* object){
    int retCode;
    if ((retCode = __increaseMultiLockObject(object)) != -1){
        currentProcess->blockAddress = object;
        CALLSUPERVISOR(SVC_multiObjectIncrease);
    }
    return retCode;
}

int decreaseMultiLock(MultiLockObject* object){
    int retCode;
    if ((retCode = __decreaseMultiLockObject(object)) != -1){
        currentProcess->blockAddress = object;
        CALLSUPERVISOR(SVC_multiObjectDecrease);
    }
    return retCode;
}

int __increaseMultiLockObjectBlock(MultiLockObject* object){
   int retCode;
   while((retCode = increaseMultiLock(object)) == -1){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        //You want to increase, so you wait for a decrease
        CALLSUPERVISOR(SVC_multiObjectWaitForDecrease);
    } 
    return retCode;  
}
int __decreaseMultiLockObjectBlock(MultiLockObject* object){
   int retCode;
   while((retCode = decreaseMultiLock(object)) == -1){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        //You want to decrease, so you wait for an increase
        CALLSUPERVISOR(SVC_multiObjectWaitForIncrease);
    } 
    return retCode;
}
int __increaseMultiLockObjectNoBlock(MultiLockObject* object){
    return increaseMultiLock(object);
}

int __decreaseMultiLockObjectNoBlock(MultiLockObject* object){
    return decreaseMultiLock(object);
}

int __increaseMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout){
   int retCode;
   if ((retCode = increaseMultiLock(object)) == -1){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        //You want to increase, so you wait for a decrease
        CALLSUPERVISOR(SVC_multiObjectWaitForDecrease);
        sleepMS(msTimeout);
        retCode = increaseMultiLock(object);
    } 
    return retCode;  
    
}

int __decreaseMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout){
   int retCode;
   if ((retCode = decreaseMultiLock(object)) == -1){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        CALLSUPERVISOR(SVC_multiObjectWaitForIncrease);
        sleepMS(msTimeout);
        retCode = decreaseMultiLock(object);
    } 
    return retCode;  
}

int __getMultiLockVal(MultiLockObject* object){
    return object->lock;
}

int __getMultiLockMaxVal(MultiLockObject* object){
   return object->maxLockVal; 
}
