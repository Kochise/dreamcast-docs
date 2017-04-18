/***********************************************************************
 *
 *  ABCTBL3.C
 *
 *  Contents Table - Part 3.
 *
 *
 *  The following routines are implemented in this file.
 *
 *
 *      IVTABC_QueryInterface
 *      IVTABC_Release
 *      IVTABC_SortTable
 *      IVTABC_QuerySortOrder
 *      IVTABC_CreateBookmark
 *      IVTABC_FreeBookmark
 *      IVTABC_ExpandRow
 *      IVTABC_ColapseRow
 *      IVTABC_WaitForCompletion
 *      IVTABC_Abort
 *      IVTABC_Advise
 *      IVTABC_Unadvise
 *      IVTABC_GetStatus
 *      IVTABC_SetColumns
 *      IVTABC_QueryColumns
 *      IVTABC_GetCollapseState,
 *      IVTABC_SetCollapseState,
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/





#include "abp.h"
#include "abctbl.h"
#include "sampabp.rh"


/*
 *  Default sort order set
 */
static const SizedSSortOrderSet(1, sosIVTABC) =
{
    1,
    0,
    0,
    {
        {
            PR_DISPLAY_NAME_A, TABLE_SORT_ASCEND
        }
    }
};




/*************************************************************************
 *
 *
 -  AVTABC_QueryInterface
 -
 *
 *
 *
 */
STDMETHODIMP 
IVTABC_QueryInterface(LPIVTABC lpIVTAbc,
    REFIID lpiid,
    LPVOID FAR * lppNewObj)
{

    HRESULT hResult = hrSuccess;

    IVTABC_ValidateObject(QueryInterface, lpIVTAbc);

    Validate_IUnknown_QueryInterface(lpIVTAbc, lpiid, lppNewObj);

    
    /*  See if the requested interface is one of ours */

    if (memcmp(lpiid, &IID_IUnknown, sizeof(IID)) &&
        memcmp(lpiid, &IID_IMAPITable, sizeof(IID)))
    {
        *lppNewObj = NULL;      /* OLE requires zeroing the [out] parameter */
        DebugTraceSc(IVTABC_QueryInterface, E_NOINTERFACE);
        return ResultFromScode(E_NOINTERFACE);
    }

    /*  We'll do this one. Bump the usage count and return a new pointer. */

    EnterCriticalSection(&lpIVTAbc->cs);
    ++lpIVTAbc->lcInit;
    LeaveCriticalSection(&lpIVTAbc->cs);
    
    *lppNewObj = lpIVTAbc;

    DebugTraceResult(IVTABC_QueryInterface,hResult);
    return hResult;
}

/*************************************************************************
 *
 -  IVTABC_Release
 -
 *
 *      Decrement the reference count on this object and free it if
 *      the reference count is zero.
 *      Returns the reference count.
 */

STDMETHODIMP_(ULONG)
IVTABC_Release(LPIVTABC lpIVTAbc)
{
    ULONG ulBK;
    long lcInit;
    
    /*
     *  Check to see if it's big enough to hold this object
     */
    if (IsBadReadPtr(lpIVTAbc, sizeof(IVTABC)))
    {
        /*
         *  Not large enough
         */
        return 1;
    }

    /*
     *  Check to see that it's the correct vtbl
     */
    if (lpIVTAbc->lpVtbl != &vtblIVTABC)
    {
        /*
         *  Not my vtbl
         */
        return 1;
    }

    Validate_IUnknown_Release(lpIVTAbc);


    EnterCriticalSection(&lpIVTAbc->cs);
    lcInit = --lpIVTAbc->lcInit;
    LeaveCriticalSection(&lpIVTAbc->cs);

    if (lcInit == 0)
    {
        /*
         *  Free up the current column set
         */
        if (lpIVTAbc->lpPTAColSet != ptagaivtabcColSet)
        {
            lpIVTAbc->lpFreeBuff (lpIVTAbc->lpPTAColSet);
        }

        /*
         *  Close up the file
         */
        if (lpIVTAbc->hFile != INVALID_HANDLE_VALUE)
        {
            CloseHandle(lpIVTAbc->hFile);
            lpIVTAbc->hFile = INVALID_HANDLE_VALUE;
        }

        /*
         *  Free up the file name
         */
        lpIVTAbc->lpFreeBuff(lpIVTAbc->lpszFileName);

        /*
         *  Rip through the bookmarks and free up any that are there
         */
        for (ulBK = 0; ulBK < MAX_BOOKMARKS; ulBK++)
            if (lpIVTAbc->rglpABCBK[ulBK])
            {
                (*(lpIVTAbc->lpFreeBuff)) (lpIVTAbc->rglpABCBK[ulBK]);
                lpIVTAbc->rglpABCBK[ulBK] = NULL;
            }

        /*
         *  Free up the ANR stuff, if used
         */
        lpIVTAbc->lpFreeBuff (lpIVTAbc->lpszPartialName);

        FreeANRBitmaps(lpIVTAbc);

        /*
         *  Free up the advise list, if used
         */
        if (lpIVTAbc->parglpAdvise)
            lpIVTAbc->lpMalloc->lpVtbl->Free(lpIVTAbc->lpMalloc, lpIVTAbc->parglpAdvise);

        /*  
         *  Release our reference to the ABLogon object.
         */
        if (lpIVTAbc->lpABLogon)
        {
            lpIVTAbc->lpABLogon->lpVtbl->Release(lpIVTAbc->lpABLogon);
            lpIVTAbc->lpABLogon = NULL;
        }

        /* Delete critical section for this object */
        DeleteCriticalSection(&lpIVTAbc->cs);

        /* Deregister the idle routine */

        DeregisterIdleRoutine(lpIVTAbc->ftg);

        /*
         *  Set the vtbl to NULL.  This way the client will find out
         *  real fast if it's calling a method on a released object.  That is,
         *  the client will crash.  Hopefully, this will happen during the
         *  development stage of the client.
         */
        lpIVTAbc->lpVtbl = NULL;

        /*
         *  Need to free the object
         */

        lpIVTAbc->lpFreeBuff(lpIVTAbc);
        return 0;
    }

    return lcInit;
}



/*
 -  IVTABC_SortTable
 -
 *  The Sample Address Book does not resort it's views.
 *
 */
STDMETHODIMP 
IVTABC_SortTable(LPIVTABC lpIVTAbc,
    LPSSortOrderSet lpSortCriteria,
    ULONG ulFlags)
{
    HRESULT hResult;

    /*
     *  Validate parameters
     */
    IVTABC_ValidateObject(SortTable, lpIVTAbc);
    
    Validate_IMAPITable_SortTable(lpIVTAbc, lpSortCriteria, ulFlags);


    /*
     *  We don't support sorting this table
     */
    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

    DebugTraceResult(IVTABC_SortTable, hResult);
    return hResult;

}

/*
 -  IVTABC_QuerySortOrder
 -
 *
 *  For this implementation there is only one sort order
 */

STDMETHODIMP 
IVTABC_QuerySortOrder(LPIVTABC lpIVTAbc,
    LPSSortOrderSet * lppSortCriteria)
{
    SCODE scode;
    HRESULT hResult = hrSuccess;
    int cbSize;

    /*
     *  Validate parameters
     */

    IVTABC_ValidateObject(QuerySortOrder, lpIVTAbc);

    Validate_IMAPITable_QuerySortOrder(lpIVTAbc, lppSortCriteria);


    /*  Calculate size of the structure we're gonna copy */
    cbSize = CbNewSSortOrderSet((int)sosIVTABC.cSorts);

    scode = lpIVTAbc->lpAllocBuff(cbSize, (LPVOID *) lppSortCriteria);
    if (FAILED(scode))
    {
        hResult = ResultFromScode(scode);

        goto out;
    }

    /*
     *  Copy the column set in
     */
    if (cbSize)
        memcpy(*lppSortCriteria, &sosIVTABC, cbSize);

out:

    DebugTraceResult(IVTABC_QuerySortOrder, hResult);
    return hResult;

}




/*
 -  IVTABC_CreateBookmark
 -
 *  Creates a bookmark associated with a row in a table
 *
 */
STDMETHODIMP 
IVTABC_CreateBookmark(LPIVTABC lpIVTAbc,
    BOOKMARK * lpbkPosition)
{
    SCODE scode;
    HRESULT hResult = hrSuccess;
    ULONG ulBK;
    LPABCBK lpABCBK = NULL;
    ULONG cbRead = 0;

    /*
     *  Validate parameters
     */

    IVTABC_ValidateObject(CreateBookmark, lpIVTAbc);

    Validate_IMAPITable_CreateBookmark(lpIVTAbc, lpbkPosition);


    EnterCriticalSection(&lpIVTAbc->cs);


    /*
     *  Open the file
     */
    hResult = HrOpenFile(lpIVTAbc);
    if (HR_FAILED(hResult))
    {
        goto out;
    }

    /*
     *  Shortcuts first
     */
    if (lpIVTAbc->ulPosition == lpIVTAbc->ulMaxPos)
    {
        *lpbkPosition = BOOKMARK_END;
        return hrSuccess;
    }

    /*
     *  search for a blank bookmark
     */
    for (ulBK = 0; lpIVTAbc->rglpABCBK[ulBK] && ulBK < MAX_BOOKMARKS; ulBK++);

    /*  did we find any??  */
    if (ulBK == MAX_BOOKMARKS)
    {
        hResult = ResultFromScode(MAPI_E_UNABLE_TO_COMPLETE);

        goto out;
    }


    scode = lpIVTAbc->lpAllocBuff (sizeof(ABCBK),(LPVOID *) &lpABCBK);
    if (FAILED(scode))
    {
        hResult = ResultFromScode(scode);
        goto out;
    }

    /*
     *  Fill in new bookmark
     */
    lpABCBK->filetime = lpIVTAbc->filetime;
    lpABCBK->ulPosition = lpIVTAbc->ulPosition;

    /*  Seek to position in file  */
    (void) SetFilePointer(lpIVTAbc->hFile, lpABCBK->ulPosition, NULL, FILE_BEGIN);

    /*  Read in the record at that location  */
    if (!ReadFile(lpIVTAbc->hFile,
            (LPVOID) &(lpABCBK->abcrec), sizeof(ABCREC), &cbRead, NULL))
    {
        goto readerror;
    }
    /*  Second check  */
    if (cbRead != sizeof(ABCREC))
    {
        goto readerror;
    }

    /*
     *  Put this in the bookmark structure
     */
    lpIVTAbc->rglpABCBK[ulBK] = lpABCBK;

    /*  Return the bookmark  */
    *lpbkPosition = ulBK + 3;

out:
    LeaveCriticalSection(&lpIVTAbc->cs);

    DebugTraceResult(IVTABC_CreateBookmark, hResult);
    return hResult;

readerror:
    /*
     *  Didn't get the record.
     */

    /*  Restore back to original position  */
    (void) SetFilePointer(lpIVTAbc->hFile, lpIVTAbc->ulPosition, NULL, FILE_BEGIN);

    /*  Free up the new bookmark  */
    lpIVTAbc->lpFreeBuff(lpABCBK);

    hResult = ResultFromScode(MAPI_E_UNABLE_TO_COMPLETE);
    SetErrorIDS(lpIVTAbc, hResult, IDS_SAB_NO_READ);

    goto out;
}

/*************************************************************************
 *
 -  IVTABC_FreeBookmark
 -
 *  Frees up the given bookmark
 *
 *
 *
 */
STDMETHODIMP 
IVTABC_FreeBookmark(LPIVTABC lpIVTAbc,
    BOOKMARK bkPosition)
{
    HRESULT hResult = hrSuccess;

    /*
     *  Validate parameters
     */

    IVTABC_ValidateObject(FreeBookmark, lpIVTAbc);

    Validate_IMAPITable_FreeBookmark(lpIVTAbc, bkPosition);


    EnterCriticalSection(&lpIVTAbc->cs);


    /*
     *  Don't try and free up any of the standard bookmarks
     */
    if ((bkPosition != BOOKMARK_BEGINNING) &&
        (bkPosition != BOOKMARK_CURRENT) &&
        (bkPosition != BOOKMARK_END))
    {
        ULONG ulBK = (ULONG) bkPosition - 3;

        /*
         *  See if it's in range
         */
        if (ulBK >= 0 && ulBK < MAX_BOOKMARKS)
        {
            LPABCBK lpABCBK = NULL;

            /*  If it's valid...  */
            if (lpABCBK = lpIVTAbc->rglpABCBK[ulBK])    /* '=' on purpose */
            {
                /*  ...free it up.  */

                lpIVTAbc->lpFreeBuff(lpABCBK);
                lpIVTAbc->rglpABCBK[ulBK] = NULL;
            }

        }
        else
        {
            /*
             * It's an error
             */
            hResult = ResultFromScode(E_INVALIDARG);

        }
    }

    LeaveCriticalSection(&lpIVTAbc->cs);

    DebugTraceResult(IVTABC_FreeBookmark, hResult);
    return hResult;

}


/*************************************************************************
 *
 -  IVTABC_ExpandRow
 -
 *  Stubbed out.  This table doesn't implement catagorization.
 *
 *
 *
 */
STDMETHODIMP 
IVTABC_ExpandRow(LPIVTABC lpIVTAbc, ULONG cbIKey, LPBYTE pbIKey,
    ULONG ulRowCount, ULONG ulFlags, LPSRowSet FAR * lppRows,
    ULONG FAR * lpulMoreRows)

{
    HRESULT hResult;

    /*
     *  Validate parameters
     */

    IVTABC_ValidateObject(ExpandRow, lpIVTAbc);

    Validate_IMAPITable_ExpandRow(lpIVTAbc,  cbIKey,  pbIKey,
                            ulRowCount,  ulFlags,  lppRows, lpulMoreRows);


    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

    DebugTraceResult(IVTABC_ExpandRow, hResult);
    return hResult;

}

/*************************************************************************
 *
 -  IVTABC_CollapseRow
 -
 *  Stubbed out.  This table doesn't implement catagorization.
 *
 *
 *
 */
STDMETHODIMP 
IVTABC_CollapseRow(LPIVTABC lpIVTAbc, ULONG cbIKey, LPBYTE pbIKey,
    ULONG ulFlags, ULONG FAR * lpulRowCount)

{
    HRESULT hResult;

    /*
     *  Validate parameters
     */

    IVTABC_ValidateObject(CollapseRow, lpIVTAbc);

    Validate_IMAPITable_CollapseRow(lpIVTAbc, cbIKey, pbIKey, ulFlags, lpulRowCount);


    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

    DebugTraceResult(IVTABC_CollapseRow, hResult);
    return hResult;

}

/*************************************************************************
 *
 -  IVTABC_WaitForCompletion
 -
 *  Stubbed out.
 *
 *
 *
 */
STDMETHODIMP 
IVTABC_WaitForCompletion(LPIVTABC lpIVTAbc, ULONG ulFlags,
    ULONG ulTimeout, ULONG FAR * lpulTableStatus)
{
    HRESULT hResult;

    IVTABC_ValidateObject(WaitForCompletion, lpIVTAbc);
    
    Validate_IMAPITable_WaitForCompletion(lpIVTAbc, ulFlags, ulTimeout, 
                                            lpulTableStatus);


    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);

    DebugTraceResult(IVTABC_WaitForCompletion, hResult);
    return hResult;

}
/*************************************************************************
 *
 -  IVTABC_Abort
 -
 *  Nothing ever to abort...
 *
 *
 *
 */
STDMETHODIMP 
IVTABC_Abort(LPIVTABC lpIVTAbc)

{

    /*
     *  Validate parameters
     */

    IVTABC_ValidateObject(Abort, lpIVTAbc);

    Validate_IMAPITable_Abort(lpIVTAbc);

    return hrSuccess;

}

/*************************************************************************
 *
 *
 -  IVTABC_Advise
 -
 *
 *
 *
 */
STDMETHODIMP 
IVTABC_Advise(LPIVTABC lpIVTAbc,
    ULONG ulEventmask,
    LPMAPIADVISESINK lpAdviseSink,
    ULONG FAR * lpulConnection)
{
    HRESULT hResult = hrSuccess;
    UINT iAdvise;

    
    /*
     *  Validate the parameters
     */
    
    IVTABC_ValidateObject(Advise, lpIVTAbc);
    
    Validate_IMAPITable_Advise(lpIVTAbc, ulEventmask, lpAdviseSink,
                                lpulConnection);
    
    /* Get the Critical Section */
    EnterCriticalSection(&lpIVTAbc->cs);

    for (iAdvise = 0;
        lpIVTAbc->parglpAdvise && iAdvise < lpIVTAbc->cAdvise;
        ++iAdvise)
    {
        if (lpIVTAbc->parglpAdvise[iAdvise] == NULL)
            break;
    }

    if (iAdvise >= lpIVTAbc->cAdvise)
    {
        /*
         *   Realloc the array if it exists
         */
        if (lpIVTAbc->parglpAdvise)
        {
            lpIVTAbc->parglpAdvise = lpIVTAbc->lpMalloc->lpVtbl->Realloc(
                lpIVTAbc->lpMalloc,
                lpIVTAbc->parglpAdvise,
                (lpIVTAbc->cAdvise + 1) * sizeof(LPMAPIADVISESINK));
        }
        else
        {
            lpIVTAbc->parglpAdvise = lpIVTAbc->lpMalloc->lpVtbl->Alloc(
                lpIVTAbc->lpMalloc,
                (lpIVTAbc->cAdvise + 1) * sizeof(LPMAPIADVISESINK));
        }

        /*
         *  Could we get the desired memory?
         */
        if (lpIVTAbc->parglpAdvise == NULL)
        {
            hResult = MakeResult(E_OUTOFMEMORY);
            goto ret;
        }
    }

    lpIVTAbc->cAdvise++;

    *lpulConnection = lpIVTAbc->ulConnectMic + iAdvise;

    lpIVTAbc->parglpAdvise[iAdvise] = lpAdviseSink;

    lpAdviseSink->lpVtbl->AddRef(lpAdviseSink);

ret:
    /* leave critical section */
    LeaveCriticalSection(&lpIVTAbc->cs);

    DebugTraceResult(IVTABC_Advise, hResult);
    return hResult;
}

/*************************************************************************
 *
 *
 -  IVTABC_Unadvise
 -
 *
 *
 *
 */
STDMETHODIMP 
IVTABC_Unadvise(LPIVTABC lpIVTAbc, ULONG ulConnection)
{
    LPMAPIADVISESINK padvise;
    UINT iAdvise;
    HRESULT hResult = hrSuccess;

    IVTABC_ValidateObject(Unadvise, lpIVTAbc);

    Validate_IMAPITable_Unadvise(lpIVTAbc, ulConnection);


    if (ulConnection - lpIVTAbc->ulConnectMic > (ULONG) lpIVTAbc->cAdvise)
    {
        DebugTraceSc(IVTABC_Unadvise, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /* Get the Critical Section */
    EnterCriticalSection(&lpIVTAbc->cs);

    iAdvise = (UINT) (ulConnection - lpIVTAbc->ulConnectMic);
    padvise = lpIVTAbc->parglpAdvise[iAdvise];
    padvise->lpVtbl->Release(padvise);
    lpIVTAbc->parglpAdvise[iAdvise] = NULL;
    lpIVTAbc->cAdvise--;

    /* leave critical section */
    LeaveCriticalSection(&lpIVTAbc->cs);

    DebugTraceResult(IVTABC_Unadvise, hResult);
    return hResult;
}

/*************************************************************************
 *
 -  IVTABC_GetStatus
 -
 *  Returns the status of this table.  This table really isn't
 *  dynamic yet, but it could be...
 *
 *
 */
STDMETHODIMP 
IVTABC_GetStatus(LPIVTABC lpIVTAbc,
    ULONG * lpulTableStatus,
    ULONG * lpulTableType)
{

    /*
     *  Parameter checking
     */

    IVTABC_ValidateObject(GetStatus, lpIVTAbc);

    Validate_IMAPITable_GetStatus(lpIVTAbc, lpulTableStatus, lpulTableType);


    *lpulTableStatus = TBLSTAT_COMPLETE;
    *lpulTableType = TBLTYPE_DYNAMIC;

    return hrSuccess;
}

/*************************************************************************
 *
 -  IVTABC_SetColumns
 -
 *
 *  SetColumns for contents table.
 *
 */
STDMETHODIMP 
IVTABC_SetColumns(LPIVTABC lpIVTAbc,
    LPSPropTagArray lpPTAColSet,
    ULONG ulFlags)
{
    SCODE scode;
    HRESULT hResult = hrSuccess;
    int cbSizeOfColSet;
    LPSPropTagArray lpPTAColSetT;
    ULONG uliCol;

    /*
     *  Check parameters
     */
    IVTABC_ValidateObject(SetColumns, lpIVTAbc);
    
    Validate_IMAPITable_SetColumns(lpIVTAbc, lpPTAColSet, ulFlags);


    /*
     *  Verify that there are no PT_ERRORs here...
     */
    for (uliCol = 0; uliCol < lpPTAColSet->cValues; uliCol++)
    {
        if (PROP_TYPE(lpPTAColSet->aulPropTag[uliCol]) == PT_ERROR)
        {
            hResult = ResultFromScode(E_INVALIDARG);

            DebugTraceResult(IVTABC_GetStatus, hResult);
            return hResult;
        }
    }

    /*
     *  Allocate a new column set.
     */

    cbSizeOfColSet = CbNewSPropTagArray(lpPTAColSet->cValues);

    scode = lpIVTAbc->lpAllocBuff(cbSizeOfColSet,(LPVOID *) &lpPTAColSetT);

    if (FAILED(scode))
    {
        hResult = ResultFromScode(scode);

        DebugTraceResult(IVTABC_GetStatus, hResult);
        return hResult;
    }

    /*
     *  Copy the column set in
     */
    if (cbSizeOfColSet)
        memcpy(lpPTAColSetT, lpPTAColSet, cbSizeOfColSet);


    EnterCriticalSection(&lpIVTAbc->cs);


    if (lpIVTAbc->lpPTAColSet != ptagaivtabcColSet)
    {
        /*
         *  Free up the old column set
         */
        lpIVTAbc->lpFreeBuff(lpIVTAbc->lpPTAColSet);
    }

    lpIVTAbc->lpPTAColSet = lpPTAColSetT;


    LeaveCriticalSection(&lpIVTAbc->cs);
    

    return hrSuccess;

}

/*************************************************************************
 *
 -  IVTABC_QueryColumns
 -
 *
 *
 *  I always have all my columns available...  and active.
 */
STDMETHODIMP 
IVTABC_QueryColumns(LPIVTABC lpIVTAbc,
    ULONG ulFlags,
    LPSPropTagArray FAR * lppColumns)
{
    SCODE scode;
    HRESULT hResult = hrSuccess;
    int cbSizeOfColSet;

    /*
     *  Check parameters
     */

    IVTABC_ValidateObject(QueryColumns, lpIVTAbc);

    Validate_IMAPITable_QueryColumns(lpIVTAbc, ulFlags, lppColumns);


    EnterCriticalSection(&lpIVTAbc->cs);

    /*
     *  Allocate enough memory for the column set
     */
    if (ulFlags & TBL_ALL_COLUMNS)

        cbSizeOfColSet = sizeof(ULONG) +
            (int)(ptagaivtabcColSet->cValues) * sizeof(ULONG);
    else
        cbSizeOfColSet = sizeof(ULONG) +
            (int)lpIVTAbc->lpPTAColSet->cValues * sizeof(ULONG);


    scode = lpIVTAbc->lpAllocBuff (cbSizeOfColSet,(LPVOID *) lppColumns);

    if (FAILED(scode))
    {
        hResult = ResultFromScode(scode);
        goto out;
    }

    /*
     *  Copy the column set in
     */
    if (ulFlags & TBL_ALL_COLUMNS)
        memcpy(*lppColumns, ptagaivtabcColSet, cbSizeOfColSet);
    else
        memcpy(*lppColumns, lpIVTAbc->lpPTAColSet, cbSizeOfColSet);


out:
    LeaveCriticalSection(&lpIVTAbc->cs);

    DebugTraceResult(IVTABC_QueryColumns, hResult);
    return hResult;

}

/*************************************************************************
 *
 -  IVTABC_GetCollapseState
 -
 *  Stubbed out.  Only necessary if this table were to support categorization.
 *
 *
 *
 */
STDMETHODIMP
IVTABC_GetCollapseState(LPIVTABC lpIVTAbc,
                        ULONG ulFlags,
                        ULONG cbInstanceKey,
                        LPBYTE pbInstanceKey,
                        ULONG FAR * lpcbCollapseState,
                        LPBYTE FAR * lppbCollapseState)
{

    HRESULT hResult;

    /*
     *  Check parameters
     */

    IVTABC_ValidateObject(GetCollapseState, lpIVTAbc);

    Validate_IMAPITable_GetCollapseState(lpIVTAbc, ulFlags, cbInstanceKey,
                                        pbInstanceKey, lpcbCollapseState,
                                        lppbCollapseState);

    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);
    DebugTraceResult(IVTABC_GetCollapseState, hResult);
    return hResult;
}

/*************************************************************************
 *
 -  IVTABC_SetCollapseState
 -
 *  Stubbed out.  Only necessary if this table were to support categorization.
 *
 *
 *
 */
STDMETHODIMP
IVTABC_SetCollapseState(LPIVTABC lpIVTAbc,
                        ULONG ulFlags,
                        ULONG cbCollapseState,
                        LPBYTE pbCollapseState,
                        BOOKMARK FAR * lpbkLocation)
{

    HRESULT hResult;

    /*
     *  Check parameters
     */

    IVTABC_ValidateObject(SetCollapseState, lpIVTAbc);

    Validate_IMAPITable_SetCollapseState(lpIVTAbc, ulFlags, cbCollapseState,
                                        pbCollapseState, lpbkLocation);


    hResult = ResultFromScode(MAPI_E_NO_SUPPORT);
    DebugTraceResult(IVTABC_SetCollapseState, hResult);
    return hResult;
}
