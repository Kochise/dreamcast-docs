USE_SNA=1

Proj=CPic

!include <BkOffice.Mak>

All: $(ObjDir)\CPicSend.exe $(ObjDir)\CPicRecv.exe

$(ObjDir)\CPicSend.Obj: CPicSR.c
    $(MkDest)
    $(cc) $(cflags) $(crtflags) $(cdebug) $(cDefines) -DCPICSEND -Fo$@ CPicSR.c

$(ObjDir)\CPicRecv.Obj: CPicSR.c
    $(MkDest)
    $(cc) $(cflags) $(crtflags) $(cdebug) $(cDefines) -Fo$@ CPicSR.c

