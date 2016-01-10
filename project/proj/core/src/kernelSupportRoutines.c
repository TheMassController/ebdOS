/*
 * This file contains some functions that are necesary for the kernel to do its work correctly, but can also be executed from process mode.
 * For now the following function exsists:
 * - Idle process: this process runs when no other process runs. We do not want it to be privileged
 * - Return function: This is the function any process returns to after run. From here on out it will yield all its timeslices (to be implemented)
 *
 */
#include <uartstdio.h>
#include <stdlib.h>

#include "coreUtils.h"
#include "process.h"
#include "sysCalls.h"
struct ProcessContext* currentContext;

void __sleepProcessFunc(void){
    while(1){
        waitForInterrupt();
    }
}

void __processReturn(void){
    exit(0);
}

