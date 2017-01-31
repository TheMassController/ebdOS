#include "core/inc/mutex.h"
#include "string.h"
#include "core/inc/sleep.h"
#include "core/inc/sysCalls.h"
#include "uartstdio.h"
#include "errno.h"

#include <assert.h>

struct Mutex mut;

static void mutPasser(void* initialDelay){
    int pid = getPid();
    assert(sleepMS((int)initialDelay) == 0);
    while(1){
        assert(lockMutex(&mut) == 0);
        UARTprintf("My pid is %d and I have a mutex!\n", pid);
        assert(sleepS(1) == 0);
        assert(unlockMutex(&mut) == 0);
        assert(sleepS(1) == 0);
    }
}

static void mutPasserWait(void* maxWait){
    assert(sleepMS(500) == 0);
    int pid = getPid();
    struct SleepRequest req = {
        .mSec = (uint32_t)maxWait
    };
    while(1){
        int retval = lockMutexTimeout(&mut, &req);
        assert(retval == 0 || retval == ETIMEDOUT);
        if (retval == ETIMEDOUT){
            UARTprintf("Pid %d did not get the mutex (mutexwaiter)\n", pid);
        } else {
            UARTprintf("My pid is %d and I have a mutex! (Im the waiter)\n", pid);
            assert(sleepS(1) == 0);
            assert(unlockMutex(&mut) == 0);
        }
    }
}

int mainProcessLocker(void){
    assert(initMutex(&mut) == 0);
    assert(createChildProcess(256, "MutPasser1", mutPasser, (void*)1500) != -1);
    assert(createChildProcess(256, "MutPasser2", mutPasser, (void*)2000) != -1);
    assert(createChildProcess(256, "MutPasser3", mutPasser, (void*)3000) != -1);
    assert(createChildProcess(256, "MutPasserW", mutPasserWait, (void*)1000) != -1);
    return 0;

}
