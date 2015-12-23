#ifndef CONTEXT_H
#define CONTEXT_H
/**
 * @brief Contains the process context, this is a set of variables that is unique per process and accesseble for the process itself.
 *
 * An example of this is errno. This part is heavily used by the syscall layer.
 */

struct ProcessContext {
    /* Syscall layer variables */
    unsigned comVal;
    unsigned retVal;
    void* genericPtr;
    /* General variables */
    int context_errno;
};

extern struct ProcessContext* currentContext;
#endif //CONTEXT_H
