//Handles the supervisor interrupt call
#include "hw_nvic.h"
#include "hw_types.h"
#include "uartstdio.h"
#include "timer.h"
#include "hw_memmap.h" //address of GPIO etc
#include "uartstdio.h"
#include "lm4f120h5qr.h" //Hardware regs
#include "hw_types.h" //Contains the special types
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include "process.h" 
#include "threadsafeCalls.h" 
#include "stdlib.h" 
#include "sysSleep.h"
#include "sleep.h"

extern struct Process* currentProcess;
extern struct Process* processesReady;
extern struct Process* sleepProcessList;
extern struct Process* kernel;
extern struct Process* newProcess;

static struct SleepingProcessStruct* sleepProcessListHead = NULL;
static struct SleepingProcessStruct* nextToWakeUp = NULL;

void rescheduleImmediately(void){
    NVIC_INT_CTRL_R |= (1<<26); //Set the SysTick to pending (Datasheet pp 156)
    NVIC_ST_CURRENT_R = 0; //Clear the register by writing to it with any value (datasheet pp 118, 136)
}


//----- Functions related to the moving of functions from one queue to another

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

//Readylist related
int processInReadyList(struct Process* process){
    return processInList(processesReady, process);
}

void addProcessToReady(struct Process* process){
    if (!processInList(processesReady, process)){
        processesReady = sortProcessIntoList(processesReady, process);
    }
}

void removeProcessFromReady(struct Process* process){
    removeProcessFromList(processesReady, process);
}

//Sleep related
void wakeupProcess(struct SleepingProcessStruct* ptr){
    if (ptr->process->state & STATE_WAIT){
        if (ptr->process->state & STATE_LOCKED){
            removeProcessFromList(((struct SingleLockObject*)ptr->process->blockAddress)->processWaitingQueue, ptr->process);
        }
        if (ptr->process->state & STATE_INC_WAIT){
            removeProcessFromList(((struct MultiLockObject*)ptr->process->blockAddress)->processWaitingQueueIncrease, ptr->process);
        }
        if (ptr->process->state & STATE_DEC_WAIT){
            removeProcessFromList(((struct MultiLockObject*)ptr->process->blockAddress)->processWaitingQueueDecrease, ptr->process);
        }
    }
    ptr->process->state = STATE_READY;
    addProcessToReady(ptr->process);
}   

void setSleepTimerWB(void){
    while (sleepProcessListHead != nextToWakeUp){
        if (sleepProcessListHead == NULL){
            ROM_TimerDisable(WTIMER0_BASE, TIMER_B);
            nextToWakeUp = NULL;
        } else if (sleepProcessListHead->overflows != 0){
            if (nextToWakeUp != NULL){
                ROM_TimerDisable(WTIMER0_BASE, TIMER_B);
                nextToWakeUp = NULL;
            }       
            break;
        } else {
            unsigned curValWTA = getCurrentSleepTimerValue();
            if (curValWTA <= sleepProcessListHead->sleepUntil){
                wakeupProcess(sleepProcessListHead);
                sleepProcessListHead = sleepProcessListHead->nextPtr;
            } else {
                nextToWakeUp = sleepProcessListHead;
                ROM_TimerLoadSet(WTIMER0_BASE, TIMER_B, curValWTA);
                ROM_TimerMatchSet(WTIMER0_BASE, TIMER_B, sleepProcessListHead->sleepUntil);
                ROM_TimerEnable(WTIMER0_BASE, TIMER_B); 
            }
        }
    }    
}

void wakeupFromWBInterrupt(void){
    wakeupProcess(nextToWakeUp);
    sleepProcessListHead = sleepProcessListHead->nextPtr;
    nextToWakeUp = NULL;
    setSleepTimerWB();
}


void addSleeperToList(struct SleepingProcessStruct* ptr){
    struct SleepingProcessStruct* current = sleepProcessListHead;
    struct SleepingProcessStruct* previous = NULL;
    while(current != NULL && current->overflows <= ptr->overflows && current->sleepUntil > ptr->sleepUntil){
        previous = current;
        current = current->nextPtr;
    }
    if (previous == NULL){
        ptr->nextPtr = current;
        sleepProcessListHead = ptr;
        setSleepTimerWB();
    } else {
        previous->nextPtr = ptr;
        ptr->nextPtr = current;
    }
}

void removeSleeperFromList(struct Process* proc){
    struct SleepingProcessStruct* current = sleepProcessListHead;
    struct SleepingProcessStruct* previous = NULL;
    while(current != NULL && current->process != proc){
        previous = current;
        current = current->nextPtr;
    }
    if (current != NULL){
        if (previous == NULL){
            sleepProcessListHead = current->nextPtr;
            setSleepTimerWB();
        } else {
            previous->nextPtr = current->nextPtr;
        }
    }
}

//LockQueue = mutex related
struct Process* popFromLockQueue(struct Process* listHead){
    if (listHead != NULL){
        struct Process* item = listHead;
        if (item->state & STATE_SLEEP){
            removeSleeperFromList(item); 
        }
        item->state = 0;
        item->blockAddress = NULL;
        listHead = listHead->nextProcess;
        addProcessToReady(item);
        rescheduleImmediately();
    }
    return listHead;
}


//----------------

void addNewProcess(void){
    if (newProcess != NULL){
        addProcessToReady(newProcess);
        newProcess = NULL;
    }    
}

void processBlockedSingleLock(void){
    SingleLockObject* waitObject = (SingleLockObject*)currentProcess->blockAddress;
    if (!waitObject->lock) return;
    removeProcessFromReady(currentProcess);
    waitObject->processWaitingQueue = sortProcessIntoList(waitObject->processWaitingQueue, currentProcess);
    rescheduleImmediately();
}

void singleLockReleased(void){
    //The released mutex is in the currentProcess->blockAddress var
    SingleLockObject* waitObject = (SingleLockObject*)currentProcess->blockAddress;
    waitObject->processWaitingQueue = popFromLockQueue(waitObject->processWaitingQueue);
    currentProcess->blockAddress = NULL;
}

void multiLockIncrease(void){
    MultiLockObject* multiLock = (MultiLockObject*)currentProcess->blockAddress;
    multiLock->processWaitingQueueIncrease = popFromLockQueue(multiLock->processWaitingQueueIncrease);
    currentProcess->blockAddress = NULL;
}

void multiLockDecrease(void){    
    MultiLockObject* multiLock = (MultiLockObject*)currentProcess->blockAddress;
    multiLock->processWaitingQueueDecrease = popFromLockQueue(multiLock->processWaitingQueueDecrease);
    currentProcess->blockAddress = NULL;
}

void multiLockIncreaseBlock(void){
    MultiLockObject* multiLock = (MultiLockObject*)currentProcess->blockAddress;
    if (multiLock->lock == 0) return;
    removeProcessFromReady(currentProcess);
    multiLock->processWaitingQueueIncrease = sortProcessIntoList(multiLock->processWaitingQueueIncrease, currentProcess);
    rescheduleImmediately();
}

void multiLockDecreaseBlock(void){
    MultiLockObject* multiLock = (MultiLockObject*)currentProcess->blockAddress;
    if (multiLock->lock < multiLock->maxLockVal) return;
    removeProcessFromReady(currentProcess);
    multiLock->processWaitingQueueDecrease = sortProcessIntoList(multiLock->processWaitingQueueDecrease, currentProcess);
    rescheduleImmediately();
}

void setKernelPrioMax(void){
   kernel->priority = 255; 
}

void fallAsleep(void){
    removeProcessFromReady(currentProcess);
    addSleeperToList((struct SleepingProcessStruct*)currentProcess->sleepObjAddress);
    currentProcess->state |= STATE_SLEEP;
    rescheduleImmediately();
}

void fallAsleepNoBlock(void){
    addSleeperToList((struct SleepingProcessStruct*)currentProcess->sleepObjAddress);
}

#ifdef DEBUG
void sayHi(void){
    UARTprintf("Hi from your favorite supervisor!\r\n");
}
#endif //DEBUG

//This function responds to an interrupt that can be generated at any runlevel.
void svcHandler_main(char reqCode){
    switch(reqCode){
        case 0:
            rescheduleImmediately();
            break;
        case 1:
            processBlockedSingleLock();
            break;
        case 2:
            singleLockReleased();
            break;
        case 3:
            multiLockIncrease();
            break;
        case 4:
            multiLockDecrease();
            break;
        case 5:
            multiLockIncreaseBlock();
            break;
        case 6:
            multiLockDecreaseBlock();
            break;
        case 7:
            setKernelPrioMax();
            break;
        case 8:
            fallAsleep();
            break;
        case 9:
            fallAsleepNoBlock();
            break;
        case 10:
            wakeupFromWBInterrupt();
            break;
        case 11:
            addNewProcess();
            break;
#ifdef DEBUG
        case 255:
            sayHi();
            break;
#endif //DEBUG
        default:
            UARTprintf("Supervisor call handler: unknown code %d\r\n",reqCode);
            break;
    }
}

