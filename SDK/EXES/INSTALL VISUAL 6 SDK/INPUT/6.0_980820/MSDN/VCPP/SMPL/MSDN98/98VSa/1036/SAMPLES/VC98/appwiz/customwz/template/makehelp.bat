@echo off
$$IF(HM_NOTE)

REM -- PLEASE NOTE: OEM VS. ANSI CHARACTER SET DIFFERENCES
REM -- Many of the file names below look wierd in most editors because they need to be 
REM -- in the OEM character set, not the ANSI character set, in order to make batch  
REM -- files work right. The output and editor windows work with the ANSI character set.  
REM -- Where names are seen only in the output window, they have been left in the 
REM -- ANSI character set.

$$ENDIF	//HM_NOTE
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by $$ROOT$$.HPJ. >"hlp\$$HM_FILE_OEM$$.hm"
echo. >>"hlp\$$HM_FILE_OEM$$.hm"
echo // Dialogs (IDD_*) >>"hlp\$$HM_FILE_OEM$$.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$$HM_FILE_OEM$$.hm"
echo. >>"hlp\$$HM_FILE_OEM$$.hm"

REM -- Make help for Project $$ROOT$$

start /wait hcw /C /E /M "$$root_oem$$.hpj"
if %errorlevel% == 1 goto :Error
if exist Debug\nul copy "$$root_oem$$.hlp" Debug
if exist Release\nul copy "$$root_oem$$.hlp" Release
goto :done

:Error
echo $$root$$.hpj(1) : error: Problem encountered creating help file

:done
echo.
