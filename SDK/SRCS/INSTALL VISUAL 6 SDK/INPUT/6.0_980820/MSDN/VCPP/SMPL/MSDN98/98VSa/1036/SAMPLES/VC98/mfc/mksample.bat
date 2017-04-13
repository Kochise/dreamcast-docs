@echo off

REM This is a part of the Microsoft Foundation Classes C++ library.
REM Copyright (C) 1992-1996 Microsoft Corporation
REM All rights reserved.
REM
REM This source code is only intended as a supplement to the
REM Microsoft Foundation Classes Reference and related
REM electronic documentation provided with the library.
REM See these sources for detailed information regarding the
REM

echo.
echo Microsoft Foundation Classes -- Sample Applications (batch build)
echo.
echo This MS-DOS Batch file will build most of the Windows/MFC sample
echo applications.  Use of the batch file will save time and
echo disk space if you are interested in seeing all of the
echo working samples as you learn the Microsoft Foundation Classes.
echo If you are modifying a sample or using it as a basis for
echo your own application, then the use of the integrated development
echo environment (IDE) is recommended.
echo.
echo.

set __DEBUG=1
if "%1"=="DEBUG" goto doit
if "%1"=="debug" goto doit

set __DEBUG=0

if "%1"=="RETAIL" goto doit
if "%1"=="retail" goto doit

if "%1"=="CLEAN" goto doit_clean
if "%1"=="clean" goto doit_clean

echo Please specify DEBUG or RETAIL or CLEAN on the command line.
echo.
echo     DEBUG will build executables with symbolic information,
echo         diagnostics, and no optimizations (large and slow).
echo     RETAIL will build ship quality executables that
echo         are fully optimized (small and fast).
echo     CLEAN will remove all compiler generated files (object
echo         files, executables, etc.)  Use this to switch between
echo         DEBUG and RETAIL.
echo.

goto end

:doit
shift

echo.
echo NOTE: Since this builds all the sample programs it could
echo take a little while.  Type Ctrl-C now if you wish
echo to build them later.  You can stop the build at
echo any time by typing Ctrl-C (several times) and
echo answer 'Y' to terminate.
echo.
pause
goto doit_build

:doit_clean

@echo on
if exist STDAFX??.PCH erase STDAFX??.PCH
if exist STDAFX??.OBJ erase STDAFX??.OBJ
if exist STDDLL??.PCH erase STDDLL??.PCH
if exist STDDLL??.OBJ erase STDDLL??.OBJ

:doit_build
@echo on

cd GENERAL\CMNCTRL1
echo General samples
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\CMNCTRL2
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\CTRLBARS
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\CTRLTEST
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DBVLIST
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DIBLOOK
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DLGCBR32
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DLGTEMPL
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DOCKTOOL
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DYNAMENU
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\HELLO
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\HELLOAPP
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MDI
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MDIDOCVW
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MODELESS
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MULTIPAD
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\NPP
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\PROPDLG
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\ROWLIST
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\SAVER
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\SNAPVW
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\TRACKER
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\VCTERM
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\VIEWEX
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\WIZARD97
nmake /nologo "DEBUG=%__DEBUG%" %1

cd ..\..\OLE\BINDSCRB
echo OLE samples
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\ACDUAL\MFCCTRL
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\..\CALCDRIV
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DRAWCLI
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\HIERSVR
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\INPROC
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\IPDRIVE
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MFCCALC
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\OCLIENT
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\OLEVIEW
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\SUPERPAD
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\WORDPAD
nmake /nologo "DEBUG=%__DEBUG%" %1

cd ..\..\DATABASE\CATALOG
echo Database samples
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\BINDENRL
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\CATALOG2
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DAOCTL
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DAOENROL
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DAOTABLE
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DAOVIEW
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DBFETCH
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DYNABIND
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\EXTBIND
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MDIBIND
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\ODBCINFO
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\STDREG
nmake /nologo "DEBUG=%__DEBUG%" %1

cd ..\..\ADVANCED\CHATSRVR
echo Advanced samples
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\CHATTER
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\CHKBOOK
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\COLLECT
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\CUBE
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DLLHUSK
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\DLLTRACE
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\FIRE
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MTGDI
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MTMDI
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MTRECALC
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MUTEXES
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\OLDBARS
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\SPEAKN
nmake /nologo "DEBUG=%__DEBUG%" %1

cd ..\..\INTERNET\COUNTER
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\FTPTREE
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\HTTPSVR
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MFCIE
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MFCUCASE
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\TEAR
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\WWWQUOTE
nmake /nologo "DEBUG=%__DEBUG%" %1

cd ..\..\UTILITY\GUIDGEN
echo Utility samples
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\MAKEHM
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\TEMPLDEF
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..\TRACER
nmake /nologo "DEBUG=%__DEBUG%" %1

cd ..\..\TUTORIAL\AUTODRIV
echo Tutorials
nmake /nologo "DEBUG=%__DEBUG%" %1

if not exist ..\SCRIBBLE\STEP7\makefile goto contain
if "%1"=="CLEAN" erase ..\SCRIBBLE\STDAFX??.PCH
if "%1"=="CLEAN" erase ..\SCRIBBLE\STDAFX??.OBJ
cd ..\SCRIBBLE\STEP7
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..

:contain
if not exist ..\CONTAIN\STEP2\makefile goto autoclik
if "%1"=="CLEAN" erase ..\CONTAIN\STDAFX??.PCH
if "%1"=="CLEAN" erase ..\CONTAIN\STDAFX??.OBJ
cd ..\CONTAIN\STEP2
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..

:autoclik
if not exist ..\AUTOCLIK\STEP3\makefile goto enroll
if "%1"=="CLEAN" erase ..\AUTOCLIK\STDAFX??.PCH
if "%1"=="CLEAN" erase ..\AUTOCLIK\STDAFX??.OBJ
cd ..\AUTOCLIK\STEP3
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..

:enroll
if not exist ..\ENROLL\STEP4\makefile goto updir
if "%1"=="CLEAN" erase ..\ENROLL\STDAFX??.PCH
if "%1"=="CLEAN" erase ..\ENROLL\STDAFX??.OBJ
cd ..\ENROLL\STEP4
nmake /nologo "DEBUG=%__DEBUG%" %1
cd ..

:updir
cd ..\..

:end
set __DEBUG=
