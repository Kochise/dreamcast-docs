/*+==========================================================================
  File:      SERVER.H

  Summary:   Internal include file for the DCDSERVE.EXE out-of-process
             server. Declares the CServer server control object class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DCDSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CServer.

  Functions: none.

  Origin:    8-23-97: atrent - Editor-inheritance from SERVER.H in
               the LOCSERVE Tutorial Code Sample. [Revised]

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
            There is an instance of CServer for every attached process.

  Methods:  none
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CServer : public CThreaded
{
  public:
    CServer(void);
    ~CServer(void);

    // Methods for server lifetime control: object counts and lock counts.
    void Lock(void);
    void Unlock(void);
    void ObjectsUp(void);
    void ObjectsDown(void);
    BOOL ObjectFirst(void);
    HRESULT ObjectSet(IUnknown* pCob);
    HRESULT ObjectQI(REFIID riid, PPVOID ppv);
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
    IUnknown* m_pCFPaper;

    // Some member variables to store Class Factory registration keys.
    DWORD m_dwCFPaper;

    // Global IUnknown interface pointer to the single COPaper object.
    IUnknown* m_pCOPaper;
};

#endif // __cplusplus

// Allow other internal DCDSERVE modules to get at the globals.
extern CServer* g_pServer;


#endif // SERVER_H
