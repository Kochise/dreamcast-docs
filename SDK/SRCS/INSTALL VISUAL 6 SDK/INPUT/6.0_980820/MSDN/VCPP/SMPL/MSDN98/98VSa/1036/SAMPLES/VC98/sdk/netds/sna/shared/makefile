USE_SNA=1
console=1

Proj = shared

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Lib

$(ObjDir)\$(Proj).lib: $(ObjDir)\cpicport.obj $(ObjDir)\cpicerr.obj \
                       $(ObjDir)\getopt.obj   $(ObjDir)\cpicinit.obj
    Lib /out:$@ $** $(LogCmd)

