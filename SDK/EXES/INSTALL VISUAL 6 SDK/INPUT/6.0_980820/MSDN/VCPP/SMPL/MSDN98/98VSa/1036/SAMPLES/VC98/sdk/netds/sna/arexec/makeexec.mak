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
           $(shared)\getopt.h    \
           $(ISVINCS)\wincpic.h  \
           $(ISVINCS)\winappc.h

INCLUDE = $(INCLUDE);$(ISVINCS);$(shared);

all: arexec.exe arexecd.exe

# Update the object files if necessary

arexecd.obj: arexecd.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) arexecd.c

arexec.obj: arexec.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) arexec.c

cpicport.obj: $(shared)\cpicport.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(shared)\cpicport.c

cpicerr.obj: $(shared)\cpicerr.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(shared)\cpicerr.c

getopt.obj: $(shared)\getopt.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(shared)\getopt.c

cpicinit.obj: $(shared)\cpicinit.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) $(shared)\cpicinit.c

arexec.exe: arexec.obj cpicport.obj cpicerr.obj getopt.obj cpicinit.obj $(snalibs)
    $(link) $(linkdebug) $(conflags) arexec.obj cpicport.obj cpicerr.obj getopt.obj cpicinit.obj $(snalibs) $(conlibsdll) -out:arexec.exe

arexecd.exe: arexecd.obj cpicport.obj cpicerr.obj getopt.obj cpicinit.obj $(snalibs)
    $(link) $(linkdebug) $(conflags) arexecd.obj cpicport.obj cpicerr.obj getopt.obj cpicinit.obj $(snalibs) $(conlibsdll) advapi32.lib -out:arexecd.exe
