# Nmake macros for building Windows 32-Bit apps

TARGETOS=WIN95
APPVER=4.0

!include <win32.mak>

all: dropext.dll

# Update the object files if necessary

defclsf.obj: defclsf.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) defclsf.c

dropext.obj: dropext.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) dropext.c

# Update the resources if necessary

dropext.res: dropext.rc dropext.h
    $(rc) $(rcvars) -r dropext.rc

# Update the import library

dropext.lib: dropext.obj dropext.def
    $(implib) -machine:$(CPU)     \
    -def:dropext.def	    \
    dropext.obj	 	    \
    -out:dropext.lib

# Update the dynamic link library

dropext.dll: dropext.lib dropext.obj defclsf.obj dropext.def
    $(link) $(linkdebug) $(dlllflags)     \
    -base:0x1C000000  \
    -out:dropext.dll   \
    dropext.exp dropext.obj defclsf.obj $(guilibsdll) shell32.lib uuid.lib
