/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    Common.cpp

Abstract:

    Contains routines and properties that are common to
    all tshirt objects. thsirt objects get the routines and
    properties through C++ inheritance.

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop


FILTERS Filters[] = {
                    {L"organizational unit", SampleDS_OU_ID},
                    {L"class", SampleDS_CLASS_ID},
                    {L"property", SampleDS_PROPERTY_ID}
                  };

#define MAX_FILTERS  (sizeof(Filters)/sizeof(FILTERS))

PFILTERS  gpFilters = Filters;
DWORD gdwMaxFilters = MAX_FILTERS;

extern WCHAR * g_szProviderName;

HRESULT
xx_put_BSTR(BSTR* lppItemName, BSTR lpName)
{
    if (*lppItemName) {
        SysFreeString(*lppItemName);
        *lppItemName = NULL;
    }

    if (!lpName) {
        RRETURN(S_OK);
    }

    *lppItemName = SysAllocString(lpName);

    if (!*lppItemName) {
        RRETURN(E_FAIL);
    }
    RRETURN(S_OK);
}

HRESULT
xx_put_LONG(long * plnItem, long lnItem)
{
    *plnItem = lnItem;
    RRETURN(S_OK);
}

HRESULT
xx_put_DATE(DATE * pdaItem, DATE daItem)
{
    *pdaItem = daItem;
    RRETURN(S_OK);
}


HRESULT
xx_put_VARIANT_BOOL(VARIANT_BOOL * pfItem, VARIANT_BOOL fItem)
{
    *pfItem = fItem;
    RRETURN(S_OK);
}


HRESULT
xx_put_VARIANT(VARIANT * * ppvItem, VARIANT vItem)
{
    if (!*ppvItem) {
        if (!(*ppvItem = (VARIANT *)AllocProvMem(sizeof(VARIANT)))){
            RRETURN(E_OUTOFMEMORY);
        }
    }
    RRETURN(VariantCopy(*ppvItem, &vItem));
}

HRESULT
BuildADsPath(
    BSTR Parent,
    BSTR Name,
    BSTR *pADsPath
    )
{
    WCHAR ADsPath[MAX_PATH];
    WCHAR ProviderName[MAX_PATH];
    HRESULT hr = S_OK;

    //
    // We will assert if bad parameters are passed to us.
    // This is because this should never be the case. This
    // is an internal call
    //

    ADsAssert(Parent && Name);
    ADsAssert(pADsPath);


    //
    // Special case the Namespace object; if
    // the parent is L"ADs:", then Name = ADsPath
    //

    if (!_wcsicmp(Parent, L"ADs:")) {
        RRETURN(xx_put_BSTR(pADsPath, Name));
    }

    //
    // The rest of the cases we expect valid data,
    // Path, Parent and Name are read-only, the end-user
    // cannot modify this data
    //

    //
    // For first level objects we do not add
    // the first backslash; so we examine that the parent is
    // L"Sample:" and skip the slash otherwise we start with
    // the slash
    //

    wsprintf(ProviderName, L"%s:", g_szProviderName);

    wcscpy(ADsPath, Parent);

    if (_wcsicmp(ADsPath, ProviderName)) {
        wcscat(ADsPath, L"/");
    }else {
        wcscat(ADsPath, L"//");
    }
    wcscat(ADsPath, Name);

    hr = xx_put_BSTR(pADsPath, ADsPath);

    RRETURN(hr);
}

HRESULT
BuildSchemaPath(
    BSTR bstrADsPath,
    BSTR bstrClass,
    BSTR *pSchemaPath
    )
{
    WCHAR ADsSchema[MAX_PATH];
    OBJECTINFO ObjectInfo;
    POBJECTINFO pObjectInfo = &ObjectInfo;
    CLexer Lexer(bstrADsPath);
    HRESULT hr = S_OK;

    wcscpy(ADsSchema, L"");

    if (bstrClass && *bstrClass) {
        memset(pObjectInfo, 0, sizeof(OBJECTINFO));
        hr = ADsObject(&Lexer, pObjectInfo);
        BAIL_ON_FAILURE(hr);

        if (pObjectInfo->RootRDN) {

            wsprintf(ADsSchema,L"%s://",pObjectInfo->ProviderName);
            wcscat(ADsSchema, pObjectInfo->RootRDN);
            wcscat(ADsSchema,L"/schema/");
            wcscat(ADsSchema, bstrClass);

        }
    }

    hr = ProvAllocString( ADsSchema, pSchemaPath);

error:

    if (pObjectInfo) {

        //
        // BugBug - KrishnaG; free up this piece of memory
        //
    }
    RRETURN(hr);
}


HRESULT
BuildADsGuid(
    REFCLSID clsid,
    BSTR *pADsClass
){
    WCHAR ADsClass[MAX_PATH];

    StringFromGUID2(clsid, ADsClass, 256);

    RRETURN(xx_put_BSTR(pADsClass, ADsClass));
}


typedef struct _typeinfotable
{
    GUID iid;
    ITypeInfo * pTypeInfo;
    struct _typeinfotable *pNext;
}TYPEINFO_TABLE, *PTYPEINFO_TABLE;


PTYPEINFO_TABLE gpTypeInfoTable = NULL;

ITypeInfo *
FindTypeInfo(
    PTYPEINFO_TABLE pTypeInfoTable,
    REFIID iid
){
    PTYPEINFO_TABLE pTemp = NULL;

    pTemp = pTypeInfoTable;

    while (pTemp) {
        if (IsEqualIID(iid, pTemp->iid)) {
            return(pTemp->pTypeInfo);
        }
        pTemp = pTemp->pNext;
    }
    return(NULL);
}


PTYPEINFO_TABLE
AddTypeInfo(
    PTYPEINFO_TABLE pTypeInfoTable,
    REFIID iid,
    ITypeInfo * pTypeInfo
){
    PTYPEINFO_TABLE pTemp = NULL;

    pTemp = (PTYPEINFO_TABLE)AllocProvMem(
                    sizeof(TYPEINFO_TABLE)
                    );
    if (!pTemp) {
        return(NULL);
    }

    memcpy(&pTemp->iid, &iid, sizeof(GUID));
    pTemp->pTypeInfo = pTypeInfo;
    pTemp->pNext = pTypeInfoTable;

    return(pTemp);
}

HRESULT
LoadTypeInfoEntry(
    CDispatchMgr *pDispMgr,
    REFIID libid,
    REFIID iid,
    void * pIntf,
    DISPID SpecialId
){
    ITypeInfo * pTypeInfo = NULL;
    HRESULT hr;

    pTypeInfo = FindTypeInfo(
                    gpTypeInfoTable,
                    iid
                    );
    if (!pTypeInfo) {

        hr = LoadTypeInfo(libid, iid, &pTypeInfo);
        BAIL_IF_ERROR(hr);

        gpTypeInfoTable = AddTypeInfo(
                                gpTypeInfoTable,
                                iid,
                                pTypeInfo
                                );
        if (!gpTypeInfoTable) {
            hr = HRESULT_FROM_WIN32(GetLastError());
            BAIL_IF_ERROR(hr);
        }
    }
    pTypeInfo->AddRef();


    hr = pDispMgr->AddTypeInfo(pTypeInfo, pIntf);
    BAIL_IF_ERROR(hr);

    if (SpecialId == -4) {
        hr = pDispMgr->MarkAsNewEnum(pTypeInfo);
    }

    RRETURN(S_OK);

cleanup:

   if (pTypeInfo) {
       pTypeInfo->Release();
   }
    RRETURN(hr);
}

HRESULT
ValidateOutParameter(BSTR * retval)
{
    if (!retval) {
        RRETURN(E_ADS_BAD_PARAMETER);
    }
    RRETURN(S_OK);
}


PKEYDATA
CreateTokenList(
    LPWSTR   pKeyData,
    WCHAR ch
){
    DWORD       cTokens;
    DWORD       cb;
    PKEYDATA    pResult;
    LPWSTR       pDest;
    LPWSTR       psz = pKeyData;
    LPWSTR      *ppToken;
    WCHAR szTokenList[MAX_PATH];


    if (!psz || !*psz)
        return NULL;

    wsprintf(szTokenList, L"%c", ch);

    cTokens=1;

    // Scan through the string looking for commas,
    // ensuring that each is followed by a non-NULL character:

    while ((psz = wcschr(psz, ch)) && psz[1]) {

        cTokens++;
        psz++;
    }

    cb = sizeof(KEYDATA) + (cTokens-1) * sizeof(LPWSTR) +
         wcslen(pKeyData)*sizeof(WCHAR) + sizeof(WCHAR);

    if (!(pResult = (PKEYDATA)AllocProvMem(cb)))
        return NULL;

    // Initialise pDest to point beyond the token pointers:

    pDest = (LPWSTR)((LPBYTE)pResult + sizeof(KEYDATA) +
                                      (cTokens-1) * sizeof(LPWSTR));

    // Then copy the key data buffer there:

    wcscpy(pDest, pKeyData);

    ppToken = pResult->pTokens;


    // Remember, wcstok has the side effect of replacing the delimiter
    // by NULL, which is precisely what we want:

    psz = wcstok (pDest, szTokenList);

    while (psz) {

        *ppToken++ = psz;
        psz = wcstok (NULL, szTokenList);
    }

    pResult->cTokens = cTokens;

    return( pResult );
}

//+------------------------------------------------------------------------
//
//  Function:   LoadTypeInfo
//
//  Synopsis:   Loads a typeinfo from a registered typelib.
//
//  Arguments:  [clsidTL] --  TypeLib GUID
//              [clsidTI] --  TypeInfo GUID
//              [ppTI]    --  Resulting typeInfo
//
//  Returns:    HRESULT
//
//-------------------------------------------------------------------------

HRESULT
LoadTypeInfo(CLSID clsidTL, CLSID clsidTI, LPTYPEINFO *ppTI)
{
    HRESULT     hr;
    ITypeLib *  pTL;

    ADsAssert(ppTI);
    *ppTI = NULL;
    hr = LoadRegTypeLib(clsidTL, 1, 0, LOCALE_SYSTEM_DEFAULT, &pTL);
    if (hr)
        RRETURN(hr);

    hr = pTL->GetTypeInfoOfGuid(clsidTI, ppTI);
    pTL->Release();
    RRETURN(hr);
}

