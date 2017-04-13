/*+==========================================================================
  File:      SERVER.CPP

  Summary:   Implementation file for the CServer server control C++
             object.  This object encapsulates the server's internal
             control of global server object and lock counts. The
             CThreaded OwnThis mechanism is used to ensure mutually
             exclusive access to this CServer object by multiple threads.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DCDSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CServer.

  Functions: .

  Origin:    8-23-97: atrent - Editor-inheritance from SERVER.CPP in
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
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include APPUTIL.H because we will be building this EXE using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include PAPINT.H and PAPGUIDS.H for the common paper-related
    Interface class, GUID, and CLSID specifications.
  We include SERVER.H for the class declarations for the C++ CServer
    server control object.
  We include FACTORY.H because it has the necessary internal class factory
    declarations for this component server.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <papint.h>
#include <papguids.h>
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
  m_pCFPaper = NULL;
  m_dwCFPaper = 0;

  // NULL the shared single object pointers.
  m_pCOPaper = NULL;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::~CServer

  Summary:  CServer Destructor.

  Args:     void

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
  if (OwnThis())
  {
    ++m_cObjects;

    UnOwnThis();
  }

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
  if (OwnThis())
  {
    --m_cObjects;

    // If no more living objects and no locks then shut the server down.
    if (0L == m_cObjects && 0L == m_cLocks && IsWindow(m_hWndServer))
    {
      // Post a message to this local server's message queue requesting
      // a close of the application.
      PostMessage(m_hWndServer, WM_CLOSE, 0, 0L);
    }

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
  LONG cLocks;

  if (OwnThis())
  {
    cLocks = ++m_cLocks;

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
    --m_cLocks;

    // Use ObjectsDown to force a server shutdown if this unlock warrants it.
    ++m_cObjects;
    ObjectsDown();

    UnOwnThis();
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::ObjectFirst

  Summary:  Returns TRUE if this is the first object created.

  Args:     void

  Returns:  BOOL
              TRUE => First object created; FALSE => Object already exists.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CServer::ObjectFirst(void)
{
  BOOL bFirst = TRUE;

  if (OwnThis())
  {
    bFirst = (NULL == m_pCOPaper);

    UnOwnThis();
  }

  return bFirst;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::ObjectSet

  Summary:  Tells server that the shared single object has been created.

  Args:     void

  Modifies: m_pCOPaper.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CServer::ObjectSet(IUnknown* pCob)
{
  HRESULT hr = NOERROR;

  if (OwnThis())
  {
    m_pCOPaper = pCob;

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::ObjectQI

  Summary:  QueryInterface on the singleton object.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CServer::ObjectQI(REFIID riid, PPVOID ppv)
{
  HRESULT hr = E_FAIL;

  if (OwnThis())
  {
    hr = m_pCOPaper->QueryInterface(riid, ppv);

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::OpenFactories

  Summary:  Create and register all of this server's class factories.

  Args:     void

  Modifies: m_pCFPaper, m_dwCFPaper.

  Returns:  BOOL
              TRUE if success; FALSE if not
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CServer::OpenFactories(void)
{
  BOOL bOk = FALSE;
  HRESULT hr;

  // Build and register the SharePaper factory.
  m_pCFPaper = new CFPaper(NULL, this);
  if (NULL != m_pCFPaper)
  {
    // AddRef this cached pointer to the Class Factory.
    m_pCFPaper->AddRef();

    // Now register this class factory with COM.
    hr = CoRegisterClassObject(
           CLSID_SharePaper,
           m_pCFPaper,
           CLSCTX_LOCAL_SERVER,
           REGCLS_MULTIPLEUSE,
           &m_dwCFPaper);

    bOk = SUCCEEDED(hr);
    if (!bOk)
    {
      // If can't register factory then clean up for server exit.
      m_pCFPaper->Release();
      DELETE_POINTER(m_pCFPaper);
    }
  }
  else
    bOk = FALSE;

  return bOk;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::CloseFactories

  Summary:  Revoke (ie, unregister) and delete all the server's class
            factories.

  Args:     void

  Modifies: m_dwCFPaper.

  Returns:  BOOL
              TRUE if success; FALSE if not
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CServer::CloseFactories(void)
{
  BOOL bOk = TRUE;
  HRESULT hr;

  // Unregister the SharePaper class factory with COM.
  if (0 != m_dwCFPaper)
  {
    hr = CoRevokeClassObject(m_dwCFPaper);
    if (FAILED(hr))
      bOk = FALSE;
  }

  // Release any and all of the Class Factory interface pointers.
  RELEASE_INTERFACE(m_pCFPaper);

  return bOk;
}

// =============================== END ======================================
