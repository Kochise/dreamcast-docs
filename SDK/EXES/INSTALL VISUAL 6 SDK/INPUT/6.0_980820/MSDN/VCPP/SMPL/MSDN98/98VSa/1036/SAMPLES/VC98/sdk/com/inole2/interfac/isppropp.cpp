/*
 * ISPPROPP.CPP
 *
 * Template ISpecifyPropertyPages interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "isppropp.h"


/*
 * CImpISpecifyPropertyPages::CImpISpecifyPropertyPages
 * CImpISpecifyPropertyPages::~CImpISpecifyPropertyPages
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpISpecifyPropertyPages::CImpISpecifyPropertyPages(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpISpecifyPropertyPages::~CImpISpecifyPropertyPages(void)
    {
    return;
    }



/*
 * CImpISpecifyPropertyPages::QueryInterface
 * CImpISpecifyPropertyPages::AddRef
 * CImpISpecifyPropertyPages::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpISpecifyPropertyPages.
 */

STDMETHODIMP CImpISpecifyPropertyPages::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpISpecifyPropertyPages::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpISpecifyPropertyPages::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpISpecifyPropertyPages::GetPages
 *
 * Purpose:
 *  Returns an array of GUIDs identifying the indivudual property
 *  pages used for this object.
 *
 * Parameters:
 *  pPages          CAUUID * pointing to a counted array of GUIDs.
 *                  This function allocates the array elements
 *                  and stores them in this structure.
 */

STDMETHODIMP CImpISpecifyPropertyPages::GetPages(CAUUID *pPages)
    {
    return ResultFromScode(E_NOTIMPL);
    }
