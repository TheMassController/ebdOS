#include <stdlib.h>                     // Declares void abort(void)

#include "kernel/inc/supervisorCall.h" // Contains the supervisor codes and call

void abort(void){
    CALLSUPERVISOR(SVC_abort);
    while(1); // This is required because abort cannot return and we have to prove to the compiler that it indeed cannot return. In reality this specific SVC call will never return.
}
