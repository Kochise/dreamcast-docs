@echo off
: /*+========================================================================
:  File:      CLEANALL.BAT
:
:  Summary:   This Batch file performs a CLEANALL of the all the COM
:             Tutorial Code Samples. WARNING: This batch file deletes all
:             Visual Studio project files and other temporary work files
:             created by VC++. All COM servers are unregistered from the
:             the registry.  Most of the files that are generated during
:             the build of the code samples are deleted. This includes the
:             EXE and DLL executables as well as all debug symbol files. It
:             assumes that you have set up your environment to compile
:             Win32 applications using the Platform SDK with Visual C++
:             v. 4.x+ or other compatible 32-bit C++ compiler.
:
:  Usage:     CLEANALL
:               To perform a cleanall on all the tutorial code samples.
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
IF NOT EXIST register\register.exe GOTO CLEAN
call unregall.bat
IF ERRORLEVEL 1 GOTO ERROR
:CLEAN
call makeall.bat cleanall
IF ERRORLEVEL 1 GOTO ERROR
goto :DONE
:ERROR
echo ================ CLEANALL Error.
goto :END
:DONE
echo ================ CLEANALL Work Done.
:END
