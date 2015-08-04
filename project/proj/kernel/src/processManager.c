// Responsible for creating and managing processes
// External headers
#include <lm4f120h5qr.h> //Hardware regs
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "process.h"
#include "coreUtils.h"
#include "process.h"
#include "supervisorCall.h"
#include "semaphore.h"
#include "getSetRegisters.h"

#ifdef DEBUG
#include <uartstdio.h>
#include "kernUtils.h"
#endif //DEBUG


//And the other defines
#define DEFAULT_KERNEL_PROCESSES 2
#define IDLEFUNCSTACKLEN 128

struct Process processPool[MAXTOTALPROCESSES + DEFAULT_KERNEL_PROCESSES];

struct Process* kernel = NULL;
extern struct Process* currentProcess;
extern struct Process* idleProcess;
struct Process* newProcess = NULL;
// Declarations of core helper functions
void __sleepProcessFunc(void);
// TODO depricate in favor of the syscall exit function, or a derative
void __processReturn(void);

void releaseFromMemPool(struct Process* process){
    process->containsProcess = 0;
}

//This function is not threadsafe: only the kernel can run it!
struct Process* getProcessFromPool(void){
    //Starts at one because process zero is always the kernel. If that process does not exist then something real is going on.
    for (int i = 1; i < MAXTOTALPROCESSES + DEFAULT_KERNEL_PROCESSES; ++i){
        if (!processPool[i].containsProcess){
            return &processPool[i];
        }
    }
    return NULL;
}

void initializeProcesses(void){
#ifdef DEBUG
    if (kernel != NULL){
        UARTprintf("PANIC: second run of initilializeProcesses\r\n");
        generateCrash();
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
    // Because the kernel works from the MSP, there is no kernel stack and the kernelstackpointer is set on first context switch
    processPool[0].stack = NULL;
    processPool[0].stackPointer = NULL;
    processPool[0].savedRegsPointer = &(processPool[0].savedRegSpace[CS_SAVEDREGSPACE + CS_FPSAVEDREGSPACE]); //Because of decrement before write, set this pointer at the very end
    processPool[0].hwFlags = PROCESS_IS_PRIVILEGED | PROCESS_USES_MSP;
    processPool[0].context = NULL; // The kernel does not need a context.

    //set some params
    currentProcess = &processPool[0];
    setPSP(currentProcess->stackPointer); //For safety, do set the PSP to zero when the kernel runs. This way, when an error is made a segfault happens and not random memory overwrite
    kernel = currentProcess;

    // It is quite vital that this happens right before a return or functioncall, else the set of the global var might be delayed
    newProcess = kernel;
    CALLSUPERVISOR(SVC_processAdd);
    //Create the sleeper
    __createNewProcess(1, IDLEFUNCSTACKLEN, "Idle Process", __sleepProcessFunc, NULL, 0, 0);
    idleProcess = kernel->nextProcess;
    kernel->nextProcess = NULL;
}

int __createNewProcess(unsigned mPid, unsigned long stacklen, char* name, void (*procFunc)(), void* param, char priority, char isPrivileged){
    if (currentProcess->pid != 1) {
        return EACCES;
    }
    struct Process* newProc = getProcessFromPool();
    if ( newProc == NULL) { //Insufficient mem
       return ENOMEM;
    }
    if (stacklen < 67){
        return EINVAL;
    }
    //Create the stack + processcontext.
    void* stack = malloc(stacklen + sizeof(struct ProcessContext));
    if (stack == NULL){
        releaseFromMemPool(newProc);
        return ENOMEM;
    }
    if (priority == 255) priority = 254; //Max 254, 255 is kernel only
    if (priority == 0) priority = 1;    //Min 1, 0 is sleeper only
    //This pointer is kept for the freeing, later
    newProc->stack = stack;

    //Set some vars
    newProc->mPid = mPid;
    newProc->nextProcess = NULL;
    newProc->priority = priority;
    newProc->state = STATE_READY;
    newProc->hwFlags = PROCESS_DEFAULT;
    if (isPrivileged) newProc->hwFlags |= PROCESS_IS_PRIVILEGED;
    newProc->blockAddress = NULL;
    newProc->sleepObj.process = newProc;
    if (strlen(name) > 20){
        //Name too long, only copy first 20 characters
        memcpy(newProc->name, name, 20);
        newProc->name[20] = 0;
    } else {
        strcpy(newProc->name, name);
    }
    // Set the context pointer
    newProc->context = (struct ProcessContext*)((long)newProc->stack + stacklen);
    //Because a stack moves down (from high to low) move the pointer to the last address and then move it down to a position where for the address of the pointer lsb and lsb+1 = 0 (lsb and lsb+1 of SP are always 0)
    //This new address is always lower then or equal to the highest address that is assigned this process.
    //stacklen -sizeof(void*) is because ptr + stacklen is one too much, the pointer itself is also assigned to the process
    int* stackPointer = (int*)(((long)newProc->stack + stacklen - 1) & ~((long)0x3));
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
    newProc->savedRegsPointer = &(newProc->savedRegSpace[16]); //Let it point to the first GP space.
#ifdef DEBUG
    //The second set is the registers that we have to move manually between RAM and regs when switching contexts
    //Order: R4, R5, R6, R7, R8, R9, R10, R11
    //FP: S16, S17, S18, S19, S20, S21, S22, S23, S24, s25, S26, S27, S28, S29, S30, S31
    //Normal regs first
    unsigned it = 0;
    for ( int u = 16; u <= 31; u++){
        newProc->savedRegSpace[it] = u;
        ++it;
    }
    //Then the FP regs
    for ( int u = 4; u <= 11; u++ ){
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
