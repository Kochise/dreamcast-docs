!include <ntwin32.mak>

proj=domtrust

all: $(proj).exe

$(proj).obj: $(proj).c
    $(cc) $(cflags) $(cvars) $(cdebug) -I..\include $(proj).c

$(proj).exe: $(proj).obj
    $(link) $(ldebug) -out:$(proj).exe $(proj).obj advapi32.lib netapi32.lib
