Microsoft ICM 2.0 SDK:                                     readme.txt
Image Color Management Version 2.0
Software Development Kit

               For Microsoft Platform SDK - PDC Edition
			Released September, 1997

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

This readme file contains the following information:

             1. Target Platform of the ICM 2.0 SDK  
	     2. Contents of the ICM 2.0 SDK


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


1. Target Platform of the ICM 2.0 SDK
--------------------------------------
This SDK is for developing software for Windows® 98, 
and for version 5.0 of Windows NT® (both unreleased). The platforms 
currently available for testing software developed using this SDK are the 
Beta 2 and later releases of Windows 98 and the Beta 1 release of 
Windows NT version 5. For information about receiving a beta version of 
Windows 98, please contact:

Memreq@microsoft.com


2. Contents of the ICM 2.0 SDK
-------------------------------

When you installed the ICM 2.0 SDK, you specified a folder 
in which to install it, which was preferably the same folder 
in which the Microsoft Win32® SDK or Platform SDK is installed 
on your system. The setup program placed the following files 
in the folders under the installation folder that you specified:

[Installation root folder]
|
+--bin
|     icmui.dll              : ICM 2.0 User Interface dynamic link library
|     Bitmap.exe             : Utility for changing bitmap headers
|     icmview.exe            : Sample image viewer showing color management
|     Icmtest.icm            : Test profile designed to dramtically change colors
|     rgbtest.icm            : Test profiles designed to mess up colors
|
+--include
|     icm.h                  : ICM 2.0 C/C++ header file
|     icmui.dlg              : If you want to hook out ICM UI dialog and replace it with your own
|
+--lib
|     icmui.lib              : ICM 2.0 User Interface static link library
|     mscms.lib              : ICM 2.0 static link library
|
+--samples
|   +--Graphics
|      +--ICM20
|             readme.txt      : This readme file
|        +--icmview            : SAMPLE APPLICATION
|             appinit.c        : Initialization source code 
|             appinit.h        : Initialization header 
|             cderr.h          : Error handling header
|             child.c          : Child windows source
|             child.h          : Child windows header
|             debug.c          : Debug routines source
|             debug.h          : Debug routines header
|             dialogs.c        : Dialog boxes source
|             dialogs.h        : Dialog boxes header
|             dibinfo.c        : DIB information source
|             dibinfo.h        : DIB information header
|             dibs.c           : DIB handling source
|             dibs.h           : DIB handling header
|             icmview.c        : Entry point source
|             icmview.h        : Entry point header
|             icmview.def      : Def file for application
|             icmview.ico      : Icon for application
|             ICMView.rc       : Resource file
|             makefile         : Generic make file for application
|             print.c          : Printing routines source
|             print.h          : Printing routines header
|             readme.txt       : Readme file about ICMView
|             regutil.c        : Registry utilities source
|             regutil.h        : Registry utilities header
|             resource.h       : Resource header file
|             small.ico        : Small icon for application
|

NOTE: The ICMView sample requires the BITMAPV5HEADER structure to compile.  
This structure should be defined in the WINGDI.H file used in the 
compilation process.  If this structure is not defined, you will need 
to obtain an updated version of the Win32 or Windows Platform SDK.
     
