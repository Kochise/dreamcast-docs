/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CProps.cpp

Abstract:

    Property Cache functionality 

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop


//+------------------------------------------------------------------------
//
//  Function:   CPropertyCache::addproperty
//
//  Synopsis:
//
//
//
//  Arguments:  [szPropertyName]    --
//              [vt]                --
//              [vaData]            --
//
//
//-------------------------------------------------------------------------
HRESULT
CPropertyCache::
addproperty(
    LPWSTR szPropertyName,
    DWORD  dwSyntaxId,
    DWORD  dwNumValues,
    PSampleDSOBJECT pSampleDSObject
    )
{
    HRESULT hr = S_OK;
    PPROPERTY pNewProperty = NULL;

    //
    //  extend the property cache by adding a new property entry
    //

    _pProperties = (PPROPERTY)ReallocProvMem(
                                _pProperties,
                                _cb,
                                _cb + sizeof(PROPERTY)
                                );
    if (!_pProperties) {
        hr = E_OUTOFMEMORY;
        BAIL_ON_FAILURE(hr);
    }


    pNewProperty = (PPROPERTY)((LPBYTE)_pProperties + _cb);

    wcscpy(pNewProperty->szPropertyName, szPropertyName);

    //
    // Update the index
    //

    _dwMaxProperties++;
    _cb += sizeof(PROPERTY);

error:
    RRETURN(hr);
}


//+------------------------------------------------------------------------
//
//  Function:   CPropertyCache::updateproperty
//
//  Synopsis:
//
//
//
//  Arguments:  [szPropertyName]    --
//              [vaData]    --
//
//-------------------------------------------------------------------------
HRESULT
CPropertyCache::
updateproperty(
    LPWSTR szPropertyName,
    DWORD  dwSyntaxId,
    DWORD  dwNumValues,
    PSampleDSOBJECT pSampleDSObject,
    BOOL fExplicit
    )
{
    HRESULT hr;
    DWORD dwIndex;
    PSampleDSOBJECT pNdsTempObject = NULL;
    PPROPERTY pThisProperty = NULL;

    hr = findproperty(
            szPropertyName,
            &dwIndex
            );
    BAIL_ON_FAILURE(hr);

    pThisProperty = _pProperties + dwIndex;

    if (!fExplicit) {
        if (PROPERTY_FLAGS(pThisProperty) & CACHE_PROPERTY_MODIFIED) {
            hr = S_OK;
            goto error;
        }
    }


    if (PROPERTY_SampleDSOBJECT(pThisProperty)) {

        SampleDSTypeFreeSampleDSObjects(
                PROPERTY_SampleDSOBJECT(pThisProperty),
                PROPERTY_NUMVALUES(pThisProperty)
                );
        PROPERTY_SampleDSOBJECT(pThisProperty) = NULL;
    }
    PROPERTY_SYNTAX(pThisProperty) = dwSyntaxId;
    PROPERTY_NUMVALUES(pThisProperty) = dwNumValues;

    hr = SampleDSTypeCopyConstruct(
            pSampleDSObject,
            dwNumValues,
            &pNdsTempObject
            );
    BAIL_ON_FAILURE(hr);

    PROPERTY_SampleDSOBJECT(pThisProperty) = pNdsTempObject;

    PROPERTY_FLAGS(pThisProperty)  &= ~CACHE_PROPERTY_MODIFIED;

error:

    RRETURN(hr);

}


//+------------------------------------------------------------------------
//
//  Function:   CPropertyCache::findproperty
//
//  Synopsis:
//
//
//
//  Arguments:  [szPropertyName] --
//              [pdwIndex]       --
//
//-------------------------------------------------------------------------
HRESULT
CPropertyCache::
findproperty(
    LPWSTR szPropertyName,
    PDWORD pdwIndex
    )

{
    DWORD i = 0;
    PPROPERTY pThisProperty = NULL;

    for (i = 0; i < _dwMaxProperties; i++) {

        pThisProperty = _pProperties + i;

        if (!_wcsicmp(pThisProperty->szPropertyName, szPropertyName)) {
            *pdwIndex = i;
            RRETURN(S_OK);
        }
    }
    *pdwIndex = 0;
    RRETURN(E_ADS_PROPERTY_NOT_FOUND);
}

//+------------------------------------------------------------------------
//
//  Function:   CPropertyCache::getproperty
//
//  Synopsis:
//
//
//
//  Arguments:  [szPropertyName]    --  Property to retrieve from the cache
//              [pvaData]           --  Data returned in a variant
//
//-------------------------------------------------------------------------
HRESULT
CPropertyCache::
getproperty(
    LPWSTR szPropertyName,
    PDWORD  pdwSyntaxId,
    PDWORD  pdwNumValues,
    PSampleDSOBJECT * ppSampleDSObject
    )
{
    HRESULT hr;
    DWORD dwIndex = 0L;
    PPROPERTY pThisProperty = NULL;

    hr = findproperty(
            szPropertyName,
            &dwIndex
            );

    if (hr == E_ADS_PROPERTY_NOT_FOUND) {

        //
        // Now call the GetInfo function
        //

        hr = _pCoreADsObject->GetInfo(
                    FALSE
                    );
        BAIL_ON_FAILURE(hr);

        hr = findproperty(
                    szPropertyName,
                    &dwIndex
                    );

    }
    BAIL_ON_FAILURE(hr);

    pThisProperty = _pProperties + dwIndex;

    if (PROPERTY_SampleDSOBJECT(pThisProperty)) {

        *pdwSyntaxId = (DWORD)PROPERTY_SYNTAX(pThisProperty);
        *pdwNumValues = (DWORD)PROPERTY_NUMVALUES(pThisProperty);

        hr = SampleDSTypeCopyConstruct(
                PROPERTY_SampleDSOBJECT(pThisProperty),
                PROPERTY_NUMVALUES(pThisProperty),
                ppSampleDSObject
                );
        BAIL_ON_FAILURE(hr);

    }else {

        *ppSampleDSObject = NULL;
        *pdwNumValues = 0;
        *pdwSyntaxId = 0;
        hr = E_FAIL;

    }

error:

   RRETURN(hr);
}

//+------------------------------------------------------------------------
//
//  Function:   CPropertyCache::putproperty
//
//  Synopsis:
//
//
//
//  Arguments:  [szPropertyName]    --  Clsid index
//              [vaData]    --  Matching clsid returned in *pclsid
//
//-------------------------------------------------------------------------
HRESULT
CPropertyCache::
putproperty(
    LPWSTR szPropertyName,
    DWORD  dwSyntaxId,
    DWORD  dwNumValues,
    PSampleDSOBJECT pSampleDSOBJECT
    )
{
    HRESULT hr;
    DWORD dwIndex = 0L;
    PSampleDSOBJECT pSampleDSTempObject = NULL;
    PPROPERTY pThisProperty = NULL;

    hr = findproperty(
            szPropertyName,
            &dwIndex
            );
    BAIL_ON_FAILURE(hr);

    pThisProperty = _pProperties + dwIndex;

    if (PROPERTY_SampleDSOBJECT(pThisProperty)) {

        SampleDSTypeFreeSampleDSObjects(
                PROPERTY_SampleDSOBJECT(pThisProperty),
                PROPERTY_NUMVALUES(pThisProperty)
                );
        PROPERTY_SampleDSOBJECT(pThisProperty) = NULL;
    }

    PROPERTY_SYNTAX(pThisProperty) = dwSyntaxId;
    PROPERTY_NUMVALUES(pThisProperty) = dwNumValues;

    hr = SampleDSTypeCopyConstruct(
            pSampleDSOBJECT,
            dwNumValues,
            &pSampleDSTempObject
            );
    BAIL_ON_FAILURE(hr);

    PROPERTY_SampleDSOBJECT(pThisProperty) = pSampleDSTempObject;

    PROPERTY_FLAGS(pThisProperty) |= CACHE_PROPERTY_MODIFIED;

error:
    RRETURN(hr);
}



//+------------------------------------------------------------------------
//
//  Function:   CPropertyCache
//
//  Synopsis:
//
//
//
//  Arguments:
//
//
//-------------------------------------------------------------------------
CPropertyCache::
CPropertyCache():
        _dwMaxProperties(0),
        _pProperties(NULL),
        _cb(0),
        _pCoreADsObject(NULL)
{

}

//+------------------------------------------------------------------------
//
//  Function:   ~CPropertyCache
//
//  Synopsis:
//
//
//
//  Arguments:
//
//
//-------------------------------------------------------------------------
CPropertyCache::
~CPropertyCache()
{
    DWORD i = 0;
    PPROPERTY pThisProperty = NULL;

    if (_pProperties) {

        for (i = 0; i < _dwMaxProperties; i++) {

            pThisProperty = _pProperties + i;

            if (PROPERTY_SampleDSOBJECT(pThisProperty)) {

                SampleDSTypeFreeSampleDSObjects(
                        PROPERTY_SampleDSOBJECT(pThisProperty),
                        PROPERTY_NUMVALUES(pThisProperty)
                        );
                PROPERTY_SampleDSOBJECT(pThisProperty) = NULL;
            }
        }

        FreeProvMem(_pProperties);
    }
}

//+------------------------------------------------------------------------
//
//  Function:
//
//  Synopsis:
//
//
//
//  Arguments:
//
//
//-------------------------------------------------------------------------
HRESULT
CPropertyCache::
createpropertycache(
    CCoreADsObject FAR * pCoreADsObject,
    CPropertyCache FAR *FAR * ppPropertyCache
    )
{
    CPropertyCache FAR * pPropertyCache = NULL;

    pPropertyCache = new CPropertyCache();

    if (!pPropertyCache) {
        RRETURN(E_FAIL);
    }

    pPropertyCache->_pCoreADsObject = pCoreADsObject;

    *ppPropertyCache = pPropertyCache;

    RRETURN(S_OK);
}


//+------------------------------------------------------------------------
//
//  Function:   CPropertyCache::getproperty
//
//  Synopsis:
//
//
//
//  Arguments:  [szPropertyName]    --  Property to retrieve from the cache
//              [pvaData]           --  Data returned in a variant
//
//-------------------------------------------------------------------------
HRESULT
CPropertyCache::
unboundgetproperty(
    LPWSTR szPropertyName,
    PDWORD  pdwSyntaxId,
    PDWORD  pdwNumValues,
    PSampleDSOBJECT * ppSampleDSOBJECT
    )
{
    HRESULT hr;
    DWORD dwIndex = 0L;
    PPROPERTY pThisProperty = NULL;

    hr = findproperty(
            szPropertyName,
            &dwIndex
            );
    BAIL_ON_FAILURE(hr);

    pThisProperty = _pProperties + dwIndex;

    if (PROPERTY_SampleDSOBJECT(pThisProperty)) {

        *pdwSyntaxId = (DWORD)PROPERTY_SYNTAX(pThisProperty);
        *pdwNumValues = (DWORD)PROPERTY_NUMVALUES(pThisProperty);

        hr = SampleDSTypeCopyConstruct(
                PROPERTY_SampleDSOBJECT(pThisProperty),
                PROPERTY_NUMVALUES(pThisProperty),
                ppSampleDSOBJECT
                );
        BAIL_ON_FAILURE(hr);

    }else {

        *ppSampleDSOBJECT = NULL;
        *pdwNumValues = 0;
        *pdwSyntaxId = 0;
        hr = E_FAIL;

    }

error:

   RRETURN(hr);
}



HRESULT
CPropertyCache::
SampleDSMarshallProperties(
    HANDLE hOperationData
    )
{
    LPSampleDS_ATTRS_INFO pAttrsInfo = (LPSampleDS_ATTRS_INFO)hOperationData;
    HRESULT hr = S_OK;
    DWORD i = 0;
    PPROPERTY pThisProperty = NULL;
    BYTE lpBuffer[2048];
    DWORD cProperty = 0;
    LPSampleDS_ATTR_INFO pAttrInfoMemStart = NULL; 
    LPSampleDS_ATTR_INFO pAttrInfoMem = NULL; 
    pAttrInfoMemStart = (LPSampleDS_ATTR_INFO)AllocProvMem(
                                     sizeof(SampleDS_ATTR_INFO)*_dwMaxProperties);
    if (!pAttrInfoMemStart)
        goto Error;

    pAttrInfoMem = pAttrInfoMemStart;

    for (i = 0; i < _dwMaxProperties ; i++) {

        pThisProperty = _pProperties + i;

        //
        // Bypass any property that has not been
        // modified
        //

        if (PROPERTY_FLAGS(pThisProperty) == 0) {

            continue;
        }

        hr = MarshallSampleDSSynIdToSampleDS(
                PROPERTY_SYNTAX(pThisProperty),
                PROPERTY_SampleDSOBJECT(pThisProperty),
                PROPERTY_NUMVALUES(pThisProperty),
                lpBuffer
                );
        CONTINUE_ON_FAILURE(hr);


        hr = marshallproperty(
                pAttrInfoMem,
                PROPERTY_NAME(pThisProperty),
                lpBuffer,
                PROPERTY_NUMVALUES(pThisProperty),
                PROPERTY_SYNTAX(pThisProperty)
                );
        CONTINUE_ON_FAILURE(hr);
        cProperty++;
        pAttrInfoMem++;
    }

    if (cProperty != _dwMaxProperties) {
        LPSampleDS_ATTR_INFO pAttrInfoNew; 
        pAttrInfoNew = (LPSampleDS_ATTR_INFO)AllocProvMem(
                                         sizeof(SampleDS_ATTR_INFO)*cProperty);
        if (!pAttrInfoNew) {
            hr = E_FAIL;
            goto Error;
        }
        memcpy( (void*)pAttrInfoNew,
                (void*)pAttrInfoMemStart,
                sizeof(SampleDS_ATTR_INFO)*cProperty);
        FreeProvMem(pAttrInfoMemStart);
        pAttrInfoMemStart = pAttrInfoNew;
    }
    pAttrsInfo->pAttrInfo = pAttrInfoMemStart;
    pAttrsInfo->dwAttr = cProperty;
    RRETURN(hr);

Error:
    if (pAttrInfoMem)
        FreeProvMem(pAttrInfoMem);
    RRETURN(hr);

}

HRESULT
CPropertyCache::
marshallproperty(
    LPSampleDS_ATTR_INFO pAttrInfo,
    LPWSTR szPropertyName,
    LPBYTE lpValues,
    DWORD  dwNumValues,
    DWORD  dwSyntaxId
    )
{
    pAttrInfo->lpAttributeName = (LPWSTR)AllocProvStr(szPropertyName);
    if (!pAttrInfo->lpAttributeName)
        RRETURN(E_FAIL);
    
    DWORD dwMemSize;
    switch (dwSyntaxId) {
        case SampleDS_DATATYPE_1:
            dwMemSize = sizeof(SampleDS_TYPE_1);
            break;
        case SampleDS_DATATYPE_2:
            dwMemSize = sizeof(SampleDS_TYPE_2);
            break;
        default:
            goto Error;
    }
    pAttrInfo->lpValue = (BYTE*)AllocProvMem(dwMemSize);
    if (!pAttrInfo->lpValue)
        goto Error;
    memcpy( (void*)pAttrInfo->lpValue,
            (void*)lpValues,
            dwMemSize);
    
    pAttrInfo->dwSyntaxId = dwSyntaxId;
    pAttrInfo->dwNumberOfValues = dwNumValues;
    RRETURN(S_OK);
Error:
    if (pAttrInfo->lpAttributeName)
        FreeProvMem(pAttrInfo->lpAttributeName);
    if (pAttrInfo->lpValue)
        FreeProvMem(pAttrInfo->lpValue);
    RRETURN(E_FAIL);
}

HRESULT
CPropertyCache::
SampleDSUnMarshallProperties(
    HANDLE hOperationData,
    BOOL fExplicit
    )

{
    LPSampleDS_ATTRS_INFO pAttrsInfo = (LPSampleDS_ATTRS_INFO)hOperationData;
    
    DWORD dwNumberOfEntries = 0L;
    LPSampleDS_ATTR_INFO lpEntries = pAttrsInfo->pAttrInfo;
    DWORD dwEntry = pAttrsInfo->dwAttr;
    HRESULT hr = S_OK;
    DWORD i = 0;
    DWORD dwStatus = 0L;

    for (i = 0; i < dwEntry; i++) {

        //
        // unmarshall this property into the
        // property cache
        //
        
        hr = unmarshallproperty(
                    lpEntries[i].lpAttributeName,
                    lpEntries[i].lpValue,
                    lpEntries[i].dwNumberOfValues,
                    lpEntries[i].dwSyntaxId,
                    fExplicit
                    );

        CONTINUE_ON_FAILURE(hr);

    }

    RRETURN(hr);

}

//+------------------------------------------------------------------------
//
//  Function:
//
//  Synopsis:
//
//
//
//  Arguments:
//
//
//-------------------------------------------------------------------------

HRESULT
CPropertyCache::
unmarshallproperty(
    LPWSTR szPropertyName,
    LPBYTE lpValue,
    DWORD  dwNumValues,
    DWORD  dwSyntaxId,
    BOOL fExplicit
    )
{

    DWORD dwIndex = 0;
    HRESULT hr = S_OK;
    PSampleDSOBJECT pSampleDSObject = NULL;

    hr = UnMarshallSampleDSToSampleDSSynId(
                dwSyntaxId,
                dwNumValues,
                lpValue,
                &pSampleDSObject 
                );
    BAIL_ON_FAILURE(hr);

    //
    // Find this property in the cache
    //

    hr = findproperty(
                szPropertyName,
                &dwIndex
                );

    //
    // If this property does not exist in the
    // cache, add this property into the cache.
    //


    if (FAILED(hr)) {
        hr = addproperty(
                    szPropertyName,
                    dwSyntaxId,
                    dwNumValues,
                    pSampleDSObject 
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

    hr = updateproperty(
                    szPropertyName,
                    dwSyntaxId,
                    dwNumValues,
                    pSampleDSObject,
                    fExplicit
                    );
    BAIL_ON_FAILURE(hr);


    if (pSampleDSObject) {
        SampleDSTypeFreeSampleDSObjects(
                pSampleDSObject,
                dwNumValues
                );

    }


error:
    RRETURN(hr);
}

























































