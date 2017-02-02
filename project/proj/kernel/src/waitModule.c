#include <errno.h>                  // Contains the macro's for the E* variables
#include <hw_types.h>               // Common types and macros for the TI libs
#include <timer.h>                  // Function prototypes for the timer module
#include <hw_memmap.h>              // Address of GPIO etc

#include "waitModule.h"             // Function prototypes
#include "kernelPredefined.h"       // Centralizes resource counts

//static struct SleepQueueElement sleepQueuePool[MAXTOTALPROCESSES];
//static struct SleepQueueElement* sleepQueueHead = NULL;

//static void updateWaitTimer(unsigned curValWTA){
//    if (sleepQueueHead == NULL || sleepQueueHead->proc->sleepObj.overflows > 0){
//        setHalfWTimerInterrupt(0, WTIMER1_BASE, TIMER_B, 0, 0);
//    } else if (sleepQueueHead->proc->sleepObj.overflows == 0 && sleepQueueHead->proc->sleepObj.sleepUntil >= curValWTA){
//        return; // Let the timer interrupt handle this case, it will just shoot an event into the kernel that will fix the rest
//    } else {
//        setHalfWTimerInterrupt(1, WTIMER1_BASE, TIMER_B, curValWTA, sleepQueueHead->proc->sleepObj.sleepUntil);
//    }
//}

struct Process* waitTimerTimeout(void){
    return NULL;

}

struct Process* waitTimerSysTimerOverflow(void){
    return NULL;
}
