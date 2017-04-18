
TARGETOS=WINNT
!include <win32.mak>

all: subauth.dll

subauth.obj: subauth.c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) -I..\include $*.c

subauth.lib: subauth.obj subauth.def
  $(implib) -machine:$(CPU) -def:subauth.def -out:subauth.lib

subauth.dll: subauth.obj
  $(link) $(linkdebug) $(dlllflags) $(guilibsdll) \
  $** -out:subauth.dll -def:subauth.def netapi32.lib
