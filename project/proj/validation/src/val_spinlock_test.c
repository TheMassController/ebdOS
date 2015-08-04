#include "spinlock.h"
#include "sleep.h"
#include <uartstdio.h>
#include <string.h>

extern struct Process* currentProcess;

struct Spinlock lSpinlock;
struct Spinlock tLSpinlock;

void tryLockPasser(void){
    struct Spinlock* spin = &tLSpinlock;
    while(1){
        int errorcode = tryLockSpinlock(spin);
        if (errorcode == 0){
            UARTprintf("My name is %s and I have the try-spinlock\n", currentProcess->name);
            sleepS(1);
            errorcode = unlockSpinlock(spin);
            if (errorcode != 0){
                UARTprintf("Problem while releasing spinlock: %a (process name: %s)\n", strerror(errorcode), currentProcess->name);
            } else {
                sleepS(1);
            }
        } else {
            UARTprintf("My name is %s and I did not get the the try-spinlock. Error: %s (code: %d)\n", currentProcess->name, strerror(errorcode), errorcode);
            sleepS(1);
        }
    }
}

void lockPasser(void){
    struct Spinlock* spin = &lSpinlock;
    while(1){
        int errorcode = lockSpinlock(spin);
        if (errorcode == 0){
            UARTprintf("My name is %s and I have the lock-spinlock\n", currentProcess->name);
            sleepS(1);
            errorcode = unlockSpinlock(spin);
            if (errorcode != 0){
                UARTprintf("Problem while releasing spinlock: %s (process name: %s)\n", strerror(errorcode), currentProcess->name);
            } else {
                sleepS(1);
            }
        } else {
            UARTprintf("My name is %s and I did not get the the lock-spinlock, this should not be possible! Error: \n", currentProcess->name, strerror(errorcode));
            sleepS(1);
        }
    }
}

void spinlocktestMain(void){
    int retcode[2];
    retcode[0] = initSpinlock(&lSpinlock);
    retcode[1] = initSpinlock(&tLSpinlock);
    for (int i = 0; i < 2; ++i){
        if (retcode[i] != 0){
            UARTprintf("Failed errorcode on %d, errocode: %d, translates to %s\n", i, retcode[i], strerror(retcode[i]));
        }
    }
    while(1){
        sleepS(100);
    }
}
