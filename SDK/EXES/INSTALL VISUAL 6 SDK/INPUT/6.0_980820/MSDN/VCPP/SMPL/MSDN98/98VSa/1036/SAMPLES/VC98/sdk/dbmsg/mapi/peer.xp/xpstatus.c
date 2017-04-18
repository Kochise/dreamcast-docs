/*
 -  X P S T A T U S . C
 -
 *  Purpose:
 *      Sample transport provider status interface code.  This module
 *      contains the following Transport SPI entry points:
 *
 *          OpenStatusEntry()
 *
 *      The Status Object methods implemented in this module are:
 *
 *          QueryInterface,
 *          AddRef,
 *          Release,
 *          GetLastError,
 *          GetProps,
 *          GetPropList,
 *          SettingsDialog,
 *          FlushQueues,
 *
 *      Additional support functions found here:
 *
 *          HrBuildTransportStatus
 *          HrUpdateTransportStatus
 *          NewSOB
 *          HrLoadStatusString
 *          MapScodeSz
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

//$BUG  Invalid flags should return MAPI_E_UNKNOWN_FLAGS!

#include "xppch.h"
#include "xpresrc.h"


#define MAX_STRING          8192
#define MAX_RESRC_STRING    256

/* Declared in xpbase.c */

extern sptLogonArray;

/*  SOB IMAPIProp jump table */

SOB_Vtbl vtblSOB =
{
    SOB_QueryInterface,
    SOB_AddRef,
    SOB_Release,
    SOB_GetLastError,
    SOB_SaveChanges,
    SOB_GetProps,
    SOB_GetPropList,
    SOB_OpenProperty,
    SOB_SetProps,
    SOB_DeleteProps,
    SOB_CopyTo,
    SOB_CopyProps,
    SOB_GetNamesFromIDs,
    SOB_GetIDsFromNames,
    SOB_ValidateState,
    SOB_SettingsDialog,
    SOB_ChangePassword,
    SOB_FlushQueues,
};

/*  Static properties. In this case the array of Property Tags available
    from the Status object if opened.  The PR_RESOURCE_PATH must be last
    because we will not tell the client about this property if it isn't
    set in the Logon dialog.  Being last makes GetPropList() easier to do. */

/* Number of columns in Status row. */

#define NUM_STATUS_ROW_PROPS 10

const static SizedSPropTagArray(NUM_STATUS_ROW_PROPS, sptaStatusRow) =
{
    NUM_STATUS_ROW_PROPS,
    {
        PR_RESOURCE_METHODS,
        PR_PROVIDER_DISPLAY,
        PR_DISPLAY_NAME,
        PR_IDENTITY_DISPLAY,
        PR_IDENTITY_ENTRYID,
        PR_IDENTITY_SEARCH_KEY,
        PR_STATUS_CODE,
        PR_STATUS_STRING,
        PR_OBJECT_TYPE,
        PR_RESOURCE_PATH
    }
};

/* List of IID's we support on open/query */

#define N_IID 3
static const LPIID lpStatusFamilyIID[N_IID] =
{
    (LPIID) &IID_IUnknown,      /* IUnknown is everyone's parent */
    (LPIID) &IID_IMAPIProp,     /* IMAPIProp follows from this   */
    (LPIID) &IID_IMAPIStatus    /* My actual interface ID        */
};

/* Local code */

static HRESULT NewSOB(LPCIID lpInterface,
    ULONG ulOpenFlags,
    LPXPL lpxpl,
    ULONG * lpulObjType,
    LPSOB * lppSOB);

static HRESULT HrLoadStatusString(LPXPL lpxpl,
    LPVOID lpvParent,
    LPTSTR * lppsz);


/*
 -  HrBuildTransportStatus
 -
 *  Purpose:
 *      Called by TransportLogon to build the Status Table entry for the
 *      Sample Transport Provider.
 *
 *  Parameters:
 *      lpxpl               The current session structure.
 *      ulFlags             0 or STATUSROW_UPDATE
 *
 *  Returns:
 *      (HRESULT)           Errors encountered if any.
 *      (Status Row)        Contains properties from session
 *
 *  Operation:
 *      This one's relatively simple: build a property value array based on
 *      data in the session structure, and call (*lpMAPISup)->ModifyStatusRow
 *      to register the row in the table.
 */

HRESULT
HrBuildTransportStatus(LPXPL lpxpl, ULONG ulFlags)
{
    SCODE sc = 0;
    LPSPropValue lpPropArray = NULL;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    LPSPropValue pPropValT;
    LPVOID lpvT;
    LPVOID lpvT1;
    LPVOID lpvT2;
    LPTSTR lpszStatus = NULL;
    ULONG ulT;

    /*  Allocate initial property array now. */

    sc = lpxpl->AllocateBuffer(sizeof(SPropValue) * (NUM_STATUS_ROW_PROPS - 1), (LPVOID *) &lpPropArray);

    if (sc)
    {
        DebugTraceSc(Status Row Allocation, sc);
        goto ret;
    }

    /*  Store the properties into the status row */

    pPropValT = lpPropArray;

    /*  1. Transport's Display Name. */

    pPropValT->ulPropTag = PR_PROVIDER_DISPLAY;
    pPropValT->Value.LPSZ = (LPTSTR) MYDISPLAYNAME;
    pPropValT++;

    /*  2. Extra methods on status object */

    pPropValT->ulPropTag = PR_RESOURCE_METHODS;
    pPropValT->Value.ul = lpxpl->ulResourceMethods;
    pPropValT++;

    /*  3. Display Name associated with session. Use email address. */

    lpvT1 = ArrayIndex (PR_SAMPLE_DISPLAY_NAME, lpxpl->lpPropArray).Value.LPSZ;
    lpvT2 = ArrayIndex (PR_SAMPLE_EMAIL_ADDRESS, lpxpl->lpPropArray).Value.LPSZ;
    ulT = (lstrlen((LPCTSTR) lpvT1)+lstrlen((LPCTSTR) lpvT2)+4)*sizeof (TCHAR);

    sc = lpxpl->AllocateMore(ulT, (LPVOID) lpPropArray, &lpvT);

    if (sc)
    {
        DebugTraceSc(Session Display Name allocation, sc);
        goto ret;
    }
    wsprintf((LPTSTR) lpvT, TEXT("%s [%s]"), (LPTSTR) lpvT1, (LPTSTR) lpvT2);
    pPropValT->ulPropTag = PR_DISPLAY_NAME;
    pPropValT->Value.LPSZ = (LPTSTR) lpvT;
    pPropValT++;

    /*  4. User's Display Name. */

    Assert(lpxpl->lpMyIDArray);
    *pPropValT = lpxpl->lpMyIDArray[1];

    Assert(pPropValT->ulPropTag == PR_SENDER_NAME);
    Assert(!IsBadStringPtr(pPropValT->Value.LPSZ, MAX_STRING));

    pPropValT->ulPropTag = PR_IDENTITY_DISPLAY;
    pPropValT++;

    /*  5. User Entry-ID. */

    Assert(lpxpl->lpMyIDArray);
    *pPropValT = lpxpl->lpMyIDArray[0];

    Assert(pPropValT->ulPropTag == PR_SENDER_ENTRYID);
    Assert(pPropValT->Value.bin.cb);
    Assert(!IsBadReadPtr(pPropValT->Value.bin.lpb, (UINT) pPropValT->Value.bin.cb));

    pPropValT->ulPropTag = PR_IDENTITY_ENTRYID;
    pPropValT++;

    /*  6. User Search Key. */

    Assert(lpxpl->lpMyIDArray);
    *pPropValT = lpxpl->lpMyIDArray[2];

    Assert(pPropValT->ulPropTag == PR_SENDER_SEARCH_KEY);
    Assert(pPropValT->Value.bin.cb);
    Assert(!IsBadReadPtr(pPropValT->Value.bin.lpb, (UINT) pPropValT->Value.bin.cb));

    pPropValT->ulPropTag = PR_IDENTITY_SEARCH_KEY;
    pPropValT++;

    /*  7. Code. Online/Offline, Send/Receive, Uploading/Downloading. */

    pPropValT->ulPropTag = PR_STATUS_CODE;
    pPropValT->Value.ul = lpxpl->ulTransportStatus;
    pPropValT++;

    /*  8. Status String based on Status Code. */

    if (HrLoadStatusString(lpxpl, lpPropArray, &lpszStatus))
    {
        pPropValT->ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_STATUS_STRING));
        pPropValT->Value.err = MAPI_E_NOT_FOUND;
    }
    else
    {
        pPropValT->ulPropTag = PR_STATUS_STRING;
        pPropValT->Value.LPSZ = lpszStatus;
    }
    pPropValT++;

    /*  9. Resource Path == WGAP Directory. */

    lpvT = (LPVOID) ArrayIndex(PR_SAMPLE_DIRECTORY, lpxpl->lpPropArray).Value.LPSZ;

    if (lstrlen((LPCTSTR) lpvT))
    {
        pPropValT->ulPropTag = PR_RESOURCE_PATH;
        pPropValT->Value.LPSZ = (LPTSTR) lpvT;
        pPropValT++;
    }

    /*  Status Row is built. Register it. */

    sc = GetScode(lpMAPISup->lpVtbl->ModifyStatusRow(lpMAPISup,
            (pPropValT - lpPropArray), lpPropArray, ulFlags));

    if (FAILED(sc))
        DebugTrace("ModifyStatusRow failed.\n");

ret:
    /*  Free the allocated memory */

    lpxpl->FreeBuffer(lpPropArray);

    DebugTraceSc(HrBuildTransportStatus, sc);
    return ResultFromScode(sc);
}


/*
 -  HrUpdateTransportStatus
 -
 *  Purpose:
 *      Called by Transport code to update the PR_STATUS_CODE property in the
 *      Status Table row for the Sample Transport Provider.
 *
 *  Parameters:
 *      lpxpl               The current session structure.
 *      ulFlags             Flags. Not currently used.
 *
 *  Returns:
 *      (HRESULT)           Errors encountered if any.
 *      (Status Row)        PR_STATUS_CODE and PR_STATUS_STRING updated
 *
 *  Operation:
 *      Transport should already have updated lpxpl->ulTransportStatus
 *      before calling here.  So all this routine does is construct a
 *      notification structure for a status object modification and call
 *      (*lpMAPISup)->ModifyStatusRow() to update the table.  If there is a
 *      string available in the StringTable, then our cProps goes to 2 and
 *      we assign the string to the 2nd element of rgProps.
 */

HRESULT
HrUpdateTransportStatus(LPXPL lpxpl, ULONG ulFlags)
{
    HRESULT hResult;
    ULONG cProps = 2;
    SPropValue rgProps[2];
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    LPTSTR lpszStatus = NULL;

    /*  Store the new Transport Provider Status Code. */

    rgProps[0].ulPropTag = PR_STATUS_CODE;
    rgProps[0].Value.ul = lpxpl->ulTransportStatus;

    /* Set the Status String according to ulStatus */

    if (HrLoadStatusString(lpxpl, NULL, &lpszStatus))
    {
        rgProps[1].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_STATUS_STRING));
        rgProps[1].Value.err = MAPI_E_NOT_FOUND;
    }
    else
    {
        rgProps[1].ulPropTag = PR_STATUS_STRING;
        rgProps[1].Value.LPSZ = lpszStatus;
    }

    /*  OK. Notify the Spooler. It will tell MAPI. */

    hResult = lpMAPISup->lpVtbl->ModifyStatusRow(lpMAPISup,
            cProps, rgProps, STATUSROW_UPDATE);

    lpxpl->FreeBuffer(lpszStatus);
    
    DebugTraceResult(ModifyStatusRow, hResult);
    return hResult;
}


/*
 -  OpenStatusEntry
 -
 *  Purpose:
 *      Called by Spooler to service client OpenEntry request.
 *
 *  Parameters:
 *      lpiid               Interface identifier.
 *      ulFlags             Open flags. The only doc'ed flag
 *                          is MAPI_MODIFY, which we don't support.
 *      lpulObjType         Pointer to a unsigned long into which
 *                          we are to store the type of the
 *                          object we've just opened.
 *      lppEntry            Points to a variable into which we
 *                          may store the object pointer.
 *
 *  Returns:
 *      (HRESULT)           E_INVALIDARG if the session
 *                          pointer isn't valid, or any other
 *                          parameter not to our liking,
 *                          or any other errors we encounter.
 *      *lpulObjType        MAPI_STATUS if we open the entry,
 *                          unchanged if not
 *      *lppEntry           Pointer to object if we open the
 *                          entry, unchanged if not
 *
 *  Operation:
 *      Validate parameters. Call NewSOB() to create the object, returning
 *      object type and object pointer into user-supplied locations.
 */

STDMETHODIMP
XPL_OpenStatusEntry(LPXPL lpxpl,
    LPCIID lpiid,
    ULONG ulFlags,
    ULONG * lpulObjType,
    LPMAPISTATUS * lppEntry)
{
    HRESULT hResult;
#ifndef MAC
    LPXPP lpxpp;
#endif

    /* Need to do weak session validation to do this */

    if (IsBadWritePtr(lpxpl, sizeof(XPL)) ||
        IsBadWritePtr((lpxpp = lpxpl->lpxppParent), sizeof(XPP)) ||
        (lpiid != NULL && IsBadReadPtr(lpiid, sizeof(IID))) ||
        (IsBadWritePtr(lpulObjType, sizeof(ULONG))) ||
        (IsBadWritePtr(lppEntry, sizeof(LPMAPISTATUS))))
    {
        DebugTraceSc(OpenStatusEntry, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /* Get the Critical Section */

    EnterCriticalSection(&lpxpp->csTransport);

    /*  Validate the user's parameters always */

    /*  Invalid parameter checking: 1) make sure the passed session
        is still valid; 2) lpiid should either be null or point
        to a piece of memory at least the size of a iid; 3) lpulObjType
        must point to a writable piece of memory the size of a ulong;
        4) lppEntry must point to enough writable memory to store a
        LPMAPISTATUS. */

    if (!FIsValidSession(lpxpl))
    {
        hResult = ResultFromScode(E_INVALIDARG);
        DebugTrace("Invalid Logon object.\n");
        goto ret;
    }

    /*  We don't support MAPI_MODIFY and no other flags are spec'ed. */

    if (ulFlags & ~MAPI_MODIFY)
    {
        hResult = ResultFromScode(MAPI_E_UNKNOWN_FLAGS);
        DebugTrace("Unknown Flags.\n");
        goto ret;
    }

    if (ulFlags & MAPI_MODIFY)
    {
        hResult = ResultFromScode(MAPI_E_NO_ACCESS);
        DebugTrace("XP Support Object doesn't support Modify access.\n");
        goto ret;
    }

    /*  The argument list looks good to us. Now, if we already have opened
        a status object on this logon context, we'll just use QueryInterface
        to get a new copy of the object... */

    if (lpxpl->lpXPStatus)
    {
        hResult = lpxpl->lpXPStatus->lpVtbl->QueryInterface(lpxpl->lpXPStatus,
                (lpiid ? lpiid : &IID_IMAPIStatus), lppEntry);
                
        if (HR_FAILED(hResult))
            DebugTrace("QueryInterface failed.\n");
        else
            *lpulObjType = MAPI_STATUS;
    }
    else
    {
        /*  Or if we don't already have an object, create it, saving a
            copy in the logon context. */

        hResult = NewSOB(lpiid, ulFlags, lpxpl, 
                lpulObjType, (LPSOB *) lppEntry);
                
        if (HR_FAILED(hResult))
            DebugTrace("NewSOB failed.\n");
        else
            lpxpl->lpXPStatus = *lppEntry;
    }

ret:
    /*  Release the critical section. */

    LeaveCriticalSection(&lpxpp->csTransport);

    /*  Errors returned from this routine are always in sc. So if
        sc is zero we return 0. If it's nonzero we return a hResult
        built here from sc. */

    DebugTraceResult(OpenStatusEntry, hResult);
    return hResult;
}


/*
 -  NewSOB
 -
 *  Purpose:
 *      Called from OpenStatusEntry to create a Status Object.
 *
 *  Parameters:
 *      lpInterface         If non-null must be IID_IMAPIStatus
 *      ulOpenFlags         Open flags. The only doc'ed flag
 *                          is MAPI_MODIFY, which we don't support.
 *      lpxpl               The handle of the session for which
 *                          we want to open a Status object. In
 *                          Spooler context, a pointer to the
 *                          session data structure.
 *      lpulObjType         Pointer to a unsigned long into which
 *                          we are to store the type of the
 *                          object we've just opened.
 *      lppSOB              Points to a variable into which we
 *                          may store the object pointer.
 *
 * Returns:
 *      (HRESULT)           MAPI_E_NO_SUPPORT if an
 *                          interface is specified, or any
 *                          other errors we encounter.
 *      *lpulObjType        MAPI_STATUS if we open the entry,
 *                          unchanged if not
 *      *lppEntry           Pointer to object if we open the
 *                          entry, unchanged if not
 *
 *  Operation:
 *      Allocates the memory for the object, initializes its data
 *      members, plugs in the jump table and returns the appropriate
 *      stuff to the caller.
 */

static HRESULT
NewSOB(LPCIID lpInterface,
    ULONG ulOpenFlags,
    LPXPL lpxpl,
    ULONG * lpulObjType,
    LPSOB * lppSOB)
{
    SCODE sc;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    LPSOB lpSOB = NULL;
    ULONG i;

    *lpulObjType = 0;
    *lppSOB = NULL;

    /*  Make sure no interface (or ours) was specified. */

    if (lpInterface)
    {
        for (i = 0; i < N_IID; i++)
        {
            if (!memcmp(lpInterface, lpStatusFamilyIID[i], sizeof(IID)))
                break;
        }

        if (i == N_IID)
        {
            DebugTraceSc(NewSOB, E_INVALIDARG);
            return ResultFromScode(E_INVALIDARG);
        }
    }


    /*  Allocate space for the SOB structure */

    sc = lpxpl->AllocateBuffer(sizeof(SOB), (LPVOID *) &lpSOB);

    if (sc)
    {
        DebugTrace("Allocation of Status Object failed.\n");
        return ResultFromScode(sc);
    }

    /*  Fill in the data members and the jump table. */

    lpSOB->lpVtbl = &vtblSOB;
    lpSOB->lcInit = 1;
    lpSOB->lpsobMyAddress = lpSOB;

    lpSOB->hrLastError = 0;
    lpSOB->ulOpenFlags = ulOpenFlags;
    lpSOB->AllocateBuffer = lpxpl->AllocateBuffer;
    lpSOB->AllocateMore = lpxpl->AllocateMore;
    lpSOB->FreeBuffer = lpxpl->FreeBuffer;
    lpSOB->lpMAPISup = lpMAPISup;
    lpSOB->lpxpl = lpxpl;

    /*  Return the newly constructed object to the caller. */

    *lpulObjType = MAPI_STATUS;
    *lppSOB = lpSOB;

    return 0;
}


/*
 -  HrLoadStatusString
 -
 *  Purpose:
 *      Retrieves a Status String from the resource StringTable
 *      based on ulStatus code passed in.
 *
 *  Parameters:
 *      lpxpl               The Transport Logon session
 *      lpvParent           If non-null we chain the memory to this block
 *      lppsz               Place to copy Status String to.
 *
 * Returns:
 *      hr                  Indicating Success/Failure
 *
 */

static HRESULT
HrLoadStatusString(LPXPL lpxpl, LPVOID lpvParent, LPTSTR *lppsz)
{
    SCODE sc = S_OK;
    UINT ids;
    ULONG cb;
    ULONG ulStatus = lpxpl->ulTransportStatus;
    TCHAR szStatus[MAX_RESRC_STRING];

    /* Determine the IDS of the status.  Since the status' are bit fields
       of ulStatus, we apply this hierarcy to determine the correct string. */
    
    if (ulStatus & STATUS_INBOUND_ACTIVE)
        ids = IDS_STATUS_UPLOADING;
    else if (ulStatus & STATUS_OUTBOUND_ACTIVE)
        ids = IDS_STATUS_DOWNLOADING;
    else if (ulStatus & STATUS_INBOUND_FLUSH)
        ids = IDS_STATUS_INFLUSHING;
    else if (ulStatus & STATUS_OUTBOUND_FLUSH)
        ids = IDS_STATUS_OUTFLUSHING;
    else if ((ulStatus & STATUS_AVAILABLE) &&
            ((ulStatus & STATUS_INBOUND_ENABLED) ||
            (ulStatus & STATUS_OUTBOUND_ENABLED)))
        ids = IDS_STATUS_ONLINE;
    else if (ulStatus & STATUS_AVAILABLE)
        ids = IDS_STATUS_AVAILABLE;
    else
        ids = IDS_STATUS_OFFLINE;

    /* Attempt to load the resource into our automatic variable. */
    
    cb = LoadString(lpxpl->lpxppParent->hInst, ids, szStatus, MAX_RESRC_STRING);
    
    if (!cb)
    {
        sc = MAPI_E_CALL_FAILED;
        DebugTrace("LoadString failed in HrLoadStatusString.\n");
        goto ret;
    }

    /* We'll get the exact size of the string and put it on the heap.
       The caller had the luxury of specifying a parent block to chain
       this allocation to. */
    
    cb = (cb + 1) * sizeof(TCHAR);

    if (lpvParent)  
        sc = lpxpl->AllocateMore(cb, lpvParent, (LPVOID *)lppsz);
    else    
        sc = lpxpl->AllocateBuffer(cb, (LPVOID *)lppsz);
    
    if (FAILED(sc))
    {
        DebugTrace("Allocation failed in HrLoadStatusString.\n");
        goto ret;
    }
    
    lstrcpy(*lppsz, szStatus);

ret:
    DebugTraceSc(HrLoadStatusString, sc);
    return ResultFromScode(sc);
}


/*
 -  IMAPISTATUS::QueryInterface
 -
 *  Purpose:
 *      Standard IUnknown method.
 *
 *  Parameters:
 *      lpObject            Pointer to object
 *      lpiid               New interface to Query to
 *      lppNewObj           Where to store pointer to new object
 *
 *  Returns:
 *      (SCODE)             E_INVALIDARG if the input object
 *                          doesn't look like a SOB, if the
 *                          IID isn't readable or lppNewObj
 *                          isn't writable; E_NOINTERFACE
 *                          if we don't know the IID.
 *
 *  Operation:
 *      Validate parameters. See if the caller wants IUnknown, IMAPIProp or
 *      IStatus. If so, increment the usage count and return a new object.
 */

STDMETHODIMP
SOB_QueryInterface(LPSOB lpSOB,
    REFIID lpiid,
    LPVOID * lppNewObj)
{
    ULONG i;

    /*  Validate the parameters: 1) Does it seem to be an object?
        2) is the refcount nonzero? 3) Is there enough there for
        an interface ID? 4) Is there enough there for a new object? */

    if ((IsBadWritePtr(lpSOB, sizeof(SOB))) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (IsBadReadPtr(lpiid, sizeof(IID))) ||
        (IsBadWritePtr(lppNewObj, sizeof(LPSOB))))
    {
        DebugTraceSc(SOB_QueryInterface, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /*  See if the requested interface is one of ours */

    for (i = 0; i < N_IID; i++)
    {
        if (!memcmp(lpiid, lpStatusFamilyIID[i], sizeof(IID)))
            break;
    }

    /*  If we didn't find the interface, get out now. */

    if (i == N_IID)
    {
        /* OLE requires zeroing [out] parameters */
        *lppNewObj = NULL;
        DebugTraceSc(SOB_QueryInterface, E_NOINTERFACE);
        return ResultFromScode(E_NOINTERFACE);
    }

    /*  We'll do this one. Bump the usage count and return a new pointer. */

    ++lpSOB->lcInit;
    *lppNewObj = lpSOB;

    return hrSuccess;

}


/*
 -  IMAPISTATUS::AddRef
 -
 *  Purpose:
 *      Increment reference count if nonzero.
 *
 *  Parameters:
 *      lpObject            Pointer to object (should be SOB)
 *
 *  Returns:
 *      (ULONG)             Current reference count or zero if
 *                          it doesn't seem to be SOB.
 *
 *  Operation:
 *      Make sure it looks like a SOB, and if so, bump the reference count
 *      and return the result to the caller.
 */

STDMETHODIMP_(ULONG)
SOB_AddRef(LPSOB lpSOB)
{
    /*  If it doesn't seem to be an object or refcount is zero, return zero */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        lpSOB->lcInit == 0 ||
        lpSOB->lpsobMyAddress != lpSOB)
        return 0;

    return ++lpSOB->lcInit;

}


/*
 -  IMAPISTATUS::Release
 -
 *  Purpose:
 *      Decrement lcInit. If it's zero, release the object.
 *
 *  Parameters:
 *      lpObject            Pointer to object (should be SOB)
 *
 *  Returns:
 *      (ULONG)             Current reference count or zero if
 *                          it doesn't seem to be SOB.
 *
 *  Operation:
 *      Make sure it looks like a SOB, and if so, decrement the reference
 *      count. If the count is now zero, deallocate the object.
 *      Return the reference count to the caller.
 */

STDMETHODIMP_(ULONG)
SOB_Release(LPSOB lpSOB)
{
    /*  If it doesn't seem to be an object or refcount is zero, return zero */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        lpSOB->lcInit == 0 ||
        lpSOB->lpsobMyAddress != lpSOB)
        return 0;

    --lpSOB->lcInit;

    if (lpSOB->lcInit == 0)
    {
        DebugTrace("SOB::Release() freeing SOB.\n");

        /* Unlink the status object from the logon object */

        if (FIsValidSession(lpSOB->lpxpl))
            lpSOB->lpxpl->lpXPStatus = NULL;

        lpSOB->lpVtbl = NULL;
        (*lpSOB->FreeBuffer) (lpSOB);
        return 0;
    }

    return lpSOB->lcInit;
}


/*
 -  IMAPISTATUS::GetLastError
 -
 *  Purpose:
 *      Returns a string associated with the last HRESULT returned
 *      by the SOB object.
 *
 *  Parameters:
 *      lpObject            Pointer to object (should be SOB)
 *      hError              HRESULT that caller is interested in
 *      ulFlags             Ignored.
 *      lppszMessage        Pointer to where message pointer should
 *                          be copied.
 *
 *  Returns:
 *      (HRESULT)           E_INVALIDARG if object doesn't look
 *                          like a SOB or if any parameters look
 *                          bad; other errors if any; 0 if successful.
 *      *lppszMessage       Pointer to error message if any, else NULL
 *
 *  Operation:
 *      Confirm the parameters. Compare the HRESULT to our last saved one. If
 *      they match, copy the string into a new buffer and store the pointer
 *      into the location provided by the caller.
 */

STDMETHODIMP
SOB_GetLastError(LPSOB lpSOB,
    HRESULT hError,
    ULONG ulFlags,
    LPMAPIERROR * lppMapiError )
{
    HRESULT hResult = hrSuccess;
    SCODE   sc;
    LPTSTR  pszMessage  = NULL;

    /*  Validate the object and return pointer */

    *lppMapiError = NULL;
    
    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (IsBadWritePtr(lppMapiError, sizeof(LPMAPIERROR))))
    {
        DebugTraceSc(SOB_GetLastError, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    if ( ulFlags & ~MAPI_UNICODE )
    {
        return ResultFromScode( MAPI_E_UNKNOWN_FLAGS );
    }
    
    if ( ulFlags & MAPI_UNICODE )
    {
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH );
    }
    
    /*  See if we have the message the caller wants. If so,
        make a copy and pass it back. */

    if ((hError != 0) && (hError == lpSOB->hrLastError))
    {
        sc = lpSOB->AllocateBuffer( sizeof( MAPIERROR ), lppMapiError );
        if ( FAILED( sc ) )
        {
            hResult = ResultFromScode( sc );
            goto ret;
        }
        
        memset( *lppMapiError, 0, sizeof( MAPIERROR ) );
        
        (*lppMapiError)->ulVersion = MAPI_ERROR_VERSION;    
    
        hResult = MapScodeSz(GetScode(hError), lpSOB->lpxpl, &pszMessage);
        if ( HR_FAILED( hResult ) )
            goto ret;
        
        sc = lpSOB->AllocateMore( Cbtszsize( pszMessage ), *lppMapiError, 
                &(*lppMapiError)->lpszError );
        if ( FAILED( sc ) )     
        {
            hResult = ResultFromScode( sc );
            goto ret;
        }
        
        lstrcpy( (*lppMapiError)->lpszError, pszMessage );
    }

ret:
    if ( hResult )
    {
        lpSOB->FreeBuffer( *lppMapiError );
        *lppMapiError = NULL;
    }
        
    lpSOB->FreeBuffer( pszMessage );
    return hResult;
}


/*
 -  IMAPISTATUS::GetProps
 -
 *  Purpose:
 *      Returns the properties listed in the lpPropTagArray.
 *
 *  Parameters:
 *      lpObject            Pointer to object (should be SOB)
 *      lpPropTagArray      List of tags for which values are desired
 *      ulFlags             UNICODE / String8
 *      lpcValues           Pointer: where to store count of values
 *      lppPropArray        Pointer: where to store pointer to values
 *
 *  Returns:
 *      (HRESULT)           E_INVALIDARG if object doesn't look like
 *                          a SOB or if any of the parameters look
 *                          bad; other errors if any; 0 if successful.
 *      *lpcValues          Contains a property count if successful
 *      *lppPropArray       Undefined if not successful; NULL if
 *                          no properties; points to array of
 *                          properties if any.
 *
 *  Operation:
 *      Confirm the parameters. If lpPropTagArray is NULL, use our canned
 *      property list.
 *      Walk through the list, and give the caller any properties in the
 *      list which we can provide. Return count in *lpcValues and pointer to
 *      the array in *lppPropArray.
 */

STDMETHODIMP
SOB_GetProps(LPSOB lpSOB,
    LPSPropTagArray lpPropTagArray,
    ULONG ulFlags,
    ULONG * lpcValues,
    LPSPropValue * lppPropArray)
{
    SCODE sc = 0;
    HRESULT hResult = 0;
    ULONG ulT = 0;
    LPXPL lpxpl = NULL;
    HINSTANCE hInst;
    LPSPropValue lpPropArray = NULL;
    LPSPropValue lpMyIDArray = NULL;
    LPSPropTagArray lpspta = NULL;
    ULONG cb;
    LPTSTR lpsz;
    LPSPropValue lpPropT;
    BOOL fGotMemErrors = FALSE;
    BOOL fMyPTA = TRUE;
    BOOL fNoResourcePath = FALSE;

    /*  Validate the object and the return pointers */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        lpSOB->lcInit == 0 ||
        lpSOB->lpsobMyAddress != lpSOB)
    {
        hResult = ResultFromScode(E_INVALIDARG);
        goto ret;
    }

    /* Validate the Flags */
    
    if ( ulFlags & ~(MAPI_UNICODE) )
    {
        hResult = ResultFromScode( MAPI_E_UNKNOWN_FLAGS );
        goto ret;
    }
    
    if ( ulFlags & MAPI_UNICODE )
    {
        hResult = ResultFromScode( MAPI_E_BAD_CHARWIDTH );
        goto ret;
    }
    
    /*  Validate the return pointers */

    if ((IsBadWritePtr(lpcValues, sizeof(ULONG))) ||
        (IsBadWritePtr(lppPropArray, sizeof(LPSPropValue))))
    {
        hResult = ResultFromScode(E_INVALIDARG);
        goto ret;
    }

    /*  Validate the passed property tag array if any */

    if (lpPropTagArray)
    {
        if ((IsBadReadPtr(lpPropTagArray, CbNewSPropTagArray(0))) ||
            (lpPropTagArray->cValues == 0) ||
            (IsBadReadPtr(&lpPropTagArray->aulPropTag[0],
                    (UINT) (lpPropTagArray->cValues * sizeof(ULONG)))))
        {
            hResult = ResultFromScode(E_INVALIDARG);
            goto ret;
        }
        fMyPTA = FALSE;
        lpspta = lpPropTagArray;
    }
    else
    {
        /*  An array wasn't passed. Use ours. */

        lpspta = (LPSPropTagArray) &sptaStatusRow;
    }

    /*  Parameters have passed muster. Create the property array. */

    lpxpl = lpSOB->lpxpl;
    hInst = lpxpl->lpxppParent->hInst;

    sc = ScCopySessionProps(lpxpl, &lpPropArray, &lpMyIDArray);

    if (FAILED(sc))
        goto ret;

    sc = (*lpSOB->AllocateBuffer) (sizeof(SPropValue) * (lpspta->cValues), (LPVOID *) lppPropArray);
    if (sc)
    {
        hResult = ResultFromScode(sc);
        lpSOB->hrLastError = hResult;
        goto ret;
    }

    /*  Count will always equal input number since we'll either get a
        property value or a PT_ERROR. */

    for (ulT = 0; ulT < lpspta->cValues; ulT++)
    {
        switch (lpspta->aulPropTag[ulT])
        {
        case PR_RESOURCE_METHODS:
            (*lppPropArray)[ulT].ulPropTag = PR_RESOURCE_METHODS;
            (*lppPropArray)[ulT].Value.ul = lpxpl->ulResourceMethods;
            break;

        case PR_PROVIDER_DISPLAY:
            (*lppPropArray)[ulT].ulPropTag = PR_PROVIDER_DISPLAY;
            (*lppPropArray)[ulT].Value.LPSZ = (LPTSTR)MYDISPLAYNAME;
            break;

        case PR_DISPLAY_NAME:
            lpsz = ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpPropArray).Value.LPSZ;
            cb = sizeof(TCHAR) * (lstrlen(lpsz) + 1);

            sc = lpSOB->AllocateMore(cb, (LPVOID) *lppPropArray,
                    (LPVOID *) &((*lppPropArray)[ulT].Value.LPSZ));
                
            if (sc)
            {
                fGotMemErrors = TRUE;
                (*lppPropArray)[ulT].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(lpspta->aulPropTag[ulT]));
                (*lppPropArray)[ulT].Value.err = sc;
            }
            else
            {
                (*lppPropArray)[ulT].ulPropTag = PR_DISPLAY_NAME;
                lstrcpy((*lppPropArray)[ulT].Value.LPSZ, lpsz);
            }
            break;

        case PR_IDENTITY_DISPLAY:
            lpPropT = &(lpMyIDArray[1]);
            Assert(lpPropT);
            Assert(lpPropT->ulPropTag == PR_SENDER_NAME);

            cb = sizeof(TCHAR) * (lstrlen(lpPropT->Value.LPSZ) + 1);

            sc = lpSOB->AllocateMore(cb, (LPVOID) * lppPropArray,
                    (LPVOID *) &((*lppPropArray)[ulT].Value.LPSZ));

            if (sc)
            {
                fGotMemErrors = TRUE;
                (*lppPropArray)[ulT].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(lpspta->aulPropTag[ulT]));
                (*lppPropArray)[ulT].Value.err = sc;
            }
            else
            {
                (*lppPropArray)[ulT].ulPropTag = PR_IDENTITY_DISPLAY;
                lstrcpy((*lppPropArray)[ulT].Value.LPSZ, lpPropT->Value.LPSZ);
            }
            break;

        case PR_IDENTITY_ENTRYID:
            lpPropT = &(lpMyIDArray[0]);
            Assert(lpPropT);
            Assert(lpPropT->ulPropTag == PR_SENDER_ENTRYID);

            cb = lpPropT->Value.bin.cb;
            Assert(cb);
            Assert(!IsBadReadPtr(lpPropT->Value.bin.lpb, (UINT)cb));

            sc = lpSOB->AllocateMore(cb, (LPVOID) *lppPropArray,
                    (LPVOID *) &((*lppPropArray)[ulT].Value.bin.lpb));
                    
            if (sc)
            {
                fGotMemErrors = TRUE;
                (*lppPropArray)[ulT].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(lpspta->aulPropTag[ulT]));
                (*lppPropArray)[ulT].Value.err = sc;
            }
            else
            {
                (*lppPropArray)[ulT].ulPropTag = PR_IDENTITY_ENTRYID;
                (*lppPropArray)[ulT].Value.bin.cb = cb;
                if (cb)
                    memcpy((*lppPropArray)[ulT].Value.bin.lpb,
                            lpPropT->Value.bin.lpb, (UINT)cb);
            }
            break;

        case PR_IDENTITY_SEARCH_KEY:
            lpPropT = &(lpMyIDArray[2]);
            Assert(lpPropT);
            Assert(lpPropT->ulPropTag == PR_SENDER_SEARCH_KEY);

            cb = lpPropT->Value.bin.cb;
            Assert(cb);
            Assert(!IsBadReadPtr(lpPropT->Value.bin.lpb, (UINT)cb));

            sc = lpSOB->AllocateMore(cb, (LPVOID) *lppPropArray,
                    (LPVOID *) &((*lppPropArray)[ulT].Value.bin.lpb));
                    
            if (sc)
            {
                fGotMemErrors = TRUE;
                (*lppPropArray)[ulT].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(lpspta->aulPropTag[ulT]));
                (*lppPropArray)[ulT].Value.err = sc;
            }
            else
            {
                (*lppPropArray)[ulT].ulPropTag = PR_IDENTITY_SEARCH_KEY;
                (*lppPropArray)[ulT].Value.bin.cb = cb;
                if (cb)
                    memcpy((*lppPropArray)[ulT].Value.bin.lpb,
                            lpPropT->Value.bin.lpb, (UINT)cb);
            }
            break;

        case PR_STATUS_CODE:
            (*lppPropArray)[ulT].ulPropTag = PR_STATUS_CODE;
            (*lppPropArray)[ulT].Value.ul = lpxpl->ulTransportStatus;
            break;

        case PR_STATUS_STRING:
            lpsz = NULL;

            if (sc = GetScode(HrLoadStatusString(lpxpl, *lppPropArray, &lpsz)))
            {
                fGotMemErrors = TRUE;
                (*lppPropArray)[ulT].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(lpspta->aulPropTag[ulT]));
                (*lppPropArray)[ulT].Value.err = sc;
            }
            else
            {
                (*lppPropArray)[ulT].ulPropTag = PR_STATUS_STRING;
                (*lppPropArray)[ulT].Value.LPSZ = lpsz;
            }
            break;

        case PR_RESOURCE_PATH:
            lpsz = (LPVOID) ArrayIndex(PR_SAMPLE_DIRECTORY, lpPropArray).Value.LPSZ;
            Assert(lpsz);

            cb = (lstrlen(lpsz) + 1) * sizeof(TCHAR);

            if (cb == sizeof(TCHAR))
            {
                if (fMyPTA)
                {
                    fNoResourcePath = TRUE;
                }
                else
                {
                    (*lppPropArray)[ulT].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_RESOURCE_PATH));
                    (*lppPropArray)[ulT].Value.err = MAPI_E_NOT_FOUND;
                }
                break;
            }

            sc = (*lpSOB->AllocateMore) (cb, (LPVOID) * lppPropArray, (LPVOID *) &((*lppPropArray)[ulT].Value.LPSZ));

            if (sc)
            {
                fGotMemErrors = TRUE;
                (*lppPropArray)[ulT].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_RESOURCE_PATH));
                (*lppPropArray)[ulT].Value.err = sc;
            }
            else
            {
                (*lppPropArray)[ulT].ulPropTag = PR_RESOURCE_PATH;
                lstrcpy((*lppPropArray)[ulT].Value.LPSZ, lpsz);
            }
            break;

        case PR_OBJECT_TYPE:
            (*lppPropArray)[ulT].ulPropTag = PR_OBJECT_TYPE;
            (*lppPropArray)[ulT].Value.ul = MAPI_STATUS;
            break;

        default:
            (*lppPropArray)[ulT].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(lpspta->aulPropTag[ulT]));
            (*lppPropArray)[ulT].Value.err = MAPI_E_NOT_FOUND;

            hResult = ResultFromScode(MAPI_W_ERRORS_RETURNED);
            lpSOB->hrLastError = hResult;
            break;
        }
    }

    /*  Store number of properties we're returning, i.e., the number
        asked for (with possible errors). */

    if (fMyPTA && fNoResourcePath)
        *lpcValues = lpspta->cValues - 1;
    else    
        *lpcValues = lpspta->cValues;

    if (fGotMemErrors)
    {
        hResult = ResultFromScode(MAPI_W_ERRORS_RETURNED);
        lpSOB->hrLastError = hResult;
    }

ret:
    if(lpxpl)
    {
        lpxpl->FreeBuffer(lpPropArray);
        lpxpl->FreeBuffer(lpMyIDArray);
    }

    DebugTraceResult(SOB_GetProps, hResult);
    return hResult;
}


/*
 -  IMAPISTATUS::GetPropList
 -
 *  Purpose:
 *
 *  Parameters:
 *      lpObject            Pointer to object (should be SOB)
 *      ulFlags             UNICODE / String8
 *      lppPropTagArray     Pointer: where to store pointer to tags
 *
 *  Returns:
 *      (HRESULT)           E_INVALIDARG if object doesn't look like a
 *                          SOB or if any of the parameters look bad;
 *                          other errors if any; 0 if successful.
 *      *lppPropArray       Undefined if not successful; points to
 *                          array of property tags otherwise.
 *
 *  Operation:
 *      Validate parameters; Create enough memory for out property tag list,
 *      copy the list into it and do so. Return the new list into the caller's
 *      pointer.
 */

STDMETHODIMP
SOB_GetPropList(LPSOB lpSOB,
    ULONG ulFlags,
    LPSPropTagArray * lppPropTagArray)
{
    SCODE sc;
    HRESULT hResult = 0;
    LPXPL lpxpl;
    ULONG ulArraySize;
    ULONG cActualProps;

    /* Validate the Flags */
    
    if ( ulFlags & ~(MAPI_UNICODE) )
    {
        hResult = ResultFromScode( MAPI_E_UNKNOWN_FLAGS );
        goto ret;
    }
    
    if ( ulFlags & MAPI_UNICODE )
    {
        hResult = ResultFromScode( MAPI_E_BAD_CHARWIDTH );
        goto ret;
    }
    
    /*  Validate the object and the return pointers */

    if ((IsBadWritePtr(lpSOB, sizeof(SOB))) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (IsBadWritePtr(lppPropTagArray, sizeof(LPSPropTagArray))))
    {
        hResult = ResultFromScode(E_INVALIDARG);
        goto ret;
    }

    lpxpl = lpSOB->lpxpl;

    /* If WGAP Directory is empty, don't tell them about this property. */
    cActualProps = sptaStatusRow.cValues;

    if (lstrlen((LPTSTR) ArrayIndex(PR_SAMPLE_DIRECTORY, lpxpl->lpPropArray).Value.LPSZ))
        ulArraySize = CbNewSPropTagArray(sptaStatusRow.cValues);
    else
    {
        /* Adjust for removing a prop tag */
        cActualProps--;
        ulArraySize = CbNewSPropTagArray(sptaStatusRow.cValues - 1);
    }

    /*  Allocate the required amount of memory */

    sc = (*lpSOB->AllocateBuffer) (ulArraySize, (LPVOID *) lppPropTagArray);

    if (sc)
    {
        hResult = ResultFromScode(sc);
        lpSOB->hrLastError = hResult;
        goto ret;
    }

    /*  Copy the contents of our canned property tag array into the buffer */

    if (ulArraySize)
    {
        memcpy(*lppPropTagArray, &sptaStatusRow, (size_t) ulArraySize);
        (*lppPropTagArray)->cValues = cActualProps;
    }

ret:
    DebugTraceResult(SOB_GetPropList, hResult);
    return hResult;
}


/*
 -  SOB_SettingsDialog
 -
 *  Purpose:
 *      This routine will invoke the Transports Logon dialog to allow
 *      the user to change the Logon properties.  The lpPropArray on the
 *      current session will be updated.
 *
 *  Parameters:
 *      lpSOB               The status object for this transport session
 *      ulUIParam           The HWnd of the caller (may be null)
 *      ulFlags             If UI_READONLY will not update the lpPropArray
 *
 *  Returns:
 *      hResult             Indicating success/failure.
 *
 *  Operation:
 *
 */

STDMETHODIMP
SOB_SettingsDialog(LPSOB lpSOB,
    ULONG ulUIParam,
    ULONG ulFlags)
{
    HRESULT hResult = hrSuccess;
    SCODE sc = S_OK;
    LPSPropValue lpMyIDArray = NULL;
    LPVOID lpvT, lpvT2;
    ULONG ulCount = MAX_LOGON_PROPERTIES - TEMP_LOGON_PROPERTIES;
    ULONG ulT;
    LPXPL lpxpl = lpSOB->lpxpl;
    LPSPropValue lpPropArray = NULL;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    LPPROFSECT lpProfileObj = NULL;
    XPDLG XPDialog;
    BOOL fNeedUI = TRUE;
    BOOL fInCS = FALSE;

    if ((IsBadReadPtr(lpSOB, sizeof(SOB))) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB))
    {
        hResult = ResultFromScode(E_INVALIDARG);
        goto ret;
    }

    if (ulFlags & ~UI_READONLY)
    {
        hResult = ResultFromScode(E_INVALIDARG);
        goto ret;
    }

    /* Get the Critical Section */

    EnterCriticalSection(&(lpxpl->lpxppParent->csTransport));

    fInCS = TRUE;

    sc = ScCopySessionProps(lpxpl, &lpPropArray, NULL);

    if (FAILED(sc))
        goto ret;

    /* Fill in the logon UI structure */

    XPDialog.hInst = lpxpl->lpxppParent->hInst;
    XPDialog.hwnd = (HWND) ulUIParam;
    XPDialog.lppPropArray = &lpPropArray;
    XPDialog.lpPTArray = (LPSPropTagArray) &sptLogonArray;
    XPDialog.AllocateBuffer = lpxpl->AllocateBuffer;
    XPDialog.AllocateMore = lpxpl->AllocateMore;
    XPDialog.FreeBuffer = lpxpl->FreeBuffer;
    XPDialog.lpMalloc = lpxpl->lpxppParent->lpMalloc;
    XPDialog.lpMAPISup = lpxpl->lpMAPISup;
    XPDialog.fLogon = FALSE;
    XPDialog.ulFlags = ulFlags;

    while (fNeedUI)
    {
        sc = ScDoLogonDlg(&XPDialog);

        if (FAILED(sc))
        {
            DebugTraceSc(Logon UI activation, sc);
            goto ret;
        }

        if (lpPropArray)
        {
            /* Got a prop array, make sure everything in it is good */

            for (ulT = 0; ulT < ulCount; ulT++)
            {
                if (PROP_TYPE((lpPropArray)[ulT].ulPropTag) == PT_ERROR)
                {
                    DebugTrace("Property %x not available.\n", PROP_ID((lpPropArray)[ulT].ulPropTag));
                    sc = MAPI_E_NO_ACCESS;
                }
            }
        }
        else
            sc = MAPI_E_NO_ACCESS;

        if (sc)
        {
            DebugTraceSc(Logon UI returning, sc);
            goto ret;
        }

        /* Do some simple validation of the Logon Props */

        sc = ScCheckLogonProps(&XPDialog, TRUE);

        if (sc == MAPI_E_USER_CANCEL)
            goto ret;
        else if (sc == MAPI_E_INVALID_PARAMETER)
            continue;
        else
            fNeedUI = FALSE;

        /* If we get here, everything is fine and we can proceed. But first
           we should write the properties out if the user is willing. */

        ulT = ArrayIndex(PR_SAMPLE_FLAGS, lpPropArray).Value.ul;

        if ((ulT & PR_SAMPLE_FLAG_SAVE_DATA))
        {
            /* Try to open our profile. */

            hResult = lpMAPISup->lpVtbl->OpenProfileSection(lpMAPISup,
                (LPMAPIUID) NULL, MAPI_MODIFY, &lpProfileObj);

            if (HR_FAILED(hResult))
            {
              DebugTraceResult(MAPISUP: :OpenProfileSection, hResult);
                goto ret;
            }

            hResult = lpProfileObj->lpVtbl->SetProps(lpProfileObj,
                ulCount, lpPropArray, NULL);

            if (HR_FAILED(hResult))
            {
              DebugTraceResult(PROFSECT: :SetProps, hResult);
                goto ret;
            }
        }
    }

    /* Allocate initial property array for transport ID. */

    sc = (*lpxpl->AllocateBuffer) (sizeof(SPropValue) * NUM_SENDER_PROPS,
        (LPVOID *) &lpMyIDArray);

    if (sc)
    {
        DebugTraceSc(Sender ID property array allocation, sc);
        goto ret;
    }

    memset(lpMyIDArray, 0, sizeof(SPropValue) * NUM_SENDER_PROPS);

    /* Create the One-Off directly into the property value structure. */

    lpMyIDArray[0].ulPropTag = PR_SENDER_ENTRYID;

    hResult = lpMAPISup->lpVtbl->CreateOneOff(lpMAPISup,
        ArrayIndex(PR_SAMPLE_DISPLAY_NAME, lpPropArray).Value.LPSZ,
        ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ,
        ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpPropArray).Value.LPSZ,
        fMapiUnicode,
        &lpMyIDArray[0].Value.bin.cb,
        (LPENTRYID *) &lpMyIDArray[0].Value.bin.lpb);

    if (hResult)
    {
      DebugTraceResult(MAPISUP: :CreateOneOff, hResult);
        lpMyIDArray[0].Value.bin.lpb = NULL;
        goto ret;
    }

    /* Create the PR_SENDER_NAME property value. */

    lpvT2 = ArrayIndex(PR_SAMPLE_DISPLAY_NAME, lpPropArray).Value.LPSZ;
    ulT = lstrlen((LPCTSTR) lpvT2) + 1;

    sc = (*lpxpl->AllocateMore) (ulT, (LPVOID) lpMyIDArray,
        (LPVOID *) &lpvT);

    if (sc)
    {
        DebugTraceSc(User Display Name allocation, sc);
        goto ret;
    }

    lstrcpy((LPTSTR) lpvT, (LPCTSTR) lpvT2);

    lpMyIDArray[1].ulPropTag = PR_SENDER_NAME;
    lpMyIDArray[1].Value.LPSZ = (LPTSTR) lpvT;

    /* Create the PR_SENDER_SEARCH_KEY value. */

    lpMyIDArray[2].ulPropTag = PR_SENDER_SEARCH_KEY;

    /* Size of property = type plus colon plus address plus null. */

    ulT = 2 + lstrlen(ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ) +
        lstrlen(ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpPropArray).Value.LPSZ);

    sc = (*lpxpl->AllocateMore) (ulT, (LPVOID) lpMyIDArray,
        (LPVOID *) &lpvT);

    if (sc)
    {
        DebugTraceSc(User Search Key allocation, sc);
        goto ret;
    }

    /* PR_SENDER_SEARCH_KEY is "TYPE:ADDRESS" folded to uppercase. */

    wsprintf((LPTSTR) lpvT, TEXT("%s:%s"),
        (ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ),
        (ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpPropArray).Value.LPSZ));

    CharUpperBuff((LPTSTR) lpvT, (UINT)-- ulT);

    lpMyIDArray[2].Value.bin.cb = sizeof(TCHAR) * (1 + lstrlen((LPTSTR) lpvT));
    lpMyIDArray[2].Value.bin.lpb = lpvT;

    /* Replace the original PropArray with the new one. */

    lpxpl->FreeBuffer(lpxpl->lpPropArray);
    lpxpl->lpPropArray = lpPropArray;

    /* Now, free the original User Display Name and Entry-ID */

    if (lpxpl->lpMyIDArray)
    {
        (*lpxpl->FreeBuffer) (lpxpl->lpMyIDArray[0].Value.bin.lpb);
        (*lpxpl->FreeBuffer) (lpxpl->lpMyIDArray);
    }

    lpxpl->lpMyIDArray = lpMyIDArray;

    hResult = HrBuildTransportStatus(lpxpl, STATUSROW_UPDATE);

ret:
    /* Release the Critical Section. */

    if (fInCS)
        LeaveCriticalSection(&(lpxpl->lpxppParent->csTransport));

    UlRelease(lpProfileObj);

    if (lpPropArray && (lpxpl->lpPropArray != lpPropArray))
        lpxpl->FreeBuffer(lpPropArray);

    if (lpMyIDArray && (lpxpl->lpMyIDArray != lpMyIDArray))
    {
        (*lpxpl->FreeBuffer) (lpMyIDArray[0].Value.bin.lpb);
        (*lpxpl->FreeBuffer) (lpMyIDArray);
    }

    if (!hResult && sc)
        hResult = ResultFromScode(sc);

    DebugTraceResult(SOB_SettingsDialog, hResult);
    return hResult;
}


/*
 -  SOB_FlushQueues
 -
 *  Purpose:
 *      Logon object method used by Spooler if FlushQueues is called on
 *      the spooler status object.
 *
 *  Parameters:
 *      lpSOB               This pointer for Status Object
 *      ulUIParam           Window handle
 *      cbTargetTransport   Count of bytes in Entryid. Zero.
 *      lpTargetTransport   Entryid of transport. NULL.
 *      ulFlags
 *
 *  Returns:
 *      (HRESULT)           E_INVALIDARG if object doesn't
 *                          look like a XPL; MAPI_E_NO_SUPPORT
 *                          otherwise.
 *
 *  Operation:
 *      Validate the object pointer.
 */

STDMETHODIMP
SOB_FlushQueues(LPSOB lpSOB,
    ULONG ulUIParam,
    ULONG cbTargetTransport,
    LPENTRYID lpTargetTransport,
    ULONG ulFlags)
{
    HRESULT hResult;

    if ((IsBadReadPtr(lpSOB, sizeof(SOB))) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB))
    {
        return ResultFromScode(E_INVALIDARG);
    }

    if (ulFlags & FLUSH_UPLOAD)
        lpSOB->lpxpl->ulTransportStatus |= STATUS_OUTBOUND_FLUSH;
    if (ulFlags & FLUSH_DOWNLOAD)
        lpSOB->lpxpl->ulTransportStatus |= STATUS_INBOUND_FLUSH;

    hResult = HrUpdateTransportStatus(lpSOB->lpxpl, 0L);
    return hResult;
}


/*
 -  Unimplemented functions. Stubbed to give access or NYI.
 -
 */

STDMETHODIMP
SOB_SaveChanges(LPSOB lpSOB,
    ULONG ulFlags)
{
    /*  Do parameter validation */

    if (IsBadReadPtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (ulFlags & ~(KEEP_OPEN_READWRITE | KEEP_OPEN_READONLY | FORCE_SAVE)))
    {
        DebugTraceSc(SOB_SaveChanges, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }
    
    DebugTraceSc(SOB_SaveChanges, MAPI_E_NO_ACCESS);
    return (ResultFromScode(MAPI_E_NO_ACCESS));
}

STDMETHODIMP
SOB_OpenProperty(LPSOB lpSOB,
    ULONG ulPropTag,
    LPCIID lpiid,
    ULONG ulInterfaceOptions,
    ULONG ulFlags,
    LPUNKNOWN * lppUnk)
{
    /*  Do parameter validation */

    if (IsBadReadPtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (!lpiid || IsBadReadPtr(lpiid, sizeof(IID))) ||
        (ulFlags & ~(MAPI_CREATE | MAPI_MODIFY | MAPI_DEFERRED_ERRORS)) ||
        (!lppUnk || IsBadWritePtr(lppUnk, sizeof(LPVOID))))
    {
        DebugTraceSc(SOB_OpenProperty, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }
    
    if ( ulInterfaceOptions & ~(MAPI_UNICODE) )
    {
        return ResultFromScode( MAPI_E_UNKNOWN_FLAGS );
    }
    
    if ( ulInterfaceOptions & MAPI_UNICODE )
    {
        return ResultFromScode( MAPI_E_UNKNOWN_FLAGS );
    }
    
    DebugTraceSc(SOB_OpenProperty, MAPI_E_NO_SUPPORT);
    return (ResultFromScode(MAPI_E_NO_SUPPORT));
}

STDMETHODIMP
SOB_SetProps(LPSOB lpSOB,
    ULONG cValues,
    LPSPropValue lpPropArray,
    LPSPropProblemArray * lppProblems)
{
    /*  Do parameter validation */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (cValues && IsBadReadPtr(lpPropArray, (UINT)cValues*sizeof(SPropValue))) ||
        (IsBadWritePtr(lppProblems, sizeof(LPSPropProblemArray))))
    {
        DebugTraceSc(SOB_SetProps, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    DebugTraceSc(SOB_SetProps, MAPI_E_NO_ACCESS);
    return (ResultFromScode(MAPI_E_NO_ACCESS));
}

STDMETHODIMP
SOB_DeleteProps(LPSOB lpSOB,
    LPSPropTagArray lpPropTagArray,
    LPSPropProblemArray * lppProblems)
{
    /*  Do parameter validation */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (!lpPropTagArray) ||
        (IsBadReadPtr(lpPropTagArray, (UINT)lpPropTagArray->cValues*sizeof(ULONG))) ||
        (IsBadWritePtr(lppProblems, sizeof(LPSPropProblemArray))))
    {
        DebugTraceSc(SOB_DeleteProps, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    DebugTraceSc(SOB_DeleteProps, MAPI_E_NO_ACCESS);
    return (ResultFromScode(MAPI_E_NO_ACCESS));
}

STDMETHODIMP
SOB_CopyTo(LPSOB lpSOB,
    ULONG ciidExclude,
    LPCIID rgiidExclude,
    LPSPropTagArray lpExcludeProps,
    ULONG ulUIParam,
    LPMAPIPROGRESS lpProgress,
    LPCIID lpInterface,
    LPVOID lpDestObj,
    ULONG ulFlags,
    LPSPropProblemArray * lppProblems)
{
    /*  Do parameter validation */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (ciidExclude && (!rgiidExclude || IsBadReadPtr(rgiidExclude, (UINT)ciidExclude*sizeof(IID)))) ||
        (lpExcludeProps && IsBadReadPtr(lpExcludeProps, (UINT)lpExcludeProps->cValues*sizeof(ULONG))) ||
        (lpProgress && IsBadReadPtr(lpProgress, sizeof(LPMAPIPROGRESS))) ||
        (!lpInterface || IsBadReadPtr(lpInterface, sizeof(IID))) ||
        (IsBadReadPtr(lpDestObj, sizeof(LPVOID))) ||
        (ulFlags & ~(MAPI_MOVE | MAPI_NOREPLACE | MAPI_DIALOG | MAPI_DECLINE_OK)) ||
        (IsBadWritePtr(lppProblems, sizeof(LPSPropProblemArray))))
    {
        DebugTraceSc(SOB_CopyTo, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    DebugTraceSc(SOB_CopyTo, MAPI_E_NO_SUPPORT);
    return (ResultFromScode(MAPI_E_NO_SUPPORT));
}

STDMETHODIMP
SOB_CopyProps(LPSOB lpSOB,
    LPSPropTagArray lpIncludeProps,
    ULONG ulUIParam,
    LPMAPIPROGRESS lpProgress,
    LPCIID lpInterface,
    LPVOID lpDestObj,
    ULONG ulFlags,
    LPSPropProblemArray * lppProblems)
{
    /*  Do parameter validation */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (lpIncludeProps && IsBadReadPtr(lpIncludeProps, (UINT)lpIncludeProps->cValues*sizeof(ULONG))) ||
        (lpProgress && IsBadReadPtr(lpProgress, sizeof(LPMAPIPROGRESS))) ||
        (!lpInterface || IsBadReadPtr(lpInterface, sizeof(IID))) ||
        (IsBadReadPtr(lpDestObj, sizeof(LPVOID))) ||
        (ulFlags & ~(MAPI_MOVE | MAPI_NOREPLACE | MAPI_DIALOG | MAPI_DECLINE_OK)) ||
        (IsBadWritePtr(lppProblems, sizeof(LPSPropProblemArray))))
    {
        DebugTraceSc(SOB_CopyProps, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    DebugTraceSc(SOB_CopyProps, MAPI_E_NO_SUPPORT);
    return (ResultFromScode(MAPI_E_NO_SUPPORT));
}

STDMETHODIMP
SOB_GetNamesFromIDs(LPSOB lpSOB,
    LPSPropTagArray * lppPropTags,
    LPGUID lpPropSet,
    ULONG ulFlags,
    ULONG * lpcPropNames,
    LPMAPINAMEID * * lpppPropNames)
{
    /*  Do parameter validation */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (IsBadReadPtr(lppPropTags, sizeof(LPSPropTagArray))) ||
        (IsBadReadPtr(lpPropSet, sizeof(GUID))) ||
        (IsBadWritePtr(lpcPropNames, sizeof(ULONG))) ||
        (IsBadWritePtr(lpppPropNames, sizeof(LPVOID))))
    {
        DebugTraceSc(SOB_GetNamesFromIDs, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    DebugTraceSc(SOB_GetNamesFromIDs, MAPI_E_NO_SUPPORT);
    return (ResultFromScode(MAPI_E_NO_SUPPORT));
}

STDMETHODIMP
SOB_GetIDsFromNames(LPSOB lpSOB,
    ULONG cPropNames,
    LPMAPINAMEID * lppPropNames,
    ULONG ulFlags,
    LPSPropTagArray * lppPropTags)
{
    /*  Do parameter validation */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (!lppPropNames || IsBadReadPtr(lppPropNames, (UINT)cPropNames*sizeof(LPMAPINAMEID))) ||
        (IsBadReadPtr(lppPropTags, sizeof(LPSPropTagArray))))
    {
        DebugTraceSc(SOB_GetIDsFromNames, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    DebugTraceSc(SOB_GetIDsFromNames, MAPI_E_NO_SUPPORT);
    return (ResultFromScode(MAPI_E_NO_SUPPORT));
}

STDMETHODIMP
SOB_ChangePassword(LPSOB lpSOB,
    LPTSTR lpOldPass,
    LPTSTR lpNewPass,
    ULONG ulFlags)
{
    /*  Do parameter validation */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (IsBadStringPtr(lpOldPass, MAX_STRING)) ||
        (IsBadStringPtr(lpNewPass, MAX_STRING)) ||
        (ulFlags & ~MAPI_UNICODE))
    {
        DebugTraceSc(SOB_ChangePassword, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }
    
    if ( ulFlags & MAPI_UNICODE )
    {
        DebugTraceSc(SOB_ChangePassword, MAPI_E_BAD_CHARWIDTH);
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH );
    }
              
    DebugTraceSc(SOB_ChangePassword, MAPI_E_NO_SUPPORT);
    return (ResultFromScode(MAPI_E_NO_SUPPORT));
}

STDMETHODIMP
SOB_ValidateState(LPSOB lpSOB,
    ULONG ulUIParam,
    ULONG ulFlags)
{
    ULONG ulFlagMask =  REFRESH_XP_HEADER_CACHE | \
                        PROCESS_XP_HEADER_CACHE | \
                        FORCE_XP_CONNECT | \
                        FORCE_XP_DISCONNECT | \
                        SUPPRESS_UI;
                        
    /*  Do parameter validation */

    if (IsBadWritePtr(lpSOB, sizeof(SOB)) ||
        (lpSOB->lcInit == 0) ||
        (lpSOB->lpsobMyAddress != lpSOB) ||
        (ulFlags & (~(ulFlagMask))))
    {
        DebugTraceSc(SOB_ValidateState, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    DebugTraceSc(SOB_ValidateState, MAPI_E_NO_SUPPORT);
    return (ResultFromScode(MAPI_E_NO_SUPPORT));
}


/* The following array maps a string identifier (IDS) to status code  */
/* (SCODE).  The order of SCODEs in the array has an external         */
/* dependency:  the order of elements in the array is dictated by     */
/* the IDS definitions in xpresrc.h.  This implicit association must  */
/* be maintained for the strings associated with string identifiers   */
/* to make sense.  Thus, if either this structure or the rc.h defines */
/* changes, the other must change to match it.                        */

SCODE mpIdsScode[] =
{
    SUCCESS_SUCCESS,
    MAPI_E_BUSY,
    MAPI_E_CALL_FAILED,
    MAPI_E_INVALID_PARAMETER,
    MAPI_E_NO_ACCESS,
    MAPI_E_NO_SUPPORT,
    MAPI_E_NOT_FOUND,
    MAPI_E_UNKNOWN_FLAGS,
    MAPI_E_VERSION,
    MAPI_E_NOT_ENOUGH_MEMORY,
    MAPI_W_ERRORS_RETURNED
};


/*
 *  MapScodeSz
 *
 *  Purpose:
 *      Look up an SCODE in a mapping of IDS <-> SCODE to find its
 *      associated informational string and return it (with memory
 *      allocated by this function) to the caller.
 *
 *  Arguments:
 *      sc          The SCODE to look up.
 *      lpxpl       Pointer to the Transport Logon object
 *      lppszError  Location in which to place an address to a
 *                  newly allocated buffer containing the
 *                  informational string associated with scArg.
 *
 *  Returns:
 *      HRESULT
 *
 *  Errors:
 *      MAPI_E_NO_MEMORY    Could not allocate space for
 *                          the return string.
 */

HRESULT
MapScodeSz(SCODE scArg, LPXPL lpxpl, LPTSTR * lppszError)
{
    HRESULT hr = hrSuccess;
    SCODE sc = SUCCESS_SUCCESS;
    ULONG cb;
    UINT ui;
    UINT ids;
    UINT uiMax = sizeof mpIdsScode / sizeof mpIdsScode[0];
    TCHAR rgch[512];

    if (!lppszError || IsBadWritePtr(lppszError, sizeof(LPVOID)))
    {
        DebugTrace("Bad lppszError in MapScodeSz\n");
        return ResultFromScode(E_INVALIDARG);
    }
    
    *lppszError = NULL;

    /* Linear search in mpIdsScode for sc. */

    for (ui = 0; ui < uiMax; ui++)
        if (mpIdsScode[ui] == scArg)
            break;

    if (ui == uiMax)
        ids = IDS_UNKNOWN_ERROR;
    else
        ids = ui + LIB_ERRORS;

    if (!LoadString(lpxpl->lpxppParent->hInst, ids, rgch, sizeof(rgch)))
    {
        hr = ResultFromScode(MAPI_E_NOT_ENOUGH_MEMORY);
        DebugTraceResult(LoadString failed in MapScodeSz, hr);
        goto ret;
    }

    /* Allocate memory for return variable and set it */

    cb = (lstrlen(rgch) + 1) * sizeof(TCHAR);
    sc = lpxpl->AllocateBuffer(cb, (LPVOID *) lppszError);

    if (sc != SUCCESS_SUCCESS)
    {
        hr = ResultFromScode(sc);
        DebugTraceResult(AllocateBuffer failed in MapScodeSz, hr);
        goto ret;
    }

    lstrcpy(*lppszError, rgch);

ret:
    DebugTraceResult(MapScodeSz, hr);
    return hr;
}
