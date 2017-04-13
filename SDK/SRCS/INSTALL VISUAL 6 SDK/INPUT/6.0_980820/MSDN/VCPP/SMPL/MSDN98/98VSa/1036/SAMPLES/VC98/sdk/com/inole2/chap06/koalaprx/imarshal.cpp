/*
 * IMARSHAL.CPP
 * Koala Object with Custom Marshaling, Chapter 6
 *
 * IMarshal interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "koala.h"


/*
 * CImpIMarshal::CImpIMarshal
 * CImpIMarshal::~CImpIMarshal
 *
 * Parameters (Constructor):
 *  pObj            PCKoala of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIMarshal::CImpIMarshal(PCKoala pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIMarshal::~CImpIMarshal(void)
    {
    return;
    }



/*
 * CImpIMarshal::QueryInterface
 * CImpIMarshal::AddRef
 * CImpIMarshal::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIMarshal.
 */

STDMETHODIMP CImpIMarshal::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIMarshal::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIMarshal::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIMarshal::GetUnmarshalClass
 * CImpIMarshal::GetMarshalSizeMax
 * CImpIMarshal::MarshalInterface
 * CImpIMarshal::ReleaseMarshalData
 * CImpIMarshal::Disconnect
 *
 * Functions not implemented in a client-side custom marshaling
 * proxy.
 */

STDMETHODIMP CImpIMarshal::GetUnmarshalClass(REFIID riid
    , LPVOID pv, DWORD dwCtx, LPVOID pvCtx, DWORD dwFlags
    , LPCLSID pClsID)
    {
    return ResultFromScode(E_NOTIMPL);
    }


STDMETHODIMP CImpIMarshal::GetMarshalSizeMax(REFIID riid, LPVOID pv
    , DWORD dwDestCtx, LPVOID pvDestCtx, DWORD dwFlags
    , LPDWORD pdwSize)
    {
    return ResultFromScode(E_NOTIMPL);
    }

STDMETHODIMP CImpIMarshal::MarshalInterface(LPSTREAM pstm
    , REFIID riid, LPVOID pv, DWORD dwDestCtx, LPVOID pvDestCtx
    , DWORD dwFlags)
    {
    return ResultFromScode(E_NOTIMPL);
    }

STDMETHODIMP CImpIMarshal::DisconnectObject(DWORD dwReserved)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIMarshal::UnmarshalInterface
 *
 * Purpose:
 *  Initializes a newly created proxy the marshaling packet in
 *  the stream created in the server-side implementation of
 *  MarshalInterface.  This is the primary member of this interface
 *  used on the client side proxy.
 *
 * Parameters:
 *  pStm            LPSTREAM to the stream containing marshal
 *                  data.
 *  riid            REFIID of the interface to be marshaled.
 *  ppv             LPVOID * in which to return the pointer.
 */

STDMETHODIMP CImpIMarshal::UnmarshalInterface(LPSTREAM pstm
    , REFIID riid, LPVOID *ppv)
    {
    KOALAMARSHAL    km;

    pstm->Read((void *)&km, sizeof(KOALAMARSHAL), NULL);
    m_pObj->m_hWndLocal=km.hWnd;

    //Get the pointer to return to the client
    return QueryInterface(riid, ppv);
    }


/*
 * CImpIMarshal::ReleaseMarshalData
 *
 * Purpose:
 *  Destroy a marshaled data packet.
 *
 * Parameters:
 *  pStm            LPSTREAM containing the data to release.
 */

STDMETHODIMP CImpIMarshal::ReleaseMarshalData(LPSTREAM pstm)
    {
    //Nothing for us to do.
    return NOERROR;
    }
