#include "semaphore.h"
#include "stdlib.h"

//TODO semaphore can not be locking-increased or decreased from interrupt

struct Semaphore* createSemaphore(int maxval){
    if (maxval <= 0) maxval = 1;
    struct Semaphore* semaphore = (struct Semaphore*)malloc(sizeof(struct Semaphore));
    if (semaphore == NULL) return NULL;
    semaphore->multiLockObject = __createMultiLockObject(maxval);
    if (semaphore->multiLockObject == NULL){
        free(semaphore);
        return NULL;
    }
    return semaphore;
}

void deleteSemaphore(struct Semaphore* semaphore){
    __deleteMultiLockObject(semaphore->multiLockObject);
    free(semaphore);
}

void increaseSemaphoreBlocking(struct Semaphore* semaphore){
    __increaseMultiLockObjectBlock(semaphore->multiLockObject);
}
int increaseSemaphoreNonBlocking(struct Semaphore* semaphore){
    if (__increaseMultiLockObjectNoBlock(semaphore->multiLockObject) == -1){
        return 0;
    }
    return 1;
}
int increaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout){
   if(__increaseMultiLockObjectBlockTimeout(semaphore->multiLockObject, timeout) == -1){
        return 0;
    }
    return 1;
}

void decreaseSemaphoreBlocking(struct Semaphore* semaphore){
    __decreaseMultiLockObjectBlock(semaphore->multiLockObject);
}
int decreaseSemaphoreNonBlocking(struct Semaphore* semaphore){
    if (__decreaseMultiLockObjectNoBlock(semaphore->multiLockObject) == -1){
        return 0;
    }
    return 1; 
}

int decreaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout){
    if(__increaseMultiLockObjectBlockTimeout(semaphore->multiLockObject, timeout) == -1){
        return 0;
    }
    return 1;
}

int getSemaphoreMaxval(struct Semaphore* semaphore){
    return __getMultiLockMaxVal(semaphore->multiLockObject);
}
int getSemaphoreCurrentVal(struct Semaphore* semaphore){
    return __getMultiLockVal(semaphore->multiLockObject);
}
