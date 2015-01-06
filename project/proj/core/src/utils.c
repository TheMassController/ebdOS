#include "stdlib.h"
#include "process.h"
#include "hw_types.h" //Contains the types
#include "rom_map.h"
#include "rom.h"

struct Process* __sortProcessIntoList(struct Process* listHead, struct Process* item){
    struct Process* current = listHead;
    struct Process* previous = NULL;
    while (current != NULL && current->priority >= item->priority){
        previous = current;
        current = current->nextProcess;
    }
    //Needs to go between previous and current, unless previous is NULL. Then it becomes the new HEAD
    if (previous == NULL){
        item->nextProcess = current;
        listHead = item;
    } else {
        previous->nextProcess = item;
        item->nextProcess = current;
    }
    return listHead;
}

struct Process* __removeProcessFromList(struct Process* listHead, struct Process* item){
    struct Process* current = listHead;
    struct Process* previous = NULL;
    while (current != NULL && current != item){
        previous = current;
        current = current->nextProcess;
    }
    //If current is NULL, then it was not in the list
    //If previous is NULL, then it is the head of the list
    if (current != NULL){
        if (previous == NULL){
            listHead = current->nextProcess;
        } else {
            previous->nextProcess = current->nextProcess;
        }
        
    }
    return listHead;
}

int __processInList(struct Process* listHead, struct Process* proc){
    while (listHead != NULL){
        if (listHead == proc) return 1;
        listHead = listHead->nextProcess; 
    }
    return 0; 
}
