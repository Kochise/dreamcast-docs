@echo off
rem
rem  BUILDALL.BAT
rem  Copyright (C) 1996 Microsoft Corp.
rem
rem  This batch file allows you to build all the SQL Server 32-bit sample
rem  C/C++ programs.
rem

if "%1" == "?" goto usage
if "%1" == "/?" goto usage
if "%1" == "-?" goto usage
if "%1" == "" goto usage

set platform=
if "%1" == "intel" set platform=Win32
if "%1" == "x86" set platform=Win32
if "%1" == "alpha" set platform=Win32 (ALPHA)
if "%1" == "axp" set platform=Win32 (ALPHA)
if "%1" == "mips" set platform=Win32 MIPS
if "%1" == "powerpc" set platform=Win32 (PPC)
if "%1" == "ppc" set platform=Win32 (PPC)
if "%platform%" == "" set platform=Win32

set debug=
if "%2" == "debug" set debug=Debug
if "%2" == "retail" set debug=Release
if "%debug%" == "" set debug=Release

set force=
if "%3" == "force" set force=/a

set ptkplatform=%platform% %debug%
@echo Building for %ptkplatform%

rem DB-Library samples
cd  DBLib\C\Example1
nmake %force% /f Example1.mak cfg="Example1 - %ptkplatform%" all
cd ..\Example2
nmake %force% /f Example2.mak cfg="Example2 - %ptkplatform%" all
cd  ..\Example3
nmake %force% /f Example3.mak cfg="Example3 - %ptkplatform%" all
cd  ..\Example4
nmake %force% /f Example4.mak cfg="Example4 - %ptkplatform%" all
cd  ..\Example5
nmake %force% /f Example5.mak cfg="Example5 - %ptkplatform%" all
cd  ..\Example6
nmake %force% /f Example6.mak cfg="Example6 - %ptkplatform%" all
cd  ..\Example7
nmake %force% /f Example7.mak cfg="Example7 - %ptkplatform%" all
cd  ..\Example8
nmake %force% /f Example8.mak cfg="Example8 - %ptkplatform%" all
cd  ..\Nmpsdmp
nmake %force% /f Nmpsdmp.mak cfg="Nmpsdmp - %ptkplatform%" all
cd  ..\SQLCurs
nmake %force% /f SQLCurs.mak cfg="SQLCurs - %ptkplatform%" all
cd  ..\SQLExamp
nmake %force% /f SQLExamp.mak cfg="SQLExamp - %ptkplatform%" all
cd  ..\SQLTestC
nmake %force% /f SQLTestC.mak cfg="SQLTestC - %ptkplatform%" all
cd  ..\SQLTestN
nmake %force% /f SQLTestN.mak cfg="SQLTestN - %ptkplatform%" all
cd  ..\Textcopy
nmake %force% /f Textcopy.mak cfg="Textcopy - %ptkplatform%" all
cd  ..\Twophase
nmake %force% /f Twophase.mak cfg="Twophase - %ptkplatform%" all
cd ..\..\..

rem MSDTC samples
cd  MSDTC\DBLIB
nmake %force% /f DBLib.mak cfg="DBLib - %ptkplatform%" all 
cd  ..\ODBC
nmake %force% /f Odbc.mak cfg="Odbc - %ptkplatform%" all
cd ..\..

rem ODS samples
cd  ODS\Gateway
nmake %force% /f Gateway.mak cfg="Gateway - %ptkplatform%" all 
cd  ..\ODSODBC
nmake %force% /f ODSSamp.mak cfg="ODSSamp - %ptkplatform%" all 
cd  ..\PROCSRV
nmake %force% /f Procsrv.mak cfg="Procsrv - %ptkplatform%" all 
cd  ..\Xp
nmake %force% /f xp.mak cfg="xp - %ptkplatform%" all 
cd  ..\xp_dblib
nmake %force% /f xp_dblib.mak cfg="xp_dblib - %ptkplatform%" all 
cd  ..\xp_odbc
nmake %force% /f xp_odbc.mak cfg="xp_odbc - %ptkplatform%" all
cd ..\..

rem SQL-DMO samples
cd  SQLDMO\C\SOC
nmake %force% /f soc.mak cfg="soc - %ptkplatform%" all 
cd ..\..\CPP\Socpp
nmake %force% /f socpp.mak cfg="socpp - %ptkplatform%" all
cd ..\..\..

goto end

:usage
@echo Syntax:
@echo BUILDALL {intel or alpha or mips or powerpc} {debug or release} {force}
@echo.

:end
