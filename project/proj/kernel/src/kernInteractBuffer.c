#include "kernInteractBuffer.h"
#include "spinlock.h"
#include "atomicIntegerOperations.h"
#include "supervisorCall.h"

#include <errno.h>
// There are no guarantees about the writers of this buffer: it has to be completely threadsafe.
// We also need a modulo operation, so can we even use the existing atomic int functions?
//
// The fact that all of the next fields are initialized to 0 is exploited like nobody's buisiness.
static enum KernBufferMessageCodes messageBuf[KERNMESSAGEBUFFERSIZE];
static struct Process* processBuf[MAXTOTALPROCESSES];
// The pointers for the messagebuffer.
static int messageReadPos;
static int messageWritePos;
// The pointers for the process buffer.
static int processReadPos;
static int processWritePos;

static int enoughSpaceInBuffer(int read, int write, const int bufLen){
    if (read == 0 && write == buflen-1) return 0;
    if (write == read-1) return 0;
    return 1;
}
// TODO try to remove the while(1)
int passMessageToKernel(const enum KernBufferMessageCodes code){
    while(1){
        if (!enoughSpaceInBuffer(messageReadPos, messageWritePos, KERNMESSAGEBUFFERSIZE)) return ENOMEM; 
        int writepos = atomicIncreaseInt(&messageWritePos);
        if (writepos >= KERNMESSAGEBUFFERSIZE){
            if (!atomicSetInt(&messageWritePos, 0, writepos)) continue;
            writepos = 0;
        }
        messageBuf[writepos] = code;
        return 0;
    }
}

enum KernBufferMessageCodes kernelBufferGetCode(void){
    if (messageReadPos == messageWritePos) return noMessageAvailable;
    enum KernBufferMessageCodes message = noMessageAvailable;
    // This loop is because the kernel might have start reading while the other process has not written yet. Wait for the write!
    while(message == noMessageAvailable){
        message = messageBuf[messageReadPos];
        CALLSUPERVISOR(SVC_yield);
    }
    messageBuf[messageReadPos] = noMessageAvailable;
    int readPos = atomicIncreaseIntWithMax(&messageReadPos, KERNMESSAGEBUFFERSIZE-1);
    if (readPos == -1) atomicSetInt(&messageReadPos, 0, KERNMESSAGEBUFFERSIZE-1);
    return message;
}
