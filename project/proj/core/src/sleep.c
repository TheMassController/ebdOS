//Contains all sleep related code

#include "hw_nvic.h"
#include "hw_types.h"
#include "uartstdio.h"
#include "timer.h"
#include "lm4f120h5qr.h" //Hardware regs
#include "hw_memmap.h" //address of GPIO etc
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs

unsigned sleepClocksPerMS = 0;

void sleepTimerInterrupt(void){
    ROM_TimerIntClear(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
    UARTprintf("Apparently, almost 40 days have passed");
}

//The second sleeper
void sleepS(unsigned seconds){

}

//The millisecond sleeper
void sleepMS(long ms){
}
