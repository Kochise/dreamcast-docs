!include <ntwin32.mak>

proj=textsid

all: $(proj).exe

$(proj).obj: $(proj).c
    $(cc) $(cflags) $(cvars) $(cdebug) $(proj).c

$(proj).exe: $(proj).obj
    $(link) $(ldebug) -out:$(proj).exe $(proj).obj advapi32.lib user32.lib
