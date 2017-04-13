/*++ 

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CGenObj.cpp

Abstract:

    Microsoft ADs DS Provider Generic Object

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

DEFINE_IDispatch_Implementation(CSampleDSGenObject)
DEFINE_IADs_Implementation(CSampleDSGenObject)


CSampleDSGenObject::CSampleDSGenObject():_pPropertyCache(NULL)
{
    VariantInit(&_vFilter);
}

HRESULT
CSampleDSGenObject::CreateGenericObject(
    BSTR Parent,
    BSTR CommonName,
    BSTR ClassName,
    DWORD dwObjectState,
    REFIID riid,
    void **ppvObj
    )
{
    CSampleDSGenObject FAR * pGenObject = NULL;
    HRESULT hr = S_OK;

    hr = AllocateGenObject(&pGenObject);
    BAIL_ON_FAILURE(hr);

    hr = pGenObject->InitializeCoreObject(
                Parent,
                CommonName,
                ClassName,
                L"",
                CLSID_SampleDSGenObject,
                dwObjectState
                );
    BAIL_ON_FAILURE(hr);

    hr = pGenObject->QueryInterface(riid, ppvObj);
    BAIL_ON_FAILURE(hr);

    pGenObject->Release();

    RRETURN(hr);

error:

    delete pGenObject;

    RRETURN(hr);
}

CSampleDSGenObject::~CSampleDSGenObject( )
{

    delete _pDispMgr;
    delete _pPropertyCache;

}

STDMETHODIMP
CSampleDSGenObject::QueryInterface(REFIID iid, LPVOID FAR* ppv)
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


HRESULT
CSampleDSGenObject::SetInfo()
{
    HRESULT hr = S_OK;

    if (GetObjectState() == ADS_OBJECT_UNBOUND) {

        hr = SampleDSCreateObject();
        BAIL_ON_FAILURE(hr);

        //
        // If the create succeded, set the object type to bound
        //

        SetObjectState(ADS_OBJECT_BOUND);

    }else {

        hr = SampleDSSetObject();
        BAIL_ON_FAILURE(hr);
    }

error:

    RRETURN(hr);
}


HRESULT
CSampleDSGenObject::SampleDSSetObject()
{
    WCHAR szSampleDSPathName[MAX_PATH];
    HANDLE hObject = NULL;
    HRESULT hr = S_OK;
    HANDLE hOperationData = NULL;


    hr = BuildDSPathFromADsPath(
                _ADsPath,
                szSampleDSPathName
                );
    BAIL_ON_FAILURE(hr);

    
    hr = SampleDSOpenObject(
                    szSampleDSPathName,
                    &hObject,
                    NULL,
                    REG_DS
                    );
    BAIL_ON_FAILURE(hr);

    hr = SampleDSCreateBuffer(&hOperationData);
    BAIL_ON_FAILURE(hr);
    
    hr = _pPropertyCache->SampleDSMarshallProperties(
                            hOperationData
                            );
    
    BAIL_ON_FAILURE(hr);
    hr = SampleDSModifyObject(hObject,
                              hOperationData
                             );
error:
    if (hObject) {
        hr = SampleDSCloseObject(hObject);
    }
    if (hOperationData) {
        SampleDSFreeBuffer(hOperationData);
    }
    RRETURN(hr);
}

HRESULT
CSampleDSGenObject::SampleDSCreateObject()
{
    WCHAR szSampleDSParentName[MAX_PATH];
    HANDLE hOperationData = NULL;
    HANDLE hObject = NULL;
    HRESULT hr = S_OK;

    hr = BuildDSPathFromADsPath(
                _Parent,
                szSampleDSParentName
                );
    BAIL_ON_FAILURE(hr);

    hr = SampleDSOpenObject(
                    szSampleDSParentName,
                    &hObject,
                    NULL,
                    REG_DS
                    );
    BAIL_ON_FAILURE(hr);

    hr = SampleDSCreateBuffer(&hOperationData);
    BAIL_ON_FAILURE(hr);
    
    hr = _pPropertyCache->SampleDSMarshallProperties(
                            hOperationData
                            );
    BAIL_ON_FAILURE(hr);
    
    hr = SampleDSAddObject(
                hObject,
                _Name,
                _ADsClass,
                hOperationData
                );
    
error:
    if (hObject) {
        hr = SampleDSCloseObject(hObject);
    }
    if (hOperationData) {
        SampleDSFreeBuffer(hOperationData);
    }

    RRETURN(hr);
}


HRESULT
CSampleDSGenObject::GetInfo()
{
    RRETURN(GetInfo(TRUE));
}

HRESULT
CSampleDSGenObject::GetInfo(
    BOOL fExplicit
){
    HANDLE hObject = NULL;
    HRESULT hr = S_OK;
    WCHAR szDSPathName[MAX_PATH];
    HANDLE hOperationData = NULL;

    if (GetObjectState() == ADS_OBJECT_UNBOUND) {
        hr = E_ADS_OBJECT_UNBOUND;
        BAIL_ON_FAILURE(hr);
    }

    hr = BuildDSPathFromADsPath(
                _ADsPath,
                szDSPathName
                );
    BAIL_ON_FAILURE(hr);

    hr = SampleDSOpenObject(
                    szDSPathName,
                    &hObject,
                    NULL,
                    REG_DS
                    );
    BAIL_ON_FAILURE(hr);

    hr = SampleDSReadObject(
        hObject,
        &hOperationData
    );
    BAIL_ON_FAILURE(hr);
            
    hr = _pPropertyCache->SampleDSUnMarshallProperties(hOperationData,
                                                       fExplicit
                                                       );
    BAIL_ON_FAILURE(hr);
error:

    if (hObject) {
        hr = SampleDSCloseObject(hObject);
    }
    if (hOperationData) {
        SampleDSFreeBuffer(hOperationData);
    }

    RRETURN(hr);
}

/* IADsContainer methods */

STDMETHODIMP
CSampleDSGenObject::get_Count(long FAR* retval)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSGenObject::get_Filter(THIS_ VARIANT FAR* pVar)
{
    VariantInit(pVar);
    RRETURN(VariantCopy(pVar, &_vFilter));
}

STDMETHODIMP
CSampleDSGenObject::put_Filter(THIS_ VARIANT Var)
{
    RRETURN(VariantCopy(&_vFilter, &Var));
}

STDMETHODIMP
CSampleDSGenObject::put_Hints(THIS_ VARIANT Var)
{
    RRETURN( E_NOTIMPL);
}

STDMETHODIMP
CSampleDSGenObject::get_Hints(THIS_ VARIANT FAR* pVar)
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSGenObject::GetObject(
    BSTR ClassName,
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
CSampleDSGenObject::get__NewEnum(
    THIS_ IUnknown * FAR* retval
    )
{
    HRESULT hr;
    IUnknown FAR* punkEnum=NULL;
    IEnumVARIANT * penum = NULL;


    *retval = NULL;

    hr = CSampleDSGenObjectEnum::Create(
                (CSampleDSGenObjectEnum **)&penum,
                _ADsPath,
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
CSampleDSGenObject::Create(
    THIS_ BSTR ClassName,
    BSTR RelativeName,
    IDispatch * FAR* ppObject
    )
{
    HRESULT hr = S_OK;
    IADs * pADs  = NULL;
    WCHAR szDSTreeName[MAX_PATH];
    DWORD dwSyntaxId = 0;

    //
    // Get the TreeName for this object
    //

    hr = BuildDSTreeNameFromADsPath(
                _ADsPath,
                szDSTreeName
                );
    BAIL_ON_FAILURE(hr);


    //
    // Validate if this class really exists in the schema
    // and validate that this object can be created in this
    // container
    //

    hr = CSampleDSGenObject::CreateGenericObject(
                    _ADsPath,
                    RelativeName,
                    ClassName,
                    ADS_OBJECT_UNBOUND,
                    IID_IDispatch,
                    (void **)ppObject
                    );
    BAIL_ON_FAILURE(hr);

error:

    RRETURN(hr);
}

STDMETHODIMP
CSampleDSGenObject::Delete(
    THIS_ BSTR bstrClassName,
    BSTR bstrRelativeName
    )
{
    WCHAR szDSPathName[MAX_PATH];
    HRESULT hr = S_OK;
    DWORD dwStatus = 0;
    HANDLE hParentObject = NULL;

    hr = BuildDSPathFromADsPath(
                _ADsPath,
                szDSPathName
                );
    BAIL_ON_FAILURE(hr);
    
    hr = SampleDSOpenObject(
                    szDSPathName,
                    &hParentObject,
                    NULL,
                    REG_DS
                    );
    BAIL_ON_FAILURE(hr);

    hr= SampleDSRemoveObject(
                hParentObject,
                bstrRelativeName);
    BAIL_ON_FAILURE(hr);


error:
    if (hParentObject) {
        dwStatus = SampleDSCloseObject(hParentObject);
    }
    RRETURN(hr);
}

STDMETHODIMP
CSampleDSGenObject::CopyHere(
    THIS_ BSTR SourceName,
    BSTR NewName,
    IDispatch * FAR* ppObject
    )
{
    RRETURN(E_NOTIMPL);
}

STDMETHODIMP
CSampleDSGenObject::MoveHere(
    THIS_ BSTR SourceName,
    BSTR NewName,
    IDispatch * FAR* ppObject
    )
{
    RRETURN(E_NOTIMPL);
}

HRESULT
CSampleDSGenObject::AllocateGenObject(CSampleDSGenObject ** ppGenObject)
{
    CSampleDSGenObject FAR * pGenObject = NULL;
    CDispatchMgr FAR * pDispMgr = NULL;
    CPropertyCache FAR * pPropertyCache = NULL;
    HRESULT hr = S_OK;

    pGenObject = new CSampleDSGenObject();
    if (pGenObject == NULL) {
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
                           (IADs *)pGenObject,
                           DISPID_REGULAR
                           );
    BAIL_ON_FAILURE(hr);

    hr = LoadTypeInfoEntry(pDispMgr,
                           LIBID_ADs,
                           IID_IADsContainer,
                           (IADsContainer *)pGenObject,
                           DISPID_NEWENUM
                           );
    BAIL_ON_FAILURE(hr);

    hr = CPropertyCache::createpropertycache(
                        (CCoreADsObject FAR *)pGenObject,
                        &pPropertyCache
                        );
    BAIL_ON_FAILURE(hr);



    pGenObject->_pPropertyCache = pPropertyCache;
    pGenObject->_pDispMgr = pDispMgr;
    *ppGenObject = pGenObject;
    
    RRETURN(hr);

error:
    delete  pDispMgr;
    RRETURN(hr);
}

STDMETHODIMP
CSampleDSGenObject::Get(
    THIS_ BSTR bstrName,
    VARIANT FAR* pvProp
    )
{
    HRESULT hr = S_OK;
    DWORD dwSyntaxId;
    DWORD dwNumValues;
    LPSampleDSOBJECT pNdsSrcObjects = NULL;

    //
    // retrieve data object from cache; if one exists
    //

    if (GetObjectState() == ADS_OBJECT_UNBOUND) {

        hr = _pPropertyCache->unboundgetproperty(
                    bstrName,
                    &dwSyntaxId,
                    &dwNumValues,
                    &pNdsSrcObjects
                    );
        BAIL_ON_FAILURE(hr);

    }else {

        hr = _pPropertyCache->getproperty(
                    bstrName,
                    &dwSyntaxId,
                    &dwNumValues,
                    &pNdsSrcObjects
                    );
        BAIL_ON_FAILURE(hr);
    }


    //
    // translate the Nds objects to variants
    //

    hr = SampleDSTypeToVarTypeCopyConstruct(
                pNdsSrcObjects,
                dwNumValues,
                pvProp
                );
    BAIL_ON_FAILURE(hr);

error:
    if (pNdsSrcObjects) {

        SampleDSTypeFreeSampleDSObjects(
            pNdsSrcObjects,
            dwNumValues
            );
    }

    RRETURN(hr);
}


STDMETHODIMP
CSampleDSGenObject::Put(
    THIS_ BSTR bstrName,
    VARIANT vProp
    )
{
    HRESULT hr = S_OK;
    DWORD dwSyntaxId  = 0;
    DWORD dwIndex = 0;
    LPSampleDSOBJECT pNdsDestObjects = NULL;
    WCHAR szSampleDSTreeName[MAX_PATH];
    DWORD dwNumValues = 0;

    VARIANT * pVarArray = NULL;
    VARIANT * pvProp = NULL;

    //
    // Issue: How do we handle multi-valued support
    //

    if ((V_VT(&vProp) &  VT_VARIANT) &&  V_ISARRAY(&vProp)) {

        hr  = ConvertSafeArrayToVariantArray(
                    vProp,
                    &pVarArray,
                    &dwNumValues
                    );
        BAIL_ON_FAILURE(hr);
        pvProp = pVarArray;

    }else {

        dwNumValues = 1;
        pvProp = &vProp;
    }

    //
    // Get the TreeName for this object
    //

    hr = BuildDSPathFromADsPath(
                _ADsPath,
                szSampleDSTreeName
                );
    BAIL_ON_FAILURE(hr);
    
    //
    // check if the variant maps to the syntax of this property
    //
    switch (vProp.vt) {
        case VT_BSTR:
                dwSyntaxId = SampleDS_DATATYPE_1;
                break;
        case VT_I4:
                dwSyntaxId = SampleDS_DATATYPE_2;
                break;
        default:
                hr = E_FAIL;
                goto error;
        }
                hr = VarTypeToSampleDSTypeCopyConstruct(
                    dwSyntaxId,
                    pvProp,
                    dwNumValues,
                    &pNdsDestObjects
                    );
    BAIL_ON_FAILURE(hr);

    //
    // Find this property in the cache
    //

    hr = _pPropertyCache->findproperty(
                        bstrName,
                        &dwIndex
                        );

    //
    // If this property does not exist in the
    // cache, add this property into the cache.
    //


    if (FAILED(hr)) {
        hr = _pPropertyCache->addproperty(
                    bstrName,
                    dwSyntaxId,
                    dwNumValues,
                    pNdsDestObjects
                    );
        //
        // If the operation fails for some reason
        // move on to the next property
        //
        BAIL_ON_FAILURE(hr);

    }

    //
    // Now update the property in the cache
    //

    hr = _pPropertyCache->putproperty(
                    bstrName,
                    dwSyntaxId,
                    dwNumValues,
                    pNdsDestObjects
                    );
    BAIL_ON_FAILURE(hr);

error:

    if (pNdsDestObjects) {
        SampleDSTypeFreeSampleDSObjects(
                pNdsDestObjects,
                dwNumValues
                );

    }


    if (pVarArray) {

        DWORD i = 0;

        for (i = 0; i < dwNumValues; i++) {
            VariantClear(pVarArray + i);
        }
        FreeProvMem(pVarArray);
    }

    RRETURN(hr);
}


HRESULT
ConvertSafeArrayToVariantArray(
    VARIANT varSafeArray,
    VARIANT ** ppVarArray,
    PDWORD pdwNumVariants
    )
{
    HRESULT hr = S_OK;
    DWORD dwSLBound = 0;
    DWORD dwSUBound = 0;
    DWORD i = 0;
    DWORD dwNumVariants = 0;
    VARIANT * pVarArray = NULL;

    *pdwNumVariants = 0;
    *ppVarArray  = 0;

    if(!((V_VT(&varSafeArray) &  VT_VARIANT) &&  V_ISARRAY(&varSafeArray))) {
        return(E_FAIL);
    }

    //
    // Check that there is only one dimension in this array
    //

    if ((V_ARRAY(&varSafeArray))->cDims != 1) {
        hr = E_FAIL;
        BAIL_ON_FAILURE(hr);
    }
    //
    // Check that there is atleast one element in this array
    //

    if ((V_ARRAY(&varSafeArray))->rgsabound[0].cElements == 0){
        hr = E_FAIL;
        BAIL_ON_FAILURE(hr);
    }

    hr = SafeArrayGetLBound(V_ARRAY(&varSafeArray),
                            1,
                            (long FAR *)&dwSLBound
                            );
    BAIL_ON_FAILURE(hr);

    hr = SafeArrayGetUBound(V_ARRAY(&varSafeArray),
                            1,
                            (long FAR *)&dwSUBound
                            );
    BAIL_ON_FAILURE(hr);

    dwNumVariants = dwSUBound - dwSLBound + 1;
    pVarArray = (VARIANT*)AllocProvMem(
                                sizeof(VARIANT)*dwNumVariants
                                );
    if (!pVarArray) {
        hr = E_OUTOFMEMORY;
        BAIL_ON_FAILURE(hr);
    }

    for (i = dwSLBound; i <= dwSUBound; i++) {

        VariantInit(pVarArray + i);
        hr = SafeArrayGetElement(V_ARRAY(&varSafeArray),
                                (long FAR *)&i,
                                (pVarArray + i)
                                );
        CONTINUE_ON_FAILURE(hr);
    }

    *ppVarArray = pVarArray;
    *pdwNumVariants = dwNumVariants;

error:

    RRETURN(hr);
}



