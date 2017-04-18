/*+==========================================================================
  File:      REGISTER.H

  Summary:   Include file for the REGISTER.EXE utility application.
             REGISTER.H contains definitions of the application's string
             resource IDs.

             For a comprehensive tutorial code tour of REGISTER's
             contents and offerings see the tutorial REGISTER.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the REGISTER source code.

  Classes:   .

  Functions: WinMain

  Origin:    9-15-95: atrent - Created based on the EXESKEL code sample.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is only intended as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

#if !defined(REGISTER_H)
#define REGISTER_H

#define MAX_STRING 128

// Error-related String Identifiers.
#define IDS_COMINITFAILED           2000
#define IDS_OUTOFMEMORY             2001
#define IDS_DLLUNREG_FAIL           2002
#define IDS_DLLREG_FAIL             2003
#define IDS_LOADLIB_FAIL            2004
#define IDS_EXERUN_FAIL             2005

#define IDS_ASSERT_FAIL             2200

// Notice-related Identifiers.
#define IDS_NOTIMPLEMENTED          2301
#define IDD_SUCCESS_MSG             2350

#define IDS_ERROR_TITLE             2400

#endif
