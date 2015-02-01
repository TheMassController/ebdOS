//The functions of the actual kernel: this is the kernel process
#include "process.h"
#include "kernelQueue.h"
#include "binaryMutex.h"
#include "uartstdio.h"

extern struct Process* currentProcess;
struct BinaryMutex binMutKern;

void kernelMain(void){
    initBinaryMutex(&binMutKern);
    lockBinaryMutexBlocking(&binMutKern);
    lockBinaryMutexBlocking(&binMutKern);
    UARTprintf("Mine?\r\n");
}
