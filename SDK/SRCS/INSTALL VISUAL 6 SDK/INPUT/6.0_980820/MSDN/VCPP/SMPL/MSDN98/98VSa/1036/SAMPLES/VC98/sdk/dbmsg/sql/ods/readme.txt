****************************************************************
          MICROSOFT SQL SERVER WORKSTATION SYSTEM 6.5
              OPEN DATA SERVICES SAMPLE PROGRAMS
****************************************************************
This file describes the Open Data Services sample programs 
included with Microsoft(R) SQL Server(TM) Workstation System 6.5.

For additional information about SQL Server 6.5, Open Data Services,
and ODBC, see the "What's New in SQL Server 6.5," "Programming 
Open Data Services," and "Programming ODBC for SQL Server" sections
of SQL Server Books Online, which contains the most up-to-date 
information available.

****************************************************************
OPEN DATA SERVICES SAMPLE APPLICATIONS

The following 32-bit C sample programs are located in the
C:\MSSQL\SAMPLES\ODS directory by default:

GATEWAY
Sample C gateway application that connects to SQL Server as an
alternate data source and demonstrates a "pass through" application. 
Includes the following files:
    GATECBS.C
    GATEWAY.C
    GATEWAY.MAK
    GATEWAY.MDP

ODSODBC
Builds an Open Data Services gateway version of the SQL Server ODBC 
driver that can be customized for the capabilities of a particular 
Open Data Services gateway application. Documented in Appendix E of 
"Programming Open Data Services." To build a 16-bit version of the
SQL Server ODBC driver, refer to 
C:\MSSQL\SAMPLES\ODS\ODSODBC\README.TXT. Includes the following files:
    BUILDW16.BAT
    LIBMAIN.C
    LOCAL.RC
    MAKEFILE.W16
    ODBCSS.H
    ODBCVER.H
    ODXRC.H
    ODSSAMP.MAK
    ODSSAMP.MDP
    README.TXT
    SAMP.RC    

PROCSRV
Demonstrates how to implement a procedure server using Open Data 
Services to handle specific pre-defined requests. Includes the 
following files:
    PROCSRV.C
    PROCSRV.MAK
    PROCSRV.MDP
    SALES.DBF
    SERVICE.C

XP
Sample extended procedure DLL built with Open Data Services. The 
functions within the DLL can be invoked by using the extended
stored procedures support in SQL Server.  To register the functions 
and allow all users to use them, run the Transact-SQL script 
INSTXP.SQL. Includes the following files:
    INSTXP.SQL
    XP.C
    XP.DEF
    XP.MAK
    XP.MDP

XP_DBLIB
Sample extended stored procedure using 32-bit Visual C++ and the 
DB-Library interface to open a new connection to the SQL Server 
that called the extended stored procedure. Returns a result set and 
passes the results to the client. Uses a bound session for the 
loopback connection.
    XP_DBLIB.C
    XP_DBLIB.DEF
    XP_DBLIB.MAK
    XP_DBLIB.MDP
    XP_DBLIB.SQL

XP_ODBC
Sample extended stored procedure using 32-bit Visual C++ and the 
ODBC interface to open a new connection to the SQL Server that 
called the extended stored procedure. Returns a result set and 
passes the results to the client. Uses a bound session for the 
loopback connection. Note: To connect to the server using integrated 
security, the local server data source name (registered using ODBC 
in the Control Panel) must be used. Includes the following 
files:
    XP_ODBC.C
    XP_ODBC.DEF
    XP_ODBC.MAK
    XP_ODBC.MDP
    XP_ODBC.SQL

Each project on the Intel(R) platform includes Visual C++ 4.0 
workspace files (.MDP). Double-click the workspace file to load 
the workspace and make file into the Developer Studio environment.

Each project also contains cross-platform native Visual C++ 4.0 make 
files (.MAK). For each 32-bit project the .MAK file contains Intel, 
Alpha AXP(R), MIPS(R), and PowerPC(TM) build information. When the 
project is loaded into Developer Studio, pick the appropriate target, 
for example "Example1 - Win32 (ALPHA) Debug", and build it.

You can also build from the command line. BUILDALL.BAT, a file that 
will build all of the 32-bit PTK samples, is in the samples 
directory. Use the following syntax: 

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
	C:\MSSQL\ODBC\INCLUDE		C:\MSSQL\ODS\LIB
	C:\MSSQL\ODS\INCLUDE
	C:\MSSQL\SQLOLE\INCLUDE

