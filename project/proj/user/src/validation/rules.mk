VALIDATIONDIRNAME := $(notdir $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))/
VALIDATIONDIR := $(USERDIR)$(SRCDIR)$(VALIDATIONDIRNAME)
VALIDATIONSRC := $(VALIDATIONDIR)
VALIDATIONCFILES := $(wildcard $(VALIDATIONSRC)*.c)
VALIDATION_OFILES := $(VALIDATIONCFILES:%.c=%.o)

#Debug part
VALIDATIONDEBUGDIR := $(USERDIR)$(DEBUG_OBJECTS_DIR)$(VALIDATIONDIRNAME)
VALIDATIONDOFILES := $(patsubst $(VALIDATIONDIR)%,$(VALIDATIONDEBUGDIR)%,$(VALIDATION_OFILES))
DOFILES += $(VALIDATIONDOFILES)

#Release part
VALIDATIONRELEASEDIR := $(USERDIR)$(RELEASE_OBJECTS_DIR)$(VALIDATIONDIRNAME)
VALIDATIONROFILES := $(patsubst $(VALIDATIONDIR)%,$(VALIDATIONRELEASEDIR)%,$(VALIDATION_OFILES))
OFILES += $(VALIDATIONROFILES)

#Make sure the output paths are created
OBJECTDIRS += $(VALIDATIONDEBUGDIR) $(VALIDATIONRELEASEDIR)

##DEP files
#-include $(VALIDATIONDOFILES:%.o=%.d)
#-include $(VALIDATIONROFILES:%.o=%.d)

#rule
$(VALIDATIONDEBUGDIR)%.o $(VALIDATIONRELEASEDIR)%.o: $(VALIDATIONSRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@
