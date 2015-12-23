#include <errno.h>

#include "context.h"


error_t* __errno(void){
    return &(currentContext->context_errno);
}
