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
    while(1){
        UARTprintf("Process %s, which runs every %d ms, has just ran\r\n",intel->name, intel->runTimeMS);
        sleepMS(intel->runTimeMS);
    }
    free(intel->name);
    free(sleepTimeStruct);
}

int testScheduler(void){
    //Spawn three processes: 1 sec, 10 sec, 30 sec
    struct SleepTimeStruct* structs[3];
    //The first one
    structs[0] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[0]->name = (char*)malloc(strlen("timeoutProc1s"));
    strcpy(structs[0]->name,"timeoutProc1s");
    structs[0]->runTimeMS = 1000;
    __createNewProcess(0, 1024, "timeoutProc1s", &testProcess, structs[0], 2);
    //structs[1] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    //structs[1]->name = (char*)malloc(strlen("timeoutProc10s"));
    //strcpy(structs[1]->name,"timeoutProc10s");
    //structs[1]->runTimeMS = 10000;
    //__createNewProcess(0, 256, "timeoutProc10s", &testProcess, structs[1], 1);
    //structs[2] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    //structs[2]->name = (char*)malloc(strlen("timeoutProc30s"));
    //strcpy(structs[2]->name,"timeoutProc30s");
    //structs[2]->runTimeMS = 30000;
    //__createNewProcess(0, 256, "timeoutProc30s", &testProcess, structs[2], 0);
    return 1;
}

