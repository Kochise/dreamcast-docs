@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by ONEWNDWZ.HPJ. >"hlp\OneWndWz.hm"
echo. >>"hlp\OneWndWz.hm"
echo // Dialogs (IDD_*) >>"hlp\OneWndWz.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\OneWndWz.hm"
echo. >>"hlp\OneWndWz.hm"

REM -- Make help for Project ONEWNDWZ

start /wait hcw /C /E /M "OneWndWz.hpj"
if %errorlevel% == 1 goto :Error
if exist Debug\nul copy "OneWndWz.hlp" Debug
if exist Release\nul copy "OneWndWz.hlp" Release
goto :done

:Error
echo OneWndWz.hpj(1) : error: Problem encountered creating help file

:done
echo.
