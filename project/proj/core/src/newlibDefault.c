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

//Even easier implementations
int _close(int file)
{
    return -1;
}

int _fstat(int file)
{
    return -1;
}

int _isatty(int file)
{
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    return -1;
}

int _open(const char *name, int flags, int mode)
{
    return -1;
}

//int _read(int file, char *ptr, int len)
//{
//	return -1;
//    //unsigned int i;
//    //for( i = 0; i < len; i++ ){
//    //    ptr[i] = (char)MAP_UARTCharGet(UART0_BASE);
//    //}
//    //return len;
//}
//
//int _write(int file, char *ptr, unsigned int len)
//{
//	return -1;
//    //unsigned int i;
//    //for(i = 0; i < len; i++){
//    //    MAP_UARTCharPut(UART0_BASE, ptr[i]);
//    //}
//    //return i;
//}

