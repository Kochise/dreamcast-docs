USE_SQL=1

Proj = SqltestN

ObjList=$(@R).obj $(@R).Res

!include <BkOffice.Mak>
crtflags = -DWIN32 $(noansi) -D_WIN32

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).Exe: $(ObjList)

$(ObjDir)\$(Proj).Res: $(@B).rc $(@B).Ico
