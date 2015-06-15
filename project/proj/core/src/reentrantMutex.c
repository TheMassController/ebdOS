#include "reentrantMutex.h"
#include "stdlib.h"

void initReentrantMutex(struct ReentrantMutex* mutex){
    initMutex(&(mutex->mutex));
    mutex->value = 0;
}

void cleanupReentrantMutex(struct ReentrantMutex* mutex){
    cleanupMutex(&(mutex->mutex));
}

void lockReentrantMutexBlocking(struct ReentrantMutex* mutex){
    lockMutexBlocking(&(mutex->mutex));
    mutex->value++;
}

int lockReentrantMutexNoBlock(struct ReentrantMutex* mutex){
    if (!lockMutexNoBlock(&(mutex->mutex))){
        return 0;
    }
    mutex->value++;
    return 1;
}

int lockReentrantMutexBlockWait(struct ReentrantMutex* mutex, unsigned msWaitTime){
    if (!lockMutexBlockWait(&(mutex->mutex), msWaitTime)){
        return 0;
    }
    mutex->value++;
    return 1;
}

void releaseReentrantMutex(struct ReentrantMutex* mutex){
    if(ownsMutex(&(mutex->mutex))){
        mutex->value--;
        if (mutex->value == 0){
            releaseMutex(&(mutex->mutex));
        }
    }
}


