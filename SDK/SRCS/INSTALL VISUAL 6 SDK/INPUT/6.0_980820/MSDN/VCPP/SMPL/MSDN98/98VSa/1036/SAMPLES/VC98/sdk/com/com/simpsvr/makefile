!include <olesampl.mak>

all: simpsvr.exe

simpsvr.exe:  app.obj         \
            doc.obj         \
            icf.obj         \
            ido.obj        \
            iec.obj        \
            ioipao.obj        \
            ioipo.obj        \
            ioo.obj        \
            ips.obj        \
            obj.obj         \
            simpsvr.obj     \
            simpsvr.res
  $(link) $(linkdebug) $(guiflags) -machine:$(CPU) -out:$*.exe $** $(olelibs) $(guilibs) ..\lib\olestd.lib oledlg.lib

.cpp.obj:
    $(cc) /D_DEBUG $(cdebug) $(cflags) $(cvars) $*.cpp

simpsvr.res: simpsvr.rc simpsvr.h
    $(rc) -r simpsvr.rc

