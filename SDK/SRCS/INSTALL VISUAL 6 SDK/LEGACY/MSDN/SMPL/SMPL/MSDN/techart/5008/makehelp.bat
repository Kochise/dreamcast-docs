@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by ADVANCEDFTP.HPJ. >"hlp\AdvancedFTP.hm"
echo. >>"hlp\AdvancedFTP.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\AdvancedFTP.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\AdvancedFTP.hm"
echo. >>"hlp\AdvancedFTP.hm"
echo // Prompts (IDP_*) >>"hlp\AdvancedFTP.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\AdvancedFTP.hm"
echo. >>"hlp\AdvancedFTP.hm"
echo // Resources (IDR_*) >>"hlp\AdvancedFTP.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\AdvancedFTP.hm"
echo. >>"hlp\AdvancedFTP.hm"
echo // Dialogs (IDD_*) >>"hlp\AdvancedFTP.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\AdvancedFTP.hm"
echo. >>"hlp\AdvancedFTP.hm"
echo // Frame Controls (IDW_*) >>"hlp\AdvancedFTP.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\AdvancedFTP.hm"
REM -- Make help for Project ADVANCEDFTP


echo Building Win32 Help files
start /wait hcrtf -x "hlp\AdvancedFTP.hpj"
echo.
if exist Debug\nul copy "hlp\AdvancedFTP.hlp" Debug
if exist Debug\nul copy "hlp\AdvancedFTP.cnt" Debug
if exist Release\nul copy "hlp\AdvancedFTP.hlp" Release
if exist Release\nul copy "hlp\AdvancedFTP.cnt" Release
echo.


