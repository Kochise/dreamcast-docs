---------------------------------------------------------
Microsoft Data Access SDK version 2.0 Readme 
---------------------------------------------------------

(c) 1998 Microsoft Corporation. All rights reserved.

This document provides late-breaking or other information that supplements the Microsoft Data Access SDK documentation.

--------
CONTENTS
--------

1. DATA ACCESS SDK TECHNICAL NOTES

2. DATA ACCESS SDK KNOWN BUGS, LIMITATIONS, AND WORKAROUNDS

3. CONFORMANCE TESTING 2.0 RELEASE NOTES

------------------
1. DATA ACCESS SDK TECHNICAL NOTES
------------------

1.0 DA SDK Release Notes

This file, DASDKReadme.txt, contains technical notes, information on bugs and workarounds, and information too late to include in the documentation for the Data Access SDK and for Conformance Testing. 

There are five other readme files associated with the Data Access SDK:

*  OLreadme.txt: The release notes for OLE DB.
*  ODreadme.txt: The release notes for ODBC.
*  OSreadme.txt: The release notes for OLE DB Simple Provider (OSP).
*  TEreadme.txt: The release notes for OLE DB for OLAP.
*  ACreadme.txt: The release notes for ActiveX Control Writer.

In addition, the release notes for each of the Microsoft Data Access Components can be found in the following locations:
*  ADO and RDS 2.0
     <drive>:\Program files\Common files\System\ADO\ADOreadme.txt
*  RDS 1.1
     <drive>:\Program files\Common files\System\MSADC\Doc11\RDS11readme.txt
*  OLE DB Provider for ODBC
     <drive>:\Program files\Common files\System\OLE DB\MSDASQLreadme.txt
*  SQL ODBC Driver
     <drive>:\<windir>\<system>\SQLSRdMe.txt
*  SQL OLE DB Provider
     <drive>:\Program files\Common files\System\OLE DB\SQLOLEDB.txt
*  Oracle ODBC Driver
     <drive>:\<windir>\<system>\MsOracle32Readme.txt
*  Oracle OLE DB Provider
     <drive>:\Program files\Common files\System\OLE DB\MSOrclOLEDBreadme.txt
*  Jet OLE DB Provider
     <drive>:\Program files\Common files\System\OLE DB\JoltReadme.txt
*  Visual FoxPro ODBC Driver
     <drive>:\<windir>\<system>\Vfpodbc.txt
*  OLE DB Service Components
     <drive>:\Program files\Common files\System\OLE DB\Msdasc.txt

1.1 Drivers, MDAC, Internet Explorer Must Be Installed on the System

The Data Access SDK assumes that the SQL Server ODBC Driver and the Microsoft Desktop Database Driver are already installed in the system. If they are not, an error will be reported when the SDK tries to create Sample DSN to these drivers.

The Data Access SDK delivered with Visual Studio requires that the Microsoft Data Access Components be installed prior to installing this SDK.

The Data Access SDK requires that Internet Explorer version 3.01 or later be installed on the system so that the HTML Help document viewer will work correctly.

1.2 OLE DB Test Tools

ITest Spy (ITestSpy.exe) requires HookOle to be successfully installed in order to spy on applications. Because HookOLE is not automatically installed by the setup, several steps are required to enable ITest Spy: 

  1. Run Setup.exe in the \Msdasdk\Hookole directory.
  2. Add the directory in which you installed HookOLE to your system's PATH. (The default directory is C:\Hookole.)
  3. Change to the \Msdasdk\Bin\Oledb directory.
  4. Run the command:
       regsvr32 ITHook.dll
  5. Run the command:
       regsvr32 oledbFilters.dll

You can now use ITestSpy.exe to spy on your application.

To use ITest Spy to spy on an application that uses notifications, you will need to turn off spying on the IConnectionPointContainer interface. Otherwise you could get an Access Violation while running the program.


-----------------
2. DATA ACCESS SDK KNOWN BUGS, LIMITATIONS, AND WORKAROUNDS
-----------------

The following is a list of Data Access SDK known bugs.

2.1 OLE DB Test Tools

2.1.1 Test Case Wizard 

Test Case Wizard does not allow double quotation marks in test descriptions. The description will be truncated after the first quote.

Test Case Wizard allows the backslash ("\") in a description, but the resulting code will not compile because the string is not properly escaped.

Test Case Wizard does not check whether a file is read-only when invoked from the command line. When trying to save a file invoked from the command line that is write-protected, you will receive the error "Unexpected File error, make sure it still exists!" It should report that the file is read-only.

The Test Case Wizard does not increment the module version after editing.

If HookOLE is installed, the Test Case Wizard crashes on exit. After HookOLE is removed, the crash will not occur.

2.1.2 Remotable or Traceable OLE DB Proxies

Because of restrictions in the MIDL compiler, the OLE DB proxies can either be remotable or traceable. The current OLE DB proxies that are installed in the SDK are traceable, but not remotable. Future OLE DB proxies that are designed to remote the OLE DB interfaces will not be traceable. The traceable proxies are in a DLL called Oledbproxy.dll. You must choose one or the other proxy. This means that when remotable proxies become available, you will not be able to trace an application using the remotable proxies. A newer application that depends on the newer proxies could be broken by the installation of this SDK, so a check is made to see if the remotable proxies are installed. If they are, you are given the choice of not registering the older Oledbproxy.dll.

You can manually switch between the proxies by using the following commands. In the examples that follow, it is assumed that you have installed the SDK onto the boot drive, and that the boot drive is the C drive. To install the traceable proxies, run the following commands:

   regsvr32 /u "c:\program files\common files\system\ole db\oledbpr.dll"
   regsvr32 c:\msdasdk\bin\oledb\oledbproxy.dll

To install the remotable proxies and stubs, run the following commands:

   regsvr32 /u c:\msdasdk\bin\oledb\oledbproxy.dll
   regsvr32 "c:\program files\common files\system\ole db\oledbpr.dll"

2.1.3 Using Full Connect in ITest with more than 20 Providers/Enumerators

If you have more than 20 providers and/or enumerators installed on your system, the Full Connect option in Interface Test (ITest.exe) may not work. Each connection attempt may give a connection failed message, and the drop-down list of providers on the Full Connect window may contain spaces at the top of the list.  

You can work around the problem by unregistering any providers you are not using.

2.1.4 Running ITest with Service Components

If Interface Test (Itest.exe) is run with the Service Components invoked, you will get an access violation when you call CreateDBInstanceEx. 

To work around, use CreateDBInstance instead, or do not invoke the Service Components.

2.1.5 LTM and DBCS Connect Strings

LTM does work with connection strings that contain DBCS characters.

Using LTM interactively, you can specify a connection string that contains DBCS characters. The connection can be made and tests can be run against the provider. However, LTM does not correctly write the DBCS string to the .ini file. Therefore, the saved .ini file will not contain a valid connection string.

2.1.6 Using ITestSpy with LTM and the ADO Minimal Conformance Tests

*  Turn off the Log to Screen option in the Start Application dialog box.
*  Enable interface filtering in ITestSpy and filter out IConnectionPoint interfaces. 

2.2 ActiveX Control Writer Toolkit

2.2.1 Building with Intel Visual C++ 5.0

PROBLEM: You will get link errors because the CtlFW and ADBCtl libraries are built with Visual C++ 6.0.. 
  
SOLUTION: Rebuild the FrameWork and ADBCtl projects found in Msdasdk\Misc\Aacwsrc to get Visual C++ 5.0 libraries. The sample will then link correctly.

2.2.2 Building with Intel Visual C++ 6.0

PROBLEM: If the INCLUDE path for ACW is placed after the include for Visual C++ 6.0, you will get the following compiler error:
   afxw_w32.h: fatal error C1189: #error : WINDOWS.H already included. 
   MFC apps must not #include <windows.h>
The error occurs because Visual C++ has an include file called util.h that contains MFC includes.

SOLUTION: Place the include directory for ACW before the include directory for Visual C++.

2.3 MDAC 2.0 Redist Setup Known Problems

2.3.1 Some Old OLE DB files Are Installed by Internet Explorer 4.01, Service Pack 1

PROBLEM: Installing Visual Studio 98 requires Internet Explorer 4.01, Service Pack 1
(IE 4.01 SP1) if it is not already on the machine. VisualStudio 98 setup prompts you to  install IE 4.01 SP1.

When running IE 4.01 SP1 installation, the following message is displayed twice:

   "Setup has determined that the existing components are newer 
   than the one being installed. Do you want to keep the 
   existing component?"

The options are to "Keep the existing component," "Install the new one," or "Cancel setup."

This message appears for two OLE DB components, Msdadc.dll and Msdaps.dll.

SOLUTION: Select "Keep the existing components" both times this message appears. The rest of the setup proceeds normally.

2.3.2 On Windows 95-Based Machines with Active Desktop, Installing MDAC 2.0 over Internet Explorer 4.01, Service Pack 1 Displays Error

PROBLEM: If you are running Active Desktop on a Windows 95-based machine and you install Internet Explorer 4.01, Service Pack 1 (IE 4.01 SP1) when prompted by Visual Studio 98 setup (as explained above), the message below may be displayed when installing MDAC 2.0 components.

If your Windows 95-based machine does not have IE 4.01 SP1 already installed, Visual Studio 98 setup asks you to install IE 4.01 SP1. The machine is rebooted after IE 4.01 SP1 has been installed and rest of the setup proceeds.

If you are running Active Desktop (on a Windows 95-based machine) and you select "server components" and install MDAC 2.0 components only from Visual Studio 98, then you may get the following error:

   "Setup could not open the file 
   "C:\Program Files\Common Files\System\Ado\MSADER15.dll.
   It is in use by another application."

The options are "Retry" and "Cancel."

SOLUTION: Cancel the Visual Studio 98 setup and reboot the machine. You can restart Visual Studio 98 setup now and it will proceed normally.

------------------
3. CONFORMANCE TESTING, VERSION 2.0
------------------

For information on OLE DB leveling and on conformance specific to OLE DB, see sections 3.1 and 3.2 in the OLE DB release notes, OLreadme.txt.

3.1 Improved Tests

Previous versions of OLE DB in the Data Access SDK contained unsupported versions of the OLE DB conformance tests. In the Data Access SDK 2.0, the level 0 tests have been significantly improved and moved to a new directory:
   <Install Directory>\Conformance\Tests\Proposed\OLEDBTests

In addition, a basic set of ADO tests (the Minimal set) has been added, under:
   <Install Directory>\Conformance\Tests\Proposed\ADOTests

For more information, see the white paper "Conformance Testing in OLE DB 2.0." This white paper can be found in the Data Access SDK under:
   Microsoft Data Access SDK
      Microsoft Data Access Technical Articles

3.2 Improved LTM (Local Test Manager) Test Tool 

The conformance tests shipped with the Data Access SDK 2.0 are run using LTM (Local Test Manager).  

LTM has been improved and simplified for the DA SDK 2.0. There is now only one executable file (LTM.exe) instead of two (LTM.exe and TD.exe). With fewer files, it's easier to install, set up, and debug tests.  

For more information on using the new LTM to run the conformance tests, see the white paper "Conformance Testing in OLE DB 2.0."

NOTE: The Help file for LTM has not been completely updated to match 2.0 functionality. In particular: 
*  The screen shots and sample output are not current.
*  Test Result Icons, described in the Test Selection Window section of the Help file, are now check marks instead of thumbs. Red still indicates failure, green still indicates success, and yellow has been added to indicate a warning.
*  The Multithreaded Execution option described in the Run section of the Help file is not available.
*  The Options dialog box (on the Tools menu, click Options, then click the Results tab) has been simplified. There are only three options:
   -- Results file. (If selected, specify file name and location.)
   -- Pass Fail file. (If selected, specify file name and location.)
   -- File Append Mode. 
*  There is a new option on the Tests menu for registering test modules within LTM. You can now click Register or Unregister on the Tests menu. It is therefore not necessary to use regserver to register each test module.
*  A more complete set of Test Module template files has been added to the 2.0 SDK. These template files can be used as a framework when creating new tests to be run in LTM. You can find template.dsp, template.h, template.cpp, and template.rc (along with the other unsupported OLEDB tests) in 
   <Install Directory>\Conformance\Tests\Unsupported\OLEDBTests

3.3 Connection String Keywords in the Conformance Tests
 
3.3.1 These keywords are case sensitive. For example, use: 
   DATASOURCE= ;    not datasource= ;
   USERID= ;        not userid= ;
   PASSWORD= ;      not password= ;

3.3.2 These keywords are based on OLE DB property names, not ODBC names. The keywords are derived from the "root" of OLE DB property names. For example, DBPROP_INIT_USERID becomes USERID. This was done to give the keyword names a consistent pattern. (In contrast, ODBC connection strings contain UID instead of USERID.)

3.4 Usage of Default Query with TableDump for Pproviders that Support Commands

Commands are not level 0 functionality. Therefore, when testing providers using the CONFLEVEL=CONF_LEVEL_0 | CONF_STRICT options, command interfaces will not be called.

To test your provider's support for commands: 
*  Do not set CONFLEVEL=CONF_LEVEL_0 | CONF_STRICT options.
*  When calling TableDump, include a value for the DefaultQuery argument.
*  Go to the QUERY section of the initialization file, fill in the other queries that are supported, and delete those queries that are not supported.

3.5 Running the ADO Minimal Tests

Before running the ADO minimal tests:
   1. Launch LTM.
   2. On the Tools menu, click Options, then click General.
   3. Under Threading Model, select Single Thread.

3.6 Debugging the ADO Minimal Tests in Visual Basic

The white paper "Conformance Testing in OLE DB 2.0," section 4, "Building and running the ADO minimal tests," states that "It is not possible at this time to debug the ADO tests in the Visual Basic environment."

With the newest version of LTM (included in the Data Access SDK 2.0), this problem has been addressed. It now is possible to debug the ADO tests in the Visual Basic environment.

To debug the ADO minimal tests:
   1. Launch LTM.
   2. Load the test module in Visual Basic, set a desired breakpoint, and run the DLL.
   3. Run the desired test from LTM.

The breakpoint should be hit.

If the breakpoint doesn't get hit, check to be sure the test being run contains the breakpoint. Also, rebuilding the test DLL may help resync the DLL and the code.

3.7 Corrections to the ADO-to-OLE DB Mapping Document

In the white paper "Conformance Testing in OLE DB 2.0," section 4, there is a link to a document that outlines ADO’s usage of OLE DB interfaces.
 
IRowsetNotify, IDBSchemaRowset, and IDBInfo are listed as interfaces that ADO doesn’t use. This is incorrect.  

ADO consumes IRowsetNotify in order to surface Recordset events. It consumes IDBSchemaRowset by using the Connection object OpenSchema method, and uses IDBSchemaRowset to populate the Parameters collection when Refresh is called. Finally, ADO consumes IDBInfo to get Literal Info information

3.8 ADO Works Best with Providers that Support ErrorInfo

ADO works best with providers that support the OLE ErrorInfo object. Currently, ADO does not call ISupportErrorInfo before calling the method ::GetErroInfo(). ADO will call ISupportErrorInfo in a future release.

3.9 Updated Header (Oledb.h)

The Data Access SDK contains the most recent Oledb.h file. This file must be located first in the INCLUDE path, before any older versions.

To do this, in Visual C++ version 5.0 or 6.0:
   1. On the Tools menu, click Options.
   2. On the Directories tab, in the Show Directories For box, select Include Files.
   3. Place Oledb.h from the MSDASDK directory in front of the file automatically included by Visual C++ 5.0 or 6.0.

3.10 OLE DB Sample, Rowset Viewer, and the New OLE DB Property, DATASOURCE

*  Use DATASOURCE to specify the server name.
*  LOCATION can be left blank.
*  To specify the database, fill in DBPROP_INIT_CATALOG, which can be found by using the Advanced button on the Properties tab.

