LDFLAGS = -T$(LINKER_SCRIPT) --entry ResetISR --gc-sections $(LIBDIR)
CFLAGS = -mcpu=cortex-m4 -mfloat-abi=softfp -ffunction-sections -fdata-sections -fomit-frame-pointer -std=c11 -Wall -Wextra -Werror -MMD -MP -mthumb $(INC) -DPART_LM4F120H5QR -DTARGET_IS_BLIZZARD_RA1
#-DPART_LM4F120H5QR -c $(INC) -DTARGET_IS_BLIZZARD_RA1 -mfpu=fpv4-sp-d16 -mthumb
ASMFLAGS = -c -mthumb -mcpu=cortex-m4 -mfloat-abi=softfp -ffunction-sections -fdata-sections
OBJCOPYFLAGS = 
