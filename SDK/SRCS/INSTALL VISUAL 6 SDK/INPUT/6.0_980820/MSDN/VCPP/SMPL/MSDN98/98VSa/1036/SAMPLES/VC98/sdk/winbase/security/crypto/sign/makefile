TARGETOS=WINNT
APPVER=4.0

!include <ntwin32.mak>

all: signfile.exe verifile.exe

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

signfile.exe: signfile.obj
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$*.exe $** $(conlibsdll) advapi32.lib

verifile.exe: verifile.obj
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$*.exe $** $(conlibsdll) advapi32.lib
