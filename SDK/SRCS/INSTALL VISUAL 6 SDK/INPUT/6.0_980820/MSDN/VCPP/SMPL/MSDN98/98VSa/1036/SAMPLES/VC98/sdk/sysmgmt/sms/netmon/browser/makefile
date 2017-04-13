USE_NETMON=1
dll=1

Proj=Browser

DLLFLAGS = -def:$(Proj).Def

ObjList=$(@R).obj $(@R).Res $(@D)\Main.Obj

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Dll

$(ObjDir)\$(Proj).Dll: $(ObjList)
