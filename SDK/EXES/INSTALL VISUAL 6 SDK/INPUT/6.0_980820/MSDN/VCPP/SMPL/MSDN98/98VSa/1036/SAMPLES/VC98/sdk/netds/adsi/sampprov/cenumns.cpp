/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CEnumNS.c

Abstract:

    Sample Provider Namespace Enumerator Code

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

#define ENUM_BUFFER_SIZE (1024 * 16)

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSNamespaceEnum::Create
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
HRESULT
CSampleDSNamespaceEnum::Create(
    CSampleDSNamespaceEnum FAR* FAR* ppenumvariant,
    VARIANT var
    )
{
    HRESULT hr = S_OK;
    CSampleDSNamespaceEnum FAR* penumvariant = NULL;

    penumvariant = new CSampleDSNamespaceEnum();

    if (penumvariant == NULL){
        hr = E_OUTOFMEMORY;
        BAIL_ON_FAILURE(hr);
    }

    hr = SampleDSRDNEnum( 
                     &penumvariant->_hEnum, 
                     NULL
                     );
    BAIL_ON_FAILURE(hr);

    hr = ObjectTypeList::CreateObjectTypeList(
                                        var,
                                        &penumvariant->_pObjList
                                        );
    BAIL_ON_FAILURE(hr);

    *ppenumvariant = penumvariant;
    RRETURN(hr);

error:
    if (penumvariant) {
        delete penumvariant;
    }
    RRETURN(hr);
}

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSNamespaceEnum::CSampleDSNamespaceEnum
//
//  Synopsis:
//
//
//  Arguments:
//
//
//  Returns:
//
//----------------------------------------------------------------------------
CSampleDSNamespaceEnum::CSampleDSNamespaceEnum()
{
    _pObjList = NULL;
    _dwEntriesRead = 0;
    _dwCurrentEntry = 0;
    _hEnum = NULL;
    _pBuffer = NULL;
}

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSNamespaceEnum::~CSampleDSNamespaceEnum
//
//  Synopsis:
//
//
//  Arguments:
//
//  Returns:
//
//----------------------------------------------------------------------------
CSampleDSNamespaceEnum::~CSampleDSNamespaceEnum()
{
    if (_pBuffer)
        FreeProvMem(_pBuffer);
}

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSNamespaceEnum::Next
//
//  Synopsis:   Returns cElements number of requested ADs objects in the
//              array supplied in pvar.
//
//  Arguments:  [cElements] -- The number of elements requested by client
//              [pvar] -- ptr to array of VARIANTs to for return objects
//              [pcElementFetched] -- if non-NULL, then number of elements
//                                 -- actually returned is placed here
//
//  Returns:    HRESULT -- S_OK if number of elements requested are returned
//                      -- S_FALSE if number of elements is < requested
//
//----------------------------------------------------------------------------
STDMETHODIMP
CSampleDSNamespaceEnum::Next(
    ULONG cElements,
    VARIANT FAR* pvar,
    ULONG FAR* pcElementFetched
    )
{
    ULONG cElementFetched = 0;
    HRESULT hr = S_OK;

    hr = EnumObjects(
            cElements,
            pvar,
            &cElementFetched
            );

    if (pcElementFetched) {
        *pcElementFetched = cElementFetched;
    }
    RRETURN(hr);
}


HRESULT
CSampleDSNamespaceEnum::EnumObjects(
    ULONG cElements,
    VARIANT FAR* pvar,
    ULONG FAR* pcElementFetched
    )
{
    DWORD           i;
    ULONG           cRequested = 0;
    ULONG           cTotalFetched = 0;
    HRESULT         hr;

    for (i = 0; i < cElements; i++)  {
        VariantInit(&pvar[i]);
    }
    cRequested = cElements;

        hr = FetchObjects(cElements, pvar, &cTotalFetched);
   
    if (pcElementFetched) {
        *pcElementFetched = cTotalFetched;
    }

    RRETURN(hr);
}

//
// Load IDispatch pointers of Next cElements Root Objects into pvar array
//
HRESULT
CSampleDSNamespaceEnum::FetchObjects(

    ULONG cElements,
    VARIANT FAR* pvar,
    ULONG FAR* pcElementFetched
    )
{
    HRESULT hr;
    IDispatch *pDispatch = NULL;
    DWORD i = 0;

    while (i < cElements) {

        hr = FetchNextObject(&pDispatch);
        if (hr == S_FALSE) {
            break;
        }

        VariantInit(&pvar[i]);
        pvar[i].vt = VT_DISPATCH;
        pvar[i].pdispVal = pDispatch;
        (*pcElementFetched)++;
        i++;
    }
    return(hr);
}


//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSNamespaceEnum::FetchNextObject
//
//  Synopsis:   Gets IDispatch pointer of next object in namespace.
//
//  Arguments:  [ppDispatch] -- Pointer to where to return IDispatch pointer.
//
//  Returns:    HRESULT -- S_OK if got the next object
//                      -- S_FALSE if not
//
//  Modifies:   [*ppDispatch]
//
//----------------------------------------------------------------------------
HRESULT
CSampleDSNamespaceEnum::FetchNextObject(
    IDispatch ** ppDispatch
    )
{
    HRESULT hr;
    LPTSTR lpRootRDN=NULL ;
    LPTSTR lpClassName=NULL ;
    *ppDispatch = NULL;

    hr = SampleDSNextRDN(_hEnum,
                         &lpRootRDN,
                         &lpClassName 
                         );    

    if (hr != S_OK) {
        if (_hEnum) {
            SampleDSFreeEnum(_hEnum);
            _hEnum = NULL;
        }
        goto error;
    }

    hr = CSampleDSGenObject::CreateGenericObject(
                                         L"Sample:",
                                        lpRootRDN,
                                        lpClassName,
                                        ADS_OBJECT_BOUND,
                                        IID_IDispatch,
                                        (void **)ppDispatch
                                        );
error:
    if (lpClassName)
        FreeProvMem(lpClassName);  
    if (lpRootRDN)
        FreeProvMem(lpRootRDN);  
    RRETURN_ENUM_STATUS(hr); 
}


