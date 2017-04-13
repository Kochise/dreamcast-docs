# Makefile to build the Simple MAPI Client

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
HOME   = $(MAPISAMP)\simple.cli^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

PROJ = SMPCLI32

# Main target dependencies

all: $(PROJ).exe

# Extra libraries needed, not defined in win32.mak

!IFDEF NODEBUG
extralibs =
!ELSE
extralibs = mapi32.lib
!ENDIF

# Object files we need to build

OBJS = client.obj bitmap.obj
COMMON_OBJS = pvalloc.obj
!IFNDEF NODEBUG
COMMON_OBJS = $(COMMON_OBJS) mapidbg.obj
!ENDIF

# Build the object files

{$(HOME)}.c.obj:
  $(cc) -I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

pvalloc.obj: $(COMMON)pvalloc.c
  $(cc) -I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

mapidbg.obj: $(COMMON)mapidbg.c
  $(cc) -I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

# Build the resources

$(PROJ).res: $(HOME)client.rc $(HOME)client.ico $(HOME)client2.ico $(HOME)envelope.bmp
  $(rc) /I$(COMMON) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)client.RC

# Link it together to make the executable image

$(PROJ).exe: $(OBJS) $(PROJ).res $(COMMON_OBJS)
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

