#ifndef SEMPAHORE_H
#define SEMAPHORE_H

#include "threadsafeCalls.h"

struct Semaphore{
    struct MultiLockObject* multiLockObject;
};

struct Semaphore* createSemaphore(int maxval);
void deleteSemaphore(struct Semaphore* semaphore);

void increaseSemaphoreBlocking(struct Semaphore* semaphore);
int increaseSemaphoreNonBlocking(struct Semaphore* semaphore);
int increaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout);

void decreaseSemaphoreBlocking(struct Semaphore* semaphore);
int decreaseSemaphoreNonBlocking(struct Semaphore* semaphore);
int decreaseSemaphoreBlockingTimeout(struct Semaphore* semaphore, unsigned timeout);

int getSemaphoreMaxval(struct Semaphore* semaphore);
int getSemaphoreCurrentVal(struct Semaphore* semaphore);
#endif //SEMPAHORE_H
