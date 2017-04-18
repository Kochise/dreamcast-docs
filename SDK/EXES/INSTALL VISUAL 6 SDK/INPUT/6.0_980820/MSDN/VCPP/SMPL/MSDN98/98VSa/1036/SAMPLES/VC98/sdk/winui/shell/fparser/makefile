# Nmake macros for building Windows 32-Bit apps

TARGETOS=WIN95
APPVER=4.0

!include <win32.mak>

all: vs4asc.dll

# Update the object files if necessary

vsd_asc.obj: vsd_asc.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) vsd_asc.c

vs_asc.obj: vs_asc.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) vs_asc.c

# Update the import library

vs_asc.lib: vs_asc.obj vsasc.def
    $(implib) -machine:$(CPU)     \
    -def:vsasc.def	    \
    vs_asc.obj	 	    \
    -out:vs_asc.lib

# Update the dynamic link library

vs4asc.dll: vs_asc.lib vs_asc.obj vsd_asc.obj vsasc.def
    $(link) $(linkdebug) $(dlllflags)     \
    -base:0x1C000000  \
    -out:vs_asc.dll   \
    -ignore:4077      \
    vs_asc.exp vs_asc.obj vsd_asc.obj $(guilibsdll) uuid.lib shell32.lib comctl32.lib


