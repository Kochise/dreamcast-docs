/*
 *  S M H A T P . C
 *
 *  Automatic Additions To Personal Address Books
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"
#include <mspab.h>

static const MAPIUID muidPAB = PAB_PROVIDER_ID;
static const SizedSPropTagArray (2, sptEid) = { 1, { PR_ENTRYID, PR_RECIPIENT_TYPE }};

HRESULT
HrAddEntriesToPab (LPSMH lpsmh, LPMESSAGE lpmsg)
{
    HRESULT hr;
    ENTRYLIST el = {0};
    LPABCONT lpPab = NULL;
    LPADRBOOK lpab = NULL;
    LPENTRYID lpeid;
    LPMAPITABLE lptbl = NULL;
    LPSPropValue lpval = NULL;
    LPSRowSet lprws = NULL;
    UINT ie;
    ULONG cbeid;
    ULONG ce = 0;
    ULONG cRows = 0;
    ULONG ulT;

    /*  If this message is a report, we do not
     *  want to add the recipient to the pab
     */
    hr = HrGetOneProp ((LPMAPIPROP)lpmsg, PR_MESSAGE_CLASS, &lpval);
    if (!HR_FAILED (hr) && FLpszContainsLpsz (lpval->Value.LPSZ, "Report"))
        goto ret;
        
    /*  Check to see if the installed PAB is the
     *  one supplied by MAPI
     */
    hr = lpsmh->lpsess->lpVtbl->OpenAddressBook (lpsmh->lpsess,
                                            0,
                                            NULL,
                                            0,
                                            &lpab);
    if (HR_FAILED(hr))
        goto ret;

    hr = lpab->lpVtbl->GetPAB (lpab, &cbeid, &lpeid);
    if (HR_FAILED (hr) || (0 == cbeid))
        goto ret;
    
    /*  If this is not the MAPI pab, then we better
     *  not play with it
     */
    if (memcmp (lpeid->ab, &muidPAB, sizeof(MAPIUID)))
        goto ret;

    hr = lpab->lpVtbl->OpenEntry (lpab,
                            cbeid,
                            lpeid,
                            NULL,
                            0,
                            &ulT,
                            (LPUNKNOWN *) &lpPab);
    (*lpsmh->lpfnFree) (lpeid);
    UlRelease (lpab);
    lpeid = NULL;
    lpab = NULL;
    if (HR_FAILED (hr))
        goto ret;

    /*  Get the recipient table from the message */

    hr = lpmsg->lpVtbl->GetRecipientTable (lpmsg, 0, &lptbl);
    if (HR_FAILED (hr))
        goto ret;

    /*  Only get the entryIDs */

    hr = HrQueryAllRows (lptbl,
                    (LPSPropTagArray) &sptEid,
                    NULL,
                    NULL,
                    0,    /* all rows */
                    &lprws);
    UlRelease (lptbl);
    lptbl = NULL;
    if (HR_FAILED (hr))
        goto ret;

    /*  Loop through all the recipients and remove those that
     *  do not belong to the MAPI PAB
     */
    cRows = lprws->cRows;
    if (FAILED ((*lpsmh->lpfnAlloc) (cRows*sizeof(SBinary), &el.lpbin)))
        goto ret;
    
    for (ce = 0, ie = 0; ie < cRows; ie++)
    {
        LPSPropValue pval = lprws->aRow[ie].lpProps;
        Assert (pval);
        Assert (pval->ulPropTag == PR_ENTRYID);
        cbeid = pval->Value.bin.cb;
        lpeid = (LPENTRYID)pval->Value.bin.lpb;
        Assert (cbeid);
        Assert (lpeid);

        /*  If this is not a P1 and not from the MAPI PAB... */

        if (!(pval[1].Value.l & MAPI_P1) &&
            memcmp (lpeid->ab, &muidPAB, sizeof(MAPIUID)))
        {
            /*  ... set it into the entry list */

            el.lpbin[ce].cb = cbeid;
            el.lpbin[ce].lpb = (LPBYTE)lpeid;
            ce++;
        }
    }

    /*  Now, copy everything over into the PAB */

    el.cValues = ce;
    lpeid = NULL;
    cbeid = 0;
    
    (void) lpPab->lpVtbl->CopyEntries (lpPab,
                                &el,
                                0,
                                NULL,
                                CREATE_CHECK_DUP_STRICT);

ret:

    if (lprws)
    {
        for (ie = 0; ie < cRows; ie++)
            (*lpsmh->lpfnFree) (lprws->aRow[ie].lpProps);
        (*lpsmh->lpfnFree) (lprws);
    }
    (*lpsmh->lpfnFree) (el.lpbin);
    (*lpsmh->lpfnFree) (lpval);
    UlRelease (lpPab);
    UlRelease (lpab);
    
    DebugTraceResult (HrAddEntryiesToPab(), hr);
    return hr;
}
