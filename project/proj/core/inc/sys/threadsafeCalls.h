//Handles the threadsafe calls and the waiting state
#ifndef THREADSAFECALLS_H
#define THREADSAFECALLS_H

#include "process.h" 

struct SingleLockObject{
    unsigned lock;
    struct Process* processWaitingQueue;
};

typedef struct SingleLockObject SingleLockObject;

SingleLockObject* __createSingleLockObject(void);
//This function might be able to generate a kernel panic
void __deleteSingleLockObject(SingleLockObject* object);

int __lockObjectNoblock(SingleLockObject* object);
void __lockObjectBlock(SingleLockObject* object);
int __lockObjectBlockTimeout(SingleLockObject* object, unsigned timeout);
void __releaseObject(SingleLockObject* object);

int __singleLockObjectIsLocked(SingleLockObject* object);

//TODO semaphore functions
#endif //THREADSAFECALLS_H
