---------------------------------------------------------
Microsoft(R) ActiveX(R) Data Objects version 2.0 Readme File
---------------------------------------------------------

(c) 1998 Microsoft Corporation. All rights reserved.

This document provides late-breaking or other information that supplements the Microsoft ADO documentation.

--------
CONTENTS
--------

1. PRODUCT DESCRIPTION
   
2. NEW FEATURES
2.1 Asynchronous Connection, Execution, Fetching, and Events
2.2 Data Shaping
2.3 Persistence
2.4 Fabricated Recordset Objects
2.5 Sort, Filter, and Find
2.6 ADO Extensions for VC++
2.7 ADO Support for Visual Analyzer (Microsoft Visual Studio(TM), Enterprise Edition Only)
2.8 Conflict Resolution for Client Cursors
2.9 Customizable DataFactory Behavior

3. TECHNICAL NOTES
3.1 Security Enhancements
3.2 Restrictive Behavior
3.3 Customizing Security Settings

4. KNOWN BUGS, LIMITATIONS, WORKAROUNDS, AND LATE-BREAKING DOCUMENTATION NOTES

----------------------
1. PRODUCT DESCRIPTION
----------------------

ActiveX Data Objects (ADO) is an Automation-based interface for accessing data. ADO uses the OLE DB interface to access a broad range of data sources, including but not limited to data provided via ODBC.

Users of RDO and DAO should quickly become comfortable with programming to ADO because the overall design of ADO comes from our experience in developing those interfaces.

Microsoft Remote Data Service (RDS) is a component of ADO that provides fast and efficient data connectivity and the data publishing framework for applications hosted in Microsoft Internet Explorer. It is based on a client/server, distributed technology that works over HTTP, HTTPS (HTTP over Secure Sockets layer), and DCOM application protocols. Using data-aware ActiveX controls, RDS provides data access programming in the style of Microsoft Visual Basic(R) to Web developers who need to build distributed, data-intensive applications for use over corporate intranets and the Internet.

---------------
2. NEW FEATURES
---------------

ADO 2.0 adds several new features for developers.

2.1 Asynchronous Connection, Execution, Fetching, and Events

As did RDO 2.0, ADO now supports asynchronous operations. Asynchronous operations allow you to cancel out of an extended operation or to continue processing while waiting for the connection to complete. Events notify you when an asynchronous operation has been completed. Asynchronous fetching is a feature specific to the client cursor (CursorLocation = adUseClient), which returns the first rows from a query result and then continues fetching in the background while you manipulate the rows that have already been fetched.

2.2 Data Shaping

In conjunction with the MSDataShape provider, ADO can expose data hierarchically. ADO can also expose grouping and aggregation over a recordset.

2.3 Persistence

You can now save a Recordset object right to your local hard drive and load it later (when working with client cursors). This allows you to connect to the server, execute a query, call rst.Save("myfilename"), shut down the computer, and later call rs.Open("myfilename",,,adCmdFile) and modify the data. 

2.4 Fabricated Recordset Objects

You can create Recordset objects in ADO 2.0 without executing a query against the data source. Just create a new Recordset object, append some Field objects, call rst.Open(), and you now have a Recordset object that you can append data to, remote, and treat just as if the Recordset object had been created from a query.

2.5 Sort, Filter, and Find

Allows you to manipulate results at the client when using client cursors.

2.6 ADO Extensions for VC++

Provides improved performance for VC++ users by enabling the use of native data types instead of Variants in C++ code.

2.7 ADO Support for Visual Analyzer (Microsoft Visual Studio, Enterprise Edition Only)

ADO works with Visual Analyzer, submitting events to help in analyzing performance.

2.8 Conflict Resolution for Client Cursors

Provides enhanced functionality for Recordset objects built with client-side cursors in two-tier scenarios. New functions, like Resync and Update, with conflict resolution are now supported on client cursors.

2.9 Customizable DataFactory Behavior

Implicit remoting behavior is customizable now via the DataFactory Handler object implementation. DataFactory handler can be used to customize the open and batchupdate behavior of Recordset objects opened via RDS. You have a choice of writing a new handler yourself or using the default handler (MSDFMAP.dll) that ships with RDS 2.0. The behavior of the default handler can be driven by editing the default INI file it uses -- MSDFMAP.INI.

------------------
3. TECHNICAL NOTES
------------------

3.1 Security Enhancements

This release includes security enhancements for ADO and RDS objects so that some of the operations are restricted when Internet Explorer is running in a "safe" mode.

3.1.1. Zones
You can set different security settings for different "zones" in Internet Explorer 4.0 to customize the behavior of ADO/RDS objects in those zones. The following four zones are defined in Internet Explorer 4.0:
*  Internet zone
*  Local intranet zone
*  Restricted sites zone
*  Trusted sites zone

3.1.2. Security Levels
For each of these zones, you can specify the security level to use. The following security levels are available for each zone:
*  High
*  Medium
*  Low
*  Custom

Like any other ActiveX controls, in order for ADO/RDS objects to work at all in Internet Explorer 4.0, the security level must be set to "Medium" or "High." Custom settings are used to set ADO/RDS objects to behave in safe or unsafe mode.

3.2 Restrictive Behavior

By default, any unsafe operations on ADO/RDS objects in Internet Explorer 4.0 will result in a user prompt when accessing pages from "Local trusted zone," "Trusted sites zone," and "Internet zone." Unsafe operations on ADO/RDS objects are disabled, by default, for pages loaded from "Restricted sites zone." The following describes ADO/RDS behavior when running in these modes:

3.2.1 Safe Objects
The following objects are considered "safe." This means that unsafe operations (detailed in 3.2.3) are disallowed in a safe environment (e.g., Internet Explorer, by default; unless custom settings are used to run in an unsafe mode) and allowed in an unsafe environment (e.g., Visual Basic).
a. RDS.DataControl object
b. RDS.DataSpace object
c. ADO Recordset object

3.2.2 Unsafe Objects
The following objects are considered "unsafe." They cannot be created directly or indirectly (and given to a user) when operating in a safe environment.
a. RDSServer.DataFactory object
b. ADO Connection object
c. ADO Command object

3.2.3 Unsafe Operations on Safe Objects
The following are considered unsafe operations on the "safe" objects -- RDS.DataControl, RDS.DataSpace, ADO Recordset. These operations are disallowed in a safe environment but allowed in an unsafe environment.

a. RDS.DataControl
i) All two-tier and DCOM scenarios on the RDS.DataControl object. This means that you cannot open database connections on your local machine or from servers to which you connect using the DCOM protocol.
ii) All three-tier operations over HTTP are restricted to the server from which the page has been downloaded. This means that the Server property on the RDS.DataControl object must be equal to the host name (http://server) from which the page has been downloaded.

b. RDS.DataSpace
i) All two-tier and DCOM scenarios on the RDS.DataSpace object. This means that you cannot use the RDS.DataSpace object to invoke business objects on your local machine or over the DCOM protocol.
ii) All three-tier scenarios over HTTP are restricted to the server from which the page has been downloaded. This means that the second parameter in the CreateObject method call on the DataSpace object must point to the same server from which the page has been downloaded.

c. ADO Recordset
i) Making any connection where provider is not MS Remote. So the connection string must start with "Provider=MS Remote". The "Remote Server" tag in the connection string must also be the same name as the server from which the page has been downloaded. Local two-tier and DCOM connections are not allowed.
ii) Local Persistence operations, like saving a recordset to the local filesystem and opening a recordset from file on the local machine.

3.3 Customizing Security Settings

ADO/RDS behavior is controlled by the setting for the "Initialize and script ActiveX controls not marked as safe" option. You can change the security settings by changing the security level for a specific zone. Default settings for the "Initialize and script ActiveX controls not marked as safe" option for the intranet zone are as follows:
Security level = High		Value = "Disable"
Security level = Medium		Value = "Disable"
Security Level = Low		Value = "Prompt"

For default settings in other security zones, please refer to the documentation for Internet Explorer.

You can override the default settings by directly manipulating the custom settings for the above option. You can choose to completely disable the unsafe operations (described above), or specify that a warning be displayed whenever such an operation is attempted, or enable such an operation without any warning. You can set different custom settings for different security zones. The following steps must be taken to customize your security settings for a specific security zone:

CAUTION: Please be aware that by enabling "Initialize and script ActiveX controls not marked as safe" (step 5 below), you are allowing ANY ActiveX control, safe or unsafe, to be used from within Web pages (which potentially exposes user machines to malicious controls or malicious scripting code). It is recommended that you should do this only in the "intranet" or "Trusted Sites" Security Zones and not on the "Internet" zone.

1. From the View menu in Internet Explorer 4.0, select Internet Options to bring up the Internet Options dialog box. Select the Security tab.
2. From the Zone drop-down list, select the zone that you want to customize settings for.
3. Select Custom for the selected zone. This enables the Settings button on the dialog box.
4. Click Settings to bring up the Security Settings dialog box.
5. If you want to enable unsafe operations (described in 3.2.3) on ADO/RDS objects without any warning being displayed, select "Enable" for the option "Initialize and script ActiveX controls not marked as safe" in the Security Settings dialog box. Click OK.
6. If you want a warning to be displayed whenever an unsafe operation (described in 3.2.3) on ADO/RDS objects is attempted, select "Prompt" for the option "Initialize and script ActiveX controls not marked as safe" in the Security Settings dialog box. Click OK.
7. If you want to completely disable unsafe operations (described in 3.2.3) on ADO/RDS objects, select "Disable" for the option "Initialize and script ActiveX controls not marked as safe" in the Security Settings dialog box. Click OK.
8. If appropriate, repeat these steps to customize the security settings for other security zones.
9. Click OK.

Now ADO/RDS objects will behave in specified custom mode. These settings affect the following behavior of ADO/RDS objects (as described in 3.2.3) in the specified security zone -- opening local two-tier connections; working over DCOM; connecting to a server other than the one from which the page was originally downloaded; saving and opening a recordset to/from files on the local machine.

If you set your custom options to "Prompt", the following warning is displayed when an unsafe operation is attempted on ADO/RDS objects:

"The page is accessing a data source on another domain. Do you want to allow this?" The user has the option of replying "Yes" or "No". If the reply is "Yes", the operation is completed; otherwise it fails.

--------------------------------------------------
4. KNOWN BUGS, LIMITATIONS, WORKAROUNDS, AND LATE-BREAKING DOCUMENTATION NOTES
--------------------------------------------------

4.1 Client impersonation in RDS is not currently supported due to missing support from the operating system.

4.2 When using adUseClient or remoting against SQL Server 6.5 Service Pack 4, using the DISTINCT keyword in queries will be ignored for updatable result sets. This is a SQL Server issue and should be resolved in a future service pack.

4.3 When creating "Virtual Servers" in Internet Information Server 4.0, the following two extra steps are needed in order to configure the server to work with RDS:

A) When setting up the server, check "Allow Execute Access."
B) Move msadcs.dll to vroot\msadc, where vroot is the home directory of your virtual server.

4.4 When using the Recordset.Save method, for best results use CursorLocation=adUseClient. Some OLE DB providers do not support all of the functionality necessary to support the saving of recordsets, and the client cursor can be used in order to supply that functionality.

4.5 ADO Events 

The titles for WillMove and MoveComplete, WillChangeField and FieldChangeComplete, WillChangeRecord and RecordChangeComplete,  WillChangeRecordset and RecordsetChangeComplete, and EndOfRecordset all list these as Connection Events. However these are Recordset events.

4.5.1 WillConnect
The description in documentation for the Options parameter to the WillConnect event is incorrect. The only valid option is adOpenAsync. 

The documentation for the WillConnect event states that the pConnection parameter can be changed.  This is incorrect; the pConnection parameter cannot be modified with an event handler.

4.5.2 ConnectComplete and Disconnect

adStatus will always return adStatusOK for these events -- the documentation states that these could also return adStatusErrorsOccurred (which is incorrect).

The description for the adStatus parameter also states to "set this parameter to adStatusUnwantedEvent to prevent subsequent notifications."  However, closing and reopening a connection causes and events that have been "turned off" in this manner to start firing again.

4.5.3 WillExecute
The description in documentation for the CursorType parameter states that "this parameter cannot be changed if it is set to adOpenUnspecified when this method is called." This is not correct. No matter what the parameter value coming in, it can be changed. If the operation that caused the event was not recordset open then it will be ignored.

The description in documentation for the LockType parameter states that "this parameter cannot be changed if it is set to adLockUnspecified when this method is called."  This is not true; this parameter can be changed no matter what the incoming value is. Again, if recordset open did not fire the event, it will be ignored.

The remark in documentation that "the corresponding pConnection, pCommand, or pRecordset parameter will be set to the object causing the event and the remaining two will be set to Nothing" is incorrect. This event will always have a pConnection object reference.

4.5.4 InfoMessage
The description in documentation for the pError parameter states that "it describes the error that occurred if the value of the adStatus is adStatusErrorsOccurred; otherwise it is not set." This is incorrect -- this event is fired anytime a warning is returned. In that case, the status for this event is set to adStatusOK and the pError object contains the warning.

The description in documentation for adStatus parameter states that "this parameter is set to adStatusOK if the operation that caused the event was successful, or adStatusErrorsOccurred if the operation failed." This event, however, is fired for warnings; the operation can never "fail," and the status will never be adStatusErrorsOccurred.

The description for the pConnection parameter states that this connection object reference is to "the connection on which the command executed."  Warnings can also occur on other types of operations, such as opening a connection.

4.5.5 WillMove and MoveComplete
In the Remarks section, the following Recordset operations can also cause these events to be fired: Filter, AbsolutePage, AbsolutePosition.  It will also fire if the child recordset has recordset events connected and the parent recordset moves. Also, Delete will NOT fire these events.

4.5.6 WillChangeRecord and RecordChangeComplete
In the remarks section, it should be noted that these events will occur for the first changed field of a row.

4.6 The ADO/RDS documentation refers to a property named URL on the RDS.DataControl object. This property does not exist in the released version of the RDS 2.0 component.

4.7 Asynchronous Fetching is available in ADO 2.0 when using CursorLocation=adUseClient.  There are two ways to turn this on -- one via the Options parameter to Recordset.Open, and another via the Recordset Properties Collection "Asynchronous Rowset Processing" property.  For best results, always use the Recordset.Open parameter.  Not using the parameter can cause the loss of ADO background fetch related events.  Additionally, background fetching using Provider="MS Remote" is not supported through the properties collection -- only via the Recordset.Open parameter.

4.8 When ADO is returning "output" or "return" parameter values to the user from a datasource, ADO will only read the values once from the provider. This means that if the user reads the values before they are ready, they may not be retrieved.

A primary case for this is exhibited by the following code:

Sub params()
Dim conn As New Connection
Dim cmd As New Command
Dim rs As Recordset

conn.Open "pubs", "sa", ""
'conn.Open "provider=sqloledb;data source=sqlserver;user id=sa;password=;initial catalog=pubs"
conn.Execute "DROP PROC test_proc"
conn.Execute "CREATE PROCEDURE test_proc as SELECT * from authors RETURN 1"
Set cmd.ActiveConnection = conn
cmd.CommandText = "test_proc"
cmd.CommandType = adCmdStoredProc
cmd.Parameters.Append cmd.CreateParameter("RetVal", adInteger, adParamReturnValue)

Set rs = cmd.Execute()
Debug.print rs(0)

'Accessing the parameter value before the recordset has been closed on a forward-only, read-only cursor on Microsoft SQL Server will result in the parameter value being retrieved before it's available. Referring to the parameter only after the recordset was closed (instead of before and after) will retrieve the correct parameter value.

Debug.Print "Return Val : "; cmd(0)
rs.Close
Debug.Print "Return Val : "; cmd(0)
conn.Close

End Sub

4.9 When using CursorLocation=adUseClient, the Recordset.Resync() method is available only for non-read-only Recordset objects.

4.10 In order to use ADO 2.0 FetchProgress and FetchComplete Events with Visual Basic, at least Visual Basic version 6 is required.

4.11 When using Events in ADO against a provider which does not support bookmarks, the user will receive a RecordsetChanged notification each time ADO is required to fetch new rows from the OLE DB provider. The frequency with which this occurs is directly dependent on the Recordset.CacheSize property.

4.12 When using RDS on an IIS server, the number of threads created per processor can be controlled by manipulating the registry on the Web server.  The number of threads per processor can affect performance in a high traffic situation, or in low traffic but large query size scenarios. The user should experiment for best results. The specific value to be adjusted is:

HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\W3SVC\Parameters\ADCThreads

where ADCThreads is a user added REG_DWORD in the range 1-50. Default is 6, and invalid values default to either 6 or 50. The user will need to create this registry value; it is not included in the registry by default.

4.13 There are some columns in the Recordset objects returned from OpenSchema on the Connection object that are of a type that cannot be compared to other variables in Visual Basic. These are columns that have a corresponding OLE DB datatype of DBTYPE_UI4. See the OLE DB specification for those columns in schema rowsets that have this type.

4.14 When using the OpenSchema method on the ADO Connection object, it is possible to restrict the results returned by using the second parameter to the function.  This parameter contains an array of variant values and can specified in VBA as:

Dim criteria(3) As Variant

criteria(0) = "pubs"		' Use the "pubs" database on the SQL Server
criteria(1) = Empty		' No restriction on the schema/owner
criteria(2) = Empty		' No restriction on the table name
criteria(3) = "table"		' Only objects of type "table" are returned.
Set rs = cnn.OpenSchema(adSchemaTables, Criteria)

4.15 In ADO, the RecordCount property of the Recordset object may not always be supported by the provider or specific cursor type being used. In those cases in which the provider or cursor type doesn't support RecordCount, -1 will be returned as the value.

4.16 Running Code Examples
You must select the entire code example in order to preserve the paragraph formatting for each line of code. Otherwise, the paragraphs will be ignored when you paste the code into the program window and the code won't run.

4.17 In the documentation for the topic "Shape Append Command," the syntax should be shown as follows:
SHAPE {parent command}
APPEND {child command} [AS] table-alias
RELATE (parent column TO child column)

4.18 In the documentation for the topic "Accessing Rows in a Hierarchical Recordset," the line of code in step 3 should be as follows:

Set rstChapter = rst("chapter").Value

4.19 In the documentation for the topic "Step4: Manipulate the data (ADO Tutorial)," the sample code refers to the Optimize property on the Field object. This is slightly incorrect -- the Optimize property is found in the Properties collection of the Field object when using CursorLocation=adUseClient or a disconnected Recordset object. Sample usage is as follows:

rs("au_lname").properties("Optimize") = True

4.20  The documentation for the StayInSync property says that the property "indicates, in a hierarchical Recordset object, whether the parent row should change when the set of underlying child records (that is, a chapter) changes."

This is incorrect. The property controls whether or not a reference to a child recordset will change as the user navigates through the parent recordset (the default is True.)

The documentation also states that the property "sets or returns a Boolean value. If set to True, the parent Recordset object will be updated if the chapter changes; if False, the parent Recordset object will continue to refer to the previous chapter."

This is incorrect. If the property is True, the child recordset stays in sync -- navigating through the parent recordset changes the data shown in the reference to the child recordset. If the property is False, a reference to a child recordset will continue to contain information for that particular chapter even as the user navigates through the parent recordset.

4.21 The code in the sample in the "Accessing rows in a Hierarchical Recordset" help topic is incorrect.

The rsChapter object should be dimensioned as an ADODB.Recordset object rather than a variant, and it should retrieve the chapter from the parent recordset with code such as the following:

        Set rsChapter = rst("chapter").Value

4.22 The help for the "WillChangeRecordset and RecordsetChangeComplete (ConnectionEvent) Methods" topic states, "A WillChangeRecordset or RecordsetChangeComplete event may occur due to the following Recordset operations: Requery, Resync, Close, Open, and Filter." This is incorrect. Filter and Close do not issue this event.

4.23 The help for the "WillMove and Move Complete (ConnectionEvent) Methods" suggests that the WillMove event will be issued for Resync.  This is incorrect; Resync does not issue this event.
