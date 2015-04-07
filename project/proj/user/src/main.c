#include "validation.h"
#include "uartstdio.h"
#include "asmUtils.h"
#include "process.h"
#include <stdlib.h>

void ledsDanceMain(void);

int main(void){
    //TODO
    //Test sleep
    //Test mutex
    //rest semaphores
    //Test the combination of sleep and mutex (blockandwait)
    //return testScheduler();
    //if(__createNewProcess(0, 512, "testFloat", testFloatMain, NULL, 5) == 2){
    //    UARTprintf("FAILURE\r\n");
    //}
    UARTprintf("%u\n", sizeof(unsigned));
    ledsDanceMain();
}
