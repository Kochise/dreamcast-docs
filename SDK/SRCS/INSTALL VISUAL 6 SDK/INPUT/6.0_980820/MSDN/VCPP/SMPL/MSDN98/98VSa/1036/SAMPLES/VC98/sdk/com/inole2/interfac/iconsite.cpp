/*
 * ICONSITE.CPP
 *
 * Template IOleControlSite interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iconsite.h"


/*
 * CImpIOleControlSite::CImpIOleControlSite
 * CImpIOleControlSite::~CImpIOleControlSite
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleControlSite::CImpIOleControlSite(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleControlSite::~CImpIOleControlSite(void)
    {
    return;
    }



/*
 * CImpIOleControlSite::QueryInterface
 * CImpIOleControlSite::AddRef
 * CImpIOleControlSite::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIOleControlSite.
 */

STDMETHODIMP CImpIOleControlSite::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIOleControlSite::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleControlSite::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIOleControlSite::OnControlInfoChanged
 *
 * Purpose:
 *  Informs the site that the CONTROLINFO for the control has
 *  changed and we thus need to reload the data.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIOleControlSite::OnControlInfoChanged(void)
    {
    return NOERROR;
    }





/*
 * CImpIOleControlSite::LockInPlaceActive
 *
 * Purpose:
 *  Forces the container to keep this control in-place active
 *  (but not UI active) regardless of other considerations, or
 *  removes this lock.
 *
 * Parameters:
 *  fLock           BOOL indicating to lock (TRUE) or unlock (FALSE)
 *                  in-place activation.
 */

STDMETHODIMP CImpIOleControlSite::LockInPlaceActive(BOOL fLock)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIOleControlSite::GetExtendedControl
 *
 * Purpose:
 *  Returns a pointer to the container's extended control that wraps
 *  the actual control in this site, if one exists.
 *
 * Parameters:
 *  ppDispatch      LPDISPATCH * in which to return the pointer
 *                  to the extended control's IDispatch interface.
 */

STDMETHODIMP CImpIOleControlSite::GetExtendedControl(LPDISPATCH
    *ppDispatch)
    {
    *ppDispatch=NULL;
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIOleControlSite::TransformCoords
 *
 * Purpose:
 *  Converts coordinates in HIMETRIC units into those used by the
 *  container.
 *
 * Parameters:
 *  pptlHiMet       POINTL * containing the coordinates to transform
 *  pptlCont        POINTF * in which to return the new coordinates
 *  dwFlags         DWORD containing instructional flags.
 */

STDMETHODIMP CImpIOleControlSite::TransformCoords(POINTL *pptlHiMet
    , POINTF *pptlCont, DWORD dwFlags)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIOleControlSite::TranslateAccelerator
 *
 * Purpose:
 *  Instructs the object to translate a keyboard accelerator
 *  message that the control has picked up instead.
 *
 * Parameters:
 *  pMsg            LPMSG to the message to translate.
 *  grfModifiers    DWORD flags with additional instructions.
 */

STDMETHODIMP CImpIOleControlSite::TranslateAccelerator(LPMSG pMsg
    , DWORD grfModifiers)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIOleControlSite::OnFocus
 *
 * Purpose:
 *  Informs the container that focus has either been lost or
 *  gained in the control.
 *
 * Parameters:
 *  fGotFocus       BOOL indicating that the control gained (TRUE)
 *                  or lost (FALSE) focus.
 */

STDMETHODIMP CImpIOleControlSite::OnFocus(BOOL fGotFocus)
    {
    return NOERROR;
    }




/*
 * CImpIOleControlSite::ShowPropertyFrame
 *
 * Purpose:
 *  Instructs the container to show the property frame if
 *  this is an extended object and requires its own property
 *  pages.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIOleControlSite::ShowPropertyFrame(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }
