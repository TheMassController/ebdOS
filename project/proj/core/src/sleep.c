//Contains all sleep related code
#include <hw_nvic.h>        // Macros for NVIC
#include <hw_types.h>       // Defines for TI libs
#include <uartstdio.h>      // Specific STDIO
#include <timer.h>          // Function prototypes for timer hw interaction
#include <lm4f120h5qr.h>    // Hardware regs
#include <hw_memmap.h>      // address of GPIO etc
#include <rom_map.h>        // Call functions directly from the ROM if available
#include <rom.h>            // Declare ROM addresses for rom funcs
#include <stdlib.h>         // C defaults like NULL
#include <stdint.h>         // All ints existing for this platform

#include "supervisorCall.h" // Defs for supervisor interrupt params
#include "process.h"        // Defs for the process
#include "sleep.h"          // Header of the same name
#include "sysSleep.h"       // Kernel facing sleep funcs
#include "coreUtils.h"      // Additional utils

#define MAXSLEEPTIMER 4294967295

unsigned sleepClocksPerMS = 0;
extern struct Process* currentProcess;

//----------- Interrupt related

void sleepTimerWAInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE,  TIMER_CAPA_MATCH|TIMER_CAPA_EVENT|TIMER_TIMA_TIMEOUT);
    //TODO
    UARTprintf("Apparently, almost 40 days have passed");

}

void sleepTimerWBInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE,  TIMER_TIMB_MATCH);
    CALLSUPERVISOR(SVC_wakeup);
}

//----------- Sys functions (internals) (Used by core)


void prepareSleep(int64_t sleepTicks){
    if (isInInterrupt()) return; // Silently fail
    unsigned overflows = 0;
    int64_t curval = (int64_t)getCurrentSytemTimerValue();
    sleepTicks = curval - sleepTicks;
    while(sleepTicks < 0){
        overflows++;
        sleepTicks += MAXSLEEPTIMER;
    }
    currentProcess->sleepObj.overflows = overflows;
    currentProcess->sleepObj.sleepUntil = sleepTicks;
}

void prepareSleepMS(unsigned ms){
    prepareSleep(ms * sleepClocksPerMS);
}

void sleepTickCount(long sleepTicks){
    //Because a half ms is exactly 1 tick
    if (isInInterrupt()) return; //cannot sleep from an interrupt
    prepareSleep(sleepTicks);
    CALLSUPERVISOR(SVC_sleep);
}

unsigned getCurrentSytemTimerValue(void){
    return ROM_TimerValueGet(WTIMER0_BASE, TIMER_A);
}

void sleepTickCountDelayBlock(long sleepticks){
    prepareSleep(sleepticks);
}

//----- User space sleep functions

void sleepMS(unsigned ms){
    //The millisecond sleeper
    sleepTickCount(ms*sleepClocksPerMS);
}

void sleepS(unsigned seconds){
    //The second sleeper
    sleepTickCount(seconds*1000*sleepClocksPerMS);
}

//------- Sleep functions as used by the mutex functions
void __sleepMSDelayBlock(unsigned ms){
    sleepTickCountDelayBlock(ms*sleepClocksPerMS);
}
