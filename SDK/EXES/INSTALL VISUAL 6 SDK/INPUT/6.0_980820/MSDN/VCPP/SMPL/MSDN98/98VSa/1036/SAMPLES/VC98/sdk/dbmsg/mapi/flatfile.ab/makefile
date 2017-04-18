# Makefile to build the MAPI Sample Address Book Provider

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
HOME   = $(MAPISAMP)\flatfile.ab^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

PROJ     = SMPAB32
BASEFILE = $(COMMON)mapibase.txt

# Main target dependencies

all: $(PROJ).dll

# Extra libraries need, not defined in win32.mak

extralibs = mapi32.lib

# Object files we need to build

OBJS = abcont.obj abctbl1.obj abctbl2.obj abctbl3.obj abguid.obj ablogon.obj \
       abp.obj absearch.obj abuser.obj ootid.obj oouser.obj root.obj \
       status.obj tid.obj wrap.obj
COMMON_OBJS =
!IFNDEF NODEBUG
COMMON_OBJS = $(COMMON_OBJS) mapidbg.obj
!ENDIF

# Build the object files

{$(HOME)}.c.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

mapidbg.obj: $(COMMON)\mapidbg.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

# Build the resources

$(PROJ).res: $(HOME)SAMPABP.RC $(HOME)SAMPABP.DLG
  $(rc) /I$(COMMON) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)SAMPABP.RC

# Link it together to make the executable image

$(PROJ).dll: $(OBJS) $(PROJ).res $(COMMON_OBJS)
  $(link) $(linkdebug) $(lflags) -dll -subsystem:windows,$(APPVER) $(OBJS) \
  $(COMMON_OBJS) $(PROJ).res $(guilibsmt) $(extralibs) \
  -def:$(HOME)$(PROJ).def -out:$(PROJ).dll -base:@$(BASEFILE),$(PROJ)
!IFDEF MAPISAMP
  -copy $@ $(MAPISAMP)\bin\$(PLATFORM)
!ENDIF

# Clean up the intermediate files

clean:
  -del *.obj
  -del *.res 
  -del *.dll 
  -del *.lib 
  -del *.exp

