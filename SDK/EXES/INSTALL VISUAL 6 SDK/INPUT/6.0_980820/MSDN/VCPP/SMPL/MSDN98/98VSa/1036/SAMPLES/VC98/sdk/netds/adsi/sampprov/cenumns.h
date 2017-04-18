/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CEnumNs.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CENUMNS_H_
#define _CENUMNS_H_

class FAR CSampleDSNamespaceEnum : public CSampleDSEnumVariant
{
public:

    // IEnumVARIANT methods
    STDMETHOD(Next)(ULONG cElements,
                    VARIANT FAR* pvar,
                    ULONG FAR* pcElementFetched);

    static HRESULT Create(CSampleDSNamespaceEnum FAR* FAR*, VARIANT var);

    CSampleDSNamespaceEnum();
    ~CSampleDSNamespaceEnum();

    HRESULT
    PrepBuffer();

    HRESULT
    FetchNextObject(
        IDispatch ** ppDispatch
        );

    HRESULT
    FetchObjects(
        ULONG cElements,
        VARIANT FAR* pvar,
        ULONG FAR* pcElementFetched
        );

    HRESULT
    CSampleDSNamespaceEnum::EnumObjects(
        ULONG cElements,
        VARIANT FAR* pvar,
        ULONG FAR* pcElementFetched
        );

private:

    ObjectTypeList FAR *_pObjList;

    DWORD _dwEntriesRead;
    DWORD _dwCurrentEntry;
    HANDLE _hEnum;
    LPVOID _pBuffer;
    LPVOID _pBufferEnd;
};

#endif

