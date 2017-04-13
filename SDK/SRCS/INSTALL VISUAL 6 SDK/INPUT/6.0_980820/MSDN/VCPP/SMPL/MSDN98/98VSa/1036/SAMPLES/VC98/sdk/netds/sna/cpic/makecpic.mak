!include <ntwin32.MAK>

!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing WCPIC32.LIB
!endif
!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing WINCPIC.H"
!endif
!if "$(SAMPLEROOT)"==""
!error "Set SAMPLEROOT to the root directory of the sample code tree"
!endif

snalibs = $(ISVLIBS)\wcpic32.lib
source  = $(SAMPLEROOT)\cpic
headers  = $(source)\cpicsr.h  \
           $(ISVINCS)\wincpic.h

INCLUDE = $(INCLUDE);$(ISVINCS);$(source);

all: cpicsend.exe cpicrecv.exe

# Update the object files if necessary

cpicsend.obj: cpicsr.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -DCPICSEND -Focpicsend.obj cpicsr.c

cpicrecv.obj: cpicsr.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -DCPICRECV -Focpicrecv.obj cpicsr.c

cpicsend.exe: cpicsend.obj $(snalibs)
    $(link) $(linkdebug) $(guiflags) cpicsend.obj $(snalibs) $(guilibsdll) -out:cpicsend.exe

cpicrecv.exe: cpicrecv.obj $(snalibs)
    $(link) $(linkdebug) $(guiflags) cpicrecv.obj $(snalibs) $(guilibsdll) -out:cpicrecv.exe
