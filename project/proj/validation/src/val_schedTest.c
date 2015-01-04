#include "validation.h"
#include "process.h" 
#include "sleep.h"
#include "stdlib.h" 
#include "uartstdio.h" 
#include "string.h" 

struct SleepTimeStruct{
    unsigned runTimeMS;
    char* name;
};

void testProcess(void* sleepTimeStruct){
    struct SleepTimeStruct* intel = (struct SleepTimeStruct*)sleepTimeStruct;
    unsigned sleepTime = 0;
    unsigned wakeTime = 0;
    while(1){
        UARTprintf("Process %s, which runs every %d ms, has just ran. Time since last run: %u\r\n",intel->name, intel->runTimeMS, sleepTime - wakeTime);
        sleepTime = getCurrentSleepTimerValue();
        sleepMS(intel->runTimeMS);
        wakeTime = getCurrentSleepTimerValue();
    }
    free(intel->name);
    free(sleepTimeStruct);
}

int testScheduler(void){
    //Spawn three processes: 1 sec, 10 sec, 30 sec
    struct SleepTimeStruct* structs[3];
    //The first one
    structs[0] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[0]->name = (char*)malloc(strlen("timeoutProc1s")+1);
    strcpy(structs[0]->name,"timeoutProc1s");
    structs[0]->runTimeMS = 1000;
    if (__createNewProcess(0, 256, "timeoutProc1s", &testProcess, structs[0], 2) == 2){
        UARTprintf("Could not create process timeoutProc1s\r\n");         
    }
    structs[1] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[1]->name = (char*)malloc(strlen("timeoutProc10s")+1);
    strcpy(structs[1]->name,"timeoutProc10s");
    structs[1]->runTimeMS = 10000;
    if (__createNewProcess(0, 256, "timeoutProc10s", &testProcess, structs[1], 1) == 2){
        UARTprintf("Could not create process timeoutProc10s\r\n");
    }
    structs[2] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[2]->name = (char*)malloc(strlen("timeoutProc30s")+1);
    strcpy(structs[2]->name,"timeoutProc30s");
    structs[2]->runTimeMS = 30000;
    if(__createNewProcess(0, 256, "timeoutProc30s", &testProcess, structs[2], 2) == 2){
        UARTprintf("Could not create process timeoutProc30s\r\n");
    }
    UARTprintf("Test prepared\r\n");
    return 1;
}

