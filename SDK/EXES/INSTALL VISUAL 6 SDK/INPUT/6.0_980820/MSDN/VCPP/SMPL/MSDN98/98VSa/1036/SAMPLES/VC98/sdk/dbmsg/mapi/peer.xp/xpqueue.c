/*
 -  X P Q U E U E . C
 -
 *  Purpose:
 *      Code to support the background queueing mechanism for the Sample
 *      Transport Provider.
 *      This module contains the following SPI entry points:
 *
 *          Idle()
 *
 *      Additional support functions found here:
 *
 *          HrBuildAdrList()
 *          HrSendOneMessage()
 *          HrIMsgToTextMsg()
 *          HrPrepareRecipientTable()
 *          HrCrackSenderEID()
 *          FPropIndex()
 *          FormatFileTime()
 *          FreeMyAdrList()
 *          ScLoadTnef()
 *
 *      Also present in this module is the transmit list management code and
 *      all the recipient list manipulation logic.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "xppch.h"
#include <tnef.h>
#include "xpsof.h"
#include "xptxtmsg.h"
#include "xpresrc.h"

BOOL FIsTextizedProp(ULONG ulPropTag);

/* Generic BAD_VALUE for use in comparisons below */

#define BAD_VALUE (0xFFFFFFFF)


/*
 -  lpxpl->lpVtbl->Idle
 -
 *  Purpose:
 *      Called by the Spooler periodically in its idle loop.
 *
 *      The Transport will determine if there's any incoming mail for the
 *      Spooler and will TransportNotify (NOTIFY_NEWMAIL) if so.
 *
 *  Parameters:
 *      ulFlags             Flags. None are currently defined.
 *
 *  Returns:
 *      (HRESULT)           Errors encountered if any.
 *
 *  Operation:
 *      If inbound operation is currently enabled, call the Poll() entry point
 *      to see if there's anything there. If we find something with Poll(), then
 *      SpoolerNotify(NOTIFY_NEWMAIL).
 */

STDMETHODIMP
XPL_Idle(LPXPL lpxpl, ULONG ulFlags)
{
    HRESULT hResult = 0;
    LPDEFMSG lpDefMsg;

    /* Incoming messages? */

    if (lpxpl->ulTransportStatus & STATUS_INBOUND_ENABLED)
    {
        ULONG ulT = 0;

        if ((hResult = XPL_Poll(lpxpl, &ulT)) != 0)
            goto ret;
        if (ulT != 0)
        {
            /* SpoolerNotify() could theoretically return a nonzero
            HRESULT, but it's much easier and unambiguous to ignore
            that possibility and field Spooler errors elsewhere. */

            (void)lpxpl->lpMAPISup->lpVtbl->SpoolerNotify(lpxpl->lpMAPISup, NOTIFY_NEWMAIL, NULL);
        }
    }

    if (lpxpl->fResendDeferred)
    {
        while (lpxpl->lpDeferredList)
        {
            lpDefMsg = lpxpl->lpDeferredList;
            lpxpl->lpDeferredList = lpDefMsg->lpNext;

            lpxpl->lpMAPISup->lpVtbl->SpoolerNotify(lpxpl->lpMAPISup,
                NOTIFY_SENTDEFERRED, &(lpDefMsg->sbinEIDDef));

            lpxpl->FreeBuffer(lpDefMsg);
        }

        lpxpl->fResendDeferred = FALSE;
    }

ret:

    DebugTraceResult(XPL_Idle, hResult);
    return hResult;
}

/*
 -  HrBuildAdrList
 -
 *  Called by outbound and inbound logic.
 *
 *  Traverses a restricted recipient table and collates the rows into
 *  a "done" adrlist structure and a "not done" adrlist structure. The
 *  only distinction between done and not done is the result of a call
 *  to an optional function to attempt to send the open message to
 *  a particular recipient.
 *
 *  Obviously, if the callback isn't specified, the "done" adrlist will
 *  contain all recipients that matched the restriction.
 *
 *  Parameters:
 *      lpxpl               Session in which we're executing
 *      lpMessage           Message containing the recipient table
 *      lpTable             Recipient table
 *      fSetResponsibility  TRUE/FALSE = Set/Clear PR_RESPONSIBILITY
 *                          in good list (clear bad list always)
 *      lpfnCallBack        Routine to call when trying to send
 *      lppMyAdrListGood    Where to store the list of done recips
 *      lppMyAdrListBad     Where to store the list of not done
 *
 *  Returns:
 *      (HRESULT)           Errors encountered if any.
 *
 *
 *  Operation:
 *      This routine builds a pair of MYADRLISTS from the (restricted)
 *      table which is passed to it.
 *
 *      Do a SetColumns so we know where to find PR_EMAIL_ADDRESS, PR_ROWID
 *      and other necessary columns. Included in the SetColumns is
 *      PR_REPORT_TEXT as a placeholder for NDR information.
 *
 *      Then, until we run out of data,
 *
 *      1) QueryRows on the input table
 *      2) For each row:
 *          a) If lpfnCallBack and PR_EMAIL_ADDRESS, invoke callback.
 *          b) If callback wasn't defined or if successful, add row to
 *             "good" list, else add to "bad" list with NDR reason
 *      3) Free RowSet
 *
 *      The caller can tell if any recipients remain by whether the
 *      "not done" set contains any elements.
 *
 *      The "not done" set will set PR_RESPONSIBILITY to FALSE if the caller
 *      wants "done" recipients set,
 */

HRESULT
HrBuildAdrList(LPXPL lpxpl,
    LPSPropValue lpPropArray,
    LPMESSAGE lpMessage,
    LPMAPITABLE lpTable,
    BOOL fSetResponsibility,
    LPMYCALLBACK lpfnCallBack,
    LPMYADRLIST FAR * lppMyAdrListGood,
    LPMYADRLIST FAR * lppMyAdrListBad)
{
    HRESULT hResult = hrSuccess;
    SCODE sc = S_OK;
    LPVOID lpvT;
    TCHAR rgchBuffer[512];
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;

    LPSRowSet lpRow = NULL;
    LPMYADRLIST lpDone = NULL;
    LPMYADRLIST lpNotDone = NULL;
    LPSPropTagArray lpsptT = NULL;

    LPMYADRLIST FAR *lppMyAdrList;
    LPSPropTagArray lpsptNew;
    LPSPropValue lpspvT;

    ULONG ulT;
    ULONG ulNew;
    ULONG ulRow;

    /*  These are the columns I need to have in the recipient table,
        even if all I get is a placeholder. If you need to add any,
        bump the definition of NUM_REQUIRED_COLS, add new defines
        for the new columns, and add the new column proptags to the
        switch below. If the property isn't necessarily going to be
        in the table, use the PR_NULL trick you see below for the
        PR_REPORT_TEXT property. */

    enum enumColumns
    {
        COLUMN_PR_ROWID,
        COLUMN_PR_EMAIL_ADDRESS,
        COLUMN_PR_RESPONSIBILITY,
        COLUMN_PR_REPORT_TEXT,
        COLUMN_PR_RECIPIENT_TYPE,
        NUM_REQUIRED_COLS
    };

    Assert(lppMyAdrListGood);
    Assert(lppMyAdrListBad);

    /*
        Arrange the columns so that we'll have the recipient properties
        we really want.

        So as not to lose any recipient properties, we need to do it in
        this fashion:

        1)  QueryColumns() on the input table
        2)  Build a new column set based on the properties we care
            about plus all other properties of the input table
        3)  SetColumns() on the input table

        The properties we care about are the following:

        1)  PR_ROWID
        2)  PR_EMAIL_ADDRESS
        3)  PR_RESPONSIBILITY */

    /*  Get the complete column set */

    hResult = lpTable->lpVtbl->QueryColumns(lpTable, TBL_ALL_COLUMNS, &lpsptT);

    if (hResult)
    {
        DebugTrace("QueryColumns failed.\n");
        goto ret;
    }

    /*  Gotta have a PR_ROWID. That guarantees at least one column! */

    Assert(lpsptT->cValues >= 1);

    /*  Allocate a new column set, linked to the old one for cleanup */

    ulT = CbNewSPropTagArray(NUM_REQUIRED_COLS + lpsptT->cValues);
    sc = (*lpxpl->AllocateMore) (ulT, (LPVOID) lpsptT, (LPVOID) &lpsptNew);

    if (sc)
    {
        hResult = ResultFromScode(sc);
        DebugTrace("New column set allocation failed.\n");
        goto ret;
    }

    /*  Fill in the new column set, required fields first in our order. */

    lpsptNew->aulPropTag[COLUMN_PR_ROWID] = PR_ROWID;
    lpsptNew->aulPropTag[COLUMN_PR_EMAIL_ADDRESS] = PR_EMAIL_ADDRESS;
    lpsptNew->aulPropTag[COLUMN_PR_RESPONSIBILITY] = PR_RESPONSIBILITY;
    lpsptNew->aulPropTag[COLUMN_PR_REPORT_TEXT] = PR_NULL;
    lpsptNew->aulPropTag[COLUMN_PR_RECIPIENT_TYPE] = PR_RECIPIENT_TYPE;
    ulNew = NUM_REQUIRED_COLS;

    for (ulT = 0; ulT < lpsptT->cValues; ulT++)
    {
        switch (lpsptT->aulPropTag[ulT])
        {
        case PR_REPORT_TEXT:
            lpsptNew->aulPropTag[COLUMN_PR_REPORT_TEXT] = PR_REPORT_TEXT;
            break;

        case PR_ROWID:
        case PR_EMAIL_ADDRESS:
        case PR_RESPONSIBILITY:
        case PR_RECIPIENT_TYPE:
            break;

        default:
            lpsptNew->aulPropTag[ulNew++] = lpsptT->aulPropTag[ulT];
            break;
        }
    }

    lpsptNew->cValues = ulNew;

    /*  Set the new columns */

    hResult = lpTable->lpVtbl->SetColumns(lpTable, lpsptNew, 0L);

    if (hResult)
    {
        DebugTrace("SetColumns failed.\n");
        goto ret;
    }

    /*  Free both old and new PropTagArrays. */

    (*lpxpl->FreeBuffer) ((LPVOID) lpsptT);
    lpsptT = NULL;

    /*  Build two big ADRLISTs from this table. Do minimal allocations so
        that all the reallocation code will be properly exercised. We can
        optimize later when we've tested.

        The obvious underlying assumption of this code is that it's
        possible to get the entire recipient list into memory at once. */

#ifdef DEBUG
#define GROW_SIZE   1       /* How much we'll add on every reallocation. */
#define QUERY_SIZE  1       /* How much we'll try for on query rows */
#else
#define GROW_SIZE   20
#define QUERY_SIZE  20
#endif

    for (;;)
    {
        /*  Get some rows from the recipient table. */

        hResult = lpTable->lpVtbl->QueryRows(lpTable, QUERY_SIZE, 0L, &lpRow);

        if (hResult)
        {
            DebugTrace("QueryRows failed.\n");
            goto ret;
        }

        /*  Are we finished getting rows? */

        if (!lpRow || !(lpRow->cRows))
        {
            /*  Free the row if any */

            (*lpxpl->FreeBuffer) ((LPVOID) lpRow);
            lpRow = NULL;

            /*  We're finished now, break out of the (for (;;)) loop. */

            break;
        }

        /*  Work our way through the RowSet */

        for (ulRow = 0; ulRow < lpRow->cRows; ulRow++)
        {
            BOOL fDone = TRUE;

            Assert(lpRow->aRow[ulRow].cValues);
            Assert(lpRow->aRow[ulRow].lpProps);

            lpspvT = lpRow->aRow[ulRow].lpProps;

            /* Check our .2 second timer before processing each row. */

            sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));

            if (sc == MAPI_W_CANCEL_MESSAGE)
            {
                DebugTrace("Cancelling message delivery.\n");
                goto ret;
            }

            /*  See if we need to do the callback. If so, make the call now */

            if (lpfnCallBack)
            {
                Assert(lpspvT[COLUMN_PR_EMAIL_ADDRESS].ulPropTag == PR_EMAIL_ADDRESS);
                Assert(lpspvT[COLUMN_PR_RECIPIENT_TYPE].ulPropTag == PR_RECIPIENT_TYPE);

                hResult = lpfnCallBack(lpxpl,
                    lpPropArray,
                    lpMessage,
                    lpspvT[COLUMN_PR_RECIPIENT_TYPE].Value.ul,
                    lpspvT[COLUMN_PR_EMAIL_ADDRESS].Value.LPSZ,
                    &fDone);

                if (hResult)
                {
                    DebugTrace("IGNORE: Callback function  failed.\n");
                    hResult = hrSuccess;
                }
            }

            /*  Set the PR_RESPONSIBILITY flag to its indicated new state. */

            Assert(lpRow->aRow[ulRow].cValues > COLUMN_PR_RESPONSIBILITY);

            /*  Make the appropriate change to PR_RESPONSIBILITY. If we're
                setting it, just do it into whatever column we've set;
                is pointing at, Prop Tag and Value. If we're clearing it,
                we only need to do anything if there was a discrete column,
                and all that's needed is to set the Prop Tag to PR_NULL. */

            if (fSetResponsibility)
            {
                lpspvT[COLUMN_PR_RESPONSIBILITY].ulPropTag = PR_RESPONSIBILITY;
                lpspvT[COLUMN_PR_RESPONSIBILITY].Value.b = fDone;
            }
            else
            {
                /*  We want to clear the flag */
                lpspvT[COLUMN_PR_RESPONSIBILITY].ulPropTag = PR_NULL;
            }

            /*  PR_NULL the PR_ROWID column if this will be a "bad" recipient, also
                adding NDR information to the row (in a column we set earlier) */

            if (!fDone)
            {
                TCHAR szReportText[512];

                lpspvT[COLUMN_PR_ROWID].ulPropTag = PR_NULL;

                /*  The Spooler will default to a NDR report and will fill in all
                    required properties in the StatusRecips call. The only thing
                    we need to do is to fill in a specific per-recipient text
                    description of the problem (it defaults too but it's good
                    to have real info from the horse's mouth) */

                LoadString(lpxpl->lpxppParent->hInst, IDS_REPORT_TEXT_MSG,
                    szReportText, sizeof(szReportText));

                wsprintf(rgchBuffer, "%s%s", szReportText,
                    lpspvT[COLUMN_PR_EMAIL_ADDRESS].Value.LPSZ);

                ulT = Cbtszsize(rgchBuffer);
                sc = lpxpl->AllocateMore(ulT, lpspvT, &lpvT);

                if (sc)
                {
                    hResult = ResultFromScode(sc);
                    DebugTrace("NDR text allocation failed.\n");
                    goto ret;
                }

                /*  Memory allocated, copy the formatted string and hook it into
                    the pre-allocated column. */

                lstrcpy((LPTSTR) lpvT, rgchBuffer);
                lpspvT[COLUMN_PR_REPORT_TEXT].ulPropTag = PR_REPORT_TEXT;
                lpspvT[COLUMN_PR_REPORT_TEXT].Value.LPSZ = (LPTSTR) lpvT;
            }

            /*  Now point ourselves at one of the two LPMYADRLIST pointers */

            lppMyAdrList = (fDone ? &lpDone : &lpNotDone);

            /*  If we didn't already have a LPMYADRLIST, allocate one now. */

            if (*lppMyAdrList == NULL)
            {
                /*  Allocate an initial MYADRLIST structure. Then allocate
                    enough memory for (GROW_SIZE) ADRENTRYs and store
                    it into the structure. Initialize the members. */

                sc = (*lpxpl->AllocateBuffer) (sizeof(MYADRLIST), &lpvT);

                if (sc)
                {
                    hResult = ResultFromScode(sc);
                    DebugTrace("Initial MYADRLIST allocation failed.\n");
                    goto ret;
                }

                /*  Hook up the MYADRLIST with no entries. */

                *lppMyAdrList = (LPMYADRLIST) lpvT;
                (*lppMyAdrList)->cMaxEntries = 0;
                (*lppMyAdrList)->lpAdrList = NULL;

                /* Now allocate a ADRLIST with GROW_SIZE entries in it. */

                sc = (*lpxpl->AllocateBuffer) (CbNewADRLIST(GROW_SIZE), &lpvT);

                if (sc)
                {
                    hResult = ResultFromScode(sc);
                    DebugTrace("Initial ADRLIST allocation failed.\n");
                    goto ret;
                }

                /*  Now hook up this ADRLIST into the MYADRLIST. */

                (*lppMyAdrList)->lpAdrList = (LPADRLIST) lpvT;
                (*lppMyAdrList)->cMaxEntries = GROW_SIZE;
                (*lppMyAdrList)->lpAdrList->cEntries = 0;
            }

            /*  Make sure that the selected MYADRLIST has room for another row */

            ulT = (*lppMyAdrList)->lpAdrList->cEntries + 1;
            Assert(ulT <= (*lppMyAdrList)->cMaxEntries + 1);

            if (ulT > (*lppMyAdrList)->cMaxEntries)
            {
                LPADRLIST lpAdrListT;

                /*  Not enough space, we need to create a new ADRLIST. */

                ulT = CbNewADRLIST((*lppMyAdrList)->cMaxEntries + GROW_SIZE);
                sc = (*lpxpl->AllocateBuffer) (ulT, &lpvT);

                if (sc)
                {
                    hResult = ResultFromScode(sc);
                    DebugTrace("Reallocation of ADRLIST failed.\n");
                    goto ret;
                }

                /*  Got it, now copy the data from the old one */

                lpAdrListT = (LPADRLIST) lpvT;
                ulT = CbNewADRLIST((*lppMyAdrList)->cMaxEntries);

                if (ulT)
                    memcpy(lpAdrListT, (*lppMyAdrList)->lpAdrList, (UINT) ulT);

                (*lppMyAdrList)->cMaxEntries += GROW_SIZE;

                /*  Exchange the pointers */

                lpvT = (LPVOID) (*lppMyAdrList)->lpAdrList;
                (*lppMyAdrList)->lpAdrList = lpAdrListT;

                /*  Free the old memory */

                lpxpl->FreeBuffer(lpvT);
            }

            /*  We have room now so store the new ADRENTRY. As part of the
                storage, we're going to copy the SRow pointer from the SRowSet
                into the ADRENTRY. Once we've done this, we won't need the
                SRowSet any more ... and the SRow will be deallocated when
                we unwind the ADRLIST. */

            /*  Calculate location in ADRLIST for the new entry. */

            ulT = (*lppMyAdrList)->lpAdrList->cEntries++;

            /*  Copy the data from the SRowSet. */

            (*lppMyAdrList)->lpAdrList->aEntries[ulT].cValues = lpRow->aRow[ulRow].cValues;
            (*lppMyAdrList)->lpAdrList->aEntries[ulT].rgPropVals = lpRow->aRow[ulRow].lpProps;

            /*  Now that we are finished with this row (eg it is in the
                adrlist) we want to disassociate it from the rowset. */

            lpRow->aRow[ulRow].lpProps = NULL;
        }

        /*  We're finished with the SRowSet (since it is allocated
            separately from the SRow). Deallocate it. */

        lpxpl->FreeBuffer((LPVOID) lpRow);
        lpRow = NULL;

    }                           /* End of big ADRLIST builder loop */

    /*  Fall into exit with hResult set if something failed. */

ret:

    /*  Clean up RowSet if any is left */

    FreeProws(lpRow);

    /*  Clean up column stuff if any's left */

    lpxpl->FreeBuffer((LPVOID) lpsptT);

    /*  If sc is set, feed it into hResult. Afterwards, hResult is the
        determinant of whether there was an error or not. */

    if (hResult)
    {
        /*  This memory should only be hanging around in the error case. */

        FreeMyAdrList(lpxpl, lpDone);
        FreeMyAdrList(lpxpl, lpNotDone);

        *lppMyAdrListGood = NULL;
        *lppMyAdrListBad = NULL;
    }
    else
    {
        /*  Success, pass the adrlists we built back to the caller */

        *lppMyAdrListGood = lpDone;
        *lppMyAdrListBad = lpNotDone;
    }

    DebugTraceResult(HrBuildAdrList, hResult);
    return hResult;
}


/*
 -  HrSendOneMessage
 -
 *  Purpose:
 *      Called by HrBuildAdrList() to send a message to a recipient
 *      that matched all of the caller's restrictions. Also called by
 *      XPL_SubmitMessage() if transport is not peer-to-peer, in which
 *      case the "Email address" is just our outbound directory.
 *
 *  Parameters:
 *      lpxpl               The Transports logon object for this session
 *      lpPropArray         Logon properties that have been copied from lpxpl
 *      lpMessage           Message to send
 *      ulRecipType         MAPI_TO, MAPI_CC, etc. If 0, not a recip.
 *      lpszEmailAddress    Email address of this recipient.
 *      lpfSent             Pointer to the boolean result
 *                          of the operation.
 *
 *  Returns:
 *      (HRESULT)           Set if an error encountered.
 *      *lpfSent            FALSE if sending failed,
 *                          TRUE if sending succeeded.
 *
 *  Operation:
 *      Initializes result in *lpfSent to FALSE.  Open a stream interface
 *      on the destination message file.  Write all the textized envelope
 *      properties into the stream, then use TNEF to encapsulate the remaining
 *      message properties into the stream.
 */

HRESULT
HrSendOneMessage(LPXPL lpxpl,
    LPSPropValue lpPropArray,
    LPMESSAGE lpMessage,
    ULONG ulRecipType,
    LPTSTR lpszEmailAddress,
    BOOL FAR * lpfSent)
{
    TCHAR rgchOutFileName[MAX_PATH];
    HRESULT hResult = 0;
    SCODE sc = 0;
    ULONG ulT;
    ULONG cValues;
    BOOL fFromMe;

    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    LPIID lpidMessage = (LPIID) &IID_IMessage;
    SPropValue spvDestMsgProps[3];

    LPSPropProblemArray lpProblems = NULL;
    LPSPropTagArray lpPropTagArray = NULL;

    LPSTnefProblemArray lptpa = NULL;

    WORD wKey = 0;
    LPITNEF lpTnef = (LPITNEF) NULL;
    LPSTREAM lpSof = (LPSTREAM) NULL;
    LPSTREAM lpXPSof = (LPSTREAM) NULL;

    /* Assume the worst, we'll fix it later if need be */

    *lpfSent = FALSE;

    /* Build file name of outgoing message. Because loopback doesn't
       always work on all platforms, we check the email address against
       our own and just substitute the inbox path if it matches. */

    if (!lstrcmpi(lpszEmailAddress,
            ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpPropArray).Value.LPSZ))
    {
        DebugTrace("Email Address is mine, doing my own internal loopback\n");
        lstrcpy(rgchOutFileName, ArrayIndex(PR_SAMPLE_INBOUND_DIR, lpPropArray).Value.LPSZ);
        fFromMe = TRUE;
    }
    else
    {
        lstrcpy(rgchOutFileName, lpszEmailAddress);

        /*  If this is a real email address, it won't have a
            trailing backslash. But if it's our outbound dir (when
            we're not p2p) it wiil have one. Only add one if
            it's needed. */

        ulT = lstrlen(rgchOutFileName);
        Assert(ulT > 1);

        if (lstrcmp(&rgchOutFileName[ulT], TEXT("\\")))
            lstrcat(rgchOutFileName, TEXT("\\"));
        fFromMe = FALSE;
    }

    hResult = OpenStreamOnFile(lpxpl->AllocateBuffer, lpxpl->FreeBuffer,
        STGM_CREATE | STGM_READWRITE | SOF_UNIQUEFILENAME,
        rgchOutFileName, TEXT("TNF"), &lpSof);
    if (HR_FAILED(hResult))
    {
        DebugTrace("OpenStreamOnFile(%s) failed.\n",rgchOutFileName);
        PrintfTransportLog(TEXT("Delivery failed in OpenStreamOnFile."));
        goto ret;
    }

    /* Wrap the Stream-On-File object in our buffered wrapper. */

    hResult = HrWrapStreamOnFile(lpxpl->AllocateBuffer, lpxpl->FreeBuffer,
            XPSOF_READWRITE, lpSof, &lpXPSof);
    if (HR_FAILED(hResult))
    {
        DebugTrace("HrWrapStreamOnFile() failed\n");
        goto ret;
    }

    /* Write all non-TNEF properties to the text file */

    hResult = HrIMsgToTextMsg(lpxpl, lpPropArray, lpMessage, lpXPSof);

    if (HR_FAILED(hResult))
    {
        DebugTrace("HrIMsgToTextMsg() failed.\n");
        PrintfTransportLog(TEXT("Delivery failed in HrIMsgToTextMsg."));
        goto ret;
    }

    hResult = hrSuccess;

    /* Check our .2 second timer after writting textized properties. */

    sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));

    if (sc == MAPI_W_CANCEL_MESSAGE)
    {
        DebugTrace("Cancelling message delivery.\n");
        goto ret;
    }

    /* Open a TNEF encapsulation on the StreamOnFile interface */

    hResult = OpenTnefStream(lpMAPISup, lpXPSof, TEXT("MAPIMAIL.DAT"),
            TNEF_ENCODE, lpMessage, 0x01AF, &lpTnef);

    if (HR_FAILED(hResult))
    {
        DebugTrace("OpenTNEFStream() failed.\n");
        PrintfTransportLog(TEXT("Delivery failed in OpenTNEFStream."));
        goto ret;
    }

    /* Find out what properties there are, so we can exclude the
       "nontransmittables" and the properties we've textized. */

    hResult = lpMessage->lpVtbl->GetPropList(lpMessage, 0, /* ansi */
            &lpPropTagArray);

    if (hResult)
    {
        DebugTrace("GetPropList failed.\n");
        goto ret;
    }

    Assert(lpPropTagArray);

    /* Build a new prop tag array on the memory we just got back. This
       prop tag array will only contain nontransmittable properties. */

    cValues = 0;

    for (ulT = 0; ulT < lpPropTagArray->cValues; ulT++)
    {
        ULONG ulPropTagT = lpPropTagArray->aulPropTag[ulT];

        /*  FIsTransmittable is a macro in the MAPI headers. Makes it
            really easy to determine transmittable/not when we need to */

        if ((!FIsTransmittable(ulPropTagT) || FIsTextizedProp(ulPropTagT)) &&
            (ulPropTagT != PR_MESSAGE_ATTACHMENTS))
        {
            lpPropTagArray->aulPropTag[cValues++] = ulPropTagT;
        }
    }
    lpPropTagArray->cValues = cValues;

    /* Exclude selected properties from our TNEF encapsulation. */

    hResult = lpTnef->lpVtbl->AddProps(lpTnef,
        TNEF_PROP_EXCLUDE, 0L, NULL, lpPropTagArray);

    if (HR_FAILED(hResult))
    {
        DebugTrace("AddProps failed.\n");
        goto ret;
    }

    /* Check our .2 second timer! */

    sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));

    if (sc == MAPI_W_CANCEL_MESSAGE)
    {
        DebugTrace("Cancelling message delivery.\n");
        goto ret;
    }

    /* If we had a recipient type, we should help the receiver side out
       with some properties, as follows:

       PR_MESSAGE_TO_ME should be set TRUE if ulRecipType == MAPI_TO
       PR_MESSAGE_CC_ME should be set TRUE if ulRecipType == MAPI_CC
       PR_MESSAGE_RECIP_ME should be set TRUE for either of the above */

    if (ulRecipType)
    {
        spvDestMsgProps[0].ulPropTag = PR_MESSAGE_TO_ME;
        spvDestMsgProps[0].Value.b = (ulRecipType == MAPI_TO);

        spvDestMsgProps[1].ulPropTag = PR_MESSAGE_CC_ME;
        spvDestMsgProps[1].Value.b = (ulRecipType == MAPI_CC);

        spvDestMsgProps[2].ulPropTag = PR_MESSAGE_RECIP_ME;
        spvDestMsgProps[2].Value.b = ((ulRecipType == MAPI_TO) || (ulRecipType == MAPI_CC));

        lpxpl->FreeBuffer(lpProblems);
        lpProblems = NULL;

        hResult = lpTnef->lpVtbl->SetProps(lpTnef, 0L, 0L, 3,
            spvDestMsgProps);

        if (HR_FAILED(hResult))
        {
            DebugTrace("SetProps failed");
            goto ret;
        }
    }

    /* OK. All the properties are copied over. Save Changes on the
       message we created. */

    hResult = lpTnef->lpVtbl->Finish(lpTnef, 0L, &wKey, &lptpa);
    lpxpl->FreeBuffer(lptpa);
    if (HR_FAILED(hResult))
    {
        DebugTrace("Finish failed.\n");
        goto ret;
    }

    hResult = lpXPSof->lpVtbl->Commit(lpXPSof, STGC_DEFAULT);

    if (HR_FAILED(hResult))
    {
        DebugTrace("Commit stream failed.\n");
        goto ret;
    }

    /* Check our .2 second timer! */

    sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));

    if (sc == MAPI_W_CANCEL_MESSAGE)
    {
        DebugTrace("Cancelling message delivery.\n");
        goto ret;
    }

    *lpfSent = TRUE;

    /* Log successful transmission. */

    PrintfTransportLog(TEXT("Delivery Complete: %s"), rgchOutFileName);

ret:
    /* Release any open object */

    UlRelease(lpTnef);
    UlRelease(lpXPSof);
    UlRelease(lpSof);

    if (HR_FAILED(hResult) && lpSof)
        DeleteFile(rgchOutFileName);

    /* Release the prop tag array and/or problem array if any */

    lpxpl->FreeBuffer(lpPropTagArray);

    DebugTraceResult(HrSendOneMessage, hResult);
    return hResult;
}


/* Stuff to support the textized message formatting */

const static SizedSPropTagArray(4, sptMsgProps) =
{
    4,
    {
        PR_CLIENT_SUBMIT_TIME,
        PR_SUBJECT,
        PR_PRIORITY,
        PR_BODY
    }
};

const static SizedSPropTagArray(5, sptRecipProps) =
{
    5,
    {
        PR_RECIPIENT_TYPE,
        PR_EMAIL_ADDRESS,
        PR_ADDRTYPE,
        PR_DISPLAY_NAME,
        PR_RESPONSIBILITY
    }
};

const static SizedSPropTagArray(3, sptSenderDelegate) =
{
    3,
    {
        PR_SENT_REPRESENTING_ENTRYID,
        PR_SENDER_ENTRYID,
        PR_REPLY_RECIPIENT_ENTRIES,
    }
};

TCHAR rgszTags[NUM_TAGS][MAX_TAG_LEN] =
{
    TEXT("Message: "),
    TEXT("From: "),
    TEXT("Representing: "),
    TEXT("Reply To: "),
    TEXT("Date: "),
    TEXT("To: "),
    TEXT("Cc: "),
    TEXT("Bcc: "),
    TEXT("Subject: "),
    TEXT("Priority Urgent: "),
    TEXT("Priority Normal: "),
    TEXT("Priority Low: "),
    TEXT("Contents: "),
    TEXT("Text Item: "),
    TEXT("File Item: ")
};

TCHAR szCRLF[3] = {TEXT("\r\n")};
TCHAR szCRLFCRLF[5] = {TEXT("\r\n\r\n")};


/*
 -  HrIMsgToTextMsg
 -
 *  Purpose:
 *      Called by HrSendOneMessage() to write the envelope properties
 *      to the destination message text file.  Uses the StreamOnFile
 *      interface for all the file access.  This stream interface
 *      is then passed to the TNEF encoder, with its current file
 *      pointer un-modified, so the non-envelope properties can be
 *      encapsulated in a TNEF encapsulation in a "File Item" section.
 *
 *  Parameters:
 *      lpxpl               Pointer to Transport Logon object
 *      lpPropArray         Copy of the sessions logon properties
 *      lpMessage           Message to send
 *      lpSof               Pointer to the stream interface
 *
 *  Returns:
 *      (HRESULT)           Set if an error encountered.
 *
 *  Operation:
 *      Call GetProps() on the message to extract PR_SUBMIT_DATE, PR_SUBJECT,
 *      PR_PRIORITY, and PR_BODY.  Then call GetRecipientTable() to extract
 *      the PR_DISPLAY_NAME and PR_EMAIL_ADDRESS for each type of
 *      PR_RECIPIENT_TYPE.  Write all this info to the stream (after
 *      formatting appropriately).
 */

HRESULT
HrIMsgToTextMsg(LPXPL lpxpl, LPSPropValue lpPropArray, LPMESSAGE lpMessage, LPSTREAM lpSof)
{
    HRESULT hr = hrSuccess;
    ULONG cMsgVals = 0;
    ULONG cSndrVals = 0;
    LPSPropValue lpMsgProps = NULL;
    LPSPropValue lpSndrProps = NULL;
    LPSPropValue lpPropT = NULL;
    LPMAPITABLE lpTbl = NULL;
    LPSRowSet lpRows = NULL;
    ULONG uli;
    ULONG cbOut;
    ULONG cbRead;
    ULONG cbCRLF = lstrlen(szCRLF);
    ULONG cbCRLFCRLF = lstrlen(szCRLFCRLF);
    TCHAR szRep[128];
    TCHAR szFrom[128];
    TCHAR szOutBuf[128];
    TCHAR rgchStrmBuf[MAX_STRM_BUF];
    LPTSTR lpszT1;
    LPTSTR lpszT2;
    LPSTREAM lpStrm = NULL;

    /* Get the 4 Message properties to be textized */

    hr = lpMessage->lpVtbl->GetProps(lpMessage,
            (LPSPropTagArray) &sptMsgProps, 0, /* ansi */
            &cMsgVals, &lpMsgProps);

    if (HR_FAILED(hr) || !cMsgVals)
    {
        DebugTrace("GetProps() MsgProps failed.\n");
        goto ret;
    }

    /* Get the 3 Sender/Delegate properties to be textized */

    hr = lpMessage->lpVtbl->GetProps(lpMessage,
            (LPSPropTagArray) &sptSenderDelegate, 0, /* ansi */
            &cSndrVals, &lpSndrProps);

    if (HR_FAILED(hr) || !cSndrVals)
    {
        DebugTrace("GetProps()  SndrProps failed.\n");
        goto ret;
    }

    /* Returns the Recipient Table in a well defined state
       (i.e. minimal column set and restricted on our AddrType). */

    hr = HrPrepareRecipientTable(lpPropArray, lpMessage, &lpTbl);

    if (HR_FAILED(hr))
    {
        DebugTrace("HrPrepareRecipientTable()  failed.\n");
        goto ret;
    }

    /* Write Message: field */

    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, rgszTags[tagMessage],
            lstrlen(rgszTags[tagMessage]), &cbOut), ret);
    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
            cbCRLFCRLF, &cbOut), ret);

    /* Write From: and Representing: fields */

    /* The following code sets the Sender/Delegate */
    /* properties as follows:

        1) If no PR_SENT_REPRESENTING_??? in message,
            a)  If no PR_SENDER_??? in message,
                    PR_SENDER_??? = transport identities
            b)  PR_SENT_REPRESENTING_??? = PR_SENDER_???
        2) (else) If there was a PR_SENT_REPRESENTING_??? in message,
            a)  If no PR_SENDER_??? in message,
                    PR_SENDER_??? = PR_SENT_REPRESENTING_???
        3)  If no PR_REPLY_RECIPIENT_???,
                PR_REPLY_RECIPIENT_ENTRIES = PR_SENT_REPRESENTING_ENTRYID
                PR_REPLY_RECIPIENT_NAMES = PR_SENT_REPRESENTING_NAME

       This just works because HrCrackSenderEID() doesn't change the
       szFrom or szRep memory unless it is successful.  It is for this
       reason that we don't check the return from HrCrackSenderEID() */

    hr = hrSuccess;
    *szFrom = '\0';
    *szRep = '\0';

    if (lpSndrProps[0].ulPropTag == PR_SENT_REPRESENTING_ENTRYID)
        HrCrackSenderEID(lpxpl, lpSndrProps[0].Value.bin.cb,
            lpSndrProps[0].Value.bin.lpb, szRep);

    if (lpSndrProps[1].ulPropTag == PR_SENDER_ENTRYID)
        HrCrackSenderEID(lpxpl, lpSndrProps[1].Value.bin.cb,
            lpSndrProps[1].Value.bin.lpb, szFrom);

    if (!*szFrom && !*szRep)
    {
        lpszT1 = ArrayIndex(PR_SAMPLE_DISPLAY_NAME, lpPropArray).Value.LPSZ;
        lpszT2 = ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpPropArray).Value.LPSZ;
        wsprintf(szFrom, TEXT("%s[%s]"), lpszT1, lpszT2);
        lstrcpy(szRep, szFrom);
    }
    else if (*szFrom && !*szRep)
    {
        lstrcpy(szRep, szFrom);
    }
    else
    {
        lstrcpy(szFrom, szRep);
    }

    wsprintf(szOutBuf, TEXT("%s%s"), rgszTags[tagFrom], szFrom);
    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szOutBuf,
            lstrlen(szOutBuf), &cbOut), ret);
    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
            cbCRLFCRLF, &cbOut), ret);

    wsprintf(szOutBuf, TEXT("%s%s"), rgszTags[tagRepresenting], szRep);
    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szOutBuf,
            lstrlen(szOutBuf), &cbOut), ret);
    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
            cbCRLFCRLF, &cbOut), ret);

    /* Write Reply To: fields */

    if (lpSndrProps[2].ulPropTag == PR_REPLY_RECIPIENT_ENTRIES)
    {
        LPFLATENTRYLIST lpList = (LPFLATENTRYLIST) lpSndrProps[2].Value.bin.lpb;
        LPBYTE lpb;
        ULONG cEntries;

        /* Attempt some level of validation for this property */

        if (!lpList
            || IsBadReadPtr(lpList, CbNewFLATENTRYLIST(0))
            || !lpList->abEntries
            || IsBadReadPtr(lpList, (UINT) CbFLATENTRYLIST(lpList))
            || !lpList->cEntries
            || (lpList->cEntries * sizeof(GUID) > lpList->cbEntries))
        {
            DebugTrace("Bad PR_REPLY_RECIPIENT_ENTRIES!\n");
            DebugTrace("Skipping the Reply To: field.\n");
        }
        else
        {
            lpb = lpList->abEntries;
            cEntries = lpList->cEntries;

            while (cEntries--)
            {
                LPFLATENTRY lpEntry = (LPFLATENTRY) lpb;
                ULONG ulSize;

                if (IsBadReadPtr(lpEntry, CbNewFLATENTRY(0))
                    || IsBadReadPtr(lpEntry, (UINT) CbFLATENTRY(lpEntry)))
                {
                    DebugTrace("Bad entry inside PR_REPLY_RECIPIENT_ENTRIES!\n");
                    break;
                }

                ulSize = lpEntry->cb;

                hr = HrCrackSenderEID(lpxpl, ulSize, lpEntry->abEntry, szFrom);

                if (!hr)
                {
                    wsprintf(szOutBuf, TEXT("%s%s"),
                        rgszTags[tagReplyTo], szFrom);
                    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szOutBuf,
                            lstrlen(szOutBuf), &cbOut), ret);
                    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLF,
                            cbCRLF, &cbOut), ret);
                }

                lpb += offsetof (FLATENTRY, abEntry) + ((ulSize + 3) & -4L);
            }

            /* Add one more CR/LF pair after Reply Recipients */

            TraceFailedWrite(lpSof->lpVtbl->Write(lpSof,
                    szCRLF, cbCRLF, &cbOut), ret);
        }
    }
    else
    {
        wsprintf(szOutBuf, TEXT("%s%s"), rgszTags[tagReplyTo], szFrom);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szOutBuf,
                lstrlen(szOutBuf), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
                cbCRLFCRLF, &cbOut), ret);
    }

    /* Write Date: field */

    if (FPropIndex(lpMsgProps, cMsgVals, PR_CLIENT_SUBMIT_TIME, &uli))
    {
        /* Property exists in message; write it to the stream */
        FormatFileTime(&lpMsgProps[uli].Value.ft, szOutBuf);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, rgszTags[tagDate],
                lstrlen(rgszTags[tagDate]), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szOutBuf,
                lstrlen(szOutBuf), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
                cbCRLFCRLF, &cbOut), ret);
    }

    /* Write To: & Cc: fields */

    while (TRUE)
    {
        /* Get a row from the Recipient Table */

        hr = lpTbl->lpVtbl->QueryRows(lpTbl, 1, 0, &lpRows);

        if (hr || !lpRows || (lpRows->cRows != 1))
            break;

        lpPropT = lpRows->aRow[0].lpProps;

        /* Throw away MAPI_ORIG and P1 Recipient Types */

        if ((lpPropT[0].Value.l != MAPI_TO) &&
            (lpPropT[0].Value.l != MAPI_CC))
        {
            FreeProws(lpRows);
            lpRows = NULL;
            lpPropT = NULL;
            continue;
        }

        /* Write Recipients as:
            '{To: | Cc: } Display Name [email-address]' */

        Assert((lpPropT[0].Value.l == MAPI_TO) ||
            (lpPropT[0].Value.l == MAPI_CC));

        wsprintf(szOutBuf, TEXT("%s%s[%s]"),
            rgszTags[tagDate + lpPropT[0].Value.l],
            lpPropT[3].Value.LPSZ, lpPropT[1].Value.LPSZ);

        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szOutBuf,
                lstrlen(szOutBuf), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLF,
                cbCRLF, &cbOut), ret);

        /* Clean-Up */

        FreeProws(lpRows);
        lpRows = NULL;
        lpPropT = NULL;
    }

    /* Add one more CR/LF pair after recipients */

    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLF, cbCRLF, &cbOut), ret);

    /* Write Subject: field */

    if (FPropIndex(lpMsgProps, cMsgVals, PR_SUBJECT, &uli))
    {
        /* Property exists and is small enough to not require a
           stream interface to be opened on it; just write it. */

        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, rgszTags[tagSubject],
                lstrlen(rgszTags[tagSubject]), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLF,
                cbCRLF, &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, lpMsgProps[uli].Value.LPSZ,
                lstrlen(lpMsgProps[uli].Value.LPSZ), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
                cbCRLFCRLF, &cbOut), ret);
    }
    else if (!(hr = lpMessage->lpVtbl->OpenProperty(lpMessage, PR_SUBJECT,
                (LPIID) &IID_IStream, 0, 0, (LPUNKNOWN *) &lpStrm)))
    {
        /* Property exists and requires a stream interface to
           access all the data.  Copy between streams! */

        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, rgszTags[tagSubject],
                lstrlen(rgszTags[tagSubject]), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLF,
                cbCRLF, &cbOut), ret);

        while (TRUE)
        {
            hr = lpStrm->lpVtbl->Read(lpStrm, (LPVOID) rgchStrmBuf,
                MAX_STRM_BUF, &cbRead);

            if (hr || (cbRead == 0))
                break;          /* There's nothing to write; we're done! */

            TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, (LPVOID) rgchStrmBuf,
                    cbRead, &cbOut), ret);

            if (cbRead < MAX_STRM_BUF)
                break;          /* We've exhausted the stream; we're done! */
        }
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
                cbCRLFCRLF, &cbOut), ret);

        lpStrm->lpVtbl->Release(lpStrm);
        lpStrm = NULL;
    }

    /* Write Priority: field */

    if (FPropIndex(lpMsgProps, cMsgVals, PR_PRIORITY, &uli))
    {
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof,
                rgszTags[tagPrioNormal - lpMsgProps[uli].Value.l],
                lstrlen(rgszTags[tagPrioNormal - lpMsgProps[uli].Value.l]),
                &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
                cbCRLFCRLF, &cbOut), ret);
    }

    /* Write Contents: field */

    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, rgszTags[tagContents],
            lstrlen(rgszTags[tagContents]), &cbOut), ret);
    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
            cbCRLFCRLF, &cbOut), ret);

    /* Text Item: */

    if (FPropIndex(lpMsgProps, cMsgVals, PR_BODY, &uli))
    {
        /* Property exists and is small enough to not require
           a stream interface to be opened on it; just copy it */

        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, rgszTags[tagTextItem],
                lstrlen(rgszTags[tagTextItem]), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLF,
                cbCRLF, &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, lpMsgProps[uli].Value.LPSZ,
                lstrlen(lpMsgProps[uli].Value.LPSZ), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
                cbCRLFCRLF, &cbOut), ret);
    }
    else if (!(hr = lpMessage->lpVtbl->OpenProperty(lpMessage, PR_BODY,
                (LPIID) &IID_IStream, 0, 0, (LPUNKNOWN *) &lpStrm)))
    {
        /* Property exists and requires a stream interface to
           access all the data.  Copy between streams! */

        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, rgszTags[tagTextItem],
                lstrlen(rgszTags[tagTextItem]), &cbOut), ret);
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLF,
                cbCRLF, &cbOut), ret);

        while (TRUE)
        {
            hr = lpStrm->lpVtbl->Read(lpStrm, (LPVOID) rgchStrmBuf,
                MAX_STRM_BUF, &cbRead);

            if (hr || (cbRead == 0))
                break;          /* There's nothing to write; we're done! */

            TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, (LPVOID) rgchStrmBuf,
                    cbRead, &cbOut), ret);

            if (cbRead < MAX_STRM_BUF)
                break;          /* We've exhausted the stream; we're done! */
        }
        TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLFCRLF,
                cbCRLFCRLF, &cbOut), ret);

        lpStrm->lpVtbl->Release(lpStrm);
        lpStrm = NULL;
    }

    /* File Item: */

    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, rgszTags[tagFileItem],
            lstrlen(rgszTags[tagFileItem]), &cbOut), ret);
    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, TEXT("MESSAGE.TNF"),
            lstrlen(TEXT("MESSAGE.TNF")), &cbOut), ret);
    TraceFailedWrite(lpSof->lpVtbl->Write(lpSof, szCRLF,
            cbCRLF, &cbOut), ret);

ret:
    lpxpl->FreeBuffer(lpMsgProps);
    lpxpl->FreeBuffer(lpSndrProps);
    FreeProws(lpRows);

    UlRelease(lpTbl);

    DebugTraceResult(HrIMsgToTextMsg(), hr);
    return hr;
}


/*
 -  HrPrepareRecipientTable
 -
 *  Purpose:
 *      Gets the Recipient Table from an IMAPIMessage and sets its
 *      columns, restricts the view, and sorts it (if sorts are
 *      supported).  All this in preparation of writing recipients
 *      to the destination message file.
 *
 *  Parameters:
 *      lpPropArray         Pointer to Transport Logon object
 *      lpMsg               Message to GetRecipientTable on
 *      lppTbl              Receives the RecipientTable
 *
 *  Returns:
 *      hr                  Indicating Success/Failure
 */

HRESULT
HrPrepareRecipientTable(LPSPropValue lpPropArray, LPMESSAGE lpMsg, LPMAPITABLE * lppTbl)
{
    HRESULT hr = hrSuccess;
    LPMAPITABLE lpTbl = NULL;

    SizedSSortOrderSet(2, rgSort) =
    {
        2, 0, 0,
        {
            PR_RECIPIENT_TYPE, TABLE_SORT_ASCEND,
                PR_ROWID, TABLE_SORT_ASCEND
        }
    };

    *lppTbl = NULL;

    hr = lpMsg->lpVtbl->GetRecipientTable(lpMsg, 0, &lpTbl);

    if (HR_FAILED(hr))
    {
        DebugTrace("GetRecipientTable() failed in HrPrepareRecipientTable()");
        goto ret;
    }

    /* SetColumns to: PR_RECIPIENT_TYPE, PR_EMAIL_ADDRESS, PR_ADDRTYPE,
       PR_DISPLAY_NAME, and PR_RESPONSIBILITY in that order */

    hr = lpTbl->lpVtbl->SetColumns(lpTbl, (LPSPropTagArray) &sptRecipProps,
        TBL_BATCH);

    if (HR_FAILED(hr))
    {
        DebugTrace("SetColumns() failed in HrPrepareRecipientTable()");
        goto ret;
    }

    /* Sort by: PR_RECIPIENT_TYPE (i.e. MAPI_TO, MAPI_CC, MAPI_BCC)
            and PR_ROWID, both in acsending order */

    hr = lpTbl->lpVtbl->SortTable(lpTbl, (LPSSortOrderSet) &rgSort, TBL_BATCH);

    if (hr)
    {
        /* Don't fail the call for no support!  Just return
           the table in whatever order it may be in by default. */

        if (GetScode(hr) == MAPI_E_NO_SUPPORT)
            hr = 0;
        else
            DebugTrace("SortTable() failed in HrPrepareRecipientTable()");
    }

    /* Seek to the beginning since sorting may have moved out position */

    hr = lpTbl->lpVtbl->SeekRow(lpTbl, BOOKMARK_BEGINNING, 0, NULL);

    if (hr)
    {
        DebugTrace("SeekRow() failed in HrPrepareRecipientTable()");
    }

ret:
    if (HR_FAILED(hr))
    {
        UlRelease(lpTbl);
    }
    else
        *lppTbl = lpTbl;

    DebugTraceResult(HrPrepareRecipientTable(), hr);
    return hr;
}


/*
 -  HrCrackSenderEID
 -
 *  Purpose:
 *      Does an OpenEntry() on the EntryID and GetProps() PR_DISPLAY_NAME
 *      and PR_EMAIL_ADDRESS.  Then formats the return string like:
 *          "Display Name[email-address]"
 *
 *  Parameters:
 *      lpxpl           Pointer to Transport Logon object
 *      cb              Count of bytes in EntryID
 *      lpb             Pointer to EntryID
 *      lpsz            Receives the formatted Name/Address pair
 *
 *  Returns:
 *      hr              Indicating Success/Failure
 *
 *  Note:
 *      No parameter validation!  I assume the caller knew what was
 *      being passed in and ensured all was well.
 */

HRESULT
HrCrackSenderEID(LPXPL lpxpl, ULONG cb, LPBYTE lpb, LPTSTR lpsz)
{
    HRESULT hr = hrSuccess;
    ULONG ulObjType;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    LPMAPIPROP lpMAPIProp = NULL;
    ULONG cVals = 0;
    LPSPropValue lpProps = NULL;

    const static SizedSPropTagArray(2, sptCracked) =
    {
        2,
        {
            PR_DISPLAY_NAME,
            PR_EMAIL_ADDRESS
        }
    };

    /* Open a Property Interface on this EntryID */

    hr = lpMAPISup->lpVtbl->OpenEntry(lpMAPISup, cb, (LPENTRYID) lpb,
        NULL, 0, &ulObjType, (LPUNKNOWN *) &lpMAPIProp);

    if (hr)
    {
        DebugTrace("OpenEntry() Failed in HrCrackSenderEID().\n");
        goto ret;
    }

    /* Get the 2 properties we need from this object */

    hr = lpMAPIProp->lpVtbl->GetProps(lpMAPIProp,
        (LPSPropTagArray) &sptCracked, 0, /* ansi */
        &cVals, &lpProps);

    if (hr || !cVals)
    {
        DebugTrace("GetProps() Failed in HrCrackSenderEID().\n");
        goto ret;
    }

    /* Assert that all went well so far!!! */

    Assert(lpProps);
    Assert(cVals == 2);
    Assert(lpProps[0].ulPropTag == PR_DISPLAY_NAME);
    Assert(lpProps[1].ulPropTag == PR_EMAIL_ADDRESS);

    /* Format our Name/Address pair as desired */

    wsprintf(lpsz, "%s[%s]", lpProps[0].Value.LPSZ, lpProps[1].Value.LPSZ);

ret:
    lpxpl->FreeBuffer(lpProps);

    UlRelease(lpMAPIProp);

    DebugTraceResult(HrCrackSenderEID(), hr);
    return hr;
}


/*
 -  FPropIndex
 -
 *  Purpose:
 *      Finds and returns (if it exists) the index of ulPropTag
 *      in the lpProps SPropValue array.
 *
 *  Parameters:
 *      lpProps         PropValue array to search through
 *      cVals           Count of properties in lpProps
 *      ulPropTag       PropTag to search for
 *      puli            Receives the index of ulPropTag in lpProps
 *
 *  Returns:
 *      TRUE/FALSE      TRUE if found, FALSE otherwise
 */

BOOL
FPropIndex(LPSPropValue lpProps, ULONG cVals, ULONG ulPropTag, ULONG * puli)
{
    Assert(lpProps);
    Assert(cVals);
    Assert(puli);

    while (cVals--)
    {
        if (lpProps[cVals].ulPropTag == ulPropTag)
        {
            *puli = cVals;
            return TRUE;
        }
    }
    return FALSE;
}


/*
 -  FormatFileTime
 -
 *  Purpose:
 *      Formats a Windows NT file time as a MAPI date/time string
 *      of the format:  yyyy/mm/dd hh:mm
 *
 *  Parameters:
 *      pft             Pointer to FILETIME to convert
 *      szTime          Destination string
 *
 *  Returns:
 *      void.
 */

void
FormatFileTime(FILETIME * pft, LPTSTR szTime)
{
    SYSTEMTIME systime;

    FileTimeToSystemTime(pft, &systime);
    wsprintf(szTime, "%04.4d/%02.2d/%02.2d %02.2d:%02.2d",
        systime.wYear, systime.wMonth, systime.wDay,
        systime.wHour, systime.wMinute);
}


/*
 -  FIsTextizedProp
 -
 *  Purpose:
 *      Used to determine if the property is one we wish to
 *      exclude from the TNEF encapsulation (i.e. one we've
 *      textized in the envelope of the message file).
 *
 *  Parameters:
 *      ulPropTag       PropTag to test
 *
 *  Return:
 *      BOOL            Indicating if the property is textized
 */

BOOL
FIsTextizedProp(ULONG ulPropTag)
{
    ULONG i;

    static SizedSPropTagArray(16, spta) =
    {
        16,
        {
            PR_SENDER_NAME,
            PR_SENDER_ENTRYID,
            PR_SENDER_SEARCH_KEY,
            PR_SENDER_EMAIL_ADDRESS,
            PR_SENDER_ADDRTYPE,
            PR_SENT_REPRESENTING_NAME,
            PR_SENT_REPRESENTING_ENTRYID,
            PR_SENT_REPRESENTING_SEARCH_KEY,
            PR_SENT_REPRESENTING_EMAIL_ADDRESS,
            PR_SENT_REPRESENTING_ADDRTYPE,
            PR_REPLY_RECIPIENT_ENTRIES,
            PR_REPLY_RECIPIENT_NAMES,
            PR_SUBJECT,
            PR_CLIENT_SUBMIT_TIME,
            PR_BODY,
            PR_PRIORITY
        }
    };

    for (i = 0; i < spta.cValues; i++)
        if (spta.aulPropTag[i] == ulPropTag)
            return TRUE;

    return FALSE;
}


/*
 -  FreeMyAdrList
 -
 *  Purpose:
 *      Called by anyone who winds up with a MYADRLIST structure
 *      and wants to free it.
 *
 *  Parameters:
 *      lpxpl               Session context.
 *      lpMyAdrList         Structure to free.
 *
 *  Returns:
 *      void                Data in lpMyAdrList freed.
 *
 *  Operation:
 *      Walks through adrlist and frees all the memory.
 */

void
FreeMyAdrList(LPXPL lpxpl, LPMYADRLIST lpMyAdrList)
{
    ULONG ulT;
    LPSPropValue lpspvT;
    LPADRLIST lpAdrListT;

    /*  Clean up any adrlist stuff that's lying around. */

    if (lpMyAdrList)
    {
        lpAdrListT = lpMyAdrList->lpAdrList;

        if (lpAdrListT && lpAdrListT->cEntries)
        {
            for (ulT = 0; ulT < lpAdrListT->cEntries; ulT++)
            {
                lpspvT = (lpAdrListT->aEntries[ulT]).rgPropVals;

                lpxpl->FreeBuffer((LPVOID) lpspvT);
            }
        }
        lpxpl->FreeBuffer((LPVOID) lpAdrListT);
        lpxpl->FreeBuffer((LPVOID) lpMyAdrList);
    }
}


CHAR lpszEOM[] = "\n*** End of Message ***\n";
#define cchEOM (sizeof(lpszEOM) - 1)

STDMETHODIMP
PreprocessMessage (LPMAPISESSION lpSession,
    LPMESSAGE lpMessage,
    LPADRBOOK lpAdrBook,
    LPMAPIFOLDER lpFolder,
    LPALLOCATEBUFFER AllocateBuffer,
    LPALLOCATEMORE AllocateMore,
    LPFREEBUFFER FreeBuffer,
    ULONG FAR *lpcOutbound,
    LPMESSAGE FAR * FAR * lpppMessage,
    LPADRLIST FAR *lppRecipList)
{
    HRESULT hr;
    LPSTREAM lpstrm = NULL;
    ULONG cb;
    LARGE_INTEGER liTo = {0};

    hr = lpMessage->lpVtbl->OpenProperty (lpMessage,
                                    PR_BODY_A,
                                    (LPIID)&IID_IStream,
                                    0,
                                    MAPI_MODIFY,
                                    (LPUNKNOWN FAR *)&lpstrm);
    if (!HR_FAILED (hr))
    {
        hr = lpstrm->lpVtbl->Seek (lpstrm, liTo, STREAM_SEEK_END, NULL);
        if (!HR_FAILED (hr))
        {
            hr = lpstrm->lpVtbl->Write (lpstrm, lpszEOM, cchEOM, &cb);
            if (!HR_FAILED (hr) && (cb == cchEOM))
            {
                if (!HR_FAILED (hr = lpstrm->lpVtbl->Commit (lpstrm, 0L)))
                    hr = lpMessage->lpVtbl->SaveChanges (lpMessage, KEEP_OPEN_READWRITE);
            }
        }
        UlRelease (lpstrm);
    }
    
    *lpcOutbound = 0;
    *lpppMessage = NULL;
    
    DebugTraceResult (PreprocessMessage(), hr);
    return hr;
}


STDMETHODIMP
RemovePreprocessInfo (LPMESSAGE lpMessage)
{
    CHAR lpszBuf[sizeof(lpszEOM)] = {0};
    HRESULT hr;
    LARGE_INTEGER liTo;
    LPSTREAM lpstrm = NULL;
    ULARGE_INTEGER liSize;
    ULONG cb;
    BOOL fUpd = FALSE;

    hr = lpMessage->lpVtbl->OpenProperty (lpMessage,
                                    PR_BODY_A,
                                    (LPIID)&IID_IStream,
                                    0,
                                    MAPI_MODIFY,
                                    (LPUNKNOWN FAR *)&lpstrm);
    if (!HR_FAILED (hr))
    {
        liTo.HighPart =  -1;
        liTo.LowPart = (ULONG)(-(LONG)(cchEOM));
        hr = lpstrm->lpVtbl->Seek (lpstrm, liTo, STREAM_SEEK_END, &liSize);
        if (!HR_FAILED (hr))
        {
            hr = lpstrm->lpVtbl->Read (lpstrm, lpszBuf, cchEOM, &cb);
            if (!HR_FAILED (hr) && (cb == cchEOM))
            {
                if (!lstrcmpiA (lpszEOM, lpszBuf))
                {
                    if (!HR_FAILED (hr = lpstrm->lpVtbl->SetSize (lpstrm, liSize)) &&
                        !HR_FAILED (hr = lpstrm->lpVtbl->Commit (lpstrm, 0L)))
                        hr = lpMessage->lpVtbl->SaveChanges (lpMessage, KEEP_OPEN_READWRITE);
                }
            }
        }
    }
    UlRelease (lpstrm);
    DebugTraceResult (RemovePreprocessInfo(), hr);
    return hr;
}
