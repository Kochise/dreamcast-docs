/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    SmpTypes.h

Abstract:

    Definitions for Sample DS Data Types and structures used by
    the SampleDS Regsitry APIs to exchange data
    
Author:

Environment:

    User mode

Revision History :

--*/
#ifndef __SampleDSTYPES_H
#define __SampleDSTYPES_H


// Two data types are supported
#define SampleDS_DATATYPE_1  1
#define SampleDS_DATATYPE_2  2

typedef struct
{
    LPWSTR DNString;

} SampleDS_TYPE_1, * LPSampleDS_TYPE_1;

typedef struct
{
    DWORD Integer;

} SampleDS_TYPE_2, * LPSampleDS_TYPE_2;

typedef struct _SampleDStype{
    DWORD SampleDSType;
    union {
        SampleDS_TYPE_1 value_1;
        SampleDS_TYPE_2 value_2;
    }SampleDSValue;
}SampleDSOBJECT, *PSampleDSOBJECT, *LPSampleDSOBJECT;

#define SampleDS_MAX_TYPE1_LEN        32

typedef struct WSTR_LIST_ELEM
{
    struct WSTR_LIST_ELEM * Next;
    LPWSTR lpString;

}  WSTR_LIST,* LPWSTR_LIST;

typedef struct
{
    LPWSTR  lpAttributeName;
    DWORD   dwSyntaxID;

} SampleDS_ATTR_DEF, * LPSampleDS_ATTR_DEF;

typedef struct
{
    LPWSTR lpAttributeName;
    DWORD  dwSyntaxId;
    DWORD  dwNumberOfValues;
    LPBYTE lpValue;

} SampleDS_ATTR_INFO, * LPSampleDS_ATTR_INFO;

typedef struct
{
    LPSampleDS_ATTR_INFO pAttrInfo;
    DWORD dwAttr;
} SampleDS_ATTRS_INFO, * LPSampleDS_ATTRS_INFO;

typedef struct
{
    LPWSTR lpObjectFullName;
    LPWSTR lpObjectName;
    LPWSTR lpObjectClass;

} DS_OBJECT_INFO, * LPDS_OBJECT_INFO;

typedef struct
{
    LPWSTR lpObjectClass;

} DS_FILTER, * LPDS_FILTER;

typedef struct
{
    DWORD      dwNumberOfFilters;
    DS_FILTER Filters[1];

} DS_FILTER_LIST, * LPDS_FILTER_LIST;

typedef struct
{
    LPWSTR  lpClassName;
    DWORD   dwNumberOfMandatoryAttributes;
    LPWSTR_LIST lpMandatoryAttributes;
} SampleDS_CLASS_DEF, * LPSampleDS_CLASS_DEF;

#endif

