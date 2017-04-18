/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CNameSp.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CNAMESP_H_
#define _CNAMESP_H_

class CSampleDSNamespace : INHERIT_TRACKING,
                        public CCoreADsObject,
                        public IADsContainer,
                        public IADs
{
public:

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) ;

    DECLARE_STD_REFCOUNTING

    DECLARE_IDispatch_METHODS

    DECLARE_IADs_METHODS

    DECLARE_IADsContainer_METHODS

    CSampleDSNamespace::CSampleDSNamespace();

    CSampleDSNamespace::~CSampleDSNamespace();

    static
    HRESULT
    CSampleDSNamespace::CreateNamespace(
        BSTR Parent,
        BSTR NamespaceName,
        DWORD dwObjectState,
        REFIID riid,
        void **ppvObj
        );

    static
    HRESULT
    CSampleDSNamespace::AllocateNamespaceObject(
        CSampleDSNamespace ** ppNamespace
        );

protected:

    VARIANT     _vFilter;
    CDispatchMgr      *_pDispMgr;
};
#endif

