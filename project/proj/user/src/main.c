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
#include "mutex.h" 

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

struct MutexStruct{
    Mutex* mutex;
};

void testProcess1(void* mutexstruct){
    struct MutexStruct* mutexStruct = (struct MutexStruct*)mutexstruct;
    lockMutex(mutexStruct->mutex);
    sleepS(2);
    releaseMutex(mutexStruct->mutex);
    UARTprintf("success!\r\n");
}

void testProcess2(void* mutexstruct){
    struct MutexStruct* mutexStruct = (struct MutexStruct*)mutexstruct;
    lockMutex(mutexStruct->mutex);
}

int main(void){
    struct MutexStruct* mutexS = (struct MutexStruct*)malloc(sizeof(struct MutexStruct));
    mutexS->mutex = createMutex();
    __createNewProcess(0, 256, "testProcess1", &testProcess1, mutexS, 2);  
    __createNewProcess(0, 128, "testProcess2", &testProcess2, mutexS, 1);
}
