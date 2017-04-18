/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CNameSp.cpp

Abstract:

    Sample Namespace Object 

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop


DEFINE_IDispatch_Implementation(CSampleDSNamespace)
DEFINE_IADs_Implementation(CSampleDSNamespace)

//  Class CSampleDSNamespace
CSampleDSNamespace::CSampleDSNamespace()
{
    VariantInit(&_vFilter);
}

HRESULT
CSampleDSNamespace::CreateNamespace(
    BSTR Parent,
    BSTR NamespaceName,
    DWORD dwObjectState,
    REFIID riid,
    void **ppvObj
    )
{
    CSampleDSNamespace FAR * pNamespace = NULL;
    HRESULT hr = S_OK;

    hr = AllocateNamespaceObject(&pNamespace);
    BAIL_ON_FAILURE(hr);

    hr = pNamespace->InitializeCoreObject(
                Parent,
                NamespaceName,
                L"Namespace",
                L"",
                CLSID_SampleDSNamespace,
                dwObjectState
                );
    BAIL_ON_FAILURE(hr);

    hr = pNamespace->QueryInterface(riid, ppvObj);
    BAIL_ON_FAILURE(hr);

    pNamespace->Release();

    RRETURN(hr);

error:

    delete pNamespace;
    RRETURN(hr);
}


CSampleDSNamespace::~CSampleDSNamespace( )
{
    delete _pDispMgr;
}

STDMETHODIMP
CSampleDSNamespace::QueryInterface(REFIID iid, LPVOID FAR* ppv)
{
    if (IsEqualIID(iid, IID_IUnknown))
    {
        *ppv = (IADs FAR *)this;
    }else if (IsEqualIID(iid, IID_IDispatch))
    {
        *ppv = (IADs FAR *)this;
    }
    else if (IsEqualIID(iid, IID_IADsContainer))
    {
        *ppv = (IADsContainer FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IADs))
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
CSampleDSNamespace::SetInfo(THIS)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSNamespace::GetInfo(THIS)
{
    RRETURN(E_NOTIMPL);
}

/* IADsContainer methods */

STDMETHODIMP
CSampleDSNamespace::get_Count(long FAR* retval)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSNamespace::get_Filter(THIS_ VARIANT FAR* pVar)
{
    VariantInit(pVar);
    RRETURN(VariantCopy(pVar, &_vFilter));
}

STDMETHODIMP
CSampleDSNamespace::put_Filter(THIS_ VARIANT Var)
{
    RRETURN(VariantCopy(&_vFilter, &Var));
}

STDMETHODIMP
CSampleDSNamespace::put_Hints(THIS_ VARIANT Var)
{
    RRETURN( E_NOTIMPL);
}


STDMETHODIMP
CSampleDSNamespace::get_Hints(THIS_ VARIANT FAR* pVar)
{
    RRETURN(E_NOTIMPL);
}


STDMETHODIMP
CSampleDSNamespace::GetObject(
    THIS_ BSTR ClassName,
    BSTR RelativeName,
    IDispatch* FAR* ppObject
    )
{
    RRETURN(::RelativeGetObject(_ADsPath,
                                ClassName,
                                RelativeName,
                                ppObject,
                                TRUE));
}


STDMETHODIMP
CSampleDSNamespace::get__NewEnum(THIS_ IUnknown * FAR* retval)
{
    HRESULT hr;
    IUnknown FAR* punkEnum=NULL;
    IEnumVARIANT * penum = NULL;


    *retval = NULL;

    //
    // Create new enumerator for items currently
    // in collection and QI for IUnknown
    //

    hr = CSampleDSNamespaceEnum::Create(
                (CSampleDSNamespaceEnum **)&penum,
                _vFilter
                );
    if (FAILED(hr)){

        goto error;
    }
    hr = penum->QueryInterface(
                IID_IUnknown,
                (VOID FAR* FAR*)retval
                );

    if (FAILED(hr)){
       goto error;
    }

    if (penum) {
        penum->Release();
    }

    return NOERROR;

error:

    if (penum) {
        delete penum;
    }

    return hr;
}

STDMETHODIMP
CSampleDSNamespace::Create(THIS_ BSTR ClassName, BSTR RelativeName, IDispatch * FAR* ppObject)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSNamespace::Delete(THIS_ BSTR SourceName, BSTR Type)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSNamespace::CopyHere(THIS_ BSTR SourceName, BSTR NewName, IDispatch * FAR* ppObject)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSNamespace::MoveHere(THIS_ BSTR SourceName, BSTR NewName, IDispatch * FAR* ppObject)
{
    RRETURN(E_NOTIMPL);
}


HRESULT
CSampleDSNamespace::AllocateNamespaceObject(CSampleDSNamespace ** ppNamespace)
{
    CSampleDSNamespace FAR * pNamespace = NULL;
    CDispatchMgr FAR * pDispMgr = NULL;
    HRESULT hr = S_OK;

    pNamespace = new CSampleDSNamespace();
    if (pNamespace == NULL) {
        hr = E_OUTOFMEMORY;
    }
    BAIL_ON_FAILURE(hr);

    pDispMgr = new CDispatchMgr;
    if (pDispMgr == NULL) {
        hr = E_OUTOFMEMORY;
    }
    BAIL_ON_FAILURE(hr);

    hr = LoadTypeInfoEntry(pDispMgr,
                           LIBID_ADs,
                           IID_IADs,
                           (IADs *)pNamespace,
                           DISPID_REGULAR
                           );
    BAIL_ON_FAILURE(hr);

    hr = LoadTypeInfoEntry(pDispMgr,
                           LIBID_ADs,
                           IID_IADsContainer,
                           (IADsContainer *)pNamespace,
                           DISPID_NEWENUM
                           );
    BAIL_ON_FAILURE(hr);

    pNamespace->_pDispMgr = pDispMgr;
    *ppNamespace = pNamespace;

    RRETURN(hr);

error:
    delete  pDispMgr;

    RRETURN(hr);

}



STDMETHODIMP
CSampleDSNamespace::Get(
    THIS_ BSTR bstrName,
    VARIANT FAR* pvProp
    )
{
    RRETURN(E_NOTIMPL);
}



STDMETHODIMP
CSampleDSNamespace::Put(
    THIS_ BSTR bstrName,
    VARIANT vProp
    )
{
    RRETURN(E_NOTIMPL);
}

