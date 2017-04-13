Active Directory Service Interfaces 1.0, Sample C++ Application

Overview:

This simple command line based program shows how to use Active Directory to browse and display objects of any Directory Service. Its usage is as follows:

    adscmd [list|dump] <ADsPath>

For example, for a Windows NT system

    adscmd dump WinNT://MYDOMAIN/SomeUser

will dump the properties of SomeUser in MYDOMAIN. Or, on an NDS system:

    adscmd list NDS://MYTREE

will list the top of the MYTREE tree. Note that the namespace ("WinNT", "NDS") is case sensitive.

List of files:

MAIN.CXX	main program
UTIL.HXX	helper functions
DUMP.CXX	functions to dump properties of an object
ENUM.CXX	functions to enumerate children of a container
MAIN.HXX	main include file
MAKEFILE	makefile

