# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: phtest.exe proghelp.dll

# Update the object files if necessary

phtest.obj: phtest.c
    $(cc) $(cflags) $(cvars) $(cdebug) phtest.c

proghelp.obj: proghelp.c
    $(cc) $(cflags) $(cvarsdll) $(cdebug) proghelp.c

# Update the resources if necessary

phtest.res: phtest.rc phtest.h
    $(rc) $(rcvars) -r phtest.rc

phtest.rbj: phtest.res
    cvtres -$(CPU) phtest.res -o phtest.rbj

# Update the import library

proghelp.lib: proghelp.obj proghelp.def
    $(implib) -machine:$(CPU)     \
    -def:proghelp.def	    \
    proghelp.obj	 	    \
    -out:proghelp.lib

# Update the dynamic link library

proghelp.dll: proghelp.obj proghelp.def
    $(link) $(linkdebug) $(dllflags)     \
    -base:0x1C000000  \
    -out:proghelp.dll   \
    proghelp.exp proghelp.obj $(guilibsdll)


# Update the executable file if necessary.
# If so, add the resource back in.

phtest.exe: phtest.obj proghelp.lib phtest.rbj
    $(link) $(linkdebug) $(guiflags) -out:phtest.exe phtest.obj proghelp.lib phtest.rbj $(guilibs)
