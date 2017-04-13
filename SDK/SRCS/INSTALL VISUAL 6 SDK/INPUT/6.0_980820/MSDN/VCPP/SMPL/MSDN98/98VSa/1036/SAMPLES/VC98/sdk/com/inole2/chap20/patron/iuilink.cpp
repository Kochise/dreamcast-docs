/*
 * IUILINK.CPP
 * Patron Chapter 20
 *
 * Implementation of an object with the IOleUILinkContainer
 * interface necessary to use the standard Links Dialog.  This
 * is implemented as a stand-along object with access to the CPage
 * with which its associated, primiarily because it is only used
 * for the one dialog.  Therefore this object has it's own IUnknown.
 * In addition, we use the Links Assistant object developed in this
 * chapter to simplify our own code.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CIOleUILinkContainer::CIOleUILinkContainer
 * CIOleUILinkContainer::~CIOleUILinkContainer
 *
 * Parameters (Constructor):
 *  pPage           PCPage of the page we're in.
 */

CIOleUILinkContainer::CIOleUILinkContainer(PCPage pPage)
    {
    m_cRef=0;
    m_pPage=pPage;
    m_iTenant=0;
    m_pDelIUILinks=NULL;
    m_fDirty=FALSE;
    return;
    }

CIOleUILinkContainer::~CIOleUILinkContainer(void)
    {
    ReleaseInterface(m_pDelIUILinks);
    return;
    }



/*
 * CIOleUILinkContainer::Init
 *
 * Purpose:
 *  Performs initialization on the object that might fail.  In
 *  particular this creates an object of CLSID_LinksAssistant that
 *  helps in implementing this interface.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CIOleUILinkContainer::Init(void)
    {
    HRESULT     hr;

    hr=CoCreateInstance(CLSID_LinksAssistant, NULL
        , CLSCTX_INPROC_SERVER, IID_IOleUILinkContainer
        , (PPVOID)&m_pDelIUILinks);

    return SUCCEEDED(hr);
    }





/*
 * CIOleUILinkContainer::QueryInterface
 * CIOleUILinkContainer::AddRef
 * CIOleUILinkContainer::Release
 *
 * Purpose:
 *  IUnknown members for CIOleUILinkContainer object.
 */

STDMETHODIMP CIOleUILinkContainer::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IOleUILinkContainer==riid)
        {
        *ppv=this;
        AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CIOleUILinkContainer::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CIOleUILinkContainer::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }



/*
 * CIOleUILinkContainer::GetNextLink
 *
 * Purpose:
 *  Called when the Links dialog is filling its listbox.  Here we
 *  need to return a key for the first link if dwLink is zero, then
 *  return the next links if it's non-zero.
 *
 * Parameters:
 *  dwLink          DWORD last returned from this function.  Zero if
 *                  this is the first call to this function.
 *
 * Return Value:
 *  DWORD           Some value that identifies this object.  Zero
 *                  stops the sequence such that this function is
 *                  no longer called.
 */

STDMETHODIMP_(DWORD) CIOleUILinkContainer::GetNextLink(DWORD dwLink)
    {
    PCTenant        pTenant;

    //If we're told to start the sequence, set index to zero.
    if (0L==dwLink)
        m_iTenant=0;

    /*
     * On each subsequent call, find the next linked object in
     * this document and return it.  Make sure the index is
     * incremented for the next time this function is called.
     */
    for ( ; m_iTenant < m_pPage->m_cTenants; m_iTenant++)
        {
        if (m_pPage->TenantGet(m_iTenant, &pTenant, FALSE))
            {
            if (TENANTTYPE_LINKEDOBJECT==pTenant->TypeGet())
                {
                m_iTenant++;
                return (DWORD)pTenant;
                }
            }
        }

    //If we hit the end of list, this tells the dialog to stop.
    return 0L;
    }





/*
 * CIOleUILinkContainer::SetLinkUpdateOptions
 *
 * Purpose:
 *  Informs the application to call IOleLink::SetUpdateOptions for
 *  the object identified by dwLink.
 *
 * Parameters:
 *  dwLink          DWORD object identifier as returned from
 *                  GetNextLink.
 *  dwOptions       DWORD containing the new options.
 *
 * Return Value:
 *  HRESULT         Return value of IOleLink::SetUpdateOptions.
 */

STDMETHODIMP CIOleUILinkContainer::SetLinkUpdateOptions(DWORD dwLink
    , DWORD dwOptions)
    {
    LPOLELINK       pIOleLink;
    HRESULT         hr;

    if (NULL==dwLink)
        return ResultFromScode(E_FAIL);

    /*
     * Your responsibility is to call the object's
     * IOleLink::SetUpdateOptions function with dwOptions.  Simple?
     *
     * For Patron we must first get the object pointer obtainable
     * from the tenant's ObjectGet function, then QI for IOleLink.
     */

    hr=GetObjectInterface(dwLink, IID_IOleLink, (PPVOID)&pIOleLink);

    if (FAILED(hr))
        return hr;

    hr=pIOleLink->SetUpdateOptions(dwOptions);
    pIOleLink->Release();

    m_fDirty=SUCCEEDED(hr);
    return hr;
    }





/*
 * CIOleUILinkContainer::GetLinkUpdateOptions
 *
 * Purpose:
 *  Requests the container to call IOleLink::GetUpdateOptions for
 *  the object identified by dwLink.
 *
 * Parameters:
 *  dwLink          DWORD identifying the object
 *  pdwOptions      LPDWORD in which to store the options.
 *
 * Return Value:
 *  HRESULT         Return value of IOleLink::GetUpdateOptions
 */

STDMETHODIMP CIOleUILinkContainer::GetLinkUpdateOptions(DWORD dwLink
    , LPDWORD pdwOptions)
    {
    LPOLELINK       pIOleLink;
    HRESULT         hr;

    if (NULL==dwLink)
        return ResultFromScode(E_FAIL);

    hr=GetObjectInterface(dwLink, IID_IOleLink, (PPVOID)&pIOleLink);

    if (FAILED(hr))
        return hr;

    hr=pIOleLink->GetUpdateOptions(pdwOptions);
    pIOleLink->Release();

    return hr;
    }





/*
 * CIOleUILinkContainer::SetLinkSource
 *
 * Purpose:
 *  Changes the moniker to which an object is linked.
 *
 * Parameters:
 *  dwLink          DWORD identifying the object in question.
 *  pszName         LPTSTR to the displayable name of the source.
 *  cchName         ULONG length of the file portaion of pszName
 *  pchEaten        ULONG * in which to return the number of
 *                  characters used in parsing pszDisplayName.
 *  fValidate       BOOL indicating if we're to validate that the
 *                  source exists first.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_FAIL otherwise.
 */

STDMETHODIMP CIOleUILinkContainer::SetLinkSource(DWORD dwLink
    , LPTSTR pszName, ULONG cchName, ULONG *pchEaten
    , BOOL fValidate)
    {
    PCTenant        pTenant=(PCTenant)dwLink;
    HRESULT         hr;
    LPOLELINK       pIOleLink;

    if (NULL==dwLink)
        return ResultFromScode(E_FAIL);

    //This is for use in GetLinkSource, below.
    pTenant->m_fLinkAvail=FALSE;

    hr=GetObjectInterface(dwLink, IID_IOleLink, (PPVOID)&pIOleLink);

    if (FAILED(hr))
        return hr;

    hr=m_pDelIUILinks->SetLinkSource((DWORD)pIOleLink, pszName
        , cchName, pchEaten, fValidate);
    pIOleLink->Release();

    if (FAILED(hr))
        return hr;

    //hr will be S_FALSE if link is unavailable.
    pTenant->Repaint();
    pTenant->m_fLinkAvail=(NOERROR==hr);
    m_fDirty=TRUE;
    return NOERROR;
    }






/*
 * CIOleUILinkContainer::GetLinkSource
 *
 * Purpose:
 *  Retrieves various strings and values for this link source.
 *
 * Parameters:
 *  dwLink          DWORD identifying the object affected.
 *  ppszName        LPTSTR * in which to return the new source
 *                  name
 *  pcchName        ULONG * in which to return the length of
 *                  pszName
 *  ppszFullLink    LPTSTR * in which to return the full name of
 *                  the class of linked object.
 *  ppszShortLink   LPTSTR * in which to return the short name of
 *                  the class of linked object.
 *  pfSourceAvail   BOOL * in which to return if this is an
 *                  available link source.
 *  pfSelected      BOOL * in which to return if this object is
 *                  currently selected in the document.  This
 *                  selects the item in the listbox for this object.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, error code otherwise.
 */

STDMETHODIMP CIOleUILinkContainer::GetLinkSource(DWORD dwLink
    , LPTSTR *ppszName, ULONG *pcchName, LPTSTR *ppszFullLink
    , LPTSTR *ppszShortLink, BOOL *pfSourceAvail, BOOL *pfSelected)
    {
    HRESULT         hr;
    PCTenant        pTenant=(PCTenant)dwLink;
    LPOLELINK       pIOleLink=NULL;
    LPOLEOBJECT     pIOleObject=NULL;
    LPMONIKER       pmk=NULL;
    LPMONIKER       pmkFirst=NULL;
    LPBC            pbc=NULL;

    if (NULL==dwLink)
        return ResultFromScode(E_FAIL);

    //We know what this is from SetLinkSource
    *pfSourceAvail=pTenant->m_fLinkAvail;

    if (pfSelected)
        *pfSelected=pTenant->FIsSelected();

    hr=GetObjectInterface(dwLink, IID_IOleLink, (PPVOID)&pIOleLink);

    if (FAILED(hr))
        return hr;

    hr=m_pDelIUILinks->GetLinkSource((DWORD)pIOleLink, ppszName
        , pcchName, ppszFullLink, ppszShortLink, pfSourceAvail
        , pfSelected);

    pIOleLink->Release();
    return hr;
    }





/*
 * CIOleUILinkContainer::OpenLinkSource
 *
 * Purpose:
 *  Asks the container to call DoVerb on this object with
 *  OLEIVERB_SHOW.
 *
 * Parameters:
 *  dwLink          DWORD identifying the linked object.
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CIOleUILinkContainer::OpenLinkSource(DWORD dwLink)
    {
    PCTenant        pTenant=(PCTenant)dwLink;

    pTenant->Activate(OLEIVERB_OPEN);
    return NOERROR;
    }




/*
 * CIOleUILinkContainer::UpdateLink
 *
 * Purpose:
 *  Asks the container to update the link for this object.
 *
 * Parameters:
 *  dwLink          DWORD identifying the linked object.
 *  fErrorMessage   BOOL indicating if we can show errors.
 *  fErrorAction    BOOL making no sense whatsoever.
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CIOleUILinkContainer::UpdateLink(DWORD dwLink
    , BOOL fErrorMessage, BOOL fErrorAction)
    {
    PCTenant        pTenant=(PCTenant)dwLink;
    LPOLELINK       pIOleLink;
    HRESULT         hr;

    hr=GetObjectInterface(dwLink, IID_IOleLink, (PPVOID)&pIOleLink);

    if (FAILED(hr))
        return hr;

    hr=m_pDelIUILinks->UpdateLink((DWORD)pIOleLink, fErrorMessage
        , fErrorAction);

    pTenant->Repaint();
    pTenant->m_fLinkAvail=SUCCEEDED(hr);
    pIOleLink->Release();

    if (FAILED(hr))
        {
        if (fErrorMessage)
            {
            MessageBox(m_pPage->m_hWnd
                , TEXT("Could not update link."), TEXT("Patron")
                , MB_OK);
            }
        }
    else
        m_fDirty=TRUE;

    return hr;
    }






/*
 * CIOleUILinkContainer::CancelLink
 *
 * Purpose:
 *  Requests that the container turn this linked object into a
 *  static object.
 *
 * Parameters:
 *  dwLink          DWORD identifying the linked object.
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CIOleUILinkContainer::CancelLink(DWORD dwLink)
    {
    PCTenant        pTenant=(PCTenant)dwLink;
    LPOLELINK       pIOleLink;
    HRESULT         hr;

    hr=GetObjectInterface(dwLink, IID_IOleLink, (PPVOID)&pIOleLink);

    if (FAILED(hr))
        return hr;

    //This sets the source moniker to NULL.
    m_pDelIUILinks->CancelLink((DWORD)pIOleLink);
    pIOleLink->Release();

    //Go change this object over to a static one.
    pTenant->ConvertToStatic();

    m_fDirty=TRUE;
    return NOERROR;
    }






//PROTECTED FUNCTIONS INTERNAL TO CIOleUILinkContainer


/*
 * CIOleUILinkContainer::GetObjectInterface
 * (Protected)
 *
 * Purpose:
 *  Retrieves and interface pointer for the object identified by
 *  dwLink
 *
 * Parameters:
 *  dwLink          DWORD identifying the object
 *  riid            REFIID of the interface desired.
 *  ppv             PPVOID into which we return the pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, error code otherwise.
 */

STDMETHODIMP CIOleUILinkContainer::GetObjectInterface(DWORD dwLink
    , REFIID riid, PPVOID ppv)
    {
    PCTenant        pTenant=(PCTenant)dwLink;
    LPUNKNOWN       pIUnknown;
    HRESULT         hr;

    pTenant->ObjectGet(&pIUnknown);
    hr=pIUnknown->QueryInterface(riid, ppv);
    pIUnknown->Release();

    return hr;
    }
