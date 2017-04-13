/***********************************************************************
 *
 *  TID.C
 *
 *  Sample Address Book Template ID  object
 *  This file contains the code for implementing a template ID object
 *  that is associated with entries from this provider.  In particular
 *  the MailUser object generated in ABUSER.C needs this TID object when
 *  it's been copied into another provider (i.e. the PAB).
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/


#include "abp.h"

/*
 *  Declaration of IMailUser object implementation
 */
#undef  INTERFACE
#define INTERFACE   struct _TID

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, TID_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, TID_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(TID_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
};


/*
 *  The definition of the TID object
 */
typedef struct _TID {

    const TID_Vtbl * lpVtbl;

    SAB_Wrapped;
    
    /*
     *  Private data
     */
    LPMAILUSER  lpABUser;

} TID, *LPTID;

/*
 *  TID jump table is defined here...
 */

static const TID_Vtbl vtblTID =
{
    (TID_QueryInterface_METHOD *)   ABU_QueryInterface,
    (TID_AddRef_METHOD *)           WRAP_AddRef,
    TID_Release,
    (TID_GetLastError_METHOD *)     WRAP_GetLastError,
    (TID_SaveChanges_METHOD *)      WRAP_SaveChanges,
    (TID_GetProps_METHOD *)         WRAP_GetProps,
    (TID_GetPropList_METHOD *)      WRAP_GetPropList,
    TID_OpenProperty,
    (TID_SetProps_METHOD *)         WRAP_SetProps,
    (TID_DeleteProps_METHOD *)      WRAP_DeleteProps,
    (TID_CopyTo_METHOD *)           WRAP_CopyTo,
    (TID_CopyProps_METHOD *)        WRAP_CopyProps,
    (TID_GetNamesFromIDs_METHOD *)  WRAP_GetNamesFromIDs,
    (TID_GetIDsFromNames_METHOD *)  WRAP_GetIDsFromNames,
};

/*************************************************************************
 *
 -  NewTID
 -
 *  Creates the TID object associated with a mail user.
 *
 *
 */
HRESULT
HrNewTID(LPMAPIPROP *       lppMAPIPropNew,
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
    LPTID lpTID = NULL;
    SCODE sc;
    HRESULT hr = hrSuccess;
    LPMAILUSER lpABUser = NULL;
    ULONG ulObjType;

    /*
     *  Create the user object corresponding to the template id
     */
    hr = HrNewSampUser( &lpABUser,
                        &ulObjType,
                        cbTemplateId,
                        lpTemplateId,
                        lpABPLogon,
                        lpInterface,
                        hLibrary,
                        lpAllocBuff,
                        lpAllocMore,
                        lpFreeBuff,
                        lpMalloc);
    if (HR_FAILED(hr))
    {
        goto err;
    }

    Assert(ulObjType == MAPI_MAILUSER);
    /*
     *  Allocate space for the TID structure
     */
    sc = lpAllocBuff(sizeof(TID), (LPVOID *) &lpTID);
    if (FAILED(sc))
    {
        hr = ResultFromScode(sc);
        goto err;
    }

    /*
     *  Initialize the TID structure
     */

    lpTID->lpVtbl = &vtblTID;
    lpTID->lcInit = 1;
    lpTID->hResult = hrSuccess;
    lpTID->idsLastError = 0;
    lpTID->hLibrary = hLibrary;
    lpTID->lpAllocBuff = lpAllocBuff;
    lpTID->lpAllocMore = lpAllocMore;
    lpTID->lpFreeBuff = lpFreeBuff;
    lpTID->lpMalloc = lpMalloc;
    lpTID->lpABLogon = lpABPLogon;
    lpTID->lpPropData = lpPropData;
    lpTID->lpABUser = (LPMAILUSER) lpABUser;


    if (ulTemplateFlags & FILL_ENTRY)
    {
        ULONG ulCount;
        LPSPropValue lpspv = NULL;

        /*
         *  Copy all the properties from my object to the propdata
         */
        hr = lpABUser->lpVtbl->GetProps(lpABUser,
            NULL,
            0,      /* ansi */
            &ulCount,
            &lpspv);

        if (HR_FAILED(hr))
            goto err;

        hr = lpPropData->lpVtbl->SetProps(lpPropData,
            ulCount,
            lpspv,
            NULL);

        lpFreeBuff(lpspv);

        if (HR_FAILED(hr))
            goto err;
    }

    /*
     *  AddRef lpPropData so we can use it after we return
     */

    (void)lpPropData->lpVtbl->AddRef(lpPropData);

    InitializeCriticalSection(&lpTID->cs);

    /*  We must AddRef the lpABPLogon object since we will be using it
     */
    lpABPLogon->lpVtbl->AddRef(lpABPLogon);

    *lppMAPIPropNew = (LPVOID) lpTID;

out:

    DebugTraceResult(HrNewTID, hr);
    return hr;

err:

    if (lpABUser)
        lpABUser->lpVtbl->Release(lpABUser);
    
    lpFreeBuff(lpTID);

    goto out;
}

/*
 -  TID_Release
 -
 *  Releases the TID object.  The main difference between this
 *  Release and WRAP_Release() is that it also has to release the
 *  lpABUser object.
 *
 *  Note the Release on the lpPropData.  This required because of
 *  WRAP's implementation of IUnknown (which this object reuses).
 */

STDMETHODIMP_(ULONG) TID_Release(LPTID lpTID)
{
    LONG lcInit;

    /*
     * Check to see if it's large enough to hold this object
     */
    if (IsBadReadPtr(lpTID, sizeof(TID)))
    {
        /*
         *  I'm not looking at an object that I expect to be.
         */
        return 1;
    }

    /*
     *  Check to see that it's TIDs vtbl
     */
    if (lpTID->lpVtbl != &vtblTID)
    {
        /*
         *  It's big enough but it's got the wrong vtbl.
         */
        return 1;
    }

    /*
     *  Release the mapi property object
     */
    lpTID->lpPropData->lpVtbl->Release(
        lpTID->lpPropData);

    EnterCriticalSection(&lpTID->cs);
    lcInit = --lpTID->lcInit;
    LeaveCriticalSection(&lpTID->cs);

    if (lcInit == 0)
    {
        /*
         *  Release the ABUser object
         */
        lpTID->lpABUser->lpVtbl->Release(
            lpTID->lpABUser);

        /*  
         *  Release our reference to the ABLogon object.
         */
        if (lpTID->lpABLogon)
        {
            lpTID->lpABLogon->lpVtbl->Release(lpTID->lpABLogon);
            lpTID->lpABLogon = NULL;
        }

        /*
         *  Clean up the critical section
         */
        DeleteCriticalSection(&lpTID->cs);

        /*
         * Need to free the object
         */
        lpTID->lpFreeBuff(lpTID);
        return 0;
    }

    return lcInit;
}

/*
 -  TID_OpenProperty
 -
 *  Satisfies the object that are needed to support the "Options" details pane
 *  associated with the MailUser object from ABUSER.C.
 *
 *  Note:  We are masking error strings that might be possible to get from the
 *  lpABUser object.  Since (for the most part) the only errors that can be returned
 *  from this object are resource failure types, it wouldn't be of much use to the
 *  user.
 */

STDMETHODIMP
TID_OpenProperty(LPTID lpTID,
    ULONG ulPropTag,
    LPCIID lpiid,
    ULONG ulInterfaceOptions,
    ULONG ulFlags,
    LPUNKNOWN * lppUnk)
{
    HRESULT hResult;

    /*
     *  Check to see if it's large enough to hold this object
     */
    if (IsBadReadPtr(lpTID, sizeof(TID)))
    {
        /*
         *  No vtbl found
         */
        return ResultFromScode(E_INVALIDARG);
    }

    /*
     *  Check to see that it's TIDs vtbl
     */
    if (lpTID->lpVtbl != &vtblTID)
    {
        /*
         *  It's big enough but it's got the wrong vtbl.
         */
        return ResultFromScode(E_INVALIDARG);
    }

    if ( ulInterfaceOptions & ~MAPI_UNICODE )
    {
        DebugTraceArg( TID_OpenProperty, "unknown flags" );
        return ResultFromScode( MAPI_E_UNKNOWN_FLAGS );
    }
    
    if ( ulInterfaceOptions & MAPI_UNICODE )
    {
        DebugTraceArg( TID_OpenProperty, "bad character width" );
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH );
    }
    /*
     *  Don't want to check any other parameters here.
     *  Calls down to wrapped objects will do this for
     *  me.
     */

    switch (ulPropTag)
    {
        case PR_LISTBOX_TABLE:
        case PR_DDLISTBOX_TABLE:
        case PR_COMBOBOX_TABLE:
        {
            hResult = lpTID->lpABUser->lpVtbl->OpenProperty(
                lpTID->lpABUser,
                ulPropTag,
                lpiid,
                ulInterfaceOptions,
                ulFlags,
                lppUnk);
            break;

        }

        default:
        {
            hResult = lpTID->lpPropData->lpVtbl->OpenProperty(
                lpTID->lpPropData,
                ulPropTag,
                lpiid,
                ulInterfaceOptions,
                ulFlags,
                lppUnk);
            break;
        }
    }

    DebugTraceResult(TID_OpenProperty, hResult);
    return hResult;
}
