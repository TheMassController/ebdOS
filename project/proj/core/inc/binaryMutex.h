#ifndef BINARYMUTEX_H
#define BINARYMUTEX_H

//Binary mutex functions.
//A binary mutex is anonymous: everyone can release it.
//You cannot grab it twice: if you try to grab it a second time, you will need to wait for a release first

struct BinaryMutex{
    unsigned lock;
    struct BinaryMutex* nextBinaryMutex;
};

typedef struct BinaryMutex BinaryMutex;

void lockBinaryMutexBlocking(BinaryMutex* mutex);

//Returns 1 if successfull, 0 if not
int lockBinaryMutexBlockWait(BinaryMutex* mutex, unsigned msWaitTime);

//Returns 1 if successfull, 0 if not
int lockBinaryMutexNoBlock(BinaryMutex* mutex);

void releaseBinaryMutex(BinaryMutex* mutex);

BinaryMutex* createBinaryMutex(void);

void deleteBinaryMutex(BinaryMutex* mutex);

#endif //BINARYMUTEX_H
