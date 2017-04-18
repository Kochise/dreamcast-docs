/*
 * SITE.CPP
 * Document Object Site Object
 *
 * Copyright (c)1995-1997 Microsoft Corporation, All Rights Reserved
 */


#include "framer.h"


/*
 * CSite::CSite
 * CSite::~CSite
 *
 * Constructor Parameters:
 *  dwID            DWORD identifer for this site.
 *  hWnd            HWND of the window associated with the site
 *  pFR             PCFrame to the parent structure.
 */

CSite::CSite(DWORD dwID, HWND hWnd, PCFrame pFR)
    {
    m_cRef=0;
    m_dwID=dwID;
    m_hWnd=hWnd;
    m_pFR=pFR;

    m_fInitialized=0;
    m_pIStorage=NULL;

    m_pObj=NULL;
    
    m_pIOleObject=NULL;
    m_pIOleIPObject=NULL;
    m_pIOleDocView=NULL;

    m_pImpIOleClientSite=NULL;
    m_pImpIAdviseSink=NULL;
    m_pImpIOleIPSite=NULL;
    m_pImpIOleDocumentSite=NULL;

    m_fDocObj=FALSE;
    return;
    }


CSite::~CSite(void)
    {
    //Object pointers cleaned up in Close.

    //We delete our own interfaces since we control them
    DeleteInterfaceImp(m_pImpIOleDocumentSite);
    DeleteInterfaceImp(m_pImpIOleIPSite);
    DeleteInterfaceImp(m_pImpIAdviseSink);
    DeleteInterfaceImp(m_pImpIOleClientSite);
    return;
    }




/*
 * CSite::QueryInterface
 * CSite::AddRef
 * CSite::Release
 *
 * Purpose:
 *  IUnknown members for CSite object.
 */

STDMETHODIMP CSite::QueryInterface(REFIID riid, void **ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IOleClientSite==riid)
        *ppv=m_pImpIOleClientSite;

    if (IID_IAdviseSink==riid)
        *ppv=m_pImpIAdviseSink;

    if (IID_IOleWindow==riid || IID_IOleInPlaceSite==riid)
        *ppv=m_pImpIOleIPSite;

    if (IID_IOleDocumentSite==riid)
        *ppv=m_pImpIOleDocumentSite;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CSite::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CSite::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }






/*
 * CSite::Create
 *
 * Purpose:
 *  Asks the site to instantiate an object given a filename.
 *  This goes through OleCreateFromFile and will either create
 *  an embedded object or a package (embedded) object.  When
 *  activated, this will either launch the app and activate
 *  as a DocObject, launch the app and open the file, or fail
 *  because no app can open the file.
 *
 * Parameters:
 *  pszFile         LPTSTR of the file from which to create the object.
 *  pIStorage       IStorage * of the parent storage in which we're
 *                  to create an IStorage for the new object.
 *  dwID            DWORD identifier for this site.
 *
 * Return Value:
 *  BOOL            Result of the creation.
 */

BOOL CSite::Create(LPTSTR pszFile, IStorage *pIStorage)
    {
    HRESULT             hr=E_FAIL;
    LPUNKNOWN           pObj;

    //Create a new storage for this object (sets m_pIStorage)
    if (!CreateStorage(pIStorage))
        return FALSE;

    //Now create an object from the file
   #ifdef UNICODE    
    hr=OleCreateFromFile(CLSID_NULL, pszFile, IID_IUnknown
        , OLERENDER_NONE, NULL, NULL, m_pIStorage, (void **)&pObj);
   #else
    OLECHAR     szFile[512];    //Assumption on string length

    MultiByteToWideChar(CP_ACP, 0, pszFile, -1, szFile, 512);    
	hr=OleCreateFromFile(CLSID_NULL, szFile, IID_IUnknown
        , OLERENDER_NONE, NULL, NULL, m_pIStorage, (void **)&pObj);
   #endif

    //If creation didn't work, get rid of the element Open created.
    if (FAILED(hr))
        {
        Destroy(pIStorage);
        return FALSE;
        }

    //We don't get the size if PatronObject data was seen already.
    if (!ObjectInitialize(pObj))
        {
        Destroy(pIStorage);
        return FALSE;
        }

    m_fInitialized=TRUE;
    return TRUE;
    }






/*
 * CSite::ObjectInitialize
 * (Protected)
 *
 * Purpose:
 *  Performs operations necessary after creating an object or
 *  reloading one from storage.
 *
 * Parameters:
 *  pObj            LPUNKNOWN of the object in this tenant.
 *  pFE             LPFORMATETC describing the graphic here.
 *  dwData          DWORD extra data.  If pFE->dwAspect==
 *                  DVASPECT_ICON then this is the iconic metafile.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CSite::ObjectInitialize(LPUNKNOWN pObj)
    {
    HRESULT         hr;
    DWORD           dw;

    if (NULL==pObj)
        return FALSE;

    m_pObj=pObj;

    //We need an IOleObject most of the time, so get one here.
    m_pIOleObject=NULL;
    hr=pObj->QueryInterface(IID_IOleObject, (void **)&m_pIOleObject);         

    /*
     * Follow up object creation with advises and so forth.  If
     * we cannot get IOleObject here, then we know we can't do
     * any IOleObject actions from here on--object is static.
     */
    if (FAILED(hr))
        return TRUE;

    //SetClientSite is critical for DocObjects
    m_pIOleObject->SetClientSite(m_pImpIOleClientSite);
    m_pIOleObject->Advise(m_pImpIAdviseSink, &dw);

	//This is to give PowerPoint a chance to initialize itself earlier
	OleRun(m_pIOleObject);
    return TRUE;
    }




/*
 * CSite::CreateStorage
 *
 * Purpose:
 *  Creates an sub-storage within a given parent storage,
 *  setting m_pIStorage.
 *
 * Parameters:
 *  pIStorage       IStorage * of the parent storage
 *
 * Return Value:
 *  BOOL            TRUE if creation succeeds, FALSE otherwise.
 */

BOOL CSite::CreateStorage(IStorage *pIStorage)
    {
    HRESULT     hr;
    DWORD       dwMode=STGM_TRANSACTED | STGM_READWRITE
                    | STGM_SHARE_EXCLUSIVE;
    TCHAR       szName[32];

    if (NULL==pIStorage)
        return FALSE;

    /*
     * Attempt to open the storage under this ID.  If there is
     * none, then create it.  In either case we end up with an
     * IStorage that we either save in pPage or release.
     */
    wsprintf(szName, TEXT("Site %lu"), m_dwID);

   #ifdef UNICODE
    hr=pIStorage->CreateStorage(szName, dwMode, 0, 0, &m_pIStorage);
   #else
    OLECHAR  szwName[32];
	MultiByteToWideChar(CP_ACP, 0, szName, -1, szwName, 32);    
    hr=pIStorage->CreateStorage(szwName, dwMode, 0, 0, &m_pIStorage);
   #endif

    if (FAILED(hr))
        return FALSE;

	//Create stream for the object; name is irrelevant
	dwMode=STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
   #ifdef UNICODE
    hr=m_pIStorage->CreateStream(TEXT("\003DocObjInfo"), dwMode, 0, 0
        , &m_pIStream);
   #else    
	MultiByteToWideChar(CP_ACP, 0, "\003DocObjInfo", -1, szwName, 32);    
    hr=m_pIStorage->CreateStream(szwName, dwMode, 0, 0, &m_pIStream);
   #endif
   
    //If we failed to create a stream in the file, do it in memory
	if (FAILED(hr))
		{
		if (FAILED(CreateStreamOnHGlobal(NULL, TRUE, &m_pIStream)))
		    return FALSE;
		}

    //Create interface implementations
    m_pImpIOleClientSite=new CImpIOleClientSite(this, this);
    m_pImpIAdviseSink=new CImpIAdviseSink(this, this);
    m_pImpIOleIPSite=new CImpIOleInPlaceSite(this, this);
    m_pImpIOleDocumentSite=new CImpIOleDocumentSite(this, this);

    if (NULL==m_pImpIOleClientSite || NULL==m_pImpIAdviseSink
        || NULL==m_pImpIOleIPSite || NULL==m_pImpIOleDocumentSite)
        return FALSE;

    return TRUE;
    }




/*
 * CSite::Close
 *
 * Purpose:
 *  Possibly commits the storage, then releases it, afterwards
 *  frees alls the object pointers.
 *
 * Parameters:
 *  fCommit         BOOL indicating if we're to commit.
 *
 * Return Value:
 *  None
 */

void CSite::Close(BOOL fCommit)
    {
    //OnInPlaceDeactivate releases this pointer.
    if (NULL!=m_pIOleIPObject)
        m_pIOleIPObject->InPlaceDeactivate();

    ReleaseInterface(m_pIOleDocView);

    if (NULL!=m_pIOleObject)
        {
        m_pIOleObject->Close(fCommit
            ? OLECLOSE_SAVEIFDIRTY : OLECLOSE_NOSAVE);
        ReleaseInterface(m_pIOleObject);
        }

    ReleaseInterface(m_pObj);
	ReleaseInterface(m_pIStream);
    ReleaseInterface(m_pIStorage);

    return;
    }




/*
 * CSite::Update
 *
 * Purpose:
 *  Forces a commit on the object's storage
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CSite::Update(void)
    {
    LPPERSISTSTORAGE    pIPS;

    if (NULL!=m_pIStorage)
        return;

    m_pObj->QueryInterface(IID_IPersistStorage, (void **)&pIPS);
    OleSave(pIPS, m_pIStorage, TRUE);
    pIPS->SaveCompleted(NULL);
    pIPS->Release();

    m_pIStorage->Commit(STGC_DEFAULT);
    return;
    }





/*
 * CSite::Destroy
 *
 * Purpose:
 *  Removes this storage from the parent storage.  The caller should
 *  eventually delete this CSite object to free the object herein.
 *  Nothing is committed when being destroyed.
 *
 * Parameters:
 *  pIStorage       IStorage * of the parent
 *
 * Return Value:
 *  None
 */

void CSite::Destroy(IStorage *pIStorage)
    {
    TCHAR     szName[32];

    if (NULL==pIStorage)
        return;

    if (NULL!=m_pObj)
        Close(FALSE);
    
	wsprintf(szName, TEXT("Site %lu"), m_dwID);
   #ifdef UNICODE
    pIStorage->DestroyElement(szName);
   #else
    OLECHAR  szwName[32];
	MultiByteToWideChar(CP_ACP, 0, szName, -1, szwName, 512);    
	pIStorage->DestroyElement(szwName);    
   #endif
    return;
    }





/*
 * CSite::Activate
 *
 * Purpose:
 *  Activates a verb on the object living in the site.
 *
 * Parameters:
 *  iVerb           LONG of the verb to execute.
 *
 * Return Value:
 *  None
 */

void CSite::Activate(LONG iVerb)
    {
    CHourglass *pHour;
    RECT        rc;
            
    pHour=new CHourglass;

    GetClientRect(m_hWnd, &rc);
    m_pIOleObject->DoVerb(iVerb, NULL, m_pImpIOleClientSite, 0
        , m_hWnd, &rc);

    delete pHour;
    return;
    }




/*
 * CSite::UpdateObjectRects
 *
 * Purpose:
 *  Informs the site that the client area window was resized and
 *  that the site needs to also tell the DocObject of the resize.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CSite::UpdateObjectRects(void)
    {
    RECT    rc;

    if (NULL==m_pIOleDocView)
        return;

    GetClientRect(m_hWnd, &rc);
    m_pIOleDocView->SetRect(&rc);
    return;
    }
