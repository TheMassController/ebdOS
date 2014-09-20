#include "defenitions.h"
#include "process.h"
#include "processManagement.h"
#include "string.h"
#include "stdlib.h"
#include "asmUtils.h"
//Responsible for creating and managing processes

unsigned char currentPid = 0;
struct Process* firstProcess = NULL;
struct Process* kernel = NULL;
//Usefull for selecting the pids
static unsigned short nextPid = 1; //Short, has to be able to become 256
#define MAX_PROCESSID (255)

struct Process* nextProcess = NULL;

struct Process* __processCreator(unsigned char mPid, unsigned long stacklen,  char* name, processFunc procFunc, void* param, struct Process* newProc, void* stack, unsigned short pid){
    if (currentPid != 0 || newProc == NULL){
        return NULL;
    }
    //Set some vars
    newProc->pid = pid;
    newProc->mPid = mPid;
    newProc->nextProcess = NULL;
    newProc->name = (char*)malloc(strlen(name));
    strcpy(newProc->name,name);
    newProc->stack = stack;
    //Because a stack moves up (from high to low) move the pointer to the last address
    int* stackPointer = (int*)(((char*)newProc->stack) + stacklen - 1 ); //Because we are lazy. The -1 is to prevent going above the stack (malloc returns addresses 0 -> asked-1)
    //Now start pushing registers

    //The first set of registers are for the interrupt handler, those will be read when the system returns from an interrupt
    //These are in order from up to down: R0, R1, R2, R3, R12, LR, PC, XSPR
    *stackPointer-- = 0x01000000; //XSPR, standard stuff 
    *stackPointer-- = (int)procFunc; //PC, initally points to start of function
    *stackPointer-- = (int)&processReturn; //LR, return func
    *stackPointer-- = 12; // reg12, 12 for debug
    *stackPointer-- = 3; // reg3, 3 for debug
    *stackPointer-- = 2; // reg2, 2 for debug
    *stackPointer-- = 1; // reg1, 1 for debug
    *stackPointer-- = (int)param; // reg 0, first param

    //The second set is the registers that we have to move manually between RAM and regs when switching contextst
    //Order: R4, R5, R6, R7, R8, R9, R10, R11
    for ( int u = 4; u <= 10; u++ ){
        *stackPointer-- = u; //Reg u, u for debug
    }  
    *stackPointer = 11; //The last reg and the pos we want the stackpointer to point to: reg 11
    
    //Save the stackpointer to the struct
    newProc->stackPointer = (void*)stackPointer;
    return newProc;   
}

int __createNewProcess(unsigned char mPid, unsigned long stacklen, char* name, processFunc procFunc, void* param){
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
    //Create the stack.
    void* stack = malloc(stacklen);
    if (stack == NULL){
        return 2;
    }
    newProc = __processCreator(mPid, stacklen, name, procFunc, param, newProc, stack, nextPid++);
    if ( firstProcess == NULL) {
        firstProcess = newProc;
    } else {
        struct Process* thisProc;
        for ( thisProc = firstProcess; thisProc->nextProcess != NULL; thisProc = thisProc->nextProcess);
        thisProc->nextProcess = newProc;
    }
   return 0; 
}

void schedule(void){
//The actual scheduler. 
}

void processReturn(void){
    //Placeholder
    while (1) {
        waitForInterrupt();
    }
}

void pendSVHandler(void){
    //Placeholder
    while (1) {
        waitForInterrupt();
    }
    
}
