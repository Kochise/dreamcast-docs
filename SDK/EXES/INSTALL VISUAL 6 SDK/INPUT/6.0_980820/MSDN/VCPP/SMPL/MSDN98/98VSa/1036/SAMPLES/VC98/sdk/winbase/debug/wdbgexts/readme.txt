Creating a WinDbg Extension


SUMMARY
=======

The WDBGEXTS sample demonstrates how to create an extention for the WinDbg
debugger. This is a port of the sample demonstrating how to create an NTSD
extension.

Extensions are DLL entry points. The arguments passed to an extension are:

    HANDLE hCurrentProcess - Supplies a handle to the current process (at
        the time the extension is called).

    HANDLE hCurrentThread - Supplies a handle to the current thread (at
        the time the extension is called).

    DWORD CurrentPc - Supplies the current pc at the time the extension is
        called.

    PWINDBG_EXTENSION_APIS lpExtensionApis - Supplies the address of the
        functions callable by this extension.

    LPSTR lpArgumentString - Supplies the command-line arguments for the
        extension.

The type PWINDBG_EXTENSION_APIS is defined in \mstools\h\wdbgexts.h.

Note that in the makefile the -Gz compiler option is specified to ensure
that __stdcall is used.

MORE INFORMATION
================

The following is a description of the exported functions.

Function   Description

igrep      Searches the instruction stream for a pattern.
str        Given a pointer to a string, it prints out the string, its 
           length, and its location in memory.

To use the commands contained in WDBGEXTS.DLL, make sure that the DLL is
placed in a directory which is on the PATH.

The syntax for the commands is as follows:

    !wdbgexts.igrep [pattern [expression] ]

    !wdbgexts.str [string]
