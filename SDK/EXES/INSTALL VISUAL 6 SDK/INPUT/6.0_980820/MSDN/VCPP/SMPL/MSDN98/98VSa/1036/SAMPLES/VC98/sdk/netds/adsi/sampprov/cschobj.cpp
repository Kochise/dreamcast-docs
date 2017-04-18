/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CSchObj.cpp

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

//  Class CSampleDSSchema

DEFINE_IDispatch_Implementation(CSampleDSSchema)
DEFINE_IADs_Implementation(CSampleDSSchema)


CSampleDSSchema::CSampleDSSchema()
{

    VariantInit(&_vFilter);

    _SampleDSTreeName = NULL;

    ENLIST_TRACKING(CSampleDSSchema);
}

HRESULT
CSampleDSSchema::CreateSchema(
    BSTR Parent,
    BSTR CommonName,
    DWORD dwObjectState,
    REFIID riid,
    void **ppvObj
    )
{
    CSampleDSSchema FAR * pSchema = NULL;
    HRESULT hr = S_OK;
    WCHAR szSampleDSTreeName[MAX_PATH];

    hr = AllocateSchema(&pSchema);
    BAIL_ON_FAILURE(hr);

    hr = pSchema->InitializeCoreObject(
                Parent,
                CommonName,
                L"schema",
                L"",
                CLSID_SampleDSSchema,
                dwObjectState
                );
    BAIL_ON_FAILURE(hr);


    hr = BuildDSPathFromADsPath(
                Parent,
                szSampleDSTreeName
                );
    BAIL_ON_FAILURE(hr);

    hr = ProvAllocString( szSampleDSTreeName,  &pSchema->_SampleDSTreeName);
    BAIL_ON_FAILURE(hr);

    hr = pSchema->QueryInterface(riid, ppvObj);
    BAIL_ON_FAILURE(hr);

    pSchema->Release();

    RRETURN(hr);

error:

    delete pSchema;
    RRETURN(hr);
}

CSampleDSSchema::~CSampleDSSchema( )
{
    if (_SampleDSTreeName) {
        ProvFreeString(_SampleDSTreeName);
    }
    delete _pDispMgr;
}

STDMETHODIMP
CSampleDSSchema::QueryInterface(REFIID iid, LPVOID FAR* ppv)
{
    if (IsEqualIID(iid, IID_IUnknown))
    {
        *ppv = (IADs FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IADsContainer))
    {
        *ppv = (IADsContainer FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IADs))
    {
        *ppv = (IADs FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IDispatch))
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
CSampleDSSchema::SetInfo(THIS)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSSchema::GetInfo(THIS)
{
    RRETURN(E_NOTIMPL);
}

/* IADsContainer methods */

STDMETHODIMP
CSampleDSSchema::get_Count(long FAR* retval)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSSchema::get_Filter(THIS_ VARIANT FAR* pVar)
{
    VariantInit(pVar);
    RRETURN(VariantCopy(pVar, &_vFilter));
}

STDMETHODIMP
CSampleDSSchema::put_Filter(THIS_ VARIANT Var)
{
    RRETURN(VariantCopy(&_vFilter, &Var));
}

STDMETHODIMP
CSampleDSSchema::put_Hints(THIS_ VARIANT Var)
{
    RRETURN( E_NOTIMPL);
}


STDMETHODIMP
CSampleDSSchema::get_Hints(THIS_ VARIANT FAR* pVar)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSSchema::GetObject(
    THIS_ BSTR ClassName,
    BSTR RelativeName,
    IDispatch * FAR* ppObject
    )
{
    RRETURN(::RelativeGetObject(_ADsPath,
                                ClassName,
                                RelativeName,
                                ppObject,
                                FALSE));
}

STDMETHODIMP
CSampleDSSchema::get__NewEnum(
    THIS_ IUnknown * FAR* retval
    )
{
    HRESULT hr;
    IUnknown FAR* punkEnum=NULL;
    IEnumVARIANT * penum = NULL;


    *retval = NULL;

    hr = CSampleDSSchemaEnum::Create(
                (CSampleDSSchemaEnum **)&penum,
                _SampleDSTreeName,
                _ADsPath,
                _Name,
                _vFilter
                );
    BAIL_ON_FAILURE(hr);

    hr = penum->QueryInterface(
                IID_IUnknown,
                (VOID FAR* FAR*)retval
                );
    BAIL_ON_FAILURE(hr);

    if (penum) {
        penum->Release();
    }

    RRETURN(NOERROR);

error:

    if (penum) {
        delete penum;
    }

    RRETURN(hr);
}


STDMETHODIMP
CSampleDSSchema::Create(
    THIS_ BSTR ClassName,
    BSTR RelativeName,
    IDispatch * FAR* ppObject
    )
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSSchema::Delete(
    THIS_ BSTR bstrClassName,
    BSTR bstrRelativeName
    )
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSSchema::CopyHere(
    THIS_ BSTR SourceName,
    BSTR NewName,
    IDispatch * FAR* ppObject
    )
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSSchema::MoveHere(
    THIS_ BSTR SourceName,
    BSTR NewName,
    IDispatch * FAR* ppObject
    )
{
    RRETURN(E_NOTIMPL);
}


HRESULT
CSampleDSSchema::AllocateSchema(
    CSampleDSSchema ** ppSchema
    )
{
    CSampleDSSchema FAR * pSchema = NULL;
    CDispatchMgr FAR * pDispMgr = NULL;
    HRESULT hr = S_OK;

    pSchema = new CSampleDSSchema();
    if (pSchema == NULL) {
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
                           (IADsDomain *)pSchema,
                           DISPID_REGULAR
                           );
    BAIL_ON_FAILURE(hr);

    hr = LoadTypeInfoEntry(pDispMgr,
                           LIBID_ADs,
                           IID_IADsContainer,
                           (IADsContainer *)pSchema,
                           DISPID_NEWENUM
                           );
    BAIL_ON_FAILURE(hr);

    pSchema->_pDispMgr = pDispMgr;
    *ppSchema = pSchema;

    RRETURN(hr);

error:
    delete  pDispMgr;

    RRETURN(hr);

}


STDMETHODIMP
CSampleDSSchema::GetInfo(
    THIS_ DWORD dwApiLevel,
    BOOL fExplicit
    )
{
    RRETURN(E_NOTIMPL);
}


STDMETHODIMP
CSampleDSSchema::Get(
    THIS_ BSTR bstrName,
    VARIANT FAR* pvProp
    )
{
    RRETURN(E_NOTIMPL);
}



STDMETHODIMP
CSampleDSSchema::Put(
    THIS_ BSTR bstrName,
    VARIANT vProp
    )
{
    RRETURN(E_NOTIMPL);
}



