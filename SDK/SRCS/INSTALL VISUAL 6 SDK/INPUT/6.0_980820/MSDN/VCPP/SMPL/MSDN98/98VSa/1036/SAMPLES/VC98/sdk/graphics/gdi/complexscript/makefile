!include <win32.mak>

all: cstext.exe

DEFINES=-DUNICODE

cstext.res: cstext.rc resource.h
    $(rc) $(rcvars) -r -fo cstext.res cstext.rc

cstext.exe: cstext.obj cstext.res
    $(link) $(linkdebug) $(guiflags) -out:cstext.exe cstext.obj cstext.res $(guilibsdll)

.c.obj:
  $(cc) $(cdebug) $(cflags) $(DEFINES) $(cvars) $(scall) $*.c
