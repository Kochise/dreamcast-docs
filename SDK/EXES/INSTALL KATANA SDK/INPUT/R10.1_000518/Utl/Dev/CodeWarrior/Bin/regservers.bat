@echo off
set reg=MWRegSvr /c
echo Registering core DLLs and IDE
%reg% .\plugins\support\MWComHelpers.dll
%reg% .\plugins\Support\CPlusSourceGen.dll

echo     IDE.exe
.\IDE.exe /RegServer

echo Done.
pause
