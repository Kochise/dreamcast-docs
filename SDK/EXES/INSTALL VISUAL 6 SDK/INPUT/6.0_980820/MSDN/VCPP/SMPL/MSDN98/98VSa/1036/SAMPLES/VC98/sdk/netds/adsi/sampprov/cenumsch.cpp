/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CEnumSch.cpp

Abstract:

    Sample Provider Enum Schema functionality

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSSchemaEnum::Create
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
//  History:    01-30-95   yihsins     Created.
//
//----------------------------------------------------------------------------
HRESULT
CSampleDSSchemaEnum::Create(
    CSampleDSSchemaEnum FAR* FAR* ppenumvariant,
    BSTR bstrSampleDSTreeName,
    BSTR bstrADsPath,
    BSTR bstrName,
    VARIANT var
    )
{
    HRESULT hr = S_OK;
    CSampleDSSchemaEnum FAR* penumvariant = NULL;

    *ppenumvariant = NULL;

    penumvariant = new CSampleDSSchemaEnum();
    if (!penumvariant)
    {
        hr = E_OUTOFMEMORY;
        BAIL_ON_FAILURE(hr);
    }

    hr = ProvAllocString( bstrSampleDSTreeName, &penumvariant->_bstrSampleDSTreeName);
    BAIL_ON_FAILURE(hr);
    hr = ProvAllocString( bstrADsPath, &penumvariant->_bstrADsPath);
    BAIL_ON_FAILURE(hr);
        
    hr = ProvAllocString( bstrName, &penumvariant->_bstrName);
    BAIL_ON_FAILURE(hr);

    hr = ObjectTypeList::CreateObjectTypeList(
            var,
            &penumvariant->_pObjList
            );
    BAIL_ON_FAILURE(hr);

    *ppenumvariant = penumvariant;

    RRETURN(hr);

error:

    delete penumvariant;

    RRETURN(hr);
}

CSampleDSSchemaEnum::CSampleDSSchemaEnum()
    : _bstrADsPath( NULL ),
      _bstrName( NULL ),
      _bstrSampleDSTreeName( NULL ),
      _pObjList( NULL )
{
    _lpClassDefs = NULL;
    _dwClassCurrent = 0;
    _dwClassReturned = 0;

    _lpAttrDefs = NULL;
    _dwAttrCurrent = 0;
    _dwAttrReturned = 0;

}

CSampleDSSchemaEnum::~CSampleDSSchemaEnum()
{
   ProvFreeString( _bstrName );
   ProvFreeString( _bstrADsPath );
   ProvFreeString( _bstrSampleDSTreeName );


   if ( _pObjList != NULL )
   {
       delete _pObjList;
       _pObjList = NULL;
   }
}

//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSSchemaEnum::Next
//
//  Synopsis:   Returns cElements number of requested NetOle objects in the
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
//  Modifies:
//
//  History:    11-3-95   yihsins     Created.
//
//----------------------------------------------------------------------------
STDMETHODIMP
CSampleDSSchemaEnum::Next(
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

    if ( pcElementFetched )
        *pcElementFetched = cElementFetched;

    RRETURN(hr);
}

HRESULT
CSampleDSSchemaEnum::EnumObjects(
    DWORD ObjectType,
    ULONG cElements,
    VARIANT FAR * pvar,
    ULONG FAR * pcElementFetched
    )
{
    switch (ObjectType)
    {
        case SampleDS_CLASS_ID:
            RRETURN (EnumClasses(cElements, pvar, pcElementFetched));
        
        case SampleDS_PROPERTY_ID:
            RRETURN (EnumProperties(cElements, pvar, pcElementFetched));

        default:
            RRETURN(S_FALSE);
    }
}

HRESULT
CSampleDSSchemaEnum::EnumObjects(
    ULONG cElements,
    VARIANT FAR* pvar,
    ULONG FAR* pcElementFetched
    )
{
    DWORD           i;
    ULONG           cRequested = 0;
    ULONG           cFetchedByPath = 0;
    ULONG           cTotalFetched = 0;
    VARIANT FAR*    pPathvar = pvar;
    HRESULT         hr;
    DWORD           ObjectType;

    for (i = 0; i < cElements; i++)
        VariantInit(&pvar[i]);

    cRequested = cElements;

    while (  SUCCEEDED( _pObjList->GetCurrentObject(&ObjectType))
          && ((hr = EnumObjects( ObjectType,
                                 cRequested,
                                 pPathvar,
                                 &cFetchedByPath)) == S_FALSE )
          )
    {
        pPathvar += cFetchedByPath;
        cRequested -= cFetchedByPath;
        cTotalFetched += cFetchedByPath;

        cFetchedByPath = 0;

        if ( FAILED(_pObjList->Next()) )
        {
            if ( pcElementFetched )
                *pcElementFetched = cTotalFetched;
            RRETURN(S_FALSE);
        }
    }

    if ( pcElementFetched )
        *pcElementFetched = cTotalFetched + cFetchedByPath;

    RRETURN(hr);
}

HRESULT
CSampleDSSchemaEnum::EnumClasses(
    ULONG cElements,
    VARIANT FAR* pvar,
    ULONG FAR* pcElementFetched
    )
{
    HRESULT hr = S_OK;
    DWORD i = 0;
    IDispatch *pDispatch = NULL;

    while ( i < cElements )
    {
        hr = GetClassObject(&pDispatch);
        if ( hr == S_FALSE )
            break;

        VariantInit( &pvar[i] );
        pvar[i].vt = VT_DISPATCH;
        pvar[i].pdispVal = pDispatch;
        (*pcElementFetched)++;
        i++;
    }

    RRETURN(hr);
}

HRESULT
CSampleDSSchemaEnum::GetClassObject(
    IDispatch ** ppDispatch
    )
{
    HRESULT hr = S_OK;
    LPSampleDS_CLASS_DEF lpCurrentObject = NULL;
    
    if (!_lpClassDefs) {
        _dwClassCurrent = 0;
        hr = SampleDSGetClassDefinition(&_lpClassDefs,
                                        &_dwClassReturned);
        BAIL_ON_FAILURE(hr);
    }

    if (_dwClassCurrent == _dwClassReturned) {
        goto error;
    }

    if (_dwClassCurrent < _dwClassReturned) {

        //
        // Now send back the current object
        //

        lpCurrentObject = _lpClassDefs + _dwClassCurrent;


        hr = CSampleDSClass::CreateClass(
                            _bstrADsPath,
                            lpCurrentObject->lpClassName,
                            lpCurrentObject,
                            ADS_OBJECT_BOUND,
                            IID_IDispatch,
                            (void **)ppDispatch
                            );
        BAIL_ON_FAILURE(hr);
        _dwClassCurrent++;

        RRETURN(S_OK);

    }

error:
    if (_lpClassDefs) {
        SampleDSFreeClassDefinition(_lpClassDefs,
                                    _dwClassReturned);
    }
    *ppDispatch = NULL;
    RRETURN(S_FALSE);
}

HRESULT
CSampleDSSchemaEnum::EnumProperties(
    ULONG cElements,
    VARIANT FAR* pvar,
    ULONG FAR* pcElementFetched
    )
{
    HRESULT hr = S_OK;
    DWORD i = 0;
    IDispatch *pDispatch = NULL;

    while ( i < cElements )
    {
        hr = GetPropertyObject(&pDispatch);
        if ( hr == S_FALSE )
            break;

        VariantInit( &pvar[i] );
        pvar[i].vt = VT_DISPATCH;
        pvar[i].pdispVal = pDispatch;
        (*pcElementFetched)++;
        i++;
    }

    RRETURN(hr);
}

HRESULT
CSampleDSSchemaEnum::GetPropertyObject(
    IDispatch ** ppDispatch
    )
{
    HRESULT hr = S_OK;
    
    LPSampleDS_ATTR_DEF lpCurrentObject = NULL;
    
    if (!_lpAttrDefs) {
        _dwAttrCurrent = 0;
        hr = SampleDSGetPropertyDefinition(&_lpAttrDefs,
                                           &_dwAttrReturned);
        BAIL_ON_FAILURE(hr);
    }

    if (_dwAttrCurrent == _dwAttrReturned) {
        goto error;
    }

    if (_dwAttrCurrent < _dwAttrReturned) {

        lpCurrentObject = _lpAttrDefs + _dwAttrCurrent;

        hr = CSampleDSProperty::CreateProperty(
                            _bstrADsPath,
                            lpCurrentObject->lpAttributeName,
                            lpCurrentObject,
                            ADS_OBJECT_BOUND,
                            IID_IDispatch,
                            (void **)ppDispatch
                            );
        BAIL_ON_FAILURE(hr);
        _dwAttrCurrent++;
        RRETURN(S_OK);
    }

error:
    if (_lpAttrDefs)
        SampleDSFreePropertyDefinition(_lpAttrDefs,
                                       _dwAttrReturned);
    *ppDispatch = NULL;
    RRETURN(S_FALSE);
}


