//Handles the threadsafe calls and the waiting state
#ifndef THREADSAFECALLS_H
#define THREADSAFECALLS_H

int __lockObjectNoblock(void* object);
void __lockObjectBlock(void* object);
int __lockObjectBlockTimeout(void* object, unsigned timeout);

void __releaseObject(void* object);

//TODO semaphore functions
#endif //THREADSAFECALLS_H
