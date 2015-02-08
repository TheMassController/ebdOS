#ifndef SEMPAHORE_H
#define SEMAPHORE_H

#include "lockObject.h"

struct Semaphore {
    struct LockObject lockObject;
};

void initSemaphore(struct Semaphore* semaphore, int maxval);
void cleanupSemaphore(struct Semaphore* semaphore);

void increaseSemaphoreBlocking(struct Semaphore* semaphore);
int increaseSemaphoreNonBlocking(struct Semaphore* semaphore);
int increaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout);

void decreaseSemaphoreBlocking(struct Semaphore* semaphore);
int decreaseSemaphoreNonBlocking(struct Semaphore* semaphore);
int decreaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout);

int getSemaphoreMaxval(struct Semaphore* semaphore);
int getSemaphoreCurrentVal(struct Semaphore* semaphore);

int takeSemaphore(struct Semaphore* semaphore, unsigned waitTime);
int releaseSemaphore(struct Semaphore* semaphore, unsigned waitTime);
#endif //SEMPAHORE_H
