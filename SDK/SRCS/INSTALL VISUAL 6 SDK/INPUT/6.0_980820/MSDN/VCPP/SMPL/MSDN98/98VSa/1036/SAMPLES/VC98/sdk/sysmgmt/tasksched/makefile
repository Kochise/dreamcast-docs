# Nmake macros for building Windows 32-Bit apps

TARGETOS=BOTH
APPVER=4.0
Proj=sa

all:SA.exe

!include <inetsdk.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!endif

sa.obj: sa.cpp
    $(cc) $(cflags) $(cvars) $(cdebug) sa.cpp

sa.exe: sa.obj
    $(link) $(lflags) $(ldebug) -out:sa.exe sa.obj $(olelibs) 

