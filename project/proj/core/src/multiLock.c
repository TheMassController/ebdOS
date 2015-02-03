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

int blockWaitForIncrease(MultiLockObject* object){
    currentProcess->state |= STATE_DEC_WAIT;
    //You want to increase, so you wait for a decrease
    currentProcess->blockAddress = object;
    CALLSUPERVISOR(SVC_multiObjectWaitForDecreaseAndSleep);
    return increaseMultiLock(object);
}

int blockWaitForDecrease(MultiLockObject* object){
    currentProcess->state |= STATE_INC_WAIT;
    currentProcess->blockAddress = object;
    CALLSUPERVISOR(SVC_multiObjectWaitForIncreaseAndSleep);
    return decreaseMultiLock(object);
}

int modifyMultiLockObjectBlock(MultiLockObject* object, const char increase){
    if (isInInterrupt()) return -1;
    int retCode;
    if (increase){
        retCode = increaseMultiLock(object);
        while (retCode == -1){
          retCode = blockWaitForIncrease(object);  
        }
    } else {
        retCode = decreaseMultiLock(object);
        while (retCode == -1){
          retCode = blockWaitForDecrease(object);  
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

int modifyMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout, const char increase){
    if (isInInterrupt()) return -1;
    int retCode;
    if (increase){
        retCode = increaseMultiLock(object);
    } else {
        retCode = decreaseMultiLock(object);
    }
    if (retCode == -1){
        __sleepMSDelayBlock(msTimeout);
        while((currentProcess->state & STATE_SLEEP) && (retCode == -1)){ 
            if (increase){
                retCode = blockWaitForIncrease(object);  
            } else {
                retCode = blockWaitForDecrease(object);  
            }
        }
        if (currentProcess->state & STATE_SLEEP) CALLSUPERVISOR(SVC_wakeupCurrent);
        __sleepDelayBlockWakeup();
    }
    return retCode;
}

int __increaseMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout){
    return modifyMultiLockObjectBlockTimeout(object, msTimeout, 1);
}

int __decreaseMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout){
    return modifyMultiLockObjectBlockTimeout(object, msTimeout, 0);
}

int __getMultiLockVal(MultiLockObject* object){
    return object->lock;
}

int __getMultiLockMaxVal(MultiLockObject* object){
   return object->maxLockVal; 
}
