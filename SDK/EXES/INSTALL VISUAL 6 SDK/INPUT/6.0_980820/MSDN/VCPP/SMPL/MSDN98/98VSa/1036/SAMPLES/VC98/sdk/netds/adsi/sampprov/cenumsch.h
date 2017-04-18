/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    EnumSch.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _ENUMSCH_H_
#define _ENUMSCH_H_

class FAR CSampleDSSchemaEnum : public CSampleDSEnumVariant
{
public:
    // IEnumVARIANT methods
    STDMETHOD(Next)(
        ULONG cElements,
        VARIANT FAR* pvar,
        ULONG FAR* pcElementFetched
        );

    static
    HRESULT
    Create(
        CSampleDSSchemaEnum FAR* FAR* ppenumvariant,
        BSTR bstrSampleDSTreeName,
        BSTR bstrADsPath,
        BSTR bstrDomainName,
        VARIANT var
        );

    CSampleDSSchemaEnum();
    ~CSampleDSSchemaEnum();

    HRESULT
    EnumObjects(
        ULONG cElements,
        VARIANT FAR * pvar,
        ULONG FAR * pcElementFetched
        );

private:

    ObjectTypeList FAR *_pObjList;
    //HANDLE _hOperationData;
    //HANDLE _hTree;
    
    LPSampleDS_ATTR_DEF _lpAttrDefs;
    DWORD _dwAttrCurrent;
    DWORD _dwAttrReturned;


    BSTR        _bstrName;
    BSTR        _bstrSampleDSTreeName;
    BSTR        _bstrADsPath;

    LPSampleDS_CLASS_DEF _lpClassDefs;
    DWORD       _dwClassCurrent;
    DWORD       _dwClassReturned;
    
    //DWORD       _dwCurrentEntry;
    //DWORD       _dwInfoType;

    HRESULT
    CSampleDSSchemaEnum::GetClassObject(
        IDispatch **ppDispatch
        );

    HRESULT
    EnumClasses(
        ULONG cElements,
        VARIANT FAR* pvar,
        ULONG FAR* pcElementFetched
        );

    HRESULT
    CSampleDSSchemaEnum::EnumObjects(
        DWORD ObjectType,
        ULONG cElements,
        VARIANT FAR * pvar,
        ULONG FAR * pcElementFetched
        );
    
    HRESULT
    CSampleDSSchemaEnum::EnumProperties(
        ULONG cElements,
        VARIANT FAR* pvar,
        ULONG FAR* pcElementFetched
        );
    
    HRESULT
    CSampleDSSchemaEnum::GetPropertyObject(
        IDispatch ** ppDispatch
        );
};

#endif

