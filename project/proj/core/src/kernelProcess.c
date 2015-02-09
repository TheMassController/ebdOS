//The functions of the actual kernel: this is the kernel process
#include "process.h"
#include "binarySemaphore.h"
#include "uartstdio.h"

extern struct Process* currentProcess;
struct BinarySemaphore binSemKern;

void popAndProcessItem(void);

void kernelMain(void){
    while(1){
        popAndProcessItem();
    }
}
