//External headers
#include <stdlib.h>
//Internal headers
#include "scheduler.h"  // Contain the declarations for all functions defined here.
#include "process.h"    // The struct Process, a lot of defines related to processes.
//TODO make processesReady static.
struct Process* processesReady = NULL;

void sysTickHandler(void){

}
