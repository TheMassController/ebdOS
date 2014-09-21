.syntax unified
.cpu cortex-m4
.thumb
@ Author: Jacko Dirks
@ Description: Handles hard faults
@ http://blog.frankvh.com/2011/12/07/cortex-m3-m4-hard-fault-handler/

.global faultISR
.extern faultISRHandler
 
faultISR:
  TST LR, #4
  ITE EQ
  MRSEQ R0, MSP
  MRSNE R0, PSP
  B faultISRHandler
