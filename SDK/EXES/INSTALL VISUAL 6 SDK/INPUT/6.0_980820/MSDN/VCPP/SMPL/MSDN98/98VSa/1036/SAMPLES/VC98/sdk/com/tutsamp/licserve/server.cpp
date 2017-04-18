/*+==========================================================================
  File:      SERVER.CPP

  Summary:   Implementation file for the CServer server-related utility
             C++ object.  This object encapsulates the server's internal
             control of global server object and lock counts and checks
             for the global machine license for this server.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial LICSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CServer.

  Functions:

  Origin:    10-5-95: atrent - Editor-inheritance from SERVER.CPP in
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
  We include APPUTIL.H because we will be building this DLL using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include SERVER.H for the object class declarations for the
    C++ CServer server control object.
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

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CServer::CServer(void)
{
  // Init the Server License Key string.
  lstrcpyA(
    m_szLicenseKey,
    "LICSERVE 1.0 - Component Server - Copyright (c) 1997 Microsoft Corp.");

  m_cLicenseLen = 0;
  m_bLicensed = FALSE;

  m_hDllInst = NULL;
  m_hWndParent = NULL;
  m_pMsgBox = NULL;

  // Zero the Object and Lock counts for this attached process.
  m_cObjects = 0;
  m_cLocks = 0;

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
  Method:   CServer::Lock

  Summary:  Increment the Server's Lock count.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::Lock(void)
{
  InterlockedIncrement((PLONG) &m_cLocks);

  LOGF1("P: CServer::Lock. New cLocks=%i.", m_cLocks);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::Unlock

  Summary:  Decrement the Server's Lock count.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::Unlock(void)
{
  InterlockedDecrement((PLONG) &m_cLocks);

  LOGF1("P: CServer::Unlock. New cLocks=%i.", m_cLocks);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::ObjectsUp

  Summary:  Increment the Server's living Object count.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::ObjectsUp(void)
{
  InterlockedIncrement((PLONG) &m_cObjects);

  LOGF1("P: CServer::ObjectsUp. New cObjects=%i.", m_cObjects);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::ObjectsDown

  Summary:  Decrement the Server's living object count.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CServer::ObjectsDown(void)
{
  InterlockedDecrement((PLONG) &m_cObjects);

  LOGF1("P: CServer::ObjectsDown. New cObjects=%i.", m_cObjects);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CServer::CheckLicense

  Summary:  Check for global machine license for this server.  Looks for a
            LICSERVE.LIC file and compares its first text line with the
            expected license key string stored in this server module.

  Args:     void

  Modifies: .

  Returns:  BOOL
              TRUE if license verified; FALSE if not.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CServer::CheckLicense(void)
{
  TCHAR  szPath[MAX_PATH];
  CHAR   szLicKeyRead[MAX_LICENSEKEY];
  UINT   cbRead;
  ULONG  cbWasRead;
  UINT   cb;
  HANDLE hFile;

  // Assume license not verified to start.
  m_bLicensed = FALSE;

  // Assume the license key string is ASCII and count its length.
  m_cLicenseLen = cb = lstrlenA(m_szLicenseKey);

  // Get the module path. Then parse and replace DLL extension with LIC.
  MakeFamilyPath(m_hDllInst, szPath, TEXT(LICENSE_FILE_EXT));

  // Open the xx.LIC file and read in and check the license key for a match.
  hFile = CreateFile(
            szPath,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

  if (INVALID_HANDLE_VALUE != hFile)
  {
    cbRead = cb * sizeof(CHAR);
    ReadFile(hFile, szLicKeyRead, cbRead, &cbWasRead, NULL);
    CloseHandle(hFile);
    if (cbRead == cbWasRead)
      if (0 == memcmp(m_szLicenseKey, szLicKeyRead, cb))
        m_bLicensed = TRUE;
  }

  LOGF1("P: CServer::CheckLicense. bLicensed=%i.", m_bLicensed);

  return m_bLicensed;
}
