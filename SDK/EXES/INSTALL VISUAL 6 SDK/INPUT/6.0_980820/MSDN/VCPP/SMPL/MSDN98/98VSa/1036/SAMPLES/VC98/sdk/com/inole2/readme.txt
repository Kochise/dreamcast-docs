===========================================================
           INSIDE OLE BY KRAIG BROCKSCHMIDT
                    COMPANION DISC
       COPYRIGHT (C) 1995 BY KRAIG BROCKSCHMIDT
===========================================================

This companion CD contains the sample source code and
related support files for the examples presented in Inside
OLE by Kraig Brockschmidt. We recommend that you store this
disc in a safe place after you install the files.




		     INSTALLATION

The files on this disc are not compressed and can be copied
to your hard disk by running the Setup program (under Windows
NT or Windows 95) or by dragging the files in the CODE directory
to an INOLE directory on your hard disk using File Manager or
another utility (under 16-bit Windows). You must have at least
7.5 MB of free space on your hard disk to install the files.

**************************************************************
*                                                            *
*                        IMPORTANT                           *
*                                                            *
**************************************************************

Many of the samples include a REG (registration) file that
must be "run" before the samples will work. Double click
on the file in FIle Manager or Explorer to "run" them.  If you
are working on Win32 platforms, use WIN32.REG.  If you are
working on Windows 3.1x, use WIN16.REG.

The REG files assume that you install the files to C:\INOLE;
you'll need to edit the REG files if you install the files
to another directory.  Simply replace all occurances of
"c:\inole" with the actual installation directory.




             DISC CONTENTS

The sample source code and support files for each chapter 
are stored under CHAPXX, where XX is the chapter number. 
For example, all files for Chapter 2 are in the CHAP02 
directory. Several other directories contain files that you 
will need for compilation or that you might want to study. 
They include:

DIRECTORY     CONTENTS
---------     --------
BUILD         Contains the  DLL and EXE files created by
              MAKEALL.BAT files. It is recommended that you
              add this directory to your path.

CLASSLIB      C++ class library created for this book.

INC           Include files (H) needed for this book.
              Must be in your INCLUDE environment path.

INTERFAC      OLE template interface implementations.

LIB           Library files (LIB) needed for this book.
              Must be in your LIB environment path.


See the file CONTENTS.TXT for a full description of the
contents of the companion disC.

Be sure that all environment variables are set correctly for
your compiler. For example, if you have the Inside OLE files,
Visual C++ 2.0, the Win32 SDK, and the OLE controls development
kit installed on drive C, your environment variables should
include the following (long lines have been broken):

INCLUDE=C:\MSVC20\INCLUDE;C:\MSVC20\MFC\INCLUDE;C:\MSVC20\CDK32\INCLUDE;
        C:\MSTOOLS\IDL;C:\MSTOOLS\H;C:\INOLE\INC
LIB=C:\MSVC20\LIB;C:\MSVC20\MFC\LIB;C:\MSVC20\CDK32\LIB;
    C:\MSTOOLS\LIB;C:\INOLE\LIB
PATH=C:\MSVC20\BIN;C:\MSVC20\CDK32\BIN;C:\MSTOOLS\BIN;C:\INOLE\BUILD


Check your compiler's documentation for more information.

NOTE: You might need to increase your environment size to accommodate
the environment variables.




         BUILDING THE SAMPLE PROGRAMS

To compile all the sample programs on this disc, run the MAKEALL.BAT
batch file in the installation directory. You must add the INCLUDE
and LIB directories from this installation to the INCLUDE and LIB
environment variables as detailed above.

For detailed information on the build process and the files
involved, see the file BUILD.TXT.  This file also includes
information on the OLE UI Library and the MIDL compiler which
may be important for your work with these samples




        KNOWN ERRORS AND PROBLEMS

As the printed copy of this book was finalized, extensive testing
and debugging were performed on the samples on Windows 3.1x (16-bit),
Windows NT 3.5 and 3.51, and Windows 95, the latter two platforms
being still in pre-release form at the time of production.  As bugs
are invariably found, there are several places where the book text
does not match the sample code.  The file ERRATA.TXT points out these
discrepancies and contains the most up-to-date information.  Please
take a few moments to review ERRATA.TXT and mark the printed
book as appropriate.




  IF THERE ARE PROBLEMS WITH THIS DISC OR THE SAMPLES

Every effort was made to ensure the accuracy of the book and
this disc. Should you encounter a problem, please contact
us at the following address:

    Microsoft Press
    Attn: Inside OLE Editor
    One Microsoft Way
    Redmond, WA  98052-6399

No telephone calls, please.

The author also welcomes your comments through email at
kraigb@microsoft.com.  Due to the potential volume of email,
responses are not guaranteed.  For timely support of OLE
questions or problems, contact Microsoft Developer Support
Services.
