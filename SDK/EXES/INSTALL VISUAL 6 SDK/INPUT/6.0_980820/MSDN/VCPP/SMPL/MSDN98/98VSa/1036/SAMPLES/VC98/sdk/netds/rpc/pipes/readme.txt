PIPES  


The PIPE sample demonstrates how to write a program that uses pipes for 
transferring data between the client and the server. The client sends a 
file to the server using pipes. The server then "encodes" the data by 
adding 1 to every element in the file, and then sends the file back using
pipes. The pipe used in this sample program is a in/out pipe.

This program also allows the user to compile either for UNICIODE or ANSI.
See section below for guidelines on how to compile for UNIOCDE

 
FILES 
===== 
 
The directory SAMPLES\RPC\PIPES contains the following files for
building the sample distributed application PIPES: 
 
File          Description
-------------------------

README.TXT      Readme file for the pipe sample 
PIPE.IDL        Interface definition language file 
PIPE.ACF        Attribute configuration file 
PIPEC.C         Client main program 
PIPES.C         Server main program 
COMMON.H        Common header file for all the files
PIPEPROC.C      Remote procedures 
MAKEFILE        nmake file to build 32-bit client and server app.
                for ANSI characters.
MAKEFILE.UNI    nmake file to build 32-bit client and server app.
                for UNICODE characters.


NMAKE builds the executable programs CLIENT.EXE (client) and
SERVER.EXE (server).

Note: The client and server applications can run on the same 
Microsoft Windows NT computer when you use different screen groups.



COMPILING FOR UNICODE:
======================

type nmake /f makefile.uni at the command line. This will cause
the compiler to use the file MAKEFILE.UNI instead of the MAKEFILE.

The reason behind the use of TEXT, TCHAR, _TUCHAR, _tprintf, _tcscpy, _tcscmp,
and _tfopen is that the program can easily be compiled to support UNICODE 
(Wide characters) as well as supporting one byte ANSI characters. 

    TEXT	:   This macro will put an L in front of the string if we are
                compiling for UNICODE, and do nothing if compiling for ANSI
    TCHAR	:   expands to either char or wchar_t during compilation
    _TUCHAR	:   expands to either unsigned char or wchar_t during compilation
    _tprintf:   expands to either printf or to wsprintf	during compilation
    _tcscpy	:   expands to either strcpy or to wcscpy during compilation
    _tcscmp	:   expands to either strcmp or to wcscmp during compilation
    _tfopen	:   expands to either fopen or to _wfopen during compilation
