#include "validation.h"
#include "uartstdio.h"
#include "coreUtils.h"
#include "process.h"
#include "sysCalls.h"
#include <stdlib.h>
#include "sleep.h"

void ledsDanceMain(void);

int main(void){
    //TODO
    //Test sleep
    //Test mutex
    //rest semaphores
    //Test the combination of sleep and mutex (blockandwait)
    //return testScheduler();
    if(createProcess(512, "testFloat", testFloatMain, NULL, 5) == 2){
        UARTprintf("FAILURE\r\n");
    }
    ledsDanceMain();
    while(1) sleepS(100);
}
