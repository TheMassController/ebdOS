#ifndef SEMPAHORE_H
#define SEMAPHORE_H

#include "threadsafeCalls.h"

struct Semaphore{
    struct MultiLockObject* multiLockObject;
};

typedef struct Semaphore Semaphore;

Semaphore* createSemaphore(int maxval);
void deleteSemaphore(Semaphore* semaphore);

void increaseSemaphoreBlocking(Semaphore* semaphore);
int increaseSemaphoreNonBlocking(Semaphore* semaphore);
int increaseSemaphoreBlockingTimeout(Semaphore* semaphore, unsigned timeout);

void decreaseSemaphoreBlocking(Semaphore* semaphore);
int decreaseSemaphoreNonBlocking(Semaphore* semaphore);
int decreaseSemaphoreBlockingTimeout(Semaphore* semaphore, unsigned timeout);

int getSemaphoreMaxval(Semaphore* semaphore);
int getSemaphoreCurrentVal(Semaphore* semaphore);
#endif //SEMPAHORE_H
