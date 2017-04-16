/*
 * TENANT.CPP
 * Patron Control Container
 *
 * Implementation of the CTentant class which holds information
 * for a single object on a page.  It maintains position, references
 * to data, and a storage.
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CTenant::CTenant
 * CTenant::~CTenant
 *
 * Constructor Parameters:
 *  dwID            DWORD identifier for this page.
 *  hWnd            HWND of the pages window.
 *  pPG             PCPages to the parent structure.
 */

CTenant::CTenant(DWORD dwID, HWND hWnd, PCPages pPG)
    {
    m_hWnd=hWnd;
    m_dwID=dwID;

    m_fInitialized=0;
    m_pIStorage=NULL;
    m_cOpens=0;

    m_pObj=NULL;
    m_pPG =pPG;
    m_clsID=CLSID_NULL;
    m_fSetExtent=FALSE;

    m_cRef=0;
    m_pIOleObject=NULL;
    m_pIViewObject2=NULL;

    m_pIOleClientSite=NULL;
    m_pIAdviseSink=NULL;

    m_fLinkAvail=TRUE;          //Checked on FLoad

    m_pmk=NULL;
    m_pmkFile=NULL;

    m_fRepaintEnabled=TRUE;
    m_pIOleIPSite=NULL;
    m_pIOleIPObject=NULL;
    m_rcPos.left=-1;
    m_fInRectSet=FALSE;

    //CONTROLMOD
    m_pIOleControlSite=NULL;
    m_pIDispatch=NULL;

    m_pIPropNoteSink=NULL;
    m_dwConnProp=0L;

    m_pIDispatchEvents=NULL;
    m_dwConnEvents=0L;
    m_iidEvents=GUID_NULL;
    m_pEventMap=NULL;

    //0x80000000 in OLE_COLOR indicates low byte is color index.
    m_clrBack=0x80000000+COLOR_WINDOW;
    m_clrFore=0x80000000+COLOR_WINDOWTEXT;

    m_hFont=m_pPG->m_hFont;
    m_lcid=LOCALE_USER_DEFAULT;
    m_fDesignMode=m_pPG->m_fDesignMode;

    m_fHaveControlInfo=FALSE;
    m_cLockInPlace=0;
    m_fPendingDeactivate=FALSE;

    m_pIOleControl=NULL;
    m_pIDispatchControl=NULL;
    //End CONTROLMOD

    return;
    }


CTenant::~CTenant(void)
    {
    if (NULL!=m_pmk)
        m_pmk->Release();

    if (NULL!=m_pmkFile)
        m_pmkFile->Release();

    //Object pointers cleaned up in Close.

    //We delete our own interfaces since we control them
    //CONTROLMOD
    if (NULL!=m_pEventMap)
        delete m_pEventMap;

    if (NULL!=m_pIOleControlSite)
        delete m_pIOleControlSite;

    if (NULL!=m_pIPropNoteSink)
        delete m_pIPropNoteSink;

    if (NULL!=m_pIDispatch)
        delete m_pIDispatch;

    if (NULL!=m_pIDispatchEvents)
        delete m_pIDispatchEvents;
    //End CONTROLMOD

    if (NULL!=m_pIOleIPSite)
        delete m_pIOleIPSite;

    if (NULL!=m_pIAdviseSink)
        delete m_pIAdviseSink;

    if (NULL!=m_pIOleClientSite)
        delete m_pIOleClientSite;

    return;
    }




/*
 * CTenant::QueryInterface
 * CTenant::AddRef
 * CTenant::Release
 *
 * Purpose:
 *  IUnknown members for CTenant object.
 */

STDMETHODIMP CTenant::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IOleClientSite==riid)
        *ppv=m_pIOleClientSite;

    if (IID_IAdviseSink2==riid || IID_IAdviseSink==riid)
        *ppv=m_pIAdviseSink;

    if (IID_IOleWindow==riid || IID_IOleInPlaceSite==riid)
        *ppv=m_pIOleIPSite;

    //CONTROLMOD
    if (IID_IOleControlSite==riid)
        *ppv=m_pIOleControlSite;

    if (IID_IPropertyNotifySink==riid)
        *ppv=m_pIPropNoteSink;

    //Queries for IDispatch return the ambient properties interface
    if (IID_IDispatch==riid)
        *ppv=m_pIDispatch;
    //End CONTROLMOD

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CTenant::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CTenant::Release(void)
    {
    ULONG           cRefT;

    cRefT=--m_cRef;

    if (0L==m_cRef)
        delete this;

    return cRefT;
    }






/*
 * CTenant::GetID
 *
 * Return Value:
 *  DWORD           dwID field in this tenant.  This function is
 *                  only here to avoid hiding inline implementations
 *                  in tenant.h.
 */

DWORD CTenant::GetID(void)
    {
    return m_dwID;
    }



/*
 * CTenant::GetStorageName
 *
 * Parameters:
 *  pszName         LPTSTR to a buffer in which to store the storage
 *                  name for this tenant.
 *
 * Return Value:
 *  UINT            Number of characters stored.
 */

UINT CTenant::GetStorageName(LPTSTR pszName)
    {
    return wsprintf(pszName, TEXT("Tenant %lu"), m_dwID);
    }





/*
 * CTenant::UCreate
 *
 * Purpose:
 *  Creates a new tenant of the given CLSID, which can be either a
 *  static bitmap or metafile now (Chapter 7) and which may
 *  eventually be any compound document object.
 *
 * Parameters:
 *  tType           TENANTTYPE to create, either a static metafile,
 *                  bitmap, or some kind of compound document object
 *                  This determines which OleCreate* call we use.
 *  pvType          LPVOID providing the relevant pointer from which
 *                  to create the tenant, depending on iType.
 *  pFE             LPFORMATETC specifying the type of renderings
 *                  to use.
 *  pptl            LPPOINTL in which we store offset coordinates.
 *  pszl            LPSIZEL where this object should store its
 *                  lometric extents.
 *  pIStorage       LPSTORAGE of the page we live in.  We have to
 *                  create another storage in this for the tenant.
 *  ppo             PPATRONOBJECT containing placement data.
 *  dwData          DWORD with extra data, sensitive to iType.
 *
 * Return Value:
 *  UINT            A UCREATE_* value depending on what we
 *                  actually do.
 */

UINT CTenant::UCreate(TENANTTYPE tType, LPVOID pvType
    , LPFORMATETC pFE, LPPOINTL pptl, LPSIZEL pszl
    , LPSTORAGE pIStorage, PPATRONOBJECT ppo, DWORD dwData)
    {
    HRESULT             hr;
    LPUNKNOWN           pObj;
    UINT                uRet=UCREATE_GRAPHICONLY;

    if (NULL==pvType || NULL==pIStorage)
        return UCREATE_FAILED;

    //Fail if this is called for an already living tenant.
    if (m_fInitialized)
        return UCREATE_FAILED;

    m_fInitialized=TRUE;

    //Create a new storage for this tenant.
    if (!FOpen(pIStorage))
        return UCREATE_FAILED;

    /*
     * Get the placement info if it's here.  We either have a non-
     * NULL PPATRONOBJECT in ppo or we have to use default
     * placement and retrieve the size from the object itself.
     */
    pszl->cx=0;
    pszl->cy=0;

    if (NULL!=ppo)
        {
        *pFE=ppo->fe;
        *pptl=ppo->ptl;
        *pszl=ppo->szl;     //Could be 0,0 , so we ask object

        uRet=UCREATE_PLACEDOBJECT;
        }

    hr=ResultFromScode(E_FAIL);

    //Now create an object based specifically for the type.
    switch (tType)
        {
        case TENANTTYPE_NULL:
            break;

        case TENANTTYPE_STATIC:
            /*
             * We could use OleCreateStaticFromData here which does
             * pretty much what we're doing below.  However, it does
             * not allow us to control whether we paste a bitmap or
             * a metafile--it uses metafile first, bitmap second.
             * For this reason we'll use code developed in Chapter
             * 6's FreeLoader to affect the paste.
             */
            hr=CreateStatic((LPDATAOBJECT)pvType, pFE, &pObj);
            break;

        case TENANTTYPE_EMBEDDEDOBJECT:
            //CONTROLMOD
            /*
             * The OLE Control specifications mention that a
             * a control might implement IPersistStreamInit
             * instead of IPersistStorage.  In that case you
             * cannot use OleCreate on a control but must rather
             * use CoCreateInstance since OleCreate assumes
             * that IPersistStorage is available.  With a control,
             * you would have to create the object first, then
             * check if OLEMISC_SETCLIENTSITEFIRST is set, then
             * send it your IOleClientSite first.  Then you check
             * for IPersistStorage and failing that, try
             * IPersistStreamInit.
             *
             * In this sample we do none of this and just assume
             * controls are normal embedded objects because there
             * are questions as to dealing with loading and
             * initialization that are not resolved.
             */
            //End CONTROLMOD

            hr=OleCreate(*((LPCLSID)pvType), IID_IUnknown
                , OLERENDER_DRAW, NULL, NULL, m_pIStorage
                , (PPVOID)&pObj);
            break;

        case TENANTTYPE_EMBEDDEDFILE:
            hr=OleCreateFromFile(CLSID_NULL, (LPTSTR)pvType
                , IID_IUnknown, OLERENDER_DRAW, NULL, NULL
                , m_pIStorage, (PPVOID)&pObj);
            break;

        case TENANTTYPE_EMBEDDEDOBJECTFROMDATA:
            hr=OleCreateFromData((LPDATAOBJECT)pvType, IID_IUnknown
                , OLERENDER_DRAW, NULL, NULL, m_pIStorage
                , (PPVOID)&pObj);
            break;

        case TENANTTYPE_LINKEDFILE:
            hr=OleCreateLinkToFile((LPTSTR)pvType, IID_IUnknown
                , OLERENDER_DRAW, NULL, NULL, m_pIStorage
                , (PPVOID)&pObj);
            break;

        case TENANTTYPE_LINKEDOBJECTFROMDATA:
            hr=OleCreateLinkFromData((LPDATAOBJECT)pvType
                , IID_IUnknown, OLERENDER_DRAW, NULL, NULL
                , m_pIStorage, (PPVOID)&pObj);
            break;

        default:
            break;
        }

    //If creation didn't work, get rid of the element FOpen created.
    if (FAILED(hr))
        {
        Destroy(pIStorage);
        return UCREATE_FAILED;
        }

    //We don't get the size if PatronObject data was seen already.
    if (!FObjectInitialize(pObj, pFE, dwData))
        {
        Destroy(pIStorage);
        return UCREATE_FAILED;
        }

    if (0==pszl->cx && 0==pszl->cy)
        {
        SIZEL   szl;

        //Try to get the real size of the object, default to 2"*2"
        SETSIZEL((*pszl), 2*LOMETRIC_PER_INCH, 2*LOMETRIC_PER_INCH);
        hr=ResultFromScode(E_FAIL);

        //Try IViewObject2 first, then IOleObject as a backup.
        if (NULL!=m_pIViewObject2)
            {
            hr=m_pIViewObject2->GetExtent(m_fe.dwAspect, -1, NULL
                , &szl);
            }
        else
            {
            if (NULL!=m_pIOleObject)
                hr=m_pIOleObject->GetExtent(m_fe.dwAspect, &szl);
            }

        if (SUCCEEDED(hr))
            {
            //Convert HIMETRIC to our LOMETRIC mapping
            SETSIZEL((*pszl), szl.cx/10, szl.cy/10);
            }
        }

    return uRet;
    }






/*
 * CTenant::FLoad
 *
 * Purpose:
 *  Recreates the object living in this tenant in place of calling
 *  FCreate.  This is used in loading as opposed to new creation.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE of the page we live in.
 *  pti             PTENTANTINFO containing persistent information.
 *                  The ID value in this structure is ignored.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CTenant::FLoad(LPSTORAGE pIStorage, PTENANTINFO pti)
    {
    HRESULT         hr;
    LPUNKNOWN       pObj;
    DWORD           dwState=TENANTSTATE_DEFAULT;

    if (NULL==pIStorage || NULL==pti)
        return FALSE;

    /*
     * If we already initialized once, clean up, releasing
     * everything before we attempt to reload.  This happens from
     * the Convert dialog.
     */

    if (m_fInitialized)
        {
        //Preserve all states except open
        dwState=(m_dwState & ~TENANTSTATE_OPEN);
        m_cRef++;   //Prevent accidental closure

        //This should release all holds on our IStorage as well.
        if (NULL!=m_pIViewObject2)
            {
            m_pIViewObject2->SetAdvise(m_fe.dwAspect, 0, NULL);
            m_pIViewObject2->Release();
            }

        if (NULL!=m_pIOleObject)
            m_pIOleObject->Release();

        if (NULL!=m_pObj)
            m_pObj->Release();

        m_pIViewObject2=NULL;
        m_pIOleObject=NULL;
        m_pObj=NULL;

        //We'll have already released this.
        m_pIStorage=NULL;

        m_cRef--;  //Match safety increment above.
        }

    m_fInitialized=TRUE;

    //Open the storage for this tenant.
    if (!FOpen(pIStorage))
        return FALSE;

    /*
     * NOTE:  If you do not pass an IOleClientSite to OleLoad
     * it will not automatically reconnect a linked object to
     * the running source via IOleLink::BindIfRunning.  Since
     * we do not pass m_pIOleClientSite here, we'll call
     * BindIfRunning ourselves in FObjectInitialize.
     */

    //CONTROLMOD
    /*
     * As with creation, OleLoad may not work for all controls,
     * especially those that implement IPersistStream or
     * instead of IPersistStorage, as well as those that have
     * OLEMISC_SETCLIENTSITEFIRST.   Instead of loading the object
     * with OleLoad we instead have to create it with CoCreateInstance
     * then initialize with IPersistStream::Load, possibly calling
     * IOleObject::SetClientSite first.
     *
     * This sample only works with controls that are the same as
     * embedded objects, that is, those with IPersistStorage and
     * those that don't need the client site first.
     */
    //End CONTROLMOD

    hr=OleLoad(m_pIStorage, IID_IUnknown, NULL, (PPVOID)&pObj);

    if (FAILED(hr))
        {
        Destroy(pIStorage);
        return FALSE;
        }

    m_fSetExtent=pti->fSetExtent;
    if (!FObjectInitialize(pObj, &pti->fe, NULL))
        {
        Destroy(pIStorage);
        return FALSE;
        }

    m_dwState=dwState;
    RectSet(&pti->rcl, FALSE, FALSE);

    /*
     * If the object is ActiveWhenVisible, send it the
     * OLEIVERB_INPLACEACTIVATE verb now unless we're
     * in design mode, then don't send at all.
     */

    //CONTROLMOD
    if ((OLEMISC_ACTIVATEWHENVISIBLE & m_grfMisc) && !m_fDesignMode)
        Activate(OLEIVERB_INPLACEACTIVATE, NULL);
    //End CONTROLMOD

    return TRUE;
    }




/*
 * CTenant::GetInfo
 *
 * Purpose:
 *  Retrieved a TENANTINFO structure for this tenant.
 *
 * Parameters:
 *  pti             PTENANTINFO structure to fill
 *
 * Return Value:
 *  None
 */

void CTenant::GetInfo(PTENANTINFO pti)
    {
    if (NULL!=pti)
        {
        pti->dwID=m_dwID;
        pti->rcl=m_rcl;
        pti->fe=m_fe;
        pti->fSetExtent=m_fSetExtent;
        }

    return;
    }




/*
 * CTenant::FObjectInitialize
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

BOOL CTenant::FObjectInitialize(LPUNKNOWN pObj, LPFORMATETC pFE
    , DWORD dwData)
    {
    HRESULT         hr;
    LPPERSIST       pIPersist=NULL;
    DWORD           dw;
    PCDocument      pDoc;
    TCHAR           szFile[CCHPATHMAX];
    LPOLELINK       pIOleLink=NULL;

    if (NULL==pObj || NULL==pFE)
        return FALSE;

    m_pObj=pObj;
    m_fe=*pFE;
    m_fe.ptd=NULL;
    m_dwState=TENANTSTATE_DEFAULT;

    /*
     * Determine the type:  Static or Embedded.  If Static,
     * this will have CLSID_Picture_Metafile or CLSID_Picture_Dib.
     * Otherwise it's embedded.  Later we'll add a case for links.
     */
    m_tType=TENANTTYPE_EMBEDDEDOBJECT;

    if (SUCCEEDED(pObj->QueryInterface(IID_IPersist
        , (PPVOID)&pIPersist)))
        {
        CLSID   clsid=CLSID_NULL;

        hr=pIPersist->GetClassID(&clsid);

        //If we don't have a CLSID, default to static
        if (FAILED(hr) || CLSID_Picture_Metafile==clsid
            || CLSID_Picture_Dib==clsid)
            m_tType=TENANTTYPE_STATIC;

        pIPersist->Release();
        }

    //Check if this is a linked object.
    if (SUCCEEDED(pObj->QueryInterface(IID_IOleLink
        , (PPVOID)&pIOleLink)))
        {
        LPMONIKER   pmk;

        hr=pIOleLink->GetSourceMoniker(&pmk);

        if (FAILED(hr) || NULL==pmk)
            m_tType=TENANTTYPE_STATIC;
        else
            {
            m_tType=TENANTTYPE_LINKEDOBJECT;
            pmk->Release();

            //Connect to the object if the source is running.
            pIOleLink->BindIfRunning();
            }

        pIOleLink->Release();
        }

    m_pIViewObject2=NULL;
    hr=pObj->QueryInterface(IID_IViewObject2
        , (PPVOID)&m_pIViewObject2);

    if (FAILED(hr))
        return FALSE;

    m_pIViewObject2->SetAdvise(m_fe.dwAspect, 0, m_pIAdviseSink);

    //We need an IOleObject most of the time, so get one here.
    m_pIOleObject=NULL;
    hr=pObj->QueryInterface(IID_IOleObject
         , (PPVOID)&m_pIOleObject);

    /*
     * Follow up object creation with advises and so forth.  If
     * we cannot get IOleObject here, then we know we can't do
     * any IOleObject actions from here on--object is static.
     */
    if (FAILED(hr))
        return TRUE;

    /*
     * Get the MiscStatus bits and check for OLEMISC_ONLYICONIC.
     * If set, force dwAspect in m_fe to DVASPECT_ICON so we
     * remember to draw it properly and do extents right.
     */
    m_pIOleObject->GetMiscStatus(m_fe.dwAspect, &m_grfMisc);

    //CONTROLMOD
    //Run the object if it says to do so
    if (OLEMISC_ALWAYSRUN & m_grfMisc)
        OleRun(pObj);
    //End CONTROLMOD

    if (OLEMISC_ONLYICONIC & m_grfMisc)
        m_fe.dwAspect=DVASPECT_ICON;

    /*
     * We could pass m_pIOleClientSite in an OleCreate* call, but
     * since this function could be called after OleLoad, we still
     * need to do this here, so it's always done here...
     */
    m_pIOleObject->SetClientSite(m_pIOleClientSite);
    m_pIOleObject->Advise(m_pIAdviseSink, &dw);

    OleSetContainedObject(m_pIOleObject, TRUE);

    /*
     * For IOleObject::SetHostNames we need the application name
     * and the document name (which is passed in the object
     * parameter).  The design of Patron doesn't give us nice
     * structured access to the name of the document we're in, so
     * I grab the parent of the Pages window (the document) and
     * send it DOCM_PDOCUMENT which returns us the pointer.
     * Roundabout, but it works.
     */

    pDoc=(PCDocument)SendMessage(GetParent(m_hWnd), DOCM_PDOCUMENT
        , 0, 0L);

    if (NULL!=pDoc)
        pDoc->FilenameGet(szFile, CCHPATHMAX);
    else
        szFile[0]=0;

    NotifyOfRename(szFile, NULL, NULL);

    /*
     * This might have been Display as Icon (or the
     * OLEMISC_ONLYICONIC flag was set) in which case
     * m_fe.dwAspect=DVASPECT_ICON.  If this is coming from
     * a Display As Icon choice, then then dwData is a handle
     * to a metafile with the iconic aspect.  We take this and shove
     * it into the cache for this aspect, releasing the content
     * aspect.  OLE2UI has a nice function that does this:
     * OleStdSwitchDisplayAspect, which also handles the case
     * when we might want to switch BACK to content in the
     * Change Type dialog.
     *
     * If the object is marked as OLEMISC_ONLYICONIC, then it
     * is responsible for rendering the iconic image--not us.
     */

    if ((DVASPECT_ICON & m_fe.dwAspect) && NULL!=dwData)
        {
        //Temps to give to OleStdSwitchDisplayAspect
        DWORD       dw=DVASPECT_CONTENT;
        BOOL        fUpdate;

        OleStdSwitchDisplayAspect(m_pIOleObject, &dw, DVASPECT_ICON
            , (HGLOBAL)(UINT)dwData, TRUE, FALSE, NULL, &fUpdate);
        }


    //CONTROLMOD
    //Go try initializing control-related things.
    FControlInitialize();
    //End CONTROLMOD

    return TRUE;
    }



/*
 * CTenant::FOpen
 *
 * Purpose:
 *  Retrieves the IStorage associated with this tenant.  The
 *  IStorage is owned by the tenant and thus the tenant always
 *  holds a reference count.
 *
 *  If the storage is already open for this tenant, then this
 *  function will AddRef it; therefore the caller must always
 *  match an FOpen with a Close.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE above this tenant (which has its
 *                  own storage).
 *
 * Return Value:
 *  BOOL            TRUE if opening succeeds, FALSE otherwise.
 */

BOOL CTenant::FOpen(LPSTORAGE pIStorage)
    {
    HRESULT     hr=NOERROR;
    DWORD       dwMode=STGM_TRANSACTED | STGM_READWRITE
                    | STGM_SHARE_EXCLUSIVE;
    TCHAR       szTemp[32];

    if (NULL==m_pIStorage)
        {
        if (NULL==pIStorage)
            return FALSE;

        /*
         * Attempt to open the storage under this ID.  If there is
         * none, then create it.  In either case we end up with an
         * IStorage that we either save in pPage or release.
         */

        GetStorageName(szTemp);
        hr=pIStorage->OpenStorage(szTemp, NULL, dwMode, NULL, 0
            , &m_pIStorage);

        if (FAILED(hr))
            {
            hr=pIStorage->CreateStorage(szTemp, dwMode, 0, 0
                , &m_pIStorage);
            }
        }
    else
        m_pIStorage->AddRef();

    if (FAILED(hr))
        return FALSE;

    m_cOpens++;

    //Create these if we don't have them already.
    if (NULL==m_pIOleClientSite && NULL==m_pIAdviseSink)
        {
        m_pIOleClientSite=new CImpIOleClientSite(this, this);
        m_pIAdviseSink=new CImpIAdviseSink(this, this);
        m_pIOleIPSite=new CImpIOleInPlaceSite(this, this);

        //CONTROLMOD
        m_pIOleControlSite=new CImpIOleControlSite(this, this);
        m_pIDispatch=new CImpIDispatch(this, this);

        if (NULL==m_pIOleClientSite || NULL==m_pIAdviseSink
            || NULL==m_pIOleIPSite || NULL==m_pIOleControlSite
            || NULL==m_pIDispatch)
            return FALSE;
        //End CONTROLMOD
        }

    return TRUE;
    }




/*
 * CTenant::Close
 *
 * Purpose:
 *  Possibly commits the storage, then releases it reversing the
 *  reference count from FOpen.  If the reference on the storage
 *  goes to zero, the storage is forgotten.  However, the object we
 *  contain is still held and as long as it's active the storage
 *  remains alive.
 *
 * Parameters:
 *  fCommit         BOOL indicating if we're to commit.
 *
 * Return Value:
 *  None
 */

void CTenant::Close(BOOL fCommit)
    {
    if (fCommit)
        Update();

    if (NULL!=m_pIStorage)
        {
        m_pIStorage->Release();

        /*
         * We can't use a zero reference count to know when to NULL
         * this since other things might have AddRef'd the storage.
         */
        if (0==--m_cOpens)
            {
            m_pIStorage=NULL;

            if (NULL!=m_pIOleIPObject)
                {
                m_pIOleIPObject->InPlaceDeactivate();
                ReleaseInterface((IUnknown **)m_pIOleIPObject);
                }

            //Close the object saving if necessary
            if (NULL!=m_pIOleObject)
                {
                m_pIOleObject->Close(OLECLOSE_SAVEIFDIRTY);
                ReleaseInterface((IUnknown **)&m_pIOleObject);
                }

            //Release all other held pointers
            //CONTROLMOD
            ReleaseInterface((IUnknown **)&m_pIOleControl);
            ReleaseInterface((IUnknown **)&m_pIDispatchControl);

            if (0!=m_dwConnEvents)
                {
                InterfaceDisconnect(m_pObj, m_iidEvents
                    , &m_dwConnEvents);
                }

            if (0!=m_dwConnProp)
                {
                InterfaceDisconnect(m_pObj
                    , IID_IPropertyNotifySink, &m_dwConnProp);
                }
            //End CONTROLMOD

            ReleaseInterface((IUnknown **)&m_pIOleObject);

            if (NULL!=m_pIViewObject2)
                {
                m_pIViewObject2->SetAdvise(m_fe.dwAspect, 0, NULL);
                ReleaseInterface((IUnknown **)&m_pIViewObject2);
                }

            ReleaseInterface((IUnknown **)&m_pObj);
            }
        }

    return;
    }




/*
 * CTenant::Update
 *
 * Purpose:
 *  Forces a common on the page if it's open.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the object is open, FALSE otherwise.
 */

BOOL CTenant::Update(void)
    {
    LPPERSISTSTORAGE    pIPS;

    if (NULL!=m_pIStorage)
        {
        /*
         * We need to OleSave again because we might have changed
         * the size or position of this tenant.  We also need to
         * save the rectangle on the page, since that's not known
         * to OLE.
         */
        m_pObj->QueryInterface(IID_IPersistStorage, (PPVOID)&pIPS);

        //CONTROLMOD
        /*
         * Some controls may not implement IPersistStorage, using
         * IPersistStream[Init] instead.  In that case, the
         * QueryInterface above will fail, and we then have to
         * create a stream ourselves in m_pIStorage in which to
         * serialize the object through IPersistStream.  This
         * sample doesn't support stream-only objects at this time.
         */
        //End CONTROLMOD

        //This fails for static objects...so we improvise if so
        if (FAILED(OleSave(pIPS, m_pIStorage, TRUE)))
            {
            //This is essentially what OleSave does.
            WriteClassStg(m_pIStorage, m_clsID);
            pIPS->Save(m_pIStorage, TRUE);
            }

        //CONTROLMOD
        /*
         * If this is a control, then we also need to serialize
         * our events list.  We do this into a stream called
         * "\x03Events Mapping" the presence of which is used in
         * FControlInitialize to initialize the events map.  Note
         * that since we're writing a container stream into the
         * object's IStorage then we have to use the ASCII 3 prefix.
         */
        if (HasEvents())
            {
            LPSTREAM    pIStream;
            HRESULT     hr;

            hr=m_pIStorage->CreateStream(SZEVENTSSTREAM
                , STGM_CREATE | STGM_DIRECT | STGM_READWRITE
                | STGM_SHARE_EXCLUSIVE, 0, 0, &pIStream);

            if (SUCCEEDED(hr));
                {
                m_pEventMap->Serialize(pIStream);
                pIStream->Release();
                }
            }
        //End CONTROLMOD

        pIPS->SaveCompleted(NULL);
        pIPS->Release();

        m_pIStorage->Commit(STGC_ONLYIFCURRENT);
        }

    return FALSE;
    }





/*
 * CTenant::Destroy
 *
 * Purpose:
 *  Removes this page from the given storage.  The caller should
 *  eventually delete this CTenant object to free the object herein.
 *  Nothing is committed when being destroyed.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE contianing this page on which to call
 *                  DestroyElement
 *
 * Return Value:
 *  None
 */

void CTenant::Destroy(LPSTORAGE pIStorage)
    {
    TCHAR       szTemp[32];

    if (NULL!=pIStorage)
        {
        if (NULL!=m_pIOleObject)
            {
            DeactivateInPlaceObject(TRUE);
            m_pIOleObject->Close(OLECLOSE_NOSAVE);
            }

        if (NULL!=m_pIStorage)
            {
            //Remove all reference/open counts on this storage.
            while (0!=m_cOpens)
                {
                m_pIStorage->Release();
                m_cOpens--;
                }
            }

        GetStorageName(szTemp);
        pIStorage->DestroyElement(szTemp);

        m_pIStorage=NULL;
        }

    return;
    }




/*
 * CTenant::Select
 *
 * Purpose:
 *  Selects or deselects the tenant.
 *
 * Parameters:
 *  fSelect         BOOL indicating the new state of the tenant.
 *  fActivate       BOOL indicating whether to activate or
 *                  deactivate an in-place object.  If TRUE, then
 *                  activation/deactivation will happen.  If
 *                  FALSE, no change in activation takes place.
 *
 * Return Value:
 *  None
 */

void CTenant::Select(BOOL fSelect, BOOL fActivate)
    {
    BOOL        fWasSelected;
    DWORD       dwState;
    RECT        rc;
    HDC         hDC;

    fWasSelected=(BOOL)(TENANTSTATE_SELECTED & m_dwState);

    //Nothing to do when there's no change.
    if (fWasSelected==fSelect)
        return;

    dwState=m_dwState & ~TENANTSTATE_SELECTED;
    m_dwState=dwState | ((fSelect) ? TENANTSTATE_SELECTED : 0);

    /*
     * Draw sizing handles to show the selection state.  We convert
     * things to MM_TEXT since that's what this function expects.
     */

    //CONTROLMOD
    /*
     * Suppress drawing any handles for invisible controls
     * unless we're in design mode.
     */
    if (!(OLEMISC_INVISIBLEATRUNTIME & m_grfMisc)
        || m_fDesignMode)
        {
    //End CONTROLMOD
        RECTFROMRECTL(rc, m_rcl);
        RectConvertMappings(&rc, NULL, TRUE);
        OffsetRect(&rc, -(int)m_pPG->m_xPos, -(int)m_pPG->m_yPos);

        hDC=GetDC(m_hWnd);

        OleUIDrawHandles(&rc, hDC, OLEUI_HANDLES_INSIDE
            | OLEUI_HANDLES_NOBORDER| OLEUI_HANDLES_USEINVERSE
            , CXYHANDLE, !fWasSelected);

        ReleaseDC(m_hWnd, hDC);
        }

    if (fActivate)
        {
        if (!fSelect)
            DeactivateInPlaceObject(FALSE);
        else
            {
            //CONTROLMOD
            /*
             * Normally we'll send OLEIVERB_UIACTIVATE to any
             * inside-out object.  A control might be marked
             * with OLEMISC_NOUIACTIVATE in which case we skip
             * this step entirely.
             */
            if ((m_grfMisc & OLEMISC_INSIDEOUT) &&
                ! (m_grfMisc & OLEMISC_NOUIACTIVATE))
                Activate(OLEIVERB_UIACTIVATE, NULL);
            //End CONTROLMOD
            }
        }

    return;
    }




/*
 * CTenant::ShowAsOpen
 *
 * Purpose:
 *  Draws or removes the hatch pattern over an object.
 *
 * Parameters:
 *  fOpen           BOOL indicating the open state of this tenant.
 *
 * Return Value:
 *  None
 */

void CTenant::ShowAsOpen(BOOL fOpen)
    {
    BOOL        fWasOpen;
    DWORD       dwState;
    RECT        rc;
    HDC         hDC;

    fWasOpen=(BOOL)(TENANTSTATE_OPEN & m_dwState);

    dwState=m_dwState & ~TENANTSTATE_OPEN;
    m_dwState=dwState | ((fOpen) ? TENANTSTATE_OPEN : 0);

    //CONTROLMOD
    /*
     * Suppress drawing shading in any case if this object is
     * invisible at run time and we're not in design mode.
     */
    if ((OLEMISC_INVISIBLEATRUNTIME & m_grfMisc)
        && !m_fDesignMode)
        {
        return;
        }
    //End CONTROLMOD

    //If this was not open, then just hatch, otherwise repaint.
    if (!fWasOpen && fOpen)
        {
        RECTFROMRECTL(rc, m_rcl);
        RectConvertMappings(&rc, NULL, TRUE);
        OffsetRect(&rc, -(int)m_pPG->m_xPos, -(int)m_pPG->m_yPos);

        hDC=GetDC(m_hWnd);
        OleUIDrawShading(&rc, hDC, OLEUI_SHADE_FULLRECT, 0);
        ReleaseDC(m_hWnd, hDC);
        }

    if (fWasOpen && !fOpen)
        Repaint();

    return;
    }





/*
 * CTenant::ShowYourself
 *
 * Purpose:
 *  Function that really just implements IOleClientSite::ShowObject.
 *  Here we first check if the tenant is fully visible, and if so,
 *  then nothing needs to happen.  Otherwise, if the upper left
 *  corner of the tenant is in the upper left visible quadrant of
 *  the window, we'll also consider ourselves done.  Otherwise
 *  we'll put the upper left corner of the object at the upper left
 *  corner of the window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CTenant::ShowYourself(void)
    {
    RECTL       rcl;
    RECT        rc;
    POINT       pt1, pt2;

    //Scrolling deals in device units; get our rectangle in those.
    RectGet(&rcl, TRUE);

    //Get the window rectangle offset for the current scroll pos.
    GetClientRect(m_hWnd, &rc);
    OffsetRect(&rc, m_pPG->m_xPos, m_pPG->m_yPos);

    //Check if the object is already visible. (macro in bookguid.h)
    SETPOINT(pt1, (int)rcl.left,  (int)rcl.top);
    SETPOINT(pt2, (int)rcl.right, (int)rcl.bottom);

    /*
     * If we're doing in-place, don't move anything if the
     * object is visible AT ALL.  IOleInPlaceSite::OnInPlaceActivate
     * will have been called by now--the object will always
     * make that call before showing itself.
     */
    if (NULL!=m_pIOleIPObject && PtInRect(&rc, pt1))
        return;

    if (PtInRect(&rc, pt1) && PtInRect(&rc, pt2))
        return;

    //Check if the upper left is within the upper left quadrant
    if (((int)rcl.left > rc.left
        && (int)rcl.left < ((rc.right+rc.left)/2))
        && ((int)rcl.top > rc.top
        && (int)rcl.top < ((rc.bottom+rc.top)/2)))
        return;

    //These are macros in INC\BOOK1632.H
    SendScrollPosition(m_hWnd, WM_HSCROLL, rcl.left-8);
    SendScrollPosition(m_hWnd, WM_VSCROLL, rcl.top-8);
    return;
    }



/*
 * CTenant::AddVerbMenu
 *
 * Purpose:
 *  Creates the variable verb menu item for the object in this
 *  tenant.
 *
 * Parmeters:
 *  hMenu           HMENU on which to add items.
 *  iPos            UINT position on that menu to add items.
 *
 * Return Value:
 *  None
 */

void CTenant::AddVerbMenu(HMENU hMenu, UINT iPos)
    {
    HMENU       hMenuTemp;
    LPOLEOBJECT pObj=m_pIOleObject;

    //If we're static, say we have no object.
    if (TENANTTYPE_STATIC==m_tType)
        pObj=NULL;

    OleUIAddVerbMenu(pObj, NULL, hMenu, iPos, IDM_VERBMIN
        , IDM_VERBMAX, TRUE, IDM_EDITCONVERT, &hMenuTemp);

    return;
    }






/*
 * CTenant::CopyEmbeddedObject
 *
 * Purpose:
 *  Copies an embedded object to the given data object (via SetData,
 *  assuming this is a data transfer object for clipboard/drag-drop)
 *  if that's what we're holding.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT in which to store the copy.
 *  pFE             LPFORMATETC into which to copy CF_EMBEDDEDOBJECT
 *                  if we put that in the data object.
 *  pptl            LPPOINTL to the pick point (NULL outside of
 *                  drag-drop);
 *
 * Return Value:
 *  None
 */

void CTenant::CopyEmbeddedObject(LPDATAOBJECT pIDataObject
    , LPFORMATETC pFE, LPPOINTL pptl)
    {
    LPPERSISTSTORAGE    pIPS;
    STGMEDIUM           stm;
    FORMATETC           fe;
    HRESULT             hr;
    UINT                cf;
    POINTL              ptl;
    SIZEL               szl;

    //Can only copy embeddings.
    if (TENANTTYPE_EMBEDDEDOBJECT!=m_tType || NULL==m_pIOleObject)
        return;

    if (NULL==pptl)
        {
        SETPOINTL(ptl, 0, 0);
        pptl=&ptl;
        }

    /*
     * Create CF_EMBEDDEDOBJECT.  This is simply an IStorage with a
     * copy of the embedded object in it.  The not-so-simple part is
     * getting an IStorage to stuff it in.  For this operation we'll
     * use a temporary compound file.
     */

    stm.pUnkForRelease=NULL;
    stm.tymed=TYMED_ISTORAGE;
    hr=StgCreateDocfile(NULL, STGM_TRANSACTED | STGM_READWRITE
        | STGM_CREATE| STGM_SHARE_EXCLUSIVE | STGM_DELETEONRELEASE
        , 0, &stm.pstg);

    if (FAILED(hr))
        return;

    m_pObj->QueryInterface(IID_IPersistStorage, (PPVOID)&pIPS);

    if (NOERROR==pIPS->IsDirty())
        {
        OleSave(pIPS, stm.pstg, FALSE);
        pIPS->SaveCompleted(NULL);
        }
    else
        m_pIStorage->CopyTo(0, NULL, NULL, stm.pstg);

    pIPS->Release();

    //stm.pstg now has a copy, so stuff it away.
    cf=RegisterClipboardFormat(CF_EMBEDDEDOBJECT);
    SETDefFormatEtc(fe, cf, TYMED_ISTORAGE);

    if (SUCCEEDED(pIDataObject->SetData(&fe, &stm, TRUE)))
        *pFE=fe;
    else
        ReleaseStgMedium(&stm);

    //Create CF_OBJECTDESCRIPTOR which OLE2UI handles.
    stm.tymed=TYMED_HGLOBAL;

    /*
     * You want to make sure that if this object is iconic, that you
     * create the object descriptor with DVASPECT_ICON instead of
     * the more typical DVASPECT_CONTENT.  Also remember that
     * the pick point is in HIMETRIC.
     */
    XformSizeInPixelsToHimetric(NULL, (LPSIZEL)pptl, (LPSIZEL)&ptl);

    SETSIZEL(szl, (10*(m_rcl.right-m_rcl.left))
        , (10 * (m_rcl.bottom-m_rcl.top)));

    stm.hGlobal=OleStdGetObjectDescriptorDataFromOleObject
        (m_pIOleObject, NULL, m_fe.dwAspect, ptl, &szl);

    cf=RegisterClipboardFormat(CF_OBJECTDESCRIPTOR);
    SETDefFormatEtc(fe, cf, TYMED_HGLOBAL);

    if (FAILED(pIDataObject->SetData(&fe, &stm, TRUE)))
        ReleaseStgMedium(&stm);

    return;
    }




/*
 * CTenant::CopyLinkedObject
 *
 * Purpose:
 *  Copies an linked object to the given data object (via SetData,
 *  assuming this is a data transfer object for clipboard/drag-drop)
 *  if that's what we're holding.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT in which to store the copy.
 *  pFE             LPFORMATETC into which to copy CF_LINKSOURCE
 *                  if we put that in the data object.
 *  pptl            LPPOINTL to the pick point (NULL outside of
 *                  drag-drop);
 *
 * Return Value:
 *  None
 */

void CTenant::CopyLinkedObject(LPDATAOBJECT pIDataObject
    , LPFORMATETC pFE, LPPOINTL pptl)
    {
    STGMEDIUM           stm;
    FORMATETC           fe;
    HRESULT             hr;
    UINT                cf;
    POINTL              ptl;
    LPMONIKER           pmk;
    CLSID               clsID;
    LPTSTR              psz=NULL;
    SIZEL               szl;

    //Can only copy links to embeddings from here.
    if (TENANTTYPE_EMBEDDEDOBJECT!=m_tType || NULL==m_pIOleObject)
        return;

    //If we don't have a full moniker, no linking allowed
    if (NULL==m_pmk)
        return;

    //If the object doesn't support this, return.
    if (OLEMISC_CANTLINKINSIDE & m_grfMisc)
        return;

    if (NULL==pptl)
        {
        SETPOINTL(ptl, 0, 0);
        pptl=&ptl;
        }

    /*
     * We need to get CF_LINKSOURCE, but the server may not be
     * running, in which case we just grab the moniker and CLSID
     * for this object and call OleStdGetLinkSrcData.
     */

    m_pIOleObject->GetUserClassID(&clsID);
    hr=m_pIOleObject->GetMoniker(0, OLEWHICHMK_OBJFULL, &pmk);

    if (FAILED(hr))
        return;

    //Set these tymeds or brain-dead OleStdGetLinkSourceData fails.
    stm.pUnkForRelease=NULL;
    stm.tymed=TYMED_NULL;
    cf=RegisterClipboardFormat(CF_LINKSOURCE);
    SETDefFormatEtc(fe, cf, TYMED_ISTREAM);
    hr=OleStdGetLinkSourceData(pmk, &clsID, &fe, &stm);

    if (FAILED(hr))
        {
        pmk->Release();
        return;
        }

    //Send it to the data object for transfer
    if (SUCCEEDED(pIDataObject->SetData(&fe, &stm, TRUE)))
        *pFE=fe;
    else
        ReleaseStgMedium(&stm);

    XformSizeInPixelsToHimetric(NULL, (LPSIZEL)pptl, (LPSIZEL)&ptl);

    SETSIZEL(szl, (10*(m_rcl.right-m_rcl.left))
        , (10 * (m_rcl.bottom-m_rcl.top)));

    stm.hGlobal=OleStdGetObjectDescriptorDataFromOleObject
        (m_pIOleObject, NULL, m_fe.dwAspect, ptl, &szl);

    //Better set these properly or errors occur.
    stm.tymed=TYMED_HGLOBAL;
    stm.pUnkForRelease=NULL;

    cf=RegisterClipboardFormat(CF_LINKSRCDESCRIPTOR);
    SETDefFormatEtc(fe, cf, TYMED_HGLOBAL);

    if (FAILED(pIDataObject->SetData(&fe, &stm, TRUE)))
        ReleaseStgMedium(&stm);

    return;
    }





/*
 * CTenant::ShowObjectType
 *
 * Purpose:
 *  Tells the object to switch on or off an indication of whether
 *  it is linked or embedded.
 *
 * Parameters:
 *  fShow           BOOL indicating to show the type (TRUE) or
 *                  not (FALSE)
 *
 * Return Value:
 *  None
 */

void CTenant::ShowObjectType(BOOL fShow)
    {
    BOOL        fWasShow;
    DWORD       dwState;
    RECT        rc;
    HDC         hDC;

    fWasShow=(BOOL)(TENANTSTATE_SHOWTYPE & m_dwState);

    dwState=m_dwState & ~TENANTSTATE_SHOWTYPE;
    m_dwState=dwState | ((fShow) ? TENANTSTATE_SHOWTYPE : 0);

    /*
     * If this wasn't previously shown, just add the line,
     * otherwise repaint.
     */
    if (!fWasShow && fShow)
        {
        RECTFROMRECTL(rc, m_rcl);
        RectConvertMappings(&rc, NULL, TRUE);
        OffsetRect(&rc, -(int)m_pPG->m_xPos, -(int)m_pPG->m_yPos);

        hDC=GetDC(m_hWnd);
        OleUIShowObject(&rc, hDC
            , (TENANTTYPE_LINKEDOBJECT==m_tType));
        ReleaseDC(m_hWnd, hDC);
        }

    if (fWasShow && !fShow)
        Repaint();

    return;
    }





/*
 * CTenant::NotifyOfRename
 *
 * Purpose:
 *  Instructs the tenant that the document was saved under a
 *  different name.  In order to keep the right compound document
 *  user interface, this tenant needs to tell its object through
 *  IOleObject::SetHostNames.
 *
 * Parameters:
 *  pszFile         LPTSTR of filename.
 *  pmkFile         LPMONIKER of the new filename.  If this and
 *                  pmkPage are NULL then nothing happens with
 *                  monikers.
 *  pmkPage         LPMONIKER of the page we're in.
 *
 * Return Value:
 *  None
 */

void CTenant::NotifyOfRename(LPTSTR pszFile, LPMONIKER pmkFile
    , LPMONIKER pmkPage)
    {
    TCHAR       szObj[40];
    TCHAR       szApp[40];

    if (NULL==m_pIOleObject)
        return;

    if (TEXT('\0')==*pszFile)
        {
        LoadString(m_pPG->m_hInst, IDS_UNTITLED, szObj
            , sizeof(szObj));
        }
    else
        {
        GetFileTitle(pszFile, szObj, sizeof(szObj));

       #ifndef WIN32
        //Force filenames to uppercase in DOS versions.
        AnsiUpper(szObj);
       #endif
        }

    LoadString(m_pPG->m_hInst, IDS_CAPTION, szApp, sizeof(szApp));
    m_pIOleObject->SetHostNames(szApp, szObj);

    if (NULL!=pmkFile)
        {
        if (NULL!=m_pmkFile)
            m_pmkFile->Release();

        m_pmkFile=pmkFile;
        m_pmkFile->AddRef();

        m_pIOleObject->SetMoniker(OLEWHICHMK_CONTAINER, pmkFile);
        }

    if (NULL!=pmkFile && NULL!=pmkPage)
        {
        LPMONIKER   pmkTenant=NULL;
        LPMONIKER   pmkRel=NULL;
        HRESULT     hr;

        //Create the moniker for this tenant.
        GetStorageName(szObj);
        hr=CreateItemMoniker(TEXT("!"), szObj, &pmkTenant);

        if (SUCCEEDED(hr))
            {
            //Create the relative moniker, i.e. no pathname.
            hr=CreateGenericComposite(pmkPage, pmkTenant, &pmkRel);
            pmkTenant->Release();

            if (SUCCEEDED(hr))
                m_pIOleObject->SetMoniker(OLEWHICHMK_OBJREL, pmkRel);

            //Hold on to the relative moniker
            if (NULL!=m_pmk)
                m_pmk->Release();

            m_pmk=pmkRel;
            }
        }

    return;
    }






/*
 * CTenant::StorageGet
 *
 * Purpose:
 *  Returns the IStorage pointer maintained by this tenant,
 *  AddRef'd of course.
 *
 * Parameters:
 *  ppStg           LPSTORAGE * in which to return the pointer.
 *
 * Return Value:
 *  None
 */

void CTenant::StorageGet(LPSTORAGE *ppStg)
    {
    if (NULL==ppStg)
        return;

    *ppStg=m_pIStorage;

    if (NULL!=*ppStg)
        (*ppStg)->AddRef();

    return;
    }





/*
 * CTenant::Activate
 *
 * Purpose:
 *  Activates a verb on the object living in the tenant.  Does
 *  nothing for static objects.
 *
 * Parameters:
 *  iVerb           LONG of the verb to execute.
 *  pMSG            LPMSG to the message causing the invocation.
 *
 * Return Value:
 *  BOOL            TRUE if the object changed due to this verb
 *                  execution.
 */

BOOL CTenant::Activate(LONG iVerb, LPMSG pMSG)
    {
    RECT        rc;
    CHourglass *pHour;
    SIZEL       szl;

    //Can't activate statics.
    if (TENANTTYPE_STATIC==m_tType || NULL==m_pIOleObject)
        {
        MessageBeep(0);
        return FALSE;
        }

    rc.left=(int)m_rcl.left*10;
    rc.right=(int)m_rcl.right*10;
    rc.top=(int)-m_rcl.top*10;
    rc.bottom=(int)-m_rcl.bottom*10;

    pHour=new CHourglass;

    //Get the server running first, then do a SetExtent, then show it
    OleRun(m_pIOleObject);

    if (m_fSetExtent)
        {
        SETSIZEL(szl, rc.right-rc.left, rc.bottom-rc.top);
        m_pIOleObject->SetExtent(m_fe.dwAspect, &szl);
        m_fSetExtent=FALSE;
        }

    //CONTROLMOD
    /*
     * If we have a pending deactivation, but we're activating
     * again, clear the pending flag.
     */
    if (OLEIVERB_UIACTIVATE==iVerb
        || OLEIVERB_INPLACEACTIVATE==iVerb)
        m_fPendingDeactivate=FALSE;
    //End CONTROLMOD

    m_pIOleObject->DoVerb(iVerb, pMSG, m_pIOleClientSite, 0
        , m_hWnd, &rc);

    delete pHour;

    //If object changes, IAdviseSink::OnViewChange will see it.
    return FALSE;
    }






/*
 * CTenant::Draw
 *
 * Purpose:
 *  Draws the tenant in its rectangle on the given hDC.  We assume
 *  the DC is already set up for the mapping mode in which our
 *  rectangle is expressed, since the Page we're in tells us both
 *  the rect and the hDC.
 *
 * Parameters:
 *  hDC             HDC in which to draw.  Could be a metafile,
 *                  memory DC, screen, or printer.
 *  ptd             DVTARGETDEVICE * describing the device.
 *  hIC             HDC holding an information context (printing).
 *  xOff, yOff      int offsets for the page in lometric
 *  fNoColor        BOOL indicating if we should do B & W
 *  fPrinter        BOOL indicating if we should render for a
 *                  printer.
 *
 * Return Value:
 *  None
 */

void CTenant::Draw(HDC hDC, DVTARGETDEVICE *ptd, HDC hIC
    , int xOff, int yOff, BOOL fNoColor, BOOL fPrinter)
    {
    HRESULT         hr;
    RECT            rc;
    RECTL           rcl;
    UINT            uMM;

    /*
     * Don't bother drawing anything but shading if we're doing in-place.
     * It would just cause a lot of flicker.
     */
    if (NULL!=m_pIOleIPObject)
        return;

    //CONTROLMOD
    /*
     * If the control is marked OLEMISC_INVISIBLEATRUNTIME and we're
     * not in design mode, then we don't want to draw anything.
     * Usually we'll not draw anything anyway because of the check
     * against m_pIOleIPObject above, but we do this to make sure.
     */
    if ((OLEMISC_INVISIBLEATRUNTIME & m_grfMisc) && !m_fDesignMode)
        return;
    //End CONTROLMOD

    RECTFROMRECTL(rc, m_rcl);
    OffsetRect(&rc, -xOff, -yOff);
    RECTLFROMRECT(rcl, rc);

    //Repaint erases the rectangle to insure full object cleanup
    if (!fNoColor && !fPrinter)
        {
        COLORREF    cr;
        cr=SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
        ExtTextOut(hDC, rc.left, rc.top, ETO_OPAQUE, &rc, NULL
            , 0, NULL);
        SetBkColor(hDC, cr);
        }

    //We have to use Draw since we have a target device and IC.
    hr=m_pIViewObject2->Draw(m_fe.dwAspect, -1, NULL, ptd, hIC, hDC
        , &rcl, NULL, NULL, 0);


    /*
     * If Draw failed, then perhaps it couldn't work for the device,
     * so try good old OleDraw as a last resort.  The code will
     * generally be OLE_E_BLANK.
     */
    if (FAILED(hr))
        OleDraw(m_pObj, m_fe.dwAspect, hDC, &rc);

    if (!fPrinter)
        {
        /*
         * Draw sizing handles to show the selection state.  We
         * convert things to MM_TEXT since that's what this
         * function expects.
         */
        RectConvertMappings(&rc, NULL, TRUE);
        uMM=SetMapMode(hDC, MM_TEXT);

        if (TENANTSTATE_SELECTED & m_dwState)
            {
            OleUIDrawHandles(&rc, hDC, OLEUI_HANDLES_INSIDE
                | OLEUI_HANDLES_NOBORDER | OLEUI_HANDLES_USEINVERSE
                , CXYHANDLE, TRUE);
            }

        if (TENANTSTATE_OPEN & m_dwState)
            OleUIDrawShading(&rc, hDC, OLEUI_SHADE_FULLRECT, 0);

        //Distinguish linked and embedded objects.
        if (TENANTSTATE_SHOWTYPE & m_dwState)
            {
            OleUIShowObject(&rc, hDC
                , (TENANTTYPE_LINKEDOBJECT==m_tType));
            }

        uMM=SetMapMode(hDC, uMM);
        }

    return;
    }





/*
 * CTenant::Repaint
 * CTenant::Invalidate
 *
 * Purpose:
 *  Repaints the tenant where it lies or invalidates its area
 *  for later repainting.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CTenant::Repaint(void)
    {
    RECT        rc;
    HDC         hDC;

    if (0==m_cOpens || !m_fRepaintEnabled)
        return;

    hDC=GetDC(m_hWnd);
    SetRect(&rc, m_pPG->m_xPos, m_pPG->m_yPos, 0, 0);
    RectConvertMappings(&rc, NULL, FALSE);

    SetMapMode(hDC, MM_LOMETRIC);
    Draw(hDC, NULL, NULL, rc.left, rc.top, FALSE, FALSE);

    ReleaseDC(m_hWnd, hDC);
    return;
    }


void CTenant::Invalidate(void)
    {
    RECTL       rcl;
    RECT        rc;

    RectGet(&rcl, TRUE);
    RECTFROMRECTL(rc, rcl);

    OffsetRect(&rc, -(int)m_pPG->m_xPos, -(int)m_pPG->m_yPos);
    InvalidateRect(m_hWnd, &rc, FALSE);

    return;
    }





/*
 * CTenant::TypeGet
 *
 * Purpose:
 *  Returns the type of this tenant
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  TENANTTYPE      Type of the tenant.
 */

TENANTTYPE CTenant::TypeGet(void)
    {
    return m_tType;
    }




/*
 * CTenant::FIsSelected
 *
 * Purpose:
 *  Returns the selection state of this tenant.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if selected, FALSE otherwise.
 */

BOOL CTenant::FIsSelected(void)
    {
    return (BOOL)(m_dwState & TENANTSTATE_SELECTED);
    }



/*
 * CTenant::FConvertToStatic
 *
 * Purpose:
 *  Changes the object that lives in this tenant to a static one.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CTenant::FConvertToStatic(void)
    {
    /*
     * If you SetSourceMoniker in IOleLink to NULL, then the link is
     * gone as far as OLE is concerned.  You only need to make sure
     * the user doesn't have access to other functionality for this
     * object, which we insure by changing our internal type.  We
     * set this on loading if GetSourceMoniker returns NULL.
     */
    m_tType=TENANTTYPE_STATIC;
    return TRUE;
    }




/*
 * CTenant::ObjectClassFormatAndIcon
 *
 * Purpose:
 *  Helper function for CPage::FConvertObject to retrieve necessary
 *  information about the object.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store the CLSID.
 *  pwFormat        LPWORD in which to store the clipboard format
 *                  used.
 *  ppszType        LPSTR * in which to return a pointer to a
 *                  type string.
 *  phMetaIcon      HGLOBAL * in which to return the metafile
 *                  icon currently in use.
 *
 * Return Value:
 *  None
 */

void CTenant::ObjectClassFormatAndIcon(LPCLSID pClsID
    , LPWORD pwFormat, LPTSTR *ppszType, HGLOBAL * phMetaIcon)
    {
    HRESULT         hr;
    TCHAR           szType[128];
    LPDATAOBJECT    pIDataObject;
    FORMATETC       fe;
    STGMEDIUM       stm;

    if (TENANTTYPE_EMBEDDEDOBJECT!=m_tType || NULL==m_pIOleObject)
        return;

    if (NULL==pClsID || NULL==pwFormat || NULL==ppszType
        || NULL==phMetaIcon)
        return;


    /*
     * For embedded objects get the real CLSID of the object and
     * its format string.  If this fails then we can try to ask
     * the object, or we can look in the regDB.
     */

    hr=ReadClassStg(m_pIStorage, pClsID);

    if (FAILED(hr))
        {
        hr=m_pIOleObject->GetUserClassID(pClsID);

        if (FAILED(hr))
            *pClsID=CLSID_NULL;
        }


    hr=ReadFmtUserTypeStg(m_pIStorage, pwFormat, ppszType);

    if (FAILED(hr))
        {
        *pwFormat=0;
        *ppszType=NULL;

        if (OleStdGetUserTypeOfClass(*pClsID, szType, sizeof(szType)
            , NULL))
            *ppszType=OleStdCopyString(szType, NULL);
        }

    //Get the icon for this thing, if we're iconic.
    *phMetaIcon=NULL;

    if (DVASPECT_ICON!=m_fe.dwAspect)
        return;

    hr=m_pObj->QueryInterface(IID_IDataObject
        , (PPVOID)&pIDataObject);

    if (SUCCEEDED(hr))
        {
        SETDefFormatEtc(fe, DVASPECT_ICON, TYMED_MFPICT);
        hr=pIDataObject->GetData(&fe, &stm);
        pIDataObject->Release();

        if (SUCCEEDED(hr))
            *phMetaIcon=stm.hGlobal;
        }

    return;
    }




/*
 * CTenant::FSwitchOrUpdateAspect
 *
 * Purpose:
 *  Switches between DVASPECT_CONTENT and DVASPECT_ICON
 *
 * Parameters:
 *  hMetaIcon       HGLOBAL to the new icon if we're changing the
 *                  icon or switching to DVASPECT_ICON.  NULL to
 *                  change back to content.
 *  fPreserve       BOOL indicating if we're to preserve the old
 *                  aspect after changing.
 *
 * Return Value:
 *  BOOL            TRUE if anything changed, FALSE otherwise.
 */

BOOL CTenant::FSwitchOrUpdateAspect(HGLOBAL hMetaIcon
    , BOOL fPreserve)
    {
    HRESULT     hr;
    DWORD       dwAspect;
    BOOL        fUpdate=FALSE;

    //Nothing to do if we're content already and there's no icon.
    if (NULL==hMetaIcon && DVASPECT_CONTENT==m_fe.dwAspect)
        return FALSE;

    //If we're iconic already, just cache the new icon
    if (NULL!=hMetaIcon && DVASPECT_ICON==m_fe.dwAspect)
        hr=OleStdSetIconInCache(m_pIOleObject, hMetaIcon);
    else
        {
        //Otherwise, switch between iconic and content.
        dwAspect=(NULL==hMetaIcon) ? DVASPECT_CONTENT : DVASPECT_ICON;

        /*
         * Switch between aspects, where dwAspect has the new one
         * and m_fe.dwAspect will be changed in the process.
         */
        hr=OleStdSwitchDisplayAspect(m_pIOleObject, &m_fe.dwAspect
            , dwAspect, hMetaIcon, !fPreserve, TRUE, m_pIAdviseSink
            , &fUpdate);

        if (SUCCEEDED(hr))
            {
            //Update MiscStatus for the new aspect
            m_pIOleObject->GetMiscStatus(m_fe.dwAspect, &m_grfMisc);

            if (fUpdate)
                {
                m_pIOleObject->Update();    //This repaints.
                return TRUE;
                }
            }
        }

    //If we switched, update our extents.
    if (SUCCEEDED(hr))
        {
        SIZEL       szl;

        m_pIOleObject->GetExtent(m_fe.dwAspect, &szl);

        if (0 > szl.cy)
            szl.cy=-szl.cy;

        //Convert HIMETRIC absolute units to our LOMETRIC mapping
        if (0!=szl.cx && 0!=szl.cy)
            SETSIZEL(szl, szl.cx/10, -szl.cy/10);

        Invalidate();                   //Remove old aspect
        SizeSet(&szl, FALSE, FALSE);    //Change size
        Repaint();                      //Paint the new one
        }

    return SUCCEEDED(hr);
    }





/*
 * CTenant::EnableRepaint
 *
 * Purpose:
 *  Toggles whether the Repaint function does anything.  This
 *  is used during conversion/emulation of an object to disable
 *  repaints until the new object can be given the proper extents.
 *
 * Parameters:
 *  fEnable         TRUE to enable repaints, FALSE to disable.
 *
 * Return Value:
 *  None
 */

void CTenant::EnableRepaint(BOOL fEnable)
    {
    m_fRepaintEnabled=fEnable;
    return;
    }





/*
 * CTenant::ObjectGet
 *
 * Purpose:
 *  Retrieves the LPUNKNOWN of the object in use by this tenant
 *
 * Parameters:
 *  ppUnk           LPUNKNOWN * in which to return the object
 *                  pointer.
 *
 * Return Value:
 *  None
 */

void CTenant::ObjectGet(LPUNKNOWN *ppUnk)
    {
    if (NULL!=ppUnk)
        {
        *ppUnk=m_pObj;
        m_pObj->AddRef();
        }

    return;
    }



/*
 * CTenant::ReleaseInterface
 *
 * Purpose:
 *  Calls IUnknown::Release and sets the pointer to NULL.
 *
 * Parameters:
 *  ppUnk           LPUNKNOWN * in which to return the object
 *                  pointer.
 *
 * Return Value:
 *  None
 */

void CTenant::ReleaseInterface(LPUNKNOWN *ppUnk)
    {
    if (NULL!=ppUnk)
        {
        if (NULL!=*ppUnk)
            {
            (*ppUnk)->Release();
            *ppUnk=NULL;
            }
        }

    return;
    }




/*
 * CTenant::FormatEtcGet
 *
 * Purpose:
 *  Retrieves the FORMATETC in use by this tenant
 *
 * Parameters:
 *  pFE             LPFORMATETC in which to store the information.
 *  fPresentation   BOOL indicating if we want the real format or
 *                  that of the presentation.
 *
 * Return Value:
 *  None
 */

void CTenant::FormatEtcGet(LPFORMATETC pFE, BOOL fPresentation)
    {
    if (NULL!=pFE)
        {
        *pFE=m_fe;

        //If there is no format, use metafile (for embedded objects)
        if (fPresentation || 0==pFE->cfFormat)
            {
            //Don't mess with dwAspect; might be icon or content.
            pFE->cfFormat=CF_METAFILEPICT;
            pFE->tymed=TYMED_MFPICT;
            }
        }

    return;
    }





/*
 * CTenant::SizeGet
 * CTenant::SizeSet
 * CTenant::RectGet
 * CTenant::RectSet
 *
 * Purpose:
 *  Returns or sets the size/position of the object contained here.
 *
 * Parameters:
 *  pszl/prcl       LPSIZEL (Size) or LPRECTL (Rect) with the
 *                  extents of interest.  In Get situations,
 *                  this will receive the extents; in Set it
 *                  contains the extents.
 *  fDevice         BOOL indicating that pszl/prcl is expressed
 *                  in device units.  Otherwise it's LOMETRIC.
 *  fInformObj      (Set Only) BOOL indicating if we need to inform
 *                  the object all.
 *
 * Return Value:
 *  None
 */

void CTenant::SizeGet(LPSIZEL pszl, BOOL fDevice)
    {
    if (!fDevice)
        {
        pszl->cx=m_rcl.right-m_rcl.left;
        pszl->cy=m_rcl.bottom-m_rcl.top;
        }
    else
        {
        RECT        rc;

        SetRect(&rc, (int)(m_rcl.right-m_rcl.left)
            , (int)(m_rcl.bottom-m_rcl.top), 0, 0);

        RectConvertMappings(&rc, NULL, TRUE);

        pszl->cx=(long)rc.left;
        pszl->cy=(long)rc.top;
        }

    return;
    }


void CTenant::SizeSet(LPSIZEL pszl, BOOL fDevice, BOOL fInformObj)
    {
    SIZEL           szl;

    if (!fDevice)
        {
        szl=*pszl;
        m_rcl.right =pszl->cx+m_rcl.left;
        m_rcl.bottom=pszl->cy+m_rcl.top;
        }
    else
        {
        RECT        rc;

        SetRect(&rc, (int)pszl->cx, (int)pszl->cy, 0, 0);
        RectConvertMappings(&rc, NULL, FALSE);

        m_rcl.right =(long)rc.left+m_rcl.left;
        m_rcl.bottom=(long)rc.top+m_rcl.top;

        SETSIZEL(szl, (long)rc.left, (long)rc.top);
        }


    //Tell OLE that this object was resized.
    if (NULL!=m_pIOleObject && fInformObj)
        {
        HRESULT     hr;
        BOOL        fRun=FALSE;

        //Convert our LOMETRIC into HIMETRIC by *=10
        szl.cx*=10;
        szl.cy*=-10;    //Our size is stored negative.

        /*
         * If the MiscStatus bit of OLEMISC_RECOMPOSEONRESIZE
         * is set, then we need to run the object before calling
         * SetExtent to make sure it has a real chance to
         * re-render the object.  We have to update and close
         * the object as well after this happens.
         */

        if (OLEMISC_RECOMPOSEONRESIZE & m_grfMisc)
            {
            if (!OleIsRunning(m_pIOleObject))
                {
                OleRun(m_pIOleObject);
                fRun=TRUE;
                }
            }

        hr=m_pIOleObject->SetExtent(m_fe.dwAspect, &szl);

        /*
         * If the object is not running and it does not have
         * RECOMPOSEONRESIZE, then SetExtent fails.  Make
         * sure that we call SetExtent again (by just calling
         * SizeSet here again) when we next run the object.
         */
        if (SUCCEEDED(hr))
            {
            m_fSetExtent=FALSE;

            if (fRun)
                {
                m_pIOleObject->Update();
                m_pIOleObject->Close(OLECLOSE_SAVEIFDIRTY);
                }
            }
        else
            {
            if (OLE_E_NOTRUNNING==GetScode(hr))
                m_fSetExtent=TRUE;
            }
        }

    return;
    }


void CTenant::RectGet(LPRECTL prcl, BOOL fDevice)
    {
    if (!fDevice)
        *prcl=m_rcl;
    else
        {
        RECT        rc;

        RECTFROMRECTL(rc, m_rcl);
        RectConvertMappings(&rc, NULL, TRUE);
        RECTLFROMRECT(*prcl, rc);
        }

    return;
    }


void CTenant::RectSet(LPRECTL prcl, BOOL fDevice, BOOL fInformObj)
    {
    SIZEL   szl;
    LONG    cx, cy;

    /*
     * Prevent reentrant calls that may come from calling
     * UpdateInPlaceObjectRects here and elsewhere.
     */
    if (m_fInRectSet)
        return;

    m_fInRectSet=TRUE;

    cx=m_rcl.right-m_rcl.left;
    cy=m_rcl.bottom-m_rcl.top;

    if (!fDevice)
        m_rcl=*prcl;
    else
        {
        RECT        rc;

        RECTFROMRECTL(rc, *prcl);
        RectConvertMappings(&rc, NULL, FALSE);
        RECTLFROMRECT(m_rcl, rc);
        }

    /*
     * Tell ourselves that the size changed, if it did.  SizeSet
     * will call IOleObject::SetExtent for us.
     */
    if ((m_rcl.right-m_rcl.left)!=cx || (m_rcl.bottom-m_rcl.top)!=cy)
        {
        SETSIZEL(szl, m_rcl.right-m_rcl.left, m_rcl.bottom-m_rcl.top);
        SizeSet(&szl, FALSE, fInformObj);
        }

    //Tell an in-place active object it moved too
    UpdateInPlaceObjectRects(NULL, TRUE);
    m_fInRectSet=FALSE;
    return;
    }







/*
 * CTenant::CreateStatic
 * (Protected)
 *
 * Purpose:
 *  Creates a new static bitmap or metafile object for this tenant
 *  using a freeloading method allowing us to specify exactly which
 *  type of data we want to paste since OleCreateStaticFromData
 *  doesn't.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT from which to paste.
 *  pFE             LPFORMATETC describing the format to paste.
 *  ppObj           LPUNKNOWN * into which we store the
 *                  object pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, error code otherwise.
 */

HRESULT CTenant::CreateStatic(LPDATAOBJECT pIDataObject
    , LPFORMATETC pFE, LPUNKNOWN *ppObj)
    {
    HRESULT             hr;
    STGMEDIUM           stm;
    LPUNKNOWN           pIUnknown;
    LPOLECACHE          pIOleCache;
    LPPERSISTSTORAGE    pIPersistStorage;
    CLSID               clsID;

    *ppObj=NULL;

    //Try to get the data desired as specified in pFE->cfFormat
    hr=pIDataObject->GetData(pFE, &stm);

    if (FAILED(hr))
        return hr;

    //Create the object to handle this data.
    if (CF_METAFILEPICT==pFE->cfFormat)
        clsID=CLSID_Picture_Metafile;
    else
        clsID=CLSID_Picture_Dib;

    hr=CreateDataCache(NULL, clsID, IID_IUnknown
        , (PPVOID)&pIUnknown);

    if (FAILED(hr))
        {
        ReleaseStgMedium(&stm);
        return hr;
        }

    m_clsID=clsID;

    //Stuff the data into the object
    pIUnknown->QueryInterface(IID_IPersistStorage
        , (PPVOID)&pIPersistStorage);
    pIPersistStorage->InitNew(m_pIStorage);

    //Now that we have the cache object, shove the data into it.
    pIUnknown->QueryInterface(IID_IOleCache, (PPVOID)&pIOleCache);
    pIOleCache->Cache(pFE, ADVF_PRIMEFIRST, NULL);

    hr=pIOleCache->SetData(pFE, &stm, TRUE);
    pIOleCache->Release();

    //Insure there is a persistent copy on the disk
    WriteClassStg(m_pIStorage, m_clsID);
    pIPersistStorage->Save(m_pIStorage, TRUE);
    pIPersistStorage->SaveCompleted(NULL);
    pIPersistStorage->Release();

    //The cache owns this now.
    ReleaseStgMedium(&stm);

    if (FAILED(hr))
        pIUnknown->Release();
    else
        *ppObj=pIUnknown;

    return hr;
    }




/*
 * CTenant::DeactivateInPlaceObject
 *
 * Purpose:
 *  Deactivates an in-place object if there is one in this tenant.
 *
 * Parameters:
 *  fFull           BOOL indicating full deactivation of UI
 *                  deactivate only.
 *
 * Return Value:
 *  None
 */

void CTenant::DeactivateInPlaceObject(BOOL fFull)
    {
    if (NULL!=m_pIOleIPObject)
        {
        /*
         * Inside-out objects stay in-place active but not UI active
         * unless we're fully deactivating.
         */
        if ((OLEMISC_INSIDEOUT & m_grfMisc) && !fFull)
            m_pIOleIPObject->UIDeactivate();
        else
            {
            //CONTROLMOD
            /*
             * Only deactivate when there's no locks.  If there
             * is a lock, then remember that we need to deactivate
             * when all the locks go away.
             */
            if (0==m_cLockInPlace)
                m_pIOleIPObject->InPlaceDeactivate();
            else
                m_fPendingDeactivate=TRUE;
            //End CONTROLMOD
            }
        }

    return;
    }



/*
 * CTenant::UpdateInPlaceObjectRects
 *
 * Purpose:
 *  Generates a call to IOleInPlaceObject::SetObjectRects to allow
 *  it to show it's shading and its object adornments properly.
 *  This function deals in HIMETRIC units.
 *
 * Parameters:
 *  prcPos          LPCRECT to the size the object wants.  Ignored
 *                  if NULL in which case we use the size of the
 *                  tenant.  This rect is in client coordinates of
 *                  the pages window.
 *  fUseTenantRect  BOOL indicating if we need to use the tenant
 *                  rectangle offset for scrolling regardless.
 *
 * Return Value:
 *  None
 */

void CTenant::UpdateInPlaceObjectRects(LPCRECT prcPos
    , BOOL fUseTenantRect)
    {
    RECTL       rcl;
    RECT        rc;
    RECT        rcClip;
    BOOL        fResizeTenant=TRUE;

    /*
     * Note that if the object here is inside-out we'll always
     * have this pointer.
     */
    if (NULL!=m_pIOleIPObject)
        {
        /*
         * This uses the last position rectangle from
         * IOleInPlaceSite::OnPosRectChange if it's been
         * initialized
         */
        if (NULL==prcPos && -1!=m_rcPos.left && !fUseTenantRect)
            prcPos=&m_rcPos;

        //This code is normally called from OnPosRectChange direct.
        if (NULL!=prcPos && !fUseTenantRect)
            {
            rc=*prcPos;

            //Calculate the boundaries of the full page
            m_pPG->CalcBoundingRect(&rcClip, FALSE);

            //Make sure we limit object to page boundaries.
            IntersectRect(&rc, &rc, &rcClip);
            }
        else
            {
            /*
             * We have no rectangle of the object on which to
             * base the position, so just use the tenant rectangle.
             * This code is also used when scrolling objects.
             */
            RectGet(&rcl, TRUE);
            RECTFROMRECTL(rc, rcl);

            //Account for scrolling
            OffsetRect(&rc, -(int)m_pPG->m_xPos, -(int)m_pPG->m_yPos);
            fResizeTenant=FALSE;
            }


        //We don't clip special anywhere in our window.
        SetRect(&rcClip, 0, 0, 32767, 32767);

        /*
         * NOTE:  The rectangles to SetObjectRects is in client
         * coordinates of the pages window.
         */
        if (NULL!=m_pIOleIPObject)
            m_pIOleIPObject->SetObjectRects(&rc, &rcClip);

        if (fResizeTenant)
            {
            //Need to tell the tenant to change position too
            RECTLFROMRECT(rcl, rc);
            RectSet(&rcl, TRUE, FALSE);
            }
        }

    return;
    }


/*
 * CTenant::ObjectWindow
 *
 * Purpose:
 *  Returns the window handle of the in-place object.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HWND            Handle of the object window.
 */

HWND CTenant::ObjectWindow(void)
    {
    HWND    hWnd=NULL;

    if (NULL!=m_pIOleIPObject)
        m_pIOleIPObject->GetWindow(&hWnd);

    return hWnd;
    }



//CONTROLMOD
/*
 * CTenant::ToggleDesignMode
 *
 * Purpose:
 *  Switches between design mode and run mode for this tenant.
 *  Going to design mode deactivates the tenant.  Otherwise it's
 *  activated in-place.  If this is the selected tenant, then
 *  it is also UI activated
 *
 * Parameters:
 *  fDesign         BOOL indicating to deactivate or activate.
 *
 * Return Value:
 *  None
 */

void CTenant::ToggleDesignMode(BOOL fDesign)
    {
    BOOL    fChange=!(m_fDesignMode & fDesign);

    if (fDesign==m_fDesignMode)
        return;

    m_fDesignMode=fDesign;

    /*
     * Inform the control of ambient property changed.  A change
     * in design mode changes UserMode, ShowGrabHandles, and
     * ShowHatching (see AMBIENTS.CPP)
     */

    AmbientChange(DISPID_AMBIENT_USERMODE);
    AmbientChange(DISPID_AMBIENT_SHOWGRABHANDLES);
    AmbientChange(DISPID_AMBIENT_SHOWHATCHING);

    if (m_fDesignMode)
        {
        //This even deactivates inside-out objects
        DeactivateInPlaceObject(TRUE);
        Invalidate();
        }
    else
        {
        //First hide whatever windows might be open
        if (TENANTSTATE_OPEN & m_dwState)
            Activate(OLEIVERB_HIDE, NULL);

        //Activate all tenants, UI activate the selected one
        Activate(OLEIVERB_INPLACEACTIVATE, NULL);

        if (TENANTSTATE_SELECTED & m_dwState)
            Activate(OLEIVERB_UIACTIVATE, NULL);
        }

    return;
    }




/*
 * CTenant::FControlInitialize
 *
 * Purpose:
 *  Initializes the control if that's the type of object we have
 *  in the site.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if initialization worked, FALSE otherwise.
 */

BOOL CTenant::FControlInitialize(void)
    {
    HRESULT         hr;
    BOOL            fEvents;

    if (NULL==m_pObj)
        return FALSE;

    hr=m_pObj->QueryInterface(IID_IOleControl
        , (PPVOID)&m_pIOleControl);

    //Failure means not a control.
    if (FAILED(hr))
        return FALSE;

    /*
     * Call IOleControl::GetControlInfo to retrieve the keyboard
     * information for this control.  We have to reload this
     * information in IOleControlSite::OnControlInfoChanged.
     */
    m_fHaveControlInfo=SUCCEEDED(m_pIOleControl
        ->GetControlInfo(&m_ctrlInfo));


    /*
     * Get the properties and methods IDispatch (NOTE:  we don't
     * ever call this in this container, but this is where you'd
     * probably ask for it.  Failure is tolerable--it just means
     * we could not set properties.
     */

    m_pObj->QueryInterface(IID_IDispatch
        , (PPVOID)&m_pIDispatchControl);


    /*
     * Connect our events IDispatch to the object.  The function
     * EventIIDFromObject (see connect.cpp) retrieves the events
     * IID for us.  If InterfaceConnect (also in connect.cpp) fails,
     * then we'll just do without events.  If we do connect to the
     * events, then we need to initialize event information.
     */
    ObjectEventsIID(m_pObj, &m_iidEvents);

    m_pIDispatchEvents=new CImpIDispatchEvents(this, this);
    fEvents=InterfaceConnect(m_pObj, m_iidEvents, m_pIDispatchEvents
        , &m_dwConnEvents);


    /*
     * If we successfully connected our IDispatch to the control
     * for events, then get all the pertinent event information
     * we need for allowing the user to assign code/actions to
     * each event.  In the case of this container, all we need
     * are the names of the events so we can show them in a listbox.
     * Real containers, like Visual Basic or a database, for example,
     * would also want the types and names of event parameters
     * and so forth.
     *
     * So in any case, we'll need an ITypeInfo interface for the
     * event set of the control.  The function ObjectEventsTypeInfo
     * (connect.cpp) gets the right ITypeInfo for us.
     */

    if (fEvents)
        {
        LPTYPEINFO      pITypeInfo;
        LPSTREAM        pIStream;

        //Get the ITypeInfo specifically for events (connect.cpp)
        fEvents=ObjectTypeInfoEvents(m_pObj, &pITypeInfo);

        if (fEvents)
            {
            fEvents=FALSE;

            //CEventMap implemented in events.cpp
            m_pEventMap=new CEventMap(pITypeInfo);

            if (NULL!=m_pEventMap)
                {
                fEvents=m_pEventMap->Init();

                //Check if there's mappings already and load them.
                if (fEvents)
                    {
                    if (SUCCEEDED(m_pIStorage->OpenStream
                        (SZEVENTSSTREAM, NULL, STGM_DIRECT
                        | STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                        , 0, &pIStream)))
                        {
                        m_pEventMap->Deserialize(pIStream);
                        pIStream->Release();
                        }
                    }
                }

            pITypeInfo->Release();
            }

        if (!fEvents)
            {
            /*
             * Event mapping failed, disconnect and clean up--we just
             * won't handle any events for this control.  We need to
             * clean up and NULL m_pIDispatchEvents which is our
             * flag that we can do events.
             */
            InterfaceDisconnect(m_pObj, m_iidEvents
                , &m_dwConnEvents);
            ReleaseInterface((IUnknown **)&m_pIDispatchEvents);
            delete m_pEventMap;
            m_pEventMap=NULL;
            }
        }


    /*
     * Connect our property notification sink to the object.
     * If "new" fails then InterfaceConnect will fail and we'll
     * just do without notifications.
     */
    m_pIPropNoteSink=new CImpIPropertyNotifySink(this, this);
    InterfaceConnect(m_pObj, IID_IPropertyNotifySink
        , m_pIPropNoteSink, &m_dwConnProp);


    return TRUE;
    }



/*
 * CTenant::EventMap
 *
 * Purpose:
 *  Retrieve the current event map from the tenant.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCEventMap      Current map for the tenant.
 */

PCEventMap CTenant::EventMap(void)
    {
    return m_pEventMap;
    }




/*
 * CTenant::HasControl
 * CTenant::HasEvents
 *
 * Purpose:
 *  Asks the tenant if it has a control in it, or if the control it
 *  has also has events (some controls might not)
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the object is a control (or has events),
 *                  FALSE otherwise.
 */

BOOL CTenant::HasControl(void)
    {
    return (NULL!=m_pIOleControl);
    }


BOOL CTenant::HasEvents(void)
    {
    /*
     * m_pIDispatchEvents only set in FControlInitialize
     * if there are events.
     */
    return (NULL!=m_pIDispatchEvents);
    }



/*
 * CTenant::AmbientChange
 *
 * Purpose:
 *  Notifes a control that an ambient property has changed in
 *  the control site.
 *
 * Parameters:
 *  dispID          DISPID of the property that changed.
 *
 * Return Value:
 *  None
 */

void CTenant::AmbientChange(DISPID dispID)
    {
    if (NULL!=m_pIOleControl)
        m_pIOleControl->OnAmbientPropertyChange(dispID);

    return;
    }

//End CONTROLMOD
