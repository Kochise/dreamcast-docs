/*
 * ICONSITE.CPP
 * Patron Chapter 24
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CImpIOleControlSite::CImpIOleControlSite
 * CImpIOleControlSite::~CImpIOleControlSite
 *
 * Parameters (Constructor):
 *  pTen            PCTenant of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleControlSite::CImpIOleControlSite(PCTenant pTen
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pTen=pTen;
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
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleControlSite::OnControlInfoChanged(void)
    {
    //We also update our "have info" flag here.
    m_pTen->m_fHaveControlInfo=SUCCEEDED(m_pTen->m_pIOleControl
        ->GetControlInfo(&m_pTen->m_ctrlInfo));

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
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleControlSite::LockInPlaceActive(BOOL fLock)
    {
    if (fLock)
        m_pTen->m_cLockInPlace++;
    else
        {
        if (0==--m_pTen->m_cLockInPlace)
            {
            //If there's a pending deactivate, do it now.
            if (m_pTen->m_fPendingDeactivate)
                m_pTen->DeactivateInPlaceObject(TRUE);
            }
        }

    return NOERROR;
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
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleControlSite::GetExtendedControl(LPDISPATCH
    * ppDispatch)
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
 *  pptlHiMet       POINTL * containing either the coordinates to
 *                  transform to container or where to store the
 *                  transformed container coordinates.
 *  pptlCont        POINTF * containing the container coordinates.
 *  dwFlags         DWORD containing instructional flags.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleControlSite::TransformCoords(POINTL *pptlHiMet
    , POINTF *pptlCont, DWORD dwFlags)
    {
    if (NULL==pptlHiMet || NULL==pptlCont)
        return ResultFromScode(E_POINTER);

    /*
     * Convert coordinates.  We use MM_LOMETRIC which means that
     * to convert from HIMETRIC we divide by 10 and negate the y
     * coordinate.  Conversion to HIMETRIC means negate the y
     * and multiply by 10.  Note that size and position are
     * considered the same thing, that is, we don't differentiate
     * the two.
     */

    if (XFORMCOORDS_HIMETRICTOCONTAINER & dwFlags)
        {
        pptlCont->x=(float)(pptlHiMet->x/10);
        pptlCont->y=(float)-(pptlHiMet->y/10);
        }
    else
        {
        pptlHiMet->x=(long)(pptlCont->x*10);
        pptlHiMet->y=(long)-(pptlCont->y*10);
        }

    return NOERROR;
    }





/*
 * CImpIOleControlSite::TranslateAccelerator
 *
 * Purpose:
 *  Instructs the container to translate a keyboard accelerator
 *  message that the control has picked up instead.
 *
 * Parameters:
 *  pMsg            LPMSG to the message to translate.
 *  grfModifiers    DWORD flags with additional instructions.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleControlSite::TranslateAccelerator(LPMSG pMsg
    , DWORD grfModifiers)
    {
    /*
     * The control has picked up a keystroke through its own
     * TranslateAccelerator and is now giving us the change to
     * play with it.  Currently there are no flags for
     * grfModifiers, so we ignore them.  Especially since
     * we have nothing to do here ourselves anyway.
     */
    return ResultFromScode(S_FALSE);
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
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleControlSite::OnFocus(BOOL fGotFocus)
    {
    /*
     * Patron doesn't do this, but to handle the default
     * and cancel buttons properly, we normally process RETURN
     * and ESC accelerators to press the right button.
     * This behavior must be disabled when the control with
     * the focus has either CTRLINFO_EATS_RETURN or
     * CTRLINFO_EATS_ESCAPE set.  We tell the frame as
     * we need to when a new control gets the focus.  We
     * do nothing when a control loses the focus.
     */
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
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleControlSite::ShowPropertyFrame(void)
    {
    /*
     * Returning an error here means that the container has
     * no property pages itself for the control, so the
     * control should display its own.
     */
    return ResultFromScode(E_NOTIMPL);
    }
