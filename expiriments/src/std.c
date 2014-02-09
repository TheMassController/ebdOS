#include "std.h"
static uint16_t const totalMemSize = 16000;
static char memory[16000]; //Points to the malloced memory
static MappedMem *mappedMem; //Points to the first mappedMem

uint16_t translateRealToVirtualAddress(void* realAddr){
	size_t stBeginAddr = (size_t)&memory[0];
	size_t stEndAddr = (size_t)&memory[totalMemSize-1];
	size_t stAskedAddr = (size_t)realAddr;
	if (stAskedAddr < stBeginAddr || stAskedAddr > stEndAddr) return totalMemSize;
	return (uint16_t)(stAskedAddr - stBeginAddr);
}

void* translateVirtualToRealAddress(uint16_t virtualAddr){
	if (virtualAddr > totalMemSize -1){
		return NULL;
	}
	return &memory[virtualAddr];
}

MemoryData getMemoryData(void){
	MemoryData memoryData;
	memoryData.totalMem = totalMemSize;
	uint16_t ui16TotalFree = totalMemSize;
	uint16_t objectAmount = 0;
	if (mappedMem != NULL){ //If there is no memory allocated at all, skip this step entirely
		for (MappedMem* myMappedMem = mappedMem; myMappedMem != NULL; myMappedMem = translateVirtualToRealAddress(myMappedMem->nextMem)){
			ui16TotalFree -= myMappedMem->size;
			++objectAmount;
		}
	}
	memoryData.memFree = ui16TotalFree;
	memoryData.memInUse = totalMemSize - ui16TotalFree;
	memoryData.objectAmount = objectAmount;
	memoryData.metaDataSize = objectAmount * sizeof(MappedMem);
	memoryData.realObjSize = memoryData.memInUse - memoryData.metaDataSize;
	return memoryData;
}

void* malloc(size_t stAmount){
	//First: find a free spot. 
	//I am working with the exact or worst fit implementation
	//if mappedMem is empty, skip this entire step
	size_t stAmountNecessary = stAmount + sizeof(MappedMem); //The size we need to find
	if (stAmountNecessary > totalMemSize){
		return NULL; //Requested amount of space is too big either way
	}
	//uint16_t ui16AmountNecessary = (uint16_t)stAmountNecessary;
	void* vPtrFirstMemAddr = memory;
	MappedMem* prevMappedMem = mappedMem; //The address of mappedmem where this new mappedMem must be linked to in order to get the correct order (order is vital). 
	if (mappedMem != NULL) {
		vPtrFirstMemAddr = NULL; //Give this thing a value that indicates that no memory place has been found yet
		size_t stBiggestFreeBlockSize = 0;
		size_t stBiggestFreeBlock = 0;
		size_t stLastBytePos = (size_t)&memory[0]; //Set at the start of the memory
		size_t stOwnPosition = (size_t)mappedMem; //Set at the start of the linkedList
		size_t stFreeSpace;
		MappedMem* searchMap = mappedMem;
		MappedMem* lastMem = (void*)memory;
		do {
			if ((stFreeSpace = stOwnPosition - stLastBytePos) > 0){ //If the difference is 0, there is no free space in between these positions.
				if (stFreeSpace == stAmountNecessary){ //Yay! Exact fit. Return the addr of the first byte that is free
					vPtrFirstMemAddr = (void*)stLastBytePos;
					prevMappedMem = lastMem; //Update the pointer to the object
					break;
				}
				
				if (stFreeSpace > stBiggestFreeBlockSize){ //We found a new biggest free block, 
					stBiggestFreeBlockSize = stFreeSpace;
					stBiggestFreeBlock = stLastBytePos;
					prevMappedMem = lastMem; //Move the indicator which indicates where the new object should be linked to one forward
				}
			} //diff = 0
			stLastBytePos = stOwnPosition + searchMap->size;
			stOwnPosition = (size_t)translateVirtualToRealAddress(searchMap->nextMem);
			lastMem = searchMap;
			if (searchMap->nextMem == 16000){ //Seems really dirty, I know no ways of fixing it
				break;
			}
		} while((searchMap = (void*)stOwnPosition) != NULL); //There is no next one 
		//Check the space between the last mappedMem and the end of the memory
		if (vPtrFirstMemAddr == NULL){ //Only if a space has not already been found
			if ((stFreeSpace =  (size_t)&memory[totalMemSize - 1] - stLastBytePos)  == stAmountNecessary){ //Yay! Exact fit. Return the addr of the first byte that is free
				vPtrFirstMemAddr = (void*)stLastBytePos;
			 	prevMappedMem = searchMap; //Update the pointer to the object
			}
			if (stFreeSpace > stBiggestFreeBlockSize){
					stBiggestFreeBlockSize = stFreeSpace;
    	        	stBiggestFreeBlock = stLastBytePos;
		    	    stBiggestFreeBlockSize = stFreeSpace;
		    	    prevMappedMem = searchMap; //Update the pointer to the object
			}
			if ((stBiggestFreeBlockSize >= stAmountNecessary ) && (vPtrFirstMemAddr == NULL)){ //Only if the amount of mem found is big enough, and a correct position was not yet found
				vPtrFirstMemAddr = (void*)stBiggestFreeBlock;
			}
			if (vPtrFirstMemAddr == NULL){
				return NULL; //There was not enough space linked together anywhere in the memory to fit this object
			}
		}
	}
	//Now that we know the address to write to, start writing!
//	void* vPtrFirstMemAddr = memory;
//	MappedMem* prevMappedMem = mappedMem; //The address of mappedmem where this new mappedMem must be linked to in order to get the correct order (order is vital). 
	//First: create the MappedMem and write down its size
	MappedMem* newMappedMem = vPtrFirstMemAddr;
	newMappedMem->size = (uint16_t)stAmountNecessary;
	//move the memory pointer to the first address of the actual object
	vPtrFirstMemAddr = (void*)((size_t)vPtrFirstMemAddr + sizeof(MappedMem));
	//Set the memaddr
	newMappedMem->memaddr = translateRealToVirtualAddress(vPtrFirstMemAddr);
	//Set the nextMem and, if necessary, change the address of the previous MappedMem
	if (prevMappedMem == NULL){ //This is for when there are no other allocations
		mappedMem = newMappedMem;
		newMappedMem->nextMem = 16000; //Set the vMemAddr to 16000 because it translates to NULL, indicating that there is no next
	} else if (prevMappedMem == (void*)memory && prevMappedMem != mappedMem) { //Indicating that this object is being created at the begin of the RAM, as the new First item
		newMappedMem->nextMem = translateRealToVirtualAddress(mappedMem);
		mappedMem = newMappedMem;	
	} else {
		newMappedMem->nextMem = prevMappedMem->nextMem;
		prevMappedMem->nextMem = translateRealToVirtualAddress(newMappedMem);
	}
	return vPtrFirstMemAddr;
	
}	

void free(void* ptr){
	//Looks for the right item in the linked list and then removes it from the list
	if (ptr == NULL){ //If given an easy task, give the easy answer
		return;
	}
	uint16_t ui16VirtualRemMemAddr = translateRealToVirtualAddress(ptr);
	MappedMem* previousMap = NULL;
	MappedMem* mapToRemove = NULL;
	for (MappedMem* searchMap = mappedMem; searchMap != NULL; searchMap = translateVirtualToRealAddress(searchMap->nextMem)){
		if (ui16VirtualRemMemAddr == searchMap->memaddr){
			mapToRemove = searchMap;
			break;
		}
		previousMap = searchMap;
	}
	if (mapToRemove == NULL){
		return;
	}
	if (previousMap == NULL) { //This was apparently the first map in the list
		if (mapToRemove->nextMem == 16000) { //And also the last one
			mappedMem = NULL;
			return;
		}
		mappedMem = translateVirtualToRealAddress(mapToRemove->nextMem); //Just shift the list back by removing the first item
		return;
	}
	previousMap->nextMem = mapToRemove->nextMem; //Just remove it from the list by connecting the previous to the next
	return;
}
