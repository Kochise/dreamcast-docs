@echo off

rem This batch file prepares a DOS shell for use with Dreamcast compiler tools.

rem Uncomment to allow easier command line text control
rem doskey /insert

echo %0: Setting environment variables..
echo.
echo ** HITACHI COMPILER **

rem Set the location of the Katana installation.
rem Default: C:\Katana

if not !%KATANA_ROOT%==%KATANA_ROOT%! goto katanarootalreadyset
SET KATANA_ROOT=
:katanarootalreadyset

rem if !%KATANA_ROOT%==%KATANA_ROOT%! goto error_nokatanaroot
rem Check for the existence of a compatible shell.  At this time, only
rem Microsoft-designed COMMAND.COM is acceptable.

ver | find "Windows"
if errorlevel 1 goto error_notcompatibleshell

rem Add Gnu Make and Hitachi compiler tools to the current path.
SET PATH=%PATH%;%KATANA_ROOT%\Utl\Dev\Make;%KATANA_ROOT%\Utl\Dev\Hitachi

rem Verify the existence of Gnu Make.

gmake -v > chk_2397.tmp
if not exist chk_2397.tmp goto error_nonmake
del chk_2397.tmp

rem Set include and library directories used by Hitachi compiler tools.
rem Edit these lines to change the default installation.

SET SHC_LIB=%KATANA_ROOT%\Utl\Dev\Hitachi
SET SHC_INC=%KATANA_ROOT%\Include\Shc
SET SHCPP_LIB=%SHC_LIB%
SET SHCPP_INC=%SHC_INC%

rem Verify Hitachi paths.

if !%SHC_LIB%==%SHC_LIB%! goto error_toolpathsnotset
if !%SHC_INC%==%SHC_INC%! goto error_toolpathsnotset
if !%SHCPP_LIB%==%SHCPP_LIB%! goto error_toolpathsnotset
if !%SHCPP_INC%==%SHCPP_INC%! goto error_toolpathsnotset

if not exist %SHC_LIB%\nul goto error_toolpathsnotset
if not exist %SHC_INC%\nul goto error_toolpathsnotset
if not exist %SHCPP_LIB%\nul goto error_toolpathsnotset
if not exist %SHCPP_INC%\nul goto error_toolpathsnotset

rem Set location of temporary files created during compilation.
rem These files (.tmp) may be left behind when a compile is interrupted.
rem Default:  SET SHC_TMP=C:\Windows\Temp

SET SHC_TMP=.
SET SHCPP_TMP=%SHC_TMP%

rem Set default library for Hitachi C/C++.
rem Default: SET HLNK_LIBRARY1=C:\Katana\Lib\sh4nlfzn.lib

SET HLNK_LIBRARY1=%KATANA_ROOT%\Lib\sh4nlfzn.lib

rem Verify the existence of HLNK_LIBRARY1

if !%HLNK_LIBRARY1%==%HLNK_LIBRARY1%! goto error_hlnknotset
if not exist %HLNK_LIBRARY1% goto error_hlnknotset

rem Verify the existence of the Hitachi tools.

shc > chk_2397.tmp
if not exist chk_2397.tmp goto error_shccmd
del chk_2397.tmp

goto setgnu

rem --------- Gnu Setup ---------
:setgnu
echo ** GNU COMPILER **

SET PATH=%PATH%;%KATANA_ROOT%\Utl\Dev\Gnu\Bin

SET CYGROOT=%KATANA_ROOT%\Utl\Dev\Gnu
SET GCC_EXEC_PREFIX=%CYGROOT%\lib\gcc-lib\
SET CYGREL=progressive-97r2a

if !%CYGROOT%==%CYGROOT%! goto error_gnupathsnotset
if !%GCC_EXEC_PREFIX%==%GCC_EXEC_PREFIX%! goto error_gnupathsnotset
if !%CYGREL%==%CYGREL%! goto error_gnupathsnotset

if not exist %CYGROOT%\nul goto error_gnupathsnotset
if not exist %GCC_EXEC_PREFIX%nul goto error_gnupathsnotset

echo Cygnus GNUPro2.0 %CYGREL%

gcc -v > chk_2397.tmp
if not exist chk_2397.tmp goto error_gnucmd
del chk_2397.tmp

rem --------- Metrowerks Setup ---------
:setmwshc
echo.
echo ** METROWERKS COMPILER **

SET PATH=%PATH%;%KATANA_ROOT%\Utl\Dev\Codewarrior\Tools\Command_line_tools

SET MWCINCLUDES=%KATANA_ROOT%\Include;%KATANA_ROOT%\Include\Shc;%KATANA_ROOT%\Utl\Dev\CodeWarrior\Dreamcast_Support\MSL\MSL_C++\MSL_Common\Include;%KATANA_ROOT%\Utl\Dev\CodeWarrior\Dreamcast_Support\MSL\MSL_C\MSL_DC\Include;%KATANA_ROOT%\Utl\Dev\CodeWarrior\Dreamcast_Support\Runtime\Common_Sources
SET MWLIBRARIES=%KATANA_ROOT%\Lib\MWerks;%KATANA_ROOT%\utl\dev\codewarrior\dreamcast_support\runtime\runtime_dc;%KATANA_ROOT%\Utl\Dev\CodeWarrior\Dreamcast_Support\MSL\MSL_C++\MSL_DC\Lib
SET MWLIBRARYFILES=MSLRuntimeDC.LIB;MSLCppDC.LIB
SET LM_LICENSE_FILE=%KATANA_ROOT%\Utl\Dev\CodeWarrior\License.dat

if "!%MWCINCLUDES%"=="%MWCINCLUDES%!" goto error_mwshcpathsnotset
if "!%MWLIBRARIES%"=="%MWLIBRARIES%!" goto error_mwshcpathsnotset
if "!%MWLIBRARYFILES%"=="%MWLIBRARYFILES%!" goto error_mwshcpathsnotset
if "!%LM_LICENSE_FILE%"=="%LM_LICENSE_FILE%!" goto error_mwshcpathsnotset

mwshc -version > chk_2397.tmp
if not exist chk_2397.tmp goto error_mwshccmd
del chk_2397.tmp

mwshc -version

goto success

rem -------------------------------------------------------------------
rem ! Error handling
rem -------------------------------------------------------------------

:error_nokatanaroot
echo Error: The path specified by the KATANA_ROOT variable does not
echo exist.  Please edit SETPATHS.BAT.
goto done

:error_notcompatibleshell
echo Error: The command shell is not compatible with SetPaths.
echo Please make COMMAND.COM your default shell and try again.
goto done

:error_nonmake
echo Error: Gnu MAKE could not be found on the default path.  Please
echo edit SETPATHS.BAT.
goto done

:error_shccmd
echo Error: The Hitachi command line tools could not be found.
echo Please edit SETPATHS.BAT.
goto setgnu

:error_gnucmd
echo Error: The Gnu command line tools could not be found.
echo Please edit SETPATHS.BAT.
goto done

:error_mwshccmd
echo Error: The Metrowerks command line tools could not be found.
echo Please edit SETPATHS.BAT.
goto done

:error_toolpathsnotset
echo Error: Environmental variables required by the SH-C compiler could
echo not be determined, or do not point to valid directories.  Please
echo edit SETPATHS.BAT or install SHC Compiler from the SDK.
goto setgnu

:error_gnupathsnotset
echo Error: Environmental variables required by the Gnu compiler could
echo not be determined, or do not point to valid directories.  Please
echo edit SETPATHS.BAT or install Gnu Compiler from the SDK.
goto done

:error_mwshcpathsnotset
echo Error: Environmental variables required by the Metrowerks compiler could
echo not be determined, or do not point to valid directories.  Please
echo edit SETPATHS.BAT or install Metrowerks Compiler from the SDK.
goto done

:error_hlnknotset
echo Error: Environmental variable HLNK_LIBRARY1 is required and
echo could not be determined, or target file does not exist.  Please
echo edit SETPATHS.BAT.
goto done

:success
echo.
:done

