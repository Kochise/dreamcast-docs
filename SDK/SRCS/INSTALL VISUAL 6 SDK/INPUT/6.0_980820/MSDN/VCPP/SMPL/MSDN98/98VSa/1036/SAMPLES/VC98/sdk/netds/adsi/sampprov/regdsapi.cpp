/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    RegDSAPI.cpp

Abstract:

    Sample Provider Registry DS APIs
    
Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop
#include "string.h"

#define SAMPLEDS_REGDSPATH       L"SOFTWARE\\Microsoft\\ADs\\SampleDS\\DS"
#define SAMPLEDS_REGSCHEMAPATH   L"SOFTWARE\\Microsoft\\ADs\\SampleDS\\Schema"
#define SAMPLEDS_REG_TYPE        L"TYPE"
#define SAMPLEDS_REG_MANPROP     L"Mandatory Properties"
#define SAMPLEDS_REG_PROPERTY    L"PROPERTY"
#define SAMPLEDS_REG_CLASS       L"CLASS"
#define SAMPLEDS_REG_SYNTAX      L"Syntax"


/*++

Routine Description:

    Open an object in the DS. Class of the object is also returned
    in szClass if the parameter is not NULL.

Arguments:
    szClass will be used to store the object class if it is not NULL.
    szClass has to be a LPWSTR of length MAX_PATH.
    
Return Value:

--*/
HRESULT
SampleDSOpenObject( 
    LPWSTR szRegPath,             
    HANDLE *phKey,                
    LPWSTR szClass,
    DWORD  dwType
    )
{
    if (!szRegPath || 
        !phKey)
        RRETURN(E_FAIL);

    WCHAR szFullRegPath[MAX_PATH] = L"";
    
    switch (dwType) {
        case REG_DS:
            wcscpy(
               szFullRegPath,
               SAMPLEDS_REGDSPATH
               );
            break;
        case REG_SCHEMA:
            wcscpy(
               szFullRegPath,
               SAMPLEDS_REGSCHEMAPATH
               );
            break;
        default:
            RRETURN(E_FAIL);
    };

    if (*szRegPath != L'\0') 
            wcscat(szFullRegPath,
            szRegPath
            );
    
    if (RegOpenKeyEx( 
            HKEY_LOCAL_MACHINE, 
            szFullRegPath, 
            0, 
            KEY_ALL_ACCESS, 
            (PHKEY)phKey
            ) != ERROR_SUCCESS) {
        RRETURN(E_FAIL);
    }
    
    if (szClass){
        DWORD dwDataType;
        DWORD dwClass = MAX_PATH * sizeof(WCHAR);
        if (RegQueryValueEx(
                (HKEY)*phKey, 
                SAMPLEDS_REG_TYPE,
                NULL,
                &dwDataType,
                (BYTE*)szClass,    
                &dwClass
                ) != ERROR_SUCCESS) {
            goto Error;
        }
        if (dwDataType != REG_SZ) {
            goto Error;
        }
    }
    RRETURN(S_OK);
Error:
    RegCloseKey((HKEY)*phKey);
    RRETURN (E_FAIL);
}


/*++

Routine Description:

    Close an object in the DS
    
Arguments:

Return Value:

--*/
HRESULT
SampleDSCloseObject(
    HANDLE hKey
    )
{
    if (RegCloseKey((HKEY)hKey
                    ) != ERROR_SUCCESS) 
        RRETURN(E_FAIL);
    RRETURN(S_OK);
}


/*++

Routine Description:

    Setup the enumeration handle of the objects in the DS
    
Arguments:

Return Value:

--*/
HRESULT
SampleDSRDNEnum( 
    HANDLE *phEnum,
    HANDLE hContainerKey
    )
{
    if (!phEnum)
        RRETURN(E_FAIL);

    LPREGDS_ENUM lprdsenum = new REGDS_ENUM;
    if (lprdsenum == NULL) 
        RRETURN(E_OUTOFMEMORY);
    
    HANDLE hKey = hContainerKey;
    if (hKey == NULL) { 
        if ( SampleDSOpenObject(L"", 
                                &hKey, 
                                NULL,
                                REG_DS
                                ) != ERROR_SUCCESS) {
            goto Error;
        }
    }
    
    lprdsenum->dwIndex = 0;
    lprdsenum->hContainerKey= hKey;

    *((LPREGDS_ENUM *) phEnum) = lprdsenum;
        
    RRETURN(S_OK);
Error:
    delete lprdsenum;
    *phEnum = NULL;
    RRETURN(E_FAIL);
}


/*++

Routine Description:

    Get the next object in the DS using the enumeration handle created
    by SampleDSRDNRnum
    
Arguments:

Return Value:

--*/
HRESULT
SampleDSNextRDN( 
    HANDLE hEnum,      
    LPWSTR *pszName,  
    LPWSTR *pszClass
    )
{
    HRESULT hr = E_FAIL;
    DWORD dwName = MAX_PATH;
    LRESULT lResult;
    FILETIME ftLastWrite;

    if (!hEnum || !pszName)
        RRETURN(hr);

    *pszName = (LPWSTR) AllocProvMem(sizeof(WCHAR)*dwName);
    if (*pszName == NULL)  
        RRETURN(E_OUTOFMEMORY);
    
    lResult = RegEnumKeyEx(
                   (HKEY)LPREGDS_ENUM(hEnum)->hContainerKey,
                    LPREGDS_ENUM(hEnum)->dwIndex,
                    *pszName, 
                    &dwName,
                    0, 
                    NULL, 
                    NULL,
                    &ftLastWrite
                    ); 
    if (lResult != ERROR_SUCCESS) {
        if (lResult == ERROR_NO_MORE_ITEMS) 
            hr = S_FALSE;       // Not an error, no items left
        goto Error;
    } else {
        LPREGDS_ENUM(hEnum)->dwIndex++;
        if (pszClass != NULL) {
            DWORD dwClass = MAX_PATH;
            *pszClass = (LPWSTR) AllocProvMem(sizeof(WCHAR)*dwClass);
            if (*pszClass == NULL) {
                hr = E_OUTOFMEMORY;
                goto Error;
            }
            if (SampleDSGetTypeText(
                        (HKEY)LPREGDS_ENUM(hEnum)->hContainerKey,
                        *pszName,
                        *pszClass,
                        &dwClass
                        ) != S_OK) {
                goto Error;
            }
        } 
    }
    RRETURN(S_OK);

Error:
    if (*pszName) {
        FreeProvMem(*pszName);
        *pszName = NULL;
    }
    if (*pszClass) {
        FreeProvMem(*pszClass);
        *pszClass = NULL;
    }
    RRETURN(hr);
}

/*++

Routine Description:

    Free the enumeration handle
        
Arguments:

Return Value:

--*/
HRESULT
SampleDSFreeEnum(HANDLE hEnum)
{
    if (!hEnum)
        RRETURN(E_FAIL);

    LPREGDS_ENUM lprdsenum = (LPREGDS_ENUM)hEnum;
    if (lprdsenum->hContainerKey) {
        SampleDSCloseObject(lprdsenum->hContainerKey);
    }
    delete lprdsenum;
    RRETURN(S_OK);
}


/*++

Routine Description:

    Modify properties of an object in the DS
    
Arguments:

Return Value:

--*/
HRESULT
SampleDSModifyObject(HANDLE hKey,
                     HANDLE hOperationData
                     )
{
    if (!hKey)
        RRETURN(E_FAIL);
    
    if (!hOperationData)
        RRETURN(S_OK);

    LPSampleDS_ATTRS_INFO pAttrsInfo = (LPSampleDS_ATTRS_INFO)hOperationData;
    LPSampleDS_ATTR_INFO pInfo = pAttrsInfo->pAttrInfo;
    DWORD cAttrInfo = pAttrsInfo->dwAttr;
    
    BYTE* pbData;
    DWORD dwData;
    DWORD dwType;

    for (DWORD i = 0;i < cAttrInfo;i++) {
        switch (pInfo->dwSyntaxId) {
            case SampleDS_DATATYPE_1:
                {
                SampleDS_TYPE_1* pData = (SampleDS_TYPE_1*)pInfo->lpValue;
                pbData = (BYTE*)pData->DNString;
                dwData = (wcslen(pData->DNString) + 1) * sizeof(WCHAR);
                dwType = REG_SZ;
                break;
                }
            case SampleDS_DATATYPE_2:
                {
                SampleDS_TYPE_2* pData = (SampleDS_TYPE_2*)pInfo->lpValue;
                pbData = (BYTE*)&(pData->Integer);
                dwData = sizeof(DWORD);
                dwType = REG_DWORD;
                break;
                }
            default:
                RRETURN(E_FAIL);
        }
        if (RegSetValueEx(
                    (HKEY)hKey,         
                    pInfo->lpAttributeName,    
                    NULL,
                    dwType,    
                    pbData,
                    dwData
                    ) != ERROR_SUCCESS)
            RRETURN(E_FAIL);
        pInfo++;
    }
    
    RRETURN(NO_ERROR);
}



/*++

Routine Description:

    Read the properties of an object in the DS
    
Arguments:

Return Value:

--*/
HRESULT
SampleDSReadObject(
    HANDLE hkey,              
    HANDLE *phOperationData
    )
{
    DWORD cValues;               
    LPSampleDS_ATTR_INFO pInfo = NULL;
    DWORD i; 
    LPWSTR pszValue = NULL;
    BYTE*  pbData = NULL;
    DWORD cProp = 0;

    if (RegQueryInfoKey(
                (HKEY)hkey,         
                NULL,
                NULL,
                NULL,                     
                NULL,
                NULL,
                NULL,
                &cValues,                 
                NULL,
                NULL,
                NULL,
                NULL
                ) != ERROR_SUCCESS) {
        RRETURN(E_FAIL);
    };
 
    if (cValues == 0) {
        *phOperationData = NULL;
        RRETURN(NO_ERROR);
    }
    
    DWORD dwData;
    DWORD dwValue;

    pInfo = (LPSampleDS_ATTR_INFO)AllocProvMem(
                                      sizeof(SampleDS_ATTR_INFO)*cValues
                                      );
    if (!pInfo)
        RRETURN(E_OUTOFMEMORY);

    for (i = 0; i < cValues; i++) { 
        DWORD dwType;
        pszValue = (LPWSTR)AllocProvMem(sizeof(WCHAR)*MAX_PATH);
        pbData = (BYTE*)AllocProvMem(sizeof(WCHAR)*MAX_PATH);
        if (pbData == NULL || pszValue == NULL) 
            goto Error;
               
        dwData = sizeof(WCHAR) * MAX_PATH;
        dwValue = sizeof(WCHAR) * MAX_PATH;

        if (RegEnumValue(
                (HKEY)hkey, 
                i, 
                pszValue, 
                &dwValue, 
                NULL, 
                &dwType,     
                pbData,     
                &dwData
                ) != ERROR_SUCCESS)
            goto Error;

     
        
        if (!_wcsicmp(
                pszValue,
                SAMPLEDS_REG_TYPE)) {
            FreeProvMem(pszValue);
            FreeProvMem(pbData);
            continue;
        };
        
        switch (dwType) {
            case REG_DWORD:
                {
                SampleDS_TYPE_2 *pData = NULL;
                pData = (SampleDS_TYPE_2*)AllocProvMem(
                                               sizeof(SampleDS_TYPE_2));
                if (pData == NULL)
                    goto Error;
                pInfo[cProp].lpValue = (BYTE*)pData;
                pData->Integer = *(DWORD*)pbData;
                pInfo[cProp].dwSyntaxId = SampleDS_DATATYPE_2;
                FreeProvMem(pbData);
                pbData = NULL;
                break;
                }
            case REG_SZ:
                {
                SampleDS_TYPE_1 *pData = NULL;
                pData = (SampleDS_TYPE_1*)AllocProvMem(
                                               sizeof(SampleDS_TYPE_1));
                if (pData == NULL)
                    goto Error;
                pInfo[cProp].lpValue = (BYTE*)pData;
                pData->DNString = (LPWSTR)pbData;
                pInfo[cProp].dwSyntaxId = SampleDS_DATATYPE_1;
                break;
                }
            default:
                goto Error;
        }
        pInfo[cProp].lpAttributeName = pszValue;
        pInfo[cProp].dwNumberOfValues = 1;
        cProp++;
    }
    
    // Ownership has already been passed
    pbData = NULL;
    pszValue = NULL;

    LPSampleDS_ATTRS_INFO pAttrsInfo;
    pAttrsInfo = (LPSampleDS_ATTRS_INFO)AllocProvMem(sizeof(SampleDS_ATTRS_INFO));
    if (!pAttrsInfo)
        goto Error;
    
    pAttrsInfo->pAttrInfo = pInfo;
    pAttrsInfo->dwAttr = cProp;
    *phOperationData = pAttrsInfo;
    
    RRETURN(NO_ERROR);

Error: 
    for (DWORD j=0; j<cProp; j++) {
        if (pInfo[j].lpAttributeName)
            FreeProvMem(pInfo[j].lpAttributeName);
        if (pInfo[j].lpValue) {
            if (pInfo[j].dwSyntaxId == SampleDS_DATATYPE_1) {
                if (((SampleDS_TYPE_1*)(pInfo[j].lpValue))->DNString)
                    FreeProvMem(((SampleDS_TYPE_1*)
                                    (pInfo[j].lpValue))->DNString);
            }
            FreeProvMem(pInfo[j].lpValue);
        }
    }
    if (pszValue)
        FreeProvMem(pszValue);
    if (pbData)
        FreeProvMem(pbData);
    FreeProvMem(pInfo);
    RRETURN(E_FAIL);
}


/*++

Routine Description:

    Get all the property defintions from the Schema
    
Arguments:

Return Value:

--*/
HRESULT
SampleDSGetPropertyDefinition( 
    LPSampleDS_ATTR_DEF* ppAttrDefsReturn,
    DWORD *pnumObject)
{                           
    WCHAR szRegPath[MAX_PATH] = SAMPLEDS_REGSCHEMAPATH;
    DWORD numEntries;
    HKEY hKey;
    LPSampleDS_ATTR_DEF pAttrDefsCurrent; 
    LPSampleDS_ATTR_DEF pAttrDefsStart; 
    LPWSTR szPropNameCur;
    DWORD dwPropNameCur = MAX_PATH;
    DWORD numProperties = 0;
    
    if( RegOpenKeyEx( 
            HKEY_LOCAL_MACHINE, 
            szRegPath, 
            0, 
            KEY_ALL_ACCESS, 
            &hKey
            ) != ERROR_SUCCESS) {
        RRETURN(E_FAIL);
    }
    
    if( RegQueryInfoKey(
                hKey,
                NULL,
                NULL,
                NULL,
                &numEntries,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL
                ) != ERROR_SUCCESS) {
        goto Error;
    }
    
    pAttrDefsStart = (LPSampleDS_ATTR_DEF)AllocProvMem(
                                    sizeof(SampleDS_ATTR_DEF)*numEntries);
    if (!pAttrDefsStart)
        goto Error;
    pAttrDefsCurrent = pAttrDefsStart;
    DWORD i;
    for (i=0; i<numEntries; i++) {
        szPropNameCur = (LPWSTR)AllocProvMem(sizeof(WCHAR)*dwPropNameCur);
        if (!szPropNameCur)
            goto Error;

        if (RegEnumKey(
                hKey,
                i,
                szPropNameCur,
                dwPropNameCur
                ) != ERROR_SUCCESS)
            goto Error;

        if (SampleDSGetPropertyInfo( 
                hKey,
                szPropNameCur,
                pAttrDefsCurrent
                ) != ERROR_SUCCESS) {
            FreeProvMem(szPropNameCur);
            continue;
        }
        pAttrDefsCurrent->lpAttributeName = szPropNameCur;
        numProperties++;
        pAttrDefsCurrent++;
    }

    // Ownership has been passed
    szPropNameCur = NULL;

    if (numProperties != numEntries) {
        LPSampleDS_ATTR_DEF pAttrDefsFinal; 
        pAttrDefsFinal = (LPSampleDS_ATTR_DEF)AllocProvMem(
                                    sizeof(SampleDS_ATTR_DEF)*numProperties);
        if (!pAttrDefsFinal)
            goto Error;
        memcpy( 
            (void*)pAttrDefsFinal,
            (void*)pAttrDefsStart,
            sizeof(SampleDS_ATTR_DEF)*numProperties
            );
        *ppAttrDefsReturn = pAttrDefsFinal;    
        FreeProvMem(pAttrDefsStart);
    }
    else {
        *ppAttrDefsReturn = pAttrDefsStart; 
    }
    *pnumObject = numProperties;
    RegCloseKey(hKey);
    RRETURN(S_OK);

Error:
    RegCloseKey(hKey);
    LPSampleDS_ATTR_DEF pAttrDefsDelete = pAttrDefsStart; 
    for (DWORD j=0; j<numProperties; j++) {
        if (pAttrDefsDelete->lpAttributeName)
            FreeProvMem(pAttrDefsDelete->lpAttributeName);
        pAttrDefsDelete++;
    }
    if (szPropNameCur)
        FreeProvMem(szPropNameCur);
    if (pAttrDefsStart)
        FreeProvMem(pAttrDefsStart);
    RRETURN(E_FAIL);
}


/*++

Routine Description:

    Get a particular property defintion from the schema

Arguments:

Return Value:

--*/
HRESULT
SampleDSGetPropertyDefinition( 
    LPSampleDS_ATTR_DEF* ppAttrDefReturn,
    LPWSTR szPropName)
{                           
    WCHAR szRegPath[MAX_PATH] = SAMPLEDS_REGSCHEMAPATH;
    DWORD numEntries;
    HKEY hKey;
    LPSampleDS_ATTR_DEF pAttrDefCurrent; 
    LPWSTR szPropNameCur;
    DWORD i;
    
    if( RegOpenKeyEx( 
            HKEY_LOCAL_MACHINE, 
            szRegPath, 
            0, 
            KEY_ALL_ACCESS, 
            &hKey
            ) != ERROR_SUCCESS) {
        RRETURN(E_FAIL);
    }
    
    if( RegQueryInfoKey(
            hKey,
            NULL,
            NULL,
            NULL,
            &numEntries,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
            ) != ERROR_SUCCESS) {
        goto Error;
    }
    
    pAttrDefCurrent= (LPSampleDS_ATTR_DEF)AllocProvMem(
                                               sizeof(SampleDS_ATTR_DEF));
    if (!pAttrDefCurrent)
        goto Error;
    szPropNameCur = (LPWSTR)AllocProvMem(sizeof(WCHAR)*MAX_PATH);
    if (!szPropNameCur)
        goto Error;

    for (i=0; i<numEntries; i++) {
        if (RegEnumKey(hKey,
            i,
            szPropNameCur,
            MAX_PATH) != ERROR_SUCCESS)
            goto Error;

        if (!_wcsicmp(
                szPropNameCur,
                szPropName)) {
            if (SampleDSGetPropertyInfo( 
                                hKey,
                                szPropNameCur,
                                pAttrDefCurrent
                                ) != ERROR_SUCCESS) 
                goto Error;
            pAttrDefCurrent->lpAttributeName = szPropNameCur;
            *ppAttrDefReturn = pAttrDefCurrent; 
            RegCloseKey(hKey);
            RRETURN(S_OK);
        }
    }
Error:
    RegCloseKey(hKey);
    if (szPropNameCur)
        FreeProvMem(szPropNameCur);
    if (pAttrDefCurrent)
        FreeProvMem(pAttrDefCurrent);
    RRETURN(E_FAIL);
}


/*++

Routine Description:

    Free memory allocated by GetPropertyDefinition

Arguments:

Return Value:

--*/
HRESULT    
SampleDSFreePropertyDefinition(LPSampleDS_ATTR_DEF pAttrDefs,
                               DWORD numObject)
{
    if (!pAttrDefs)
        RRETURN(E_FAIL);

    LPSampleDS_ATTR_DEF pAttrDefCurrent = pAttrDefs;
    for (DWORD j=0; j<numObject; j++) {
        if (pAttrDefCurrent->lpAttributeName)
            FreeProvMem(pAttrDefCurrent->lpAttributeName);
        pAttrDefCurrent++;
    }
    FreeProvMem(pAttrDefs);
    RRETURN(S_OK);
}


/*++

Routine Description:

    Get the type of an object in text format

Arguments:

Return Value:

--*/
HRESULT
SampleDSGetTypeText(HKEY hKey,
                    LPWSTR szPropertyName,
                    LPWSTR szClassName,
                    DWORD *pdwClassName) 
{
    HKEY hKeyProperty;
    
    if (RegOpenKey(
            hKey,
            szPropertyName,
            &hKeyProperty
            ) != ERROR_SUCCESS) {
        RRETURN(E_FAIL);
    }
    
    DWORD dwType;
    if (RegQueryValueEx(
            hKeyProperty, 
            SAMPLEDS_REG_TYPE,
            NULL,
            &dwType,
            (BYTE*)szClassName,    
            pdwClassName
            ) != ERROR_SUCCESS) {
        goto Error;
    }

    if (dwType != REG_SZ) {
        goto Error;
    }
    RegCloseKey(hKeyProperty);
    RRETURN(S_OK);
Error:
    RegCloseKey(hKeyProperty);
    RRETURN(E_FAIL);

}

/*++

Routine Description:

    Get the type of an object 

Arguments:

Return Value:

--*/
HRESULT
SampleDSGetType(HKEY hKey,
                LPWSTR szPropertyName,
                DWORD *pdwType)
{
    HRESULT hrReturn = S_OK;
    LPWSTR szClassName;
    DWORD dwClassName = MAX_PATH * sizeof(WCHAR);

    szClassName = (LPWSTR)AllocProvMem(dwClassName);
    if (!szClassName) {
        hrReturn = E_OUTOFMEMORY;
        goto Error;
    }

    if (SampleDSGetTypeText(
                    hKey,
                    szPropertyName,
                    szClassName,
                    &dwClassName
                    ) == E_FAIL) {
        hrReturn = E_FAIL;
        goto Error;
    }
       
    if (!_wcsicmp(
            szClassName,
            SAMPLEDS_REG_PROPERTY)) {
        *pdwType = SAMPLEDS_PROPERTY;
    }
    else if (!_wcsicmp(
                szClassName,
                SAMPLEDS_REG_CLASS)) {
        *pdwType = SAMPLEDS_CLASS;
    }
    else {
        *pdwType = SAMPLEDS_UNKNOWN;
    }
Error:
    if (szClassName)
        FreeProvMem(szClassName);
    RRETURN(hrReturn);
}

/*++

Routine Description:

    Get information about a property from the schema

Arguments:

Return Value:

--*/
HRESULT
SampleDSGetPropertyInfo(HKEY hKey,
                        LPWSTR szPropertyName,
                        LPSampleDS_ATTR_DEF pAttrDef)
{
    HKEY hKeyClass;
    DWORD dwSyntax;
    DWORD dwType;
    DWORD dwSyntaxSize = sizeof(DWORD);
    DWORD dwSchemaType;

    if ((SampleDSGetType(
                    hKey,
                    szPropertyName,
                    &dwSchemaType
                    ) == E_FAIL) || 
        (dwSchemaType != SAMPLEDS_PROPERTY)) 
        RRETURN(E_FAIL);
    
    if (RegOpenKeyEx(
                hKey,
                szPropertyName,
                NULL,
                KEY_READ,
                &hKeyClass
                ) != ERROR_SUCCESS)
        RRETURN(E_FAIL);

    if (RegQueryValueEx(
                    hKeyClass, 
                    SAMPLEDS_REG_SYNTAX,
                    NULL,
                    &dwType,
                    (BYTE*)&dwSyntax,    
                    &dwSyntaxSize
                    ) == ERROR_SUCCESS) {
        pAttrDef->dwSyntaxID = dwSyntax;
        RegCloseKey(hKeyClass);
        RRETURN(S_OK);
    } 
    RegCloseKey(hKeyClass);
    RRETURN(E_FAIL);
}


/*++

Routine Description:

    Free the memory used by a LPWSTR_LIST

Arguments:

Return Value:

--*/
void FreeList(LPWSTR_LIST pList)
{
    if (pList) {
        if (pList->lpString) {
            FreeProvStr(pList->lpString);
                }
        FreeList(pList->Next);
        FreeProvMem(pList);
        };
}

/*++

Routine Description:

Arguments:

Return Value:

--*/
HRESULT
SampleDSGetClassDefinition( 
    LPSampleDS_CLASS_DEF* ppClassDefsReturn,
    DWORD *pnumObject)
{                           
    WCHAR szRegPath[MAX_PATH] = SAMPLEDS_REGSCHEMAPATH;
    DWORD numEntries;
    HKEY hKey;
    LPSampleDS_CLASS_DEF pClassDefsCurrent; 
    LPSampleDS_CLASS_DEF pClassDefsStart; 
    LPWSTR szClassName;
    DWORD dwClassName = MAX_PATH;
    DWORD numClass = 0;
    
    if( RegOpenKeyEx( 
                HKEY_LOCAL_MACHINE, 
                szRegPath, 
                0, 
                KEY_ALL_ACCESS, 
                &hKey
                ) != ERROR_SUCCESS) {
        RRETURN(E_FAIL);
    }
    
    if( RegQueryInfoKey(
                    hKey,
                    NULL,
                    NULL,
                    NULL,
                    &numEntries,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                    ) != ERROR_SUCCESS) {
        goto Error;
    }
    
    pClassDefsStart = (LPSampleDS_CLASS_DEF)AllocProvMem(
                                      sizeof(SampleDS_CLASS_DEF)*numEntries);
    if (!pClassDefsStart)
        goto Error;
    pClassDefsCurrent = pClassDefsStart;
    DWORD i;
    for (i=0; i<numEntries; i++) {
        szClassName = (LPWSTR)AllocProvMem(sizeof(WCHAR)*dwClassName);
        if (!szClassName)
            goto Error;

        if (RegEnumKey(
                    hKey,
                    i,
                    szClassName,
                    dwClassName
                    ) != ERROR_SUCCESS)
            goto Error;

        if (SampleDSGetClassInfo(
                            hKey,
                            szClassName,
                            pClassDefsCurrent
                            ) != ERROR_SUCCESS) {
            FreeProvMem(szClassName);
            continue;
        }
        pClassDefsCurrent->lpClassName = szClassName;
        numClass++;
        pClassDefsCurrent++;
    }
    szClassName = NULL;

    if (numClass != numEntries) {
        LPSampleDS_CLASS_DEF pClassDefsFinal; 
        pClassDefsFinal = (LPSampleDS_CLASS_DEF)AllocProvMem(
                                     sizeof(SampleDS_CLASS_DEF)*numClass);
        if (!pClassDefsFinal)
            goto Error;
        memcpy( 
            (void*)pClassDefsFinal,
            (void*)pClassDefsStart,
            sizeof(SampleDS_CLASS_DEF)*numClass
            );
        *ppClassDefsReturn = pClassDefsFinal;
        FreeProvMem(pClassDefsStart);
    }
    else {
        *ppClassDefsReturn = pClassDefsStart; 
    }
    *pnumObject = numClass;
    RegCloseKey(hKey);
    RRETURN(S_OK);

Error:
    RegCloseKey(hKey);
    LPSampleDS_CLASS_DEF pClassDefsDelete = pClassDefsStart; 
    DWORD j;
    for (j=0; j<numClass; j++) {
        if (pClassDefsDelete->lpClassName)
            FreeProvMem(pClassDefsDelete->lpClassName);
        if (pClassDefsDelete->lpMandatoryAttributes)
            FreeList(pClassDefsDelete->lpMandatoryAttributes);
        pClassDefsDelete++;
    }
    if (szClassName)
        FreeProvMem(szClassName);
    if (pClassDefsStart)
        FreeProvMem(pClassDefsStart);
    RRETURN(E_FAIL);
}

/*++

Routine Description:

    Get the class defintion for a particular class 

Arguments:

Return Value:

--*/
HRESULT
SampleDSGetClassDefinition( 
    LPSampleDS_CLASS_DEF* ppClassDefReturn,
    LPWSTR szClassName)
{                           
    WCHAR szRegPath[MAX_PATH] = SAMPLEDS_REGSCHEMAPATH;
    DWORD numEntries;
    HKEY hKey;
    LPSampleDS_CLASS_DEF pClassDefCurrent; 
    LPWSTR szClassNameCurrent;
    DWORD i;
    
    if( RegOpenKeyEx( 
                HKEY_LOCAL_MACHINE, 
                szRegPath, 
                0, 
                KEY_ALL_ACCESS, 
                &hKey
                ) != ERROR_SUCCESS) {
        RRETURN(E_FAIL);
    }
    
    if( RegQueryInfoKey(
                    hKey,
                    NULL,
                    NULL,
                    NULL,
                    &numEntries,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                    ) != ERROR_SUCCESS) {
        goto Error;
    }
    
    pClassDefCurrent= (LPSampleDS_CLASS_DEF)AllocProvMem(
                                             sizeof(SampleDS_CLASS_DEF));
    if (!pClassDefCurrent)
        goto Error;
    szClassNameCurrent = (LPWSTR)AllocProvMem(sizeof(WCHAR)*MAX_PATH);
    if (!szClassNameCurrent)
        goto Error;

    for (i=0; i<numEntries; i++) {
        if (RegEnumKey(hKey,
            i,
            szClassNameCurrent,
            MAX_PATH) != ERROR_SUCCESS)
            goto Error;

        if (!_wcsicmp(szClassNameCurrent,szClassName)) {
            if (SampleDSGetClassInfo( 
                                hKey,
                                szClassNameCurrent,
                                pClassDefCurrent
                                ) != ERROR_SUCCESS)
                goto Error;
            pClassDefCurrent->lpClassName = szClassNameCurrent;
            *ppClassDefReturn = pClassDefCurrent; 
            RegCloseKey(hKey);
            RRETURN(S_OK);
        }
    }
Error:
    RegCloseKey(hKey);
    if (szClassNameCurrent)
        FreeProvMem(szClassNameCurrent);
    if (pClassDefCurrent)
        FreeProvMem(pClassDefCurrent);
    RRETURN(E_FAIL);
}

/*++

Routine Description:

    Free memory allocated by GetClassDefinition

Arguments:

Return Value:

--*/
HRESULT    
SampleDSFreeClassDefinition(LPSampleDS_CLASS_DEF pClassDefs,
                            DWORD numObject)
{
    if (!pClassDefs)
        RRETURN(E_FAIL);

    LPSampleDS_CLASS_DEF pClassDefCurrent = pClassDefs;
    for (DWORD j=0; j<numObject; j++) {
        if (pClassDefCurrent->lpClassName)
            FreeProvMem(pClassDefCurrent->lpClassName);
        if (pClassDefCurrent->lpMandatoryAttributes)
            FreeList(pClassDefCurrent->lpMandatoryAttributes);
        pClassDefCurrent++;
    }
    FreeProvMem(pClassDefs);
    RRETURN(S_OK);
}

/*++

Routine Description:

    Get the next token in a REG_MULTISZ string returned by the 
    Regsitry getvalue function 

Arguments:

Return Value:

--*/
LPWSTR nexttoken(LPWSTR szCurrent)
{
    static LPWSTR szRemainder = NULL;
    LPWSTR szReturn = NULL;

    if (szCurrent) {
        szRemainder = szCurrent;
    } 
    else if (szRemainder == NULL) {
        return NULL;
    }

    if (*szRemainder) {
        szReturn = szRemainder;
        while (*++szRemainder);
        szRemainder++;
    }
    return szReturn;
}

/*++

Routine Description:

    Get information about a particular class from the schema

Arguments:

Return Value:

--*/
HRESULT
SampleDSGetClassInfo(HKEY hKey,
                     LPWSTR szClassName,
                     LPSampleDS_CLASS_DEF pClassDef)
{
    HKEY hKeyClass;
    DWORD dwType;
    LPWSTR szProperties;
    DWORD dwProperties = MAX_PATH * 3;
    LPWSTR_LIST pListStart = NULL; 

    DWORD dwManProp = 0;
    LPWSTR_LIST pListCurrent = NULL; 
    LPWSTR szPropCurrent = NULL;
    LPWSTR szProperty = NULL;
    LPWSTR szPropertyNew = NULL;
    
    DWORD dwSchemaType;
    if ((SampleDSGetType(
                    hKey,
                    szClassName,
                    &dwSchemaType) == E_FAIL) || 
        (dwSchemaType != SAMPLEDS_CLASS)) 
        RRETURN(E_FAIL);
    
    if (RegOpenKeyEx(
                hKey,
                szClassName,
                NULL,
                KEY_READ,
                &hKeyClass
                ) != ERROR_SUCCESS)
        RRETURN(E_FAIL);

    szProperties= (LPWSTR)AllocProvMem(sizeof(WCHAR)*dwProperties);
    if (!szProperties)
        goto Error;

    if (RegQueryValueEx(
                    hKeyClass, 
                    SAMPLEDS_REG_MANPROP,
                    NULL,
                    &dwType,
                    (BYTE*)szProperties,    
                    &dwProperties
                    ) != ERROR_SUCCESS) {
        goto Error;
    }
    if (dwType != REG_MULTI_SZ) {
        goto Error;
    }

    szPropCurrent = szProperties;
    szProperty = nexttoken(szPropCurrent);
    szPropertyNew;
    if (szProperty) {
        pListStart = (LPWSTR_LIST)AllocProvMem(sizeof(WSTR_LIST));
        if (!pListStart)
            goto Error;
        pListCurrent = pListStart;
        szPropertyNew = AllocProvStr(szProperty);
        if (!szPropertyNew)
            goto Error;
        pListCurrent->lpString = szPropertyNew;
        szProperty = nexttoken(NULL);
        dwManProp++;
        while( szProperty != NULL ) {
            LPWSTR_LIST pListNew = (LPWSTR_LIST)AllocProvMem(
                                                  sizeof(WSTR_LIST));
            if (!pListNew)
                goto Error;
            pListCurrent->Next = pListNew;
            szPropertyNew = AllocProvStr(szProperty);
            if (!szPropertyNew)
                goto Error;
            pListNew->lpString = szPropertyNew;
            pListCurrent = pListNew;
            szProperty = nexttoken(NULL);
            dwManProp++;
        }                              
       pListCurrent->Next = NULL;
    }
    pClassDef->lpMandatoryAttributes = pListStart;
    pClassDef->dwNumberOfMandatoryAttributes = dwManProp;
    RegCloseKey(hKeyClass);
    RRETURN(S_OK);      

Error:
    RegCloseKey(hKeyClass);
    if (pListStart)
        FreeList(pListStart);
    if (szProperties)
        FreeProvMem(szProperties);
    RRETURN(E_FAIL);
}


/*++

Routine Description:
    
    Add an object in the DS

Arguments:

Return Value:

--*/
HRESULT
SampleDSAddObject(HANDLE hKey,
                  LPWSTR szObject,
                  LPWSTR szClass,
                  HANDLE hOperationData
                  )
{
    if (!szObject || !szClass || !hKey)
        RRETURN(E_FAIL);

    HKEY hKeyNew;
    if (RegCreateKey(
                (HKEY)hKey,
                szObject,
                &hKeyNew
                ) != ERROR_SUCCESS) {
        RRETURN(E_FAIL);
    };
    
    if (RegSetValueEx(
                hKeyNew,
                SAMPLEDS_REG_TYPE,
                NULL,
                REG_SZ,
                (BYTE*)szClass,
                (wcslen(szClass) + 1) * sizeof(WCHAR)
                ) != ERROR_SUCCESS) {
        RRETURN(E_FAIL);
    };
    if (hOperationData) {
        if (SampleDSModifyObject(
                            hKeyNew,
                            hOperationData
                            ) != S_OK) {
            RRETURN(E_FAIL);
        };
    };
    RRETURN(S_OK);
}


/*++

Routine Description:

    Delete a registry key and all its subkeys

Arguments:

Return Value:

--*/
LONG RegDeleteAllKeys(HKEY hKeyDelete,
                      LPWSTR pszSubKey)
{
    HKEY  hKeyChild;
    TCHAR szTmp[MAX_PATH];
    LONG  lResult;
    DWORD dwTmpSize = MAX_PATH;

    lResult = RegOpenKeyEx(
                       hKeyDelete,
                       pszSubKey,
                       NULL,
                       KEY_ALL_ACCESS,
                       &hKeyChild
                       );
    if (lResult != ERROR_SUCCESS)
        return lResult;
   
    lResult = RegEnumKey(
                     hKeyChild,
                     0,
                     szTmp,
                     dwTmpSize
                     );

    while (lResult != ERROR_NO_MORE_ITEMS) {
        RegDeleteAllKeys(
                 hKeyChild,
                 szTmp
                 );

        lResult = RegEnumKey(
                         hKeyChild,
                         0,
                         szTmp,
                         dwTmpSize
                         );
    }   

    RegCloseKey(hKeyChild);
    lResult = RegDeleteKey(
                       hKeyDelete,
                       pszSubKey
                       );

    return lResult;
}


/*++

Routine Description:

    Remove an object from the DS

Arguments:

Return Value:

--*/
HRESULT
SampleDSRemoveObject(HANDLE hKey,
                     LPWSTR szObject) 
{
    if (RegDeleteAllKeys(
                    (HKEY)hKey,
                    szObject
                    ) == ERROR_SUCCESS)
        RRETURN(S_OK);
    else
        RRETURN(E_FAIL);
}



/*++

Routine Description:

    Create Memory Buffer for operation data

Arguments:

Return Value:

--*/
HRESULT
SampleDSCreateBuffer(HANDLE *phOperationData)
{
    LPSampleDS_ATTRS_INFO pAttrsInfo;
    pAttrsInfo = (LPSampleDS_ATTRS_INFO)AllocProvMem(sizeof(SampleDS_ATTRS_INFO));
    if (!pAttrsInfo)
        RRETURN(E_OUTOFMEMORY);
    *phOperationData = pAttrsInfo;
    RRETURN(S_OK);
}



/*++

Routine Description:

    Free memroy pointed to by operationdata

Arguments:

Return Value:

--*/
HRESULT
SampleDSFreeBuffer(HANDLE hOperationData)
{
    if (!hOperationData)
        RRETURN(E_FAIL);
    
    LPSampleDS_ATTRS_INFO pAttrsInfo;
    pAttrsInfo = (LPSampleDS_ATTRS_INFO)hOperationData;

    LPSampleDS_ATTR_INFO pAttrInfo;
    DWORD cAttr;
    pAttrInfo = pAttrsInfo->pAttrInfo;
    cAttr = pAttrsInfo->dwAttr;

    if (pAttrInfo) {
        for (DWORD i = 0;i<cAttr;i++) {
            if (pAttrInfo->lpAttributeName)
                FreeProvMem(pAttrInfo->lpAttributeName);
            if (pAttrInfo->lpValue) {
                if (pAttrInfo->dwSyntaxId == SampleDS_DATATYPE_1) {
                    if (((SampleDS_TYPE_1*)(pAttrInfo->lpValue))->DNString)
                        FreeProvMem(((SampleDS_TYPE_1*)
                                        (pAttrInfo->lpValue))->DNString);
                }
                FreeProvMem(pAttrInfo->lpValue);
            }
            pAttrInfo++;
        }
    }
    FreeProvMem(pAttrsInfo->pAttrInfo);
    FreeProvMem(pAttrsInfo);
    RRETURN(S_OK);
}


