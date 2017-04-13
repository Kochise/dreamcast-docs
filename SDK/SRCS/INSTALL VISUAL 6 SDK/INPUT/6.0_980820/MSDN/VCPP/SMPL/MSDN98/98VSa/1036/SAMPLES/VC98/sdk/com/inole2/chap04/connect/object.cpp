/*
 * OBJECT.CPP
 *
 * Connectable Object implementation that supports the sample
 * interface IDuckEvents.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "connect.h"


/*
 * CConnObject::CConnObject
 * CConnObject::~CConnObject
 *
 * Constructor Parameters:
 *  None
 */

CConnObject::CConnObject(void)
    {
    UINT        i;

    m_cRef=0;

    for (i=0; i < CCONNPOINTS; i++)
        m_rgpConnPt[i]=NULL;

    return;
    }

CConnObject::~CConnObject(void)
    {
    UINT    i;

    for (i=0; i < CCONNPOINTS; i++)
        {
        if (NULL!=m_rgpConnPt[i])
            {
            if (NULL!=m_rgpConnPt[i])
                delete m_rgpConnPt[i];
            }
        }

    return;
    }



/*
 * CConnObject::Init
 *
 * Purpose:
 *  Instantiates the interface implementations for this object.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeds, FALSE otherwise.
 */

BOOL CConnObject::Init(void)
    {
    UINT    i;

    //Create our connection points
    for (i=0; i < CCONNPOINTS; i++)
        {
        m_rgpConnPt[i]=new CConnectionPoint(this, IID_IDuckEvents);

        if (NULL==m_rgpConnPt[i])
            return FALSE;

        m_rgpConnPt[i]->AddRef();
        }

    return TRUE;
    }



/*
 * CConnObject::QueryInterface
 *
 * Purpose:
 *  Manages the interfaces for this object which supports the
 *  IUnknown, ISampleOne, and ISampleTwo interfaces.
 *
 * Parameters:
 *  riid            REFIID of the interface to return.
 *  ppv             PPVOID in which to store the pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, E_NOINTERFACE if the
 *                  interface is not supported.
 */

STDMETHODIMP CConnObject::QueryInterface(REFIID riid, PPVOID ppv)
    {
    //Always NULL the out-parameters
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IConnectionPointContainer==riid)
        *ppv=this;

    if (NULL==*ppv)
        return ResultFromScode(E_NOINTERFACE);

    ((LPUNKNOWN)*ppv)->AddRef();
    return NOERROR;
    }



/*
 * CConnObject::AddRef
 * CConnObject::Release
 *
 * Reference counting members.  When Release sees a zero count
 * the object destroys itself.
 */

DWORD CConnObject::AddRef(void)
    {
    return ++m_cRef;
    }

DWORD CConnObject::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }



/*
 * CConnObject::EnumConnectionPoints
 *
 * Purpose:
 *  Creates and returns an enumerator object with the
 *  IEnumConnectionPoints interface that will enumerate the
 *  individual connection points supported in this object.
 *
 * Parameters:
 *  ppEnum          LPENUMCONNECTIONPOINTS in which to store the
 *                  IEnumConnectionPoints pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, E_OUTOFMEMORY on failure or
 *                  other error code.
 */

STDMETHODIMP CConnObject::EnumConnectionPoints
    (LPENUMCONNECTIONPOINTS *ppEnum)
    {
    IConnectionPoint       *rgCP[CCONNPOINTS];
    UINT                    i;
    PCEnumConnectionPoints  pEnum;

    *ppEnum=NULL;

    for (i=0; i < CCONNPOINTS; i++)
        rgCP[i]=(IConnectionPoint *)m_rgpConnPt[i];

    //Create the enumerator:  we only have one connection point
    pEnum=new CEnumConnectionPoints(this, CCONNPOINTS, rgCP);

    if (NULL==pEnum)
        return ResultFromScode(E_OUTOFMEMORY);

    pEnum->AddRef();
    *ppEnum=pEnum;
    return NOERROR;
    }



/*
 * CConnObject::FindConnectionPoint
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

STDMETHODIMP CConnObject::FindConnectionPoint(REFIID riid
    , IConnectionPoint **ppCP)
    {
    *ppCP=NULL;

    if (IID_IDuckEvents==riid)
        {
        return m_rgpConnPt[0]->QueryInterface(IID_IConnectionPoint
            , (PPVOID)ppCP);
        }

    return ResultFromScode(E_NOINTERFACE);
    }



/*
 * CConnObject::TriggerEvent
 *
 * Purpose:
 *  Functions to make each connection point generate calls
 *  to any connected sinks.  Since these functions are specific
 *  to IDuckEvents, they only deal with the connection point
 *  for that one interface
 *
 * Parameters:
 *  iEvent          UINT of the event to trigger, either
 *                  EVENT_QUACK, EVENT_FLAP, or EVENT_PADDLE.
 *
 * Return Value:
 *  BOOL            TRUE events are triggered, FALSE if there
 *                  are no connected sinks.
 */

BOOL CConnObject::TriggerEvent(UINT iEvent)
    {
    IEnumConnections   *pEnum;
    CONNECTDATA         cd;

    if (FAILED(m_rgpConnPt[0]->EnumConnections(&pEnum)))
        return FALSE;

    while (NOERROR==pEnum->Next(1, &cd, NULL))
        {
        IDuckEvents    *pDuck;

        if (SUCCEEDED(cd.pUnk->QueryInterface(IID_IDuckEvents
            , (PPVOID)&pDuck)))
            {
            switch (iEvent)
                {
                case EVENT_QUACK:
                    pDuck->Quack();
                    break;

                case EVENT_FLAP:
                    pDuck->Flap();
                    break;

                case EVENT_PADDLE:
                    pDuck->Paddle();
                    break;
                }

            pDuck->Release();
            }

        cd.pUnk->Release();
        }

    pEnum->Release();
    return TRUE;
    }







//Connection Point Enumerator follows


/*
 * CEnumConnectionPoints::CEnumConnectionPoints
 * CEnumConnectionPoints::~CEnumConnectionPoints
 *
 * Parameters (Constructor):
 *  pUnkRef         LPUNKNOWN to use for reference counting.
 *  cPoints         ULONG number of connection points in prgpCP
 *  rgpCP           IConnectionPoint** to the array to enumerate.
 */

CEnumConnectionPoints::CEnumConnectionPoints(LPUNKNOWN pUnkRef
    , ULONG cPoints, IConnectionPoint **rgpCP)
    {
    UINT        i;

    m_cRef=0;
    m_pUnkRef=pUnkRef;

    m_iCur=0;
    m_cPoints=cPoints;
    m_rgpCP=new IConnectionPoint *[(UINT)cPoints];

    if (NULL!=m_rgpCP)
        {
        for (i=0; i < cPoints; i++)
            {
            m_rgpCP[i]=rgpCP[i];
            m_rgpCP[i]->AddRef();
            }
        }

    return;
    }


CEnumConnectionPoints::~CEnumConnectionPoints(void)
    {
    if (NULL!=m_rgpCP)
        {
        UINT        i;

        for (i=0; i < m_cPoints; i++)
            m_rgpCP[i]->Release();

        delete [] m_rgpCP;
        }

    return;
    }




/*
 * CEnumConnectionPoints::QueryInterface
 * CEnumConnectionPoints::AddRef
 * CEnumConnectionPoints::Release
 *
 * Purpose:
 *  IUnknown members for CEnumConnectionPoints object.
 */

STDMETHODIMP CEnumConnectionPoints::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IEnumConnectionPoints==riid)
        *ppv=(LPVOID)this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CEnumConnectionPoints::AddRef(void)
    {
    ++m_cRef;
    m_pUnkRef->AddRef();
    return m_cRef;
    }

STDMETHODIMP_(ULONG) CEnumConnectionPoints::Release(void)
    {
    m_pUnkRef->Release();

    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }





/*
 * CEnumConnectionPoints::Next
 *
 * Purpose:
 *  Returns the next element in the enumeration.
 *
 * Parameters:
 *  cPoints         ULONG number of connection points to return.
 *  ppCP            IConnectionPoint** in which to store the returned
 *                  pointers.
 *  pulEnum         ULONG * in which to return how many we
 *                  enumerated.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE otherwise,
 */

STDMETHODIMP CEnumConnectionPoints::Next(ULONG cPoints
    , IConnectionPoint **ppCP, ULONG *pulEnum)
    {
    ULONG               cReturn=0L;

    if (NULL==m_rgpCP)
        return ResultFromScode(S_FALSE);

    if (NULL==ppCP)
        return ResultFromScode(E_POINTER);

    if (NULL==pulEnum)
        {
        if (1L!=cPoints)
            return ResultFromScode(E_POINTER);
        }
    else
        *pulEnum=0L;

    if (NULL==*ppCP || m_iCur >= m_cPoints)
        return ResultFromScode(S_FALSE);

    while (m_iCur < m_cPoints && cPoints > 0)
        {
        *ppCP=m_rgpCP[m_iCur++];

        if (NULL!=*ppCP)
            (*ppCP)->AddRef();

        ppCP++;
        cReturn++;
        cPoints--;
        }

    if (NULL!=pulEnum)
        *pulEnum=cReturn;

    return NOERROR;
    }







STDMETHODIMP CEnumConnectionPoints::Skip(ULONG cSkip)
    {
    if (((m_iCur+cSkip) >= m_cPoints) || NULL==m_rgpCP)
        return ResultFromScode(S_FALSE);

    m_iCur+=cSkip;
    return NOERROR;
    }


STDMETHODIMP CEnumConnectionPoints::Reset(void)
    {
    m_iCur=0;
    return NOERROR;
    }


STDMETHODIMP CEnumConnectionPoints::Clone
    (LPENUMCONNECTIONPOINTS *ppEnum)
    {
    PCEnumConnectionPoints   pNew;

    *ppEnum=NULL;

    //Create the clone
    pNew=new CEnumConnectionPoints(m_pUnkRef, m_cPoints, m_rgpCP);

    if (NULL==pNew)
        return ResultFromScode(E_OUTOFMEMORY);

    pNew->AddRef();
    pNew->m_iCur=m_iCur;

    *ppEnum=pNew;
    return NOERROR;
    }
