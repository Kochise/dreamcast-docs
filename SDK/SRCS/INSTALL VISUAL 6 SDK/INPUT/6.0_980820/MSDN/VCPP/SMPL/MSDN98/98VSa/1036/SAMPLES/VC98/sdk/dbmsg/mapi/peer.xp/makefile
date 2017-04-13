# Makefile to build the MAPI Sample Transport Provider

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
HOME   = $(MAPISAMP)\peer.xp^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

PROJ     = SMPXP32
BASEFILE = $(COMMON)mapibase.txt

# Main target dependencies

all: $(PROJ).dll

# Extra libraries needed, not defined in win32.mak

extralibs = mapi32.lib

# Object files we need to build

OBJS =  XPBASE.OBJ XPDIALOG.OBJ XPGUID.OBJ XPLOGGER.OBJ XPOPTION.OBJ \
	XPQUEUE.OBJ XPRCVMSG.OBJ XPSNDMSG.OBJ XPSOF.OBJ XPSTATUS.OBJ
COMMON_OBJS = 
!IFNDEF NODEBUG
COMMON_OBJS = $(COMMON_OBJS) mapidbg.obj
!ENDIF

# Build the object files

{$(HOME)}.c.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

mapidbg.obj: $(COMMON)mapidbg.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

# Build the resources

$(PROJ).res: $(HOME)XPRESRC.RC $(HOME)XPRESRC.DLG
  $(rc) /I$(COMMON) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)XPRESRC.RC

# Link it together to make the executable image

$(PROJ).dll: $(OBJS) $(COMMON_OBJS) $(PROJ).res
  $(link) $(linkdebug) $(lflags) -dll -subsystem:windows,$(APPVER) $(OBJS) \
  $(COMMON_OBJS) $(PROJ).res $(extralibs) $(guilibsmt) \
  -def:$(HOME)$(PROJ).def -out:$(PROJ).dll -base:@$(BASEFILE),$(PROJ)
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

