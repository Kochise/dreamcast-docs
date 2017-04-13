/***********************************************************************
 *
 *  ROOT.C
 *
 *
 *  Sample AB Root object
 *      - This file contains the code for implementing the Sample AB
 *      root object and the hierarchy table.
 *
 *  The Root container object is returned via an ABPOpenEntry() with a
 *  0-sized entryid.  It only has a limited set of properties available on
 *  it.  The most useful method on it is GetHierarchyTable() which returns
 *  the root hierarchy associated with this provider.
 *
 *  The hierarchy table has only a single row in it.  The row represents the
 *  single .SAB file which this provider browses.  If a provider wanted to
 *  browse many different lists, it would have multiple rows.
 *
 *  The following routines are implemented in this file:
 *
 *
 *    To implement the Root container object:
 *
 *      HrNewROOT
 *      SetErrorSz
 *      ROOT_QueryInterface
 *      ROOT_AddRef
 *      ROOT_Release
 *      ROOT_GetLastError
 *      ROOT_SaveChanges
 *      ROOT_OpenProperty
 *      ROOT_GetContentsTable
 *      ROOT_GetHierarchyTable
 *      ROOT_OpenEntry
 *      ROOT_CreateEntry
 *      ROOT_CopyEntries
 *      ROOT_DeleteEntries
 *      ROOT_ResolveNames
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/

#include "abp.h"
#include "sampabp.rh"


/*
 *  The structure behind the 'this' pointer
 */
typedef struct _ROOT
{
    const ROOT_Vtbl FAR *   lpVtbl;

    SAB_Wrapped;
    
} ROOT, *LPROOT;


/*
 *  Root vtbl is filled in here
 */
static const ROOT_Vtbl vtblROOT =
{
    ROOT_QueryInterface,
    ROOT_AddRef,
    ROOT_Release,
    ROOT_GetLastError,
    ROOT_SaveChanges,
    (ROOT_GetProps_METHOD *) WRAP_GetProps,
    (ROOT_GetPropList_METHOD *) WRAP_GetPropList,
    ROOT_OpenProperty,
    (ROOT_SetProps_METHOD *) WRAP_SetProps,
    (ROOT_DeleteProps_METHOD *) WRAP_DeleteProps,
    (ROOT_CopyTo_METHOD *) WRAP_CopyTo,
    (ROOT_CopyProps_METHOD *) WRAP_CopyProps,
    (ROOT_GetNamesFromIDs_METHOD *) WRAP_GetNamesFromIDs,
    (ROOT_GetIDsFromNames_METHOD *) WRAP_GetIDsFromNames,
    ROOT_GetContentsTable,
    ROOT_GetHierarchyTable,
    ROOT_OpenEntry,
    ROOT_SetSearchCriteria,
    ROOT_GetSearchCriteria,
    ROOT_CreateEntry,
    ROOT_CopyEntries,
    ROOT_DeleteEntries,
    ROOT_ResolveNames
};


/*
 *  Default properties in this object
 */
enum {  ivalPR_DISPLAY_TYPE = 0,
        ivalPR_OBJECT_TYPE,
        ivalPR_ENTRYID,
        ivalPR_RECORD_KEY,
        ivalPR_SEARCH_KEY,
        ivalPR_DISPLAY_NAME_A,
        ivalPR_CONTAINER_FLAGS,
        cvalMax };

/*
 -  HrNewROOT
 -
 *  Creates a new Root Container object.  This object is created
 *  when an lpABLogon::OpenEntry() is called with a 0-sized entryid.
 *
 *
 */
HRESULT
HrNewROOT(LPABCONT *        lppROOT,
          ULONG *           lpulObjType,
          LPABLOGON         lpABPLogon,
          LPCIID            lpInterface,
          HINSTANCE         hLibrary,
          LPALLOCATEBUFFER  lpAllocBuff,
          LPALLOCATEMORE    lpAllocMore,
          LPFREEBUFFER      lpFreeBuff,
          LPMALLOC          lpMalloc )
{
    LPROOT lpROOT = NULL;
    SCODE scode;
    LPPROPDATA lpPropData = NULL;
    SPropValue spv[cvalMax];
    HRESULT hResult;
    char szDisplayName[MAX_ROOT_NAME];
    LPSTR pszDisplayName = (LPSTR) szDisplayName;
    SCODE sc;
    DIR_ENTRYID eidRoot =   {   {0, 0, 0, 0},
                                MUIDABSAMPLE,
                                SAMP_VERSION,
                                SAMP_DIRECTORY };

    /*  Do I support this interface?? */
    if (lpInterface)
    {
        if (memcmp(lpInterface, &IID_IUnknown, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IMAPIProp, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IMAPIContainer, sizeof(IID)) &&
            memcmp(lpInterface, &IID_IABContainer, sizeof(IID)))
        {
            DebugTraceSc(HrNewROOT, MAPI_E_INTERFACE_NOT_SUPPORTED);
            return ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
        }
    }
    /*
     *  Allocate space for the ROOT structure
     */
    scode = lpAllocBuff (sizeof(ROOT), (LPVOID *) &lpROOT);
    if (FAILED(scode))
    {
        hResult = ResultFromScode(scode);
        goto err;
    }

    lpROOT->lpVtbl = &vtblROOT;
    lpROOT->lcInit = 1;
    lpROOT->hResult = hrSuccess;
    lpROOT->idsLastError = 0;

    lpROOT->hLibrary = hLibrary;
    lpROOT->lpAllocBuff = lpAllocBuff;
    lpROOT->lpAllocMore = lpAllocMore;
    lpROOT->lpFreeBuff = lpFreeBuff;
    lpROOT->lpMalloc = lpMalloc;

    lpROOT->lpABLogon = lpABPLogon;

    /*
     *  Create a property storage object
     */

    scode = CreateIProp((LPIID) &IID_IMAPIPropData,
        lpAllocBuff,
        lpAllocMore,
        lpFreeBuff,
        lpMalloc,
        &lpPropData);

    if (FAILED(scode))
    {
        hResult = ResultFromScode(scode);
        goto err;
    }

    /*
     *  Set up initial set of properties associated with this
     *  container.
     */

    spv[ivalPR_DISPLAY_TYPE].ulPropTag = PR_DISPLAY_TYPE;
    spv[ivalPR_DISPLAY_TYPE].Value.l = 0;           /* undefined for now */

    spv[ivalPR_OBJECT_TYPE].ulPropTag = PR_OBJECT_TYPE;
    spv[ivalPR_OBJECT_TYPE].Value.l = MAPI_ABCONT;

    spv[ivalPR_ENTRYID].ulPropTag = PR_ENTRYID;
    spv[ivalPR_ENTRYID].Value.bin.cb = sizeof(DIR_ENTRYID);
    spv[ivalPR_ENTRYID].Value.bin.lpb = (LPBYTE) &eidRoot;

    spv[ivalPR_RECORD_KEY].ulPropTag = PR_RECORD_KEY;
    spv[ivalPR_RECORD_KEY].Value.bin.cb = sizeof(DIR_ENTRYID);
    spv[ivalPR_RECORD_KEY].Value.bin.lpb = (LPBYTE) &eidRoot;

    spv[ivalPR_SEARCH_KEY].ulPropTag = PR_SEARCH_KEY;
    spv[ivalPR_SEARCH_KEY].Value.bin.cb = sizeof(DIR_ENTRYID);
    spv[ivalPR_SEARCH_KEY].Value.bin.lpb = (LPBYTE) &eidRoot;

    sc = ScLoadString(  IDS_ROOT_NAME,
                        MAX_ROOT_NAME,
                        NULL,
                        hLibrary,
                        (LPSTR *) &pszDisplayName);
    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto out;
    }

    spv[ivalPR_DISPLAY_NAME_A].ulPropTag = PR_DISPLAY_NAME_A;
    spv[ivalPR_DISPLAY_NAME_A].Value.lpszA = szDisplayName;

    spv[ivalPR_CONTAINER_FLAGS].ulPropTag = PR_CONTAINER_FLAGS;
    spv[ivalPR_CONTAINER_FLAGS].Value.l = AB_SUBCONTAINERS;

    /*
     *   Set the default properties
     */
    hResult = lpPropData->lpVtbl->SetProps(lpPropData,
        cvalMax,
        spv,
        NULL);

    if (HR_FAILED(hResult))
    {
        goto err;
    }

    /*
     *  The whole object is set READONLY thus eliminating the need to
     *  set access rights for the individual properties.
     */
    (void) lpPropData->lpVtbl->HrSetObjAccess(lpPropData, IPROP_READONLY);

    lpROOT->lpPropData = (LPMAPIPROP) lpPropData;

    InitializeCriticalSection(&lpROOT->cs);


    /*  We must AddRef the lpABPLogon object since we will be using it
     */
    lpABPLogon->lpVtbl->AddRef(lpABPLogon);

    *lpulObjType = MAPI_ABCONT;
    *lppROOT = (LPVOID) lpROOT;

out:
    DebugTraceResult(HrNewROOT, hResult);
    return hResult;

err:
    /*
     *  free the root object
     */
    lpFreeBuff (lpROOT);

    /*
     *  free the prop data
     */
    if (lpPropData)
        lpPropData->lpVtbl->Release(lpPropData);

    goto out;
    
}

/*************************************************************************
 *
 *
 -  SetErrorIDS
 -
 *  Handles remembering the last error string associated with an object.
 *  This string is retrieved by the method GetLastError()
 *
 *
 */

VOID
SetErrorIDS(LPVOID lpObject, HRESULT hResult, UINT ids)
{
    ((LPROOT) lpObject)->hResult = hResult;
    ((LPROOT) lpObject)->idsLastError = ids;
}

/*
 -  ROOT_QueryInterface
 -
 *  Supports QI'ing to IUnknown, IMAPIProp, IMAPIContainer, and IABContainer.
 *
 */
STDMETHODIMP
ROOT_QueryInterface(LPROOT lpROOT,
                    REFIID lpiid,
                    LPVOID FAR * lppNewObj)
{

    HRESULT hr = hrSuccess;

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  Not large enough
         */
        hr = ResultFromScode(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
                     offsetof(ROOT_Vtbl, QueryInterface)+sizeof(ROOT_QueryInterface_METHOD *)))
    {
        /*
         *  Jump table not derived from IUnknown
         */
        hr = ResultFromScode(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ROOT_QueryInterface != lpROOT->lpVtbl->QueryInterface)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */
        hr = ResultFromScode(E_INVALIDARG);
        goto out;
    }

    Validate_IUnknown_QueryInterface(lpROOT, lpiid, lppNewObj);

    /*  See if the requested interface is one of ours */

    if (memcmp(lpiid, &IID_IUnknown, sizeof(IID)) &&
        memcmp(lpiid, &IID_IMAPIProp, sizeof(IID)) &&
        memcmp(lpiid, &IID_IMAPIContainer, sizeof(IID)) &&
        memcmp(lpiid, &IID_IABContainer, sizeof(IID)))
    {
        *lppNewObj = NULL;      /* OLE requires zeroing [out] parameter */
        hr = ResultFromScode(E_NOINTERFACE);
        goto out;
    }

    /*  We'll do this one. Bump the usage count and return a new pointer. */

    EnterCriticalSection(&lpROOT->cs);
    ++lpROOT->lcInit;
    LeaveCriticalSection(&lpROOT->cs);
    
    *lppNewObj = lpROOT;

out:

    DebugTraceResult(ROOT_QueryInterface, hr);
    return hr;
}

/**************************************************
 *
 -  ROOT_AddRef
 -
 *      Increment lcInit
 *
 */

STDMETHODIMP_(ULONG) ROOT_AddRef(LPROOT lpROOT)
{
    LONG lcInit;

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  Not large enough
         */
        return 1;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
                     offsetof(ROOT_Vtbl, AddRef)+sizeof(ROOT_AddRef_METHOD *)))
    {
        /*
         *  Jump table not derived from IUnknown
         */
        return 1;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ROOT_AddRef != lpROOT->lpVtbl->AddRef)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */
        return 1;
    }

    Validate_IUnknown_AddRef(lpROOT);


    EnterCriticalSection(&lpROOT->cs);
    lcInit = ++lpROOT->lcInit;
    LeaveCriticalSection(&lpROOT->cs);

    return lcInit;
}

/**************************************************
 *
 -  ROOT_Release
 -
 *      Decrement lcInit.
 *      When lcInit == 0, free up the lpROOT structure
 *
 */

STDMETHODIMP_(ULONG) ROOT_Release(LPROOT lpROOT)
{

    LONG lcInit;
    
    /*
     *  Check to see if it can be a ROOT object
     */
    if (IsBadReadPtr(lpROOT, sizeof(ROOT)))
    {
        /*
         *  Not large enough
         */
        return 1;
    }

    /*
     *  Check to see that it's ROOTs vtbl
     */
    if (lpROOT->lpVtbl != &vtblROOT)
    {
        /*
         *  Not my jump table
         */
        return 1;
    }

    Validate_IUnknown_Release(lpROOT);


    EnterCriticalSection(&lpROOT->cs);
    lcInit = --lpROOT->lcInit;
    LeaveCriticalSection(&lpROOT->cs);

    if (lcInit == 0)
    {

        /*
         *  Delete our critical section
         */

        DeleteCriticalSection(&lpROOT->cs);

        /*
         *  Set the vtbl to NULL.  This way the client will find out
         *  real fast if it's calling a method on a released object.  That is,
         *  the client will crash.  Hopefully, this will happen during the
         *  development stage of the client.
         */
        lpROOT->lpVtbl = NULL;

        /*
         *  free the property storage object
         */
        if (lpROOT->lpPropData)
            lpROOT->lpPropData->lpVtbl->Release(lpROOT->lpPropData);

        /*  
         *  Release our reference to the ABLogon object.
         */
        if (lpROOT->lpABLogon)
        {
            lpROOT->lpABLogon->lpVtbl->Release(lpROOT->lpABLogon);
            lpROOT->lpABLogon = NULL;
        }

        /*
         *  Free the object
         */

        lpROOT->lpFreeBuff(lpROOT);
        return 0;
    }

    return lcInit;
}

/*
 -  ROOT_GetLastError
 -
 *      Returns a string associated with the last hResult
 *  returned by the ROOT object.
 *
 */

STDMETHODIMP
ROOT_GetLastError(  LPROOT lpROOT,
                    HRESULT hError,
                    ULONG ulFlags,
                    LPMAPIERROR FAR * lppMapiError )
{
    SCODE scode;
    HRESULT hResult = hrSuccess;
    LPSTR   lpszMessage = NULL;

    /*
     *  Validate parameters
     */

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  Not large enough
         */
        hResult = MakeResult(E_INVALIDARG);

        return hResult;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
        offsetof(ROOT_Vtbl, GetLastError)+sizeof(ROOT_GetLastError_METHOD *)))
    {
        /*
         *  Jump table not derived from IUnknown
         */

        hResult = MakeResult(E_INVALIDARG);

        return hResult;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ROOT_GetLastError != lpROOT->lpVtbl->GetLastError)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */
        hResult = ResultFromScode(E_INVALIDARG);
        DebugTraceResult(ROOT_GetLastError, hResult);
        return hResult;
    }

    Validate_IMAPIProp_GetLastError(lpROOT, hError, ulFlags, lppMapiError);



    /*                              
     *  NOTE:  We don't handle UNICODE yet.  Everything is
     *  assumed to be working in 8-bit char mode.
     */
    if (ulFlags & MAPI_UNICODE)
    {
        hResult = ResultFromScode(MAPI_E_BAD_CHARWIDTH);
        DebugTraceResult(ROOT_GetLastError, hResult);
        return hResult;
    }


    EnterCriticalSection(&lpROOT->cs);
    
    if ((hError != hrSuccess) && (hError == lpROOT->hResult))
    {
        scode = lpROOT->lpAllocBuff( sizeof( MAPIERROR ), lppMapiError );
        if ( FAILED( scode ) )      
        {
            hResult = ResultFromScode(scode);
            goto ret;
        }
        
        ZeroMemory( *lppMapiError, sizeof( MAPIERROR ) );
        
        (*lppMapiError)->ulVersion = MAPI_ERROR_VERSION;

        /*
         *  Get the MAPI Allocated string associated with the last error
         */
        scode = ScLoadString(lpROOT->idsLastError,
                             MAX_ERROR_STRING_LENGTH,
                             lpROOT->lpAllocBuff,
                             lpROOT->hLibrary,
                             &lpszMessage);
        if ( FAILED( scode) )                            
        {
            hResult = ResultFromScode(scode);
            goto ret;
        }
        
        scode = lpROOT->lpAllocMore( lstrlenA( lpszMessage ) + 1, *lppMapiError, 
            &(*lppMapiError)->lpszError );
        if ( FAILED( scode ) )      
        {
            hResult = ResultFromScode(scode);
            goto ret;
        }
        
        lstrcpyA( (*lppMapiError)->lpszError, lpszMessage );
        
        
    } else
    {
        *lppMapiError = NULL;
    }

ret:
    if ( hResult )
    {
        lpROOT->lpFreeBuff( *lppMapiError );
        *lppMapiError = NULL;
    }
    
    lpROOT->lpFreeBuff( lpszMessage );
    LeaveCriticalSection(&lpROOT->cs);

    return hResult;
}

/*
 -  ROOT_SaveChanges
 -
 *  Can't save changes on this object.
 *
 *
 */
STDMETHODIMP
ROOT_SaveChanges(LPROOT lpROOT, ULONG ulFlags)
{

    HRESULT hResult;

    ROOT_ValidateObject(ROOT_SaveChanges, lpROOT);

    Validate_IMAPIProp_SaveChanges(lpROOT, ulFlags);


    hResult = ResultFromScode(E_ACCESSDENIED);

    DebugTraceResult(ROOT_SaveChanges, hResult);
    return hResult;

}

/*
 -  ROOT_OpenProperty
 -
 *
 *  For this object I only need to support opening the hierarchy table.
 *
 */
STDMETHODIMP
ROOT_OpenProperty(  LPROOT lpROOT,
                    ULONG ulPropTag,
                    LPCIID lpiid,
                    ULONG ulInterfaceOptions,
                    ULONG ulFlags,
                    LPUNKNOWN * lppUnk)
{

    HRESULT hResult;

    ROOT_ValidateObject(ROOT_OpenProperty, lpROOT);
    
    Validate_IMAPIProp_OpenProperty(lpROOT, ulPropTag, lpiid,
                            ulInterfaceOptions, ulFlags, lppUnk);

    
    if (ulFlags & MAPI_CREATE)
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
        hResult = ResultFromScode( MAPI_E_BAD_CHARWIDTH );
        goto out;
    }


    switch (ulPropTag)
    {

        case PR_CONTAINER_HIERARCHY:
        {
            /*
             *  Check to see if they're expecting a IMAPITable object
             */
            if (memcmp(lpiid, &IID_IMAPITable, sizeof(IID)))
            {
                hResult = ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
                goto out;
            }

            hResult = ROOT_GetHierarchyTable(lpROOT, 0, (LPMAPITABLE *) lppUnk);

            goto out;
        }

        default:
            break;

    }
    
    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

out:

    DebugTraceResult(ROOT_OpenProperty, hResult);
    return hResult;

}

/*************************************************************************
 *
 *
 -  ROOT_GetContentsTable
 -
 *  There are no contents in the root
 *
 *
 *
 */
STDMETHODIMP
ROOT_GetContentsTable(  LPROOT lpROOT,
                        ULONG ulFlags,
                        LPMAPITABLE * lppTable)
{

    HRESULT hResult;

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  Not large enough
         */
        hResult = MakeResult(E_INVALIDARG);

        return hResult;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
        offsetof(ROOT_Vtbl, GetContentsTable)+sizeof(ROOT_GetContentsTable_METHOD *)))
    {
        /*
         *  Jump table not derived from IUnknown
         */

        hResult = MakeResult(E_INVALIDARG);

        return hResult;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ROOT_GetContentsTable != lpROOT->lpVtbl->GetContentsTable)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */
        hResult = ResultFromScode(E_INVALIDARG);
        DebugTraceResult(ROOT_GetContentsTable, hResult);
        return hResult;
    }

    Validate_IMAPIContainer_GetContentsTable(lpROOT, ulFlags, lppTable);

    
    if ( ulFlags & MAPI_UNICODE )
    {
        hResult = ResultFromScode( MAPI_E_BAD_CHARWIDTH );
        goto out;
    }
    

    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

out:
    DebugTraceResult(ROOT_GetContentsTable, hResult);
    return hResult;

}

/*
 -  ROOT_GetHierarchyTable
 -
 *  Returns the table with just one entry in it.
 *
 *
 *
 */
STDMETHODIMP
ROOT_GetHierarchyTable( LPROOT lpROOT,
                        ULONG ulFlags,
                        LPMAPITABLE * lppTable)
{

    HRESULT hResult = hrSuccess;


    ROOT_ValidateObject(ROOT_GetHierarchyTable, lpROOT);
    Validate_IMAPIContainer_GetHierarchyTable(lpROOT, ulFlags, lppTable);

    
    /*
     *  Since we only have one item in our hierarchy table, CONVENIENT_DEPTH
     *  is equivalent to any other depth level (>1).  So, just ignore the
     *  flag.  MAPI_DEFERRED_ERROR is fine.  We don't ever defer errors.
     */

    /*
     *  Create a View Table for the hierarchy.
     */
    hResult = HrBuildRootHier(lpROOT->lpABLogon, lppTable);

    DebugTraceResult(ROOT_GetHierarchyTable, hResult);
    return hResult;

}

/*
 -  ROOT_OpenEntry
 -
 *  Check parameters and use our logon object's OpenEntry method.
 */
STDMETHODIMP
ROOT_OpenEntry(LPROOT lpROOT,
    ULONG cbEntryID,
    LPENTRYID lpEntryID,
    LPCIID lpInterface,
    ULONG ulFlags,
    ULONG * lpulObjType,
    LPUNKNOWN * lppUnk)
{
    HRESULT hResult;

    
    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  No vtbl found
         */
        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
        offsetof(ROOT_Vtbl, OpenEntry)+sizeof(ROOT_OpenEntry_METHOD *)))
    {
        /*
         *  vtbl cannot hold this method
         */

        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see that it's the correct method
     */
    if (ROOT_OpenEntry != lpROOT->lpVtbl->OpenEntry)
    {
        /*
         *  Not my vtbl
         */
        hResult = ResultFromScode(E_INVALIDARG);
        goto out;
    }

    Validate_IABLogon_OpenEntry(lpROOT, cbEntryID, lpEntryID, lpInterface,
                                    ulFlags, lpulObjType, lppUnk);


    hResult = lpROOT->lpABLogon->lpVtbl->OpenEntry(lpROOT->lpABLogon,
        cbEntryID,
        lpEntryID,
        lpInterface,
        ulFlags,
        lpulObjType,
        lppUnk);
    
out:

    DebugTraceResult(ROOT_OpenEntry, hResult);
    return hResult;

}

/*
 -  ROOT_SetSearchCriteria
 -
 *
 *  Not implemented for this object
 */
STDMETHODIMP
ROOT_SetSearchCriteria(LPROOT lpROOT,
    LPSRestriction lpRestriction,
    LPENTRYLIST lpContainerList,
    ULONG ulSearchFlags)
{
    HRESULT hResult;

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  Not large enough
         */
        hResult = MakeResult(E_INVALIDARG);

        goto out;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
        offsetof(ROOT_Vtbl, SetSearchCriteria)+sizeof(ROOT_SetSearchCriteria_METHOD *)))
    {
        /*
         *  vtbl not large enough to support this method
         */

        hResult = MakeResult(E_INVALIDARG);

        goto out;
    }

    /*
     *  Check to see that it's the correct method
     */
    if (ROOT_SetSearchCriteria != lpROOT->lpVtbl->SetSearchCriteria)
    {
        /*
         *  Not my vtbl
         */
        hResult = ResultFromScode(E_INVALIDARG);
        goto out;
    }

    Validate_IMAPIContainer_SetSearchCriteria(lpROOT, lpRestriction,
                                        lpContainerList, ulSearchFlags);

    
    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

out:
    DebugTraceResult(ROOT_SetSearchCriteria, hResult);
    return hResult;
}

/*
 -  ROOT_GetSearchCriteria
 -
 *
 *  Not implemented for this object
 *
 */
STDMETHODIMP
ROOT_GetSearchCriteria(LPROOT lpROOT,
    ULONG ulFlags,
    LPSRestriction FAR * lppRestriction,
    LPENTRYLIST FAR * lppContainerList,
    ULONG FAR * lpulSearchState)
{
    HRESULT hResult;

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  Not large enough
         */
        hResult = MakeResult(E_INVALIDARG);

        return hResult;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
        offsetof(ROOT_Vtbl, GetSearchCriteria)+sizeof(ROOT_GetSearchCriteria_METHOD *)))
    {
        /*
         *  Jump table not derived from IUnknown
         */

        hResult = MakeResult(E_INVALIDARG);

        return hResult;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ROOT_GetSearchCriteria != lpROOT->lpVtbl->GetSearchCriteria)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */
        hResult = ResultFromScode(E_INVALIDARG);
        DebugTraceResult(ROOT_GetSearchCriteria, hResult);
        return hResult;
    }
    
    Validate_IMAPIContainer_GetSearchCriteria(lpROOT, ulFlags, lppRestriction,
                                            lppContainerList, lpulSearchState);
    
    
    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

    DebugTraceResult(ROOT_GetSearchCriteria, hResult);
    return hResult;
}

/*
 -  ROOT_CreateEntry
 -
 *  New entries cannot be created in the root
 *
 */
STDMETHODIMP
ROOT_CreateEntry(LPROOT lpROOT,
    ULONG cbEntryID,
    LPENTRYID lpEntryID,
    ULONG ulCreateFlags,
    LPMAPIPROP FAR * lppMAPIPropEntry)
{

    HRESULT hResult;

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  No vtbl found
         */
        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
                     offsetof(ROOT_Vtbl, CreateEntry)+sizeof(ROOT_CreateEntry_METHOD *)))
    {
        /*
         *  vtbl not large enough to hold this method
         */

        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ROOT_CreateEntry != lpROOT->lpVtbl->CreateEntry)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */

        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    Validate_IABContainer_CreateEntry(lpROOT, cbEntryID, lpEntryID,
                                ulCreateFlags, lppMAPIPropEntry );


    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

out:
    DebugTraceResult(ROOT_CreateEntry, hResult);
    return hResult;

}

/*
 -  ROOT_CopyEntries
 -
 *  Entries cannot be copied into the root
 *
 *
 *
 */
STDMETHODIMP
ROOT_CopyEntries(LPROOT lpROOT,
    LPENTRYLIST lpEntries,
    ULONG ulUIParam,
    LPMAPIPROGRESS lpProgress,
    ULONG ulFlags)
{

    HRESULT hResult;

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  No vtbl found
         */
        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
                     offsetof(ROOT_Vtbl, CopyEntries)+sizeof(ROOT_CopyEntries_METHOD *)))
    {
        /*
         *  vtbl not large enough to hold this method
         */

        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ROOT_CopyEntries != lpROOT->lpVtbl->CopyEntries)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */

        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    Validate_IABContainer_CopyEntries(lpROOT, lpEntries, ulUIParam,
                                        lpProgress, ulFlags);
    
    
    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

out:
    DebugTraceResult(ROOT_CopyEntries, hResult);
    return hResult;

}

/*
 -  ROOT_DeleteEntries
 -
 *  Entries cannot be deleted from the root
 *
 *
 *
 */
STDMETHODIMP
ROOT_DeleteEntries(LPROOT lpROOT,
    LPENTRYLIST lpEntries,
    ULONG ulFlags)
{

    HRESULT hResult;

    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  No vtbl found
         */
        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
                     offsetof(ROOT_Vtbl, DeleteEntries)+sizeof(ROOT_DeleteEntries_METHOD *)))
    {
        /*
         *  vtbl not large enough to hold this method
         */

        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ROOT_DeleteEntries != lpROOT->lpVtbl->DeleteEntries)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */

        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    Validate_IABContainer_DeleteEntries(lpROOT, lpEntries, ulFlags);



    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

out:
    DebugTraceResult(ROOT_DeleteEntries, hResult);
    return hResult;
}

/*
 -  ROOT_ResolveNames
 -
 *  No special case handling of resolving names within this container
 *
 *
 *
 */
STDMETHODIMP
ROOT_ResolveNames(  LPROOT          lpROOT,
                    LPSPropTagArray lptagaColSet,
                    ULONG           ulFlags,
                    LPADRLIST       lpAdrList,
                    LPFlagList      lpFlagList )
{

    HRESULT hResult;

        
    /*
     *  Check to see if it has a lpVtbl object member
     */
    if (IsBadReadPtr(lpROOT, offsetof(ROOT, lpVtbl)+sizeof(ROOT_Vtbl *)))
    {
        /*
         *  No vtbl found
         */
        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see that the Vtbl is large enough to include this method
     */
    if (IsBadReadPtr(lpROOT->lpVtbl,
                     offsetof(ROOT_Vtbl, ResolveNames)+sizeof(ROOT_ResolveNames_METHOD *)))
    {
        /*
         *  vtbl not large enough to hold this method
         */

        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    /*
     *  Check to see if the method is the same
     */
    if (ROOT_ResolveNames != lpROOT->lpVtbl->ResolveNames)
    {
        /*
         *  Wrong object - the object passed doesn't have this
         *  method.
         */

        hResult = MakeResult(E_INVALIDARG);
        goto out;
    }

    CheckParameters_IABContainer_ResolveNames(lpROOT, lptagaColSet, ulFlags,
                                            lpAdrList, lpFlagList);

    
    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

out:
    DebugTraceResult(ROOT_ResolveNames, hResult);
    return hResult;
}


