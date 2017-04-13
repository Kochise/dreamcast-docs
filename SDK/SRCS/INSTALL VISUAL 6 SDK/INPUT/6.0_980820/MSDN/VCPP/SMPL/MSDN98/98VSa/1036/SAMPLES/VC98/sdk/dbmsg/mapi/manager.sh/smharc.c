/*
 *  S M H A R C . C
 *
 *  Sample mail handling message archiving
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"

/*
 *  FIsLeapYear()
 *
 *  Used to calculate leap years when determining month ranges for
 *  archive folders.
 */
#define FIsLeapYear(_yr) ((!((_yr) % 400) || ((_yr) % 100) && !((_yr) % 4)) ? TRUE : FALSE)

/*
 *  sptMsgDates
 *
 *  The list of properties that are used for archiving.  If
 *  PR_MESSAGE_DELIVERY_TIME is not available, then SMH will use
 *  PR_CLIENT_SUBMIT_TIME.
 */
const static SizedSPropTagArray(2, sptMsgDates) =
{
    2,
    {
        PR_MESSAGE_DELIVERY_TIME,
        PR_CLIENT_SUBMIT_TIME
    }
};

/*
 *  sptFldrDates
 *
 *  Theses properties describe the range of dates that an archive folder
 *  with the returned EntryID will support.  This is used in the call to
 *  find a supporting sub-folder.
 */
const static SizedSPropTagArray (3, sptFldrDates) =
{
    3,
    {
        PR_START_DATE,
        PR_END_DATE,
        PR_ENTRYID
    }
};

/*
 *  rgtstrMonth
 *  rgtstrMonthFull
 *  rgwDaysPerMonth
 *
 *  These arrays are used in the calculation and creation of supporting
 *  archive folders.
 */
const static TCHAR FAR * rgtstrMonth[] =
{
    TEXT ("Jan"),
    TEXT ("Feb"),
    TEXT ("Mar"),
    TEXT ("Apr"),
    TEXT ("May"),
    TEXT ("Jun"),
    TEXT ("Jul"),
    TEXT ("Aug"),
    TEXT ("Sep"),
    TEXT ("Oct"),
    TEXT ("Nov"),
    TEXT ("Dec")
};
const TCHAR FAR * rgtstrMonthFull[] =
{
    TEXT ("January"),
    TEXT ("February"),
    TEXT ("March"),
    TEXT ("April"),
    TEXT ("May"),
    TEXT ("June"),
    TEXT ("July"),
    TEXT ("August"),
    TEXT ("September"),
    TEXT ("October"),
    TEXT ("November"),
    TEXT ("December")
};
const static WORD rgwDaysPerMonth[] =
{
    31, //  JAN
    28, //  FEB
    31, //  MAR
    30, //  APR
    31, //  MAY
    30, //  JUN
    31, //  JUL
    31, //  AUG
    30, //  SEP
    31, //  OCT
    30, //  NOV
    31  //  DEC
};


/*
 *  HrCacheFolder()
 *
 *  Purpose:
 *
 *      Caches the passed in entryid along with a matching folder
 *
 *  Arguments:
 *
 *      lpsmh       pointer to the sentmail handler
 *      cbeid       count of bytes for the entryid to check
 *      lpeid       data for the entryid to check
 *      lpcbeid     points to the cached entryid size
 *      lppeid      points to the cached entryid data
 *      lppfldr     points to the cached mapi folder object
 *      lpfUpdated  points to cache update flag
 *
 *  Returns:
 *
 *      (HRESULT)
 *      lpcbeid     [OUT] size of newly cached entryid
 *      lppeid      [OUT] data of newly cached entryid
 *      lppfldr     [OUT] folder corresponding to cached entryid
 *      lpfUpdated  [OUT] TRUE iff the out folder is not the
 *                          previously cached folder
 */
HRESULT
HrCacheFolder (LPSMH lpsmh,
    LPMDB lpmdbPref,
    ULONG cbeid,
    LPENTRYID lpeid,
    ULONG FAR * lpcbeid,
    LPENTRYID FAR * lppeid,
    LPMAPIFOLDER FAR * lppfldr,
    BOOL far * lpfUpdated)
{
    HRESULT hr;
    ULONG ulType;
    ULONG ulMatch;
    LPMAPIPROP lpmp = NULL;

    /* Init the update flag */

    *lpfUpdated = FALSE;

    /*  Is the topmost sent mail folder the same folder
     *  as the last filtered message?
     */
    hr = lpsmh->lpsess->lpVtbl->CompareEntryIDs (lpsmh->lpsess,
                                        cbeid,
                                        lpeid,
                                        *lpcbeid,
                                        *lppeid,
                                        0,
                                        &ulMatch);
    if (HR_FAILED (hr) || !ulMatch)
    {
        /* Different folder, guess we better toss the cached one */

        (*lpsmh->lpfnFree) (*lppeid);
        *lppeid = NULL;
        *lpcbeid = 0;

        /* Cache the SentMail */

        hr = ResultFromScode ((*lpsmh->lpfnAlloc) (cbeid, lppeid));
        if (HR_FAILED (hr))
            goto ret;
        memcpy (*lppeid, lpeid, (UINT)cbeid);
        *lpcbeid = cbeid;
        *lpfUpdated = TRUE;
    }
    else if (*lppfldr)
        return hrSuccess;

    /* Open the new folder, but try the preferred store first */

    hr = lpmdbPref->lpVtbl->OpenEntry (lpmdbPref,
                                        cbeid,
                                        lpeid,
                                        NULL,
                                        MAPI_BEST_ACCESS,
                                        &ulType,
                                        (LPUNKNOWN FAR *)&lpmp);
    if (HR_FAILED (hr))
    {
        /* Try the MAPI session now and see if we can get the folder */
        
        hr = lpsmh->lpsess->lpVtbl->OpenEntry (lpsmh->lpsess,
                                        cbeid,
                                        lpeid,
                                        NULL,
                                        MAPI_BEST_ACCESS,
                                        &ulType,
                                        (LPUNKNOWN FAR *)&lpmp);
    }
    if (HR_FAILED (hr))
        goto ret;

    if (ulType != MAPI_FOLDER)
    {
        hr = ResultFromScode (MAPI_E_UNEXPECTED_TYPE);
        goto ret;
    }

ret:

    if (HR_FAILED (hr))
    {
        UlRelease (lpmp);
        (*lpsmh->lpfnFree) (*lppeid);
        *lppeid = NULL;
        *lpcbeid = 0;
        lpmp = NULL;
    }

    UlRelease (*lppfldr);
    *lppfldr = (LPMAPIFOLDER)lpmp;

    DebugTraceResult (HrCacheFolder(), hr);
    return hr;
}


/*
 *  HrCreateHashedFolder()
 *
 *  Purpose:
 *
 *      Create/Caches the a folder that satisfies the hash value
 *
 *  Arguments:
 *
 *      lpsmh       pointer to the sentmail handler
 *      lpdft       pointer the the hash interval
 *      lpfldrPar   parnet folder
 *      lpszName    name for folder
 *      lpszComment comment for folder
 *      lpcbeid     points to the cached entryid size
 *      lppeid      points to the cached entryid data
 *      lppfldr     points to the cached mapi folder object
 *
 *  Returns:
 *
 *      (HRESULT)
 *      lpcbeid     [OUT] size of newly cached entryid
 *      lppeid      [OUT] data of newly cached entryid
 *      lppfldr     [OUT] folder corresponding to cached entryid
 */
HRESULT
HrCreateHashedFolder (LPSMH lpsmh,
    LPDFT lpdft,
    LPMAPIFOLDER lpfldrPar,
    LPTSTR lpszName,
    LPTSTR lpszComment,
    ULONG FAR * lpcbeid,
    LPENTRYID FAR * lppeid,
    LPMAPIFOLDER FAR * lppfldr)
{
    HRESULT hr;
    LPMAPIFOLDER lpfldr = NULL;
    LPSPropValue lpval = NULL;
    SPropValue rgval[2] = {0};
    ULONG cval;

    /* Toss the current cache info */

    (*lpsmh->lpfnFree) (*lppeid);
    *lppeid = NULL;
    *lpcbeid = 0;

    /* Create the new folder */

    hr = lpfldrPar->lpVtbl->CreateFolder (lpfldrPar,
                            FOLDER_GENERIC,
                            lpszName,
                            lpszComment,
                            NULL,
                            OPEN_IF_EXISTS,
                            &lpfldr);
    if (HR_FAILED (hr))
        goto ret;

    /* Set the hashing interval properties */

    rgval[0].ulPropTag = PR_START_DATE;
    rgval[0].Value.ft = lpdft->ftStart;
    rgval[1].ulPropTag = PR_END_DATE;
    rgval[1].Value.ft = lpdft->ftEnd;
    hr = lpfldr->lpVtbl->SetProps (lpfldr, 2, rgval, NULL);
    if (HR_FAILED (hr))
        goto ret;

    /* Cache the folder info */

    hr = lpfldr->lpVtbl->GetProps (lpfldr,
                            (LPSPropTagArray)&sptFldrDates,
                            FALSE,
                            &cval,
                            &lpval);
    if (HR_FAILED (hr))
        goto ret;

    /* Make sure we have all the info we need */

    if ((lpval[0].ulPropTag != PR_START_DATE) ||
        (lpval[1].ulPropTag != PR_END_DATE) ||
        (lpval[2].ulPropTag != PR_ENTRYID))
    {
        hr = ResultFromScode (MAPI_E_BAD_VALUE);
        goto ret;
    }

    /* Cache the entryid */

    hr = ResultFromScode ((*lpsmh->lpfnAlloc) (lpval[2].Value.bin.cb, lppeid));
    if (HR_FAILED (hr))
        goto ret;
    memcpy (*lppeid, lpval[2].Value.bin.lpb, (UINT)lpval[2].Value.bin.cb);
    *lpcbeid = lpval[2].Value.bin.cb;

ret:

    (*lpsmh->lpfnFree) (lpval);
    if (HR_FAILED (hr))
    {
        UlRelease (lpfldr);
        lpfldr = NULL;
    }
    UlRelease (*lppfldr);
    *lppfldr = lpfldr;

    DebugTraceResult (HrCreateHashedFolder(), hr);
    return hr;
}


/*
 *  HrCacheHashedFolder()
 *
 *  Purpose:
 *
 *      Caches the folder that matches the hash value (file time)
 *
 *  Arguments:
 *
 *      lpsmh       pointer to the sentmail handler
 *      ft          hash filetime
 *      lpdft       pointer the the hash interval
 *      lpcbeid     points to the cached entryid size
 *      lppeid      points to the cached entryid data
 *      lppfldr     points to the cached mapi folder object
 *      lpfUpdated  points to cache update flag
 *
 *  Returns:
 *
 *      (HRESULT)
 *      lpcbeid     [OUT] size of newly cached entryid
 *      lppeid      [OUT] data of newly cached entryid
 *      lppfldr     [OUT] folder corresponding to cached entryid
 *      lpfUpdated  [OUT] TRUE iff the out folder is not the
 *                          previously cached folder
 */
HRESULT
HrCacheHashedFolder (LPSMH lpsmh,
    LPMDB lpmdbPref,
    FILETIME ft,
    LPDFT lpdft,
    LPMAPIFOLDER lpfldr,
    ULONG FAR * lpcbeid,
    LPENTRYID FAR * lppeid,
    LPMAPIFOLDER FAR * lppfldr,
    BOOL far * lpfUpdated)
{
    HRESULT hr;
    LPMAPIPROP lpmp = NULL;
    LPMAPITABLE lptbl = NULL;
    LPSRow lprw = NULL;
    LPSRowSet lprws = NULL;
    ULONG ulType;
    UINT i;

    /*  Check to see if the new hash fits the
     *  the current hashed folder, if the hash
     *  value does not work, find one that does
     */
    if (!*lpfUpdated &&
        (CompareFileTime (&lpdft->ftStart, &ft) != 1) &&
        (CompareFileTime (&lpdft->ftEnd, &ft) != -1))
    {
        /* The hash works, but do we have a folder? */

        if (*lppfldr)
            return hrSuccess;

        hr = lpsmh->lpsess->lpVtbl->OpenEntry (lpsmh->lpsess,
                                        *lpcbeid,
                                        *lppeid,
                                        NULL,
                                        MAPI_BEST_ACCESS,
                                        &ulType,
                                        (LPUNKNOWN FAR *)&lpmp);
        if (!HR_FAILED (hr) && (ulType != MAPI_FOLDER))
        {
            hr = ResultFromScode (MAPI_E_UNEXPECTED_TYPE);
            UlRelease (lpmp);
            lpmp = NULL;
        }
        goto ret;
    }

    /* Toss the cached info */

    (*lpsmh->lpfnFree) (*lppeid);
    *lppeid = NULL;
    *lpcbeid = 0;

    /* Get the hierachy and set it up to find the target folder */

    hr = lpfldr->lpVtbl->GetHierarchyTable (lpfldr, 0, &lptbl);
    if (HR_FAILED (hr))
        goto ret;

    hr = lptbl->lpVtbl->SetColumns (lptbl, (LPSPropTagArray)&sptFldrDates, 0);
    if (HR_FAILED (hr))
        goto ret;

    hr = lptbl->lpVtbl->QueryRows (lptbl, 12, 0L, &lprws);
    if (HR_FAILED (hr))
        goto ret;

    while (lprws->cRows)
    {
        for (i = 0; i < lprws->cRows; i++)
        {
            lprw = &lprws->aRow[i];

            if (!lpmp &&
                (lprw->lpProps[0].ulPropTag == PR_START_DATE) &&
                (lprw->lpProps[1].ulPropTag == PR_END_DATE) &&
                (CompareFileTime (&lprw->lpProps[0].Value.ft, &ft) != 1) &&
                (CompareFileTime (&lprw->lpProps[1].Value.ft, &ft) != -1))
            {
                /* Hey, this looks like the folder we want */

                hr = HrCacheFolder (lpsmh,
                        lpmdbPref,
                        lprw->lpProps[2].Value.bin.cb,
                        (LPENTRYID)lprw->lpProps[2].Value.bin.lpb,
                        lpcbeid,
                        lppeid,
                        (LPMAPIFOLDER FAR *)&lpmp,
                        lpfUpdated);
                if (!HR_FAILED (hr))
                {
                    lpdft->ftStart = lprw->lpProps[0].Value.ft;
                    lpdft->ftEnd = lprw->lpProps[1].Value.ft;
                }
            }
        }

        /* Clean up the row properies */

        for (i = 0; i < lprws->cRows; i++)
            (*lpsmh->lpfnFree) (lprws->aRow[i].lpProps);

        /* We either found the folder or we had an error */

        if (lpmp || HR_FAILED (hr))
            break;

        /* Clean up the row set */

        (*lpsmh->lpfnFree) (lprws);
        hr = lptbl->lpVtbl->QueryRows (lptbl, 12, 0L, &lprws);
        if (HR_FAILED (hr))
            goto ret;
    }

    /* Clean up the final row set */

    (*lpsmh->lpfnFree) (lprws);

ret:

    UlRelease (lptbl);
    UlRelease (*lppfldr);
    *lppfldr = (LPMAPIFOLDER)lpmp;

    DebugTraceResult (HrCacheHashedFolder(), hr);
    return hr ? hr : (lpmp ? hrSuccess : ResultFromScode (MAPI_E_NOT_FOUND));
}


/*
 *  HrArchiveByDate()
 *
 *  Purpose:
 *
 *      The purpose of this function is to "hash" a single message by
 *      processing based on date.  The most obvious bucket size is
 *      monthly but there is no reason not to make this an option the
 *      user could confiigure.
 *
 *  Arguments:
 *
 *      lpsmh           this filter hook obj
 *      lpft            the date to be filtered against
 *      lpfldrDef       the owning folder of the message
 *      lpmdbDef        the owning store of the message
 *      lpbkit          the cached bucket structure
 *      fCatByYear      uses yearly subfolders iff TRUE
 *      cbeid           cb for entryid of default target for message
 *      lpbeid          pb for entryid of default target for message
 *
 *  Operation:
 *
 *      Opens the suggested folder (if needed) and checks for the
 *      existence of the appropriate "bucket" folder.  If it does exist,
 *      then the  folder is created and cached.  The entryid is grabbed
 *      and passed back in to the spooler.
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrArchiveByDate (LPSMH lpsmh,
    FILETIME FAR * lpft,
    LPMAPIFOLDER lpfldrDef,
    LPMDB lpmdbDef,
    LPBKIT lpbkit,
    BOOL fCatByYear,
    ULONG cbeid,
    LPBYTE lpeid)
{
    HRESULT hr = hrSuccess;
    BOOL fUpdated = FALSE;
    LPMAPIFOLDER lpfldr;
    SYSTEMTIME st;
    SYSTEMTIME sty;
    TCHAR rgchName[64] = {0};
    
    if (!FileTimeToSystemTime (lpft, &st))
    {
        hr = ResultFromScode (MAPI_E_BAD_VALUE);
        goto ret;
    }

    /* Cache the parent folder */

    hr = HrCacheFolder (lpsmh,
                    lpmdbDef,
                    cbeid,
                    (LPENTRYID)lpeid,
                    &lpbkit->cbeidParent,
                    &lpbkit->lpeidParent,
                    &lpbkit->lpfldrParent,
                    &fUpdated);
    if (HR_FAILED (hr))
        goto ret;

    if (fCatByYear)
    {
        /* Cache the year folder */

        hr = HrCacheHashedFolder (lpsmh,
                    lpmdbDef,
                    *lpft,
                    &lpbkit->dftYr,
                    lpbkit->lpfldrParent,
                    &lpbkit->cbeidYr,
                    &lpbkit->lpeidYr,
                    &lpbkit->lpfldrYr,
                    &fUpdated);
        if (HR_FAILED (hr) && (GetScode (hr) == MAPI_E_NOT_FOUND))
        {
            wsprintf (rgchName, "%04hu", st.wYear);
            sty.wYear = st.wYear;
            sty.wMonth = 1;
            sty.wDayOfWeek = 0;
            sty.wDay = 1;
            sty.wHour = 0;
            sty.wMinute = 0;
            sty.wSecond = 0;
            sty.wMilliseconds = 0;
            if (!SystemTimeToFileTime (&sty, &lpbkit->dftYr.ftStart))
            {
                hr = ResultFromScode (MAPI_E_BAD_VALUE);
                goto ret;
            }
            sty.wMonth = 12;
            sty.wDay = rgwDaysPerMonth[sty.wMonth - 1];
            sty.wDayOfWeek = 0;
            sty.wDay = 31;
            sty.wHour = 23;
            sty.wMinute = 59;
            sty.wSecond = 59;
            sty.wMilliseconds = 999;
            if (!SystemTimeToFileTime (&sty, &lpbkit->dftYr.ftEnd))
            {
                hr = ResultFromScode (MAPI_E_BAD_VALUE);
                goto ret;
            }
            hr = HrCreateHashedFolder (lpsmh,
                            &lpbkit->dftYr,
                            lpbkit->lpfldrParent,
                            rgchName,
                            NULL,
                            &lpbkit->cbeidYr,
                            &lpbkit->lpeidYr,
                            &lpbkit->lpfldrYr);
            if (HR_FAILED (hr))
                goto ret;
        }
        else if (HR_FAILED (hr))
            goto ret;

        lpfldr = lpbkit->lpfldrYr;
    }
    else
        lpfldr = lpbkit->lpfldrParent;

    /* Cache the hashed target folder */

    hr = HrCacheHashedFolder (lpsmh,
                    lpmdbDef,
                    *lpft,
                    &lpbkit->dft,
                    lpfldr,
                    &lpbkit->cbeid,
                    &lpbkit->lpeid,
                    &lpbkit->lpfldr,
                    &fUpdated);
    if (HR_FAILED (hr) && (GetScode (hr) == MAPI_E_NOT_FOUND))
    {
        if (fCatByYear)
        {
            wsprintf (rgchName,
                "%02hu %s",
                st.wMonth,
                rgtstrMonthFull[st.wMonth - 1]);
        }
        else
        {
            wsprintf (rgchName,
                TEXT("'%02hu/%02hu %s"),
                st.wYear % 100,
                st.wMonth,
                rgtstrMonthFull[st.wMonth - 1]);
        }
        st.wDayOfWeek = (st.wDay - st.wDayOfWeek - 1) % 7;
        st.wDay = 1;
        st.wHour = 0;
        st.wMinute = 0;
        st.wSecond = 0;
        st.wMilliseconds = 0;
        if (!SystemTimeToFileTime (&st, &lpbkit->dft.ftStart))
        {
            hr = ResultFromScode (MAPI_E_BAD_VALUE);
            goto ret;
        }
        st.wDay = rgwDaysPerMonth[st.wMonth - 1];
        if ((st.wMonth == 2) && FIsLeapYear (st.wYear))
            st.wDay += 1;
        st.wDayOfWeek = (st.wDayOfWeek + st.wDay - 1) % 7;
        st.wHour = 23;
        st.wMinute = 59;
        st.wSecond = 59;
        st.wMilliseconds = 999;
        if (!SystemTimeToFileTime (&st, &lpbkit->dft.ftEnd))
        {
            hr = ResultFromScode (MAPI_E_BAD_VALUE);
            goto ret;
        }
        hr = HrCreateHashedFolder (lpsmh,
                            &lpbkit->dft,
                            lpfldr,
                            rgchName,
                            NULL,
                            &lpbkit->cbeid,
                            &lpbkit->lpeid,
                            &lpbkit->lpfldr);
    }

ret:

    DebugTraceResult (HrArchiveMessage(), hr);
    return hr;
}


/*
 *  HrArchiveMessage()
 *
 *  Purpose:
 *
 *      The purpose of this function is to "hash" a single message by
 *      processing based on date.  The most obvious bucket size is
 *      monthly but there is no reason not to make this an option the
 *      user could confiigure.
 *
 *  Arguments:
 *
 *      lpsmh           this filter hook obj
 *      lpmsg           the message to be filtered
 *      lpfldrDef       the owning folder of the message
 *      lpmdbDef        the owning store of the message
 *      lpbkit          the cached bucket structure
 *      fCatByYear      uses yearly subfolders iff TRUE
 *      lpcbeid         cb for entryid of default target for message
 *      lppbeid         pb for entryid of default target for message
 *
 *  Operation:
 *
 *      Extracts the date of the message that is to be used in the
 *      archiving, and calls off to HrArchiveByDate().
 *
 *      IMPORTANT: the entryid passed in will be swapped out by this
 *      call.  Therefore the *lppeid buffer must be allocated with the
 *      MAPIAllocateBuffer provider to the filter.
 *
 *  Returns:
 *
 *      (HRESULT)
 *      lpcbeid [out]   the size of the returned EntryID
 *      lppbeid [out]   the data of the returned EntryID
 */
HRESULT
HrArchiveMessage (LPSMH lpsmh,
    LPMESSAGE lpmsg,
    LPMAPIFOLDER lpfldrDef,
    LPMDB lpmdbDef,
    LPBKIT lpbkit,
    BOOL fCatByYear,
    ULONG FAR * lpcbeid,
    LPBYTE FAR * lppeid)
{
    HRESULT hr = hrSuccess;
    FILETIME ft;
    LPSPropValue lpval = NULL;
    ULONG cval;

    /* Quick and dirty parameter check */

    if (IsBadWritePtr (lpsmh, sizeof(SMH)) ||
        IsBadWritePtr (lpcbeid, sizeof(ULONG)) ||
        IsBadWritePtr (lppeid, sizeof(LPBYTE)) ||
        IsBadWritePtr (*lppeid, (UINT)(*lpcbeid)))
        return ResultFromScode (MAPI_E_INVALID_PARAMETER);

    /* Get the date used by the hash */

    hr = lpmsg->lpVtbl->GetProps (lpmsg,
                            (LPSPropTagArray)&sptMsgDates,
                            FALSE,
                            &cval,
                            &lpval);
    if (HR_FAILED (hr))
        goto ret;

    /* Make sure what we end up with is usable */

    if (lpval[0].ulPropTag == PR_MESSAGE_DELIVERY_TIME)
    {
        DebugTrace ("SMH: filtering on PR_MESSAGE_DELIVERY_TIME\n");
        ft = lpval[0].Value.ft;
    }
    else if (lpval[1].ulPropTag == PR_CLIENT_SUBMIT_TIME)
    {
        DebugTrace ("SMH: filtering on PR_CLIENT_SUBMIT_TIME\n");
        ft = lpval[1].Value.ft;
    }
    else
    {
        DebugTrace ("SMH: cannot filter on provided time props\n");
        hr = ResultFromScode (MAPI_E_BAD_VALUE);
        goto ret;
    }

    hr = HrArchiveByDate (lpsmh,
                    &ft,
                    lpfldrDef,
                    lpmdbDef,
                    lpbkit,
                    fCatByYear,
                    *lpcbeid,
                    *lppeid);

ret:
    
    if (!HR_FAILED (hr))
    {
        LPBYTE lpeid;

        /* OK, If we get this far we are moving the message */

        hr = ResultFromScode ((*lpsmh->lpfnAlloc) (lpbkit->cbeid, &lpeid));
        if (HR_FAILED (hr))
            goto ret;
        memcpy (lpeid, lpbkit->lpeid, (UINT)lpbkit->cbeid);
        (*lpsmh->lpfnFree) (*lppeid);
        *lpcbeid = lpbkit->cbeid;
        *lppeid = lpeid;
    }
    (*lpsmh->lpfnFree) (lpval);
    
    DebugTraceResult (HrArchiveMessage(), hr);
    return hr;
}
