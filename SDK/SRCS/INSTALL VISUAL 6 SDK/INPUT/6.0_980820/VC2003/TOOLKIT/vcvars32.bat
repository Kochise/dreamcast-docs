@echo off

Set PATH={app}\VCTK2003\bin;%PATH%
Set INCLUDE={app}\VCTK2003\include;%INCLUDE%
Set LIB={app}\VCTK2003\lib;%LIB%

echo Setting environment for using Microsoft Visual C++ 2003 Toolkit.
echo (If you have another version of Visual Studio or Visual C++ installed and wish
echo to use its tools from the command line, run vcvars32.bat for that version.)
echo.
echo Thank you for choosing the Visual C++ Toolkit 2003!  Get started quickly by
echo building the code samples included in the "Samples" directory.  Each sample
echo includes a short whitepaper discussing the Visual C++ features, and a batch
echo file for building the code.
echo.
echo Type "cl /?" for brief documentation on compiler options.
echo.
echo Visit http://msdn.microsoft.com/visualc/using/documentation/default.aspx for
echo complete compiler documentation.
