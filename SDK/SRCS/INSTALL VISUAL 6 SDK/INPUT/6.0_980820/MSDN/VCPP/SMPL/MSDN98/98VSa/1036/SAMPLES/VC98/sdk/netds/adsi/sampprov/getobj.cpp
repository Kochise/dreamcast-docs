/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    GetObj.cpp

Abstract:

    Sample Provider GetObject functionality

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

//+---------------------------------------------------------------------------
//  Function:   RelativeGetObject
//
//  Synopsis:   Gets object relative to given OLE DS path.
//
//  Arguments:  [BSTR ADsPath]
//              [BSTR ClassName]
//              [BSTR RelativeName]
//              [IUnknown** ppObject]
//              [BOOT bNamespaceRelative]
//
//  Returns:    HRESULT
//
//  Modifies:   *ppObject
//
//----------------------------------------------------------------------------
HRESULT
RelativeGetObject(
    BSTR ADsPath,
    BSTR ClassName,
    BSTR RelativeName,
    IDispatch* FAR* ppObject,
    BOOL bNamespaceRelative
    )
{
    WCHAR szBuffer[MAX_PATH];
    HRESULT hr = S_OK;

    *ppObject = NULL;

    if (!RelativeName || !*RelativeName) {
        RRETURN(E_ADS_UNKNOWN_OBJECT);
    }

    wcscpy(szBuffer, ADsPath);

    if (bNamespaceRelative)
        wcscat(szBuffer, L"//");
    else
        wcscat(szBuffer, L"/");
    wcscat(szBuffer, RelativeName);

    if (ClassName && *ClassName) {
        wcscat(szBuffer,L",");
        wcscat(szBuffer, ClassName);
    }

    hr = ::GetObject(
                szBuffer,
                (LPVOID *)ppObject
                );
    BAIL_ON_FAILURE(hr);

error:
    RRETURN(hr);
}

//+---------------------------------------------------------------------------
//  Function:  GetObject
//
//  Synopsis:  Called by ResolvePathName to return an object
//
//  Arguments:  [LPWSTR szBuffer]
//              [LPVOID *ppObject]
//
//  Returns:    HRESULT
//

//----------------------------------------------------------------------------
HRESULT
GetObject(
    LPWSTR szBuffer,
    LPVOID * ppObject
    )
{
    HRESULT hr;
    DWORD dwStatus = NO_ERROR;
    DWORD dwNumberEntries = 0;
    DWORD dwModificationTime = 0;
    WCHAR szObjectClassName[MAX_PATH];
    WCHAR szDSPath[MAX_PATH];
    WCHAR szParent[MAX_PATH];
    WCHAR szCommonName[MAX_PATH];
    HANDLE hObject = NULL;

    OBJECTINFO ObjectInfo;
    POBJECTINFO pObjectInfo = &ObjectInfo;
    CLexer Lexer(szBuffer);

    IADs * pADs = NULL;
    szObjectClassName[0]=L'\0';

    memset(pObjectInfo, 0, sizeof(OBJECTINFO));
    hr = ADsObject(&Lexer, pObjectInfo);
    BAIL_ON_FAILURE(hr);

    //
    // Validate that this ADs pathname is to be processed by
    // us - as in the provider name is @Sample!
    //

    hr = ValidateProvider(pObjectInfo);
    BAIL_ON_FAILURE(hr);



    hr = ValidateObjectType(pObjectInfo);

    switch (pObjectInfo->ObjectType) {

    case TOKEN_NAMESPACE:
        //
        // This means that this is a namespace object;
        // instantiate the namespace object
        //

        hr = GetNamespaceObject(
                pObjectInfo,
                ppObject
                );
        BAIL_ON_FAILURE(hr);

        break;

    case TOKEN_SCHEMA:

        hr = GetSchemaObject(
                pObjectInfo,
                ppObject
                );
        BAIL_ON_FAILURE(hr);

        break;
    
    default:
        hr = BuildDSPathFromADsPath(
                    szBuffer,
                    szDSPath
                    );
        BAIL_ON_FAILURE(hr);

        hr  = SampleDSOpenObject(
                        szDSPath,
                        &hObject,
                        szObjectClassName,
                        REG_DS);
        BAIL_ON_FAILURE(hr);

        hr = BuildADsParentPath(
                    szBuffer,
                    szParent,
                    szCommonName
                    );
        BAIL_ON_FAILURE(hr);

        hr = CSampleDSGenObject::CreateGenericObject(
                        szParent,
                        szCommonName,
                        szObjectClassName,
                        ADS_OBJECT_BOUND,
                        IID_IUnknown,
                        (void**)ppObject
                        );
        BAIL_ON_FAILURE(hr);
        break;

    }

error:

    if (pADs) {
        pADs->Release();
    }
    if (hObject) {
        SampleDSCloseObject(hObject);
    }

    RRETURN(hr);
}



HRESULT
BuildADsPathFromDSPath(
    LPWSTR szDSRootRDN,
    LPWSTR szDSDNName,
    LPWSTR szADsPathName
    )
{
    PKEYDATA pKeyData = NULL;
    DWORD dwCount = 0;
    DWORD i = 0;

    if (!szDSRootRDN || !szDSDNName) {
        RRETURN(E_FAIL);
    }

    wsprintf(szADsPathName,L"%s:%s", g_szProviderName, szDSRootRDN);

    pKeyData = CreateTokenList(
                    szDSDNName,
                    L'.'
                    );

    if (pKeyData) {

        dwCount = pKeyData->cTokens;
        for (i = 0; i < dwCount; i++) {
            wcscat(szADsPathName, L"/");
            wcscat(szADsPathName, pKeyData->pTokens[dwCount - 1 - i]);
        }
    }

    if (pKeyData) {
        FreeProvMem(pKeyData);
    }
    RRETURN(S_OK);
}

HRESULT
BuildDSTreeNameFromADsPath(
    LPWSTR szBuffer,
    LPWSTR szSampleDSTreeName
    )
{
    OBJECTINFO ObjectInfo;
    POBJECTINFO pObjectInfo = &ObjectInfo;
    CLexer Lexer(szBuffer);
    DWORD dwNumComponents = 0;
    HRESULT hr;

    memset(pObjectInfo, 0, sizeof(OBJECTINFO));
    hr = ADsObject(&Lexer, pObjectInfo);
    BAIL_ON_FAILURE(hr);

    dwNumComponents = pObjectInfo->NumComponents;


    if (!dwNumComponents && !pObjectInfo->RootRDN) {
        //
        // There are no CNs in this pathname and
        // no tree name specified. This is the
        // namespace object - its parent is the
        // @ADs! object
        //

        hr = E_FAIL;

    } else if (!dwNumComponents && pObjectInfo->RootRDN) {
        //
        // There are no CNs in this pathname and a tree
        // name has been specified. This is the root
        // object - its parent is the  @SampleDS! object

        wsprintf(szSampleDSTreeName,L"\\\\%s", pObjectInfo->RootRDN);


        hr = S_OK;

    }else {
        //
        // There are one or more CNs, a tree name has been
        // specified. In the worst case the parent is the
        // root object. In the best case a long CN.
        //

        wsprintf(szSampleDSTreeName,L"\\\\%s", pObjectInfo->RootRDN);

        hr = S_OK;
    }

error:
    RRETURN(hr);

}

HRESULT
BuildDSPathFromADsPath(
    LPWSTR szADsPathName,
    LPWSTR szDSPathName
    )
{
    OBJECTINFO ObjectInfo;
    POBJECTINFO pObjectInfo = &ObjectInfo;
    CLexer Lexer(szADsPathName);
    DWORD i = 0;
    DWORD dwNumComponents = 0;
    HRESULT hr;

    memset(pObjectInfo, 0, sizeof(OBJECTINFO));
    hr = ADsObject(&Lexer, pObjectInfo);
    BAIL_ON_FAILURE(hr);

    dwNumComponents = pObjectInfo->NumComponents;

    wcscpy(szDSPathName, L"\\");
    wcscat(szDSPathName, pObjectInfo->RootRDN);
    
    for (i = 0; i < dwNumComponents; i++) {
        wcscat(szDSPathName, L"\\");
                wcscat(szDSPathName, pObjectInfo->ComponentArray[i].szComponent);
    }

error:

    RRETURN(hr);

}

HRESULT
AppendComponent(
   LPWSTR szDSPathName,
   PCOMPONENT pComponent
){
        DebugBreak();
    RRETURN(S_OK);
}



HRESULT
BuildADsParentPath(
    LPWSTR szBuffer,
    LPWSTR szParent,
    LPWSTR szCommonName
    )
{
    OBJECTINFO ObjectInfo;
    POBJECTINFO pObjectInfo = &ObjectInfo;
    CLexer Lexer(szBuffer);
    DWORD i = 0;
    DWORD dwNumComponents = 0;
    HRESULT hr;
    LPWSTR pszComponent = NULL, pszValue = NULL;

    memset(pObjectInfo, 0, sizeof(OBJECTINFO));
    hr = ADsObject(&Lexer, pObjectInfo);
    BAIL_ON_FAILURE(hr);

    dwNumComponents = pObjectInfo->NumComponents;


    if (!dwNumComponents && !pObjectInfo->RootRDN) {
        //
        // There are no CNs in this pathname and
        // no Root name specified. This is the
        // namespace object - its parent is the
        // @ADs! object
        //

        wsprintf(szParent,L"ADs:");

        RRETURN(S_OK);

    } else if (!dwNumComponents && pObjectInfo->RootRDN) {
        //
        // There are no CNs in this pathname and a Root
        // name has been specified. This is the root
        // object - its parent is the  @Sample! object

        wsprintf(szParent, L"%s:", pObjectInfo->ProviderName);

        //
        // And the common name is the RootRDN
        //

        wsprintf(szCommonName,L"%s", pObjectInfo->RootRDN);


        RRETURN(S_OK);


    }else {
        //
        // There are one or more CNs, a Root name has been
        // specified. In the worst case the parent is the
        // root object. In the best case a long CN.
        //

        wsprintf(
            szParent, L"%s://%s",
            pObjectInfo->ProviderName,
            pObjectInfo->RootRDN
            );

        for (i = 0; i < dwNumComponents - 1; i++) {

            wcscat(szParent, L"/");


            pszComponent =  pObjectInfo->ComponentArray[i].szComponent;
            pszValue = pObjectInfo->ComponentArray[i].szValue;


            if (pszComponent && pszValue) {

                wcscat(
                    szParent,
                    pObjectInfo->ComponentArray[i].szComponent
                    );
                wcscat(szParent,L"=");
                wcscat(
                    szParent,
                    pObjectInfo->ComponentArray[i].szValue
                    );
            }else if (pszComponent){

                wcscat(
                    szParent,
                    pObjectInfo->ComponentArray[i].szComponent
                    );

            }else {
                //
                // Error - we should never hit this case!!
                //

            }
        }

        //
        // And the common name is the last component
        //

        pszComponent =  pObjectInfo->ComponentArray[dwNumComponents - 1].szComponent;
        pszValue = pObjectInfo->ComponentArray[dwNumComponents - 1].szValue;


        if (pszComponent && pszValue) {

            wsprintf(szCommonName, L"%s=%s",pszComponent, pszValue);

        }else if (pszComponent){

            wsprintf(szCommonName, L"%s", pszComponent);

        }else {
            //
            // Error - we should never hit this case!!
            //

        }

    }

error:

    RRETURN(hr);

}

HRESULT
InstantiateDerivedObject(
    IADs FAR * pADs,
    REFIID riid,
    void  ** ppObject
    )
{
        *ppObject = 0;

    RRETURN(S_OK);
}


//+---------------------------------------------------------------------------
// Function:    GetNamespaceObject
//
// Synopsis:    called by GetObject
//
// Arguments:   [POBJECTINFO pObjectInfo]
//              [LPVOID * ppObject]
//
// Returns:     HRESULT
//
//----------------------------------------------------------------------------
HRESULT
GetNamespaceObject(
    POBJECTINFO pObjectInfo,
    LPVOID * ppObject
    )
{
    HRESULT hr;

    hr = ValidateNamespaceObject(
                pObjectInfo
                );
    BAIL_ON_FAILURE(hr);

    hr = CoCreateInstance(CLSID_SampleDSNamespace,
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          IID_IUnknown,
                          (void **)ppObject
                          );

error:

    RRETURN(hr);
}

HRESULT
ValidateNamespaceObject(
    POBJECTINFO pObjectInfo
    )
{

    if (!_wcsicmp(pObjectInfo->ProviderName, g_szProviderName)) {
    }
    RRETURN(S_OK);
}


HRESULT
ValidateProvider(
    POBJECTINFO pObjectInfo
    )
{

    //
    // The provider name is case-sensitive.  This is a restriction that OLE
    // has put on us.
    //
    if (!(wcscmp(pObjectInfo->ProviderName, g_szProviderName))) {
        RRETURN(S_OK);
    }
    RRETURN(E_FAIL);
}



//+---------------------------------------------------------------------------
// Function:    GetSchemaObject
//
// Synopsis:    called by GetObject
//
// Arguments:   [POBJECTINFO pObjectInfo]
//              [LPVOID * ppObject]
//
// Returns:     HRESULT
//
// Modifies:      -
//
//----------------------------------------------------------------------------
HRESULT
GetSchemaObject(
    POBJECTINFO pObjectInfo,
    LPVOID * ppObject
    )
{
    HRESULT hr = S_OK;
    WCHAR szParent[MAX_PATH];
    WCHAR szCommonName[MAX_PATH];
    WCHAR szSampleDSPathName[MAX_PATH];
    DWORD dwObjectType = 0;
    HANDLE hObject= NULL;

    hr = ValidateSchemaObject(
                pObjectInfo,
                &dwObjectType
                );
    BAIL_ON_FAILURE(hr);

    hr = BuildADsParentPath(
             pObjectInfo,
             szParent,
             szCommonName
             );
    BAIL_ON_FAILURE(hr);

    switch(dwObjectType) {
    case SampleDS_CLASS_ID:
    case SampleDS_PROPERTY_ID:
    case SampleDS_CLASSPROP_ID:

        wcscpy(szSampleDSPathName, L"\\");
        wcscat(szSampleDSPathName, szCommonName);
        hr = SampleDSOpenObject(
                        szSampleDSPathName,
                        &hObject,
                        NULL,
                        REG_SCHEMA
                        );
        BAIL_ON_FAILURE(hr);
        
        break;

    default:
        break;
    }

    //
    // Note: The "error:" tag is at the end of the switch statement,
    //       so we can simply break out.
    //

    switch (dwObjectType) {
    case SampleDS_SCHEMA_ID:
        hr = CSampleDSSchema::CreateSchema(
                    szParent,
                    szCommonName,
                    ADS_OBJECT_BOUND,
                    IID_IUnknown,
                    ppObject
                    );
        break;
    case SampleDS_CLASSPROP_ID:
        hr = CSampleDSClass::CreateClass(
                    szParent,
                    szCommonName,
                    hObject,
                    ADS_OBJECT_BOUND,
                    IID_IUnknown,
                    ppObject
                    );
        if (FAILED(hr)) {
            hr = CSampleDSProperty::CreateProperty(
                                    szParent,
                                    szCommonName,
                                    hObject,
                                    ADS_OBJECT_BOUND,
                                    IID_IUnknown,
                                    ppObject
                                    );
        }
        break;

   default:
        hr = E_ADS_UNKNOWN_OBJECT;
        break;
    }

error:
    if (hObject) {
        SampleDSCloseObject(hObject);
    }
    RRETURN(hr);
}

HRESULT
ValidateSchemaObject(
    POBJECTINFO pObjectInfo,
    PDWORD pdwObjectType
    )
{
    DWORD dwNumComponents = 0;

    dwNumComponents = pObjectInfo->NumComponents;

    switch (dwNumComponents) {

    case 1:
        if (!_wcsicmp(pObjectInfo->ComponentArray[0].szComponent, L"schema")) {
            *pdwObjectType = SampleDS_SCHEMA_ID;
            RRETURN(S_OK);
        }
        break;

    case 2:
        *pdwObjectType = SampleDS_CLASSPROP_ID;
        RRETURN(S_OK);
    
    default:
        break;


    }

    RRETURN(E_FAIL);
}

HRESULT
BuildADsParentPath(
    POBJECTINFO pObjectInfo,
    LPWSTR szParent,
    LPWSTR szCommonName
    )
{
    DWORD i = 0;
    DWORD dwNumComponents = 0;
    LPWSTR pszComponent = NULL, pszValue = NULL;

    dwNumComponents = pObjectInfo->NumComponents;

    if (!dwNumComponents && !pObjectInfo->RootRDN) {
        //
        // There are no CNs in this pathname and
        // no root name specified. This is the
        // namespace object - its parent is the
        // @ADs! object
        //

        wsprintf(szParent,L"ADs:");

        RRETURN(S_OK);

    } else if (!dwNumComponents && pObjectInfo->RootRDN) {
        //
        // There are no CNs in this pathname and a root
        // name has been specified. This is the root
        // object - its parent is the  @Sample! object

        wsprintf(szParent, L"%s:", pObjectInfo->ProviderName);

        //
        // And the common name is the RootRDN. Remember the
        // "//" will be added on  when we reconstruct the full
        // pathname
        //

        wsprintf(szCommonName,L"%s", pObjectInfo->RootRDN);


        RRETURN(S_OK);


    }else {
        //
        // There are one or more CNs, a root name has been
        // specified. In the worst case the parent is the
        // root object. In the best case a long CN.
        //

        wsprintf(
            szParent, L"%s://%s",
            pObjectInfo->ProviderName,
            pObjectInfo->RootRDN
            );

        for (i = 0; i < dwNumComponents - 1; i++) {

            wcscat(szParent, L"/");


            pszComponent =  pObjectInfo->ComponentArray[i].szComponent;
            pszValue = pObjectInfo->ComponentArray[i].szValue;


            if (pszComponent && pszValue) {

                wcscat(
                    szParent,
                    pObjectInfo->ComponentArray[i].szComponent
                    );
                wcscat(szParent,L"=");
                wcscat(
                    szParent,
                    pObjectInfo->ComponentArray[i].szValue
                    );
            }else if (pszComponent){

                wcscat(
                    szParent,
                    pObjectInfo->ComponentArray[i].szComponent
                    );

            }else {
                //
                // Error - we should never hit this case!!
                //

            }
        }

        //
        // And the common name is the last component
        //

        pszComponent =  pObjectInfo->ComponentArray[dwNumComponents - 1].szComponent;
        pszValue = pObjectInfo->ComponentArray[dwNumComponents - 1].szValue;


        if (pszComponent && pszValue) {

            wsprintf(szCommonName, L"%s=%s",pszComponent, pszValue);

        }else if (pszComponent){

            wsprintf(szCommonName, L"%s", pszComponent);

        }else {
            //
            // Error - we should never hit this case!!
            //

        }

    }

    RRETURN(S_OK);
}

HRESULT
ValidateObjectType(
    POBJECTINFO pObjectInfo
    )
{

    pObjectInfo->ObjectType = TOKEN_DSOBJECT;

    if (pObjectInfo->ProviderName && !pObjectInfo->RootRDN
            && !pObjectInfo->NumComponents) {
        pObjectInfo->ObjectType = TOKEN_NAMESPACE;
    }else if (pObjectInfo->ProviderName && pObjectInfo->RootRDN
                && pObjectInfo->NumComponents) {

        if (!_wcsicmp(pObjectInfo->ComponentArray[0].szComponent,L"schema")) {
            pObjectInfo->ObjectType = TOKEN_SCHEMA;
        }

    }

    RRETURN(S_OK);
}

HRESULT
BuildSampleDSRootRDNFromADsPath(
    LPWSTR szBuffer,
    LPWSTR szDSRootRDN
    )
{
    OBJECTINFO ObjectInfo;
    POBJECTINFO pObjectInfo = &ObjectInfo;
    CLexer Lexer(szBuffer);
    DWORD dwNumComponents = 0;
    HRESULT hr;

    memset(pObjectInfo, 0, sizeof(OBJECTINFO));
    hr = ADsObject(&Lexer, pObjectInfo);
    BAIL_ON_FAILURE(hr);

    dwNumComponents = pObjectInfo->NumComponents;


    if (!dwNumComponents && !pObjectInfo->RootRDN) {
        //
        // There are no CNs in this pathname and
        // no root name specified. This is the
        // namespace object - its parent is the
        // @ADs! object
        //

        hr = E_FAIL;

    } else if (!dwNumComponents && pObjectInfo->RootRDN) {
        //
        // There are no CNs in this pathname and a root 
        // name has been specified. This is the root
        // object - its parent is the  @Sample! object

        wsprintf(szDSRootRDN,L"\\\\%s", pObjectInfo->RootRDN);


        hr = S_OK;

    }else {
        //
        // There are one or more CNs, a root name has been
        // specified. In the worst case the parent is the
        // root object. In the best case a long CN.
        //

        wsprintf(szDSRootRDN,L"\\\\%s", pObjectInfo->RootRDN);

        hr = S_OK;
    }

error:
    RRETURN(hr);

}


HRESULT
BuildDSPathFromADsPath(
    LPWSTR szADsPathName,
    LPWSTR szDSRootRDN,
    LPWSTR szDSPathName
    )
{
    OBJECTINFO ObjectInfo;
    POBJECTINFO pObjectInfo = &ObjectInfo;
    CLexer Lexer(szADsPathName);
    DWORD i = 0;
    DWORD dwNumComponents = 0;
    HRESULT hr;

    memset(pObjectInfo, 0, sizeof(OBJECTINFO));
    hr = ADsObject(&Lexer, pObjectInfo);
    BAIL_ON_FAILURE(hr);

    dwNumComponents = pObjectInfo->NumComponents;

    wcscpy(szDSRootRDN, L"\\");
    wcscat(szDSRootRDN, pObjectInfo->RootRDN);

    *szDSPathName = L'\0';

    for (i = dwNumComponents; i >  0; i--) {
                wcscat(szDSPathName, pObjectInfo->ComponentArray[i-1].szComponent);
        if (i>1) wcscat(szDSPathName, L"\\");
    }

error:

    RRETURN(hr);
}
