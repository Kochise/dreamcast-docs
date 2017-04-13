
! include <ntwin32.mak>

# define these if you want a debug version
#PDB = sockspx.pdb
#CDEBUG= -Zi -Fd"$(PDB)"
#LDEBUG = -debug:full

LIBS = kernel32.lib user32.lib wsock32.lib oldnames.lib libcmt.lib 

.c.obj:
	cl $(CDEBUG) -W3 -MT  -c $<

all:sockspx.exe 

sockspx.exe:sockspx.obj
	link -nodefaultlib sockspx.obj $(LIBS) $(LDEBUG) \
#
# uncomment the line below for a debug build
#	-pdb:$(PDB)  \
	-out:sockspx.exe

clean:
	-del *.obj *.pdb *.ilk

cleanall:clean
	-del *.exe
