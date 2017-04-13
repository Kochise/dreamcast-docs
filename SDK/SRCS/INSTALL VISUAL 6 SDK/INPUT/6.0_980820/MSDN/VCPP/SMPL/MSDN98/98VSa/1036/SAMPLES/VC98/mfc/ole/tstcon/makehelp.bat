@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
REM -- Now done manually by running MakeTCHM.bat, so that we can check
REM -- hlp\TstCon.hm into SourceSafe for the localization crew to get at
REM --   -DBartol, 10/22/97

REM -- call MakeTCHM.bat

REM -- Make help for Project TstCon

echo Building Win32 Help files
if exist hlp\TstCon32.hlp del hlp\TstCon32.hlp
start /wait hcw /C /E /M "hlp\TstCon.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\TstCon32.hlp" goto :Error
if not exist "hlp\TstCon32.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\TstCon32.hlp" Debug
if exist Debug\nul copy "hlp\TstCon32.cnt" Debug
if exist Release\nul copy "hlp\TstCon32.hlp" Release
if exist Release\nul copy "hlp\TstCon32.cnt" Release
echo.
goto :done

:Error
echo hlp\TstCon.hpj(1) : error: Problem encountered creating help file

:done
echo.
