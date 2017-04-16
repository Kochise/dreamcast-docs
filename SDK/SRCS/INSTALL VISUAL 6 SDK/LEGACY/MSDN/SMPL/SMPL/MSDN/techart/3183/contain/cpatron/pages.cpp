/*
 * PAGES.CPP
 * Patron Control Containter
 *
 * Implementation of the CPages class.  See PAGEWIN.CPP for
 * additional member functions.
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
    m_pmkFile=NULL;

    m_fAddUI=FALSE;
    //CONTROLMOD
    m_fDesignMode=FALSE;
    //End CONTROLMOD
    return;
    }


CPages::~CPages(void)
    {
    //Ensure memory cleaned up in list; do final IStorage::Release
    FIStorageSet(NULL, FALSE, FALSE);

    if (NULL!=m_pmkFile)
        m_pmkFile->Release();

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
 * CPages::FInit
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

BOOL CPages::FInit(HWND hWndParent, LPRECT pRect, DWORD dwStyle
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
     * We have to set the parent to NULL such that the window hangs
     * around after the pages window is destroyed so that we can
     * clean up the memory stored in it from the CPages destructor.
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
 * CPages::FIStorageSet
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
 *  None
 */

BOOL CPages::FIStorageSet(LPSTORAGE pIStorage, BOOL fChange
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

        FPageGet(m_iPageCur, &m_pPageCur, TRUE);
        return TRUE;
        }

    if (NULL!=m_hWndPageList)
        {
        //On new or open, clean out whatever it is we have.
        for (i=0; i < m_cPages; i++)
            {
            if (FPageGet(i, &pPage, FALSE))
                pPage->Release();
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
                    fRet &=FPageAdd(NOVALUE, *(pdwID+i), FALSE);

                pIMalloc->Free(pdwID);
                }
            }

        pIMalloc->Release();
        }

    pIStream->Release();

    if (!fRet)
        return FALSE;

    FPageGet(m_iPageCur, &m_pPageCur, TRUE);

    InvalidateRect(m_hWnd, NULL, FALSE);
    UpdateWindow(m_hWnd);

    return TRUE;
    }





/*
 * CPages::FIStorageUpdate
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

BOOL CPages::FIStorageUpdate(BOOL fCloseAll)
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
                FPageGet(i, &pPage, FALSE);
                *(pdwID+i)=pPage->GetID();
                }

            pIStream->Write(pdwID, cb, &cb);
            pIMalloc->Free(pdwID);
            fRet=TRUE;
            }
        pIMalloc->Release();
        }

    pIStream->Release();

    //Don't forget to clean up the dirty flag when we do an update.
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
    if (!FPageAdd(m_iPageCur, m_dwIDNext, TRUE))
        return 0;

    m_dwIDNext++;
    m_iPageCur++;
    m_cPages++;

    InvalidateRect(m_hWnd, NULL, FALSE);
    UpdateWindow(m_hWnd);

    FPageGet(m_iPageCur, &m_pPageCur, FALSE);
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
    //Delete the page in both the storage and in memory.
    SendMessage(m_hWndPageList, LB_DELETESTRING, m_iPageCur, 0L);

    m_pPageCur->Destroy(m_pIStorage);

    m_pPageCur->Release();   //Does final pPage->Close
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
        FPageGet(m_iPageCur, &m_pPageCur, TRUE);
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
    if (!FPageGet(iPagePrev, &pPage, FALSE))
        return NOVALUE;

    pPage->Close(TRUE);

    m_iPageCur=iPageNew;

    //Open the new page.
    FPageGet(m_iPageCur, &m_pPageCur, TRUE);

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
 * CPages::DevModeSet
 *
 * Purpose:
 *  Provides the Pages with the current printer information.
 *
 * Parameters:
 *  hDevMode        HGLOBAL to the memory containing the DEVMODE.
 *                  This function assumes responsibility for this
 *                  handle.
 *  hDevNames       HGLOBAL providing the driver name and device
 *                  name from which we can create a DC for
 *                  information.
 *
 * Return Value:
 *  BOOL            TRUE if we could accept this configuration,
 *                  FALSE otherwise.  If we return TRUE we also
 *                  delete the old memory we hold.
 */

BOOL CPages::DevModeSet(HGLOBAL hDevMode, HGLOBAL hDevNames)
    {
    LPDEVNAMES      pdn;
    LPTSTR          psz;
    HGLOBAL         hMem;
    PDEVICECONFIG   pdc;
    LPDEVMODE       pdm;
    LPSTREAM        pIStream;
    HRESULT         hr;
    ULONG           cbDevMode, cbWrite;
    BOOL            fRet=FALSE;

    if (NULL==hDevMode || NULL==hDevNames)
        return FALSE;

    hr=m_pIStorage->OpenStream(SZSTREAMDEVICECONFIG, 0, STGM_DIRECT
        | STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return FALSE;

    /*
     * DEVMODE is variable length--total length in hDevMode, so the
     * amount to write is that plus string space.  We subtract
     * sizeof(DEVMODE) as that is already included from GlobalSize.
     */
    cbDevMode=GlobalSize(hDevMode);
    cbWrite=cbDevMode+sizeof(DEVICECONFIG)-sizeof(DEVMODE);

    hMem=GlobalAlloc(GHND, cbWrite);

    if (NULL==hMem)
        {
        pIStream->Release();
        return FALSE;
        }

    pdc=(PDEVICECONFIG)GlobalLock(hMem);    //This always works
    pdm=(LPDEVMODE)GlobalLock(hDevMode);    //This might not

    if (NULL!=pdm)
        {
        pdc->cb=cbWrite;
        pdc->cbDevMode=cbDevMode;
        memcpy(&pdc->dm, pdm, (int)cbDevMode);
        GlobalUnlock(hDevMode);

        psz=(LPTSTR)GlobalLock(hDevNames);

        if (NULL!=psz)
            {
            pdn=(LPDEVNAMES)psz;
            lstrcpy(pdc->szDriver, psz+pdn->wDriverOffset);
            lstrcpy(pdc->szDevice, psz+pdn->wDeviceOffset);
            lstrcpy(pdc->szPort,   psz+pdn->wOutputOffset);

            pIStream->Write(pdc, cbWrite, &cbWrite);
            GlobalUnlock(hDevNames);
            fRet=TRUE;
            }
        }

    GlobalUnlock(hMem);
    GlobalFree(hMem);

    pIStream->Release();

    if (!fRet)
        return FALSE;

    GlobalFree(hDevNames);
    GlobalFree(hDevMode);

    return ConfigureForDevice();
    }






/*
 * CPages::DevModeGet
 *
 * Purpose:
 *  Retrieves a copy of the current DEVMODE structure for this
 *  Pages window.  The caller is responsible for this memory.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HGLOBAL         Handle to the memory containing the DEVMODE
 *                  structure.
 */

HGLOBAL CPages::DevModeGet(void)
    {
    HGLOBAL         hMem;
    LPVOID          pv;
    ULONG           cbDevMode, cbRead;
    LARGE_INTEGER   li;
    LPSTREAM        pIStream;
    HRESULT         hr;

    hr=m_pIStorage->OpenStream(SZSTREAMDEVICECONFIG, 0, STGM_DIRECT
        | STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return FALSE;

    //Read how much to allocate for the DEVMODE structure
    LISet32(li, CBSEEKOFFSETCBDEVMODE);
    pIStream->Seek(li, STREAM_SEEK_SET, NULL);
    pIStream->Read(&cbDevMode, sizeof(ULONG), &cbRead);

    hMem=GlobalAlloc(GHND, cbDevMode);

    if (NULL!=hMem)
        {
        pv=(LPVOID)GlobalLock(hMem);
        pIStream->Read(pv, cbDevMode, &cbRead);
        GlobalUnlock(hMem);
        }

    pIStream->Release();
    return hMem;
    }




/*
 * CPages::DevReadConfig
 *
 * Purpose:
 *  Public function to read the current device configuration and
 *  optionally return an information context for it.
 *
 *
 * Parameters:
 *  ppcd            PCOMBINEDEVICE * in which to return a pointer
 *                  to an allocated structure that has all the
 *                  device information we want.  Ignored if NULL.
 *                  This is allocated with the task allocator.
 *  phDC            HDC * in which to return the information
 *                  context.  If NULL, no IC is created.  Caller
 *                  becomes responsible for the returned IC.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPages::DevReadConfig(PCOMBINEDEVICE *ppcd, HDC *phDC)
    {
    HRESULT         hr;
    LPSTREAM        pIStream;
    LPMALLOC        pIMalloc;
    PCOMBINEDEVICE  pcd;
    ULONG           cb, cbRead;
    LARGE_INTEGER   li;

    hr=m_pIStorage->OpenStream(SZSTREAMDEVICECONFIG, 0, STGM_DIRECT
        | STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return FALSE;

    /*
     * Allocate the COMBINEDEVICE structure including the variable
     * information past the DEVMODE part.
     */

    hr=CoGetMalloc(MEMCTX_TASK, &pIMalloc);

    if (FAILED(hr))
        {
        pIStream->Release();
        return FALSE;
        }

    /*
     * Read size of the DEVICECONFIG structure including variable
     * portion of DEVMODE.  We need to load all this information
     * for CreateIC.  To this size we'll add the size of
     * DVTARGETDEVICE in order to allocate a COMBINEDEVICE.
     */

    pIStream->Read(&cb, sizeof(DWORD), &cbRead);

    pcd=(PCOMBINEDEVICE)pIMalloc->Alloc(cb+sizeof(DVTARGETDEVICE));

    if (NULL==pcd)
        {
        pIMalloc->Release();
        pIStream->Release();
        return FALSE;
        }

    //Now get the real information.
    LISet32(li, 0);
    pIStream->Seek(li, STREAM_SEEK_SET, NULL);
    pIStream->Read(&(pcd->dc), cb, &cbRead);
    pIStream->Release();


    /*
     * If requested, complete the DVTARGETDEVICE structure in
     * pcd and store pcd in *ppcd for return.
     */

    if (NULL!=ppcd)
        {
        WORD    cb=sizeof(DVTARGETDEVICE);

        pcd->td.tdSize=cb;
        pcd->td.tdExtDevmodeOffset=cb;
        pcd->td.tdDriverNameOffset=cb+sizeof(DEVMODE);
        pcd->td.tdDeviceNameOffset=cb+sizeof(DEVMODE)
            +(CCHDEVICENAME*sizeof(TCHAR));
        pcd->td.tdPortNameOffset  =cb+sizeof(DEVMODE)
            +(CCHDEVICENAME*2*sizeof(TCHAR));

        *ppcd=pcd;
        }

    //Create an IC if requested.
    if (NULL!=phDC)
        {
        //Get the DC then configure
        *phDC=CreateIC(pcd->dc.szDriver, pcd->dc.szDevice
            , pcd->dc.szPort, &(pcd->dc.dm));

        if (NULL==*phDC)
            return FALSE;
        }

    //pcd is a temporary allocation in this case
    if (NULL==ppcd)
        pIMalloc->Free(pcd);

    pIMalloc->Release();
    return (NULL!=*phDC);
    }





/*
 * CPages::ConfigureForDevice
 *
 * Purpose:
 *  Recalculates our drawing configuration based on the contents of
 *  an hDC.  If no HDC is given we use the contents of our DevMode
 *  stream.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPages::ConfigureForDevice(void)
    {
    POINT           ptOffset, ptPaper;
    RECT            rc;
    HDC             hDC;

    if (!DevReadConfig(NULL, &hDC))
        return FALSE;

    //Get usable page dimensions:  already sensitive to orientation
    m_cx=GetDeviceCaps(hDC, HORZSIZE)*10-16; //*10: mm to LOMETRIC
    m_cy=GetDeviceCaps(hDC, VERTSIZE)*10-16; //-16: for driver bugs.

    //Calculate the printer-limited margins on each side in LOMETRIC
    Escape(hDC, GETPRINTINGOFFSET, NULL, NULL, &ptOffset);
    Escape(hDC, GETPHYSPAGESIZE,   NULL, NULL, &ptPaper);

    SetRect(&rc, ptOffset.x, ptOffset.y, ptPaper.x, ptPaper.y);
    SetMapMode(hDC, MM_LOMETRIC);
    RectConvertMappings(&rc, hDC, FALSE);

    //Left and top margins are the printing offset.
    m_xMarginLeft= rc.left+8;   //+8 to match -16 above
    m_yMarginTop =-rc.top+8;    //LOMETRIC makes this negative.

    //Right is (paper width)-(usable width)-(left margin)
    m_xMarginRight =rc.right-m_cx-m_xMarginLeft;

    //Bottom is (paper height)-(usable height)-(top margin)+1
    m_yMarginBottom=-rc.bottom-m_cy-m_yMarginTop+1;

    UpdateScrollRanges();

    DeleteDC(hDC);
    return TRUE;
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
 *  pMSG            LPMSG to whatever invoked the verb.
 *
 * Return Value:
 *  None
 */

void CPages::ActivateObject(LONG iVerb, LPMSG pMSG)
    {
    if (NULL==m_pPageCur)
        return;

    m_pPageCur->ActivateObject(iVerb, pMSG);
    return;
    }




//CONTROLMOD
/*
 * CPages::ToggleDesignMode
 *
 * Purpose:
 *  Pass-through to CPage::ToggleDesignMode
 *
 * Parameters:
 *  fDesign         BOOL indicating the mode
 *
 * Return Value:
 *  None
 */

void CPages::ToggleDesignMode(BOOL fDesign)
    {
    if (NULL==m_pPageCur)
        return;

    m_fDesignMode=fDesign;
    m_pPageCur->ToggleDesignMode(fDesign);
    return;
    }


/*
 * CPages::FQueryEnableEvents
 *
 * Purpose:
 *  Determines whether or not the Edit Events menu item should be
 *  enabled on the frame window menu.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE to enable the item, FALSE otherwise.
 */

BOOL CPages::FQueryEnableEvents(void)
    {
    if (NULL==m_pPageCur)
        return FALSE;

    return m_pPageCur->FQueryEnableEvents();
    }


/*
 * CPages::AssignEvents
 *
 * Purpose:
 *  Pass-through to CPage::AssignEvents
 *
 * Parameters:
 *  hWndParent      HWND to use as the dialog parent.
 *
 * Return Value:
 *  None
 */

void CPages::AssignEvents(HWND hWndParent)
    {
    if (NULL!=m_pPageCur)
        m_pPageCur->AssignEvents(hWndParent);

    return;
    }

//End CONTROLMOD




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

    if (NULL!=m_pmkFile)
        m_pmkFile->Release();

    m_pmkFile=pmk;
    m_pmkFile->AddRef();
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
 * CPages::FGetUILinkContainer
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

BOOL CPages::FGetUILinkContainer(PCIOleUILinkContainer *ppObj)
    {
    PCIOleUILinkContainer   pObj;

    *ppObj=NULL;

    if (NULL==m_pPageCur)
        return FALSE;

    pObj=new CIOleUILinkContainer(m_pPageCur);

    if (NULL==pObj)
        return FALSE;

    if (!pObj->FInit())
        {
        delete pObj;
        return FALSE;
        }

    pObj->AddRef();
    *ppObj=pObj;
    return TRUE;
    }




/*
 * CPages::FConvertObject
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

BOOL CPages::FConvertObject(HWND hWndFrame)
    {
    if (NULL==m_pPageCur)
        return FALSE;

    return m_pPageCur->FConvertObject(hWndFrame, FALSE);
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
 * CPages::FPageGet
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

BOOL CPages::FPageGet(UINT iPage, PCPage *ppPage, BOOL fOpen)
    {
    if (NULL==ppPage)
        return FALSE;

    if (LB_ERR!=SendMessage(m_hWndPageList, LB_GETTEXT
        , iPage, (LONG)ppPage))
        {
        if (fOpen)
            (*ppPage)->FOpen(m_pIStorage);

        return TRUE;
        }

    return FALSE;
    }






/*
 * CPages::FPageAdd
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

BOOL CPages::FPageAdd(UINT iPage, DWORD dwID, BOOL fOpenStorage)
    {
    PCPage      pPage;
    LRESULT     lr;

    pPage=new CPage(dwID, m_hWnd, this);

    if (NULL==pPage)
        return FALSE;

    pPage->AddRef();

    if (fOpenStorage)
        pPage->FOpen(m_pIStorage);

    if (NOVALUE==iPage)
        iPage--;

    //Now try to add to the listbox.
    lr=SendMessage(m_hWndPageList, LB_INSERTSTRING, iPage+1
        , (LONG)pPage);

    if (LB_ERRSPACE==lr)
        {
        if (fOpenStorage)
            pPage->Close(FALSE);

        pPage->Release();
        return FALSE;
        }

    return TRUE;
    }




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
        if (!FPageGet(i, &pPage, FALSE))
            continue;

        if (pPage->GetID()==dwID)
            {
            if (fOpen)
                pPage->FOpen(m_pIStorage);

            *ppPage=pPage;
            return i;
            }
        }

    return NOVALUE;
    }
