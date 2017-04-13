/*
 * ICLISITE.CPP
 * IOleClientSite for Document Objects CSite class
 *
 * Copyright (c)1995-1997 Microsoft Corporation, All Rights Reserved
 */


#include "framer.h"


/*
 * CImpIOleClientSite::CImpIOleClientSite
 * CImpIOleClientSite::~CImpIOleClientSite
 *
 * Parameters (Constructor):
 *  pSite           PCSite of the site we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleClientSite::CImpIOleClientSite(PCSite pSite
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pSite=pSite;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleClientSite::~CImpIOleClientSite(void)
    {
    return;
    }




/*
 * CImpIOleClientSite::QueryInterface
 * CImpIOleClientSite::AddRef
 * CImpIOleClientSite::Release
 *
 * Purpose:
 *  IUnknown members for CImpIOleClientSite object.
 */

STDMETHODIMP CImpIOleClientSite::QueryInterface(REFIID riid
    , void **ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIOleClientSite::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleClientSite::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIOleClientSite::SaveObject
 *
 * Purpose:
 *  Requests that the container call OleSave for the object that
 *  lives here.  Typically this happens on server shutdown.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::SaveObject(void)
    {
    m_pSite->Update();
    return NOERROR;
    }




/*
 * Unimplemented/trivial members
 *  GetMoniker
 *  GetContainer
 *  RequestNewObjectLayout
 *  OnShowWindow
 *  ShowObject
 */

STDMETHODIMP CImpIOleClientSite::GetMoniker(DWORD dwAssign
    , DWORD dwWhich, LPMONIKER *ppmk)
    {
    return E_NOTIMPL;
    }

STDMETHODIMP CImpIOleClientSite::GetContainer(LPOLECONTAINER
    * ppContainer)
    {
		*ppContainer=NULL;
		return E_NOINTERFACE;
    }

STDMETHODIMP CImpIOleClientSite::RequestNewObjectLayout(void)
    {
    return E_NOTIMPL;
    }

STDMETHODIMP CImpIOleClientSite::OnShowWindow(BOOL fShow)
    {
    return NOERROR;
    }

STDMETHODIMP CImpIOleClientSite::ShowObject(void)
    {
    return NOERROR;
    }
