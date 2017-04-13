/*
 *  S M H M D B . C
 *
 *  Sample mail handling hook
 *  Store Tables
 *
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"


/*
 *  sptStoTbl
 *
 *  The store table column set and enum
 */
enum { ipNull, ipEid, ipDispNm, ipRsrcFlags, cpStoTblMax };
static const SizedSPropTagArray (cpStoTblMax, sptStoTbl) =
{
    cpStoTblMax,
    {
        PR_NULL,
        PR_ENTRYID,
        PR_DISPLAY_NAME_A,
        PR_RESOURCE_FLAGS
    }
};


/*
 *  HrInitStoresTable()
 *
 *  Purpose:
 *
 *      Inits the stores table stucture and adds a reference to the SMH
 *      parent object.  This is done by getting the message stores table
 *      from the MAPI session and querying all rows (up to cStoMax) and
 *      mapping the return to an LPSTOTABLE structure.
 *
 *  Arguments:
 *
 *      lpsmh           the SMH parent object
 *      lpsess          the MAPI session that this SMH instance belongs to
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrInitStoresTable (LPSMH lpsmh, LPMAPISESSION lpsess)
{
    HRESULT hr;
    LPMAPITABLE lptbl;
    LPSRowSet lprws = NULL;
    LPSTOTABLE lpstotbl;
    UINT i;

    Assert (lpsmh->lpstotbl == NULL);
    hr = lpsess->lpVtbl->GetMsgStoresTable (lpsess, 0, &lptbl);
    if (!HR_FAILED (hr))
    {
        hr = lptbl->lpVtbl->SetColumns (lptbl, (LPSPropTagArray)&sptStoTbl, 0);
        if (!HR_FAILED (hr))
        {
            hr = lptbl->lpVtbl->QueryRows (lptbl, cStoMax, 0, &lprws);
            if (!HR_FAILED (hr))
            {
                /*  Zero fill the initial property in all rows.
                 *  This has the nice side effect of NULL'ing the
                 *  lpmdb member of the structure
                 */
                lpstotbl = (LPSTOTABLE)lprws;
                for (i = 0; i < lpstotbl->cSto; i++)
                    memset (&lpstotbl->aSto[i].lpstoe->valPad,
                        0, sizeof(SPropValue));

                lpsmh->lpstotbl = lpstotbl;
            }
        }
        UlRelease (lptbl);
    }

    DebugTraceResult (HrInitStoresTable(), hr);
    return hr;
}


/*
 *  ReleaseStoresTable()
 *
 *  Purpose:
 *
 *      Releases all resources owned by the store table and disconnects
 *      the SMH parent from the table.
 *
 *  Arguments:
 *
 *      lpsmh       the SMH parent object
 */
VOID
ReleaseStoresTable (LPSMH lpsmh)
{
    LPSTOTABLE lpstotbl = lpsmh->lpstotbl;
    UINT i;

    if (lpstotbl)
    {
        for (i = 0; i < lpstotbl->cSto; i++)
        {
            UlRelease (lpstotbl->aSto[i].lpstoe->lpmdb);
            (*lpsmh->lpfnFree) (lpstotbl->aSto[i].lpProps);
        }
        (*lpsmh->lpfnFree) (lpstotbl);
        lpsmh->lpstotbl = NULL;
    }
    return;
}


/*
 *  HrOpenStoEntry()
 *
 *  Purpose:
 *
 *      Opens the store associated with a stoenty in the stores table.
 *
 *      IMPORTANT: the caller does not end up owning the store reference
 *      and should NOT call Release() on the store unless they also call
 *      AddRef().  The referece is owned by the stores table and is
 *      released upon the tables destruction.
 *
 *  Arguments:
 *
 *      lpsess          the MAPI session object
 *      lpsto           the STO structure for the MDB to open
 *      lppmdb  [OUT]   contains the LPMDB iff the call succeeds
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrOpenStoEntry (LPMAPISESSION lpsess, LPSTO lpsto, LPMDB FAR * lppmdb)
{
    HRESULT hr = hrSuccess;
    LPMDB lpmdb = NULL;

    if (!lpsto->lpstoe->lpmdb)
    {
        hr = lpsess->lpVtbl->OpenMsgStore (lpsess,
                                0,
                                lpsto->lpProps[ipEid].Value.bin.cb,
                                (LPENTRYID)lpsto->lpProps[ipEid].Value.bin.lpb,
                                NULL,
                                MDB_WRITE | MDB_NO_DIALOG | MDB_NO_MAIL,
                                &lpmdb);
        if (!HR_FAILED (hr))
            lpsto->lpstoe->lpmdb = lpmdb;
        
        *lppmdb = lpmdb;
    }
    else
    {
        *lppmdb = lpsto->lpstoe->lpmdb;
    }

    DebugTraceResult (HrOpenStoEntry(), hr);
    return hr;
}


/*
 *  HrOpenMdbFromEid()
 *
 *  Purpose:
 *
 *      Opens a message store by entryid.  The entryid is looked up in
 *      the stores table to find the proper STOENTRY.  If no entry is
 *      found, then the store is not opened.  If one is found, then the
 *      MDB is retrieved from the STOENTRY.  If it has not yet been opened,
 *      the MDB is opened at this time and stored (no pun intended).
 *
 *      IMPORTANT: the caller does not end up owning the store reference
 *      and should NOT call Release() on the store unless they also call
 *      AddRef().  The referece is owned by the stores table and is
 *      released upon the tables destruction.
 *
 *  Arguments:
 *
 *      lpsmh           the SMH parent object
 *      cbeid           size of the stores entryid
 *      lpeid           the entryid to be opened
 *      lppmdb  [OUT]   contains the LPMDB iff the call succeeds
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrOpenMdbFromEid (LPSMH lpsmh, ULONG cbeid, LPENTRYID lpeid, LPMDB FAR * lppmdb)
{
    HRESULT hr = ResultFromScode (MAPI_E_NOT_FOUND);
    LPSTOTABLE lpstotbl = lpsmh->lpstotbl;
    UINT i;

    if (lpstotbl)
    {
        for (i = 0; i < lpstotbl->cSto; i++)
        {
            if ((cbeid == lpstotbl->aSto[i].lpProps[ipEid].Value.bin.cb) &&
                !memcmp (lpeid, lpstotbl->aSto[i].lpProps[ipEid].Value.bin.lpb, (UINT)cbeid))
            {
                if (lpstotbl->aSto[i].lpstoe->lpmdb)
                {
                    *lppmdb = lpstotbl->aSto[i].lpstoe->lpmdb;
                    hr = hrSuccess;
                }
                else
                    hr = HrOpenStoEntry (lpsmh->lpsess, &lpstotbl->aSto[i], lppmdb);

                break;
            }
        }
    }

    if (HR_FAILED (hr))
        *lppmdb = NULL;

    DebugTraceResult (HrOpenMdbFromEid(), hr);
    return hr;
}


/*
 *  HrOpenMdbFromName()
 *
 *  Purpose:
 *
 *      Opens a message store by PR_DISPLAY_NAME value.  The name is
 *      looked up in the stores table to find the proper STOENTRY.  If no
 *      entry is found, then the store is not opened.  If one is found,
 *      then the MDB is retrieved from the STOENTRY.  If it has not yet
 *      been opened, the MDB is opened at this time and stored (no pun
 *      intended).
 *
 *      IMPORTANT: the caller does not end up owning the store reference
 *      and should NOT call Release() on the store unless they also call
 *      AddRef().  The referece is owned by the stores table and is
 *      released upon the tables destruction.
 *
 *  Arguments:
 *
 *      lpsmh           the SMH parent object
 *      lpszName        the name of the store to open
 *      lppmdb  [OUT]   contains the LPMDB iff the call succeeds
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrOpenMdbFromName (LPSMH lpsmh, LPTSTR lpszName, LPMDB FAR * lppmdb)
{
    HRESULT hr = ResultFromScode (MAPI_E_NOT_FOUND);
    LPSTOTABLE lpstotbl = lpsmh->lpstotbl;
    UINT i;

    if (lpstotbl)
    {
        for (i = 0; i < lpstotbl->cSto; i++)
        {
            if (!lstrcmpi (lpszName, lpstotbl->aSto[i].lpProps[ipDispNm].Value.LPSZ))
            {
                if (lpstotbl->aSto[i].lpstoe->lpmdb)
                {
                    *lppmdb = lpstotbl->aSto[i].lpstoe->lpmdb;
                    hr = hrSuccess;
                }
                else
                    hr = HrOpenStoEntry (lpsmh->lpsess, &lpstotbl->aSto[i], lppmdb);

                break;
            }
        }
    }

    if (HR_FAILED (hr))
        *lppmdb = NULL;

    DebugTraceResult (HrOpenMdbFromEid(), hr);
    return hr;
}
