//The (external) assembly functions
void * pushRegistersToCurrentPSP(int iVar);
void popRegistersFromCurrentPSP(int iVar);
void * readPSP(int iVar);
void writePSP(void * ptr);
void * readMSP(int iVar);
void writeMSP(void * ptr);
int testFunc(void);
void* getR7(void* ptr);
