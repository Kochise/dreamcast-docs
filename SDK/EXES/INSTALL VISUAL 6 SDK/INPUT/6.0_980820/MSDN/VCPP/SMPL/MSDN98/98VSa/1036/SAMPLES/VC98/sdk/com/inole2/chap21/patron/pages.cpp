/*
 * PAGES.CPP
 * Patron Chapter 21
 *
 * Implementation of the CPages class.  See PAGEWIN.CPP and PRINT.CPP
 * for additional member functions.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CPages:CPages
 * CPages::~CPages
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application we're in.
 *  cf              UINT application clipboard format.
 */

CPages::CPages(HINSTANCE hInst, UINT cf)
    : CWindow(hInst)
    {
    m_pPageCur=NULL;
    m_iPageCur=NOVALUE;  //Pages are 0 indexed, this is one before
    m_cPages=0;
    m_hWndPageList=NULL;
    m_hFont=NULL;
    m_fSystemFont=FALSE;

    //Initialize to 8.5*11 inch with .25 inch margins as a default.
    m_cx=(LOMETRIC_PER_INCH*17)/2;
    m_cy=LOMETRIC_PER_INCH*11;

    m_xMarginLeft=LOMETRIC_PER_INCH/4;
    m_xMarginRight=LOMETRIC_PER_INCH/4;
    m_yMarginTop=LOMETRIC_PER_INCH/4;
    m_yMarginBottom=LOMETRIC_PER_INCH/4;

    m_xPos=0L;
    m_yPos=0L;

    m_dwIDNext=0;
    m_pIStorage=NULL;

    m_fDirty=FALSE;
    m_cf=cf;

    m_fDragSource=FALSE;
    m_fMoveInPage=FALSE;
    m_fLinkAllowed=FALSE;

    m_fDragRectShown=FALSE;

    m_uScrollInset=GetProfileInt(TEXT("windows")
        , TEXT("DragScrollInset"), DD_DEFSCROLLINSET);

    m_uScrollDelay=GetProfileInt(TEXT("windows")
        , TEXT("DragScrollDelay"), DD_DEFSCROLLDELAY);

    m_uHScrollCode=0;
    m_uVScrollCode=0;
    m_fShowTypes=FALSE;

    //CHAPTER21MOD
    m_pmkFile=NULL;
    //End CHAPTER21MOD
    return;
    }


CPages::~CPages(void)
    {
    //Ensure memory cleaned up in list; do final IStorage::Release
    StorageSet(NULL, FALSE, FALSE);

    //CHAPTER21MOD
    ReleaseInterface(m_pmkFile);
    //End CHAPTER21MOD

    if (NULL!=m_hFont && !m_fSystemFont)
        DeleteObject(m_hFont);

    if (NULL!=m_hWndPageList)
        DestroyWindow(m_hWndPageList);

    //m_hWnd destroyed with the document.
    return;
    }



/*
 * CPages::FIsDirty
 *
 * Purpose:
 *  Tells the caller (document) if anything's happened to dirty us.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

BOOL CPages::FIsDirty(void)
    {
    return m_fDirty;
    }



/*
 * CPages::Init
 *
 * Purpose:
 *  Instantiates a pages window within a given parent.  The
 *  parent may be a main application window, could be an MDI child
 *  window. We really do not care.
 *
 * Parameters:
 *  hWndParent      HWND of the parent of this window
 *  pRect           LPRECT that this window should occupy
 *  dwStyle         DWORD containing the window's style flags.
 *                  Should contain WS_CHILD | WS_VISIBLE in
 *                  typical circumstances.
 *  uID             UINT ID to associate with this window
 *  pv              LPVOID unused for now.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CPages::Init(HWND hWndParent, LPRECT pRect, DWORD dwStyle
    , UINT uID, LPVOID pv)
    {
    int     cy;

    m_hWnd=CreateWindowEx(WS_EX_NOPARENTNOTIFY, SZCLASSPAGES
        , SZCLASSPAGES, dwStyle, pRect->left, pRect->top
        , pRect->right-pRect->left, pRect->bottom-pRect->top
        , hWndParent, (HMENU)uID, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    /*
     * Create the hidden listbox we'll use to track pages.  We give
     * it the owner-draw style so we can just store pointers in it.
     */
    m_hWndPageList=CreateWindow(TEXT("listbox"), TEXT("Page List")
        , WS_POPUP | LBS_OWNERDRAWFIXED, 0, 0, 100, 100
        , HWND_DESKTOP, NULL, m_hInst, NULL);

    if (NULL==m_hWndPageList)
        return FALSE;

    //Create a 14 point Arial font, or use the system variable font.
    cy=MulDiv(-14, LOMETRIC_PER_INCH, 72);
    m_hFont=CreateFont(cy, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE
        , ANSI_CHARSET, OUT_TT_PRECIS, CLIP_TT_ALWAYS, PROOF_QUALITY
        , VARIABLE_PITCH | FF_SWISS, TEXT("Arial"));

    if (NULL==m_hFont)
        {
        m_hFont=(HFONT)GetStockObject(ANSI_VAR_FONT);
        m_fSystemFont=TRUE;
        }

    return TRUE;
    }






/*
 * CPages::StorageSet
 *
 * Purpose:
 *  Provides the document's IStorage to the pages for its own use.
 *  If this is a new storage, we initalize it with streams that we
 *  want to always exists.  If this is an open, then we create
 *  our page list from the PageList string we wrote before.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE to the new or opened storage.  If
 *                  NULL, we just clean up and exit.
 *  fChange         BOOL indicating is this was a Save As operation,
 *                  meaning that we have the structure already and
 *                  just need to change the value of m_pIStorage.
 *  fInitNew        BOOL indicating if this is a new storage or one
 *                  opened from a previous save.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPages::StorageSet(LPSTORAGE pIStorage, BOOL fChange
    , BOOL fInitNew)
    {
    DWORD           dwMode=STGM_DIRECT | STGM_READWRITE
                        | STGM_SHARE_EXCLUSIVE;
    HRESULT         hr;
    PCPage          pPage;
    BOOL            fRet=FALSE;
    ULONG           cbRead;
    PAGELIST        pgList;
    LPSTREAM        pIStream;
    LPMALLOC        pIMalloc;
    LPDWORD         pdwID;
    UINT            i;

    //If we're changing saved roots, simply open current page again
    if (fChange)
        {
        if (NULL==pIStorage)
            return FALSE;

        m_pIStorage->Release();
        m_pIStorage=pIStorage;
        m_pIStorage->AddRef();

        PageGet(m_iPageCur, &m_pPageCur, TRUE);
        m_fDirty=FALSE;
        return TRUE;
        }

    if (NULL!=m_hWndPageList)
        {
        //On new or open, clean out whatever it is we have.
        for (i=0; i < m_cPages; i++)
            {
            //CHAPTER21MOD
            if (PageGet(i, &pPage, FALSE))
                pPage->Release();
            //End CHAPTER21MOD
            }

        SendMessage(m_hWndPageList, LB_RESETCONTENT, 0, 0L);
        }

    if (NULL!=m_pIStorage)
        m_pIStorage->Release();

    m_pIStorage=NULL;

    //If we're just cleaning up, then we're done.
    if (NULL==pIStorage)
        return TRUE;

    m_pIStorage=pIStorage;
    m_pIStorage->AddRef();

    //If this is a new storage, create the streams we require
    if (fInitNew)
        {
        //Page list header.
        hr=m_pIStorage->CreateStream(SZSTREAMPAGELIST, dwMode
            | STGM_CREATE, 0, 0, &pIStream);

        if (FAILED(hr))
            return FALSE;

        pIStream->Release();

        //Device Configuration
        hr=m_pIStorage->CreateStream(SZSTREAMDEVICECONFIG, dwMode
            | STGM_CREATE, 0, 0, &pIStream);

        if (FAILED(hr))
            return FALSE;

        pIStream->Release();
        return TRUE;
        }


    /*
     * We're opening an existing file:
     *  1)  Configure for the device we're on
     *  2)  Read the Page List and create page entries for each.
     */

    ConfigureForDevice();

    //Read the page list.
    hr=m_pIStorage->OpenStream(SZSTREAMPAGELIST, NULL, dwMode, 0
        , &pIStream);

    if (FAILED(hr))
        return FALSE;

    if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        {
        pIStream->Read(&pgList, sizeof(PAGELIST), &cbRead);
        m_cPages  =(UINT)pgList.cPages;
        m_iPageCur=(UINT)pgList.iPageCur;
        m_dwIDNext=pgList.dwIDNext;

        fRet=TRUE;
        cbRead=pgList.cPages*sizeof(DWORD);

        if (0!=cbRead)
            {
            pdwID=(LPDWORD)pIMalloc->Alloc(cbRead);

            if (NULL!=pdwID)
                {
                pIStream->Read(pdwID, cbRead, &cbRead);

                for (i=0; i < m_cPages; i++)
                    fRet &=PageAdd(NOVALUE, *(pdwID+i), FALSE);

                pIMalloc->Free(pdwID);
                }
            }

        pIMalloc->Release();
        }

    pIStream->Release();

    if (!fRet)
        return FALSE;

    PageGet(m_iPageCur, &m_pPageCur, TRUE);
    m_fDirty=FALSE;

    InvalidateRect(m_hWnd, NULL, FALSE);
    UpdateWindow(m_hWnd);

    return TRUE;
    }





/*
 * CPages::StorageUpdate
 *
 * Purpose:
 *  Insures that all pages are committed before a root save.
 *
 * Parameters:
 *  fCloseAll       BOOL directing us to close all open storages
 *                  and streams.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPages::StorageUpdate(BOOL fCloseAll)
    {
    PCPage          pPage;
    LPSTREAM        pIStream;
    LPMALLOC        pIMalloc;
    LPDWORD         pdwID;
    ULONG           cb;
    HRESULT         hr;
    PAGELIST        pgList;
    BOOL            fRet=FALSE;
    UINT            i;

    //We only need to close the current page--nothing else is open.
    if (NULL!=m_pPageCur)
        {
        m_pPageCur->Update();

        if (fCloseAll)
            m_pPageCur->Close(FALSE);
        }

    //We don't hold anything else open, so write the page list.
    hr=m_pIStorage->OpenStream(SZSTREAMPAGELIST, NULL, STGM_DIRECT
        | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return FALSE;

    if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        {
        pgList.cPages=m_cPages;
        pgList.iPageCur=m_iPageCur;
        pgList.dwIDNext=m_dwIDNext;

        pIStream->Write(&pgList, sizeof(PAGELIST), &cb);

        cb=m_cPages*sizeof(DWORD);
        pdwID=(LPDWORD)pIMalloc->Alloc(cb);

        if (NULL!=pdwID)
            {
            for (i=0; i < m_cPages; i++)
                {
                PageGet(i, &pPage, FALSE);
                *(pdwID+i)=pPage->GetID();
                }

            pIStream->Write(pdwID, cb, &cb);
            pIMalloc->Free(pdwID);
            fRet=TRUE;
            }
        pIMalloc->Release();
        }

    pIStream->Release();

    //Clean up the dirty flag when we do an update.
    m_fDirty=!fRet;
    return fRet;
    }







/*
 * CPages::RectGet
 *
 * Purpose:
 *  Returns the rectangle of the Pages window in parent coordinates.
 *
 * Parameters:
 *  pRect           LPRECT in which to return the rectangle.
 *
 * Return Value:
 *  None
 */

void CPages::RectGet(LPRECT pRect)
    {
    RECT        rc;
    POINT       pt;

    //Retrieve the size of our rectangle in parent coordinates.
    GetWindowRect(m_hWnd, &rc);
    SETPOINT(pt, rc.left, rc.top);
    ScreenToClient(GetParent(m_hWnd), &pt);

    SetRect(pRect, pt.x, pt.y, pt.x+(rc.right-rc.left)
        , pt.y+(rc.bottom-rc.top));

    return;
    }






/*
 * CPages::RectSet
 *
 * Purpose:
 *  Sets a new rectangle for the Pages window which sizes to fit.
 *  Coordinates are given in parent terms.
 *
 * Parameters:
 *  pRect           LPRECT containing the new rectangle.
 *  fNotify         BOOL indicating if we're to notify anyone of
 *                  the change.
 *
 * Return Value:
 *  None
 */

void CPages::RectSet(LPRECT pRect, BOOL fNotify)
    {
    UINT        cx, cy;

    if (NULL==pRect)
        return;

    cx=pRect->right-pRect->left;
    cy=pRect->bottom-pRect->top;

    SetWindowPos(m_hWnd, NULL, pRect->left, pRect->top
        , (UINT)cx, (UINT)cy, SWP_NOZORDER);

    UpdateScrollRanges();
    return;
    }




/*
 * CPages::SizeGet
 *
 * Purpose:
 *  Retrieves the size of the pages window in parent coordinates.
 *
 * Parameters:
 *  pRect           LPRECT in which to return the size.  The right
 *                  and bottom fields will contain the dimensions.
 *
 * Return Value:
 *  None
 */

void CPages::SizeGet(LPRECT pRect)
    {
    RectGet(pRect);
    return;
    }







/*
 * CPages::SizeSet
 *
 * Purpose:
 *  Sets a new size in parent coordinates for the Pages window.
 *
 * Parameters:
 *  pRect           LPRECT containing the new rectangle.
 *  fNotify         BOOL indicating if we're to notify anyone of
 *                  the change.
 *
 * Return Value:
 *  None
 */

void CPages::SizeSet(LPRECT pRect, BOOL fNotify)
    {
    UINT        cx, cy;

    if (NULL==pRect)
        return;

    cx=pRect->right-pRect->left;
    cy=pRect->bottom-pRect->top;

    SetWindowPos(m_hWnd, NULL, 0, 0, (UINT)cx, (UINT)cy
        , SWP_NOMOVE | SWP_NOZORDER);

    UpdateScrollRanges();
    return;
    }






/*
 * CPages::ActivePage
 *
 * Purpose:
 *  Returns a CPage pointer to the current page.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCPage          Pointer to the current page.
 */

PCPage CPages::ActivePage(void)
    {
    PCPage      pPage;
    BOOL        fRet;

    fRet=PageGet(m_iPageCur, &pPage, FALSE);
    return fRet ? pPage : NULL;
    }





/*
 * CPages::PageInsert
 *
 * Purpose:
 *  Creates a new page immediately after the current page.  If
 *  there are no pages then this creates page 1.
 *
 * Parameters:
 *  uReserved       UINT unused
 *
 * Return Value:
 *  UINT            Index of the new page, 0 on failure.
 */

UINT CPages::PageInsert(UINT uReserved)
    {
    if (0!=m_cPages && NULL!=m_pPageCur)
        {
        //Close the current page, committing changes.
        m_pPageCur->Close(TRUE);
        }

    //Create and open the new page.
    if (!PageAdd(m_iPageCur, m_dwIDNext, TRUE))
        return 0;

    m_dwIDNext++;
    m_iPageCur++;
    m_cPages++;

    InvalidateRect(m_hWnd, NULL, FALSE);
    UpdateWindow(m_hWnd);

    PageGet(m_iPageCur, &m_pPageCur, FALSE);
    return m_iPageCur;
    }







/*
 * CPages::PageDelete
 *
 * Removes the current page from the page list.
 *
 * Parameters:
 *  uReserved       UINT unused
 *
 * Return Value:
 *  UINT            Index to the now current page from the page
 *                  list, NOVALUE on error.
 */

UINT CPages::PageDelete(UINT uReserved)
    {
    PCPage      pPage;

    if (!PageGet(m_iPageCur, &pPage, FALSE))
        return NOVALUE;

    //Delete the page in both the storage and in memory.
    SendMessage(m_hWndPageList, LB_DELETESTRING, m_iPageCur, 0L);

    m_pPageCur->Destroy(m_pIStorage);

    //CHAPTER21MOD
    m_pPageCur->Release();   //Does final pPage->Close
    //End CHAPTER21MOD
    m_pPageCur=NULL;

    /*
     * If this is the last page then the current is one less.  If
     * it's the only page the current is zero.  Otherwise the
     * current is the next page.
     */

    if (m_iPageCur==m_cPages-1)   //Covers last or only page.
        m_iPageCur--;

    m_cPages--;

    //Insure the new visible page is open.
    if (0!=m_cPages)
        {
        PageGet(m_iPageCur, &m_pPageCur, TRUE);
        InvalidateRect(m_hWnd, NULL, FALSE);
        }
    else
        InvalidateRect(m_hWnd, NULL, TRUE);

    UpdateWindow(m_hWnd);
    return m_iPageCur;
    }






/*
 * CPages::CurPageGet
 *
 * Purpose:
 *  Retrieves the index of the current page we're viewing.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Index of the current page.
 */

UINT CPages::CurPageGet(void)
    {
    return m_iPageCur;
    }





/*
 * CPages::CurPageSet
 *
 * Purpose:
 *  Sets the index of the current page to view.
 *
 * Parameters:
 *  iPage           UINT index of the page to view. 0 means first
 *                  page, NOVALUE means last page.
 *
 * Return Value:
 *  UINT            Index of the previous current page, NOVALUE on
 *                  error.
 */

UINT CPages::CurPageSet(UINT iPage)
    {
    UINT    iPageNew;
    UINT    iPagePrev=m_iPageCur;
    PCPage  pPage;

    switch (iPage)
        {
        case 0:
            iPageNew=0;
            break;

        case NOVALUE:
            iPageNew=m_cPages-1;
            break;

        default:
            if (iPage >= m_cPages)
                iPage=0;

            iPageNew=iPage;
            break;
        }

    //No reason to switch to the same page.
    if (iPagePrev==iPageNew)
        return iPage;

    //Close the old page committing changes.
    if (!PageGet(iPagePrev, &pPage, FALSE))
        return NOVALUE;

    pPage->Close(TRUE);

    m_iPageCur=iPageNew;

    //Open the new page.
    PageGet(m_iPageCur, &m_pPageCur, TRUE);

    InvalidateRect(m_hWnd, NULL, FALSE);
    UpdateWindow(m_hWnd);
    return iPagePrev;
    }





/*
 * CPages::NumPagesGet
 *
 * Purpose:
 *  Returns the number of pages this object current contains.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Number of pages we contain.
 */

UINT CPages::NumPagesGet(void)
    {
    return m_cPages;
    }





/*
 * CPages::TenantCreate
 * CPages::TenantDestroy
 *
 * Purpose:
 *  Pass-throughs for CPage members on the current page.
 */

BOOL CPages::TenantCreate(TENANTTYPE tType, LPVOID pv
    , LPFORMATETC pFE, PPATRONOBJECT ppo, DWORD dwData)
    {
    BOOL    fRet;

    if (NULL==m_pPageCur)
        return FALSE;

    fRet=m_pPageCur->TenantCreate(tType, pv, pFE, ppo, dwData);
    m_fDirty |= fRet;
    return fRet;
    }


BOOL CPages::TenantDestroy(void)
    {
    BOOL    fRet;

    if (NULL==m_pPageCur)
        return FALSE;

    fRet=m_pPageCur->TenantDestroy();
    m_fDirty |= fRet;
    return fRet;
    }



/*
 * CPages::TenantClip
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

BOOL CPages::TenantClip(BOOL fCut)
    {
    BOOL    fRet;

    if (NULL==m_pPageCur)
        return FALSE;

    fRet=m_pPageCur->TenantClip(fCut);
    m_fDirty |= (fRet && fCut);
    return fRet;
    }






/*
 * CPages::FQueryObjectSelected
 *
 * Purpose:
 *  Returns whether or not there is an object selected on this
 *  page for Cut, Copy, Delete functions.
 *
 * Parameters:
 *  hMenu           HMENU on which object related items live.
 *
 * Return Value:
 *  BOOL            TRUE if we have an object, FALSE otherwise.
 */

BOOL CPages::FQueryObjectSelected(HMENU hMenu)
    {
    if (NULL==m_pPageCur)
        return FALSE;

    return m_pPageCur->FQueryObjectSelected(hMenu);
    }



/*
 * CPages::ActivateObject
 *
 * Purpose:
 *  Executes a verb on the currently selected object.
 *
 * Parameters:
 *  iVerb           LONG of the selected verb.
 *
 * Return Value:
 *  None
 */

void CPages::ActivateObject(LONG iVerb)
    {
    if (NULL==m_pPageCur)
        return;

    m_pPageCur->ActivateObject(iVerb);
    return;
    }




/*
 * CPages::ShowObjectTypes
 *
 * Purpose:
 *  Pass-through to CPage::ShowObjectTypes
 *
 * Parameters:
 *  fShow           BOOL indicating to show the type or not.
 *
 * Return Value:
 *  None
 */

void CPages::ShowObjectTypes(BOOL fShow)
    {
    if (NULL==m_pPageCur)
        return;

    m_fShowTypes=fShow;
    m_pPageCur->ShowObjectTypes(fShow);
    return;
    }




/*
 * CPages::NotifyTenantsOfRename
 *
 * Purpose:
 *  Pass-through to CPage to tell tenants that the document
 *  changes names.
 *
 * Parameters:
 *  pszFile         LPTSTR of the new filename.
 *  pmk             LPMONKIER to the new file moniker.
 *
 * Return Value:
 *  None
 */

void CPages::NotifyTenantsOfRename(LPTSTR pszFile, LPMONIKER pmk)
    {
    if (NULL==m_pPageCur)
        return;

    //CHAPTER21MOD
    ReleaseInterface(m_pmkFile);
    m_pmkFile=pmk;
    m_pmkFile->AddRef();
    //End CHAPTER21MOD
    m_pPageCur->NotifyTenantsOfRename(pszFile, pmk);
    return;
    }




/*
 * CPages::FQueryLinksInPage
 *
 * Purpose:
 *  Pass through to current page to see if there are any
 *  linked objects
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

BOOL CPages::FQueryLinksInPage()
    {
    if (NULL==m_pPageCur)
        return FALSE;

    return m_pPageCur->FQueryLinksInPage();
    }





/*
 * CPages::GetUILinkContainer
 *
 * Purpose:
 *  Creates an object with the IOleUILinkContainer interface for
 *  the links dialog.  We know the current page which is what
 *  we need to create this thing, so we can create it here instead
 *  of bugging the page for it.
 *
 * Parameters:
 *  ppObj           PCIOleUILinkContainer * in which we return
 *                  the pointer.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPages::GetUILinkContainer(PCIOleUILinkContainer *ppObj)
    {
    PCIOleUILinkContainer   pObj;

    *ppObj=NULL;

    if (NULL==m_pPageCur)
        return FALSE;

    pObj=new CIOleUILinkContainer(m_pPageCur);

    if (NULL==pObj)
        return FALSE;

    if (!pObj->Init())
        {
        delete pObj;
        return FALSE;
        }

    pObj->AddRef();
    *ppObj=pObj;
    return TRUE;
    }




/*
 * CPages::ConvertObject
 *
 * Purpose:
 *  Pass-through to the current page.
 *
 * Parameters:
 *  hWndFrame       HWND of the frame window.
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful, FALSE
 *                  otherwise.
 */

BOOL CPages::ConvertObject(HWND hWndFrame)
    {
    if (NULL==m_pPageCur)
        return FALSE;

    return m_pPageCur->ConvertObject(hWndFrame, FALSE);
    }





/*
 * CPages::CalcBoundingRect
 * (Protected)
 *
 * Purpose:
 *  Calculates a rectangle that bounds the printed page and the
 *  current scroll state of the window.
 *
 * Parameters:
 *  prc             LPRECT to fill with window (device) coordinates.
 *  fWindow         BOOL indicating to include the window in this
 *                  calculation or return only the printed page
 *                  coordinates.
 *
 * Return Value:
 *  None
 */

void CPages::CalcBoundingRect(LPRECT prc, BOOL fWindow)
    {
    RECT        rc, rcT;

    if (NULL==prc)
        return;

    //Calculate the boundaries for sizing: intersect page & screen
    rc.left=LOMETRIC_BORDER+m_xMarginLeft;
    rc.top =-LOMETRIC_BORDER-m_yMarginTop;
    rc.right =rc.left+(UINT)m_cx;
    rc.bottom=rc.top -(UINT)m_cy;
    RectConvertMappings(&rc, NULL, TRUE);
    OffsetRect(&rc, -(int)m_xPos, -(int)m_yPos);

    if (!fWindow)
        {
        *prc=rc;
        return;
        }

    //Intersect with window to make the size bounds.
    GetClientRect(m_hWnd, &rcT);
    IntersectRect(prc, &rc, &rcT);
    return;
    }






/*
 * CPages::PageGet
 * (Protected)
 *
 * Purpose:
 *  Returns a page of a given index returning a BOOL so it's simple
 *  to use this function inside if statements.
 *
 * Parameters:
 *  iPage           UINT page to retrieve 0 based.
 *  ppPage          PCPage * in which to return the page pointer
 *  fOpen           BOOL indicating if we should open this page as
 *                  well.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPages::PageGet(UINT iPage, PCPage *ppPage, BOOL fOpen)
    {
    if (NULL==ppPage)
        return FALSE;

    if (LB_ERR!=SendMessage(m_hWndPageList, LB_GETTEXT
        , iPage, (LONG)ppPage))
        {
        if (fOpen)
            (*ppPage)->Open(m_pIStorage);

        return TRUE;
        }

    return FALSE;
    }






/*
 * CPages::PageAdd
 * (Protected)
 *
 * Purpose:
 *  Creates a new page initialized to the given values.  The new
 *  page's storage is created if it does not already exist.  If
 *  fOpenStorage is set the page's storage is opened and left
 *  opened.
 *
 * Parameters:
 *  iPage           UINT Location at which to insert page; new page
 *                  is inserted after this position.  NOVALUE for
 *                  the end.
 *  dwID            DWORD ID for this page.
 *  fOpenStorage    BOOL indicating if we're to leave the storage
 *                  open.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CPages::PageAdd(UINT iPage, DWORD dwID, BOOL fOpenStorage)
    {
    PCPage      pPage;
    LRESULT     lr;

    pPage=new CPage(dwID, m_hWnd, this);

    if (NULL==pPage)
        return FALSE;

    //CHAPTER21MOD
    pPage->AddRef();
    //End CHAPTER21MOD

    if (fOpenStorage)
        pPage->Open(m_pIStorage);

    if (NOVALUE==iPage)
        iPage--;

    //Now try to add to the listbox.
    lr=SendMessage(m_hWndPageList, LB_INSERTSTRING, iPage+1
        , (LONG)pPage);

    if (LB_ERRSPACE==lr)
        {
        if (fOpenStorage)
            pPage->Close(FALSE);

        //CHAPTER21MOD
        pPage->Release();
        //End CHAPTER21MOD
        return FALSE;
        }

    return TRUE;
    }




//CHAPTER21MOD
/*
 * CPages::IPageGetFromID
 * (Protected)
 *
 * Purpose:
 *  Returns a page of a given identifier
 *
 * Parameters:
 *  dwID            DWORD identifier of the page to retrieve.  If
 *                  NOVALUE, then we return the current page.
 *  ppPage          PCPage * in which to return the page
 *                  pointer
 *  fOpen           BOOL indicating if we should open this page as
 *                  well.
 *
 * Return Value:
 *  UINT            Index of the page if successful, NOVALUE
 *                  otherwise.
 */

UINT CPages::IPageGetFromID(DWORD dwID, PCPage *ppPage
    , BOOL fOpen)
    {
    UINT        i;
    PCPage      pPage;

    if (NULL==ppPage)
        return FALSE;

    if ((LONG)-1==(LONG)dwID)
        {
        *ppPage=m_pPageCur;
        return m_iPageCur;
        }

    *ppPage=NULL;

    for (i=0; i < m_cPages; i++)
        {
        if (!PageGet(i, &pPage, FALSE))
            continue;

        if (pPage->GetID()==dwID)
            {
            if (fOpen)
                pPage->Open(m_pIStorage);

            *ppPage=pPage;
            return i;
            }
        }

    return NOVALUE;
    }

//End CHAPTER21MOD
