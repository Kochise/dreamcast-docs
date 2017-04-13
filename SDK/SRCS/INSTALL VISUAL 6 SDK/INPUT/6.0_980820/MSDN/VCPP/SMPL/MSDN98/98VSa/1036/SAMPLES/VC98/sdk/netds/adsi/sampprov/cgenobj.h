/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CGenObj.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CGENOBJ_H_
#define _CGENOBJ_H_

class CSampleDSGenObject;


class CSampleDSGenObject : INHERIT_TRACKING,
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

    CSampleDSGenObject::CSampleDSGenObject();

    CSampleDSGenObject::~CSampleDSGenObject();

    static
    HRESULT
    CSampleDSGenObject::CreateGenericObject(
        BSTR bstrADsPath,
        DWORD dwObjectState,
        REFIID riid,
        void **ppvObj
        );

    static
    HRESULT
    CSampleDSGenObject::CreateGenericObject(
        BSTR Parent,
        BSTR CommonName,
        BSTR ClassName,
        DWORD dwObjectState,
        REFIID riid,
        void **ppvObj
        );

    static
    HRESULT
    CSampleDSGenObject::AllocateGenObject(
        CSampleDSGenObject ** ppGenObject
        );

    STDMETHOD(GetInfo)(
        BOOL fExplicit
        );


    HRESULT
    CSampleDSGenObject::SampleDSSetObject();
    
    HRESULT
    CSampleDSGenObject::SampleDSCreateObject();
    
    protected:
    
        VARIANT     _vFilter;
        CPropertyCache FAR * _pPropertyCache;
        CDispatchMgr FAR * _pDispMgr;
};

HRESULT
ConvertSafeArrayToVariantArray(
    VARIANT varSafeArray,
    VARIANT ** ppVarArray,
    PDWORD pdwNumVariants
    );
#endif

