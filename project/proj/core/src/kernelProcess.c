//The functions of the actual kernel: this is the kernel process
#include "process.h"
#include "kernelQueue.h"
#include "binarySemaphore.h"
#include "uartstdio.h"

extern struct Process* currentProcess;
struct BinarySemaphore binSemKern;

void kernelMain(void){
    initBinarySemaphore(&binSemKern);
    lockBinarySemaphoreBlocking(&binSemKern);
    lockBinarySemaphoreBlocking(&binSemKern);
    UARTprintf("Mine?\r\n");
}
