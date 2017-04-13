/***********************************************************************
 *
 *  ABSEARCH.C
 *
 *  Sample AB directory container Search object
 *
 *  This file contains the code for implementing the Sample AB
 *  directory container search object.  Also known as advanced
 *  search.
 *
 *  This search object was retrieved by OpenProperty on PR_SEARCH on the
 *  AB directory found in ABCONT.C.
 *
 *  The following routines are implemented in this file:
 *
 *      HrNewSearch
 *      ABSRCH_Release
 *      ABSRCH_SaveChanges
 *      ABSRCH_OpenProperty
 *      ABSRCH_GetSearchCriteria
 *
 *      HrGetSearchDialog
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/

#include "abp.h"
#include "sampabp.rh"
#include <smpab.h>


/*
 *  Proptags used only in this module
 */
#define PR_ANR_STRING               PROP_TAG(PT_STRING8,0x6602)


/*
 *  Structure for the 'this'
 */

typedef struct _ABSRCH
{
    const ABSRCH_Vtbl FAR * lpVtbl;

    SAB_Wrapped;

    /*  Private data */

    LPSPropValue lpRestrictData;
    
} ABSRCH, *LPABSRCH;



/* Display table control structures for the Search property sheet. */

/*
 *  The Sample AB exposes an 'advanced' search dialog.  The following
 *  structures define it's layout.
 */

/*
 *  The edit control that will have the name to be search for on it.
 */
#define MAX_SEARCH_NAME                 50

DTBLEDIT editSearchName =
{
    sizeof(DTBLEDIT),
    0,
    MAX_SEARCH_NAME,
    PR_ANR_STRING
};

/*
 *  Display table pages for Search property sheet
 */
DTCTL rgdtctlSearchGeneral[] =
{

    /*
     *  Defines the name of this Pane.
     */
    {DTCT_PAGE, 0, NULL, 0, NULL, 0, &dtblpage},

    /* group box control */
    {DTCT_GROUPBOX, 0, NULL, 0, NULL, IDC_STATIC_CONTROL,
        &dtblgroupbox},

    /* control and edit control */
    {DTCT_LABEL, 0, NULL, 0, NULL, IDC_STATIC_CONTROL,
        &dtbllabel},
    {DTCT_EDIT, DT_EDITABLE, NULL, 0, szNoFilter, IDC_SEARCH_NAME,
        &editSearchName},
};

/*
 *  Actual definition of the set of pages that make up this advanced search
 *  dialog.  Note that there's no limit to the number of pages that can be
 *  displayed.  This sample AB, however, only exposes on page.
 */
DTPAGE rgdtpageSearch[] =
{
    {
        sizeof(rgdtctlSearchGeneral) / sizeof(DTCTL),
        (LPTSTR) MAKEINTRESOURCE(SearchGeneralPage),
        "",
        rgdtctlSearchGeneral
    }
};

/*
 *  ABSearch vtbl is filled in here.
 */
ABSRCH_Vtbl vtblABSRCH =
{
    (ABSRCH_QueryInterface_METHOD *)        ROOT_QueryInterface,
    (ABSRCH_AddRef_METHOD *)                ROOT_AddRef,    
    ABSRCH_Release,
    (ABSRCH_GetLastError_METHOD *)          ROOT_GetLastError,
    ABSRCH_SaveChanges,
    (ABSRCH_GetProps_METHOD *)              WRAP_GetProps,
    (ABSRCH_GetPropList_METHOD *)           WRAP_GetPropList,
    ABSRCH_OpenProperty,
    (ABSRCH_SetProps_METHOD *)              WRAP_SetProps,
    (ABSRCH_DeleteProps_METHOD *)           WRAP_DeleteProps,
    (ABSRCH_CopyTo_METHOD *)                WRAP_CopyTo,
    (ABSRCH_CopyProps_METHOD *)             WRAP_CopyProps,
    (ABSRCH_GetNamesFromIDs_METHOD *)       WRAP_GetNamesFromIDs,
    (ABSRCH_GetIDsFromNames_METHOD *)       WRAP_GetIDsFromNames,
    (ABSRCH_GetContentsTable_METHOD *)      ROOT_GetContentsTable,
    (ABSRCH_GetHierarchyTable_METHOD *)     ABC_GetHierarchyTable,
    (ABSRCH_OpenEntry_METHOD *)             ROOT_OpenEntry,
    (ABSRCH_SetSearchCriteria_METHOD *)     ROOT_SetSearchCriteria,
    ABSRCH_GetSearchCriteria,
};



HRESULT HrGetSearchDialog(LPABSRCH lpABSearch, LPMAPITABLE * lppSearchTable);

/*
 -  HrNewSearch
 -
 *  Creates an advanced search object
 *
 *
 */


/*
 *  Properties that are initially set on this object
 */
enum {  ivalabsrchPR_ANR_STRING = 0,
        cvalabsrchMax };

HRESULT
HrNewSearch(LPMAPICONTAINER *   lppABSearch,
            LPABLOGON           lpABLogon,
            LPCIID              lpInterface,
            HINSTANCE           hLibrary,
            LPALLOCATEBUFFER    lpAllocBuff,
            LPALLOCATEMORE      lpAllocMore,
            LPFREEBUFFER        lpFreeBuff,
            LPMALLOC            lpMalloc )
{
    HRESULT hResult = hrSuccess;
    LPABSRCH lpABSearch = NULL;
    SCODE sc;
    LPPROPDATA lpPropData = NULL;
    SPropValue spv[cvalabsrchMax];
    
    /*  Do I support this interface?? */
    if (lpInterface)
    {
        if (memcmp(lpInterface, &IID_IMAPIContainer, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IMAPIProp, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IUnknown, sizeof(IID)))
        {
            DebugTraceSc(HrNewSearch, MAPI_E_INTERFACE_NOT_SUPPORTED);
            return ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
        }
    }

    /*
     *  Allocate space for the directory container structure
     */

    sc = lpAllocBuff( sizeof(ABSRCH), (LPVOID *) &lpABSearch );

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto err;
    }

    lpABSearch->lpVtbl = &vtblABSRCH;
    lpABSearch->lcInit = 1;
    lpABSearch->hResult = hrSuccess;
    lpABSearch->idsLastError = 0;

    lpABSearch->hLibrary = hLibrary;
    lpABSearch->lpAllocBuff = lpAllocBuff;
    lpABSearch->lpAllocMore = lpAllocMore;
    lpABSearch->lpFreeBuff = lpFreeBuff;
    lpABSearch->lpMalloc = lpMalloc;

    lpABSearch->lpABLogon = lpABLogon;
    lpABSearch->lpRestrictData = NULL;

    /*
     *  Create property storage object
     */

    sc = CreateIProp((LPIID) &IID_IMAPIPropData,
        lpAllocBuff,
        lpAllocMore,
        lpFreeBuff,
        lpMalloc,
        &lpPropData);

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto err;
    }

    spv[ivalabsrchPR_ANR_STRING].ulPropTag = PR_ANR_STRING;
    spv[ivalabsrchPR_ANR_STRING].Value.lpszA = "";

    /*
     *   Set the default properties
     */
    hResult = lpPropData->lpVtbl->SetProps(lpPropData,
        cvalabsrchMax,
        spv,
        NULL);

    InitializeCriticalSection(&lpABSearch->cs);

    /*  We must AddRef the lpABLogon object since we will be using it
     */
    lpABLogon->lpVtbl->AddRef(lpABLogon);

    lpABSearch->lpPropData = (LPMAPIPROP) lpPropData;
    *lppABSearch = (LPMAPICONTAINER) lpABSearch;

out:

    DebugTraceResult(HrNewSearch, hResult);
    return hResult;

err:
    /*
     *  free the ABContainer object
     */
    lpFreeBuff( lpABSearch );

    /*
     *  free the property storage object
     */
    if (lpPropData)
        lpPropData->lpVtbl->Release(lpPropData);

    goto out;
}


/*
 -  ABSRCH_Release
 -
 *  Decrement lcInit.
 *      When lcInit == 0, free up the lpABSearch structure
 *
 */

STDMETHODIMP_(ULONG)
ABSRCH_Release(LPABSRCH lpABSearch)
{

    long lcInit;
    
    /*
     *  Check to see if it has a jump table
     */
    if (IsBadReadPtr(lpABSearch, sizeof(ABSRCH)))
    {
        /*
         *  No jump table found
         */
        return 1;
    }

    /*
     *  Check to see that it's the correct jump table
     */
    if (lpABSearch->lpVtbl != &vtblABSRCH)
    {
        /*
         *  Not my jump table
         */
        return 1;
    }

    Validate_IUnknown_Release(lpABSearch);


    EnterCriticalSection(&lpABSearch->cs);
    lcInit = --lpABSearch->lcInit;
    LeaveCriticalSection(&lpABSearch->cs);

    if (lcInit == 0)
    {

        /*
         *  Get rid of the lpPropData
         */
        if (lpABSearch->lpPropData)
            lpABSearch->lpPropData->lpVtbl->Release(lpABSearch->lpPropData);

        /*
         *  Free up the restriction data
         */
        lpABSearch->lpFreeBuff(lpABSearch->lpRestrictData);

        /*  
         *  Release our reference to the ABLogon object.
         */
        if (lpABSearch->lpABLogon)
        {
            lpABSearch->lpABLogon->lpVtbl->Release(lpABSearch->lpABLogon);
            lpABSearch->lpABLogon = NULL;
        }

        /*
         *  Destroy the critical section for this object
         */

        DeleteCriticalSection(&lpABSearch->cs);

        /*
         *  Set the Jump table to NULL.  This way the client will find out
         *  real fast if it's calling a method on a released object.  That is,
         *  the client will crash.  Hopefully, this will happen during the
         *  development stage of the client.
         */
        lpABSearch->lpVtbl = NULL;

        /*
         *  Need to free the object
         */

        lpABSearch->lpFreeBuff(lpABSearch);
        return 0;
    }

    return lpABSearch->lcInit;

}


/*
 -  ABSRCH_SaveChanges
 -
 *  This is used to save changes associated with the search dialog
 *  in order to get the advanced search restriction and to save changes
 *  associated with the container details dialog.
 *
 */
SPropTagArray tagaANR_INT =
{
    1,
    {
        PR_ANR_STRING
    }
};

STDMETHODIMP
ABSRCH_SaveChanges(LPABSRCH lpABSearch, ULONG ulFlags)
{
    HRESULT hResult;
    ULONG ulCount;
    LPSPropValue lpspv = NULL;
    LPPROPDATA lpPropData = (LPPROPDATA) lpABSearch->lpPropData;

    
    ABSRCH_ValidateObject(SaveChanges, lpABSearch);
    
    Validate_IMAPIProp_SaveChanges(lpABSearch, ulFlags);


    EnterCriticalSection(&lpABSearch->cs);

    /*
     *  Is there a PR_ANR_STRING??
     */
    hResult = lpPropData->lpVtbl->GetProps(lpPropData,
        &tagaANR_INT,
        0,      /* ansi */
        &ulCount,
        &lpspv);
    if (HR_FAILED(hResult))
    {
        goto ret;
    }

    if ((lpspv->ulPropTag == PR_ANR_STRING) && (lpspv->Value.lpszA[0] != '\0'))
    {
        /*
         * save away the information to build up the new restriction
         */

        /*  Free any existing data */
        if (lpABSearch->lpRestrictData)
        {
            lpABSearch->lpFreeBuff(lpABSearch->lpRestrictData);
        }

        lpABSearch->lpRestrictData = lpspv;
        lpspv = NULL;
    }

ret:

    LeaveCriticalSection(&lpABSearch->cs);

    lpABSearch->lpFreeBuff(lpspv);
    DebugTraceResult(ABSRCH_SaveChanges, hResult);
    return hResult;
}

/*************************************************************************
 *
 -  ABSRCH_OpenProperty
 -
 *
 *  This method allows the opening of the following object:
 *
 *  PR_DETAILS_TABLE        :-  Gets the display table associated with
 *                              the advanced search dialog.
 */
STDMETHODIMP
ABSRCH_OpenProperty(LPABSRCH lpABSearch,
    ULONG ulPropTag,
    LPCIID lpiid,
    ULONG ulInterfaceOptions,
    ULONG ulFlags,
    LPUNKNOWN * lppUnk)
{
    HRESULT hResult;

    ABSRCH_ValidateObject(OpenProperty, lpABSearch);
    
    Validate_IMAPIProp_OpenProperty(lpABSearch, ulPropTag, lpiid,
                            ulInterfaceOptions, ulFlags, lppUnk);

    /*
     *  Check for flags we can't support
     */

    if (ulFlags & (MAPI_CREATE|MAPI_MODIFY))
    {
        hResult = ResultFromScode(E_ACCESSDENIED);
        goto out;
    }
        
    if (ulInterfaceOptions & ~MAPI_UNICODE)
    {
        /*
         *  Only UNICODE flag should be set for any of the objects that might
         *  be returned from this object.
         */
        
        hResult = ResultFromScode(MAPI_E_UNKNOWN_FLAGS);
        goto out;
    }
    
    if ( ulInterfaceOptions & MAPI_UNICODE )
    {
        hResult = ResultFromScode(MAPI_E_BAD_CHARWIDTH);
        DebugTraceArg( ABSRCH_OpenProperty, "bad character width" );
        goto out;
        
    }


    /*
     *  Details for this Search object
     */

    if (ulPropTag == PR_DETAILS_TABLE)
    {
        if (!memcmp(lpiid, &IID_IMAPITable, sizeof(IID)))
        {
            hResult = HrGetSearchDialog(lpABSearch, (LPMAPITABLE *) lppUnk);

            goto out;
        }

    } 

    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

out:

    DebugTraceResult(ABSRCH_OpenProperty, hResult);
    return hResult;


}

/*
 -  ABSRCH_GetSearchCriteria
 -
 *  Generates the restriction associated with the data from
 *  the advanced search dialog.  This restriction is subsequently
 *  applied to the contents table retrieved from this container.
 */
STDMETHODIMP
ABSRCH_GetSearchCriteria(   LPABSRCH lpABSearch,
                        ULONG   ulFlags,
                        LPSRestriction FAR * lppRestriction,
                        LPENTRYLIST FAR * lppContainerList,
                        ULONG FAR * lpulSearchState)
{
    HRESULT hResult = hrSuccess;
    SCODE sc;
    LPSRestriction lpRestriction = NULL;
    LPSPropValue lpPropANR = NULL;
    LPSTR lpszPartName;
    LPSTR lpszRestrName;

    ABSRCH_ValidateObject(GetSearchCriteria, lpABSearch);
    
    Validate_IMAPIContainer_GetSearchCriteria(lpABSearch, ulFlags,
                                lppRestriction, lppContainerList, 
                                lpulSearchState);

    if (!lpABSearch->lpRestrictData)
    {
        hResult = ResultFromScode(MAPI_E_NOT_INITIALIZED);

        if (lppRestriction)
            *lppRestriction = NULL;

        if (lppContainerList)
            *lppContainerList = NULL;

        if (lpulSearchState)
            *lpulSearchState = 0L;

        DebugTraceResult(ABSRCH_GetSearchCriteria, hResult);
        return hResult;
    }

    if (ulFlags & MAPI_UNICODE)
    {
        hResult = ResultFromScode(MAPI_E_BAD_CHARWIDTH);
        
        DebugTraceResult(ABSRCH_GetSearchCriteria, hResult);
        return hResult;
    }


    /*
     *  Entering state dependant section
     */
    EnterCriticalSection(&lpABSearch->cs);

    /*
     *  Ok, now build up a restriction using lpRestrictData (an LPSPropValue)
     */

    sc = lpABSearch->lpAllocBuff(sizeof(SRestriction), &lpRestriction);
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto err;
    }

    sc = lpABSearch->lpAllocMore(sizeof(SPropValue), lpRestriction, &lpPropANR);
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto err;

    }

    lpszRestrName = lpABSearch->lpRestrictData->Value.lpszA;

    sc = lpABSearch->lpAllocMore(lstrlenA(lpszRestrName)+1,
        lpRestriction,
        &lpszPartName);
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto err;
    }

    lstrcpyA(lpszPartName, lpszRestrName);

    lpPropANR->ulPropTag = PR_ANR;
    lpPropANR->Value.LPSZ = lpszPartName;

    lpRestriction->rt = RES_PROPERTY;
    lpRestriction->res.resProperty.relop = RELOP_EQ;
    lpRestriction->res.resProperty.ulPropTag = PR_ANR;
    lpRestriction->res.resProperty.lpProp = lpPropANR;

    *lppRestriction = lpRestriction;

    /*
     *  The returned SearchState is set to 0 because none
     *  of the defined states match what's going on.
     */
    if (lpulSearchState)
        *lpulSearchState = 0;

out:
    LeaveCriticalSection(&lpABSearch->cs);

    DebugTraceResult(ABSRCH_GetSearchCriteria, hResult);
    return hResult;

err:
    lpABSearch->lpFreeBuff(lpRestriction);

    goto out;
}

/*
 -  HrGetSearchDialog
 -
 *
 *  Builds a display table for the search dialog.
 */

HRESULT
HrGetSearchDialog(LPABSRCH lpABSearch, LPMAPITABLE * lppSearchTable)
{
    HRESULT hResult;

    /* Create a display table */
    hResult = BuildDisplayTable(
            lpABSearch->lpAllocBuff,
            lpABSearch->lpAllocMore,
            lpABSearch->lpFreeBuff,
            lpABSearch->lpMalloc,
            lpABSearch->hLibrary,
            sizeof(rgdtpageSearch) / sizeof(DTPAGE),
            rgdtpageSearch,
            0,
            lppSearchTable,
            NULL);

    DebugTraceResult(ABSRCH_GetSearchDialog, hResult);
    return hResult;
}

