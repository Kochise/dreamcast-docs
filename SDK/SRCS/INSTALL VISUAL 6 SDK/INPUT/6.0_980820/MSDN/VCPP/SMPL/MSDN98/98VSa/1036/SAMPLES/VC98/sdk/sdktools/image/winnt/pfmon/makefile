
TARGETOS=WINNT
APPVER=4.0

!include <win32.mak>

all: ..\..\bin\pfmon.exe


OBJS = pfmon.res     \
       debug.obj     \
       error.obj     \
       init.obj      \
       module.obj    \
       pfmon.obj     \
       process.obj

errormsg.h errormsg.rc msg00001.bin: errormsg.mc
  mc -v errormsg.mc

pfmon.res: errormsg.rc msg00001.bin pfmon.rc
  rc -r -fo pfmon.res pfmon.rc

.c.obj:
  $(cc) $(cflags) $(cvars) $(cdebug) -I..\..\include -I. $*.c


..\..\bin\pfmon.exe:  $(OBJS)
  @if not exist ..\..\bin md ..\..\bin > nul
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$@ $** \
    $(conlibs) psapi.lib imagehlp.lib
