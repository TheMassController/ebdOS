include mk/basedirs.mk
include mk/compilers.mk
include mk/emptyvars.mk
include mk/predefined.mk
include mk/flags.mk

TARGET := jackoOS
TARGETBIN := jackoOS_stripped

KERNELAR := kernel.a
COREAR := core.a
USERAR := user.a

DEBUG_OBJECTS_DIR := $(OBJ_DIR)$(DEBUG_DIR)
RELEASE_OBJECTS_DIR := $(OBJ_DIR)$(RELEASE_DIR)
RELEASETARGET := $(RELEASE_DIR)$(TARGET)
DEBUGTARGET := $(DEBUG_DIR)$(TARGET)
RELEASETARGETBIN := $(RELEASE_DIR)$(TARGETBIN)
DEBUGTARGETBIN := $(DEBUG_DIR)$(TARGETBIN)

KERNELARDEBUG := $(DEBUG_DIR)$(KERNELAR)
KERNELARRELEASE := $(RELEASE_DIR)$(KERNELAR)
COREARDEBUG := $(DEBUG_DIR)$(COREAR)
COREARRELEASE := $(RELEASE_DIR)$(COREAR)
USERARDEBUG := $(DEBUG_DIR)$(USERAR)
USERARRELEASE := $(RELEASE_DIR)$(USERAR)

LINKRECEIPE = $(LD) $(LDFLAGS) -o $@ $^ $(LIB) 
OBJCOPYRECEIPE = $(OBJCOPY) $(OBJCPYFLAGS) -O binary $< $@ 
CCRECEIPE = $(CC) $(CFLAGS) -c $< -o $@
ASMRECEIPE = $(CC) $(ASMFLAGS) -c $< -o $@
ARRECEIPE = $(AR) $(ARFLAGS) $< $@

OBJECTDIRS += $(RELEASE_DIR) $(DEBUG_DIR)

TOP :=./

DIRS := $(shell ls -d */)
DIRS := $(DIRS:=rules.mk)


.PHONY: echo all debug

#all: echo
all: CFLAGS += -Os
all: pre-build
all: $(RELEASETARGETBIN)

debug: CFLAGS += -DDEBUG -g
debug: LDFLAGS += -g
debug: ASMFLAGS +=
debug: pre-build 
debug: $(DEBUGTARGET)

-include $(DIRS)

INC := $(addprefix -I,$(INCDIRS))
LIBDIR := $(addprefix -L,$(LIBDIRS))
LIB := $(addprefix -l,$(LIBS))

-include $(OFILES:%.o=%.d)
-include $(DOFILES:%.o=%.d)

$(RELEASETARGET) : $(OFILES) $(KERNELARRELEASE) $(LINKER_SCRIPT)
	$(LD) $(LDFLAGS) -o $@ $(OFILES) $(KERNELARRELEASE) $(LIB)

$(RELEASETARGETBIN) : $(RELEASETARGET)
	$(OBJCOPYRECEIPE)
	
$(DEBUGTARGET) : $(DOFILES) $(KERNELARDEBUG) $(LINKER_SCRIPT)
	$(LD) $(LDFLAGS) -L$(DEBUG_DIR) -o $@ $(DOFILES) $(KERNELARDEBUG) $(LIB) 

$(DEBUGTARGETBIN) : $(DEBUGTARGET)
	$(OBJCOPYRECEIPE)

echo:
	@echo "DIRS" $(DIRS)
	@echo "LIBDIR" $(LIBDIR)
	@echo "LIB" $(LIB)
	@echo "OFILES" $(OFILES) 
	@echo "DOFILES" $(DOFILES)
	@echo "INC" $(INC)
	@echo "OBJECTDIRS" $(OBJECTDIRS)

pre-build:
	@mkdir -p $(OBJECTDIRS)

clean: 
	@rm -f $(OFILES) $(DOFILES) $(RELEASETARGET) $(RELEASETARGETBIN) $(DEBUGTARGET) $(DEBUGTARGETBIN)

distclean: 
	@rm -rf $(OBJECTDIRS)
