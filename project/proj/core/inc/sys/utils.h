#ifndef UTILS_H
#define UTILS_H

//Contains some processes that are used in the core, but do not specifically belong anywhere

//Updates the list and returns the (new) head
struct Process* __sortProcessIntoList(struct Process* listHead, struct Process* item);

struct Process* __removeProcessFromList(struct Process* listHead, struct Process* item);

int __processInList(struct Process* listHead, struct Process* proc);

int __inInterrupt(void);

#endif //UTILS_H
