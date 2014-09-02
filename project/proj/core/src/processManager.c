#include "defenitions.h"
#include "process.h"
#include "processManagement.h"
#include "string.h"
#include "stdlib.h"
#include "asmUtils.h"
//Responsible for creating and managing processes

unsigned char currentPid = 0;
struct Process* firstProcess = NULL;
//Usefull for selecting the pids
static unsigned short nextPid = 1; //Short, has to be able to become 256
#define MAX_PROCESSID (255)

int __createNewProcess(unsigned char mPid, unsigned long stacklen, char* name, processFunc procFunc, void* param ){
    if (currentPid != 0) {
        return 3;
    } 
    if ( nextPid > MAX_PROCESSID ) {
        return 1;
    }
    //Create the process on the heap
    struct Process* newProc = (struct Process*)malloc(sizeof(struct Process)); 
    if ( newProc == NULL) { //Insufficient mem
       return 2; 
    }
    //Set some vars
    newProc->pid = nextPid++;
    newProc->mPid = mPid;
    newProc->nextProcess = NULL;
    newProc->name = (char*)malloc(strlen(name));
    strcpy(newProc->name,name);
    //Create the stack.
    //Because a stack moves up (from high to low) also move the pointer to the last address
    newProc->stack = malloc(stacklen);
    int* stackPointer = (int*)(((char*)newProc->stack) + stacklen); //Because we are lazy
    //Now start pushing registers
    //These are in order from up to down: R0, R1, R2, R3, R12, LR, PC, XSPR
    *stackPointer-- = 0x01000000; //XSPR, standard stuff 
    *stackPointer-- = (int)procFunc;
    *stackPointer-- = (int)&processReturn;
    *stackPointer-- = 12; // reg12, 12 for debug
    *stackPointer-- = 3; // reg3, 3 for debug
    *stackPointer-- = 2; // reg2, 2 for debug
    *stackPointer-- = 1; // reg1, 1 for debug
    *stackPointer-- = (int)param; // reg 0, first param
    
    if ( firstProcess == NULL) {
        firstProcess = newProc;
    } else {
        struct Process* thisProc;
        for ( thisProc = firstProcess; thisProc->nextProcess != NULL; thisProc = thisProc->nextProcess);
        thisProc->nextProcess = newProc;
        
    }
   return 0; 
}

void processReturn(void){
    //Placeholder
    while (1) {
        waitForInterrupt();
    }
}
