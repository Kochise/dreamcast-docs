/*+==========================================================================
  File:      SERVER.CPP

  Summary:   Implementation file for the CServer server control C++
             object.  This object encapsulates the server's internal
             control of global server object and lock counts. The
             CThreaded OwnThis mechanism is used to ensure mutually
             exclusive access to this CServer object by multiple
             contending threads.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CServer.

  Functions: .

  Origin:    2-4-97: atrent - Editor-inheritance from SERVER.CPP in
               the STOSERVE Tutorial Code Sample.

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
  We include APPUTIL.H because we will be building this DLL using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include SERVER.H for the class declarations for the C++ CServer
    server control object.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include "server.h"


/*---------------------------------------------------------------------------
  Implementation the internal CServer C++ object.  Used to encapsulate
  some server data and the methods for Lock and Object count incrementing
  and decrementing.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::CServer

  Summary:  CServer Constructor.

  Args:     void

  Modifies: m_cObjects, m_cLocks.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CServer::CServer(void)
{
  // Zero the Object and Lock counts for this attached process.
  m_cObjects = 0;
  m_cLocks = 0;

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
  Method:   CServer::Lock

  Summary:  Increment the Server's Lock count.

  Args:     void

  Modifies: m_cLocks.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::Lock(void)
{
  InterlockedIncrement((PLONG) &m_cLocks);

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

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::CanUnloadNow

  Summary:  Check if we can unload the server (ie, if there are no longer
            any living COM objects and no locks.

  Args:     void

  Modifies: .

  Returns:  HRESULT
              S_OK if this server can be unloaded.
              S_FALSE if this server can not be unloaded.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CServer::CanUnloadNow(void)
{
  HRESULT hr = S_FALSE;
  LONG cObjects, cLocks;

  if (OwnThis())
  {
    cObjects = m_cObjects;
    cLocks = m_cLocks;

    hr = (0L==cObjects && 0L==cLocks) ? S_OK : S_FALSE;

    UnOwnThis();
  }

  return hr;
}
