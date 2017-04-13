/*
 * PAGE.CPP
 * Patron Chapter 24
 *
 * Implementation of parts of the CPage class; those member
 * functions dealing with mouse events are in PAGEMOUS.CPP.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CPage::CPage
 * CPage::~CPage
 *
 * Constructor Parameters:
 *  dwID            DWORD identifier for this page.
 *  hWnd            HWND of the pages window (for repaints, etc).
 *  pPG             PCPages to the Pages window.
 */

CPage::CPage(DWORD dwID, HWND hWnd, PCPages pPG)
    {
    m_dwID     =dwID;
    m_pIStorage=NULL;

    m_cOpens=0;
    m_hWnd=hWnd;
    m_pPG=pPG;

    m_dwIDNext      =0;
    m_cTenants      =0;
    m_hWndTenantList=NULL;
    m_iTenantCur    =NOVALUE;   //Tenants are zero indexed.
    m_pTenantCur    =NULL;

    m_uHTCode=HTNOWHERE;
    m_uSizingFlags=0;
    m_fTracking=FALSE;
    m_hDC=NULL;

    m_fDragPending=FALSE;
    m_fSizePending=FALSE;
    m_fTimer=FALSE;

    //Get WIN.INI distance and delay values, with OLE defaults.
    m_cxyDist=GetProfileInt(TEXT("windows"), TEXT("DragMinDist")
        , DD_DEFDRAGMINDIST);
    m_cDelay=GetProfileInt(TEXT("windows"), TEXT("DragDelay")
        , DD_DEFDRAGDELAY);

    m_fReopen=FALSE;
    m_pmkFile=m_pPG->m_pmkFile;

    if (NULL!=m_pmkFile)
        m_pmkFile->AddRef();

    m_cRef=0L;
    m_dwRegROTWild=0L;
    m_pImpIOleItemContainer=NULL;

    m_fFirstUIActivate=TRUE;  //We haven't UIActivated anyone yet
    return;
    }


CPage::~CPage(void)
    {
    INOLE_RevokeAsRunning(&m_dwRegROTWild);

    if (m_fTimer)
        KillTimer(m_hWnd, IDTIMER_DEBOUNCE);

    m_hWnd=NULL;
    Close(FALSE);
    return;
    }



/*
 * CPage::QueryInterface
 * CPage::AddRef
 * CPage::Release
 *
 * Purpose:
 *  IUnknown members for CPage object.
 */

STDMETHODIMP CPage::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IOleItemContainer==riid || IID_IOleContainer==riid
        || IID_IParseDisplayName==riid)
        *ppv=m_pImpIOleItemContainer;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CPage::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CPage::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }





/*
 * CPage::GetID
 *
 * Return Value:
 *  DWORD           dwID field in this page.
 */

DWORD CPage::GetID(void)
    {
    return m_dwID;
    }





/*
 * CPage::Open
 *
 * Purpose:
 *  Retrieves the IStorage associated with this page.  The IStorage
 *  is owned by the page and thus the page always holds a reference
 *  count.  The caller should call Close or delete this page to
 *  match this open.
 *
 *  This function may be called multiple times resulting in
 *  additional reference counts on the storage each of which must be
 *  matched with a call to Close.  The last Close can be done
 *  through delete.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE in which this page lives.
 *
 * Return Value:
 *  BOOL            TRUE if opening succeeds, FALSE otherwise.
 */

BOOL CPage::Open(LPSTORAGE pIStorage)
    {
    HRESULT                 hr=NOERROR;
    LPSTREAM                pIStream;
    DWORD                   dwMode;
    OLECHAR                 szTemp[32];
    TCHAR                   szCap[32];
    BOOL                    fNew;
    BOOL                    fCreated=FALSE;
    TENANTLIST              tl;
    PTENANTINFO             pti;
    ULONG                   cb;
    LPMALLOC                pIMalloc;
    UINT                    i;
    PCTenant                pTenant;
    UINT                    cLinks;
    LPOLELINK               pIOleLink;
    LPUNKNOWN               pIUnknown;
    UINT                    uRet;
    OLEUIEDITLINKS          el;
    PCIOleUILinkContainer   pIUILinks;
    HWND                    hWndDoc;

    fNew=(NULL==m_pIStorage);

    if (!fNew)
        {
        m_cOpens++;
        m_pIStorage->AddRef();
        return TRUE;
        }

    if (NULL==pIStorage)
        return FALSE;

    /*
     * Attempt to open the storage under this ID.  If none,
     * create one.  In either case, the IStorage is either
     * saved in pPage or released.
     */

    GetStorageName(szTemp);
    dwMode=STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;

    hr=pIStorage->OpenStorage(szTemp, NULL, dwMode, NULL, 0
        , &m_pIStorage);

    if (FAILED(hr))
        {
        hr=pIStorage->CreateStorage(szTemp, dwMode, 0, 0
            , &m_pIStorage);
        fCreated=TRUE;
        }

    if (FAILED(hr))
        return FALSE;

    m_cOpens++;

    if (NULL==m_hWndTenantList)
        {
        /*
         * The first time we open this page, create the hidden
         * listbox we'll use to track tenants.  We give it the
         * owner-draw style so we can just store pointers in it.
         */
        m_hWndTenantList=CreateWindow(TEXT("listbox")
            , TEXT("Tenant List"), WS_POPUP | LBS_OWNERDRAWFIXED
            , 0, 0, 100, 100, HWND_DESKTOP, NULL
            , m_pPG->m_hInst, NULL);

        if (NULL==m_hWndTenantList)
            return FALSE;
        }

    m_pImpIOleItemContainer=new CImpIOleItemContainer(this, this
        , FALSE);

    if (NULL==m_pImpIOleItemContainer)
        return FALSE;

    //If this is brand-new, we're done.
    if (fCreated)
        return TRUE;


    /*
     * Now open the stream we saved in Close and load all the
     * tenants listed in there.  If there are none, then we don't
     * have to load squat.
     */

    hr=m_pIStorage->OpenStream(SZSTREAMTENANTLIST, NULL, STGM_DIRECT
        | STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return FALSE;

    if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        {
        pIStream->Read(&tl, sizeof(tl), NULL);
        m_cTenants=tl.cTenants;
        m_dwIDNext=tl.dwIDNext;
        m_iTenantCur=0;

        cb=tl.cTenants*sizeof(TENANTINFO);

        if (0!=cb)
            {
            pti=(PTENANTINFO)pIMalloc->Alloc(cb);

            if (NULL!=pti)
                {
                pIStream->Read(pti, cb, NULL);

                for (i=0; i < m_cTenants; i++)
                    {
                    if (TenantAdd(NOVALUE, (pti+i)->dwID, &pTenant))
                        {
                        pTenant->Load(m_pIStorage, (pti+i));

                        //Make sure it knows about the show state.
                        pTenant->ShowObjectType(m_pPG->m_fShowTypes);
                        }
                    }

                pIMalloc->Free(pti);
                }
            }

        pIMalloc->Release();
        }

    pIStream->Release();

    //Get and select the first tenant
    if (TenantGet(0, &m_pTenantCur, FALSE))
        m_pTenantCur->Select(TRUE, TRUE);

    //If we just saved and closed, don't bother with updating links
    if (m_fReopen)
        {
        m_fReopen=FALSE;
        return TRUE;
        }

    /*
     * Update all the links in this page, showing the progress
     * indicator as it's happening.  We use the same
     * IOlUILinkContainer implementation as we do for the links
     * dialog, passing it to OleUIUpdateLinks which does everything
     * for us.
     *
     * We might also optimize this to not do anything if there are
     * no automatic links, but it's not a big concern.
     */

    //First, count the number of automatic links.
    cLinks=0;

    for (i=0; i < m_cTenants; i++)
        {
        if (TenantGet(i, &pTenant, FALSE))
            {
            DWORD       dw;

            pTenant->ObjectGet(&pIUnknown);
            hr=pIUnknown->QueryInterface(IID_IOleLink
                , (PPVOID)&pIOleLink);
            pIUnknown->Release();

            if (FAILED(hr))
                continue;

            pIOleLink->GetUpdateOptions(&dw);
            pIOleLink->Release();

            if (OLEUPDATE_ALWAYS==dw)
                cLinks++;
            }
        }

    //If we have any automatic links, invoke the update dialog.
    if (0==cLinks)
        return TRUE;

    //Create an IOleUILinkContainer instantiation.
    if (!m_pPG->GetUILinkContainer(&pIUILinks))
        return TRUE;    //Guess we can't update, oh well.

    hWndDoc=GetParent(m_hWnd);
    LoadString(m_pPG->m_hInst, IDS_CAPTION, szCap, sizeof(szCap));

    if (!OleUIUpdateLinks(pIUILinks, hWndDoc, szCap, cLinks))
        {
        /*
         * If updating failed, ask to show the links dialog.  NOTE:
         * OleUIPromptUser has a variable wsprintf argument list
         * after the hWnd parameter!  Use appropriate typecasting!
         */
        uRet=OleUIPromptUser(IDD_CANNOTUPDATELINK, hWndDoc, szCap);

       #ifdef IDC_PU_LINKS
        if (IDC_PU_LINKS==uRet)
       #else
        if (ID_PU_LINKS==uRet)
       #endif
            {
            //Throw up the links dialog.
            memset(&el, 0, sizeof(el));
            el.cbStruct=sizeof(el);
            el.hWndOwner=hWndDoc;
            el.lpOleUILinkContainer=pIUILinks;
            OleUIEditLinks(&el);
            }
        }

    m_pPG->m_fDirty=pIUILinks->m_fDirty;
    pIUILinks->Release();
    return TRUE;
    }





/*
 * CPage::Close
 *
 * Purpose:
 *  Possibly commits the storage, then releases it reversing the
 *  reference count from Open.
 *
 * Parameters:
 *  fCommit         BOOL indicating if we're to commit.
 *
 * Return Value:
 *  None
 */

void CPage::Close(BOOL fCommit)
    {
    if (NULL==m_pIStorage)
        return;

    if (fCommit)
        Update();

    m_pIStorage->Release();

    //If this was the last close, make all tenants loaded->passive
    if (0==--m_cOpens)
        {
        UINT        i;
        PCTenant    pTenant;

        m_pIStorage=NULL;

        for (i=0; i < m_cTenants; i++)
            {
            if (TenantGet(i, &pTenant, FALSE))
                {
                if (NULL!=m_hWnd)
                    {
                    //Open may select again, so this repaints.
                    pTenant->Select(FALSE, TRUE);
                    }

                pTenant->Close(FALSE);
                pTenant->Release();
                }
            }

        DestroyWindow(m_hWndTenantList);
        m_hWndTenantList=NULL;
        m_fReopen=TRUE;

        if (NULL!=m_pmkFile)
            m_pmkFile->Release();

        m_pmkFile=NULL;

        DeleteInterfaceImp(m_pImpIOleItemContainer);
        }

    return;
    }




/*
 * CPage::Update
 *
 * Purpose:
 *  Forces a common on the page if it's open.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if there are any open objects on this page,
 *                  that is, we should remain open.
 */

BOOL CPage::Update(void)
    {
    BOOL            fOpen=FALSE;
    UINT            i;
    PCTenant        pTenant;
    HRESULT         hr;
    LPSTREAM        pIStream;
    TENANTLIST      tl;
    PTENANTINFO     pti;
    ULONG           cb;
    LPMALLOC        pIMalloc;

    //Walk the list of objects and update them all as well.
    for (i=0; i < m_cTenants; i++)
        {
        if (TenantGet(i, &pTenant, FALSE))
            fOpen |= pTenant->Update();
        }

    //Now write our own stream containing the tenant list.
    hr=m_pIStorage->CreateStream(SZSTREAMTENANTLIST, STGM_CREATE
        | STGM_WRITE| STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 0, 0
        , &pIStream);

    if (FAILED(hr))
        return fOpen;

    if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        {
        tl.cTenants=m_cTenants;
        tl.dwIDNext=m_dwIDNext;

        pIStream->Write(&tl, sizeof(TENANTLIST), &cb);

        cb=m_cTenants*sizeof(TENANTINFO);
        pti=(PTENANTINFO)pIMalloc->Alloc(cb);

        if (NULL!=pti)
            {
            for (i=0; i < m_cTenants; i++)
                {
                TenantGet(i, &pTenant, FALSE);
                pTenant->GetInfo((pti+i));
                }

            pIStream->Write(pti, cb, &cb);
            pIMalloc->Free(pti);
            }

        pIMalloc->Release();
        }

    pIStream->Release();

    //Now commit the whole mess and we're done
    if (NULL!=m_pIStorage)
        m_pIStorage->Commit(STGC_DEFAULT);

    return fOpen;
    }





/*
 * CPage::Destroy
 *
 * Purpose:
 *  Removes this page from the given storage.  The caller should
 *  eventually delete this Page object to free the storage.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE contianing this page on which to call
 *                  DestroyElement
 *
 * Return Value:
 *  None
 */

void CPage::Destroy(LPSTORAGE pIStorage)
    {
    if (NULL!=pIStorage)
        {
        OLECHAR szTemp[32];

        Close(FALSE);
        GetStorageName(szTemp);
        pIStorage->DestroyElement(szTemp);
        }

    return;
    }




/*
 * CPage::GetStorageName
 *
 * Parameters:
 *  pszName         LPOLESTR to a buffer in which to store the
 *                  storage name for this page.
 *
 * Return Value:
 *  UINT            Number of characters stored.
 */

UINT CPage::GetStorageName(LPOLESTR pszName)
    {
   #ifdef WIN32ANSI
    char        szTemp[32];
    UINT        cch;

    cch=wsprintf(szTemp, "Page %lu", m_dwID);
    MultiByteToWideChar(CP_ACP, 0, szTemp, -1, pszName, 32);
    return cch;
   #else
    return wsprintf(pszName, TEXT("Page %lu"), m_dwID);
   #endif
    }




/*
 * CPage::Draw
 *
 * Purpose:
 *  Draws the objects on this page to the given hDC.
 *
 * Parameters:
 *  hDC             HDC on which to draw.
 *  xOff, yOff      int offsets for the page.
 *  fNoColor        BOOL indicating black & white screen rendering.
 *  fPrinter        BOOL indicating hDC is on the printer.
 *
 * Return Value:
 *  None
 */

void CPage::Draw(HDC hDC, int xOff, int yOff, BOOL fNoColor
    , BOOL fPrinter)
    {
    int                 i;
    PCTenant            pTenant;
    HDC                 hIC=NULL;
    PCOMBINEDEVICE      pcd=NULL;
    DVTARGETDEVICE     *ptd=NULL;

    /*
     * If printing, tell the tenant to forget the borders. Otherwise
     * we leave xOff and yOff the same to account for scrolling.
     */
    if (fPrinter)
        {
        xOff=LOMETRIC_BORDER+m_pPG->m_xMarginLeft;
        yOff=-LOMETRIC_BORDER-m_pPG->m_yMarginTop;

        /*
         * Get device information.  If this fails, ptd is
         * NULL which is acceptable.
         */
        if (m_pPG->DevReadConfig(&pcd, &hIC))
            ptd=&(pcd->td);
        }

    for (i=(int)m_cTenants-1; i >=0; i--)
        {
        if (TenantGet(i, &pTenant, FALSE))
            {
            RECT        rc, rcWin;
            RECTL       rcl;

            //Paint this tenant only if visible.
            pTenant->RectGet(&rcl, TRUE);
            RECTFROMRECTL(rc, rcl);
            OffsetRect(&rc, -(int)m_pPG->m_xPos
                , -(int)m_pPG->m_yPos);
            GetClientRect(m_hWnd, &rcWin);

            if (IntersectRect(&rc, &rc, &rcWin))
                {
                pTenant->Draw(hDC, ptd, hIC, xOff, yOff
                    , fNoColor, fPrinter);
                }
            }
        }

    //Free whatever CPages::DevReadConfig returned.
    if (NULL!=pcd)
        {
        LPMALLOC    pIMalloc;

        if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
            {
            pIMalloc->Free(pcd);
            pIMalloc->Release();
            }
        }

    if (NULL!=hIC)
        DeleteDC(hIC);

    return;
    }






/*
 * CPage::TenantCreate
 *
 * Purpose:
 *  Creates a new tenant of a specific type.
 *
 * Parameters:
 *  tType           TENANTTYPE to create.
 *  pv              LPVOID providing information for the new
 *                  object creation.
 *  pFE             LPFORMATETC describing how we want this
 *                  rendered.
 *  ppo             PPATRONOBJECT with placement data.
 *  dwData          DWORD extra data to pass to the tenant.
 *
 * Return Value:
 *  None
 */

BOOL CPage::TenantCreate(TENANTTYPE tType, LPVOID pv
    , LPFORMATETC pFE, PPATRONOBJECT ppo, DWORD dwData)
    {
    PCTenant    pTenant;
    UINT        uRet;
    int         x, y;
    int         h, v;
    POINTL      ptl;
    SIZEL       szl;
    RECTL       rcl;
    RECT        rc;

    //New tenants go at top of the pile; zero index to TenantAdd.
    if (!TenantAdd(0, m_dwIDNext, &pTenant))
        return FALSE;

    uRet=pTenant->Create(tType, pv, pFE, &ptl, &szl, m_pIStorage
        , ppo, dwData);

    if (CREATE_FAILED==uRet)
        {
        //Reverse Create AND TenantAdd
        SendMessage(m_hWndTenantList, LB_DELETESTRING, 0, 0L);
        pTenant->Destroy(m_pIStorage);

        pTenant->Release();
        return FALSE;
        }

    m_dwIDNext++;
    m_cTenants++;

    if (NULL!=m_pTenantCur)
        m_pTenantCur->Select(FALSE, TRUE);

    m_iTenantCur=0;             //First one in the list now.
    m_pTenantCur=pTenant;

    //Tell the tenant where it lives, default is (0,0) in print area
    x=LOMETRIC_BORDER+m_pPG->m_xMarginLeft;
    y=-LOMETRIC_BORDER-m_pPG->m_yMarginTop;

    h=x;
    v=y;

    if (CREATE_PLACEDOBJECT==uRet)
        {
        SetRect(&rc, 3*CXYHANDLE, 3*CXYHANDLE, 0, 0);
        RectConvertMappings(&rc, NULL, FALSE);

        //Make sure place point is on page, otherwise go to (0,0)
        if (((int)ptl.x > x)
            && ((int)ptl.x < x+(int)m_pPG->m_cx-rc.left))
            x=(int)ptl.x;

        //m_pPG->m_cy is absolute
        if (((int)ptl.y < y)
            && ((int)ptl.y > y-(int)m_pPG->m_cy-rc.top))
            y=(int)ptl.y;
        }

    //Bounds check size of the object and fit to page as necessary.
    if (x+(int)szl.cx > (int)(h+m_pPG->m_cx))
        szl.cx=h+m_pPG->m_cx-x;

    //Remember that szl we get from Create is absolute
    if (y-(int)szl.cy < (int)(v-m_pPG->m_cy))
        szl.cy=-(int)(v-m_pPG->m_cy-y);

    SETRECTL(rcl, x, y, x+szl.cx, y-szl.cy);
    m_pTenantCur->RectSet(&rcl, FALSE, TRUE);

    //Force a repaint on this new guy
    m_pTenantCur->Invalidate();
    UpdateWindow(m_hWnd);

    m_pTenantCur->Select(TRUE, TRUE);

    //Make sure this new tenant knows about showing it's type.
    m_pTenantCur->ShowObjectType(m_pPG->m_fShowTypes);

    //New tenants must know the available monikers
    if (NULL!=m_pmkFile)
        {
        LPBC        pbc;
        LPMONIKER   pmkPage;
        TCHAR       szTemp[32];
        LPTSTR      pszFile;

       #ifdef WIN32ANSI
        OLECHAR     szW[32];

        GetStorageName(szW);
        WideCharToMultiByte(CP_ACP, 0, szW, -1, szTemp, 32
           , NULL, NULL);
       #else
        GetStorageName(szTemp);
       #endif
        CreateItemMoniker(TEXT("!"), szTemp, &pmkPage);

        //We can get the filename from our file moniker
        CreateBindCtx(0, &pbc);
       #ifdef WIN32ANSI
        LPOLESTR    pszTemp;
        m_pmkFile->GetDisplayName(pbc, NULL, &pszTemp);
        pszFile=(LPTSTR)CoTaskMemAlloc(512);
        WideCharToMultiByte(CP_ACP, 0, pszTemp, -1, pszFile
           , 512, NULL, NULL);
        CoTaskMemFree((void *)pszTemp);
       #else
        m_pmkFile->GetDisplayName(pbc, NULL, &pszFile);
       #endif
        pbc->Release();

        pTenant->NotifyOfRename(pszFile, m_pmkFile, pmkPage);
        pmkPage->Release();
        CoTaskMemFree((void *)pszFile);
        }

    //Activate new objects immediately and force a save on them
    if (TENANTTYPE_EMBEDDEDOBJECT==tType)
        {
        //CHAPTER24MOD
        DWORD       dwFlags;

        /*
         * A control, by virtue of being a control, will already
         * be in-place active except in design mode.  In any case,
         * the only thing a control can do is draw on our page,
         * so there's little point in activating a control here.
         */
        dwFlags=m_pTenantCur->GetControlFlags();

        if (!(TENANTSTATE_CONTROL & dwFlags))
            {
            m_pTenantCur->Activate(OLEIVERB_SHOW, NULL);
            m_pTenantCur->Update();
            }
        //End CHAPTER24MOD
        }

    return TRUE;
    }






/*
 * CPage::TenantDestroy
 *
 * Purpose:
 *  Destroys the currently selected tenant on this page.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

BOOL CPage::TenantDestroy(void)
    {
    if (NULL==m_pTenantCur)
        {
        MessageBeep(0);
        return FALSE;
        }

    SendMessage(m_hWndTenantList, LB_DELETESTRING
        , m_iTenantCur, 0L);

    m_pTenantCur->Invalidate();
    m_pTenantCur->Destroy(m_pIStorage);
    m_pTenantCur->Release();
    m_pTenantCur=NULL;

    //Update counts, etc., and select the next tenant in the list.
    if (m_iTenantCur==m_cTenants-1)
        m_iTenantCur--;

    if (0==--m_cTenants)
        m_pTenantCur=NULL;
    else
        {
        TenantGet(m_iTenantCur, &m_pTenantCur, TRUE);
        m_pTenantCur->Select(TRUE, TRUE);
        }

    UpdateWindow(m_hWnd);
    return TRUE;
    }





/*
 * CPage::TenantClip
 *
 * Purpose:
 *  Copies or cuts the currently selected tenant to the clipoard.
 *
 * Parameters:
 *  fCut            BOOL TRUE to cut the object, FALSE to copy.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPage::TenantClip(BOOL fCut)
    {
    LPDATAOBJECT    pIDataObject;
    BOOL            fRet=FALSE;

    if (NULL==m_pTenantCur)
        return FALSE;

    /*
     * To perform a data transfer operation, we need to create a
     * data object with the selected object's data inside. To do
     * this we CoCreateInstance on CLSID_DataTransferObject
     * (Also implemented in this chapter), retrieve data from the
     * object we have, stuff that data into the transfer object,
     * then stick that object on the clipboard.
     *
     * Since we'll want an identical object at other times, like for
     * drag-drop, we use a private function to actually create it.
     */

    pIDataObject=TransferObjectCreate(NULL);

    if (NULL!=pIDataObject)
        {
        if (SUCCEEDED(OleSetClipboard(pIDataObject)))
            {
            if (fCut)
                TenantDestroy();

            fRet=TRUE;
            }

        pIDataObject->Release();
        }

    return fRet;
    }





/*
 * CPage::FQueryObjectSelected
 *
 * Purpose:
 *  Returns whether or not there is an object selected on this
 *  page for Cut, Copy, Delete functions.
 *
 * Parameters:
 *  hMenu           HMENU of the Edit menu.
 *
 * Return Value:
 *  BOOL            TRUE if we have an object, FALSE otherwise.
 */

BOOL CPage::FQueryObjectSelected(HMENU hMenu)
    {
    HMENU       hMenuTemp;

    /*
     * This will only be called on WM_INITMENUPOPUP, we'll also
     * use this function to create the Verb menu for this object.
     */
    if (NULL!=m_pTenantCur)
        {
        m_pTenantCur->AddVerbMenu(hMenu, MENUPOS_OBJECT);
        return TRUE;
        }

    OleUIAddVerbMenu(NULL, NULL, hMenu, MENUPOS_OBJECT
        , IDM_VERBMIN, IDM_VERBMAX, FALSE, 0, &hMenuTemp);

    return FALSE;
    }




/*
 * CPage::ActivateObject
 *
 * Purpose:
 *  Executes a verb on the currently selected object.
 *
 * Parameters:
 *  iVerb           LONG of the selected verb.
 *  pMSG            LPMSG that caused the invocation of the verb.
 *
 * Return Value:
 *  None
 */

void CPage::ActivateObject(LONG iVerb, LPMSG pMSG)
    {
    if (NULL==m_pTenantCur)
        return;

    m_pTenantCur->Activate(iVerb, pMSG);
    return;
    }




/*
 * CPage::ShowObjectTypes
 *
 * Purpose:
 *  Loops through all the tenants and tells each one to turn on or
 *  off the Show Objects features.
 *
 * Parameters:
 *  fShow           BOOL indicating to show the type or not.
 *
 * Return Value:
 *  None
 */

void CPage::ShowObjectTypes(BOOL fShow)
    {
    PCTenant    pTenant;
    UINT        i;

    for (i=0; i < m_cTenants; i++)
        {
        if (TenantGet(i, &pTenant, FALSE))
            pTenant->ShowObjectType(fShow);
        }

    return;
    }




/*
 * CPage::NotifyTenantsOfRename
 *
 * Purpose:
 *  Loops through all the tenants and informs each of the new
 *  document name.
 *
 * Parameters:
 *  pszFile         LPTSTR of the new filename.
 *  pmk             LPMONKIER for the new filename.
 *
 * Return Value:
 *  None
 */

void CPage::NotifyTenantsOfRename(LPTSTR pszFile, LPMONIKER pmk)
    {
    PCTenant    pTenant;
    UINT        i;
    LPMONIKER   pmkPage;
    LPMONIKER   pmkAll;
    TCHAR       szTemp[32];

    //Save the file moniker
    ReleaseInterface(m_pmkFile);
    m_pmkFile=pmk;
    m_pmkFile->AddRef();

    //Create a page moniker to send to the tenants.
   #ifdef WIN32ANSI
    OLECHAR     szW[32];

    GetStorageName(szW);
    WideCharToMultiByte(CP_ACP, 0, szW, -1, szTemp, 32
       , NULL, NULL);
   #else
    GetStorageName(szTemp);
   #endif
    CreateItemMoniker(TEXT("!"), szTemp, &pmkPage);

    for (i=0; i < m_cTenants; i++)
        {
        if (TenantGet(i, &pTenant, FALSE))
            pTenant->NotifyOfRename(pszFile, pmk, pmkPage);
        }

    /*
     * Register a File!Page!"\" wildcard moniker as well.
     * Note that the page is already marked as running
     * with the document's wildcard moniker.
     */
    CreateItemMoniker(TEXT("!"), TEXT("\\"), &pmkAll);

    if (NULL!=pmkAll)
        {
        LPMONIKER   pmkWild=NULL;
        LPMONIKER   pmkTemp=NULL;

        INOLE_RevokeAsRunning(&m_dwRegROTWild);
        pmk->ComposeWith(pmkPage, FALSE, &pmkTemp);

        if (NULL!=pmkTemp)
            {
            pmkTemp->ComposeWith(pmkAll, FALSE, &pmkWild);
            pmkTemp->Release();
            }

        if (NULL!=pmkWild)
            {
            INOLE_RegisterAsRunning(this, pmk, 0
                , &m_dwRegROTWild);
            pmkWild->Release();
            }

        pmkAll->Release();
        }

    //If anything held onto this, they AddRef'd
    pmkPage->Release();
    return;
    }


/*
 * CPage::ConvertObject
 *
 * Purpose:
 *  Invokes and handles the results of the Convert dialog
 *
 * Parameters:
 *  hWndFrame       HWND to use as the parent of the dialog.
 *  fNoServer       BOOL indicating if this was called because
 *                  ActivateObject failed.
 *
 * Return Value:
 *  None
 */

BOOL CPage::ConvertObject(HWND hWndFrame, BOOL fNoServer)
    {
    HRESULT         hr;
    OLEUICONVERT    ct;
    TENANTTYPE      tType;
    TENANTINFO      ti;
    UINT            uRet;
    HCURSOR         hCur;
    BOOL            fActivate=fNoServer;
    SIZEL           szl;

    if (NULL==m_pTenantCur)
        return FALSE;

    tType=m_pTenantCur->TypeGet();

    if (TENANTTYPE_STATIC==tType)
        {
        MessageBeep(0);
        return FALSE;
        }

    //Get object information we may want.
    m_pTenantCur->GetInfo(&ti);

    //Fill the structure.
    memset(&ct, 0, sizeof(ct));
    ct.cbStruct=sizeof(OLEUICONVERT);
    ct.hWndOwner=hWndFrame;
    ct.fIsLinkedObject=(TENANTTYPE_LINKEDOBJECT==tType);
    ct.dvAspect=ti.fe.dwAspect;

    m_pTenantCur->ObjectClassFormatAndIcon(&ct.clsid, &ct.wFormat
        , &ct.lpszUserType, &ct.hMetaPict, &ct.lpszDefLabel);

    uRet=OleUIConvert(&ct);

    if (OLEUI_OK==uRet)
        {
        //Potentially a long operation.
        hCur=SetCursor(LoadCursor(NULL, IDC_WAIT));

        //Prevent multiple repaints.
        m_pTenantCur->EnableRepaint(FALSE);

        //First, let's bother with the iconic aspect switch.
        if ((DVASPECT_ICON==ct.dvAspect && ct.fObjectsIconChanged)
            || ct.dvAspect!=ti.fe.dwAspect)
            {
            HGLOBAL     hMem=NULL;

            //Only pass non-NULL handle for icon aspects.
            if (DVASPECT_ICON==ct.dvAspect)
                hMem=ct.hMetaPict;

            m_pPG->m_fDirty=m_pTenantCur->SwitchOrUpdateAspect(hMem
                , FALSE);
            }

        //Now change types around.
        if ((CF_SELECTCONVERTTO & ct.dwFlags)
            && ct.clsid!=ct.clsidNew)
            {
            LPSTORAGE   pIStorage;

            /*
             * User selected convert, so:
             *  1.  Unload the object (back to passive state)
             *  2.  Call INOLE_DoConvert, which calls WriteClassStg,
             *      WriteFmtUserTypeStg, and SetConvertStg.
             *  3.  Reload the object and force an update.
             */

            //This should be the only close necessary.
            m_pTenantCur->StorageGet(&pIStorage);
            m_pTenantCur->Close(TRUE);

            hr=INOLE_DoConvert(pIStorage, ct.clsidNew);

            //Need to commit the new type and format
            pIStorage->Commit(STGC_DEFAULT);
            pIStorage->Release();

            if (SUCCEEDED(hr))
                {
                LPUNKNOWN   pObj;
                LPOLEOBJECT pIOleObject;

                //Reload and update.
                m_pTenantCur->Load(m_pIStorage, &ti);

                m_pTenantCur->ObjectGet(&pObj);
                pObj->QueryInterface(IID_IOleObject
                    , (PPVOID)&pIOleObject);
                pIOleObject->Update();
                pIOleObject->Release();
                pObj->Release();
                }

            m_pPG->m_fDirty=TRUE;
            }


        if (CF_SELECTACTIVATEAS & ct.dwFlags)
            {
            /*
             * User selected Activate As, so:
             *  1.  Add the TreatAs entry in the registry
             *      through CoTreatAsClass
             *  2.  Unload all objects of the old CLSID that you
             *      have loaded.
             *  3.  Reload objects as desired
             *  4.  Activate the current object.
             */

            hr=CoTreatAsClass(ct.clsid, ct.clsidNew);

            if (SUCCEEDED(hr))
                {
                PCTenant    pTenant;
                UINT        i;

                for (i=0; i < m_cTenants; i++)
                    {
                    if (TenantGet(i, &pTenant, FALSE))
                        {
                        pTenant->GetInfo(&ti);
                        pTenant->Close(FALSE);
                        pTenant->Load(m_pIStorage, &ti);
                        }
                    }

                fActivate=TRUE;
                }
            }

        //These two steps insure the object knows of the size.
        m_pTenantCur->SizeGet(&szl, FALSE);
        m_pTenantCur->SizeSet(&szl, FALSE, TRUE);

        m_pTenantCur->EnableRepaint(TRUE);
        m_pTenantCur->Repaint();

        if (fActivate)
            m_pTenantCur->Activate(OLEIVERB_SHOW, NULL);

        SetCursor(hCur);
        }

    CoTaskMemFree((void*)ct.lpszUserType);
    INOLE_MetafilePictIconFree(ct.hMetaPict);

    return TRUE;
    }







/*
 * CPages::FQueryLinksInPage
 *
 * Purpose:
 *  Pass through to current page to see if there are any linked
 *  objects.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

BOOL CPage::FQueryLinksInPage()
    {
    PCTenant    pTenant;
    UINT        i;
    BOOL        fRet=FALSE;

    for (i=0; i < m_cTenants; i++)
        {
        if (TenantGet(i, &pTenant, FALSE))
            fRet |= (pTenant->TypeGet()==TENANTTYPE_LINKEDOBJECT);
        }

    return fRet;
    }




/*
 * CPage::ScrolledWindow
 *
 * Purpose:
 *  Instructs the page to call CTenant::UpdateInPlaceObjectRects
 *  for the current tenant when the window is scrolled.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPage::ScrolledWindow(void)
    {
    UINT        i;
    PCTenant    pTenant;

    /*
     * Tell all tenants to update the position of in-place objects.
     * If you do not support inside-out, only the selected object
     * need be notified.
     */
    for (i=0; i < m_cTenants; i++)
        {
        if (!TenantGet(i, &pTenant, FALSE))
            continue;

        pTenant->UpdateInPlaceObjectRects(NULL, TRUE);
        }

    return;
    }


/*
 * CPage::SwitchActiveTenant
 *
 * Purpose:
 *  Changes the activation of in-place objects from the current
 *  one known to the page to the new one passed to this function.
 *  This is called from IOleInPlaceSite::OnUIDeactivate.
 *
 * Parameters:
 *  pTenant         PCTenant that is becoming active.
 *
 * Return Value:
 *  None
 */

void CPage::SwitchActiveTenant(PCTenant pTenant)
    {
    BOOL        fSelect;

    /*
     * If we're UI activating the selected tenant, don't
     * bother changing selection--just so activation.
     */
    fSelect=(pTenant!=m_pTenantCur);

    /*
     * The first time we UI Activate we're not switching
     * anything so avoid the whole sequence.
     */
    if (m_fFirstUIActivate)
        {
        m_fFirstUIActivate=FALSE;
        return;
        }

    if (NULL!=m_pTenantCur && fSelect)
        m_pTenantCur->Select(FALSE, TRUE);

    m_pTenantCur=pTenant;

    //Select the new tenant, but don't activate it again
    if (NULL!=m_pTenantCur)
        {
        UINT        i;

        if (fSelect)
            m_pTenantCur->Select(TRUE, FALSE);

        //Find the new tenant in our list and move to the top
        for (i=0; i < m_cTenants; i++)
            {
            PCTenant        pTenList;

            if (TenantGet(i, &pTenList, FALSE))
                {
                if (pTenList==m_pTenantCur)
                    {
                    HWND        hWndObj;

                    m_iTenantCur=0;

                    //Remove the tenant and add to the top again.
                    SendMessage(m_hWndTenantList, LB_DELETESTRING
                        , i, 0L);
                    SendMessage(m_hWndTenantList, LB_INSERTSTRING
                        , 0, (LONG)pTenant);

                    hWndObj=pTenant->ObjectWindow();

                    if (NULL!=hWndObj)
                        {
                        SetWindowPos(hWndObj, HWND_TOP, 0, 0, 0, 0
                            , SWP_NOMOVE | SWP_NOSIZE
                            | SWP_NOACTIVATE);
                        }
                    break;
                    }
                }
            }
        }

    return;
    }



//CHAPTER24MOD
/*
 * CPage::ToggleDesignMode
 * CPage::ToggleUIDead
 * CPage::ToggleHatchHandles
 *
 * Purpose:
 *  Loops through all the tenants and toggles a state.
 */

void CPage::ToggleDesignMode(BOOL fDesign)
    {
    PCTenant    pTenant;
    int         i;

    /*
     * We do this in reverse order such that when we reactivate
     * objects coming out of design mode we reactivate the
     * visible "top" tenant last, therefore it's in-place window
     * will be top of the z-order in the container and will overlap
     * other objects correctly.
     */
    for (i=(int)m_cTenants-1; i >=0; i--)
        {
        if (TenantGet(i, &pTenant, FALSE))
            pTenant->ToggleDesignMode(fDesign);
        }

    return;
    }


void CPage::ToggleUIDead(BOOL fUIDead)
    {
    PCTenant    pTenant;
    UINT        i;

    for (i=0; i < m_cTenants; i++)
        {
        if (TenantGet(i, &pTenant, FALSE))
            pTenant->ToggleUIDead(fUIDead);
        }

    return;
    }


void CPage::ToggleHatchHandles(BOOL fHatchHandles)
    {
    PCTenant    pTenant;
    UINT        i;

    for (i=0; i < m_cTenants; i++)
        {
        if (TenantGet(i, &pTenant, FALSE))
            pTenant->ToggleHatchHandles(fHatchHandles);
        }

    return;
    }



/*
 * CPage::FQueryEnableEvents
 *
 * Purpose:
 *  Returns whether to enable events for the current tenant.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE to enable the item, FALSE otherwise.
 */

BOOL CPage::FQueryEnableEvents(void)
    {
    DWORD   dwFlags;

    if (NULL==m_pTenantCur)
        return FALSE;

    dwFlags=m_pTenantCur->GetControlFlags();
    return 0!=(TENANTSTATE_EVENTS & dwFlags);
    }



/*
 * CPage::AssignEvents
 *
 * Purpose:
 *  Invokes a dialog in which the user can assign actions to
 *  control events.
 *
 * Parameters:
 *  hWndParent      HWND to use as the dialog parent.
 *
 * Return Value:
 *  None
 */

void CPage::AssignEvents(HWND hWndParent)
    {
    DialogBoxParam(m_pPG->m_hInst, MAKEINTRESOURCE(IDD_EVENTS)
        , hWndParent, EventsDlgProc
        , (LONG)m_pTenantCur->EventMap());

    return;
    }




/*
 * CPage::TryMnemonic
 *
 * Purpose:
 *  Loops through all the tenants checking each for a match
 *  with a keybord mnemonic.
 *
 * Parameters:
 *  pMsg            LPMSG containing the message to check.
 *
 * Return Value:
 *  BOOL            TRUE if the mnemonic was a match with any
 *                  tenant, FALSE otherwise.
 */

BOOL CPage::TryMnemonic(LPMSG pMsg)
    {
    BOOL    fRet=FALSE;
    UINT    i;

    for (i=0; i < m_cTenants; i++)
        {
        PCTenant    pTenant;

        if (TenantGet(i, &pTenant, FALSE))
            {
            fRet=pTenant->TryMnemonic(pMsg);

            if (fRet)
                break;
            }
        else
            break;
        }

    return fRet;
    }
//End CHAPTER24MOD




/*
 * CPage::TenantGet
 * (Protected)
 *
 * Purpose:
 *  Returns a tenant of a given index returning a BOOL so it's
 *  simple to use this function inside if statements.
 *
 * Parameters:
 *  iTenant         UINT tenant to retrieve 0 based.
 *  ppTenant        PCPage * in which to return the tenant
 *                  pointer
 *  fOpen           BOOL indicating if we should open this
 *                  tenant as well.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPage::TenantGet(UINT iTenant, PCTenant *ppTenant
    , BOOL fOpen)
    {
    if (NULL==ppTenant)
        return FALSE;

    if (LB_ERR!=SendMessage(m_hWndTenantList, LB_GETTEXT
        , iTenant, (LONG)ppTenant))
        {
        if (fOpen)
            (*ppTenant)->Open(m_pIStorage);

        return TRUE;
        }

    return FALSE;
    }






/*
 * CPage::TenantGetFromID
 * (Protected)
 *
 * Purpose:
 *  Finds a tenant pointer from an ID for use from
 *  IOleItemContainer::GetObject
 *
 * Parameters:
 *  dwID            DWORD identifier of the tenant to find.
 *  ppTenant        PCTenant * in which to return the tenant
 *                  pointer
 *  fOpen           BOOL indicating if we should open this tenant as
 *                  well.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPage::TenantGetFromID(DWORD dwID, PCTenant *ppTenant
    , BOOL fOpen)
    {
    UINT        i;
    PCTenant    pTenant;

    if (NULL==ppTenant)
        return FALSE;

    for (i=0; i < m_cTenants; i++)
        {
        if (!TenantGet(i, &pTenant, FALSE))
            continue;

        if (pTenant->GetID()==dwID)
            {
            if (fOpen)
                pTenant->Open(m_pIStorage);

            *ppTenant=pTenant;
            return TRUE;
            }
        }

    return FALSE;
    }





/*
 * CPage::TenantAdd
 * (Protected)
 *
 * Purpose:
 *  Creates a new tenant initialized to the given values.  The new
 *  tenants's storage is created if it does not already exist.  If
 *  fOpenStorage is set the the tenants's storage is opened and left
 *  opened.
 *
 * Parameters:
 *  iTenant         UINT Location at which to insert tenant; new
 *                  tenant is inserted after this position.  NOVALUE
 *                  for the end.
 *  dwID            DWORD ID for this tenant.
 *  ppNew           PCTenant * in which to store the new tenant.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CPage::TenantAdd(UINT iTenant, DWORD dwID
    , PCTenant *ppNew)
    {
    PCTenant    pTenant;
    LRESULT     lr;

    if (NULL!=ppNew)
        *ppNew=NULL;

    pTenant=new CTenant(dwID, m_hWnd, m_pPG);

    if (NULL==pTenant)
        return FALSE;

    //The constructor doesn't AddRef, so we need to.
    pTenant->AddRef();

    //Now try to add to the listbox.
    lr=SendMessage(m_hWndTenantList, LB_INSERTSTRING, iTenant
        , (LONG)pTenant);

    if (lr < 0)
        {
        pTenant->Release();
        return FALSE;
        }

    *ppNew=pTenant;
    return TRUE;
    }





/*
 * CPage::TransferObjectCreate
 * (Protected)
 *
 * Purpose:
 *  Creates a DataTransferObject and stuff the current selection's
 *  data into it.
 *
 * Parameters:
 *  pptl            PPOINTL containing the pick point in device
 *                  units applicable only to drag-drop; since
 *                  drag-drop is inherently mouse oriented, we use
 *                  device units for the point.  Ignored if NULL.
 *
 * Return Value:
 *  LPDATAOBJECT    Pointer to the object created, NULL on failure
 */

LPDATAOBJECT CPage::TransferObjectCreate(PPOINTL pptl)
    {
    LPDATAOBJECT    pIDataObject;
    LPDATAOBJECT    pIDataT;
    PPATRONOBJECT   ppo;
    RECTL           rcl;
    LPUNKNOWN       pObj;
    FORMATETC       fe;
    STGMEDIUM       stm;
    HRESULT         hr;
    HGLOBAL         hMem;

    m_pTenantCur->ObjectGet(&pObj);

    hr=CoCreateInstance(CLSID_DataTransferObject, NULL
        , CLSCTX_INPROC_SERVER, IID_IDataObject
        , (PPVOID)&pIDataObject);

    if (FAILED(hr))
        return NULL;

    //Go get the data we should hold on to.
    hr=pObj->QueryInterface(IID_IDataObject, (PPVOID)&pIDataT);

    if (FAILED(hr))
        {
        pIDataObject->Release();
        pObj->Release();
        return NULL;
        }

    //Copy from known obj into transfer obj.  Ordering is important!

    //Generate placeable object structure
    stm.tymed=TYMED_HGLOBAL;
    stm.pUnkForRelease=NULL;
    stm.hGlobal=GlobalAlloc(GHND, sizeof(PATRONOBJECT));

    if (NULL==stm.hGlobal)
        {
        pIDataObject->Release();
        pObj->Release();
        return NULL;
        }

    ppo=(PPATRONOBJECT)GlobalLock(stm.hGlobal);

    m_pTenantCur->SizeGet(&ppo->szl, FALSE);
    ppo->szl.cy=-ppo->szl.cy; //Negate to make absolute size

    m_pTenantCur->RectGet(&rcl, FALSE);
    ppo->ptl.x=rcl.left;
    ppo->ptl.y=rcl.top;

    if (NULL==pptl)
        {
        ppo->ptlPick.x=0;
        ppo->ptlPick.y=0;
        }
    else
        ppo->ptlPick=*pptl;

    m_pTenantCur->FormatEtcGet(&ppo->fe, FALSE);

    //If this is a linked object, just copy a presentation
    if (TENANTTYPE_LINKEDOBJECT==m_pTenantCur->TypeGet())
        m_pTenantCur->FormatEtcGet(&ppo->fe, TRUE);

    SETDefFormatEtc(fe, m_pPG->m_cf, TYMED_HGLOBAL);
    pIDataObject->SetData(&fe, &stm, TRUE);

    /*
     * Here now we have to include CFSTR_EMBEDDEDOBJECT and
     * CFSTR_OBJECTDESCRIPTOR when what we have selected is, in
     * fact, a compound document object.  We'll just ask the tenant
     * to set these in pIDataObject since it knows what the object.
     * If we copy embedded object data, make sure the PATRONOBJECT
     * structure has the right format in it as well.
     */
    m_pTenantCur->CopyEmbeddedObject(pIDataObject, &ppo->fe, pptl);
    hMem=stm.hGlobal;

    //Copy the actual presentation.
    m_pTenantCur->FormatEtcGet(&fe, TRUE);
    pIDataT->GetData(&fe, &stm);
    pIDataObject->SetData(&fe, &stm, TRUE);

    //Copy a link to this tenant if it's embedded
    m_pTenantCur->CopyLinkedObject(pIDataObject, &ppo->fe, pptl);
    GlobalUnlock(hMem); //ppo

    pIDataT->Release();
    pObj->Release();
    return pIDataObject;    //Caller now responsible
    }
