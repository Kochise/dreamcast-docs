USE_SNA=1

Proj = appc

linkflags = /nologo /NOD /INCREMENTAL:NO

!include <BkOffice.Mak>

All: $(ObjDir)\sendtp.exe $(ObjDir)\recvtp.exe

# this makefile is slightly weird since the same source file is compiled into
# different objects and .exes.

$(ObjDir)\sendtp.Obj: sendrecv.c
    $(MkDest)
    $(cc) $(cflags) $(crtflags) $(cdebug) $(cDefines)  -DSENDTP -Fo$@ sendrecv.c

$(ObjDir)\sendtp.exe: $(@R).obj
    Link $(linkflags) $(ldebug) $** $(liblist) $(linklibs) $(libcrt) -out:$@

$(ObjDir)\recvtp.Obj: sendrecv.c
    $(MkDest)
    $(cc) $(cflags) $(crtflags) $(cdebug) $(cDefines)  -DRECVTP -Fo$@ sendrecv.c

$(ObjDir)\recvtp.exe: $(@R).obj
    Link $(linkflags) $(ldebug) $** $(liblist) $(linklibs) $(libcrt) -out:$@

