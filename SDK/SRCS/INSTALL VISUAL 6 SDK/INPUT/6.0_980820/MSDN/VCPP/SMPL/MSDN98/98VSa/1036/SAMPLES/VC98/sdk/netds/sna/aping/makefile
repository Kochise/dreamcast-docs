USE_SNA=1
console=1

Proj = aping

shared=..\Shared

cDefines = -I..\Shared

LibList = $(shared)\$(ObjDir)\Shared.Lib

!include <BkOffice.Mak>

All: $(ObjDir)\aping.exe $(ObjDir)\apingd.exe

$(ObjDir)\aping.exe: $(@R).obj $(LibList)

$(ObjDir)\apingd.exe: $(@R).obj $(LibList)
