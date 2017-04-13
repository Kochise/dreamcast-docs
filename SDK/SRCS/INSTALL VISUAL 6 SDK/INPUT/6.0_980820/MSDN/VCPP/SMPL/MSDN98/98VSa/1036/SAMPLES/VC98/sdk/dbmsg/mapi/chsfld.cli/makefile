# Makefile to build the MAPI sample choose folder dlg

# Copyright 1986-1996 Microsoft Corporation. All Rights Reserved.

#REM Key to CPU specific conditions, CPU == i386 || ALPHA || MIPS || PPC     1) cvtres
# 	cvtres -$(CPU) ...
!IF "$(CPU)" == ""
!IF "$(PROCESSOR_ARCHITECTURE)" == "MIPS" || "$(PROCESSOR_ARCHITECTURE)" == "ALPHA" || "$(PROCESSOR_ARCHITECTURE)" == "PPC"
CPU = $(PROCESSOR_ARCHITECTURE)
!ELSE
CPU = i386
!ENDIF
!ENDIF

!include <win32.mak>

!IFDEF MAPISAMP
HOME   = $(MAPISAMP)\chsfld.cli^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

cflags = $(cflags) -GX
!IFNDEF NODEBUG
cflags = $(cflags) -DDEBUG
!ENDIF

!IFDEF PROFILE
lflags = $(lflags) /PROFILE
!ENDIF

PROJ     = chsfld32

# Main target dependencies

all: $(PROJ).dll

# Extra libraries need, not defined in win32.mak

extralibs = mapi32.lib ole32.lib uuid.lib comctl32.lib

# Object files we need to build

OBJS = chsfld.obj tvnode.obj

COMMON_OBJS = lasterr.obj
!IFNDEF NODEBUG
COMMON_OBJS = $(COMMON_OBJS) mapidbg.obj
!ENDIF

# Build the object files

{$(HOME)}.c.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags)  $(cvarsmt) $**

{$(HOME)}.cpp.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags)  $(cvarsmt) -Utry $**

lasterr.obj: $(COMMON)lasterr.cpp
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

wrap3d.obj: $(COMMON)wrap3d.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

mapidbg.obj: $(COMMON)mapidbg.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

cindex.obj: $(COMMON)cindex.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**


# Build the resources

$(PROJ).res: $(HOME)chsfld.RC 
  $(rc) /I$(COMMON) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)chsfld.RC

# Link it together to make the executable image

$(PROJ).dll: $(OBJS) $(COMMON_OBJS) $(PROJ).res
  $(link) $(linkdebug) $(dlllflags) -subsystem:WINDOWS,$(APPVER) $(OBJS) \
  $(COMMON_OBJS)  $(PROJ).res $(guilibsmt) $(extralibs) -def:$(HOME)$(PROJ).def \
  -out:$(PROJ).dll
!IFDEF MAPISAMP
  -copy $@ $(MAPISAMP)\bin\$(PLATFORM)
!ENDIF

# Clean up the intermediate files

clean:
  -del *.obj
  -del *.res 
  -del *.lib 
  -del *.dll 
  -del *.exp

