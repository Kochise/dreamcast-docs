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

PROJ = appmem

all: $(PROJ).dll

# Define project specific macros
PROJ_OBJS  =perfutil.obj perfmem.obj datamem.obj sharemem.obj 
BASE_OBJS  =perfmem.res
EXTRA_LIBS = kernel32.lib advapi32.lib msvcrt.lib
GLOBAL_DEP = datamem.h perfmsg.h pertutil.h
RC_DEP     = 


# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

# Build rule for resource file
perfmem.res: perfmem.rc memctrs.rc msg00001.bin $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo perfmem.res perfmem.rc

# Build rule for message file
memctrs.h memctrs.rc msg00001.bin: memctrs.mc
    mc -v memctrs.mc

# Build rule for DLL
$(PROJ).DLL: $(BASE_OBJS) $(PROJ_OBJS)
    $(link) $(linkdebug) $(dlllflags) \
    $(BASE_OBJS) $(PROJ_OBJS) /NOLOGO \
    /NODEFAULTLIB /INCREMENTAL:NO /PDB:NONE /RELEASE \
    $(EXTRA_LIBS) \
    -out:..\pub\$(PROJ).dll /DEF:appmem.def /MACHINE:$(CPU)


# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc *.lst *.err
