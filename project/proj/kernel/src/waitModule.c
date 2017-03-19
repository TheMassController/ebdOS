#include <errno.h>                  // Contains the macro's for the E* variables
#include <hw_types.h>               // Common types and macros for the TI libs
#include <timer.h>                  // Function prototypes for the timer module
#include <hw_memmap.h>              // Address of GPIO etc

#include "waitModule.h"             // Function prototypes
#include "kernelPredefined.h"       // Centralizes resource counts
#include "abstrSysSleepFuncs.h"     // Contains information about the struct SleepRequest and related functions
#include "systemClockManagement.h"  // Contains the function getCurrentSytemTimerValue

struct WaitQueueElement{
    struct WaitQueueElement* nextElement;
    struct Process* proc;
    void (*remove)(struct Process*);
};

// This is in the BSS section, so required to be NULL on OS launch
static struct WaitQueueElement waitQueuePool[MAXTOTALPROCESSES];
static struct WaitQueueElement* waitQueueHead = NULL;

// There should always be a free space, since no process can be waiting twice
static struct WaitQueueElement* getElementFromPool(void){
    static int cursor = 0;
    while(waitQueuePool[cursor++].proc != NULL){
        cursor %= MAXTOTALPROCESSES;
    }
    return &waitQueuePool[cursor-1];
}

static void releaseElementToPool(struct WaitQueueElement* we){
    we->proc = NULL;
}

static void updateListAndInterrupt(void){
    unsigned curValWTA = getSystemClockValue();
    struct WaitQueueElement* ref = waitQueueHead;
    // Start with cleaning out the current list
    while( waitQueueHead != NULL && waitQueueHead->proc->sleepObj.overflows == 0 && waitQueueHead->proc->sleepObj.sleepUntil >= curValWTA){
        waitQueueHead->remove(waitQueueHead->proc);
        releaseElementToPool(waitQueueHead);
        waitQueueHead = waitQueueHead->nextElement;
    }
    // Configure the interrupt.
    if (waitQueueHead != ref) {
        int disable = waitQueueHead == NULL || waitQueueHead->proc->sleepObj.overflows > 0;
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
    translateSleepRequest(proc, sleepReq);
    if (proc->sleepObj.sleepUntil > getSystemClockValue()) return ETIMEDOUT;
    struct WaitQueueElement* we = getElementFromPool();
    we->remove = remove;
    we->proc = proc;
    addToWaitQueue(we);
    updateListAndInterrupt();
    return 0;
}

int removeWaiter(struct Process* proc){
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
    return EINVAL;
}

struct Process* waitTimerTimeout(void){
    updateListAndInterrupt();
    return NULL;
}

struct Process* waitTimerSysTimerOverflow(void){
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
    return NULL;
}
