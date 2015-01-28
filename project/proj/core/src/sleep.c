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
#include "threadsafeCalls.h"
#include "asmUtils.h"
#include "stdint.h"

#define MAXSLEEPTIMER 4294967295

unsigned sleepClocksPerMS = 0;
extern struct Process* currentProcess;

//----------- Interrupt related

void sleepTimerWAInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE,  TIMER_CAPA_MATCH|TIMER_CAPA_EVENT|TIMER_TIMA_TIMEOUT);
    UARTprintf("Apparently, almost 40 days have passed");
    
}

void sleepTimerWBInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE,  TIMER_TIMB_MATCH);
    CALLSUPERVISOR(SVC_wakeup);
}

//----------- Sys functions (internals)


void prepareSleep(int64_t sleepTicks){
    unsigned overflows = 0;
    int64_t curval = (int64_t)getCurrentSleepTimerValue();
    sleepTicks = curval - sleepTicks;
    while(sleepTicks < 0){
        overflows++;
        sleepTicks += MAXSLEEPTIMER;
    }
    struct SleepingProcessStruct* sleepObj = (struct SleepingProcessStruct*)malloc(sizeof(struct SleepingProcessStruct));
    sleepObj->process = currentProcess;
    sleepObj->overflows = overflows;
    sleepObj->sleepUntil = (unsigned)sleepTicks;
    currentProcess->sleepObjAddress = (void*) sleepObj;
}

void sleepHalfMS(long sleepTicks){
    //Because a half ms is exactly 1 tick
    prepareSleep(sleepTicks);
    currentProcess->state |= STATE_SLEEP;
    CALLSUPERVISOR(SVC_sleep);
    free(currentProcess->sleepObjAddress); 
    currentProcess->sleepObjAddress = NULL;
}

unsigned getCurrentSleepTimerValue(void){
    return ROM_TimerValueGet(WTIMER0_BASE, TIMER_A);
}

void sleepHalfMSDelayBlock(long sleepticks){
    currentProcess->state |= STATE_SLEEP;
    prepareSleep(sleepticks);
}

//----- User space sleep functions

void sleepMS(unsigned ms){
    //The millisecond sleeper
    sleepHalfMS(ms*sleepClocksPerMS);
}

void sleepS(unsigned seconds){
    //The second sleeper
    sleepHalfMS(seconds*1000*sleepClocksPerMS);
}

//------- Sleep functions as used by the mutex functions
void __sleepMSDelayBlock(unsigned ms){
    sleepHalfMSDelayBlock(ms*sleepClocksPerMS);    
}

void __sleepDelayBlockWakeup(void){
    free(currentProcess->sleepObjAddress);
    currentProcess->sleepObjAddress = NULL;
}
