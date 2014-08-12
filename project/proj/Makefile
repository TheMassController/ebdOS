include mk/basedirs.mk
include mk/compilers.mk
include mk/emptyvars.mk
include mk/predefined.mk
include mk/flags.mk

TARGET := jackoOS
TARGETBIN := jackoOS_stripped

DEBUG_OBJECTS_DIR := $(OBJ_DIR)$(DEBUG_DIR)
RELEASE_OBJECTS_DIR := $(OBJ_DIR)$(RELEASE_DIR)
RELEASETARGET := $(RELEASE_DIR)$(TARGET)
DEBUGTARGET := $(DEBUG_DIR)$(TARGET)
RELEASETARGETBIN := $(RELEASE_DIR)$(TARGETBIN)
DEBUGTARGETBIN := $(DEBUG_DIR)$(TARGETBIN)

TOP :=./

DIRS := $(shell ls -d */)
DIRS := $(DIRS:=rules.mk)

-include $(DIRS)

.PHONY: echo all debug

all: echo
#all: CFLAGS += -O3
#all: pre-build
#all: $(RELEASETARGETBIN)

debug: CFLAGS += -DDEBUG -g3
debug: LDFLAGS += -g3
debug: pre-build 
debug: $(DEBUGTARGET)

LINKRECEIPE = $(LD) $(LDFLAGS) -o $@ $^ $(LIB) 
OBJCOPYRECEIPE = $(OBJCOPY) $(OBJCPYFLAGS) -O binary $< $@ 

INC := $(addprefix -I,$(INCDIRS))
LIBDIR := $(addprefix -L,$(LIBDIRS))
LIB := $(addprefix -l,$(LIBS))

$(RELEASETARGET) : $(OFILES)
	$(LINKRECEIPE)

$(RELEASETARGETBIN) : $(RELEASETARGET)
	$(OBJCOPYRECEIPE)
	
$(DEBUGTARGET) : $(DOFILES)
	$(LINKRECEIPE)

$(DEBUGTARGETBIN) : $(DEBUGTARGET)
	$(OBJCOPYRECEIPE)


echo:
	@echo "DIRS" $(DIRS)
	@echo "LIBDIRS" $(LIBDIRS)
	@echo "LIBS" $(LIBS)
	@echo "OFILES" $(OFILES) 

