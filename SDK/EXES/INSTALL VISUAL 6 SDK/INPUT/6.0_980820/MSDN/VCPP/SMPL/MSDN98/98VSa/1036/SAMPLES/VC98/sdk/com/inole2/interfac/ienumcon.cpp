/*
 * IENUMCON.CPP
 *
 * Standard implementation of an enumerator with the
 * IEnumConnections interface that will generally not need
 * modification.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "ienumcon.h"


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
    m_rgConnData=new CONNECTDATA[(UINT)cConn];

    if (NULL!=m_rgConnData)
        {
        for (i=0; i < cConn; i++)
            m_rgConnData[i]=prgConnData[i];
        }

    return;
    }


CEnumConnections::~CEnumConnections(void)
    {
    if (NULL!=m_rgConnData)
        delete [] m_rgConnData;

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

    /*
     * Enumerators are separate objects, so we only need to support
     * ou IUnknown and IEnumConnections interfaces here with no
     * concern for aggregation.
     */
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
        m_rgConnData[m_iCur++].pUnk->AddRef;
        cReturn++;
        cConn--;
        }

    if (NULL!=pulEnum)
        *pulEnum=cReturn;

    return NOERROR;
    }







/*
 * CEnumConnections::Skip
 *
 * Purpose:
 *  Skips the next n elements in the enumeration.
 *
 * Parameters:
 *  cSkip           ULONG number of elements to skip.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE if we could not
 *                  skip the requested number.
 */

STDMETHODIMP CEnumConnections::Skip(ULONG cSkip)
    {
    if (((m_iCur+cSkip) >= m_cConn) || NULL==m_rgConnData)
        return ResultFromScode(S_FALSE);

    m_iCur+=cSkip;
    return NOERROR;
    }






/*
 * CEnumConnections::Reset
 *
 * Purpose:
 *  Resets the current element index in the enumeration to zero.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CEnumConnections::Reset(void)
    {
    m_iCur=0;
    return NOERROR;
    }






/*
 * CEnumConnections::Clone
 *
 * Purpose:
 *  Returns another IEnumConnections with the same state as ourselves.
 *
 * Parameters:
 *  ppEnum          LPENUMCONNECTIONPOINTS * in which to return the
 *                  new object.
 */

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
