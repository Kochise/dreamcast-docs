Secure Network OLE

DCOM is implemented only on Windows NT 4.0 and later versions.  This sample
will not work correctly on Windows 95 or on earlier versions of Windows NT.

The SECURE sample consists of a client portion and a server portion. Its
purpose is to demonstrate client-side and server-side security in a Network
OLE application.

The server application, SECSVR.EXE, demonstrates the packaging options
available to server writers and the call-security capabilities. It implements
the following server capabilities:

 - A free-threaded server implemented as a service. The application implements
   the class "LocalService" (CLSID_SecureObjectService).
 - A free-threaded server implemented as a standard executable. The application
   implements the class "LocalServer32" (CLSID_SecureObject).
 - An apartment-threaded server implemented as a standard executable. The
   application implements the class "LocalServer32" (CLSID_SecureObject).

The client application, SECCLNT.EXE, allows you to select security settings
for the client application's connections to the server application.

This sample also include PSMYPROP.DLL, which supplies the remoting proxies
and stubs for the custom interface used between the client and the server.

To compile
----------

Build the client and the server by running NMAKE. 

To run
------

The run the client and server, use the following steps:

 - Install the server by running INSTALL.BAT. Note that SECSVR.EXE and
   PSMYPROP.DLL must be in the same directory as INSTALL.BAT.

 - To run the apartment-threaded server, use the command "SECSVR -Interactive". 
   Choose options to initialize security and view objects used by the clients.

 - Run SECCLNT.EXE. The user interface has three different sections.
    - In section one, choose the security parameters to CoInitializeSecurity
      from the two drop-down lists. Click the Initialize button.
    - In section two, choose a machine name to instantiate the object on or
      leave blank to use the current machine. In addition, choose between the
      LocalServer32 or LocalService objects. Click the Create Now button to
      create an instance.
    - In section three, set the color and the name of the object. This results
      in changes to the IMyProperties interface.
   Click the Release button in section two to release the object and connect to
   a different object. Click the Exit button in section one at any time to exit.

 - Once a client has created an instance of the "LocalServer32" class, the
   object will be listed in the interface of the server. Select the object to
   be viewed from the list. Use the Lock button to prevent the client from
   setting the color or name of the object. The client will display an
   access-denied message if it fails to set the color or name of the object.
