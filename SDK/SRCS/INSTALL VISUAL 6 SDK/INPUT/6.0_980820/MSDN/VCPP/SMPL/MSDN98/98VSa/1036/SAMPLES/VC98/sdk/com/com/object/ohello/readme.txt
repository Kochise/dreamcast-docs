OHELLO


The OHELLO program demonstrates OLE custom interfaces and proper reference 
counting and shutdown behavior for a multiple-use local server. The program 
also shows how to use the Win32 registry functions to install a local server 
and a proxy DLL in the registry.

FILES
=====

File          Description

README.TXT    Readme file for the AUTO sample
OHELLO.IDL    Interface definition language file
OHELLO.DEF    Module definition file
CLIENT.CXX    Client main program
SERVER.CXX    Server main program
CHELLO.CXX    Implements the CHello object and class factory
ERROR.CXX     Demonstrates how to get error code message text from
              system resources
MAKEFILE      Nmake file to build for Windows NT or Windows 95
