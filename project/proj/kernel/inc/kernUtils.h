#ifndef KERNUTILS_H
#define KERNUTILS_H
/* Contains misc functions that help the kernel do its thing
 */

/** 
 * @brief Crashes the kernel when there is a non-recoverable issue. 
 * Generates the NMI. This function does not really return
 */
#ifdef __GNUC__
void generateCrash(void) __attribute__ ((noreturn));
#else
void generateCrash(void);
#endif //__GNUC__

#endif //KERNUTILS_H
