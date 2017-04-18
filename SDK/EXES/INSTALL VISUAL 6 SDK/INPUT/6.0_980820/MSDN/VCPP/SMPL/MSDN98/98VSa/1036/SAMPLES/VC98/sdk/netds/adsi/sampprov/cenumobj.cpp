/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CEnumObj.c

Abstract:

    Generic Object Enumeration CodeStandard IClassFactory implementation

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop


//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSEnumVariant::Create
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
//  History:    
//
//----------------------------------------------------------------------------
HRESULT
CSampleDSGenObjectEnum::Create(
    CSampleDSGenObjectEnum FAR* FAR* ppenumvariant,
    BSTR ADsPath,
    VARIANT var
    )
{
    HRESULT hr = NOERROR;
    CSampleDSGenObjectEnum FAR* penumvariant = NULL;
    WCHAR szDSPath[MAX_PATH];
    DWORD dwModificationTime = 0L;
    DWORD dwNumberOfEntries = 0L;
    DWORD dwStatus = 0L;

    *ppenumvariant = NULL;

    penumvariant = new CSampleDSGenObjectEnum();
    if (!penumvariant) {
        hr = E_OUTOFMEMORY;
        BAIL_ON_FAILURE(hr);
    }

    hr = xx_put_BSTR(&penumvariant->_ADsPath, ADsPath);
    BAIL_ON_FAILURE(hr);

    hr = BuildDSFilterArray(
                var,
                (LPBYTE *)&penumvariant->_pDSFilterList
                );
    if (FAILED(hr)) {
        penumvariant->_pDSFilterList = NULL;
    }

    *ppenumvariant = penumvariant;

    hr = BuildDSPathFromADsPath(
                ADsPath,
                szDSPath
                );
    BAIL_ON_FAILURE(hr);

    hr = SampleDSOpenObject(
                    szDSPath,
                    &penumvariant->_hObject,
                    NULL,
                    REG_DS
                    );
    BAIL_ON_FAILURE(hr);

    hr = SampleDSRDNEnum( 
                 &penumvariant->_hEnum, 
                 penumvariant->_hObject
                 );
    
    RRETURN(hr);

error:
    if (penumvariant->_hObject) {
        SampleDSCloseObject(penumvariant->_hObject);
    }
    
    delete penumvariant;

    RRETURN(hr);
}

CSampleDSGenObjectEnum::CSampleDSGenObjectEnum():
                    _ADsPath(NULL)
{
    _pObjList = NULL;
    _dwObjectReturned = 0;
    _dwObjectCurrentEntry = 0;
    _dwObjectTotal = 0;
    _hObject = NULL;
    _hEnum = NULL;
    _lpObjects = NULL;
    _pDSFilterList = NULL;

    _bNoMore = FALSE;
}


CSampleDSGenObjectEnum::~CSampleDSGenObjectEnum()
{
    if (_pDSFilterList) {
        FreeFilterList((LPBYTE)_pDSFilterList);
    }
}

HRESULT
CSampleDSGenObjectEnum::EnumObjects(
    DWORD ObjectType,
    ULONG cElements,
    VARIANT FAR * pvar,
    ULONG FAR * pcElementFetched
    )
{

    //
    // Multi-level detection of Objects may not be necessary for DS code
    //

    RRETURN(EnumGenericObjects(cElements, pvar, pcElementFetched));

}
HRESULT
CSampleDSGenObjectEnum::EnumGenericObjects(
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
// Load IDispatch pointers of Next cElements Filtered Objects into pvar array
//
HRESULT
CSampleDSGenObjectEnum::FetchObjects(

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
//  Synopsis:   Gets IDispatch pointer of next object in namespace subject to
//                              filter.
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
CSampleDSGenObjectEnum::FetchNextObject(
    IDispatch ** ppDispatch
    )
 {
    HRESULT hr;
    LPTSTR lpszObjectRDN=NULL ;
    LPTSTR lpszObjectClass = 0;
    DWORD dwClassId = 0;
    IADs * pADs = NULL;
    *ppDispatch = NULL;

    hr = S_OK;
    while (hr == S_OK){
        hr=SampleDSNextRDN(_hEnum,
                           &lpszObjectRDN,
                           &lpszObjectClass
                           );    
        if (S_OK==hr && 
            S_OK==IsValidDSFilter(lpszObjectClass)) {
            break;
        }
    }

    //
    // Now create and send back the current object
    //
    if (hr == S_OK) {
        hr = CSampleDSGenObject::CreateGenericObject(_ADsPath,
                                                     lpszObjectRDN,
                                                     lpszObjectClass,
                                                     ADS_OBJECT_BOUND,
                                                     IID_IDispatch,
                                                     (void **)ppDispatch
                                                     );
        BAIL_ON_FAILURE(hr);
    }
    else {
        if (_hEnum) {
            SampleDSFreeEnum(_hEnum);
            _hEnum = NULL;
        }
    }

error:

    //
    // Free the intermediate pADs pointer.
    //
    if (pADs) {
        pADs->Release();
    }
    if (lpszObjectRDN)
        FreeProvMem(lpszObjectRDN);
    if (lpszObjectClass)
        FreeProvMem(lpszObjectClass);
    RRETURN_ENUM_STATUS(hr); 
}


//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSGenObjectEnum::Next
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
//
//----------------------------------------------------------------------------
STDMETHODIMP
CSampleDSGenObjectEnum::Next(
    ULONG cElements,
    VARIANT FAR* pvar,
    ULONG FAR* pcElementFetched
    )
{
    ULONG cElementFetched = 0;
    HRESULT hr = S_OK;

    hr = EnumGenericObjects(
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
CSampleDSGenObjectEnum::IsValidDSFilter(LPWSTR ObjectName){

    if (_pDSFilterList){
                for (DWORD i = 0; i < _pDSFilterList->dwNumberOfFilters; i++) {

                        if ( !_wcsicmp(ObjectName,_pDSFilterList->Filters[i].lpObjectClass) ) {
                                RRETURN(S_OK);
                        }
                }
                RRETURN(E_FAIL);
    }
    RRETURN(S_OK);
}

HRESULT
BuildDSFilterArray(
    VARIANT var,
    LPBYTE * ppContigFilter
    )
{
    LONG uDestCount = 0;
    LONG dwSLBound = 0;
    LONG dwSUBound = 0;
    VARIANT v;
    LONG i;
    HRESULT hr = S_OK;

    LPDS_FILTER_LIST pDsFilterList = NULL;
    LPBYTE pContigFilter = NULL;

    if(!((V_VT(&var) &  VT_VARIANT) &&  V_ISARRAY(&var))) {
        RRETURN(E_FAIL);
    }

    //
    // Check that there is only one dimension in this array
    //

    if ((V_ARRAY(&var))->cDims != 1) {
        hr = E_FAIL;
        BAIL_ON_FAILURE(hr);
    }
    //
    // Check that there is atleast one element in this array
    //

    if ((V_ARRAY(&var))->rgsabound[0].cElements == 0){
        hr = E_FAIL;
        BAIL_ON_FAILURE(hr);
    }

    //
    // We know that this is a valid single dimension array
    //

    hr = SafeArrayGetLBound(V_ARRAY(&var),
                            1,
                            (long FAR *)&dwSLBound
                            );
    BAIL_ON_FAILURE(hr);

    hr = SafeArrayGetUBound(V_ARRAY(&var),
                            1,
                            (long FAR *)&dwSUBound
                            );
    BAIL_ON_FAILURE(hr);


    pContigFilter = (LPBYTE)AllocProvMem(
                            sizeof(DS_FILTER_LIST)
                            - sizeof(DS_FILTER)
                            );
    if (!pContigFilter) {

        hr = E_FAIL;
        BAIL_ON_FAILURE(hr);
    }


    for (i = dwSLBound; i <= dwSUBound; i++) {
        VariantInit(&v);
        hr = SafeArrayGetElement(V_ARRAY(&var),
                                (long FAR *)&i,
                                &v
                                );
        if (FAILED(hr)) {
            continue;
        }

        //
        //  Create an entry in the filter block
        //  Append it to the existing block
        //

        pContigFilter = CreateAndAppendFilterEntry(
                            pContigFilter,
                            V_BSTR(&v)
                            );
        if (!pContigFilter) {

            hr = E_FAIL;
            BAIL_ON_FAILURE(hr);
        }

    }

    pDsFilterList = (LPDS_FILTER_LIST)pContigFilter;

    if (!pDsFilterList->dwNumberOfFilters){

        hr = E_FAIL;
        BAIL_ON_FAILURE(hr);
    }

    *ppContigFilter = pContigFilter;

    RRETURN(S_OK);

error:

    if (pContigFilter){

        FreeFilterList(
               pContigFilter
               );

    }

    *ppContigFilter = NULL;

    RRETURN(hr);
}

LPBYTE
CreateAndAppendFilterEntry(
    LPBYTE pContigFilter,
    LPWSTR lpObjectClass
    )
{
    LPWSTR pszFilter = NULL;
    LPDS_FILTER_LIST pDsFilterList = NULL;
    DWORD dwFilterCount = 0;
    LPBYTE pNewContigFilter = NULL;
    LPDS_FILTER pNewEntry = NULL;


    pszFilter = (LPWSTR)AllocProvStr(lpObjectClass);
    if (!pszFilter) {
        return(pContigFilter);
    }

    pDsFilterList = (LPDS_FILTER_LIST)pContigFilter;

    dwFilterCount = pDsFilterList->dwNumberOfFilters;

    pNewContigFilter = (LPBYTE)ReallocProvMem(
                                    pContigFilter,

                                    sizeof(DS_FILTER_LIST) +
                                    (dwFilterCount - 1)* sizeof(DS_FILTER),

                                    sizeof(DS_FILTER_LIST)
                                    + dwFilterCount * sizeof(DS_FILTER)
                                    );
    if (!pNewContigFilter) {
        return(pContigFilter);
    }

    pNewEntry = (LPDS_FILTER)(pNewContigFilter + sizeof(DS_FILTER_LIST)
                        + (dwFilterCount - 1)* sizeof(DS_FILTER));

    pNewEntry->lpObjectClass = pszFilter;

    pDsFilterList = (LPDS_FILTER_LIST)pNewContigFilter;

    pDsFilterList->dwNumberOfFilters = dwFilterCount + 1;

    return(pNewContigFilter);
}

void
FreeFilterList(
    LPBYTE lpContigFilter
    )
{
    LPDS_FILTER_LIST lpDsFilterList = (LPDS_FILTER_LIST)lpContigFilter;
    DWORD dwNumFilters = 0;
    LPDS_FILTER lpDsFilter = NULL;
    DWORD i = 0;

    dwNumFilters = lpDsFilterList->dwNumberOfFilters;

    if (dwNumFilters){

        lpDsFilter = (LPDS_FILTER)(lpContigFilter  + sizeof(DS_FILTER_LIST)
                                      - sizeof(DS_FILTER));

        for (i = 0; i < dwNumFilters; i++) {

            FreeProvStr((lpDsFilter + i)->lpObjectClass);
        }

    }

    FreeProvMem(lpContigFilter);
}


