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

PROJ = MTTTY

all: $(PROJ).exe

# Define project specific macros
PROJ_OBJS  =    about.obj error.obj \
		init.obj mttty.obj \
		reader.obj readstat.obj \
		settings.obj status.obj \
		transfer.obj writer.obj
STD_LIBS   =    libcmt.lib kernel32.lib \
		user32.lib gdi32.lib \
		comdlg32.lib
EXTRA_LIBS =    winmm.lib comctl32.lib 
GLOBAL_DEP =    mttty.h ttyinfo.h
RC_DEP     =    resource.h mttty.ico \
		mttty2.ico mttty3.ico \
		mttty4.ico

# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) /MT $(cflags) $(cvars) $*.c 

# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc

# Build rule for EXE
$(PROJ).EXE: $(PROJ_OBJS) $(PROJ).res
    $(link) $(linkdebug) $(guilflags) \
    $(PROJ_OBJS) $(PROJ).res $(STD_LIBS) $(EXTRA_LIBS) \
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

