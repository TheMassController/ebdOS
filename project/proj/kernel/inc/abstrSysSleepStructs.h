#ifndef ABSTRSYSSLEEPSTRUCTS_H
#define ABSTRSYSSLEEPSTRUCTS_H
/**
 * @author Jacko Dirks
 * @file abstrSysSleepStructs.h
 *
 * Defines some common sleep structs, used by multiple kernel modules.
 */

struct SleepingProcessStruct {
    unsigned overflows;
    unsigned sleepUntil;
};

#endif //ABSTRSYSSLEEPSTRUCTS_H
