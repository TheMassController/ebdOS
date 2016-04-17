#include <stdlib.h>                     // NULL
#include <hw_types.h>                   // Common types and macros for the TI libs
#include <timer.h>                      // Function prototypes for the timer module
#include <hw_memmap.h>                  // Address of GPIO etc

#include "process.h"                    // Contains information about the struct Process
#include "abstrSysSleepFuncs.h"         // Contains information about the struct SleepRequest and related functions
#include "systemClockManagement.h"      // Contains the function getCurrentSytemTimerValue

static struct Process* sleepList = NULL;

static struct Process* updateListAndInterrupt(void){
    unsigned curValWTA = getSystemClockValue();
    // Start with cleaning out the current list: all processes that should have waken up by now are awakened.
    struct Process* retList = NULL;
    struct Process* it = NULL;
    while( sleepList != NULL && sleepList->sleepObj.overflows == 0 && sleepList->sleepObj.sleepUntil >= curValWTA){
        if ( retList == NULL ){
            retList = sleepList;
            sleepList = sleepList->nextProcess;
            retList->nextProcess = NULL;
            it = retList;
        } else {
            it->nextProcess = sleepList;
            it = sleepList;
            sleepList = sleepList->nextProcess;
            it->nextProcess = NULL;
        }
    }
    // Configure the interrupt.
    int disable = sleepList == NULL || sleepList->sleepObj.overflows > 0;
    setHalfWTimerInterrupt(!disable, WTIMER0_BASE, TIMER_B, curValWTA, sleepList->sleepObj.sleepUntil);
    return retList;
}

static struct Process* internalAddSleeper(struct Process* proc){
    // Sort the process into the sleeplist
    if (sleepList == NULL){
        sleepList = proc;
        proc->nextProcess = NULL;
    } else {
        // The item needs to go in between prev and cur
        struct Process* prevNode = NULL;
        struct Process* curNode = sleepList;
        // First part of search: sort into the correct amount of overflows
         for (; curNode != NULL; curNode = curNode->nextProcess){
             if ((curNode->sleepObj).overflows >= (proc->sleepObj).overflows){
                 break;
             }
            prevNode = curNode;
         }
         // Then sort into the correct wakeup moment. Higher goes first
         for (; curNode != NULL; curNode = curNode->nextProcess){
             if ((curNode->sleepObj).sleepUntil < (proc->sleepObj).sleepUntil){
                 break;
             }
             prevNode = curNode;
         }
         if (prevNode == NULL){
             sleepList = proc;
             proc->nextProcess = curNode;
         } else {
             prevNode->nextProcess = proc;
             proc->nextProcess = curNode;
         }
    }
    return updateListAndInterrupt();
}

struct Process* addSleeper(struct Process* proc, const struct SleepRequest* sleepRequest){
    translateSleepRequest(proc, sleepRequest);
    return internalAddSleeper(proc);
}

struct Process* removeSleeper(struct Process* proc){
    // It is assumed that proc is in the sleepList.
    if (proc == sleepList){
        sleepList = sleepList->nextProcess;
        proc->nextProcess = updateListAndInterrupt();
    } else {
        struct Process* prev = sleepList;
        struct Process* cur = sleepList->nextProcess;
        while( cur != NULL){
            if (cur == proc){
                prev->nextProcess = cur->nextProcess;
                proc->nextProcess = updateListAndInterrupt();
                break;
            }
            prev = cur;
            cur = cur->nextProcess;
        }
    }
    return proc;
}

struct Process* refreshSleeplist(void){
    return updateListAndInterrupt();
}

struct Process* sleepHandleSysTimerOverflow(void){
    struct Process* ret = NULL;
    struct Process* in = NULL;
    struct Process* it = sleepList;
    if (it->sleepObj.overflows == 0){
        ret = it;
        in = it;
        it = it->nextProcess;
        while (it != NULL && it->sleepObj.overflows == 0){
            it = it->nextProcess;
            in = it;
        }
    }
    sleepList = it;
    while (it != NULL){
        if (it->sleepObj.overflows > 0){
            it->sleepObj.overflows--;
        }
        it = it->nextProcess;
    }
    if (ret != NULL) {
        in->nextProcess = updateListAndInterrupt();
    } else {
        ret = updateListAndInterrupt();
    }
    return ret;
}
