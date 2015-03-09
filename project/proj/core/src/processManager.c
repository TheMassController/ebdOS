#include "defenitions.h"
#include "process.h"
#include "string.h"
#include "stdlib.h"
#include "asmUtils.h"
#include "uartstdio.h"
#include "process.h"
#include "supervisorCall.h" 
#include "lm4f120h5qr.h" //Hardware regs
#include "semaphore.h"

#define UNUSED(x) (void)(x) //To suppress compiler warning

#ifdef DEBUG
#include "malloc.h"
#include "uartstdio.h"
#endif //DEBUG
#include "getSetRegisters.h"

//Responsible for creating and managing processes

//Stack save reg size: the total amount of bytes that needs to be written from regs to stack.
#define STACKSAVEREGSIZE 64

struct Process* processesReady = NULL;
struct Process* kernel = NULL;
extern struct Process* currentProcess;
//Usefull for selecting the pids

struct Process* newProcess = NULL;

#define DEFAULT_KERNEL_PROCESSES 2

struct Process processPool[MAXTOTALPROCESSES + DEFAULT_KERNEL_PROCESSES];

#define KERNELSTACKLEN 67
#define IDLEFUNCSTACKLEN 128

//char kernelPSPStack[KERNELSTACKLEN];

void __sleepProcessFunc(void){
    while(1){
        waitForInterrupt();
    }
}

void __processReturn(void){
    UARTprintf("Process %s with pid %d has just returned.\r\n",currentProcess->name, currentProcess->pid);
    //TODO tell kernel about this stuff and let it cleanup the mess
    currentProcess->state = STATE_WAIT;
    while(1){
        CALLSUPERVISOR(SVC_reschedule);
    }
}

struct Process* getProcessFromPool(void){
    //Starts at one because process zero is always the kernel. If that process does not exist then something real is going on.
    for (int i = 1; i < MAXTOTALPROCESSES + 2; ++i){
        if (!processPool[i].containsProcess){
            return &processPool[i];
        }
    }
    return NULL;
}

void initializeProcesses(void){
#ifdef DEBUG
    if (processesReady != NULL){
        UARTprintf("PANIC: second run of initilializeProcesses\r\n");
    }
#endif
    for (int i = 0; i < MAXTOTALPROCESSES + DEFAULT_KERNEL_PROCESSES; ++i){
        processPool[i].containsProcess = 0;
        processPool[i].pid = i+1;
    }
    //Create the kernel
    processPool[0].mPid = 0;
    processPool[0].containsProcess = 1;
    processPool[0].nextProcess = NULL;
    processPool[0].priority = 100;
    processPool[0].state = STATE_READY;
    processPool[0].blockAddress = NULL;
    processPool[0].sleepObj.process = &processPool[0];
    strcpy(processPool[0].name, "Kernel");
    //processPool[0].stack = kernelPSPStack;
    //processPool[0].stackPointer = (void*)((long)(&kernelPSPStack[KERNELSTACKLEN - 1]) & (long)0xFFFFFFFC);
    processPool[0].stack = NULL;
    processPool[0].stackPointer = NULL;
    processPool[0].savedRegsPointer = &(processPool[0].savedRegSpace[8]); //Because of decrement before write, set this pointer at the very end
    
    //set some params 
    processesReady = &processPool[0];
    currentProcess = &processPool[0]; 
    setPSP(currentProcess->stackPointer); //For safety, do set the PSP to zero when the kernel runs. This way, when an error is made a segfault happens and not random memory overwrite
    kernel = currentProcess;

    //Create the sleeper
    __createNewProcess(1, IDLEFUNCSTACKLEN, "Idle Process", __sleepProcessFunc, NULL, 0);
    kernel->nextProcess->priority = 0; //Set the priority of the sleep process to min.
}


int __createNewProcess(unsigned mPid, unsigned long stacklen, char* name, void (*procFunc)(), void* param, char priority){
    if (priority == 255) priority = 254; //Max 254, 255 is kernel only
    if (priority == 0) priority = 1;    //Min 1, 0 is sleeper only
    if (currentProcess->pid != 1) {
        return 3;
    } 
    struct Process* newProc = getProcessFromPool();
    if ( newProc == NULL) { //Insufficient mem
       return 1; 
    }
    if (stacklen < 67){
        return 4;
    }
    //Set some vars
    newProc->mPid = mPid;
    newProc->nextProcess = NULL;
    newProc->priority = priority;
    newProc->state = STATE_READY;
    newProc->blockAddress = NULL;
    newProc->sleepObj.process = newProc;
    if (strlen(name) > 20){
        //Name too long, only copy first 20 characters
        memcpy(newProc->name, name, 20);
        newProc->name[20] = 0;
    } else {
        strcpy(newProc->name, name);
    }
    //Create the stack.
    void* stack = malloc(stacklen);
    if (stack == NULL){
        free(newProc->name);
        free(newProc);
        return 2;
    }
    newProc->stack = stack;
    //Because a stack moves up (from high to low) move the pointer to the last address and then move it back up to a position where for the address of the pointer lsb and lsb+1 = 0 (lsb and lsb+1 of SP are always 0)
    int* stackPointer = (int*)((((long)newProc->stack) + stacklen - 4) & (long)0xFFFFFFFC ); //TODO is the -4 necessary?
    //Now start pushing registers
    //The first set of registers are for the interrupt handler, those will be read when the system returns from an interrupt
    //These are in order from up to down: R0, R1, R2, R3, R12, LR, PC, XSPR
    *stackPointer-- = 0x01000000; //XPSR, standard stuff 
    *stackPointer-- = (int)procFunc; //PC, initally points to start of function
    *stackPointer-- = (int)&__processReturn; //LR, return func
#ifdef DEBUG
    *stackPointer-- = 12; // reg12, 12 for debug
    *stackPointer-- = 3; // reg3, 3 for debug
    *stackPointer-- = 2; // reg2, 2 for debug
    *stackPointer-- = 1; // reg1, 1 for debug
#else
    stackPointer -= 4;      //If not debugging, just decrease the stackptr    
#endif //DEBUG
    *stackPointer = (int)param; // reg 0, first param
    //Save the stackpointer to the struct
    newProc->stackPointer = (void*)stackPointer;

    //Init the saved temp reg space
    newProc->savedRegsPointer = &(newProc->savedRegSpace);
#ifdef DEBUG
    //The second set is the registers that we have to move manually between RAM and regs when switching contexts
    //Order: R4, R5, R6, R7, R8, R9, R10, R11
    unsigned it = 0;
    for ( int u = 11; u >= 4; u-- ){
        newProc->savedRegSpace[it] = u;
        ++it;
    }  
#endif //DEBUG
    newProc->containsProcess = 1;

    //Add the new process to the list of processes
    newProcess = newProc;
    CALLSUPERVISOR(SVC_processAdd);
    return 0; 
}
