# Makefile to build the MAPI Sample Form
#Copyright (c) 1986-1996, Microsoft Corporation.

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
HOME   = $(MAPISAMP)\simple.frm^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

!IFNDEF NODEBUG
cflags = $(cflags) -DDEBUG
!ENDIF

PROJ     = SMPFRM32

# Main target dependencies

all: $(PROJ).exe

# Extra libraries need, not defined in win32.mak

extralibs = mapi32.lib ole32.lib uuid.lib

# This sample requires the extra lib libcimt.lib when building with VC++ 4.2
# Rather than specifying that explicitly (it is difficult to determine
# compiler version number in a makefile), instead, link with the extra
# library by turning off the /NODEFAULTLIB link switch that is normally
# defined in win32.mak in the the lflags macro.  Below, we define our own
# alternative to $(lflags)

deflflags  = /INCREMENTAL:NO /PDB:NONE /RELEASE /NOLOGO



# Object files we need to build

OBJS = formbase.obj formwnd.obj guid.obj iclassf.obj \
	main.obj viewntfr.obj 

COMMON_OBJS = wrap3d.obj cindex.obj lasterr.obj
!IFNDEF NODEBUG
COMMON_OBJS = $(COMMON_OBJS) mapidbg.obj
!ENDIF

# Build the object files

{$(HOME)}.c.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags)  $(cvarsmt) $**

{$(HOME)}.cpp.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags)  $(cvarsmt) $**

lasterr.obj: $(COMMON)lasterr.cpp
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**
  

wrap3d.obj: $(COMMON)wrap3d.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

mapidbg.obj: $(COMMON)mapidbg.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

cindex.obj: $(COMMON)cindex.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

# Build the resources

$(PROJ).res: $(HOME)SMPFRM.RC
  $(rc) /I$(COMMON) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)SMPFRM.RC

# Link it together to make the executable image

$(PROJ).exe: $(OBJS) $(COMMON_OBJS) $(PROJ).res
  $(link) $(linkdebug) $(deflflags) \
   -subsystem:windows,$(APPVER) $(OBJS) \
  $(COMMON_OBJS) $(PROJ).res $(guilibsmt) $(extralibs) -out:$(PROJ).exe
!IFDEF MAPISAMP
  -copy $@ $(MAPISAMP)\bin\$(PLATFORM)
!ENDIF

# Clean up the intermediate files

clean:
  -del *.obj
  -del *.res 
  -del *.lib 
  -del *.exe 
  -del *.exp
