//-----------------------------------------------------------------------------
// Microsoft OLE DB TABLECOPY Sample
// Copyright (C) 1995-1998 Microsoft Corporation
//
// @doc
//
// @module SPY.H
//
//-----------------------------------------------------------------------------------

#ifndef _SPY_H_
#define _SPY_H_


/////////////////////////////////////////////////////////////////////////////
// Includes
//
/////////////////////////////////////////////////////////////////////////////
#include "objidl.h" //IMallocSpy
#include "Common.h" //ASSERT
#include "List.h"   //CList



/////////////////////////////////////////////////////////////////////////////
// CMallocSpy
//
/////////////////////////////////////////////////////////////////////////////
class CMallocSpy : public IMallocSpy
{
public:
    CMallocSpy(void);
	virtual ~CMallocSpy(void);

	//Interface
	virtual HRESULT AddToList(void* pv);
	virtual HRESULT RemoveFromList(void* pv);
	virtual HRESULT DumpLeaks();

    // IUnknown methods
    virtual STDMETHODIMP QueryInterface(REFIID riid, void** ppIUnknown);
    virtual STDMETHODIMP_(ULONG) AddRef();
    virtual STDMETHODIMP_(ULONG) Release();

	// IMallocSpy methods

    //Alloc
	virtual STDMETHODIMP_(ULONG) PreAlloc(ULONG cbRequest);
    virtual STDMETHODIMP_(void*) PostAlloc(void *pActual);

    //Free
	virtual STDMETHODIMP_(void*) PreFree(void *pRequest, BOOL fSpyed);
    virtual STDMETHODIMP_(void ) PostFree(BOOL fSpyed);

    //Realloc
	virtual STDMETHODIMP_(ULONG) PreRealloc(void *pRequest, ULONG cbRequest, void **ppNewRequest, BOOL fSpyed);
    virtual STDMETHODIMP_(void*) PostRealloc(void *pActual, BOOL fSpyed);

    //GetSize
	virtual STDMETHODIMP_(void*) PreGetSize(void *pRequest, BOOL fSpyed);
    virtual STDMETHODIMP_(ULONG) PostGetSize(ULONG cbActual, BOOL fSpyed);

    //DidAlloc
	virtual STDMETHODIMP_(void*) PreDidAlloc(void *pRequest, BOOL fSpyed);
    virtual STDMETHODIMP_(BOOL)  PostDidAlloc(void *pRequest, BOOL fSpyed, BOOL fActual);

    //HeapMinimize
	virtual STDMETHODIMP_(void ) PreHeapMinimize();
    virtual STDMETHODIMP_(void ) PostHeapMinimize();


private:
    ULONG    m_cRef;			//Reference count
    ULONG    m_cbRequest;		//Bytes requested

	CList<void*> CAllocList;	//List to keep track of leaks
};

/////////////////////////////////////////////////////////////////////////////
// Registration
//
/////////////////////////////////////////////////////////////////////////////
HRESULT MallocSpyRegister(CMallocSpy** ppCMallocSpy);
HRESULT MallocSpyUnRegister(CMallocSpy* pCMallocSpy);
HRESULT MallocSpyDump(CMallocSpy* pCMallocSpy);


#endif // _SPY_H_
