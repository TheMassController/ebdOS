#ifndef SYSCALLS_H
#define SYSCALLS_H

/**
    RETCODES:
    0: sucess
    2: unknown error
**/

int createProcess(unsigned long stacklen, char* name, void (*procFunc)(), void* param, char priority);
#endif //SYSCALLS_H
