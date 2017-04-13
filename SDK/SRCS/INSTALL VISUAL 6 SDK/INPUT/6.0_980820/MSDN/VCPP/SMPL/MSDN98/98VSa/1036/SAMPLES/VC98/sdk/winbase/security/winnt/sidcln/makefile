TARGETOS=WINNT

!include <ntwin32.mak>

all: sidclean.exe

sidclean.obj: sidclean.c
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

sidclean.exe: sidclean.obj
  $(link) $(linkdebug) $(conflags) -out:$*.exe $*.obj $(conlibs) advapi32.lib user32.lib
