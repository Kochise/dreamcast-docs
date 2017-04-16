=======================================================================
The Preparing Localizing Strings Sample kit.

Basic Overview
=======================================================================

The Preparing Localizing Strings Sample contains the following files...


1) AccATM.mdb
-------------
   This is a Microsoft Access 7.0 database that demonstrates how to 
   implement the Preparing Localizing Strings Sample.

2) AccATM.dll
-------------
   This is an OLE Server DLL used to demonstrates how to 
   implement the Preparing Localizing Strings Sample.  Use the following
   syntax to manually register the dll...

     regsrv32 <path>\AccATM.dll

   (note: regsrv32.exe is included...)

3) AccATM.mdt
-------------
   A sample setup template to use with the Microsoft Access 95
   Developers Toolkit's (ADT) "Setup Wizard" application.  This file
   contains all of the options needed to install the database and the
   OLE Server DLL using the ADT.

4) vbsource.exe
---------------
   The self-extracting sample source code for the OLE Server DLL to use 
   with Microsoft Visual Basic 4.0.

5) rcsource.exe
---------------
   The self-extracting sample source for the Resource File and Icons to
   use with Microsoft Visual Basic 4.0.

6) zipsetup.exe
---------------
   A self-extracting zip file that will install the components on a machine
   that has the retail version of Microsoft Access.  You must unzip 
   the file in the same directory where the AccATM.mdb file is located
   for the setup to work correctly