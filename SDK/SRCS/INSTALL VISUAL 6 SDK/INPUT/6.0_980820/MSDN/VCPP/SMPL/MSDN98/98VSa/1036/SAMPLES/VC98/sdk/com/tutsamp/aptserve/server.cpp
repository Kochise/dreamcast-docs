/*+==========================================================================
  File:      SERVER.CPP

  Summary:   Implementation file for the CServer server control utility
             C++ object.  This object encapsulates the server's internal
             control of global server object and lock counts to govern
             server lifetime.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial APTSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   CServer.

  Functions: .

  Origin:    1-17-97: atrent - Editor-inheritance from SERVER.CPP in
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

/*---------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will make calls to the COM/OLE Libraries.
  We include PROCESS.H because we will be using the C-Runtime's
    _beginthreadex function.
  We include APPUTIL.H because we will be building this DLL using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include MICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include SERVER.H for the object class declarations for the
    C++ CServer server control object.
  We include FACTORY.H because it has the necessary internal class factory
    declarations for this component server.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <process.h>
#include <apputil.h>
#include <micars.h>
#include <carguids.h>
#include "server.h"
#include "factory.h"


/*---------------------------------------------------------------------------
  Implementation the internal CServer C++ object.  Used to encapsulate
  global server data and the methods for Lock and Object count incrementing
  and decrementing.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::CServer

  Summary:  CServer Constructor.

  Args:     void

  Modifies: lots-o-stuff.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CServer::CServer(void)
{
  // Zero the Object and Lock counts for this server.
  m_cObjects = 0;
  m_cLocks = 0;

  // Zero the cached handles.
  m_hInstServer = NULL;
  m_hWndServer = NULL;

  // Zero the Factory and Apartment thread references.
  m_pCFCar = NULL;
  m_pCFUtilityCar = NULL;
  m_pCFCruiseCar = NULL;
  m_paiAptCar = NULL;
  m_paiAptUtilityCar = NULL;
  m_paiAptCruiseCar = NULL;
  m_dwAptCar = 0;
  m_dwAptUtilityCar = 0;
  m_dwAptCruiseCar = 0;

  // NULL the apartment handle array
  for (UINT i = 0; i<NUM_APARTMENTS; i++)
    m_hApts[i] = NULL;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::~CServer

  Summary:  CServer Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CServer::~CServer(void)
{

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::OwnThis

  Summary:  Wait for multithread exclusive ownership of this CServer object.
            This definition overrides the virtual function defined in the
            CThreaded base class to permit convenient trace logging here.

  Args:     void

  Modifies: m_bOwned.

  Returns:  BOOL
              TRUE if success; FALSE if not.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CServer::OwnThis(void)
{
  BOOL bOwned = FALSE;

  LOGF1("L: CServer::OwnThis. Thread <%X> waiting to own CServer.",TID);

  if (WAIT_OBJECT_0 == WaitForSingleObject(m_hOwnerMutex, INFINITE))
  {
    m_bOwned = bOwned = TRUE;
    LOGF1("L: CServer::OwnThis. CServer now owned by Thread <%X>.",TID);
  }

  return bOwned;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::UnOwnThis

  Summary:  Relinquish ownership of this CServer object.
            This definition overrides the virtual function defined in the
            CThreaded base class to permit convenient trace logging here.

  Args:     void

  Modifies: m_bOwned.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::UnOwnThis(void)
{
  if (m_bOwned)
  {
    LOGF1("L: CServer::UnOwnThis. Ownership relinquished by <%X>.",TID);
    m_bOwned = FALSE;
    ReleaseMutex(m_hOwnerMutex);
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::ObjectsUp

  Summary:  Increment the Server's living Object count.

  Args:     void

  Modifies: m_cObjects.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::ObjectsUp(void)
{
  if (OwnThis())
  {
    m_cObjects += 1;
    LOGF2("L<%X>: CServer::ObjectsUp. New cObjects=%i.",TID,m_cObjects);

    UnOwnThis();
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::ObjectsDown

  Summary:  Decrement the Server's living object count. Trigger an unload
            of this entire server if no more living components.

  Args:     void

  Modifies: m_cObjects.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::ObjectsDown(void)
{
  if (OwnThis())
  {
    if (m_cObjects > 0)
      m_cObjects -= 1;

    LOGF2("L<%X>: CServer::ObjectsDown. New cObjects=%i.",TID,m_cObjects);

    // If no more living objects and no locks then shut down the server.
    if (0L == m_cObjects && 0L == m_cLocks && IsWindow(m_hWndServer))
    {
      LOGF1("L<%X>: CServer::ObjectsDown. Closing down APTSERVE server.",TID);

      // Relinquish current thread ownership of CServer before signaling
      // the main server thread to close down the entire server. During
      // shutdown other threads may need to access CServer.
      UnOwnThis();

      // Post a message to this local server's message queue requesting
      // a close of the entire server application. This will force a
      // termination of all apartment threads (including the one that
      // may be executing this ObjectsDown)
      PostMessage(m_hWndServer, WM_CLOSE, 0, 0L);
    }
    else
      UnOwnThis();
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::Lock

  Summary:  Increment the Server's Lock count.

  Args:     void

  Modifies: m_cLocks.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::Lock(void)
{
  if (OwnThis())
  {
    m_cLocks += 1;

    LOGF2("L<%X>: CServer::Lock. New cLocks=%i.",TID,m_cLocks);

    UnOwnThis();
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::Unlock

  Summary:  Decrement the Server's Lock count.

  Args:     void

  Modifies: m_cLocks.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::Unlock(void)
{
  if (OwnThis())
  {
    m_cLocks -= 1;
    if (m_cLocks < 0)
      m_cLocks = 0;

    LOGF2("L<%X>: CServer::Unlock. New cLocks=%i.",TID,m_cLocks);

    // If no more living objects and no locks then shut down the server.
    if (0L == m_cObjects && 0L == m_cLocks && IsWindow(m_hWndServer))
    {
      LOGF1("L<%X>: CServer::Unlock. Closing down APTSERVE server.",TID);

      // Relinquish current thread ownership of CServer before signaling
      // the main server thread to close down the entire server. During
      // shutdown other threads may need to access CServer.
      UnOwnThis();

      // Post a message to this local server's message queue requesting
      // a close of the entire server application. This will force a
      // termination of all apartment threads (including the one that
      // may be executing this ObjectsDown)
      PostMessage(m_hWndServer, WM_CLOSE, 0, 0L);
    }
    else
      UnOwnThis();
  }

  return;
}


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: StartThread

  Summary:  This local function starts a new execution thread using the
            C-RunTime's _beginthreadex function which takes care of
            necessary business (that the Win32 CreateThread does not) if
            the thread will make calls to C-Runtime functions--a likely
            possibility.

  Args:     PCRTTHREADPROC pThreadProc,
              Address of the Thread Procedure to start executing.
            LPVOID pInitData,
              Address of a structure of initialization data. Instead of
              containing an address, this parameter can also contain a
              single DWORD of data.
            DWORD* pdwThreadId);
              Address of a DWORD variable that will receive the
              thread ID of the new thread.

  Returns:  void.
------------------------------------------------------------------------F-F*/
HANDLE StartThread(
         PCRTTHREADPROC pThreadProc,
         LPVOID pInitData,
         DWORD* pdwThreadId)
{
  HANDLE hThrd;

  hThrd = (HANDLE) _beginthreadex(
                     0,                       // Default security specified.
                     0,                       // Default stack size.
                     pThreadProc,             // Thread Procedure address.
                     (LPVOID) pInitData,      // Address of Init data.
                     0,                       // Default state (running).
                     (unsigned*)pdwThreadId); // Address of ThreadID Var.

  return hThrd;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: AptThreadProc

  Summary:  The common apartment model thread procedure for this server.

  Args:     LPARAM lparam
              Standard Window Proc parameter.

  Modifies: .

  Returns:  unsigned
              Thread procedure return (usually msg.wParam).
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
unsigned WINAPI AptThreadProc(
                  LPARAM lparam)
{
  HRESULT hr;
  MSG msg;
  DWORD dwCFRegId;
  APT_INIT_DATA* paid = (APT_INIT_DATA*) lparam;

  LOGF1("L: AptThreadProc. Starting Apartment Thread <%X>.",TID);

  // Initialize COM for this apartment thread. Default of apartment
  // model is assumed.
  hr = CoInitialize(NULL);

  // Now register the class factory with COM.
  LOGF1("L: AptThreadProc. Registering class factory of apartment <%X>.",TID);
  hr = CoRegisterClassObject(
         paid->rclsid,
         paid->pcf,
         CLSCTX_LOCAL_SERVER,
         REGCLS_MULTIPLEUSE,
         &dwCFRegId);
  LOGERROR("L:CoRegisterClassObject",hr);
  if (SUCCEEDED(hr))
  {
    // Provide a message pump for this thread.
    while (GetMessage(&msg, 0, 0, 0))
      DispatchMessage(&msg);

    LOGF1("L: AptThreadProc. Revoking class factory of apartment <%X>.",TID);
    // Unregister the class factory with COM when the thread dies.
    CoRevokeClassObject(dwCFRegId);
  }
  else
  {
    LOGF2("L<%X>: AptThreadProc. RegisterClass failed. hr=0x%X.",TID,hr);
  }

  // Uninitialize COM in the context of this apartment thread.
  CoUninitialize();

  LOGF1("L: AptThreadProc. Apartment Thread <%X> Terminated.",TID);

  return msg.wParam;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::OpenFactories

  Summary:  Create and register all of this server's class factories.

  Args:     void

  Modifies: See below.

  Returns:  BOOL
              TRUE if success; FALSE if not
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CServer::OpenFactories(void)
{
  BOOL bOk = FALSE;
  HRESULT hr;

  LOGF1("L<%X>: CServer::OpenFactories. Begin.",TID);

  if (OwnThis())
  {
    // Create the ClassFactory C++ objects.
    m_pCFCar = new CFCar(NULL, this);
    m_pCFUtilityCar = new CFUtilityCar(NULL, this);
    m_pCFCruiseCar = new CFCruiseCar(NULL, this);

    // Create Structures for Apartment initialization.
    m_paiAptCar = new APT_INIT_DATA(CLSID_AptCar);
    m_paiAptUtilityCar = new APT_INIT_DATA(CLSID_AptUtilityCar);
    m_paiAptCruiseCar = new APT_INIT_DATA(CLSID_AptCruiseCar);

    // Create the Appartment for AptCar.
    LOGF1("L<%X>: CServer::OpenFactories. AptCar.",TID);
    if (NULL != m_pCFCar && NULL != m_paiAptCar)
    {
      // AddRef this cached pointer to the Class Factory.
      m_pCFCar->AddRef();

      // Assign the ClassFactory in the apartment init data and AddRef.
      m_paiAptCar->pcf = m_pCFCar;
      m_paiAptCar->pcf->AddRef();

      // Start the Apartment Thread using a local utility function.
      m_hApts[APTCAR] = StartThread(
                          (PCRTTHREADPROC) AptThreadProc,
                          (LPVOID) m_paiAptCar,
                          &m_dwAptCar);

      bOk = (NULL != m_hApts[APTCAR]);
      if (!bOk)
      {
        hr = GetLastError();
        LOGF2("L<%X>: CServer::OpenFactories. AptCar failed. hr=0x%X.",TID,hr);
        // If can't register factory then clean up for server exit.
        m_pCFCar->Release();
        m_paiAptCar->pcf->Release();
        DELETE_POINTER(m_pCFCar);
        DELETE_POINTER(m_paiAptCar);
      }
    }
    else
      bOk = FALSE;

    // Create the Appartment for AptUtiliytCar.
    LOGF1("L<%X>: CServer::OpenFactories. AptUtilityCar.",TID);
    if (bOk)
    {
      if (NULL != m_pCFUtilityCar && NULL != m_paiAptUtilityCar)
      {
        // AddRef this cached pointer to the Class Factory.
        m_pCFUtilityCar->AddRef();

        // Assign the ClassFactory in the apartment init data and AddRef again.
        m_paiAptUtilityCar->pcf = m_pCFUtilityCar;
        m_paiAptUtilityCar->pcf->AddRef();

        // Start the Apartment Thread using a local utility function.
        m_hApts[APTUTILITYCAR] = StartThread(
                                   (PCRTTHREADPROC) AptThreadProc,
                                   (LPVOID) m_paiAptUtilityCar,
                                   &m_dwAptUtilityCar);

        bOk = (NULL != m_hApts[APTUTILITYCAR]);
        if (!bOk)
        {
          hr = GetLastError();
          LOGF2("L<%X>: CServer::OpenFactories. AptUtilityCar failed. hr=0x%X.",TID,hr);
          // If can't register factory then clean up for server exit.
          m_pCFUtilityCar->Release();
          m_paiAptUtilityCar->pcf->Release();
          DELETE_POINTER(m_pCFUtilityCar);
          DELETE_POINTER(m_paiAptUtilityCar);
        }
      }
      else
        bOk = FALSE;
    }

    // Create the Appartment for AptCruiseCar.
    LOGF1("L<%X>: CServer::OpenFactories. AptCruiseCar.",TID);
    if (bOk)
    {
      if (NULL != m_pCFCruiseCar && NULL != m_paiAptCruiseCar)
      {
        // AddRef this cached pointer to the Class Factory.
        m_pCFCruiseCar->AddRef();

        // Assign the ClassFactory in the apartment init data and AddRef again.
        m_paiAptCruiseCar->pcf = m_pCFCruiseCar;
        m_paiAptCruiseCar->pcf->AddRef();

        // Start the Apartment Thread using a local utility function.
        m_hApts[APTCRUISECAR] = StartThread(
                                  (PCRTTHREADPROC) AptThreadProc,
                                  (LPVOID) m_paiAptCruiseCar,
                                  &m_dwAptCruiseCar);

        bOk = (NULL != m_hApts[APTCRUISECAR]);
        if (!bOk)
        {
          hr = GetLastError();
          LOGF2("L<%X>: CServer::OpenFactories. AptCruiseCar failed. hr=0x%X.",TID,hr);
          // If can't register factory then clean up for server exit.
          m_pCFCruiseCar->Release();
          m_paiAptCruiseCar->pcf->Release();
          DELETE_POINTER(m_pCFCruiseCar);
          DELETE_POINTER(m_paiAptCruiseCar);
        }
      }
      else
        bOk = FALSE;
    }

    UnOwnThis();
  }

  LOGF1("L<%X>: CServer::OpenFactories. End.",TID);

  return bOk;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::CloseFactories

  Summary:  Shutdown the class factory apartments. Revoke (ie, unregister)
            and delete all the server's class factories too.

  Args:     void

  Modifies: .

  Returns:  BOOL
              TRUE if success; FALSE if not
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CServer::CloseFactories(void)
{
  BOOL bOk = TRUE;
  HRESULT hr;

  LOGF1("L<%X>: CServer::CloseFactories. Begin.",TID);

  if (OwnThis())
  {
    // Shutdown the AptCar Apartment Thread.
    if (0 != m_dwAptCar)
    {
      LOGF1("L<%X>: CServer::CloseFactories. Terminate AptCar Apartment.",TID);
      bOk = PostThreadMessage(m_dwAptCar, WM_QUIT, 0, 0);
      if (!bOk)
      {
        hr = GetLastError();
        LOGF2("L<%X>: CServer::CloseFactories. AptCar failed. hr=0x%X.",TID,hr);
      }
    }

    // Shutdown the AptUtilityCar Apartment Thread.
    if (0 != m_dwAptUtilityCar)
    {
      LOGF1("L<%X>: CServer::CloseFactories. Terminate AptUtilityCar Apartment.",TID);
      bOk = PostThreadMessage(m_dwAptUtilityCar, WM_QUIT, 0, 0);
      if (!bOk)
      {
        hr = GetLastError();
        LOGF2("L<%X>: CServer::CloseFactories. AptUtilityCar failed. hr=0x%X.",TID,hr);
      }
    }

    // Shutdown the AptCruiseCar Apartment Thread.
    if (0 != m_dwAptCruiseCar)
    {
      LOGF1("L<%X>: CServer::CloseFactories. Terminate AptCruiseCar Apartment.",TID);
      bOk = PostThreadMessage(m_dwAptCruiseCar, WM_QUIT, 0, 0);
      if (!bOk)
      {
        hr = GetLastError();
        LOGF2("L<%X>: CServer::CloseFactories. AptCruiseCar failed. hr=0x%X.",TID,hr);
      }
    }

    if (m_pCFCar && m_pCFUtilityCar && m_pCFCruiseCar)
    {
      // Release any and all of the Class Factory interface pointers.
      LOGF1("L<%X>: CServer::CloseFactories. Releasing all Classfactory interfaces.",TID);
      RELEASE_INTERFACE(m_pCFCar);
      RELEASE_INTERFACE(m_paiAptCar->pcf);
      RELEASE_INTERFACE(m_pCFUtilityCar);
      RELEASE_INTERFACE(m_paiAptUtilityCar->pcf);
      RELEASE_INTERFACE(m_pCFCruiseCar);
      RELEASE_INTERFACE(m_paiAptCruiseCar->pcf);
      DELETE_POINTER(m_paiAptCar);
      DELETE_POINTER(m_paiAptUtilityCar);
      DELETE_POINTER(m_paiAptCruiseCar);

      // Give CServer back before waiting on threads to die.
      UnOwnThis();

      // Wait a very long time (in CPU terms) for the apartment threads
      // to exit/terminate before closing their thread handles.
      WaitForMultipleObjects(NUM_APARTMENTS, m_hApts, TRUE, LONG_WAIT);
      for (UINT i = 0; i<NUM_APARTMENTS; i++)
        if (NULL != m_hApts[i])
          CloseHandle(m_hApts[i]);
    }
    else
      UnOwnThis();
  }

  LOGF1("L<%X>: CServer::CloseFactories. End.",TID);

  return bOk;
}

// =============================== END ======================================
