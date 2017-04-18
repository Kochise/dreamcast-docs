# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: lsasamp.exe

lsasamp.obj: lsasamp.c
    $(cc) $(cflags) $(cvars) -I..\include -Zi -Od lsasamp.c

lsasamp.exe: lsasamp.obj
    $(link) $(linkdebug) $(conflags) -out:lsasamp.exe lsasamp.obj $(conlibs) user32.lib advapi32.lib
