/*+==========================================================================
  File:      PAGEFILE.H

  Summary:   Include file for the CPageFile C++ class. A CPageFile is a
             C++ object that encapsulates load and save operations on an
             COM structured storage compound file. CPageFile knows about
             an underlying server-based persistent COM object, COPageList,
             that manages the actual page list data. COPageList supports
             persistence of its page list data by exposing the
             IPersistStream interface.

             For a comprehensive tutorial code tour of PAGEFILE's contents
             and offerings see the tutorial PERCLIEN.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the PAGEFILE source code.

  Classes:   CPageFile.

  Origin:    5-25-96: atrent - Created for PERCLIEN Code Sample.

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

#if !defined(PAGEFILE_H)
#define PAGEFILE_H

#if defined(__cplusplus)


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CPageFile

  Summary:  Class to encapsulate operations on the page list's data
            compound file.

  Methods:  CPageFile
              Constructor.
            ~CPageFile
              Destructor.
            HRESULT Init(
                      TCHAR* pszAppFileName);
              Initialize the CPageFile C++ object.
            HRESULT New(
                      TCHAR* pszFileName,
                      IStorage** ppIStorage,
                      IPageList** ppIPageList);
              Create a new empty Page List compound file.
            HRESULT Load(
                      TCHAR* pszFileName,
                      IStorage** ppIStorage,
                      IPageList** ppIPageList);
              Load Page List data using the specified compound file name.
            HRESULT Save(
                      IStorage* pIStorage,
                      IPageList* pIPageList);
              Save current page list under specified root storage.
            HRESULT SaveAs(
                      TCHAR* pszFileName,
                      IPageList* pIPageList,
                      IStorage** ppIStorage);
              Create a new page list compound file of specified file name.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CPageFile
{
  public:
    CPageFile(void);
   ~CPageFile(void);
    HRESULT Init(
              TCHAR* pszAppFileName);
    HRESULT New(
              TCHAR* pszFileName,
              IStorage** ppIStorage,
              IPageList** ppIPageList);
    HRESULT Load(
              TCHAR* pszFileName,
              IStorage** ppIStorage,
              IPageList** ppIPageList);
    HRESULT Save(
              IStorage* pIStorage,
              IPageList* pIPageList);
    HRESULT SaveAs(
              TCHAR* pszFileName,
              IPageList* pIPageList,
              IStorage** ppIStorage);

  private:
    TCHAR          m_szCurFileName[MAX_PATH];
    CLSID          m_CidPageList;
};


#endif // __cplusplus

#endif
