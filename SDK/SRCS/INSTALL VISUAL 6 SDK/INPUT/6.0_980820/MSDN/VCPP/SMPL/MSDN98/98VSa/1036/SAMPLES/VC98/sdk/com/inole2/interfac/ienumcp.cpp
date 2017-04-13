/*
 * IENUMCP.CPP
 *
 * Standard implementation of an IConnectionPoint enumerator with the
 * IEnumConnectionPoints interface that will generally not need
 * modification.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "ienumcp.h"


/*
 * CEnumConnectionPoints::CEnumConnectionPoints
 * CEnumConnectionPoints::~CEnumConnectionPoints
 *
 * Parameters (Constructor):
 *  pUnkRef         LPUNKNOWN to use for reference counting.
 *  cPoints         ULONG number of connection points in rgpCP
 *  rgpCP           LPCONNECTIONPOINT * to the array to enumerate.
 */

CEnumConnectionPoints::CEnumConnectionPoints(LPUNKNOWN pUnkRef
    , ULONG cPoints, LPCONNECTIONPOINT *rgpCP)
    {
    UINT        i;

    m_cRef=0;
    m_pUnkRef=pUnkRef;

    m_iCur=0;
    m_cPoints=cPoints;
    m_rgpCP=new LPCONNECTIONPOINT[(UINT)cPoints];

    if (NULL!=m_rgpCP)
        {
        for (i=0; i < cPoints; i++)
            m_rgpCP[i]=rgpCP[i];
        }

    return;
    }


CEnumConnectionPoints::~CEnumConnectionPoints(void)
    {
    if (NULL!=m_rgpCP)
        delete [] m_rgpCP;

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

    /*
     * Enumerators are separate objects, not the data object, so
     * we only need to support out IUnknown and IEnumConnectionPoints
     * interfaces here with no concern for aggregation.
     */
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
 *  pCP             LPCONNECTIONPOINT in which to store the returned
 *                  pointers.
 *  pulEnum         ULONG * in which to return how many we
 *                  enumerated.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE otherwise,
 */

STDMETHODIMP CEnumConnectionPoints::Next(ULONG cPoints
    , LPCONNECTIONPOINT *pCP, ULONG *pulEnum)
    {
    ULONG               cReturn=0L;

    if (NULL==m_rgpCP)
        return ResultFromScode(S_FALSE);

    if (NULL==pulEnum)
        {
        if (1L!=cPoints)
            return ResultFromScode(E_POINTER);
        }
    else
        *pulEnum=0L;

    if (NULL==pCP || m_iCur >= m_cPoints)
        return ResultFromScode(S_FALSE);

    while (m_iCur < m_cPoints && cPoints > 0)
        {
        *pCP=m_rgpCP[m_iCur++];

        if (NULL!=*pCP)
            (*pCP)->AddRef();

        pCP++;
        cReturn++;
        cPoints--;
        }

    if (NULL!=pulEnum)
        *pulEnum=cReturn;

    return NOERROR;
    }







/*
 * CEnumConnectionPoints::Skip
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

STDMETHODIMP CEnumConnectionPoints::Skip(ULONG cSkip)
    {
    if (((m_iCur+cSkip) >= m_cPoints) || NULL==m_rgpCP)
        return ResultFromScode(S_FALSE);

    m_iCur+=cSkip;
    return NOERROR;
    }






/*
 * CEnumConnectionPoints::Reset
 *
 * Purpose:
 *  Resets the current element index in the enumeration to zero.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CEnumConnectionPoints::Reset(void)
    {
    m_iCur=0;
    return NOERROR;
    }






/*
 * CEnumConnectionPoints::Clone
 *
 * Purpose:
 *  Returns another IEnumConnectionPoints with the same state as ourselves.
 *
 * Parameters:
 *  ppEnum          LPENUMCONNECTIONPOINTS * in which to return the
 *                  new object.
 */

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
