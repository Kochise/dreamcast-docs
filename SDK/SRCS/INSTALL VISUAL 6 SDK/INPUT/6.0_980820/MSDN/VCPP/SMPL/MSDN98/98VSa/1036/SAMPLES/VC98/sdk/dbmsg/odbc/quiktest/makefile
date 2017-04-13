USE_ODBC=1
Proj = QuikTest
dll=1

cDefines = /DDLL_INVOKED

LibList=gtrtst32.lib

LinkFlags=-Def:$(Proj).Def

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Dll

$(ObjDir)\$(Proj).Dll: $(@R).Obj $(@D)\DllStub.Obj $(@R).Res
