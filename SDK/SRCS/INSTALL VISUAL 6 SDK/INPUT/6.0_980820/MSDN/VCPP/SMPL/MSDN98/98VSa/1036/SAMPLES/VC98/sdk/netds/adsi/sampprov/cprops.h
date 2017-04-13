/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CProps.h

Abstract:

    Property Cache Object
    
Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CPROPS_H_
#define _CPROPS_H_


typedef struct _property{
    WCHAR   szPropertyName[MAX_PATH];
    DWORD   dwFlags;
    DWORD   dwNumValues;        
    DWORD   dwSyntaxId;         
    PSampleDSOBJECT pSampleDSObject;      // Pointer to the SampleDS Object
}PROPERTY, *PPROPERTY;

#define PROPERTY_NAME(pProperty)            pProperty->szPropertyName
#define PROPERTY_VALUES(pProperty)          pProperty->lpValues
#define PROPERTY_NUMVALUES(pProperty)       pProperty->dwNumValues
#define PROPERTY_SYNTAX(pProperty)          pProperty->dwSyntaxId
#define PROPERTY_SampleDSOBJECT(pProperty)  pProperty->pSampleDSObject
#define PROPERTY_FLAGS(pProperty)           pProperty->dwFlags

#define CACHE_PROPERTY_MODIFIED        0x1

class CPropertyCache {

public:

    HRESULT
    CPropertyCache::
    addproperty(
        LPWSTR szPropertyName,
        DWORD  dwSyntaxId,
        DWORD  dwNumValues,
        PSampleDSOBJECT pSampleDSObject
        );

    HRESULT
    CPropertyCache::
    updateproperty(
        LPWSTR szPropertyName,
        DWORD  dwSyntaxId,
        DWORD  dwNumValues,
        PSampleDSOBJECT pSampleDSObject,
        BOOL fExplicit
        );

    HRESULT
    CPropertyCache::
    findproperty(
        LPWSTR szPropertyName,
        PDWORD pdwIndex
        );

    HRESULT
    CPropertyCache::
    getproperty(
        LPWSTR szPropertyName,
        PDWORD  pdwSyntaxId,
        PDWORD  pdwNumValues,
        PSampleDSOBJECT * ppSampleDSObject
        );

    HRESULT
    CPropertyCache::
    unboundgetproperty(
        LPWSTR szPropertyName,
        PDWORD  pdwSyntaxId,
        PDWORD  pdwNumValues,
        PSampleDSOBJECT * ppSampleDSObject
        );

    HRESULT
    CPropertyCache::
    putproperty(
        LPWSTR szPropertyName,
        DWORD  dwSyntaxId,
        DWORD  dwNumValues,
        PSampleDSOBJECT pSampleDSObject
        );

    CPropertyCache::
    CPropertyCache();

    CPropertyCache::
    ~CPropertyCache();

    static
    HRESULT
    CPropertyCache::
    createpropertycache(
        CCoreADsObject FAR * pCoreADsObject,
        CPropertyCache FAR * FAR * ppPropertyCache
        );

    HRESULT
    CPropertyCache::
    unmarshallproperty(
        LPWSTR szPropertyName,
        LPBYTE lpValue,
        DWORD  dwNumValues,
        DWORD  dwSyntaxId,
        BOOL fExplicit
        );

    HRESULT
    CPropertyCache::
    SampleDSUnMarshallProperties(
        HANDLE hOperationData,
        BOOL fExplicit
        );


    HRESULT
    CPropertyCache::
    marshallproperty(
        LPSampleDS_ATTR_INFO pAttrInfo,
        LPWSTR szPropertyName,
        LPBYTE lpValues,
        DWORD  dwNumValues,
        DWORD  dwSyntaxId
        );

    HRESULT
    CPropertyCache::
    SampleDSMarshallProperties(
       HANDLE hOperationData
    );



protected:

    DWORD _dwMaxProperties;


    PPROPERTY _pProperties;
    DWORD   _cb;

    CCoreADsObject FAR * _pCoreADsObject;
};

#endif






















































