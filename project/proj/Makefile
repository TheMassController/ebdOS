include mk/basedirs.mk
include mk/compilers.mk
include mk/emptyvars.mk
include mk/predefined.mk
include mk/flags.mk
include mk/receipes.mk

TARGET := ebdOS
TARGETBIN := ebdOS_stripped

KERNELAR := kernel.a
COREAR := core.a

INCDIRS += .

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

OBJECTDIRS += $(RELEASE_DIR) $(DEBUG_DIR)

TOP :=./

DIRS := $(shell ls -d */)
DIRS := $(DIRS:=rules.mk)

.PHONY: echo all debug full clean distclean

all: CFLAGS += $(ALLBUILDCFLAGS)
all: LDFLAGS += $(ALLBUILDLDFLAGS)
all: pre-build
all: $(RELEASETARGETBIN)

debug: CFLAGS += $(DEBUGBUILDCFLAGS)
debug: LDFLAGS += $(DEBUGBUILDLDFLAGS)
debug: pre-build
debug: $(DEBUGTARGETBIN)

full: all debug

-include $(DIRS)

INC := $(addprefix -I,$(INCDIRS))
INC += $(addprefix -isystem,$(SYSINCDIRS))
LIBDIR := $(addprefix -L,$(LIBDIRS))
LIB := $(addprefix -l,$(LIBS))

-include $(ALLOFILES:%.o=%.d)

$(COREARDEBUG) : $(COREDOFILES)
	$(ARRECEIPE)

$(KERNELARDEBUG) : $(KERNELDOFILES)
	$(ARRECEIPE)

$(DEBUGTARGET) : $(DOFILES) $(KERNELARDEBUG) $(COREARDEBUG) $(LINKER_SCRIPT)
	$(LD) $(LDFLAGS) -L$(DEBUG_DIR) -o $@ $(DOFILES) $(KERNELARDEBUG) $(COREARDEBUG) $(LIB)

$(DEBUGTARGETBIN) : $(DEBUGTARGET)
	$(OBJCOPYRECEIPE)

$(COREARRELEASE) : $(COREROFILES)
	$(ARRECEIPE)

$(KERNELARRELEASE) : $(KERNELROFILES)
	$(ARRECEIPE)

$(RELEASETARGET) : $(OFILES) $(KERNELARRELEASE) $(COREARRELEASE) $(LINKER_SCRIPT)
	$(LD) $(LDFLAGS) -L$(RELEASE_DIR) -o $@ $(OFILES) $(KERNELARRELEASE) $(COREARRELEASE) $(LIB)

$(RELEASETARGETBIN) : $(RELEASETARGET)
	$(OBJCOPYRECEIPE)


echo:
	@echo "DIRS" $(DIRS)
	@echo "LIBDIR" $(LIBDIR)
	@echo "LIB" $(LIB)
	@echo "ALLOFILES" $(ALLOFILES)
	@echo "COREDOFILES" $(COREDOFILES)
	@echo "DOFILES" $(DOFILES)
	@echo "INC" $(INC)
	@echo "OBJECTDIRS" $(OBJECTDIRS)

pre-build:
	@mkdir -p $(OBJECTDIRS)

clean:
	@rm -f $(ALLOFILES)

distclean:
	@rm -rf $(OBJECTDIRS)
