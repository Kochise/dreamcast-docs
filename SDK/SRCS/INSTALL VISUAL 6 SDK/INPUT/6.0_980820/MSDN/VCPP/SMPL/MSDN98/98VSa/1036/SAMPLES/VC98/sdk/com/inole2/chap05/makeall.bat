@echo off

call ..\mksamp2 dkoala1  "Koala_Object_#1_DLL_Chapter_5"       dkoala1.dll
call ..\mksamp2 dkoala2  "Koala_Object_#2_DLL_Chapter_5"       dkoala2.dll
call ..\mksamp2 dkoala3  "Koala_Object_#3_DLL_Chapter_5"       dkoala3.dll

call ..\mksamp2 ekoala1  "Koala_Object_#1_EXE_Chapter_5"       ekoala1.exe
call ..\mksamp2 ekoala2  "Koala_Object_#2_EXE_Chapter_5"       ekoala2.exe

call ..\mksamp2 objuser  "Object_User_Chapter_5"               objuser.exe
call ..\mksamp2 licuser  "Licensed_Object_User_Chapter_5"      licuser.exe

call ..\mksamp2 selfreg  "Self_Registration_Utility_Chapter_5" selfreg.exe

call ..\mksamp2 polyline "Polyline_Component_Chapter_5"        poly05.dll
call ..\mksamp1 cocosmo  "Component_Cosmo_Chapter_5"           cocosmo5.exe
