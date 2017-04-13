@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by CUSTMWZ.HPJ. >"hlp\CustmWz.hm"
echo. >>"hlp\CustmWz.hm"
echo // Dialogs (IDD_*) >>"hlp\CustmWz.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\CustmWz.hm"
echo. >>"hlp\CustmWz.hm"

REM -- Make help for Project CUSTMWZ

hcw /C /E /M hlp\custmwz.hpj
if %errorlevel% == 1 goto :Error
if exist Debug\nul copy hlp\custmwz.hlp Debug
if exist Release\nul copy hlp\custmwz.hlp Release
goto :done

:Error
echo hlp\custmwz.hpj(1) : error: Problem creating help file

:done
echo.