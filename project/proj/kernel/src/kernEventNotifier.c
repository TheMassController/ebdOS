#include <errno.h>

#include "kernEventNotifier.h"
#include "spinlock.h"
#include "atomicIntegerOperations.h"
#include "supervisorCall.h"
#include "coreUtils.h"

#ifdef DEBUG
    #include <uartstdio.h>

    #include "kernUtils.h"
#endif //DEBUG

static enum KernBufferMessageCodes messageBuf[KERNMESSAGEBUFFERSIZE];
static struct Spinlock messageBufLock;
static int messageReadPos;
static int messageWritePos;

extern volatile const int kernelIsActive;

static void activateKernel(void) {
    if (!kernelIsActive){
        CALLSUPERVISOR(SVC_wakeupKernel);
    }
}

static int enoughSpaceInBuffer(int read, int write, const int buflen){
    if (read == 0 && write == buflen-1) return 0;
    if (write == read-1) return 0;
    return 1;
}

// TODO try to remove the while(1)
static int addMessageToBuffer(const enum KernBufferMessageCodes code){
    while(1){
        if (!enoughSpaceInBuffer(messageReadPos, messageWritePos, KERNMESSAGEBUFFERSIZE)) return ENOMEM;
        int writepos = atomicIncreaseIntWithMax(&messageWritePos, KERNMESSAGEBUFFERSIZE-1);
        if (writepos == -1){
            if (atomicSetInt(&messageWritePos, 0, KERNMESSAGEBUFFERSIZE-1) == -1) continue;
            writepos = 0;
        }
        messageBuf[writepos] = code;
        return 0;
    }
}

int passMessageToKernel(const enum KernBufferMessageCodes code){
#ifdef DEBUG
    if (isInSVCInterrupt()){
        UARTprintf("Illegal function call in __FILE__, __LINE__\n");
        generateCrash();
    }
#endif //DEBUG
    activateKernel();
    if (isInInterrupt()){
        return addMessageToBuffer(code);
    } else {
        lockSpinlock(&messageBufLock);
        int retCode = addMessageToBuffer(code);
        unlockSpinlock(&messageBufLock);
        return retCode;
    }
}

enum KernBufferMessageCodes kernelBufferGetCode(void){
#ifdef DEBUG
    if (isInInterrupt()){
        UARTprintf("Illegal function call in __FILE__, __LINE__\n");
        generateCrash();
    }
#endif //DEBUG
    if (messageReadPos == messageWritePos){
        return noMessageAvailable;
    }
    lockSpinlock(&messageBufLock);
    messageReadPos = (messageReadPos + 1) % KERNMESSAGEBUFFERSIZE;
    enum KernBufferMessageCodes message = messageBuf[messageReadPos];
#ifdef DEBUG
    messageBuf[messageReadPos] = noMessageAvailable;
#endif //DEBUG
    unlockSpinlock(&messageBufLock);
    return message;
}

int kernBufferIsEmpty(void){
    return messageReadPos == messageWritePos;
}
