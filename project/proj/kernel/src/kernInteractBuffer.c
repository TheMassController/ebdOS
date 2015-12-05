#include "kernInteractBuffer.h"
#include "anonymousSpinlock.h"
#include "atomicIntegerOperations.h"
#include "supervisorCall.h"

#include <errno.h>
// There are no guarantees about the writers of this buffer: it has to be completely threadsafe.
// We also need a modulo operation, so can we even use the existing atomic int functions?
//
// The fact that all of the next fields are initialized to 0 is exploited like nobody's buisiness.
static enum KernBufferMessageCodes messageBuf[KERNMESSAGEBUFFERSIZE];
static struct AnonymousSpinlock messageBufLock[KERNMESSAGEBUFFERSIZE];
//static struct Process* processBuf[MAXTOTALPROCESSES];
// The pointers for the messagebuffer.
static int messageReadPos;
static int messageWritePos;
// The pointers for the process buffer.
//static int processReadPos;
//static int processWritePos;

static int enoughSpaceInBuffer(int read, int write, const int buflen){
    if (read == 0 && write == buflen-1) return 0;
    if (write == read-1) return 0;
    return 1;
}
// TODO try to remove the while(1)
int passMessageToKernel(const enum KernBufferMessageCodes code){
    while(1){
        if (!enoughSpaceInBuffer(messageReadPos, messageWritePos, KERNMESSAGEBUFFERSIZE)) return ENOMEM; 
        int writepos = atomicIncreaseIntWithMax(&messageWritePos, KERNMESSAGEBUFFERSIZE-1);
        if (writepos == -1){
            if (!atomicSetInt(&messageWritePos, 0, writepos)) continue;
            writepos = 0;
        }
        lockAnonymousSpinlock(&messageBufLock[writepos]);
        messageBuf[writepos] = code;
        unlockAnonymousSpinlock(&messageBufLock[writepos]);
        return 0;
    }
}
// TODO make it so that multiple threads can read from this without any issue
enum KernBufferMessageCodes kernelBufferGetCode(void){
    if (messageReadPos == messageWritePos) return noMessageAvailable;
    lockAnonymousSpinlock(&messageBufLock[messageReadPos]);
    enum KernBufferMessageCodes message = messageBuf[messageReadPos];
    unlockAnonymousSpinlock(&messageBufLock[messageReadPos]);
    int readPos = atomicIncreaseIntWithMax(&messageReadPos, KERNMESSAGEBUFFERSIZE-1);
    if (readPos == -1) atomicSetInt(&messageReadPos, 0, KERNMESSAGEBUFFERSIZE-1);
    return message;
}
