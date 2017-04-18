# Nmake macros for building Win32 apps
# Copyright 1995 - 1997 Microsoft Corporation

TARGETOS=WINNT
APPVER=4.0

all:SecClnt.Exe SecSvr.Exe psMyProp.Dll

!include <win32.mak>

cflags=$(cflags) -Gz -DREGISTER_PROXY_DLL
lflag=/NODEFAULTLIB:LIBCMT

# --------------------------------------
# Security Sample Client:

SecClnt.Cpp: MyProp.h

SecClnt.Obj: SecClnt.Cpp
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -FdSecClnt.Pdb SecClnt.Cpp

SecClnt.Rc: SecClnt.h

SecClnt.Res: SecClnt.Rc
    $(rc) $(rcvars) $(rflags) SecClnt.Rc

SecClnt.Exe: SecClnt.Obj SecClnt.Res
    $(link) -debug $(lflag) -pdb:SecClnt.Pdb -out:SecClnt.Exe SecClnt.Obj SecClnt.Res $(olelibs)


# --------------------------------------
# Security Sample Server (LocalServer, LocalService, and UI):

SecSvr.Cpp: MyProp.h

SecSvr.Obj: SecSvr.Cpp
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -FdSecSvr.Pdb SecSvr.Cpp

SecSvr.Rc: SecSvr.h

SecSvr.Res: SecSvr.Rc
    $(rc) $(rcvars) $(rflags) SecSvr.Rc

SecSvr.Exe: SecSvr.Obj SecSvr.Res
    $(link) -debug $(lflag) -pdb:SecSvr.Pdb -out:SecSvr.Exe SecSvr.Obj SecSvr.Res $(olelibs)


# --------------------------------------
# Security Sample IMyProperties Proxy-Stub DLL:

MyProp_p.c MyProp_i.c DllData.c MyProp.h : MyProp.Idl
    midl MyProp.Idl -h MyProp.h -iid MyProp_I.c -proxy MyProp_P.c

MyProp_p.Obj: MyProp_p.c
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -FdpsMyProp.Pdb MyProp_p.c

MyProp_i.Obj: MyProp_i.c
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -FdpsMyProp.Pdb MyProp_i.c

DllData.Obj: DllData.c
    $(cc) $(cflags) $(cvarsmt) $(cdebug) -FdpsMyProp.Pdb DllData.c

psMyProp.Dll: MyProp_p.Obj MyProp_i.Obj DllData.Obj psMyProp.def
    $(link) -dll $(lflag) -debug -pdb:psMyProp.Pdb -def:psMyProp.def -out:psMyProp.Dll MyProp_p.Obj MyProp_i.Obj DllData.Obj $(olelibs) rpcrt4.Lib

clean:
    del *.Exe
    del *.Dll
    del *.Obj
    del *.Pdb
    del *.ilk
    del *.Res
    del *.Lib
    del *.Exp
