!include <ntwin32.mak>

all: nmpipe.exe

nmpipe.obj: $*.c

.c.obj:
  $(cc) $(cflags) $(cdebug) $(cvarsdll) $*.c

.obj.exe:
  $(link) $(ldebug) $(conlflags) -out:$*.exe $*.obj $(conlibsdll) \
      user32.lib
