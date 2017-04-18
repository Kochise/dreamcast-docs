REPAS


The REPAS program demonstrates the represent_as ACF attribute.

FILES
=====

The directory samples\rpc\data\repas contains the following files for
building the sample distributed application REPAS:

File          Description

README.TXT    Readme file for the REPAS sample
REPAS.IDL     Interface definition language file
REPASC.ACF    Client version of Attribute configuration file
REPASS.ACF    Server version of Attribute configuration file
REPASC.C      Client main program
REPASS.C      Server main program
REPASP.C      Remote procedures
REPASCU.C     Client Utility functions
REPASSU.C     Server Utility functions
MAKEFILE      Nmake file to build for Windows NT or Windows 95

-------------------------------------------
BUILDING CLIENT AND SERVER APPLICATIONS FOR
MICROSOFT WINDOWS NT OR WINDOWS 95
-------------------------------------------

The following environment variables should already be set for you:

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

This builds the executable programs repasc.exe (client) and 
repass.exe (server).

-----------------------------------------------------------------------
BUILDING THE CLIENT APPLICATION FOR MS-DOS
-----------------------------------------------------------------------

DOS build not yet ready...

------------------------------------------
RUNNING THE CLIENT AND SERVER APPLICATIONS
------------------------------------------

On the server, enter:

  repass

On the client, enter:

  net start workstation
  repasc

Note:  The client and server applications can run on the same Microsoft 
Windows NT computer when you use different screen groups.

Several command line switches are available to change settings for this 
program. For a listing of the switches available from the client program, 
enter:

  repasc -?

For a listing of switches available from the server
program, enter:

  repass -?
