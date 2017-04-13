/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CPrpObj.h

Abstract:

    Sample Provider GetObject functionality

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CPRPOBJ_H_
#define _CPRPOBJ_H_

struct SYNTAXMAP
{
    BSTR   bstrName;
    BSTR   bstrSampleDSName;
    long   lOleAutoDataType;
};

struct SYNTAXINFO
{
    BSTR   bstrName;
    long   lOleAutoDataType;
};

class CSampleDSProperty : INHERIT_TRACKING,
                       public CCoreADsObject,
                       public IADsProperty
{
public:

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) ;
    DECLARE_STD_REFCOUNTING

    /* Other methods */
    DECLARE_IDispatch_METHODS

    DECLARE_IADs_METHODS

    DECLARE_IADsProperty_METHODS

    /* Constructors, Destructors, ... */
    CSampleDSProperty::CSampleDSProperty();

    CSampleDSProperty::~CSampleDSProperty();

    static
    HRESULT
    CSampleDSProperty::CreateProperty(
        BSTR   bstrParent,
        BSTR   bstrName,
        LPSampleDS_ATTR_DEF lpAttrDef,
        DWORD  dwObjectState,
        REFIID riid,
        void **ppvObj
        );

    static
    HRESULT
    CSampleDSProperty::CreateProperty(
        BSTR   bstrParent,
        BSTR   bstrName,
        HANDLE hTree,
        DWORD  dwObjectState,
        REFIID riid,
        void **ppvObj
        );

    static
    HRESULT
    CSampleDSProperty::AllocatePropertyObject(
        CSampleDSProperty **ppProperty
        );

protected:

    CDispatchMgr FAR * _pDispMgr;

    /* Properties */
    VARIANT _vADsNames;
    VARIANT _vDsNames;
    BSTR _bstrSyntax;
};

HRESULT
MapSyntaxIdtoADsSyntax(
    DWORD dwSyntaxId,
    LPWSTR pszADsSyntax
    );

HRESULT
MapSyntaxIdtoSampleDSSyntax(
    DWORD dwSyntaxId,
    LPWSTR pszSampleDSSyntax
    );
#endif

