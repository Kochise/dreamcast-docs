/*
 * IMALLOC.CPP
 *
 * Template IMalloc interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "imalloc.h"


/*
 * CImpIMalloc::CImpIMalloc
 * CImpIMalloc::~CImpIMalloc
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIMalloc::CImpIMalloc(LPVOID pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIMalloc::~CImpIMalloc(void)
    {
    return;
    }



/*
 * CImpIMalloc::QueryInterface
 * CImpIMalloc::AddRef
 * CImpIMalloc::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIMalloc.
 */

STDMETHODIMP CImpIMalloc::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIMalloc::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIMalloc::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }






/*
 * CImpIMalloc::Alloc
 *
 * Purpose:
 *  Allocates memory according to the rules of the allocator
 *  object with this interface.
 *
 * Parameters:
 *  cb              ULONG number of bytes to allocate.
 *
 * Return Value:
 *  void *          Pointer to the reallocated memory
 */


STDMETHODIMP_(void *) CImpIMalloc::Alloc(ULONG cb)
    {
    return NULL;
    }





/*
 * CImpIMalloc::Realloc
 *
 * Purpose:
 *  Reallocates a previous allocation to a different size.
 *
 * Parameters:
 *  pv              void * to the previously allocated memory.
 *  cb              ULONG with the new size.
 *
 * Return Value:
 *  void *          Pointer to the reallocated memory
 */

STDMETHODIMP_(void *) CImpIMalloc::Realloc(void *pv, ULONG cb)
    {
    return NULL;
    }





/*
 * CImpIMalloc::Free
 *
 * Purpose:
 *  Frees and allocation from Alloc.
 *
 * Parameters:
 *  pv              void * of the allocation to free.
 *
 * Return Value:
 *  None
 */


STDMETHODIMP_(void) CImpIMalloc::Free(void *pv)
    {
    return;
    }





/*
 * CImpIMalloc::GetSize
 *
 * Purpose:
 *  Return the size of an allocation.
 *
 * Parameters:
 *  pv              void * of the allocation in question.
 *
 * Return Value:
 *  ULONG           The number of bytes in the allocation.
 */


STDMETHODIMP_(ULONG) CImpIMalloc::GetSize(void *pv)
    {
    return 0;
    }





/*
 * CImpIMalloc::DidAlloc
 *
 * Purpose:
 *  Answers if this allocator allocated the given block of memory.
 *
 * Parameters:
 *  pv              void * of the allocation in question.
 *
 * Return Value:
 *  int             1 if the allocation was made by this allocator,
 *                  0 if not, -1 if the answer is indeterminate.
 */


STDMETHODIMP_(int) CImpIMalloc::DidAlloc(void *pv)
    {
    return -1;
    }





/*
 * CImpIMalloc::HeapMinimize
 *
 * Purpose:
 *  Releases unused memory to the operating system, minimizing the
 *  heap.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */


STDMETHODIMP_(void) CImpIMalloc::HeapMinimize(void)
    {
    return;
    }
