!include <ntwin32.MAK>

!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing WINRUI.LIB and WINCSV.LIB
!endif
!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing WINRUI.H and WINCSV.H"
!endif

snalibs = $(ISVLIBS)\winrui32.lib $(ISVLIBS)\wincsv32.lib $(ISVLIBS)\fmistr32.lib
headers  = $(ISVINCS)\winrui.h   \
           $(ISVINCS)\wincsv.h

INCLUDE = $(INCLUDE);$(ISVINCS);

all: wrui3270.exe

# Update the object files if necessary

rui3270.obj: rui3270.c $(headers)
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -Forui3270.obj rui3270.c

wrui3270.exe: rui3270.obj $(snalibs)
    $(link) $(linkdebug) $(conlflags) rui3270.obj $(snalibs) $(conlibsmt) -out:wrui3270.exe

