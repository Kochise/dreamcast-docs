/*
 * IMALLOC.H
 *
 * Definitions of a template IMalloc interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IMALLOC_H_
#define _IMALLOC_H_

#include <inole.h>

class CImpIMalloc;
typedef class CImpIMalloc *PCImpIMalloc;

class CImpIMalloc : public IMalloc
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIMalloc(LPVOID, LPUNKNOWN);
        ~CImpIMalloc(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(void *) Alloc(ULONG);
        STDMETHODIMP_(void *) Realloc(void *, ULONG);
        STDMETHODIMP_(void)   Free(void *);
        STDMETHODIMP_(ULONG)  GetSize(void *);
        STDMETHODIMP_(int)    DidAlloc(void *);
        STDMETHODIMP_(void)   HeapMinimize(void);
    };


#endif //_IMALLOC_H_
