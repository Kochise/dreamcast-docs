!include <win32.mak>

all: admapi.exe admindll.dll

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) -DUNICODE $*.c

admapi.exe: admapi.obj
    $(link) $(ldebug) -out:$*.exe $** $(conlibs) rassapi.lib user32.lib


admindll.dll: admindll.obj
    $(link) $(linkdebug) $(dlllflags) \
      $** -out:admindll.dll -def:admindll.def \
      $(conlibsdll) rassapi.lib user32.lib
