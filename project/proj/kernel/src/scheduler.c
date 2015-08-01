// External headers
#include <stdlib.h>         // STD Lib, for default defs like NULL
#include <lm4f120h5qr.h>    // Hardware regs
#include <rom_map.h>        // Declares the ROM functions as either ROM funcs or their C implementation
#include <rom.h>            // Declare ROM addresses for rom funcs, if they are available
// Internal headers
#include "scheduler.h"      // Contain the declarations for all functions defined here.
#include "process.h"        // The struct Process, a lot of defines related to processes.
#include "coreUtils.h"      // Contains some supporting functions
#include "supervisorCall.h" // So that the sysTickHandler can call SVC_reschedule
// Debug headers
#ifdef DEBUG
#include <uartstdio.h>      // Used for STDIO for this specific UART, written by TI
#include "kernUtils.h"      // Kernel's util funcs. Used for generateCrash
#endif //DEBUG

static struct Process* processesReady   = NULL;
struct Process* nextProcess             = NULL;
struct Process* currentProcess          = NULL;
struct Process* idleProcess             = NULL;
// Default values and consts related to systick and timeslicing
static const unsigned ticksPerMS = 4000;
static const unsigned maxSystickVal = 16777216;
static unsigned timeSliceMS = 20;

// Interrupt hanler
void sysTickHandler(void){
    CALLSUPERVISOR(SVC_yield);
}

static void setSystick(unsigned timeSlices) {
    // The tickCount needs to be the requested ticks -1. see datasheet pp 135
    unsigned tickCount = (timeSlices * timeSliceMS * ticksPerMS) - 1;
    if (tickCount > maxSystickVal) tickCount = maxSystickVal;
    if (tickCount != NVIC_ST_RELOAD_R){ //If the nextvalue is equal to the previous, do nothing
        if (tickCount > 0) {
            ROM_SysTickDisable();
            NVIC_ST_CURRENT_R = 0; // Clear the current register to force a call to enable to re-read its period
            ROM_SysTickPeriodSet(tickCount);
            ROM_SysTickEnable();
        } else {
            ROM_SysTickPeriodSet(1);
            ROM_SysTickDisable();
        }
    }
}

static void rescheduleImmediately(void){
    if (currentProcess != processesReady){
        unsigned nextSliceLength = 1;
        if (processesReady == NULL){
            nextProcess = idleProcess;
            nextSliceLength = 0;
        } else {
            nextProcess = processesReady;
        }
#ifdef DEBUG
        if (nextProcess == NULL){
            UARTprintf("The context switcher is trying to switch to NULL. Cannot continue");
            generateCrash();
        }
#endif //DEBUG
        setSystick(nextSliceLength);
        NVIC_INT_CTRL_R |= (1<<28); // Set the pendSV to pending (Datasheet pp 156)
    }
}

static struct Process* appendProcessToList(struct Process* listHead, struct Process* item){
    // Run trough the singly linked list until you find an empty spot
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

static struct Process* removeProcessFromList(struct Process* listHead, struct Process* item){
    struct Process* current = listHead;
    struct Process* previous = NULL;
    while (current != NULL && current != item){
        previous = current;
        current = current->nextProcess;
    }
    // If current is NULL, then it was not in the list
    // If previous is NULL, then it is the head of the list
    if (current != NULL){
        if (previous == NULL){
            listHead = current->nextProcess;
        } else {
            previous->nextProcess = current->nextProcess;
        }
    }
    return listHead;
}

static int processInList(struct Process* listHead, struct Process* proc){
    while (listHead != NULL){
        if (listHead == proc) return 1;
        listHead = listHead->nextProcess;
    }
    return 0;
}

void addProcessToScheduler(struct Process* proc){
    if (isInSVCInterrupt() && !processInList(processesReady, proc))
        processesReady = appendProcessToList(processesReady, proc);
    rescheduleImmediately();
}

void removeProcessFromScheduler(struct Process* proc){
    if (isInSVCInterrupt() && processInList(processesReady, proc))
        processesReady = removeProcessFromList(processesReady, proc);
    rescheduleImmediately();
}

int processInScheduler(struct Process* proc){
    return processInList(processesReady, proc);
}

void preemptCurrentProcess(void){
    // TODO revise
    if (isInSVCInterrupt() && processesReady != NULL && currentProcess->nextProcess != NULL){
        removeProcessFromScheduler(currentProcess);
        addProcessToScheduler(currentProcess);
    }
}
