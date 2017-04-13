/*
 *  CREATEPR.C
 *
 *      Very simple console app creating a profile with hardcoded values.
 *
 *   Copyright (c) 1995, Microsoft Corporation. All Rights Reserved.
 *
 */

#include <mapiutil.h>
#include <mapiwin.h>
#include <mapidbg.h>
#include <stdio.h>
#include <smpms.h>
#include <smpxp.h>
#include <smpab.h>

#ifdef DEBUG
#define TraceFnResult(f, hr)    \
{ (hr) ?   \
printf(#f " returns 0x%08lX %s\n", GetScode(hr), SzDecodeScode(GetScode(hr))) : 0;\
}
#else
#define TraceFnResult(f, hr)
#endif  /*/DEBUG*/


HRESULT HrCreateProfile(void);


int main (void)
{
    HRESULT hr = 0;

    hr = HrCreateProfile();

    return (int) hr;
}




HRESULT HrCreateProfile(void)
{
    LPPROFADMIN         ppa = NULL;
    LPSERVICEADMIN      psa = NULL;
    LPMAPISESSION       pses = NULL;
    LPMAPITABLE         ptblSvc = NULL;
    HRESULT             hr;
    
    LPSRowSet           prows = NULL;
    LPSRow              prow = NULL;

    enum {iSvcName, iSvcUID, cptaSvc};
    SizedSPropTagArray (cptaSvc, ptaSvc) = { cptaSvc, 
                                            {   PR_SERVICE_NAME,
                                                PR_SERVICE_UID } };
    LPSTR               szProfile = "User XXX";
    #define cProviders  3
    #define nMAXProps   6
    SPropValue          rgval[nMAXProps];


    hr = MAPIInitialize(NULL);
    if (HR_FAILED(hr))
    {
        TraceFnResult(MAPIInitialize, hr);
        return hr;
    }

    hr = MAPIAdminProfiles(0, &ppa);
    if (HR_FAILED(hr))
    {
        TraceFnResult(MAPIAdminProfiles, hr);
        goto ret;
    }

    (void) ppa->lpVtbl->DeleteProfile(ppa, szProfile, 0);

    printf("Creating profile \"%s\"\n", szProfile);
    hr = ppa->lpVtbl->CreateProfile(ppa, szProfile, NULL, 0, 0);
    if (HR_FAILED(hr))
    {
        TraceFnResult(CreateProfile, hr);
        goto ret;
    }

    hr = MAPILogonEx(0, szProfile, NULL, MAPI_NO_MAIL | MAPI_NEW_SESSION,
                               &pses);
    if (HR_FAILED(hr))
    {
        TraceFnResult(MAPILogonEx, hr);
        goto ret;
    }

    hr = pses->lpVtbl->AdminServices(pses, 0, &psa);
    if (HR_FAILED(hr))
        goto ret;
    
    printf("Creating Sample Message Store\n");
    hr = psa->lpVtbl->CreateMsgService(psa, "SMPMS", "MAPI Sample Msg Store", 0, 0);
    if (HR_FAILED(hr))
    {
        TraceFnResult(CreateMsgService, hr);
        goto ret;
    }

    printf("Creating Sample Transport\n");
    hr = psa->lpVtbl->CreateMsgService(psa, "SMPXP", 
                                        "Sample Peer To Peer Transport", 0, 0);
    if (HR_FAILED(hr))
    {
        TraceFnResult(CreateMsgService, hr);
        goto ret;
    }

    printf("Creating Sample Address Book\n");
    hr = psa->lpVtbl->CreateMsgService(psa, "SMPAB", 
                                        "Sample Addres Book", 0, 0);
    if (HR_FAILED(hr))
    {
        TraceFnResult(CreateMsgService, hr);
        goto ret;
    }


    hr = psa->lpVtbl->GetMsgServiceTable(psa, 0, &ptblSvc);
    if (HR_FAILED(hr))
    {
        TraceFnResult(GetMsgServiceTable, hr);
        goto ret;
    }

    hr = HrQueryAllRows(ptblSvc, (LPSPropTagArray)&ptaSvc, NULL, NULL, 0, &prows);
    if (HR_FAILED(hr))
    {
        TraceFnResult(HrQueryAllRows, hr);
        goto ret;
    }

    Assert(prows->cRows == cProviders);
    
    for(prow = prows->aRow; prow < prows->aRow + cProviders; ++prow)
    {
        Assert(prow->cValues == cptaSvc);
        Assert(prow->lpProps[iSvcName].ulPropTag == PR_SERVICE_NAME);
        Assert(prow->lpProps[iSvcUID].ulPropTag == PR_SERVICE_UID);
        Assert(prow->lpProps[iSvcUID].Value.bin.cb == sizeof(MAPIUID));

        if(!lstrcmp(prow->lpProps[iSvcName].Value.lpszA, "SMPMS"))
        {
            printf("Configuring Sample Message Store...");
        
            rgval[0].ulPropTag      = PR_SMS_PATH;
            rgval[0].Value.lpszA    = "d:\\sms";
            
            rgval[1].ulPropTag      = PR_SMS_PASSWORD;
            rgval[1].Value.lpszA    = "PASSWORD";
            
            rgval[2].ulPropTag      = PR_SMS_REMEMBER_PW;
            rgval[2].Value.b        = TRUE;
            
            rgval[3].ulPropTag      = PR_SMS_CREATE;
            rgval[3].Value.b        = TRUE;
            
            hr = psa->lpVtbl->ConfigureMsgService(psa, 
                                (LPMAPIUID) prow->lpProps[iSvcUID].Value.bin.lpb,
                                            0, 0, 4, rgval);
            if (HR_FAILED(hr))
            {
                printf("failed\n");
                TraceFnResult(ConfigureMsgService, hr);
                //goto ret;
            }
            else
            {
                printf("OK\n");
            }
        }
        else if(!lstrcmp(prow->lpProps[iSvcName].Value.lpszA, "SMPXP"))
        {
            printf("Configuring Sample Transport...");
        
            rgval[0].ulPropTag  = PR_SAMPLE_DISPLAY_NAME;
            rgval[0].Value.LPSZ = "USER XXX";
            
            rgval[1].ulPropTag  = PR_SAMPLE_EMAIL_ADDR_TYPE;
            rgval[1].Value.LPSZ = "MSPEER";
            
            rgval[2].ulPropTag  = PR_SAMPLE_EMAIL_ADDRESS;
            rgval[2].Value.LPSZ = "\\\\aleksank\\d\\test\\inbound";
            
            rgval[3].ulPropTag  = PR_SAMPLE_INBOUND_DIR;
            rgval[3].Value.LPSZ = "d:\\test\\inbound";

            rgval[4].ulPropTag  = PR_SAMPLE_OUTBOUND_DIR;
            rgval[4].Value.LPSZ = "d:\\test\\outbound";

            rgval[5].ulPropTag  = PR_SAMPLE_FLAGS;
            rgval[5].Value.l    = 9;

            hr = psa->lpVtbl->ConfigureMsgService(psa, 
                                (LPMAPIUID) prow->lpProps[iSvcUID].Value.bin.lpb,
                                            0, 0, 6, rgval);
            if (HR_FAILED(hr))
            {
                printf("failed\n");
                TraceFnResult(ConfigureMsgService, hr);
                //goto ret;
            }
            else
            {
                printf("OK\n");
            }
        }
        else if(!lstrcmp(prow->lpProps[iSvcName].Value.lpszA, "SMPAB"))
        {
            printf("Configuring Sample Address Book...");
        
            rgval[0].ulPropTag  = PR_SAB_FILE;
            rgval[0].Value.LPSZ = "d:\\sampab.sab";
            
            hr = psa->lpVtbl->ConfigureMsgService(psa, 
                                (LPMAPIUID) prow->lpProps[iSvcUID].Value.bin.lpb,
                                            0, 0, 1, rgval);
            if (HR_FAILED(hr))
            {
                printf("failed\n");
                TraceFnResult(ConfigureMsgService, hr);
                //goto ret;
            }
            else
            {
                printf("OK\n");
            }
        }
        else
        {
            Assert(FALSE);
        }
    }
            
ret:
    
    UlRelease(ptblSvc);
    UlRelease(psa);
    UlRelease(pses);
    UlRelease(ppa);
    FreeProws(prows);
    MAPIUninitialize();
    return hr;
}

