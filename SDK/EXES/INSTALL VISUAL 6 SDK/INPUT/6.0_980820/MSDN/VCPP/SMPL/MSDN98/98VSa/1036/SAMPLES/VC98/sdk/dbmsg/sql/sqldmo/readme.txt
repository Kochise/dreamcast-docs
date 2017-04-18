****************************************************************
         MICROSOFT SQL SERVER WORKSTATION SYSTEM 6.5 
 SQL DISTRIBUTED MANAGEMENT OBJECTS (SQL-DMO) SAMPLE PROGRAMS
****************************************************************
This file describes the SQL-DMO sample programs included with
Microsoft(R) SQL Server(TM) 6.5 and Microsoft SQL Server 
Workstation System 6.5.

For additional information about SQL Server 6.5, SQL Distributed
Management Objects, and ODBC, see the "What's New in SQL Server 6.5,"
"Programming SQL Distributed Management Objects," and "Programming 
ODBC for SQL Server" sections of SQL Server Books Online, which 
contains the most up-to-date information available.

****************************************************************
32-BIT VISUAL BASIC SAMPLES

The following 32-bit Microsoft(R) Visual Basic(R)-based sample 
programs are located in the C:\MSSQL\SAMPLES\SQLDMO\VB directory 
by default:

EXPLORE
Sample SQL-DMO object browser using 32-bit Visual Basic. Includes 
the following files:
    EXPLORE.MAK
    EXPLORE.FRM
    EXPLORE.BAS

GENERIC
Sample SQL-DMO generic program using 32-bit Visual Basic. Includes 
the following files:
    GENERIC.MAK
    GENERIC.FRM

****************************************************************
32-BIT VISUAL C++ SAMPLES

The following 32-bit C++ sample program is located in the
C:\MSSQL\SAMPLES\SQLDMO\C\CPP directory by default:

SOCPP
Sample C++ program using 32-bit Visual C++. Includes the following 
files:
    SOCPP.MAK
    SOCPP.CPP
    SOCPP.MDP

The following 32-bit C sample program is located in the
C:\MSSQL\SAMPLES\SQLDMO\C\CPP directory by default:

SOC
Sample C program using 32-bit Visual C++. Includes the following 
files:
    SOC.MAK
    SOC.C
    SOC.MDP

Each project on the Intel(R) platform includes Visual C++ 4.0 
workspace files (.MDP). Double-click on the workspace file to load 
the workspace and make file into the Developer Studio environment.

Each project also contains cross-platform native Visual C++ 4.0 make 
files (.MAK). For each 32-bit project the .MAK file contains Intel, 
Alpha AXP(R), MIPS(R), and PowerPC(TM) build information. When the 
project is loaded into Developer Studio, pick the appropriate target, 
for example "Example1 - Win32 (ALPHA) Debug", and build it.

You can also build from the command line. BUILDALL.BAT, a file that 
will build all of the 32-bit PTK samples, is in the samples directory. 
Use the following syntax: 

BUILDALL ({intel | alpha | mips | powerpc} {debug | release} {force})

To use these samples with Visual C++ 4.0, you need to ensure that 
your Library and Include directory settings point to your own 
directories. To do this using Developer Studio, from the Tools menu, 
choose Options, then click the Directories tab. From the "Show 
directories for" box, choose Include files and Library files, and 
ensure that these directories (as appropriate) are included:

	Include files:			Library files:
	C:\MSSQL\DBLIB\INCLUDE		C:\MSSQL\DBLIB\LIB
	C:\MSSQL\MSDTC\INCLUDE		C:\MSSQL\MSDTC\LIB
	C:\MSSQL\ODBD\INCLUDE		C:\MSSQL\ODS\LIB
	C:\MSSQL\ODS\INCLUDE
	C:\MSSQL\SQLOLE\INCLUDE

