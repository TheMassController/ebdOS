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
#include "threadsafeCalls.h"

extern struct Process* currentProcess;

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
    UARTprintf("Process with pid %d and prio %d is trying to lock mutex.\r\n",currentProcess->pid, currentProcess->priority);
    lockMutex(mutexStruct->mutex);
    UARTprintf("Process with pid %d and prio %d has locked mutex and is falling asleep for 2 seconds\r\n", currentProcess->pid, currentProcess->priority);
    sleepS(2);
    releaseMutex(mutexStruct->mutex);
    UARTprintf("Process with pid %d and prio %d has just released mutex\r\n", currentProcess->pid, currentProcess->priority);
}

void testProcess2(void* mutexstruct){
    struct MutexStruct* mutexStruct = (struct MutexStruct*)mutexstruct;
    UARTprintf("Process with pid %d is trying to lock mutex.\r\n",currentProcess->pid);
    lockMutex(mutexStruct->mutex);
}

int mutexTest(void){
    struct MutexStruct* mutexS = (struct MutexStruct*)malloc(sizeof(struct MutexStruct));
    mutexS->mutex = createMutex();
    __createNewProcess(0, 300, "testProcess2", &testProcess1, mutexS, 99);
    __createNewProcess(0, 300, "testProcess4", &testProcess1, mutexS, 100);
    __createNewProcess(0, 300, "testProcess3", &testProcess1, mutexS, 97);
    __createNewProcess(0, 300, "testProcess1", &testProcess1, mutexS, 100);  
    return 1;
}

int main(void){
    MultiLockObject* mLockObject = __createMultiLockObject(3);
    UARTprintf("MaxLockVal: %d\r\n", __getMultiLockMaxVal(mLockObject));
    for (int i = 0; i < 5; ++i){
        UARTprintf("mLockObject increasing: %d\r\n", __increaseMultiLockObjectNoBlock(mLockObject)); 
    }
    for (int i = 4; i >=0 ; --i){
        UARTprintf("mLockObject decreasing: %d\r\n", __decreaseMultiLockObjectNoBlock(mLockObject)); 
    }
    
}
