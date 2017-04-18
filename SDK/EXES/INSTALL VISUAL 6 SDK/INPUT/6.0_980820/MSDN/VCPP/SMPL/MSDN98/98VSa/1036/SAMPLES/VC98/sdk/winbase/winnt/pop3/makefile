
TARGETOS=WINNT
!include <win32.mak>

!IFNDEF NODEBUG
cdebug = $(cdebug) -DDBG
debugobj = debug.obj
!ENDIF

all: pop3srv.exe

pop3evnt.h pop3evnt.rc msg00001.bin: pop3evnt.mc
    mc -v pop3evnt.mc

pop3evnt.res: pop3evnt.rc msg00001.bin pop3evnt.rc
    rc -r -fo pop3evnt.res pop3evnt.rc 

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) -DUNICODE -D_UNICODE -DRPC_NO_WINDOWS_H $*.c

pop3srv.exe: pop3evnt.res \
            pop3srv.obj \
            pop3.obj    \
            popfile.obj \
            service.obj \
            events.obj  \
            $(debugobj) \
            param.obj   \
            threads.obj \
            socket.obj
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$*.exe $** $(conlibsdll) advapi32.lib rpcrt4.lib
