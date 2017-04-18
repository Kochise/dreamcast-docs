USE_SNA=1
console=1

Proj=mpingd

shared=..\Shared

cDefines = -I..\Shared

LibList = $(shared)\$(ObjDir)\Shared.Lib

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Exe

$(ObjDir)\$(Proj).exe: $(@R).obj $(LibList)
