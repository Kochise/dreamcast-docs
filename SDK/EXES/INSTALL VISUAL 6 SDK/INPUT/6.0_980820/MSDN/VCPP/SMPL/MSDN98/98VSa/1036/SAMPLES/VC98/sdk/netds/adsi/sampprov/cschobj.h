/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CSchObj.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CSCHOBJ_H_
#define _CSCHOBJ_H_

class CSampleDSSchema;


class CSampleDSSchema : INHERIT_TRACKING,
                     public CCoreADsObject,
                     public IADs,
                     public IADsContainer
{
public:

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) ;

    DECLARE_STD_REFCOUNTING

    DECLARE_IDispatch_METHODS

    DECLARE_IADs_METHODS

    DECLARE_IADsContainer_METHODS

    CSampleDSSchema::CSampleDSSchema();

    CSampleDSSchema::~CSampleDSSchema();

    static
    HRESULT
    CSampleDSSchema::CreateSchema(
        BSTR Parent,
        BSTR CommonName,
        DWORD dwObjectState,
        REFIID riid,
        void **ppvObj
        );

    static
    HRESULT
    CSampleDSSchema::AllocateSchema(
        CSampleDSSchema ** ppSchema
        );

    STDMETHOD(GetInfo)(
        THIS_ DWORD dwApiLevel,
        BOOL fExplicit
        );

protected:

    VARIANT     _vFilter;
    BSTR        _SampleDSTreeName;

    CDispatchMgr FAR * _pDispMgr;

};

#endif




