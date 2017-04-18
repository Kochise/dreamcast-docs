/*
 * IPROVINF.CPP
 *
 * Template IProvideClassInfo interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iprovinf.h"


/*
 * CImpIProvideClassInfo::CImpIProvideClassInfo
 * CImpIProvideClassInfo::~CImpIProvideClassInfo
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIProvideClassInfo::CImpIProvideClassInfo(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIProvideClassInfo::~CImpIProvideClassInfo(void)
    {
    return;
    }



/*
 * CImpIProvideClassInfo::QueryInterface
 * CImpIProvideClassInfo::AddRef
 * CImpIProvideClassInfo::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIProvideClassInfo.
 */

STDMETHODIMP CImpIProvideClassInfo::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIProvideClassInfo::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIProvideClassInfo::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIProvideClassInfo::GetClassInfo
 *
 * Purpose:
 *  Returns the ITypeInfo through which the caller can retrieve
 *  information about the entire object.
 *
 * Parameters:
 *  ppTI            LPTYPEINFO * in which to store the ITypeInfo
 *                  pointer.
 */

STDMETHODIMP CImpIProvideClassInfo::GetClassInfo(LPTYPEINFO *ppTI)
    {
    return ResultFromScode(E_NOTIMPL);
    }
