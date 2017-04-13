/*
 * IOLECONT.CPP
 * Link Source Server Chapter 9
 *
 * Implementation of the IOleItemContainer interface for
 * LinkSource's CFileObject and CContainerItem, using constructor
 * arguments to distinguish the relevant object.
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
#undef CreateItemMoniker
#define CreateItemMoniker CreateItemMoniker

#endif

extern ULONG g_cObj;


/*
 * CImpIOleItemContainer::CImpIOleItemContainer
 * CImpIOleItemContainer::~CImpIOleItemContainer
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the page or pages.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 *  fFileObj        BOOL indicating if we're in CFileObject.
 */

CImpIOleItemContainer::CImpIOleItemContainer(LPVOID pObj
    , LPUNKNOWN pUnkOuter, BOOL fFileObj)
    {
    m_cRef=0;
    m_fFileObj=fFileObj;

    if (fFileObj)
        {
        m_pObjFile=(PCFileObject)pObj;
        m_pObjCont=NULL;
        }
    else
        {
        m_pObjFile=NULL;
        m_pObjCont=(PCContainerItem)pObj;
        }

    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleItemContainer::~CImpIOleItemContainer(void)
    {
    return;
    }




/*
 * CImpIOleItemContainer::QueryInterface
 * CImpIOleItemContainer::AddRef
 * CImpIOleItemContainer::Release
 */

STDMETHODIMP CImpIOleItemContainer::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIOleItemContainer::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleItemContainer::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIOleItemContainer::ParseDisplayName
 *
 * Purpose:
 *  Parse the given name into a moniker as far as we know how
 *  to parse.
 *
 * Parameters:
 *  pbc             LPBC to the binding context
 *  pszName         LPOLESTR to the name to parse.
 *  pchEaten        ULONG * into which to store how many
 *                  characters we scanned in the display name.
 *  ppmk            LPMONIKER * in which to return the moniker.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::ParseDisplayName(LPBC pbc
    , LPOLESTR pszName, ULONG *pchEaten, LPMONIKER *ppmk)
    {
    OLECHAR     ch;
    ULONG       chEaten=0;
    TCHAR       szName[256];
    TCHAR       szComp[15];
    LPTSTR      psz;
    UINT        cch;

    *ppmk=NULL;
    *pchEaten=0;

    /*
     * All we have to look for is the string between the !
     * delimeters (or a null terminator).  pszName should be pointing
     * to a !, so skip it and scan the string for a ! or 0,
     * then pass the result to CreateItemMoniker.
     */

    psz=szName;

    ch=*pszName++;
    chEaten++;

    if ((OLECHAR)'!'!=ch)
        return ResultFromScode(MK_E_SYNTAX);

    ch=*pszName++;

    while ((OLECHAR)0!=ch && (OLECHAR)'!' !=ch)
        {
        *psz++=(TCHAR)ch;
        chEaten++;
        ch=*pszName++;
        }

    *psz=(TCHAR)0;

    /*
     * Syntax check.  If we're the File object, check for "Object n"
     * at the beginning of the string.  Otherwise check for
     * "Sub-Object n".
     */
    lstrcpy(szComp, m_fFileObj ? TEXT("Object ")
        : TEXT("Sub-Object "));

    //Does szName start with szComp?
    cch=lstrlen(szComp);

    if (0!=_tcsncicmp(szName, szComp, cch))
        {
        *pchEaten=1;    //Parsed ! at least
        return ResultFromScode(MK_E_SYNTAX);
        }

    //Check for a number in szName
    if ((TCHAR)'0' != szName[cch])
        {
        if (0==_ttoi(szName+cch))
            {
            *pchEaten=cch;  //Got past name
            return ResultFromScode(MK_E_SYNTAX);
            }
        }

    *pchEaten=chEaten;
   #ifdef WIN32ANSI
    //Use the ANSI version here since szName is ANSI
    return INOLE_CreateItemMoniker(TEXT("!"), szName, ppmk);
   #else
    return CreateItemMoniker(OLETEXT("!"), szName, ppmk);
   #endif
    }




/*
 * CImpIOleItemContainer::EnumObjects
 *
 * Purpose:
 *  Creates and returns an IEnumUnknown object that allows the
 *  caller to walk through the objects in this continer thing.
 *
 * Parameters:
 *  dwFlags         DWORD specifying what kind of objects to
 *                  enumerate.
 *  ppEnum          LPENUMUNKNOWN * into which to return the
 *                  enumerator
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::EnumObjects(DWORD dwFlags
    , LPENUMUNKNOWN *ppEnum)
    {
    *ppEnum=NULL;

    /*
     * We can leave this unimplemented in this sample since
     * we know no one will ever call it.  A real container
     * should be able to enumerate its contents.
     */
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleItemContainer::LockContainer
 *
 * Purpose:
 *  Establishes a lock on the container to prevent it from shutting
 *  down outside of user control.  This is used to control the
 *  lifetime of the container when it's used to update a link to an
 *  embedded object within it.  If we're unlock and the user has not
 *  taken control, we close.
 *
 * Parameters:
 *  fLock           BOOL indicating a lock or unlock.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::LockContainer(BOOL fLock)
    {
    /*
     * For the purposes of this server, we need only AddRef
     * and release ourselves depending on fLock.
     */

    if (fLock)
        AddRef();
    else
        Release();

    return NOERROR;
    }






/*
 * CImpIOleItemContainer::GetObject
 *
 * Purpose:
 *  Returns the requested interface pointer on an object in this
 *  container.
 *
 * Parameters:
 *  pszItem         LPOLESTR to the item we must locate.
 *  dwSpeed         DWORD identifying how long the caller is willing
 *                  to wait.
 *  pcb             LPBINDCTX providing the binding context.
 *  riid            REFIID of the interface requested.
 *  ppv             PPVOID into which to return the object.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::GetObject(LPOLESTR pszItem
    , DWORD dwSpeed, LPBINDCTX pbc, REFIID riid, PPVOID ppv)
    {
    HRESULT         hr;
    IStorage       *pIStorage;
    PCContainerItem pCI;
    PCSimpleItem    pSI;
    BOOL            fSuccess;
    IUnknown       *pUnk;

    *ppv=NULL;

    /*
     * The item name given to either CFileObj or CContainerItem
     * instantiations of this interface will be the name of
     * a storage below the current object's storage.  So we
     * use m_fFileObj to know which storage to look under
     * (names are either "Object n" or "Sub-Object n").
     *
     * If that storage exists, the object exists.  If it is
     * already running, we can check in the Running Object Table
     * and just return that object.  This is the only case that
     * works when the bind speed in the bind context is
     * immediate.
     *
     * Otherwise we open the storage and hand it to a new
     * instance of the right type of object (CContainerItem or
     * CSimpleItem), and register the new objects as running.
     */

    //Get the object if running
    hr=GetRunning(pszItem, pbc, riid, ppv, FALSE);

    if (BINDSPEED_IMMEDIATE==dwSpeed && NOERROR!=hr)
        return ResultFromScode(MK_E_EXCEEDEDDEADLINE);

    //If object was running, we're done!
    if (NOERROR==hr)
        return NOERROR;

    //Otherwise we need to get the storage.
    hr=GetObjectStorage(pszItem, pbc, IID_IStorage
        , (void **)&pIStorage);

    if (FAILED(hr))
        return hr;

    /*
     * Storage exists, so create an object and give that storage
     * to it.  The new object will also register itself in the
     * Running Object Table.
     */
    fSuccess=FALSE;

    if (m_fFileObj)
        {
        pCI=new CContainerItem(m_pObjFile, m_pObjFile->m_pfnDestroy);

        pUnk=pCI;

        if (NULL!=pCI)
            {
            pUnk->AddRef();
            fSuccess=pCI->Init(m_pObjFile->m_pmk, pbc, pszItem
                , pIStorage);
            }
        }
    else
        {
        pSI=new CSimpleItem(m_pObjCont, m_pObjCont->m_pfnDestroy);

        pUnk=pSI;

        if (NULL!=pSI)
            {
            pUnk->AddRef();
            fSuccess=pSI->Init(m_pObjCont->m_pmk, pbc, pszItem
                , pIStorage);
            }
        }

    if (!fSuccess)
        {
        if (NULL!=pUnk)
            pUnk->Release();

        return ResultFromScode(E_OUTOFMEMORY);
        }

    g_cObj++;

    //If QueryInterface fails, this Release destroys the object
    hr=pUnk->QueryInterface(riid, ppv);
    pUnk->Release();

    if (FAILED(hr))
        return hr;

    return NOERROR;
    }






/*
 * CImpIOleItemContainer::GetObjectStorage
 *
 * Purpose:
 *  Similar to GetObject in that we have to locate the object
 *  described by a given name, but instead of returning any old
 *  interface we return a storage element.
 *
 * Parameters:
 *  pszItem         LPOLESTR to the item we must locate.
 *  pcb             LPBINDCTX providing the binding context.
 *  riid            REFIID of the interface requested.  Usually
 *                  IStorage or IStream.
 *  ppv             PPVOID into which to return the object.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::GetObjectStorage(LPOLESTR pszItem
    , LPBINDCTX pbc, REFIID riid, PPVOID ppv)
    {
    IStorage       *pIStorageObj;
    IStorage       *pIStorageNew;
    HRESULT         hr;

    if (IID_IStorage!=riid)
        return ResultFromScode(MK_E_NOSTORAGE);

    pIStorageObj=m_fFileObj ? m_pObjFile->m_pIStorage
        : m_pObjCont->m_pIStorage;

    //Check storage existence
    hr=pIStorageObj->OpenStorage(pszItem
        , NULL, STGM_TRANSACTED | STGM_READ | STGM_SHARE_EXCLUSIVE
        , NULL, 0, &pIStorageNew);

    if (FAILED(hr))
        {
        IUnknown   *pUnk;

        /*
         * Because you must open a substorage with exclusive access,
         * we'll run into a problem where an object created for use
         * with parsing will still be running when another object of
         * the same type is used for binding.  The reason is that the
         * bind context holds these thing for optimization purposes.
         * But that does mean that OpenStorage above might fail
         * with STG_E_ACCESSDENIED.  In this case, we'll try to get
         * a previously opened storage from the bind context
         * (see below).
         */
        if (STG_E_ACCESSDENIED!=GetScode(hr))
            return hr;

        if (FAILED(pbc->GetObjectParam(SZOPENSTORAGE, &pUnk)))
            return ResultFromScode(STG_E_ACCESSDENIED);

        //This does the necessary AddRef on the IStorage pointer
        hr=pUnk->QueryInterface(IID_IStorage
            , (void **)&pIStorageNew);
        pUnk->Release();

        //This sets the out-parameter to NULL on failure
        *ppv=pIStorageNew;
        return hr;
        }

    *ppv=pIStorageNew;
    pbc->RegisterObjectParam(SZOPENSTORAGE, pIStorageNew);
    return NOERROR;
    }






/*
 * CImpIOleItemContainer::IsRunning
 *
 * Purpose:
 *  Answers if the object under the given name is currently running.
 *
 * Parameters:
 *  pszItem         LPOLESTR of the item to check
 *
 * Return Value:
 *  HRESULT         NOERROR if the object is running, S_FALSE
 *                  otherwise.  Possibly MK_E_NOOBJECT if the name
 *                  is bogus.
 */

STDMETHODIMP CImpIOleItemContainer::IsRunning(LPOLESTR pszItem)
    {
    return GetRunning(pszItem, NULL, IID_NULL, NULL, TRUE);
    }





/*
 * (Internal)
 * CImpIOleItemContainer::GetRunning
 *
 * Purpose:
 *  Grabs a running object from the running object table or
 *  just checks existence.
 *
 * Parameters:
 *  pszItem         LPOLESTR of the item to check
 *  pbc             IBindCtx * to use, can be NULL.
 *  riid            REFIID to return if fCheck is FALSE.
 *  ppv             void ** in which to return a pointer.
 *  fCheck          BOOL indicating to check (TRUE) or
 *                  retrieve (FALSE).
 *
 * Return Value:
 *  HRESULT         NOERROR if the object is running, S_FALSE
 *                  or an error otherwise.
 */

HRESULT CImpIOleItemContainer::GetRunning(LPOLESTR pszItem
    , IBindCtx *pbc, REFIID riid, void **ppv, BOOL fCheck)
    {
    OLECHAR              szDelim[]=OLETEXT("!");
    HRESULT              hr=ResultFromScode(S_FALSE);
    IMoniker            *pmkBase;
    IMoniker            *pmkItem;
    IMoniker            *pmkComp;
    IRunningObjectTable *pROT;

    pmkBase=m_fFileObj ? m_pObjFile->m_pmk : m_pObjCont->m_pmk;

    if (FAILED(CreateItemMoniker(szDelim, pszItem, &pmkItem)))
        return hr;

    //Create a composite with this item
    hr=pmkBase->ComposeWith(pmkItem, FALSE, &pmkComp);

    if (FAILED(hr))
        {
        pmkItem->Release();
        return hr;
        }


    if (NULL!=pbc)
        hr=pbc->GetRunningObjectTable(&pROT);
    else
        hr=GetRunningObjectTable(0, &pROT);

    if (SUCCEEDED(hr))
        {
        hr=pROT->IsRunning(pmkComp);

        //If running, grab the object if necessary
        if (!fCheck && NOERROR==hr)
            {
            IUnknown *pUnk;

            if(SUCCEEDED(pROT->GetObject(pmkComp, &pUnk)))
                {
                hr=pUnk->QueryInterface(riid, ppv);
                pUnk->Release();
                }
            }

        pROT->Release();
        }

    pmkComp->Release();
    pmkItem->Release();
    return hr;
    }
