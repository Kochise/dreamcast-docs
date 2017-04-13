# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT

!include <ntwin32.mak>

my_libs = advapi32.lib

all: takeown.exe

takeown.obj: takeown.c
    $(cc) $(cflags) $(cvars) $(cdebug) takeown.c

takeown.exe: takeown.obj
    $(link) $(linkdebug) $(conflags) -out:takeown.exe takeown.obj $(conlibs) $(my_libs)
