/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CProv.cpp

Abstract:

    ADsSampleDS Provider Object

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

CSampleDSProvider::CSampleDSProvider()
{

}

HRESULT
CSampleDSProvider::Create(CSampleDSProvider FAR * FAR * ppProvider)
{
    CSampleDSProvider FAR * pProvider = NULL;
    HRESULT hr = S_OK;

    //Create the Provider Object

    pProvider = new CSampleDSProvider();
    if (pProvider == NULL) {
        RRETURN(ResultFromScode(E_OUTOFMEMORY));
    }

    if (FAILED(hr)) {
        delete pProvider;
        RRETURN(hr);
    }


    *ppProvider = pProvider;
    RRETURN(hr);
}

CSampleDSProvider::~CSampleDSProvider( )
{
    ENLIST_TRACKING(CSampleDSProvider);
}

STDMETHODIMP
CSampleDSProvider::QueryInterface(REFIID iid, LPVOID FAR* ppv)
{
    if (IsEqualIID(iid, IID_IUnknown))
    {
        *ppv = this;
    }
    else if (IsEqualIID(iid, IID_IParseDisplayName))
    {
        *ppv = (IADs FAR *) this;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    AddRef();
    return NOERROR;
}

STDMETHODIMP
CSampleDSProvider::ParseDisplayName(IBindCtx* pbc, WCHAR* szDisplayName, ULONG* pchEaten, IMoniker** ppmk)
{
    HRESULT hr;

    *ppmk = NULL;

    if (pchEaten != NULL){
        *pchEaten = 0;
    }

    hr = ResolvePathName(
                pbc,
                szDisplayName,
                pchEaten,
                ppmk
                );

    RRETURN(hr);
}

HRESULT
CSampleDSProvider::ResolvePathName(IBindCtx* pbc,
                WCHAR* szDisplayName,
                ULONG* pchEaten,
                IMoniker** ppmk
                )
{
    HRESULT hr;
    LPUNKNOWN pUnknown = NULL;

    *pchEaten = 0;
    hr = GetObject(szDisplayName, (LPVOID *)&pUnknown);
    BAIL_IF_ERROR(hr);

    hr = CreatePointerMoniker(pUnknown, ppmk);
    BAIL_IF_ERROR(hr);

    *pchEaten += wcslen(szDisplayName);

cleanup:

    if (pUnknown) {
        pUnknown->Release();
    }

    RRETURN (hr);
}

