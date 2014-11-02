#ifndef MUTEX_H
#define MUTEX_H
//Mutex functions

struct Mutex{
    unsigned lock;
    unsigned ownerPid;
    struct Mutex* nextMutex;
};

typedef struct Mutex Mutex;

void lockMutexBlocking(Mutex* mutex);

//Returns 1 if successfull, 0 if not
int lockMutexBlockWait(Mutex* mutex, unsigned msWaitTime);

//Returns 1 if successfull, 0 if not
int lockMutexNoBlock(Mutex* mutex);

void releaseMutex(Mutex* mutex);

Mutex* createMutex(void);

void deleteMutex(Mutex* mutex);

#endif //MUTEX_H
