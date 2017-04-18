@echo off

call ..\mksamp2 ddataobj "Data_Object_DLL_Chapter_10"    ddataobj.dll
call ..\mksamp2 edataobj "Data_Object_EXE_Chapter_10"    edataobj.exe
call ..\mksamp2 datauser "Data_User_Chapter_10"          datauser.exe

call ..\mksamp2 polyline "Polyline_Component_Chapter_10" poly10.dll
call ..\mksamp1 cocosmo  "Component_Cosmo_Chapter_10"    cocos10.exe
