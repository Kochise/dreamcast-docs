# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT
APPVER=4.0

all:sclient.exe sserver.exe

!include <win32.mak>

cflags=$(cflags) -Gz /YX

#
# Simple Client
#

sclient.obj: sclient.cpp
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -Fdsclient.pdb sclient.cpp -DUNICODE=1 -D_UNICODE=1 -DUNICODE=1

sclient.exe: sclient.obj
    $(link) -debug:full -debugtype:cv -pdb:sclient.pdb -out:sclient.exe sclient.obj $(olelibs) msvcrt.lib -subsystem:console

#
# Simple Server
#

sserver.obj: sserver.cpp
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -Fdserver.pdb sserver.cpp -DUNICODE=1 -D_UNICODE=1

sserver.exe: sserver.obj
    $(link) -debug -out:sserver.exe sserver.obj $(olelibs) -subsystem:console

clean:
    del *.exe
    del *.obj
    del *.pdb
    del *.ilk
    del *.pch

