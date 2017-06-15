#include <errno.h>                  // Contains the macro's for the E* variables
#include <hw_types.h>               // Common types and macros for the TI libs
#include <timer.h>                  // Function prototypes for the timer module
#include <hw_memmap.h>              // Address of GPIO etc

#include "waitModule.h"             // Function prototypes
#include "kernelPredefined.h"       // Centralizes resource counts
#include "abstrSysSleepFuncs.h"     // Contains information about the struct SleepRequest and related functions
#include "systemClockManagement.h"  // Contains the function getCurrentSytemTimerValue
#ifdef DEBUG
#include "uartstdio.h"
#include "kernUtils.h"
#include "core/inc/anonymousSpinlock.h"
#endif //DEBUG

struct WaitQueueElement{
    struct WaitQueueElement* nextElement;
    struct Process* proc;
    void (*remove)(struct Process*);
};

// This is in the BSS section, so required to be NULL on OS launch
static struct WaitQueueElement waitQueuePool[MAXTOTALPROCESSES];
static struct WaitQueueElement* waitQueueHead = NULL;
#ifdef DEBUG
static struct AnonymousSpinlock spinLock;
#endif //DEBUG

#ifdef DEBUG
static void unknownStateResponse(){
    UARTprintf("The waitmodule is now in an unknown state because a combination of two waitQueuePool or waitQueueHead altering functions is running\n");
    generateCrash();
}
#endif //DEBUG

// There should always be a free space, since no process can be waiting twice
static struct WaitQueueElement* getElementFromPool(void){
    static int cursor = 0;
    while(waitQueuePool[cursor].proc != NULL){
        cursor++;
        if (cursor == MAXTOTALPROCESSES) cursor = 0;
    }
    return &waitQueuePool[cursor];
}

static void releaseElementToPool(struct WaitQueueElement* we){
    we->proc = NULL;
}

static void updateListAndInterrupt(void){
    unsigned curValWTA = getSystemClockValue();
    // Start with cleaning out the current list
    while( waitQueueHead != NULL && waitQueueHead->proc->sleepObj.overflows == 0 && waitQueueHead->proc->sleepObj.sleepUntil >= curValWTA){
        waitQueueHead->remove(waitQueueHead->proc);
        struct WaitQueueElement* tmp = waitQueueHead->nextElement;
        releaseElementToPool(waitQueueHead);
        waitQueueHead = tmp;
    }
    // Configure the interrupt.
    if (waitQueueHead == NULL){
        setHalfWTimerInterrupt(0, WTIMER1_BASE, TIMER_B, curValWTA, 0);
    } else {
        int disable = waitQueueHead->proc->sleepObj.overflows > 0;
        setHalfWTimerInterrupt(!disable, WTIMER1_BASE, TIMER_B, curValWTA, waitQueueHead->proc->sleepObj.sleepUntil);
    }
}

static void addToWaitQueue(struct WaitQueueElement* wqe){
    // Sort the process into the wait list
    if ( waitQueueHead == NULL){
        waitQueueHead = wqe;
        waitQueueHead->nextElement = NULL;
    } else {
        // The item needs to go in between prev and cur
        struct WaitQueueElement* prev = NULL;
        struct WaitQueueElement* cur = waitQueueHead;
        // First part of search: sort into the correct amount of overflows
        for (; cur != NULL; cur = cur->nextElement){
            if (cur->proc->sleepObj.overflows >= wqe->proc->sleepObj.overflows) break;
            prev = cur;
        }
        // Then sort into the correct wakeup moment. Higher goes first
        for (; cur != NULL; cur = cur->nextElement){
            if (cur->proc->sleepObj.sleepUntil < wqe->proc->sleepObj.sleepUntil || cur->proc->sleepObj.overflows > wqe->proc->sleepObj.overflows){
                break;
            }
            prev = cur;
        }
        if (prev == NULL){
            wqe->nextElement = waitQueueHead;
            waitQueueHead = wqe;
        } else {
            prev->nextElement = wqe;
            wqe->nextElement = cur;
        }
    }
}

int addWaiter(void(*remove)(struct Process*), struct Process* proc, const struct SleepRequest* sleepReq){
#ifdef DEBUG
    if (tryLockAnonymousSpinlock(&spinLock) != 0) unknownStateResponse();
#endif //DEBUG
    translateSleepRequest(proc, sleepReq);
    if (proc->sleepObj.sleepUntil > getSystemClockValue()) return ETIMEDOUT;
    struct WaitQueueElement* we = getElementFromPool();
    we->remove = remove;
    we->proc = proc;
    addToWaitQueue(we);
    updateListAndInterrupt();
#ifdef DEBUG
    unlockAnonymousSpinlock(&spinLock);
#endif //DEBUG
    return 0;
}

int removeWaiter(struct Process* proc){
#ifdef DEBUG
    if (tryLockAnonymousSpinlock(&spinLock) != 0) unknownStateResponse();
#endif //DEBUG
    struct WaitQueueElement* cur = waitQueueHead;
    struct WaitQueueElement* prev = NULL;
    for(; cur != NULL; cur = cur->nextElement){
        if (cur->proc == proc){
            if (prev == NULL){
                waitQueueHead = waitQueueHead->nextElement;
            } else {
                prev->nextElement = cur->nextElement;
            }
            releaseElementToPool(cur);
            return 0;
        }
        prev = cur;
    }
#ifdef DEBUG
    unlockAnonymousSpinlock(&spinLock);
#endif //DEBUG
    return EINVAL;
}

struct Process* waitTimerTimeout(void){
#ifdef DEBUG
    if (tryLockAnonymousSpinlock(&spinLock) != 0) unknownStateResponse();
#endif //DEBUG
    updateListAndInterrupt();
#ifdef DEBUG
    unlockAnonymousSpinlock(&spinLock);
#endif //DEBUG
    return NULL;
}

struct Process* waitTimerSysTimerOverflow(void){
#ifdef DEBUG
    if (tryLockAnonymousSpinlock(&spinLock) != 0) unknownStateResponse();
#endif //DEBUG
    struct WaitQueueElement* prev = NULL;
    struct WaitQueueElement* cur = waitQueueHead;
    for (; cur != NULL; cur = cur->nextElement){
        if (cur->proc->sleepObj.overflows > 0){
            cur->proc->sleepObj.overflows--;
        } else {
            if (prev == NULL){
                waitQueueHead = waitQueueHead->nextElement;
            } else {
                prev->nextElement = cur->nextElement;
            }
            cur->remove(cur->proc);
            releaseElementToPool(cur);
        }
        prev = cur;
    }
    updateListAndInterrupt();
#ifdef DEBUG
    unlockAnonymousSpinlock(&spinLock);
#endif //DEBUG
    return NULL;
}
