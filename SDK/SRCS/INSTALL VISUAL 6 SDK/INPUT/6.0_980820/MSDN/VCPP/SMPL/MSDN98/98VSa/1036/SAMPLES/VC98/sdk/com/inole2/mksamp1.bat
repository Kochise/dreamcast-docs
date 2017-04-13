@echo off
cd %1

if "%SDI%" == "1" goto SDI

set SDI=
echo Building MDI %2 > err
goto Exit

:SDI

SET SDI=1
echo Building SDI %2 > err

SET SDI=

:Exit

nmake /NOLOGO clean
nmake /I /NOLOGO >> err

if exist %3 copy %3 ..\..\build
type err >> ..\..\build\err

echo. >> ..\..\build\err
echo ****************************************** >> ..\..\build\err
echo. >> ..\..\build\err

cd..
