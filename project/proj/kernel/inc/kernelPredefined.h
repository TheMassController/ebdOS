/**
 * @author Jacko Dirks
 * @file kernelPredefined.h
 * This file is used to compile the limits of the memory pools into the operating systems.
 * All variables here are directly related to the kernel mempools: if you encouter a lot of ENOMEM errors, you should probably change something here.
 */
#ifndef KERNELPREDEFINED_H
#define KERNELPREDEFINED_H

// The maximal amount of managed locks that can exist
#define MANAGEDLOCKCOUNT 30
// The next var is only about user processes, the kernel-based processes (kernel itself and idle) are counted seperately
#define MAXTOTALPROCESSES 10

#endif //KERNELPREDEFINED_H
