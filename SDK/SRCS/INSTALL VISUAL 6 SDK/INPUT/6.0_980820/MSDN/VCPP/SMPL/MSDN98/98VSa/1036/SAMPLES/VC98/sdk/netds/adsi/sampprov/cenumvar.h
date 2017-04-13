/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CEnumVar.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CENUMVAR_H_
#define _CENUMVAR_H_

class FAR CSampleDSEnumVariant : public IEnumVARIANT
{
public:
    // IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj) ;
    STDMETHOD_(ULONG, AddRef)() ;
    STDMETHOD_(ULONG, Release)() ;

    // IEnumVARIANT methods
    STDMETHOD(Next)(ULONG cElements,
                    VARIANT FAR* pvar,
                    ULONG FAR* pcElementFetched) PURE;
    STDMETHOD(Skip)(ULONG cElements);
    STDMETHOD(Reset)();
    STDMETHOD(Clone)(IEnumVARIANT FAR* FAR* ppenum);

    CSampleDSEnumVariant();
    ~CSampleDSEnumVariant();

private:
    ULONG m_cRef;
};

#endif

