;******************************************************************************
;* G3 TMS470 C/C++ Codegen                                          PC v4.9.9 *
;* Date/Time created: Tue Dec 10 11:03:53 2013                                *
;******************************************************************************
	.compiler_opts --abi=eabi --arm_vmrs_si_workaround=on --code_state=16 --disable_dual_state --embedded_constants=on --endian=little --float_support=FPv4SPD16 --hll_source=on --object_format=elf --silicon_version=7M4 --symdebug:dwarf --symdebug:dwarf_version=2 
	.thumb

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../main.c")
	.dwattr $C$DW$CU, DW_AT_producer("G3 TMS470 C/C++ Codegen PC v4.9.9 Copyright (c) 1996-2013 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("C:\Developing\workspace\versdOS\Debug")

$C$DW$1	.dwtag  DW_TAG_subprogram, DW_AT_name("addTaskToList")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("addTaskToList")
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$1, DW_AT_decl_line(0x21)
	.dwattr $C$DW$1, DW_AT_decl_column(0x06)
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$21)
$C$DW$3	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$10)
$C$DW$4	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$10)
	.dwendtag $C$DW$1

;	C:\ti\ccsv5\tools\compiler\arm_4.9.9\bin\acpia470.exe -@C:\\TEMP\\0556812 
	.sect	".text:delay"
	.clink
	.thumbfunc delay
	.thumb
	.global	delay

$C$DW$5	.dwtag  DW_TAG_subprogram, DW_AT_name("delay")
	.dwattr $C$DW$5, DW_AT_low_pc(delay)
	.dwattr $C$DW$5, DW_AT_high_pc(0x00)
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("delay")
	.dwattr $C$DW$5, DW_AT_external
	.dwattr $C$DW$5, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$5, DW_AT_TI_begin_line(0x25)
	.dwattr $C$DW$5, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$5, DW_AT_decl_file("../main.c")
	.dwattr $C$DW$5, DW_AT_decl_line(0x25)
	.dwattr $C$DW$5, DW_AT_decl_column(0x06)
	.dwattr $C$DW$5, DW_AT_TI_max_frame_size(0x08)
	.dwpsn	file "../main.c",line 38,column 1,is_stmt,address delay

	.dwfde $C$DW$CIE, delay
$C$DW$6	.dwtag  DW_TAG_formal_parameter, DW_AT_name("count")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("count")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$6, DW_AT_location[DW_OP_reg0]
;----------------------------------------------------------------------
;  37 | void delay(unsigned int count)                                         
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: delay                                                      *
;*                                                                           *
;*   Regs Modified     : A1,A2,SP,SR                                         *
;*   Regs Used         : A1,A2,SP,LR,SR                                      *
;*   Local Frame Size  : 0 Args + 4 Auto + 0 Save = 4 byte                   *
;*****************************************************************************
delay:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
        SUB       SP, SP, #8            ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 8
$C$DW$7	.dwtag  DW_TAG_variable, DW_AT_name("count")
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("count")
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$7, DW_AT_location[DW_OP_breg13 0]
        STR       A1, [SP, #0]          ; [DPU_3_PIPE] |38| 
	.dwpsn	file "../main.c",line 39,column 2,is_stmt
;----------------------------------------------------------------------
;  39 | while(count--);                                                        
;----------------------------------------------------------------------
        LDR       A1, [SP, #0]          ; [DPU_3_PIPE] |39| 
        SUBS      A2, A1, #1            ; [DPU_3_PIPE] |39| 
        STR       A2, [SP, #0]          ; [DPU_3_PIPE] |39| 
        CBZ       A1, ||$C$L2||         ; [] 
        ; BRANCHCC OCCURS {||$C$L2||}    ; [] |39| 
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L1||
;*
;*   Loop source line                : 39
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L1||:    
$C$DW$L$delay$2$B:
        LDR       A1, [SP, #0]          ; [DPU_3_PIPE] |39| 
        SUBS      A2, A1, #1            ; [DPU_3_PIPE] |39| 
        CMP       A1, #0                ; [DPU_3_PIPE] |39| 
        STR       A2, [SP, #0]          ; [DPU_3_PIPE] |39| 
        BNE       ||$C$L1||             ; [DPU_3_PIPE] |39| 
        ; BRANCHCC OCCURS {||$C$L1||}    ; [] |39| 
$C$DW$L$delay$2$E:
;* --------------------------------------------------------------------------*
	.dwpsn	file "../main.c",line 40,column 1,is_stmt
;* --------------------------------------------------------------------------*
||$C$L2||:    
        ADD       SP, SP, #8            ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 0
$C$DW$8	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$8, DW_AT_low_pc(0x00)
	.dwattr $C$DW$8, DW_AT_TI_return
        BX        LR                    ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 

$C$DW$9	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$9, DW_AT_name("C:\Developing\workspace\versdOS\Debug\main.asm:$C$L1:1:1386669833")
	.dwattr $C$DW$9, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$9, DW_AT_TI_begin_line(0x27)
	.dwattr $C$DW$9, DW_AT_TI_end_line(0x27)
$C$DW$10	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$10, DW_AT_low_pc($C$DW$L$delay$2$B)
	.dwattr $C$DW$10, DW_AT_high_pc($C$DW$L$delay$2$E)
	.dwendtag $C$DW$9

	.dwattr $C$DW$5, DW_AT_TI_end_file("../main.c")
	.dwattr $C$DW$5, DW_AT_TI_end_line(0x28)
	.dwattr $C$DW$5, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$5

	.sect	".text:toggleRed"
	.clink
	.thumbfunc toggleRed
	.thumb
	.global	toggleRed

$C$DW$11	.dwtag  DW_TAG_subprogram, DW_AT_name("toggleRed")
	.dwattr $C$DW$11, DW_AT_low_pc(toggleRed)
	.dwattr $C$DW$11, DW_AT_high_pc(0x00)
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("toggleRed")
	.dwattr $C$DW$11, DW_AT_external
	.dwattr $C$DW$11, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$11, DW_AT_TI_begin_line(0x2b)
	.dwattr $C$DW$11, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$11, DW_AT_decl_file("../main.c")
	.dwattr $C$DW$11, DW_AT_decl_line(0x2b)
	.dwattr $C$DW$11, DW_AT_decl_column(0x06)
	.dwattr $C$DW$11, DW_AT_TI_max_frame_size(0x08)
	.dwpsn	file "../main.c",line 44,column 1,is_stmt,address toggleRed

	.dwfde $C$DW$CIE, toggleRed
;----------------------------------------------------------------------
;  43 | void toggleRed(void)                                                   
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: toggleRed                                                  *
;*                                                                           *
;*   Regs Modified     : A1,A2,A4,V9,SP,LR,SR,FPEXC,FPSCR                    *
;*   Regs Used         : A1,A2,A4,V9,SP,LR,SR,FPEXC,FPSCR                    *
;*   Local Frame Size  : 0 Args + 0 Auto + 4 Save = 4 byte                   *
;*****************************************************************************
toggleRed:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
        PUSH      {A4, LR}              ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 4
	.dwcfi	save_reg_to_mem, 14, -4
	.dwcfi	cfa_offset, 8
	.dwcfi	save_reg_to_mem, 3, -8
	.dwcfi	cfa_offset, 8
	.dwpsn	file "../main.c",line 45,column 8,is_stmt
;----------------------------------------------------------------------
;  45 | while(1)                                                               
;----------------------------------------------------------------------
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L3||
;*
;*   Loop source line                : 45
;*   Loop closing brace source line  : 49
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L3||:    
$C$DW$L$toggleRed$2$B:
	.dwpsn	file "../main.c",line 47,column 3,is_stmt
;----------------------------------------------------------------------
;  47 | GPIO_PORTF_AHB_DATA_R   ^= RED_LED;             //Toggle red led.. surp
;     | rise!                                                                  
;----------------------------------------------------------------------
        LDR       A2, $C$CON1           ; [DPU_3_PIPE] |47| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |47| 
        EOR       A1, A1, #2            ; [DPU_3_PIPE] |47| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |47| 
	.dwpsn	file "../main.c",line 48,column 3,is_stmt
;----------------------------------------------------------------------
;  48 | delay(3000000);                                                        
;----------------------------------------------------------------------
        LDR       A1, $C$CON2           ; [DPU_3_PIPE] |48| 
$C$DW$12	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$12, DW_AT_low_pc(0x00)
	.dwattr $C$DW$12, DW_AT_name("delay")
	.dwattr $C$DW$12, DW_AT_TI_call
        BL        delay                 ; [DPU_3_PIPE] |48| 
        ; CALL OCCURS {delay }           ; [] |48| 
	.dwpsn	file "../main.c",line 45,column 8,is_stmt
        B         ||$C$L3||             ; [DPU_3_PIPE] |45| 
        ; BRANCH OCCURS {||$C$L3||}      ; [] |45| 
$C$DW$L$toggleRed$2$E:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 8

$C$DW$13	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$13, DW_AT_name("C:\Developing\workspace\versdOS\Debug\main.asm:$C$L3:1:1386669833")
	.dwattr $C$DW$13, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$13, DW_AT_TI_begin_line(0x2d)
	.dwattr $C$DW$13, DW_AT_TI_end_line(0x31)
$C$DW$14	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$14, DW_AT_low_pc($C$DW$L$toggleRed$2$B)
	.dwattr $C$DW$14, DW_AT_high_pc($C$DW$L$toggleRed$2$E)
	.dwendtag $C$DW$13

	.dwattr $C$DW$11, DW_AT_TI_end_file("../main.c")
	.dwattr $C$DW$11, DW_AT_TI_end_line(0x32)
	.dwattr $C$DW$11, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$11

	.sect	".text:toggleGreen"
	.clink
	.thumbfunc toggleGreen
	.thumb
	.global	toggleGreen

$C$DW$15	.dwtag  DW_TAG_subprogram, DW_AT_name("toggleGreen")
	.dwattr $C$DW$15, DW_AT_low_pc(toggleGreen)
	.dwattr $C$DW$15, DW_AT_high_pc(0x00)
	.dwattr $C$DW$15, DW_AT_TI_symbol_name("toggleGreen")
	.dwattr $C$DW$15, DW_AT_external
	.dwattr $C$DW$15, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$15, DW_AT_TI_begin_line(0x34)
	.dwattr $C$DW$15, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$15, DW_AT_decl_file("../main.c")
	.dwattr $C$DW$15, DW_AT_decl_line(0x34)
	.dwattr $C$DW$15, DW_AT_decl_column(0x06)
	.dwattr $C$DW$15, DW_AT_TI_max_frame_size(0x08)
	.dwpsn	file "../main.c",line 53,column 1,is_stmt,address toggleGreen

	.dwfde $C$DW$CIE, toggleGreen
;----------------------------------------------------------------------
;  52 | void toggleGreen(void)                                                 
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: toggleGreen                                                *
;*                                                                           *
;*   Regs Modified     : A1,A2,A4,V9,SP,LR,SR,FPEXC,FPSCR                    *
;*   Regs Used         : A1,A2,A4,V9,SP,LR,SR,FPEXC,FPSCR                    *
;*   Local Frame Size  : 0 Args + 0 Auto + 4 Save = 4 byte                   *
;*****************************************************************************
toggleGreen:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
        PUSH      {A4, LR}              ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 4
	.dwcfi	save_reg_to_mem, 14, -4
	.dwcfi	cfa_offset, 8
	.dwcfi	save_reg_to_mem, 3, -8
	.dwcfi	cfa_offset, 8
	.dwpsn	file "../main.c",line 54,column 8,is_stmt
;----------------------------------------------------------------------
;  54 | while(1)                                                               
;----------------------------------------------------------------------
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L4||
;*
;*   Loop source line                : 54
;*   Loop closing brace source line  : 58
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L4||:    
$C$DW$L$toggleGreen$2$B:
	.dwpsn	file "../main.c",line 56,column 3,is_stmt
;----------------------------------------------------------------------
;  56 | GPIO_PORTF_AHB_DATA_R   ^= GREEN_LED;   //Toggle green led..           
;----------------------------------------------------------------------
        LDR       A2, $C$CON3           ; [DPU_3_PIPE] |56| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |56| 
        EOR       A1, A1, #8            ; [DPU_3_PIPE] |56| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |56| 
	.dwpsn	file "../main.c",line 57,column 3,is_stmt
;----------------------------------------------------------------------
;  57 | delay(6000000);                                                        
;----------------------------------------------------------------------
        LDR       A1, $C$CON4           ; [DPU_3_PIPE] |57| 
$C$DW$16	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$16, DW_AT_low_pc(0x00)
	.dwattr $C$DW$16, DW_AT_name("delay")
	.dwattr $C$DW$16, DW_AT_TI_call
        BL        delay                 ; [DPU_3_PIPE] |57| 
        ; CALL OCCURS {delay }           ; [] |57| 
	.dwpsn	file "../main.c",line 54,column 8,is_stmt
        B         ||$C$L4||             ; [DPU_3_PIPE] |54| 
        ; BRANCH OCCURS {||$C$L4||}      ; [] |54| 
$C$DW$L$toggleGreen$2$E:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 8

$C$DW$17	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$17, DW_AT_name("C:\Developing\workspace\versdOS\Debug\main.asm:$C$L4:1:1386669833")
	.dwattr $C$DW$17, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$17, DW_AT_TI_begin_line(0x36)
	.dwattr $C$DW$17, DW_AT_TI_end_line(0x3a)
$C$DW$18	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$18, DW_AT_low_pc($C$DW$L$toggleGreen$2$B)
	.dwattr $C$DW$18, DW_AT_high_pc($C$DW$L$toggleGreen$2$E)
	.dwendtag $C$DW$17

	.dwattr $C$DW$15, DW_AT_TI_end_file("../main.c")
	.dwattr $C$DW$15, DW_AT_TI_end_line(0x3b)
	.dwattr $C$DW$15, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$15

	.sect	".text:toggleBlue"
	.clink
	.thumbfunc toggleBlue
	.thumb
	.global	toggleBlue

$C$DW$19	.dwtag  DW_TAG_subprogram, DW_AT_name("toggleBlue")
	.dwattr $C$DW$19, DW_AT_low_pc(toggleBlue)
	.dwattr $C$DW$19, DW_AT_high_pc(0x00)
	.dwattr $C$DW$19, DW_AT_TI_symbol_name("toggleBlue")
	.dwattr $C$DW$19, DW_AT_external
	.dwattr $C$DW$19, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$19, DW_AT_TI_begin_line(0x3d)
	.dwattr $C$DW$19, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$19, DW_AT_decl_file("../main.c")
	.dwattr $C$DW$19, DW_AT_decl_line(0x3d)
	.dwattr $C$DW$19, DW_AT_decl_column(0x06)
	.dwattr $C$DW$19, DW_AT_TI_max_frame_size(0x08)
	.dwpsn	file "../main.c",line 62,column 1,is_stmt,address toggleBlue

	.dwfde $C$DW$CIE, toggleBlue
;----------------------------------------------------------------------
;  61 | void toggleBlue(void)                                                  
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: toggleBlue                                                 *
;*                                                                           *
;*   Regs Modified     : A1,A2,A4,V9,SP,LR,SR,FPEXC,FPSCR                    *
;*   Regs Used         : A1,A2,A4,V9,SP,LR,SR,FPEXC,FPSCR                    *
;*   Local Frame Size  : 0 Args + 0 Auto + 4 Save = 4 byte                   *
;*****************************************************************************
toggleBlue:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
        PUSH      {A4, LR}              ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 4
	.dwcfi	save_reg_to_mem, 14, -4
	.dwcfi	cfa_offset, 8
	.dwcfi	save_reg_to_mem, 3, -8
	.dwcfi	cfa_offset, 8
	.dwpsn	file "../main.c",line 63,column 8,is_stmt
;----------------------------------------------------------------------
;  63 | while(1)                                                               
;----------------------------------------------------------------------
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L5||
;*
;*   Loop source line                : 63
;*   Loop closing brace source line  : 67
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L5||:    
$C$DW$L$toggleBlue$2$B:
	.dwpsn	file "../main.c",line 65,column 3,is_stmt
;----------------------------------------------------------------------
;  65 | GPIO_PORTF_AHB_DATA_R   ^= BLUE_LED;    //Toggle blue led..            
;----------------------------------------------------------------------
        LDR       A2, $C$CON5           ; [DPU_3_PIPE] |65| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |65| 
        EOR       A1, A1, #4            ; [DPU_3_PIPE] |65| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |65| 
	.dwpsn	file "../main.c",line 66,column 3,is_stmt
;----------------------------------------------------------------------
;  66 | delay(1500000);                                                        
;----------------------------------------------------------------------
        LDR       A1, $C$CON6           ; [DPU_3_PIPE] |66| 
$C$DW$20	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$20, DW_AT_low_pc(0x00)
	.dwattr $C$DW$20, DW_AT_name("delay")
	.dwattr $C$DW$20, DW_AT_TI_call
        BL        delay                 ; [DPU_3_PIPE] |66| 
        ; CALL OCCURS {delay }           ; [] |66| 
	.dwpsn	file "../main.c",line 63,column 8,is_stmt
        B         ||$C$L5||             ; [DPU_3_PIPE] |63| 
        ; BRANCH OCCURS {||$C$L5||}      ; [] |63| 
$C$DW$L$toggleBlue$2$E:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 8

$C$DW$21	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$21, DW_AT_name("C:\Developing\workspace\versdOS\Debug\main.asm:$C$L5:1:1386669833")
	.dwattr $C$DW$21, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$21, DW_AT_TI_begin_line(0x3f)
	.dwattr $C$DW$21, DW_AT_TI_end_line(0x43)
$C$DW$22	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$22, DW_AT_low_pc($C$DW$L$toggleBlue$2$B)
	.dwattr $C$DW$22, DW_AT_high_pc($C$DW$L$toggleBlue$2$E)
	.dwendtag $C$DW$21

	.dwattr $C$DW$19, DW_AT_TI_end_file("../main.c")
	.dwattr $C$DW$19, DW_AT_TI_end_line(0x44)
	.dwattr $C$DW$19, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$19

	.sect	".text:initLeds"
	.clink
	.thumbfunc initLeds
	.thumb
	.global	initLeds

$C$DW$23	.dwtag  DW_TAG_subprogram, DW_AT_name("initLeds")
	.dwattr $C$DW$23, DW_AT_low_pc(initLeds)
	.dwattr $C$DW$23, DW_AT_high_pc(0x00)
	.dwattr $C$DW$23, DW_AT_TI_symbol_name("initLeds")
	.dwattr $C$DW$23, DW_AT_external
	.dwattr $C$DW$23, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$23, DW_AT_TI_begin_line(0x46)
	.dwattr $C$DW$23, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$23, DW_AT_decl_file("../main.c")
	.dwattr $C$DW$23, DW_AT_decl_line(0x46)
	.dwattr $C$DW$23, DW_AT_decl_column(0x06)
	.dwattr $C$DW$23, DW_AT_TI_max_frame_size(0x00)
	.dwpsn	file "../main.c",line 71,column 1,is_stmt,address initLeds

	.dwfde $C$DW$CIE, initLeds
;----------------------------------------------------------------------
;  70 | void initLeds(void)                                                    
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: initLeds                                                   *
;*                                                                           *
;*   Regs Modified     : A1,A2,SR                                            *
;*   Regs Used         : A1,A2,LR,SR                                         *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                   *
;*****************************************************************************
initLeds:
;* --------------------------------------------------------------------------*
;----------------------------------------------------------------------
;  72 | // Enable and configure the GPIO port for the LED operation.           
;----------------------------------------------------------------------
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
	.dwpsn	file "../main.c",line 73,column 2,is_stmt
;----------------------------------------------------------------------
;  73 | SYSCTL_RCGCGPIO_R               = SYSCTL_RCGC2_GPIOF;
;     |  //Enable clock for GPIOF                                              
;----------------------------------------------------------------------
        LDR       A2, $C$CON7           ; [DPU_3_PIPE] |73| 
        MOVS      A1, #32               ; [DPU_3_PIPE] |73| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |73| 
	.dwpsn	file "../main.c",line 74,column 2,is_stmt
;----------------------------------------------------------------------
;  74 | SYSCTL_GPIOHBCTL_R              = (1<<5);
;     |                  //Enable the AHB for portf                            
;  76 | //actually configure the pins                                          
;----------------------------------------------------------------------
        LDR       A2, $C$CON8           ; [DPU_3_PIPE] |74| 
        MOVS      A1, #32               ; [DPU_3_PIPE] |74| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |74| 
	.dwpsn	file "../main.c",line 77,column 2,is_stmt
;----------------------------------------------------------------------
;  77 | GPIO_PORTF_AHB_DEN_R    = RED_LED|BLUE_LED|GREEN_LED;   //Digital enabl
;     | e pins                                                                 
;----------------------------------------------------------------------
        LDR       A2, $C$CON9           ; [DPU_3_PIPE] |77| 
        MOVS      A1, #14               ; [DPU_3_PIPE] |77| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |77| 
	.dwpsn	file "../main.c",line 78,column 2,is_stmt
;----------------------------------------------------------------------
;  78 | GPIO_PORTF_AHB_DIR_R    = RED_LED|BLUE_LED|GREEN_LED;   //Set pins to o
;     | utput                                                                  
;----------------------------------------------------------------------
        LDR       A2, $C$CON10          ; [DPU_3_PIPE] |78| 
        MOVS      A1, #14               ; [DPU_3_PIPE] |78| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |78| 
	.dwpsn	file "../main.c",line 79,column 2,is_stmt
;----------------------------------------------------------------------
;  79 | GPIO_PORTF_AHB_DATA_R   = 0;
;     |          //Make PORTF low                                              
;----------------------------------------------------------------------
        LDR       A2, $C$CON11          ; [DPU_3_PIPE] |79| 
        MOVS      A1, #0                ; [DPU_3_PIPE] |79| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |79| 
	.dwpsn	file "../main.c",line 80,column 1,is_stmt
$C$DW$24	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$24, DW_AT_low_pc(0x00)
	.dwattr $C$DW$24, DW_AT_TI_return
        BX        LR                    ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$23, DW_AT_TI_end_file("../main.c")
	.dwattr $C$DW$23, DW_AT_TI_end_line(0x50)
	.dwattr $C$DW$23, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$23

	.sect	".text:main"
	.clink
	.thumbfunc main
	.thumb
	.global	main

$C$DW$25	.dwtag  DW_TAG_subprogram, DW_AT_name("main")
	.dwattr $C$DW$25, DW_AT_low_pc(main)
	.dwattr $C$DW$25, DW_AT_high_pc(0x00)
	.dwattr $C$DW$25, DW_AT_TI_symbol_name("main")
	.dwattr $C$DW$25, DW_AT_external
	.dwattr $C$DW$25, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$25, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$25, DW_AT_TI_begin_line(0x54)
	.dwattr $C$DW$25, DW_AT_TI_begin_column(0x05)
	.dwattr $C$DW$25, DW_AT_decl_file("../main.c")
	.dwattr $C$DW$25, DW_AT_decl_line(0x54)
	.dwattr $C$DW$25, DW_AT_decl_column(0x05)
	.dwattr $C$DW$25, DW_AT_TI_max_frame_size(0x08)
	.dwpsn	file "../main.c",line 85,column 1,is_stmt,address main

	.dwfde $C$DW$CIE, main
;----------------------------------------------------------------------
;  84 | int main(void)                                                         
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: main                                                       *
;*                                                                           *
;*   Regs Modified     : A1,A2,A3,A4,V9,SP,LR,SR,D0,D0_hi,D1,D1_hi,D2,D2_hi, *
;*                           D3,D3_hi,D4,D4_hi,D5,D5_hi,D6,D6_hi,D7,D7_hi,   *
;*                           FPEXC,FPSCR                                     *
;*   Regs Used         : A1,A2,A3,A4,V9,SP,LR,SR,D0,D0_hi,D1,D1_hi,D2,D2_hi, *
;*                           D3,D3_hi,D4,D4_hi,D5,D5_hi,D6,D6_hi,D7,D7_hi,   *
;*                           FPEXC,FPSCR                                     *
;*   Local Frame Size  : 0 Args + 0 Auto + 4 Save = 4 byte                   *
;*****************************************************************************
main:
;* --------------------------------------------------------------------------*
;----------------------------------------------------------------------
;  86 | // Setup the system clock to run at 40 Mhz from PLL with crystal refere
;     | nce                                                                    
;----------------------------------------------------------------------
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
        PUSH      {A4, LR}              ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 4
	.dwcfi	save_reg_to_mem, 14, -4
	.dwcfi	cfa_offset, 8
	.dwcfi	save_reg_to_mem, 3, -8
	.dwcfi	cfa_offset, 8
	.dwpsn	file "../main.c",line 87,column 2,is_stmt
;----------------------------------------------------------------------
;  87 | SYSCTL_RCC_R = 0x02C00540;                                             
;----------------------------------------------------------------------
        LDR       A1, $C$CON13          ; [DPU_3_PIPE] |87| 
        LDR       A2, $C$CON12          ; [DPU_3_PIPE] |87| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |87| 
	.dwpsn	file "../main.c",line 89,column 2,is_stmt
;----------------------------------------------------------------------
;  89 | initLeds();                                                            
;  91 | //fpointer, stacksize, priority                                        
;----------------------------------------------------------------------
$C$DW$26	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$26, DW_AT_low_pc(0x00)
	.dwattr $C$DW$26, DW_AT_name("initLeds")
	.dwattr $C$DW$26, DW_AT_TI_call
        BL        initLeds              ; [DPU_3_PIPE] |89| 
        ; CALL OCCURS {initLeds }        ; [] |89| 
	.dwpsn	file "../main.c",line 92,column 2,is_stmt
;----------------------------------------------------------------------
;  92 | addTaskToList(toggleRed         , 128, 2);                             
;----------------------------------------------------------------------
        MOVS      A3, #2                ; [DPU_3_PIPE] |92| 
        MOVS      A2, #128              ; [DPU_3_PIPE] |92| 
        LDR       A1, $C$CON14          ; [DPU_3_PIPE] |92| 
$C$DW$27	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$27, DW_AT_low_pc(0x00)
	.dwattr $C$DW$27, DW_AT_name("addTaskToList")
	.dwattr $C$DW$27, DW_AT_TI_call
        BL        addTaskToList         ; [DPU_3_PIPE] |92| 
        ; CALL OCCURS {addTaskToList }   ; [] |92| 
	.dwpsn	file "../main.c",line 93,column 2,is_stmt
;----------------------------------------------------------------------
;  93 | addTaskToList(toggleGreen       , 128, 2);                             
;----------------------------------------------------------------------
        MOVS      A3, #2                ; [DPU_3_PIPE] |93| 
        MOVS      A2, #128              ; [DPU_3_PIPE] |93| 
        LDR       A1, $C$CON15          ; [DPU_3_PIPE] |93| 
$C$DW$28	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$28, DW_AT_low_pc(0x00)
	.dwattr $C$DW$28, DW_AT_name("addTaskToList")
	.dwattr $C$DW$28, DW_AT_TI_call
        BL        addTaskToList         ; [DPU_3_PIPE] |93| 
        ; CALL OCCURS {addTaskToList }   ; [] |93| 
	.dwpsn	file "../main.c",line 94,column 2,is_stmt
;----------------------------------------------------------------------
;  94 | addTaskToList(toggleBlue        , 128, 2);                             
;  96 | //Configure Systick                                                    
;----------------------------------------------------------------------
        MOVS      A3, #2                ; [DPU_3_PIPE] |94| 
        MOVS      A2, #128              ; [DPU_3_PIPE] |94| 
        LDR       A1, $C$CON16          ; [DPU_3_PIPE] |94| 
$C$DW$29	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$29, DW_AT_low_pc(0x00)
	.dwattr $C$DW$29, DW_AT_name("addTaskToList")
	.dwattr $C$DW$29, DW_AT_TI_call
        BL        addTaskToList         ; [DPU_3_PIPE] |94| 
        ; CALL OCCURS {addTaskToList }   ; [] |94| 
	.dwpsn	file "../main.c",line 97,column 2,is_stmt
;----------------------------------------------------------------------
;  97 | NVIC_ST_RELOAD_R        = F_TICK-1;             //a systick every ms   
;----------------------------------------------------------------------
        LDR       A2, $C$CON17          ; [DPU_3_PIPE] |97| 
        MOV       A1, #39999            ; [DPU_3_PIPE] |97| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |97| 
	.dwpsn	file "../main.c",line 98,column 2,is_stmt
;----------------------------------------------------------------------
;  98 | NVIC_ST_CTRL_R          = 0x7;                  //enable systick timer,
;     |  interrupt, main clock source                                          
; 100 | //Interupt enable                                                      
;----------------------------------------------------------------------
        LDR       A2, $C$CON18          ; [DPU_3_PIPE] |98| 
        MOVS      A1, #7                ; [DPU_3_PIPE] |98| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |98| 
	.dwpsn	file "../main.c",line 101,column 2,is_stmt
;----------------------------------------------------------------------
; 101 | NVIC_EN0_R                      |= (1<<15);             //systick is ve
;     | ctor 15 in the interrupt table, enable it                              
;----------------------------------------------------------------------
        LDR       A2, $C$CON19          ; [DPU_3_PIPE] |101| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |101| 
        ORR       A1, A1, #32768        ; [DPU_3_PIPE] |101| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |101| 
	.dwpsn	file "../main.c",line 103,column 11,is_stmt
;----------------------------------------------------------------------
; 103 | while(1)                                                               
; 105 |     //this could be used as an idle function                           
; 106 |     //sleep();                                                         
;----------------------------------------------------------------------
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L6||
;*
;*   Loop source line                : 103
;*   Loop closing brace source line  : 107
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L6||:    
$C$DW$L$main$2$B:
        B         ||$C$L6||             ; [DPU_3_PIPE] |103| 
        ; BRANCH OCCURS {||$C$L6||}      ; [] |103| 
$C$DW$L$main$2$E:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 8

$C$DW$30	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$30, DW_AT_name("C:\Developing\workspace\versdOS\Debug\main.asm:$C$L6:1:1386669833")
	.dwattr $C$DW$30, DW_AT_TI_begin_file("../main.c")
	.dwattr $C$DW$30, DW_AT_TI_begin_line(0x67)
	.dwattr $C$DW$30, DW_AT_TI_end_line(0x6b)
$C$DW$31	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$31, DW_AT_low_pc($C$DW$L$main$2$B)
	.dwattr $C$DW$31, DW_AT_high_pc($C$DW$L$main$2$E)
	.dwendtag $C$DW$30

	.dwattr $C$DW$25, DW_AT_TI_end_file("../main.c")
	.dwattr $C$DW$25, DW_AT_TI_end_line(0x6c)
	.dwattr $C$DW$25, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$25

;******************************************************************************
;* CONSTANT TABLE                                                             *
;******************************************************************************
	.sect	".text:toggleRed"
	.align	4
||$C$CON1||:	.bits	1074123772,32
	.align	4
||$C$CON2||:	.bits	3000000,32
;******************************************************************************
;* CONSTANT TABLE                                                             *
;******************************************************************************
	.sect	".text:toggleGreen"
	.align	4
||$C$CON3||:	.bits	1074123772,32
	.align	4
||$C$CON4||:	.bits	6000000,32
;******************************************************************************
;* CONSTANT TABLE                                                             *
;******************************************************************************
	.sect	".text:toggleBlue"
	.align	4
||$C$CON5||:	.bits	1074123772,32
	.align	4
||$C$CON6||:	.bits	1500000,32
;******************************************************************************
;* CONSTANT TABLE                                                             *
;******************************************************************************
	.sect	".text:initLeds"
	.align	4
||$C$CON7||:	.bits	1074783752,32
	.align	4
||$C$CON8||:	.bits	1074782316,32
	.align	4
||$C$CON9||:	.bits	1074124060,32
	.align	4
||$C$CON10||:	.bits	1074123776,32
	.align	4
||$C$CON11||:	.bits	1074123772,32
;******************************************************************************
;* CONSTANT TABLE                                                             *
;******************************************************************************
	.sect	".text:main"
	.align	4
||$C$CON12||:	.bits	1074782304,32
	.align	4
||$C$CON13||:	.bits	46138688,32
	.align	4
||$C$CON14||:	.bits	toggleRed,32
	.align	4
||$C$CON15||:	.bits	toggleGreen,32
	.align	4
||$C$CON16||:	.bits	toggleBlue,32
	.align	4
||$C$CON17||:	.bits	-536813548,32
	.align	4
||$C$CON18||:	.bits	-536813552,32
	.align	4
||$C$CON19||:	.bits	-536813312,32
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	addTaskToList

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
$C$DW$T$3	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$3, DW_AT_address_class(0x20)
$C$DW$T$27	.dwtag  DW_TAG_typedef, DW_AT_name("__builtin_va_list")
	.dwattr $C$DW$T$27, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$T$27, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$27, DW_AT_decl_file("../main.c")
	.dwattr $C$DW$T$27, DW_AT_decl_line(0x6c)
	.dwattr $C$DW$T$27, DW_AT_decl_column(0x01)

$C$DW$T$20	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$20, DW_AT_language(DW_LANG_C)
$C$DW$T$21	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$21, DW_AT_address_class(0x20)
$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)
$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)
$C$DW$T$32	.dwtag  DW_TAG_typedef, DW_AT_name("int8_t")
	.dwattr $C$DW$T$32, DW_AT_type(*$C$DW$T$5)
	.dwattr $C$DW$T$32, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$32, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$32, DW_AT_decl_line(0x2a)
	.dwattr $C$DW$T$32, DW_AT_decl_column(0x1d)
$C$DW$T$33	.dwtag  DW_TAG_typedef, DW_AT_name("int_least8_t")
	.dwattr $C$DW$T$33, DW_AT_type(*$C$DW$T$32)
	.dwattr $C$DW$T$33, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$33, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$33, DW_AT_decl_line(0x37)
	.dwattr $C$DW$T$33, DW_AT_decl_column(0x17)
$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)
$C$DW$T$23	.dwtag  DW_TAG_typedef, DW_AT_name("uint8_t")
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$T$6)
	.dwattr $C$DW$T$23, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$23, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$23, DW_AT_decl_line(0x2b)
	.dwattr $C$DW$T$23, DW_AT_decl_column(0x1c)
$C$DW$T$34	.dwtag  DW_TAG_typedef, DW_AT_name("uint_least8_t")
	.dwattr $C$DW$T$34, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$T$34, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$34, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$34, DW_AT_decl_line(0x38)
	.dwattr $C$DW$T$34, DW_AT_decl_column(0x16)
$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x02)
$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x02)
$C$DW$T$35	.dwtag  DW_TAG_typedef, DW_AT_name("int16_t")
	.dwattr $C$DW$T$35, DW_AT_type(*$C$DW$T$8)
	.dwattr $C$DW$T$35, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$35, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$35, DW_AT_decl_line(0x2c)
	.dwattr $C$DW$T$35, DW_AT_decl_column(0x1d)
$C$DW$T$36	.dwtag  DW_TAG_typedef, DW_AT_name("int_least16_t")
	.dwattr $C$DW$T$36, DW_AT_type(*$C$DW$T$35)
	.dwattr $C$DW$T$36, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$36, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$36, DW_AT_decl_line(0x3a)
	.dwattr $C$DW$T$36, DW_AT_decl_column(0x17)
$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x02)
$C$DW$T$37	.dwtag  DW_TAG_typedef, DW_AT_name("uint16_t")
	.dwattr $C$DW$T$37, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$37, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$37, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$37, DW_AT_decl_line(0x2d)
	.dwattr $C$DW$T$37, DW_AT_decl_column(0x1c)
$C$DW$T$38	.dwtag  DW_TAG_typedef, DW_AT_name("uint_least16_t")
	.dwattr $C$DW$T$38, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$T$38, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$38, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$38, DW_AT_decl_line(0x3b)
	.dwattr $C$DW$T$38, DW_AT_decl_column(0x16)
$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x04)
$C$DW$T$19	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$19, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$19, DW_AT_address_class(0x20)
$C$DW$T$40	.dwtag  DW_TAG_typedef, DW_AT_name("int32_t")
	.dwattr $C$DW$T$40, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$40, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$40, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$40, DW_AT_decl_line(0x2e)
	.dwattr $C$DW$T$40, DW_AT_decl_column(0x1d)
$C$DW$T$41	.dwtag  DW_TAG_typedef, DW_AT_name("int_fast16_t")
	.dwattr $C$DW$T$41, DW_AT_type(*$C$DW$T$40)
	.dwattr $C$DW$T$41, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$41, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$41, DW_AT_decl_line(0x47)
	.dwattr $C$DW$T$41, DW_AT_decl_column(0x17)
$C$DW$T$42	.dwtag  DW_TAG_typedef, DW_AT_name("int_fast32_t")
	.dwattr $C$DW$T$42, DW_AT_type(*$C$DW$T$40)
	.dwattr $C$DW$T$42, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$42, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$42, DW_AT_decl_line(0x4a)
	.dwattr $C$DW$T$42, DW_AT_decl_column(0x17)
$C$DW$T$43	.dwtag  DW_TAG_typedef, DW_AT_name("int_fast8_t")
	.dwattr $C$DW$T$43, DW_AT_type(*$C$DW$T$40)
	.dwattr $C$DW$T$43, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$43, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$43, DW_AT_decl_line(0x45)
	.dwattr $C$DW$T$43, DW_AT_decl_column(0x17)
$C$DW$T$44	.dwtag  DW_TAG_typedef, DW_AT_name("int_least32_t")
	.dwattr $C$DW$T$44, DW_AT_type(*$C$DW$T$40)
	.dwattr $C$DW$T$44, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$44, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$44, DW_AT_decl_line(0x3c)
	.dwattr $C$DW$T$44, DW_AT_decl_column(0x17)
$C$DW$T$45	.dwtag  DW_TAG_typedef, DW_AT_name("intptr_t")
	.dwattr $C$DW$T$45, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$45, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$45, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$45, DW_AT_decl_line(0x52)
	.dwattr $C$DW$T$45, DW_AT_decl_column(0x1a)
$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x04)
$C$DW$T$24	.dwtag  DW_TAG_typedef, DW_AT_name("uint32_t")
	.dwattr $C$DW$T$24, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$24, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$24, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$24, DW_AT_decl_line(0x2f)
	.dwattr $C$DW$T$24, DW_AT_decl_column(0x1c)
$C$DW$T$46	.dwtag  DW_TAG_typedef, DW_AT_name("uint_fast16_t")
	.dwattr $C$DW$T$46, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$T$46, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$46, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$46, DW_AT_decl_line(0x48)
	.dwattr $C$DW$T$46, DW_AT_decl_column(0x16)
$C$DW$T$47	.dwtag  DW_TAG_typedef, DW_AT_name("uint_fast32_t")
	.dwattr $C$DW$T$47, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$T$47, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$47, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$47, DW_AT_decl_line(0x4b)
	.dwattr $C$DW$T$47, DW_AT_decl_column(0x16)
$C$DW$T$48	.dwtag  DW_TAG_typedef, DW_AT_name("uint_fast8_t")
	.dwattr $C$DW$T$48, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$T$48, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$48, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$48, DW_AT_decl_line(0x46)
	.dwattr $C$DW$T$48, DW_AT_decl_column(0x16)
$C$DW$T$49	.dwtag  DW_TAG_typedef, DW_AT_name("uint_least32_t")
	.dwattr $C$DW$T$49, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$T$49, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$49, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$49, DW_AT_decl_line(0x3d)
	.dwattr $C$DW$T$49, DW_AT_decl_column(0x16)
$C$DW$T$50	.dwtag  DW_TAG_typedef, DW_AT_name("uintptr_t")
	.dwattr $C$DW$T$50, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$50, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$50, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$50, DW_AT_decl_line(0x53)
	.dwattr $C$DW$T$50, DW_AT_decl_column(0x1a)
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
$C$DW$T$53	.dwtag  DW_TAG_typedef, DW_AT_name("int64_t")
	.dwattr $C$DW$T$53, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$T$53, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$53, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$53, DW_AT_decl_line(0x32)
	.dwattr $C$DW$T$53, DW_AT_decl_column(0x21)
$C$DW$T$54	.dwtag  DW_TAG_typedef, DW_AT_name("int_fast64_t")
	.dwattr $C$DW$T$54, DW_AT_type(*$C$DW$T$53)
	.dwattr $C$DW$T$54, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$54, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$54, DW_AT_decl_line(0x4e)
	.dwattr $C$DW$T$54, DW_AT_decl_column(0x17)
$C$DW$T$55	.dwtag  DW_TAG_typedef, DW_AT_name("int_least64_t")
	.dwattr $C$DW$T$55, DW_AT_type(*$C$DW$T$53)
	.dwattr $C$DW$T$55, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$55, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$55, DW_AT_decl_line(0x40)
	.dwattr $C$DW$T$55, DW_AT_decl_column(0x17)
$C$DW$T$56	.dwtag  DW_TAG_typedef, DW_AT_name("intmax_t")
	.dwattr $C$DW$T$56, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$T$56, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$56, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$56, DW_AT_decl_line(0x56)
	.dwattr $C$DW$T$56, DW_AT_decl_column(0x20)
$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x08)
$C$DW$T$57	.dwtag  DW_TAG_typedef, DW_AT_name("uint64_t")
	.dwattr $C$DW$T$57, DW_AT_type(*$C$DW$T$15)
	.dwattr $C$DW$T$57, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$57, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$57, DW_AT_decl_line(0x33)
	.dwattr $C$DW$T$57, DW_AT_decl_column(0x20)
$C$DW$T$58	.dwtag  DW_TAG_typedef, DW_AT_name("uint_fast64_t")
	.dwattr $C$DW$T$58, DW_AT_type(*$C$DW$T$57)
	.dwattr $C$DW$T$58, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$58, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$58, DW_AT_decl_line(0x4f)
	.dwattr $C$DW$T$58, DW_AT_decl_column(0x16)
$C$DW$T$59	.dwtag  DW_TAG_typedef, DW_AT_name("uint_least64_t")
	.dwattr $C$DW$T$59, DW_AT_type(*$C$DW$T$57)
	.dwattr $C$DW$T$59, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$59, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$59, DW_AT_decl_line(0x41)
	.dwattr $C$DW$T$59, DW_AT_decl_column(0x16)
$C$DW$T$60	.dwtag  DW_TAG_typedef, DW_AT_name("uintmax_t")
	.dwattr $C$DW$T$60, DW_AT_type(*$C$DW$T$15)
	.dwattr $C$DW$T$60, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$60, DW_AT_decl_file("C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h")
	.dwattr $C$DW$T$60, DW_AT_decl_line(0x57)
	.dwattr $C$DW$T$60, DW_AT_decl_column(0x20)
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
$C$DW$T$25	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$25, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$25, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$25, DW_AT_byte_size(0x01)

$C$DW$T$26	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$26, DW_AT_name("_task")
	.dwattr $C$DW$T$26, DW_AT_byte_size(0x14)
$C$DW$32	.dwtag  DW_TAG_member
	.dwattr $C$DW$32, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$32, DW_AT_name("stack")
	.dwattr $C$DW$32, DW_AT_TI_symbol_name("stack")
	.dwattr $C$DW$32, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$32, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$32, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$32, DW_AT_decl_line(0x16)
	.dwattr $C$DW$32, DW_AT_decl_column(0x0b)
$C$DW$33	.dwtag  DW_TAG_member
	.dwattr $C$DW$33, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$33, DW_AT_name("function")
	.dwattr $C$DW$33, DW_AT_TI_symbol_name("function")
	.dwattr $C$DW$33, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$33, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$33, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$33, DW_AT_decl_line(0x18)
	.dwattr $C$DW$33, DW_AT_decl_column(0x08)
$C$DW$34	.dwtag  DW_TAG_member
	.dwattr $C$DW$34, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$34, DW_AT_name("state")
	.dwattr $C$DW$34, DW_AT_TI_symbol_name("state")
	.dwattr $C$DW$34, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$34, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$34, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$34, DW_AT_decl_line(0x19)
	.dwattr $C$DW$34, DW_AT_decl_column(0x11)
$C$DW$35	.dwtag  DW_TAG_member
	.dwattr $C$DW$35, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$35, DW_AT_name("uiPriority")
	.dwattr $C$DW$35, DW_AT_TI_symbol_name("uiPriority")
	.dwattr $C$DW$35, DW_AT_data_member_location[DW_OP_plus_uconst 0x9]
	.dwattr $C$DW$35, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$35, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$35, DW_AT_decl_line(0x1a)
	.dwattr $C$DW$35, DW_AT_decl_column(0x0c)
$C$DW$36	.dwtag  DW_TAG_member
	.dwattr $C$DW$36, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$36, DW_AT_name("uiCounter")
	.dwattr $C$DW$36, DW_AT_TI_symbol_name("uiCounter")
	.dwattr $C$DW$36, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr $C$DW$36, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$36, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$36, DW_AT_decl_line(0x1b)
	.dwattr $C$DW$36, DW_AT_decl_column(0x0c)
$C$DW$37	.dwtag  DW_TAG_member
	.dwattr $C$DW$37, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$37, DW_AT_name("bInitialized")
	.dwattr $C$DW$37, DW_AT_TI_symbol_name("bInitialized")
	.dwattr $C$DW$37, DW_AT_data_member_location[DW_OP_plus_uconst 0x10]
	.dwattr $C$DW$37, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$37, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$37, DW_AT_decl_line(0x1d)
	.dwattr $C$DW$37, DW_AT_decl_column(0x09)
	.dwendtag $C$DW$T$26

	.dwattr $C$DW$T$26, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$T$26, DW_AT_decl_line(0x15)
	.dwattr $C$DW$T$26, DW_AT_decl_column(0x10)
$C$DW$T$61	.dwtag  DW_TAG_typedef, DW_AT_name("task")
	.dwattr $C$DW$T$61, DW_AT_type(*$C$DW$T$26)
	.dwattr $C$DW$T$61, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$61, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$T$61, DW_AT_decl_line(0x1e)
	.dwattr $C$DW$T$61, DW_AT_decl_column(0x03)

$C$DW$T$22	.dwtag  DW_TAG_enumeration_type
	.dwattr $C$DW$T$22, DW_AT_name("taskState")
	.dwattr $C$DW$T$22, DW_AT_byte_size(0x01)
$C$DW$38	.dwtag  DW_TAG_enumerator, DW_AT_name("RUNNING"), DW_AT_const_value(0x00)
	.dwattr $C$DW$38, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$38, DW_AT_decl_line(0x12)
	.dwattr $C$DW$38, DW_AT_decl_column(0x10)
$C$DW$39	.dwtag  DW_TAG_enumerator, DW_AT_name("READY"), DW_AT_const_value(0x01)
	.dwattr $C$DW$39, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$39, DW_AT_decl_line(0x12)
	.dwattr $C$DW$39, DW_AT_decl_column(0x19)
$C$DW$40	.dwtag  DW_TAG_enumerator, DW_AT_name("WAITING"), DW_AT_const_value(0x02)
	.dwattr $C$DW$40, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$40, DW_AT_decl_line(0x12)
	.dwattr $C$DW$40, DW_AT_decl_column(0x20)
	.dwendtag $C$DW$T$22

	.dwattr $C$DW$T$22, DW_AT_decl_file("..\src/task.h")
	.dwattr $C$DW$T$22, DW_AT_decl_line(0x12)
	.dwattr $C$DW$T$22, DW_AT_decl_column(0x06)
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

$C$DW$41	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A1")
	.dwattr $C$DW$41, DW_AT_location[DW_OP_reg0]
$C$DW$42	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A2")
	.dwattr $C$DW$42, DW_AT_location[DW_OP_reg1]
$C$DW$43	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A3")
	.dwattr $C$DW$43, DW_AT_location[DW_OP_reg2]
$C$DW$44	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A4")
	.dwattr $C$DW$44, DW_AT_location[DW_OP_reg3]
$C$DW$45	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V1")
	.dwattr $C$DW$45, DW_AT_location[DW_OP_reg4]
$C$DW$46	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V2")
	.dwattr $C$DW$46, DW_AT_location[DW_OP_reg5]
$C$DW$47	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V3")
	.dwattr $C$DW$47, DW_AT_location[DW_OP_reg6]
$C$DW$48	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V4")
	.dwattr $C$DW$48, DW_AT_location[DW_OP_reg7]
$C$DW$49	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V5")
	.dwattr $C$DW$49, DW_AT_location[DW_OP_reg8]
$C$DW$50	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V6")
	.dwattr $C$DW$50, DW_AT_location[DW_OP_reg9]
$C$DW$51	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V7")
	.dwattr $C$DW$51, DW_AT_location[DW_OP_reg10]
$C$DW$52	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V8")
	.dwattr $C$DW$52, DW_AT_location[DW_OP_reg11]
$C$DW$53	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V9")
	.dwattr $C$DW$53, DW_AT_location[DW_OP_reg12]
$C$DW$54	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SP")
	.dwattr $C$DW$54, DW_AT_location[DW_OP_reg13]
$C$DW$55	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("LR")
	.dwattr $C$DW$55, DW_AT_location[DW_OP_reg14]
$C$DW$56	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PC")
	.dwattr $C$DW$56, DW_AT_location[DW_OP_reg15]
$C$DW$57	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SR")
	.dwattr $C$DW$57, DW_AT_location[DW_OP_reg17]
$C$DW$58	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AP")
	.dwattr $C$DW$58, DW_AT_location[DW_OP_reg16]
$C$DW$59	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D0")
	.dwattr $C$DW$59, DW_AT_location[DW_OP_reg20]
$C$DW$60	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D0_hi")
	.dwattr $C$DW$60, DW_AT_location[DW_OP_reg21]
$C$DW$61	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D1")
	.dwattr $C$DW$61, DW_AT_location[DW_OP_reg22]
$C$DW$62	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D1_hi")
	.dwattr $C$DW$62, DW_AT_location[DW_OP_reg23]
$C$DW$63	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D2")
	.dwattr $C$DW$63, DW_AT_location[DW_OP_reg24]
$C$DW$64	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D2_hi")
	.dwattr $C$DW$64, DW_AT_location[DW_OP_reg25]
$C$DW$65	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D3")
	.dwattr $C$DW$65, DW_AT_location[DW_OP_reg26]
$C$DW$66	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D3_hi")
	.dwattr $C$DW$66, DW_AT_location[DW_OP_reg27]
$C$DW$67	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D4")
	.dwattr $C$DW$67, DW_AT_location[DW_OP_reg28]
$C$DW$68	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D4_hi")
	.dwattr $C$DW$68, DW_AT_location[DW_OP_reg29]
$C$DW$69	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D5")
	.dwattr $C$DW$69, DW_AT_location[DW_OP_reg30]
$C$DW$70	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D5_hi")
	.dwattr $C$DW$70, DW_AT_location[DW_OP_reg31]
$C$DW$71	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D6")
	.dwattr $C$DW$71, DW_AT_location[DW_OP_regx 0x20]
$C$DW$72	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D6_hi")
	.dwattr $C$DW$72, DW_AT_location[DW_OP_regx 0x21]
$C$DW$73	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D7")
	.dwattr $C$DW$73, DW_AT_location[DW_OP_regx 0x22]
$C$DW$74	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D7_hi")
	.dwattr $C$DW$74, DW_AT_location[DW_OP_regx 0x23]
$C$DW$75	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D8")
	.dwattr $C$DW$75, DW_AT_location[DW_OP_regx 0x24]
$C$DW$76	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D8_hi")
	.dwattr $C$DW$76, DW_AT_location[DW_OP_regx 0x25]
$C$DW$77	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D9")
	.dwattr $C$DW$77, DW_AT_location[DW_OP_regx 0x26]
$C$DW$78	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D9_hi")
	.dwattr $C$DW$78, DW_AT_location[DW_OP_regx 0x27]
$C$DW$79	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D10")
	.dwattr $C$DW$79, DW_AT_location[DW_OP_regx 0x28]
$C$DW$80	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D10_hi")
	.dwattr $C$DW$80, DW_AT_location[DW_OP_regx 0x29]
$C$DW$81	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D11")
	.dwattr $C$DW$81, DW_AT_location[DW_OP_regx 0x2a]
$C$DW$82	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D11_hi")
	.dwattr $C$DW$82, DW_AT_location[DW_OP_regx 0x2b]
$C$DW$83	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D12")
	.dwattr $C$DW$83, DW_AT_location[DW_OP_regx 0x2c]
$C$DW$84	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D12_hi")
	.dwattr $C$DW$84, DW_AT_location[DW_OP_regx 0x2d]
$C$DW$85	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D13")
	.dwattr $C$DW$85, DW_AT_location[DW_OP_regx 0x2e]
$C$DW$86	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D13_hi")
	.dwattr $C$DW$86, DW_AT_location[DW_OP_regx 0x2f]
$C$DW$87	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D14")
	.dwattr $C$DW$87, DW_AT_location[DW_OP_regx 0x30]
$C$DW$88	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D14_hi")
	.dwattr $C$DW$88, DW_AT_location[DW_OP_regx 0x31]
$C$DW$89	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D15")
	.dwattr $C$DW$89, DW_AT_location[DW_OP_regx 0x32]
$C$DW$90	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D15_hi")
	.dwattr $C$DW$90, DW_AT_location[DW_OP_regx 0x33]
$C$DW$91	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FPEXC")
	.dwattr $C$DW$91, DW_AT_location[DW_OP_reg18]
$C$DW$92	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FPSCR")
	.dwattr $C$DW$92, DW_AT_location[DW_OP_reg19]
$C$DW$93	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CIE_RETA")
	.dwattr $C$DW$93, DW_AT_location[DW_OP_regx 0x54]
	.dwendtag $C$DW$CU

