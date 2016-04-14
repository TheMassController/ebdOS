#ifndef ABSTRSYSSLEEPFUNCS_H
#define ABSTRSYSSLEEPFUNCS_H
/**
 * @author Jacko Dirks
 * @file abstrSysSleepFuncs.h
 *
 * Defines some common sleep functions, used by multiple kernel modules.
 */
#include "process.h"
#include "sleep.h"

void translateSleepRequest(struct Process* proc, const struct SleepRequest* sleepReq);

#endif //ABSTRSYSSLEEPFUNCS_H
