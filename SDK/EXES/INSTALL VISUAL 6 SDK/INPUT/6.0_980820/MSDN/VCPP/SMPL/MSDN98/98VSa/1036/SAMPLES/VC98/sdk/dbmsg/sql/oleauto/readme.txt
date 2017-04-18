****************************************************************
          MICROSOFT SQL SERVER WORKSTATION SYSTEM 6.5
                OLE AUTOMATION SAMPLE PROGRAMS
****************************************************************
This file describes the OLE automation sample programs included 
with Microsoft(R) SQL Server(TM) Workstation System 6.5.

For additional information about SQL Server 6.5, DB-Library, and 
ODBC, see the "What's New in SQL Server 6.5," "Programming 
DB-Library for Visual Basic," and "Programming ODBC for SQL 
Server" sections of SQL Server Books Online, which containsthe 
most up-to-date information available.

****************************************************************
OLE AUTOMATION SAMPLE APPLICATIONS

The sample applications require the Microsoft(R) Visual Basic(R) 4.0 
Enterprise Edition. The following Visual Basic sample programs and 
Transact-SQL scripts are located in the C:\MSSQL\SAMPLES\OLEAUTO 
directory by default:

GETNPV
Demonstrates the use of an OLE Automation object to call an NPV 
function in Visual Basic from a trigger. Includes the following 
files:
    CGETNPV.CLS
    GETNPV.VBP
    NPVMAIN.BAS
    NPVTEST.SQL
    NPVTRIG.SQL
    TESTERR.SQL

To run this application
1.  Create the test table and trigger by running the NPVTEST.SQL 
    script.
2.  Open the Visual Basic project, GETNPV.VBP. From the File Menu 
    choose Make EXE file or Make OLE DLL file to compile GETNPV.VBP.
3.  Run the script, NPVTEST.SQL to insert sample data into the table. 
    The trigger then fires and calls the Visual Basic NPV function.
4.  Run the script, TESTERR.SQL, to show an example of the VB 
    function raising a custom error message that can be retrieved by 
    calling sp_OAGetErrorInfo.

LOOPBACK.DAO
Demonstrates connecting back to a SQL Server via an OLE Automation
object. The OLE Automation server retrieves a result set from a SQL 
Server table and returns it to the stored procedure that called it. 
In the Visual Basic project, if you make an OLE DLL file, the OA 
server that is created will run in the same process space as SQL 
Server. If you make an EXE file, the OA server will run as a separate 
process. Includes the following files:
    CSQLDAO.CLS
    DAOMAIN.BAS
    LOOPDAO.SQL
    SQLDAO.VBP

LOOPBACK.RDO
Demonstrates connecting back to a SQL Server via an OLE Automation
object. The OLE Automation server retrieves a result set from a SQL 
Server table and returns it to the stored procedure that called it. 
In the Visual Basic project, if you make an OLE DLL file, the OA 
server that is created will run in the same process space as SQL 
Server. Ifyou make an EXE file, the OA server will run as a separate 
process. Includes the following files:
    CSQLRDO.CLS
    LOOPRDO.SQL
    RDOMAIN.BAS
    SQLRDO.VBP

TRAVERSE
Transact-SQL script that demonstrates how to use traversal syntax 
for object hierarchies. Uses the SQL-DMO administration objects. 
Includes the following file:
    TRAVERSE.SQL
    
    
