#include "process.h"
#include "processManagement.h"
#include "getSetRegisters.h"
#include "regDumpLoad.h"
#include "stdlib.h"

// This file handles scheduling, basically

extern struct Process* kernel;
extern struct Process* currentProcess;
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
    //TODO correct return
}


void schedule(void){
//The actual scheduler. 
}
