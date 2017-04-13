TARGETOS=WINNT
APPVER=4.0

!include <ntwin32.mak>

all: encrypt.exe decrypt.exe

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

encrypt.exe: encrypt.obj
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$*.exe $** $(conlibsdll) advapi32.lib

decrypt.exe: decrypt.obj
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$*.exe $** $(conlibsdll) advapi32.lib
