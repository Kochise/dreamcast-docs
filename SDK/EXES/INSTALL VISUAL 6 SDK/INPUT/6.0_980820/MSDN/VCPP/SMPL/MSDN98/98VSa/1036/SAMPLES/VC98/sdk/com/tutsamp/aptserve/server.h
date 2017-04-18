/*+==========================================================================
  File:      SERVER.H

  Summary:   Internal include file for the APTSERVE.EXE local server code
             sample.  Contains class declarations, resource IDs and string
             macros for internal use in constructing this EXE as a local
             COM component server using Apartment model multi-threading.
             Declares the CServer server control object class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial APTSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   CServer.

  Functions: none

  Origin:    3-11-97: atrent - Editor-inheritance from SERVER.H in
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

// Period to wait for all apartment threads to exit/terminate (8 seconds).
#define LONG_WAIT 8000

// Appartment Thread Initialization data.
enum { NUM_APARTMENTS = 3 };
enum { APTCAR = 0, APTUTILITYCAR = 1, APTCRUISECAR = 2 };
struct APT_INIT_DATA
{
  REFCLSID rclsid;
  IUnknown* pcf;

  // Member initializer MUST be used here because VC++ 4.0+ is strict
  // about const and reference (&) types like REFCLSID that need to
  // be initialized in this app.  For example, VC++ 4.x will not permit
  // a simple assignment of rclsid in the constructor.
  APT_INIT_DATA(REFCLSID rclsidi) : rclsid(rclsidi)
  {
    pcf = NULL;
  };

  ~APT_INIT_DATA() {};
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CServer

  Summary:  Class to encapsulate control of this COM server (eg, handle
            Lock and Object counting, encapsulate otherwise global data).
            Govern server and Apartment lifetimes.

  Methods:  none
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CServer : public CThreaded
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

    // CThreaded method overrides.
    BOOL OwnThis(void);
    void UnOwnThis(void);

    // A place to store the server's instance handle.
    HINSTANCE m_hInstServer;

    // A place to store the server's main window.
    HWND      m_hWndServer;

    // Global Server living Object count.
    LONG      m_cObjects;

    // Global Server Client Lock count.
    LONG      m_cLocks;

    // Some member variables to store pointers to Class Factories.
    IUnknown* m_pCFCar;
    IUnknown* m_pCFUtilityCar;
    IUnknown* m_pCFCruiseCar;

    // Pointers to Apartment init data structures.
    APT_INIT_DATA* m_paiAptCar;
    APT_INIT_DATA* m_paiAptUtilityCar;
    APT_INIT_DATA* m_paiAptCruiseCar;

    // Some member variables to store apartment thread ids.
    DWORD     m_dwAptCar;
    DWORD     m_dwAptUtilityCar;
    DWORD     m_dwAptCruiseCar;

    // An array of handles to the apartment threads.
    HANDLE    m_hApts[NUM_APARTMENTS];
};

#endif // __cplusplus

// Allow other internal APTSERVE modules to get at the globals.
extern CServer*  g_pServer;
extern CSendLog* g_pMsgLog;

#endif // SERVER_H
