/*+==========================================================================
  File:      PAPFILE.CPP

  Summary:   Implementation file for the CPapFile C++ class. A CPapFile is
             a C++ object that encapsulates load and save operations on an
             COM structured storage compound file.  CPapFile knows about
             an underlying server-based COM object, COPaper, that manages
             the actual paper drawing data and uses an IStorage provided
             to store retrieve that paper data.

             For a comprehensive tutorial code tour of PapFile's contents
             and offerings see the tutorial STOCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the PAPFILE source code.

  Classes:   CPapFile.

  Functions: .

  Origin:    6-13-96: atrent - Created for STOCLIEN Code Sample.

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

/*--------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include IPAPER.H and PAPGUIDS.H for the common paper-related Interface
    class, GUID, and CLSID specifications.
  We include PAPFILE.H because it has the C++ class declaration used
    for CPapFile.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <ipaper.h>
#include <papguids.h>
#include "papfile.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPapFile::CPapFile

  Summary:  CPapFile Constructor.

  Args:     .

  Modifies: .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CPapFile::CPapFile()
{
  m_szCurFileName[0] = 0;
  m_pIPaper = NULL;
  m_pIStorage = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPapFile::~CPapFile

  Summary:  CPapFile Destructor.

  Args:     .

  Modifies: .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CPapFile::~CPapFile()
{
  RELEASE_INTERFACE(m_pIPaper);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPapFile::Init

  Summary:  Initializes the CPapFile C++ object.

  Args:     TCHAR* pszAppFileName
              Name/Path of the app's default compound file to open.
            IPaper* pIPaper
              Interface pointer for a COPaper COM object that manages
              a collection of Ink Data in memory and has facilities
              for Loading and Saving that data using an IStorage to
              a client-provided compound file.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CPapFile::Init(
                    TCHAR* pszAppFileName,
                    IPaper* pIPaper)
{
  HRESULT hr = E_FAIL;

  if (NULL != pIPaper)
  {
    // Keep CPapFile copy of pIPaper. Thus AddRef it. Released in Destructor.
    m_pIPaper = pIPaper;
    m_pIPaper->AddRef();

    if (NULL != pszAppFileName)
    {
      // Set the default current file name.
      lstrcpy(m_szCurFileName, pszAppFileName);

      hr = NOERROR;
    }
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPapFile::Load

  Summary:  Load paper data using the specified compound file name.

  Args:     SHORT nLockKey
              The lock key previously obtained in a IPaper::Lock call.
            TCHAR* pszFileName
              Name/Path of the compound file to open. If NULL then use
              CPapFile's m_szCurFileName as the compound file to load.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CPapFile::Load(
                    SHORT nLockKey,
                    TCHAR* pszFileName)
{
  HRESULT hr = E_FAIL;
  BOOL bNewFile = (NULL != pszFileName);
  TCHAR* pszFile;

  // If NULL file name passed then use current file name.
  pszFile = bNewFile ? pszFileName : m_szCurFileName;

  // First check if the file is out there using APPUTIL function.
  if (FileExist(pszFile))
  {
    // Use COM service to next check if the file is actually a valid
    // compound file.
    hr = StgIsStorageFile(pszFile);
    if (SUCCEEDED(hr))
    {
      // We're go. Use COM service to open the compound file and
      // obtain a IStorage interface.
      hr = StgOpenStorage(
             pszFile,
             NULL,
             STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
             NULL,
             0,
             &m_pIStorage);
      if (SUCCEEDED(hr))
      {
        // We have an IStorage. Now ask the COPaper object on the server
        // side to load into itself the file's paper data using the
        // IStorage for our client-provided compound file.
        hr = m_pIPaper->Load(nLockKey, m_pIStorage);
        if (SUCCEEDED(hr))
        {
          // The paper data was loaded and we have a current compound
          // file name. Copy it for later use in a saves and loads.
          if (bNewFile)
            lstrcpy(m_szCurFileName, pszFileName);
        }

        // We are done with the Storage for now. We don't hold the file
        // open. We re-obtain the IStorage again later (and thus re-open
        // the compound file) when we need it for another save or load.
        RELEASE_INTERFACE(m_pIStorage);
      }
    }
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPapFile::Save

  Summary:  Save current paper data using the specified compound file name.

  Args:     SHORT nLockKey
              The lock key previously obtained in a IPaper::Lock call.
            TCHAR* pszFileName
              Name/Path of the compound file to open. If NULL then use
              CPapFile's m_szCurFileName as the compound file to save.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CPapFile::Save(
                    SHORT nLockKey,
                    TCHAR* pszFileName)
{
  HRESULT hr = E_FAIL;
  BOOL bNewFile = (NULL != pszFileName);
  TCHAR* pszFile;

  // If NULL file name passed then use current file name.
  pszFile = bNewFile ? pszFileName : m_szCurFileName;

  // Use COM service to re-open (or newly create) the compound file.
  hr = StgCreateDocfile(
         pszFile,
         STGM_CREATE | STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
         0,
         &m_pIStorage);
  if (SUCCEEDED(hr))
  {
    // We've got the IStorage and the compound file is open.
    // Now tell the COPaper object on the server side to save its
    // paper data into the compound file using the IStorage of our
    // client-provided compound file.
    hr = m_pIPaper->Save(nLockKey, m_pIStorage);
    if (SUCCEEDED(hr))
    {
      // The paper data was saved and we have a new current compound
      // file name. Copy it for later use in a saves and loads.
      if (bNewFile)
        lstrcpy(m_szCurFileName, pszFileName);
    }

    // We are done with the Storage for now. We don't hold the file
    // open. We re-obtain the IStorage again later (and thus re-open
    // the compound file) when we need it for another save or load.
    RELEASE_INTERFACE(m_pIStorage);
  }

  return (hr);
}
