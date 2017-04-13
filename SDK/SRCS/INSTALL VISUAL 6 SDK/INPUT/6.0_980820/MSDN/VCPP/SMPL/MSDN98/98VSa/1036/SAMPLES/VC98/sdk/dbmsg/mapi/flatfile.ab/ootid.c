/***********************************************************************
 *
 *  OOTID.C
 *
 *  Sample Address Book OneOff Template ID object
 *  This file contains the code for implementing the Sample AB
 *  template ID for it's one-off.
 *
 *  The template ID for the Sample Address Book one-offs has only one
 *  purpose.  When the SaveChanges() method gets called it recalculates
 *  PR_EMAIL_ADDRESS_A and PR_SEARCH_KEY from data that was changed by the
 *  user.  See how this interacts with the one-off user object implemented
 *  in OOUSER.C.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/

#include "abp.h"

/*
 *  Declaration of IMailUser object implementation
 */
#undef  INTERFACE
#define INTERFACE   struct _OOTID

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, OOTID_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, OOTID_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)


DECLARE_MAPI_INTERFACE(OOTID_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
};


/*
 *  The structure behind the 'this' pointer
 */
typedef struct _OOTID {

    const OOTID_Vtbl * lpVtbl;

    SAB_Wrapped;
    
} OOTID, *LPOOTID;

/*
 *  OOTID vtbl is filled in here.
 */

static const OOTID_Vtbl vtblOOTID =
{
    (OOTID_QueryInterface_METHOD *)     ABU_QueryInterface,
    (OOTID_AddRef_METHOD *)             WRAP_AddRef,
    (OOTID_Release_METHOD *)            WRAP_Release,
    (OOTID_GetLastError_METHOD *)       WRAP_GetLastError,
    OOTID_SaveChanges,
    (OOTID_GetProps_METHOD *)           WRAP_GetProps,
    (OOTID_GetPropList_METHOD *)        WRAP_GetPropList,
    (OOTID_OpenProperty_METHOD *)       WRAP_OpenProperty,
    (OOTID_SetProps_METHOD *)           WRAP_SetProps,
    (OOTID_DeleteProps_METHOD *)        WRAP_DeleteProps,
    (OOTID_CopyTo_METHOD *)             WRAP_CopyTo,
    (OOTID_CopyProps_METHOD *)          WRAP_CopyProps,
    (OOTID_GetNamesFromIDs_METHOD *)    WRAP_GetNamesFromIDs,
    (OOTID_GetIDsFromNames_METHOD *)    WRAP_GetIDsFromNames,
};

/*************************************************************************
 *
 -  NewOOTID
 -
 *  Creates the OOTID object associated with a mail user.
 *
 *
 */

enum {
    isptOOTIDFillPR_ADDRTYPE_A = 0,
    isptOOTIDFillPR_TEMPLATEID,
    isptOOTIDFillPR_DISPLAY_TYPE,
    cmaxOOTIDFill
};

HRESULT
HrNewOOTID( LPMAPIPROP *        lppMAPIPropNew,
            ULONG               cbTemplateId,
            LPENTRYID           lpTemplateId,
            ULONG               ulTemplateFlags,
            LPMAPIPROP          lpPropData,
            LPABLOGON           lpABPLogon,
            LPCIID              lpInterface,
            HINSTANCE           hLibrary,
            LPALLOCATEBUFFER    lpAllocBuff,
            LPALLOCATEMORE      lpAllocMore,
            LPFREEBUFFER        lpFreeBuff,
            LPMALLOC            lpMalloc )
{
    LPOOTID lpOOTID = NULL;
    SCODE sc;
    HRESULT hResult = hrSuccess;

    /*
     *  Allocate space for the OOTID structure
     */
    sc = lpAllocBuff( sizeof(OOTID), (LPVOID *) &lpOOTID );
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto err;
    }

    /*
     *  Initialize the OOTID structure
     */

    lpOOTID->lpVtbl = &vtblOOTID;
    lpOOTID->lcInit = 1;
    lpOOTID->hResult = hrSuccess;
    lpOOTID->idsLastError = 0;
    lpOOTID->hLibrary = hLibrary;
    lpOOTID->lpAllocBuff = lpAllocBuff;
    lpOOTID->lpAllocMore = lpAllocMore;
    lpOOTID->lpFreeBuff = lpFreeBuff;
    lpOOTID->lpMalloc = lpMalloc;
    lpOOTID->lpABLogon = lpABPLogon;
    lpOOTID->lpPropData = lpPropData;

    /*
     *  Fill in the wrapped object if we're asked to.
     */
    if (ulTemplateFlags & FILL_ENTRY)
    {
        SPropValue spv[cmaxOOTIDFill];

        spv[isptOOTIDFillPR_ADDRTYPE_A].ulPropTag = PR_ADDRTYPE_A;
        spv[isptOOTIDFillPR_ADDRTYPE_A].Value.lpszA = lpszEMT;

        spv[isptOOTIDFillPR_TEMPLATEID].ulPropTag = PR_TEMPLATEID;
        spv[isptOOTIDFillPR_TEMPLATEID].Value.bin.lpb = (LPBYTE) lpTemplateId;
        spv[isptOOTIDFillPR_TEMPLATEID].Value.bin.cb = cbTemplateId;

        spv[isptOOTIDFillPR_DISPLAY_TYPE].ulPropTag = PR_DISPLAY_TYPE;
        spv[isptOOTIDFillPR_DISPLAY_TYPE].Value.l = DT_MAILUSER;

        hResult = lpPropData->lpVtbl->SetProps(
            lpPropData,
            cmaxOOTIDFill,
            spv,
            NULL);
        
        if (HR_FAILED(hResult))
        {
            goto err;
        }

    }

    /*
     *  AddRef lpPropData so we can use it after we return
     */

    (void)lpPropData->lpVtbl->AddRef(lpPropData);

    InitializeCriticalSection(&lpOOTID->cs);
    
    /*  We must AddRef the lpABPLogon object since we will be using it
     */
    lpABPLogon->lpVtbl->AddRef(lpABPLogon);

    *lppMAPIPropNew = (LPVOID) lpOOTID;

out:

    DebugTraceResult(HrNewOOTID, hResult);
    return hResult;

err:

    lpFreeBuff(lpOOTID);
    goto out;

}


/*
 *  These properties are used and set by the one off dialog, and are
 *  combined to make up a valid email address.
 */

enum {
    isptcontpropPR_SERVER_NAME = 0,
    isptcontpropPR_SHARE_NAME,
    isptcontpropPR_PATH_NAME,
    cmaxcontprop
};      

static const SizedSPropTagArray(cmaxcontprop, pta) =
{
    cmaxcontprop,
    {
        PR_SERVER_NAME,
        PR_SHARE_NAME,
        PR_PATH_NAME,
    }
};

/*
 *  These properties are computed by this function and saved back into the underlying
 *  property storage.
 */
enum {
    isptcomppropsPR_EMAIL_ADDRESS_A = 0,
    isptcomppropsPR_SEARCH_KEY,
    cmaxcompprops
};


/*
 -  OOTID_SaveChanges
 -
 *  All this method does is build the PR_EMAIL_ADDRESS_A and PR_SEARCH_KEY from PR_SERVER_NAME,
 *  PR_SHARE_NAME, and PR_PATH_NAME.
 */

STDMETHODIMP
OOTID_SaveChanges(LPOOTID lpOOTID, ULONG ulFlags)
{
    HRESULT hResult;
    /*
     *  szEMA can be of the format:
     *
     *      \\SERVER_NAME\SHARE_NAME[\PATH]'\0'
     */
    CHAR szEMA[ MAX_SERVER_NAME + 2 + MAX_SHARE_NAME + 1 + MAX_PATH + 2 ];
    LPSPropValue lpspv = NULL;
    SPropValue rgspv[cmaxcompprops];
    ULONG ulcValues;
    ULONG cbT = 0;
    LPBYTE lpbT = NULL;
    SCODE sc;

    /*
     *  Check to see if it is big enough to be my object
     */
    if (IsBadReadPtr(lpOOTID, sizeof(OOTID)))
    {
        /*
         *  Not big enough
         */
        return MakeResult(E_INVALIDARG);
    }

    /*
     *  Check to see that it's OOTIDs vtbl
     */
    if (lpOOTID->lpVtbl != &vtblOOTID)
    {
        /*
         *  vtbl not ours
         */
        return MakeResult(E_INVALIDARG);
    }


    /*
     *  Get the properties that make up the email address from the
     *  mapiprop object
     */
    hResult = lpOOTID->lpPropData->lpVtbl->GetProps(
        lpOOTID->lpPropData,
        (LPSPropTagArray) &pta,
        0,      /* ansi */
        &ulcValues,
        &lpspv);

    if (HR_FAILED(hResult))
    {
        goto out;
    }

    /*
     *  Must have at least PR_SERVER_NAME and PR_SHARE_NAME to make a valid
     *  email address
     */
    if (lpspv[isptcontpropPR_SERVER_NAME].ulPropTag != PR_SERVER_NAME
        || lpspv[isptcontpropPR_SHARE_NAME].ulPropTag != PR_SHARE_NAME)
    {
        /*
         *  Without at least these two properties I cannot recalculate
         *  anything.  So, just exit cleanly without changing anything.
         */
        hResult = hrSuccess; /* to mask any warnings from above */
        goto out;
    }

    /* create the email address */
    wsprintfA(szEMA, "\\\\%s\\%s",
        lpspv[isptcontpropPR_SERVER_NAME].Value.lpszA, lpspv[isptcontpropPR_SHARE_NAME].Value.lpszA);

    /*  Did we also get a path??  If so append it on */
    if (lpspv[isptcontpropPR_PATH_NAME].ulPropTag == PR_PATH_NAME)
    {
        /*  But only if there's a value that make sense */
        if (*lpspv[isptcontpropPR_PATH_NAME].Value.lpszA)   /* i.e. !'\0' */
            wsprintfA(szEMA, "%s\\%s", szEMA, lpspv[isptcontpropPR_PATH_NAME].Value.lpszA);
    }

    /* initialize the email address prop value */
    rgspv[isptcomppropsPR_EMAIL_ADDRESS_A].ulPropTag = PR_EMAIL_ADDRESS_A;
    rgspv[isptcomppropsPR_EMAIL_ADDRESS_A].Value.lpszA = szEMA;

    /*
     *  Generate the PR_SEARCH_KEY
     */
    /*  Search keys for mailable recipients that have email addresses are
     *  defined as "EmailType':'EmailAddress\0".  We do the +2 for the ':' and
     *  '\0'.
     */
    cbT = lstrlenA(szEMA) + lstrlenA(lpszEMT) + 2;

    sc = lpOOTID->lpAllocBuff( cbT, (LPVOID *) &lpbT );
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }
    lstrcpyA((LPSTR) lpbT, lpszEMT);
    lstrcatA((LPSTR) lpbT, ":");
    lstrcatA((LPSTR) lpbT, szEMA);
    CharUpperBuffA((LPSTR) lpbT, (UINT) cbT);

    rgspv[isptcomppropsPR_SEARCH_KEY].ulPropTag = PR_SEARCH_KEY;
    rgspv[isptcomppropsPR_SEARCH_KEY].Value.bin.cb = cbT;
    rgspv[isptcomppropsPR_SEARCH_KEY].Value.bin.lpb = lpbT;

    
    /*
     *  set the email address and search key properties
     */
    hResult = lpOOTID->lpPropData->lpVtbl->SetProps(
        lpOOTID->lpPropData,
        cmaxcompprops,
        rgspv,
        NULL);

    lpOOTID->lpFreeBuff(lpbT);

    if (HR_FAILED(hResult))
    {
        goto out;
    }

out:
    //
    //  If I'm leaving this routine and everything up to this point has been successful,
    //  then pass on the SaveChanges to the underlying property storage.
    //
    if (!HR_FAILED(hResult))
    {
        hResult = lpOOTID->lpPropData->lpVtbl->SaveChanges(
            lpOOTID->lpPropData,
            ulFlags);
    }

    /* free the buffer */
    lpOOTID->lpFreeBuff(lpspv);

    DebugTraceResult(OOTID_SaveChanges, hResult);
    return hResult;
}

