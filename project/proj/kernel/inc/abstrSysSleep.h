#ifndef ABSTRSYSSLEEP_H
#define ABSTRSYSSLEEP_H
/**
 * @author Jacko Dirks
 * @file abstrSysSleep.h
 *
 * Defines some common sleep structs and functions, used by multiple kernel modules.
 */

struct SleepingProcessStruct {
    unsigned overflows;
    unsigned sleepUntil;
};

#endif //ABSTRSYSSLEEP_H
