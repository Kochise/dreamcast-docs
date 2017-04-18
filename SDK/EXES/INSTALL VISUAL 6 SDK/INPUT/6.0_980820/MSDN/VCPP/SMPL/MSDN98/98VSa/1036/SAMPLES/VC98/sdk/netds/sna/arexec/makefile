USE_SNA=1
console=1

Proj=arexec

Shared=..\Shared

cDefines=-I$(Shared)

LibList = $(Shared)\$(ObjDir)\Shared.Lib

!include <BkOffice.Mak>

All: $(ObjDir)\arexec.exe $(ObjDir)\arexecd.exe

$(ObjDir)\arexec.exe: $(@R).obj $(LibList)

$(ObjDir)\arexecd.exe: $(@R).obj $(LibList)
    Link $(LFLAGS) $(linkflags) $** $(LinkLibs) $(LogCmd)
