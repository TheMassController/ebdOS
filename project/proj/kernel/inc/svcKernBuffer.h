/**
 * @file svcKernBuffer.h
 * @author Jacko Dirks
 *
 * This is the header file for the functions responsible for the communication between kernel and supervisor.
 * The functions defined here make sure that everything happens safely.
 *
 * There are two types of communication: messages, that usually indicate an interrupt happend and the kernel should do something about it and processes which need service.
 * The process service part is mainly handled in sysCalls.h (core). The messages are defined as an enum here.
 *
 */


