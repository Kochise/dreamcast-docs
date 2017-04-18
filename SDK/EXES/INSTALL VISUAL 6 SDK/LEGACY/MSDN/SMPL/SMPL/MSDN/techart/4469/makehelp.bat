@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by NTDDWZD.HPJ. >hlp\ntddwzd.hm
echo. >>hlp\ntddwzd.hm
echo // Dialogs (IDD_*) >>hlp\ntddwzd.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\ntddwzd.hm
echo. >>hlp\ntddwzd.hm

REM -- Make help for Project NTDDWZD

call hc31 ntddwzd.hpj
if exist windebug copy ntddwzd.hlp windebug
if exist winrel copy ntddwzd.hlp winrel
