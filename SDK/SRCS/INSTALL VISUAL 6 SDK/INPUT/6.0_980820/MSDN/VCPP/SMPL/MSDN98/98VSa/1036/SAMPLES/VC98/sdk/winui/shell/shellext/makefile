TARGETOS=WIN95
APPVER=4.0

!include <win32.mak>

all: shellext.dll

shellext.dll:   COPYHOOK.OBJ    \
                CTXMENU.obj    \
                ICONHDLR.obj    \
                PROPSHET.obj    \
                SHELLEXT.obj    \
                SHEXINIT.obj    \
                shellext.res 
  $(implib) -machine:$(CPU) -def:shellext.def $** -out:shellext.lib
  $(link) $(linkdebug) $(dlllflags) -base:0x1C000000 -out:$*.dll $** $(olelibsdll) shell32.lib shellext.lib comctl32.lib shellext.exp

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.cpp

shellext.res: shellext.rc
    $(rc) $(rcflags) $(rcvars)  shellext.rc
