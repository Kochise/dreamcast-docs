# Nmake macros for building Windows 32-Bit apps

APPVER=4.0

!include <win32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

objs=rnrclnt.obj

all: rnrclnt.exe

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $*.c

rnrclnt.exe: rnrclnt.obj
   $(link) $(linkdebug) $(conflags) -out:rnrclnt.exe rnrclnt.obj ws2_32.lib mswsock.lib   $(conlibs)

