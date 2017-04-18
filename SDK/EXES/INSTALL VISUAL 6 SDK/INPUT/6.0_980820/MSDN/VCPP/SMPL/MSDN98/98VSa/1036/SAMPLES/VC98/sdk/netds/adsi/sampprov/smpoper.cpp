/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    SmpOper.cpp

Abstract:

    SampleDS DataType Operation routines 
    
Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop


HRESULT
SampleDSTypeFreeSampleDSSynId1(
    PSampleDSOBJECT lpSampleDSDestObject
    )
{
    HRESULT hr = S_OK;

    FreeProvStr(lpSampleDSDestObject->SampleDSValue.value_1.DNString);

    RRETURN(hr);
}

HRESULT
SampleDSTypeFreeSampleDSSynId2(
    PSampleDSOBJECT lpSampleDSDestObject
    )
{
    HRESULT hr = S_OK;

    //
    // Do nothing - Integer
    //

    RRETURN(hr);

}

HRESULT
SampleDSTypeClear(
    PSampleDSOBJECT lpSampleDSDestObject
    )
{
    HRESULT hr = S_OK;
    switch (lpSampleDSDestObject->SampleDSType) {
    case 1:
        hr = SampleDSTypeFreeSampleDSSynId1(
                lpSampleDSDestObject
                );
        break;
    case 2:
        hr = SampleDSTypeFreeSampleDSSynId2(
                lpSampleDSDestObject
                );
        break;


    default:
        hr = E_FAIL;
        break;
    }

    RRETURN(hr);
}

void
SampleDSTypeFreeSampleDSObjects(
    PSampleDSOBJECT pSampleDSObject,
    DWORD dwNumValues
    )
{
    DWORD i = 0;

    for (i = 0; i < dwNumValues; i++ ) {
         SampleDSTypeClear(pSampleDSObject + i);
    }

    FreeProvMem(pSampleDSObject);

    return;
}


HRESULT
SampleDSTypeCopySampleDSSynId1(
    PSampleDSOBJECT lpSampleDSSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    )
{
    HRESULT hr = S_OK;

    lpSampleDSDestObject->SampleDSType = lpSampleDSSrcObject->SampleDSType;

    lpSampleDSDestObject->SampleDSValue.value_1.DNString =
                    (LPWSTR)AllocProvStr(
                            lpSampleDSSrcObject->SampleDSValue.value_1.DNString
                            );
    RRETURN(hr);
}

HRESULT
SampleDSTypeCopySampleDSSynId2(
    PSampleDSOBJECT lpSampleDSSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    )
{
    HRESULT hr = S_OK;

    lpSampleDSDestObject->SampleDSType = lpSampleDSSrcObject->SampleDSType;


    lpSampleDSDestObject->SampleDSValue.value_2.Integer =
                        lpSampleDSSrcObject->SampleDSValue.value_2.Integer;

    RRETURN(hr);

}

HRESULT
SampleDSTypeCopy(
    PSampleDSOBJECT lpSampleDSSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    )
{
    HRESULT hr = S_OK;
    switch (lpSampleDSSrcObject->SampleDSType) {
    case 1:
        hr = SampleDSTypeCopySampleDSSynId1(
                lpSampleDSSrcObject,
                lpSampleDSDestObject
                );
        break;
    case 2:
        hr = SampleDSTypeCopySampleDSSynId2(
                lpSampleDSSrcObject,
                lpSampleDSDestObject
                );
        break;


    default:
        hr = E_FAIL;
        break;
    }

    RRETURN(hr);
}



HRESULT
SampleDSTypeCopyConstruct(
    LPSampleDSOBJECT pSampleDSSrcObjects,
    DWORD dwNumObjects,
    LPSampleDSOBJECT * ppSampleDSDestObjects
    )
{

    DWORD i = 0;
    LPSampleDSOBJECT pSampleDSDestObjects = NULL;
    HRESULT hr = S_OK;

    pSampleDSDestObjects = (LPSampleDSOBJECT)AllocProvMem(
                                    dwNumObjects * sizeof(SampleDSOBJECT)
                                    );

    if (!pSampleDSDestObjects) {
        RRETURN(E_FAIL);
    }

     for (i = 0; i < dwNumObjects; i++ ) {
         hr = SampleDSTypeCopy(pSampleDSSrcObjects + i, 
                               pSampleDSDestObjects + i
                               );
     }

     *ppSampleDSDestObjects = pSampleDSDestObjects;

     RRETURN(S_OK);

}

HRESULT
UnMarshallSampleDSToSampleDSSynId(
    DWORD dwSyntaxId,
    DWORD dwNumValues,
    LPBYTE lpValue,
    PSampleDSOBJECT * ppSampleDSObject
    )
{
    LPBYTE lpByte = lpValue;
    DWORD  i = 0;
    PSampleDSOBJECT pSampleDSObject = NULL;

    pSampleDSObject = (PSampleDSOBJECT)AllocProvMem(
                            dwNumValues * sizeof(SampleDSOBJECT)
                            );

    if (!pSampleDSObject) {
        RRETURN(E_FAIL);
    }


    for (i = 0; i < dwNumValues; i++) {

        lpByte = CopySampleDSToSampleDSSynId(
                         dwSyntaxId,
                         lpByte,
                         (pSampleDSObject + i)
                         );

    }

    *ppSampleDSObject = pSampleDSObject;

    RRETURN(S_OK);
}

LPBYTE
CopySampleDS1ToSampleDSSynId1(
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    )
{
    LPSampleDS_TYPE_1 lpData_1 = (LPSampleDS_TYPE_1) lpByte;

    lpSampleDSObject->SampleDSType = 1;

    lpSampleDSObject->SampleDSValue.value_1.DNString =
                    (LPWSTR)AllocProvStr(lpData_1->DNString);

    lpByte = (LPBYTE ) lpData_1 + sizeof(SampleDS_TYPE_1);

    return(lpByte);
}
       
LPBYTE
CopySampleDS2ToSampleDSSynId2(
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    )

{
    LPSampleDS_TYPE_2 lpData_2 = (LPSampleDS_TYPE_2) lpByte;

    lpSampleDSObject->SampleDSType = 2;

    lpSampleDSObject->SampleDSValue.value_2.Integer = lpData_2->Integer;

    lpByte = (LPBYTE ) lpData_2 + sizeof(SampleDS_TYPE_2);

    return(lpByte);
}

LPBYTE
CopySampleDSToSampleDSSynId(
    DWORD dwSyntaxId,
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    )
{
    switch (dwSyntaxId) {
    case 1:
        lpByte = CopySampleDS1ToSampleDSSynId1(
                         lpByte,
                         lpSampleDSObject
                         );
        break;
    case 2:
        lpByte = CopySampleDS2ToSampleDSSynId2(
                         lpByte,
                         lpSampleDSObject
                         );
        break;

    default:
        break;

    }

    return(lpByte);
}

HRESULT
MarshallSampleDSSynIdToSampleDS(
    DWORD dwSyntaxId,
    PSampleDSOBJECT pSampleDSObject,
    DWORD dwNumValues,
    LPBYTE lpValue
    )
{

    DWORD  i = 0;


    for (i = 0; i < dwNumValues; i++) {

        lpValue = CopySampleDSSynIdToSampleDS(
                         dwSyntaxId,
                         lpValue,
                         (pSampleDSObject + i)
                         );

    }

    RRETURN(S_OK);
}

LPBYTE
CopySampleDSSynId1ToSampleDS1(
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    )
{
    LPSampleDS_TYPE_1 lpData_1 = (LPSampleDS_TYPE_1) lpByte;

    lpData_1->DNString =
                (LPWSTR)AllocProvStr(
                        lpSampleDSObject->SampleDSValue.value_1.DNString
                        );

    lpByte = (LPBYTE ) lpData_1 + sizeof(SampleDS_TYPE_1);

    return(lpByte);

}

LPBYTE
CopySampleDSSynId2ToSampleDS2(
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    )

{
    LPSampleDS_TYPE_2 lpData_2 = (LPSampleDS_TYPE_2) lpByte;


    lpData_2->Integer = lpSampleDSObject->SampleDSValue.value_2.Integer;

    lpByte = (LPBYTE ) lpData_2 + sizeof(SampleDS_TYPE_2);

    return(lpByte);
}


LPBYTE
CopySampleDSSynIdToSampleDS(
    DWORD dwSyntaxId,
    LPBYTE lpByte,
    PSampleDSOBJECT lpSampleDSObject
    )
{
    switch (dwSyntaxId) {
    case 1:
        lpByte = CopySampleDSSynId1ToSampleDS1(
                         lpByte,
                         lpSampleDSObject
                         );
        break;

    case 2:
        lpByte = CopySampleDSSynId2ToSampleDS2(
                         lpByte,
                         lpSampleDSObject
                         );
        break;

    default:
        break;

    }

    return(lpByte);
}


void
VarTypeFreeVarObjects(
    VARIANT *pVarObject,
    DWORD dwNumValues
    )
{
    DWORD i = 0;

    for (i = 0; i < dwNumValues; i++ ) {
         VariantClear(pVarObject + i);
    }

    FreeProvMem(pVarObject);

    return;
}


HRESULT
SampleDSTypeToVarTypeCopySampleDSSynId1(
    PSampleDSOBJECT lpSampleDSSrcObject,
    VARIANT *lpVarDestObject
    )
{
    HRESULT hr = S_OK;

    lpVarDestObject->vt = VT_BSTR;

    hr = ProvAllocString(
            lpSampleDSSrcObject->SampleDSValue.value_1.DNString,
            &(lpVarDestObject->bstrVal)
            );

    RRETURN(hr);
}

HRESULT
SampleDSTypeToVarTypeCopySampleDSSynId2(
    PSampleDSOBJECT lpSampleDSSrcObject,
    PVARIANT lpVarDestObject
    )
{
    HRESULT hr = S_OK;

    lpVarDestObject->vt = VT_I4;

    lpVarDestObject->lVal =
                lpSampleDSSrcObject->SampleDSValue.value_2.Integer;

    RRETURN(hr);

}


HRESULT
SampleDSTypeToVarTypeCopy(
    PSampleDSOBJECT lpSampleDSSrcObject,
    VARIANT* lpVarDestObject
    )
{
    HRESULT hr = S_OK;
    switch (lpSampleDSSrcObject->SampleDSType) {
    case 1:
        hr = SampleDSTypeToVarTypeCopySampleDSSynId1(
                lpSampleDSSrcObject,
                lpVarDestObject
                );
        break;
    case 2:
        hr = SampleDSTypeToVarTypeCopySampleDSSynId2(
                lpSampleDSSrcObject,
                lpVarDestObject
                );
        break;


    default:
        hr = E_FAIL;
        break;
    }

    RRETURN(hr);
}

HRESULT
SampleDSTypeToVarTypeCopyConstruct(
    LPSampleDSOBJECT pSampleDSSrcObjects,
    DWORD dwNumObjects,
    VARIANT *pVarDestObjects
    )
{
    long i = 0;
    HRESULT hr = S_OK;

    VariantInit(pVarDestObjects);

    if ( dwNumObjects == 1 )
    {
        hr = SampleDSTypeToVarTypeCopy( pSampleDSSrcObjects,
                                   pVarDestObjects );

        RRETURN(hr);
    }

    //
    // The following are for handling are multi-value properties
    //

    SAFEARRAY *aList = NULL;
    SAFEARRAYBOUND aBound;

    aBound.lLbound = 0;
    aBound.cElements = dwNumObjects;

    aList = SafeArrayCreate( VT_VARIANT, 1, &aBound );

    if ( aList == NULL )
    {
        hr = E_OUTOFMEMORY;
        BAIL_ON_FAILURE(hr);
    }

    for ( i = 0; i < (long) dwNumObjects; i++ )
    {
        VARIANT v;

        VariantInit(&v);
        hr = SampleDSTypeToVarTypeCopy( pSampleDSSrcObjects + i,
                                   &v );
        BAIL_ON_FAILURE(hr);

        hr = SafeArrayPutElement( aList, &i, &v );
        BAIL_ON_FAILURE(hr);
    }

    V_VT(pVarDestObjects) = VT_ARRAY | VT_VARIANT;
    V_ARRAY(pVarDestObjects) = aList;

    RRETURN(S_OK);

error:

    if ( aList )
        SafeArrayDestroy( aList );

    RRETURN(hr);
}

HRESULT
VarTypeToSampleDSTypeCopySampleDSSynId1(
    PVARIANT lpVarSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    )
{
    HRESULT hr = S_OK;

    if(lpVarSrcObject->vt != VT_BSTR){
        RRETURN(hr = E_ADS_CANT_CONVERT_DATATYPE);
    }

    lpSampleDSDestObject->SampleDSType = 1;

    lpSampleDSDestObject->SampleDSValue.value_1.DNString =
                        AllocProvStr(
                            lpVarSrcObject->bstrVal
                        );

    RRETURN(hr);
}

HRESULT
VarTypeToSampleDSTypeCopySampleDSSynId2(
    PVARIANT lpVarSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    )
{
    HRESULT hr = S_OK;

    if(lpVarSrcObject->vt != VT_I4){
        RRETURN(hr = E_ADS_CANT_CONVERT_DATATYPE);
    }

    lpSampleDSDestObject->SampleDSType = 2;

    lpSampleDSDestObject->SampleDSValue.value_2.Integer =
                        lpVarSrcObject->lVal;

    RRETURN(hr);
}

HRESULT
VarTypeToSampleDSTypeCopy(
    DWORD dwSampleDSType,
    PVARIANT lpVarSrcObject,
    PSampleDSOBJECT lpSampleDSDestObject
    )
{
    HRESULT hr = S_OK;
    switch (dwSampleDSType){
    case 1:
        hr = VarTypeToSampleDSTypeCopySampleDSSynId1(
                lpVarSrcObject,
                lpSampleDSDestObject
                );
        break;

    case 2:
        hr = VarTypeToSampleDSTypeCopySampleDSSynId2(
                lpVarSrcObject,
                lpSampleDSDestObject
                );
        break;
    default:
        hr = E_FAIL;
        break;
    }

    RRETURN(hr);
}



HRESULT
VarTypeToSampleDSTypeCopyConstruct(
    DWORD dwSampleDSType,
    LPVARIANT pVarSrcObjects,
    DWORD dwNumObjects,
    LPSampleDSOBJECT * ppSampleDSDestObjects
    )
{

    DWORD i = 0;
    LPSampleDSOBJECT pSampleDSDestObjects = NULL;
    HRESULT hr = S_OK;

    pSampleDSDestObjects = (LPSampleDSOBJECT)AllocProvMem(
                                    dwNumObjects * sizeof(SampleDSOBJECT)
                                    );

    if (!pSampleDSDestObjects) {
        RRETURN(E_FAIL);
    }

     for (i = 0; i < dwNumObjects; i++ ) {
         hr = VarTypeToSampleDSTypeCopy(
                    dwSampleDSType,
                    pVarSrcObjects + i,
                    pSampleDSDestObjects + i
                    );
         BAIL_ON_FAILURE(hr);

     }

     *ppSampleDSDestObjects = pSampleDSDestObjects;

     RRETURN(S_OK);

error:

     if (pSampleDSDestObjects) {

        SampleDSTypeFreeSampleDSObjects(
                pSampleDSDestObjects,
                dwNumObjects
                );
     }

     *ppSampleDSDestObjects = NULL;

     RRETURN(hr);
}



