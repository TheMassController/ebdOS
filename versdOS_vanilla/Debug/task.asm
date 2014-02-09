;******************************************************************************
;* G3 TMS470 C/C++ Codegen                                          PC v4.9.9 *
;* Date/Time created: Tue Dec 10 11:03:54 2013                                *
;******************************************************************************
	.compiler_opts --abi=eabi --arm_vmrs_si_workaround=on --code_state=16 --disable_dual_state --embedded_constants=on --endian=little --float_support=FPv4SPD16 --hll_source=on --object_format=elf --silicon_version=7M4 --symdebug:dwarf --symdebug:dwarf_version=2 
	.thumb

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../src/task.c")
	.dwattr $C$DW$CU, DW_AT_producer("G3 TMS470 C/C++ Codegen PC v4.9.9 Copyright (c) 1996-2013 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("C:\Developing\workspace\versdOS\Debug")

$C$DW$1	.dwtag  DW_TAG_subprogram, DW_AT_name("malloc")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("malloc")
	.dwattr $C$DW$1, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$1, DW_AT_decl_line(0x98)
	.dwattr $C$DW$1, DW_AT_decl_column(0x19)
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$33)
	.dwendtag $C$DW$1


$C$DW$3	.dwtag  DW_TAG_subprogram, DW_AT_name("writePSP")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("writePSP")
	.dwattr $C$DW$3, DW_AT_declaration
	.dwattr $C$DW$3, DW_AT_external
	.dwattr $C$DW$3, DW_AT_decl_file("..\src\schedule.h")
	.dwattr $C$DW$3, DW_AT_decl_line(0x19)
	.dwattr $C$DW$3, DW_AT_decl_column(0x06)
$C$DW$4	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$3)
	.dwendtag $C$DW$3

	.global	taskList
taskList:	.usect	".bss:taskList",320,4
$C$DW$5	.dwtag  DW_TAG_variable, DW_AT_name("taskList")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("taskList")
	.dwattr $C$DW$5, DW_AT_location[DW_OP_addr taskList]
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$74)
	.dwattr $C$DW$5, DW_AT_external
	.dwattr $C$DW$5, DW_AT_decl_file("../src/task.c")
	.dwattr $C$DW$5, DW_AT_decl_line(0x13)
	.dwattr $C$DW$5, DW_AT_decl_column(0x06)
$C$DW$6	.dwtag  DW_TAG_variable, DW_AT_name("currentTask")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("currentTask")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$6, DW_AT_declaration
	.dwattr $C$DW$6, DW_AT_external
	.dwattr $C$DW$6, DW_AT_decl_file("../src/task.c")
	.dwattr $C$DW$6, DW_AT_decl_line(0x16)
	.dwattr $C$DW$6, DW_AT_decl_column(0x0f)
;	C:\ti\ccsv5\tools\compiler\arm_4.9.9\bin\acpia470.exe -@C:\\TEMP\\0512412 
	.sect	".text:addTaskToList"
	.clink
	.thumbfunc addTaskToList
	.thumb
	.global	addTaskToList

$C$DW$7	.dwtag  DW_TAG_subprogram, DW_AT_name("addTaskToList")
	.dwattr $C$DW$7, DW_AT_low_pc(addTaskToList)
	.dwattr $C$DW$7, DW_AT_high_pc(0x00)
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("addTaskToList")
	.dwattr $C$DW$7, DW_AT_external
	.dwattr $C$DW$7, DW_AT_TI_begin_file("../src/task.c")
	.dwattr $C$DW$7, DW_AT_TI_begin_line(0x22)
	.dwattr $C$DW$7, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$7, DW_AT_decl_file("../src/task.c")
	.dwattr $C$DW$7, DW_AT_decl_line(0x22)
	.dwattr $C$DW$7, DW_AT_decl_column(0x06)
	.dwattr $C$DW$7, DW_AT_TI_max_frame_size(0x18)
	.dwpsn	file "../src/task.c",line 35,column 1,is_stmt,address addTaskToList

	.dwfde $C$DW$CIE, addTaskToList
$C$DW$8	.dwtag  DW_TAG_formal_parameter, DW_AT_name("function")
	.dwattr $C$DW$8, DW_AT_TI_symbol_name("function")
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$8, DW_AT_location[DW_OP_reg0]
$C$DW$9	.dwtag  DW_TAG_formal_parameter, DW_AT_name("stackSize")
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("stackSize")
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$9, DW_AT_location[DW_OP_reg1]
$C$DW$10	.dwtag  DW_TAG_formal_parameter, DW_AT_name("priority")
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("priority")
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$10, DW_AT_location[DW_OP_reg2]
;----------------------------------------------------------------------
;  34 | void addTaskToList(void(*function)(void), int stackSize, int priority) 
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: addTaskToList                                              *
;*                                                                           *
;*   Regs Modified     : A1,A2,A3,A4,V9,SP,LR,SR,D0,D0_hi,D1,D1_hi,D2,D2_hi, *
;*                           D3,D3_hi,D4,D4_hi,D5,D5_hi,D6,D6_hi,D7,D7_hi,   *
;*                           FPEXC,FPSCR                                     *
;*   Regs Used         : A1,A2,A3,A4,V9,SP,LR,SR,D0,D0_hi,D1,D1_hi,D2,D2_hi, *
;*                           D3,D3_hi,D4,D4_hi,D5,D5_hi,D6,D6_hi,D7,D7_hi,   *
;*                           FPEXC,FPSCR                                     *
;*   Local Frame Size  : 0 Args + 16 Auto + 4 Save = 20 byte                 *
;*****************************************************************************
addTaskToList:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
        PUSH      {LR}                  ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 4
	.dwcfi	save_reg_to_mem, 14, -4
        SUB       SP, SP, #20           ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 24
$C$DW$11	.dwtag  DW_TAG_variable, DW_AT_name("function")
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("function")
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$11, DW_AT_location[DW_OP_breg13 0]
$C$DW$12	.dwtag  DW_TAG_variable, DW_AT_name("stackSize")
	.dwattr $C$DW$12, DW_AT_TI_symbol_name("stackSize")
	.dwattr $C$DW$12, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$12, DW_AT_location[DW_OP_breg13 4]
$C$DW$13	.dwtag  DW_TAG_variable, DW_AT_name("priority")
	.dwattr $C$DW$13, DW_AT_TI_symbol_name("priority")
	.dwattr $C$DW$13, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$13, DW_AT_location[DW_OP_breg13 8]
$C$DW$14	.dwtag  DW_TAG_variable, DW_AT_name("i")
	.dwattr $C$DW$14, DW_AT_TI_symbol_name("i")
	.dwattr $C$DW$14, DW_AT_type(*$C$DW$T$26)
	.dwattr $C$DW$14, DW_AT_location[DW_OP_breg13 12]
        STR       A3, [SP, #8]          ; [DPU_3_PIPE] |35| 
        STR       A2, [SP, #4]          ; [DPU_3_PIPE] |35| 
        STR       A1, [SP, #0]          ; [DPU_3_PIPE] |35| 
	.dwpsn	file "../src/task.c",line 36,column 10,is_stmt
;----------------------------------------------------------------------
;  36 | uint8_t i=0;                                                           
;  38 | //Simply find the next empty spot                                      
;----------------------------------------------------------------------
        MOVS      A1, #0                ; [DPU_3_PIPE] |36| 
        STRB      A1, [SP, #12]         ; [DPU_3_PIPE] |36| 
	.dwpsn	file "../src/task.c",line 39,column 2,is_stmt
;----------------------------------------------------------------------
;  39 | while(taskList[i].function != 0){                                      
;  40 |         //increment i and roll back at the limit                       
;----------------------------------------------------------------------
        B         ||$C$L2||             ; [DPU_3_PIPE] |39| 
        ; BRANCH OCCURS {||$C$L2||}      ; [] |39| 
;* --------------------------------------------------------------------------*
||$C$L1||:    
$C$DW$L$addTaskToList$2$B:
	.dwpsn	file "../src/task.c",line 41,column 3,is_stmt
;----------------------------------------------------------------------
;  41 | i++;                                                                   
;----------------------------------------------------------------------
        LDRB      A1, [SP, #12]         ; [DPU_3_PIPE] |41| 
        ADDS      A1, A1, #1            ; [DPU_3_PIPE] |41| 
        STRB      A1, [SP, #12]         ; [DPU_3_PIPE] |41| 
	.dwpsn	file "../src/task.c",line 42,column 3,is_stmt
;----------------------------------------------------------------------
;  42 | i &= TASK_MASK;                                                        
;  45 | //The new and latest task will become the currentTask                  
;----------------------------------------------------------------------
        LDRB      A1, [SP, #12]         ; [DPU_3_PIPE] |42| 
        AND       A1, A1, #15           ; [DPU_3_PIPE] |42| 
        STRB      A1, [SP, #12]         ; [DPU_3_PIPE] |42| 
$C$DW$L$addTaskToList$2$E:
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L2||
;* --------------------------------------------------------------------------*
||$C$L2||:    
$C$DW$L$addTaskToList$3$B:
	.dwpsn	file "../src/task.c",line 39,column 8,is_stmt
        LDRB      A2, [SP, #12]         ; [DPU_3_PIPE] |39| 
        LSLS      A1, A2, #2            ; [DPU_3_PIPE] |39| 
        ADD       A1, A1, A2, LSL #4    ; [DPU_3_PIPE] |39| 
        LDR       A2, $C$CON1           ; [DPU_3_PIPE] |39| 
        LDR       A1, [A2, +A1]         ; [DPU_3_PIPE] |39| 
        CMP       A1, #0                ; [DPU_3_PIPE] |39| 
        BNE       ||$C$L1||             ; [DPU_3_PIPE] |39| 
        ; BRANCHCC OCCURS {||$C$L1||}    ; [] |39| 
$C$DW$L$addTaskToList$3$E:
;* --------------------------------------------------------------------------*
	.dwpsn	file "../src/task.c",line 46,column 2,is_stmt
;----------------------------------------------------------------------
;  46 | currentTask = &taskList[i];                                            
;----------------------------------------------------------------------
        LDRB      A2, [SP, #12]         ; [DPU_3_PIPE] |46| 
        LSLS      A1, A2, #2            ; [DPU_3_PIPE] |46| 
        ADD       A1, A1, A2, LSL #4    ; [DPU_3_PIPE] |46| 
        LDR       A2, $C$CON3           ; [DPU_3_PIPE] |46| 
        ADDS      A2, A2, A1            ; [DPU_3_PIPE] |46| 
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |46| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |46| 
	.dwpsn	file "../src/task.c",line 48,column 2,is_stmt
;----------------------------------------------------------------------
;  48 | currentTask->function = function;                                      
;  50 | //Allocate memory... do we wanna use malloc or our own implementation ;
;     | -) ?                                                                   
;----------------------------------------------------------------------
        LDR       A2, $C$CON2           ; [DPU_3_PIPE] |48| 
        LDR       A1, [SP, #0]          ; [DPU_3_PIPE] |48| 
        LDR       A2, [A2, #0]          ; [DPU_3_PIPE] |48| 
        STR       A1, [A2, #4]          ; [DPU_3_PIPE] |48| 
	.dwpsn	file "../src/task.c",line 51,column 2,is_stmt
;----------------------------------------------------------------------
;  51 | currentTask->stack = (int *)malloc(stackSize)+stackSize;               
;  53 | //now we initialize the stack for when we return the first time from th
;     | e scheduler                                                            
;  54 | //This is the 'hardware' stack                                         
;----------------------------------------------------------------------
        LDR       A1, [SP, #4]          ; [DPU_3_PIPE] |51| 
$C$DW$15	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$15, DW_AT_low_pc(0x00)
	.dwattr $C$DW$15, DW_AT_name("malloc")
	.dwattr $C$DW$15, DW_AT_TI_call
        BL        malloc                ; [DPU_3_PIPE] |51| 
        ; CALL OCCURS {malloc }          ; [] |51| 
        LDR       A2, [SP, #4]          ; [DPU_3_PIPE] |51| 
        ADD       A1, A1, A2, LSL #2    ; [DPU_3_PIPE] |51| 
        LDR       A2, $C$CON2           ; [DPU_3_PIPE] |51| 
        LDR       A2, [A2, #0]          ; [DPU_3_PIPE] |51| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |51| 
	.dwpsn	file "../src/task.c",line 55,column 2,is_stmt
;----------------------------------------------------------------------
;  55 | *((currentTask->stack)--)       = 0x01000000;
;     |          //XSPR  nothing special , no fpu etc.                         
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |55| 
        LDR       A2, [A1, #0]          ; [DPU_3_PIPE] |55| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |55| 
        SUBS      A3, A1, #4            ; [DPU_3_PIPE] |55| 
        STR       A3, [A2, #0]          ; [DPU_3_PIPE] |55| 
        MOV       A2, #16777216         ; [DPU_3_PIPE] |55| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |55| 
	.dwpsn	file "../src/task.c",line 56,column 2,is_stmt
;----------------------------------------------------------------------
;  56 | *((currentTask->stack)--)       = (int)currentTask->function;   //set P
;     | C to function pointer, cast as int to silence the compiler             
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |56| 
        LDR       A2, [A1, #0]          ; [DPU_3_PIPE] |56| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |56| 
        SUBS      A3, A1, #4            ; [DPU_3_PIPE] |56| 
        STR       A3, [A2, #0]          ; [DPU_3_PIPE] |56| 
        LDR       A2, $C$CON2           ; [DPU_3_PIPE] |56| 
        LDR       A2, [A2, #0]          ; [DPU_3_PIPE] |56| 
        LDR       A2, [A2, #4]          ; [DPU_3_PIPE] |56| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |56| 
	.dwpsn	file "../src/task.c",line 57,column 2,is_stmt
;----------------------------------------------------------------------
;  57 | *((currentTask->stack)--)       = 0xFFFFFFFD;
;     |          //LR                                                          
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |57| 
        LDR       A2, [A1, #0]          ; [DPU_3_PIPE] |57| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |57| 
        SUBS      A3, A1, #4            ; [DPU_3_PIPE] |57| 
        STR       A3, [A2, #0]          ; [DPU_3_PIPE] |57| 
        MVN       A2, #2                ; [DPU_3_PIPE] |57| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |57| 
	.dwpsn	file "../src/task.c",line 58,column 2,is_stmt
;----------------------------------------------------------------------
;  58 | *((currentTask->stack)--)       = 0x0000000C;
;     |          //R12   Initial values used for debugging purposes            
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |58| 
        LDR       A2, [A1, #0]          ; [DPU_3_PIPE] |58| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |58| 
        SUBS      A3, A1, #4            ; [DPU_3_PIPE] |58| 
        STR       A3, [A2, #0]          ; [DPU_3_PIPE] |58| 
        MOVS      A2, #12               ; [DPU_3_PIPE] |58| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |58| 
	.dwpsn	file "../src/task.c",line 59,column 2,is_stmt
;----------------------------------------------------------------------
;  59 | *((currentTask->stack)--)       = 0x00000003;
;     |          //R3                                                          
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |59| 
        LDR       A2, [A1, #0]          ; [DPU_3_PIPE] |59| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |59| 
        SUBS      A3, A1, #4            ; [DPU_3_PIPE] |59| 
        STR       A3, [A2, #0]          ; [DPU_3_PIPE] |59| 
        MOVS      A2, #3                ; [DPU_3_PIPE] |59| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |59| 
	.dwpsn	file "../src/task.c",line 60,column 2,is_stmt
;----------------------------------------------------------------------
;  60 | *((currentTask->stack)--)       = 0x00000002;
;     |          //R2                                                          
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |60| 
        LDR       A2, [A1, #0]          ; [DPU_3_PIPE] |60| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |60| 
        SUBS      A3, A1, #4            ; [DPU_3_PIPE] |60| 
        STR       A3, [A2, #0]          ; [DPU_3_PIPE] |60| 
        MOVS      A2, #2                ; [DPU_3_PIPE] |60| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |60| 
	.dwpsn	file "../src/task.c",line 61,column 2,is_stmt
;----------------------------------------------------------------------
;  61 | *((currentTask->stack)--)       = 0x00000001;
;     |          //R1                                                          
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |61| 
        LDR       A2, [A1, #0]          ; [DPU_3_PIPE] |61| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |61| 
        SUBS      A3, A1, #4            ; [DPU_3_PIPE] |61| 
        STR       A3, [A2, #0]          ; [DPU_3_PIPE] |61| 
        MOVS      A2, #1                ; [DPU_3_PIPE] |61| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |61| 
	.dwpsn	file "../src/task.c",line 62,column 2,is_stmt
;----------------------------------------------------------------------
;  62 | *((currentTask->stack))         = 0x00000000;
;     |          //R0                                                          
;  64 | //currentTask->stack-=8;                //lower the stack pointer to si
;     | mulate the other R4-R11 registers                                      
;  66 | //Update the CPU PSP with our new stack pointer                        
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |62| 
        LDR       A1, [A1, #0]          ; [DPU_3_PIPE] |62| 
        LDR       A1, [A1, #0]          ; [DPU_3_PIPE] |62| 
        MOVS      A2, #0                ; [DPU_3_PIPE] |62| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |62| 
	.dwpsn	file "../src/task.c",line 67,column 2,is_stmt
;----------------------------------------------------------------------
;  67 | writePSP(currentTask->stack);                                          
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |67| 
        LDR       A1, [A1, #0]          ; [DPU_3_PIPE] |67| 
        LDR       A1, [A1, #0]          ; [DPU_3_PIPE] |67| 
$C$DW$16	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$16, DW_AT_low_pc(0x00)
	.dwattr $C$DW$16, DW_AT_name("writePSP")
	.dwattr $C$DW$16, DW_AT_TI_call
        BL        writePSP              ; [DPU_3_PIPE] |67| 
        ; CALL OCCURS {writePSP }        ; [] |67| 
	.dwpsn	file "../src/task.c",line 72,column 2,is_stmt
;----------------------------------------------------------------------
;  72 | currentTask->state                      = READY;                       
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |72| 
        LDR       A1, [A1, #0]          ; [DPU_3_PIPE] |72| 
        MOVS      A2, #1                ; [DPU_3_PIPE] |72| 
        STRB      A2, [A1, #8]          ; [DPU_3_PIPE] |72| 
	.dwpsn	file "../src/task.c",line 73,column 2,is_stmt
;----------------------------------------------------------------------
;  73 | currentTask->bInitialized       = 0;                                   
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |73| 
        LDR       A1, [A1, #0]          ; [DPU_3_PIPE] |73| 
        MOVS      A2, #0                ; [DPU_3_PIPE] |73| 
        STRB      A2, [A1, #16]         ; [DPU_3_PIPE] |73| 
	.dwpsn	file "../src/task.c",line 74,column 2,is_stmt
;----------------------------------------------------------------------
;  74 | currentTask->uiPriority         = priority;                            
;----------------------------------------------------------------------
        LDR       A2, $C$CON2           ; [DPU_3_PIPE] |74| 
        LDRB      A1, [SP, #8]          ; [DPU_3_PIPE] |74| 
        LDR       A2, [A2, #0]          ; [DPU_3_PIPE] |74| 
        STRB      A1, [A2, #9]          ; [DPU_3_PIPE] |74| 
	.dwpsn	file "../src/task.c",line 77,column 2,is_stmt
;----------------------------------------------------------------------
;  77 | return;                                                                
;----------------------------------------------------------------------
	.dwpsn	file "../src/task.c",line 78,column 1,is_stmt
        ADD       SP, SP, #20           ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 4
$C$DW$17	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$17, DW_AT_low_pc(0x00)
	.dwattr $C$DW$17, DW_AT_TI_return
        POP       {PC}                  ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 

$C$DW$18	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$18, DW_AT_name("C:\Developing\workspace\versdOS\Debug\task.asm:$C$L2:1:1386669834")
	.dwattr $C$DW$18, DW_AT_TI_begin_file("../src/task.c")
	.dwattr $C$DW$18, DW_AT_TI_begin_line(0x27)
	.dwattr $C$DW$18, DW_AT_TI_end_line(0x2a)
$C$DW$19	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$19, DW_AT_low_pc($C$DW$L$addTaskToList$3$B)
	.dwattr $C$DW$19, DW_AT_high_pc($C$DW$L$addTaskToList$3$E)
$C$DW$20	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$20, DW_AT_low_pc($C$DW$L$addTaskToList$2$B)
	.dwattr $C$DW$20, DW_AT_high_pc($C$DW$L$addTaskToList$2$E)
	.dwendtag $C$DW$18

	.dwattr $C$DW$7, DW_AT_TI_end_file("../src/task.c")
	.dwattr $C$DW$7, DW_AT_TI_end_line(0x4e)
	.dwattr $C$DW$7, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$7

;******************************************************************************
;* CONSTANT TABLE                                                             *
;******************************************************************************
	.sect	".text:addTaskToList"
	.align	4
||$C$CON1||:	.bits	taskList+4,32
	.align	4
||$C$CON2||:	.bits	currentTask,32
	.align	4
||$C$CON3||:	.bits	taskList,32
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	malloc
	.global	writePSP
	.global	currentTask

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "aeabi", Tag_File, 1, Tag_ABI_PCS_wchar_t(2)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_rounding(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_denormal(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_exceptions(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_number_model(1)
	.battr "aeabi", Tag_File, 1, Tag_ABI_enum_size(1)
	.battr "aeabi", Tag_File, 1, Tag_ABI_optimization_goals(5)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_optimization_goals(2)
	.battr "TI", Tag_File, 1, Tag_Bitfield_layout(2)

;******************************************************************************
;* TYPE INFORMATION                                                           *
;******************************************************************************

$C$DW$T$19	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$19, DW_AT_byte_size(0x08)
$C$DW$21	.dwtag  DW_TAG_member
	.dwattr $C$DW$21, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$21, DW_AT_name("quot")
	.dwattr $C$DW$21, DW_AT_TI_symbol_name("quot")
	.dwattr $C$DW$21, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$21, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$21, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$21, DW_AT_decl_line(0x4f)
	.dwattr $C$DW$21, DW_AT_decl_column(0x16)
$C$DW$22	.dwtag  DW_TAG_member
	.dwattr $C$DW$22, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$22, DW_AT_name("rem")
	.dwattr $C$DW$22, DW_AT_TI_symbol_name("rem")
	.dwattr $C$DW$22, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$22, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$22, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$22, DW_AT_decl_line(0x4f)
	.dwattr $C$DW$22, DW_AT_decl_column(0x1c)
	.dwendtag $C$DW$T$19

	.dwattr $C$DW$T$19, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$19, DW_AT_decl_line(0x4f)
	.dwattr $C$DW$T$19, DW_AT_decl_column(0x10)
$C$DW$T$30	.dwtag  DW_TAG_typedef, DW_AT_name("div_t")
	.dwattr $C$DW$T$30, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$T$30, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$30, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$30, DW_AT_decl_line(0x4f)
	.dwattr $C$DW$T$30, DW_AT_decl_column(0x23)

$C$DW$T$20	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$20, DW_AT_byte_size(0x08)
$C$DW$23	.dwtag  DW_TAG_member
	.dwattr $C$DW$23, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$23, DW_AT_name("quot")
	.dwattr $C$DW$23, DW_AT_TI_symbol_name("quot")
	.dwattr $C$DW$23, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$23, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$23, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$23, DW_AT_decl_line(0x51)
	.dwattr $C$DW$23, DW_AT_decl_column(0x16)
$C$DW$24	.dwtag  DW_TAG_member
	.dwattr $C$DW$24, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$24, DW_AT_name("rem")
	.dwattr $C$DW$24, DW_AT_TI_symbol_name("rem")
	.dwattr $C$DW$24, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$24, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$24, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$24, DW_AT_decl_line(0x51)
	.dwattr $C$DW$24, DW_AT_decl_column(0x1c)
	.dwendtag $C$DW$T$20

	.dwattr $C$DW$T$20, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$20, DW_AT_decl_line(0x51)
	.dwattr $C$DW$T$20, DW_AT_decl_column(0x10)
$C$DW$T$31	.dwtag  DW_TAG_typedef, DW_AT_name("ldiv_t")
	.dwattr $C$DW$T$31, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$31, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$31, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$31, DW_AT_decl_line(0x51)
	.dwattr $C$DW$T$31, DW_AT_decl_column(0x23)

$C$DW$T$21	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$21, DW_AT_byte_size(0x10)
$C$DW$25	.dwtag  DW_TAG_member
	.dwattr $C$DW$25, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$25, DW_AT_name("quot")
	.dwattr $C$DW$25, DW_AT_TI_symbol_name("quot")
	.dwattr $C$DW$25, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$25, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$25, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$25, DW_AT_decl_line(0x54)
	.dwattr $C$DW$25, DW_AT_decl_column(0x1c)
$C$DW$26	.dwtag  DW_TAG_member
	.dwattr $C$DW$26, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$26, DW_AT_name("rem")
	.dwattr $C$DW$26, DW_AT_TI_symbol_name("rem")
	.dwattr $C$DW$26, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$26, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$26, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$26, DW_AT_decl_line(0x54)
	.dwattr $C$DW$26, DW_AT_decl_column(0x22)
	.dwendtag $C$DW$T$21

	.dwattr $C$DW$T$21, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$21, DW_AT_decl_line(0x54)
	.dwattr $C$DW$T$21, DW_AT_decl_column(0x10)
$C$DW$T$32	.dwtag  DW_TAG_typedef, DW_AT_name("lldiv_t")
	.dwattr $C$DW$T$32, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$T$32, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$32, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$32, DW_AT_decl_line(0x54)
	.dwattr $C$DW$T$32, DW_AT_decl_column(0x29)
$C$DW$T$3	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$3, DW_AT_address_class(0x20)
$C$DW$T$36	.dwtag  DW_TAG_typedef, DW_AT_name("__builtin_va_list")
	.dwattr $C$DW$T$36, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$T$36, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$36, DW_AT_decl_file("../src/task.c")
	.dwattr $C$DW$T$36, DW_AT_decl_line(0x4e)
	.dwattr $C$DW$T$36, DW_AT_decl_column(0x01)

$C$DW$T$23	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$23, DW_AT_language(DW_LANG_C)
$C$DW$T$24	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$24, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$T$24, DW_AT_address_class(0x20)
$C$DW$T$39	.dwtag  DW_TAG_typedef, DW_AT_name("__TI_atexit_fn")
	.dwattr $C$DW$T$39, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$T$39, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$39, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$39, DW_AT_decl_line(0xa2)
	.dwattr $C$DW$T$39, DW_AT_decl_column(0x14)
$C$DW$T$41	.dwtag  DW_TAG_const_type
$C$DW$T$42	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$42, DW_AT_type(*$C$DW$T$41)
	.dwattr $C$DW$T$42, DW_AT_address_class(0x20)
$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)
$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)
$C$DW$T$43	.dwtag  DW_TAG_typedef, DW_AT_name("int8_t")
	.dwattr $C$DW$T$43, DW_AT_type(*$C$DW$T$5)
	.dwattr $C$DW$T$43, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$43, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$43, DW_AT_decl_line(0x2a)
	.dwattr $C$DW$T$43, DW_AT_decl_column(0x1d)
$C$DW$T$44	.dwtag  DW_TAG_typedef, DW_AT_name("int_least8_t")
	.dwattr $C$DW$T$44, DW_AT_type(*$C$DW$T$43)
	.dwattr $C$DW$T$44, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$44, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$44, DW_AT_decl_line(0x37)
	.dwattr $C$DW$T$44, DW_AT_decl_column(0x17)
$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)
$C$DW$T$26	.dwtag  DW_TAG_typedef, DW_AT_name("uint8_t")
	.dwattr $C$DW$T$26, DW_AT_type(*$C$DW$T$6)
	.dwattr $C$DW$T$26, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$26, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$26, DW_AT_decl_line(0x2b)
	.dwattr $C$DW$T$26, DW_AT_decl_column(0x1c)
$C$DW$T$45	.dwtag  DW_TAG_typedef, DW_AT_name("uint_least8_t")
	.dwattr $C$DW$T$45, DW_AT_type(*$C$DW$T$26)
	.dwattr $C$DW$T$45, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$45, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$45, DW_AT_decl_line(0x38)
	.dwattr $C$DW$T$45, DW_AT_decl_column(0x16)
$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x02)
$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x02)
$C$DW$T$46	.dwtag  DW_TAG_typedef, DW_AT_name("int16_t")
	.dwattr $C$DW$T$46, DW_AT_type(*$C$DW$T$8)
	.dwattr $C$DW$T$46, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$46, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$46, DW_AT_decl_line(0x2c)
	.dwattr $C$DW$T$46, DW_AT_decl_column(0x1d)
$C$DW$T$47	.dwtag  DW_TAG_typedef, DW_AT_name("int_least16_t")
	.dwattr $C$DW$T$47, DW_AT_type(*$C$DW$T$46)
	.dwattr $C$DW$T$47, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$47, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$47, DW_AT_decl_line(0x3a)
	.dwattr $C$DW$T$47, DW_AT_decl_column(0x17)
$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x02)
$C$DW$T$48	.dwtag  DW_TAG_typedef, DW_AT_name("uint16_t")
	.dwattr $C$DW$T$48, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$48, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$48, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$48, DW_AT_decl_line(0x2d)
	.dwattr $C$DW$T$48, DW_AT_decl_column(0x1c)
$C$DW$T$49	.dwtag  DW_TAG_typedef, DW_AT_name("uint_least16_t")
	.dwattr $C$DW$T$49, DW_AT_type(*$C$DW$T$48)
	.dwattr $C$DW$T$49, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$49, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$49, DW_AT_decl_line(0x3b)
	.dwattr $C$DW$T$49, DW_AT_decl_column(0x16)
$C$DW$T$50	.dwtag  DW_TAG_typedef, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$50, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$50, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$50, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$50, DW_AT_decl_line(0x69)
	.dwattr $C$DW$T$50, DW_AT_decl_column(0x1a)
$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x04)
$C$DW$T$22	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$22, DW_AT_address_class(0x20)

$C$DW$T$51	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$51, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$51, DW_AT_language(DW_LANG_C)
$C$DW$27	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$27, DW_AT_type(*$C$DW$T$42)
$C$DW$28	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$28, DW_AT_type(*$C$DW$T$42)
	.dwendtag $C$DW$T$51

$C$DW$T$52	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$52, DW_AT_type(*$C$DW$T$51)
	.dwattr $C$DW$T$52, DW_AT_address_class(0x20)
$C$DW$T$53	.dwtag  DW_TAG_typedef, DW_AT_name("__TI_compar_fn")
	.dwattr $C$DW$T$53, DW_AT_type(*$C$DW$T$52)
	.dwattr $C$DW$T$53, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$53, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$53, DW_AT_decl_line(0xa5)
	.dwattr $C$DW$T$53, DW_AT_decl_column(0x13)
$C$DW$T$54	.dwtag  DW_TAG_typedef, DW_AT_name("int32_t")
	.dwattr $C$DW$T$54, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$54, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$54, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$54, DW_AT_decl_line(0x2e)
	.dwattr $C$DW$T$54, DW_AT_decl_column(0x1d)
$C$DW$T$55	.dwtag  DW_TAG_typedef, DW_AT_name("int_fast16_t")
	.dwattr $C$DW$T$55, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$T$55, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$55, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$55, DW_AT_decl_line(0x47)
	.dwattr $C$DW$T$55, DW_AT_decl_column(0x17)
$C$DW$T$56	.dwtag  DW_TAG_typedef, DW_AT_name("int_fast32_t")
	.dwattr $C$DW$T$56, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$T$56, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$56, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$56, DW_AT_decl_line(0x4a)
	.dwattr $C$DW$T$56, DW_AT_decl_column(0x17)
$C$DW$T$57	.dwtag  DW_TAG_typedef, DW_AT_name("int_fast8_t")
	.dwattr $C$DW$T$57, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$T$57, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$57, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$57, DW_AT_decl_line(0x45)
	.dwattr $C$DW$T$57, DW_AT_decl_column(0x17)
$C$DW$T$58	.dwtag  DW_TAG_typedef, DW_AT_name("int_least32_t")
	.dwattr $C$DW$T$58, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$T$58, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$58, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$58, DW_AT_decl_line(0x3c)
	.dwattr $C$DW$T$58, DW_AT_decl_column(0x17)
$C$DW$T$59	.dwtag  DW_TAG_typedef, DW_AT_name("intptr_t")
	.dwattr $C$DW$T$59, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$59, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$59, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$59, DW_AT_decl_line(0x52)
	.dwattr $C$DW$T$59, DW_AT_decl_column(0x1a)
$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x04)
$C$DW$T$33	.dwtag  DW_TAG_typedef, DW_AT_name("size_t")
	.dwattr $C$DW$T$33, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$33, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$33, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h")
	.dwattr $C$DW$T$33, DW_AT_decl_line(0x63)
	.dwattr $C$DW$T$33, DW_AT_decl_column(0x19)
$C$DW$T$27	.dwtag  DW_TAG_typedef, DW_AT_name("uint32_t")
	.dwattr $C$DW$T$27, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$27, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$27, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$27, DW_AT_decl_line(0x2f)
	.dwattr $C$DW$T$27, DW_AT_decl_column(0x1c)
$C$DW$T$60	.dwtag  DW_TAG_typedef, DW_AT_name("uint_fast16_t")
	.dwattr $C$DW$T$60, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$T$60, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$60, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$60, DW_AT_decl_line(0x48)
	.dwattr $C$DW$T$60, DW_AT_decl_column(0x16)
$C$DW$T$61	.dwtag  DW_TAG_typedef, DW_AT_name("uint_fast32_t")
	.dwattr $C$DW$T$61, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$T$61, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$61, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$61, DW_AT_decl_line(0x4b)
	.dwattr $C$DW$T$61, DW_AT_decl_column(0x16)
$C$DW$T$62	.dwtag  DW_TAG_typedef, DW_AT_name("uint_fast8_t")
	.dwattr $C$DW$T$62, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$T$62, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$62, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$62, DW_AT_decl_line(0x46)
	.dwattr $C$DW$T$62, DW_AT_decl_column(0x16)
$C$DW$T$63	.dwtag  DW_TAG_typedef, DW_AT_name("uint_least32_t")
	.dwattr $C$DW$T$63, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$T$63, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$63, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$63, DW_AT_decl_line(0x3d)
	.dwattr $C$DW$T$63, DW_AT_decl_column(0x16)
$C$DW$T$64	.dwtag  DW_TAG_typedef, DW_AT_name("uintptr_t")
	.dwattr $C$DW$T$64, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$64, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$64, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$64, DW_AT_decl_line(0x53)
	.dwattr $C$DW$T$64, DW_AT_decl_column(0x1a)
$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x04)
$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x04)
$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x08)
$C$DW$T$65	.dwtag  DW_TAG_typedef, DW_AT_name("int64_t")
	.dwattr $C$DW$T$65, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$T$65, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$65, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$65, DW_AT_decl_line(0x32)
	.dwattr $C$DW$T$65, DW_AT_decl_column(0x21)
$C$DW$T$66	.dwtag  DW_TAG_typedef, DW_AT_name("int_fast64_t")
	.dwattr $C$DW$T$66, DW_AT_type(*$C$DW$T$65)
	.dwattr $C$DW$T$66, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$66, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$66, DW_AT_decl_line(0x4e)
	.dwattr $C$DW$T$66, DW_AT_decl_column(0x17)
$C$DW$T$67	.dwtag  DW_TAG_typedef, DW_AT_name("int_least64_t")
	.dwattr $C$DW$T$67, DW_AT_type(*$C$DW$T$65)
	.dwattr $C$DW$T$67, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$67, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$67, DW_AT_decl_line(0x40)
	.dwattr $C$DW$T$67, DW_AT_decl_column(0x17)
$C$DW$T$68	.dwtag  DW_TAG_typedef, DW_AT_name("intmax_t")
	.dwattr $C$DW$T$68, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$T$68, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$68, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$68, DW_AT_decl_line(0x56)
	.dwattr $C$DW$T$68, DW_AT_decl_column(0x20)
$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x08)
$C$DW$T$69	.dwtag  DW_TAG_typedef, DW_AT_name("uint64_t")
	.dwattr $C$DW$T$69, DW_AT_type(*$C$DW$T$15)
	.dwattr $C$DW$T$69, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$69, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$69, DW_AT_decl_line(0x33)
	.dwattr $C$DW$T$69, DW_AT_decl_column(0x20)
$C$DW$T$70	.dwtag  DW_TAG_typedef, DW_AT_name("uint_fast64_t")
	.dwattr $C$DW$T$70, DW_AT_type(*$C$DW$T$69)
	.dwattr $C$DW$T$70, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$70, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$70, DW_AT_decl_line(0x4f)
	.dwattr $C$DW$T$70, DW_AT_decl_column(0x16)
$C$DW$T$71	.dwtag  DW_TAG_typedef, DW_AT_name("uint_least64_t")
	.dwattr $C$DW$T$71, DW_AT_type(*$C$DW$T$69)
	.dwattr $C$DW$T$71, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$71, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$71, DW_AT_decl_line(0x41)
	.dwattr $C$DW$T$71, DW_AT_decl_column(0x16)
$C$DW$T$72	.dwtag  DW_TAG_typedef, DW_AT_name("uintmax_t")
	.dwattr $C$DW$T$72, DW_AT_type(*$C$DW$T$15)
	.dwattr $C$DW$T$72, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$72, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$72, DW_AT_decl_line(0x57)
	.dwattr $C$DW$T$72, DW_AT_decl_column(0x20)
$C$DW$T$16	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$16, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$16, DW_AT_name("float")
	.dwattr $C$DW$T$16, DW_AT_byte_size(0x04)
$C$DW$T$17	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$17, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$17, DW_AT_name("double")
	.dwattr $C$DW$T$17, DW_AT_byte_size(0x08)
$C$DW$T$18	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$18, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$18, DW_AT_name("long double")
	.dwattr $C$DW$T$18, DW_AT_byte_size(0x08)
$C$DW$T$28	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$28, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$28, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$28, DW_AT_byte_size(0x01)

$C$DW$T$29	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$29, DW_AT_name("_task")
	.dwattr $C$DW$T$29, DW_AT_byte_size(0x14)
$C$DW$29	.dwtag  DW_TAG_member
	.dwattr $C$DW$29, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$29, DW_AT_name("stack")
	.dwattr $C$DW$29, DW_AT_TI_symbol_name("stack")
	.dwattr $C$DW$29, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$29, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$29, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$29, DW_AT_decl_line(0x16)
	.dwattr $C$DW$29, DW_AT_decl_column(0x0b)
$C$DW$30	.dwtag  DW_TAG_member
	.dwattr $C$DW$30, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$30, DW_AT_name("function")
	.dwattr $C$DW$30, DW_AT_TI_symbol_name("function")
	.dwattr $C$DW$30, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$30, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$30, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$30, DW_AT_decl_line(0x18)
	.dwattr $C$DW$30, DW_AT_decl_column(0x08)
$C$DW$31	.dwtag  DW_TAG_member
	.dwattr $C$DW$31, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$31, DW_AT_name("state")
	.dwattr $C$DW$31, DW_AT_TI_symbol_name("state")
	.dwattr $C$DW$31, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$31, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$31, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$31, DW_AT_decl_line(0x19)
	.dwattr $C$DW$31, DW_AT_decl_column(0x11)
$C$DW$32	.dwtag  DW_TAG_member
	.dwattr $C$DW$32, DW_AT_type(*$C$DW$T$26)
	.dwattr $C$DW$32, DW_AT_name("uiPriority")
	.dwattr $C$DW$32, DW_AT_TI_symbol_name("uiPriority")
	.dwattr $C$DW$32, DW_AT_data_member_location[DW_OP_plus_uconst 0x9]
	.dwattr $C$DW$32, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$32, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$32, DW_AT_decl_line(0x1a)
	.dwattr $C$DW$32, DW_AT_decl_column(0x0c)
$C$DW$33	.dwtag  DW_TAG_member
	.dwattr $C$DW$33, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$33, DW_AT_name("uiCounter")
	.dwattr $C$DW$33, DW_AT_TI_symbol_name("uiCounter")
	.dwattr $C$DW$33, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr $C$DW$33, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$33, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$33, DW_AT_decl_line(0x1b)
	.dwattr $C$DW$33, DW_AT_decl_column(0x0c)
$C$DW$34	.dwtag  DW_TAG_member
	.dwattr $C$DW$34, DW_AT_type(*$C$DW$T$28)
	.dwattr $C$DW$34, DW_AT_name("bInitialized")
	.dwattr $C$DW$34, DW_AT_TI_symbol_name("bInitialized")
	.dwattr $C$DW$34, DW_AT_data_member_location[DW_OP_plus_uconst 0x10]
	.dwattr $C$DW$34, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$34, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$34, DW_AT_decl_line(0x1d)
	.dwattr $C$DW$34, DW_AT_decl_column(0x09)
	.dwendtag $C$DW$T$29

	.dwattr $C$DW$T$29, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$T$29, DW_AT_decl_line(0x15)
	.dwattr $C$DW$T$29, DW_AT_decl_column(0x10)
$C$DW$T$73	.dwtag  DW_TAG_typedef, DW_AT_name("task")
	.dwattr $C$DW$T$73, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$T$73, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$73, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$T$73, DW_AT_decl_line(0x1e)
	.dwattr $C$DW$T$73, DW_AT_decl_column(0x03)

$C$DW$T$74	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$74, DW_AT_type(*$C$DW$T$73)
	.dwattr $C$DW$T$74, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$74, DW_AT_byte_size(0x140)
$C$DW$35	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$35, DW_AT_upper_bound(0x0f)
	.dwendtag $C$DW$T$74

$C$DW$T$75	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$75, DW_AT_type(*$C$DW$T$73)
	.dwattr $C$DW$T$75, DW_AT_address_class(0x20)

$C$DW$T$25	.dwtag  DW_TAG_enumeration_type
	.dwattr $C$DW$T$25, DW_AT_name("taskState")
	.dwattr $C$DW$T$25, DW_AT_byte_size(0x01)
$C$DW$36	.dwtag  DW_TAG_enumerator, DW_AT_name("RUNNING"), DW_AT_const_value(0x00)
	.dwattr $C$DW$36, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$36, DW_AT_decl_line(0x12)
	.dwattr $C$DW$36, DW_AT_decl_column(0x10)
$C$DW$37	.dwtag  DW_TAG_enumerator, DW_AT_name("READY"), DW_AT_const_value(0x01)
	.dwattr $C$DW$37, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$37, DW_AT_decl_line(0x12)
	.dwattr $C$DW$37, DW_AT_decl_column(0x19)
$C$DW$38	.dwtag  DW_TAG_enumerator, DW_AT_name("WAITING"), DW_AT_const_value(0x02)
	.dwattr $C$DW$38, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$38, DW_AT_decl_line(0x12)
	.dwattr $C$DW$38, DW_AT_decl_column(0x20)
	.dwendtag $C$DW$T$25

	.dwattr $C$DW$T$25, DW_AT_decl_file("..\src\task.h")
	.dwattr $C$DW$T$25, DW_AT_decl_line(0x12)
	.dwattr $C$DW$T$25, DW_AT_decl_column(0x06)
	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C)

;***************************************************************
;* DWARF CIE ENTRIES                                           *
;***************************************************************

$C$DW$CIE	.dwcie 84
	.dwcfi	cfa_register, 13
	.dwcfi	cfa_offset, 0
	.dwcfi	undefined, 0
	.dwcfi	undefined, 1
	.dwcfi	undefined, 2
	.dwcfi	undefined, 3
	.dwcfi	same_value, 4
	.dwcfi	same_value, 5
	.dwcfi	same_value, 6
	.dwcfi	same_value, 7
	.dwcfi	same_value, 8
	.dwcfi	same_value, 9
	.dwcfi	same_value, 10
	.dwcfi	same_value, 11
	.dwcfi	undefined, 12
	.dwcfi	undefined, 13
	.dwcfi	undefined, 14
	.dwcfi	undefined, 15
	.dwcfi	undefined, 17
	.dwcfi	undefined, 16
	.dwcfi	undefined, 20
	.dwcfi	undefined, 21
	.dwcfi	undefined, 22
	.dwcfi	undefined, 23
	.dwcfi	undefined, 24
	.dwcfi	undefined, 25
	.dwcfi	undefined, 26
	.dwcfi	undefined, 27
	.dwcfi	undefined, 28
	.dwcfi	undefined, 29
	.dwcfi	undefined, 30
	.dwcfi	undefined, 31
	.dwcfi	undefined, 32
	.dwcfi	undefined, 33
	.dwcfi	undefined, 34
	.dwcfi	undefined, 35
	.dwcfi	same_value, 36
	.dwcfi	same_value, 37
	.dwcfi	same_value, 38
	.dwcfi	same_value, 39
	.dwcfi	same_value, 40
	.dwcfi	same_value, 41
	.dwcfi	same_value, 42
	.dwcfi	same_value, 43
	.dwcfi	same_value, 44
	.dwcfi	same_value, 45
	.dwcfi	same_value, 46
	.dwcfi	same_value, 47
	.dwcfi	same_value, 48
	.dwcfi	same_value, 49
	.dwcfi	same_value, 50
	.dwcfi	same_value, 51
	.dwcfi	undefined, 18
	.dwcfi	undefined, 19
	.dwcfi	undefined, 84
	.dwendentry

;***************************************************************
;* DWARF REGISTER MAP                                          *
;***************************************************************

$C$DW$39	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A1")
	.dwattr $C$DW$39, DW_AT_location[DW_OP_reg0]
$C$DW$40	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A2")
	.dwattr $C$DW$40, DW_AT_location[DW_OP_reg1]
$C$DW$41	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A3")
	.dwattr $C$DW$41, DW_AT_location[DW_OP_reg2]
$C$DW$42	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A4")
	.dwattr $C$DW$42, DW_AT_location[DW_OP_reg3]
$C$DW$43	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V1")
	.dwattr $C$DW$43, DW_AT_location[DW_OP_reg4]
$C$DW$44	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V2")
	.dwattr $C$DW$44, DW_AT_location[DW_OP_reg5]
$C$DW$45	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V3")
	.dwattr $C$DW$45, DW_AT_location[DW_OP_reg6]
$C$DW$46	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V4")
	.dwattr $C$DW$46, DW_AT_location[DW_OP_reg7]
$C$DW$47	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V5")
	.dwattr $C$DW$47, DW_AT_location[DW_OP_reg8]
$C$DW$48	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V6")
	.dwattr $C$DW$48, DW_AT_location[DW_OP_reg9]
$C$DW$49	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V7")
	.dwattr $C$DW$49, DW_AT_location[DW_OP_reg10]
$C$DW$50	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V8")
	.dwattr $C$DW$50, DW_AT_location[DW_OP_reg11]
$C$DW$51	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V9")
	.dwattr $C$DW$51, DW_AT_location[DW_OP_reg12]
$C$DW$52	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SP")
	.dwattr $C$DW$52, DW_AT_location[DW_OP_reg13]
$C$DW$53	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("LR")
	.dwattr $C$DW$53, DW_AT_location[DW_OP_reg14]
$C$DW$54	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PC")
	.dwattr $C$DW$54, DW_AT_location[DW_OP_reg15]
$C$DW$55	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SR")
	.dwattr $C$DW$55, DW_AT_location[DW_OP_reg17]
$C$DW$56	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AP")
	.dwattr $C$DW$56, DW_AT_location[DW_OP_reg16]
$C$DW$57	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D0")
	.dwattr $C$DW$57, DW_AT_location[DW_OP_reg20]
$C$DW$58	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D0_hi")
	.dwattr $C$DW$58, DW_AT_location[DW_OP_reg21]
$C$DW$59	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D1")
	.dwattr $C$DW$59, DW_AT_location[DW_OP_reg22]
$C$DW$60	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D1_hi")
	.dwattr $C$DW$60, DW_AT_location[DW_OP_reg23]
$C$DW$61	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D2")
	.dwattr $C$DW$61, DW_AT_location[DW_OP_reg24]
$C$DW$62	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D2_hi")
	.dwattr $C$DW$62, DW_AT_location[DW_OP_reg25]
$C$DW$63	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D3")
	.dwattr $C$DW$63, DW_AT_location[DW_OP_reg26]
$C$DW$64	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D3_hi")
	.dwattr $C$DW$64, DW_AT_location[DW_OP_reg27]
$C$DW$65	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D4")
	.dwattr $C$DW$65, DW_AT_location[DW_OP_reg28]
$C$DW$66	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D4_hi")
	.dwattr $C$DW$66, DW_AT_location[DW_OP_reg29]
$C$DW$67	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D5")
	.dwattr $C$DW$67, DW_AT_location[DW_OP_reg30]
$C$DW$68	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D5_hi")
	.dwattr $C$DW$68, DW_AT_location[DW_OP_reg31]
$C$DW$69	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D6")
	.dwattr $C$DW$69, DW_AT_location[DW_OP_regx 0x20]
$C$DW$70	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D6_hi")
	.dwattr $C$DW$70, DW_AT_location[DW_OP_regx 0x21]
$C$DW$71	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D7")
	.dwattr $C$DW$71, DW_AT_location[DW_OP_regx 0x22]
$C$DW$72	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D7_hi")
	.dwattr $C$DW$72, DW_AT_location[DW_OP_regx 0x23]
$C$DW$73	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D8")
	.dwattr $C$DW$73, DW_AT_location[DW_OP_regx 0x24]
$C$DW$74	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D8_hi")
	.dwattr $C$DW$74, DW_AT_location[DW_OP_regx 0x25]
$C$DW$75	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D9")
	.dwattr $C$DW$75, DW_AT_location[DW_OP_regx 0x26]
$C$DW$76	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D9_hi")
	.dwattr $C$DW$76, DW_AT_location[DW_OP_regx 0x27]
$C$DW$77	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D10")
	.dwattr $C$DW$77, DW_AT_location[DW_OP_regx 0x28]
$C$DW$78	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D10_hi")
	.dwattr $C$DW$78, DW_AT_location[DW_OP_regx 0x29]
$C$DW$79	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D11")
	.dwattr $C$DW$79, DW_AT_location[DW_OP_regx 0x2a]
$C$DW$80	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D11_hi")
	.dwattr $C$DW$80, DW_AT_location[DW_OP_regx 0x2b]
$C$DW$81	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D12")
	.dwattr $C$DW$81, DW_AT_location[DW_OP_regx 0x2c]
$C$DW$82	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D12_hi")
	.dwattr $C$DW$82, DW_AT_location[DW_OP_regx 0x2d]
$C$DW$83	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D13")
	.dwattr $C$DW$83, DW_AT_location[DW_OP_regx 0x2e]
$C$DW$84	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D13_hi")
	.dwattr $C$DW$84, DW_AT_location[DW_OP_regx 0x2f]
$C$DW$85	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D14")
	.dwattr $C$DW$85, DW_AT_location[DW_OP_regx 0x30]
$C$DW$86	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D14_hi")
	.dwattr $C$DW$86, DW_AT_location[DW_OP_regx 0x31]
$C$DW$87	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D15")
	.dwattr $C$DW$87, DW_AT_location[DW_OP_regx 0x32]
$C$DW$88	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D15_hi")
	.dwattr $C$DW$88, DW_AT_location[DW_OP_regx 0x33]
$C$DW$89	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FPEXC")
	.dwattr $C$DW$89, DW_AT_location[DW_OP_reg18]
$C$DW$90	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FPSCR")
	.dwattr $C$DW$90, DW_AT_location[DW_OP_reg19]
$C$DW$91	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CIE_RETA")
	.dwattr $C$DW$91, DW_AT_location[DW_OP_regx 0x54]
	.dwendtag $C$DW$CU

