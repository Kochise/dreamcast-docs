@echo off

cd %1

nmake /NOLOGO clean
echo Building %2 > err
nmake /I /NOLOGO >> err
if exist %3 copy %3 ..\build

type err >> ..\build\err

echo. >> ..\build\err
echo ****************************************** >> ..\build\err
echo. >> ..\build\err

cd..
