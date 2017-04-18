MANDEL


The MANDEL program is a distributed fractal drawing application that uses 
reference pointers, the implicit_handle attribute and handl_t primitive types.

FILES
=====

The directory samples\rpc\mandel contains the following files for the
sample distributed application MANDEL:

File          Description

README.TXT    Readme file for the MANDEL sample
MDLRPC.IDL    Interface definition language file
MDLRPC.ACF    Attribute configuration file
MANDEL.C      Client main program
MANDEL.H      Client global data
REMOTE.C      Client code that calls remote procedures
RPC.ICO       Client icon
MANDEL.DEF    Client module definition file
MANDEL.RC     Client resource script file
SERVER.C      Server main program
CALC.C        Remote procedures
MAKEFILE      nmake utility for Windows NT or Windows 95
MAKEFILE.WIN  nmake utility for Win 3.x

-------------------------------------------
BUILDING CLIENT AND SERVER APPLICATIONS FOR
MICROSOFT WINDOWS NT OR WINDOWS 95
-------------------------------------------

The following environment variables should be already set for you:

  set CPU=i386
  set INCLUDE=%SDKROOT%\h
  set LIB=%SDKROOT%\lib
  set PATH=%SDKROOT%\system32;%SDKROOT%\bin

where %SDKROOT% is the root directory for the 32-bit Windows SDK.

For mips, set CPU=mips
For alpha, set CPU=alpha

Build the sample distributed application:

  nmake cleanall
  nmake

This builds the executable programs client.exe and server.exe for Microsoft 
Windows NT or Windows 95.

--------------------------------------------
BUILDING THE CLIENT APPLICATION FOR WIN 3.X
--------------------------------------------

After installing the Microsoft Visual C/C++ version 1.50 development
environment and the 16-bit RPC SDK on a Windows NT or Windows 95
computer, you can build the sample client application from Windows NT
or Windows 95:

  nmake -f makefile.win cleanall
  nmake -f makefile.win

This builds the client application client.exe.

You may also execute the Microsoft Visual C/C++ compiler under MS-DOS.
This requires a two-step build process.

  Step One: Compile the .IDL files under Windows NT or Windows 95:

     nmake -a -f makefile.win yield.h

  Step Two: Compile the C sources (stub and application) under MS-DOS:

     nmake -f makefile.win

------------------------------------------
RUNNING THE CLIENT AND SERVER APPLICATIONS
------------------------------------------

On the server, enter:

  server

On the client, enter:

  net start workstation
  client

Note:  The client and server applications can run on the same Microsoft 
Windows NT computer when you use different screen groups. If you run the 
client on the Microsoft MS-DOS and Windows computer, choose the Run
command from the File menu in the Microsoft Windows 3.x Program Manager and 
enter client.exe.

Several command line switches are available to change settings for the 
server program. For a listing of switches available from the server program, 
enter:

  server -?
