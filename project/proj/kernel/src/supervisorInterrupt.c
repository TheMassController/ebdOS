// Handles the supervisor interrupt call
#include <hw_nvic.h>                // Macros related to the NVIC hardware
#include <hw_types.h>               // Common types and macros for the TI libs
#include <uartstdio.h>              // UART stdio declarations
#include <timer.h>                  // Function prototypes for the timer module
#include <hw_memmap.h>              // Address of GPIO etc
#include <lm4f120h5qr.h>            // Hardware regs
#include <hw_types.h>               // Contains the special types
#include <rom_map.h>                // Call functions directly from the ROM if available
#include <rom.h>                    // Declare ROM addresses for rom funcs
#include <stdlib.h>                 // Contains C defs like NULL

#include "process.h"                // Declares the OS's process structs and funcs
#include "lockObject.h"             // Declarations for the lockobjects
#include "supervisorCall.h"         // Supplies the SVC commands
#include "scheduler.h"              // All functions related to the scheduler
#include "kernMaintenanceQueue.h"   // The kernel maintenaince queue
#include "kernUtils.h"              // To escalate to NMI
#include "kernEventNotifier.h"      // To check if there are no more events waiting for the kernel.

static struct Process* kernel                               = &kernelStruct;
//TODO depricate: Futex! Well, this should become a kernel thing.
void* volatile intrBlockObject;

volatile int kernelIsActive = 1;

//----- Functions related to the moving of functions from one queue to another

static void activateKernel(void){
    if (!kernelIsActive){
        addProcessToScheduler(kernel);
        kernelIsActive = 1;
    }
}

static void suspendKernel(void){
    if (kernelIsActive){
        removeProcessFromScheduler(kernel);
        kernelIsActive = 0;
    }
}

//Common
int processInList(struct Process* listHead, struct Process* proc){
    while (listHead != NULL){
        if (listHead == proc) return 1;
        listHead = listHead->nextProcess;
    }
    return 0;
}

struct Process* sortProcessIntoList(struct Process* listHead, struct Process* item){
    struct Process* current = listHead;
    struct Process* previous = NULL;
    while (current != NULL && current->priority >= item->priority){
        previous = current;
        current = current->nextProcess;
    }
    //Needs to go between previous and current, unless previous is NULL. Then it becomes the new HEAD
    if (previous == NULL){
        item->nextProcess = current;
        listHead = item;
    } else {
        previous->nextProcess = item;
        item->nextProcess = current;
    }
    return listHead;
}

struct Process* appendProcessToList(struct Process* listHead, struct Process* item){
    if (listHead == NULL){
        item->nextProcess = NULL;
        return item;
    }
    struct Process* current = listHead;
    for (; current->nextProcess != NULL; current = current->nextProcess);
    current->nextProcess = item;
    item->nextProcess = NULL;
    return listHead;
}

struct Process* removeProcessFromList(struct Process* listHead, struct Process* item){
    struct Process* current = listHead;
    struct Process* previous = NULL;
    while (current != NULL && current != item){
        previous = current;
        current = current->nextProcess;
    }
    //If current is NULL, then it was not in the list
    //If previous is NULL, then it is the head of the list
    if (current != NULL){
        if (previous == NULL){
            listHead = current->nextProcess;
        } else {
            previous->nextProcess = current->nextProcess;
        }

    }
    return listHead;
}

//----------------

struct Process* popFromLockQueue(struct Process* listHead){
    if (listHead != NULL){
        //Fully ignore the fact that the process might also be sleeping.
        //This would indicate a block and wait and we only want this process to stop sleeping (waiting) when it has the mutex
        //So the process itself will check wether or not it is still "sleeping"
        //Sleeping is an extension module to blocking
        struct Process* item = listHead;
        item->state |= STATE_WAIT;
        item->state ^= STATE_WAIT;
        item->blockAddress = NULL;
        listHead = listHead->nextProcess;
        addProcessToScheduler(item);
    }
    return listHead;
}

//Used to signal increase/decrease
void lockObjectModified(const char increase){
    struct Process* curProc = getCurrentProcess();
    struct LockObject* lockObject = (struct LockObject*)curProc->blockAddress;
    if (increase){
        lockObject->processWaitingQueueIncrease = popFromLockQueue(lockObject->processWaitingQueueIncrease);
    } else {
        lockObject->processWaitingQueueDecrease = popFromLockQueue(lockObject->processWaitingQueueDecrease);
    }
    curProc->blockAddress = NULL;
}

void lockObjectModifiedIntr(const char increase){
    struct LockObject* volatile lockObject = intrBlockObject;
    if (increase){
        lockObject->processWaitingQueueIncrease = popFromLockQueue(lockObject->processWaitingQueueIncrease);
    } else {
        lockObject->processWaitingQueueDecrease = popFromLockQueue(lockObject->processWaitingQueueDecrease);
    }
}

/*
 * Returns 1 if successful
 */
int tryAddLockQueue(const char increase){
    struct Process* curProc = getCurrentProcess();
    struct LockObject* lockObject = (struct LockObject*)curProc->blockAddress;
    if (increase){
        if (lockObject->lock != 0) return 0;
        removeProcessFromScheduler(curProc);
        lockObject->processWaitingQueueIncrease = appendProcessToList(lockObject->processWaitingQueueIncrease, curProc);
    } else {
        if (lockObject->lock < lockObject->maxLockVal) return 0;
        removeProcessFromScheduler(curProc);
        lockObject->processWaitingQueueDecrease = appendProcessToList(lockObject->processWaitingQueueDecrease, curProc);
    }
    return 1;
}

void lockObjectBlock(const char increase) {
    struct Process* curProc = getCurrentProcess();
    if (tryAddLockQueue(increase)){
        if (increase) {
            curProc->state |= STATE_INC_WAIT;
        } else {
            curProc->state |= STATE_DEC_WAIT;
        }
    }
}

static void currentProcessRequestsService(void){
    struct Process* curProc = popCurrentProcess();
    curProc->state = STATE_WAIT;
    passProcessToKernel(curProc);
    activateKernel();
}

static void kernelIsDoneServing(void){
    struct Process* tempPtr = kernRetQueuePop();
    while(tempPtr != NULL){
        tempPtr->state = STATE_READY;
        addProcessToScheduler(tempPtr);
        tempPtr = kernRetQueuePop();
    }
    if(KernelProcessBufferIsEmpty() && kernBufferIsEmpty()){
        suspendKernel();
    }
}

#ifdef DEBUG
static void sayHi(void){
    UARTprintf("Hi from your favorite supervisor!\r\n");
}
#endif //DEBUG

// This function responds to an interrupt that can be generated at any runlevel.
// Handlermode is somewhere near equal to being in an interrupt.
void svcHandler_main(const char reqCode, const unsigned fromHandlerMode){
    switch(reqCode){
        case SVC_yield:
            preemptCurrentProcess();
            break;
        case SVC_multiObjectIncrease:
            if (fromHandlerMode) lockObjectModifiedIntr(1);
            else lockObjectModified(1);
            break;
        case SVC_multiObjectDecrease:
            if (fromHandlerMode) lockObjectModifiedIntr(0);
            else lockObjectModified(0);
            break;
        case SVC_multiObjectWaitForIncrease:
            if (!fromHandlerMode) lockObjectBlock(1);
            break;
        case SVC_multiObjectWaitForDecrease:
            if (!fromHandlerMode) lockObjectBlock(0);
            break;
        case SVC_wakeupKernel:
            activateKernel();
            break;
        case SVC_serviceRequired:
            currentProcessRequestsService();
            break;
        case SVC_serviced:
            kernelIsDoneServing();
            break;
#ifdef DEBUG
        case SVC_test:
            sayHi();
            break;
#endif //DEBUG
        default:
            UARTprintf("Supervisor call handler: unknown code %d\r\n",reqCode);
            break;
    }
}
