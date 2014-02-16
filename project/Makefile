#defenitions
#Thumb or ARM?

#Directories and files
SRCDIR=src/
ASMDIR=asm/
INCDIR=inc/ 
LIBDIR=lib/
ODIR=obj/
GDBDIR=gdb/

#libraries


#C Files
CFILES=$(wildcard $(SRCDIR)*.c)
_OFILES=$(patsubst %.c,%.c.o,$(CFILES))
OFILES=$(patsubst src/%,$(ODIR)%,$(_OFILES))
#ASM Files
ASMFILES=$(wildcard $(ASMDIR)*.S)
_OASMFILES=$(patsubst %.S,%.S.o,$(ASMFILES))
OFILES+=$(patsubst asm/%,$(ODIR)%,$(_OASMFILES))

INC= -I$(INCDIR)
INC+= -I$(LIBDIR)inc
INC+= -I/usr/arm-none-eabi/include
#LIBPATH=-L $(LIBDIR) -L /usr/arm-none-eabi/lib/thumb -L /usr/lib/gcc/arm-none-eabi/4.8.3/thumb/
LIBPATH=-L $(LIBDIR) -L /usr/arm-none-eabi/lib/armv7e-m/ -L /usr/lib/gcc/arm-none-eabi/4.8.3/armv7e-m/

LIB=-ldriver-cm4f -lc -lg -lgcc
LINKER_SCRIPT = $(LIBDIR)linker_script.ld
TARGET=final.bin
TARGETELF=final.elf
SYS_OBJECTS=$(wildcard $(LIBDIR)sys_obj/*.o)

#compilers, linkers etc
CPP=arm-none-eabi-g++
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy

#compiling and linking options
LDFLAGS=-T$(LINKER_SCRIPT) --entry ResetISR --gc-sections
#CFLAGS=-mthumb -mcpu=cortex-m4 -mfloat-abi=softfp -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -DPART_LM4F120H5QR -c $(INC) -DTARGET_IS_BLIZZARD_RA1
CFLAGS=-mthumb -march=armv7e-m -mfloat-abi=softfp -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -DPART_LM4F120H5QR -c $(INC) -DTARGET_IS_BLIZZARD_RA1
#-mfpu=fpv4-sp-d16
OBJCPYFLAGS=
ASMFLAGS=-c -mthumb -mcpu=cortex-m4 -mfloat-abi=softfp -ffunction-sections -fdata-sections

.PHONY: all clean debug flash

all: CFLAGS += -Os
all: pre-build $(TARGET)

debug: CFLAGS += -DDEBUG -g
debug: LDFLAGS += -g
debug: pre-build $(TARGETELF)

echo: 
	echo $(OFILES)

pre-build: 
	@mkdir -p $(ODIR)
	 
$(ODIR)%.c.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -o $@ $<

$(ODIR)%.S.o: $(ASMDIR)%.S
	$(CC) $(ASMFLAGS) -o $@ $<

$(TARGETELF): $(OFILES) $(SYS_OBJECTS)
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIB) 

$(TARGET): $(TARGETELF)
	$(OBJCOPY) $(OBJCPYFLAGS) -O binary $< $@ 

flash:
	lm4flash $(TARGET)

debugRun: clean debug
	pkill openocd || true
	lm4flash $(TARGETELF)
	openocd --file /usr/local/share/openocd/scripts/board/ek-lm4f120xl.cfg > openocdLog.txt 2>&1 &
	arm-none-eabi-gdb final.elf -x $(GDBDIR)gdb.script
	pkill openocd

clean:
	@rm -rf $(ODIR)
	@rm -f $(TARGETELF)
	@rm -f $(TARGET)
