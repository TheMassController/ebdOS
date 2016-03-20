#include "mutex.h"
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

int mainProcessLocker(void){
    int retVal = initMutex(&mut);
    if (retVal !=0){
        errno = retVal;
        return -1;
    }
    if (createChildProcess(128, "MutPasser1", mutPasser, (void*)1000) == -1) return -1;
    if (createChildProcess(128, "MutPasser2", mutPasser, (void*)1500) == -1) return -1;
    if (createChildProcess(128, "MutPasser3", mutPasser, (void*)2500) == -1) return -1;
    return 0;

}

