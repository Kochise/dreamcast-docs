/*
 -  X P S N D M S G . C
 -
 *  Purpose:
 *      Code to support the MAPI Transport SPI entry points for
 *      message transmission.
 *      This module contains the following SPI entry points:
 *
 *          SubmitMessage()
 *          EndMessage()
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "xppch.h"


HRESULT HrAddDeferred(LPXPL lpxpl, LPMESSAGE lpMsg, ULONG *lpulMsgRef);


/*
 -  XPL_SubmitMessage
 -
 *  Purpose:
 *      Called by the Spooler when it wishes to attempt transmission
 *      of a message.
 *
 *  Parameters:
 *      ulFlags             Flags from the Spooler. The only
 *                          flag defined in the MAPI 1.0 TSPI
 *                          is BEGIN_DEFERRED, and this transport
 *                          doesn't do deferred transmission.
 *      lpMessage           Pointer to message object that the
 *                          Spooler wants sent.
 *      lpulMsgRef          Pointer to where the transport should
 *                          store a unsigned long for use in
 *                          identifying TransportNotify() message
 *                          events. Initialized to 1 by the
 *                          Spooler. We use this to ID deferred
 *                          messages using DEFERRED_MSG_REF.
 *      lpulReturnParm      Used for several MAPI_E_XXX returns,
 *                          but this transport doesn't do any
 *                          of them.
 *
 *  Returns:
 *      (HRESULT)           MAPI_E_BUSY if the Spooler calls
 *                          here again while we're busy, else
 *                          errors encountered if any.
 *
 *  Operation:
 *      For non peer-to-peer, "send" the message to our outbound directory.
 *
 *      For peer-to-peer, use the ADRLIST builder HrBuildAdrList to attempt
 *      transmission to each recipient and build both a sent ADRLIST and a
 *      NDR ADRLIST. ModifyRecipients() on the Spooler message if there's
 *      anyone in the sent ADRLIST. This tells the spooler which ones got
 *      the mail.  If there were any recipients in the NDR ADRLIST, we need
 *      to StatusRecips() with that list, and we will need to
 *      ModifyRecipients() again with them.
 *
 *      For non peer-to-peer or p2p with NDR recipients, use the ADRLIST
 *      builder HrBuildAdrList to make a ADRLIST with all of our unsent
 *      recipients (for non p2p, delivery to all recipients consists of
 *      putting a file into the outbound and for NDR cases, we just take
 *      responsibility because we've already NDR'ed them) and
 *      ModifyRecipients().
 */

STDMETHODIMP
XPL_SubmitMessage(LPXPL lpxpl,
    ULONG ulFlags,
    LPMESSAGE lpMessage,
    ULONG * lpulMsgRef,
    ULONG * lpulReturnParm)
{
    LPTSTR lpszMyDir;
    HRESULT hResult = 0;
    SCODE sc = 0;
    BOOL fUpdatedStatus = FALSE;
    BOOL fPeer2Peer;

    LPSPropValue lpPropArray = NULL;
    LPMAPISUP lpMAPISup;

    ULONG cValues;
    LPSPropValue lpMsgProps = NULL;

    static const SizedSPropTagArray(2, sptMsgDefer) =
    {
        2,
        {
            PR_SAMPLE_PER_MSG_DEFER,
            PR_SAMPLE_PER_RECIP_DEFER
        }
    };

    SPropValue spvRecipUnsent =
    {PR_RESPONSIBILITY, 0L, FALSE};
    SPropValue spvRecipDefer =
    {PR_SAMPLE_PER_RECIP_DEFER, 0L, TRUE};
    SRestriction rgsrOr[2];
    SRestriction rgsrAnd[2];
    SRestriction srExist;
    SRestriction srRecipUnsent;

    LPMAPITABLE lpTable = NULL;
    LPMYADRLIST lpMyAdrListDone = NULL;
    LPMYADRLIST lpMyAdrListNotDone = NULL;

    /* Simple re-entrancy test. Should never happen anyway. */

    if (lpxpl->ulTransportStatus & STATUS_OUTBOUND_ACTIVE)
    {
        hResult = ResultFromScode(MAPI_E_BUSY);
        DebugTrace("XPL_SubmitMessage reentrancy test failed.\n");
        goto ret;
    }

    /* Signal that we're uploading. */

    lpxpl->ulTransportStatus |= STATUS_OUTBOUND_ACTIVE;
    hResult = HrUpdateTransportStatus(lpxpl, 0L);
    if (hResult)
        goto ret;
    fUpdatedStatus = TRUE;

    /*  Session's OK, hook up some local references */

    sc = ScCopySessionProps(lpxpl, &lpPropArray, NULL);

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        DebugTrace("ScCopySessionProps failed in SubmitMessage.\n");
        goto ret;
    }

    lpMAPISup = lpxpl->lpMAPISup;
    fPeer2Peer = ((ArrayIndex(PR_SAMPLE_FLAGS, lpPropArray).Value.ul) & PR_SAMPLE_FLAG_PEER_TO_PEER) != 0;
    lpszMyDir = ArrayIndex(PR_SAMPLE_OUTBOUND_DIR, lpPropArray).Value.LPSZ;

    PrintfTransportLog(TEXT("Start Outbound: %s"),
        ArrayIndex(PR_SAMPLE_DISPLAY_NAME, lpPropArray).Value.LPSZ);

    /* Reset the timer for SpoolerYield() */

    HrCheckSpoolerYield(lpMAPISup, TRUE);

    /* Check if we are to defer this message */

    hResult = lpMessage->lpVtbl->GetProps(lpMessage,
        (LPSPropTagArray) &sptMsgDefer, 0, /* ansi */
        &cValues, &lpMsgProps);

    if (HR_FAILED(hResult))
    {
        DebugTrace("Failed getting props on the message.\n");
        goto ret;
    }

    /* We'll default fResendDeferred to TRUE unless we defer this msg */

    lpxpl->fResendDeferred = TRUE;

    /* If PR_SAMPLE_PER_MSG_DEFER exists and is TRUE, then we delete
       this property from the message, and add this message to our
       deferred list.  The lpulMsgRef is set to the value assigned to
       the node in our list.  When EndMessage is called we search for
       this Ref in to list.  If found, we return END_DONT_RESEND,
       causing the spooler to defer the msg. */

    if (lpMsgProps->ulPropTag == PR_SAMPLE_PER_MSG_DEFER)
    {
        lpMessage->lpVtbl->DeleteProps(lpMessage,
            (LPSPropTagArray) &sptMsgDefer, NULL);

        lpMessage->lpVtbl->SaveChanges(lpMessage, KEEP_OPEN_READWRITE);

        if (lpMsgProps->Value.b == TRUE)
        {
            hResult = HrAddDeferred(lpxpl, lpMessage, lpulMsgRef);
            goto ret;
        }
    }

    /* Now, see if any Recipients have PR_SAMPLE_PER_RECIP_DEFER set to
       TRUE in the RecipientTable.  If so, then slam a non-transmittable
       property into the message to indicate we've deferred this message
       for some recipients this time around.  If this property already
       exists, then we know it has already been deferred and we should
       just go ahead and send to all un-handled recipients.              */

    if (lpMsgProps[1].ulPropTag == PR_SAMPLE_PER_RECIP_DEFER)
    {
        lpMessage->lpVtbl->DeleteProps(lpMessage,
            (LPSPropTagArray) &sptMsgDefer, NULL);

        lpMessage->lpVtbl->SaveChanges(lpMessage, KEEP_OPEN_READWRITE);

        /*  Initialize a restriction -- we'll need it soon. */

        srRecipUnsent.rt = RES_PROPERTY;
        srRecipUnsent.res.resProperty.relop = RELOP_EQ;
        srRecipUnsent.res.resProperty.ulPropTag = PR_RESPONSIBILITY;
        srRecipUnsent.res.resProperty.lpProp = &spvRecipUnsent;
    }
    else
    {
        SRestriction srRecipDefer;

        srRecipDefer.rt = RES_PROPERTY;
        srRecipDefer.res.resProperty.relop = RELOP_EQ;
        srRecipDefer.res.resProperty.ulPropTag = PR_SAMPLE_PER_RECIP_DEFER;
        srRecipDefer.res.resProperty.lpProp = &spvRecipDefer;

        hResult = lpMessage->lpVtbl->GetRecipientTable(
            lpMessage, 0L, &lpTable);

        if (hResult)
        {
            DebugTrace("GetRecipientTable failed in SubmitMessage.\n");
            goto ret;
        }

        hResult = lpTable->lpVtbl->FindRow(lpTable, &srRecipDefer,
            BOOKMARK_BEGINNING, 0);

        /* Check our .2 second timer! */

        sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));

        if (sc == MAPI_W_CANCEL_MESSAGE)
        {
            DebugTrace("Cancelling message delivery.\n");
            goto ret;
        }

        if (GetScode(hResult) != MAPI_E_NOT_FOUND)
        {
            hResult = HrAddDeferred(lpxpl, lpMessage, lpulMsgRef);

            if (HR_FAILED(hResult))
            {
                DebugTrace("HrAddDeferred failed doing a per-recip deferral.\n");
                goto ret;
            }
        }
        else
        {
            hResult = lpTable->lpVtbl->SeekRow(lpTable,
                BOOKMARK_BEGINNING, 0L, NULL);
        }

        /*  Initialize a restriction -- we'll need it soon. */

        spvRecipDefer.Value.b = FALSE;

        srExist.rt = RES_EXIST;
        srExist.res.resExist.ulPropTag = PR_SAMPLE_PER_RECIP_DEFER;

        rgsrOr[0].rt = RES_NOT;
        rgsrOr[0].res.resNot.lpRes = &srExist;

        rgsrOr[1].rt = RES_PROPERTY;
        rgsrOr[1].res.resProperty.relop = RELOP_EQ;
        rgsrOr[1].res.resProperty.ulPropTag = PR_SAMPLE_PER_RECIP_DEFER;
        rgsrOr[1].res.resProperty.lpProp = &spvRecipDefer;

        rgsrAnd[0].rt = RES_PROPERTY;
        rgsrAnd[0].res.resProperty.relop = RELOP_EQ;
        rgsrAnd[0].res.resProperty.ulPropTag = PR_RESPONSIBILITY;
        rgsrAnd[0].res.resProperty.lpProp = &spvRecipUnsent;

        rgsrAnd[1].rt = RES_OR;
        rgsrAnd[1].res.resOr.cRes = 2;
        rgsrAnd[1].res.resOr.lpRes = rgsrOr;

        srRecipUnsent.rt = RES_AND;
        srRecipUnsent.res.resAnd.cRes = 2;
        srRecipUnsent.res.resAnd.lpRes = rgsrAnd;
    }

    /* Check our .2 second timer before attempting to send */

    sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));

    if (sc == MAPI_W_CANCEL_MESSAGE)
    {
        DebugTrace("Cancelling message delivery.\n");
        goto ret;
    }

    /*  If not peer-to-peer, "send message" to our outbound directory. */

    if (!fPeer2Peer)
    {
        BOOL fSent;

        hResult = HrSendOneMessage(lpxpl, lpPropArray,
                lpMessage, 0, lpszMyDir, &fSent);

        if (hResult)
        {
            DebugTrace("Copying message to outbound failed.\n");
            goto ret;
        }
    }

    /*  If we are peer-to-peer, send to all our recipients. */

    else
    {
        /*  Get the recipient table from the message if we haven't already */

        if (!lpTable)
        {
            hResult = lpMessage->lpVtbl->GetRecipientTable(
                lpMessage, 0L, &lpTable);

            if (hResult)
            {
                DebugTrace("GetRecipientTable failed in SubmitMessage.\n");
                goto ret;
            }
        }

        /*  Restrict to all unsent recipients */

        hResult = lpTable->lpVtbl->Restrict(lpTable, &srRecipUnsent, 0L);

        if (hResult)
        {
            DebugTrace("Restriction on recipient table  failed in SubmitMessage.\n");
            goto ret;
        }

        /* Check our .2 second timer! */

        sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));

        if (sc == MAPI_W_CANCEL_MESSAGE)
        {
            DebugTrace("Cancelling message delivery.\n");
            goto ret;
        }

        /*  Send to the recipients which we can reach, and build ADRLISTs of
            the sent and unsent recipients */

        hResult = HrBuildAdrList(lpxpl, lpPropArray, lpMessage, lpTable,
                TRUE, HrSendOneMessage, &lpMyAdrListDone, &lpMyAdrListNotDone);

        if (hResult)
        {
            DebugTrace("HrBuildAdrList failed in SubmitMessage.\n");
            goto ret;
        }

        /*  No error, do we have some recipients? If so, do the ModifyRecipients(). */

        if (lpMyAdrListDone)
        {
            hResult = lpMessage->lpVtbl->ModifyRecipients(lpMessage,
                    MODRECIP_MODIFY, lpMyAdrListDone->lpAdrList);

            if (hResult)
            {
                DebugTrace("ModifyRecipients failed in SubmitMessage.\n");
                goto ret;
            }

            /* Now we need to save changes on the message. */

            hResult = lpMessage->lpVtbl->SaveChanges(lpMessage,
                    lpMyAdrListNotDone ? KEEP_OPEN_READWRITE : 0L);

            if (hResult)
            {
                DebugTrace("SaveChanges failed in SubmitMessage.\n");
                goto ret;
            }
        }

        /*  Check for unsent recipients. If there were any, we need to NDR
            them and (finally) mark them as taken. If there were not any,
            we're really finished and can just go and release the message. */

        if (!lpMyAdrListNotDone)
            goto ret;

        hResult = lpMAPISup->lpVtbl->StatusRecips(lpMAPISup,
                lpMessage, lpMyAdrListNotDone->lpAdrList);

        if (HR_FAILED(hResult))
        {
            DebugTrace("StatusRecips failed in SubmitMessage.\n");
            goto ret;
        }

        /*  StatusRecips killed the ADRLIST so zero out our pointer. */

        lpMyAdrListNotDone->lpAdrList = NULL;

        /* Get rid of the MYADRLISTs. */

        FreeMyAdrList(lpxpl, lpMyAdrListDone);
        FreeMyAdrList(lpxpl, lpMyAdrListNotDone);

        lpMyAdrListDone = lpMyAdrListNotDone = NULL;

        /*  Free the recipient table. */

        lpTable->lpVtbl->Release(lpTable);
        lpTable = NULL;
    }

    /* Check our .2 second timer after attempting to send */

    sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));

    if (sc == MAPI_W_CANCEL_MESSAGE)
    {
        DebugTrace("Cancelling message delivery.\n");
        goto ret;
    }

    /*  At this point we have either:

        a)  If not peer-to-peer, made a single container file in
            the outbound directory
        b)  If peer-to-peer, created a container file in every
            inbound directory we were able to reach (but not all
            of them) -- and have NDR'ed the ones we could not reach

        All that remains to do is to mark all unsent recipients as
        handled, since in the non-peer case the creation of the
        container suffices as "handling" and in the peer case the
        NDR message also does this.
    */

    hResult = lpMessage->lpVtbl->GetRecipientTable(lpMessage, 0L, &lpTable);

    if (hResult)
    {
        DebugTrace("Second GetRecipientTable failed in SubmitMessage.\n");
        goto ret;
    }

    /*  Restrict the recipient table to the remaining unsent */

    hResult = lpTable->lpVtbl->Restrict(lpTable, &srRecipUnsent, 0L);

    if (hResult)
    {
        DebugTrace("Restriction on recipient table failed.\n");
        goto ret;
    }

    /*  Build the ADRLIST of the unsent recipients */

    hResult = HrBuildAdrList(lpxpl, lpPropArray, lpMessage, lpTable,
            TRUE, NULL,  &lpMyAdrListDone, &lpMyAdrListNotDone);

    if (hResult)
    {
        DebugTrace("HrBuildAdrList failed in SubmitMessage.\n");
        goto ret;
    }

    Assert(!lpMyAdrListNotDone);

    /*  No error, do we have some recipients? If so, do the ModifyRecipients(). */

    if (lpMyAdrListDone)
    {
        hResult = lpMessage->lpVtbl->ModifyRecipients(lpMessage,
                MODRECIP_MODIFY, lpMyAdrListDone->lpAdrList);

        if (hResult)
        {
            DebugTrace("ModifyRecipients failed in SubmitMessage.\n");
            goto ret;
        }
    }

    /*  Release the table, we're finished with it */

    UlRelease(lpTable);
    lpTable = NULL;

    /* With the recipient table work done, save changes again. */

    hResult = lpMessage->lpVtbl->SaveChanges(lpMessage, 0L);

    if (hResult)
    {
        DebugTrace("SaveChanges failed in SubmitMessage.\n");
        goto ret;
    }

    PrintfTransportLog(TEXT("End Outbound: %s"),
        ArrayIndex(PR_SAMPLE_DISPLAY_NAME, lpPropArray).Value.LPSZ);

ret:
    /* Free-Up Memory */

    lpxpl->FreeBuffer(lpPropArray);
    lpxpl->FreeBuffer(lpMsgProps);

    /* Get rid of any MYADRLISTs. */

    FreeMyAdrList(lpxpl, lpMyAdrListDone);
    FreeMyAdrList(lpxpl, lpMyAdrListNotDone);

    /* Release any open table */

    UlRelease(lpTable);

    /* Release the spooler's message if need be */

    UlRelease(lpMessage);

    /* Reset upload status if set. If this errors, use the error only
       if no other error had occurred here. */

    if (fUpdatedStatus)
    {
        lpxpl->ulTransportStatus &= ~STATUS_OUTBOUND_ACTIVE;
        (void)HrUpdateTransportStatus(lpxpl, 0L);
    }

    DebugTraceResult(XPL_SubmitMessage, hResult);
    return hResult;

}

/*
 -  XPL_EndMessage
 -
 *  Purpose:
 *      Called by the Spooler to complete transmission of a message.
 *
 *  Parameters:
 *      ulMsgRef            Opaque identifier from SubmitMessage
 *      lpulFlags           Pointer to where the transport should
 *                          store special flags on return. This
 *                          Transport doesn't use any.
 *
 *  Returns:
 *      (HRESULT)           Success.
 *
 *  Operation:
 *      Clears unsigned long status, and returns success.
 */

STDMETHODIMP
XPL_EndMessage(LPXPL lpxpl, ULONG ulMsgRef, ULONG * lpulFlags)
{
    LPDEFMSG lpDefMsg;

    Assert(!IsBadWritePtr(lpulFlags, sizeof(ULONG)));

    *lpulFlags = 0L;

    /* If the ulMsgRef is non zero, look for it in the deferred
       list.  If found, return END_DONT_RESEND to the Spooler.  */

    if (ulMsgRef)
    {
        lpDefMsg = lpxpl->lpDeferredList;

        while (lpDefMsg)
        {
            if (lpDefMsg->ulMsgRef == ulMsgRef)
            {
                *lpulFlags = END_DONT_RESEND;
                break;
            }
        }
    }

    return hrSuccess;
}


/*
 -  HrAddDeferred
 -
 *  Purpose:
 *      Adds the EntryID and ulMsgRef of a message we are deferring
 *      to our list of deferred message.
 *
 *  Parameters:
 *      lpxpl           Transport session
 *      lpMsg           The message we wish to defer
 *      lpulMsgRef      Receives the reference we assign to this message
 *
 *  Returns:
 *      hResult         Indicating Success/Failure
 */

HRESULT
HrAddDeferred(LPXPL lpxpl, LPMESSAGE lpMsg, ULONG *lpulMsgRef)
{
    HRESULT hResult;
    SCODE sc;
    LPDEFMSG lpDefMsg = NULL;
    ULONG cVals;
    LPSPropValue lpEIDProp = NULL;
    static SPropTagArray spta = {1, {PR_ENTRYID}};

    /* Allocate a new DefMsg node */

    sc = lpxpl->AllocateBuffer(sizeof(DEFMSG), (LPVOID *)&lpDefMsg);

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        DebugTrace("Allocation failed in HrAddDeferred.\n");
        goto ret;
    }

    /* Get the EntryID of the message we are deferring */

    hResult = lpMsg->lpVtbl->GetProps(lpMsg, &spta, 0, &cVals, &lpEIDProp);

    if (HR_FAILED(hResult))
    {
        DebugTrace("GetProps failed in HrAddDeferred.\n");
        goto ret;
    }

    Assert(cVals == 1);
    Assert(lpEIDProp);
    Assert(lpEIDProp->ulPropTag == PR_ENTRYID);

    /* We'll make our own copy of the EntryID */

    sc = lpxpl->AllocateMore(lpEIDProp->Value.bin.cb, (LPVOID)lpDefMsg,
            (LPVOID *)&(lpDefMsg->sbinEIDDef.lpb));

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        DebugTrace("Allocation failed in HrAddDeferred.\n");
        goto ret;
    }

    /* Fill in this new node and add it to the list */

    lpDefMsg->sbinEIDDef.cb = lpEIDProp->Value.bin.cb;
    memcpy(lpDefMsg->sbinEIDDef.lpb, lpEIDProp->Value.bin.lpb,
            (UINT)lpDefMsg->sbinEIDDef.cb);

    lpDefMsg->ulMsgRef = ++lpxpl->ulDeferredMsgRef;
    lpDefMsg->lpNext = lpxpl->lpDeferredList;
    lpxpl->lpDeferredList = lpDefMsg;

    lpxpl->fResendDeferred = FALSE;

    *lpulMsgRef = lpDefMsg->ulMsgRef;

ret:
    if (HR_FAILED(hResult))
        lpxpl->FreeBuffer(lpDefMsg);

    lpxpl->FreeBuffer(lpEIDProp);

    DebugTraceResult(HrAddDeferred, hResult);
    return hResult;
}
