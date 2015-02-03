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


void intrModifyCall(void* oldBlockAddr, const char increase){
    if (increase){
        CALLSUPERVISOR(SVC_multiObjectIncrease);
    } else {
        CALLSUPERVISOR(SVC_multiObjectDecrease);
    }
    currentProcess->blockAddress = oldBlockAddr;
}

int modifyMultiLockObject(MultiLockObject* object, const char increase){
    int retCode;
    if (increase){
        retCode = __increaseMultiLockObject(object);
    } else {
        retCode = __decreaseMultiLockObject(object);
    }
    if (retCode != -1){
        void* oldBlockAddress = currentProcess->blockAddress;
        currentProcess->blockAddress = object;
        intrModifyCall(oldBlockAddress, increase);
    }
    return retCode;
}


int increaseMultiLock(MultiLockObject* object){
    return modifyMultiLockObject(object, 1);
}

int decreaseMultiLock(MultiLockObject* object){
    return modifyMultiLockObject(object, 0);
}

int __increaseMultiLockObjectNoBlock(MultiLockObject* object){
    return increaseMultiLock(object);
}

int __decreaseMultiLockObjectNoBlock(MultiLockObject* object){
    return decreaseMultiLock(object);
}

int modifyMultiLockObjectBlock(MultiLockObject* object, const char increase){
    if (isInInterrupt()) return -1;
    int retCode;
    if (increase){
        while((retCode = increaseMultiLock(object)) == -1){
            currentProcess->blockAddress = object;
            currentProcess->state |= STATE_DEC_WAIT;
            //You want to increase, so you wait for a decrease
            CALLSUPERVISOR(SVC_multiObjectWaitForDecrease);
        }
    } else {
        while((retCode = decreaseMultiLock(object)) == -1){
            currentProcess->blockAddress = object;
            currentProcess->state |= STATE_INC_WAIT;
            //You want to decrease, so you wait for an increase
            CALLSUPERVISOR(SVC_multiObjectWaitForIncrease);
        }
    }
    return retCode;
}

int __increaseMultiLockObjectBlock(MultiLockObject* object){
    return modifyMultiLockObjectBlock(object, 1);
}

int __decreaseMultiLockObjectBlock(MultiLockObject* object){
    return modifyMultiLockObjectBlock(object, 0);
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
