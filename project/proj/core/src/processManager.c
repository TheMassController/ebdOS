#include "defenitions.h"
#include "process.h"
#include "processManagement.h"
#include "string.h"
#include "stdlib.h"
#include "asmUtils.h"
//Responsible for creating and managing processes

struct Process* firstProcess = NULL;
struct Process* kernel = NULL;
extern struct Process* currentProcess;
//Usefull for selecting the pids
static unsigned char nextPid = 1; //Short, has to be able to become 256
#define MAX_PROCESSID (254)

int __createNewProcess(unsigned char mPid, unsigned long stacklen, char* name, processFunc procFunc, void* param){
    if (currentProcess->pid != 0) {
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
    if (newProc->name == NULL){
        free(newProc);
        return 2;
    }
    newProc->state = READY;
    strcpy(newProc->name,name);
    //Create the stack.
    void* stack = malloc(stacklen);
    if (stack == NULL){
        free(newProc->name);
        free(newProc);
        return 2;
    }
    newProc->stack = stack;
    //Because a stack moves up (from high to low) move the pointer to the last address and then move it back up to a position where lsb and lsb+1 = 0 (lsb and lsb+1 of SP are always 0)
    int* stackPointer = (int*)((((long)newProc->stack) + stacklen - 4) & (long)0xFFFFFFFC ); //Because we are lazy. The -1 is to prevent going above the stack (malloc returns addresses 0 -> asked-1)
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
    for ( int u = 11; u > 4; u-- ){
        *stackPointer-- = u; //Reg u, u for debug
    }  
    *stackPointer = 4;
    //Save the stackpointer to the struct
    newProc->stackPointer = (void*)stackPointer;

    //Add the new process to the list of processes
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
