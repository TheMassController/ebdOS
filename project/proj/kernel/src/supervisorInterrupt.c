// Handles the supervisor interrupt call
#include <hw_nvic.h>                // Macros related to the NVIC hardware
#include <hw_types.h>               // Common types and macros for the TI libs
#include <uartstdio.h>              // UART stdio declarations
#include <timer.h>                  // Function prototypes for the timer module
#include <hw_memmap.h>              // Address of GPIO etc
#include <lm4f120h5qr.h>            // Hardware regs
#include <hw_types.h>               // Contains the special types
#include <rom_map.h>                // Call functions directly from the ROM if available
#include <rom.h>                    // Declare ROM addresses for rom funcs
#include <stdlib.h>                 // Contains C defs like NULL

#include "process.h"                // Declares the OS's process structs and funcs
#include "supervisorCall.h"         // Supplies the SVC commands
#include "scheduler.h"              // All functions related to the scheduler
#include "kernMaintenanceQueue.h"   // The kernel maintenaince queue
#include "kernUtils.h"              // To escalate to NMI
#include "kernEventNotifier.h"      // To check if there are no more events waiting for the kernel.

static struct Process* kernel                               = &kernelStruct;

volatile int kernelIsActive = 1;

//----- Functions related to the moving of functions from one queue to another

static void activateKernel(void){
    if (!kernelIsActive){
        addProcessToScheduler(kernel);
        kernelIsActive = 1;
    }
}

static void suspendKernel(void){
    if (kernelIsActive){
        removeProcessFromScheduler(kernel);
        kernelIsActive = 0;
    }
}

static void currentProcessRequestsService(void){
    struct Process* curProc = popCurrentProcess();
    curProc->state = STATE_WAIT;
    passProcessToKernel(curProc);
    activateKernel();
}

static void kernelIsDoneServing(void){
    struct Process* tempPtr = kernRetQueuePop();
    while(tempPtr != NULL){
        tempPtr->state = STATE_READY;
        addProcessToScheduler(tempPtr);
        tempPtr = kernRetQueuePop();
    }
    if(KernelProcessBufferIsEmpty() && kernBufferIsEmpty()){
        suspendKernel();
    }
}

#ifdef DEBUG
static void sayHi(void){
    UARTprintf("Hi from your favorite supervisor!\r\n");
}
#endif //DEBUG

// This function responds to an interrupt that can be generated at any runlevel.
// Handlermode is somewhere near equal to being in an interrupt.
void svcHandler_main(const uint8_t reqCode, const unsigned fromHandlerMode){
    switch(reqCode){
        case SVC_yield:
            if (!fromHandlerMode) preemptCurrentProcess();
            break;
        case SVC_wakeupKernel:
            activateKernel();
            break;
        case SVC_serviceRequired:
            if (!fromHandlerMode) currentProcessRequestsService();
            break;
        case SVC_serviced:
            if (!fromHandlerMode) kernelIsDoneServing();
            break;
        case SVC_abort:
            generateCrash();
            break;
#ifdef DEBUG
        case SVC_test:
            sayHi();
            break;
#endif //DEBUG
        default:
            UARTprintf("Supervisor call handler: unknown code %d\r\n",reqCode);
            break;
    }
}
