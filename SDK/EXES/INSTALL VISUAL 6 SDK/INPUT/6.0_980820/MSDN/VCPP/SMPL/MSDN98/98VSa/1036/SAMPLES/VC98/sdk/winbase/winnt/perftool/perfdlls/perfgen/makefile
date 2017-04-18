# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993 - 1995  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

PROJ = PERFGEN

all: $(PROJ).dll

# Define project specific macros
PROJ_OBJS  = perfutil.obj datagen.obj perfgen.obj 
BASE_OBJS  =
EXTRA_LIBS = kernel32.lib advapi32.lib msvcrt.lib
GLOBAL_DEP = datagen.h genctrnm.h perfmsg.h perfutil.h
RC_DEP     = 


# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

# Build rule for resource file
$(PROJ).res: genctrs.rc msg00001.bin $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc

# Build rule for message file
genctrs.h genctrs.rc msg00001.bin: genctrs.mc
    mc -v genctrs.mc

# Build rule for DLL
$(PROJ).DLL: $(PROJ).res $(BASE_OBJS) $(PROJ_OBJS) 
    $(link) $(linkdebug) $(dlllflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(dlllibs) $(EXTRA_LIBS) \
    -out:$(PROJ).dll /DEF:perfgen.def /MACHINE:$(CPU)


# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc *.lst *.err
