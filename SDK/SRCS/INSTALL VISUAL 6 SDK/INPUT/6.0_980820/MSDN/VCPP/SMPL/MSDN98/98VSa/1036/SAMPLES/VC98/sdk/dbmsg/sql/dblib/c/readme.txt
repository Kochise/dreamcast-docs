****************************************************************
         MICROSOFT SQL SERVER WORKSTATION SYSTEM 6.5
              DB-LIBRARY FOR C SAMPLE PROGRAMS
****************************************************************
This file describes the DB-Library for C sample programs included
with Microsoft(R) SQL Server(TM) Workstation System 6.5.

For additional information about SQL Server 6.5, DB-Library for C,
and ODBC, see the "What's New in SQL Server 6.5," "Programming 
DB-Library for C," and "Programming ODBC for SQL Server" sections
of SQL Server Books Online, which contains the most up-to-date 
information available.

****************************************************************
DB-LIBRARY FOR C SAMPLE APPLICATIONS

The DB-Library for C sample program files are stored as projects
in their own directories. The following DB-Library sample projects 
are targeted to specific client operating systems: Microsoft(R) 
Windows NT(R) and Microsoft Windows(R) 95 for Intel(R), MIPS(R), 
Alpha AXP(R), and PowerPC(TM) platforms; Microsoft Windows and 
MS-DOS(R) for Intel. Each of these samples has an associated make 
file for building with the NMAKE utility:

****************************************************************
DB-LIBRARY FOR C SAMPLE 32-BIT APPLICATIONS

Windows NT for Intel, Alpha AXP, MIPS, and PowerPC platforms

Project directories are located in the following path:

     C:\MSSQL\SAMPLES\DBLIB\C

     EXAMPLE1    Sending queries in a command batch
     EXAMPLE2    Working with data files
     EXAMPLE3    Binding aggregate and compute results
     EXAMPLE4    Using row buffering
     EXAMPLE5    Converting data with dbconvert
     EXAMPLE6    Querying and updating the database
     EXAMPLE7    Using browse-mode functions
     EXAMPLE8    Using remote stored procedures and return 
		 parameters
     NMPSDMP     Windows NT-based console named pipe dump device 
		 sample
     SQLCURS     Using cursor functions
     SQLEXAMP    Command-line interpreter
     SQLTESTC    Windows NT-based console sample 
     SQLTESTN    Windows NT-based GUI sample
     TEXTCOPY    Windows NT-based console text and image sample, 
		 also uses GETOPT.*
     TWOPHASE    Two-phase commit example

     DATAFILE    Data file used by the EXAMPLE2 and EXAMPLE 6 
		 programs.

Each project on the Intel platform includes Visual C++ 4.0 
workspace files (.MDP). Double-click the workspace file to load 
the workspace and make file into the Developer Studio environment.

Each project also contains cross-platform native Visual C++ 4.0 make 
files (.MAK). For each 32-bit project the .MAK file contains Intel, 
Alpha, MIPS, and PowerPC build information. When the project is 
loaded into Developer Studio, pick the appropriate target, for 
example "Example1 - Win32 (ALPHA) Debug", and build it.

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
	C:\MSSQL\ODBC\INCLUDE		C:\MSSQL\ODS\LIB
	C:\MSSQL\ODS\INCLUDE
	C:\MSSQL\SQLOLE\INCLUDE

****************************************************************
DB-LIBRARY FOR C SAMPLE 16-BIT APPLICATIONS

16-bit Windows project directories are located in the following path:

	C:\MSSQL\SAMPLES\DBLIB\C\WIN16

    SQLTEST3      Windows-based sample
    SQLCURSW      Windows-based cursor sample

    SQLTEST.ICO   Icon used by both Windows-based samples

The MS-DOS project directory is located in the following path:

	C:\MSSQL\SAMPLES\DBLIB\C\MSDOS

    SQLTESTR      MS-DOS-based sample

Visual C++ 1.5x batch and make files are included to build all of 
these cross-platform samples on a given platform. Use "?" to display 
options:

    BUILDR.BAT    Builds the examples for MS-DOS
    BUILDR.MAK
    BUILDBOR.BAT  Builds the examples for MS-DOS using Borland C
    BUILDBOR.MAK



