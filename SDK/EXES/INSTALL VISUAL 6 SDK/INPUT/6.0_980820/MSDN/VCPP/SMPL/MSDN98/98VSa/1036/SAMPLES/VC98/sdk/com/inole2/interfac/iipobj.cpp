/*
 * IIPOBJ.CPP
 *
 * Template IOleInPlaceObject interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iipobj.h"


/*
 * CImpIOleInPlaceObject::CImpIOleInPlaceObject
 * CImpIOleInPlaceObject::~CImpIOleInPlaceObject
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleInPlaceObject::CImpIOleInPlaceObject(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleInPlaceObject::~CImpIOleInPlaceObject(void)
    {
    return;
    }



/*
 * CImpIOleInPlaceObject::QueryInterface
 * CImpIOleInPlaceObject::AddRef
 * CImpIOleInPlaceObject::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIOleInPlaceObject.
 */

STDMETHODIMP CImpIOleInPlaceObject::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIOleInPlaceObject::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleInPlaceObject::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIOleInPlaceObject::GetWindow
 *
 * Purpose:
 *  Retrieves the handle of the window associated with the object on
 *  which this interface is implemented.
 *
 * Parameters:
 *  phWnd           HWND * in which to store the window handle.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_FAIL if no window.
 */

STDMETHODIMP CImpIOleInPlaceObject::GetWindow(HWND *phWnd)
    {
    return ResultFromScode(E_FAIL);
    }




/*
 * CImpIOleInPlaceObject::ContextSensitiveHelp
 *
 * Purpose:
 *  Instructs the object on which this interface is implemented to
 *  enter or leave a context-sensitive help mode.
 *
 * Parameters:
 *  fEnterMode      BOOL TRUE to enter the mode, FALSE otherwise.
 */

STDMETHODIMP CImpIOleInPlaceObject::ContextSensitiveHelp(
    BOOL fEnterMode)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleInPlaceObject::InPlaceDeactivate
 *
 * Purpose:
 *  Instructs the object to deactivate itself from an in-place
 *  state and to discard any Undo state.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIOleInPlaceObject::InPlaceDeactivate(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleInPlaceObject::UIDeactivate
 *
 * Purpose:
 *  Instructs the object to just remove any in-place user
 *  interface but to do no other deactivation.  The object
 *  should just hide the UI components but not destroy them
 *  until InPlaceDeactivate is called.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIOleInPlaceObject::UIDeactivate(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleInPlaceObject::SetObjectRects
 *
 * Purpose:
 *  Provides the object with rectangles describing the position
 *  of the object in the container window as well as its visible
 *  area.  The object must reposition according to these rectangles.
 *
 * Parameters:
 *  prcPos          LPCRECT providing the object's full rectangle
 *                  relative to the continer's document.  The object
 *                  should scale to this rectangle.
 *  prcClip         LPCRECT describing the visible area of the object
 *                  which should not draw outside these areas.
 */

STDMETHODIMP CImpIOleInPlaceObject::SetObjectRects(LPCRECT prcPos
    , LPCRECT prcClip)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleInPlaceObject::ReactivateAndUndo
 *
 * Purpose:
 *  Instructs the object to reactivate itself in-place and perform
 *  whatever Undo means for it.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIOleInPlaceObject::ReactivateAndUndo(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }
