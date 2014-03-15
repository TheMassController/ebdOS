#include "stdio.h"
#include "stdlib.h"
#include "rom_map.h"
#include "rom.h"

int main(void){
	printf("Hello, World!\n");
	int i = 2;
	int *j = NULL;
	j = (int*)malloc(sizeof(int));	
	//Check the cpu speed
	unsigned long cpuSpeed = ROM_SysCtlClockGet();	
	if ((j ==  NULL)| (cpuSpeed != 80000000)){
		for(;;); //On failure, the program hangs here
	}
	printf("i=%x\r\n",i);
	while(1); //On success the program hangs here
}
