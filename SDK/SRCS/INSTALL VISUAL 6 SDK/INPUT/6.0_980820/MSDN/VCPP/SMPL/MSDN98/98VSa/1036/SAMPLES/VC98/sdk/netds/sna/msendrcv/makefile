USE_SNA=1

Proj = MSendRcv

!include <BkOffice.Mak>

All: $(ObjDir)\msendrcv.exe $(ObjDir)\mrcv.exe $(ObjDir)\msend.exe

$(ObjDir)\MSendRcv.exe: $(@R).obj $(@R).res

$(ObjDir)\msend.exe: $(@R).obj $(@R).res
    Link $(LFLAGS) $(linkflags) $** $(LinkLibs) $(LogCmd)

$(ObjDir)\mrcv.exe: $(@R).obj $(@R).res
    Link $(LFLAGS) $(linkflags) $** $(LinkLibs) $(LogCmd)
