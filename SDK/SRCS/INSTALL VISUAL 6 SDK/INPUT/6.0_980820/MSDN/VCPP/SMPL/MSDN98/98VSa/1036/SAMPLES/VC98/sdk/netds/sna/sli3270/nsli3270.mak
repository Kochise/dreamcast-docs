!include <ntwin32.MAK>

!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing WINSLI32.LIB and WINCSV32.LIB
!endif
!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing WINSLI.H and WINCSV.H"
!endif

snalibs = $(ISVLIBS)\winsli32.lib $(ISVLIBS)\wincsv32.lib
headers  = $(ISVINCS)\winsli.h   \
           $(ISVINCS)\wincsv.h

INCLUDE = $(INCLUDE);$(ISVINCS);


all: wsli3270.exe

# Update the object files if necessary

sli3270.obj: sli3270.c $(headers)
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -Fosli3270.obj sli3270.c

wsli3270.exe: sli3270.obj $(snalibs)
    $(link) $(linkdebug) $(conlflags) sli3270.obj $(snalibs) $(conlibsmt) -out:wsli3270.exe
