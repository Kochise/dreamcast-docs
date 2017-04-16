@echo off
if "%1"=="32" Goto Win32
mktyplib /nologo /win16 /DWIN16 /tlb win16.tlb win.odl
copy win16.tlb %windir%
:Win32
if "%1"=="16" Goto Exit
mktyplib /nologo /win32 /DWIN32 /tlb win32.tlb win.odl
copy win32.tlb %windir%
:Exit
