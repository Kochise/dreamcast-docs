/*
 * ICONNPT.CPP
 * Polyline Component Chapter 23
 *
 * Implementation of CImpIConnectionPoint for the Polyline object
 * as well as CConnectionPoint.
 *
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


/*
 * CImpIConnPtCont:CImpIConnPtCont
 * CImpIConnPtCont::~CImpIConnPtCont
 *
 * Constructor Parameters:
 *  pObj            PCPolyline pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIConnPtCont::CImpIConnPtCont(PCPolyline pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }


CImpIConnPtCont::~CImpIConnPtCont(void)
    {
    return;
    }




/*
 * CImpIConnPtCont::QueryInterface
 * CImpIConnPtCont::AddRef
 * CImpIConnPtCont::Release
 */

STDMETHODIMP CImpIConnPtCont::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIConnPtCont::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIConnPtCont::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIConnPtCont::EnumConnectionPoints
 *
 * Purpose:
 *  Not implemented.
 *
 * Return Value:
 *  HRESULT         E_NOTIMPL
 */

STDMETHODIMP CImpIConnPtCont::EnumConnectionPoints
    (LPENUMCONNECTIONPOINTS *ppEnum)
    {
    *ppEnum=NULL;
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIConnPtCont::FindConnectionPoint
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
 *
 * Return Value:
 *  HRESULT         NOERROR if the connection point is found,
 *                  E_NOINTERFACE if it's not supported.
 */

STDMETHODIMP CImpIConnPtCont::FindConnectionPoint(REFIID riid
    , IConnectionPoint **ppCP)
    {
    *ppCP=NULL;

    //CHAPTER24MOD
    if (IID_IPolylineAdviseSink10==riid
        || DIID_DIPolylineAdviseSink10==riid)
        {
        /*
         * This tells the connection point which one we're
         * using.  Note that Polyline only has one
         * connection point and can handle only one sink.
         */
        m_pObj->m_pConnPt->SetIID(riid);

        return m_pObj->m_pConnPt->QueryInterface
            (IID_IConnectionPoint, (PPVOID)ppCP);
        }
    //End CHAPTER24MOD

    return ResultFromScode(E_NOINTERFACE);
    }





//CConnectionPoint implementation

/*
 * CConnectionPoint::CConnectionPoint
 * CConnectionPoint::~CConnectionPoint
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.  We can
 *                  query this for the IConnectionPointContainer
 *                  interface we might need.
 */

CConnectionPoint::CConnectionPoint(PCPolyline pObj)
    {
    m_cRef=0;

    /*
     * Our lifetime is controlled by the connectable object itself,
     * although other external clients will call AddRef and Release.
     * Since we're nested in the connectable object's lifetime,
     * there's no need to call AddRef on pObj.
     */
    m_pObj=pObj;
    return;
    }

CConnectionPoint::~CConnectionPoint(void)
    {
    ReleaseInterface(m_pObj->m_pAdv);
    return;
    }



//CHAPTER24MOD

/*
 * CConnectionPoint::SetIID
 *
 * Purpose:
 *  Informs the connection point which outgoing interface
 *  it should use (vtable or dispatch interface).
 *
 * Parameters:
 *  riid            REFIID of the interface we're using.
 */

void CConnectionPoint::SetIID(REFIID riid)
    {
    m_iid=riid;
    return;
    }

//End CHAPTER24MOD




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
    if (NULL==pIID)
        return ResultFromScode(E_POINTER);

    //CHPATER24MOD
    *pIID=m_iid;
    //End CHAPTER24MOD
    return NOERROR;
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
    return m_pObj->QueryInterface(IID_IConnectionPointContainer
        , (void **)ppCPC);
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
    IPolylineAdviseSink10  *pSink;

    *pdwCookie=0;

    //Only allow one connection
    if (NULL!=m_pObj->m_pAdv)
        return ResultFromScode(CONNECT_E_ADVISELIMIT);

    //CHAPTER24MOD
    /*
     * Polyline code is set to handle calls to
     * IPolylineAdviseSink10 everywhere else around the code.
     * To handle calling a control container's dispinterface
     * implementation of the dispatch version of this interface,
     * we'll create an instance of our own CAdviseRouter
     * and get an IPolylineAdviseSink10 from it.  That router
     * will then convert vtable calls into IDispatch calls.
     */
    if (DIID_DIPolylineAdviseSink10==m_iid)
        {
        IDispatch  *pIDisp;

        if (FAILED(pUnkSink->QueryInterface(m_iid
            , (PPVOID)&pIDisp)))
            {
            return ResultFromScode(CONNECT_E_CANNOTCONNECT);
            }

        /*
         * We have IDispatch, create a wrapper for it,
         * which takes ownership of the pointer.
         */
        pSink=new CAdviseRouter(pIDisp, m_pObj);
        pSink->AddRef();
        }

    //Otherwise, do what we always did before
    if (IID_IPolylineAdviseSink10==m_iid)
        {
        //Check for the right interface on the sink.
        if (FAILED(pUnkSink->QueryInterface(m_iid
            , (PPVOID)&pSink)))
            {
            return ResultFromScode(CONNECT_E_CANNOTCONNECT);
            }
        }
    //End CHAPTER24MOD


    *pdwCookie=ADVISEKEY;
    m_pObj->m_pAdv=pSink;
    return NOERROR;
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
    if (0==dwCookie)
        return ResultFromScode(E_INVALIDARG);

    if (ADVISEKEY!=dwCookie)
        ResultFromScode(CONNECT_E_NOCONNECTION);

    ReleaseInterface(m_pObj->m_pAdv);
    return NOERROR;
    }



/*
 * CConnectionPoint::EnumConnections
 *
 * Purpose:
 *  Not implemented.
 */

STDMETHODIMP CConnectionPoint::EnumConnections
    (LPENUMCONNECTIONS *ppEnum)
    {
    *ppEnum=NULL;
    return ResultFromScode(E_NOTIMPL);
    }
