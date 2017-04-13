@echo off
: /*+========================================================================
:  File:      LOGMALL.BAT
:
:  Summary:   This Batch file builds all of the COM Tutorial Samples.
:             It assumes that you have set up your environment to compile
:             Win32 applications using the Win32 Platform SDK with Visual
:             C++ v. 4.x+ or other compatible 32-bit C++ compiler.
:
:             LOGMALL does the same as MAKEALL.BAT except that all
:             compilation output is logged to an ERRORLOG.TXT file.
:             NOTEPAD.EXE is launched at the end of LOGMALL to view the
:             content of ERRORLOG.TXT. ERRORLOG.TXT is generated in the
:             same main tutorial directory where LOGMALL.BAT resides.
:
:  Usage:     LOGMALL
:               To build all with debug info.
:
:             LOGMALL clean
:               To clean up temporary binaries (leaves EXEs and DLLs).
:
:             LOGMALL cleanall
:               To perform an exhaustive cleanall of all generated files.
:
:             LOGMALL "nodebug=1"
:               To build all with no debug info (you need quotes).
:
:             LOGMALL "unicode=1"
:               To build all for UNICODE string support (ANSI is default).
:
:             LOGMALL "tune=1"
:               To build all with Working Set Tuner Info.
:
:             LOGMALL "profile=1"
:               To build all with Call Attributed Profiling Info.
:
:             LOGMALL "no_ansi=1"
:               To build all for no ANSI NULL Compliance.
:
:             LOGMALL "nodebug=1" "unicode=1"
:               Options can be combined on one invocation.
:
:  Origin:    8-23-97: atrent - Editor inheritance from MAKEALL.BAT.
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
echo ========================= Build of All Samples ==========================
echo ================ Logging all errors to file ERRORLOG.TXT ================
echo ============  COM Tutorial Samples ============== > ehh
echo ====== Make/Error log for build of all samples ====== >> ehh
:
echo ================ Working on APPUTIL...
cd apputil
echo ================ Working on APPUTIL ================ > ..\e00
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e00
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on READTUT...
cd ..\readtut
echo ================ Working on READTUT ================ > ..\e01
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e01
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on EXESKEL...
cd ..\exeskel
echo ================ Working on EXESKEL ================ > ..\e02
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e02
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DLLSKEL...
cd ..\dllskel
echo ================ Working on DLLSKEL ================ > ..\e03
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e03
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DLLUSER...
cd ..\dlluser
echo ================ Working on DLLUSER ================ > ..\e04
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e04
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on COMOBJ...
cd ..\comobj
echo ================ Working on COMOBJ ================ > ..\e05
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e05
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on COMUSER...
cd ..\comuser
echo ================ Working on COMUSER ================ > ..\e06
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e06
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on REGISTER...
cd ..\register
echo ================ Working on REGISTER ================ >> ..\e07
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e07
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DLLSERVE...
cd ..\dllserve
echo ================ Working on DLLSERVE ================ > ..\e08
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e08
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DLLCLIEN...
cd ..\dllclien
echo ================ Working on DLLCLIEN ================ > ..\e09
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e09
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on LICSERVE...
cd ..\licserve
echo ================ Working on LICSERVE ================ > ..\e10
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e10
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on LICCLIEN...
cd ..\licclien
echo ================ Working on LICCLIEN ================ > ..\e11
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e11
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on MARSHAL...
cd ..\marshal
echo ================ Working on MARSHAL ================ > ..\e12
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e12
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on MARSHAL2...
cd ..\marshal2
echo ================ Working on MARSHAL2 ================ > ..\e13
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e13
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on LOCSERVE...
cd ..\locserve
echo ================ Working on LOCSERVE ================ > ..\e14
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e14
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on LOCCLIEN...
cd ..\locclien
echo ================ Working on LOCCLIEN ================ > ..\e15
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e15
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on APTSERVE...
cd ..\aptserve
echo ================ Working on APTSERVE ================ > ..\e16
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e16
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on APTCLIEN...
cd ..\aptclien
echo ================ Working on APTCLIEN ================ > ..\e17
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e17
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on REMCLIEN...
cd ..\remclien
echo ================ Working on REMCLIEN ================ > ..\e18
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e18
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on FRESERVE...
cd ..\freserve
echo ================ Working on FRESERVE ================ > ..\e19
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e19
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on FRECLIEN...
cd ..\freclien
echo ================ Working on FRECLIEN ================ > ..\e20
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e20
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on CONSERVE...
cd ..\conserve
echo ================ Working on CONSERVE ================ > ..\e21
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e21
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on CONCLIEN...
cd ..\conclien
echo ================ Working on CONCLIEN ================ > ..\e22
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e22
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on STOSERVE...
cd ..\stoserve
echo ================ Working on STOSERVE ================ > ..\e23
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e23
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on STOCLIEN...
cd ..\stoclien
echo ================ Working on STOCLIEN ================ > ..\e24
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e24
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on PERSERVE...
cd ..\perserve
echo ================ Working on PERSERVE ================ > ..\e25
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e25
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on PERTEXT...
cd ..\pertext
echo ================ Working on PERTEXT ================ > ..\e26
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e26
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on PERDRAW...
cd ..\perdraw
echo ================ Working on PERDRAW ================ > ..\e27
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e27
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on PERCLIEN...
cd ..\perclien
echo ================ Working on PERCLIEN ================ > ..\e28
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e28
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DCDMARSH...
cd ..\dcdmarsh
echo ================ Working on DCDMARSH ================ > ..\e29
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e29
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DCDSERVE...
cd ..\DCDSERVE
echo ================ Working on DCDSERVE ================ > ..\e30
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e30
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Working on DCOMDRAW...
cd ..\dcomdraw
echo ================ Working on DCOMDRAW ================ > ..\e31
nmake -nologo %1 %2 %3 %4 %5 %6 %7 %8 %9 >> ..\e31
IF ERRORLEVEL 1 GOTO ERROR
:
goto :DONE
:ERROR
cd ..
echo ================ LOGMALL Done. Errors. > err
echo ================ LOGMALL Done. Errors. >> err
echo ================ LOGMALL Done. Errors. >> err
goto :END
:DONE
cd ..
echo ================ LOGMALL Done. No Errors. > err
echo ================ LOGMALL Done. No Errors. >> err
echo ================ LOGMALL Done. No Errors. >> err
:END
copy e00+e01+e02+e03+e04+e05+e06+e07+e08+e09+e10+e11+e12+e13+e14+e15 ep1
copy e16+e17+e18+e19+e20+e21+e22+e23+e24+e25+e26+e27+e28+e29+e30+e31 ep2
copy ehh+ep1+ep2+err errorlog.txt
del e??.
echo ================ LOGMALL Done.
echo ================ LOGMALL Done.
echo ================ LOGMALL Done.
: Substitute your favorite ASCII text viewer here for notepad.
notepad errorlog.txt
