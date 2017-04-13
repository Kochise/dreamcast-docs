/*
 * FILEOBJ.CPP
 * File Object for Link Source, Chapter 9
 *
 * Implementation of a "file" object named with a file moniker,
 * which implements IPersistFile, IOleItemContainer, and
 * IDescription.  The latter two interfaces are implemented
 * generically in IOLECONT.CPP and IDESCRIP.CPP.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "linksrc.h"

#ifdef WIN32ANSI
/*
 * This is to turn off the mapping to ANSI wrapper APIs because
 * we're actually using wide char strings under Win32 all the time
 * in parts of this code.
 */
#undef StgOpenStorage
#define StgOpenStorage StgOpenStorage

#undef CreateFileMoniker
#define CreateFileMoniker CreateFileMoniker
#endif


/*
 * CFileObject::CFileObject
 * CFileObject::~CFileObject
 *
 * Parameters (Constructor):
 *  pUnkOuter       LPUNKNOWN of a controlling unknown.
 *  pfnDestroy      PFNDESTROYED to call when an object
 *                  is destroyed.
 */

CFileObject::CFileObject(LPUNKNOWN pUnkOuter
    , PFNDESTROYED pfnDestroy)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pfnDestroy=pfnDestroy;

    m_clsID=CLSID_LinkedFile;
    m_szFile[0]=(OLECHAR)0;
    m_pIStorage=NULL;
    m_pmk=NULL;
    m_dwRegROT=0;

    m_pImpIPersistFile=NULL;
    m_pImpIOleItemContainer=NULL;
    m_pImpIDescription=NULL;

    return;
    }

CFileObject::~CFileObject(void)
    {
    //Remove us from the running object table
    if (0!=m_dwRegROT)
        {
        IRunningObjectTable    *pROT;

        if (SUCCEEDED(GetRunningObjectTable(0, &pROT)))
            {
            pROT->Revoke(m_dwRegROT);
            pROT->Release();
            }
        }

    ReleaseInterface(m_pmk);
    ReleaseInterface(m_pIStorage);
    DeleteInterfaceImp(m_pImpIDescription);
    DeleteInterfaceImp(m_pImpIOleItemContainer);
    DeleteInterfaceImp(m_pImpIPersistFile);
    return;
    }



/*
 * CFileObject::Init
 *
 * Purpose:
 *  Performs any intiailization of a CFileObject that's prone to
 *  failure that we also use internally before exposing the object
 *  outside.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CFileObject::Init(void)
    {
    IUnknown   *pUnk=this;

    if (NULL!=m_pUnkOuter)
        pUnk=m_pUnkOuter;

    m_pImpIPersistFile=new CImpIPersistFile(this, pUnk);

    if (NULL==m_pImpIPersistFile)
        return FALSE;

    m_pImpIOleItemContainer=new CImpIOleItemContainer(this, pUnk
        , TRUE);

    if (NULL==m_pImpIOleItemContainer)
        return FALSE;

    m_pImpIDescription=new CImpIDescription(pUnk);

    if (NULL==m_pImpIDescription)
        return FALSE;

    return TRUE;
    }




/*
 * CFileObject::QueryInterface
 * CFileObject::AddRef
 * CFileObject::Release
 *
 * Purpose:
 *  IUnknown members for CFileObject object.
 */

STDMETHODIMP CFileObject::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IPersist==riid || IID_IPersistFile==riid)
        *ppv=m_pImpIPersistFile;

    if (IID_IParseDisplayName==riid || IID_IOleContainer==riid
        || IID_IOleItemContainer==riid)
        *ppv=m_pImpIOleItemContainer;

    if (IID_IDescription==riid)
        *ppv=m_pImpIDescription;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CFileObject::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CFileObject::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0;
    }




/**
 ** IPersistFile implementation
 **/

/*
 * CImpIPersistFile:CImpIPersistFile
 * CImpIPersistFile::~CImpIPersistFile
 * CImpIPersistFile::QueryInterface
 * CImpIPersistFile::AddRef
 * CImpIPersistFile::Release
 *
 * Basic object members.
 */

CImpIPersistFile::CImpIPersistFile(PCFileObject pObj
    , LPUNKNOWN pUnkOuter)
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
 * CImpIPersistFile::IsDirty
 * CImpIPersistFile::Save
 * CImpIPersistFile::SaveCompleted
 *
 * Trivial or unimplemented members.
 */

STDMETHODIMP CImpIPersistFile::GetClassID(LPCLSID pClsID)
    {
    *pClsID=m_pObj->m_clsID;
    return NOERROR;
    }

STDMETHODIMP CImpIPersistFile::IsDirty(void)
    {
    //We're never dirty
    return ResultFromScode(S_FALSE);
    }

STDMETHODIMP CImpIPersistFile::Save(LPCOLESTR pszFile, BOOL fRemember)
    {
    return ResultFromScode(E_NOTIMPL);
    }

STDMETHODIMP CImpIPersistFile::SaveCompleted(LPCOLESTR pszFile)
    {
    return NOERROR;
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
    const int   cch=512;
    HRESULT     hr;

    //We should only be loaded once; having a moniker tells us
    if (NULL!=m_pObj->m_pmk)
        return ResultFromScode(E_UNEXPECTED);

    /*
     * Since the server is single-use, we can be assured that
     * this Load will only happen once, so we can hold the
     * IStorage until the object is released.
     */
    hr=StgOpenStorage(pszFile, NULL
        , STGM_TRANSACTED | STGM_READ | STGM_SHARE_DENY_WRITE, NULL, 0
        , &m_pObj->m_pIStorage);

    if (FAILED(hr))
        return hr;

    m_pObj->m_pImpIDescription->SetStorage(m_pObj->m_pIStorage);

    /*
     * We opened it successfully, and that's all we have to
     * do, so we can simply save the filename.
     */
   #ifdef WIN32ANSI
    wcsncpy(m_pObj->m_szFile, pszFile, cch);
   #else
    lstrcpyn(m_pObj->m_szFile, pszFile, cch);
   #endif

    /*
     * Create a moniker for this file object and register as
     * running.
     */
    if (SUCCEEDED(CreateFileMoniker(pszFile, &m_pObj->m_pmk)))
        {
        IRunningObjectTable    *pROT;

        if (SUCCEEDED(GetRunningObjectTable(0, &pROT)))
            {
            //Register as weak so clients can free us
            pROT->Register(0, m_pObj, m_pObj->m_pmk
                , &m_pObj->m_dwRegROT);
            pROT->Release();
            }
        }

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
    LPMALLOC    pIMalloc;
    const int   cch=512;
    LPOLESTR    psz;

    *ppszFile=NULL;

    if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        return ResultFromScode(E_FAIL);

    psz=(LPOLESTR)pIMalloc->Alloc(cch*sizeof(OLECHAR));
    pIMalloc->Release();

    if (NULL==psz)
        return ResultFromScode(E_OUTOFMEMORY);

   #ifdef WIN32ANSI
    wcsncpy(psz, m_pObj->m_szFile, cch);
   #else
    lstrcpyn(psz, m_pObj->m_szFile, cch);
   #endif
    *ppszFile=psz;
    return NOERROR;
    }
