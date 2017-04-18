TARGETOS=WINNT
APPVER=4.0

!include <ntwin32.mak>

all: inituser.exe

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

inituser.exe: inituser.obj
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$*.exe $** $(conlibsdll) advapi32.lib
