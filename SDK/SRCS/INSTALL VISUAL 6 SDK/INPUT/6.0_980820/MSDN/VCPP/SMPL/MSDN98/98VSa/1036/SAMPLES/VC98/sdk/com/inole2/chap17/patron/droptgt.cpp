/*
 * DROPTGT.CPP
 * Patron Chapter 17
 *
 * Implementation of a DropTarget object
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CDropTarget::CDropTarget
 * CDropTarget::~CDropTarget
 *
 * Constructor Parameters:
 *  pDoc            PCPatronDoc of the window containing us.
 */

CDropTarget::CDropTarget(PCPatronDoc pDoc)
    {
    m_cRef=0;
    m_pDoc=pDoc;

    m_pIDataObject=NULL;
    return;
    }


CDropTarget::~CDropTarget(void)
    {
    return;
    }




/*
 * CDropTarget::QueryInterface
 * CDropTarget::AddRef
 * CDropTarget::Release
 *
 * Purpose:
 *  IUnknown members for CDropTarget object.
 */

STDMETHODIMP CDropTarget::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IDropTarget==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CDropTarget::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CDropTarget::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }





/*
 * CDropTarget::DragEnter
 *
 * Purpose:
 *  Indicates that data in a drag operation has been dragged over
 *  our window that's a potential target.  We are to decide if it's
 *  something in which we're interested.
 *
 * Parameters:
 *  pIDataSource    LPDATAOBJECT providing the source data.
 *  grfKeyState     DWORD flags: states of keys and mouse buttons.
 *  pt              POINTL coordinates in the client space of
 *                  the document.
 *  pdwEffect       LPDWORD into which we'll place the appropriate
 *                  effect flag for this point.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CDropTarget::DragEnter(LPDATAOBJECT pIDataSource
    , DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)
    {
    PCPages         ppg=m_pDoc->m_pPG;
    HWND            hWnd;
    FORMATETC       fe;
    STGMEDIUM       stm;
    UINT            uRet;

    m_fFeedback=FALSE;
    m_pIDataObject=NULL;

    *pdwEffect=DROPEFFECT_NONE;

    //Don't allow drops on iconic documents
    if (!IsWindowVisible(m_pDoc->Window()))
        return NOERROR;

    if (!m_pDoc->FQueryPasteFromData(pIDataSource, &fe, NULL))
        return NOERROR;

    //Check if this is a valid drop point.
    uRet=ppg->UTestDroppablePoint(&pt);
    ppg->m_uLastTest=uRet;

    if (UDROP_NONE==uRet)
        *pdwEffect=DROPEFFECT_NONE;
    else
        {
        //Default is move if we can, in fact drop here.
        *pdwEffect=DROPEFFECT_MOVE;

        if (grfKeyState & MK_CONTROL)
            *pdwEffect=DROPEFFECT_COPY;
        }

    m_pIDataObject=pIDataSource;
    m_pIDataObject->AddRef();

    /*
     * Determine the size of the data, if we can.  The default is
     * a small rectangle since we can't easily tell what size
     * something will be if we're pulling in a metafile or bitmap.
     * It's not a good idea to render it here with GetData just to
     * find that out. We only know the size if it's our own object
     * in which case a GetData will be fast.
     */

    if (fe.cfFormat==m_pDoc->m_cf)
        {
        if (SUCCEEDED(pIDataSource->GetData(&fe, &stm)))
            {
            PPATRONOBJECT   ppo;
            RECT            rc;

            ppo=(PPATRONOBJECT)GlobalLock(stm.hGlobal);

            SetRect(&rc, (int)ppo->szl.cx, -(int)ppo->szl.cy, 0, 0);
            RectConvertMappings(&rc, NULL, TRUE);
            SETSIZEL(m_szl, rc.left, rc.top);

            m_ptPick=ppo->ptlPick;
            m_fe=ppo->fe;

            GlobalUnlock(stm.hGlobal);
            ReleaseStgMedium(&stm);
            }
        }
    else
        {
        SETSIZEL(m_szl, 30, 30);
        m_ptPick.x=0;
        m_ptPick.y=0;
        m_fe.cfFormat=0;

        //CHAPTER17MOD
        /*
         * Try to get CFSTR_OBJECTDESCRIPTOR which might have a size
         * and a pick point.  If it exists, then always use the
         * point but still default to a 30*30 size if the sizes
         * are zero.
         */
        uRet=RegisterClipboardFormat(CFSTR_OBJECTDESCRIPTOR);
        SETDefFormatEtc(fe, uRet, TYMED_HGLOBAL);

        if (SUCCEEDED(pIDataSource->GetData(&fe, &stm)))
            {
            LPOBJECTDESCRIPTOR  pOD;

            pOD=(LPOBJECTDESCRIPTOR)GlobalLock(stm.hGlobal);

            //Get the size, converting to LOMETRIC.
            if (0!=pOD->sizel.cx && 0!=pOD->sizel.cy)
                {
                XformSizeInHimetricToPixels(NULL, &pOD->sizel
                    , &m_szl);
                }

            //POINTL and SIZEL are interchangeable
            XformSizeInHimetricToPixels(NULL, (LPSIZEL)&pOD->pointl
                , (LPSIZEL)&m_ptPick);

            GlobalUnlock(stm.hGlobal);
            ReleaseStgMedium(&stm);
            }
        //End CHAPTER17MOD
        }


    //Bring the document window up front, show what a drop will do.
    hWnd=m_pDoc->Window();
    BringWindowToTop(hWnd);
    UpdateWindow(hWnd);

    ppg->m_uVScrollCode=NOVALUE;
    ppg->m_uHScrollCode=NOVALUE;
    m_fPendingRepaint=FALSE;

    pt.x-=m_ptPick.x;
    pt.y-=m_ptPick.y;

    m_ptLast=pt;
    m_fFeedback=TRUE;
    ppg->DrawDropTargetRect(&pt, &m_szl);

    return NOERROR;
    }






/*
 * CDropTarget::DragOver
 *
 * Purpose:
 *  Indicates that the mouse was moved inside the window represented
 *  by this drop target.  This happens on every WM_MOUSEMOVE, so
 *  this function should be very efficient.
 *
 * Parameters:
 *  grfKeyState     DWORD providing the current keyboard and
 *                  mouse states
 *  pt              POINTL where the mouse currently is.
 *  pdwEffect       LPDWORD in which to store the effect flag
 *                  for this point.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CDropTarget::DragOver(DWORD grfKeyState, POINTL pt
    , LPDWORD pdwEffect)
    {
    PCPages     ppg=m_pDoc->m_pPG;
    UINT        uRet, uLast;
    UINT        xPos, yPos;

    *pdwEffect=DROPEFFECT_NONE;

    if (NULL==m_pIDataObject)
        return NOERROR;

    //Check if this is still a valid point.  uRet used below as well
    uRet=ppg->UTestDroppablePoint(&pt);

    if (UDROP_NONE==uRet)
        *pdwEffect=DROPEFFECT_NONE;
    else
        {
        //Store these before possibly ORing in DROPEFFECT_SCROLL
        *pdwEffect=DROPEFFECT_MOVE;

        if (grfKeyState & MK_CONTROL)
            *pdwEffect=DROPEFFECT_COPY;
        }

    //If we haven't moved and we are not scrolling, then we're done.
    if ((pt.x-m_ptPick.x==m_ptLast.x)
        && (pt.y-m_ptPick.y==m_ptLast.y)
        && !((UDROP_INSETHORZ|UDROP_INSETVERT) & ppg->m_uLastTest))
        {
        return NOERROR;
        }

    //Remove the last feedback rectangle.
    if (m_fFeedback)
        ppg->DrawDropTargetRect(&m_ptLast, &m_szl);

    uLast=ppg->m_uLastTest;
    ppg->m_uLastTest=uRet;

    if (UDROP_NONE==uRet)
        {
        //If we're now an invalid point, better repaint as necessary
        if (m_fPendingRepaint)
            {
            UpdateWindow(ppg->m_hWnd);
            m_fPendingRepaint=FALSE;
            }

        ppg->m_uVScrollCode=NOVALUE;
        ppg->m_uHScrollCode=NOVALUE;
        m_fFeedback=FALSE;
        return NOERROR;
        }


    /*
     * Scrolling is a little tricky:  We get a DragOver pulse even
     * if we didn't move.  First we have to delay scrolling for
     * ppg->m_uScrollDelay clock ticks which we can determine using
     * GetTickCount.  Timers do not work here since we may not be
     * yielding to our message loop.
     *
     * Once we know we are scrolling then we determine if we
     * scroll again or if we reset the scrolling state.
     */

    if ((UDROP_INSETHORZ & uLast) && !(UDROP_INSETHORZ & uRet))
        ppg->m_uHScrollCode=NOVALUE;

    if (!(UDROP_INSETHORZ & uLast) && (UDROP_INSETHORZ & uRet))
        {
        ppg->m_dwTimeLast=GetTickCount();
        ppg->m_uHScrollCode=(0!=(UDROP_INSETLEFT & uRet))
            ? SB_LINELEFT : SB_LINERIGHT; //Same as UP & DOWN codes.
        }

    if ((UDROP_INSETVERT & uLast) && !(UDROP_INSETVERT & uRet))
        ppg->m_uVScrollCode=NOVALUE;

    if (!(UDROP_INSETVERT & uLast) && (UDROP_INSETVERT & uRet))
        {
        ppg->m_dwTimeLast=GetTickCount();
        ppg->m_uVScrollCode=(0!=(UDROP_INSETTOP & uRet))
            ? SB_LINEUP : SB_LINEDOWN;
        }

    //Only change the last time if ALL scrolling stops.
    if (NOVALUE==ppg->m_uHScrollCode && NOVALUE==ppg->m_uVScrollCode)
        ppg->m_dwTimeLast=0L;

    //Set the scroll effect on any inset hit.
    if ((UDROP_INSETHORZ | UDROP_INSETVERT) & uRet)
        *pdwEffect |= DROPEFFECT_SCROLL;

    xPos=ppg->m_xPos;
    yPos=ppg->m_yPos;

    //Has the delay elapsed?  We can scroll if so
    if (ppg->m_dwTimeLast!=0
        && (GetTickCount()-ppg->m_dwTimeLast)
        > (DWORD)ppg->m_uScrollDelay)
        {
        if (NOVALUE!=ppg->m_uHScrollCode)
            {
            m_fPendingRepaint=TRUE;
            SendMessage(ppg->m_hWnd, WM_HSCROLL
                , ppg->m_uHScrollCode, 0L);
            }

        if (NOVALUE!=ppg->m_uVScrollCode)
            {
            m_fPendingRepaint=TRUE;
            SendMessage(ppg->m_hWnd, WM_VSCROLL
                , ppg->m_uVScrollCode, 0L);
            }
        }

    //If we didn't scroll but have a pending repaint, do it now.
    if (xPos==ppg->m_xPos && yPos==ppg->m_yPos && m_fPendingRepaint)
        {
        UpdateWindow(ppg->m_hWnd);
        m_fPendingRepaint=FALSE;
        }

    pt.x-=m_ptPick.x;
    pt.y-=m_ptPick.y;

    m_ptLast=pt;
    m_fFeedback=TRUE;
    ppg->DrawDropTargetRect(&pt, &m_szl);

    return NOERROR;
    }






/*
 * CDropTarget::DragLeave
 *
 * Purpose:
 *  Informs the drop target that the operation has left its window.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CDropTarget::DragLeave(void)
    {
    PCPages         ppg=m_pDoc->m_pPG;

    if (NULL==m_pIDataObject)
        return NOERROR;

    //Stop scrolling
    ppg->m_uHScrollCode=NOVALUE;
    ppg->m_uVScrollCode=NOVALUE;

    if (m_fPendingRepaint)
        UpdateWindow(ppg->m_hWnd);

    //Remove the last feedback rectangle.
    if (m_fFeedback)
        ppg->DrawDropTargetRect(&m_ptLast, &m_szl);

    m_fFeedback=FALSE;
    m_pIDataObject->Release();
    return NOERROR;
    }





/*
 * CDropTarget::Drop
 *
 * Purpose:
 *  Instructs the drop target to paste the data that was just now
 *  dropped on it.
 *
 * Parameters:
 *  pIDataSource    LPDATAOBJECT from which we'll paste.
 *  grfKeyState     DWORD providing current keyboard/mouse state.
 *  pt              POINTL at which the drop occurred.
 *  pdwEffect       LPDWORD in which to store what you did.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CDropTarget::Drop(LPDATAOBJECT pIDataSource
    , DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)
    {
    PCPages         ppg=m_pDoc->m_pPG;
    BOOL            fRet=TRUE;
    FORMATETC       fe;
    TENANTTYPE      tType;
    PATRONOBJECT    po;
    POINT           ptS;

    *pdwEffect=DROPEFFECT_NONE;

    if (NULL==m_pIDataObject)
        return ResultFromScode(E_FAIL);

    if (UDROP_NONE==ppg->UTestDroppablePoint(&pt))
        return ResultFromScode(E_FAIL);

    //Stop scrolling
    ppg->m_uHScrollCode=NOVALUE;
    ppg->m_uVScrollCode=NOVALUE;

    if (m_fPendingRepaint)
        UpdateWindow(ppg->m_hWnd);

    //2.  Remove the UI feedback
    if (m_fFeedback)
        ppg->DrawDropTargetRect(&m_ptLast, &m_szl);

    m_pIDataObject->Release();


    /*
     * Check if we can do the paste, and if so, tell our pasting
     * mechanism exactly where to place us.
     */
    pt.x-=m_ptPick.x;
    pt.y-=m_ptPick.y;

    POINTFROMPOINTL(ptS, pt);
    ScreenToClient(ppg->Window(), &ptS);
    POINTLFROMPOINT(po.ptl, ptS);

    //This is true if we didn't see placement data in DragEnter
    if (0!=m_fe.cfFormat)
        {
        po.szl.cx=m_szl.cx;         //We stored these positive
        po.szl.cy=-m_szl.cy;
        }
    else
        SETSIZEL(po.szl, 0, 0); //Ask object for its size.

    //Adjust for scrolling and mapping mode.
    ppg->AdjustPosition(&po.ptl, &po.szl);


    /*
     * If we're in the same document and moving, then we can just
     * stuff the Pages' m_ptDrop which will move us and return.
     */
    if (ppg->m_fDragSource && !(grfKeyState & MK_CONTROL))
        {
        *pdwEffect=DROPEFFECT_MOVE;
        ppg->m_fMoveInPage=TRUE;
        ppg->m_ptDrop=po.ptl;
        return NOERROR;
        }

    /*
     * Otherwise, paste either from another document or from
     * the same document which will always be a copy to the new
     * point.
     */

    ppg->m_fMoveInPage=FALSE;
    fRet=m_pDoc->FQueryPasteFromData(pIDataSource, &fe, &tType);

    if (fRet)
        {
        //Copy the real format if we have placement data.
        po.fe=(m_pDoc->m_cf==fe.cfFormat) ? m_fe : fe;

        //CHAPTER17MOD
        //Flag PasteFromData to use CFSTR_OBJECTDESCRIPTOR
        fRet=m_pDoc->PasteFromData(pIDataSource, &fe, tType
            , &po, 0, TRUE);
        //End CHAPTER17MOD
        }

    if (!fRet)
        return ResultFromScode(E_FAIL);


    *pdwEffect=DROPEFFECT_MOVE;

    if (grfKeyState & MK_CONTROL)
        *pdwEffect=DROPEFFECT_COPY;

    return NOERROR;
    }
