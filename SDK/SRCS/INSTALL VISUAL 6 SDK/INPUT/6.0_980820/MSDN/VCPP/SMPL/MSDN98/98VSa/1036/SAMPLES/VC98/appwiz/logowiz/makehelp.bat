@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by LOGOWIZ.HPJ. >hlp\logowiz.hm
echo. >>hlp\logowiz.hm
echo // Dialogs (IDD_*) >>hlp\logowiz.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\logowiz.hm
echo. >>hlp\logowiz.hm

REM -- Make help for Project LOGOWIZ

start /wait hcw /C /E /M logowiz.hpj
if exist Debug copy logowiz.hlp Debug
if exist Release copy logowiz.hlp Release
