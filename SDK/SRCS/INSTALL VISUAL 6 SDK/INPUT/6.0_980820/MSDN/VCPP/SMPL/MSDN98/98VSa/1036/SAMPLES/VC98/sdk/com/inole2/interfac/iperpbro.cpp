/*
 * IPERPBRO.CPP
 *
 * Template IPerPropertyBrowsing interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iperpbro.h"


/*
 * CImpIPerPropertyBrowsing::CImpIPerPropertyBrowsing
 * CImpIPerPropertyBrowsing::~CImpIPerPropertyBrowsing
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIPerPropertyBrowsing::CImpIPerPropertyBrowsing(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIPerPropertyBrowsing::~CImpIPerPropertyBrowsing(void)
    {
    return;
    }



/*
 * CImpIPerPropertyBrowsing::QueryInterface
 * CImpIPerPropertyBrowsing::AddRef
 * CImpIPerPropertyBrowsing::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPerPropertyBrowsing.
 */

STDMETHODIMP CImpIPerPropertyBrowsing::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPerPropertyBrowsing::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPerPropertyBrowsing::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIPerPropertyBrowsing::OnStatusChange
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

STDMETHODIMP CImpIPerPropertyBrowsing::OnStatusChange(DWORD dwFlags)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPerPropertyBrowsing::GetDisplayString
 *
 * Purpose:
 *  Retrieves a description string for a property.
 *
 * Parameters:
 *  dispID          DISPID of the property in question.
 *  pbstr           BSTR * in which to return the string that
 *                  describes the property.  This can be NULL
 *                  indicating that the caller only wants to
 *                  know about availability of the string, not
 *                  the string itself.
 *
 * Return Value:
 *  HRESULT         NOERROR if a string is give, S_FALSE if
 *                  a default string is acceptable.
 */

STDMETHODIMP CImpIPerPropertyBrowsing::GetDisplayString
    (DISPID dispid, BSTR *pbstr)
    {
    if (NULL!=pbstr)
        *pbstr=NULL;

    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPerPropertyBrowsing::MapPropertyToPage
 *
 * Purpose:
 *  Maps a property with a given dispID to a property page CLSID
 *  that can be used to edit this property.
 *
 * Parameters:
 *  dispID          DISPID of the property in question
 *  pCLSID          CLSID * in which to return the CLSID of the
 *                  associated property page.
 *
 * Return Value:
 *  HRESULT         NOERROR if a page is available but not necessarily
 *                  needed to do editing.  S_FALSE if the page must be
 *                  used for editing, CTL_E_NOPAGEAVAILABLE otherwise.
 */

STDMETHODIMP CImpIPerPropertyBrowsing::MapPropertyToPage
    (DISPID dispid, LPCLSID pCLSID)
    {
    *pCLSID=CLSID_NULL;
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIPerPropertyBrowsing::GetPredefinedStrings
 *
 * Purpose:
 *  Allows the property to define known legal strings that a browser
 *  might display in a listbox.
 *
 * Parameters:
 *  dispID          DISPID identifying the property.
 *  pcaStringsOut   CALPOLESTR * in which to store the strings.
 *  pcaCookiesOut   CADWORD * providing identifiers for each string.
 */

STDMETHODIMP CImpIPerPropertyBrowsing::GetPredefinedStrings
    (DISPID dispid, CALPOLESTR *pcaStringsOut
    , CADWORD *pcaCookiesOut)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIPerPropertyBrowsing::GetPredefinedValue
 *
 * Purpose:
 *  Allows the property to define a known legal value that a browser
 *  might display as a default or use in valudation.
 *
 * Parameters:
 *  dispID          DISPID identifying the property.
 *  dwCookie        DWORD identifying the value from
 *                  GetPredefinedStrings.
 *  pVarOut         VARIANT * in which to return the value.
 *
 */

STDMETHODIMP CImpIPerPropertyBrowsing::GetPredefinedValue
    (DISPID dispid, DWORD dwCookie, VARIANT *pVarOut)
    {
    return ResultFromScode(E_NOTIMPL);
    }
