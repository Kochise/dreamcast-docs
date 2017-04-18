@echo off
: /*+========================================================================
:  File:      UNREGALL.BAT
:
:  Summary:   This Batch file Unregisters all the COM servers in the
:             COM Tutorial Code Sample series.  It assumes that the
:             servers have already been built and that the REGISTER
:             sample has been built.
:
:  Usage:     UNREGALL
:               To Unregister all COM servers.
:
:  Origin:    8-23-97: atrent - Revised for COM Tutorial Sample series.
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
IF NOT EXIST register\register.exe GOTO ERROR
echo ================ UnRegistering DLLSERVE...
cd dllserve
..\register\register.exe /u dllserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering LICSERVE...
cd ..\licserve
..\register\register.exe /u licserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering MARSHAL...
cd ..\marshal
..\register\register.exe /u marshal.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering LOCSERVE...
cd ..\locserve
..\register\register.exe /u /e locserve.exe
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering APTSERVE...
cd ..\aptserve
..\register\register.exe /u /e aptserve.exe
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering FRESERVE...
cd ..\freserve
..\register\register.exe /u freserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering CONSERVE...
cd ..\conserve
..\register\register.exe /u conserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering STOSERVE...
cd ..\stoserve
..\register\register.exe /u stoserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering PERSERVE...
cd ..\perserve
..\register\register.exe /u perserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering PERTEXT...
cd ..\pertext
..\register\register.exe /u pertext.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering PERDRAW...
cd ..\perdraw
..\register\register.exe /u perdraw.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering DCDMARSH...
cd ..\dcdmarsh
..\register\register.exe /u dcdmarsh.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ UnRegistering DCDSERVE...
cd ..\dcdserve
..\register\register.exe /u /e dcdserve.exe
IF ERRORLEVEL 1 GOTO ERROR
:
cd ..
goto :DONE
:ERROR
echo ================ UNREGALL Error.
goto :END
:DONE
echo ================ UNREGALL Work Done.
:END
