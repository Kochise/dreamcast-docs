/*
 * ISIMPSIT.CPP
 *
 * Template ISimpleFrameSite interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "isimpsit.h"


/*
 * CImpISimpleFrameSite::CImpISimpleFrameSite
 * CImpISimpleFrameSite::~CImpISimpleFrameSite
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpISimpleFrameSite::CImpISimpleFrameSite(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpISimpleFrameSite::~CImpISimpleFrameSite(void)
    {
    return;
    }



/*
 * CImpISimpleFrameSite::QueryInterface
 * CImpISimpleFrameSite::AddRef
 * CImpISimpleFrameSite::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpISimpleFrameSite.
 */

STDMETHODIMP CImpISimpleFrameSite::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpISimpleFrameSite::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpISimpleFrameSite::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpISimpleFrameSite::PreMessageFilter
 *
 * Purpose:
 *  Allows the simple frame to pre-process messages that are
 *  going to controls within it.
 *
 * Parameters:
 *  Same as to a window procedure, plus:
 *  plResult        LRESULT * in which to store the return value
 *                  for the message.
 *  pdwCookie       DWORD * in which to store extra information to
 *                  pass to PostMessageFilter
 */

STDMETHODIMP CImpISimpleFrameSite::PreMessageFilter(HWND hWnd
    , UINT iMsg, WPARAM wParam, LPARAM lParam, LRESULT *plResult
    , DWORD *pdwCookie)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpISimpleFrameSite::PostMessageFilter
 *
 * Purpose:
 *  Allows the simple frame to post-process messages that are
 *  going to controls within it.
 *
 * Parameters:
 *  Same as to a window procedure, plus:
 *  plResult        LRESULT * in which to store the return value
 *                  for the message.
 *  dwCookie        DWORD from PreMessageFilter
 */

STDMETHODIMP CImpISimpleFrameSite::PostMessageFilter(HWND hWnd
    , UINT iMsg, WPARAM wParam, LPARAM lParam, LRESULT *plResult
    , DWORD dwCookie)
    {
    return ResultFromScode(E_NOTIMPL);
    }
