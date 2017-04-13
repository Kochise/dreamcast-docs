# Makefile to build the MAPI Sample Hook Provider

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
HOME   = $(MAPISAMP)\manager.sh^\
COMMON = $(MAPISAMP)\common^\
rcvars = $(rcvars) /I$(HOME)
!ELSE
HOME   = 
COMMON = ..\common^\
!ENDIF

PROJ     = SMH32
BASEFILE = $(COMMON)mapibase.txt

# Main target dependencies

all: $(PROJ).dll

# Extra libraries needed, not defined in win32.mak

extralibs = mapi32.lib ole32.lib winmm.lib uuid.lib comctl32.lib

# Object files we need to build

OBJS = smh.obj smharc.obj smhatp.obj smhcfg.obj smhguid.obj smhinpxp.obj \
	   smhmdb.obj smhole.obj smhoof.obj smhps.obj smhrk.obj smhtb.obj \
	   smhwb.obj smhwiz.obj

COMMON_OBJS = wrap3d.obj cindex.obj
!IFNDEF NODEBUG
COMMON_OBJS = $(COMMON_OBJS) mapidbg.obj
!ENDIF

# Bitmap files we use

BITMAPS = $(HOME)down.bmp $(HOME)downdis.bmp $(HOME)downinv.bmp \
          $(HOME)updis.bmp $(HOME)upinv.bmp $(HOME)up.bmp

# Build the object files

{$(HOME)}.c.obj:
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

mapidbg.obj: $(COMMON)mapidbg.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

wrap3d.obj: $(COMMON)wrap3d.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

cindex.obj: $(COMMON)cindex.c
  $(cc) /I$(COMMON) $(cdebug) $(cflags) $(cvarsmt) $**

# Build the resources

$(PROJ).res: $(HOME)SMH.RC $(HOME)SMHRC.H $(HOME)SMH.DLG $(HOME)SMH.ICO $(BITMAPS)
  $(rc) /I$(COMMON) $(rcflags) $(rcvars) /fo $(PROJ).res $(HOME)SMH.RC

# Link it together to make the executable image

$(PROJ).dll: $(OBJS) $(COMMON_OBJS) $(PROJ).res
  $(link) $(linkdebug) $(lflags) -dll -subsystem:windows,$(APPVER) $(OBJS) \
  $(COMMON_OBJS) $(PROJ).res $(extralibs) $(guilibsmt) \
  -def:$(HOME)smh32.def -out:$(PROJ).dll -base:@$(BASEFILE),$(PROJ)
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
