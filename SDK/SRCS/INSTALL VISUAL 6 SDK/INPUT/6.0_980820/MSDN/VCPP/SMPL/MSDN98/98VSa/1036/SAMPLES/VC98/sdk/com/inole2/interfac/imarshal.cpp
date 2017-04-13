/*
 * IMARSHAL.CPP
 *
 * Template IMarshal interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "imarshal.h"


/*
 * CImpIMarshal::CImpIMarshal
 * CImpIMarshal::~CImpIMarshal
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIMarshal::CImpIMarshal(LPVOID pObj, LPUNKNOWN pUnkOuter)
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
 *
 * Purpose:
 *  Determines the class of object to be used to create an
 *  uninitalized proxy in the unmarshaling process.
 *
 * Parameters:
 *  riid            REFIID of the interface to be marshaled.
 *  pv              LPVOID to the interface to be marshaled.
 *  dwCtx           DWORD specifying the relation of the processes
 *                  between which the marshaling is occuring, from the
 *                  MSHCTX enumeration.
 *  pvCtx           LPVOID Reserved for future MSHCTX values.
 *  dwFlags         DWORD specifying why marshaling is taking place.
 *  pClsID          LPCLSID in which to store the proxy CLSID.
 */

STDMETHODIMP CImpIMarshal::GetUnmarshalClass(REFIID riid
    , LPVOID pv, DWORD dwCtx, LPVOID pvCtx, DWORD dwFlags
    , LPCLSID pClsID)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIMarshal::GetMarshalSizeMax
 *
 * Purpose:
 *  Returns the upper memory bound needed to write data into a stream
 *  for IMarshal::MarshalInterface.
 *
 * Parameters:
 *  riid            REFIID of the interface to be marshaled.
 *  pv              LPVOID of the interface to be marshaled.
 *  dwDestCtx       DWORD with the destination context from MSHCTX.
 *  pvDestCtx       LPVOID reserved for future MSHCTX flags.
 *  dwFlags         DWORD specifying why marshaling is taking place.
 *  pdwSize         LPDWORD in which the size is returned.
 */

STDMETHODIMP CImpIMarshal::GetMarshalSizeMax(REFIID riid, LPVOID pv
    , DWORD dwDestCtx, LPVOID pvDestCtx, DWORD dwFlags
    , LPDWORD pdwSize)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIMarshal::MarshalInterface
 *
 * Purpose:
 *  Stores a marshaling packet in a stream for use by a client-side
 *  proxy.
 *
 * Parameters:
 *  pStm            LPSTREAM into which to marshal the interface.
 *  riid            REFIID of the interface to be marshaled.
 *  pv              LPVOID of the interface to be marshaled.
 *  dwDestCtx       DWORD with the destination context from MSHCTX.
 *  pvDestCtx       LPVOID reserved for future MSHCTX flags.
 *  dwFlags         DWORD specifying why marshaling is taking place.
 */

STDMETHODIMP CImpIMarshal::MarshalInterface(LPSTREAM pstm
    , REFIID riid, LPVOID pv, DWORD dwDestCtx, LPVOID pvDestCtx
    , DWORD dwFlags)
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
 *  ppv             LPVOID * in which to return the pointer for the
 *                  client.
 */

STDMETHODIMP CImpIMarshal::UnmarshalInterface(LPSTREAM pstm
    , REFIID riid, LPVOID *ppv)
    {
    return ResultFromScode(E_NOTIMPL);
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
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIMarshal::Disconnect
 *
 * Purpose:
 *  Instructs an object with custom marshaling that it's being
 *  disconnected.
 *
 * Parameters:
 *  dwReserved      DWORD reserved.
 */

STDMETHODIMP CImpIMarshal::DisconnectObject(DWORD dwReserved)
    {
    return ResultFromScode(E_NOTIMPL);
    }
