USE_SNA=1

Proj = Install

ObjList=$(@R).obj $(@R).Res

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).exe: $(ObjList)

$(ObjDir)\$(Proj).res: $(@B).rc dialogs.h

$(ObjDir)\$(Proj).obj: $(@B).c $(@B).h dialogs.h
