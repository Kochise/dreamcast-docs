/*+==========================================================================
  File:      SERVER.H

  Summary:   Internal include file for the LOCSERVE.DLL server code
             sample.  Contains class declarations, resource IDs and string
             macros for internal use in constructing this EXE as a local
             COM component server.  Declares the CServer server control
             object class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial LOCSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   CServer.

  Functions: none

  Origin:    8-29-97: atrent - Editor-inheritance from SERVER.H in
               the DLLSERVE Tutorial Code Sample. [Revised]

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
    BOOL OpenFactories(void);
    BOOL CloseFactories(void);

    // A place to store the server's instance handle.
    HINSTANCE m_hInstServer;

    // A place to store the server's main window.
    HWND m_hWndServer;

    // Global Server living Object count.
    LONG m_cObjects;

    // Global Server Client Lock count.
    LONG m_cLocks;

    // Some member variables to store pointers to Class Factories.
    IUnknown* m_pCFCar;
    IUnknown* m_pCFUtilityCar;
    IUnknown* m_pCFCruiseCar;

    // Some member variables to store Class Factory registration keys.
    DWORD m_dwCFCar;
    DWORD m_dwCFUtilityCar;
    DWORD m_dwCFCruiseCar;
};

#endif // __cplusplus

// Allow other internal LOCSERVE modules to get at the globals.
extern CServer*  g_pServer;
extern CSendLog* g_pMsgLog;

#endif // SERVER_H
