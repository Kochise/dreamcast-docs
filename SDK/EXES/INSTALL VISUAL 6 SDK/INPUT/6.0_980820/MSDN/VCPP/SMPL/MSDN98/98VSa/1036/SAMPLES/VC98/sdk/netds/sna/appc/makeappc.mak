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
source  = $(SAMPLEROOT)\appc
headers  = $(source)\sendrecv.h  \
           $(ISVINCS)\winappc.h   \
           $(ISVINCS)\wincsv.h

INCLUDE = $(INCLUDE);$(ISVINCS);$(source);

all: sendtp.exe recvtp.exe

# Update the object files if necessary

sendtp.obj: sendrecv.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -DSENDTP -Fosendtp.obj sendrecv.c

recvtp.obj: sendrecv.c $(headers)
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -DRECVTP -Forecvtp.obj sendrecv.c

sendtp.exe: sendtp.obj $(snalibs)
    $(link) $(linkdebug) $(guiflags) sendtp.obj $(snalibs) $(guilibsdll) -out:sendtp.exe

recvtp.exe: recvtp.obj $(snalibs)
    $(link) $(linkdebug) $(guiflags) recvtp.obj $(snalibs) $(guilibsdll) -out:recvtp.exe
