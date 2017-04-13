//+---------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1994 - 1996.
//
//  File:       cmallspy.c
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
#include <olestd.h>

OLEDBGDATA

#include "malspy.h"

#define TOKEN 0xDEAD

typedef struct tagHeader
{
    UINT    uiTag;
    ULONG   cbSize;
} HEADER, * LPHEADER;

// The following macro is used to ensure that the token placed at the
// end of each memory block is always aligned on a dword boundary.
// This is necessary to avoid alignment faults on some systems.
#define DWORDALIGN(x) ((x + 3) & (~3))

typedef struct CMallocSpy {
  IMallocSpyVtbl FAR*     lpVtbl;
  ULONG                   m_cRef;   // interface specific ref count.
  ULONG                   m_cbRequested;
} CMALLOCSPY, *LPCMALLOCSPY;

STDMETHODIMP MallocSpy_QueryInterface(
      LPMALLOCSPY             this,
      REFIID                  riid,
      LPVOID FAR*             lplpUnk);

STDMETHODIMP_(ULONG) MallocSpy_AddRef(
    LPMALLOCSPY this);

STDMETHODIMP_(ULONG) MallocSpy_Release(
    LPMALLOCSPY this);

STDMETHODIMP_(ULONG) MallocSpy_PreAlloc(
    LPMALLOCSPY this,
    ULONG cbRequest);

STDMETHODIMP_(void *) MallocSpy_PostAlloc(
    LPMALLOCSPY this,
    void *pActual);

STDMETHODIMP_(void *) MallocSpy_PreFree(
    LPMALLOCSPY this,
    void *pRequest, BOOL fSpyed);

STDMETHODIMP_(void) MallocSpy_PostFree(
    LPMALLOCSPY this,
    BOOL fSpyed);

STDMETHODIMP_(ULONG) MallocSpy_PreRealloc(
    LPMALLOCSPY this,
    void *pRequest,
    ULONG cbRequest,
    void **ppNewRequest,
    BOOL fSpyed);

STDMETHODIMP_(void *) MallocSpy_PostRealloc(
    LPMALLOCSPY this,
    void *pActual,
    BOOL fSpyed);

STDMETHODIMP_(void *) MallocSpy_PreGetSize(
    LPMALLOCSPY this,
    void *pRequest,
    BOOL fSpyed);

STDMETHODIMP_(ULONG) MallocSpy_PostGetSize(
    LPMALLOCSPY this,
    ULONG cbActual,
    BOOL fSpyed);

STDMETHODIMP_(void *) MallocSpy_PreDidAlloc(
    LPMALLOCSPY this,
    void *pRequest,
    BOOL fSpyed);

STDMETHODIMP_(BOOL) MallocSpy_PostDidAlloc(
    LPMALLOCSPY this,
    void *pRequest,
    BOOL fSpyed,
    BOOL fActual);

STDMETHODIMP_(void) MallocSpy_PreHeapMinimize(
    LPMALLOCSPY this);

STDMETHODIMP_(void) MallocSpy_PostHeapMinimize(
    LPMALLOCSPY this);


IMallocSpyVtbl g_MallocSpyVtbl;

BOOL InitializeMallocSpy(void)
{
    BOOL fStatus;
    LPCMALLOCSPY lpcMallocSpy = NULL;
    HRESULT hr;

    OleStdInitVtbl(
          &g_MallocSpyVtbl,
          sizeof(g_MallocSpyVtbl));

    g_MallocSpyVtbl.QueryInterface      = MallocSpy_QueryInterface;
    g_MallocSpyVtbl.AddRef              = MallocSpy_AddRef;
    g_MallocSpyVtbl.Release             = MallocSpy_Release;
    g_MallocSpyVtbl.PreAlloc            = MallocSpy_PreAlloc;
    g_MallocSpyVtbl.PostAlloc           = MallocSpy_PostAlloc;
    g_MallocSpyVtbl.PreFree             = MallocSpy_PreFree;
    g_MallocSpyVtbl.PostFree            = MallocSpy_PostFree;
    g_MallocSpyVtbl.PreRealloc          = MallocSpy_PreRealloc;
    g_MallocSpyVtbl.PostRealloc         = MallocSpy_PostRealloc;
    g_MallocSpyVtbl.PreGetSize          = MallocSpy_PreGetSize;
    g_MallocSpyVtbl.PostGetSize         = MallocSpy_PostGetSize;
    g_MallocSpyVtbl.PreDidAlloc         = MallocSpy_PreDidAlloc;
    g_MallocSpyVtbl.PostDidAlloc        = MallocSpy_PostDidAlloc;
    g_MallocSpyVtbl.PreHeapMinimize     = MallocSpy_PreHeapMinimize;
    g_MallocSpyVtbl.PostHeapMinimize    = MallocSpy_PostHeapMinimize;

    fStatus = OleStdCheckVtbl(
          &g_MallocSpyVtbl,
          sizeof(g_MallocSpyVtbl),
          OLESTR("IMallocSpy"));
    if (! fStatus)
        return FALSE;

    lpcMallocSpy = malloc(sizeof(CMALLOCSPY));

    if (NULL == lpcMallocSpy)
    {
        return FALSE;
    }
    lpcMallocSpy->lpVtbl = &g_MallocSpyVtbl;
    lpcMallocSpy->m_cRef = 0;

    hr = CoRegisterMallocSpy((LPMALLOCSPY)lpcMallocSpy);

    return(SUCCEEDED(hr));
}

void UninitializeMallocSpy()
{
    CoRevokeMallocSpy();
}

//+---------------------------------------------------------------------------
//
//  Function:   CbUserFromCbActual
//
//  Synopsis:   adjusts the size to account for the header and footer
//
//  Arguments:  [cbActual] - actual size of the memory block
//
//  Returns:    size reported to the user
//
//----------------------------------------------------------------------------

ULONG CbUserFromCbActual(ULONG cbActual)
{
    return(cbActual - (sizeof(HEADER) + sizeof(UINT)));
}

//+---------------------------------------------------------------------------
//
//  Function:   CbActualFromCbUser
//
//  Synopsis:   adjusts the size to account for the header and footer
//
//  Arguments:  [cbUser] - size reported to the user
//
//  Returns:    actual size of the memory block
//
//----------------------------------------------------------------------------

ULONG CbActualFromCbUser(ULONG cbUser)
{
    return(DWORDALIGN(cbUser) + sizeof(HEADER) + sizeof(UINT));
}

//+---------------------------------------------------------------------------
//
//  Function:   PActualFromPUser
//
//  Synopsis:   adjusts the pointer to account for the header, verifying
//              the memory integrity in the process
//
//  Arguments:  [pUser] - pointer reported to the user
//
//  Returns:    acutal pointer to the memory block
//
//----------------------------------------------------------------------------

void * PActualFromPUser(void * pUser)
{
    HEADER * pHeader;
    UINT * puiFooter;
    pHeader = ((LPHEADER)pUser) - 1;
    puiFooter = (UINT *)(((BYTE *)pUser) + DWORDALIGN(pHeader->cbSize));

    OleDbgAssertSz(TOKEN == pHeader->uiTag, "Illegal memory block.");
    OleDbgAssertSz(TOKEN == *puiFooter, "Memory block was overrun.");

    if (TOKEN != pHeader->uiTag)
    {
        // Just to be safe, if we don't find the TOKEN we'll not adjust the
        // pointer
        return(pUser);
    }
    return ((void *) (pHeader));
}

//+---------------------------------------------------------------------------
//
//  Function:   PUserFromPActual
//
//  Synopsis:   adjusts the pointer to account for the header, initializing
//              the header and footer in the process to allow verification of
//              memory integrity
//
//  Arguments:  [pActual]    - actual pointer to the memory block
//              [cbDataSize] - size of the memory block requested by the user
//
//  Returns:    pointer to the data which the user may modify
//
//----------------------------------------------------------------------------

void * PUserFromPActual(void * pActual, ULONG cbDataSize)
{
    // Mark the block with a TOKEN at the front and the end
    // and its size so we can tell if it is bogus
    LPHEADER pHeader = pActual;
    UINT* puiFooter;

    pHeader->uiTag = TOKEN;
    pHeader->cbSize = cbDataSize;

    pActual = (void *)(pHeader + 1);

    puiFooter = (UINT *)(((BYTE *) pActual) + DWORDALIGN(pHeader->cbSize));
    *puiFooter = TOKEN;
    return(pActual);
}

STDMETHODIMP MallocSpy_QueryInterface(
      LPMALLOCSPY  this,
      REFIID riid,
      LPVOID *                ppUnk)
{
    HRESULT hr = S_OK;

    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IMallocSpy))
    {
        *ppUnk = this;
    }
    else
    {
        *ppUnk = NULL;
        hr =  E_NOINTERFACE;
    }
    this->lpVtbl->AddRef((LPMALLOCSPY)this);
    return hr;
}

STDMETHODIMP_(ULONG) MallocSpy_AddRef(
    LPMALLOCSPY this)
{
    return ++(((LPCMALLOCSPY)this)->m_cRef);
}

STDMETHODIMP_(ULONG) MallocSpy_Release(
    LPMALLOCSPY this)
{
    ULONG cRef;

    cRef = --(((LPCMALLOCSPY)this)->m_cRef);
    if (cRef == 0)
    {
        free(this);
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
//  Returns:    The count of bytes to actually allocate
//
//----------------------------------------------------------------------
STDMETHODIMP_(ULONG) MallocSpy_PreAlloc(
    LPMALLOCSPY this,
    ULONG cbRequest)
{
    ((LPCMALLOCSPY)this)->m_cbRequested = cbRequest;
    return CbActualFromCbUser(cbRequest);
}

#ifdef TRACEMEM
char szScratch[256];
#endif

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
//----------------------------------------------------------------------
STDMETHODIMP_(void *) MallocSpy_PostAlloc(
    LPMALLOCSPY this,
    void *pActual)
{
    void * pUser = PUserFromPActual(pActual, ((LPCMALLOCSPY)this)->m_cbRequested);

#ifdef TRACEMEM
    wsprintf(szScratch, "IMalloc: 0x%08lX allocated\n", pUser);
    OleDbgOut1(szScratch);
#endif

    return(pUser);
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
//----------------------------------------------------------------------
STDMETHODIMP_(void *) MallocSpy_PreFree(
    LPMALLOCSPY this,
    void *pRequest, BOOL fSpyed)
{
    // Check for NULL
    if (pRequest == NULL)
    {
        return NULL;
    }

#ifdef TRACEMEM
    wsprintf(szScratch, "IMalloc: 0x%08lX freeing\n", pRequest);
    OleDbgOut1(szScratch);
#endif

    // Undo the offset
    if (fSpyed)
    {
        return(PActualFromPUser(pRequest));
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
//----------------------------------------------------------------------
STDMETHODIMP_(void) MallocSpy_PostFree(
    LPMALLOCSPY this,
    BOOL fSpyed)
{
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
//----------------------------------------------------------------------
STDMETHODIMP_(ULONG) MallocSpy_PreRealloc(
    LPMALLOCSPY this,
    void *pRequest,
    ULONG cbRequest,
    void **ppNewRequest,
    BOOL fSpyed)
{
#ifdef TRACEMEM
    wsprintf(szScratch, "IMalloc: 0x%08lX realocating\n", pRequest);
    OleDbgOut1(szScratch);
#endif

    if (fSpyed)
    {
        *ppNewRequest = PActualFromPUser(pRequest);
        ((LPCMALLOCSPY)this)->m_cbRequested = cbRequest;
        return CbActualFromCbUser(cbRequest);
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
//----------------------------------------------------------------------
STDMETHODIMP_(void *) MallocSpy_PostRealloc(
    LPMALLOCSPY this,
    void *pActual,
    BOOL fSpyed)
{
    void * pUser;

    if (fSpyed)
    {
        pUser = PUserFromPActual(pActual, ((LPCMALLOCSPY)this)->m_cbRequested);
    }
    else
    {
        pUser = pActual;
    }

#ifdef TRACEMEM
    wsprintf(szScratch, "IMalloc: 0x%08lX reallocated\n", pUser);
    OleDbgOut1(szScratch);
#endif

    return(pUser);
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
//----------------------------------------------------------------------
STDMETHODIMP_(void *) MallocSpy_PreGetSize(
    LPMALLOCSPY this,
    void *pRequest,
    BOOL fSpyed)
{
    if (fSpyed)
    {
        return(PActualFromPUser(pRequest));
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
//----------------------------------------------------------------------
STDMETHODIMP_(ULONG) MallocSpy_PostGetSize(
    LPMALLOCSPY this,
    ULONG cbActual,
    BOOL fSpyed)
{
    if (fSpyed)
    {
        return CbUserFromCbActual(cbActual);
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
//----------------------------------------------------------------------
STDMETHODIMP_(void *) MallocSpy_PreDidAlloc(
    LPMALLOCSPY this,
    void *pRequest,
    BOOL fSpyed)
{
    if (fSpyed)
    {
        return(PActualFromPUser(pRequest));
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
//----------------------------------------------------------------------
STDMETHODIMP_(BOOL) MallocSpy_PostDidAlloc(
    LPMALLOCSPY this,
    void *pRequest,
    BOOL fSpyed,
    BOOL fActual)
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
//----------------------------------------------------------------------
STDMETHODIMP_(void) MallocSpy_PreHeapMinimize(
    LPMALLOCSPY this)
{
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
//----------------------------------------------------------------------
STDMETHODIMP_(void) MallocSpy_PostHeapMinimize(
    LPMALLOCSPY this)
{
    return;
}

