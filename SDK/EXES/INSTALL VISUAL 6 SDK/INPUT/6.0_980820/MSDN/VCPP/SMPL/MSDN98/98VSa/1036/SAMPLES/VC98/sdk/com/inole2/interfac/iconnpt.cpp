/*
 * ICONNPT.CPP
 *
 * Template implemenation of a connection point object.  Usually
 * these objects will be stand-alone objects contained within
 * a connection point container.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iconnpt.h"


/*
 * CConnectionPoint::CConnectionPoint
 * CConnectionPoint::~CConnectionPoint
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 */

CConnectionPoint::CConnectionPoint(LPVOID pObj)
    {
    m_cRef=0;
    m_pObj=pObj;
    return;
    }

CConnectionPoint::~CConnectionPoint(void)
    {
    return;
    }



/*
 * CConnectionPoint::QueryInterface
 * CConnectionPoint::AddRef
 * CConnectionPoint::Release
 *
 * Purpose:
 *  Non-delegating IUnknown members for CConnectionPoint.
 */

STDMETHODIMP CConnectionPoint::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IConnectionPoint==riid)
        *ppv=(LPVOID)this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }

STDMETHODIMP_(ULONG) CConnectionPoint::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CConnectionPoint::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }



/*
 * CConnectionPoint::GetConnectionInterface
 *
 * Purpose:
 *  Returns the IID of the outgoing interface supported through
 *  this connection point.
 *
 * Parameters:
 *  pIID            IID * in which to store the IID.
 */

STDMETHODIMP CConnectionPoint::GetConnectionInterface(IID *pIID)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CConnectionPoint::GetConnectionPointContainer
 *
 * Purpose:
 *  Returns a pointer to the IConnectionPointContainer that
 *  is manageing this connection point.
 *
 * Parameters:
 *  ppCPC           IConnectionPointContainer ** in which to return
 *                  the pointer after calling AddRef.
 */

STDMETHODIMP CConnectionPoint::GetConnectionPointContainer
    (IConnectionPointContainer **ppCPC)
    {
    *ppCPC=NULL;
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CConnectionPoint::Advise
 *
 * Purpose:
 *  Provides this connection point with a notification sink to
 *  call whenever the appropriate outgoing function/event occurs.
 *
 * Parameters:
 *  pUnkSink        LPUNKNOWN to the sink to notify.  The connection
 *                  point must QueryInterface on this pointer to obtain
 *                  the proper interface to call.  The connection
 *                  point must also insure that any pointer held has
 *                  a reference count (QueryInterface will do it).
 *  pdwCookie       DWORD * in which to store the connection key for
 *                  later calls to Unadvise.
 */

STDMETHODIMP CConnectionPoint::Advise(LPUNKNOWN pUnkSink
    , DWORD *pdwCookie)
    {
    *pdwCookie=0;
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CConnectionPoint::Unadvise
 *
 * Purpose:
 *  Terminates the connection to the notification sink identified
 *  with dwCookie (that was returned from Advise).  The connection
 *  point has to Release any held pointers for that sink.
 *
 * Parameters:
 *  dwCookie        DWORD connection key from Advise.
 */

STDMETHODIMP CConnectionPoint::Unadvise(DWORD dwCookie)
    {
    return ResultFromScode(E_NOTIMPL);
    }


/*
 * CConnectionPoint::EnumConnections
 *
 * Purpose:
 *  Creates and returns an enumerator object with the
 *  IEnumConnections interface that will enumerate the IUnknown
 *  pointers of each connected sink.
 *
 * Parameters:
 *  ppEnum          LPENUMCONNECTIONS in which to store the
 *                  IEnumConnections pointer.
 */

STDMETHODIMP CConnectionPoint::EnumConnections
    (LPENUMCONNECTIONS *ppEnum)
    {
    *ppEnum=NULL;
    return ResultFromScode(E_NOTIMPL);
    }
