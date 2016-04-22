#include "reentrantMutex.h"
#include "stdlib.h"
#include "context.h"

int initReentrantMutex(struct ReentrantMutex* mutex){
    mutex->ownerContext = NULL;
    mutex->value = 0;
    return initFutex(&mutex->fut, 1);
}

int destroyReentrantMutex(struct ReentrantMutex* mutex){
    return destroyFutex(&mutex->fut);
}

int lockReentrantMutex(struct ReentrantMutex* mutex){
    if (mutex->ownerContext == currentContext){
        mutex->value++;
    } else {
        int retVal = futexWait(&mutex->fut);
        if (retVal == 0) {
            mutex->value = 1;
            mutex->ownerContext = currentContext;
        } else {
            return retVal;
        }
    }
    return 0;
}

int lockReentrantMutexNoBlock(struct ReentrantMutex* mutex){
    if (mutex->ownerContext == currentContext){
        mutex->value++;
    } else {
        int retVal = futexTryWait(&mutex->fut);
        if (retVal == 0) {
            mutex->value = 1;
            mutex->ownerContext = currentContext;
        } else {
            return retVal;
        }
    }
    return 0;
}

int lockReentrantMutexTimeout(struct ReentrantMutex* restrict mutex, struct SleepRequest* restrict sleepReq){
    if (mutex->ownerContext == currentContext){
        mutex->value++;
    } else {
        int retVal = futexWaitTimeout(&mutex->fut, sleepReq);
        if (retVal == 0) {
            mutex->value = 1;
            mutex->ownerContext = currentContext;
        } else {
            return retVal;
        }
    }
    return 0;
}

int unlockReentrantMutex(struct ReentrantMutex* mutex){
    if (mutex->ownerContext != currentContext) return EPERM;
    if (--mutex->value == 0) {
        mutex->ownerContext = NULL;
        return futexPost(&mutex->fut);
    } else return 0;
}
