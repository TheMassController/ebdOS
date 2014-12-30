//Handles the supervisor interrupt call
#include "uartstdio.h"
#include "lm4f120h5qr.h" //Hardware regs
#include "hw_types.h" //Contains the special types
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include "process.h" 
#include "threadsafeCalls.h" 
#include "stdlib.h" 
#include "utils.h"
#include "sysSleep.h"

extern struct Process* currentProcess;
extern struct Process* processesReady;
extern struct Process* sleepProcessList;
extern struct Process* kernel;

void rescheduleImmediately(void){
    NVIC_INT_CTRL_R |= (1<<26); //Set the SysTick to pending (Datasheet pp 156)
    NVIC_ST_CURRENT_R = 0; //Clear the register by writing to it with any value (datasheet pp 118, 136)
}

struct Process* popFromLockQueue(struct Process* listHead){
    if (listHead != NULL){
        struct Process* item = listHead;
        if (item->state & STATE_SLEEP){
            __removeSleeperFromList(item); 
        }
        item->state = 0;
        item->blockAddress = NULL;
        listHead = listHead->nextProcess;
        __addProcessToReady(item);
        rescheduleImmediately();
    }
    return listHead;
}

void processBlockedSingleLock(void){
    SingleLockObject* waitObject = (SingleLockObject*)currentProcess->blockAddress;
    if (!waitObject->lock) return;
    __removeProcessFromReady(currentProcess);
    waitObject->processWaitingQueue = __sortProcessIntoList(waitObject->processWaitingQueue, currentProcess);
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
    __removeProcessFromReady(currentProcess);
    multiLock->processWaitingQueueIncrease = __sortProcessIntoList(multiLock->processWaitingQueueIncrease, currentProcess);
    rescheduleImmediately();
}

void multiLockDecreaseBlock(void){
    MultiLockObject* multiLock = (MultiLockObject*)currentProcess->blockAddress;
    if (multiLock->lock < multiLock->maxLockVal) return;
    __removeProcessFromReady(currentProcess);
    multiLock->processWaitingQueueDecrease = __sortProcessIntoList(multiLock->processWaitingQueueDecrease, currentProcess);
    rescheduleImmediately();
}

void setKernelPrioMax(void){
   kernel->priority = 255; 
}

void fallAsleep(void){
    __addSleeperToList((struct SleepingProcessStruct*)currentProcess->sleepObjAddress);
    rescheduleImmediately();
}

void fallAsleepNoBlock(void){
    __addSleeperToList((struct SleepingProcessStruct*)currentProcess->sleepObjAddress);
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

