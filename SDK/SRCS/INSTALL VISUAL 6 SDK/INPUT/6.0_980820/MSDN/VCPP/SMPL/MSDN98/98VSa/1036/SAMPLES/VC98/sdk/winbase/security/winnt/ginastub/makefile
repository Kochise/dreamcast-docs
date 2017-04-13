
TARGETOS=WINNT
!include <win32.mak>

proj=ginastub

all: $(proj).dll

$(proj).obj: $(proj).c
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

$(proj).lib: $(proj).obj $(proj).def
  $(implib) -machine:$(CPU) -def:$(proj).def -out:$(proj).lib

$(proj).dll: $(proj).obj
  $(link) $(linkdebug) $(dlllflags) $(guilibsdll) \
  $** -out:$(proj).dll -def:$(proj).def
