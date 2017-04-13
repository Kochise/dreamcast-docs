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
headers  = $(source)\mrcv.h  \
           $(ISVINCS)\winappc.h   \
           $(ISVINCS)\wincsv.h

INCLUDE = $(INCLUDE);$(ISVINCS);$(source);

all: mrcv.exe

# Update the object files if necessary

mrcv.res: mrcv.rc
    $(rc) -DWIN32 -fo temp.res -r mrcv.rc
    cvtres temp.res -o mrcv.res -$(CPU)
    del temp.res

mrcv.obj: mrcv.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -Fomrcv.obj mrcv.c

mrcv.exe: mrcv.obj mrcv.res $(snalibs)
    $(link) -debug:full -debugtype:both $(guiflags) mrcv.res mrcv.obj $(snalibs) $(guilibsdll) -out:mrcv.exe

