;******************************************************************************
;* G3 TMS470 C/C++ Codegen                                          PC v4.9.9 *
;* Date/Time created: Tue Dec 10 10:58:51 2013                                *
;******************************************************************************
	.compiler_opts --abi=eabi --arm_vmrs_si_workaround=on --code_state=16 --disable_dual_state --embedded_constants=on --endian=little --float_support=FPv4SPD16 --hll_source=on --object_format=elf --silicon_version=7M4 --symdebug:dwarf --symdebug:dwarf_version=2 
	.thumb

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../startup_ccs.c")
	.dwattr $C$DW$CU, DW_AT_producer("G3 TMS470 C/C++ Codegen PC v4.9.9 Copyright (c) 1996-2013 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("C:\Developing\workspace\versdOS\Debug")

$C$DW$1	.dwtag  DW_TAG_subprogram, DW_AT_name("SystickISR")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("SystickISR")
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_decl_file("../startup_ccs.c")
	.dwattr $C$DW$1, DW_AT_decl_line(0x34)
	.dwattr $C$DW$1, DW_AT_decl_column(0x0d)

$C$DW$2	.dwtag  DW_TAG_subprogram, DW_AT_name("PendSVISR")
	.dwattr $C$DW$2, DW_AT_TI_symbol_name("PendSVISR")
	.dwattr $C$DW$2, DW_AT_declaration
	.dwattr $C$DW$2, DW_AT_external
	.dwattr $C$DW$2, DW_AT_decl_file("../startup_ccs.c")
	.dwattr $C$DW$2, DW_AT_decl_line(0x35)
	.dwattr $C$DW$2, DW_AT_decl_column(0x0d)
$C$DW$3	.dwtag  DW_TAG_variable, DW_AT_name("__STACK_TOP")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("__STACK_TOP")
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$13)
	.dwattr $C$DW$3, DW_AT_declaration
	.dwattr $C$DW$3, DW_AT_external
	.dwattr $C$DW$3, DW_AT_decl_file("../startup_ccs.c")
	.dwattr $C$DW$3, DW_AT_decl_line(0x31)
	.dwattr $C$DW$3, DW_AT_decl_column(0x16)
	.global	g_pfnVectors
	.sect	".intvecs"
	.align	4
	.elfsym	g_pfnVectors,SYM_SIZE(620)
g_pfnVectors:
	.bits	__STACK_TOP,32		; g_pfnVectors[0] @ 0
	.bits	ResetISR,32		; g_pfnVectors[1] @ 32
	.bits	NmiSR,32		; g_pfnVectors[2] @ 64
	.bits	FaultISR,32		; g_pfnVectors[3] @ 96
	.bits	IntDefaultHandler,32		; g_pfnVectors[4] @ 128
	.bits	IntDefaultHandler,32		; g_pfnVectors[5] @ 160
	.bits	IntDefaultHandler,32		; g_pfnVectors[6] @ 192
	.bits	0,32			; g_pfnVectors[7] @ 224
	.bits	0,32			; g_pfnVectors[8] @ 256
	.bits	0,32			; g_pfnVectors[9] @ 288
	.bits	0,32			; g_pfnVectors[10] @ 320
	.bits	IntDefaultHandler,32		; g_pfnVectors[11] @ 352
	.bits	IntDefaultHandler,32		; g_pfnVectors[12] @ 384
	.bits	0,32			; g_pfnVectors[13] @ 416
	.bits	PendSVISR,32		; g_pfnVectors[14] @ 448
	.bits	SystickISR,32		; g_pfnVectors[15] @ 480
	.bits	IntDefaultHandler,32		; g_pfnVectors[16] @ 512
	.bits	IntDefaultHandler,32		; g_pfnVectors[17] @ 544
	.bits	IntDefaultHandler,32		; g_pfnVectors[18] @ 576
	.bits	IntDefaultHandler,32		; g_pfnVectors[19] @ 608
	.bits	IntDefaultHandler,32		; g_pfnVectors[20] @ 640
	.bits	IntDefaultHandler,32		; g_pfnVectors[21] @ 672
	.bits	IntDefaultHandler,32		; g_pfnVectors[22] @ 704
	.bits	IntDefaultHandler,32		; g_pfnVectors[23] @ 736
	.bits	IntDefaultHandler,32		; g_pfnVectors[24] @ 768
	.bits	IntDefaultHandler,32		; g_pfnVectors[25] @ 800
	.bits	IntDefaultHandler,32		; g_pfnVectors[26] @ 832
	.bits	IntDefaultHandler,32		; g_pfnVectors[27] @ 864
	.bits	IntDefaultHandler,32		; g_pfnVectors[28] @ 896
	.bits	IntDefaultHandler,32		; g_pfnVectors[29] @ 928
	.bits	IntDefaultHandler,32		; g_pfnVectors[30] @ 960
	.bits	IntDefaultHandler,32		; g_pfnVectors[31] @ 992
	.bits	IntDefaultHandler,32		; g_pfnVectors[32] @ 1024
	.bits	IntDefaultHandler,32		; g_pfnVectors[33] @ 1056
	.bits	IntDefaultHandler,32		; g_pfnVectors[34] @ 1088
	.bits	IntDefaultHandler,32		; g_pfnVectors[35] @ 1120
	.bits	IntDefaultHandler,32		; g_pfnVectors[36] @ 1152
	.bits	IntDefaultHandler,32		; g_pfnVectors[37] @ 1184
	.bits	IntDefaultHandler,32		; g_pfnVectors[38] @ 1216
	.bits	IntDefaultHandler,32		; g_pfnVectors[39] @ 1248
	.bits	IntDefaultHandler,32		; g_pfnVectors[40] @ 1280
	.bits	IntDefaultHandler,32		; g_pfnVectors[41] @ 1312
	.bits	IntDefaultHandler,32		; g_pfnVectors[42] @ 1344
	.bits	IntDefaultHandler,32		; g_pfnVectors[43] @ 1376
	.bits	IntDefaultHandler,32		; g_pfnVectors[44] @ 1408
	.bits	IntDefaultHandler,32		; g_pfnVectors[45] @ 1440
	.bits	IntDefaultHandler,32		; g_pfnVectors[46] @ 1472
	.bits	IntDefaultHandler,32		; g_pfnVectors[47] @ 1504
	.bits	IntDefaultHandler,32		; g_pfnVectors[48] @ 1536
	.bits	IntDefaultHandler,32		; g_pfnVectors[49] @ 1568
	.bits	IntDefaultHandler,32		; g_pfnVectors[50] @ 1600
	.bits	IntDefaultHandler,32		; g_pfnVectors[51] @ 1632
	.bits	IntDefaultHandler,32		; g_pfnVectors[52] @ 1664
	.bits	IntDefaultHandler,32		; g_pfnVectors[53] @ 1696
	.bits	IntDefaultHandler,32		; g_pfnVectors[54] @ 1728
	.bits	IntDefaultHandler,32		; g_pfnVectors[55] @ 1760
	.bits	IntDefaultHandler,32		; g_pfnVectors[56] @ 1792
	.bits	IntDefaultHandler,32		; g_pfnVectors[57] @ 1824
	.bits	IntDefaultHandler,32		; g_pfnVectors[58] @ 1856
	.bits	IntDefaultHandler,32		; g_pfnVectors[59] @ 1888
	.bits	IntDefaultHandler,32		; g_pfnVectors[60] @ 1920
	.bits	IntDefaultHandler,32		; g_pfnVectors[61] @ 1952
	.bits	IntDefaultHandler,32		; g_pfnVectors[62] @ 1984
	.bits	IntDefaultHandler,32		; g_pfnVectors[63] @ 2016
	.bits	IntDefaultHandler,32		; g_pfnVectors[64] @ 2048
	.bits	IntDefaultHandler,32		; g_pfnVectors[65] @ 2080
	.bits	IntDefaultHandler,32		; g_pfnVectors[66] @ 2112
	.bits	IntDefaultHandler,32		; g_pfnVectors[67] @ 2144
	.bits	IntDefaultHandler,32		; g_pfnVectors[68] @ 2176
	.bits	IntDefaultHandler,32		; g_pfnVectors[69] @ 2208
	.bits	IntDefaultHandler,32		; g_pfnVectors[70] @ 2240
	.bits	IntDefaultHandler,32		; g_pfnVectors[71] @ 2272
	.bits	IntDefaultHandler,32		; g_pfnVectors[72] @ 2304
	.bits	IntDefaultHandler,32		; g_pfnVectors[73] @ 2336
	.bits	IntDefaultHandler,32		; g_pfnVectors[74] @ 2368
	.bits	IntDefaultHandler,32		; g_pfnVectors[75] @ 2400
	.bits	IntDefaultHandler,32		; g_pfnVectors[76] @ 2432
	.bits	IntDefaultHandler,32		; g_pfnVectors[77] @ 2464
	.bits	IntDefaultHandler,32		; g_pfnVectors[78] @ 2496
	.bits	IntDefaultHandler,32		; g_pfnVectors[79] @ 2528
	.bits	0,32			; g_pfnVectors[80] @ 2560
	.bits	0,32			; g_pfnVectors[81] @ 2592
	.bits	0,32			; g_pfnVectors[82] @ 2624
	.bits	0,32			; g_pfnVectors[83] @ 2656
	.bits	IntDefaultHandler,32		; g_pfnVectors[84] @ 2688
	.bits	IntDefaultHandler,32		; g_pfnVectors[85] @ 2720
	.bits	IntDefaultHandler,32		; g_pfnVectors[86] @ 2752
	.bits	IntDefaultHandler,32		; g_pfnVectors[87] @ 2784
	.bits	0,32			; g_pfnVectors[88] @ 2816
	.bits	0,32			; g_pfnVectors[89] @ 2848
	.bits	0,32			; g_pfnVectors[90] @ 2880
	.bits	0,32			; g_pfnVectors[91] @ 2912
	.bits	0,32			; g_pfnVectors[92] @ 2944
	.bits	0,32			; g_pfnVectors[93] @ 2976
	.bits	0,32			; g_pfnVectors[94] @ 3008
	.bits	0,32			; g_pfnVectors[95] @ 3040
	.bits	0,32			; g_pfnVectors[96] @ 3072
	.bits	0,32			; g_pfnVectors[97] @ 3104
	.bits	0,32			; g_pfnVectors[98] @ 3136
	.bits	0,32			; g_pfnVectors[99] @ 3168
	.bits	0,32			; g_pfnVectors[100] @ 3200
	.bits	0,32			; g_pfnVectors[101] @ 3232
	.bits	0,32			; g_pfnVectors[102] @ 3264
	.bits	0,32			; g_pfnVectors[103] @ 3296
	.bits	0,32			; g_pfnVectors[104] @ 3328
	.bits	0,32			; g_pfnVectors[105] @ 3360
	.bits	0,32			; g_pfnVectors[106] @ 3392
	.bits	0,32			; g_pfnVectors[107] @ 3424
	.bits	IntDefaultHandler,32		; g_pfnVectors[108] @ 3456
	.bits	IntDefaultHandler,32		; g_pfnVectors[109] @ 3488
	.bits	IntDefaultHandler,32		; g_pfnVectors[110] @ 3520
	.bits	IntDefaultHandler,32		; g_pfnVectors[111] @ 3552
	.bits	IntDefaultHandler,32		; g_pfnVectors[112] @ 3584
	.bits	IntDefaultHandler,32		; g_pfnVectors[113] @ 3616
	.bits	IntDefaultHandler,32		; g_pfnVectors[114] @ 3648
	.bits	IntDefaultHandler,32		; g_pfnVectors[115] @ 3680
	.bits	IntDefaultHandler,32		; g_pfnVectors[116] @ 3712
	.bits	IntDefaultHandler,32		; g_pfnVectors[117] @ 3744
	.bits	IntDefaultHandler,32		; g_pfnVectors[118] @ 3776
	.bits	IntDefaultHandler,32		; g_pfnVectors[119] @ 3808
	.bits	IntDefaultHandler,32		; g_pfnVectors[120] @ 3840
	.bits	IntDefaultHandler,32		; g_pfnVectors[121] @ 3872
	.bits	IntDefaultHandler,32		; g_pfnVectors[122] @ 3904
	.bits	IntDefaultHandler,32		; g_pfnVectors[123] @ 3936
	.bits	IntDefaultHandler,32		; g_pfnVectors[124] @ 3968
	.bits	IntDefaultHandler,32		; g_pfnVectors[125] @ 4000
	.bits	IntDefaultHandler,32		; g_pfnVectors[126] @ 4032
	.bits	IntDefaultHandler,32		; g_pfnVectors[127] @ 4064
	.bits	IntDefaultHandler,32		; g_pfnVectors[128] @ 4096
	.bits	IntDefaultHandler,32		; g_pfnVectors[129] @ 4128
	.bits	IntDefaultHandler,32		; g_pfnVectors[130] @ 4160
	.bits	0,32			; g_pfnVectors[131] @ 4192
	.bits	IntDefaultHandler,32		; g_pfnVectors[132] @ 4224
	.bits	IntDefaultHandler,32		; g_pfnVectors[133] @ 4256
	.bits	IntDefaultHandler,32		; g_pfnVectors[134] @ 4288
	.bits	IntDefaultHandler,32		; g_pfnVectors[135] @ 4320
	.bits	IntDefaultHandler,32		; g_pfnVectors[136] @ 4352
	.bits	IntDefaultHandler,32		; g_pfnVectors[137] @ 4384
	.bits	IntDefaultHandler,32		; g_pfnVectors[138] @ 4416
	.bits	IntDefaultHandler,32		; g_pfnVectors[139] @ 4448
	.bits	IntDefaultHandler,32		; g_pfnVectors[140] @ 4480
	.bits	IntDefaultHandler,32		; g_pfnVectors[141] @ 4512
	.bits	IntDefaultHandler,32		; g_pfnVectors[142] @ 4544
	.bits	IntDefaultHandler,32		; g_pfnVectors[143] @ 4576
	.bits	IntDefaultHandler,32		; g_pfnVectors[144] @ 4608
	.bits	IntDefaultHandler,32		; g_pfnVectors[145] @ 4640
	.bits	IntDefaultHandler,32		; g_pfnVectors[146] @ 4672
	.bits	IntDefaultHandler,32		; g_pfnVectors[147] @ 4704
	.bits	IntDefaultHandler,32		; g_pfnVectors[148] @ 4736
	.bits	IntDefaultHandler,32		; g_pfnVectors[149] @ 4768
	.bits	IntDefaultHandler,32		; g_pfnVectors[150] @ 4800
	.bits	IntDefaultHandler,32		; g_pfnVectors[151] @ 4832
	.bits	IntDefaultHandler,32		; g_pfnVectors[152] @ 4864
	.bits	IntDefaultHandler,32		; g_pfnVectors[153] @ 4896
	.bits	IntDefaultHandler,32		; g_pfnVectors[154] @ 4928

$C$DW$4	.dwtag  DW_TAG_variable, DW_AT_name("g_pfnVectors")
	.dwattr $C$DW$4, DW_AT_TI_symbol_name("g_pfnVectors")
	.dwattr $C$DW$4, DW_AT_location[DW_OP_addr g_pfnVectors]
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$4, DW_AT_external
	.dwattr $C$DW$4, DW_AT_decl_file("../startup_ccs.c")
	.dwattr $C$DW$4, DW_AT_decl_line(0x3f)
	.dwattr $C$DW$4, DW_AT_decl_column(0x0f)
;	C:\ti\ccsv5\tools\compiler\arm_4.9.9\bin\acpia470.exe -@C:\\TEMP\\0530412 
	.sect	".text:ResetISR"
	.clink
	.thumbfunc ResetISR
	.thumb
	.global	ResetISR

$C$DW$5	.dwtag  DW_TAG_subprogram, DW_AT_name("ResetISR")
	.dwattr $C$DW$5, DW_AT_low_pc(ResetISR)
	.dwattr $C$DW$5, DW_AT_high_pc(0x00)
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("ResetISR")
	.dwattr $C$DW$5, DW_AT_external
	.dwattr $C$DW$5, DW_AT_TI_begin_file("../startup_ccs.c")
	.dwattr $C$DW$5, DW_AT_TI_begin_line(0xea)
	.dwattr $C$DW$5, DW_AT_TI_begin_column(0x01)
	.dwattr $C$DW$5, DW_AT_decl_file("../startup_ccs.c")
	.dwattr $C$DW$5, DW_AT_decl_line(0xea)
	.dwattr $C$DW$5, DW_AT_decl_column(0x01)
	.dwattr $C$DW$5, DW_AT_TI_max_frame_size(0x00)
	.dwpsn	file "../startup_ccs.c",line 235,column 1,is_stmt,address ResetISR

	.dwfde $C$DW$CIE, ResetISR
;----------------------------------------------------------------------
; 234 | ResetISR(void)                                                         
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: ResetISR                                                   *
;*                                                                           *
;*   Regs Modified     :                                                     *
;*   Regs Used         : LR                                                  *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                   *
;*****************************************************************************
ResetISR:
;* --------------------------------------------------------------------------*
;----------------------------------------------------------------------
; 236 | //                                                                     
; 237 | // Jump to the CCS C initialization routine.  This will enable the     
; 238 | // floating-point unit as well, so that does not need to be done here. 
; 239 | //                                                                     
;----------------------------------------------------------------------
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
	.dwpsn	file "../startup_ccs.c",line 240,column 5,is_stmt
;----------------------------------------------------------------------
; 240 | __asm("    .global _c_int00\n"                                         
; 241 |       "    b.w     _c_int00");                                         
;----------------------------------------------------------------------
    .global _c_int00
    b.w     _c_int00
	.dwpsn	file "../startup_ccs.c",line 242,column 1,is_stmt
$C$DW$6	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$6, DW_AT_low_pc(0x00)
	.dwattr $C$DW$6, DW_AT_TI_return
        BX        LR                    ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$5, DW_AT_TI_end_file("../startup_ccs.c")
	.dwattr $C$DW$5, DW_AT_TI_end_line(0xf2)
	.dwattr $C$DW$5, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$5

	.sect	".text:NmiSR"
	.clink
	.thumbfunc NmiSR
	.thumb

$C$DW$7	.dwtag  DW_TAG_subprogram, DW_AT_name("NmiSR")
	.dwattr $C$DW$7, DW_AT_low_pc(NmiSR)
	.dwattr $C$DW$7, DW_AT_high_pc(0x00)
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("NmiSR")
	.dwattr $C$DW$7, DW_AT_TI_begin_file("../startup_ccs.c")
	.dwattr $C$DW$7, DW_AT_TI_begin_line(0xfc)
	.dwattr $C$DW$7, DW_AT_TI_begin_column(0x01)
	.dwattr $C$DW$7, DW_AT_decl_file("../startup_ccs.c")
	.dwattr $C$DW$7, DW_AT_decl_line(0xfc)
	.dwattr $C$DW$7, DW_AT_decl_column(0x01)
	.dwattr $C$DW$7, DW_AT_TI_max_frame_size(0x00)
	.dwpsn	file "../startup_ccs.c",line 253,column 1,is_stmt,address NmiSR

	.dwfde $C$DW$CIE, NmiSR
;----------------------------------------------------------------------
; 252 | NmiSR(void)                                                            
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: NmiSR                                                      *
;*                                                                           *
;*   Regs Modified     :                                                     *
;*   Regs Used         : LR                                                  *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                   *
;*****************************************************************************
NmiSR:
;* --------------------------------------------------------------------------*
;----------------------------------------------------------------------
; 254 | //                                                                     
; 255 | // Enter an infinite loop.                                             
; 256 | //                                                                     
;----------------------------------------------------------------------
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
	.dwpsn	file "../startup_ccs.c",line 257,column 11,is_stmt
;----------------------------------------------------------------------
; 257 | while(1)                                                               
;----------------------------------------------------------------------
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L1||
;*
;*   Loop source line                : 257
;*   Loop closing brace source line  : 259
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L1||:    
$C$DW$L$NmiSR$2$B:
        B         ||$C$L1||             ; [DPU_3_PIPE] |257| 
        ; BRANCH OCCURS {||$C$L1||}      ; [] |257| 
$C$DW$L$NmiSR$2$E:
;* --------------------------------------------------------------------------*

$C$DW$8	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$8, DW_AT_name("C:\Developing\workspace\versdOS\Debug\startup_ccs.asm:$C$L1:1:1386669531")
	.dwattr $C$DW$8, DW_AT_TI_begin_file("../startup_ccs.c")
	.dwattr $C$DW$8, DW_AT_TI_begin_line(0x101)
	.dwattr $C$DW$8, DW_AT_TI_end_line(0x103)
$C$DW$9	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$9, DW_AT_low_pc($C$DW$L$NmiSR$2$B)
	.dwattr $C$DW$9, DW_AT_high_pc($C$DW$L$NmiSR$2$E)
	.dwendtag $C$DW$8

	.dwattr $C$DW$7, DW_AT_TI_end_file("../startup_ccs.c")
	.dwattr $C$DW$7, DW_AT_TI_end_line(0x104)
	.dwattr $C$DW$7, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$7

	.sect	".text:FaultISR"
	.clink
	.thumbfunc FaultISR
	.thumb

$C$DW$10	.dwtag  DW_TAG_subprogram, DW_AT_name("FaultISR")
	.dwattr $C$DW$10, DW_AT_low_pc(FaultISR)
	.dwattr $C$DW$10, DW_AT_high_pc(0x00)
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("FaultISR")
	.dwattr $C$DW$10, DW_AT_TI_begin_file("../startup_ccs.c")
	.dwattr $C$DW$10, DW_AT_TI_begin_line(0x10e)
	.dwattr $C$DW$10, DW_AT_TI_begin_column(0x01)
	.dwattr $C$DW$10, DW_AT_decl_file("../startup_ccs.c")
	.dwattr $C$DW$10, DW_AT_decl_line(0x10e)
	.dwattr $C$DW$10, DW_AT_decl_column(0x01)
	.dwattr $C$DW$10, DW_AT_TI_max_frame_size(0x00)
	.dwpsn	file "../startup_ccs.c",line 271,column 1,is_stmt,address FaultISR

	.dwfde $C$DW$CIE, FaultISR
;----------------------------------------------------------------------
; 270 | FaultISR(void)                                                         
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: FaultISR                                                   *
;*                                                                           *
;*   Regs Modified     :                                                     *
;*   Regs Used         : LR                                                  *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                   *
;*****************************************************************************
FaultISR:
;* --------------------------------------------------------------------------*
;----------------------------------------------------------------------
; 272 | //                                                                     
; 273 | // Enter an infinite loop.                                             
; 274 | //                                                                     
;----------------------------------------------------------------------
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
	.dwpsn	file "../startup_ccs.c",line 275,column 11,is_stmt
;----------------------------------------------------------------------
; 275 | while(1)                                                               
;----------------------------------------------------------------------
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L2||
;*
;*   Loop source line                : 275
;*   Loop closing brace source line  : 277
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L2||:    
$C$DW$L$FaultISR$2$B:
        B         ||$C$L2||             ; [DPU_3_PIPE] |275| 
        ; BRANCH OCCURS {||$C$L2||}      ; [] |275| 
$C$DW$L$FaultISR$2$E:
;* --------------------------------------------------------------------------*

$C$DW$11	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$11, DW_AT_name("C:\Developing\workspace\versdOS\Debug\startup_ccs.asm:$C$L2:1:1386669531")
	.dwattr $C$DW$11, DW_AT_TI_begin_file("../startup_ccs.c")
	.dwattr $C$DW$11, DW_AT_TI_begin_line(0x113)
	.dwattr $C$DW$11, DW_AT_TI_end_line(0x115)
$C$DW$12	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$12, DW_AT_low_pc($C$DW$L$FaultISR$2$B)
	.dwattr $C$DW$12, DW_AT_high_pc($C$DW$L$FaultISR$2$E)
	.dwendtag $C$DW$11

	.dwattr $C$DW$10, DW_AT_TI_end_file("../startup_ccs.c")
	.dwattr $C$DW$10, DW_AT_TI_end_line(0x116)
	.dwattr $C$DW$10, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$10

	.sect	".text:IntDefaultHandler"
	.clink
	.thumbfunc IntDefaultHandler
	.thumb

$C$DW$13	.dwtag  DW_TAG_subprogram, DW_AT_name("IntDefaultHandler")
	.dwattr $C$DW$13, DW_AT_low_pc(IntDefaultHandler)
	.dwattr $C$DW$13, DW_AT_high_pc(0x00)
	.dwattr $C$DW$13, DW_AT_TI_symbol_name("IntDefaultHandler")
	.dwattr $C$DW$13, DW_AT_TI_begin_file("../startup_ccs.c")
	.dwattr $C$DW$13, DW_AT_TI_begin_line(0x120)
	.dwattr $C$DW$13, DW_AT_TI_begin_column(0x01)
	.dwattr $C$DW$13, DW_AT_decl_file("../startup_ccs.c")
	.dwattr $C$DW$13, DW_AT_decl_line(0x120)
	.dwattr $C$DW$13, DW_AT_decl_column(0x01)
	.dwattr $C$DW$13, DW_AT_TI_max_frame_size(0x00)
	.dwpsn	file "../startup_ccs.c",line 289,column 1,is_stmt,address IntDefaultHandler

	.dwfde $C$DW$CIE, IntDefaultHandler
;----------------------------------------------------------------------
; 288 | IntDefaultHandler(void)                                                
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: IntDefaultHandler                                          *
;*                                                                           *
;*   Regs Modified     :                                                     *
;*   Regs Used         : LR                                                  *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                   *
;*****************************************************************************
IntDefaultHandler:
;* --------------------------------------------------------------------------*
;----------------------------------------------------------------------
; 290 | //                                                                     
; 291 | // Go into an infinite loop.                                           
; 292 | //                                                                     
;----------------------------------------------------------------------
	.dwcfi	cfa_offset, 0
	.dwcfi	save_reg_to_reg, 84, 14
	.dwpsn	file "../startup_ccs.c",line 293,column 11,is_stmt
;----------------------------------------------------------------------
; 293 | while(1)                                                               
;----------------------------------------------------------------------
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L3||
;*
;*   Loop source line                : 293
;*   Loop closing brace source line  : 295
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L3||:    
$C$DW$L$IntDefaultHandler$2$B:
        B         ||$C$L3||             ; [DPU_3_PIPE] |293| 
        ; BRANCH OCCURS {||$C$L3||}      ; [] |293| 
$C$DW$L$IntDefaultHandler$2$E:
;* --------------------------------------------------------------------------*

$C$DW$14	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$14, DW_AT_name("C:\Developing\workspace\versdOS\Debug\startup_ccs.asm:$C$L3:1:1386669531")
	.dwattr $C$DW$14, DW_AT_TI_begin_file("../startup_ccs.c")
	.dwattr $C$DW$14, DW_AT_TI_begin_line(0x125)
	.dwattr $C$DW$14, DW_AT_TI_end_line(0x127)
$C$DW$15	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$15, DW_AT_low_pc($C$DW$L$IntDefaultHandler$2$B)
	.dwattr $C$DW$15, DW_AT_high_pc($C$DW$L$IntDefaultHandler$2$E)
	.dwendtag $C$DW$14

	.dwattr $C$DW$13, DW_AT_TI_end_file("../startup_ccs.c")
	.dwattr $C$DW$13, DW_AT_TI_end_line(0x128)
	.dwattr $C$DW$13, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$13

;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	SystickISR
	.global	PendSVISR
	.global	__STACK_TOP

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "aeabi", Tag_File, 1, Tag_ABI_PCS_wchar_t(2)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_rounding(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_denormal(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_exceptions(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_number_model(1)
	.battr "aeabi", Tag_File, 1, Tag_ABI_enum_size(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_optimization_goals(5)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_optimization_goals(2)
	.battr "TI", Tag_File, 1, Tag_Bitfield_layout(2)

;******************************************************************************
;* TYPE INFORMATION                                                           *
;******************************************************************************
$C$DW$T$3	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$3, DW_AT_address_class(0x20)
$C$DW$T$19	.dwtag  DW_TAG_typedef, DW_AT_name("__builtin_va_list")
	.dwattr $C$DW$T$19, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$T$19, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$19, DW_AT_decl_file("../startup_ccs.c")
	.dwattr $C$DW$T$19, DW_AT_decl_line(0x128)
	.dwattr $C$DW$T$19, DW_AT_decl_column(0x01)

$C$DW$T$20	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$20, DW_AT_language(DW_LANG_C)
$C$DW$T$21	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$21, DW_AT_address_class(0x20)
$C$DW$T$22	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$T$21)

$C$DW$T$23	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$T$23, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$23, DW_AT_byte_size(0x26c)
$C$DW$16	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$16, DW_AT_upper_bound(0x9a)
	.dwendtag $C$DW$T$23

$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)
$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)
$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)
$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x02)
$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x02)
$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x02)
$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x04)
$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x04)
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
$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x08)
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

$C$DW$17	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A1")
	.dwattr $C$DW$17, DW_AT_location[DW_OP_reg0]
$C$DW$18	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A2")
	.dwattr $C$DW$18, DW_AT_location[DW_OP_reg1]
$C$DW$19	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A3")
	.dwattr $C$DW$19, DW_AT_location[DW_OP_reg2]
$C$DW$20	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A4")
	.dwattr $C$DW$20, DW_AT_location[DW_OP_reg3]
$C$DW$21	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V1")
	.dwattr $C$DW$21, DW_AT_location[DW_OP_reg4]
$C$DW$22	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V2")
	.dwattr $C$DW$22, DW_AT_location[DW_OP_reg5]
$C$DW$23	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V3")
	.dwattr $C$DW$23, DW_AT_location[DW_OP_reg6]
$C$DW$24	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V4")
	.dwattr $C$DW$24, DW_AT_location[DW_OP_reg7]
$C$DW$25	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V5")
	.dwattr $C$DW$25, DW_AT_location[DW_OP_reg8]
$C$DW$26	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V6")
	.dwattr $C$DW$26, DW_AT_location[DW_OP_reg9]
$C$DW$27	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V7")
	.dwattr $C$DW$27, DW_AT_location[DW_OP_reg10]
$C$DW$28	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V8")
	.dwattr $C$DW$28, DW_AT_location[DW_OP_reg11]
$C$DW$29	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("V9")
	.dwattr $C$DW$29, DW_AT_location[DW_OP_reg12]
$C$DW$30	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SP")
	.dwattr $C$DW$30, DW_AT_location[DW_OP_reg13]
$C$DW$31	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("LR")
	.dwattr $C$DW$31, DW_AT_location[DW_OP_reg14]
$C$DW$32	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PC")
	.dwattr $C$DW$32, DW_AT_location[DW_OP_reg15]
$C$DW$33	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SR")
	.dwattr $C$DW$33, DW_AT_location[DW_OP_reg17]
$C$DW$34	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AP")
	.dwattr $C$DW$34, DW_AT_location[DW_OP_reg16]
$C$DW$35	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D0")
	.dwattr $C$DW$35, DW_AT_location[DW_OP_reg20]
$C$DW$36	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D0_hi")
	.dwattr $C$DW$36, DW_AT_location[DW_OP_reg21]
$C$DW$37	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D1")
	.dwattr $C$DW$37, DW_AT_location[DW_OP_reg22]
$C$DW$38	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D1_hi")
	.dwattr $C$DW$38, DW_AT_location[DW_OP_reg23]
$C$DW$39	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D2")
	.dwattr $C$DW$39, DW_AT_location[DW_OP_reg24]
$C$DW$40	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D2_hi")
	.dwattr $C$DW$40, DW_AT_location[DW_OP_reg25]
$C$DW$41	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D3")
	.dwattr $C$DW$41, DW_AT_location[DW_OP_reg26]
$C$DW$42	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D3_hi")
	.dwattr $C$DW$42, DW_AT_location[DW_OP_reg27]
$C$DW$43	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D4")
	.dwattr $C$DW$43, DW_AT_location[DW_OP_reg28]
$C$DW$44	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D4_hi")
	.dwattr $C$DW$44, DW_AT_location[DW_OP_reg29]
$C$DW$45	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D5")
	.dwattr $C$DW$45, DW_AT_location[DW_OP_reg30]
$C$DW$46	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D5_hi")
	.dwattr $C$DW$46, DW_AT_location[DW_OP_reg31]
$C$DW$47	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D6")
	.dwattr $C$DW$47, DW_AT_location[DW_OP_regx 0x20]
$C$DW$48	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D6_hi")
	.dwattr $C$DW$48, DW_AT_location[DW_OP_regx 0x21]
$C$DW$49	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D7")
	.dwattr $C$DW$49, DW_AT_location[DW_OP_regx 0x22]
$C$DW$50	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D7_hi")
	.dwattr $C$DW$50, DW_AT_location[DW_OP_regx 0x23]
$C$DW$51	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D8")
	.dwattr $C$DW$51, DW_AT_location[DW_OP_regx 0x24]
$C$DW$52	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D8_hi")
	.dwattr $C$DW$52, DW_AT_location[DW_OP_regx 0x25]
$C$DW$53	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D9")
	.dwattr $C$DW$53, DW_AT_location[DW_OP_regx 0x26]
$C$DW$54	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D9_hi")
	.dwattr $C$DW$54, DW_AT_location[DW_OP_regx 0x27]
$C$DW$55	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D10")
	.dwattr $C$DW$55, DW_AT_location[DW_OP_regx 0x28]
$C$DW$56	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D10_hi")
	.dwattr $C$DW$56, DW_AT_location[DW_OP_regx 0x29]
$C$DW$57	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D11")
	.dwattr $C$DW$57, DW_AT_location[DW_OP_regx 0x2a]
$C$DW$58	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D11_hi")
	.dwattr $C$DW$58, DW_AT_location[DW_OP_regx 0x2b]
$C$DW$59	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D12")
	.dwattr $C$DW$59, DW_AT_location[DW_OP_regx 0x2c]
$C$DW$60	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D12_hi")
	.dwattr $C$DW$60, DW_AT_location[DW_OP_regx 0x2d]
$C$DW$61	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D13")
	.dwattr $C$DW$61, DW_AT_location[DW_OP_regx 0x2e]
$C$DW$62	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D13_hi")
	.dwattr $C$DW$62, DW_AT_location[DW_OP_regx 0x2f]
$C$DW$63	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D14")
	.dwattr $C$DW$63, DW_AT_location[DW_OP_regx 0x30]
$C$DW$64	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D14_hi")
	.dwattr $C$DW$64, DW_AT_location[DW_OP_regx 0x31]
$C$DW$65	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D15")
	.dwattr $C$DW$65, DW_AT_location[DW_OP_regx 0x32]
$C$DW$66	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("D15_hi")
	.dwattr $C$DW$66, DW_AT_location[DW_OP_regx 0x33]
$C$DW$67	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FPEXC")
	.dwattr $C$DW$67, DW_AT_location[DW_OP_reg18]
$C$DW$68	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FPSCR")
	.dwattr $C$DW$68, DW_AT_location[DW_OP_reg19]
$C$DW$69	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CIE_RETA")
	.dwattr $C$DW$69, DW_AT_location[DW_OP_regx 0x54]
	.dwendtag $C$DW$CU

