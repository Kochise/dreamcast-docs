-----------------------------------------------------------
Microsoft(R) OLE DB Provider for Jet version 3.52 Readme File
-----------------------------------------------------------

(c) 1998 Microsoft Corporation. All rights reserved.

This document provides late-breaking or other information that supplements the Microsoft OLE DB Provider for Jet documentation.

--------
CONTENTS
--------

1. PRODUCT DESCRIPTION
   
2. NEW FEATURES
   
3. TECHNICAL NOTES

4. KNOWN BUGS, LIMITATIONS, AND WORKAROUNDS

----------------------
1. PRODUCT DESCRIPTION
----------------------
The Microsoft OLE DB Provider for Jet is a native OLE DB provider for data stored in the .mdb file format used by Microsoft Access. With this native OLE DB provider, you no longer have to rely on the Microsoft Access ODBC Driver to read and write data in a Microsoft Access database.

---------------
2. NEW FEATURES
---------------
With this release of the Microsoft OLE DB Provider for Jet, you can use ANSI standard syntax with respect to parameter markers in queries. Previous versions of this provider supported only the Microsoft Jet-specific parameter marker syntax consisting of a parameter name enclosed in square brackets, where the parameter name is optional.

Example: parameters parm1 text; select * from Table1 WHERE col1 = [parm1];

This version of the provider also supports the ANSI syntax, where a question mark, "?", is the parameter marker -- e.g., "...WHERE col1 = ?". 

Also with this release of the Microsoft OLE DB Provider for Jet, Jet-specific syntax for wildcards ("*" and "?") has been replaced by ANSI syntax for wildcards ("%" and "_"). For example, consider a query that would return all instances where the data for a column started with the letter "A". Previously, the restriction would have been written "...WHERE col1 LIKE("A*")" but now would be written "...WHERE col1 LIKE("A%")".  Please note that queries using the older, non-ANSI syntax will no longer return the same set of rows.

------------------
3. TECHNICAL NOTES
------------------
If you have previously created OLE DB applications to access your Microsoft Access .mdb files, your applications used the Microsoft Access ODBC Driver. However, you may now be able to create more efficient applications with the Microsoft OLE DB Provider for the Microsoft Access Jet database engine. 

With the new functionality provided by the Microsoft OLE DB Provider for Jet, you can bypass the Open Database Connectivity (ODBC) layer when accessing your Microsoft Access database files. This means that you do not need to create a Data Source Name (DSN) file, which ODBC uses for mapping data sources to underlying database software. 

To connect to a Microsoft Access database, you previously had to create and reference a DSN in your scripts.  For example, the following script establishes a connection with a Microsoft Access database:

Set cnnConn = Server.CreateObject("ADODB.Connection")
cnnConn.Open "DSN=PayRollData;UID=SnrAccnt;pwd=Accnt1"

However, with the Microsoft OLE DB Provider for Jet, you can directly access your Microsoft Access database files.  The following opens a database connection without referencing a DSN:

ADOConnection.Provider = "Microsoft.JET.OLEDB.3.51"
ADOConnection.Properties("user id") = "admin"
ADOConnection.Properties("password") = ""
ADOConnection.Properties("data source") = "d:\payroll\raises.mdb"
ADOConnection.Open

Your applications that use the Microsoft Access ODBC Driver will continue to be supported. However, you may choose to convert your existing applications from the Microsoft Access ODBC Driver to the Microsoft OLE DB Provider for Jet.   

If you need to access secure databases through the Microsoft OLE DB Provider for Jet, you may have to set additional information to what is listed above.  To specify a database password (as opposed to a user password), you need to set the property "Jet OLEDB:Database Password" on the ADO connection object (as above).  Furthermore, if you need to specify a specific system database, you should use the property "Jet OLEDB:System database".

Please note that the default mode for opening databases in the Microsoft OLE DB Provider for Jet is read-write.  If your .mdb file is on a read-only file system, you will get a failure if you try to open the database using the default settings.  You can open these databases only in the read-only mode.

-------------------------------------------
4. KNOWN BUGS, LIMITATIONS, AND WORKAROUNDS
-------------------------------------------
If you choose to convert your applications, you must be aware of the functionality differences between the two providers' access methods.  Specifically, for this release, the Microsoft OLE DB Provider for Jet does not support the following:

* The ODBC specified canonical syntax for invoking intrinsic functions.
* Access to databases or files other than native Microsoft Jet databases (e.g., Excel, dBase, Text, etc.) via Microsoft Jet installable ISAMs.
* The ability to create stored queries, sometimes referred to as stored procedures.

Installable ISAM Support

There is currently no support for accessing data other than native Jet data when using the Microsoft OLE DB Provider for Jet directly.  If it is imperative that you access external data from your application, you can -- and should -- continue to use the Microsoft OLE DB Provider for ODBC data until the next release of the Microsoft OLE DB Provider for Jet data.  This provider will be available with the MDAC 2.1 release.

Stored Procedure Support

Stored procedures must first be created in Access as Querydefs to be exercised by the Microsoft OLE DB Provider for Jet.  There is no facility to create the stored procedures directly from code for this release.


The following is a list of Microsoft OLE DB Provider for Jet 3.52 known bugs.

IRowsetUpdate::GetOriginalData will fail on a newly inserted row while change is pending.
-----------------------------------------------------------------------------------------
IRowsetUpdate::GetOriginalData will fail on a newly inserted row while the pending change is outstanding. The Jet 3.5 Engine itself will not handle the case where you try to retrieve the original values for newly inserted columns, hence the OLE DB provider cannot support this functionality.

Rowset Properties subject to change by JET.
-------------------------------------------
For Jet 3.52, the properties that you set prior to creating a rowset may be altered in order to reflect the actual attributes of the returned rowset for conditions that force a deviation. An example of this would be setting DBPROP_BOOKMARK property to VT_FALSE (along with DBPROPOPTIONS_REQUIRED) using ICommand::SetProperties or IOpenRowset::OpenRowset and then getting back a rowset that actually has bookmarks due to the type of rowset Jet was forced to create. Rather than failing to return a rowset at all, Jet will return it with different properties. 

A practical impact of this would be that some OLEDB APIs will return extra information.  For example, IColumnsInfo::GetColumnsInfo might return an unexpected, extra entry for the bookmark column.

