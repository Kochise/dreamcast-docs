# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: scroll32.exe

# Update the resource if necessary

scroll32.res: scroll32.rc scroll32.h
    $(rc) -r -fo scroll32.tmp scroll32.rc
    $(cvtres) -$(CPU) scroll32.tmp -o scroll32.res
    del scroll32.tmp

# Update the object file if necessary

scroll32.obj: scroll32.c scroll32.h
    $(cc) $(cdebug) $(cflags) $(cvars) scroll32.c

# Update the executable file if necessary, and if so, add the resource back in.

scroll32.exe: scroll32.obj scroll32.res
    $(link) $(linkdebug) $(guiflags) -out:scroll32.exe scroll32.obj scroll32.res $(guilibs)
