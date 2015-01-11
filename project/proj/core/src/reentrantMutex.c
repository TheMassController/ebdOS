#include "reentrantMutex.h"
#include "stdlib.h"

struct ReentrantMutex* createReentrantMutex(void){
    struct ReentrantMutex* mutex = (struct ReentrantMutex*)malloc(sizeof(struct ReentrantMutex));
    if (mutex == NULL) return NULL;
    mutex->mutex = createMutex();
    if (mutex->mutex == NULL){
        free(mutex);
        return NULL;
    }
    mutex->value = 0;
    return mutex;
}

void deleteReentrantMutex(struct ReentrantMutex* mutex){
    deleteMutex(mutex->mutex); 
    free(mutex);
}

void lockReentrantMutexBlocking(struct ReentrantMutex* mutex){
    lockMutexBlocking(mutex->mutex);
    mutex->value++;
}

int lockReentrantMutexNoBlock(struct ReentrantMutex* mutex){
    if (!lockMutexNoBlock(mutex->mutex)){
        return 0;
    }
    mutex->value++;
    return 1;
}

int lockReentrantMutexBlockWait(struct ReentrantMutex* mutex, unsigned msWaitTime){
    if (!lockMutexBlockWait(mutex->mutex, msWaitTime)){
        return 0;
    }
    mutex->value++;
    return 1;
}

void releaseReentrantMutex(struct ReentrantMutex* mutex){
    if (!lockMutexNoBlock(mutex->mutex)) return;
    mutex->value--;
    if (mutex->value == 0){
        releaseMutex(mutex->mutex);
    }
}


