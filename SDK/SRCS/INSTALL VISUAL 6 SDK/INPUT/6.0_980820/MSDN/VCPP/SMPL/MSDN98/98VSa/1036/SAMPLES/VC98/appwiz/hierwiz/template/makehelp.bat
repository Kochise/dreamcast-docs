@echo off
REM -- First make map file from App Studio generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by $$ROOT$$.HPJ. >hlp\$$root$$.hm
echo. >>hlp\$$root$$.hm
echo // Commands (ID_* and IDM_*) >>hlp\$$root$$.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\$$root$$.hm
echo. >>hlp\$$root$$.hm
echo // Prompts (IDP_*) >>hlp\$$root$$.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\$$root$$.hm
echo. >>hlp\$$root$$.hm
echo // Resources (IDR_*) >>hlp\$$root$$.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\$$root$$.hm
echo. >>hlp\$$root$$.hm
echo // Dialogs (IDD_*) >>hlp\$$root$$.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\$$root$$.hm
echo. >>hlp\$$root$$.hm
echo // Frame Controls (IDW_*) >>hlp\$$root$$.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\$$root$$.hm
REM -- Make help for Project $$ROOT$$
call hc31 $$root$$.hpj
echo.
