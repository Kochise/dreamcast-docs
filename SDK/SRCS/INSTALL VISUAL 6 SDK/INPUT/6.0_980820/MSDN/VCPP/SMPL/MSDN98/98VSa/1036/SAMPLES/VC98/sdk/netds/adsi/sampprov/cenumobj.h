/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CEnumObj.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CENUMOBJ_H_
#define _CENUMOBJ_H_

class FAR CSampleDSGenObjectEnum : public CSampleDSEnumVariant
{
public:
    CSampleDSGenObjectEnum(ObjectTypeList ObjList);
    CSampleDSGenObjectEnum();
    ~CSampleDSGenObjectEnum();

    HRESULT
    EnumObjects(
        ULONG cElements,
        VARIANT FAR * pvar,
        ULONG FAR * pcElementFetched
        );

    static
    HRESULT
    CSampleDSGenObjectEnum::Create(
        CSampleDSGenObjectEnum FAR* FAR* ppenumvariant,
        BSTR ADsPath,
        VARIANT var
        );

private:

        HRESULT
        CSampleDSGenObjectEnum::FetchObjects(
            ULONG cElements,
                VARIANT FAR* pvar,
                ULONG FAR* pcElementFetched
                );

        HRESULT
        CSampleDSGenObjectEnum::FetchNextObject(
                IDispatch ** ppDispatch
                );
        
    ObjectTypeList FAR *_pObjList;
    LPDS_FILTER_LIST _pDSFilterList;

    HANDLE      _hObject;
    HANDLE      _hEnum;
    LPDS_OBJECT_INFO _lpObjects;
    DWORD       _dwObjectReturned;
    DWORD       _dwObjectCurrentEntry;
    DWORD       _dwObjectTotal;

    BSTR        _ADsPath;

    BOOL        _bNoMore;

    HRESULT
    CSampleDSGenObjectEnum::GetGenObject(
        IDispatch ** ppDispatch
        );

    HRESULT
    EnumGenericObjects(
        ULONG cElements,
        VARIANT FAR* pvar,
        ULONG FAR* pcElementFetched
        );


    HRESULT
    CSampleDSGenObjectEnum::EnumObjects(
        DWORD ObjectType,
        ULONG cElements,
        VARIANT FAR * pvar,
        ULONG FAR * pcElementFetched
        );

    STDMETHOD(Next)(
        ULONG cElements,
        VARIANT FAR* pvar,
        ULONG FAR* pcElementFetched
        );

        HRESULT
        CSampleDSGenObjectEnum::IsValidDSFilter(
                LPWSTR lpObjectClass
                );

};

HRESULT
BuildDSFilterArray(
    VARIANT var,
    LPBYTE * ppContigFilter
    );

void
FreeFilterList(
    LPBYTE lpContigFilter
    );

LPBYTE
CreateAndAppendFilterEntry(
    LPBYTE pContigFilter,
    LPWSTR lpObjectClass
    );
#endif

