#include "semaphore.h"

int initSemaphore(struct Semaphore* semaphore, int value){
    return initFutex(&semaphore->fut, value);
}

int destroySemaphore(struct Semaphore* semaphore){
    return destroyFutex(&semaphore->fut);
}

int semaphorePost(struct Semaphore* semaphore){
   return futexPost(&semaphore->fut);
}

int semaphoreWait(struct Semaphore* semaphore){
    return futexWait(&semaphore->fut);
}

int semaphoreTryWait(struct Semaphore* semaphore){
    return futexTryWait(&semaphore->fut);
}

int semaphoreWaitTimeout(struct Semaphore* restrict semaphore, struct SleepRequest* restrict sleepReq){
    return futexWaitTimeout(&semaphore->fut, sleepReq);
}

int semaphoreGetValue(struct Semaphore* semaphore){
   return futexGetValue(&semaphore->fut);
}
