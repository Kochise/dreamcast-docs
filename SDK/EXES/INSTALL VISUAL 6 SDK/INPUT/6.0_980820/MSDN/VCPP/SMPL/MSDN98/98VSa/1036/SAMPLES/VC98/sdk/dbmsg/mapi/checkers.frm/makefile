# Makefile to build the Checkers Sample Form

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
HOME   = $(MAPISAMP)\checkers.frm^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

!IFNDEF NODEBUG
cflags = $(cflags) -DDEBUG
!ENDIF

PROJ = WCHECK

# Main target dependencies

all: $(PROJ).exe

# Extra libraries needed, not defined in win32.mak

extralibs = version.lib uuid.lib

# Object files we need to build

OBJS = wcheck.obj engine.obj form.obj

# Build the object files

{$(HOME)}.cpp.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

engine.obj: $(HOME)engine\lut.cpp $(HOME)engine\debugio.cpp \
			$(HOME)engine\quality.cpp $(HOME)engine\prune.cpp \
			$(HOME)engine\check.cpp $(HOME)engine.cpp $(HOME)check.h
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $(HOME)engine.cpp

# Build the resources

$(PROJ).res: $(HOME)$(PROJ).RC $(HOME)$(PROJ).DLG
  $(rc) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)$(PROJ).RC

# Link it together to make the executable image

$(PROJ).exe: $(OBJS) $(COMMON_OBJS) $(PROJ).res
  $(link) $(linkdebug) $(lflags) -subsystem:windows,$(APPVER) $(OBJS) \
  $(COMMON_OBJS) $(PROJ).res $(extralibs) $(guilibsmt) -out:$(PROJ).exe
!IFDEF MAPISAMP
  -copy $@ $(MAPISAMP)\bin\$(PLATFORM)
!ENDIF

# Clean up the intermediate files

clean:
  -del *.obj
  -del *.res
  -del *.exe

