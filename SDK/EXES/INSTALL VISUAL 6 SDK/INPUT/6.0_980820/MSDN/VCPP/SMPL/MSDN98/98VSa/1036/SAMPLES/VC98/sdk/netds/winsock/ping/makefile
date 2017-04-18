!include <win32.mak>

LIBS = kernel32.lib oldnames.lib libcmt.lib ws2_32.lib

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c

all:ping.exe

ping.exe:ping.obj
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(LIBS)

clean:
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe
