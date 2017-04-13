/*
 -  X P O P T I O N . C
 -
 *  Purpose:
 *      Defines a wrapped implementation of an IMAPIProp interface
 *      to be used by ScMsgOptionCallBack() and ScRecipOptionCallBack()
 *      to wrap the IMAPIProp passed in.  This object is wrapped so we
 *      can effect the behavior of the OpenProperty() call.  Specifically,
 *      we wish to put up a Property Sheet when the user tries to open
 *      the PR_DETAILS_TABLE property.
 *
 *      This file overloads the OpenProperty() method on the Wrapped
 *      IMAPIProp in order to slam properties from a Display Table
 *      into the underlying message object.  It also creates the
 *      Display Table used by IMAPISession::MessageOptions().
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "xppch.h"
#include "xpresrc.h"
#include "xpoption.h"
#include <mapiutil.h>

/* Generic control structures */

DTBLPAGE dtblMsgOptPage =
{sizeof(DTBLPAGE), 0, 0, 0};
DTBLPAGE dtblRecipOptPage =
{sizeof(DTBLPAGE), 0, 0, 0};

/* Display table control structures for the General property sheet. */

DTBLCHECKBOX chkPerMsgDefer =
{sizeof(DTBLCHECKBOX), fMapiUnicode,
    PR_SAMPLE_PER_MSG_DEFER};
DTBLCHECKBOX chkPerRecipDefer =
{sizeof(DTBLCHECKBOX), fMapiUnicode,
    PR_SAMPLE_PER_RECIP_DEFER};

DTCTL rgdtctlMsgOpt[] =
{
    {DTCT_PAGE, 0, NULL, 0, NULL, 0, &dtblMsgOptPage},
    {DTCT_CHECKBOX, DT_EDITABLE, NULL, 0, NULL, IDC_PER_MSG_DEFER, &chkPerMsgDefer}
};

DTCTL rgdtctlRecipOpt[] =
{
    {DTCT_PAGE, 0, NULL, 0, NULL, 0, &dtblRecipOptPage},
    {DTCT_CHECKBOX, DT_EDITABLE, NULL, 0, NULL, IDC_PER_RECIP_DEFER, &chkPerRecipDefer}
};


/* Display table pages */

DTPAGE rgdtpageMsgOpt[] =
{
    {
        sizeof(rgdtctlMsgOpt) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(PerMsgOpt),
        "",
        rgdtctlMsgOpt
    }
};


DTPAGE rgdtpageRecipOpt[] =
{
    {
        sizeof(rgdtctlRecipOpt) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(PerRecipOpt),
        "",
        rgdtctlRecipOpt
    }
};


/*
 *  WMProp jump table is defined here...
 */

WMPROP_Vtbl vtblOPT =
{
    WMPROP_QueryInterface,
    WMPROP_AddRef,
    WMPROP_Release,
    WMPROP_GetLastError,
    WMPROP_SaveChanges,
    WMPROP_GetProps,
    WMPROP_GetPropList,
    WMPROP_OpenProperty,
    WMPROP_SetProps,
    WMPROP_DeleteProps,
    WMPROP_CopyTo,
    WMPROP_CopyProps,
    WMPROP_GetNamesFromIDs,
    WMPROP_GetIDsFromNames,
};


/*
 *  Private functions prototypes
 */

SCODE ScNewWrappedMAPIProp(
    LPMAPIPROP lpMAPIProp,
    HINSTANCE hInst,
    LPMALLOC lpMalloc,
    ULONG ulType,
    ULONG cbOptionData,
    LPBYTE lpbOptionData,
    LPMAPISUP lpMAPISup,
    LPWMPROP * lppWMProp);

OPTIONCALLBACK ScOptionDataCallBack;


/*
 -  ScOptionDataCallBack
 -
 *  Purpose:
 *      Gets called by MAPI to wrap the source IMessage in
 *      preparation to Display Table calls.
 *
 *  Parameters:
 *      hInst               - Instance of myself from LoadLibrary call
 *      lpMalloc            - OLE 2.0 style allocator
 *      ulFlags             - OPTION_TYPE_MESSAGE | OPTION_TYPE_RECIPIENT
 *      cbOptionData        - Size of OptionData I sent at Register time
 *      lpbOptionData       - OptionData I sent at Register time
 *      lpMAPISup           - A support object for mem routines
 *      lpDataSource        - Underlying IMessage object
 *      lppWrappedSource    - Returned wrapped version of lpDataSource
 *      lppszErrorMsg       - Context sensitive error msg for MAPI
 *      lppszErrorComponent - Help filename if one exists
 *      lpulErrorContext    - Context in Help File
 *
 *  Returns:
 *      sc                  - Scode of failure if any
 */

STDINITMETHODIMP_(SCODE)
ScOptionDataCallBack(
    HINSTANCE hInst,
    LPMALLOC lpMalloc,
    ULONG ulFlags,
    ULONG cbOptionData,
    LPBYTE lpbOptionData,
    LPMAPISUP lpMAPISup,
    LPMAPIPROP lpDataSource,
    LPMAPIPROP FAR * lppWrappedSource,
    LPMAPIERROR FAR * lppMapiError )
{
    SCODE sc;
    LPWMPROP lpWMProp = NULL;

    /* Do Parameter Validation Now */

#ifdef _WIN32
    if (!hInst)
#else
    if (hInst < HINSTANCE_ERROR)
#endif
    {
        DebugTrace("ScOptionDataCallBack() - Invalid hInst");
        return E_INVALIDARG;
    }

    if (ulFlags & (~(OPTION_TYPE_MESSAGE | OPTION_TYPE_RECIPIENT)))
    {
        DebugTrace("ScOptionDataCallBack() - Unknown ulFlags!");
        return E_INVALIDARG;
    }

    if (cbOptionData && !lpbOptionData)
    {
        DebugTrace("ScOptionDataCallBack() - Invalid lpbOptionData");
        return E_INVALIDARG;
    }

    if (cbOptionData)
    {
        if (IsBadReadPtr(lpbOptionData, (UINT) cbOptionData))
        {
            DebugTrace("ScOptionDataCallBack() - Invalid lpbOptionData");
            return E_INVALIDARG;
        }
    }

    if (!lpMAPISup || IsBadReadPtr(lpMAPISup, sizeof(LPVOID)))
    {
        DebugTrace("ScOptionDataCallBack() - Invalid lpMAPISup");
        return E_INVALIDARG;
    }

    if (!lpDataSource || IsBadReadPtr(lpDataSource, sizeof(LPVOID)))
    {
        DebugTrace("ScOptionDataCallBack() - Invalid lpDataSource");
        return E_INVALIDARG;
    }

    if (!lppWrappedSource || IsBadWritePtr(lppWrappedSource, sizeof(LPVOID)))
    {
        DebugTrace("ScOptionDataCallBack() - Invalid lppWrappedSource");
        return E_INVALIDARG;
    }

    if (!lppMapiError || IsBadWritePtr(lppMapiError, sizeof(LPMAPIERROR)))
    {
        DebugTrace("ScOptionDataCallBack() - Invalid lppMapiError");
        return E_INVALIDARG;
    }

    *lppWrappedSource = NULL;
    *lppMapiError = NULL;

    /* Everything is OK, Lets build the Wrapped Source now. */

    sc = ScNewWrappedMAPIProp(lpDataSource, hInst, lpMalloc, ulFlags, 
            cbOptionData, lpbOptionData, lpMAPISup, &lpWMProp);

    if (sc)
        goto ret;

    *lppWrappedSource = (LPMAPIPROP) lpWMProp;

ret:
    return sc;
}


/*
 -  ScNewWrappedMAPIProp
 -
 *  Purpose:
 *      Creates a wrapped Per-Message or Per-Recipient Options
 *      property interface to pass back to caller.  All methods
 *      call through to the base class except OpenProperty(),
 *      which intercepts PR_DETAILS_TABLE and creates a Display
 *      Table to pass back to the caller.
 *
 *  Parameters:
 *      lpMAPIProp          - The Property Interface to wrapper (an IMsg)
 *      lpXPLogon           - The opaque XP Logon object
 *      hInst               - My hInst of this DLL
 *      ulType              - Either OPTION_TYPE_MESSAGE or _RECIPIENT
 *      cbOptionData        - Size of my OptionData blob
 *      lpbOptionData       - My OptionData blob
 *      lpMAPISup           - Needed for memory alloc routines
 *      lppWMProp           - Returned wrapped IMAPIProp object
 *
 *  Returns:
 *      sc                  - Indicating Success/Failure
 */

SCODE
ScNewWrappedMAPIProp(
    LPMAPIPROP lpMAPIProp,
    HINSTANCE hInst,
    LPMALLOC lpMalloc,
    ULONG ulType,
    ULONG cbOptionData,
    LPBYTE lpbOptionData,
    LPMAPISUP lpMAPISup,
    LPWMPROP FAR * lppWMProp)
{
    HRESULT hr;
    SCODE sc;
    LPWMPROP lpWMProp = NULL;
    LPBYTE lpb = NULL;
    LPALLOCATEBUFFER lpAllocBuff = NULL;
    LPALLOCATEMORE lpAllocMore = NULL;
    LPFREEBUFFER lpFreeBuff = NULL;

    hr = lpMAPISup->lpVtbl->GetMemAllocRoutines(lpMAPISup,
        &lpAllocBuff, &lpAllocMore, &lpFreeBuff);

    if (hr)
    {
        sc = GetScode(hr);
        goto ret;
    }

    sc = (*lpAllocBuff) (sizeof(WMPROP), &lpWMProp);

    if (sc)
    {
        goto ret;
    }

    lpWMProp->lpVtbl = &vtblOPT;
    lpWMProp->lcInit = 1;
    lpWMProp->lpAllocBuff = lpAllocBuff;
    lpWMProp->lpAllocMore = lpAllocMore;
    lpWMProp->lpFreeBuff = lpFreeBuff;
    lpWMProp->hInst = hInst;
    lpWMProp->lpMalloc = lpMalloc;
    lpWMProp->ulType = ulType;
    lpWMProp->lpMAPIProp = lpMAPIProp;

    if (cbOptionData)
    {
        sc = (*lpAllocMore) (cbOptionData, lpWMProp, &lpb);

        if (sc)
        {
            goto ret;
        }

        memcpy(lpb, lpbOptionData, (UINT) cbOptionData);

        lpWMProp->cbOptionData = cbOptionData;
        lpWMProp->lpbOptionData = lpb;
    }

    lpMalloc->lpVtbl->AddRef(lpMalloc);
    lpMAPIProp->lpVtbl->AddRef(lpMAPIProp);

    *lppWMProp = lpWMProp;

ret:
    if (sc && lpFreeBuff)
        (*lpFreeBuff) (lpWMProp);

    return sc;
}


/*
 -  WMPROP_OpenProperty
 -
 *  Purpose:
 *      Traps a request to OpenProperty() on PR_DETAILS_TABLE so I
 *      can supply a DisplayTable for the user.  Else, passes the
 *      request to the underlying object.
 *
 */

STDMETHODIMP
WMPROP_OpenProperty(
    LPWMPROP lpWMProp,
    ULONG ulPropTag,
    LPCIID lpiid,
    ULONG ulInterfaceOptions,
    ULONG ulFlags,
    LPUNKNOWN * lppUnk)
{
    HRESULT hResult;

    /* Check to see if it has a jump table */

    if (FBadUnknown(lpWMProp))
    {
        hResult = ResultFromScode(E_INVALIDARG);
        DebugTraceResult(WMPROP_OpenProperty, hResult);
        return hResult;
    }

    /* Check to see that it's the correct jump table */

    if (lpWMProp->lpVtbl != &vtblOPT)
    {
        hResult = ResultFromScode(E_INVALIDARG);
        DebugTraceResult(WMPROP_OpenProperty, hResult);
        return hResult;
    }

    if (IsBadWritePtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, OpenProperty)))
    {
        hResult = ResultFromScode(E_INVALIDARG);
        DebugTraceResult(WMPROP_OpenProperty, hResult);
        return hResult;
    }

    if ( ulInterfaceOptions & ~MAPI_UNICODE )
    {
        hResult = ResultFromScode(MAPI_E_UNKNOWN_FLAGS);
        DebugTraceResult(WMPROP_OpenProperty, hResult);
        return hResult;
    }
    
    if ( ulInterfaceOptions & MAPI_UNICODE )
    {
        hResult = ResultFromScode(MAPI_E_BAD_CHARWIDTH);
        DebugTraceResult(WMPROP_OpenProperty, hResult);
        return hResult;
    }
    
    /* PR_DETAILS_TABLE is the secret code for "DisplayTable" */

    if (ulPropTag == PR_DETAILS_TABLE)
    {
        /* Check to see if they're expecting a table interface */

        if (memcmp(lpiid, &IID_IMAPITable, sizeof(IID)))
        {
            hResult = ResultFromScode(E_NOINTERFACE);
            goto ret;
        }

        if (lpWMProp->ulType == OPTION_TYPE_MESSAGE)
        {
            hResult = BuildDisplayTable(
                lpWMProp->lpAllocBuff,
                lpWMProp->lpAllocMore,
                lpWMProp->lpFreeBuff,
                lpWMProp->lpMalloc,
                lpWMProp->hInst,
                sizeof(rgdtpageMsgOpt) / sizeof(DTPAGE),
                rgdtpageMsgOpt,
                0,
                (LPMAPITABLE FAR *) lppUnk,
                NULL);
        }
        else
        {
            Assert(lpWMProp->ulType == OPTION_TYPE_RECIPIENT);

            hResult = BuildDisplayTable(
                lpWMProp->lpAllocBuff,
                lpWMProp->lpAllocMore,
                lpWMProp->lpFreeBuff,
                lpWMProp->lpMalloc,
                lpWMProp->hInst,
                sizeof(rgdtpageRecipOpt) / sizeof(DTPAGE),
                rgdtpageRecipOpt,
                0,
                (LPMAPITABLE FAR *) lppUnk,
                NULL);
        }
    }
    else
    {
        hResult = lpWMProp->lpMAPIProp->lpVtbl->OpenProperty(
            lpWMProp->lpMAPIProp, ulPropTag, lpiid,
            ulInterfaceOptions, ulFlags, lppUnk);
    }

ret:
    DebugTraceResult(WMPROP_OpenProperty, hResult);
    return hResult;
}


/*
 -  WMPROP_QueryInterface
 -  WMPROP_AddRef
 -  WMPROP_Release
 *
 *  Purpose:
 *      Wrapped version of the IUnknown methods.
 */

STDMETHODIMP
WMPROP_QueryInterface(
    LPWMPROP lpWMProp,
    REFIID lpiid,
    LPVOID * lppNewObj)
{
    /* Check to see if it has a jump table */

    if (FBadUnknown(lpWMProp))
    {
        DebugTraceSc(WMPROP_QueryInterface, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /* Check to see if the method is the same */

    if (WMPROP_QueryInterface != lpWMProp->lpVtbl->QueryInterface)
    {
        DebugTraceSc(WMPROP_QueryInterface, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /*  Call the internal prop interface */

    return lpWMProp->lpMAPIProp->lpVtbl->QueryInterface(
        lpWMProp->lpMAPIProp, lpiid, lppNewObj);
}


STDMETHODIMP_(ULONG)
WMPROP_AddRef(LPWMPROP lpWMProp)
{
    /* Check to see if it has a jump table */

    if (FBadUnknown(lpWMProp))
    {
        DebugTrace("Bad lpWMProp in WMPROP_AddRef\n");
        return 1;
    }

    /* Check to see if the method is the same */

    if (WMPROP_AddRef != lpWMProp->lpVtbl->AddRef)
    {
        DebugTrace("Bad lpWMProp in WMPROP_AddRef\n");
        return 1;
    }

    return ++lpWMProp->lcInit;
}


STDMETHODIMP_(ULONG)
WMPROP_Release(LPWMPROP lpWMProp)
{
    ULONG cRef;

    /* Check to see if it has a jump table */

    if (FBadUnknown(lpWMProp))
    {
        DebugTrace("Bad lpWMProp in WMPROP_Release\n");
        return 1;
    }

    /* Check to see if the method is the same */

    if (WMPROP_Release != lpWMProp->lpVtbl->Release)
    {
        DebugTrace("Bad lpWMProp in WMPROP_Release\n");
        return 1;
    }

    cRef = --lpWMProp->lcInit;

    if (lpWMProp->lcInit == 0)
    {
        /* Release the allocator that was handed to us */
        
        lpWMProp->lpMalloc->lpVtbl->Release(lpWMProp->lpMalloc);
        
        /* Release the underlying IMAPIProp object */
        
        lpWMProp->lpMAPIProp->lpVtbl->Release(lpWMProp->lpMAPIProp);

        /* Need to free the object */

        (*lpWMProp->lpFreeBuff) (lpWMProp);
    }

    return cRef;
}


/*
 -  WMPROP_GetLastError
 -  WMPROP_SaveChanges
 -  WMPROP_GetProps
 -  WMPROP_GetPropList
 -  WMPROP_OpenProperty
 -  WMPROP_SetProps
 -  WMPROP_DeleteProps
 -  WMPROP_CopyTo
 -  WMPROP_CopyProps
 -  WMPROP_GetNamesFromID
 -  WMPROP_GetIDsFromName
 *
 *  Purpose:
 *      Wrapped version of the IMAPIProp methods.
 */

STDMETHODIMP
WMPROP_GetLastError(
    LPWMPROP lpWMProp,
    HRESULT hError,
    ULONG ulFlags,
    LPMAPIERROR FAR * lppMapiError )
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, GetLastError)) ||
        WMPROP_GetLastError != lpWMProp->lpVtbl->GetLastError)
    {
        DebugTraceSc(WMPROP_GetLastError, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    if ( ulFlags & ~MAPI_UNICODE )
    {
        DebugTraceSc(WMPROP_GetLastError, MAPI_E_UNKNOWN_FLAGS);
        return ResultFromScode( MAPI_E_UNKNOWN_FLAGS );
    }
    
    if ( ulFlags & MAPI_UNICODE )
    {
        DebugTraceSc(WMPROP_GetLastError, MAPI_E_BAD_CHARWIDTH);
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH );
    }
    
    return lpWMProp->lpMAPIProp->lpVtbl->GetLastError(
            lpWMProp->lpMAPIProp, hError, ulFlags, lppMapiError );
}


STDMETHODIMP
WMPROP_SaveChanges(
    LPWMPROP lpWMProp,
    ULONG ulFlags)
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, SaveChanges)) ||
        WMPROP_SaveChanges != lpWMProp->lpVtbl->SaveChanges)
    {
        DebugTraceSc(WMPROP_SaveChanges,  E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /*  We don't want to really call SaveChanges() on the underlying object,
        as this would make an incomplete message still under composition
        actually appear in the folder where it was created.

        If we had some computed properties here, we should do so (since some
        of them might have changed) and return any error encountered in
        doing so. But we don't. So all we need to do is return success. */

    return hrSuccess;
}


STDMETHODIMP
WMPROP_GetProps(
    LPWMPROP lpWMProp,
    LPSPropTagArray lpPropTagArray,
    ULONG ulFlags,
    ULONG * lpcValues,
    LPSPropValue * lppPropArray)
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, GetProps)) ||
        WMPROP_GetProps != lpWMProp->lpVtbl->GetProps)
    {
        DebugTraceSc(WMPROP_GetProps, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }
    
    if ( ulFlags & ~(MAPI_UNICODE) )
    {
        DebugTraceSc(WMPROP_GetProps, MAPI_E_UNKNOWN_FLAGS);
        return ResultFromScode( MAPI_E_UNKNOWN_FLAGS );
    }

    if ( ulFlags & MAPI_UNICODE )
    {
        DebugTraceSc(WMPROP_GetProps, MAPI_E_BAD_CHARWIDTH);
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH );
    }
    
    return lpWMProp->lpMAPIProp->lpVtbl->GetProps(
        lpWMProp->lpMAPIProp, lpPropTagArray, ulFlags,
        lpcValues, lppPropArray);
}


STDMETHODIMP
WMPROP_GetPropList(
    LPWMPROP lpWMProp,
    ULONG ulFlags,
    LPSPropTagArray * lppPropTagArray)
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, GetPropList)) ||
        WMPROP_GetPropList != lpWMProp->lpVtbl->GetPropList)
    {
        DebugTraceSc(WMPROP_GetPropList, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    if ( ulFlags & ~(MAPI_UNICODE) )
    {
        DebugTraceSc(WMPROP_GetProps, MAPI_E_UNKNOWN_FLAGS);
        return ResultFromScode( MAPI_E_UNKNOWN_FLAGS );
    }

    if ( ulFlags & MAPI_UNICODE )
    {
        DebugTraceSc(WMPROP_GetProps, MAPI_E_BAD_CHARWIDTH);
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH );
    }
    
    return lpWMProp->lpMAPIProp->lpVtbl->GetPropList(
        lpWMProp->lpMAPIProp, ulFlags, lppPropTagArray);
}


STDMETHODIMP
WMPROP_SetProps(
    LPWMPROP lpWMProp,
    ULONG cValues,
    LPSPropValue lpPropArray,
    LPSPropProblemArray * lppProblems)
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, SetProps)) ||
        WMPROP_SetProps != lpWMProp->lpVtbl->SetProps)
    {
        DebugTraceSc(WMPROP_SetProps, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    return lpWMProp->lpMAPIProp->lpVtbl->SetProps(lpWMProp->lpMAPIProp,
        cValues, lpPropArray, lppProblems);
}


STDMETHODIMP
WMPROP_DeleteProps(
    LPWMPROP lpWMProp,
    LPSPropTagArray lpPropTagArray,
    LPSPropProblemArray * lppProblems)
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, DeleteProps)) ||
        WMPROP_DeleteProps != lpWMProp->lpVtbl->DeleteProps)
    {
        DebugTraceSc(WMPROP_DeleteProps, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    return lpWMProp->lpMAPIProp->lpVtbl->DeleteProps(lpWMProp->lpMAPIProp,
        lpPropTagArray, lppProblems);
}


STDMETHODIMP
WMPROP_CopyTo(
    LPWMPROP lpWMProp,
    ULONG ciidExclude,
    LPCIID rgiidExclude,
    LPSPropTagArray lpExcludeProps,
    ULONG ulUIParam,
    LPMAPIPROGRESS lpProgress,
    LPCIID lpInterface,
    LPVOID lpDestObj,
    ULONG ulFlags,
    LPSPropProblemArray FAR * lppProblems)
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, CopyTo)) ||
        WMPROP_CopyTo != lpWMProp->lpVtbl->CopyTo)
    {
        DebugTraceSc(WMPROP_CopyTo, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    return lpWMProp->lpMAPIProp->lpVtbl->CopyTo(lpWMProp->lpMAPIProp,
        ciidExclude, rgiidExclude, lpExcludeProps, ulUIParam, 
        lpProgress, lpInterface, lpDestObj, ulFlags, lppProblems);
}


STDMETHODIMP
WMPROP_CopyProps(
    LPWMPROP lpWMProp,
    LPSPropTagArray lpIncludeProps,
    ULONG ulUIParam,
    LPMAPIPROGRESS lpProgress,
    LPCIID lpInterface,
    LPVOID lpDestObj,
    ULONG ulFlags,
    LPSPropProblemArray FAR * lppProblems)
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, CopyProps)) ||
        WMPROP_CopyProps != lpWMProp->lpVtbl->CopyProps)
    {
        DebugTraceSc(WMPROP_CopyProps, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    return lpWMProp->lpMAPIProp->lpVtbl->CopyProps(lpWMProp->lpMAPIProp,
        lpIncludeProps, ulUIParam, lpProgress, lpInterface, lpDestObj,
        ulFlags, lppProblems);
}


STDMETHODIMP
WMPROP_GetNamesFromIDs(
    LPWMPROP lpWMProp,
    LPSPropTagArray * lppPropTags,
    LPGUID lpPropSetGuid,
    ULONG ulFlags,
    ULONG * lpcPropNames,
    LPMAPINAMEID * *lpppPropNames)
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, GetNamesFromIDs)) ||
        WMPROP_GetNamesFromIDs != lpWMProp->lpVtbl->GetNamesFromIDs)
    {
        DebugTraceSc(WMPROP_GetNamesFromIDs, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    return lpWMProp->lpMAPIProp->lpVtbl->GetNamesFromIDs(lpWMProp->lpMAPIProp,
        lppPropTags, lpPropSetGuid, ulFlags, lpcPropNames, lpppPropNames);
}


STDMETHODIMP
WMPROP_GetIDsFromNames(
    LPWMPROP lpWMProp,
    ULONG cPropNames,
    LPMAPINAMEID * lppPropNames,
    ULONG ulFlags,
    LPSPropTagArray * lppPropTags)
{
    /* Validate the object */

    if (FBadUnknown(lpWMProp) ||
        IsBadWritePtr(lpWMProp, sizeof(WMPROP)) ||
        IsBadReadPtr(lpWMProp->lpVtbl, offsetof(WMPROP_Vtbl, GetIDsFromNames)) ||
        WMPROP_GetIDsFromNames != lpWMProp->lpVtbl->GetIDsFromNames)
    {
        DebugTraceSc(WMPROP_GetIDsFromNames, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    return lpWMProp->lpMAPIProp->lpVtbl->GetIDsFromNames(lpWMProp->lpMAPIProp,
        cPropNames, lppPropNames, ulFlags, lppPropTags);
}
