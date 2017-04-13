/*
 * ENUMC.C
 * Enumerator in C Chapter 2
 *
 * Implements the RECTENUMERATOR structure and functions (an object).
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "enumrect.h"


//We have to explicitly define the function table for IEnumRECT in C
static IEnumRECTVtbl  vtEnumRect;
static BOOL           g_fVtblInitialized=FALSE;


/*
 * CreateRECTEnumeratorC
 *
 * Purpose:
 *  Creates an enumerator object returning an IEnumRECT interface.
 *
 * Parameters:
 *  ppEnum          PENUMRECT * in which to return the interface
 *                  pointer on the created object.
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CreateRECTEnumeratorC(PENUMRECT *ppEnum)
    {
    PRECTENUMERATOR     pRE;
    HRESULT             hr;

    if (NULL==ppEnum)
        return FALSE;

    //Create the object
    pRE=RECTENUM_Constructor();

    if (NULL==pRE)
        return FALSE;

    //Get the interface, which calls AddRef
    hr=pRE->lpVtbl->QueryInterface((PENUMRECT)pRE, &IID_IEnumRECT
        , (void **)ppEnum);
    return SUCCEEDED(hr);
    }





/*
 * RECTENUM_Constructor
 *
 * Purpose:
 *  Constructor for an IMPIEnumRect structure
 *
 * Parameters:
 *  None
 */

PRECTENUMERATOR RECTENUM_Constructor(void)
    {
    PRECTENUMERATOR     pRE;
    UINT                i;

    /*
     * First time through initialize function table.  Such a table
     * could be defined as a constant instead of doing explicit
     * initialization here.  However, this method shows exactly
     * which pointers are going where and does not depend on knowing
     * the ordering of the functions in the table, just the names.
     */
    if (!g_fVtblInitialized)
        {
        vtEnumRect.QueryInterface=RECTENUM_QueryInterface;
        vtEnumRect.AddRef        =RECTENUM_AddRef;
        vtEnumRect.Release       =RECTENUM_Release;
        vtEnumRect.Next          =RECTENUM_Next;
        vtEnumRect.Skip          =RECTENUM_Skip;
        vtEnumRect.Reset         =RECTENUM_Reset;
        vtEnumRect.Clone         =RECTENUM_Clone;

        g_fVtblInitialized=TRUE;
        }

    pRE=(PRECTENUMERATOR)malloc(sizeof(RECTENUMERATOR));

    if (NULL==pRE)
        return NULL;

    //Initialize function table pointer
    pRE->lpVtbl=&vtEnumRect;

    //Initialize the array of rectangles
    for (i=0; i < CRECTS; i++)
        SetRect(&pRE->m_rgrc[i], i, i*2, i*3, i*4);

    //Ref counts always start at zero
    pRE->m_cRef=0;

    //Current pointer is the first element.
    pRE->m_iCur=0;

    return pRE;
    }





/*
 * RECTENUM_Destructor
 *
 * Purpose:
 *  Destructor for RECTENUMERATOR structures.
 *
 * Parameters:
 *  pRE            PRECTENUMERATOR to free
 */

void RECTENUM_Destructor(PRECTENUMERATOR pRE)
    {
    if (NULL==pRE)
        return;

    free(pRE);
    return;
    }




/*
 * RECTENUM_QueryInterface
 *
 * Purpose:
 *  Manages interfaces for the RECTENUMERATOR object.
 *
 * Parameters:
 *  pEnum           PENUMRECT to affect
 *  riid            REFIID of the interface to return.
 *  ppv             PPVOID in which to return the pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_NOINTERFACE if the
 *                  interface is not supported.
 */

STDMETHODIMP RECTENUM_QueryInterface(PENUMRECT pEnum
    , REFIID riid, PPVOID ppv)
    {
    //Always NULL the out-parameters
    *ppv=NULL;

    if (IsEqualIID(riid, &IID_IUnknown)
        || IsEqualIID(riid, &IID_IEnumRECT))
        *ppv=pEnum;

    if (NULL==*ppv)
        return ResultFromScode(E_NOINTERFACE);

    //AddRef any interface we'll return.
    ((LPUNKNOWN)*ppv)->lpVtbl->AddRef((LPUNKNOWN)*ppv);
    return NOERROR;
    }







/*
 * RECTENUM_AddRef
 *
 * Purpose:
 *  Increments the reference count on the object.
 *
 * Parameters:
 *  pEnum           PENUMRECT to affect
 *
 * Return Value:
 *  ULONG           New reference count.
 */

STDMETHODIMP_(ULONG) RECTENUM_AddRef(PENUMRECT pEnum)
    {
    PRECTENUMERATOR       pRE=(PRECTENUMERATOR)pEnum;

    return ++pRE->m_cRef;
    }






/*
 * RECTENUM_Release
 *
 * Purpose:
 *  Indicates that someone on whose behalf we once AddRef'd has
 *  finished with the object.  We decrement our reference count
 *  and if zero, we delete the object.
 *
 * Parameters:
 *  pEnum           PENUMRECT to affect
 *
 * Return Value:
 *  ULONG           Current reference count after decrement.  If
 *                  this returns zero then the interface is no
 *                  longer valid.
 */

STDMETHODIMP_(ULONG) RECTENUM_Release(PENUMRECT pEnum)
    {
    PRECTENUMERATOR       pRE=(PRECTENUMERATOR)pEnum;

    if (0!=--pRE->m_cRef)
        return pRE->m_cRef;

    RECTENUM_Destructor(pRE);
    return 0;
    }







/*
 * RECTENUM_Next
 *
 * Purpose:
 *  Returns the next rectangle in the enumerator.
 *
 * Parameters:
 *  pEnum           PENUMRECT to affect
 *  cRect           DWORD number of RECTs to return
 *  prc             LPRECT in which to store the returned RECT.
 *  pdwRects        LPDWORD in which to store the number of
 *                  structs returned.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE otherwise,
 */

STDMETHODIMP RECTENUM_Next(PENUMRECT pEnum, DWORD cRect, LPRECT prc
    , LPDWORD pdwRects)
    {
    PRECTENUMERATOR     pRE=(PRECTENUMERATOR)pEnum;
    DWORD               cRectReturn=0L;

    if (NULL==pdwRects)
        {
        if (1L!=cRect)
            return ResultFromScode(S_FALSE);
        }
    else
        *pdwRects=0L;

    if (NULL==prc || (pRE->m_iCur >= CRECTS))
        return ResultFromScode(S_FALSE);

    while (pRE->m_iCur < CRECTS && cRect > 0)
        {
        *prc++=pRE->m_rgrc[pRE->m_iCur++];
        cRectReturn++;
        cRect--;
        }

    if (NULL!=pdwRects)
        *pdwRects=cRectReturn;

    return NOERROR;
    }





/*
 * RECTENUM_Skip
 *
 * Purpose:
 *  Skips the next n elements in the enumerator.
 *
 * Parameters:
 *  pEnum           PENUMRECT to affect
 *  cSkip           DWORD number of elements to skip.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE if we could not
 *                  skip the requested number.
 */

STDMETHODIMP RECTENUM_Skip(PENUMRECT pEnum, DWORD cSkip)
    {
    PRECTENUMERATOR     pRE=(PRECTENUMERATOR)pEnum;

    if ((pRE->m_iCur+cSkip) >= CRECTS)
        return ResultFromScode(S_FALSE);

    pRE->m_iCur+=cSkip;
    return NOERROR;
    }





/*
 * RECTENUM_Reset
 *
 * Purpose:
 *  Resets the current element in the enumerator to zero.
 *
 * Parameters:
 *  pEnum           PENUMRECT to affect
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP RECTENUM_Reset(PENUMRECT pEnum)
    {
    PRECTENUMERATOR     pRE=(PRECTENUMERATOR)pEnum;

    pRE->m_iCur=0;
    return NOERROR;
    }




/*
 * RECTENUM_Clone
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

STDMETHODIMP RECTENUM_Clone(PENUMRECT pEnum, PENUMRECT *ppEnum)
    {
    PRECTENUMERATOR     pRE=(PRECTENUMERATOR)pEnum;

    if (CreateRECTEnumeratorC(ppEnum))
        {
        /*
         * Copy the current index.  The typecast is safe because
         * we know that the IEnumRECT from the creation function
         * is really a RECTENUMERATOR pointer.
         */
        ((PRECTENUMERATOR)(*ppEnum))->m_iCur=pRE->m_iCur;
        return NOERROR;
        }

    return ResultFromScode(E_OUTOFMEMORY);
    }
