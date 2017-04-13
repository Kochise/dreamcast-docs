@echo off

call ..\mksamp2 datatran "Data_Transfer_Object_Chapter_12" datatran.dll
call ..\mksamp1 cosmo    "Cosmo_Chapter_12"                cosmo12.exe
call ..\mksamp1 patron   "Patron_Chapter_12"               patron12.exe
call ..\mksamp1 cocosmo  "Component_Cosmo_Chapter_12"      cocos12.exe
