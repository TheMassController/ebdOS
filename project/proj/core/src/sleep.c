//Contains all sleep related code

#include "hw_nvic.h"
#include "hw_types.h"
#include "uartstdio.h"
#include "timer.h"
#include "lm4f120h5qr.h" //Hardware regs
#include "hw_memmap.h" //address of GPIO etc
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include "supervisorCall.h"
#include "process.h"
#include "sleep.h"
#include "sysSleep.h"
#include "stdlib.h"
#include "utils.h"

#define MAXSLEEPTIMER 4294967295

unsigned sleepClocksPerMS = 0;
extern struct Process* currentProcess;
static struct SleepingProcessStruct* sleepProcessListHead = NULL;
static struct SleepingProcessStruct* nextToWakeUp = NULL;

void sleepTimerWAInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE,  TIMER_CAPA_MATCH|TIMER_CAPA_EVENT|TIMER_TIMA_TIMEOUT);
    UARTprintf("Apparently, almost 40 days have passed");
    //TODO decrease overflows
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
                __addProcessToReady(sleepProcessListHead->process);
                sleepProcessListHead = sleepProcessListHead->nextPtr;
            } else {
                ROM_TimerLoadSet(WTIMER0_BASE, TIMER_B, curValWTA);
                ROM_TimerMatchSet(WTIMER0_BASE, TIMER_B, sleepProcessListHead->sleepUntil);
                ROM_TimerEnable(WTIMER0_BASE, TIMER_B); 
            }
        }
    }    
}

void sleepTimerWBInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE,  TIMER_CAPB_MATCH|TIMER_CAPB_EVENT|TIMER_TIMB_TIMEOUT);
    __addProcessToReady(nextToWakeUp->process);
    sleepProcessListHead = sleepProcessListHead->nextPtr;
    setSleepTimerWB();
}

void __addSleeperToList(struct SleepingProcessStruct* ptr){
    struct SleepingProcessStruct* current = sleepProcessListHead;
    struct SleepingProcessStruct* previous = NULL;
    while(current != NULL && current->overflows < ptr->overflows && current->sleepUntil > ptr->sleepUntil){
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

void __removeSleeperFromList(struct Process* proc){
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

unsigned getCurrentSleepTimerValue(void){
    return ROM_TimerValueGet(WTIMER0_BASE, TIMER_A);
}

void prepareSleep(long sleepTicks){
    unsigned overflows = 0;
    sleepTicks = getCurrentSleepTimerValue() - sleepTicks;
    while(sleepTicks < 0){
        overflows++;
        sleepTicks += MAXSLEEPTIMER;
    }
    currentProcess->state |= STATE_SLEEP;
    struct SleepingProcessStruct* sleepObj = (struct SleepingProcessStruct*)malloc(sizeof(struct SleepingProcessStruct));
    sleepObj->process = currentProcess;
    sleepObj->overflows = overflows;
    sleepObj->sleepUntil = sleepTicks;
    currentProcess->sleepObjAddress = (void*) sleepObj;
}

//Because a half ms is exactly 1 tick
void sleepHalfMS(long sleepTicks){
    prepareSleep(sleepTicks);
    CALLSUPERVISOR(SVC_sleep);
    free(currentProcess->sleepObjAddress); 
    currentProcess->sleepObjAddress = NULL;
}

//The millisecond sleeper
void sleepMS(unsigned ms){
    sleepHalfMS(ms*sleepClocksPerMS);
}

//The second sleeper
void sleepS(unsigned seconds){
    sleepHalfMS(seconds*1000*sleepClocksPerMS);
}

void sleepHalfMSDelayBlock(long sleepticks){
    prepareSleep(sleepticks);
    CALLSUPERVISOR(SVC_sleepNoBlock);
}

void __sleepMSDelayBlock(unsigned ms){
    sleepHalfMSDelayBlock(ms*sleepClocksPerMS);    
}

void __sleepDelayBlockWakeup(void){
    free(currentProcess->sleepObjAddress);
    currentProcess->sleepObjAddress = NULL;
}
