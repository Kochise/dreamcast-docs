USE_SMS=1
console=1
Use_MFC=1
crtmt=1

Proj=Pdf

cDefines=-DSTRICT=1 -D_NTWIN -D_CONSOLE=1

ObjList=$(@R).Obj

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).Exe: $(ObjList)

clean:
    del $(ObjDir)\*.Obj
    del $(ObjDir)\*.Exe
