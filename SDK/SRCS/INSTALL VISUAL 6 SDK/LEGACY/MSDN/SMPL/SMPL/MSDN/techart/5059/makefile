# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993 - 1996  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

PROJ = PDHTest

all: $(PROJ).exe

# Define project specific macros
PROJ_OBJS  =    PDHFns.obj\
		Window.obj

STD_LIBS   =    User32.lib Kernel32.lib libC.lib

EXTRA_LIBS =    PDH.lib ComCtl32.lib ComDlg32.lib
GLOBAL_DEP =    PDHTEST.h
RESOURCES  =    PDHRes
RC_DEP     =    RESOURCE.h

# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c 

# Build rule for resource file
$(RESOURCES).res: $(RESOURCES).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(RESOURCES).res $(RESOURCES).rc

# Build rule for EXE
$(PROJ).EXE: $(PROJ_OBJS) $(RESOURCES).res
    $(link) $(linkdebug) $(guilflags) \
    $(PROJ_OBJS) $(RESOURCES).res $(STD_LIBS) $(EXTRA_LIBS) \
    -out:$(PROJ).exe


# Rules for cleaning out those old files
clean:
    del *.bak 
    del *.pdb 
    del *.obj 
    del *.res 
    del *.exp 
    del *.map 
    del *.sbr 
    del *.bsc

