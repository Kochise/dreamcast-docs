4/16/97
Sample files for Scripting a Pair of Transaction Processors
-------------------------------------------------------------------------------------------------

The client folder contains script files for the client-side application
The db folder contains the database file
The server folder contains script files for the server-side application
The src folder contains source code for the data services component


General notes
-------------------------------------------------------------------------------------------------
The data services COM server, and the database file, are located on the server for both of the applications in order to perform a reasonable comparison of the different scripting techniques.

Perform the following steps to run the sample applications.

1. Modify the scripts for both applications and substitute your database path for what is provided in the scripts. The client-side database path is found in banks.htm and the server-side database path is found in global.asa.

2. Register the appropriate data services component on the server and, for the client-side aplication, on the client computers.


These applications both require a Windows NT 4.0 server running Internet Information Server Active Server Pages 3.0 or greater.

The server-side application will support any client platform and browser that supports frames.

The client-side application requires a browser that supports ActiveX scripting and frames such as Internet Explorer 3.0 or greater. VBScript 2.0 is required. You can download the latest version of VBScript from the Microsoft Web site(http://www.microsoft.com/vbscript/). The client OS for the client-side application must support DCOM in order to use data services on the server. Windows NT 4.0 and Windows95(with DCOM95) support DCOM. You can download the latest version of DCOM 95 from  (http://www.microsoft.com/oledev/olemkt/oledcom/dcom95.htm).



Registering and configuring the data services component for the Server-Side application
-------------------------------------------------------------------------------------------------
Use banksrv.dll for the server-side application in order to exploit the advantages of in-process COM servers with ASP.

Register banksrv.dll on the server with regsvr32.exe.
 Use regsvr32 banksrv.dll to register the component classes.
 Use regsve32/u banksrv.dll to unregister.



Registering and configuring the data services component for the Client-Side application
-------------------------------------------------------------------------------------------------
The client-side application uses the data services remotely via DCOM.
Use banksrv.exe for the client-side application because DCOM favors out-of-process COM servers.

Register banksrv.exe on the server by using it's self registration feature.
 Type banksrv /regserver to register the component classes.
 Type banksrv /unregserver to unregister.

Run dcomcnfg.exe on the server to configure security for remote instantiation of the banking classes. The easiest way to get started with DCOM security is to open default security as wide as possible to get the system running and then make it progressively more restrictive until you have the desired level of security. Start with a default authentication level of None and a default impersonation level of anonymous. With default security configured, set each banking class to use default security.


-Client Registration method A-
Banking.reg is supplied in order to allow you to register banksrv.exe on the client machines for use via DCOM without actually installing it.
 Edit banking.reg with notepad to replace MyServer with your server's name.
 Import banking.reg by double clicking it from explorer or importing it with regedit.exe. 

-Client Registration method B-
As an alternate registration method, you can create a setup program with the VB5 setup wizzard that will configure your client computers to use the data services via DCOM. Mark the data services component as safe for scripting and safe to initialize.

-Client Registration method C-
Another alternate registration method is to copy banksrv.exe to the client machines and register it there using the banksrv /regserver synatx. Add the following entries to the registry with regedit in order to mark the data services classes as safe for scripting and safe for initializing:
HKEY_CLASSES_ROOT\CLSID\{03990E7E-B686-11D0-B157-00AA006C3AB9}\Implemented Categories\{7DD95801-9882-11CF-9FA9-00AA006C42C4}

HKEY_CLASSES_ROOT\CLSID\{03990E7E-B686-11D0-B157-00AA006C3AB9}\Implemented Categories\{7DD95802-9882-11CF-9FA9-00AA006C42C4}

HKEY_CLASSES_ROOT\CLSID\{03990E80-B686-11D0-B157-00AA006C3AB9}\Implemented Categories\{7DD95801-9882-11CF-9FA9-00AA006C42C4}

HKEY_CLASSES_ROOT\CLSID\{03990E80-B686-11D0-B157-00AA006C3AB9}\Implemented Categories\{7DD95802-9882-11CF-9FA9-00AA006C42C4}

HKEY_CLASSES_ROOT\CLSID\{03990E82-B686-11D0-B157-00AA006C3AB9}\Implemented Categories\{7DD95801-9882-11CF-9FA9-00AA006C42C4}

HKEY_CLASSES_ROOT\CLSID\{03990E82-B686-11D0-B157-00AA006C3AB9}\Implemented Categories\{7DD95802-9882-11CF-9FA9-00AA006C42C4}

The class IDs listed here assume that you use the servers as provided or recompile only with project compatibility or greater.

Use the RacMgr utility, part of Visual Basic 5.0, to configure the Banksrv classes for DCOM.
Use DCOMCNFG(NT4) to configure DCOM security options.

-------------------------------------------------------------------------------------------------

If you recompile the data services components without setting the component compatibility level to project or binary, the Unique Identifiers of the classes will change and make it necessary for you to either modify banking.reg or to use another registration method.


