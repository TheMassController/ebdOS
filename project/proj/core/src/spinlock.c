// User headers
#include "spinlock.h"           // Implies include process.h. Used to define the Spinlock struct
#include "supervisorCall.h"     // Needed for supervisor calls
#include "coreUtils.h"          // Needed for threadsafe integer operations
// System headers
#include <errno.h>              // Contains the error values
#include <stdlib.h>             // Contains the def of NULL

extern struct Process* currentProcess;

int initSpinlock(struct Spinlock* spinlock){
    if (spinlock != NULL){
        spinlock->value = 0;
        spinlock->owner = NULL;
        return 0;
    }
    return EINVAL;
}

int destroySpinlock(struct Spinlock* spinlock){
    if (spinlock != NULL){
        if (spinlock->value == 1 || spinlock->owner != NULL){
            return EBUSY;
        } else {
            return 0;
        }
    }
    return EINVAL;
}

int lockSpinlock(struct Spinlock* spinlock){
    if (spinlock != NULL){
        while(incrIntegerTS(&spinlock->value, 1) == -1){
            if (spinlock->owner == currentProcess)
                return EDEADLK;
            CALLSUPERVISOR(SVC_yield);
        }
        spinlock->owner = currentProcess;
        return 0;
    }
    return EINVAL;
}

int tryLockSpinlock(struct Spinlock* spinlock){
    if (spinlock != NULL){
        if (incrIntegerTS(&spinlock->value, 1) == 1){
            spinlock->owner = currentProcess;
            return 0;
        } else {
            if (spinlock->owner == currentProcess)
                return EDEADLK;
            else
                return EBUSY;
        }
    }
    return EINVAL;
}

int unlockSpinlock(struct Spinlock* spinlock){
    if (spinlock != NULL){
        if (incrIntegerTS(&spinlock->value, 1) == 1){
            // The spinlock was not locked, do nothing
            decrIntegerTS(&spinlock->value);
            return 0;
        } else {
            if (spinlock->owner != currentProcess){
                return EPERM;
            }
            spinlock->owner = NULL;
            decrIntegerTS(&spinlock->value);
            return 0;
        }
    }
    return EINVAL;
}
