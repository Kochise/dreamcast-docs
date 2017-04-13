/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    StdFact.cpp

Abstract:

    Standard IClassFactory implementation

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"

STDMETHODIMP
StdClassFactory::QueryInterface(REFIID riid, LPVOID FAR* ppv)
{
    if (!ppv)
        RRETURN(E_INVALIDARG);

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_IClassFactory))
    {
        *ppv = (IClassFactory *) this;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    ((IUnknown *)*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG)
StdClassFactory::AddRef(void)
{
    ADsAssert(_ulRefs);

    if (_ulRefs == 1)
        INC_OBJECT_COUNT();

    return ++_ulRefs;
}

STDMETHODIMP_(ULONG)
StdClassFactory::Release(void)
{
    ADsAssert(_ulRefs > 1);

    if (--_ulRefs == 1)
        DEC_OBJECT_COUNT();

    return _ulRefs;
}

STDMETHODIMP
StdClassFactory::LockServer (BOOL fLock)
{
    if (fLock)
        INC_OBJECT_COUNT();
    else
        DEC_OBJECT_COUNT();
    return NOERROR;
}

CDynamicCF::CDynamicCF(void)
{
    _ulRefs = 1;

    INC_OBJECT_COUNT();
}

CDynamicCF::~CDynamicCF(void)
{
    DEC_OBJECT_COUNT();
}

STDMETHODIMP
CDynamicCF::QueryInterface(REFIID riid, LPVOID FAR* ppv)
{
    if (!ppv)
        RRETURN(E_INVALIDARG);

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_IClassFactory))
    {
        *ppv = (IClassFactory *) this;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    ((IUnknown *)*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP
CDynamicCF::LockServer (BOOL fLock)
{
    if (fLock)
    {
        _ulRefs++;
    }
    else
    {
        _ulRefs--;
    }

    return S_OK;
}

#ifdef DOCGEN

STDMETHODIMP
StdClassFactory::CreateInstance(LPUNKNOWN pUnkOuter,
        REFIID iid,
        LPVOID FAR* ppv) {};
#endif  // DOCGEN


