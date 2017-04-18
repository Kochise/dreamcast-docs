# Nmake macros for building Windows 32-Bit apps

TARGETOS=WIN95
APPVER=4.0

!include <win32.mak>

all: traynot.exe

# Update the resource if necessary

app32.res: app32.rc app32.h resource.h
    $(rc) $(rcflags) $(rcvars) app32.rc

# Update the object file if necessary

app32.obj: app32.c app32.h
    $(cc) $(cflags) $(cvars) $(cdebug) app32.c

# Update the executable file if necessary, and if so, add the resource back in.

traynot.exe: app32.obj app32.res
    $(link) $(linkdebug) $(guiflags) -out:app32.exe app32.obj app32.res $(guilibs) shell32.lib
