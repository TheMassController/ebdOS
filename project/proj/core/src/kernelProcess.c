//The functions of the actual kernel: this is the kernel process
#include "process.h"
#include "kernelQueue.h"

extern struct Process* currentProcess;

void kernelMain(void){
    currentProcess->state |= STATE_WAIT;
    while(1){
        
    } 
}
