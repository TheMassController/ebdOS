/**
@file std.h
@author Jacko Dirks
@brief This file contains functions and includes that every other header will need to include, like myAlloc.

Virtualaddress points to the place in the character array, real address is the address it got from the OS.
**/
#ifndef STD_H
#define STD_H
#include <stdio.h>
#include <stdint.h>
//#include <stdlib.h>

/**
@struct MappedMem
@brief This struct is used by the memory management. It is a LinkedList

It contains the address that is returned, the size of the block and the location of the next mappedMem.
All addresses are represented as virtual addresses (adresses in the char[])
*/
typedef struct{
	uint16_t memaddr; //This is the virtual representation of the address that is returned by malloc
	uint16_t size; //This is the total size: including metadata.
	uint16_t nextMem;
} MappedMem;

/**
@struct MemoryData
@brief This structure contains data about the memory. All values are in byte, except when stated differently
*/
typedef struct{
	uint16_t totalMem;
	uint16_t memFree;
	uint16_t memInUse;
	uint16_t objectAmount; //Amount of objects currently residing in memory (object = MappedMem)
	uint16_t metaDataSize; //Amount of the memInUse that is metadata
	uint16_t realObjSize; //Amount of the memInUse that is part of the real object
} MemoryData;


/**
@brief this function allocates memory
@param amount The amount of memory (in byte) that will be allocated
@return A pointer to the first address 
*/
void* malloc(size_t stAmount);
/**
@brief The inverse of myAlloc: this cuntion frees the memory again.
@param ptr The pointer containing the memory address that I want freed
*/
void free(void* ptr);

/**
@brief This function looks trough the mappedMem array for the correct memory address
@param realAddr The real address of the pointer
@return The virtual address of the pointer, totalMemSize if not found.
*/
uint16_t translateRealToVirtualAddress(void* realAddr);
/**
@brief This function returns the address of an index in the array and NULL if not found
@param virtualAddr The place in the char *memory where this address resides.
@return The actual address of this place, NULL if arrIndex > totalMemSize-1;
*/
void* translateVirtualToRealAddress(uint16_t virtualAddr);
/**
@brief Gets the total amount of free RAM
@return Amount of memory free in bytes
*/
MemoryData getMemoryData(void);
#endif
