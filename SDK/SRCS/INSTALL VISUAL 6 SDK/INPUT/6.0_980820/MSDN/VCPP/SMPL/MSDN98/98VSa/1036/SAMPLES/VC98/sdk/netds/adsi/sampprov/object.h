/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    Object.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _OBJECT_H_
#define _OBJECT_H_

class FAR ObjectTypeList
{
private:
   SAFEARRAY FAR * _pObjList;
   DWORD    _dwCurrentIndex;
   DWORD    _dwLBound;
   DWORD    _dwUBound;
   DWORD    _dwMaxElements;

public:
    ObjectTypeList();

    static
    HRESULT
    ObjectTypeList::CreateObjectTypeList(
        VARIANT vFilter,
        ObjectTypeList ** ppObjectTypeList
        );

    ~ObjectTypeList();

    HRESULT
    GetCurrentObject(
        PDWORD pdwObject
        );

    HRESULT
    Next();

    HRESULT
    Reset();


};

HRESULT
BuildObjectArray(
    VARIANT var,
    SAFEARRAY ** ppFilter,
    DWORD * pdwNumElements
    );

HRESULT
BuildDefaultObjectArray(
    PFILTERS  pFilters,
    DWORD dwMaxFilters,
    SAFEARRAY ** ppFilter,
    DWORD * pdwNumElements
    );


HRESULT
IsValidFilter(
    LPWSTR ObjectName,
    DWORD *pdwFilterId,
    PFILTERS pFilters,
    DWORD dwMaxFilters
    );

#endif

