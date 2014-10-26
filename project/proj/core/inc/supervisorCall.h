//Contains the macro to create the supervisor call
#define CALLSUPERVISOR(code) CALLSUPERVISOR_HELPER(#code) //Add quotes around the literal number
#define CALLSUPERVISOR_HELPER(code)__asm__("svc "code); //Inject the code into the ASM

