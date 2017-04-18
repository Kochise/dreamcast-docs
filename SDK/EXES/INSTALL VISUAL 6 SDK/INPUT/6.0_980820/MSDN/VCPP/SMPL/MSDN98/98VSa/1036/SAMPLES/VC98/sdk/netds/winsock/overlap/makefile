
! include <ntwin32.mak>

# define these if you want a debug version
#PDB = overlap.pdb
#CDEBUG= -Zi -Fd"$(PDB)"
#LDEBUG = -debug:full

LIBS = kernel32.lib ws2_32.lib mswsock.lib oldnames.lib libcmt.lib

# The _WIN32_WINNT flag is required in order to use AcceptEx().
.c.obj:
	cl $(CDEBUG) -D_WIN32_WINNT=0x0400 -W3 -MT  -c $<

all:overlap.exe 

overlap.exe:overlap.obj
	link -nodefaultlib overlap.obj $(LIBS) $(LDEBUG) \
#
# uncomment the line below for a debug build
#	-pdb:$(PDB)  \
	-out:overlap.exe

clean:
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe
