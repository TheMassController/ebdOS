// External headers
#include <stdlib.h>         // STD Lib, for default defs like NULL
#include <lm4f120h5qr.h>    // Hardware regs
// Internal headers
#include "scheduler.h"      // Contain the declarations for all functions defined here.
#include "process.h"        // The struct Process, a lot of defines related to processes.
#include "coreUtils.h"      // Contains some supporting functions
// Debug headers
#ifdef DEBUG
#include <uartstdio.h>      // Used for STDIO for this specific UART, written by TI
#include "kernUtils.h"      // Kernel's util funcs. Used for generateCrash
#endif //DEBUG

// TODO make processesReady static.
struct Process* processesReady  = NULL;
struct Process* nextProcess     = NULL;
struct Process* currentProcess  = NULL;
struct Process* idleProcess     = NULL;

// Interrupt hanler
void sysTickHandler(void){
    (void)processesReady;
}

static void rescheduleImmediately(void){
    if (currentProcess != processesReady){
        if (processesReady == NULL){
            nextProcess = idleProcess;
        } else if (processesReady != currentProcess){
            nextProcess = processesReady;
        }
#ifdef DEBUG
        if (nextProcess == NULL){
            UARTprintf("The context switcher is trying to switch to NULL. Cannot continue");
            generateCrash();
        }
#endif //DEBUG
        NVIC_INT_CTRL_R |= (1<<28); // Set the pendSV to pending (Datasheet pp 156)
    }

}

static struct Process* appendProcessToList(struct Process* listHead, struct Process* item){
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
    if (isInInterrupt() && !processInList(processesReady, proc))
        processesReady = appendProcessToList(processesReady, proc);
    rescheduleImmediately();
}

void removeProcessFromScheduler(struct Process* proc){
    if (isInInterrupt() && processInList(processesReady, proc))
        processesReady = removeProcessFromList(processesReady, proc);
    rescheduleImmediately();
}

int processInScheduler(struct Process* proc){
    return processInList(processesReady, proc);
}

void preemptCurrentProcess(void){
    if (isInInterrupt() && processesReady != NULL && currentProcess->nextProcess != NULL){
        removeProcessFromScheduler(currentProcess);
        addProcessToScheduler(currentProcess);
    }
}
