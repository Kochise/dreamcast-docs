/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    GetObj.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _GETOBJ_H_
#define _GETOBJ_H_

#define MAXCOMPONENTS               20

#define TOKEN_IDENTIFIER                1
#define TOKEN_COMMA                     2
#define TOKEN_BSLASH                    3
#define TOKEN_END                       4
#define TOKEN_OU                        5
#define TOKEN_USER                      6
#define TOKEN_GROUP                     7

#define TOKEN_ATSIGN                   11
#define TOKEN_EXCLAMATION              12
#define TOKEN_COLON                    13
#define TOKEN_FSLASH                   14
#define TOKEN_PROVIDER                 15

#define TOKEN_SCHEMA                   17
#define TOKEN_CLASS                    18
#define TOKEN_PROPERTY                 21
#define TOKEN_SYNTAX                   22

#define TOKEN_PERIOD                   24
#define TOKEN_EQUAL                    25
#define TOKEN_NAMESPACE                26
#define TOKEN_DSOBJECT                 28


typedef struct _component {
    LPWSTR szComponent;
    LPWSTR szValue;
}COMPONENT, *PCOMPONENT;

typedef struct _objectinfo {
    LPWSTR  ProviderName;
    LPWSTR  RootRDN;
    DWORD   ObjectType;
    DWORD   NumComponents;
    COMPONENT  ComponentArray[MAXCOMPONENTS];
} OBJECTINFO, *POBJECTINFO;

HRESULT
RelativeGetObject(
    BSTR ADsPath,
    BSTR ClassName,
    BSTR RelativeName,
    IDispatch* FAR* ppObject,
    BOOL bNamespaceRelative
    );

HRESULT
GetObject(
    LPWSTR szBuffer,
    LPVOID * ppObject
    );

HRESULT
GetNamespaceObject(
    POBJECTINFO pObjectInfo,
    LPVOID * ppObject
    );

HRESULT
ValidateNamespaceObject(
    POBJECTINFO pObjectInfo
    );

HRESULT
GetSchemaObject(
    POBJECTINFO pObjectInfo,
    LPVOID * ppObject
    );

HRESULT
ValidateSchemaObject(
    POBJECTINFO pObjectInfo,
    PDWORD pdwObjectType
    );

HRESULT
ValidateProvider(
    POBJECTINFO pObjectInfo
    );

HRESULT
AddComponent(
    POBJECTINFO pObjectInfo,
    LPWSTR szComponent,
    LPWSTR szValue
    );

HRESULT
AddProviderName(
    POBJECTINFO pObjectInfo,
    LPWSTR szToken
    );


HRESULT
BuildADsParentPath(
    LPWSTR szBuffer,
    LPWSTR szParent,
    LPWSTR szCommonName
    );

HRESULT
BuildDSPathFromADsPath(
    LPWSTR szADsPathName,
    LPWSTR szSampleDSPathName
    );

HRESULT
BuildADsParentPath(
    POBJECTINFO pObjectInfo,
    LPWSTR szParent,
    LPWSTR szCommonName
    );


HRESULT
BuildDSTreeNameFromADsPath(
    LPWSTR szBuffer,
    LPWSTR szSampleDSTreeName
    );

HRESULT
ValidateObjectType(
    POBJECTINFO pObjectInfo
    );


HRESULT
BuildSampleDSRootRDNFromADsPath(
    LPWSTR szBuffer,
    LPWSTR szDSTreeName
    );


HRESULT
AppendComponent(
   LPWSTR szDSPathName,
   PCOMPONENT pComponent
   );

HRESULT
BuildDSPathFromADsPath(
    LPWSTR szADsPathName,
    LPWSTR szDSRootName,
    LPWSTR szDSPathName
    );

HRESULT
InstantiateDerivedObject(
    IADs FAR * pADs,
    REFIID riid,
    void  ** ppObject
    );
#endif

