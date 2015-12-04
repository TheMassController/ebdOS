// User headers
#include "spinlock.h"                   // Implies include process.h. Used to define the Spinlock struct
#include "supervisorCall.h"             // Needed for supervisor calls
#include "atomicIntegerOperations.h"    // Needed for threadsafe integer operations
// System headers
#include <errno.h>              // Contains the error values
#include <stdlib.h>             // Contains the def of NULL

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
        while(atomicIncreaseIntWithMax(&spinlock->value, 1) == -1){
            if (spinlock->owner == currentContext)
                return EDEADLK;
            CALLSUPERVISOR(SVC_yield);
        }
        spinlock->owner = currentContext;
        return 0;
    }
    return EINVAL;
}

int tryLockSpinlock(struct Spinlock* spinlock){
    if (spinlock != NULL){
        if (atomicIncreaseIntWithMax(&spinlock->value, 1) == 1){
            spinlock->owner = currentContext;
            return 0;
        } else {
            if (spinlock->owner == currentContext)
                return EDEADLK;
            else
                return EBUSY;
        }
    }
    return EINVAL;
}

int unlockSpinlock(struct Spinlock* spinlock){
    if (spinlock != NULL){
        if (atomicIncreaseIntWithMax(&spinlock->value, 1) == 1){
            // The spinlock was not locked, do nothing
            atomicDecreaseIntWithMax(&spinlock->value);
            return 0;
        } else {
            if (spinlock->owner != currentContext){
                return EPERM;
            }
            spinlock->owner = NULL;
            atomicDecreaseIntWithMax(&spinlock->value);
            return 0;
        }
    }
    return EINVAL;
}
