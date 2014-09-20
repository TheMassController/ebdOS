void waitForInterrupt(void);

//The void* becomes the content of the LR, then the LR will be pushed to PC.
void forceManualReturn(void*);
