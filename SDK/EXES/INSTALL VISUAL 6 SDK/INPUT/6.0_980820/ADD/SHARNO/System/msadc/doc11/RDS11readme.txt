                 ---------------------------------------------------------
                 Microsoft(R) Remote Data Service version 1.1 Readme File
                                           1997
                 ---------------------------------------------------------

	    		      (c) Microsoft Corporation, 1997

This document provides late-breaking or other information that supplements the Microsoft Remote Data Service (RDS) version 1.1 documentation.

--------
CONTENTS
--------

1. PRODUCT DESCRIPTION
   1.1 Change in Product Name

2. NEW FEATURES

3. INSTALLATION NOTES
   3.1 Before You Run Setup
       3.1.1 Hardware Requirements
       3.1.2 Software Requirements
   3.2 Installing Microsoft Remote Data Service
       3.2.1 Installing RDS Client Components on Your Web Servers
       3.2.2 Installing and Using RDS Client Components on Your Client Computers
   3.3 Validating Setup

4. TECHNICAL SUPPORT
   4.1 Contacting Microsoft Technical Support
   4.2 Visiting the Microsoft Remote Data Service Web Site
   4.3 Joining the Remote Data Service Public Newsgroup

5. TECHNICAL NOTES

6. KNOWN PROBLEMS

----------------------
1. PRODUCT DESCRIPTION
----------------------

Microsoft Remote Data Service (RDS) is a fast and efficient data connectivity and data publishing framework for applications hosted in Microsoft Internet Explorer. It is based on a client/server, distributed technology that works over HTTP, HTTPS (HTTP over Secure Sockets layer), and DCOM application protocols. Using data-aware ActiveX(R) controls, RDS provides Visual Basic(R)-style data access programming to Web developers who need to build distributed, data-intensive applications for use over corporate intranets and the Internet.

1.1 Change in Product Name

The name Microsoft Advanced Data Connector (ADC) is changing to Microsoft Remote Data Service (RDS), a feature of Microsoft ActiveX Data Objects (ADO). ADC has always relied on ADO and this change represents a move to more closely integrate and clarify the relationship between these two components. ADO is a programming interface which allows easy and flexible access to OLE DB and ODBC data sources. Remote Data Service builds on ADO to provide an easy, disconnected recordset, and remoting service. The functionality of Advanced Data Connector has not been affected by this change.


---------------
2. NEW FEATURES
---------------

The following are new features in Remote Data Service 1.1 client. For more information on these features, refer to the documentation.

The 1.1 client provides an upgrade path for your 1.0 applications. Advanced Data Connector 1.0 provided support for the Internet Explorer 3.0x browser. Remote Data Service 1.1 supports both Internet Explorer 3.0x and 4.0, allowing a forward compatibility path. In the 1.5 client, there is a slightly updated programming model for data binding. Your 1.1 client preserves the 1.0 programming model, so you can still run your applications while choosing when you have time to make the few easy changes needed.

The 1.1 client consists primarily of minor fixes and compatiblity changes, but it also provides expanded updatability. You can now update data to all ODBC compliant data sources, and you no longer need to use the "for browse" clause.

Because the 1.1 client relies on the 1.5 server, your 1.5 server can host both the 1.1 and 1.5 clients.

---------------------
3. INSTALLATION NOTES
---------------------

3.1 Before You Run Setup

Before you install Microsoft Remote Data Service, make sure that your client and server computers meet the minimum hardware and software requirements.

3.1.1 Hardware Requirements

To install Remote Data Service, you must meet certain hardware requirements, which include the following:

· Any Microsoft Windows NT(R) or Microsoft Windows 95 x86-compatible computer.
· A hard disk with a minimum of 8 megabytes (MB) available space for a full installation of all the updated components required for RDS to run. 
· A minimum of 12 MB of RAM for client computers. 
· A minimum of 24 MB of RAM for server computers (32 MB of RAM recommended). 

3.1.2 Software Requirements

Before you install Remote Data Service on a server computer, your Web server computer must meet the following software requirements:

· Remote Data Service 1.5 server.
· Any of the following operating system platforms: Windows NT Server 4.0 or Workstation SP3 or later. Remote Data Service 1.1 currently supports the x86/Intel platform. For production data environments, the NT Server platform is strongly recommended.
· Microsoft Internet Information Server (IIS) 3.0 or 4.0, with Microsoft Active Server Pages.
· Microsoft SQL Server 6.5 with Service Pack 2 (or other ODBC data source).
 
To access Remote Data Service applications from client computers, client computers must meet the following software requirements:

· Any of the following operating system platforms: Windows 95, Windows NT Server 4.0 (with Service Pack 3) or later, or Windows NT Workstation 4.0 or later. 
· Microsoft Internet Explorer version 3.0x or 4.0, or later.

Note: Remote Data Service has not been tested with the Netscape browser technology.
 
To build client Web pages, you can use typical HTML authoring tools, such as Notepad or the more fully featured Microsoft ActiveX Control Pad.

To program server-side business objects, you can use any ActiveX/COM DLL-compatible tool, such as Microsoft Visual Basic 4.0 or later or Microsoft Visual C++(R).

3.2 Installing Microsoft Remote Data Service

For Remote Data Service to work correctly, you should ensure that the Remote Data Service server and client components are installed correctly on server and client computers, respectively. 

3.2.1 Installing RDS Client Components on Your Web Server

You will install the Microsoft Remote Data Service 1.5 server components on your Web server computer via the MDAC (Microsoft Data Access Components) 1.5 setup. Setup assumes that your computer meets all of the software requirements.

Note: The Microsoft Remote Data Service version 1.1 client components work with the Microsoft Remote Data Service 1.5 server components. RDS 1.1 is an upgrade path for RDS 1.0 applications to port to Internet Explorer 4.0 and to take advantage of new RDS 1.5 server functionality. For existing RDS 1.0 applications, you can use the 1.1 client with the 1.5 server components for both Internet Explorer 3.0x and 4.0 functionality. For new and Internet Explorer 4.0-only applications, it is recommended you use the RDS 1.5 client components with the RDS 1.5 server components. 
 
>>>To install Remote Data Service 1.1 client components:

1) From your Web server computer, connect to the Remote Data Service World Wide Web site at http://www.microsoft.com/data/rds/.
2) Click Free Downloads in the left frame.
3) Click the link for the installation you want (mdac_nts.exe for Windows NT Server; mdac_ntw.exe for Windows NT Workstation; mdac_95.exe for Windows 95; mdac_as.exe for Alpha server; mdac_aw.exe for Alpha workstation) and choose Custom Install to install the RDS 1.1 client components and documentation. 
4) Follow the Setup instructions on the screen. 
 
The Setup program installs the program files to the <device>:\Program Files\Common Files\System\MSADC directory. (This location is adjacent to other complementary Microsoft technologies such as ActiveX Data Objects and OLE DB.) The following subdirectories are created under the \MSADC directory with the setup program.

Subdirectory		Description
------------		-----------
..\MSADC\Doc11 		Contains the documentation.
..\MSADC\Samples11	Contains the sample files.

The server installation program will have already created a Microsoft Internet Information Server virtual root on your Web server computer. The root is designated http://<servername>/msadc which you can use to reference the physical file system from the browser.

Once you have followed this procedure to set up Microsoft Remote Data Service on your Web server computer, you can validate your installation. (See Section 3.3.)

3.2.2 Installing and Using RDS Client Components on Your Client Computers

To ensure that client computers include all of the appropriate client DLLs to run Remote Data Service, you should include the mdac11.cab file in the HTML CODEBASE parameter in the RDS.DataControl object code on your Web page. When the mdac11.cab file is downloaded, it automatically installs the required client files to the client computer. This simplifies the deployment of Remote Data Service-enabled Web pages. For more information on how to include this information on your Web pages, see the RDS.DataControl object topic in online Help.

 
3.3 Validating Setup

You can use the ADCTest.asp sample application to validate your Microsoft Remote Data Service installation. 

>>>To validate setup with ADCTest
1 Start Internet Explorer, and enter the following address: 

  http://<servername>/MSADC/Samples11/adctest.asp 

  where <servername> is the name of your Web server.
  This should display the Remote Data Service Query Page. You'll notice that the server, connection, and query information is already provided for you.
2 Click the Run! button to execute the query. 
  If the grid displays a resultset, your installation is correct. 

If you run into any problems, review the setup instructions and see "Troubleshooting Remote Data Service" and "Other RDS Configuration Information" in online Help. Help can be accessed by running default.htm from the \docs directory.

--------------------
4. TECHNICAL SUPPORT
--------------------

4.1 Contacting Microsoft Technical Support

If you have a technical question about Remote Data Service, please contact the manufacturer of your PC or server. Refer to the documentation that came with your PC or server for the product support telephone number.

4.2 Visiting the Microsoft Remote Data Service Web Site

You can visit the Microsoft Remote Data Service Home Page on the World Wide Web for documentation updates and information about related technologies. The address is http://www.microsoft.com/data/rds/.

4.3 Joining the Remote Data Service Public Newsgroup

To facilitate discussion and information sharing, Microsoft has set up a public newsgroup: microsoft.public.ado.rds. You are welcome to post articles and messages to this unmoderated, unsupported newsgroup. Microsoft does not guarantee responses or direct support. For more information, visit the Remote Data Service Web site, http://www.microsoft.com/data/rds/.

------------------
5. TECHNICAL NOTES
------------------

· Sample Applications
To load the grid in the RDS sample applications, you need to be able to access the Internet (as opposed to your intranet). If you try to load the samples that use the Sheridan grid, the Sheridan cab file referenced in the CODEBASE line attempts to download the mfc42.dll file patch from the Microsoft general fixes Web site. If it is unable to access this patch, the grid will not load. If the ActiveX control for the grid (ssdatb32.ocx) already resides on the client computer, the CODEBASE line will not need to unpack the cab file and the problem will not be encountered.

· When you install the sample applications, an attempt is made to create a user account ("adcdemo") within SQL Server. If this account already exists, the installation will succeed; however, when you run the sample application you may receive a "login failed" message. You can edit the sample files to set the username and password to a working account.

· Using FoxPro Databases
If you access Visual FoxPro data, you must use the latest Visual FoxPro ODBC driver (version 5.0.0.402 or later), which is available from http://www.microsoft.com/vfoxpro/vfdownload. If you don't use the latest driver, you may not be able to execute queries correctly.

· "System error: out of virtual memory" Error
If you receive the error, "System error: out of virtual memory" from the Web Server, requiring a reboot, the following may address the error. Your Web server machine might be out of virtual memory, or the SQL data source server might require more TempDB space to handle the size of the query you are attempting to run. Virtual memory can be adjusted from Control Panel. (Click the System icon, select the Performance tab, and click the Virtual Memory button to see if there is extra hard disk space available.) More information on how to adjust the TempDB space can be found in the the "Performance" Help topic's subtopic, "Ensuring Sufficient TempDB Space."

-----------------
6. KNOWN PROBLEMS
-----------------

The following is a list of Remote Data Service 1.1 known problems.

· Version 1.0.0.806 of the Visual Basic Script DLL (vbscript.dll) contains a memory leak. An updated version of the DLL (2.0.0.1114 or later) resolves the issue. It is available with Internet Information Server 3.0 and can be downloaded from http://www.microsoft.com/vbscript.

· When you use RDS with the Visual Basic 5.0 list box or combo box control in Internet Explorer version 4.0, you should set the ListField property for the list box or combo box control at design time in the control's <OBJECT> tags. Otherwise, if you set the ListField property at run time in VBScript code, the data won't be populated in the controls. Therefore, you should use HTML code like the following:

	<OBJECT....>
	   <PARAM NAME="ListField" VALUE="ColName">
	   ...
	</OBJECT>

instead of VBScript code like:

	Combo1.ListField="ColName"

· If you make changes to data on your RDS page and then go to another page without canceling or submitting the changes, when you return to your RDS page, you might get an "Unexpected Error" message. Calling the RDS.DataControl object's Refresh method when you return to the page will resolve this problem.

· When loading the sample pages for the first time on some machines with Microsoft Internet Explorer version 3.02, an object may not load or you may receive an "Unexpected Error (0x80020009)" message. If this happens, click the "Refresh" button to correct the problem.
