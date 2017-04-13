WINTYP  


The WINTYP sample demonstrates how to write a program that uses RPC calls to
transfer windows datatypes between the client and the server. 
The client reads in a bitmap and when the user selects to modify the image,
the bitmap is sent to the server, where the server is doing the modification.
The bitmap is then sent back to the client, where the new bitmap is displayed.

There are two choices for manipulating the images, either to flip it, or to 
find the edges in it. The find edge procedure will only work when the 
screen resolution is set to 256 colors. The reason for this is that the 
algorithm used in the remote procedures only works with 8 bits per pixel.

This program also allows the user to compile either for UNICODE or ANSI.
See section below for guidelines on how to compile for UNICODE

 
FILES 
===== 
 
The directory SAMPLES\RPC\WINTYP contains the following files for
building the sample distributed application WINTYP: 
 
File          Description
-------------------------

README.TXT      Readme file for the pipe sample 
WINTYP.IDL      Interface definition language file 
WINTYP.ACF      Attribute configuration file 
CLIENT.C        Client main program 
CLIENT.H        Header file specific for the client side
CLIENT.RC       Resource file for the client application
CLIRES.H        Resource header file
SERVER.C        Server main program 
COMMON.H        Common header file for all the files
REMOTE.C        Remote procedures 
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

The reason behind the use of TEXT, TCHAR, _TUCHAR, _tprintf, _tcscpy, 
_tcscmp, and _stprintf is that these macros expand to either 
regular one byte ANSI functions or to UNICODE (Wide characters) functions
when they are compiled
    TEXT    :   This macro will put an L in front of the string if we are 
                compiling for UNICODE
    TCHAR   :   Maps to either char or wchar_t 
    _TUCHAR :   Maps to either unsigned char or wchar_t 
    _tprintf:   Maps to either printf or wsprintf
    _stprintf:  Maps to either sprintf or swprintf
    _tcscpy :   Maps to either strcpy or wcscpy
    _tcscmp :   Maps to either strcmp or wcscmp
