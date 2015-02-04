#ifndef BINARYMUTEX_H
#define BINARYMUTEX_H
/**
@file binaryMutex.h
@author J. Dirks

Creation, deletion and usage of binary mutexes

Binary mutex functions.
A binary mutex is anonymous: everyone can release it.
You cannot grab it twice: if you try to grab it a second time, you will need to wait for a release first
*/

#include "lockObject.h"


struct BinarySemaphore{
   struct LockObject lockObject; 
};

/**
Locks the binary mutex, blocks until the mutex is locked.

@param mutex The mutex you want to block.
*/
void lockBinarySemaphoreBlocking(struct BinarySemaphore* mutex);

/**
Tries to lock the binary mutex. If unsucsessfull, blocks until the mutex can be locked or timeout, whichever comes first.

@param mutex The mutex you want to block.
@param msWaitTime Maximum blocking time.

@return 1 if the mutex was sucsessfully locked, else 0.
*/
int lockBinarySemaphoreBlockWait(struct BinarySemaphore* mutex, unsigned msWaitTime);

/**
Attemps one time to lock the binary mutex.

@param mutex The mutex you want to lock

@return 1 if the mutex was sucsessfully locked, else 0.
*/
int lockBinarySemaphoreNoBlock(struct BinarySemaphore* mutex);

void releaseBinarySemaphore(struct BinarySemaphore* mutex);

void initBinarySemaphore(struct BinarySemaphore* mutex);

void cleanupBinarySemaphore(struct BinarySemaphore* mutex);

#endif //BINARYMUTEX_H
