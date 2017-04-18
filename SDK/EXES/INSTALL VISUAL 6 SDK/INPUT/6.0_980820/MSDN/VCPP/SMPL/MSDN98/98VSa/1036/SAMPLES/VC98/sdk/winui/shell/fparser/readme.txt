File Parser


SUMMARY
=======

The FPARSER sample parses files with a particular extension.

The default file extension for this sample is TST. To use this file parser 
for ASCII files of different extensions, the registry must be changed. The 
registry entry for the new extension must be given a new key named 
QuickViewAddOn under the subkey that contains our viewer class identifier. 
Within this key, the registry should have an item named DllName, whose value 
is the name of your DLL.

As an example, a filter whose file extension is .XXX, would need the
following reg file contents merged into the registry:

   HKEY_LOCAL_MACHINE\SOFTWARE\
   Classes\QuickView\.XXX\{F0F08735-0C36-101B-B086-0020AF07D0F4}
   \QuickViewAddOn

   DllName"="vsxxx.dll

This would enable a user to right-click on a file of extension .XXX and
have the vsxxx.dll file parser be used.

This approach will override any built-in file identification used by
SCC's DLLs, using the extension only to choose the specified file parser.

NOTE: No other identifier can be used in the above registry entry.

MORE INFORMATION
================

This sample provides a template for an ASCII file parser. It is configured
to work with the file extension .TST, but this can be changed by modifying
FPARSER.REG to the extension you wish.

Usage
-----

To use this file parser, use the following steps:

1. Import FPARSER.REG into your registry.

2. Set the key HKEY_LOCAL_MACHINE\SOFTWARE\SCC\Viewer Technology\MS1. 
   Verify to a non-zero value. This will reset the list of parsers the next 
   time a file is viewed.

3. Build VS_ASC.DLL.

4. Copy VS_ASC.DLL to <windows path>\SYSTEM\VIEWERS.

5. Rename or copy an ASCII file to a .TST extension.

6. From the Explorer, right-click the file.

7. Select Quick View.
