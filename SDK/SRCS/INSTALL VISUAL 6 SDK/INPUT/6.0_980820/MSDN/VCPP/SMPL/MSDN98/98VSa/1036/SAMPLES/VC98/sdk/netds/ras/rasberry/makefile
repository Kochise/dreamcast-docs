# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993 - 1997  Microsoft Corporation.  All Rights Reserved.
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <ntwin32.mak>

PROJ = rasberry

all: $(PROJ).exe

# Define project specific macros
PROJ_OBJS  = rasberry.obj statdlg.obj phbkdlg.obj dialdlg.obj authdlg.obj rasutil.obj
BASE_OBJS  = winmain.obj init.obj misc.obj about.obj dispatch.obj
EXTRA_LIBS = version.lib rasapi32.lib
GLOBAL_DEP = win16ext.h globals.h
RC_DEP     = globals.h about.dlg statdlg.dlg phbkdlg.obj dialdlg.dlg authdlg.dlg

# Dependencies
winmain.obj:  winmain.c  $(GLOBAL_DEP)
init.obj:     init.c     $(GLOBAL_DEP)
misc.obj:     misc.c     $(GLOBAL_DEP)
about.obj:    about.c    $(GLOBAL_DEP)
dispatch.obj: dispatch.c $(GLOBAL_DEP)
statdlg.obj:  statdlg.c  $(GLOBAL_DEP)
phbkdlg.obj:  phbkdlg.c  $(GLOBAL_DEP)
dialdlg.obj:  dialdlg.c  $(GLOBAL_DEP)
authdlg.obj:  authdlg.c  $(GLOBAL_DEP)
rasutil.obj:  rasutil.c  $(GLOBAL_DEP)



# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

# Build rule for resource file
$(PROJ).res: $(PROJ).rc $(RC_DEP)
    $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(PROJ).rc

# Build rule for EXE
$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res
    $(link) $(linkdebug) $(guiflags) \
    $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(guilibs) $(EXTRA_LIBS) \
    -out:$(PROJ).exe $(MAPFILE)



# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc
