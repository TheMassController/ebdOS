#include <errno.h>

#include "sysFutex.h"
#include "sysManagedLock.h"

int sysInitFutex(struct Futex* fut, struct Process* proc){
    return allocateManagedLock(&(fut->lockId), proc->pid);
}

int sysDestroyFutex(struct Futex* fut){
    return freeManagedLock(fut->lockId);
}

int sysFutexWait(struct Futex* fut, struct Process* proc){
    if (fut->atomicVal > 0) return EAGAIN;
    return waitForManagedLock(fut->lockId, proc);
}

int sysFutexPost(struct Futex* fut, struct Process** procPtr){
    return releaseManagedLock(fut->lockId, procPtr);
}

int sysFutexWaitTimeout(struct Futex* restrict fut, struct Process* restrict proc, struct SleepRequest* restrict sleepReq){
    if (fut->atomicVal > 0) return EAGAIN;
    return timedWaitForManagedLock(fut->lockId, proc, sleepReq);
}
