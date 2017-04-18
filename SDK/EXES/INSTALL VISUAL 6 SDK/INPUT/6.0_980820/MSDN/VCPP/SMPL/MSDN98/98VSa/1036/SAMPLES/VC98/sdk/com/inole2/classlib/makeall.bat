@echo off

nmake /NOLOGO clean

if not "%CLEAN%" == "" goto :Contin

if "%SDI%" == "1" goto SDI

set SDI=
echo Building MDI CLASSLIB > err
nmake /I /NOLOGO >> err
if exist classmdi.lib copy classmdi.lib ..\lib

goto Contin

:SDI

SET SDI=1
echo Building SDI CLASSLIB > err
nmake /I /NOLOGO >> err
if exist classsdi.lib copy classsdi.lib ..\lib

SET SDI=

:Contin
if exist err type err >> ..\build\err

echo. >> ..\build\err
echo ****************************************** >> ..\build\err
echo. >> ..\build\err

if not "%CLEAN%" == "" goto :NoCopy
if exist classlib.h copy classlib.h ..\inc
if exist classres.h copy classres.h ..\inc

:NoCopy

call ..\mksamp1 skel "CLASSLIB_Skeleton" skel.exe
