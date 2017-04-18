Porting Tool


SUMMARY
=======

The PORTTOOL tool is used to help identify the places in your 16-bit 
Windows-based source code that might need to change to make it 
Win32-compatible. The tool provides a brief description of the problem 
and a possible solution.

MORE INFORMATION
================

The porting tool has two operating modes. It can be run interactively or in 
the background. The background mode inserts comments in the locations where 
issues are found.

In the file that the porting tool uses to help identify potential issues 
(PORT.INI), there is a section available for entering programmer-defined 
strings. This allows the porting tool to be updated when new issues arise.

