/*+==========================================================================
  File:      SERVER.CPP

  Summary:   Implementation file for the CServer server-related utility
             C++ object.  This object encapsulates the server's internal
             control of global server object and lock counts.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial LOCSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   CServer.

  Functions:

  Origin:    11-14-95: atrent - Editor-inheritance from DLLSERVE.CPP in
               the DLLSERVE Tutorial Code Sample.

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
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include APPUTIL.H because we will be building this EXE using
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
#include <apputil.h>
#include <micars.h>
#include <carguids.h>
#include "server.h"
#include "factory.h"


/*---------------------------------------------------------------------------
  Implementation the internal CServer C++ object.  Used to encapsulate
  some server data and the methods for Lock and Object count incrementing
  and decrementing.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::CServer

  Summary:  CServer Constructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CServer::CServer(void)
{
  // Zero the Object and Lock counts.
  m_cObjects = 0;
  m_cLocks = 0;

  // Zero the cached handles.
  m_hInstServer = NULL;
  m_hWndServer = NULL;

  // Zero the Factory references.
  m_pCFCar = NULL;
  m_pCFUtilityCar = NULL;
  m_pCFCruiseCar = NULL;
  m_dwCFCar = 0;
  m_dwCFUtilityCar = 0;
  m_dwCFCruiseCar = 0;

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
  Method:   CServer::ObjectsUp

  Summary:  Increment the Server's living Object count.

  Args:     void

  Modifies: m_cObjects.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::ObjectsUp(void)
{
  InterlockedIncrement((PLONG) &m_cObjects);

  LOGF1("L: CServer::ObjectsUp. New cObjects=%i.", m_cObjects);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::ObjectsDown

  Summary:  Decrement the Server's living object count.

  Args:     void

  Modifies: m_cObjects.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::ObjectsDown(void)
{
  InterlockedDecrement((PLONG) &m_cObjects);

  LOGF1("L: CServer::ObjectsDown. New cObjects=%i.", m_cObjects);

  // If no more living objects and no locks then shut the server down.
  if (0L == m_cObjects && 0L == m_cLocks && IsWindow(m_hWndServer))
  {
    LOG("L: CServer::ObjectsDown. Closing down LOCSERVE server.");
    // Post a message to this local server's message queue requesting
    // a close of the application.
    PostMessage(m_hWndServer, WM_CLOSE, 0, 0L);
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
  InterlockedIncrement((PLONG) &m_cLocks);

  LOGF1("L: CServer::Lock. New cLocks=%i.", m_cLocks);

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
  InterlockedDecrement((PLONG) &m_cLocks);

  LOGF1("L: CServer::Unlock. New cLocks=%i.", m_cLocks);

  // Use ObjectsDown to force a server shutdown if this unlock warrants it.
  InterlockedIncrement((PLONG) &m_cObjects);
  ObjectsDown();

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::OpenFactories

  Summary:  Create and register all of this server's class factories.

  Args:     void

  Modifies: m_pCFCar, m_pCFUtilityCar, m_pCFCruiseCar,
            m_dwCFCar, m_dwCFUtilityCar, m_dwCFCruiseCar.

  Returns:  BOOL
              TRUE if success; FALSE if not
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CServer::OpenFactories(void)
{
  BOOL bOk = FALSE;
  HRESULT hr;

  LOG("L: CServer::OpenFactories. Begin.");

  // Build and register the LocCar factory.
  m_pCFCar = new CFCar(NULL, this);
  if (NULL != m_pCFCar)
  {
    // AddRef this cached pointer to the Class Factory.
    m_pCFCar->AddRef();

    // Now register this class factory with COM.
    hr = CoRegisterClassObject(
           CLSID_LocCar,
           m_pCFCar,
           CLSCTX_LOCAL_SERVER,
           REGCLS_MULTIPLEUSE,
           &m_dwCFCar);

    bOk = SUCCEEDED(hr);
    if (!bOk)
    {
      LOGF1("L: CServer::OpenFactories. CFCar failed. hr=0x%X.", hr);
      // If can't register factory then clean up for server exit.
      m_pCFCar->Release();
      DELETE_POINTER(m_pCFCar);
    }
  }
  else
    bOk = FALSE;

  // Build and register the LocUtilityCar factory.
  if (bOk)
  {
    m_pCFUtilityCar = new CFUtilityCar(NULL, this);
    if (NULL != m_pCFUtilityCar)
    {
      // AddRef this cached pointer to the Class Factory.
      m_pCFUtilityCar->AddRef();

      // Now register this class factory with COM.
      hr = CoRegisterClassObject(
             CLSID_LocUtilityCar,
             m_pCFUtilityCar,
             CLSCTX_LOCAL_SERVER,
             REGCLS_MULTIPLEUSE,
             &m_dwCFUtilityCar);

      bOk = SUCCEEDED(hr);
      if (!bOk)
      {
        LOGF1("L: CServer::OpenFactories. CFUtilityCar failed. hr=0x%X.", hr);
        // If can't register factory then clean up for server exit.
        m_pCFUtilityCar->Release();
        DELETE_POINTER(m_pCFUtilityCar);
      }
    }
    else
      bOk = FALSE;
  }

  // Build and register the LocCruiseCar factory.
  if (bOk)
  {
    m_pCFCruiseCar = new CFCruiseCar(NULL, this);
    if (NULL != m_pCFCruiseCar)
    {
      // AddRef this cached pointer to the Class Factory.
      m_pCFCruiseCar->AddRef();

      // Now register this class factory with COM.
      hr = CoRegisterClassObject(
             CLSID_LocCruiseCar,
             m_pCFCruiseCar,
             CLSCTX_LOCAL_SERVER,
             REGCLS_MULTIPLEUSE,
             &m_dwCFCruiseCar);

      bOk = SUCCEEDED(hr);
      if (!bOk)
      {
        LOGF1("L: CServer::OpenFactories. CFCruiseCar failed. hr=0x%X.", hr);
        // If can't register factory then clean up for server exit.
        m_pCFCruiseCar->Release();
        DELETE_POINTER(m_pCFCruiseCar);
      }
    }
    else
      bOk = FALSE;
  }

  LOG("L: CServer::OpenFactories. End.");

  return bOk;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::CloseFactories

  Summary:  Revoke (ie, unregister) and delete all the server's class
            factories.

  Args:     void

  Modifies: m_pCFCar, m_pCFUtilityCar, m_pCFCruiseCar.

  Returns:  BOOL
              TRUE if success; FALSE if not
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CServer::CloseFactories(void)
{
  BOOL bOk = TRUE;
  HRESULT hr;

  LOG("L: CServer::CloseFactories. Begin.");

  // Unregister the LocCar class factory with COM.
  if (0 != m_dwCFCar)
  {
    LOG("L: CServer::CloseFactories. Revoke CFCar.");
    hr = CoRevokeClassObject(m_dwCFCar);
    if (FAILED(hr))
      bOk = FALSE;
  }

  // Unregister the LocUtilityCar class factory with COM.
  if (0 != m_dwCFCar)
  {
    LOG("L: CServer::CloseFactories. Revoke CFUtilityCar.");
    hr = CoRevokeClassObject(m_dwCFUtilityCar);
    if (FAILED(hr))
      bOk = FALSE;
  }

  // Unregister the LocCruiseCar class factory with COM.
  if (0 != m_dwCFCar)
  {
    LOG("L: CServer::CloseFactories. Revoke CFCruiseCar.");
    hr = CoRevokeClassObject(m_dwCFCruiseCar);
    if (FAILED(hr))
      bOk = FALSE;
  }

  // Release any and all of the Class Factory interface pointers.
  LOG("L: CServer::CloseFactories. Release all factory interfaces.");
  RELEASE_INTERFACE(m_pCFCar);
  RELEASE_INTERFACE(m_pCFUtilityCar);
  RELEASE_INTERFACE(m_pCFCruiseCar);

  LOG("L: CServer::CloseFactories. End.");

  return bOk;
}

// =============================== END ======================================
