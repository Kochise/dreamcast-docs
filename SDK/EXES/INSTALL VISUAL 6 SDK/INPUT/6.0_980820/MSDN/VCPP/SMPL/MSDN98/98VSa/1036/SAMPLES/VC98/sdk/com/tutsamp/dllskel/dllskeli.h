/*+==========================================================================
  File:      DLLSKELI.H

  Summary:   Internal include file for the DLLSKEL.DLL skeleton code sample.
             Contains class declarations, Resource IDs and string macros for
             internal use in constructing this DLL.  Instead of one
             DLLSKEL.H we split what would be the content of that file
             into two files.  One file, DLLSKEL.H has only the external
             definitions needed for outside use of the DLL.  The other file,
             this current DLLSKELI.H has definitions not needed by external
             users of the DLL but needed for internal use.

             For a comprehensive tutorial code tour of DLLSKEL's
             contents and offerings see the tutorial DLLSKEL.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the DLLSKEL source code.

  Classes:   none

  Functions: none

  Origin:    8-5-95: atrent - Editor-inheritance from the EXESKEL source.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

#if !defined(DLLSKELI_H)
#define DLLSKELI_H


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CDllData

  Summary:  Class to encapsulate global data of a the DLL.

  Methods:  none
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CDllData
{
public:
  // A place to store the loaded instance of this DLL module.
  HINSTANCE hDllInst;

  // A place in this instance data to save this DLL's user count.
  int iUserCount;

  // A Pointer to a Message Box object.
  CMsgBox* pMsgBox;
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CDllShared

  Summary:  Class to encapsulate shared data of a the DLL.

  Methods:  none
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CDllShared
{
public:
  // The hello counter. A global shared counter that is Incremented
  // by all DLL users
  int iHelloCount;

  // The global data instance counter. A count of the Processes that attach.
  int iUserCount;
};

// String Macros.
#define ABOUT_TITLE_STR "DLLSKEL: Tutorial Code Sample"

// Dialog IDs.
#define IDD_ABOUTBOX                1000

// Error-related String Identifiers.
#define IDS_COMINITFAILED           2000
#define IDS_DLLINITFAILED           2001
#define IDS_OUTOFMEMORY             2002
#define IDS_NOHELPFILE              2003

#define IDS_ASSERT_FAIL             2200

// Notice-related String Identifiers.
#define IDS_NOTIMPLEMENTED          2301
#define IDS_HELLOCOUNTFMT           2302
#define IDS_HELLOTITLE              2303

#endif
