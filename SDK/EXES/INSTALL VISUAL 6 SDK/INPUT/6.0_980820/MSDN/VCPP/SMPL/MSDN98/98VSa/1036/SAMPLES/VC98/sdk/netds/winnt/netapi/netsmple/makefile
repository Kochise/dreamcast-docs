# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT
APPVER=4.0

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all: netsmple.exe

netsmple.obj: netsmple.c
    $(cc) $(cflags) $(cvars) -Zi -Od netsmple.c

netsmple.exe: netsmple.obj
    $(link) $(linkdebug) $(conflags) -out:netsmple.exe netsmple.obj $(conlibs) netapi32.lib
