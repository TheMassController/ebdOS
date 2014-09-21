#include "process.h"
#include "processManagement.h"
#include "getSetRegisters.h"
#include "regDumpLoad.h"
#include "stdlib.h"
#include "asmUtils.h"

//Defines for correct returns
// See datasheet pp 106
#define PSPNONFP_RETURN ((void*)0xFFFFFFFD)
#define MSPNONFP_RETURN ((void*)0xFFFFFFF9)
#define PSPFP_RETURN    ((void*)0xFFFFFFED)
#define MSPFP_RETURN    ((void*)0xFFFFFFE9)

// This file handles scheduling, basically

extern struct Process* kernel;
extern struct Process* currentProcess;
extern struct Process* firstProcess;
struct Process* nextProcess = NULL;

void switchFromKernel(void){
    saveRegistersToMSPAndMoveMSP();
    setPSP(nextProcess->stackPointer);        
    loadRegistersFromPSPAndMovePSP();
}

void switchToKernel(void){
    currentProcess->stackPointer = saveRegistersToPSPAndMovePSP();
    loadRegistersFromMSPAndMoveMSP();
}

void switchProcesses(void){
    currentProcess->stackPointer = saveRegistersToPSPAndMovePSP();   
    setPSP(nextProcess->stackPointer);
    loadRegistersFromPSPAndMovePSP();
}

void pendSVHandler(void){
    //We are assuming nextProcess is not null
    if (currentPid == 0){
        switchFromKernel();
    } else if (nextProcess->pid == 0){
        switchToKernel();
    } else {
        switchProcesses();
    }
    currentProcess = nextProcess;
    if (nextProcess->pid == 0){
        forceManualReturn(MSPNONFP_RETURN);
    } else {
        forceManualReturn(PSPNONFP_RETURN);
    }
}


void schedule(void){
//The actual scheduler. 
}
