# Makefile to build the Sample Events Extension

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
HOME   = $(MAPISAMP)\events.ext^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

PROJ = EVEXT32

# Main target dependencies

all: $(PROJ).dll

# Extra libraries needed, not defined in win32.mak

extralibs = mapi32.lib uuid.lib

# Object files we need to build

OBJS = evntext.obj prshtdlg.obj

# Build the object files

{$(HOME)}.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsmt) $**

# Build the resources

$(PROJ).res: $(HOME)EVNTEXT.RC
  $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)EVNTEXT.RC

# Link it together to make the executable image

$(PROJ).dll: $(OBJS) $(COMMON_OBJS) $(PROJ).res
  $(link) $(linkdebug) $(lflags) -dll -subsystem:windows,$(APPVER) $(OBJS) \
  $(COMMON_OBJS) $(PROJ).res $(extralibs) $(guilibsmt) \
  -def:$(HOME)evext32.def -out:$(PROJ).dll
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

