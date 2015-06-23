LINKRECEIPE = $(LD) $(LDFLAGS) -o $@ $^ $(LIB)
OBJCOPYRECEIPE = $(OBJCOPY) $(OBJCPYFLAGS) -O binary $< $@
CCRECEIPE = $(CC) $(CFLAGS) -c $< -o $@
ASMRECEIPE = $(AS) $(ASMFLAGS) -c $< -o $@
ARRECEIPE = $(AR) $(ARFLAGS) $@ $^
