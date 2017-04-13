//+---------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1994 - 1996.
//
//  File:       cmallspy.cxx
//
//  Contents:   Sample implementation of IMallocSpy.  The implementation here
//              is pretty simple.  It assumes that all we want to do is keep
//              a header on the front of all allocations so we can note
//              interesting information.
//
//  Classes:    CMallocSpy
//
//----------------------------------------------------------------------


#include <ole2.h>
#include "cmallspy.hxx"



const ULONG HEADERSIZE = 128;



//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::CMallocSpy
//
//  Synopsis:   Constructor
//
//  Returns:
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
CMallocSpy::CMallocSpy(void)
{
    m_cRef = 0;
}




//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::~CMallocSpy
//
//  Synopsis:   Destructor
//
//  Returns:
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
CMallocSpy::~CMallocSpy(void)
{
    // Nothing to do here
}




//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::QueryInterface
//
//  Synopsis:   Only IUnknown and IMallocSpy are meaningful
//
//  Arguments:  [riid] --
//              [ppUnk] --
//
//  Returns:    S_OK or E_NOINTERFACE
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
HRESULT CMallocSpy::QueryInterface(REFIID riid, LPVOID *ppUnk)
{
    HRESULT hr = S_OK;

    if (IsEqualIID(riid, IID_IUnknown))
    {
        *ppUnk = (IUnknown *) this;
    }
    else if (IsEqualIID(riid, IID_IMallocSpy))
    {
        *ppUnk =  (IMalloc *) this;
    }
    else
    {
        *ppUnk = NULL;
        hr =  E_NOINTERFACE;
    }
    AddRef();
    return hr;
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::AddRef
//
//  Synopsis:   Add a reference
//
//  Returns:    New reference count
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
ULONG CMallocSpy::AddRef(void)
{
    return ++m_cRef;
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::Release
//
//  Synopsis:   Remove a reference
//
//  Returns:    The new reference count
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
ULONG CMallocSpy::Release(void)
{
    ULONG cRef;

    cRef = --m_cRef;
    if (cRef == 0)
    {
        delete this;
    }
    return cRef;
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PreAlloc
//
//  Synopsis:   Called prior to OLE calling IMalloc::Alloc
//
//  Arguments:  [cbRequest] -- The number of bytes the caller of
//                             is requesting IMalloc::Alloc
//
//  Returns:    The count of bytes to actuallay allocate
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
ULONG CMallocSpy::PreAlloc(ULONG cbRequest)
{
    m_cbRequest = cbRequest;
    return cbRequest + HEADERSIZE;
}




//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PostAlloc
//
//  Synopsis:   Called after OLE calls IMalloc::Alloc
//
//  Arguments:  [pActual] -- The allocation returned by IMalloc::Alloc
//
//  Returns:    The allocation pointer to return to the caller of
//              IMalloc::Alloc
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
void *CMallocSpy::PostAlloc(void *pActual)
{
    // Store interesting information in the first HEADERSIZE bytes
    // of the allcation
    // ...

    // Return the allocation plus offset
    return (void *) (((BYTE *) pActual) + HEADERSIZE);
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PreFree
//
//  Synopsis:   Called prior to OLE calling IMalloc::Free
//
//  Arguments:  [pRequest] -- The allocation to be freed
//              [fSpyed]   -- Whether it was allocated with a spy active
//
//  Returns:
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
void *CMallocSpy::PreFree(void *pRequest, BOOL fSpyed)
{
    // Use the stored information
    // ...

    // Check for NULL
    if (pRequest == NULL)
    {
        return NULL;
    }

    // Undo the offset
    if (fSpyed)
    {
        return (void *) (((BYTE *) pRequest) - HEADERSIZE);
    }
    else
    {
        return pRequest;
    }
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PostFree
//
//  Synopsis:   Called after OLE calls IMalloc::Free
//
//  Arguments:  [fSpyed]   -- Whether it was allocated with a spy active
//
//  Returns:
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
void CMallocSpy::PostFree(BOOL fSpyed)
{
    // Note the free or whatever

    return;
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PreRealloc
//
//  Synopsis:   Called prior to OLE calling IMalloc::Realloc
//
//  Arguments:  [pRequest]     -- The buffer to be reallocated
//              [cbRequest]    -- The requested new size of the buffer
//              [ppNewRequest] -- Where to store the new buffer pointer
//                                to be reallocated
//              [fSpyed]       -- Whether it was allocated with a spy active
//
//  Returns:    The new size to actually be allocated
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
ULONG CMallocSpy::PreRealloc(void *pRequest, ULONG cbRequest,
                             void **ppNewRequest, BOOL fSpyed)
{
    // Typically we don't need to extend/distend the header
    if (fSpyed)
    {
        *ppNewRequest = (void *) (((BYTE *) pRequest) - HEADERSIZE);
        return cbRequest + HEADERSIZE;
    }
    else
    {
        *ppNewRequest = pRequest;
        return cbRequest;
    }
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PostRealloc
//
//  Synopsis:   Called after OLE calls IMalloc::Realloc
//
//  Arguments:  [pActual] -- Pointer to the reallocated buffer
//              [fSpyed]  -- Whether it was allocated with a spy active
//
//  Returns:    The buffer pointer to return
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
void *CMallocSpy::PostRealloc(void *pActual, BOOL fSpyed)
{
    // Return the buffer with the header offset
    if (fSpyed)
    {
        return (void *) (((BYTE *) pActual) + HEADERSIZE);
    }
    else
    {
        return pActual;
    }

    // If we extend/distend the header for a reallocation, then we'd
    // have to do some more work here
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PreGetSize
//
//  Synopsis:   Called prior to OLE calling IMalloc::GetSize
//
//  Arguments:  [pRequest] -- The buffer whose size is to be returned
//              [fSpyed]   -- Whether it was allocated with a spy active
//
//  Returns:    The actual buffer with which to call IMalloc::GetSize
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
void *CMallocSpy::PreGetSize(void *pRequest, BOOL fSpyed)
{
    if (fSpyed)
    {
        return (void *) (((BYTE *) pRequest) - HEADERSIZE);
    }else
    {
        return pRequest;
    }
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PostGetSize
//
//  Synopsis:   Called after OLE calls IMalloc::GetSize
//
//  Arguments:  [cbActual] -- The result of IMalloc::GetSize
//              [fSpyed]   -- Whether it was allocated with a spy active
//
//  Returns:    The size to return to the IMalloc::GetSize caller
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
ULONG CMallocSpy::PostGetSize(ULONG cbActual, BOOL fSpyed)
{
    if (fSpyed)
    {
        return cbActual - HEADERSIZE;
    }
    else
    {
        return cbActual;
    }
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PreDidAlloc
//
//  Synopsis:   Called prior to OLE calling IMalloc::DidAlloc
//
//  Arguments:  [pRequest] -- The buffer whose allocation is being tested
//              [fSpyed]   -- Whether it was allocated with a spy active
//
//  Returns:    The buffer whose allocation is actually to be tested
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
void *CMallocSpy::PreDidAlloc(void *pRequest, BOOL fSpyed)
{
    if (fSpyed)
    {
        return (void *) (((BYTE *) pRequest) - HEADERSIZE);
    }
    else
    {
        return pRequest;
    }
}





//+---------------------------------------------------------------------
//
//  Function:   PostDidAlloc
//
//  Synopsis:   Called after OLE calls the IMalloc::DidAlloc
//
//  Arguments:  [pRequest] -- The passed allocation
//              [fSpyed]   -- Whether it was allocated with a spy active
//              [fActual]  -- The result of IMalloc::DidAlloc
//
//  Returns:    The result of IMalloc::DidAlloc
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
BOOL CMallocSpy::PostDidAlloc(void *pRequest, BOOL fSpyed, BOOL fActual)
{
    return fActual;
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PreHeapMinimize
//
//  Synopsis:   Called prior to OLE calling the IMalloc::HeapMinimize
//
//  Returns:
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
void CMallocSpy::PreHeapMinimize(void)
{
    // We don't do anything here
    return;
}





//+---------------------------------------------------------------------
//
//  Member:     CMallocSpy::PostHeapMinimize
//
//  Synopsis:   Called after OLE calls the IMalloc::HeapMinimize
//
//  Returns:
//
//  History:    24-Oct-94   Created.
//
//  Notes:
//
//----------------------------------------------------------------------
void CMallocSpy::PostHeapMinimize(void)
{
    // We don't do anything here
    return;
}
