.syntax unified
@ Author: Jacko Dirks
@ Description: Contains functions to move the CPU regs between RAM and CPU

    .global regDump
    .global regLoad

regDump:
    STMDB   R0! ,   {r4-r11}    @Move R4 to R11 to param R0, while decreasing R0    
    MOV     PC  ,   LR          @Return

regLoad:
    LDMFD   R0! , {r4-r11}      @Move from ram to regs while increasing R0
    MOV     PC  ,   LR          @return
    
