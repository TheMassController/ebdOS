#include "reentrantMutex.h"
#include "stdlib.h"

ReentrantMutex* createReentrantMutex(void){
    ReentrantMutex* mutex = (ReentrantMutex*)malloc(sizeof(ReentrantMutex));
    if (mutex == NULL) return NULL;
    mutex->mutex = createMutex();
    if (mutex->mutex == NULL){
        free(mutex);
        return NULL;
    }
    mutex->value = 0;
    return mutex;
}

void deleteReentrantMutex(ReentrantMutex* mutex){
    deleteMutex(mutex->mutex); 
    free(mutex);
}

void lockReentrantMutexBlocking(ReentrantMutex* mutex){
    lockMutexBlocking(mutex->mutex);
    mutex->value++;
}

int lockReentrantMutexNoBlock(ReentrantMutex* mutex){
    if (!lockMutexNoBlock(mutex->mutex)){
        return 0;
    }
    mutex->value++;
    return 1;
}

int lockReentrantMutexBlockWait(ReentrantMutex* mutex, unsigned msWaitTime){
    if (!lockMutexBlockWait(mutex->mutex, msWaitTime)){
        return 0;
    }
    mutex->value++;
    return 1;
}

void releaseReentrantMutex(ReentrantMutex* mutex){
    if (!lockMutexNoBlock(mutex->mutex)) return;
    mutex->value--;
    if (mutex->value == 0){
        releaseMutex(mutex->mutex);
    }
}


