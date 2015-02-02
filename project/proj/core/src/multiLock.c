#include "threadsafeCalls.h"
#include "process.h"
#include "supervisorCall.h"
#include "sysSleep.h"
#include "stdlib.h"
#include "asmUtils.h"

extern struct Process* currentProcess;

//Returns new value of multilockobject, or -1 in case of failure
int __increaseMultiLockObject(MultiLockObject* addr);
int __decreaseMultiLockObject(MultiLockObject* addr);

void __initMultiLockObject(MultiLockObject* object, int maxval){
    if (maxval <= 0) maxval = 1;
    object->lock = 0;
    object->maxLockVal = maxval;
    object->processWaitingQueueIncrease = NULL;
    object->processWaitingQueueDecrease = NULL;
}

void __cleanupMultiLockObject(MultiLockObject* object){
    if (object->lock != 0 || object->processWaitingQueueIncrease != NULL || object->processWaitingQueueDecrease != NULL){
        //TODO kernel panic
    }
}

void callForIncrease(void* oldBlockAddr){
    CALLSUPERVISOR(SVC_multiObjectIncrease);
    currentProcess->blockAddress = oldBlockAddr;
}

int increaseMultiLock(MultiLockObject* object){
    int retCode;
    if ((retCode = __increaseMultiLockObject(object)) != -1){
        if (isInInterrupt()){
            void* oldBlockAddress = currentProcess->blockAddress;
            currentProcess->blockAddress = object;
            callForIncrease(oldBlockAddress);
        } else {
            currentProcess->blockAddress = object;
            CALLSUPERVISOR(SVC_multiObjectIncrease);
        }
    }
    return retCode;
}

void callForDecrease(void* oldBlockAddr){
    CALLSUPERVISOR(SVC_multiObjectDecrease);
    currentProcess->blockAddress = oldBlockAddr;
}

int decreaseMultiLock(MultiLockObject* object){
    int retCode;
    if ((retCode = __decreaseMultiLockObject(object)) != -1){
        if (isInInterrupt()){
            void* oldBlockAddress = currentProcess->blockAddress;
            currentProcess->blockAddress = object;
            callForDecrease(oldBlockAddress);    
        } else {
            currentProcess->blockAddress = object;
            CALLSUPERVISOR(SVC_multiObjectDecrease);
        }
    }
    return retCode;
}

int __increaseMultiLockObjectBlock(MultiLockObject* object){
    if (isInInterrupt()) return -1;
    int retCode;
    while((retCode = increaseMultiLock(object)) == -1){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_DEC_WAIT;
        //You want to increase, so you wait for a decrease
        CALLSUPERVISOR(SVC_multiObjectWaitForDecrease);
    } 
    return retCode;  
}

int __decreaseMultiLockObjectBlock(MultiLockObject* object){
    if (isInInterrupt()) return -1;
   int retCode;
   while((retCode = decreaseMultiLock(object)) == -1){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_INC_WAIT;
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
    if (isInInterrupt()) return -1;
    int retCode;
    if ((retCode = increaseMultiLock(object)) == -1){
        __sleepMSDelayBlock(msTimeout);
        while((currentProcess->state & STATE_SLEEP) && (retCode == -1)){ 
            currentProcess->state |= STATE_DEC_WAIT;
            //You want to increase, so you wait for a decrease
            currentProcess->blockAddress = object;
            CALLSUPERVISOR(SVC_multiObjectWaitForDecreaseAndSleep);
            retCode = increaseMultiLock(object);
        }
        if (currentProcess->state & STATE_SLEEP) CALLSUPERVISOR(SVC_wakeupCurrent);
        __sleepDelayBlockWakeup();
    } 
    return retCode;  
    
}

int __decreaseMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout){
    if (isInInterrupt()) return -1;
    int retCode;
    if ((retCode = decreaseMultiLock(object)) == -1){
        __sleepMSDelayBlock(msTimeout);
        while((currentProcess->state & STATE_SLEEP) && (retCode == -1)){ 
            currentProcess->state |= STATE_INC_WAIT;
            currentProcess->blockAddress = object;
            CALLSUPERVISOR(SVC_multiObjectWaitForIncreaseAndSleep);
            retCode = decreaseMultiLock(object);
        }
        if (currentProcess->state & STATE_SLEEP) CALLSUPERVISOR(SVC_wakeupCurrent);
        __sleepDelayBlockWakeup();
    } 
    return retCode;  
}

int __getMultiLockVal(MultiLockObject* object){
    return object->lock;
}

int __getMultiLockMaxVal(MultiLockObject* object){
   return object->maxLockVal; 
}
