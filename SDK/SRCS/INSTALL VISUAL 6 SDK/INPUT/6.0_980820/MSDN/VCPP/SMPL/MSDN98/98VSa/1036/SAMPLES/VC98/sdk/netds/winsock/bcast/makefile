
! include <ntwin32.mak>

# define these if you want a debug version
#PDB = bcast.pdb
#CDEBUG= -Zi -Fd"$(PDB)"
#LDEBUG = -debug:full

LIBS = kernel32.lib user32.lib wsock32.lib oldnames.lib libcmt.lib 

.c.obj:
	cl $(CDEBUG) -W3 -MT  -c $<

all:bcast.exe 

bcast.exe:bcast.obj
	link -nodefaultlib bcast.obj $(LIBS) $(LDEBUG) \
#
# uncomment the line below for a debug build
#	-pdb:$(PDB)  \
	-out:bcast.exe

clean:
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe
