#include "regDumpLoad.h"
#include "stdlib.h" 

int testRegDumpLoad(void){
    //Heap size is 8 * 32 bit = 256 bit = 32 byte
    const int HEAPSIZE = 32;
    void* regdumpLoc = malloc(HEAPSIZE);
    char* regloc = (char*)regdumpLoc;
    long* convience = (long*)regdumpLoc;
    void* regdumplocEnd = regDump(regdumpLoc);
    void* calculatedEnd = (void*)((char*)regdumpLoc - 32);
    if (!(regdumplocEnd == calculatedEnd)){
        return 0;
    }
    void* regdumplocStart = regLoad(regdumplocEnd);
    if (!(regdumplocStart == regdumpLoc)){
        return 0;
    }
    for (int i = 0; i < 8; ++i){
        convience[i] = 0x01010101;
    }
    regdumplocStart = regLoad(regdumplocEnd); 
    void* regdumpLoc2 = malloc(HEAPSIZE);
    regdumpLoc2  = (void*)((char*)regdumpLoc2 - 32);
    regdumplocEnd = regDump(regdumpLoc2);
    for (int i = 0; i < HEAPSIZE; ++i){
        if (!(regloc[i] == i)){
            return 0;
        }
    }
    return 1;
}
