#include "stdlib.h" //Malloc
#include "rom.h" //rom_ funcs
#include "uartstdio.h" //For printf, scanf

#include "getSetRegisters.h" //ASM funcs for getting CPU regs
#include "asmUtils.h"
#include "validation.h" 
#include "sleep.h"
#include "string.h"
#include "process.h"
#include "supervisorCall.h"

int validationStuffz(void){
    int testRet = testUARTstdio();
    int failure = 0;
    if (testRet != 1){
        UARTprintf("TestUARTstdio failure %d\n",testRet);
        failure = 1;
    }
    testRet = testProcessStructure();
    if (testRet != 1){
        UARTprintf("testProcessStructure failure %d\n",testRet);
        failure = 1;
    }
    testRet = testSVCcall();
    if (testRet != 1){
        UARTprintf("TestSVCcall failure %d\n",testRet);
        failure = 1;
    }
    if (failure){
        UARTprintf("Run failed!");
    } else {
        UARTprintf("Great Succes!");
    }
    UARTprintf(" (Run finished)\r\n");
	while(1){ //On success the program hangs here
        waitForInterrupt();
    }
}

struct SleepTimeStruct{
    unsigned runTimeMS;
    char* name;
};

void testProcess(void* sleepTimeStruct){
    struct SleepTimeStruct* intel = (struct SleepTimeStruct*)sleepTimeStruct;
    while(1){
        UARTprintf("Process %s, which runs every %d ms, has just ran\r\n",intel->name, intel->runTimeMS);
        sleepMS(intel->runTimeMS);
    }
    free(intel->name);
    free(sleepTimeStruct);
}

int main(void){
    //Spawn three processes: 1 sec, 10 sec, 30 sec
    struct SleepTimeStruct* structs[3];
    //The first one
    structs[0] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[0]->name = (char*)malloc(strlen("timeoutProc1s"));
    strcpy(structs[0]->name,"timeoutProc1s");
    structs[0]->runTimeMS = 1000;
    __createNewProcess(0, 256, "timeoutProc1s", &testProcess, structs[0], 2);  
    structs[1] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[1]->name = (char*)malloc(strlen("timeoutProc10s"));
    strcpy(structs[1]->name,"timeoutProc10s");
    structs[1]->runTimeMS = 10000;
    __createNewProcess(0, 256, "timeoutProc10s", &testProcess, structs[1], 1);  
    structs[2] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[2]->name = (char*)malloc(strlen("timeoutProc30s"));
    strcpy(structs[2]->name,"timeoutProc30s");
    structs[2]->runTimeMS = 30000;
    __createNewProcess(0, 256, "timeoutProc30s", &testProcess, structs[2], 0);  
}
