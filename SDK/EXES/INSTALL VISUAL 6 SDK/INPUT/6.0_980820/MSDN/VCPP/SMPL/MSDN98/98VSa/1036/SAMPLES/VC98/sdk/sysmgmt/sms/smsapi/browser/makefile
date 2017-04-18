USE_SMS=1
Use_MFC=1
crtmt=1

Proj=Browser

cDefines=-DSTRICT=1 -D_NTWIN -D_LOCAL

ObjList=$(@R).Obj $(@R).Res

LibList=Ctl3D32.Lib

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).Exe: $(ObjList)
