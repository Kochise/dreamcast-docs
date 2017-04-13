/*
 * IIPSITE.CPP
 * Patron Chapter 24
 *
 * IOleInPlaceSite interface implementation for Patron
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


BOOL        g_fSwitchingActive=FALSE;

/*
 * CImpIOleInPlaceSite::CImpIOleInPlaceSite
 * CImpIOleInPlaceSite::~CImpIOleInPlaceSite
 *
 * Parameters (Constructor):
 *  pTen            PCTenant of the tenant we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleInPlaceSite::CImpIOleInPlaceSite(PCTenant pTen
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pTen=pTen;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleInPlaceSite::~CImpIOleInPlaceSite(void)
    {
    return;
    }



/*
 * CImpIOleInPlaceSite::QueryInterface
 * CImpIOleInPlaceSite::AddRef
 * CImpIOleInPlaceSite::Release
 *
 * Purpose:
 *  IUnknown members for CImpIOleInPlaceSite object.
 */

STDMETHODIMP CImpIOleInPlaceSite::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIOleInPlaceSite::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleInPlaceSite::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIOleInPlaceActiveObject::GetWindow
 *
 * Purpose:
 *  Retrieves the handle of the window associated with the object
 *  on which this interface is implemented.
 *
 * Parameters:
 *  phWnd           HWND * in which to store the window handle.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_FAIL if there is no
 *                  window.
 */

STDMETHODIMP CImpIOleInPlaceSite::GetWindow(HWND *phWnd)
    {
    *phWnd=m_pTen->m_hWnd;
    return NOERROR;
    }




/*
 * CImpIOleInPlaceActiveObject::ContextSensitiveHelp
 *
 * Purpose:
 *  Instructs the object on which this interface is implemented to
 *  enter or leave a context-sensitive help mode.
 *
 * Parameters:
 *  fEnterMode      BOOL TRUE to enter the mode, FALSE otherwise.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleInPlaceSite::ContextSensitiveHelp
    (BOOL fEnterMode)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::CanInPlaceActivate
 *
 * Purpose:
 *  Answers the server whether or not we can currently in-place
 *  activate its object.  By implementing this interface we say
 *  that we support in-place activation, but through this function
 *  we indicate whether the object can currently be activated
 *  in-place.  Iconic aspects, for example, cannot, meaning we
 *  return S_FALSE.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR if we can in-place activate the object
 *                  in this site, S_FALSE if not.
 */

STDMETHODIMP CImpIOleInPlaceSite::CanInPlaceActivate(void)
    {
    if (DVASPECT_CONTENT!=m_pTen->m_fe.dwAspect)
        return ResultFromScode(S_FALSE);

    if (TENANTTYPE_EMBEDDEDOBJECT!=m_pTen->m_tType)
        return ResultFromScode(S_FALSE);

    //CHAPTER24MOD
    if (m_pTen->m_pPG->m_fDesignMode)
        return ResultFromScode(S_FALSE);
    //End CHAPTER24MOD

    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::OnInPlaceActivate
 *
 * Purpose:
 *  Informs the container that an object is being activated in-place
 *  such that the container can prepare appropriately.  The
 *  container does not, however, make any user interface changes at
 *  this point.  See OnUIActivate.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR or an appropriate error code.
 */

STDMETHODIMP CImpIOleInPlaceSite::OnInPlaceActivate(void)
    {
    //CHAPTER24MOD
    m_pTen->m_fPendingDeactivate=FALSE;
    //End CHAPTER24MOD

    //m_pIOleIPObject is our in-place flag.
    m_pTen->m_pObj->QueryInterface(IID_IOleInPlaceObject
        , (PPVOID)&m_pTen->m_pIOleIPObject);

    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::OnInPlaceDeactivate
 *
 * Purpose:
 *  Notifies the container that the object has deactivated itself
 *  from an in-place state.  Opposite of OnInPlaceActivate.  The
 *  container does not change any UI at this point.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR or an appropriate error code.
 */

STDMETHODIMP CImpIOleInPlaceSite::OnInPlaceDeactivate(void)
    {
    /*
     * Since we don't have an Undo command, we can tell the object
     * right away to discard its Undo state.
     */
    m_pTen->Activate(OLEIVERB_DISCARDUNDOSTATE, NULL);
    ReleaseInterface(m_pTen->m_pIOleIPObject);
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::OnUIActivate
 *
 * Purpose:
 *  Informs the container that the object is going to start munging
 *  around with user interface, like replacing the menu.  The
 *  container should remove any relevant UI in preparation.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR or an appropriate error code.
 */

STDMETHODIMP CImpIOleInPlaceSite::OnUIActivate(void)
    {
    PCPatronDoc     pDoc;

    m_pTen->m_pPG->m_fAddUI=FALSE;

    //CHAPTER24MOD
    m_pTen->m_fPendingDeactivate=FALSE;
    //End CHAPTER24MOD

    pDoc=(PCPatronDoc)SendMessage(GetParent(m_pTen->m_hWnd)
        , DOCM_PDOCUMENT, 0, 0L);

    /*
     * Change the currently selected tenant in the page.  This
     * will UIDeactivate the currently UI Active tenant.
     */
    g_fSwitchingActive=TRUE;
    m_pTen->m_pPG->m_pPageCur->SwitchActiveTenant(m_pTen);
    g_fSwitchingActive=FALSE;

    //Hide the frame tools if necessary.
    g_pFR->ShowUIAndTools(pDoc->NoObjectFrameTools(0, FALSE), FALSE);
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::OnUIDeactivate
 *
 * Purpose:
 *  Informs the container that the object is deactivating its
 *  in-place user interface at which time the container may
 *  reinstate its own.  Opposite of OnUIActivate.
 *
 * Parameters:
 *  fUndoable       BOOL indicating if the object will actually
 *                  perform an Undo if the container calls
 *                  ReactivateAndUndo.
 *
 * Return Value:
 *  HRESULT         NOERROR or an appropriate error code.
 */

STDMETHODIMP CImpIOleInPlaceSite::OnUIDeactivate(BOOL fUndoable)
    {
    PCDocument  pDoc;
    MSG         msg;

    /*
     * Ignore this notification if we're switching between
     * multiple active objects.
     */
    if (g_fSwitchingActive)
        return NOERROR;

    //If in shutdown (NULL storage), don't check messages.
    if (NULL==m_pTen->m_pIStorage)
        {
        g_pFR->ReinstateUI();
        return NOERROR;
        }

    pDoc=(PCDocument)SendMessage(GetParent(m_pTen->m_hWnd)
        , DOCM_PDOCUMENT, 0, 0L);

    //If there's a pending double-click, delay showing our UI
    if (!PeekMessage(&msg, pDoc->Window(), WM_LBUTTONDBLCLK
        , WM_LBUTTONDBLCLK, PM_NOREMOVE | PM_NOYIELD))
        {
        //Turn everything back on.
        g_pFR->ReinstateUI();
        }
    else
        m_pTen->m_pPG->m_fAddUI=TRUE;

    SetFocus(pDoc->Window());
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::DeactivateAndUndo
 *
 * Purpose:
 *  If immediately after activation the object does an Undo, the
 *  action being undone is the activation itself, and this call
 *  informs the container that this is, in fact, what happened.
 *  The container should call IOleInPlaceObject::UIDeactivate.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR or an appropriate error code.
 */

STDMETHODIMP CImpIOleInPlaceSite::DeactivateAndUndo(void)
    {
    //CHAPTER24MOD
    /*
     * Note that we don't pay attention to the locking
     * from IOleControlSite::LockInPlaceActive since only
     * the object calls this function and should know
     * that it's going to be deactivated.
     */
    //End CHAPTER24MOD

    m_pTen->m_pIOleIPObject->InPlaceDeactivate();
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::DiscardUndoState
 *
 * Purpose:
 *  Informs the container that something happened in the object
 *  that means the container should discard any undo information
 *  it currently maintains for the object.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR or an appropriate error code.
 */

STDMETHODIMP CImpIOleInPlaceSite::DiscardUndoState(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleInPlaceSite::GetWindowContext
 *
 * Purpose:
 *  Provides an in-place object with pointers to the frame and
 *  document level in-place interfaces (IOleInPlaceFrame and
 *  IOleInPlaceUIWindow) such that the object can do border
 *  negotiation and so forth.  Also requests the position and
 *  clipping rectangles of the object in the container and a
 *  pointer to an OLEINPLACEFRAME info structure which contains
 *  accelerator information.
 *
 *  Note that the two interfaces this call returns are not
 *  available through QueryInterface on IOleInPlaceSite since they
 *  live with the frame and document, but not the site.
 *
 * Parameters:
 *  ppIIPFrame      LPOLEINPLACEFRAME * in which to return the
 *                  AddRef'd pointer to the container's
 *                  IOleInPlaceFrame.
 *  ppIIPUIWindow   LPOLEINPLACEUIWINDOW * in which to return
 *                  the AddRef'd pointer to the container document's
 *                  IOleInPlaceUIWindow.
 *  prcPos          LPRECT in which to store the object's position.
 *  prcClip         LPRECT in which to store the object's visible
 *                  region.
 *  pFI             LPOLEINPLACEFRAMEINFO to fill with accelerator
 *                  stuff.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleInPlaceSite::GetWindowContext
    (LPOLEINPLACEFRAME *ppIIPFrame, LPOLEINPLACEUIWINDOW
    *ppIIPUIWindow, LPRECT prcPos, LPRECT prcClip
    , LPOLEINPLACEFRAMEINFO pFI)
    {
    PCPatronDoc     pDoc;
    RECTL           rcl;

    *ppIIPUIWindow=NULL;

    *ppIIPFrame=(LPOLEINPLACEFRAME)g_pFR;
    g_pFR->AddRef();

    pDoc=(PCPatronDoc)SendMessage(GetParent(m_pTen->m_hWnd)
        , DOCM_PDOCUMENT, 0, 0L);

    if (NULL!=pDoc)
        {
        pDoc->QueryInterface(IID_IOleInPlaceUIWindow
            , (PPVOID)ppIIPUIWindow);
        }

    //Now get the rectangles and frame information.
    m_pTen->RectGet(&rcl, TRUE);
    RECTFROMRECTL(*prcPos, rcl);

    //Include scroll position here.
    OffsetRect(prcPos, -(int)m_pTen->m_pPG->m_xPos
        , -(int)m_pTen->m_pPG->m_yPos);

    SetRect(prcClip, 0, 0, 32767, 32767);

    pFI->cb=sizeof(OLEINPLACEFRAMEINFO);
   #ifdef MDI
    pFI->fMDIApp=TRUE;
   #else
    pFI->fMDIApp=FALSE;
   #endif

    pFI->hwndFrame=g_pFR->Window();

    pFI->haccel=g_pFR->m_hAccelIP;
    pFI->cAccelEntries=CINPLACEACCELERATORS;

    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::Scroll
 *
 * Purpose:
 *  Asks the container to scroll the document, and thus the object,
 *  by the given amounts in the sz parameter.
 *
 * Parameters:
 *  sz              SIZE containing signed horizontal and vertical
 *                  extents by which the container should scroll.
 *                  These are in device units.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleInPlaceSite::Scroll(SIZE sz)
    {
    int         x, y;

    x=m_pTen->m_pPG->m_xPos+sz.cx;
    y=m_pTen->m_pPG->m_yPos+sz.cy;

    SendScrollPosition(m_pTen->m_hWnd, WM_HSCROLL, x);
    SendScrollPosition(m_pTen->m_hWnd, WM_VSCROLL, y);
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::OnPosRectChange
 *
 * Purpose:
 *  Informs the container that the in-place object was resized.
 *  The container must call IOleInPlaceObject::SetObjectRects.
 *  This does not change the site's rectangle in any case.
 *
 * Parameters:
 *  prcPos          LPCRECT containing the new size of the object.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleInPlaceSite::OnPosRectChange(LPCRECT prcPos)
    {
    if (NULL!=prcPos)
        m_pTen->m_rcPos=*prcPos;

    m_pTen->UpdateInPlaceObjectRects(prcPos, FALSE);
    return NOERROR;
    }
