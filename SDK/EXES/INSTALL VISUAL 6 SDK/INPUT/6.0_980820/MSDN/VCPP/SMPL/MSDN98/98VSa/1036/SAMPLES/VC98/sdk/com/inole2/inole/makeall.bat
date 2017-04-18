@echo off

nmake /NOLOGO clean
echo Building "Inside_OLE_Utilities_DLL" > err
nmake /I /NOLOGO >> err
if exist inole.dll copy inole.dll ..\build
if exist inole.lib copy inole.lib ..\lib

type err >> ..\build\err

echo. >> ..\build\err
echo ****************************************** >> ..\build\err
echo. >> ..\build\err
