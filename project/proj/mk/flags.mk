LDFLAGS = -T$(LINKER_SCRIPT) --entry ResetISR --gc-sections $(LIBDIR)
CFLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=softfp -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -DPART_LM4F120H5QR -c $(INC) -DTARGET_IS_BLIZZARD_RA1 -mfpu=fpv4-sp-d16 -MMD -MP
ASMFLAGS = -c -mthumb -mcpu=cortex-m4 -mfloat-abi=softfp -ffunction-sections -fdata-sections
OBJCOPYFLAGS = 
