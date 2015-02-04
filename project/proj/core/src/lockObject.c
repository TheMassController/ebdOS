#include "lockObject.h"
#include "process.h"
#include "supervisorCall.h"
#include "sysSleep.h"
#include "stdlib.h"
#include "asmUtils.h"

extern struct Process* currentProcess;

//Returns new value of multilockobject, or -1 in case of failure
int __increaseLockObject(struct LockObject* addr);
int __decreaseLockObject(struct LockObject* addr);

void __initLockObject(struct LockObject* object, int maxval){
    if (maxval <= 0) maxval = 1;
    object->lock = 0;
    object->maxLockVal = maxval;
    object->processWaitingQueueIncrease = NULL;
    object->processWaitingQueueDecrease = NULL;
}

void __cleanupLockObject(struct LockObject* object){
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

int modifyLockObject(struct LockObject* object, const char increase){
    int retCode;
    if (increase){
        retCode = __increaseLockObject(object);
    } else {
        retCode = __decreaseLockObject(object);
    }
    if (retCode != -1){
        void* oldBlockAddress = currentProcess->blockAddress;
        currentProcess->blockAddress = object;
        intrModifyCall(oldBlockAddress, increase);
    }
    return retCode;
}

int increaseLock(struct LockObject* object){
    return modifyLockObject(object, 1);
}

int decreaseLock(struct LockObject* object){
    return modifyLockObject(object, 0);
}

int __increaseLockObjectNoBlock(struct LockObject* object){
    return increaseLock(object);
}

int __decreaseLockObjectNoBlock(struct LockObject* object){
    return decreaseLock(object);
}

int blockWaitForIncrease(struct LockObject* object){
    currentProcess->state |= STATE_DEC_WAIT;
    //You want to increase, so you wait for a decrease
    currentProcess->blockAddress = object;
    CALLSUPERVISOR(SVC_multiObjectWaitForDecreaseAndSleep);
    return increaseLock(object);
}

int blockWaitForDecrease(struct LockObject* object){
    currentProcess->state |= STATE_INC_WAIT;
    currentProcess->blockAddress = object;
    CALLSUPERVISOR(SVC_multiObjectWaitForIncreaseAndSleep);
    return decreaseLock(object);
}

int modifyLockObjectBlock(struct LockObject* object, const char increase){
    if (isInInterrupt()) return -1;
    int retCode;
    if (increase){
        retCode = increaseLock(object);
        while (retCode == -1){
          retCode = blockWaitForIncrease(object);  
        }
    } else {
        retCode = decreaseLock(object);
        while (retCode == -1){
          retCode = blockWaitForDecrease(object);  
        }
    }
    return retCode;
}

int __increaseLockObjectBlock(struct LockObject* object){
    return modifyLockObjectBlock(object, 1);
}

int __decreaseLockObjectBlock(struct LockObject* object){
    return modifyLockObjectBlock(object, 0);
}

int modifyLockObjectBlockTimeout(struct LockObject* object, unsigned msTimeout, const char increase){
    if (isInInterrupt()) return -1;
    int retCode;
    if (increase){
        retCode = increaseLock(object);
    } else {
        retCode = decreaseLock(object);
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
    }
    return retCode;
}

int __increaseLockObjectBlockTimeout(struct LockObject* object, unsigned msTimeout){
    return modifyLockObjectBlockTimeout(object, msTimeout, 1);
}

int __decreaseLockObjectBlockTimeout(struct LockObject* object, unsigned msTimeout){
    return modifyLockObjectBlockTimeout(object, msTimeout, 0);
}

int __getLockVal(struct LockObject* object){
    return object->lock;
}

int __getLockMaxVal(struct LockObject* object){
   return object->maxLockVal; 
}

int __LockIsMaxVal(struct LockObject* object){
    return (object->lock == object->maxLockVal);
}

int __LockIsMinVal(struct LockObject* object){
    return (!object->lock);
}
