/*
 * ENUMCPP.CPP
 * Enumerator in C++ Chapter 2
 *
 * Implements the CEnumRECT class
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "enumrect.h"


/*
 * CreateRECTEnumeratorCPP
 *
 * Purpose:
 *  Creates an enumerator object returning an IEnumRECT interface.
 *
 * Parameters:
 *  ppEnum          PENUMRECT * in which to return the
 *                  interface pointer on the created object.
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CreateRECTEnumeratorCPP(PENUMRECT *ppEnum)
    {
    PCEnumRect  pER;
    HRESULT     hr;

    if (NULL==ppEnum)
        return FALSE;

    //Create the object
    pER=new CEnumRect();

    if (NULL==pER)
        return FALSE;

    //Get the interface, which calls AddRef
    hr=pER->QueryInterface(IID_IEnumRECT, (void **)ppEnum);
    return SUCCEEDED(hr);
    }





/*
 * CEnumRect::CEnumRect
 * CEnumRect::~CEnumRect
 *
 * Constructor Parameters:
 *  None
 */

CEnumRect::CEnumRect(void)
    {
    UINT        i;

    //Initialize the array of rectangles
    for (i=0; i < CRECTS; i++)
        SetRect(&m_rgrc[i], i, i*2, i*3, i*4);

    //Ref counts always start at zero
    m_cRef=0;

    //Current pointer is the first element.
    m_iCur=0;

    return;
    }


CEnumRect::~CEnumRect(void)
    {
    return;
    }




/*
 * CEnumRect::QueryInterface
 *
 * Purpose:
 *  Manages interfaces for the CEnumRect object.
 *
 * Parameters:
 *  riid            REFIID of the interface to return.
 *  ppv             PPVOID in which to return the pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_NOINTERFACE if the
 *                  interface is not supported.
 */

STDMETHODIMP CEnumRect::QueryInterface(REFIID riid, PPVOID ppv)
    {
    //Always NULL the out-parameters
    *ppv=NULL;

    /*
     * No explicit typecast necessary since we singly derive
     * from IEnumRECT.
     */
    if (IID_IUnknown==riid || IID_IEnumRECT==riid)
        *ppv=this;

    if (NULL==*ppv)
        return ResultFromScode(E_NOINTERFACE);

    //AddRef any interface we'll return.
    ((LPUNKNOWN)*ppv)->AddRef();
    return NOERROR;
    }




/*
 * CEnumRect::AddRef
 *
 * Purpose:
 *  Increments the reference count on the object.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  ULONG           New reference count.
 */

STDMETHODIMP_(ULONG) CEnumRect::AddRef(void)
    {
    return ++m_cRef;
    }






/*
 * CEnumRect::Release
 *
 * Purpose:
 *  Indicates that someone on whose behalf we once AddRef'd has
 *  finished with the object.  We decrement our reference count
 *  and if zero, we delete the object.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  ULONG           Current reference count after decrement.  If
 *                  this returns zero then the interface is no
 *                  longer valid.
 */

STDMETHODIMP_(ULONG) CEnumRect::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }







/*
 * CEnumRect::Next
 *
 * Purpose:
 *  Returns the next rectangle in the enumerator.
 *
 * Parameters:
 *  cRect           DWORD number of RECTs to return
 *  prc             LPRECT in which to store the returned RECT.
 *  pdwRects        LPDWORD in which to store the number of
 *                  structs returned.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE otherwise,
 */

STDMETHODIMP CEnumRect::Next(DWORD cRect, LPRECT prc, LPDWORD pdwRects)
    {
    DWORD           cRectReturn=0L;

    if (NULL==pdwRects)
        {
        if (1L!=cRect)
            return ResultFromScode(S_FALSE);
        }
    else
        *pdwRects=0L;

    if (NULL==prc || (m_iCur >= CRECTS))
        return ResultFromScode(S_FALSE);

    while (m_iCur < CRECTS && cRect > 0)
        {
        *prc++=m_rgrc[m_iCur++];
        cRectReturn++;
        cRect--;
        }

    if (NULL!=pdwRects)
        *pdwRects=cRectReturn;

    return NOERROR;
    }





/*
 * CEnumRect::Skip
 *
 * Purpose:
 *  Skips the next n elements in the enumerator.
 *
 * Parameters:
 *  cSkip           DWORD number of elements to skip.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE if we could not
 *                  skip the requested number.
 */

STDMETHODIMP CEnumRect::Skip(DWORD cSkip)
    {
    if ((m_iCur+cSkip) >= CRECTS)
        return ResultFromScode(S_FALSE);

    m_iCur+=cSkip;
    return NOERROR;
    }




/*
 * CEnumRect::Reset
 *
 * Purpose:
 *  Resets the current element in the enumerator to zero.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CEnumRect::Reset(void)
    {
    m_iCur=0;
    return NOERROR;
    }




/*
 * CImpEnumRECT::Clone
 *
 * Purpose:
 *  Creates a copy enumerator.
 *
 * Parameters:
 *  ppEnum          PENUMRECT * in which to store the clone.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, error code otherwise.
 */

STDMETHODIMP CEnumRect::Clone(PENUMRECT *ppEnum)
    {
    if (CreateRECTEnumeratorCPP(ppEnum))
        {
        /*
         * Copy the current index.  The typecast is safe because
         * we know that the IEnumRECT from the creation function
         * is really a CEnumRect pointer.
         */
        ((PCEnumRect)(*ppEnum))->m_iCur=m_iCur;
        return NOERROR;
        }

    return ResultFromScode(E_OUTOFMEMORY);
    }
