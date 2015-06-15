//Handles the threadsafe calls and the waiting state
#ifndef LOCKOBJECT_H
#define LOCKOBJECT_H

#include "process.h"
#define MAXWAITTIME 0xFFFFFFFF

/**
    There is a quite fundamental difference between the lockobject and the semaphore from theoretical information schience.
    The obvious difference is that the lockobject can not be increased indefinitely.
    The less obvious differences are that the lockobject can also block on maxval to increase performance or readability in some consumer-producer problems.
    Dijkstra's semaphore only blocks on wait() (=try decrease). POSIX's sem_t will return an error when trying to increase beyond its bounds.
    This implementation can return an errorcode (-1) when increase or decrease is impossible (lock == maxval || lock == 0) and it can block when inc- or decrease is impossible.
    So this implementation is a bit more flexible, but can easaly be used to implement POSIX style sem_t's.
**/

/**
    This object serves as a primitive and should not be used directly. Rather, it should be wrapped into mutexes and semaphores before being used
**/

struct LockObject{
    unsigned lock;
    unsigned maxLockVal;
    struct Process* processWaitingQueueIncrease; //Processes waiting for the object being increased
    struct Process* processWaitingQueueDecrease; //Processes waiting for the object being decreased
};
//Init, cleanup
void __initLockObject(struct LockObject* object, int maxval);
void __cleanupLockObject(struct LockObject* object);

//All forms of in and decrease. Returnvals are the new value of the lock in case of success, -1 in case of failure. Blocking modify cannot fail. It can make your process starve.
//Block until increased
int __increaseLockObjectBlock(struct LockObject* object);
int __decreaseLockObjectBlock(struct LockObject* object);
//Try increase, return immediately
int __increaseLockObjectNoBlock(struct LockObject* object);
int __decreaseLockObjectNoBlock(struct LockObject* object);
//Try decrease for a finite amount of time
int __increaseLockObjectBlockTimeout(struct LockObject* object, unsigned msTimeout);
int __decreaseLockObjectBlockTimeout(struct LockObject* object, unsigned msTimeout);
//Not threadsafe: value might be wrong
int __getLockVal(struct LockObject* object);

int __getLockMaxVal(struct LockObject* object);
int __LockIsMaxVal(struct LockObject* object);
int __LockIsMinVal(struct LockObject* object);
#endif //LOCKOBJECT_H
