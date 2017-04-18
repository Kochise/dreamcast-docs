@echo off
IF "%V6TOOLS%" == "" goto Usage1

if exist nmktobat.exe goto built_exe
echo =-=-=-=-= Building NMKtoBAT.EXE =-=-=-=-= 
echo This program is used in the MSVC CRTL build process
cl /W4 /WX /Za nmktobat.c
if errorlevel 1 goto errlev
:built_exe


IF "%1" == "PMAC" goto buildpmac
IF "%1" == "PMac" goto buildpmac
IF "%1" == "pmac" goto buildpmac
IF "%1" == "" goto buildx86
goto Usage2

:buildpmac
set PROCESSOR_ARCHITECTURE=PMAC
set PATH=%V6TOOLS%\mac\mppc\bin;%V6TOOLS%\mac\bin;%PATH%
set INCLUDE=%V6TOOLS%\mac\include;%V6TOOLS%\mac\include\macos;%INCLUDE%
set LIB=%V6TOOLS%\mac\mppc\lib;%LIB%
shift
goto dobuild

:buildx86
if "%PROCESSOR_ARCHITECTURE%"=="" set PROCESSOR_ARCHITECTURE=x86

:dobuild

echo =-=-=-=-= Doing MSVC40 CRTL Source build (Objects) =-=-=-=-= 
nmake -nologo -i -n BLD_OBJ=1 %1 %2 %3 %4 %5 > do_build.out
nmktobat < do_build.out > do_build.bat
call do_build.bat
if errorlevel 1 goto errlev
echo =-=-=-=-= Doing MSVC40 CRTL Source build (Libraries) =-=-=-=-= 
nmake -nologo BLD_LIB=1 %1 %2 %3 %4 %5
if errorlevel 1 goto errlev
goto finish

:errlev
echo.
echo ***
echo *** BUILD ABORTED -- ErrorLevel is non-zero!
echo ***
goto finish

:Usage1
echo The environment variable V6TOOLS must be set to point
echo to the root of your VC++ 6.0 installation.

goto finish

:Usage2
echo "bldwin95" builds the runtimes for Intel platforms.
echo "bldwin95 PMac" builds the runtimes for the Power Macintosh.
:finish
