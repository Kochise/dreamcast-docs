!include <ntwin32.MAK>

!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing WAPPC32.LIB and WCPIC32.LIB"
!endif
!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing WINCPIC.H and WINAPPC.H"
!endif
!if "$(SAMPLEROOT)"==""
!error "Set SAMPLEROOT to the root directory of the sample code tree"
!endif

snalibs = $(ISVLIBS)\wappc32.lib $(ISVLIBS)\wcpic32.lib
shared   = $(SAMPLEROOT)\shared
headers  = $(shared)\cpicerrs.h   \
           $(shared)\cpicdefs.h  \
           $(shared)\cpicport.h  \
           $(shared)\cpicinit.h  \
           $(ISVINCS)\wincpic.h  \
           $(ISVINCS)\winappc.h

INCLUDE = $(INCLUDE);$(ISVINCS);$(shared);

all: mpingd.exe

# Update the object files if necessary

mpingd.obj: mpingd.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) mpingd.c

cpicport.obj: $(shared)\cpicport.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -DEXITTHREAD $(shared)\cpicport.c

cpicerr.obj: $(shared)\cpicerr.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(shared)\cpicerr.c

cpicinit.obj: $(shared)\cpicinit.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(shared)\cpicinit.c

mpingd.exe: mpingd.obj cpicport.obj cpicerr.obj cpicinit.obj $(snalibs)
    $(link) $(linkdebug) $(conflags) mpingd.obj cpicport.obj cpicerr.obj cpicinit.obj $(snalibs) $(conlibsdll) advapi32.lib -out:mpingd.exe
