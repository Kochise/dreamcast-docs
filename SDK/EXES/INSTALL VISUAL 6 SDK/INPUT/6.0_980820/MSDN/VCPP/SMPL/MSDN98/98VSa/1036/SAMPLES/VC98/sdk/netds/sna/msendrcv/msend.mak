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
headers  = $(source)\msend.h  \
           $(ISVINCS)\winappc.h   \
           $(ISVINCS)\wincsv.h

INCLUDE = $(INCLUDE);$(ISVINCS);$(source);

all: msend.exe

# Update the object files if necessary

msend.res: msend.rc
    $(rc) -DWIN32 -fo temp.res -r msend.rc
    cvtres temp.res -o msend.res -$(CPU)
    del temp.res

msend.obj: msend.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -Fomsend.obj msend.c

msend.exe: msend.obj msend.res $(snalibs)
    $(link) -debug:full -debugtype:both $(guiflags) msend.res msend.obj $(snalibs) $(guilibsdll) -out:msend.exe

