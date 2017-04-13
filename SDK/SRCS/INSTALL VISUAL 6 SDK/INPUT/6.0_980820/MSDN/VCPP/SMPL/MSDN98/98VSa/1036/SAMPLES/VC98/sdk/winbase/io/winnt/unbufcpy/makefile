# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

ALLEXES = unbufcp1.exe unbufcp2.exe

all: $(ALLEXES)

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

$(ALLEXES): $*.obj
  $(link) $(ldebug) $(conflags) -out:$*.exe $*.obj user32.lib $(conlibs)
