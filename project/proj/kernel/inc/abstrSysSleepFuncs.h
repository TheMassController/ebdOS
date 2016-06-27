#ifndef ABSTRSYSSLEEPFUNCS_H
#define ABSTRSYSSLEEPFUNCS_H
/**
 * @author Jacko Dirks
 * @file abstrSysSleepFuncs.h
 *
 * Defines some common sleep functions, used by multiple kernel modules.
 */
#include "process.h"
#include "core/inc/sleep.h"
/**
 * @brief Translates a sleepRequest struct to a number of overflows and an additional amount of time, to be written down in the process itself
 * @param proc The target proc
 * @param sleepReq The struct
 */
void translateSleepRequest(struct Process* proc, const struct SleepRequest* sleepReq);

#endif //ABSTRSYSSLEEPFUNCS_H
