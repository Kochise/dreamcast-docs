/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CEnumVar.cpp

Abstract:

    Base Implementation for xxxEnumVariant derived classes

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSEnumVariant::CSampleDSEnumVariant
//
//  Synopsis:
//
//
//  Arguments:
//
//
//  Returns:
//
//  Modifies:
//
//----------------------------------------------------------------------------
CSampleDSEnumVariant::CSampleDSEnumVariant()
{
    //
    // Set the reference count on the enumerator.
    //
    m_cRef = 1;

}

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSEnumVariant::~CSampleDSEnumVariant
//
//  Synopsis:
//
//
//  Arguments:
//
//  Returns:
//
//  Modifies:
//
//----------------------------------------------------------------------------
CSampleDSEnumVariant::~CSampleDSEnumVariant()
{
    //
    // Bump down the reference count on the Collection object
    //
}

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSEnumVariant::QueryInterface
//
//  Synopsis:
//
//  Arguments:  [iid]
//              [ppv]
//
//  Returns:    HRESULT
//
//  Modifies:
//
//----------------------------------------------------------------------------
STDMETHODIMP
CSampleDSEnumVariant::QueryInterface(REFIID iid, void FAR* FAR* ppv)
{
    *ppv = NULL;

    if (iid == IID_IUnknown || iid == IID_IEnumVARIANT) {

        *ppv = this;

    }
    else {

        return ResultFromScode(E_NOINTERFACE);
    }

    AddRef();
    return NOERROR;
}


//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSEnumVariant::AddRef
//
//  Synopsis:
//
//  Arguments:
//
//  Returns:    HRESULT
//
//  Modifies:
//
//----------------------------------------------------------------------------
STDMETHODIMP_(ULONG)
CSampleDSEnumVariant::AddRef(void)
{

    return ++m_cRef;
}


//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSEnumVariant::Release
//
//  Synopsis:
//
//
//  Arguments:  [void]
//
//  Returns:
//
//  Modifies:
//
//----------------------------------------------------------------------------
STDMETHODIMP_(ULONG)
CSampleDSEnumVariant::Release(void)
{


    if(--m_cRef == 0){

        delete this;
        return 0;
    }

    return m_cRef;
}


//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSEnumVariant::Skip
//
//  Synopsis:
//
//  Arguments:  [cElements]
//
//  Returns:    HRESULT
//
//  Modifies:
//
//----------------------------------------------------------------------------
STDMETHODIMP
CSampleDSEnumVariant::Skip(ULONG cElements)
{

    RRETURN(ResultFromScode(E_FAIL));

}

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSEnumVariant::Reset
//
//  Synopsis:
//
//  Arguments:  []
//
//  Returns:    HRESULT
//
//  Modifies:
//
//----------------------------------------------------------------------------
STDMETHODIMP
CSampleDSEnumVariant::Reset()
{

    RRETURN(ResultFromScode(S_OK));
}


//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSEnumVariant::Clone
//
//  Synopsis:
//
//  Arguments:  [pCollection]
//              [ppEnumVariant]
//
//  Returns:    HRESULT
//
//  Modifies:
//
//----------------------------------------------------------------------------
STDMETHODIMP
CSampleDSEnumVariant::Clone(IEnumVARIANT FAR* FAR* ppenum)
{
    RRETURN(ResultFromScode(E_FAIL));
}
