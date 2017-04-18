USE_ODS=1
USE_ODBC=1
dll=1

Proj = Xp_ODBC

cDefines = -I .

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Dll

$(ObjDir)\$(Proj).Dll: $(@R).Exp $(@R).Obj

$(ObjDir)\$(Proj).Exp: $(@B).Def $(@R).Obj
