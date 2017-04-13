Use_MFC=1
Use_MSCRT=1
console=1

Proj=Socpp

ObjList=$(@R).obj

!include <BkOffice.Mak>
LFLAGS=OLEAUT32.LIB UUID.LIB $(LFLAGS)

All: $(ObjDir)\$(Proj).exe

$(ObjDir)\$(Proj).exe: $(ObjList)
