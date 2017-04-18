/*
 * PAGEMOUS.CPP
 * Patron Chapter 17
 *
 * Implementation of mouse-related member functions of CPage.
 * The remainder is in PAGE.CPP.  This separate file keeps this
 * grungy hit-testing/drawing code out of our way.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


//Lookups into the array using g_rgHTCode[x+y*3] in PAGEMOUS.CPP
#define YTOP            0
#define YMID            1
#define YBOT            2
#define XLEFT           0
#define XMID            1
#define XRIGHT          2

//Values to restrict sizing in CPage::OnMouseMove
#define SIZINGTOP       0x0001
#define SIZINGBOTTOM    0x0002
#define SIZINGLEFT      0x0004
#define SIZINGRIGHT     0x0008


//This array is for hit-testing lookups
static UINT g_rgHTCode[9]={HTTOPLEFT, HTTOP, HTTOPRIGHT
    , HTLEFT, HTCLIENT, HTRIGHT, HTBOTTOMLEFT, HTBOTTOM
    , HTBOTTOMRIGHT};


//This is for restricting tracking based on the hit-test
static UINT g_rguSizingFlags[9]={SIZINGTOP | SIZINGLEFT, SIZINGTOP
    , SIZINGTOP | SIZINGRIGHT, SIZINGLEFT, 0, SIZINGRIGHT
    , SIZINGBOTTOM | SIZINGLEFT, SIZINGBOTTOM
    , SIZINGBOTTOM | SIZINGRIGHT};



//CHAPTER17MOD
/*
 * CPage::OnRightDown
 *
 * Purpose:
 *  Called when the user clicks with the right button on this
 *  page.  If there is an object here, determined by the last
 *  hit-test code, the we'll make a popup-menu for it.
 *
 * Parameters:
 *  uKeys           UINT carrying the key state.
 *  x, y            UINT coordinates of the click in device units.
 *
 * Return Value:
 *  BOOL            Indicates if the action changed the object.
 */

BOOL CPage::OnRightDown(UINT uKeys, UINT x, UINT y)
    {
    HMENU       hMenu;
    HMENU       hMenuRes;
    HINSTANCE   hInst;
    HWND        hWndFrame, hWndT;
    POINT       pt;
    UINT        i, cItems;

    //Select the tenant under the mouse, if there is one.
    if (!SelectTenantAtPoint(x, y))
        return FALSE;

    /*
     * Get the top-level window to which menu command will go.  This
     * will be whatever parent doesn't have a parent itself...
     */
    hWndT=GetParent(m_hWnd);

    while (NULL!=hWndT)
        {
        hWndFrame=hWndT;
        hWndT=GetParent(hWndT);
        }

    /*
     * Build a popup menu for this object with Cut, Copy, Delete,
     * and object verbs.
     */
    hInst=GETWINDOWINSTANCE(m_hWnd);    //Macro in BOOK1632.H
    hMenuRes=LoadMenu(hInst, MAKEINTRESOURCE(IDR_RIGHTPOPUPMENU));

    if (NULL==hMenuRes)
        return FALSE;

    hMenu=CreatePopupMenu();
    cItems=GetMenuItemCount(hMenuRes);

    for (i=0; i < cItems; i++)
        {
        TCHAR       szTemp[80];
        int         id, uFlags;

        GetMenuString(hMenuRes, i, szTemp, sizeof(szTemp)
            , MF_BYPOSITION);
        id=GetMenuItemID(hMenuRes, i);

        uFlags=(0==id) ? MF_SEPARATOR : MF_STRING | MF_ENABLED;
        AppendMenu(hMenu, uFlags, id, szTemp);
        }

    DestroyMenu(hMenuRes);

    //Munge the Object menu item
    m_pTenantCur->AddVerbMenu(hMenu, MENUPOS_OBJECTONPOPUP);

    SETPOINT(pt, x, y);
    ClientToScreen(m_hWnd, &pt);

    TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON
        , pt.x, pt.y, 0, hWndFrame, NULL);

    DestroyMenu(hMenu);
    return FALSE;
    }




/*
 * CPage::SelectTenantAtPoint
 *
 * Purpose:
 *  Selects whatever tenant is at the point (x,y) if there is one,
 *  deselecting the previously selected tenant.
 *
 * Parameters:
 *  x, y            UINT coordinates of the mouse.
 *
 * Return Value:
 *  BOOL            TRUE if there is a tenant here, FALSE otherwise.
 */

BOOL CPage::SelectTenantAtPoint(UINT x, UINT y)
    {
    UINT            iTenant;
    PCTenant        pTenant;
    PCDocument      pDoc;

    iTenant=TenantFromPoint(x, y, &pTenant);

    if (NULL==pTenant)
        return FALSE;

    //Make the document window active in any case
    pDoc=(PCDocument)SendMessage(GetParent(m_hWnd), DOCM_PDOCUMENT
        , 0, 0L);

    if (NULL!=pDoc)
        BringWindowToTop(pDoc->Window());

    //If this one is already current, we might be now sizing.
    if (pTenant==m_pTenantCur)
        return TRUE;

    //Deselect the current tenant
    if (NULL!=m_pTenantCur)
        m_pTenantCur->Select(FALSE);

    //Move this tenant to the top of the list
    m_iTenantCur=0;

    SendMessage(m_hWndTenantList, LB_DELETESTRING, iTenant, 0L);
    SendMessage(m_hWndTenantList, LB_INSERTSTRING, 0
        , (LONG)pTenant);

    //Select and repaint the new tenant to show it up front
    m_pTenantCur=pTenant;

    m_pTenantCur->Repaint();
    m_pTenantCur->Select(TRUE);

    return TRUE;
    }

//End CHAPTER17MOD




/*
 * CPage::OnLeftDown
 *
 * Purpose:
 *  Called when the user clicks with the left button on this page.
 *  We find the object under that position that is visibly on top
 *  (always the first one under this location in the page list since
 *  we paint in reverse order) and select it.
 *
 * Parameters:
 *  uKeys           UINT carrying the key state.
 *  x, y            UINT coordinates of the click in device units.
 *
 * Return Value:
 *  BOOL            Indicates if the action changed the object.
 */

BOOL CPage::OnLeftDown(UINT uKeys, UINT x, UINT y)
    {
    /*
     * If the mouse is in a position to start dragging,
     * start the timer as with sizing below.
     */
    if (HTCAPTION==m_uHTCode)
        {
        m_fDragPending=TRUE;

        //Save down point and start timer.
        m_ptDown.x=x;
        m_ptDown.y=y;

        m_uKeysDown=uKeys;

        m_fTimer=TRUE;
        SetTimer(m_hWnd, IDTIMER_DEBOUNCE, m_cDelay, NULL);
        return FALSE;
        }

    /*
     * If the mouse is in a position to start sizing, start
     * the debounce timer and note the condition.  The sizing
     * will start in OnTimer or OnMouseMove.  This will always
     * happen on the currently selected tenant, and m_uHTCode is
     * set in OnNCHitTest below.
     */
    if (HTNOWHERE!=m_uHTCode && HTCLIENT!=m_uHTCode)
        {
        m_fSizePending=TRUE;

        //Save down point and start timer.
        m_ptDown.x=x;
        m_ptDown.y=y;

        m_fTimer=TRUE;
        SetTimer(m_hWnd, IDTIMER_DEBOUNCE, m_cDelay, NULL);
        return FALSE;
        }

    //CHAPTER17MOD
    //Selection logic moved to a function so OnRightDown can use it.
    SelectTenantAtPoint(x, y);
    //End CHAPTER17MOD

    return FALSE;
    }






/*
 * CPage::OnLeftUp
 *
 * Purpose:
 *  Called when the user clicks up with the left button on this
 *  page. We stop tracking on this message, if necessary, and
 *  resize the object.
 *
 * Parameters:
 *  uKeys           UINT carrying the key state.
 *  x, y            UINT coordinates of the click in device units.
 *
 * Return Value:
 *  BOOL            Indicates if this action changed the object.
 */

BOOL CPage::OnLeftUp(UINT uKeys, UINT x, UINT y)
    {
    RECT    rc, rcT;

    if (m_fSizePending || m_fDragPending)
        {
        m_fSizePending=FALSE;
        m_fDragPending=FALSE;

        if (m_fTimer)
            {
            KillTimer(m_hWnd, IDTIMER_DEBOUNCE);
            m_fTimer=FALSE;
            }

        return FALSE;
        }

    if (!m_fTracking)
        return FALSE;

    //Remove the dotted rectangle.
    RECTFROMRECTL(rc, m_rcl)
    DrawFocusRect(m_hDC, &rc);
    ReleaseDC(m_hWnd, m_hDC);

    ReleaseCapture();
    m_fTracking=FALSE;

    //If the original and new rects are the same, nothing happened.
    RECTFROMRECTL(rcT, m_rclOrg);

    if (EqualRect(&rc, &rcT))
        return FALSE;

    RECTFROMRECTL(rcT, m_rclOrg);
    InvalidateRect(m_hWnd, &rcT, TRUE);

    //Invalidate on the screen before accounting for scrolling
    InvalidateRect(m_hWnd, &rc, TRUE);

    //Factor in scrolling and tell the tenant where it now stands.
    OffsetRect(&rc, (int)m_pPG->m_xPos, (int)m_pPG->m_yPos);
    RECTLFROMRECT(m_rcl, rc);
    //CHPATER17MOD
    m_pTenantCur->RectSet(&m_rcl, TRUE, TRUE);
    //End CHAPTER17MOD

    UpdateWindow(m_hWnd);
    return TRUE;
    }





/*
 * CPage::OnLeftDoubleClick
 *
 * Purpose:
 *  Called when the user double-clicks with the left button on this
 *  page.  We find the object under that position that is visibly on
 *  top (always the first one under this location in the page list
 *  since we paint in reverse order) and activate it.
 *
 * Parameters:
 *  uKeys           UINT carrying the key state.
 *  x, y            UINT coordinates of the click in device units.
 *
 * Return Value:
 *  BOOL            Indicates if the action changed the object.
 */

BOOL CPage::OnLeftDoubleClick(UINT uKeys, UINT x, UINT y)
    {
    /*
     * The current tenant is the only one that can be activated, so
     * we just have to make sure the mouse is there.  For that we
     * can use the last hit-test code we saw since it's updated on
     * every mouse move.
     */

    if (HTNOWHERE!=m_uHTCode)
        return m_pTenantCur->Activate(OLEIVERB_PRIMARY);

    return FALSE;
    }






/*
 * CPage::OnMouseMove
 *
 * Purpose:
 *  Processes WM_MOUSEMOVE on a page so we can handle tracking
 *  resize of a tenant.
 *
 * Parameters:
 *  x, y            int device coordinates to check.
 *
 * Return Value:
 *  None
 */

void CPage::OnMouseMove(UINT uKeys, int x, int y)
    {
    RECT        rc, rcO, rcB;
    int         cxy;

    if (m_fSizePending || m_fDragPending)
        {
        int     dx, dy;

        dx=(x > m_ptDown.x) ? (x-m_ptDown.x) : (m_ptDown.x-x);
        dy=(y > m_ptDown.y) ? (y-m_ptDown.y) : (m_ptDown.y-y);

        /*
         * Has the mouse moved outside the debounce distance?  If
         * so, we can start sizing.  Note that this happens
         * regardless of the timer state.
         */
        if (dx > m_cxyDist || dy > m_cxyDist)
            {
            POINT       pt;
            BOOL        fSize=m_fSizePending;
            BOOL        fDrag=m_fDragPending;

            m_fSizePending=FALSE;
            m_fDragPending=FALSE;

            if (m_fTimer)
                {
                KillTimer(m_hWnd, IDTIMER_DEBOUNCE);
                m_fTimer=FALSE;
                }

            if (fDrag)
                {
                //Set dirty flag if drag & drop changed things.
                m_pPG->m_fDirty |= DragDrop(m_uKeysDown, x, y);
                return;
                }

            if (fSize)
                StartSizeTracking();

            /*
             * Since we might have moved out of the sizing handle
             * in order to start the operation, we need to set the
             * m_uSizingFlags field based on the original down point
             * for subsequent mouse moves to function properly.
             * Note that OnNCHitTest expects screen coordinates.
             */
            SETPOINT(pt, m_ptDown.x, m_ptDown.y);
            ClientToScreen(m_hWnd, &pt);
            OnNCHitTest(pt.x, pt.y);
            OnSetCursor(m_uHTCode);
            return;
            }
        }

    if (!m_fTracking)
        return;

    //Get rid of the old rectangle.
    RECTFROMRECTL(rc, m_rcl)
    DrawFocusRect(m_hDC, &rc);

    /*
     * Calculate the new.  The flags in m_uSizingFlags tell us what
     * to change.  We limit the object by the page margins and a
     * minimum size of 3*CXYHANDLE in either dimension.
     */
    cxy=3*CXYHANDLE;

    RECTFROMRECTL(rcO, m_rclOrg);
    RECTFROMRECTL(rcB, m_rclBounds);

    if (m_uSizingFlags & SIZINGTOP)
        {
        if (y >= rcO.bottom-cxy)
            y=rcO.bottom-cxy;

        if (y <= rcB.top)           //Limit to top of page.
            y=rcB.top;

        m_rcl.top=y;
        }

    if (m_uSizingFlags & SIZINGBOTTOM)
        {
        if (y <= rcO.top+cxy)
            y=rcO.top+cxy;

        if (y >= rcB.bottom)         //Limit to bottom of page.
            y=rcB.bottom;

        m_rcl.bottom=y;
        }

    if (m_uSizingFlags & SIZINGLEFT)
        {
        if (x >= rcO.right-cxy)
            x=rcO.right-cxy;

        if (x <= rcB.left)           //Limit to left of page.
            x=rcB.left;

        m_rcl.left=x;
        }

    if (m_uSizingFlags & SIZINGRIGHT)
        {
        if (x <= rcO.left+cxy)
            x=rcO.left+cxy;

        if (x >= rcB.right)          //Limit to right of page.
            x=rcB.right;

        m_rcl.right=x;
        }


    //Draw the new
    RECTFROMRECTL(rc, m_rcl)
    DrawFocusRect(m_hDC, &rc);

    return;
    }




/*
 * CPage::OnTimer
 *
 * Purpose:
 *  Processes WM_TIMER messages to a page used to perform mouse
 *  debouncing.
 *
 * Parameters:
 *  uID             UINT timer ID.
 *
 * Return Value:
 *  None
 */

void CPage::OnTimer(UINT uID)
    {
    if (m_fSizePending || m_fDragPending)
        {
        BOOL        fSize=m_fSizePending;
        BOOL        fDrag=m_fDragPending;

        /*
         * Having this function called means the delay requirement
         * is satisfied.  Start tracking for sizing or dragging.
         */

        m_fSizePending=FALSE;
        m_fDragPending=FALSE;

        KillTimer(m_hWnd, IDTIMER_DEBOUNCE);
        m_fTimer=FALSE;

        if (fDrag)
            {
            POINT       pt;

            GetCursorPos(&pt);
            m_pPG->m_fDirty |= DragDrop(m_uKeysDown
                , m_ptDown.x, m_ptDown.y);
            return;
            }

        if (fSize)
            StartSizeTracking();
        }

    return;
    }





/*
 * CPage::StartSizeTracking
 *
 * Purpose:
 *  Begins sizing of a tenant when mouse debounce conditions are
 *  met.
 *
 * Parameters:
 *  uID             UINT timer ID.
 *
 * Return Value:
 *  None
 */

void CPage::StartSizeTracking(void)
    {
    RECT        rc;

    m_pTenantCur->RectGet(&m_rcl, TRUE);
    SetCapture(m_hWnd);
    m_fTracking=TRUE;

    m_hDC=GetDC(m_hWnd);

    //Place the rectangle exactly where it is on the screen.
    RECTFROMRECTL(rc, m_rcl)
    OffsetRect(&rc, -(int)m_pPG->m_xPos, -(int)m_pPG->m_yPos);
    RECTLFROMRECT(m_rcl, rc);
    m_rclOrg=m_rcl;

    DrawFocusRect(m_hDC, &rc);

    m_pPG->CalcBoundingRect(&rc, TRUE);
    RECTLFROMRECT(m_rclBounds, rc);
    return;
    }





/*
 * CPage::OnNCHitTest
 *
 * Purpose:
 *  Processes WM_NCHITTEST on a page so we can check for hits on the
 *  handles of the selected object for resizing.  We only save
 *  information for ourselves and do not interfere with normal
 *  hit-testing.
 *
 * Parameters:
 *  x, y            UINT device coordinates to check.
 *
 * Return Value:
 *  None
 */

void CPage::OnNCHitTest(UINT x, UINT y)
    {
    RECT        rc;
    RECTL       rcl;
    int         iMid1, iMid2;
    int         xHit, yHit;
    POINT       pt;
    int         x0, y0;

    /*
     * Ignore this message if it occurs during tracking to adjust
     * for the behavior of oddball mouse drivers.
     */
    if (m_fSizePending || m_fTracking)
        return;

    //Default: don't start sizing on a click, don't hit an object.
    m_uSizingFlags=0;
    m_uHTCode=HTNOWHERE;

    if (NULL==m_pTenantCur)
        return;

    //Convert device points to our coordinates
    m_pTenantCur->RectGet(&rcl, FALSE);
    RECTFROMRECTL(rc, rcl);
    RectConvertMappings(&rc, NULL, TRUE);
    OffsetRect(&rc, -(int)m_pPG->m_xPos, -(int)m_pPG->m_yPos);

    SETPOINT(pt, x, y);
    ScreenToClient(m_hWnd, &pt);
    x0=pt.x;
    y0=pt.y;

    if (x0 < rc.left || x0 > rc.right)
        return;

    if (y0 < rc.top || y0 > rc.bottom)
        return;

    //It's at least in the object.
    m_uHTCode=HTCLIENT;

    //Check for hits in horizontal regions
    xHit=NOVALUE;
    iMid1=rc.left+((rc.right-rc.left-CXYHANDLE) >> 1);
    iMid2=rc.left+((rc.right-rc.left+CXYHANDLE) >> 1);

    if (x0 >= rc.left && x0 <= rc.left+CXYHANDLE)
        xHit=XLEFT;
    else if (x0 >= iMid1 && x0 <= iMid2)
        xHit=XMID;
    else if (x0 >= rc.right-CXYHANDLE && x0 <= rc.right)
        xHit=XRIGHT;

    //Don't exit yet if we didn't hit a handle--might hit a y edge.

    //Check for hits in vertical regions
    yHit=NOVALUE;
    iMid1=rc.top+((rc.bottom-rc.top-CXYHANDLE) >> 1);
    iMid2=rc.top+((rc.bottom-rc.top+CXYHANDLE) >> 1);

    if (y0 >= rc.top && y0 <= rc.top+CXYHANDLE)
        yHit=YTOP;
    else if (y0 >= iMid1 && y0 <= iMid2)
        yHit=YMID;
    else if (y0 >= rc.bottom-CXYHANDLE && y0 <= rc.bottom)
        yHit=YBOT;

    /*
     * If we hit any edge, but didn't hit a handle, then one of xHit
     * and yHit will be NOVALUE and the other something else.  When
     * we hit an edge on the 'something else' then we're on a drag
     * point.
     */

    if ((NOVALUE==xHit && NOVALUE==yHit)
        || (XMID==xHit && YMID==yHit)
        || (NOVALUE==xHit && YMID==yHit)
        || (XMID==xHit && NOVALUE==yHit))
        return;

    if ((NOVALUE==xHit && (YTOP==yHit || YBOT==yHit))
        || ((XLEFT==xHit || XRIGHT==xHit) && NOVALUE==yHit))
        {
        m_uHTCode=HTCAPTION;
        return;
        }

    //We hit a handle, so save our HT code
    m_uSizingFlags=g_rguSizingFlags[xHit+(yHit*3)];
    m_uHTCode=g_rgHTCode[xHit+(yHit*3)];
    return;
    }





/*
 * CPage::SetCursor
 *
 * Purpose:
 *  Processes WM_SETCURSOR using the code from OnNCHitTest.
 *
 * Parameters:
 *  x, y            UINT device coordinates to check.
 *
 * Return Value:
 *  LRESULT         HT* code for Windows.
 */

BOOL CPage::OnSetCursor(UINT uHTCode)
    {
    HCURSOR     hCur;
    UINT        iCur;

    /*
     * We really just ignore uHTCode and use the one we saved
     * in OnNCHitTest.
     */

    switch (m_uHTCode)
        {
        case HTTOP:
        case HTBOTTOM:
            iCur=IDC_VARROWS;
            break;

        case HTLEFT:
        case HTRIGHT:
            iCur=IDC_HARROWS;
            break;


        case HTTOPLEFT:
        case HTBOTTOMRIGHT:
            iCur=IDC_NWSEARROWS;
            break;

        case HTTOPRIGHT:
        case HTBOTTOMLEFT:
            iCur=IDC_NESWARROWS;
            break;

        case HTCAPTION:
            iCur=IDC_SMALLARROWS;
            break;

        default:
            return FALSE;
        }

    hCur=UICursorLoad(iCur);
    SetCursor(hCur);

    return TRUE;
    }





/*
 * CPage::TenantFromPoint
 * (Protected)
 *
 * Purpose:
 *  Finds the tenant under the given device coordinates on this
 *  page.
 *
 * Parmeters:
 *  x, y            UINT coordinates.
 *  ppTenant        PCTenant * in which to return the pointer.
 *
 * Return Value:
 *  UINT            Index of the matched tenant, NOVALUE if not
 *                  found.
 */

UINT CPage::TenantFromPoint(UINT x, UINT y, PCTenant *ppTenant)
    {
    PCTenant    pTenant;
    RECTL       rcl;
    UINT        i;
    int         x0, y0;

    x0=x+m_pPG->m_xPos;
    y0=y+m_pPG->m_yPos;

    for (i=0; i < m_cTenants; i++)
        {
        if (!TenantGet(i, &pTenant, FALSE))
            continue;

        pTenant->RectGet(&rcl, TRUE);

        //Essentially Perform PointInRECTL
        if (x0 >= rcl.left && x0 <= rcl.right)
            {
            if (y0 <=rcl.bottom && y0 >=rcl.top)
                {
                *ppTenant=pTenant;
                return i;
                }
            }
        }

    *ppTenant=NULL;
    return NOVALUE;
    }







/*
 * CPage::DragDrop
 *
 * Purpose:
 *  Performs drag-drop operations from the page window
 *
 * Parmeters:
 *  uKeys           UINT state of the keyboard
 *  x, y            UINT mouse coordinates of the starting click.
 *
 * Return Value:
 *  BOOL            TRUE if we modified the page, FALSE otherwise.
 */

BOOL CPage::DragDrop(UINT uKeys, UINT x, UINT y)
    {
    LPDROPSOURCE    pIDropSource;
    LPDATAOBJECT    pIDataObject;
    HRESULT         hr;
    DWORD           dwEffect;
    POINTL          ptl;
    SIZEL           szl;
    RECTL           rcl;
    RECT            rc, rcT;

    pIDropSource=new CDropSource();

    if (NULL==pIDropSource)
        return FALSE;

    pIDropSource->AddRef();
    m_pPG->m_fDragSource=TRUE;


    /*
     * Store a pick point with the data indicating the offset from
     * the upper left of the rectangle where we grabbed it.  This is
     * so the UI feedback in IDropTarget lines up with this tenant.
     */

    m_pTenantCur->RectGet(&rcl, TRUE);
    ptl.x=x+m_pPG->m_xPos-rcl.left;
    ptl.y=y+m_pPG->m_yPos-rcl.top;
    pIDataObject=TransferObjectCreate(&ptl);

    if (NULL==pIDataObject)
        {
        pIDropSource->Release();
        return FALSE;
        }

    m_pPG->m_fMoveInPage=FALSE;

    dwEffect=DROPEFFECT_COPY | DROPEFFECT_MOVE;
    hr=DoDragDrop(pIDataObject, pIDropSource
        , DROPEFFECT_COPY | DROPEFFECT_MOVE, &dwEffect);

    pIDataObject->Release();
    pIDropSource->Release();

    m_pPG->m_fDragSource=FALSE;

    //No drop-no action.
    if (DRAGDROP_S_DROP!=GetScode(hr) || DROPEFFECT_NONE==dwEffect)
        return FALSE;

    /*
     * If m_pPG->m_fMoveInPage is set, then we just change the
     * coordinates on m_pTenantCur and we're done.
     */
    if (m_pPG->m_fMoveInPage)
        {
        m_pTenantCur->Invalidate();

        /*
         * Clip to page boundaries.  We know that ptDrop has to be
         * in the page somewhere or we would not have dropped
         * (effect was NONE).  So first make sure that ptDrop is
         * within 3*CXYHANDLE of the right or bottom, and if so,
         * pull it out to 3*CXYHANDLE.  Then we can just clip the
         * size to the page rectangle and we'll always be sure to
         * have at least a sizeable object.
         */
        m_pTenantCur->SizeGet(&szl, TRUE);
        SetRect(&rc, (int)m_pPG->m_ptDrop.x, (int)m_pPG->m_ptDrop.y
            , 0, 0);
        RectConvertMappings(&rc, NULL, TRUE);

        m_pPG->CalcBoundingRect(&rcT, FALSE);
        OffsetRect(&rcT, (int)m_pPG->m_xPos, (int)m_pPG->m_yPos);

        if (rc.left >= rcT.right-3*CXYHANDLE)
            rc.left=rcT.right-3*CXYHANDLE;

        if (rc.top >= rcT.bottom-3*CXYHANDLE)
            rc.top=rcT.bottom-3*CXYHANDLE;

        rc.right=rc.left+(int)szl.cx;
        rc.bottom=rc.top+(int)szl.cy;
        IntersectRect(&rc, &rc, &rcT);

        RECTLFROMRECT(rcl, rc);

        //CHAPTER17MOD
        m_pTenantCur->RectSet(&rcl, TRUE, FALSE);
        //End CHAPTER17MOD
        m_pTenantCur->Repaint();
        return TRUE;
        }

    /*
     * Otherwise we may have to delete the old tenant if the effect
     * was move.  This will not happen in the move in page case.
     */

    if (DROPEFFECT_MOVE==dwEffect)
        {
        TenantDestroy();
        return TRUE;
        }

    //Copy is a clean operation
    return FALSE;
    }
