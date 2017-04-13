# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all: scrnsave.lib

cparrow.obj: cparrow.c
    $(cc) $(cflags) $(cvars) $(cdebug) $(scall) cparrow.c

skeleton.obj: skeleton.c
    $(cc) $(cflags) $(cvars) $(cdebug) $(scall) skeleton.c

scrnsave.lib: skeleton.obj cparrow.obj
    $(implib) -machine:$(CPU) -out:scrnsave.lib skeleton.obj cparrow.obj
