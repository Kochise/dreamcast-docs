@echo off
REM  Set environment for the PPC target
REM  This batch file serves as a template only.
Title WCE PPC Environment

REM This batch file sets up an environment for building for a specific CPU from the command line.
REM The build environment defaults to an H/PC Ver. 2.00 platform. The macros that control the
REM platform are: PLATFORM, OSVERSION, WCEROOT and SDKROOT. The H/PC Ver. 2.00 default settings
REM are as follows:
REM    PLATFORM=MS HPC
REM        OSVERSION=WCE200
REM        WCEROOT=C:\Windows CE Tools    //Root dir for VCCE
REM        SDKROOT=C:\Windows CE Tools    //Root dir for H/PC SDK
REM The Palm-size PC 2.01 default settings are:
REM    PLATFORM=ms palm size pc
REM        OSVERSION=WCE201
REM        WCEROOT=C:\Windows CE Tools    //Root dir for VCCE
REM        SDKROOT=C:\Windows CE Tools    //Root dir for PSPC SDK
REM The batch file uses these macros to set the PATH, INCLUDE, LIB macros for the default
REM H/PC Ver. 2.00 platform. Please note that if the default setup options were altered during
REM installation (for example, if the install directories were changed), then the user needs
REM to modify these macros accordingly.

if "%OSVERSION%"=="" set OSVERSION=WCE200
if "%PLATFORM%"=="" set PLATFORM=MS HPC
if "%WCEROOT%"=="" set WCEROOT={app}\Windows CE Tools
if "%SDKROOT%"=="" set SDKROOT={app}\Windows CE Tools

set PATH=%WCEROOT%\bin;%WCEROOT%\%OSVERSION%\bin;%path%
set INCLUDE=%WCEROOT%\%OSVERSION%\%PLATFORM%\include;%WCEROOT%\%OSVERSION%\%PLATFORM%\MFC\include;%WCEROOT%\%OSVERSION%\%PLATFORM%\ATL\include;
set LIB=%WCEROOT%\%OSVERSION%\%PLATFORM%\lib\PPC;%WCEROOT%\%OSVERSION%\%PLATFORM%\MFC\lib\PPC;%WCEROOT%\%OSVERSION%\%PLATFORM%\ATL\lib\PPC;

set CC=clppc.exe

set TARGETCPU=PPC
set CFG=none
