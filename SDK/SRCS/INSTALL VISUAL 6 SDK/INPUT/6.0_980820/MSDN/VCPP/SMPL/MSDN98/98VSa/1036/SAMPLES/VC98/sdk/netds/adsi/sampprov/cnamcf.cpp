/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CNamCF.cpp

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop


//+---------------------------------------------------------------------------
//
//  Function:   CSampleDSNamespaceCF::CreateInstance
//
//  Synopsis:
//
//  Arguments:  [pUnkOuter]
//              [iid]
//              [ppv]
//
//  Returns:    HRESULT
//
//  Modifies:
//
//----------------------------------------------------------------------------
STDMETHODIMP
CSampleDSNamespaceCF::CreateInstance(IUnknown * pUnkOuter, REFIID iid, LPVOID * ppv)
{
    HRESULT     hr = S_OK;

    if (pUnkOuter)
        RRETURN(E_FAIL);
        
        WCHAR wcaProviderDispName[MAX_PATH] = L"";
        wcscpy(wcaProviderDispName,g_szProviderName);
        wcscat(wcaProviderDispName,L":");

    hr = CSampleDSNamespace::CreateNamespace(
                L"ADs:",
                wcaProviderDispName,                    // Displayed by Enum of Namespaces
                ADS_OBJECT_BOUND,
                iid,
                ppv
                );

    RRETURN(hr);
}





