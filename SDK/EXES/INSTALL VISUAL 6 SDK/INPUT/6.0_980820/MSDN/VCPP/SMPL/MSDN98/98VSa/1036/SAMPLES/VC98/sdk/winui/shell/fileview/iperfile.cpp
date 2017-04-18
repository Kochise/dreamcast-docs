//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//	PROGRAM: IPERFILE.CPP		
//
//	PURPOSE:   IPersistFile interface implementation for a FileViewer.
// This interface is written to not generally require modifications
// for a custom FileViewer but is written to interact with the
// definition for CFileViewer in FVTEXT.H.
//
//	PLATFORMS:	Windows 95
//
//	SPECIAL INSTRUCTIONS: N/A
//

#include "fileview.h"

//
//   FUNCTION:CImpIPersistFile::CImpIPersistFile 	
//
//   PURPOSE:  Constructor 
//
//   PARAMETERS: 
//	pObj            PCFileViewer of the object we're in.
//  pUnkOuter       LPUNKNOWN to which we delegate.
//
CImpIPersistFile::CImpIPersistFile(PCFileViewer pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }
//
//   FUNCTION: 	 CImpIPersistFile::~CImpIPersistFile
//
//   PURPOSE:   Destructor
//
CImpIPersistFile::~CImpIPersistFile(void)
    {
    return;
    }
//
//   FUNCTIONS: CImpIPersistFile::QueryInterface	
//							  CImpIPersistFile::AddRef
//							  CImpIPersistFile::Release
//
//   PURPOSE:   
//	    IUnknown members for CImpIPersistFile object that only delegate.
//
STDMETHODIMP CImpIPersistFile::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPersistFile::AddRef(void)
    {
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPersistFile::Release(void)
    {
    return m_pUnkOuter->Release();
    }
//
//   FUNCTION: 	 CImpIPersistFile::GetClassID
//
//   PURPOSE:   Returns the Class ID of this object.
//
//   PARAMETERS: 
//		 pClsID          LPCLSID in which to store our class ID.
//
//   RETURN VALUE:
//		 HRESULT         NOERROR always.	
//
STDMETHODIMP CImpIPersistFile::GetClassID(LPCLSID pClsID)
    {
    *pClsID=m_pObj->m_clsID;
    return NOERROR;
    }
//
//   FUNCTION: 	CImpIPersistFile::IsDirty
//
//   PURPOSE:  Always returns ResultFromScode(S_FALSE) for a FileViewer which
//   never makes any changes to the file. 
//
//   RETURN VALUE:
//	   HRESULT         S_FALSE always
//
STDMETHODIMP CImpIPersistFile::IsDirty(void)
    {
    return ResultFromScode(S_FALSE);
    }
//
//   FUNCTION: 	CImpIPersistFile::Load
//
//   PURPOSE:  Receives the filename of the path to show in this FileViewer.
//  The object need do nothing more than store this path for later
//  use in IFileViewer::Show. 
//
//   PARAMETERS: 
//	   pszFile         LPCOLESTR of the filename to load.
//     grfMode         DWORD flags to use when opening the file.
//
//   RETURN VALUE:
//   	HRESULT         NOERROR or a general error value.
//
STDMETHODIMP CImpIPersistFile::Load(LPCOLESTR pszFile, DWORD grfMode)
    {
    char        szFile[MAX_PATH];
    LPSTR       psz;

     // No modifications are necessary to this code:  it simply
     // copies the parameters into the CFileViewer::m_pszPath and
     // m_grfMode members for use in IFileViewer::ShowInitialize
     // and IFileViewer::Show later on.

    //We should never be called twice
    if (NULL!=m_pObj->m_pszPath)
    {
        // Review:: Make sure everything else is handled correctly
        m_pObj->m_fLoadCalled = FALSE;  // handle error case
        m_pObj->MemFree(m_pObj->m_pszPath);
        m_pObj->m_pszPath = NULL;

    }

    if (NULL==pszFile)
        {
        ODS("IPersistFile::Load called with NULL pointer");
        return ResultFromScode(E_INVALIDARG);
        }

    //Convert Unicode filename to ANSI
    wcstombs(szFile, pszFile, sizeof(szFile));

    psz=(LPSTR)m_pObj->MemAlloc(lstrlen(szFile)+1);

    if (NULL==psz)
        {
        ODS("IPersistFile::Load failed to allocate duplicate pathname");
        return ResultFromScode(E_OUTOFMEMORY);
        }

    //Copy the ANSI filename and the mode to use in opening it.
    lstrcpy(psz, szFile);
    m_pObj->m_pszPath=psz;
    m_pObj->m_grfMode=grfMode;

    //Remember that this function has been called.
    m_pObj->m_fLoadCalled=TRUE;
    return NOERROR;
    }
//
//   FUNCTION: 	CImpIPersistFile::Save
//
//   PURPOSE:  Not implemented in a FileViewer: since FileViewer objects never
//  make changes to a file there is nothing to save.  Parameters
//  are irrelevant. 
//
//   RETURN VALUE:
//	  HRESULT         Always contains E_NOTIMPL.
//
STDMETHODIMP CImpIPersistFile::Save(LPCOLESTR pszFile, BOOL fRemember)
    {
    ODS("IPersistFile::Save called...unexpected");
    return ResultFromScode(E_NOTIMPL);
    }
//
//   FUNCTION: 	 CImpIPersistFile::SaveCompleted
//
//   PURPOSE:  Not implemented in a FileViewer.  Parameters are irrelevant. 
//
//   RETURN VALUE:
//	   HRESULT         Always contains E_NOTIMPL.
//
STDMETHODIMP CImpIPersistFile::SaveCompleted(LPCOLESTR pszFile)
    {
    ODS("IPersistFile::SaveCompleted called...unexpected");
    return ResultFromScode(E_NOTIMPL);
    }
//
//   FUNCTION: CImpIPersistFile::GetCurFile	
//
//   PURPOSE:   Not implemented in a FileViewer.  Normally this function
//  would return a copy of the pathname from IPersistFile::Load
//  in a piece of memory allocated with the shared allocator
//  and stored in *ppszFile.  However, this function will not
//  be called in a FileViewer and can be left unimplemented.
//
//   PARAMETERS: 
//	  ppszFile        LPOLESTR * into which we store a pointer to
//                  the filename that should be allocated with the shared IMalloc.
//
//   RETURN VALUE:
//  HRESULT         NOERROR or a general error value.
//
STDMETHODIMP CImpIPersistFile::GetCurFile(LPOLESTR *ppszFile)
    {
    LPOLESTR    psz;
    ULONG       cb;

     // No modifications are necessary to this code:  it simply
     // copies the CFileViewer::m_pszPath string into a piece
     // of memory and stores the pointer at *ppszFile.
    //Load must be called, of course.
    if (m_pObj->m_fLoadCalled)
        {
        ODS("IPersistFile::GetCurFile called without IPersistFile::Load");
        return ResultFromScode(E_UNEXPECTED);
        }

    if (NULL==ppszFile)
        {
        ODS("IPersistFile::GetCurFile called with NULL pointer");
        return ResultFromScode(E_INVALIDARG);
        }

    cb=(lstrlen(m_pObj->m_pszPath)+1)*sizeof(OLECHAR);
    psz=(LPOLESTR)m_pObj->MemAlloc(cb);

    if (NULL==psz)
        {
        ODS("IPersistFile::GetCurFile failed to allocate duplicate pathname");
        return ResultFromScode(E_OUTOFMEMORY);
        }

    //Copy the ANSI filename to the new memory, converting to Unicode
    mbstowcs(psz, m_pObj->m_pszPath, cb);

    //Save the pointer which is not caller's responsibility
    *ppszFile=psz;
    return NOERROR;
    }
