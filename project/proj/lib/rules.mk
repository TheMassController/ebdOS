SYSLIBDIR := $(TOP)$(notdir $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))/
INCDIRS += $(shell find $(SYSLIBDIR)$(INCDIR) -type d)
LIBS += driver-cm4f uartstdio
LIBDIRS += $(SYSLIBDIR)/hardfp

#External libs, these will become obsolete eventually. Maybe
LIBDIRS += $(ARMGCCGCCLIBSDIR)
LIBDIRS += $(ARMADITIONALLIBSDIR)
LIBS += c #libc, contains basic I/O, Malloc, etc
LIBS += gcc #libgcc contains function routines for things like dividing. It contains things which may need many instructions, but cannot be optimized.
