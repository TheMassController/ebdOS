LDFLAGS = -T$(LINKER_SCRIPT) -nostdlib --entry ResetISR --gc-sections -u _sbrk -u .isr_vector $(LIBDIR)
CFLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -ffunction-sections -fdata-sections -fomit-frame-pointer -std=c11 -Wall -Wextra -Werror -MMD -MP $(INC) -DPART_LM4F120H5QR -DTARGET_IS_BLIZZARD_RA1 -mtune=cortex-m4
ASMFLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -ffunction-sections -fdata-sections
OBJCOPYFLAGS = 
ARFLAGS = rcs
