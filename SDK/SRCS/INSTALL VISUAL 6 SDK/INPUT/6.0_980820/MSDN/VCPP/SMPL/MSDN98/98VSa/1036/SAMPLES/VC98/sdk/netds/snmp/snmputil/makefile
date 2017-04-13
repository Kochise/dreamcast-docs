# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all: snmputil.exe

snmputil.obj: snmputil.c
    $(cc) $(cflags) $(cvars) $(cdebug) snmputil.c

snmputil.exe: snmputil.obj
    $(link) $(linkdebug) $(conflags) -out:snmputil.exe snmputil.obj $(conlibsdll) \
    advapi32.lib snmpapi.lib mgmtapi.lib
