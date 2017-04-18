/*
 * IIPSITE.CPP
 *
 * Template IOleInPlaceSite interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iipsite.h"


/*
 * CImpIOleInPlaceSite::CImpIOleInPlaceSite
 * CImpIOleInPlaceSite::~CImpIOleInPlaceSite
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleInPlaceSite::CImpIOleInPlaceSite(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
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
    , LPVOID *ppv)
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
 * CImpIOleInPlaceSite::GetWindow
 *
 * Purpose:
 *  Retrieves the handle of the window associated with the object
 *  on which this interface is implemented.
 *
 * Parameters:
 *  phWnd           HWND * in which to store the window handle.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_FAIL if no window.
 */

STDMETHODIMP CImpIOleInPlaceSite::GetWindow(HWND *phWnd)
    {
    return ResultFromScode(E_FAIL);
    }




/*
 * CImpIOleInPlaceSite::ContextSensitiveHelp
 *
 * Purpose:
 *  Instructs the object on which this interface is implemented to
 *  enter or leave a context-sensitive help mode.
 *
 * Parameters:
 *  fEnterMode      BOOL TRUE to enter the mode, FALSE otherwise.
 */

STDMETHODIMP CImpIOleInPlaceSite::ContextSensitiveHelp(
    BOOL fEnterMode)
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
 *  in-place.  Linked objects, for example, cannot, meaning we
 *  return S_FALSE.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR if we can in-place activate the
 *                  object in this site, S_FALSE if not.
 */

STDMETHODIMP CImpIOleInPlaceSite::CanInPlaceActivate(void)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::OnInPlaceActivate
 *
 * Purpose:
 *  Informs the container that an object is being activated
 *  in-place such that the container can prepare appropriately.
 *  The container does not, however, make any user interface
 *  changes at this point.  See OnUIActivate.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIOleInPlaceSite::OnInPlaceActivate(void)
    {
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
 */

STDMETHODIMP CImpIOleInPlaceSite::OnInPlaceDeactivate(void)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::OnUIActivate
 *
 * Purpose:
 *  Informs the container that the object is going to start
 *  munging around with user interface, like replacing the menu.
 *  The container should remove any relevant UI in preparation.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIOleInPlaceSite::OnUIActivate(void)
    {
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
 */

STDMETHODIMP CImpIOleInPlaceSite::OnUIDeactivate(BOOL fUndoable)
    {
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
 */

STDMETHODIMP CImpIOleInPlaceSite::DeactivateAndUndo(void)
    {
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
 */

STDMETHODIMP CImpIOleInPlaceSite::DiscardUndoState(void)
    {
    return NOERROR;
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
 *  ppIIPFrame      LPOLEINPLACEFRAME * in which to return
 *                  the AddRef'd pointer to the IOleInPlaceFrame.
 *  ppIIPUIWindow   LPOLEINPLACEUIWINDOW * in which to return
 *                  the AddRef'd pointer to the document's
 *                  IOleInPlaceUIWindow.
 *  prcPos          LPRECT in which to store the object's position.
 *  prcClip         LPRECT in which to store the object's
 *                  visible region.
 *  pFI             LPOLEINPLACEFRAMEINFO for accelerator info.
 */

STDMETHODIMP CImpIOleInPlaceSite::GetWindowContext(
    LPOLEINPLACEFRAME *ppIIPFrame, LPOLEINPLACEUIWINDOW
    *ppIIPUIWindow, LPRECT prcPos, LPRECT prcClip
    , LPOLEINPLACEFRAMEINFO pFI)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::Scroll
 *
 * Purpose:
 *  Asks the container to scroll the document, and thus the
 *  object, by the given amounts in the sz parameter.
 *
 * Parameters:
 *  sz              SIZE containing signed horizontal and vertical
 *                  extents by which the container should scroll.
 */

STDMETHODIMP CImpIOleInPlaceSite::Scroll(SIZE sz)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceSite::OnPosRectChange
 *
 * Purpose:
 *  Informs the container that the in-place object was resized.
 *  The container must call IOleInPlaceObject::SetObjectRects.
 *
 * Parameters:
 *  prcPos          LPCRECT containing the new size of the object.
 */

STDMETHODIMP CImpIOleInPlaceSite::OnPosRectChange(LPCRECT prcPos)
    {
    return NOERROR;
    }
