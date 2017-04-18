/*
 * CONNPT.CPP
 *
 * Implemenation of a connection point object that manages
 * IUnknown pointers.  This is a stand-alone object created from
 * the implementation of IConnectionPointContainer.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "connect.h"


/*
 * CConnectionPoint::CConnectionPoint
 * CConnectionPoint::~CConnectionPoint
 *
 * Parameters (Constructor):
 *  pObj            PCConnObject of the object we're in.  We can
 *                  query this for the IConnectionPointContainer
 *                  interface we might need.
 *  riid            REFIID of the interface we're supporting
 */

CConnectionPoint::CConnectionPoint(PCConnObject pObj, REFIID riid)
    {
    UINT        i;

    m_cRef=0;
    m_iid=riid;

    /*
     * Our lifetime is controlled by the connectable object itself,
     * although other external clients will call AddRef and Release.
     * Since we're nested in the connectable object's lifetime,
     * there's no need to call AddRef on pObj.
     */
    m_pObj=pObj;

    for (i=0; i < CCONNMAX; i++)
        {
        m_rgpIUnknown[i]=NULL;
        m_rgdwCookies[i]=0;
        }

    m_cConn=0;
    m_dwCookieNext=100;       //Arbitrary starting cookie value
    return;
    }

CConnectionPoint::~CConnectionPoint(void)
    {
    UINT        i;

    for (i=0; i < CCONNMAX; i++)
        ReleaseInterface(m_rgpIUnknown[i]);

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
    if (NULL==pIID)
        return ResultFromScode(E_POINTER);

    *pIID=m_iid;
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
    UINT            i;
    IUnknown       *pSink;

    *pdwCookie=0;

    //Check if we're already full of sink pointers
    if (CCONNMAX==m_cConn)
        return ResultFromScode(CONNECT_E_ADVISELIMIT);

    /*
     * Verify that the sink has the interface it's supposed
     * to.  We don't have to know what it is because we have
     * m_iid to describe it.  If this works, then we neatly
     * have a pointer with an AddRef that we can stow away.
     */
    if (FAILED(pUnkSink->QueryInterface(m_iid, (PPVOID)&pSink)))
        return ResultFromScode(CONNECT_E_CANNOTCONNECT);

    /*
     * We got the sink, now store it in our array.  We'll look for
     * the first entry that is NULL, indicating a free spot.
     */
    for (i=0; i < CCONNMAX; i++)
        {
        if (NULL==m_rgpIUnknown[i])
            {
            m_rgpIUnknown[i]=pSink;

            /*
             * Note:  this increment is not thread safe.  Needs
             * to be blocked with a semaphore if this were a
             * multi-threaded object.
             */
            m_rgdwCookies[i]=++m_dwCookieNext;
            *pdwCookie=m_dwCookieNext;
            break;
            }
        }

    m_cConn++;
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
    UINT        i;

    if (0==dwCookie)
        return ResultFromScode(E_INVALIDARG);

    for (i=0; i < CCONNMAX; i++)
        {
        if (dwCookie==m_rgdwCookies[i])
            {
            //This releases the sink and sets the pointer to NULL
            ReleaseInterface(m_rgpIUnknown[i]);
            m_rgdwCookies[i]=0;
            m_cConn--;
            return NOERROR;
            }
        }

    return ResultFromScode(CONNECT_E_NOCONNECTION);
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
    LPCONNECTDATA       pCD;
    UINT                i, j;
    PCEnumConnections   pEnum;

    *ppEnum=NULL;

    if (0==m_cConn)
        return ResultFromScode(OLE_E_NOCONNECTION);

    /*
     * Create the array of CONNECTDATA structures to give to the
     * enumerator.
     */
    pCD=new CONNECTDATA[(UINT)m_cConn];

    if (NULL==pCD)
        return ResultFromScode(E_OUTOFMEMORY);

    for (i=0, j=0; i < CCONNMAX; i++)
        {
        if (NULL!=m_rgpIUnknown[i])
            {
            pCD[j].pUnk=(LPUNKNOWN)m_rgpIUnknown[i];
            pCD[j].dwCookie=m_rgdwCookies[i];
            j++;
            }
        }

    /*
     * If creation works, it makes a copy pCD, so we can
     * always delete it regardless of the outcome.
     */
    pEnum=new CEnumConnections(this, m_cConn, pCD);
    delete [] pCD;

    if (NULL==pEnum)
        return ResultFromScode(E_OUTOFMEMORY);

    //This does an AddRef for us.
    return pEnum->QueryInterface(IID_IEnumConnections, (PPVOID)ppEnum);
    }




//Connection Enumerator follows


/*
 * CEnumConnections::CEnumConnections
 * CEnumConnections::~CEnumConnections
 *
 * Parameters (Constructor):
 *  pUnkRef         LPUNKNOWN to use for reference counting.
 *  cConn           ULONG number of connections in prgpConn
 *  prgConnData     LPCONNECTDATA to the array to enumerate.
 */

CEnumConnections::CEnumConnections(LPUNKNOWN pUnkRef, ULONG cConn
    , LPCONNECTDATA prgConnData)
    {
    UINT        i;

    m_cRef=0;
    m_pUnkRef=pUnkRef;

    m_iCur=0;
    m_cConn=cConn;

    /*
     * Copy the passed array.  We need to do this because a clone
     * has to have its own copy as well.
     */
    m_rgConnData=new CONNECTDATA[(UINT)cConn];

    if (NULL!=m_rgConnData)
        {
        for (i=0; i < cConn; i++)
            {
            m_rgConnData[i]=prgConnData[i];
            m_rgConnData[i].pUnk->AddRef();
            }
        }

    return;
    }


CEnumConnections::~CEnumConnections(void)
    {
    if (NULL!=m_rgConnData)
        {
        UINT        i;

        for (i=0; i < m_cConn; i++)
            m_rgConnData[i].pUnk->Release();

        delete [] m_rgConnData;
        }

    return;
    }




/*
 * CEnumConnections::QueryInterface
 * CEnumConnections::AddRef
 * CEnumConnections::Release
 *
 * Purpose:
 *  IUnknown members for CEnumConnections object.
 */

STDMETHODIMP CEnumConnections::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IEnumConnections==riid)
        *ppv=(LPVOID)this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CEnumConnections::AddRef(void)
    {
    ++m_cRef;
    m_pUnkRef->AddRef();
    return m_cRef;
    }

STDMETHODIMP_(ULONG) CEnumConnections::Release(void)
    {
    m_pUnkRef->Release();

    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }





/*
 * CEnumConnections::Next
 *
 * Purpose:
 *  Returns the next element in the enumeration.
 *
 * Parameters:
 *  cConn           ULONG number of connections to return.
 *  pConnData       LPCONNECTDATA in which to store the returned
 *                  structures.
 *  pulEnum         ULONG * in which to return how many we
 *                  enumerated.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE otherwise,
 */

STDMETHODIMP CEnumConnections::Next(ULONG cConn
    , LPCONNECTDATA pConnData, ULONG *pulEnum)
    {
    ULONG               cReturn=0L;

    if (NULL==m_rgConnData)
        return ResultFromScode(S_FALSE);

    if (NULL==pulEnum)
        {
        if (1L!=cConn)
            return ResultFromScode(E_POINTER);
        }
    else
        *pulEnum=0L;

    if (NULL==pConnData || m_iCur >= m_cConn)
        return ResultFromScode(S_FALSE);

    while (m_iCur < m_cConn && cConn > 0)
        {
        *pConnData++=m_rgConnData[m_iCur];
        m_rgConnData[m_iCur++].pUnk->AddRef();
        cReturn++;
        cConn--;
        }

    if (NULL!=pulEnum)
        *pulEnum=cReturn;

    return NOERROR;
    }



STDMETHODIMP CEnumConnections::Skip(ULONG cSkip)
    {
    if (((m_iCur+cSkip) >= m_cConn) || NULL==m_rgConnData)
        return ResultFromScode(S_FALSE);

    m_iCur+=cSkip;
    return NOERROR;
    }


STDMETHODIMP CEnumConnections::Reset(void)
    {
    m_iCur=0;
    return NOERROR;
    }


STDMETHODIMP CEnumConnections::Clone(LPENUMCONNECTIONS *ppEnum)
    {
    PCEnumConnections   pNew;

    *ppEnum=NULL;

    //Create the clone
    pNew=new CEnumConnections(m_pUnkRef, m_cConn, m_rgConnData);

    if (NULL==pNew)
        return ResultFromScode(E_OUTOFMEMORY);

    pNew->AddRef();
    pNew->m_iCur=m_iCur;

    *ppEnum=pNew;
    return NOERROR;
    }
