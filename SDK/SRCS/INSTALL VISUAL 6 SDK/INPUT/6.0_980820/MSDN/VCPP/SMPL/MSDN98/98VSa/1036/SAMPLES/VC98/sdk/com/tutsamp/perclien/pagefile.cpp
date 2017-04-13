/*+==========================================================================
  File:      PAGEFILE.CPP

  Summary:   Implementation file for the CPageFile C++ class. A CPageFile
             is a C++ object that encapsulates load and save operations on
             an COM structured storage compound file. CPageFile knows
             about an underlying server-based persistent COM object,
             COPageList, that manages the actual page list data.
             COPageList supports persistence of its page list data by
             exposing the IPersistStream interface.

             For a comprehensive tutorial code tour of PageFile's contents
             and offerings see the tutorial PERCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the PAGEFILE source code.

  Classes:   CPageFile.

  Functions: .

  Origin:    5-24-97: atrent - Created for PERCLIEN Code Sample.

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
  We include IPAGES.H and PAGEGUID.H for the common page-related Interface
    class, GUID, and CLSID specifications.
  We include PAGEFILE.H because it has the C++ class declaration used
    for CPageFile.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "pagefile.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPageFile::CPageFile

  Summary:  CPageFile Constructor.

  Args:     void.

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CPageFile::CPageFile(void)
{
  m_szCurFileName[0] = 0;

  // Save the ClassID of PageLists using overloaded '=' operator.
  m_CidPageList = CLSID_PageList;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPageFile::~CPageFile

  Summary:  CPageFile Destructor.

  Args:     void

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CPageFile::~CPageFile(void)
{
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPageFile::Init

  Summary:  Initializes the CPageFile C++ object.

  Args:     TCHAR* pszAppFileName
              Name/Path of the app's default compound file to open.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CPageFile::Init(
          TCHAR* pszAppFileName)
{
  HRESULT hr = E_POINTER;

  if (NULL != pszAppFileName)
  {
    // Set the default current file name.
    lstrcpy(m_szCurFileName, pszAppFileName);

    hr = NOERROR;
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPageFile::New

  Summary:  Create a new empty PageList compound file using the specified
            file name.

  Args:     TCHAR* pszFileName,
              Name/Path of the compound file to Create. If NULL then use
              CPageFile's m_szCurFileName as the compound file to Create.
            IStorage** ppIStorage,
              Address of an IStorage pointer variable that will receive
              the IStorage interface for the new PageList file.
            IPageList** ppIPageList)
              Address of an IPageList pointer variable that will receive
              the IPageList interface for a new COPageList COM object.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CPageFile::New(
          TCHAR* pszFileName,
          IStorage** ppIStorage,
          IPageList** ppIPageList)
{
  HRESULT hr = E_POINTER;
  BOOL bNewFile = (NULL != pszFileName);
  TCHAR* pszFile;
  IStorage* pIStorage;
  IStream* pIStream;
  IPersistStream* pIPersistStream;
  IPageList* pIPageList;
  ULARGE_INTEGER uliMaxSize;

  if (NULL != ppIStorage && NULL != ppIPageList)
  {
    // Zero the output pointers in case of errror.
    *ppIStorage = NULL;
    *ppIPageList = NULL;

    // If NULL file name passed then use current file name.
    pszFile = bNewFile ? pszFileName : m_szCurFileName;

    // Use COM service to create a new compound file.
    hr = StgCreateDocfile(
           pszFile,
           STGM_CREATE | STGM_DIRECT | STGM_READWRITE
             | STGM_SHARE_EXCLUSIVE,
           0,
           &pIStorage);
    if (SUCCEEDED(hr))
    {
      // We have created a new compound file. Now store the CLSID of
      // COPageList.
      hr = WriteClassStg(pIStorage, m_CidPageList);
      if (SUCCEEDED(hr))
      {
        // Now Create the single "PageList" stream under the root storage.
        hr = pIStorage->CreateStream(
               PAGELIST_USTR,
               STGM_CREATE | STGM_WRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
               0,
               0,
               &pIStream);
        if (SUCCEEDED(hr))
        {
          // Now use the Class ID to create a COPageList object. Initially
          // ask for the IPageList interface.
          hr = CoCreateInstance(
                 m_CidPageList,
                 NULL,
                 CLSCTX_INPROC_SERVER,
                 IID_IPageList  ,
                 (PPVOID)&pIPageList);
          if (SUCCEEDED(hr))
          {
            // Clear the content of the Page List.
            pIPageList->Clear();

            // Now obtain the IPersistStream interface on the new
            // COPageList object. At this point the client assumes that
            // PageList COM objects support the IPersistStream interface.
            hr = pIPageList->QueryInterface(
                   IID_IPersistStream,
                   (PPVOID)&pIPersistStream);
            if (SUCCEEDED(hr))
            {
              // And as expected by this client, COPageList supports
              // the IPersistStream interface. Now use this interface
              // to ask the COPageList object to save an empty Page List.

              // First ask the COPageList object how much space the
              // maximum save would consume and then pre-allocate that
              // space in the stream.
              hr = pIPersistStream->GetSizeMax(&uliMaxSize);
              if (SUCCEEDED(hr))
              {
                hr = pIStream->SetSize(uliMaxSize);
                if (SUCCEEDED(hr))
                {
                  // Now save the new Page List into the
                  // pre-allocated space.
                  hr = pIPersistStream->Save(pIStream, TRUE);
                }
              }

              // Done with IPersistStream for now so release it.
              pIPersistStream->Release();
            }

            // Done with the stream for now so release it.
            pIStream->Release();
          }
        }
      }
    }

    if (SUCCEEDED(hr))
    {
      // COPageList is fully created and the page list is
      // loaded. Assign a copy of COPageList's IPageList
      // interface for use by the caller.
      *ppIPageList = pIPageList;

      // For performance, keep the Page List 'Document' file
      // open (ie, don't release IStorage here) and give the
      // caller a copy of the IStorage Pointer.
      *ppIStorage = pIStorage;

      // The page list was loaded and we have a current compound
      // file name. Copy it for later use in saves and loads.
      if (bNewFile)
        lstrcpy(m_szCurFileName, pszFileName);
    }
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPageFile::Load

  Summary:  Load PageList data using the specified compound file name.
            If this file is found then it is loaded. If it is not found
            then an empty new file of the specified name is created.

  Args:     TCHAR* pszFileName,
              Name/Path of the compound file to open. If NULL then use
              CPageFile's m_szCurFileName as the compound file to load.
            IStorage** ppIStorage,
              Address of an IStorage pointer variable that will receive
              the IStorage interface for the loaded PageList file.
            IPageList** ppIPageList)
              Address of an IPageList pointer variable that will receive
              the IPageList interface for a new COPageList COM object.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CPageFile::Load(
          TCHAR* pszFileName,
          IStorage** ppIStorage,
          IPageList** ppIPageList)
{
  HRESULT hr = E_POINTER;
  BOOL bNewFile = (NULL != pszFileName);
  TCHAR* pszFile;
  IStorage* pIStorage;
  IStream* pIStream;
  IPersistStream* pIPersistStream;
  IPageList* pIPageList;
  ULARGE_INTEGER uliMaxSize;

  if (NULL != ppIStorage && NULL != ppIPageList)
  {
    // Zero the output pointers in case of errror.
    *ppIStorage = NULL;
    *ppIPageList = NULL;

    // If NULL file name passed then use current file name.
    pszFile = bNewFile ? pszFileName : m_szCurFileName;

    // Use COM service to check if the file is out there and is actually
    // a valid compound file.
    hr = StgIsStorageFile(pszFile);
    if (SUCCEEDED(hr))
    {
      // We have a compound file. Use COM service to open the compound file
      // and obtain a IStorage interface.
      hr = StgOpenStorage(
             pszFile,
             NULL,
             STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
             NULL,
             0,
             &pIStorage);
      if (SUCCEEDED(hr))
      {
        // We have an IStorage. Now get the ClassID of the COM Server
        // that handles Page Files.
        hr = ReadClassStg(pIStorage, &m_CidPageList);
        if (SUCCEEDED(hr))
        {
          // We have a ClassID for a server. Now Open the single "PageList"
          // stream under the root storage.
          hr = pIStorage->OpenStream(
                 PAGELIST_USTR,
                 0,
                 STGM_READ | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
                 0,
                 &pIStream);
          if (SUCCEEDED(hr))
          {
            // Now use the previously obtained Class ID to create a
            // COPageList object. Initially ask for IPageList interface.
            hr = CoCreateInstance(
                   m_CidPageList,
                   NULL,
                   CLSCTX_INPROC_SERVER,
                   IID_IPageList  ,
                   (PPVOID)&pIPageList);
            if (SUCCEEDED(hr))
            {
              // We have a new COPageList object. Now obtain the
              // IPersistStream interface on it. The client assumes at
              // this point that PageList COM objects support only the
              // IPersistStream interface for their persistence.
              hr = pIPageList->QueryInterface(
                     IID_IPersistStream,
                     (PPVOID)&pIPersistStream);
              if (SUCCEEDED(hr))
              {
                // And as expected by this client, COPageList supports
                // the IPersistStream interface. Now use this interface
                // to ask the COPageList object to load the Page List.
                hr = pIPersistStream->Load(pIStream);

                // Done with IPersistStream for now so release it.
                pIPersistStream->Release();
              }
              else
                pIPageList->Release();
            }

            // Done with the stream for now so release it.
            pIStream->Release();
          }
        }
      }
    }
    else
    {
      // If there was no existing compound file use COM services to
      // create a new compound file.
      hr = StgCreateDocfile(
             pszFile,
             STGM_CREATE | STGM_DIRECT | STGM_READWRITE
               | STGM_SHARE_EXCLUSIVE,
             0,
             &pIStorage);
      if (SUCCEEDED(hr))
      {
        // We have created a new compound file. Now store the CLSID of
        // COPageList.
        hr = WriteClassStg(pIStorage, m_CidPageList);
        if (SUCCEEDED(hr))
        {
          // Now Create the single "PageList" stream under the root storage.
          hr = pIStorage->CreateStream(
                 PAGELIST_USTR,
                 STGM_CREATE | STGM_WRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
                 0,
                 0,
                 &pIStream);
          if (SUCCEEDED(hr))
          {
            // Now use the Class ID to create a COPageList object. Initially
            // ask for the IPageList interface.
            hr = CoCreateInstance(
                   m_CidPageList,
                   NULL,
                   CLSCTX_INPROC_SERVER,
                   IID_IPageList  ,
                   (PPVOID)&pIPageList);
            if (SUCCEEDED(hr))
            {
              // We have a new COPageList object. Now obtain the
              // IPersistStream interface on it. The client assumes at
              // this point that PageList COM objects support only the
              // IPersistStream interface for their persistence.
              hr = pIPageList->QueryInterface(
                   IID_IPersistStream,
                     (PPVOID)&pIPersistStream);
              if (SUCCEEDED(hr))
              {
                // And as expected by this client, COPageList supports
                // the IPersistStream interface. Now use this interface
                // to ask the COPageList object to save an empty Page List.

                // First ask the COPageList object how much space the
                // next save would consume and then pre-allocate that
                // space in the stream.
                hr = pIPersistStream->GetSizeMax(&uliMaxSize);
                if (SUCCEEDED(hr))
                {
                  hr = pIStream->SetSize(uliMaxSize);
                  if (SUCCEEDED(hr))
                  {
                    // Now save the new Page List into the
                    // pre-allocated space.
                    hr = pIPersistStream->Save(pIStream, TRUE);
                  }
                }

                // Done with IPersistStream for now so release it.
                pIPersistStream->Release();
              }

              // Done with the stream for now so release it.
              pIStream->Release();
            }
          }
        }
      }
    }

    if (SUCCEEDED(hr))
    {
      // COPageList is fully created and the page list is
      // loaded. Assign a copy of COPageList's IPageList
      // interface for use by the caller.
      *ppIPageList = pIPageList;

      // For performance, keep the Page List 'Document' file
      // open (ie, don't release IStorage here) and give the
      // caller a copy of the IStorage Pointer.
      *ppIStorage = pIStorage;

      // The page list was loaded and we have a current compound
      // file name. Copy it for later use in saves and loads.
      if (bNewFile)
        lstrcpy(m_szCurFileName, pszFileName);
    }
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPageFile::Save

  Summary:  Save current pagelist data using the specified IStorage
            and IPageList interfaces.

  Args:     IStorage* pIStorage,
              Pointer to the opened file's IStorage interface.
            IPageList* pIPageList)
              Pointer to the IPageList interface on the COPageList object.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CPageFile::Save(
          IStorage* pIStorage,
          IPageList* pIPageList)
{
  HRESULT hr = E_POINTER;
  IStream* pIStream;
  IPersistStream* pIPersistStream;

  if (NULL != pIStorage && NULL != pIPageList)
  {
    // Obtain the IPersistStream interface on the COPageList
    // COM object.
    hr = pIPageList->QueryInterface(
           IID_IPersistStream,
           (PPVOID)&pIPersistStream);
    if (SUCCEEDED(hr))
    {
      // Save if the data is dirty (ie, doesn't match file data).
      if (S_FALSE != pIPersistStream->IsDirty())
      {
        // Use the existing IStorage to Open the single "PageList" stream
        // under the root storage.
        hr = pIStorage->OpenStream(
               PAGELIST_USTR,
               0,
               STGM_WRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
               0,
               &pIStream);
        if (SUCCEEDED(hr))
        {
          // Ask the persistent object to save itself in the stream
          // and clear the PageList dirty bit.
          hr = pIPersistStream->Save(pIStream, TRUE);

          // Done with the stream for now so release it.
          pIStream->Release();
        }
      }

      // Done with IPersistStream for now so release it.
      pIPersistStream->Release();
    }
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CPageFile::SaveAs

  Summary:  Create a new PageList compound file using the specified
            file name. You must release the previous open IStorage prior
            to calling this method.

  Args:     TCHAR* pszFileName,
              Name/Path of the compound file to open. If NULL then use
              CPageFile's m_szCurFileName as the compound file to load.
            IPageList* pIPageList,
              Pointer to the IPageList interface on the COPageList object.
            IStorage** ppIStorage,
              Address of an IStorage pointer variable that will receive
              the IStorage interface for the new PageList file.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CPageFile::SaveAs(
          TCHAR* pszFileName,
          IPageList* pIPageList,
          IStorage** ppIStorage)
{
  HRESULT hr = E_POINTER;
  BOOL bNewFile = (NULL != pszFileName);
  IStorage* pIStorage;

  if (NULL != ppIStorage)
  {
    // Zero the output pointers in case of errror.
    *ppIStorage = NULL;

    if (bNewFile)
    {
      // We have a compound file. Use COM service to reopen the
      // compound file and obtain a IStorage interface.
      hr = StgOpenStorage(
             pszFileName,
             NULL,
             STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
             NULL,
             0,
             &pIStorage);
      if (SUCCEEDED(hr))
      {
        // For performance, keep the Page List 'Document' file
        // open (ie, don't release IStorage here) and give the
        // caller a copy of the IStorage Pointer.
        *ppIStorage = pIStorage;

        // Copy the new file name for later use in saves and loads.
        lstrcpy(m_szCurFileName, pszFileName);
      }
    }
  }

  return (hr);
}
