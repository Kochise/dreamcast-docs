!include <win32.mak>

all: eap.dll

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) -DUNICODE $*.c

eap.dll: eap.obj
    $(link) $(linkdebug) $(dlllflags) \
      $** -out:eap.dll -def:eap.def   \
      $(conlibsdll) user32.lib
