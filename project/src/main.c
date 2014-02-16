#include "stdio.h"
#include "stdlib.h"

int main(void){
//	printf("Hello, World!\n");
	int i = 5;
	int *j = NULL;
	j = (int*)malloc(sizeof(int));	
	if (j ==  NULL){
		for(;;); //On failure, the program hangs here
	}
//	printf("%d = i, %p = j",i,(void*)j);
	while(1); //On success the program hangs here
}
