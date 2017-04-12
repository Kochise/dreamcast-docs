@echo off
IF "%V6TOOLS%" == "" goto Usage1

setlocal
IF "%1" == "PMAC" goto buildpmac
IF "%1" == "PMac" goto buildpmac
IF "%1" == "pmac" goto buildpmac
IF "%1" == "" goto dobuild
goto Usage2

:buildpmac
shift
set PROCESSOR_ARCHITECTURE=PMAC
set PATH=%V6TOOLS%\mac\mppc\bin;%V6TOOLS%\mac\bin;%PATH%
set INCLUDE=%V6TOOLS%\mac\include;%V6TOOLS%\mac\include\macos;%INCLUDE%
set LIB=%V6TOOLS%\mac\mppc\lib;%LIB%

:dobuild
nmake %1 %2 %3 %4 %5 %6 %7 %8
endlocal

goto End

:Usage1
echo The environment variable V6TOOLS must be set to point
echo to the root of your VC++ 6.0 installation.

goto End

:Usage2
echo "bldnt" builds the runtimes for Win32 platform.
echo "bldnt PMac" builds the runtimes for the Power Macintosh.

:End

