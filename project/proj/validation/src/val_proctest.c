#include "stdlib.h" //Malloc
#include "uartstdio.h" //For printf, scanf
#include "processManagement.h"
#include "process.h"

extern struct Process* firstProcess;

void testFunction(void){
    while(1); //Placeholder
}

int testProcessStructure(void){
    int retcode;
    retcode = __createNewProcess(0, 1024, "testproc1", (processFunc)&testFunction, NULL);
    retcode = __createNewProcess(0, 1024, "testproc2", (processFunc)&testFunction, NULL);
    UARTprintf("Functions created. Code: %d",retcode);
    if (!retcode) retcode = 1;
    return retcode;
}

