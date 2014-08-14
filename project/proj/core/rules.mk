COREDIR := $(TOP)$(notdir $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))/
INCDIRS += $(shell find $(COREDIR)$(INCDIR) -type d)
CORESRC := $(COREDIR)$(SRCDIR)
CORECFILES := $(wildcard $(CORESRC)*.c)
CORE_OFILES := $(CORECFILES:%.c=%.o)

#Debug part
COREDEBUGDIR := $(COREDIR)$(DEBUG_OBJECTS_DIR)
COREDOFILES := $(patsubst $(COREDIR)$(SRCDIR)%,$(COREDEBUGDIR)%,$(CORE_OFILES))
DOFILES += $(COREDOFILES)

#Release part
CORERELEASEDIR := $(COREDIR)$(RELEASE_OBJECTS_DIR)
COREROFILES := $(patsubst $(COREDIR)$(SRCDIR)%,$(CORERELEASEDIR)%,$(CORE_OFILES))
OFILES += $(COREROFILES)

#Make sure the output paths are created
OBJECTDIRS += $(COREDEBUGDIR) $(CORERELEASEDIR)

$(COREDEBUGDIR)%.o $(CORERELEASEDIR)%.o: $(CORESRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

