/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    Pack.cpp

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop

HRESULT
PackStringinVariant(
    BSTR bstrString,
    VARIANT * pvarInputData
    )
{
    HRESULT hr = S_OK;

    if ( bstrString == NULL )
        RRETURN(E_FAIL);

    VariantInit(pvarInputData);

    pvarInputData->vt = VT_BSTR;

    if (!bstrString) {
        V_BSTR(pvarInputData) = NULL;
        RRETURN(S_OK);
    }

    hr = ProvAllocString(bstrString, &(V_BSTR(pvarInputData)));

    RRETURN(hr);
}


HRESULT
UnpackStringfromVariant(
    VARIANT varSrcData,
    BSTR * pbstrDestString
    )
{
    HRESULT hr = S_OK;

    if( varSrcData.vt != VT_BSTR){
        RRETURN(E_ADS_CANT_CONVERT_DATATYPE);
    }

    if (!V_BSTR(&varSrcData)) {
        *pbstrDestString = NULL;
        RRETURN(S_OK);
    }

    hr = ProvAllocString(V_BSTR(&varSrcData), pbstrDestString);

    RRETURN(hr);
}


HRESULT
PackLONGinVariant(
    LONG  lValue,
    VARIANT * pvarInputData
    )
{
    VariantInit(pvarInputData);

    pvarInputData->vt = VT_I4;
    V_I4(pvarInputData) = lValue;

    RRETURN(S_OK);
}

HRESULT
UnpackLONGfromVariant(
    VARIANT varSrcData,
    LONG * plValue
    )
{
    if( varSrcData.vt != VT_I4){
        RRETURN(E_ADS_CANT_CONVERT_DATATYPE);
    }

    *plValue = V_I4(&varSrcData);

    RRETURN(S_OK);
}


HRESULT
PackDATEinVariant(
    DATE  daValue,
    VARIANT * pvarInputData
    )
{
    VariantInit(pvarInputData);

    pvarInputData->vt = VT_DATE;
    V_DATE(pvarInputData) = daValue;

    RRETURN(S_OK);
}

HRESULT
UnpackDATEfromVariant(
    VARIANT varSrcData,
    DATE * pdaValue
    )
{
    if( varSrcData.vt != VT_DATE){
        RRETURN(E_ADS_CANT_CONVERT_DATATYPE);
    }

    *pdaValue = V_DATE(&varSrcData);

    RRETURN(S_OK);
}


HRESULT
PackVARIANT_BOOLinVariant(
    VARIANT_BOOL  fValue,
    VARIANT * pvarInputData
    )
{
    VariantInit(pvarInputData);

    pvarInputData->vt = VT_BOOL;
    V_BOOL(pvarInputData) = fValue;

    RRETURN(S_OK);
}

HRESULT
UnpackVARIANT_BOOLfromVariant(
    VARIANT varSrcData,
    VARIANT_BOOL * pfValue
    )
{
    if( varSrcData.vt != VT_BOOL){
        RRETURN(E_ADS_CANT_CONVERT_DATATYPE);
    }

    *pfValue = V_BOOL(&varSrcData);

    RRETURN(S_OK);
}


HRESULT
PackVARIANTinVariant(
    VARIANT vaValue,
    VARIANT * pvarInputData
    )
{
    VariantInit(pvarInputData);

    pvarInputData->vt = VT_VARIANT;
    RRETURN( VariantCopy( pvarInputData, &vaValue ));
}

HRESULT
UnpackVARIANTfromVariant(
    VARIANT varSrcData,
    VARIANT * pvaValue
    )
{
    VariantInit( pvaValue );

    RRETURN( VariantCopy( pvaValue, &varSrcData ));
}





