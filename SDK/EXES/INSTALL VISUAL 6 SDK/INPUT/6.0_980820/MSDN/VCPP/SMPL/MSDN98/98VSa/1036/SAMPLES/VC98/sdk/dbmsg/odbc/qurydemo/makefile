USE_ODBC=1
Proj = QuryDemo

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).Exe: $(@D)\Query.Exe
 Copy $? $@

$(ObjDir)\Query.Exe: $(@R).Obj  $(@D)\$(Proj).Res $(@D)\Main.Obj
