# Makefile to build the Sample Routing Client
# Copyright 1986-1996, Microsoft Corporation. All Rights Reserved.

# Key to CPU specific conditions, CPU == i386 || ALPHA || MIPS || PPC
!IF "$(CPU)" == ""
!IF "$(PROCESSOR_ARCHITECTURE)" == "MIPS" || "$(PROCESSOR_ARCHITECTURE)" == "ALPHA" || "$(PROCESSOR_ARCHITECTURE)" == "PPC"
CPU = $(PROCESSOR_ARCHITECTURE)
!ELSE
CPU = i386
!ENDIF
!ENDIF

!include <win32.mak>

!IFNDEF NODEBUG
cflags = $(cflags) -DDEBUG
!ENDIF

!IFDEF PROFILE
lflags = $(lflags) /PROFILE
!ENDIF

!IFDEF MAPISAMP
HOME   = $(MAPISAMP)\route.cli^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

PROJ = ROUTE32

# Main target dependencies

all: $(PROJ).exe

# Extra libraries needed, not defined in win32.mak

extralibs = mapi32.lib ole32.lib uuid.lib

# Object files we need to build


OBJS = $(OBJS) client.obj route.obj bitmap.obj
COMMON_OBJS = wrap3d.obj cindex.obj
!IFNDEF NODEBUG
COMMON_OBJS = $(COMMON_OBJS) mapidbg.obj
!ENDIF

# Build the object files

{$(HOME)}.c.obj:
  $(cc) -I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

pvalloc.obj: $(COMMON)pvalloc.c
  $(cc) -I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

wrap3d.obj: $(COMMON)wrap3d.c
  $(cc) -I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

mapidbg.obj: $(COMMON)mapidbg.c
  $(cc) -I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

cindex.obj: $(COMMON)cindex.c
  $(cc) -I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

# Build the resources

$(PROJ).res: $(HOME)client.rc $(HOME)client.ico $(HOME)client2.ico $(HOME)envelope.bmp
  $(rc) /I$(COMMON) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)client.RC

# Link it together to make the executable image

$(PROJ).exe: $(OBJS) $(COMMON_OBJS) $(PROJ).res
  $(link) $(linkdebug) $(lflags) -subsystem:windows,$(APPVER) $(OBJS) \
  $(COMMON_OBJS) $(PROJ).res $(guilibsmt) $(extralibs) -out:$(PROJ).exe
!IFDEF MAPISAMP
  -copy $@ $(MAPISAMP)\bin\$(PLATFORM)
!ENDIF

# Clean up the intermediate files

clean:
  -del *.obj 
  -del *.res
  -del *.exe
  -del *.map

