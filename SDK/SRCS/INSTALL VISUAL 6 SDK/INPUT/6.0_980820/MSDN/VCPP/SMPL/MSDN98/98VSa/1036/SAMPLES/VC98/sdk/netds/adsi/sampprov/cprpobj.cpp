/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CPrpObj.cpp

Abstract:


Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

// Class CSampleDSProperty

DEFINE_IDispatch_Implementation(CSampleDSProperty)
DEFINE_IADs_Implementation(CSampleDSProperty)

CSampleDSProperty::CSampleDSProperty()
    : _pDispMgr( NULL ),
      _bstrSyntax( NULL )
{

    ENLIST_TRACKING(CSampleDSProperty);
}

CSampleDSProperty::~CSampleDSProperty()
{
    delete _pDispMgr;
}

HRESULT
CSampleDSProperty::CreateProperty(
    BSTR   bstrParent,
    BSTR   bstrName,
    LPSampleDS_ATTR_DEF lpAttrDef,
    DWORD  dwObjectState,
    REFIID riid,
    void **ppvObj
    )
{
    CSampleDSProperty FAR * pProperty = NULL;
    HRESULT hr = S_OK;
    WCHAR szADsSyntax[MAX_PATH];
    WCHAR szSampleDSSyntax[MAX_PATH];

    hr = AllocatePropertyObject( &pProperty );
    BAIL_ON_FAILURE(hr);

    hr = pProperty->InitializeCoreObject(
             bstrParent,
             bstrName,
             PROPERTY_CLASS_NAME,
             L"",
             CLSID_SampleDSProperty,
             dwObjectState
             );
    BAIL_ON_FAILURE(hr);

    hr = pProperty->QueryInterface( riid, ppvObj );
    BAIL_ON_FAILURE(hr);

    MapSyntaxIdtoADsSyntax(
            lpAttrDef->dwSyntaxID,
            szADsSyntax
            );

    hr = ProvAllocString(
                szADsSyntax,
                &pProperty->_bstrSyntax
                );
    BAIL_ON_FAILURE(hr);

    MapSyntaxIdtoSampleDSSyntax(
            lpAttrDef->dwSyntaxID,
            szSampleDSSyntax
            );
    
    pProperty->Release();

    RRETURN(hr);

error:

    delete pProperty;
    RRETURN(hr);
}

HRESULT
CSampleDSProperty::CreateProperty(
    BSTR   bstrParent,
    BSTR   bstrName,
    HANDLE hTree,
    DWORD  dwObjectState,
    REFIID riid,
    void **ppvObj
    )
{
    DWORD dwStatus = 0;
    HRESULT hr = S_OK;
    LPSampleDS_ATTR_DEF lpAttrDefs = NULL;
    DWORD dwNumberOfEntries = 0;
    DWORD dwInfoType = 0;
    HANDLE hOperationData = NULL;
    hr = SampleDSGetPropertyDefinition(&lpAttrDefs,
                                       bstrName);
    BAIL_ON_FAILURE(hr);

    if (!lpAttrDefs) {
        hr = E_FAIL;
        BAIL_ON_FAILURE(hr);
    }

    hr = CSampleDSProperty::CreateProperty(
                bstrParent,
                bstrName,
                lpAttrDefs,
                dwObjectState,
                riid,
                ppvObj
                );
error:
    if (lpAttrDefs)
        SampleDSFreePropertyDefinition(lpAttrDefs,
                                       1
                                      );
    RRETURN(hr);
}

STDMETHODIMP
CSampleDSProperty::QueryInterface(
    REFIID iid,
    LPVOID FAR* ppv
    )
{
    if (IsEqualIID(iid, IID_IUnknown))
    {
        *ppv = (IADsProperty FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IDispatch))
    {
        *ppv = (IADsProperty FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IADsProperty))
    {
        *ppv = (IADsProperty FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IADs))
    {
        *ppv = (IADsProperty FAR *) this;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    AddRef();
    return NOERROR;
}

/* IADs methods */

STDMETHODIMP
CSampleDSProperty::SetInfo(THIS)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSProperty::GetInfo(THIS)
{
    RRETURN(S_OK);
}


HRESULT
CSampleDSProperty::AllocatePropertyObject(
    CSampleDSProperty FAR * FAR * ppProperty
    )
{
    CSampleDSProperty FAR *pProperty = NULL;
    CDispatchMgr FAR *pDispMgr = NULL;
    HRESULT hr = S_OK;

    pProperty = new CSampleDSProperty();
    if ( pProperty == NULL )
        hr = E_OUTOFMEMORY;
    BAIL_ON_FAILURE(hr);

    pDispMgr = new CDispatchMgr;
    if ( pDispMgr == NULL )
        hr = E_OUTOFMEMORY;
    BAIL_ON_FAILURE(hr);

    hr = LoadTypeInfoEntry(
            pDispMgr,
            LIBID_ADs,
            IID_IADsProperty,
            (IADsProperty *) pProperty,
            DISPID_REGULAR
            );
    BAIL_ON_FAILURE(hr);

    pProperty->_pDispMgr = pDispMgr;
    *ppProperty = pProperty;

    RRETURN(hr);

error:

    delete pDispMgr;
    delete pProperty;

    RRETURN(hr);

}


STDMETHODIMP
CSampleDSProperty::Get(
    THIS_ BSTR bstrName,
    VARIANT FAR* pvProp
    )
{
    RRETURN(E_NOTIMPL);
}



STDMETHODIMP
CSampleDSProperty::Put(
    THIS_ BSTR bstrName,
    VARIANT vProp
    )
{
    RRETURN(E_NOTIMPL);
}


HRESULT
MapSyntaxIdtoADsSyntax(
    DWORD dwSyntaxId,
    LPWSTR pszADsSyntax
    )
{

    if (dwSyntaxId > g_cSampleDSSyntaxMap) {
        wcscpy(pszADsSyntax, L"Out of Bounds");
    }else {
        wcscpy(pszADsSyntax, g_aSampleDSSyntaxMap[dwSyntaxId - 1].bstrName);
    }
    RRETURN(S_OK);

}

HRESULT
MapSyntaxIdtoSampleDSSyntax(
    DWORD dwSyntaxId,
    LPWSTR pszSampleDSSyntax
    )
{

    if (dwSyntaxId > g_cSampleDSSyntaxMap) {
        wcscpy(pszSampleDSSyntax, L"Out of Bounds");
    }else {
        wcscpy(pszSampleDSSyntax, g_aSampleDSSyntaxMap[dwSyntaxId - 1].bstrSampleDSName);
    }
    RRETURN(S_OK);

}
/* IADsProperty methods */

STDMETHODIMP
CSampleDSProperty::get_OID( THIS_ BSTR FAR *pbstrOID )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSProperty::put_OID( THIS_ BSTR bstrOID )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSProperty::get_Syntax( THIS_ BSTR FAR *pbstrSyntax )
{
    if ( !pbstrSyntax )
        RRETURN(E_ADS_BAD_PARAMETER);

    RRETURN( ProvAllocString( _bstrSyntax, pbstrSyntax ));
}

STDMETHODIMP
CSampleDSProperty::put_Syntax( THIS_ BSTR bstrSyntax )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSProperty::get_MaxRange( THIS_ long FAR *plMaxRange )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSProperty::put_MaxRange( THIS_ long lMaxRange )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSProperty::get_MinRange( THIS_ long FAR *plMinRange )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSProperty::put_MinRange( THIS_ long lMinRange )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSProperty::get_MultiValued( THIS_ VARIANT_BOOL FAR *pfMultiValued )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSProperty::put_MultiValued( THIS_ VARIANT_BOOL fMultiValued )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSProperty::Qualifiers(THIS_ IADsCollection FAR* FAR* ppQualifiers)
{
    RRETURN(E_NOTIMPL);
}
    
