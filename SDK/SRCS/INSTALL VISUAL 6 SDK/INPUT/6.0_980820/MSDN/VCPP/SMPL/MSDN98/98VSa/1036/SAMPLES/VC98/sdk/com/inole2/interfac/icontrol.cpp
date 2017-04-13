/*
 * ICONTROL.CPP
 *
 * Template IOleControl interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "icontrol.h"


/*
 * CImpIOleControl::CImpIOleControl
 * CImpIOleControl::~CImpIOleControl
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleControl::CImpIOleControl(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleControl::~CImpIOleControl(void)
    {
    return;
    }



/*
 * CImpIOleControl::QueryInterface
 * CImpIOleControl::AddRef
 * CImpIOleControl::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIOleControl.
 */

STDMETHODIMP CImpIOleControl::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIOleControl::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleControl::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIOleControl::GetControlInfo
 *
 * Purpose:
 *  Fills a CONTROLINFO structure containing information about
 *  the controls mnemonics and other behavioral aspects.
 *
 * Parameters:
 *  pCI             LPCONTROLINFO to the structure to fill
 */

STDMETHODIMP CImpIOleControl::GetControlInfo(LPCONTROLINFO pCI)
    {
    return ResultFromScode(E_NOTIMPL);
    }


/*
 * CImpIOleControl::OnMnemonic
 *
 * Purpose:
 *  Notifies the control that a mnemonic was activated.
 *
 * Parameters:
 *  pMsg            LPMSG containing the message that matches one of
 *                  the control's mnemonics.  The control uses this
 *                  to distinguish which mnemonic was pressed.
 */

STDMETHODIMP CImpIOleControl::OnMnemonic(LPMSG pMsg)
    {
    return ResultFromScode(E_NOTIMPL);
    }


/*
 * CImpIOleControl::OnAmbientPropertyChange
 *
 * Purpose:
 *  Notifies the control that one or more of the container's ambient
 *  properties changed.
 *
 * Parameters:
 *  dispID          DISPID identifying the property, which can
 *                  be DISPID_UNKNOWN indicating that more than
 *                  one changed.
 */

STDMETHODIMP CImpIOleControl::OnAmbientPropertyChange(DISPID dispid)
    {
    return NOERROR;
    }




/*
 * CImpIOleControl::FreezeEvents
 *
 * Purpose:
 *  Instructs the control to stop firing events or to continue
 *  firing them.
 *
 * Parameters:
 *  fFreeze         BOOL indicating to freeze (TRUE) or thaw (FALSE)
 *                  events from this control.
 */

STDMETHODIMP CImpIOleControl::FreezeEvents(BOOL fFreeze)
    {
    return ResultFromScode(E_NOTIMPL);
    }
