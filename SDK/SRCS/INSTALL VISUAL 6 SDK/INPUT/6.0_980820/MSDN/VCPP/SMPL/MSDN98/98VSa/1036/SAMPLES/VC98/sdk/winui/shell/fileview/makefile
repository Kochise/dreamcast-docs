TARGETOS=WIN95
APPVER=4.0

!include <win32.mak>

all: fvtext.dll

fvtext.dll:   CSTATHLP.obj \
                CSTRTABL.obj \
                FILEVIEW.obj \
                FVINIT.obj   \
                FVPROC.obj   \
                FVTEXT.obj   \
                IFILEVW.obj  \
                IPERFILE.obj \
                fvtext.res 
  $(implib) -machine:$(CPU) -def:fvtext.def $** -out:fvtext.lib
  $(link) $(linkdebug) $(dlllflags) -base:0x1C000000 -out:$*.dll $** $(olelibsdll) shell32.lib fvtext.lib comctl32.lib fvtext.exp

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.cpp

fvtext.res: fvtext.rc
    $(rc) $(rcflags) $(rcvars)  fvtext.rc
