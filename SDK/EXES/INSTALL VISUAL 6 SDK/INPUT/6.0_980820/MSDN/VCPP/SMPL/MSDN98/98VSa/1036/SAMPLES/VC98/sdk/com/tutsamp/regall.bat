@echo off
: /*+========================================================================
:  File:      REGALL.BAT
:
:  Summary:   This Batch file registers all the COM servers in the
:             COM Tutorial Code Sample series.  It assumes that the
:             servers have already been built and that the REGISTER
:             sample has been built.
:
:  Usage:     REGALL
:               To register all COM servers.
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
echo ================ Registering DLLSERVE...
cd dllserve
..\register\register.exe dllserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering LICSERVE...
cd ..\licserve
..\register\register.exe licserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering MARSHAL...
cd ..\marshal
..\register\register.exe marshal.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering LOCSERVE...
cd ..\locserve
..\register\register.exe /e locserve.exe
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering APTSERVE...
cd ..\aptserve
..\register\register.exe /e aptserve.exe
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering FRESERVE...
cd ..\freserve
..\register\register.exe freserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering CONSERVE...
cd ..\conserve
..\register\register.exe conserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering STOSERVE...
cd ..\stoserve
..\register\register.exe stoserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering PERSERVE...
cd ..\perserve
..\register\register.exe perserve.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering PERTEXT...
cd ..\pertext
..\register\register.exe pertext.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering PERDRAW...
cd ..\perdraw
..\register\register.exe perdraw.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering DCDMARSH...
cd ..\dcdmarsh
..\register\register.exe dcdmarsh.dll
IF ERRORLEVEL 1 GOTO ERROR
:
echo ================ Registering DCDSERVE...
cd ..\dcdserve
..\register\register.exe /e dcdserve.exe
IF ERRORLEVEL 1 GOTO ERROR
:
cd ..
goto :DONE
:ERROR
echo ================ REGALL Error.
goto :END
:DONE
echo ================ REGALL Work Done.
:END
