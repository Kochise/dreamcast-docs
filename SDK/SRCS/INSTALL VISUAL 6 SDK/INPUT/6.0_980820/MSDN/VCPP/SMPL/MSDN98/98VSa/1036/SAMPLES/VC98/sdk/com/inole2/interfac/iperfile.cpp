/*
 * IPERFILE.CPP
 *
 * Template IPersistFile interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iperfile.h"


/*
 * CImpIPersistFile:CImpIPersistFile
 * CImpIPersistFile::~CImpIPersistFile
 *
 * Constructor Parameters:
 *  pObj            LPVOID pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPersistFile::CImpIPersistFile(LPVOID pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }


CImpIPersistFile::~CImpIPersistFile(void)
    {
    return;
    }



/*
 * CImpIPersistFile::QueryInterface
 * CImpIPersistFile::AddRef
 * CImpIPersistFile::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPersistFile.
 */

STDMETHODIMP CImpIPersistFile::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPersistFile::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPersistFile::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIPersistFile::GetClassID
 *
 * Purpose:
 *  Returns the CLSID of the file represented by this interface.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store our CLSID.
 */

STDMETHODIMP CImpIPersistFile::GetClassID(LPCLSID pClsID)
    {
    return NOERROR;
    }





/*
 * CImpIPersistFile::IsDirty
 *
 * Purpose:
 *  Tells the caller if we have made changes to this object since
 *  it was loaded or initialized new.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Contains S_OK if we ARE dirty, S_FALSE if
 *                  NOT dirty.
 */

STDMETHODIMP CImpIPersistFile::IsDirty(void)
    {
    return ResultFromScode(S_FALSE);
    }








/*
 * CImpIPersistFile::Load
 *
 * Purpose:
 *  Asks the server to load the document for the given filename.
 *
 * Parameters:
 *  pszFile         LPCOLESTR of the filename to load.
 *  grfMode         DWORD flags to use when opening the file.
 */

STDMETHODIMP CImpIPersistFile::Load(LPCOLESTR pszFile, DWORD grfMode)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIPersistFile::Save
 *
 * Purpose:
 *  Instructs the server to write the current file into a new
 *  filename, possibly then using that filename as the current one.
 *
 * Parameters:
 *  pszFile         LPCOLESTR of the file into which we save.  If NULL,
 *                  this means save the current file.
 *  fRemember       BOOL indicating if we're to use this filename as
 *                  the current file now (Save As instead of Save
 *                  Copy As).
 */

STDMETHODIMP CImpIPersistFile::Save(LPCOLESTR pszFile, BOOL fRemember)
    {
    return ResultFromScode(E_NOTIMPL);
    }








/*
 * CImpIPersistFile::SaveCompleted
 *
 * Purpose:
 *  Informs us that the operation that called Save is now finished
 *  and we can access the file again.
 *
 * Parameters:
 *  pszFile         LPCOLESTR of the file in which we can start
 *                  writing again.
 */

STDMETHODIMP CImpIPersistFile::SaveCompleted(LPCOLESTR pszFile)
    {
    return NOERROR;
    }





/*
 * CImpIPersistFile::GetCurFile
 *
 * Purpose:
 *  Returns the current filename.
 *
 * Parameters:
 *  ppszFile        LPOLESTR * into which we store a pointer to
 *                  the filename that should be allocated with the
 *                  shared IMalloc.
 */

STDMETHODIMP CImpIPersistFile::GetCurFile(LPOLESTR *ppszFile)
    {
    return ResultFromScode(E_NOTIMPL);
    }
