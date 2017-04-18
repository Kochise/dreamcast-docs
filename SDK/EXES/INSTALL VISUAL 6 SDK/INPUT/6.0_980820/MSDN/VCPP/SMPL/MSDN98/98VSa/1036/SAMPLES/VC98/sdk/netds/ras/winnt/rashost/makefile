
TARGETOS=WINNT
!include <win32.mak>

all: RASHOST.dll

rashost.obj: rashost.cpp rashost.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) rashost.cpp

rashost.res: rashost.rc
    $(rc) $(rcvars) -r -fo rashost.res rashost.rc

rashost.dll: rashost.obj rashost.def rashost.res
    $(link) $(linkdebug) $(dlllflags) \
    -def:rashost.def   \
    -out:rashost.dll    \
    rashost.obj rashost.res $(guilibsdll)
