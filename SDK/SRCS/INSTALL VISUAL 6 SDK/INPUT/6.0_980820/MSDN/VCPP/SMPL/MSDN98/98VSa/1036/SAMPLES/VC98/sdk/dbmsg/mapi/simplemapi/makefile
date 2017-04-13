# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

cflags=$(cflags) -DDEVL=1

all: MapiApp.exe

# Update the resource if necessary

MapiApp.res: MapiApp.rc MapiApp.h MapiApp.ico
    $(rc) $(rcvars) -r MapiApp.rc

# Update the object files if necessary

MapiApp.obj: MapiApp.c MapiApp.h
    $(cc) $(cdebug) $(cflags) $(cvars) MapiApp.c

Mapinit.obj: Mapinit.c MapiApp.h
    $(cc) $(cdebug) $(cflags) $(cvars) Mapinit.c

# Update the executable file if necessary, and if so, add the resource back in.

MapiApp.exe: MapiApp.obj Mapinit.obj MapiApp.res makefile
    $(link) $(linkdebug)  $(guiflags) -out:MapiApp.exe\
    MapiApp.obj Mapinit.obj MapiApp.res version.lib $(guilibsmt)
