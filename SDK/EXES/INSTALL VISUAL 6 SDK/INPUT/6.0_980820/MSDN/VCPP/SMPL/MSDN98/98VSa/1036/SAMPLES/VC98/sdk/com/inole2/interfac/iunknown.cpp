/*
 * IUNKNOWN.CPP
 *
 * Template implementation of a delegating IUnknown.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iunknown.h"


/*
 * CImpIUnknown::CImpIUnknown
 * CImpIUnknown::~CImpIUnknown
 *
 * Constructor Parameters:
 *  pObj            LPVOID of the object containing us.
 *  pUnkOuter       LPUNKNOWN to which we blindly delegate
 *                  all IUnknown calls.
 */

CImpIUnknown::CImpIUnknown(LPVOID pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;

    /*
     * We don't need to AddRef pUnkOuter since it defines
     * our lifetime.
     */
    m_pUnkOuter=pUnkOuter;
    return;
    }


CImpIUnknown::~CImpIUnknown(void)
    {
    return;
    }




/*
 * CImpIUnknown::QueryInterface
 *
 * Purpose:
 *  Delegate to whoever is providing IUnknown implementations
 *  for this interface.  May be our containing object, may be
 *  a controlling unknown.  We don't care.
 *
 * Parameters:
 *  riid            REFIID being asked for.
 *  ppv             LPVOID * in which to return the interface.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise contains
 *                  E_NOINTERFACE.
 */

STDMETHODIMP CImpIUnknown::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }





/*
 * CImpIUnknown::AddRef
 *
 * Purpose:
 *  Increments the interface reference count (for debugging) and
 *  delegates to whoever is controlling this interface.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  ULONG           New reference count of the object.
 */

STDMETHODIMP_(ULONG) CImpIUnknown::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }






/*
 * CImpIUnknown::Release
 *
 * Purpose:
 *  Decrements the interface reference count (for debugging) and
 *  delegates to whoever is controlling this interface.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  ULONG           Current reference count after decrement.  If
 *                  this returns zero then the interface is no
 *                  longer valid because the object is dead.
 */

STDMETHODIMP_(ULONG) CImpIUnknown::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }
