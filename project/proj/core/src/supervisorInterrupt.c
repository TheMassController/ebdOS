//Handles the supervisor interrupt call
#include "uartstdio.h"
#include "lm4f120h5qr.h" //Hardware regs
#include "hw_types.h" //Contains the special types
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include "process.h" 
#include "threadsafeCalls.h" 
#include "stdlib.h" 


extern struct Process* currentProcess;
extern struct Process* processesReady;
extern struct Process* sleepProcessList;

void rescheduleImmediately(void){
    NVIC_INT_CTRL_R |= (1<<26); //Set the SysTick to pending (Datasheet pp 156)
    NVIC_ST_CURRENT_R = 0; //Clear the register by writing to it with any value (datasheet pp 118, 136)
}

void processBlockedSingleLock(void){
    //Remove the currentProcess from the list of active processes
    struct Process* prevProc = processesReady;
    for (; prevProc->nextProcess != currentProcess; prevProc = prevProc->nextProcess);
    prevProc->nextProcess = currentProcess->nextProcess;
    //Add it to the waiting queue for the singleLockObject
    SingleLockObject* waitObject = (SingleLockObject*)currentProcess->blockAddress;
    if (waitObject->processWaitingQueue == NULL){
        waitObject->processWaitingQueue = currentProcess;
        currentProcess->nextProcess = NULL;
    } else {
        struct Process* waitQueueProc = waitObject->processWaitingQueue;
        for(;waitQueueProc->nextProcess != NULL && waitQueueProc->nextProcess->priority >= currentProcess->priority; waitQueueProc = waitQueueProc->nextProcess);
        currentProcess->nextProcess = waitQueueProc->nextProcess;
        waitQueueProc->nextProcess = currentProcess;
    }
    rescheduleImmediately();
}

void singleLockReleased(void){
    //The released mutex is in the currentProcess->blockAddress var
    SingleLockObject* waitObject = (SingleLockObject*)currentProcess->blockAddress;
    if (waitObject->processWaitingQueue != NULL){
        //Pop the first item
        struct Process* awokenOne = waitObject->processWaitingQueue;
        waitObject->processWaitingQueue = awokenOne->nextProcess;
        awokenOne->state = 0;
        awokenOne->blockAddress = NULL;
        __addProcessToReady(awokenOne);
        rescheduleImmediately();
    }    
    currentProcess->blockAddress = NULL;
}

void sayHi(void){
    UARTprintf("Hi from your favorite supervisor!\r\n");
}

//This function responds to an interrupt that can be generated at any runlevel.
void svcHandler_main(char reqCode){
    //UARTprintf("supervisor interrupt, id:%d\r\n",reqCode);
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
        case 255:
            sayHi();
            break;
        default:
            UARTprintf("Supervisor call handler: unknown code %d\r\n",reqCode);
            break;
    }
}
