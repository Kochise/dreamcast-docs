# Nmake macros for building Windows 32-Bit apps

TARGETOS=WINNT
APPVER=4.0

all:comperf.exe psperf.dll

!include <win32.mak>

cflags=$(cflags) -Gz -DREGISTER_PROXY_DLL

# --------------------------------------
# COMPERF Sample:

comperf.cpp: psperf.h

comperf.obj: comperf.cpp
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -GX comperf.cpp

psperf_i.obj: psperf_i.c
    $(cc) $(cflags) $(cvarsmt) $(cdebug) psperf_i.c


comperf.exe: comperf.obj  psperf_i.obj
    $(link) -debug -out:comperf.exe comperf.obj psperf_i.obj $(olelibs)


# --------------------------------------
# COMPERF Sample ICOMPerformance Proxy-Stub DLL:

psperf_p.c psperf_i.c dlldata.c psperf.h : psperf.idl
    midl /win32 /ms_ext /c_ext /Oicf psperf.idl

psperf_p.obj: psperf_p.c
    $(cc) $(cflags) $(cvarsmt) $(cdebug) psperf_p.c

dlldata.obj: dlldata.c
    $(cc) $(cflags) $(cvarsmt) $(cdebug) dlldata.c

psperf.dll: psperf_p.obj psperf_i.obj dlldata.obj psperf.def
    $(link) -dll -debug -def:psperf.def -out:psperf.dll psperf_p.obj psperf_i.obj dlldata.obj $(olelibs) rpcrt4.lib

clean:
    del *.exe
    del *.dll
    del *.obj
    del *.pdb
    del *.ilk
    del *.res
    del *.lib
    del *.exp
    del psperf.h
    del psperf_p.c
    del psperf_i.c
    del dlldata.c
