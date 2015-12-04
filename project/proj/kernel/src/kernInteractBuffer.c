#include "kernInteractBuffer.h"
// There are no guarantees about the writers of this buffer: it has to be completely threadsafe.
// We also need a modulo operation, so can we even use the existing atomic int functions?
//static enum KernBufferMessageCodes messageBuf[KERNMESSAGEBUFFERSIZE];
//static struct Process* processBuf[MAXTOTALPROCESSES];
//// The pointers for the messagebuffer.
//static int messageReadPos;
//static int messageWritePos;
//// The pointers for the process buffer.
//static int processReadPos;
//static int processWritePos;
