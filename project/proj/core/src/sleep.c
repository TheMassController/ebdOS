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

#define MAXSLEEPTIMER 4294967295

unsigned sleepClocksPerMS = 0;
extern struct Process* currentProcess;

void sleepTimerInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE,  TIMER_CAPA_MATCH|TIMER_CAPA_EVENT|TIMER_TIMA_TIMEOUT);
    UARTprintf("Apparently, almost 40 days have passed");
    while(1){}
    //TODO alert kernel, let it decrease overflows
}

unsigned getCurrentSleepTimerValue(void){
    return ROM_TimerValueGet(WTIMER0_BASE, TIMER_A);
}

//Because a half ms is exactly 1 tick
void __sleepHalfMS(unsigned sleepTicks){
    sleepTicks = getCurrentSleepTimerValue() - sleepTicks;
    while(sleepTicks < 0){
        currentProcess->sleepClockOverflows += 1;
        sleepTicks += MAXSLEEPTIMER;
    }
    currentProcess->sleepClockTime = sleepTicks;
    currentProcess->state |= STATE_SLEEP;
    //Reschedule right the hell now 
    CALLSUPERVISOR(SVC_reschedule);
}

//The millisecond sleeper
void sleepMS(unsigned ms){
    __sleepHalfMS(ms*sleepClocksPerMS);
}

//The second sleeper
void sleepS(unsigned seconds){
    //recalculate to ms, then call the ms function
    __sleepHalfMS(seconds*1000*sleepClocksPerMS);
}
