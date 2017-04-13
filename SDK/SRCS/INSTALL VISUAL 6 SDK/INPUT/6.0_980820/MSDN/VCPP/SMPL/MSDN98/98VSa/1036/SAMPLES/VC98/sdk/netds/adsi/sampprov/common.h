/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    Common.h

Abstract:

   Contains Sample Provider routines and properties that are common to
   all objects.  Objects get the routines and properties through C++ 
   inheritance.

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _COMMON_H_
#define _COMMON_H_

#define MAX_DWORD 0xFFFFFFFF
#define SCHEMA_NAME L"Schema"  //Name of Schema object off of RootObject

HRESULT xx_put_BSTR(
    BSTR* lppItemName,
    BSTR lpName
    );

HRESULT xx_put_LONG(
    long *plnItem,
    long Item
    );

HRESULT
xx_put_DATE(
    DATE * pdaItem,
    DATE daItem
    );

HRESULT
xx_put_VARIANT_BOOL(
    VARIANT_BOOL * pfItem,
    VARIANT_BOOL fItem
    );

HRESULT
xx_put_VARIANT(
    VARIANT * * pvItem,
    VARIANT vItem
    );

HRESULT
LoadTypeInfoEntry(
    CDispatchMgr * pDispMgr,
    REFIID libid,
    REFIID iid,
    void * pIntf,
    DISPID SpecialId
    );


HRESULT
MakeUncName(
    LPWSTR szSrcBuffer,
    LPWSTR szTargBuffer
    );

HRESULT
ValidateOutParameter(
    BSTR * retval
    );

HRESULT
BuildADsPath(
    BSTR Parent,
    BSTR Name,
    BSTR *pADsPath
    );

HRESULT
BuildSchemaPath(
    BSTR bstrADsPath,
    BSTR bstrClass,
    BSTR *pSchemaPath
    );

HRESULT
BuildADsGuid(
    REFCLSID clsid,
    BSTR *pADsClass
    );


//
// Accessing Well-known object types
//
//RHA  will have to do filters as whatever user passes in
typedef struct _filters {
    WCHAR szObjectName[MAX_PATH];
    DWORD dwFilterId;
} FILTERS, *PFILTERS;


extern PFILTERS  gpFilters;
extern DWORD gdwMaxFilters;


HRESULT
BuildADsPathFromDSPath(
    LPWSTR szDSRootRDN,
    LPWSTR szDSDNName,
    LPWSTR szADsPathName
    );

HRESULT
BuildDSPathFromADsPath(
    LPWSTR szADsPathName,
    LPWSTR szDSPathName
    );

HRESULT
BuildDSParentPathFromDSPath(
    LPWSTR szDSPathName,
    LPWSTR szDSParentPathName,
    LPWSTR szCommonName
    );

HRESULT
BuildDSPathFromDSParentPath(
    LPWSTR szDSParentPathName,
    LPWSTR szDSObjectCommonName,
    LPWSTR szDSPathName
    );


typedef struct _KEYDATA {
    DWORD   cTokens;
    LPWSTR  pTokens[1];
} KEYDATA, *PKEYDATA;


PKEYDATA
CreateTokenList(
    LPWSTR   pKeyData,
    WCHAR ch
    );

HRESULT LoadTypeInfo(CLSID clsidTL, CLSID clsidTI, LPTYPEINFO *ppTI);

#endif

