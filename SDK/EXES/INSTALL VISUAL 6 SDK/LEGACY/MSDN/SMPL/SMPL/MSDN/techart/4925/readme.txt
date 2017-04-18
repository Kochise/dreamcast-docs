              Extending Visual Basic with C++ DLLs
                           Sample Code

If you unzipped the sample code file correctly (with the -D option),
it will have the following directory structure:

Cpp4VB          Visual Basic Cpp4VB project to test libraries
    WinTlb      Windows API Functions type library
    OleType     OleType static library project files
    VBUtil      VBUTIL dynamic link library project files
    Include     Standard include files (.H and .ODL)
    Lib         OleType static library (Debug and Release)
    Bin         Type libraries and DLLs

You should copy the include files in the Include directory to your a
standard INCLUDE directory (default C:\MSDEV\INCLUDE). Copy the static
libraries to a standard LIB directory (default C:\MSDEV\LIB). The
OleType projects are set up to build the libraries in C:\MSDEV\LIB, so
you can build them instead of copying them. You can copy the contents
of the Bin directory to your Windows directory or some other location
in your path.

You can load the .MDP project files into Microsoft Visual C++. If you
have a different compiler or if you prefer building from a command
line, you may still be able to use the .MAK files.

For easier Unicode debugging, you may want to copy the following
definitions to your AUTOEXP.DAT file in the MSDEV binary directory
(default C:\MSDEV\BIN):

; From BString.h
String =<m_bs,su>

; From Variant.h
Variant =vt=<vt,x> short=<iVal> long=<lVal> dbl=<dblVal,g> str=<bstrVal,su>

[Unicode]
DisplayUnicode=1


Note: The Unicode Release version of VBUTIL32.DLL caused a protection
fault when built with full optimization under Visual C++ version 4.1.
Therefore, this version uses custom optimization settings that avoid
the problem. I had not yet isolated the bug when this version of the
library was completed, but you can avoid it by using similar
optimizations rather than the default release settings in your own
Unicode projects.
