CALLBACK


The CALLBACK program demonstrates the use of the callback attribute to 
allow a server application to execute code on a client application. The 
distributed program generates a Fibonacci number with a static callback.

The directory samples\rpc\callback contains the following files for
building the sample distributed application CALLBACK:

File          Description

README.TXT      Readme file for the CALLBACK sample
CALL.IDL        Interface definition language file
CALL.ACF        Application configuration file
CALLC.C         Client main program
CALLS.C         Server main program
CALLP.C         Remote procedures
MAKEFILE        Nmake file to build for Windows NT or Windows 95
MAKEFILE.DOS    Nmake file to build for MS-DOS

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

This builds the executable programs callc.exe (client) and calls.exe
(server).

-----------------------------------------------------------------------
BUILDING THE CLIENT APPLICATION FOR MS-DOS
-----------------------------------------------------------------------

After installing the Microsoft Visual C/C++ version 1.50 development
environment and the 16-bit RPC SDK on a Windows NT or Windows 95
computer, you can build the sample client application from Windows NT
or Windows 95:

  nmake -f makefile.dos cleanall
  nmake -f makefile.dos

This builds the client application callc.exe.

You may also execute the Microsoft Visual C/C++ compiler under MS-DOS.
This requires a two-step build process.

  Step One: Compile the .IDL files under Windows NT or Windows 95:

     nmake -a -f makefile.dos hello.h

  Step Two: Compile the C sources (stub and application) under MS-DOS:

     nmake -f makefile.dos



-----------------------------------------------------------------------
RUNNING THE CLIENT AND SERVER APPLICATIONS
-----------------------------------------------------------------------

On the server, enter:

  calls

On the client, enter:

  net start workstation
  callc

Note:  The client and server applications can run on the same Microsoft
Windows NT computer when you use different screen groups.

Several command-line switches are available to change settings for this
program. For a listing of the switches available from the client
program, enter:

  callc -?

For a listing of switches available from the server program, enter:

  calls -?
