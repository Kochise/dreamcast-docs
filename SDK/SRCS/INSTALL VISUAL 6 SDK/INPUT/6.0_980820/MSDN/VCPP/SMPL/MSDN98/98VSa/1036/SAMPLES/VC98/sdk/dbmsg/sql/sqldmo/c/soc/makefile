console=1

Proj=Soc

ObjList=$(@R).obj

!include <BkOffice.Mak>
LFLAGS=OLEAUT32.LIB $(LFLAGS)

All: $(ObjDir)\$(Proj).exe

$(ObjDir)\$(Proj).exe: $(ObjList)
