#include <stdint.h>                     // uint64_t
#include <stdlib.h>                     // NULL
#include <string.h>                     // strerror

#include <hw_nvic.h>                    // Macros related to the NVIC hardware
#include <hw_types.h>                   // Common types and macros for the TI libs
#include <uartstdio.h>                  // UART stdio declarations
#include <timer.h>                      // Function prototypes for the timer module
#include <hw_memmap.h>                  // Address of GPIO etc
#include <lm4f120h5qr.h>                // Hardware regs
#include <hw_types.h>                   // Contains the special types
#include <rom_map.h>                    // Call functions directly from the ROM if available
#include <rom.h>                        // Declare ROM addresses for rom funcs

#include "supervisorCall.h"             // Contains the macro's necessary for making a supervisor call
#include "process.h"                    // Contains information about the struct Process
#include "sleep.h"                      // Contains information about the struct SleepRequest
#include "systemClockManagement.h"      // Contains information and functions about the main clock
#include "coreUtils.h"                  // For testing if inside SVC interrupt
#include "spinlock.h"                   // For the spinlock
#include "systemClockManagement.h"      // Contains the function getCurrentSytemTimerValue
#ifdef DEBUG
#include <uartstdio.h>                  // Printfs etc.
#endif //DEBUG

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
    if (sleepList == NULL || sleepList->sleepObj.overflows > 0){
        ROM_TimerDisable(WTIMER0_BASE, TIMER_B);
    } else {
        ROM_TimerLoadSet(WTIMER0_BASE, TIMER_B, curValWTA);
        ROM_TimerMatchSet(WTIMER0_BASE, TIMER_B, sleepList->sleepObj.sleepUntil);
        ROM_TimerEnable(WTIMER0_BASE, TIMER_B);
    }
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
    //Usually called from kernel
    struct SleepingProcessStruct* sleepStruct = &(proc->sleepObj);
    /* The systemClock runs from max to min. So if we want to sleep for x time, we want to wait until reftime - x
     * First of all: we need the total amount of us we are going to sleep. This is the delta.
     * */
    uint64_t sleepDelta = sleepRequest->uSec + sleepRequest->mSec * 1000 + sleepRequest->sec * 1000000;
    /* So now we need to find the overflow count.
     * We basically remove the max count of the sysclock from the wakeupMoment and add 1 to the overflow until wakeupMoment <= sleepRequest->reftime
     */
    sleepStruct->overflows = 0;
    if (sleepDelta <= sleepRequest->refTime){
        sleepStruct->sleepUntil = sleepRequest->refTime - sleepDelta;
    } else {
        sleepDelta -= sleepRequest->refTime;
        sleepStruct->overflows = 1;
        while ( sleepDelta >= EBD_SYSCLOCKMAXVAL ){
            sleepDelta -= EBD_SYSCLOCKMAXVAL;
            sleepStruct->overflows++;
        }
        sleepStruct->sleepUntil = EBD_SYSCLOCKMAXVAL- sleepDelta;
    }
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
    for (struct Process* it = sleepList; it != NULL; it = it->nextProcess){
        if (it->sleepObj.overflows > 0){
            it->sleepObj.overflows--;
        }
    }
    return updateListAndInterrupt();
}
