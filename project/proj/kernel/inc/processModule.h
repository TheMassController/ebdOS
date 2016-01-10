#ifndef PROCESSMODULE_H
#define PROCESSMODULE_H

#include "process.h"

/**
 * @brief The actual call to create a new process
 * @param params A struct containing the necessary information to create the process
 * @param parentProc A pointer to the new parent
 * @return NULL if something went wrong (errno will be set), pointer to the newly created process if everything was ok.
 */
struct Process* createNewProcess(const struct ProcessCreateParams* params, struct Process* parentProc);

/**
 * @brief Terminates a process, zombie-fying it until the parent reads the exit value.
 * @return 0 if everything was ok, errno code if not.
 */
int terminateProcess(struct Process* proc, int32_t exitStatus);
#endif //PROCESSMODULE_H
