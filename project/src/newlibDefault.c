//This file contains all implementations of necessary system functions as defined in the documentation: file:///home/jacko/Downloads/gcc-arm-none-eabi-4_8-2013q4/share/doc/gcc-arm-none-eabi/html/libc/Stubs.html#Stubs
#include <errno.h>
#undef errno
extern int errno;

char *__env[1] = { 0 };
char **environ = __env;

int close(int file){
	return -1;
}

int execve(char *name, char **argv, char **env) {
	errno = ENOMEM;
	return -1;
}


