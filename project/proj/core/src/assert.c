#include <assert.h>
#include <uartstdio.h>
#include <stdlib.h>

void __assert_func (const char* fileName, int lineNum, const char* funcName, const char* msg){
    UARTprintf("Assertion failure: %s:%d, %s (%s)", fileName, lineNum, funcName, msg);
    abort();
}
