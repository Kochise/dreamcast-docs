echo off
cls
if !%1==%1! goto error_usage
rem
echo DBFlash will update your Dreamcast Development System
echo with the current firmware for the debug adapter (DA),
echo GD-ROM emulator (GD-M), and Boot ROM.
echo.
echo You must have a Set 5.24 development system connected
echo to your PC with the latest Adaptec ASPI drivers installed.
echo See readme.txt for details.
echo.
echo ----------------------------------------------------------------
echo This process does *NOT* work on Set 5.23 systems.  Check the
echo serial number on the bottom of the unit if you are unsure of the
echo version of your system.
echo.
echo To halt this script, press [Ctrl-C] then Y to quit
echo.
pause
if not exist %1\dbflash.exe goto error_noutil
start /wait %1\dbflash.exe
cls
echo If you adjusted the SLIDE SW switch on the front of the Set 5.24
echo to flash the Boot ROM, please return the switch to the LEFT now.
echo Shut down your PC and turn OFF the development system for
echo at least thirty seconds.
echo.
goto done

:error_util
echo The reflashing program, DBFlash.exe, could not be found.
goto help

:error_usage
echo Usage: %0 [path to firmware images]
goto done

:help
echo.
echo Please check the target system and try reflashing the target.
echo If you are unable to reflash the system after multiple attempts,
echo please contact Sega Developer Technical Support.

:done
pause
cls