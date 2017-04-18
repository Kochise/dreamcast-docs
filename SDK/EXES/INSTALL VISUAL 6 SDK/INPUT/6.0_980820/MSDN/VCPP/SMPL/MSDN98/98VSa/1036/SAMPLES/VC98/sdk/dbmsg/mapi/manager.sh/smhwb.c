/*
 *  S M H W B . C
 *
 *  Sample mail handling wastbasket message archiving
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"

/*
 *  sptFilterWb
 *
 *  These are the columns used in wastebasket filtering\archiving
 */
enum { iwbEid, iwbDlv, iwbSbmt };
const static SizedSPropTagArray (3, sptFilterWb) =
{
    3,
    {
        PR_ENTRYID,
        PR_MESSAGE_DELIVERY_TIME,
        PR_CLIENT_SUBMIT_TIME
    }
};


/*
 *  HrFilterDeleted()
 *
 *  Purpose:
 *
 *      Filters all the current message from the 'Wastebasket'/'Deleted Items'
 *      folder based on the archiving model used in sent mail processing.
 *
 *  Arguments:
 *
 *      lpwb            wastbucket struct for the current store
 *      lpbin           sbinary holding the entryid of the message
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrFilterDeleted (LPWB lpwb, LPSRowSet lprws)
{
    HRESULT hr = ResultFromScode (MAPI_E_NOT_ENOUGH_MEMORY);
    FILETIME ft;
    LPBYTE lpeid = NULL;
    LPMAPIFOLDER lpfldr = lpwb->lpfldr;
    LPMDB lpmdb = lpwb->lpmdb;
    LPSBinary lpbin = NULL;
    LPSMH lpsmh = lpwb->lpsmh;
    SBinaryArray sba;
    UINT ib;
    UINT irw;
    ULONG cb = lpwb->lpvalEid->Value.bin.cb;
    ULONG ulFlags = 0;

    if (!FAILED ((*lpsmh->lpfnAlloc) (lprws->cRows * sizeof(SBinary), &lpbin)))
    {
        for (irw = 0; irw < lprws->cRows; )
        {
            ib = 0;
            if (!FAILED ((*lpsmh->lpfnAlloc) (cb, &lpeid)))
            {
                memcpy (lpeid, lpwb->lpvalEid->Value.bin.lpb, (UINT)cb);
                if (lprws->aRow[irw].lpProps[iwbDlv].ulPropTag == PR_MESSAGE_DELIVERY_TIME)
                    ft = lprws->aRow[irw].lpProps[iwbDlv].Value.ft;
                else if (lprws->aRow[irw].lpProps[iwbSbmt].ulPropTag == PR_CLIENT_SUBMIT_TIME)
                    ft = lprws->aRow[irw].lpProps[iwbSbmt].Value.ft;
                else
                {
                    ++irw;
                    continue;
                }
                
                hr = HrArchiveByDate (lpsmh,
                                &ft,
                                lpfldr,
                                lpmdb,
                                &lpwb->bkit,
                                lpsmh->fCatWb,
                                cb,
                                lpeid);
                if (!HR_FAILED (hr))
                {
                    lpbin[ib++] = lprws->aRow[irw].lpProps[iwbEid].Value.bin;
                    for (irw += 1; irw < lprws->cRows; irw++)
                    {
                        if (lprws->aRow[irw].lpProps[iwbDlv].ulPropTag == PR_MESSAGE_DELIVERY_TIME)
                        {
                            ft = lprws->aRow[irw].lpProps[iwbDlv].Value.ft;
                            if ((CompareFileTime (&lpwb->bkit.dft.ftStart, &ft) == 1) ||
                                (CompareFileTime (&lpwb->bkit.dft.ftEnd, &ft) == -1))
                                break;

                            lpbin[ib++] = lprws->aRow[irw].lpProps[iwbEid].Value.bin;
                        }
                        else if (lprws->aRow[irw].lpProps[iwbSbmt].ulPropTag == PR_CLIENT_SUBMIT_TIME)
                        {
                            ft = lprws->aRow[irw].lpProps[iwbSbmt].Value.ft;
                            if ((CompareFileTime (&lpwb->bkit.dft.ftStart, &ft) == 1) ||
                                (CompareFileTime (&lpwb->bkit.dft.ftEnd, &ft) == -1))
                                break;

                            lpbin[ib++] = lprws->aRow[irw].lpProps[iwbEid].Value.bin;
                        }
                        else
                            break;
                    }

                    sba.cValues = ib;
                    sba.lpbin = lpbin;
                    hr = lpfldr->lpVtbl->CopyMessages (lpfldr,
                                &sba,
                                NULL,
                                lpwb->bkit.lpfldr,
                                0,
                                NULL,
                                MAPI_MOVE);
                }
            }
            (*lpsmh->lpfnFree) (lpeid);
            lpeid = NULL;
        }
    }
    (*lpsmh->lpfnFree) (lpbin);
    DebugTraceResult (HrFilterDeleted(), hr);
    return hr;
}


/*
 *  FilterDeletedThread()
 *  
 *  Purpose:
 *  
 *      This function will spin off and do the archiving of the messages
 *      in the deleted folder.  It is important to note that on 32 bit
 *      platforms, this function will belong to its own thread.  Thus
 *      cleanup and logoff must wait for the thread to terminate before
 *      releasing returning.
 *  
 *  Arguments:
 *  
 *      lpwb        pointer to the wastebasket object
 *  
 *  Returns:
 *  
 *      (DOWRD) : Ignored
 */
static DWORD WINAPI
FilterDeletedThread (LPWB lpwb)
{
    HRESULT hr;
    LPMAPITABLE lptbl;
    LPSRowSet lprws = NULL;

    lptbl = lpwb->lptbl;

#ifdef  _WIN32
    SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_IDLE);
#endif

    while (!lpwb->fBail)
    {
        lptbl->lpVtbl->SeekRow (lptbl, BOOKMARK_BEGINNING, 0, NULL);
        hr = lptbl->lpVtbl->QueryRows (lptbl, 64, 0, &lprws);
        if (HR_FAILED (hr))
            break;

        if (lprws->cRows)
        {
            //  Filter the deleted messages
            //
            HrFilterDeleted (lpwb, lprws);

            while (lprws->cRows)
                (*lpwb->lpsmh->lpfnFree) (lprws->aRow[--lprws->cRows].lpProps);
        }
        else
            break;

        (*lpwb->lpsmh->lpfnFree) (lprws);
        lprws = NULL;
    }
    
    (*lpwb->lpsmh->lpfnFree) (lprws);
    
    /*  Reset the filtering indicator */
#ifdef  _WIN32
    CloseHandle (lpwb->ht);
    lpwb->ht = NULL;
#endif
    return 0;
}


/*
 *  WBNotify()
 *
 *  Purpose:
 *
 *      Notification callback on the WB folders of message stores.  When
 *      rows are added to the WB contents table, we enum the table and
 *      filter each message added.
 *
 *  Arguments:
 *
 *      lpv         void pointer to current WB struct
 *      cntf        count of notifications
 *      lpntf       notifications
 *
 *  Returns:
 *
 *      (SCODE)
 */
STDAPI_(SCODE)
WBNotify (LPVOID lpv, ULONG cntf, LPNOTIFICATION lpntf)
{
    BOOL fFilter = FALSE;
    LPWB lpwb = (LPWB)lpv;

    /* Quick and dirty check on the context */

    if (IsBadReadPtr (lpv, sizeof(WB)) ||
        IsBadReadPtr (((LPWB)lpv)->lpsmh, sizeof(SMH)))
        return S_OK;

    /* Just incase we were turned off */

    if (lpwb->lpsmh->fCatWb)
    {
        while (cntf--)
        {
            Assert (lpntf->ulEventType == fnevTableModified);
            if (lpntf->info.tab.ulTableEvent == TABLE_ROW_ADDED)
            {
                fFilter |= TRUE;
                break;
            }
        }
        
        if (fFilter)
        {
#ifdef  _WIN32
            if(!lpwb->ht)
            {
                DWORD dw;
                
                lpwb->ht = CreateThread (NULL,
                            1024,
                            (LPTHREAD_START_ROUTINE)FilterDeletedThread,
                            lpwb,
                            0,
                            &dw);
            }
#else
            FilterDeletedThread (lpwb);
#endif  // _WIN32
        }       
    }
    return S_OK;
}


/*
 *  HrInitDeletedMailFilter()
 *
 *  Purpose:
 *
 *      Inits the deleted mail filters by opening the store, finding the
 *      WB folder, opening the contents table of the WB, and registering
 *      for table modification notifications.
 *
 *  Arguments:
 *
 *      lpsmg           the sample mail handler object
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrInitDeletedMailFilter (LPSMH lpsmh)
{
    HRESULT hr;
    LPMAPIADVISESINK lpadvz = NULL;
    LPMAPIFOLDER lpfldr = NULL;
    LPMAPITABLE lptbl = NULL;
    LPMDB lpmdb = NULL;
    LPSPropValue lpval = NULL;
    LPWB lpwb = NULL;
    ULONG ulType;
    UINT cerr = 0;
    UINT i;

    for (i = 0; i < lpsmh->lpstotbl->cSto; i++)
    {
        hr = ResultFromScode ((*lpsmh->lpfnAlloc) (sizeof(WB), &lpwb));
        if (HR_FAILED (hr))
            goto nxt;
        memset (lpwb, 0, sizeof(WB));

        hr = HrOpenStoEntry (lpsmh->lpsess, &lpsmh->lpstotbl->aSto[i], &lpmdb);
        if (HR_FAILED (hr))
            goto nxt;

        hr = HrGetOneProp ((LPMAPIPROP)lpmdb, PR_IPM_WASTEBASKET_ENTRYID, &lpval);
        if (HR_FAILED (hr))
            goto nxt;

        hr = lpmdb->lpVtbl->OpenEntry (lpmdb,
                                lpval->Value.bin.cb,
                                (LPENTRYID)lpval->Value.bin.lpb,
                                NULL,
                                MAPI_MODIFY,
                                &ulType,
                                (LPUNKNOWN FAR *)&lpfldr);
        if (HR_FAILED (hr))
            goto nxt;

        hr = lpfldr->lpVtbl->GetContentsTable (lpfldr, 0, &lptbl);
        if (HR_FAILED (hr))
            goto nxt;

        hr = lptbl->lpVtbl->SetColumns (lptbl, (LPSPropTagArray)&sptFilterWb, 0);
        if (HR_FAILED (hr))
            goto nxt;

        hr = HrAllocAdviseSink ((LPNOTIFCALLBACK)&WBNotify, lpwb, &lpadvz);
        if (HR_FAILED (hr))
            goto nxt;

        hr = lptbl->lpVtbl->Advise (lptbl, fnevTableModified, lpadvz, &lpwb->ulAdvz);
        if (HR_FAILED (hr))
            goto nxt;

        UlAddRef (lptbl);
        UlAddRef (lpfldr);
        lpwb->lpmdb = lpmdb;
        lpwb->lptbl = lptbl;
        lpwb->lpfldr = lpfldr;
        lpwb->lpvalEid = lpval;
        lpwb->lpsmh = lpsmh;
        lpval = NULL;

        /* Hook it in */

        lpwb->wbNext = lpsmh->lstWb;
        lpsmh->lstWb = lpwb;
        lpwb = NULL;
nxt:

        if (HR_FAILED (hr))
            cerr++;

        (*lpsmh->lpfnFree) (lpval);
        lpval = NULL;

        (*lpsmh->lpfnFree) (lpwb);
        lpwb = NULL;

        UlRelease (lpadvz);
        lpadvz = NULL;

        UlRelease (lpfldr);
        lpfldr = NULL;

        UlRelease (lptbl);
        lptbl = NULL;
    }

    hr = ResultFromScode (cerr ? MAPI_W_ERRORS_RETURNED : S_OK);
    DebugTraceResult (HrInitDeletedMailFilter(), hr);
    return hr;
}


