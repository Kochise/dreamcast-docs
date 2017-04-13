/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CClsObj.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CCLSOBJ_H_
#define _CCLSOBJ_H_

typedef struct _propentry{
    DWORD dwSyntaxId;
    LPWSTR pszPropName;
    struct _propentry *pNext;
} PROPENTRY, *PPROPENTRY;

#define SampleDS_CONTAINER_CLASS               0x01
#define SampleDS_EFFECTIVE_CLASS               0x02
#define SampleDS_NONREMOVABLE_CLASS            0x04
#define SampleDS_AMBIGUOUS_NAMING              0x08
#define SampleDS_AMBIGUOUS_CONTAINMENT         0x10

class CSampleDSClass;


class CSampleDSClass : INHERIT_TRACKING,
                     public CCoreADsObject,
                     public IADsClass
{
public:

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) ;

    DECLARE_STD_REFCOUNTING

    DECLARE_IDispatch_METHODS

    DECLARE_IADs_METHODS


    DECLARE_IADsClass_METHODS

    CSampleDSClass::CSampleDSClass();

    CSampleDSClass::~CSampleDSClass();

    static
    HRESULT
    CSampleDSClass::CreateClass(
        BSTR Parent,
        BSTR CommonName,
        LPSampleDS_CLASS_DEF lpClassDefs,
        DWORD dwObjectState,
        REFIID riid,
        void **ppvObj
        );

    static
    HRESULT
    CSampleDSClass::CreateClass(
        BSTR Parent,
        BSTR CommonName,
        HANDLE hTree,
        DWORD dwObjectState,
        REFIID riid,
        void **ppvObj
        );
    
    static
    HRESULT
    CSampleDSClass::AllocateClassObject(
        CSampleDSClass ** ppClass
        );

    STDMETHOD(GetInfo)(
        THIS_ DWORD dwApiLevel,
        BOOL fExplicit
        );

protected:
    VARIANT     _vFilter;
    LPWSTR      _lpClassName;
    DWORD       _dwNumberOfMandatoryAttributes;
    PPROPENTRY  _lpMandatoryAttributes;
    CDispatchMgr FAR * _pDispMgr;
};


PPROPENTRY
CreatePropertyList(
    LPWSTR_LIST  lpStringList
    );

PPROPENTRY
CreatePropertyEntry(
    LPWSTR pszPropertyName,
    DWORD dwSyntaxId
    );

void
FreePropertyEntry(
    PPROPENTRY pPropName
    );


HRESULT
MakeVariantFromPropList(
    PPROPENTRY pPropList,
    DWORD dwNumEntries,
    VARIANT * pVarList
    );
#endif

