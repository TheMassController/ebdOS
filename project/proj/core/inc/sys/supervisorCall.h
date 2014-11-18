//The codes
#define SVC_reschedule "0"
#define SVC_objectLock "1"
#define SVC_objectRelease "2"
#define SVC_sleep "3"
#define SVC_test "255"        
//Contains the macro to create the supervisor call
#define CALLSUPERVISOR(code) __asm__("svc "code); //Inject the code into the ASM
