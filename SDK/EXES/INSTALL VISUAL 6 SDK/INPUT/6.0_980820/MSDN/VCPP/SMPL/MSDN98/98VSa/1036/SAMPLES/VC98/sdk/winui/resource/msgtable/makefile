!include <ntwin32.mak>

all: msgtest.exe

msgtest.exe: $*.c messages.h messages.dll
  $(cc) $(cflags) $(cdebug) $(cvarsdll) $*.c
  $(link) $(ldebug) $(conlflags) -out:$*.exe $*.obj $(conlibsdll) \
      user32.lib

messages.dll: $*.res
  $(link) $(lflags) -base:0x60000000 -machine:$(CPU) -dll -noentry \
    -out:$*.dll $*.res

messages.h: messages.rc

messages.rc: messages.mc
  mc $*.mc

.rc.rbj:
    $(rc) -r -fo $*.res $*.rc
