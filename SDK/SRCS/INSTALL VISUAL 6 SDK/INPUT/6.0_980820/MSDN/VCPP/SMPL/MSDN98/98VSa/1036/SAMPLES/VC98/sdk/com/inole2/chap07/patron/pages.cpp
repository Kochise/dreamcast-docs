/*
 * PAGES.CPP
 * Patron Chapter 7
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
 */

CPages::CPages(HINSTANCE hInst)
    : CWindow(hInst)
    {
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

    //CHAPTER7MOD
    //m_hDevMode removed

    m_pIStorage=NULL;
    //End CHAPTER7MOD

    return;
    }


CPages::~CPages(void)
    {
    //CHAPTER7MOD
    //Ensure memory cleaned up in list; do final IStorage::Release
    StorageSet(NULL, FALSE, FALSE);
    //End CHAPTER7MOD

    if (NULL!=m_hFont && !m_fSystemFont)
        DeleteObject(m_hFont);

    if (NULL!=m_hWndPageList)
        DestroyWindow(m_hWndPageList);

    return;
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






//CHAPTER7MOD

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

        PageGet(m_iPageCur, &pPage, TRUE);
        return TRUE;
        }

    if (NULL!=m_hWndPageList)
        {
        //On new or open, clean out whatever it is we have.
        for (i=0; i < m_cPages; i++)
            {
            if (PageGet(i, &pPage, FALSE))
                delete pPage;
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

    PageGet(m_iPageCur, &pPage, TRUE);

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
    if (PageGet(m_iPageCur, &pPage, FALSE))
        {
        pPage->Update();

        if (fCloseAll)
            pPage->Close(FALSE);
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
    return fRet;
    }


//End CHAPTER7MOD






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
    //CHAPTER7MOD
    SETPOINT(pt, rc.left, rc.top);
    //End CHAPTER7MOD
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
    //CHAPTER7MOD
    PCPage      pPage;

    if (0!=m_cPages)
        {
        //Close the current page, committing changes.
        if (!PageGet(m_iPageCur, &pPage, FALSE))
            return 0;

        pPage->Close(TRUE);
        }
    //End CHAPTER7MOD

    //Create and open the new page.
    if (!PageAdd(m_iPageCur, m_dwIDNext, TRUE))
        return 0;

    m_dwIDNext++;
    m_iPageCur++;
    m_cPages++;

    InvalidateRect(m_hWnd, NULL, FALSE);
    UpdateWindow(m_hWnd);
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

    //Delete the page in storage, memory, and the listbox.
    SendMessage(m_hWndPageList, LB_DELETESTRING, m_iPageCur, 0L);

    //CHAPTER7MOD
    pPage->Destroy(m_pIStorage);
    //End CHAPTER7MOD

    delete pPage;   //Does final pPage->Close

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
        //CHAPTER7MOD
        PageGet(m_iPageCur, &pPage, TRUE);
        //End CHAPTER7MOD
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
    //CHAPTER7MOD
    PCPage  pPage;
    //End CHAPTER7MOD

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

    //CHAPTER7MOD
    //Close the old page committing changes.
    if (!PageGet(iPagePrev, &pPage, FALSE))
        return NOVALUE;

    pPage->Close(TRUE);
    //End CHAPTER7MOD

    m_iPageCur=iPageNew;

    //CHAPTER7MOD
    //Open the new page.
    PageGet(m_iPageCur, &pPage, TRUE);
    //End CHAPTER7MOD

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

//CHAPTER7MOD
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
//End CHAPTER7MOD





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

//CHAPTER7MOD
BOOL CPages::PageAdd(UINT iPage, DWORD dwID, BOOL fOpenStorage)
    {
//End CHAPTER7MOD
    PCPage      pPage;
    LRESULT     lr;

    pPage=new CPage(dwID);

    if (NULL==pPage)
        return FALSE;

    //CHAPTER7MOD
    if (fOpenStorage)
        pPage->Open(m_pIStorage);
    //End CHAPTER7MOD

    if (NOVALUE==iPage)
        iPage--;

    //Now try to add to the listbox.
    lr=SendMessage(m_hWndPageList, LB_INSERTSTRING, iPage+1
        , (LONG)pPage);

    if (LB_ERRSPACE==lr)
        {
        //CHAPTER7MOD
        if (fOpenStorage)
            pPage->Close(FALSE);
        //End CHAPTER7MOD

        delete pPage;
        return FALSE;
        }

    return TRUE;
    }
