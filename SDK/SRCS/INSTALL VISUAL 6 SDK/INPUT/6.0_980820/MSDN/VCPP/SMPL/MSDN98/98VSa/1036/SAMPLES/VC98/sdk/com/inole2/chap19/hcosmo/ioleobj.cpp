/*
 * IOLEOBJ.CPP
 * Cosmo Handler Chapter 19
 *
 * Implementation of the IOleObject interface for Cosmo Handler.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "hcosmo.h"


/*
 * CImpIOleObject::CImpIOleObject
 * CImpIOleObject::~CImpIOleObject
 *
 * Parameters (Constructor):
 *  pObj            PCFigure of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleObject::CImpIOleObject(PCFigure pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleObject::~CImpIOleObject(void)
    {
    return;
    }



/*
 * CImpIOleObject::QueryInterface
 * CImpIOleObject::AddRef
 * CImpIOleObject::Release
 */

STDMETHODIMP CImpIOleObject::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIOleObject::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleObject::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * The only member function we need to implement in a handler is
 * IOleObject::GetExtent since we know exactly how large our data
 * is.  All others can be delegated.
 */


/*
 * CImpIOleObject::GetExtent
 *
 * Purpose:
 *  Retrieves the size of the object in HIMETRIC units.
 *
 * Parameters:
 *  dwAspect        DWORD of the aspect requested
 *  pszl            LPSIZEL into which to store the size.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, error code otherwise.
 */

STDMETHODIMP CImpIOleObject::GetExtent(DWORD dwAspect, LPSIZEL pszl)
    {
    //We can just use IViewObject2 for this.
    return m_pObj->m_pImpIViewObject2->GetExtent(dwAspect, -1
        , NULL, pszl);
    }



/*
 * CImpIOleObject::DoVerb
 *
 * An example of displaying a message when the local server is not
 * present.  This is a good way to get some free advertising if you
 * allow free redistribution of your handler with documents
 * containing your objects.
 */

STDMETHODIMP CImpIOleObject::DoVerb(LONG iVerb, LPMSG pMSG
    , LPOLECLIENTSITE pSite, LONG lIndex, HWND hWnd, LPCRECT prc)
    {
    HRESULT     hr;

    hr=m_pObj->m_pDefIOleObject->DoVerb(iVerb, pMSG, pSite, lIndex
        , hWnd, prc);

    if (FAILED(hr))
        {
        MessageBox(hWnd, TEXT("Local server not present.\nIf\
 I wanted to make money\nI would put some advertising here.")
            , TEXT("Cosmo Handler"), MB_OK);
        }

    return hr;
    }





STDMETHODIMP CImpIOleObject::SetClientSite
    (LPOLECLIENTSITE pIOleClientSite)
    {
    return m_pObj->m_pDefIOleObject->SetClientSite(pIOleClientSite);
    }

STDMETHODIMP CImpIOleObject::GetClientSite
    (LPOLECLIENTSITE *ppSite)
    {
    return m_pObj->m_pDefIOleObject->GetClientSite(ppSite);
    }

STDMETHODIMP CImpIOleObject::SetHostNames(LPCOLESTR pszApp
    , LPCOLESTR pszObj)
    {
    return m_pObj->m_pDefIOleObject->SetHostNames(pszApp, pszObj);
    }

STDMETHODIMP CImpIOleObject::Close(DWORD dwSaveOption)
    {
    return m_pObj->m_pDefIOleObject->Close(dwSaveOption);
    }

STDMETHODIMP CImpIOleObject::SetMoniker(DWORD dwWhich
    , LPMONIKER pmk)
    {
    return m_pObj->m_pDefIOleObject->SetMoniker(dwWhich, pmk);
    }

STDMETHODIMP CImpIOleObject::GetMoniker(DWORD dwAssign
    , DWORD dwWhich, LPMONIKER *ppmk)
    {
    return m_pObj->m_pDefIOleObject->GetMoniker(dwAssign, dwWhich
        , ppmk);
    }

STDMETHODIMP CImpIOleObject::InitFromData(LPDATAOBJECT pIDataObject
    , BOOL fCreation, DWORD dw)
    {
    return m_pObj->m_pDefIOleObject->InitFromData(pIDataObject
        , fCreation, dw);
    }

STDMETHODIMP CImpIOleObject::GetClipboardData(DWORD dwReserved
    , LPDATAOBJECT *ppIDataObj)
    {
    return m_pObj->m_pDefIOleObject->GetClipboardData(dwReserved
        , ppIDataObj);
    }

STDMETHODIMP CImpIOleObject::EnumVerbs(LPENUMOLEVERB *ppEnum)
    {
    return m_pObj->m_pDefIOleObject->EnumVerbs(ppEnum);
    }

STDMETHODIMP CImpIOleObject::Update(void)
    {
    return m_pObj->m_pDefIOleObject->Update();
    }

STDMETHODIMP CImpIOleObject::IsUpToDate(void)
    {
    return m_pObj->m_pDefIOleObject->IsUpToDate();
    }

STDMETHODIMP CImpIOleObject::GetUserClassID(LPCLSID pClsID)
    {
    return m_pObj->m_pDefIOleObject->GetUserClassID(pClsID);
    }

STDMETHODIMP CImpIOleObject::GetUserType(DWORD dwForm
    , LPOLESTR *ppszType)
    {
    return m_pObj->m_pDefIOleObject->GetUserType(dwForm, ppszType);
    }

STDMETHODIMP CImpIOleObject::SetExtent(DWORD dwAspect, LPSIZEL pszl)
    {
    return m_pObj->m_pDefIOleObject->SetExtent(dwAspect, pszl);
    }

STDMETHODIMP CImpIOleObject::Advise(LPADVISESINK pIAdviseSink
    , LPDWORD pdwConn)
    {
    return m_pObj->m_pDefIOleObject->Advise(pIAdviseSink, pdwConn);
    }

STDMETHODIMP CImpIOleObject::Unadvise(DWORD dwConn)
    {
    return m_pObj->m_pDefIOleObject->Unadvise(dwConn);
    }

STDMETHODIMP CImpIOleObject::EnumAdvise(LPENUMSTATDATA *ppEnum)
    {
    return m_pObj->m_pDefIOleObject->EnumAdvise(ppEnum);
    }

STDMETHODIMP CImpIOleObject::GetMiscStatus(DWORD dwAspect
    , LPDWORD pdwStatus)
    {
    return m_pObj->m_pDefIOleObject->GetMiscStatus(dwAspect
        , pdwStatus);
    }

STDMETHODIMP CImpIOleObject::SetColorScheme(LPLOGPALETTE pLP)
    {
    return m_pObj->m_pDefIOleObject->SetColorScheme(pLP);
    }
