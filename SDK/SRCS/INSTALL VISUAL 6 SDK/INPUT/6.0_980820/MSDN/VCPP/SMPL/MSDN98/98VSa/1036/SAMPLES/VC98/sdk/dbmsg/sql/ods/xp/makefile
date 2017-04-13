USE_ODS=1
dll=1

Proj = Xp

Sources=$(Proj).c

cDefines=-DDBNTWIN32

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Dll

$(ObjDir)\$(Proj).Dll: $(@R).Exp $(@R).Obj

$(ObjDir)\$(Proj).Exp: $(@B).Def $(@R).Obj

