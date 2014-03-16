#include "stdio.h"
#include "stdlib.h"
#include "rom_map.h"
#include "rom.h"
#include "hw_types.h"
#include "uart.h"
#include "uartstdio.h"

int main(void){
	UARTprintf("Hello, World!\n");
	int i = 2;
	int *j = NULL;
	j = (int*)malloc(sizeof(int));	
	//Check the cpu speed
	unsigned long cpuSpeed = ROM_SysCtlClockGet();	
	if ((j ==  NULL)| (cpuSpeed != 80000000)){
		for(;;); //On failure, the program hangs here
	}
	UARTprintf("i=%x\r\n",i);
	while(1); //On success the program hangs here
}
