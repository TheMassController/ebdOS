#include "semaphore.h"
#include "stdlib.h"

//TODO semaphore can not be locking-increased or decreased from interrupt

void initSemaphore(struct Semaphore* semaphore, int maxval){
    if (maxval <= 0) maxval = 1;
    __initLockObject(&(semaphore->lockObject), maxval);
}

void cleanupSemaphore(struct Semaphore* semaphore){
    __cleanupLockObject(&(semaphore->lockObject));
}

void increaseSemaphoreBlocking(struct Semaphore* semaphore){
    __increaseLockObjectBlock(&(semaphore->lockObject));
}
int increaseSemaphoreNonBlocking(struct Semaphore* semaphore){
    if (__increaseLockObjectNoBlock(&(semaphore->lockObject)) == -1){
        return 0;
    }
    return 1;
}
int increaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout){
   if(__increaseLockObjectBlockTimeout(&(semaphore->lockObject), timeout) == -1){
        return 0;
    }
    return 1;
}

void decreaseSemaphoreBlocking(struct Semaphore* semaphore){
    __decreaseLockObjectBlock(&(semaphore->lockObject));
}
int decreaseSemaphoreNonBlocking(struct Semaphore* semaphore){
    if (__decreaseLockObjectNoBlock(&(semaphore->lockObject)) == -1){
        return 0;
    }
    return 1; 
}

int decreaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout){
    if(__decreaseLockObjectBlockTimeout(&(semaphore->lockObject), timeout) == -1){
        return 0;
    }
    return 1;
}

int getSemaphoreMaxval(struct Semaphore* semaphore){
    return __getLockMaxVal(&(semaphore->lockObject));
}
int getSemaphoreCurrentVal(struct Semaphore* semaphore){
    return __getLockVal(&(semaphore->lockObject));
}

int takeSemaphore(struct Semaphore* semaphore, unsigned waitTime){
    if (waitTime == MAXWAITTIME){
        increaseSemaphoreBlocking(semaphore);
        return 1;
    } else if (waitTime == 0){
        return increaseSemaphoreNonBlocking(semaphore);
    } else {
        return increaseSemaphoreBlockingTimeout(semaphore, waitTime);
    }
}

int releaseSemaphore(struct Semaphore* semaphore, unsigned waitTime){
    if (waitTime == MAXWAITTIME){
        decreaseSemaphoreBlocking(semaphore);
        return 1;
    } else if (waitTime == 0){
        return decreaseSemaphoreNonBlocking(semaphore);
    } else {
        return decreaseSemaphoreBlockingTimeout(semaphore, waitTime);
    }
}
