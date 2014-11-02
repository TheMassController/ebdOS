#ifndef SLEEP_H
#define SLEEP_H

//This header file is user-facing, meaning that all functions defined here can safely be used by an user. As opposed to functions which should only be called by the kernel or related interrupts

void sleepMS(unsigned long ms);
void sleepS(unsigned seconds);
unsigned getCurrentSleepTimerValue(void);
#endif //SLEEP_H
