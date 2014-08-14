USERDIR := $(TOP)$(notdir $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))/
INCDIRS += $(shell find $(USERDIR)$(INCDIR) -type d)
USERSRC := $(USERDIR)$(SRCDIR)
USERCFILES := $(wildcard $(USERSRC)*.c)
USER_OFILES := $(USERCFILES:%.c=%.o)

#Debug part
USERDEBUGDIR := $(USERDIR)$(DEBUG_OBJECTS_DIR)
USERDOFILES := $(patsubst $(USERDIR)$(SRCDIR)%,$(USERDEBUGDIR)%,$(USER_OFILES))
DOFILES += $(USERDOFILES)

#Release part
USERRELEASEDIR := $(USERDIR)$(RELEASE_OBJECTS_DIR)
USERROFILES := $(patsubst $(USERDIR)$(SRCDIR)%,$(USERRELEASEDIR)%,$(USER_OFILES))
OFILES += $(USERROFILES)

#Make sure the output paths are created
OBJECTDIRS += $(USERDEBUGDIR) $(USERRELEASEDIR)

#include subdir
include $(USERDIR)src/validation/rules.mk


$(USERDEBUGDIR)%.o $(USERRELEASEDIR)%.o: $(USERSRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

