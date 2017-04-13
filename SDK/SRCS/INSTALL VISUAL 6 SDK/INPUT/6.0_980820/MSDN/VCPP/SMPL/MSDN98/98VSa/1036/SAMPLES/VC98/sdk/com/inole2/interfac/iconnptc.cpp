/*
 * ICONNPTC.CPP
 *
 * Template implemenation of IConnectionPointContainer.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iconnptc.h"


/*
 * CImpIConnectionPointContainer::CImpIConnectionPointContainer
 * CImpIConnectionPointContainer::~CImpIConnectionPointContainer
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIConnectionPointContainer::CImpIConnectionPointContainer
    (LPVOID pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIConnectionPointContainer::~CImpIConnectionPointContainer(void)
    {
    return;
    }



/*
 * CImpIConnectionPointContainer::QueryInterface
 * CImpIConnectionPointContainer::AddRef
 * CImpIConnectionPointContainer::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIConnectionPointContainer.
 */

STDMETHODIMP CImpIConnectionPointContainer::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIConnectionPointContainer::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIConnectionPointContainer::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIConnectionPointContainer::EnumConnectionPoints
 *
 * Purpose:
 *  Creates and returns an enumerator object with the
 *  IEnumConnectionPoints interface that will enumerate the
 *  individual connection points supported in this object.
 *
 * Parameters:
 *  ppEnum          LPENUMCONNECTIONPOINTS in which to store the
 *                  IEnumConnectionPoints pointer.
 */

STDMETHODIMP CImpIConnectionPointContainer::EnumConnectionPoints
    (LPENUMCONNECTIONPOINTS *ppEnum)
    {
    *ppEnum=NULL;
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIConnectionPointContainer::FindConnectionPoint
 *
 * Purpose:
 *  Returns a pointer to the IConnectionPoint for a given
 *  outgoing IID.
 *
 * Parameters:
 *  riid            REFIID of the outgoing interface for which
 *                  a connection point is desired.
 *  ppCP            IConnectionPoint ** in which to return
 *                  the pointer after calling AddRef.
 */

STDMETHODIMP CImpIConnectionPointContainer::FindConnectionPoint
    (REFIID riid, IConnectionPoint **ppCP)
    {
    *ppCP=NULL;
    return ResultFromScode(E_NOTIMPL);
    }
