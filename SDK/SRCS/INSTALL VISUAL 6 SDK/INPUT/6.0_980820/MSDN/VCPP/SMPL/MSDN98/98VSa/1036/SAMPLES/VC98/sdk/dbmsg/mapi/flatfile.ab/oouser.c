/***********************************************************************
 *
 *  OOUSER.C
 *
 *  Sample AB One Off Mail User object
 *  This file contains the code for implementing the Sample AB
 *  One Off Mail user.
 *
 *  This is the object that is opened in response to the entryID that is
 *  supplied by this provider in the one-off table (see GetOneOffTable() in
 *  ABP.C).  All this object does is supply a display table and any default
 *  values for properties that might need to be there.  One important property
 *  that this object exports is it's PR_TEMPLATEID (see how this object and
 *  the implementation in OOTID.C work together).
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/

#include "abp.h"
#include "sampabp.rh"

/*
 *  Display table control structures for the OneOff property sheet.
 */

/*
 *  This is the edit control on the one-off pane.
 */
static DTBLEDIT editOOUserDisplayName =
{
    sizeof(DTBLEDIT),
    0,
    MAX_DISPLAY_NAME,
    PR_DISPLAY_NAME_A
};

/*
 *  This edit control is for the server name edit box.
 */
static DTBLEDIT editOOUserServer =
{
    sizeof(DTBLEDIT),
    0,
    MAX_SERVER_NAME,
    PR_SERVER_NAME
};

/*
 *  This is the edit control associated with the Share field.
 */
static DTBLEDIT editOOUserShare =
{
    sizeof(DTBLEDIT),
    0,
    MAX_SHARE_NAME,
    PR_SHARE_NAME
};

/*
 *  This is the edit control associated with the path.
 */
static DTBLEDIT editOOUserPath =
{
    sizeof(DTBLEDIT),
    0,
    MAX_PATH,
    PR_PATH_NAME
};

/*
 *  General Property Page definition
 */
static DTCTL rgdtctlOOUserGeneral[] =
{
    /* general property page */
    /*
     *  Although this control is not absolutely required,
     *  we suggest filling it in.  This non-requirement
     *  will probibly change before we actually ship!
     */
    {DTCT_PAGE, 0, NULL, 0, NULL, 0, &dtblpage},

    /* display name static control and edit control */
    /*
     *  Note that this edit control is editable and required
     */
    {DTCT_LABEL, 0, NULL, 0, NULL,
        IDC_STATIC_CONTROL, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE|DT_REQUIRED, NULL, 0, szNoFilter,
        IDC_OOUSER_DISPLAY_NAME, &editOOUserDisplayName},

    /* group box */
    {DTCT_GROUPBOX, 0, NULL, 0, NULL,
        IDC_STATIC_CONTROL, &dtblgroupbox},
    /*
     *  The following three label/edit pairs make up the
     *  calculated email address (see OOTID.C's SaveChanges() method).
     */
    /* server static control and edit control */
    
    {DTCT_LABEL, 0, NULL, 0, NULL,
        IDC_STATIC_CONTROL, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE | DT_REQUIRED, NULL, 0, szFileNameFilter,
        IDC_OOUSER_SERVER, &editOOUserServer},

    /* share static control and edit control */
    {DTCT_LABEL, 0, NULL, 0, NULL,
        IDC_STATIC_CONTROL, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE | DT_REQUIRED, NULL, 0, szFileNameFilter,
        IDC_OOUSER_SHARE, &editOOUserShare},

    /* path static control and edit control */
    {DTCT_LABEL, 0, NULL, 0, NULL,
        IDC_STATIC_CONTROL, &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter,
        IDC_OOUSER_PATH, &editOOUserPath},
};

/*
 *  The OneOff property sheet definition.  This is an array of
 *  property sheet pages that gets passed to BuildDisplayTable().
 */
static DTPAGE rgdtpage[] =
{
    {
        sizeof(rgdtctlOOUserGeneral) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(OOUserGeneralPage),
        "",
        rgdtctlOOUserGeneral
    },
};




/*
 *  Declaration of IMailUser object implementation
 */
#undef  INTERFACE
#define INTERFACE   struct _ABOOUSER

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, ABOOUSER_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAILUSER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, ABOOUSER_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAILUSER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(ABOOUSER_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IMAILUSER_METHODS(IMPL)
};

/*
 *  Structure behind the 'this'
 */

typedef struct _ABOOUSER
{
    const ABOOUSER_Vtbl FAR * lpVtbl;

    SAB_Wrapped;

} ABOOUSER, *LPABOOUSER;


#define ABOOUSER_ValidateObject(Method, pThis)      \
{                                                   \
    HRESULT hResult;                                \
    if (IsBadReadPtr(pThis, sizeof(ABOOUSER)))      \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABOOUSER##_##Method, hResult); \
        return hResult;                             \
    }                                               \
                                                    \
    if (pThis->lpVtbl != &vtblABOOUSER)             \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABOOUSER##_##Method, hResult); \
        return hResult;                             \
    }                                               \
}

/*
 *  ABOOUser vtbl is set up here.
 */
static const ABOOUSER_Vtbl vtblABOOUSER =
{
    (ABOOUSER_QueryInterface_METHOD *)  ABU_QueryInterface,
    (ABOOUSER_AddRef_METHOD *)          WRAP_AddRef,
    (ABOOUSER_Release_METHOD *)         WRAP_Release,
    (ABOOUSER_GetLastError_METHOD *)    WRAP_GetLastError,
    (ABOOUSER_SaveChanges_METHOD *)     WRAP_SaveChanges,
    (ABOOUSER_GetProps_METHOD *)        WRAP_GetProps,
    (ABOOUSER_GetPropList_METHOD *)     WRAP_GetPropList,
    ABOOUSER_OpenProperty,
    (ABOOUSER_SetProps_METHOD *)        WRAP_SetProps,
    (ABOOUSER_DeleteProps_METHOD *)     WRAP_DeleteProps,
    (ABOOUSER_CopyTo_METHOD *)          WRAP_CopyTo,
    (ABOOUSER_CopyProps_METHOD *)       WRAP_CopyProps,
    (ABOOUSER_GetNamesFromIDs_METHOD *) WRAP_GetNamesFromIDs,
    (ABOOUSER_GetIDsFromNames_METHOD *) WRAP_GetIDsFromNames,
};

enum {  ivaloousrPR_DISPLAY_TYPE = 0,
        ivaloousrPR_ADDRTYPE_A,
        ivaloousrPR_TEMPLATEID,
        cvaloousrMax };

SizedSPropTagArray( cvaloousrMax, tagaABOOUSERAccess) =
{
      cvaloousrMax
    , { PR_DISPLAY_TYPE
      , PR_ADDRTYPE_A
      , PR_TEMPLATEID
      }
};

ULONG   rgulABOOUSERAccess[cvaloousrMax] =
{
      IPROP_READONLY | IPROP_CLEAN  /* PR_DISPLAY_TYPE */
    , IPROP_READONLY | IPROP_CLEAN  /* PR_ADDRTYPE_A */
    , IPROP_READONLY | IPROP_CLEAN  /* PR_TEMPLATEID */
};

/*************************************************************************
 *
 -  NewSampOOUser
 -
 *  Creates the IMailUser associated with a one off mail user.
 *
 *
 */
HRESULT
HrNewSampOOUser(LPMAILUSER *        lppMAPIPropEntry,
                ULONG *             lpulObjType,
                ULONG               cbEntryID,
                LPENTRYID           lpEntryID,
                LPABLOGON           lpABPLogon,
                LPCIID              lpInterface,
                HINSTANCE           hLibrary,
                LPALLOCATEBUFFER    lpAllocBuff,
                LPALLOCATEMORE      lpAllocMore,
                LPFREEBUFFER        lpFreeBuff,
                LPMALLOC            lpMalloc )
{
    LPABOOUSER lpABOOUser = NULL;
    SCODE sc;
    HRESULT hr = hrSuccess;
    LPPROPDATA lpPropData = NULL;
    SPropValue spv[4];

    /*  Do I support this interface?? */
    if (lpInterface)
    {
        if (memcmp(lpInterface, &IID_IMailUser, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IMAPIProp, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IUnknown, sizeof(IID)))
        {
            DebugTraceSc(HrNewSampOOUser, MAPI_E_INTERFACE_NOT_SUPPORTED);
            return ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
        }
    }

    /*
     *  Allocate space for the ABOOUser structure
     */
    sc = lpAllocBuff(sizeof(ABOOUSER), (LPVOID *) &lpABOOUser);

    if (FAILED(sc))
    {
        hr = ResultFromScode(sc);
        goto err;
    }

    lpABOOUser->lpVtbl = &vtblABOOUSER;
    lpABOOUser->lcInit = 1;
    lpABOOUser->hResult = hrSuccess;
    lpABOOUser->idsLastError = 0;
    lpABOOUser->hLibrary = hLibrary;
    lpABOOUser->lpAllocBuff = lpAllocBuff;
    lpABOOUser->lpAllocMore = lpAllocMore;
    lpABOOUser->lpFreeBuff = lpFreeBuff;
    lpABOOUser->lpMalloc = lpMalloc;
    lpABOOUser->lpABLogon = lpABPLogon;

    /*
     *  Create property storage object.
     */

    sc = CreateIProp(
        (LPIID) &IID_IMAPIPropData,
        lpAllocBuff,
        lpAllocMore,
        lpFreeBuff,
        lpMalloc,
        &lpPropData);

    if (FAILED(sc))
    {
        hr = ResultFromScode(sc);
        goto err;
    }

    /*
     *  Set up the initial set of properties
     */

    spv[0].ulPropTag = PR_DISPLAY_TYPE;
    spv[0].Value.l = DT_MAILUSER;

    spv[1].ulPropTag = PR_OBJECT_TYPE;
    spv[1].Value.l = MAPI_MAILUSER;

    /*
     *  Note that we're using our entryID for our templateID.
     *  This is a really simple way to implement templateIDs.
     *  (See OOTID.C)
     */
    spv[2].ulPropTag = PR_TEMPLATEID;
    spv[2].Value.bin.cb = sizeof(OOUSR_ENTRYID);
    spv[2].Value.bin.lpb = (LPBYTE) lpEntryID;

    spv[3].ulPropTag = PR_ADDRTYPE;
    spv[3].Value.lpszA = lpszEMT;

    /*
     *   Set the default properties
     */
    hr = lpPropData->lpVtbl->SetProps(
        lpPropData,
        sizeof(spv) / sizeof(SPropValue),
        spv,
        NULL);

    if (HR_FAILED(hr))
    {
        goto err;
    }

    /*
    *   We mark these properties READONLY so that they can't be changed by
    *   the client.
    */
    (void) lpPropData->lpVtbl->HrSetPropAccess(lpPropData,
                                (LPSPropTagArray) &tagaABOOUSERAccess,
                                rgulABOOUSERAccess);

    (void) lpPropData->lpVtbl->HrSetObjAccess(lpPropData, IPROP_READWRITE);

    lpABOOUser->lpPropData = (LPMAPIPROP) lpPropData;

    InitializeCriticalSection(&lpABOOUser->cs);

    /*  We must AddRef the lpABPLogon object since we will be using it
     */
    lpABPLogon->lpVtbl->AddRef(lpABPLogon);

    *lppMAPIPropEntry = (LPVOID) lpABOOUser;
    *lpulObjType = MAPI_MAILUSER;

out:

    DebugTraceResult(HrNewSampOOUser, hr);
    return hr;

err:

    if (lpPropData)
        lpPropData->lpVtbl->Release(lpPropData);

    lpFreeBuff( lpABOOUser );

    goto out;
}


/*************************************************************************
 *
 -  ABOOUSER_OpenProperty
 -
 *
 *  This is how we get the display table associated with this one-off's
 *  details screen.
 */
STDMETHODIMP
ABOOUSER_OpenProperty(
    LPABOOUSER lpABOOUser,
    ULONG ulPropTag,
    LPCIID lpiid,
    ULONG ulInterfaceOptions,
    ULONG ulFlags,
    LPUNKNOWN * lppUnk)
{

    /*
     *  Since the default is that we do not support opening this
     *  object, we can initialize our hResult here.
     */
    HRESULT hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

    ABOOUSER_ValidateObject(OpenProperty, lpABOOUser);

    Validate_IMAPIProp_OpenProperty(lpABOOUser, ulPropTag, lpiid,
                            ulInterfaceOptions, ulFlags, lppUnk);


    if (ulInterfaceOptions & ~MAPI_UNICODE )
    {
        /*
         *  Only UNICODE flag should be set for any of the objects that might
         *  be returned from this object.
         */
        hResult = ResultFromScode(MAPI_E_UNKNOWN_FLAGS);
        goto ret;
    }
    
    if ( ulInterfaceOptions & MAPI_UNICODE )
    {
        hResult = ResultFromScode( MAPI_E_BAD_CHARWIDTH );
        goto ret;
    }
    

    
    if (ulFlags & MAPI_CREATE)
    {
        /*
         *  Don't support creating any sub-objects
         */
        hResult = ResultFromScode(E_ACCESSDENIED);
        goto ret;
    }
    
    
    /*  Check to see if I need a display table*/

    if (ulPropTag == PR_DETAILS_TABLE)
    {
        /* Looking for the display table */
        /* Check to see if they're expecting a table interface*/

        if (memcmp(lpiid, &IID_IMAPITable, sizeof(IID)))
        {
            /*
             *  This provider will only export a table interface for
             *  PR_DETAILS_TABLE
             */
            hResult = ResultFromScode(E_NOINTERFACE);
            goto ret;
        }

        /* Create a display table */

        hResult = BuildDisplayTable(
            lpABOOUser->lpAllocBuff,
            lpABOOUser->lpAllocMore,
            lpABOOUser->lpFreeBuff,
            lpABOOUser->lpMalloc,
            lpABOOUser->hLibrary,
            sizeof(rgdtpage) / sizeof(DTPAGE),
            rgdtpage,
            0,
            (LPMAPITABLE *) lppUnk,
            NULL);

        if (HR_FAILED(hResult))
        {
            goto ret;
        }

        /*
         * We're succeeding. Ensure our hResult is set properly (i.e. mask warnings)
         */

        hResult = hrSuccess;
    }

ret:
    DebugTraceResult(ABOOUSER_OpenProperty, hResult);
    return hResult;
}
