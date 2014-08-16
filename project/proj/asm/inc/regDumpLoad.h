//Register dump and load functions
//The MSP will never be dumped. R0-12, PSP, LR and PC are dumped to the given memory location or loaded from it.

void* regDump(void* dumpLocation);
void* regLoad(void* loadLocation);
