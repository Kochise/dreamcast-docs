# Makefile to build the MAPI Sample Message Store Provider

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

!IFDEF MAPISAMP
HOME   = $(MAPISAMP)\docfile.ms^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

PROJ     = SMPMS32
BASEFILE = $(COMMON)mapibase.txt

# Main target dependencies

all: $(PROJ).dll

# Extra libraries needed, not defined in win32.mak

extralibs = mapi32.lib ole32.lib

# Object files we need to build

OBJS = msp.obj mspatch.obj mspfld.obj mspgle.obj mspguid.obj mspinit.obj \
       msplogon.obj mspmisc.obj mspms.obj mspmsg.obj mspntfy.obj mspobj.obj \
       msprfs.obj msptbl.obj

COMMON_OBJS = imem.obj wrap3d.obj 
!IFNDEF NODEBUG
COMMON_OBJS = $(COMMON_OBJS) mapidbg.obj
!ENDIF

# Build the general object files

{$(HOME)}.c.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

# Build the specific common object files

imem.obj: $(COMMON)imem.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

wrap3d.obj: $(COMMON)wrap3d.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

mapidbg.obj: $(COMMON)mapidbg.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

# Build the resources

$(PROJ).res: $(HOME)MSP.RC $(HOME)MSP.DLG
  $(rc) /I$(COMMON) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)MSP.RC

# Link it together to make the executable image

$(PROJ).dll: $(OBJS) $(PROJ).res $(COMMON_OBJS)
  $(link) $(linkdebug) $(lflags) -dll -subsystem:windows,$(APPVER) $(OBJS) \
  $(COMMON_OBJS) $(PROJ).res $(extralibs) $(guilibsmt) -def:$(HOME)$(PROJ).def \
  -out:$(PROJ).dll -base:@$(BASEFILE),$(PROJ)
!IFDEF MAPISAMP
  -copy $@ $(MAPISAMP)\bin\$(PLATFORM)
!ENDIF

# Clean up the intermediate files

clean:
  -del *.obj
  -del *.res 
  -del *.dll 
  -del *.exp 
  -del *.lib

