!include <olesampl.mak>

INCLUDE=.;$(INCLUDE)

all: simpcntr.exe

simpcntr.exe:  app.obj        \
            doc.obj         \
            ias.obj         \
            iocs.obj        \
            ioipf.obj       \
            ioips.obj       \
            simpcntr.obj    \
            simpcntr.res    \
            site.obj
  $(link) $(linkdebug) $(guiflags) -machine:$(CPU) -out:$*.exe $** $(olelibs) oledlg.lib

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $*.cpp

simpcntr.res: simpcntr.rc simpcntr.h
    $(rc) -r simpcntr.rc

