// User headers
#include "anonymousSpinlock.h"                   // Implies include process.h. Used to define the AnonymousSpinlock struct
#include "kernel/inc/supervisorCall.h"             // Needed for supervisor calls
#include "atomicIntegerOperations.h"    // Needed for threadsafe integer operations
// System headers
#include <errno.h>              // Contains the error values
#include <stdlib.h>             // Contains the def of NULL

int initAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock){
    if (anonymousSpinlock != NULL){
        anonymousSpinlock->value = 0;
        return 0;
    }
    return EINVAL;
}

int destroyAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock){
    if (anonymousSpinlock != NULL){
        if (anonymousSpinlock->value == 1){
            return EBUSY;
        } else {
            return 0;
        }
    }
    return EINVAL;
}

int lockAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock){
    if (anonymousSpinlock != NULL){
        while(atomicIncreaseIntWithMax(&anonymousSpinlock->value, 1) == -1){
            CALLSUPERVISOR(SVC_yield);
        }
        return 0;
    }
    return EINVAL;
}

int tryLockAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock){
    if (anonymousSpinlock != NULL){
        if (atomicIncreaseIntWithMax(&anonymousSpinlock->value, 1) == 1){
            return 0;
        } else {
            return EBUSY;
        }
    }
    return EINVAL;
}

int unlockAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock){
    if (anonymousSpinlock != NULL){
        // We do not care if this fails or not
        atomicDecreaseIntWithMax(&anonymousSpinlock->value);
        return 0;
    }
    return EINVAL;
}
