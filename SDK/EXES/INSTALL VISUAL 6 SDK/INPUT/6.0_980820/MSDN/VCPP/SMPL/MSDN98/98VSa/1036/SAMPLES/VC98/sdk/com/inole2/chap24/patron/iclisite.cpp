/*
 * ICLISITE.CPP
 * Patron Chapter 24
 *
 * Implementation of the IOleClientSite interface for
 * Patron's tenants.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CImpIOleClientSite::CImpIOleClientSite
 * CImpIOleClientSite::~CImpIOleClientSite
 *
 * Parameters (Constructor):
 *  pTenant         PCTenant of the tenant we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleClientSite::CImpIOleClientSite(PCTenant pTenant
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pTen=pTenant;
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
    , PPVOID ppv)
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
    //We're already set up with the tenant to save; this is trivial.
    m_pTen->Update();
    return NOERROR;
    }





/*
 * CImpIOleClientSite::GetMoniker
 *
 * Purpose:
 *  Retrieves the moniker for the site in which this object lives,
 *  either the moniker relative to the container or the full
 *  moniker.
 *
 * Parameters:
 *  dwAssign        DWORD specifying that the object wants moniker
 *                  assignment.  Yeah.  Right.  Got any bridges to
 *                  sell?
 *  dwWhich         DWORD identifying which moniker the object
 *                  wants, either the container's moniker, the
 *                  moniker relative to this client site, or the
 *                  full moniker.
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::GetMoniker(DWORD dwAssign
    , DWORD dwWhich, LPMONIKER *ppmk)
    {
    *ppmk=NULL;

    switch (dwWhich)
        {
        case OLEWHICHMK_CONTAINER:
            //This is just the file we're living in.
            if (NULL!=m_pTen->m_pmkFile)
                *ppmk=m_pTen->m_pmkFile;

            break;

        case OLEWHICHMK_OBJREL:
            //This is everything but the filename.
            if (NULL!=m_pTen->m_pmk)
                *ppmk=m_pTen->m_pmk;

            break;

        case OLEWHICHMK_OBJFULL:
            //Concatenate file and relative monikers for this one.
            if (NULL!=m_pTen->m_pmkFile && NULL!=m_pTen->m_pmk)
                {
                return m_pTen->m_pmkFile->ComposeWith
                    (m_pTen->m_pmk, FALSE, ppmk);
                }

            break;
        }

    if (NULL==*ppmk)
        return ResultFromScode(E_FAIL);

    (*ppmk)->AddRef();
    return NOERROR;
    }






/*
 * CImpIOleClientSite::GetContainer
 *
 * Purpose:
 *  Returns a pointer to the document's IOleContainer interface.
 *
 * Parameters:
 *  ppContainer     LPOLECONTAINER * in which to return the
 *                  interface.
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::GetContainer(LPOLECONTAINER
    * ppContainer)
    {
    PCPage  pPage;

    *ppContainer=NULL;

    /*
     * Here we want to get the interface on the page we're in.
     * The function we call in CPages does not AddRef the page, but
     * QueryInterface does.
     */
    m_pTen->m_pPG->IPageGetFromID((DWORD)-1L, &pPage, FALSE);

    if (NULL!=pPage)
        {
        return pPage->QueryInterface(IID_IOleItemContainer
            , (PPVOID)ppContainer);
        }

    return ResultFromScode(E_FAIL);
    }






/*
 * CImpIOleClientSite::ShowObject
 *
 * Purpose:
 *  Tells the container to bring the object fully into view as much
 *  as possible, that is, scroll the document.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::ShowObject(void)
    {
    HWND        hWnd, hWndT;

    /*
     * We let the tenant do this, since it can access the current
     * scroll position as a friend of CPages whereas we cannot.
     */

    //Don't try to show objects that are always active.
    if (!((OLEMISC_INSIDEOUT | OLEMISC_ACTIVATEWHENVISIBLE)
        & m_pTen->m_grfMisc))
        m_pTen->ShowYourself();

    //For linking to embedding, show the main window.
    hWndT=GetParent(m_pTen->m_hWnd);

    while (NULL!=hWndT)
        {
        hWnd=hWndT;
        hWndT=GetParent(hWnd);
        }

    ShowWindow(hWnd, SW_SHOWNOACTIVATE);
    m_pTen->UpdateInPlaceObjectRects(NULL, TRUE);
    return NOERROR;
    }






/*
 * CImpIOleClientSite::OnShowWindow
 *
 * Purpose:
 *  Informs the container if the object is showing itself or
 *  hiding itself.  This is done only in the opening mode and allows
 *  the container to know when to shade or unshade the object.
 *
 * Parameters:
 *  fShow           BOOL indiciating that the object is being shown
 *                  (TRUE) or hidden (FALSE).
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::OnShowWindow(BOOL fShow)
    {
    //All we have to do is tell the tenant of the open state change.
    m_pTen->ShowAsOpen(fShow);
    return NOERROR;
    }






//CHAPTER24MOD
/*
 * CImpIOleClientSite::RequestNewObjectLayout
 *
 * Purpose:
 *  Called when the object would like to have its layout
 *  reinitialized.  This is used by OLE Controls.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CImpIOleClientSite::RequestNewObjectLayout(void)
    {
    RECT    rc, rcT;
    SIZEL   szl;
    HRESULT hr;

    /*
     * This function is called by a control that is not in-place
     * active or UI active and therefore doesn't have our
     * IOleInPlaceSite interface in which to call OnPosRectChange.
     * Therefore we do pretty much the same thing we do in that
     * function although we ask the control for the size it wants.
     */

    //Get the size from the control
    if (NULL!=m_pTen->m_pIViewObject2)
        {
        hr=m_pTen->m_pIViewObject2->GetExtent(m_pTen->m_fe.dwAspect
            , -1, NULL, &szl);
        }

    if (FAILED(hr))
        return hr;

    //Add these extents to the existing tenant position.
    SetRect(&rcT, 0, 0, szl.cx*10, -szl.cy*10);
    RectConvertMappings(&rcT, NULL, TRUE);

    rc=m_pTen->m_rcPos;
    rc.right=rc.left+rcT.right;
    rc.bottom=rc.top+rcT.bottom;

    m_pTen->UpdateInPlaceObjectRects(&rc, FALSE);
    return NOERROR;
    }
//End CHAPTER24MOD
