@echo off
: /*+========================================================================
:  File:      MAKEALL.BAT
:
:  Summary:   This Batch file builds all of the COM Tutorial Samples.
:             It assumes that you have set up your environment to compile
:             Win32 applications using the Win32 SDK with Visual C++ v.
:             4.x+ or other compatible 32-bit C++ compiler.
:
:  Usage:     MAKEALL
:               To build all with debug info.
:
:             MAKEALL clean
:               To clean up temporary binaries (leaves EXEs and DLLs).
:
:             MAKEALL cleanall
:               To perform an exhaustive cleanall of all generated files.
:
:             MAKEALL "nodebug=1"
:               To build all with no debug info (you need quotes).
:
:             MAKEALL "unicode=1"
:               To build all for UNICODE string support (ANSI is default).
:
:             MAKEALL "tune=1"
:               To build all with Working Set Tuner Info.
:
:             MAKEALL "profile=1"
:               To build all with Call Attributed Profiling Info.
:
:             MAKEALL "no_ansi=1"
:               To build all for no ANSI NULL Compliance.
:
:             MAKEALL "nodebug=1" "unicode=1"
:               Options can be combined on one invocation.
:
:  Origin:    8-23-97: atrent - Revised for OLE Tutorial Code Sample series.
:
: --------------------------------------------------------------------------
:
:  This file is part of the Microsoft COM Tutorial Code Samples.
:
:  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.
:
:  This source code is intended only as a supplement to Microsoft
:  Development Tools and/or on-line documentation.  See these other
:  materials for detailed information regarding Microsoft code samples.
:
:  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
:  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
:  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
:  PARTICULAR PURPOSE.
: ==========================================================================+*/
:
cls
echo ================ Working on APPUTIL...
cd apputil
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on READTUT...
cd ..\readtut
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on EXESKEL...
cd ..\exeskel
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DLLSKEL...
cd ..\dllskel
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DLLUSER...
cd ..\dlluser
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on COMOBJ...
cd ..\comobj
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on COMUSER...
cd ..\comuser
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on REGISTER...
cd ..\register
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DLLSERVE...
cd ..\dllserve
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DLLCLIEN...
cd ..\dllclien
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on LICSERVE...
cd ..\licserve
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on LICCLIEN...
cd ..\licclien
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on MARSHAL...
cd ..\marshal
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on MARSHAL2...
cd ..\marshal2
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on LOCSERVE...
cd ..\locserve
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on LOCCLIEN...
cd ..\locclien
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on APTSERVE...
cd ..\aptserve
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on APTCLIEN...
cd ..\aptclien
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on REMCLIEN...
cd ..\remclien
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on FRESERVE...
cd ..\freserve
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on FRECLIEN...
cd ..\freclien
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on CONSERVE...
cd ..\conserve
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on CONCLIEN...
cd ..\conclien
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on STOSERVE...
cd ..\stoserve
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on STOCLIEN...
cd ..\stoclien
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on PERSERVE...
cd ..\perserve
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on PERTEXT...
cd ..\pertext
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on PERDRAW...
cd ..\perdraw
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on PERCLIEN...
cd ..\perclien
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DCDMARSH...
cd ..\dcdmarsh
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DCDSERVE...
cd ..\dcdserve
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DCOMDRAW...
cd ..\dcomdraw
nmake %1 %2 %3 %4 %5 %6 %7 %8 %9
IF ERRORLEVEL 1 GOTO ERROR
:
cd ..
goto :DONE
:ERROR
echo ================ MAKEALL Error.
goto :END
:DONE
echo ================ MAKEALL Work Done.
:END
