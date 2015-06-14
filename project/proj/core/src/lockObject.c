#include "lockObject.h"
#include "process.h"
#include "supervisorCall.h"
#include "sysSleep.h"
#include "stdlib.h"
#include "coreUtils.h"

extern struct Process* currentProcess;
extern void* volatile intrBlockObject;

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

int modifyLockObject(struct LockObject* object, const char increase){
    int retCode;
    if (increase){
        retCode = __increaseLockObject(object);
    } else {
        retCode = __decreaseLockObject(object);
    }
    if (retCode != -1){
        if (!isInInterrupt()){
            currentProcess->blockAddress = object;
            if (increase){
                CALLSUPERVISOR(SVC_multiObjectIncrease);
            } else {
                CALLSUPERVISOR(SVC_multiObjectDecrease);
            }
        } else {
            void * volatile storeAddr = intrBlockObject;
            intrBlockObject = object;
            if (increase){
                CALLSUPERVISOR(SVC_multiObjectIncrease);
            } else {
                CALLSUPERVISOR(SVC_multiObjectDecrease);
            }
            intrBlockObject = storeAddr;
        }
    }
    return retCode;
}

int __increaseLockObjectNoBlock(struct LockObject* object){
    return modifyLockObject(object, 1);
}

int __decreaseLockObjectNoBlock(struct LockObject* object){
    return modifyLockObject(object, 0);
}

int modifyLockObjectBlock(struct LockObject* object, const char increase){
    if (isInInterrupt()) return -1;
    int retCode;
    if (increase){
        retCode = modifyLockObject(object, 1);
        while (retCode == -1){
            currentProcess->state |= STATE_DEC_WAIT;
            //You want to increase, so you wait for a decrease
            currentProcess->blockAddress = object;
            CALLSUPERVISOR(SVC_multiObjectWaitForDecrease);
            retCode = modifyLockObject(object, 1);
        }
    } else {
        retCode = modifyLockObject(object, 0);
        while (retCode == -1){
            currentProcess->state |= STATE_INC_WAIT;
            currentProcess->blockAddress = object;
            CALLSUPERVISOR(SVC_multiObjectWaitForIncrease);
            retCode = modifyLockObject(object, 0);
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
        retCode = modifyLockObject(object, 1);
    } else {
        retCode = modifyLockObject(object, 0);
    }
    if (retCode == -1){
        __sleepMSDelayBlock(msTimeout);
        while((currentProcess->state & STATE_SLEEP) && (retCode == -1)){ 
            if (increase){
                currentProcess->state |= STATE_DEC_WAIT;
                //You want to increase, so you wait for a decrease
                currentProcess->blockAddress = object;
                CALLSUPERVISOR(SVC_multiObjectWaitForDecreaseAndSleep);
                retCode = modifyLockObjectBlock(object, 1);
            } else {
                currentProcess->state |= STATE_INC_WAIT;
                currentProcess->blockAddress = object;
                CALLSUPERVISOR(SVC_multiObjectWaitForIncreaseAndSleep);
                retCode = modifyLockObjectBlock(object, 0);
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
