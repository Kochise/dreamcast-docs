/*+==========================================================================
  File:      SERVER.H

  Summary:   Internal include file for the LICSERVE.DLL server code
             sample.  Contains class declarations, Resource IDs and
             string macros for internal use in constructing this DLL
             as a COM component server.  Declares the CServer server
             control object class to control server object and lock
             counts as well as server licensing.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial LICSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CServer.

  Functions: none

  Origin:    10-5-95: atrent - Editor-inheritance from CAR.H in
               the COMOBJ Tutorial Code Sample.

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


#if !defined(SERVER_H)
#define SERVER_H

// String Macros.
#define ABOUT_TITLE_STR  "LICSERVE: Tutorial Code Sample"
#define LICENSE_EXT_STR  ".LIC"

#define MAX_LICENSEKEY              128

// Dialog IDs.
#define IDD_ABOUTBOX                1000

// Error-related String Identifiers.
#define IDS_ASSERT_FAIL             2200

#ifdef __cplusplus

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CServer

  Summary:  Class to encapsulate control of this COM server (eg, handle
            Lock and Object counting, encapsulate otherwise global data).

  Methods:  none
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CServer
{
  public:
    CServer(void);
    ~CServer(void);

    void Lock(void);
    void Unlock(void);
    void ObjectsUp(void);
    void ObjectsDown(void);
    BOOL CheckLicense(void);

    // A place to store the handle to loaded instance of this DLL module.
    HINSTANCE m_hDllInst;

    // A place to store a client's parent window.
    HWND m_hWndParent;

    // A Pointer to a Message Box object.
    CMsgBox* m_pMsgBox;

    // Global DLL Server living Object count.
    LONG m_cObjects;

    // Global DLL Server Client Lock count.
    LONG m_cLocks;

    // The Machine License key string for the LICSERVE server.
    CHAR m_szLicenseKey[MAX_LICENSEKEY];

    // Length of the global g_szLicenseKey string.
    UINT m_cLicenseLen;

    // Machine license verified.
    BOOL m_bLicensed;
};

#endif // __cplusplus

// Allow other internal LICSERVE modules to get at the globals.
extern CServer* g_pServer;
extern CMsgLog* g_pMsgLog;


#endif // SERVER_H
