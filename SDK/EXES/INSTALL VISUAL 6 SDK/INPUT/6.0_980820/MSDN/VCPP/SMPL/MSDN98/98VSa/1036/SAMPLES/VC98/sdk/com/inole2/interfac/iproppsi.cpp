/*
 * IPROPPSI.CPP
 *
 * Template IPropertyPageSite interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iproppsi.h"


/*
 * CImpIPropertyPageSite::CImpIPropertyPageSite
 * CImpIPropertyPageSite::~CImpIPropertyPageSite
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIPropertyPageSite::CImpIPropertyPageSite(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIPropertyPageSite::~CImpIPropertyPageSite(void)
    {
    return;
    }



/*
 * CImpIPropertyPageSite::QueryInterface
 * CImpIPropertyPageSite::AddRef
 * CImpIPropertyPageSite::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPropertyPageSite.
 */

STDMETHODIMP CImpIPropertyPageSite::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPropertyPageSite::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPropertyPageSite::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIPropertyPageSite::OnStatusChange
 *
 * Purpose:
 *  Informs the page site that the status of its page has changed
 *  according to the flags in dwFlags:
 *      PROPPAGESTATUS_DIRTY        A value was changed.
 *      PROPPAGESTATUS_VALIDATE     It's an appropriate time to
 *                                  validate and apply changes.
 *
 * Parameters:
 *  dwFlags         DWORD identifying the changes.
 */

STDMETHODIMP CImpIPropertyPageSite::OnStatusChange(DWORD dwFlags)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPageSite::GetLocaleID
 *
 * Purpose:
 *  Retrieves the LCID for the page frame, if the page wants to
 *  localize to this locale.
 *
 * Parameters:
 *  plcid           LCID * in which to store the LCID.
 */

STDMETHODIMP CImpIPropertyPageSite::GetLocaleID(LCID *plcid)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPageSite::GetPageContainer
 *
 * Purpose:
 *  Retrieves a pointer to the property frame.
 *
 * Parameters:
 *  ppUnk           IUnknown ** in which to return the frame's
 *                  IUnknown pointer.
 */

STDMETHODIMP CImpIPropertyPageSite::GetPageContainer(IUnknown **ppUnk)
    {
    *ppUnk=NULL;
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIPropertyPageSite::TranslateAccelerator
 *
 * Purpose:
 *  Provides the page site with the oportunity to process messages.
 *
 * Parameters:
 *  pMsg            LPMSG containing the message of the accelerator.
 */

STDMETHODIMP CImpIPropertyPageSite::TranslateAccelerator(LPMSG lpMsg)
    {
    return ResultFromScode(E_NOTIMPL);
    }
