!include <ntwin32.MAK>

!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing WAPPC32.LIB and WINCSV32.LIB
!endif
!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing WINAPPC.H and WINCSV.H"
!endif
!if "$(SAMPLEROOT)"==""
!error "Set SAMPLEROOT to the root directory of the sample code tree"
!endif

snalibs = $(ISVLIBS)\wappc32.lib $(ISVLIBS)\wincsv32.lib
source  = $(SAMPLEROOT)\msendrcv
headers  = $(source)\msendrcv.h  \
           $(ISVINCS)\winappc.h   \
           $(ISVINCS)\wincsv.h

INCLUDE = $(INCLUDE);$(ISVINCS);$(source);

all: msendrcv.exe

# Update the object files if necessary

msendrcv.res: msendrcv.rc
    $(rc) -DWIN32 -fo temp.res -r msendrcv.rc
    cvtres temp.res -o msendrcv.res -$(CPU)
    del temp.res

msendrcv.obj: msendrcv.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -Fomsendrcv.obj msendrcv.c

msendrcv.exe: msendrcv.obj msendrcv.res $(snalibs)
    $(link) -debug:full -debugtype:both $(guiflags) msendrcv.res msendrcv.obj $(snalibs) $(guilibsdll) -out:msendrcv.exe

