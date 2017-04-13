# Some nmake macros for Win32 apps development

TARGETOS=WINNT
SEHMAP=TRUE

!include <ntwin32.mak>

# application specific C defines

cf = -DDBG

all: simplex.exe

# Update the object file if necessary

simplex.obj: simplex.c
    $(cc) $(cflags) $(cvars) $(cdebug) $(cf) simplex.c

dlcdebug.obj: dlcdebug.c dlcdebug.h 
    $(cc) $(cflags) $(cvars) $(cdebug) $(cf) dlcdebug.c

# Update the executable file if necessary

simplex.exe: simplex.obj dlcdebug.obj
    $(link) $(linkdebug) $(conflags) -out:simplex.exe simplex.obj dlcdebug.obj $(conlibs) dlcapi.lib
