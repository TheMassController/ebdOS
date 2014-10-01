#include "process.h"
#include "processManagement.h"
#include "getSetRegisters.h"
#include "regDumpLoad.h"
#include "stdlib.h"
#include "asmUtils.h"

//Defines for correct returns
// See datasheet pp 106
// pendSVHandler has been moved to assembly
#define PSPNONFP_RETURN ((unsigned)0xFFFFFFFD)
#define MSPNONFP_RETURN ((unsigned)0xFFFFFFF9)
#define PSPFP_RETURN    ((unsigned)0xFFFFFFED)
#define MSPFP_RETURN    ((unsigned)0xFFFFFFE9)

// This file handles scheduling, basically

extern struct Process* kernel;
extern struct Process* currentProcess;
extern struct Process* firstProcess;
extern struct Process* nextProcess;

void schedule(void){
//The actual scheduler. 
}
