#include "stdlib.h" //Malloc
#include "uartstdio.h" //For printf, scanf
#include "process.h"
#include "lm4f120h5qr.h"

extern struct Process* processesReady;
extern struct Process* kernel;
extern struct Process* nextProcess;
extern struct Process* currentProcess;

#define UNUSED(x) (void)(x) //To suppress compiler warning

void testFunction1(void* param){
    UNUSED(param);
    UARTprintf("testFunction1 says hi!\r\n");
    nextProcess = processesReady->nextProcess;
    NVIC_INT_CTRL_R |= (1<<28);
}

void testFunction2(void* param){
    UNUSED(param);
    UARTprintf("testFunction2 says hi!\r\n");
    nextProcess = kernel;
    NVIC_INT_CTRL_R |= (1<<28);
    
}

int testProcessStructure(void){
    int retcode;
    retcode = __createNewProcess(0, 1024, "testproc1", &testFunction1, NULL, 240);
    retcode = __createNewProcess(0, 1024, "testproc2", &testFunction2, NULL, 240);
    UARTprintf("Functions created. Code: %d\r\n",retcode);
    UARTprintf("Kernel says hi!\r\n");
    //Do a pendSV interrupt
    nextProcess = processesReady;
    NVIC_INT_CTRL_R |= (1<<28);
    UARTprintf("Kernel says hi, once again!\r\n");
    if (currentProcess != nextProcess) retcode = 2;   
    if (retcode == 1) retcode = 11;
    if (!retcode) retcode = 1;
    return retcode;
}

