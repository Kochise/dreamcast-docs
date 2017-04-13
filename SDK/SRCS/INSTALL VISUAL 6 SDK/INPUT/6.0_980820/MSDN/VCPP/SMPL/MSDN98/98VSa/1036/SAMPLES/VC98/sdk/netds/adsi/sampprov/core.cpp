/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    Core.cpp

Abstract:

    CCoreADsObject - Implementation

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

HRESULT
CCoreADsObject::InitializeCoreObject(
        BSTR Parent,
        BSTR Name,
        BSTR ClassName,
        BSTR Schema,
        REFCLSID rclsid,
        DWORD dwObjectState
        )
{
    HRESULT hr = S_OK;
    ADsAssert(Parent);
    ADsAssert(Name);
    ADsAssert(ClassName);

    hr = BuildADsPath(
            Parent,
            Name,
            &_ADsPath
            );
    BAIL_ON_FAILURE(hr);

    hr = BuildADsGuid(
            rclsid,
            &_ADsGuid
            );
    BAIL_ON_FAILURE(hr);

    hr = xx_put_BSTR(&_Parent, Parent);
    BAIL_ON_FAILURE(hr);


    hr = xx_put_BSTR(&_Name, Name);
    BAIL_ON_FAILURE(hr);

    hr = xx_put_BSTR(&_ADsClass, ClassName);
    BAIL_ON_FAILURE(hr);

    hr = BuildSchemaPath(
            _ADsPath,
            ClassName,
            &_Schema
            );
    BAIL_ON_FAILURE(hr);
    
    _dwObjectState = dwObjectState;

error:
    RRETURN(hr);

}

CCoreADsObject::CCoreADsObject():
                        _Name(NULL),
                        _ADsPath(NULL),
                        _Parent(NULL),
                        _ADsClass(NULL),
                        _Schema(NULL),
                        _ADsGuid(NULL),
                        _dwObjectState(0)
{
}

CCoreADsObject::~CCoreADsObject()
{
    if (_Name) {
        ProvFreeString(_Name);
    }

    if (_ADsPath) {
        ProvFreeString(_ADsPath);
    }

    if (_Parent) {
        ProvFreeString(_Parent);
    }

    if (_ADsClass) {
        ProvFreeString(_ADsClass);
    }

    if (_Schema) {
        ProvFreeString(_Schema);
    }

    if (_ADsGuid) {
        ProvFreeString(_ADsGuid);
    }

}

HRESULT
CCoreADsObject::get_CoreName(BSTR * retval)
{
    HRESULT hr;

    if (FAILED(hr = ValidateOutParameter(retval))){
        RRETURN(hr);
    }

    RRETURN(ProvAllocString(_Name, retval));
}


HRESULT
CCoreADsObject::get_CoreADsPath(BSTR * retval)
{
    HRESULT hr;

    if (FAILED(hr = ValidateOutParameter(retval))){
        RRETURN(hr);
    }

    RRETURN(ProvAllocString(_ADsPath, retval));

}

HRESULT
CCoreADsObject::get_CoreADsClass(BSTR * retval)
{
    HRESULT hr;

    if (FAILED(hr = ValidateOutParameter(retval))){
        RRETURN(hr);
    }

    RRETURN(ProvAllocString(_ADsClass, retval));
}

HRESULT
CCoreADsObject::get_CoreParent(BSTR * retval)
{

    HRESULT hr;

    if (FAILED(hr = ValidateOutParameter(retval))){
        RRETURN(hr);
    }

    RRETURN(ProvAllocString(_Parent, retval));
}

HRESULT
CCoreADsObject::get_CoreSchema(BSTR * retval)
{

    HRESULT hr;

    if (FAILED(hr = ValidateOutParameter(retval))){
        RRETURN(hr);
    }

    if ( _Schema == NULL || *_Schema == 0 )
        RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);

    RRETURN(ProvAllocString(_Schema, retval));
}

HRESULT
CCoreADsObject::get_CoreGUID(BSTR * retval)
{
    HRESULT hr;

    if (FAILED(hr = ValidateOutParameter(retval))){
        RRETURN(hr);
    }

    RRETURN(ProvAllocString(_ADsGuid, retval));
}

STDMETHODIMP
CCoreADsObject::GetInfo(
    BOOL fExplicit
    )
{
    RRETURN(E_NOTIMPL);
}






















