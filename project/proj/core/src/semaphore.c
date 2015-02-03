#include "semaphore.h"
#include "stdlib.h"

//TODO semaphore can not be locking-increased or decreased from interrupt

void initSemaphore(struct Semaphore* semaphore, int maxval){
    if (maxval <= 0) maxval = 1;
    __initMultiLockObject(&(semaphore->multiLockObject), maxval);
}

void cleanupSemaphore(struct Semaphore* semaphore){
    __cleanupMultiLockObject(&(semaphore->multiLockObject));
}

void increaseSemaphoreBlocking(struct Semaphore* semaphore){
    __increaseMultiLockObjectBlock(&(semaphore->multiLockObject));
}
int increaseSemaphoreNonBlocking(struct Semaphore* semaphore){
    if (__increaseMultiLockObjectNoBlock(&(semaphore->multiLockObject)) == -1){
        return 0;
    }
    return 1;
}
int increaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout){
   if(__increaseMultiLockObjectBlockTimeout(&(semaphore->multiLockObject), timeout) == -1){
        return 0;
    }
    return 1;
}

void decreaseSemaphoreBlocking(struct Semaphore* semaphore){
    __decreaseMultiLockObjectBlock(&(semaphore->multiLockObject));
}
int decreaseSemaphoreNonBlocking(struct Semaphore* semaphore){
    if (__decreaseMultiLockObjectNoBlock(&(semaphore->multiLockObject)) == -1){
        return 0;
    }
    return 1; 
}

int decreaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout){
    if(__decreaseMultiLockObjectBlockTimeout(&(semaphore->multiLockObject), timeout) == -1){
        return 0;
    }
    return 1;
}

int getSemaphoreMaxval(struct Semaphore* semaphore){
    return __getMultiLockMaxVal(&(semaphore->multiLockObject));
}
int getSemaphoreCurrentVal(struct Semaphore* semaphore){
    return __getMultiLockVal(&(semaphore->multiLockObject));
}
