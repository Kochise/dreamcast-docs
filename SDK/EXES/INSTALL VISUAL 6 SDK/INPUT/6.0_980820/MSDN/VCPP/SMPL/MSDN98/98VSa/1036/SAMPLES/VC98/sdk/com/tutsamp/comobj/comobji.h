/*+==========================================================================
  File:      COMOBJI.H

  Summary:   Internal include file for the COMOBJ.DLL skeleton code sample.
             Contains class declarations, Resource IDs and string macros for
             internal use in constructing this DLL.  Instead of one
             COMOBJ.H we split what would be the content of that file
             into two files.  One file, COMOBJ.H has only the external
             definitions needed for outside use of the DLL.  The other file,
             this current COMOBJI.H has definitions not needed by external
             users of the DLL but needed for internal use.

             For a comprehensive tutorial code tour of COMOBJ's
             contents and offerings see the tutorial COMOBJ.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the COMOBJ source code.

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


#if !defined(COMOBJI_H)
#define COMOBJI_H

// Allow other internal COMOBJ modules to get at the g_pMsgLog.
extern CMsgLog* g_pMsgLog;


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

  // A Pointer to a Message Box object.
  CMsgBox* pMsgBox;
};

// String Macros.
#define ABOUT_TITLE_STR "COMOBJ: Tutorial Code Sample"

// Dialog IDs.
#define IDD_ABOUTBOX                1000

// Error-related String Identifiers.
#define IDS_ASSERT_FAIL             2200

#endif
