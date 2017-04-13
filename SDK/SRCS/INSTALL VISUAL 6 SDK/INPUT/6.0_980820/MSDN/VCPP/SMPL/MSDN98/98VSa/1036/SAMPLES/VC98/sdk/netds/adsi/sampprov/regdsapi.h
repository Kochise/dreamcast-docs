/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    RegDsAPI.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _REGDSAPI_
#define _REGDSAPI_

#define REG_DS      1
#define REG_SCHEMA  2

#define SAMPLEDS_UNKNOWN  0
#define SAMPLEDS_PROPERTY 1
#define SAMPLEDS_CLASS    2

typedef struct REGDS_ENUM{
    DWORD  dwIndex;
    HANDLE hContainerKey;
} *LPREGDS_ENUM;

HRESULT
SampleDSOpenObject( 
    LPWSTR szRegPath,             
    HANDLE *phKey,                
    LPWSTR szClass,
    DWORD  dwType);

HRESULT
SampleDSCloseObject(
    HANDLE hKey);


HRESULT
SampleDSRDNEnum( 
    HANDLE *phEnum,
    HANDLE hContainerKey);


HRESULT
SampleDSNextRDN( 
    HANDLE hEnum,      
    LPWSTR *pszName,  
    LPWSTR *pszClass);

HRESULT
SampleDSFreeEnum(HANDLE hEnum);


HRESULT
SampleDSModifyObject(HANDLE hKey,
                     HANDLE hOperationData
                     );

HRESULT
SampleDSReadObject(
    HANDLE hkey,              
    HANDLE *phOperationData
    );


HRESULT
SampleDSGetPropertyDefinition( 
    LPSampleDS_ATTR_DEF* ppAttrDefReturn,
    DWORD *pnumObject
);

HRESULT
SampleDSGetPropertyDefinition( 
    LPSampleDS_ATTR_DEF* ppAttrDefReturn,
    LPWSTR szPropName
);

HRESULT
SampleDSGetType(HKEY hKey,
                LPWSTR szPropertyName,
                DWORD *pdwType
                );

HRESULT
SampleDSGetPropertyInfo(HKEY hKey,
                        LPWSTR szPropertyName,
                        LPSampleDS_ATTR_DEF pAttrDef
                        );

HRESULT
SampleDSGetClassDefinition( 
    LPSampleDS_CLASS_DEF* ppClassDefsReturn,
    DWORD *pnumObject
    );

HRESULT
SampleDSGetClassDefinition( 
    LPSampleDS_CLASS_DEF* ppClassDefReturn,
    LPWSTR szClassName
    );

HRESULT
SampleDSGetClassInfo(HKEY hKey,
                     LPWSTR szClassName,
                     LPSampleDS_CLASS_DEF pClassDef
                     );
HRESULT
SampleDSAddObject(HANDLE hKey,
                  LPWSTR szObject,
                  LPWSTR szClass,
                  HANDLE hOperationData
                  );

HRESULT
SampleDSRemoveObject(
     HANDLE hKey,
     LPWSTR szObject);

HRESULT
SampleDSGetTypeText(HKEY hKey,
                    LPWSTR szPropertyName,
                    LPWSTR szClassName,
                    DWORD *pdwClassName);
HRESULT
SampleDSCreateBuffer(HANDLE *phOperationData);

HRESULT
SampleDSFreeBuffer(HANDLE hOperationData);

HRESULT    
SampleDSFreeClassDefinition(LPSampleDS_CLASS_DEF pClassDefs,
                            DWORD numObject);

HRESULT    
SampleDSFreePropertyDefinition(LPSampleDS_ATTR_DEF pPropertyDefs,
                               DWORD numObject);


#endif
