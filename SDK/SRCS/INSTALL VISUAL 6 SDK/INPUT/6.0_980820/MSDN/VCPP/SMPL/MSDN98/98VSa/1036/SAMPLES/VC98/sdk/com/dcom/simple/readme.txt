Simple Network OLE Sample

DCOM is implemented only on Windows NT 4.0 and later versions.  This sample
will not work correctly on Windows 95 or on earlier versions of Windows NT.

The SIMPLE sample demonstrates the minimum requirements to use a COM object,
whether it is on the same machine or on a different machine. This sample
consists of a client and a server portion.

The server application, SSERVER.EXE, implements the CLSID_SimpleObject class as
a LocalServer. Instances of the class supports a limited form of the IStream
interface. Calls to Read and Write succeed, but they do nothing. Calls to other
methods fail with E_NOTIMPL.

The client application, SCLIENT.EXE, uses the CLSID_SimpleObject class
implemented by the server.

To compile
----------

Build the sample using the NMAKE command.

To run
------

The run the sample, use the following steps.

 - Edit the SSERVER.REG file to make the LocalServer32 key point to the location
   of SSERVER.EXE.
 - Install the server on the current machine or a remote machine by running
   INSTALL.BAT. This copies SSERVER.REG to the registry.
 - Run SSERVER. It should display the message "Waiting...".
 - Run SCLIENT. Use no command-line arguments to instantiate the object on the
   current machine. Use the name of a remote machine (UNC or DNS) as an argument
   to instantiate the object on the remote machine. SCLIENT displays simple
   information about the calls it is making on the object.
