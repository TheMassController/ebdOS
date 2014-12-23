#include "semaphore.h"
#include "stdlib.h"

//TODO semaphore can not be locking-increased or decreased from interrupt

Semaphore* createSemaphore(int maxval){
    if (maxval <= 0) maxval = 1;
    Semaphore* semaphore = (Semaphore*)malloc(sizeof(Semaphore));
    if (semaphore == NULL) return NULL;
    semaphore->multiLockObject = __createMultiLockObject(maxval);
    if (semaphore->multiLockObject == NULL){
        free(semaphore);
        return NULL;
    }
    return semaphore;
}

void deleteSemaphore(Semaphore* semaphore){
    __deleteMultiLockObject(semaphore->multiLockObject);
    free(semaphore);
}

void increaseSemaphoreBlocking(Semaphore* semaphore){
    __increaseMultiLockObjectBlock(semaphore->multiLockObject);
}
int increaseSemaphoreNonBlocking(Semaphore* semaphore){
    if (__increaseMultiLockObjectNoBlock(semaphore->multiLockObject) == -1){
        return 0;
    }
    return 1;
}
int increaseSemaphoreBlockingTimeout(Semaphore* semaphore, unsigned timeout){
   if(__increaseMultiLockObjectBlockTimeout(semaphore->multiLockObject, timeout) == -1){
        return 0;
    }
    return 1;
}

void decreaseSemaphoreBlocking(Semaphore* semaphore){
    __decreaseMultiLockObjectBlock(semaphore->multiLockObject);
}
int decreaseSemaphoreNonBlocking(Semaphore* semaphore){
    if (__decreaseMultiLockObjectNoBlock(semaphore->multiLockObject) == -1){
        return 0;
    }
    return 1; 
}

int decreaseSemaphoreBlockingTimeout(Semaphore* semaphore, unsigned timeout){
    if(__increaseMultiLockObjectBlockTimeout(semaphore->multiLockObject, timeout) == -1){
        return 0;
    }
    return 1;
}

int getSemaphoreMaxval(Semaphore* semaphore){
    return __getMultiLockMaxVal(semaphore->multiLockObject);
}
int getSemaphoreCurrentVal(Semaphore* semaphore){
    return __getMultiLockVal(semaphore->multiLockObject);
}
