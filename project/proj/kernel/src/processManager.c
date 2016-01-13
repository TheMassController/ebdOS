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
#include "kernUtils.h"
#include "context.h"

#ifdef DEBUG
#include <uartstdio.h>
#endif //DEBUG

//And the other defines
// For now we want it to be 128 bytes
#define IDLEFUNCSTACKLEN (128/sizeof(uint8_t))

static struct Process processPool[MAXTOTALPROCESSES];
static uint8_t idleProcStack[IDLEFUNCSTACKLEN + sizeof(struct ProcessContext)];
static struct ProcessContext kernelContext;

struct Process kernelStruct = {
    .mPid = 0,
    .pid = 0,
    .containsProcess = 1,
    .nextProcess = NULL,
    .priority = 100,
    .state = STATE_READY,
    .blockAddress = NULL,
    .stack = NULL,
    .stackPointer = NULL,
    .savedRegsPointer = &(kernelStruct.savedRegSpace[CS_SAVEDREGSPACE + CS_FPSAVEDREGSPACE]), // At the very end
    .hwFlags = PROCESS_IS_PRIVILEGED | PROCESS_USES_MSP,
    .context = &kernelContext,
    .stacklen = 0,
    .name = "Kernel",
};

struct Process idleProcessStruct = {
    .mPid = 0,
    .pid = 1,
    .containsProcess = 1,
    .state = STATE_READY,
    .hwFlags = PROCESS_DEFAULT,
    .name = "IdleProcess",
};

// TODO depricate in favor of the syscall exit function, or a derative
void __processReturn(void);
void __sleepProcessFunc(void);

static void releaseFromMemPool(struct Process* process){
    process->containsProcess = 0;
}

static struct Process* getProcessFromPool(void){
    //Starts at one because process zero is always the kernel. If that process does not exist then something real is going on.
    for (int i = 0; i < MAXTOTALPROCESSES; ++i){
        if (!processPool[i].containsProcess){
            return &processPool[i];
        }
    }
    return NULL;
}

// The child is added to the parent as a child process.
static void assignChildToProcess(struct Process* parent, struct Process* child){
    if (parent->childPtr == NULL){
        parent->childPtr = child;
    } else {
        struct Process* it = parent->childPtr;
        for (; it->nextChildPtr != NULL; it = it->nextChildPtr);
        it->nextChildPtr = child;
    }
}

static void setupDynamicMem(struct Process* proc, void* stack, size_t stacklen, void (*procFunc)(), void* param){
    proc->stack = stack;
    proc->stacklen = stacklen;
    // Set the context pointer
    proc->context = (struct ProcessContext*)((uintptr_t)proc->stack + stacklen);
    //Because a stack moves down (from high to low) move the pointer to the last address and then move it down to a position where for the address of the pointer lsb and lsb+1 = 0 (lsb and lsb+1 of SP are always 0)
    //This new address is always lower then or equal to the highest address that is assigned this process.
    //stacklen -sizeof(void*) is because ptr + stacklen is one too much, the pointer itself is also assigned to the process
    uintptr_t* stackPointer = (uintptr_t*)(((uintptr_t)proc->stack + stacklen - 1) & ~((uintptr_t)0x3));
    //Now start pushing registers
    //The first set of registers are for the interrupt handler, those will be read when the system returns from an interrupt
    //These are in order from down to up: R0, R1, R2, R3, R12, LR, PC, XSPR
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
    *stackPointer = (uintptr_t)param; // reg 0, first param
    //Save the stackpointer to the struct
    proc->stackPointer = (void*)stackPointer;

    //Init the saved temp reg space
    proc->savedRegsPointer = &(proc->savedRegSpace[16]); //Let it point to the first space.
#ifdef DEBUG
    //The second set is the registers that we have to move manually between RAM and regs when switching contexts
    //Order: R4, R5, R6, R7, R8, R9, R10, R11
    //FP: S16, S17, S18, S19, S20, S21, S22, S23, S24, s25, S26, S27, S28, S29, S30, S31
    //FP regs at the top
    uint32_t it = 0;
    for ( uint32_t u = 16; u <= 31; u++){
        proc->savedRegSpace[it] = u;
        ++it;
    }
    //Normal regs at the bottom
    for ( uint32_t u = 4; u <= 11; u++ ){
        proc->savedRegSpace[it] = u;
        ++it;
    }
#endif //DEBUG
}

void initializeProcesses(void){
    for (uint32_t i = 0; i < MAXTOTALPROCESSES; ++i){
        processPool[i].pid = i + 2;
    }
    setupDynamicMem(&idleProcessStruct, (void*)&idleProcStack, IDLEFUNCSTACKLEN, __sleepProcessFunc, NULL);
}

struct Process* createNewProcess(const struct ProcessCreateParams* params, struct Process* parentProc){
    // Sanity of parameter test
    if (params->stacklen < 67 || strlen(params->name) > 31){
        errno = EINVAL;
        return NULL;
    }
    struct Process* newProc = getProcessFromPool();
    if ( newProc == NULL) { //Insufficient mem
        errno = ENOMEM;
        return NULL;
    }
    //Create the stack + processcontext.
    void* stack = malloc(params->stacklen + sizeof(struct ProcessContext));
    if (stack == NULL){
        releaseFromMemPool(newProc);
        errno = ENOMEM;
        return NULL;
    }
    strcpy(newProc->name, params->name);
    char priority = params->priority;
    if (priority == 255) priority = 254; //Max 254, 255 is kernel only
    if (priority == 0) priority = 1;    //Min 1, 0 is sleeper only
    newProc->containsProcess = 1;
    newProc->mPid = parentProc->pid;
    newProc->nextProcess = NULL;
    newProc->nextChildPtr = NULL;
    newProc->priority = priority;
    newProc->state = STATE_READY;
    newProc->hwFlags = PROCESS_DEFAULT;
    if (params->isPrivileged) newProc->hwFlags |= PROCESS_IS_PRIVILEGED;
    newProc->blockAddress = NULL;
    setupDynamicMem(newProc, stack, params->stacklen, params->procFunc, params->param);
    // Add it as a child to its parent
    assignChildToProcess(parentProc, newProc);
    return newProc;
}

int terminateProcess(struct Process* proc, int32_t exitStatus){
    // Set the state to terminated
    proc->state = STATE_TERM;
    // Put all the childeren as children of the kernel
    if (proc->childPtr != NULL){
        assignChildToProcess(&kernelStruct, proc->childPtr);
    }
    // Free the stack
    free(proc->stack);
    proc->retval = exitStatus;
    return 0;
}
