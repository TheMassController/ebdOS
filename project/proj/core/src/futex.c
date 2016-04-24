#include "futex.h"
#include "context.h"
#include "supervisorCall.h"
#include "atomicIntegerOperations.h"
#include "systemClockManagement.h"
/**
 * @brief The implementation of the userspace side of the futex.
 */

int initFutex(struct Futex* fut, int value){
    fut->atomicVal = value;
    // Do a syscall to initialize the futex.
    setContextParams(FUTEXINIT, fut, 0);
    CALLSUPERVISOR(SVC_serviceRequired);
    return currentContext->retVal;
}


int destroyFutex(struct Futex* fut){
    setContextParams(FUTEXDESTROY, fut, 0);
    CALLSUPERVISOR(SVC_serviceRequired);
    return currentContext->retVal;
}

int futexPost(struct Futex* fut){
    // Post: increment. If the newvalue is <= 0 inform the kernel that one process should be awoken.
    int newVal = atomicIncreaseInt(&fut->atomicVal);
    if (newVal <= 0){
        setContextParams(FUTEXPOST, fut, 0);
        CALLSUPERVISOR(SVC_serviceRequired);
        return currentContext->retVal;
    }
    return 0;
}

int futexWait(struct Futex* fut){
    // Wait: decrement. If the newvalue is < 0, wait until a resource falls free
    int newVal = atomicDecreaseInt(&fut->atomicVal);
    if (newVal < 0){
        setContextParams(FUTEXWAIT, fut, 0);
        CALLSUPERVISOR(SVC_serviceRequired);
        return currentContext->retVal;
    }
    return 0;
}

int futexWaitTimeout(struct Futex* restrict fut, struct SleepRequest* restrict sleepReq){
    struct DoublePtr{
        struct Futex* fut;
        struct SleepRequest* sleepReq;
    };
    // Wait: decrement. If the newvalue is < 0, wait until a resource falls free
    int newVal = atomicDecreaseInt(&fut->atomicVal);
    if (newVal < 0){
        sleepReq->refTime = getSystemClockValue();
        struct DoublePtr ptr = {
            .fut = fut,
            .sleepReq = sleepReq
        };
        setContextParams(FUTEXWAITTIMEOUT, &ptr, 0);
        CALLSUPERVISOR(SVC_serviceRequired);
        if (currentContext->retVal == ETIMEDOUT) atomicIncreaseInt(&fut->atomicVal);
        return currentContext->retVal;
    }
    return 0;
}

int futexTryWait(struct Futex* fut){
    int newVal = atomicDecreaseInt(&fut->atomicVal);
    if (newVal < 0){
        atomicIncreaseInt(&fut->atomicVal);
        return EBUSY;
    } else {
        return 0;
    }
}
