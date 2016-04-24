#include "mutex.h"
#include "string.h"
#include "sleep.h"
#include "sysCalls.h"
#include "uartstdio.h"
#include "errno.h"

struct Mutex mut;

static void mutPasser(void* initialDelay){
    int pid = getPid();
    sleepMS((int)initialDelay);
    while(1){
        lockMutex(&mut);
        UARTprintf("My pid is %d and I have a mutex!\n", pid);
        sleepS(1);
        unlockMutex(&mut);
        sleepS(1);
    }
}

static void mutPasserWait(void* maxWait){
    sleepMS(500);
    int pid = getPid();
    struct SleepRequest req = {
        .mSec = (uint32_t)maxWait
    };
    while(1){
        int retVal = lockMutexTimeout(&mut, &req);
        if (retVal != 0){
            UARTprintf("Oops, the retval was not 0. ERRNO: %d (%s)\n", retVal, strerror(retVal));
        } else{
            UARTprintf("My pid is %d and I have a mutex! (Im the waiter)\n", pid);
            sleepS(1);
            unlockMutex(&mut);
        }
    }
}

int mainProcessLocker(void){
    (void)(mutPasserWait);
    (void)(mutPasser);
    int retVal = initMutex(&mut);
    //lockMutex(&mut);
    if (retVal !=0){
        errno = retVal;
        return -1;
    }
    if (createChildProcess(256, "MutPasser1", mutPasser, (void*)1500) == -1) return -1;
    if (createChildProcess(256, "MutPasser2", mutPasser, (void*)2000) == -1) return -1;
    if (createChildProcess(256, "MutPasser3", mutPasser, (void*)3000) == -1) return -1;
    if (createChildProcess(256, "MutPasserW", mutPasserWait, (void*)1000) == -1) return -1;
    return 0;

}
