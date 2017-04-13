/*
 * IENUMVRB.CPP
 *
 * Standard implementation of am OLEVERB enumerator with the
 * IEnumOLEVERB interface that will generally not need
 * modification.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "ienumvrb.h"


/*
 * CEnumOLEVERB::CEnumOLEVERB
 * CEnumOLEVERB::~CEnumOLEVERB
 *
 * Parameters (Constructor):
 *  pUnkRef         LPUNKNOWN to use for reference counting.
 *  cVerb           ULONG number of OLEVERBs in prgVerb
 *  prgVerb         LPOLEVERB * to the array to enumerate.
 */

CEnumOLEVERB::CEnumOLEVERB(LPUNKNOWN pUnkRef, ULONG cVerb
    , LPOLEVERB *prgVerb)
    {
    UINT        i;

    m_cRef=0;
    m_pUnkRef=pUnkRef;

    m_iCur=0;
    m_cVerb=cVerb;
    m_prgVerb=new LPOLEVERB[(UINT)cVerb];

    if (NULL!=m_prgVerb)
        {
        for (i=0; i < cVerb; i++)
            m_prgVerb[i]=prgVerb[i];
        }

    return;
    }


CEnumOLEVERB::~CEnumOLEVERB(void)
    {
    if (NULL!=m_prgVerb)
        delete [] m_prgVerb;

    return;
    }






/*
 * CEnumOLEVERB::QueryInterface
 * CEnumOLEVERB::AddRef
 * CEnumOLEVERB::Release
 *
 * Purpose:
 *  IUnknown members for CEnumOLEVERB object.
 */

STDMETHODIMP CEnumOLEVERB::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IEnumOLEVERB==riid)
        *ppv=(LPVOID)this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CEnumOLEVERB::AddRef(void)
    {
    ++m_cRef;
    m_pUnkRef->AddRef();
    return m_cRef;
    }

STDMETHODIMP_(ULONG) CEnumOLEVERB::Release(void)
    {
    m_pUnkRef->Release();

    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }







/*
 * CEnumOLEVERB::Next
 *
 * Purpose:
 *  Returns the next element in the enumeration.
 *
 * Parameters:
 *  cVerb           ULONG number of OLEVERBs to return.
 *  pVerb           LPOLEVERB in which to store the returned
 *                  structures.
 *  pulVerb         ULONG * in which to return how many we
 *                  enumerated.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE otherwise,
 */

STDMETHODIMP CEnumOLEVERB::Next(ULONG cVerb, LPOLEVERB pVerb
    , ULONG *pulVerb)
    {
    ULONG               cReturn=0L;

    if (NULL==m_prgVerb)
        return ResultFromScode(S_FALSE);

    if (NULL==pulVerb)
        {
        if (1L!=cVerb)
            return ResultFromScode(E_POINTER);
        }
    else
        *pulVerb=0L;

    if (NULL==pVerb || m_iCur >= m_cVerb)
        return ResultFromScode(S_FALSE);

    while (m_iCur < m_cVerb && cVerb > 0)
        {
        *pVerb++=*m_prgVerb[m_iCur++];
        cReturn++;
        cVerb--;
        }

    if (NULL!=pulVerb)
        *pulVerb=cReturn;

    return NOERROR;
    }







/*
 * CEnumOLEVERB::Skip
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

STDMETHODIMP CEnumOLEVERB::Skip(ULONG cSkip)
    {
    if (((m_iCur+cSkip) >= m_cVerb) || NULL==m_prgVerb)
        return ResultFromScode(S_FALSE);

    m_iCur+=cSkip;
    return NOERROR;
    }






/*
 * CEnumOLEVERB::Reset
 *
 * Purpose:
 *  Resets the current element index in the enumeration to zero.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CEnumOLEVERB::Reset(void)
    {
    m_iCur=0;
    return NOERROR;
    }






/*
 * CEnumOLEVERB::Clone
 *
 * Purpose:
 *  Returns another IEnumOLEVERB with the same state as ourselves.
 *
 * Parameters:
 *  ppEnum          LPENUMOLEVERB * in which to return the
 *                  new object.
 */

STDMETHODIMP CEnumOLEVERB::Clone(LPENUMOLEVERB *ppEnum)
    {
    PCEnumOLEVERB   pNew;

    *ppEnum=NULL;

    //Create the clone
    pNew=new CEnumOLEVERB(m_pUnkRef, m_cVerb, m_prgVerb);

    if (NULL==pNew)
        return ResultFromScode(E_OUTOFMEMORY);

    pNew->AddRef();
    pNew->m_iCur=m_iCur;

    *ppEnum=pNew;
    return NOERROR;
    }
