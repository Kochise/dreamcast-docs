# Some nmake macros for building Win32 applications

!include <ntwin32.mak>

all: regmpad.exe

OBJS = multipad.obj mpinit.obj mpfile.obj mpfind.obj mpprint.obj mpopen.obj regdb.obj

regdb.obj: regdb.c regdb.h multipad.h
    $(cc) $(cflags) $(cvars) $(cdebug) $*.c

multipad.obj: multipad.c multipad.h regdb.h
    $(cc) $(cflags) $(cvars) $(cdebug) $*.c

mpinit.obj: mpinit.c multipad.h
    $(cc) $(cflags) $(cvars) $(cdebug) $*.c

mpfind.obj: mpfind.c multipad.h
    $(cc) $(cflags) $(cvars) $(cdebug) $*.c

mpfile.obj: mpfile.c multipad.h
    $(cc) $(cflags) $(cvars) $(cdebug) $*.c

mpprint.obj: mpprint.c multipad.h
    $(cc) $(cflags) $(cvars) $(cdebug) $*.c

mpopen.obj: mpopen.c multipad.h
    $(cc) $(cflags) $(cvars) $(cdebug) $*.c

multipad.res: multipad.rc multipad.h
    $(rc) $(rcvars) -r multipad.rc

regmpad.exe: $(OBJS) multipad.def multipad.res
    $(link) $(guiflags) $(ldebug) -out:regmpad.exe multipad.obj mpinit.obj \
    mpfile.obj mpfind.obj mpprint.obj mpopen.obj regdb.obj \
    multipad.res $(guilibs) advapi32.lib
