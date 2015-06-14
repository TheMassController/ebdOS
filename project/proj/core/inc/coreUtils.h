#ifndef COREUTILS_H
#define COREUTILS_H
/* coreUtils.h: Provides common utility functions. Many have been written in assembly
 */

void waitForInterrupt(void);
int isInInterrupt(void);
void zeroFillSection(void* startPtr, void* endPtr);

#endif //COREUTILS_H
