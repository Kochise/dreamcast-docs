# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT

!include <win32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all: sockcli.exe socksrv.exe

sockcli.obj: sockcli.c sockcli.h commdef.h
    $(cc) $(cflags) $(cvars) sockcli.c

sockcli.exe: sockcli.obj
    $(link) $(conflags) -out:sockcli.exe sockcli.obj $(conlibs)

socksrv.obj: socksrv.c socksrv.h commdef.h
    $(cc) $(cflags) $(cvars) socksrv.c

socksrv.exe: socksrv.obj
    $(link) $(conflags) -out:socksrv.exe socksrv.obj $(conlibs)
