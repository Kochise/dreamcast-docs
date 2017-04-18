# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT

!include <win32.mak>


PROJNAME = EXIT
OBJFILES = atl.obj certexit.obj exit.obj pch.obj
EXTRA_LIBS = certidl.lib

all: $(PROJNAME).dll


certexit.res: certexit.rc certexit.tlb
    $(rc) $(rcvars) -r -fo $*.res $*.rc


certexit.tlb: certexit.idl
    midl certexit.idl


.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) -I. -DUNICODE $*.cpp


$(PROJNAME).dll: $(OBJFILES) certexit.res
    $(link) $(linkdebug) $(dlllflags) -out:$*.dll $** $(olelibsdll) $(EXTRA_LIBS)


clean:
    del *.obj *.res
