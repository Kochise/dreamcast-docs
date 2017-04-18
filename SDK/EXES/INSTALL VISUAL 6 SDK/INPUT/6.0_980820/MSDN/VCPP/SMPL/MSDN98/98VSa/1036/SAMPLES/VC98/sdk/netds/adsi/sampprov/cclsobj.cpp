/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CClsObj.cpp

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

//  Class CSampleDSClass

DEFINE_IDispatch_Implementation(CSampleDSClass)
DEFINE_IADs_Implementation(CSampleDSClass)


CSampleDSClass::CSampleDSClass():
      _pDispMgr( NULL ),
      _lpClassName(0),
      _dwNumberOfMandatoryAttributes(0),
      _lpMandatoryAttributes(0)

{
    ENLIST_TRACKING(CSampleDSClass);
}

HRESULT
CSampleDSClass::CreateClass(
    BSTR Parent,
    BSTR CommonName,
    LPSampleDS_CLASS_DEF lpClassDefs,
    DWORD dwObjectState,
    REFIID riid,
    void **ppvObj
    )
{
    CSampleDSClass FAR * pClass = NULL;
    HRESULT hr = S_OK;

    hr = AllocateClassObject(&pClass);
    BAIL_ON_FAILURE(hr);

    hr = pClass->InitializeCoreObject(
                Parent,
                CommonName,
                CLASS_CLASS_NAME,
                L"",
                CLSID_SampleDSClass,
                dwObjectState
                );
    BAIL_ON_FAILURE(hr);

    hr = pClass->QueryInterface(riid, ppvObj);
    BAIL_ON_FAILURE(hr);

    pClass->_dwNumberOfMandatoryAttributes =
                    lpClassDefs->dwNumberOfMandatoryAttributes;
    pClass->_lpMandatoryAttributes = CreatePropertyList(
                                          lpClassDefs->lpMandatoryAttributes
                                          );
    
    pClass->Release();

    RRETURN(hr);

error:

    delete pClass;
    RRETURN(hr);
}

HRESULT
CSampleDSClass::CreateClass(
    BSTR Parent,
    BSTR CommonName,
    HANDLE hTree,
    DWORD dwObjectState,
    REFIID riid,
    void **ppvObj
    )
{
    HRESULT hr = S_OK;
    LPSampleDS_CLASS_DEF lpClassDefs = NULL;

    hr = SampleDSGetClassDefinition(&lpClassDefs,
                                    CommonName);
    BAIL_ON_FAILURE(hr);
    
    if (!lpClassDefs) {
        hr = E_FAIL;
        BAIL_ON_FAILURE(hr);
    }

    hr = CSampleDSClass::CreateClass(
                    Parent,
                    CommonName,
                    lpClassDefs,
                    dwObjectState,
                    riid,
                    ppvObj
                    );

error:
    if (lpClassDefs) {
        SampleDSFreeClassDefinition(lpClassDefs,
                                    1);
    };
    RRETURN(hr);
}


CSampleDSClass::~CSampleDSClass( )
{
    delete _pDispMgr;
}

STDMETHODIMP
CSampleDSClass::QueryInterface(
    REFIID iid,
    LPVOID FAR* ppv
    )
{
    if (IsEqualIID(iid, IID_IUnknown))
    {
        *ppv = (IADsClass FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IADsClass))
    {
        *ppv = (IADsClass FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IADs))
    {
        *ppv = (IADsClass FAR *) this;
    }
    else if (IsEqualIID(iid, IID_IDispatch))
    {
        *ppv = (IADsClass FAR *) this;
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
CSampleDSClass::SetInfo(THIS)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSClass::GetInfo(THIS)
{
    RRETURN(E_NOTIMPL);
}

HRESULT
CSampleDSClass::AllocateClassObject(
    CSampleDSClass ** ppClass
    )
{
    CSampleDSClass FAR * pClass = NULL;
    CDispatchMgr FAR * pDispMgr = NULL;
    HRESULT hr = S_OK;

    pClass = new CSampleDSClass();
    if (pClass == NULL) {
        hr = E_OUTOFMEMORY;
    }
    BAIL_ON_FAILURE(hr);

    pDispMgr = new CDispatchMgr;
    if (pDispMgr == NULL) {
        hr = E_OUTOFMEMORY;
    }
    BAIL_ON_FAILURE(hr);

    hr = LoadTypeInfoEntry(
                pDispMgr,
                LIBID_ADs,
                IID_IADsClass,
                (IADsClass *)pClass,
                DISPID_REGULAR
                );
    BAIL_ON_FAILURE(hr);

    hr = LoadTypeInfoEntry(
                pDispMgr,
                LIBID_ADs,
                IID_IADsContainer,
                (IADsContainer *)pClass,
                DISPID_NEWENUM
                );
    BAIL_ON_FAILURE(hr);

    pClass->_pDispMgr = pDispMgr;
    *ppClass = pClass;

    RRETURN(hr);

error:
    delete  pDispMgr;

    RRETURN(hr);

}


STDMETHODIMP
CSampleDSClass::GetInfo(
    THIS_ DWORD dwApiLevel,
    BOOL fExplicit
    )
{
    RRETURN(E_NOTIMPL);
}


STDMETHODIMP
CSampleDSClass::Get(
    THIS_ BSTR bstrName,
    VARIANT FAR* pvProp
    )
{
    RRETURN(E_NOTIMPL);
}



STDMETHODIMP
CSampleDSClass::Put(
    THIS_ BSTR bstrName,
    VARIANT vProp
    )
{
    RRETURN(E_NOTIMPL);
}

PPROPENTRY
CreatePropertyList(
    LPWSTR_LIST  lpStringList
    )
{
    PPROPENTRY pStart = NULL;
    PPROPENTRY pPropEntry = NULL;

    while (lpStringList) {

        pPropEntry = CreatePropertyEntry(
                            lpStringList->lpString,
                            0
                            );

        pPropEntry->pNext = pStart;
        pStart = pPropEntry;

        lpStringList = lpStringList->Next;
    }

    return(pStart);
}


PPROPENTRY
CreatePropertyEntry(
    LPWSTR pszPropertyName,
    DWORD dwSyntaxId
    )
{
    LPWSTR pszTemp = NULL;
    PPROPENTRY pPropName = NULL;

    pszTemp = (LPWSTR)AllocProvStr(
                    pszPropertyName
                    );
    if (!pszTemp) {
        return(NULL);
    }

    pPropName = (PPROPENTRY)AllocProvMem(
                        sizeof(PROPENTRY)
                        );
    if (!pPropName) {
        FreeProvStr(pszTemp);
        return(NULL);
    }

    pPropName->pszPropName = pszTemp;
    pPropName->dwSyntaxId = dwSyntaxId;

    return(pPropName);
}

void
FreePropertyEntry(
    PPROPENTRY pPropName
    )
{
    if (pPropName->pszPropName) {
        FreeProvStr(pPropName->pszPropName);
    }

    FreeProvMem(pPropName);

    return;
}

HRESULT
MakeVariantFromPropList(
    PPROPENTRY pPropList,
    DWORD dwNumEntries,
    VARIANT * pVarList
    )
{
    SAFEARRAYBOUND sabNewArray;
    SAFEARRAY * pFilter = NULL;
    HRESULT hr = S_OK;
    DWORD dwSLBound = 0;
    DWORD dwSUBound = 0;
    DWORD i = 0;
    VARIANT v;

    VariantInit(pVarList);

    sabNewArray.cElements = dwNumEntries;
    sabNewArray.lLbound = 0;

    pFilter = SafeArrayCreate(
                    VT_VARIANT,
                    1,
                    &sabNewArray
                    );

    if (!pFilter) {
        hr = E_OUTOFMEMORY;
        BAIL_ON_FAILURE(hr);
    }

    for (i = dwSLBound; i < (dwSLBound + dwNumEntries); i++) {
        VariantInit(&v);
        V_VT(&v) = VT_BSTR;

        V_BSTR(&v) = SysAllocString(pPropList->pszPropName);

        hr = SafeArrayPutElement(
                pFilter,
                (long*)&i,
                (void *)&v
                );
        BAIL_ON_FAILURE(hr);

        pPropList = pPropList->pNext;

    }

    V_VT(pVarList) = VT_ARRAY | VT_VARIANT;
    V_ARRAY(pVarList) = pFilter;

    RRETURN(S_OK);

error:

    if (pFilter) {
        SafeArrayDestroy(pFilter);
    }

    RRETURN(hr);
}

/* IADsClass methods */

STDMETHODIMP
CSampleDSClass::get_PrimaryInterface( THIS_ BSTR FAR *pbstrGUID )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_CLSID( THIS_ BSTR FAR *pbstrCLSID )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::put_CLSID( THIS_ BSTR bstrCLSID )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_OID( THIS_ BSTR FAR *pbstrOID )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::put_OID( THIS_ BSTR bstrOID )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_Abstract( THIS_ VARIANT_BOOL FAR *pfAbstract )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::put_Abstract( THIS_ VARIANT_BOOL fAbstract )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_MandatoryProperties( THIS_ VARIANT FAR *pvMandatoryProperties )
{
    HRESULT hr = S_OK;

    hr = MakeVariantFromPropList(
            _lpMandatoryAttributes,
            _dwNumberOfMandatoryAttributes,
            pvMandatoryProperties
            );
    RRETURN(hr);
}

STDMETHODIMP
CSampleDSClass::put_MandatoryProperties( THIS_ VARIANT vMandatoryProperties )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_DerivedFrom( THIS_ VARIANT FAR *pvDerivedFrom )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::put_DerivedFrom( THIS_ VARIANT vDerivedFrom )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_Containment( THIS_ VARIANT FAR *pvContainment )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::put_Containment( THIS_ VARIANT vContainment )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_Container( THIS_ VARIANT_BOOL FAR *pfContainer )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::put_Container( THIS_ VARIANT_BOOL fContainer )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_HelpFileName( THIS_ BSTR FAR *pbstrHelpFileName )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::put_HelpFileName( THIS_ BSTR bstrHelpFile )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_HelpFileContext( THIS_ long FAR *plHelpContext )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::put_HelpFileContext( THIS_ long lHelpContext )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::Qualifiers(THIS_ IADsCollection FAR* FAR* ppQualifiers)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSClass::get_Auxiliary( THIS_ VARIANT_BOOL FAR *pfAuxiliary )
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSClass::put_Auxiliary( THIS_ VARIANT_BOOL fAuxiliary )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_OptionalProperties( THIS_ VARIANT FAR *retval )
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSClass::put_OptionalProperties( THIS_ VARIANT vOptionalProperties )
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSClass::get_NamingProperties( THIS_ VARIANT FAR *retval )
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSClass::put_NamingProperties( THIS_ VARIANT vNamingProperties )
{
    RRETURN(E_NOTIMPL);
}
STDMETHODIMP
CSampleDSClass::get_AuxDerivedFrom( THIS_ VARIANT FAR *pvAuxDerivedFrom )
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSClass::put_AuxDerivedFrom( THIS_ VARIANT vAuxDerivedFrom )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

STDMETHODIMP
CSampleDSClass::get_PossibleSuperiors( THIS_ VARIANT FAR *pvPossSuperiors)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSClass::put_PossibleSuperiors( THIS_ VARIANT vPossSuperiors )
{
    RRETURN(E_ADS_PROPERTY_NOT_SUPPORTED);
}

