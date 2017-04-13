!include <win32.mak>

LIBS = kernel32.lib oldnames.lib libcmt.lib ws2_32.lib

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c

all:simples.exe simplec.exe ioctl.exe

simples.exe:simples.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS)

simplec.exe:simplec.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS) user32.lib

ioctl.exe:ioctl.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS) user32.lib

clean:
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe
