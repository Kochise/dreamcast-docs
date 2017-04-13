/*
 -  X P R C V M S G . C
 -
 *  Purpose:
 *      Code to support the MAPI Transport SPI entry points for
 *      message reception.  This module contains the following
 *      SPI entry points:
 *
 *          Poll()
 *          StartMessage()
 *
 *      Additional support functions found here:
 *
 *          HrIMsgFromTextMsg()
 *          HrBuildSenderProps()
 *          HrAddRecipToAdrList()
 *          HrAddRecipToReplyList()
 *          HrMakeSearchKey()
 *          HrGetLine()
 *          FGetTagAndToken()
 *          FileTimeFromSzTime()
 *          SetFromMeFlag()
 *
 *      Also, the Idle() code in XPQUEUE.C will call into this module to
 *      find out if there's any mail to tell SpoolerNotify() about.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "xppch.h"
#include <tnef.h>
#include <stdlib.h>
#include "xpsof.h"
#include "xptxtmsg.h"

/* Local function prototype(s) */

VOID SetFromMeFlag(LPXPL lpxpl, LPMESSAGE lpMsg);


/*
 -  Poll
 -
 *  Purpose:
 *      Called by the Spooler periodically in its idle loop. Also called from
 *      the Idle() entry point code.
 *
 *  Parameters:
 *      lpulIncoming        Pointer to a ULONG.
 *
 *  Returns:
 *      *lpulIncoming       Nonzero if any messages are found;
 *                          Zero if no messages were found.
 *
 *  Operation:
 *      This routine uses FindFirst/FindNext to look for message container
 *      files in the inbound directory. Because its FIND_DATA structure and
 *      the associated Handle is contained in the session structure, it's
 *      easy to keep context and pass it along to StartMessage().
 *
 *      Because it can be called from multiple places, and there's no
 *      guarantee that StartMessage() will be called between the time we
 *      signal the presence of inbound mail and the next time we're called,
 *      we maintain a boolean in the session structure which we set to TRUE
 *      when we find a message, and which StartMessage() sets to FALSE after
 *      processing that message. If we see it as TRUE when called, we return
 *      immediately with *lpulIncoming set.
 *
 *      Otherwise, we do a FindNext if a find handle is open. If it fails, we
 *      close the handle.
 *
 *      If we have no open handle (either because one wasn't open or because
 *      we just closed one), we do a FindFirst.
 *
 *      If we find a message container file, we set the boolean and
 *      *lpulIncoming and return. Else we close the find handle.
 *
 *      This function always returns SUCCESS_SUCCESS.
 */

STDMETHODIMP
XPL_Poll(LPXPL lpxpl, ULONG * lpulIncoming)
{
    HANDLE *lpPollHandle;
    LPWIN32_FIND_DATA lpFindData;
    LPMAPISUP lpMAPISup;
    LPSPropValue lpPropArray = lpxpl->lpPropArray;
    BOOL fFound = FALSE;
    DWORD dwIgnoreAttrs =
    FILE_ATTRIBUTE_READONLY |
    FILE_ATTRIBUTE_SYSTEM |
    FILE_ATTRIBUTE_DIRECTORY |
    FILE_ATTRIBUTE_TEMPORARY;

    lpPollHandle = &lpxpl->hInFindHandle;
    lpFindData = &lpxpl->wfdInFindData;

    lpMAPISup = lpxpl->lpMAPISup;

    /* Start out with default of no incoming message */

    *lpulIncoming = 0;

    /* Is inbound enabled for this session? */

    if (!(lpxpl->ulTransportStatus & STATUS_INBOUND_ENABLED))
        goto ret;

    /* See if we found one on a previous pass through here and haven't
       done a StartMessage() yet... */

    if (lpxpl->fFoundInMessage)
    {
        *lpulIncoming = 1;
        goto ret;
    }

    /*  One of the following is now true:

        A)  We have a search already active, use FindNextFile.
            If it fails, we will want to restart the search
            (in case something appeared in the search behind
            us.

        B)  We don't have a search active, use FindFirstFile.
    */

    /* Try the active search */

    if (*lpPollHandle != INVALID_HANDLE_VALUE)
    {
        fFound = FindNextFile(*lpPollHandle, lpFindData);

        /* If we fail, close the old search so we can start
           a new one below. */

        if (!fFound)
        {
            FindClose(*lpPollHandle);
            *lpPollHandle = INVALID_HANDLE_VALUE;
        }
    }

    /* If there was no search or if the old one was just closed above */

    if (*lpPollHandle == INVALID_HANDLE_VALUE)
    {
        HANDLE hFindT;
        TCHAR chFileName[MAX_PATH];

        /* Copy the directory name. Note that we trust the value in the
           profile to be correct, since the UI should have enforced a
           syntax that included a trailing : or \ in the spec. */

        lstrcpy(chFileName,
            (ArrayIndex(PR_SAMPLE_INBOUND_DIR, lpPropArray)).Value.LPSZ);

        lstrcat(chFileName, TEXT("TNF*.TMP"));

        hFindT = FindFirstFile(chFileName, lpFindData);

        /* If nothing's found, we're done here. */

        if (hFindT == INVALID_HANDLE_VALUE)
            goto ret;

        /* Found something, continue along. */

        fFound = TRUE;
        *lpPollHandle = hFindT;
    }

    /*
        Here on a match. Exclude unwanted files.

        Any match with DIRECTORY, READONLY, SYSTEM or TEMPORARY attribute
        is ignored. Keep trying until we exhaust the current supply or we
        find a file without these attributes. Also, ignore files smaller
        than some arbitrary size, they're probably trash.
    */

    while (fFound)
    {
        /*  We found a file. Does it have any of the attributes we
            want to ignore? If not, get out. If so, try another. */

#define MIN_USEFUL_FILESIZE ((DWORD) 64)

        if ((!((lpFindData)->dwFileAttributes & dwIgnoreAttrs)) &&
            ((lpFindData->nFileSizeHigh != 0) ||
                (lpFindData->nFileSizeLow >= MIN_USEFUL_FILESIZE)))
            break;

        fFound = FindNextFile(*lpPollHandle, lpFindData);
    }

    if (fFound)
        lpxpl->fFoundInMessage = TRUE;
    else
    {
        FindClose(*lpPollHandle);
        *lpPollHandle = INVALID_HANDLE_VALUE;
    }

ret:
    if (lpxpl->fFoundInMessage)
    {
        /*  Got a hit. If fFound is set, we found it this time. If fFound
            is not set, we got it before and we were called again before
            StartMessage(). */

        *lpulIncoming = 1;
        DebugTrace("XPL_Poll returns *lpulIncoming=%lx\n", *lpulIncoming);
    }
    else if (lpxpl->ulTransportStatus & STATUS_INBOUND_FLUSH)
    {
        lpxpl->ulTransportStatus &= ~STATUS_INBOUND_FLUSH;
        (void)HrUpdateTransportStatus(lpxpl, 0L);
    }
    return hrSuccess;
}


/*
 -  StartMessage
 -
 *  Purpose:
 *      Called by the Spooler for receipt of an inbound message. This sequence
 *      of events is set off by a SpoolerNotify (NOTIFY_NEWMAIL) or a Poll()
 *      returning *lpulIncoming != 0.
 *
 *  Parameters:
 *      ulFlags             Flags from the Spooler. Currently
 *                          there are no StartMessage() flags
 *                          defined in the MAPI 1.0 TSPI.
 *      lpMessage           Pointer to message object into which
 *                          the Spooler wants the transport to
 *                          store the incoming message.
 *      lpulMsgRef          Pointer to where the transport should
 *                          store a unsigned long for use in
 *                          identifying TransportNotify() message
 *                          events. Initialized to 0 by the
 *                          Spooler. We don't do anything with
 *                          message events in this transport, so
 *                          we don't store anything there.
 *
 *  Returns:
 *      (HRESULT)           MAPI_E_BUSY if the Spooler calls
 *                          here again while we're busy, else
 *                          errors encountered if any.
 *      (*lpMessage)        Contains the new input message if any.
 *
 *  Operation:
 *      Checks for the result of a FindFirst/FindNext operation in the
 *      session's FIND_DATA buffer. If none, exit without changing the input
 *      message (this should result in the new message being destroyed when
 *      the Spooler releases its object).
 *
 *      If a file was found, attempt to open it. If the open fails and the
 *      reason is not attributable to network locking, return the error; if
 *      attributable to network locking (like if a peer's transmit code is
 *      writing a container file), return no error. In either case, exit
 *      without changing the input message.
 *
 *      Open a stream interface on the input message file.  Pass this off
 *      to HrIMsgFromTxtMsg() to convert all the textized envelope properties
 *      to SPropValues which are then set on the spoolers IMessage.  When
 *      we return, the input stream will be pointing to the beginning of
 *      the embedded TNEF encapsulation in the input message file.  Make
 *      the appropriate calls to TNEF to extract the properties from the
 *      encapsulation and set them on the message.
 *
 *      Finally, SaveChanges() on the Spooler's message to retain the result,
 *      delete the container file, and reset the "found message" flag for the
 *      benefit of Poll().
 */

STDMETHODIMP
XPL_StartMessage(LPXPL lpxpl,
    ULONG ulFlags,
    LPMESSAGE lpMessage,
    ULONG * lpulMsgRef)
{
    LPWIN32_FIND_DATA lpFindData;
    LPSPropValue lpMyIDArray = NULL;
    LPSPropValue lpPropArray = NULL;
    SPropValue rgDelegateProps[3];
    SPropValue spvTime;
    LPSPropProblemArray lpProblems = NULL;
    TCHAR rgchFileName[MAX_PATH];
    LPTSTR lptMyDir;
    HRESULT hResult = 0;
    SCODE sc = 0;
    BOOL fUpdatedStatus = FALSE;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    WORD wKey = 0;
    SPropTagArray sptExcludeNone = {0};
    LPITNEF lpTnef = (LPITNEF) NULL;
    LPSTREAM lpSof = (LPSTREAM) NULL;
    LPSTREAM lpXPSof = (LPSTREAM) NULL;
    LPSTnefProblemArray lptpa = NULL;

    /* Reset our .2 second timer before starting. */

    HrCheckSpoolerYield(lpMAPISup, TRUE);

    /* Do this first so we know at exit time if we tried to open a file */

    rgchFileName[0] = '\0';

    /* Simple re-entrancy test. Should never happen anyway. */

    if (lpxpl->ulTransportStatus & STATUS_INBOUND_ACTIVE)
    {
        hResult = ResultFromScode(MAPI_E_BUSY);
        DebugTrace("XPL_StartMessage reentrancy test failed\n");
        goto ret;
    }

    /* Signal that we're downloading. */

    *lpulMsgRef = 1L;           /* This is good enough. */
    lpxpl->ulTransportStatus |= STATUS_INBOUND_ACTIVE;
    hResult = HrUpdateTransportStatus(lpxpl, 0L);
    if (hResult)
    {
        DebugTrace("Update of status row failed\n");
        goto ret;
    }
    fUpdatedStatus = TRUE;

    /* Get the current findfirst/findnext buffer */

    lpFindData = &lpxpl->wfdInFindData;

    /* Is there actually a message available? If not, go away. */

    if (!lpxpl->fFoundInMessage)
        goto ret;

    sc = ScCopySessionProps(lpxpl, &lpPropArray, &lpMyIDArray);

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        goto ret;
    }

    /* Build file name of incoming message */

    lptMyDir = ArrayIndex(PR_SAMPLE_INBOUND_DIR, lpPropArray).Value.LPSZ;

    lstrcpy(rgchFileName, lptMyDir);
    lstrcat(rgchFileName, lpFindData->cFileName);

    PrintfTransportLog(TEXT("Start Incoming: %s"), rgchFileName);

    hResult = OpenStreamOnFile(lpxpl->AllocateBuffer, lpxpl->FreeBuffer,
        STGM_READ, rgchFileName, NULL, &lpSof);

    if (hResult)
    {
        sc = GetScode(hResult);
        DebugTrace("OpenStreamOnFile() failed in StartMessage()\n");
        PrintfTransportLog(TEXT("OpenStreamOnFile(%s) returns %lx"), rgchFileName, sc);

        /*  If "Access Denied" just don't do anything.
            It's usually a situation that will clear up (when another
            instance of this transport closes the msg file or when the
            other system comes online) */

        if (sc == MAPI_E_NO_ACCESS)
            hResult = hrSuccess;

        /*  If "Not Found", clear fFoundInMessage so that we'll do a
            FindNext. */

        if (sc == MAPI_E_NOT_FOUND)
            lpxpl->fFoundInMessage = FALSE;

        goto ret;
    }

    /* Wrap the Stream-On-File object in our buffered wrapper. */

    hResult = HrWrapStreamOnFile(lpxpl->AllocateBuffer, lpxpl->FreeBuffer,
            XPSOF_READ, lpSof, &lpXPSof);

    if (HR_FAILED(hResult))
    {
        DebugTrace("HrWrapStreamOnFile() failed\n");
        goto ret;
    }

    /* Check our .2 second timer before attempting to receive */

    sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));
        
    if (sc == MAPI_W_CANCEL_MESSAGE)
    {
        DebugTrace("Cancelling message download.\n");
        goto ret;
    }

    hResult = HrIMsgFromTextMsg(lpxpl, lpPropArray, lpMessage, lpXPSof);

    if (HR_FAILED(hResult))
    {
        DebugTrace("HrIMsgFromTextMsg() failed\n");
        goto ret;
    }

    /* Check our .2 second timer again. */

    sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));
        
    if (sc == MAPI_W_CANCEL_MESSAGE)
    {
        DebugTrace("Cancelling message download.\n");
        goto ret;
    }

    /* The 0x01AF if a key used to identify the TNEF.  A real transport
       should generate a pseudo-random sequence for this field. */

    hResult = OpenTnefStream(lpxpl->lpMAPISup, lpXPSof, 
            TEXT("MAPIMAIL.DAT"), TNEF_DECODE, lpMessage, 0x01AF, &lpTnef);

    if (HR_FAILED(hResult))
    {
        DebugTrace("OpenTNEF() failed.\n");
        goto ret;
    }

    /* Extract properties from the incomming message and add them to
       the target message. */

    hResult = lpTnef->lpVtbl->ExtractProps(lpTnef,
        TNEF_PROP_EXCLUDE, &sptExcludeNone, &lptpa);
    lpxpl->FreeBuffer(lptpa);
    if (HR_FAILED(hResult))
    {
        DebugTrace("GetTNEFProps() failed.\n");
        goto ret;
    }

    /* Check our .2 second timer again. */

    sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));
        
    if (sc == MAPI_W_CANCEL_MESSAGE)
    {
        DebugTrace("Cancelling message download.\n");
        goto ret;
    }

    /* All the properties have been copied over. Set the PR_RECEIVED_BY
       delegate properties (all the others were set by the transmitter) */

    if (lpMyIDArray)
    {
        Assert(!IsBadReadPtr(lpMyIDArray, 3 * sizeof(SPropValue)));
        Assert(lpMyIDArray[0].ulPropTag == PR_SENDER_ENTRYID);
        Assert(lpMyIDArray[1].ulPropTag == PR_SENDER_NAME);
        Assert(lpMyIDArray[2].ulPropTag == PR_SENDER_SEARCH_KEY);

        memcpy(rgDelegateProps, lpMyIDArray, 3 * sizeof(SPropValue));
        rgDelegateProps[0].ulPropTag = PR_RECEIVED_BY_ENTRYID;
        rgDelegateProps[1].ulPropTag = PR_RECEIVED_BY_NAME;
        rgDelegateProps[2].ulPropTag = PR_RECEIVED_BY_SEARCH_KEY;

        /* At this point we have all the delegate properties set. Put them into
           the old message and then we'll just get them on the CopyTo(). */

        hResult = lpMessage->lpVtbl->SetProps(lpMessage, 3,
            rgDelegateProps, &lpProblems);

        if (hResult)
        {
            DebugTrace("SetProps of Receiver ID to message failed.\n");
            goto ret;
        }

        if (lpProblems)
        {
            /* If there were problems, let's dump them to the debugger. */

            DebugTraceProblems("XPL_StartMessage", lpProblems);

            lpxpl->FreeBuffer(lpProblems);
            lpProblems = NULL;
        }
    }

    /* Set the Received Time to be the last-modified time on the file. */

    spvTime.ulPropTag = PR_MESSAGE_DELIVERY_TIME;
    spvTime.Value.ft = lpFindData->ftLastWriteTime;

    hResult = lpMessage->lpVtbl->SetProps(lpMessage, 1, &spvTime, NULL);

    if (hResult)
    {
        DebugTrace("SetProps of PR_MESSAGE_DELIVERY_TIME failed.\n");
        goto ret;
    }

    /*  Finished with all properties and recipients now, SaveChanges
        on the message. */

    /* Check our .2 second timer again. */

    sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));
        
    if (sc == MAPI_W_CANCEL_MESSAGE)
    {
        DebugTrace("Cancelling message download.\n");
        goto ret;
    }

    hResult = lpMessage->lpVtbl->SaveChanges(lpMessage, 0L);

    if (hResult)
    {
        DebugTrace("SaveChanges on incoming message failed.\n");
        goto ret;
    }

    /* Finally, set the found message flag so we'll get another file. */

    lpxpl->fFoundInMessage = FALSE;

ret:
    /* Log end of incoming if we logged start. */

    if (*rgchFileName)
        PrintfTransportLog(TEXT("End Incoming: %s"), rgchFileName);

    UlRelease(lpTnef);
    UlRelease(lpXPSof);
    UlRelease(lpSof);

    /* If we got the message into the store, delete the inbound file. */

    if (!(HR_FAILED (hResult)) && *rgchFileName)
        (void)DeleteFile(rgchFileName);

    /* Release the prop tag array and/or problem array if any */

    lpxpl->FreeBuffer(lpPropArray);
    lpxpl->FreeBuffer(lpMyIDArray);

    /* Reset download status if set. */

    if (fUpdatedStatus)
    {
        lpxpl->ulTransportStatus &= ~STATUS_INBOUND_ACTIVE;
        (void)HrUpdateTransportStatus(lpxpl, 0L);
    }

    DebugTraceResult(XPL_StartMessage, hResult);
    return hResult;
}


/*
 -  HrIMsgFromTextMsg
 -
 *  Purpose:
 *      Called by StartMessage() to read a text formatted message file,
 *      containing a TNEF encapsulation, and converting it into a
 *      MAPI Message.  The TNEF DLL is used to decode the binary portion
 *      of this message into all the correct IMessage components.
 *
 *  Parameters:
 *      lpxpl               Pointer to Transport Logon object
 *      lpPropArray         Array of the transports logon properties
 *      lpMessage           Message to receive into
 *      lpSof               Pointer to the stream interface
 *
 *  Returns:
 *      hr                  Indicating Success/Failure
 *
 *  Operation:
 *      Read each Tag out of the text file and process its Token according
 *      to my rules for the Tag ID.  PR_SUBJECT and PR_BODY are automatically
 *      streamed into the message, PR_CLIENT_SUBMIT_TIME, PR_PRIORITY,
 *      PR_SENDER_NAME, and PR_SENDER_ENTRYID are added with SetProps().
 *      All To: and Cc: recipients are added by building an AdrList
 *      and doing a ModifyRecipients() on the message.  When we're finished
 *      here, the file pointer in the input stream will (hopefully) be
 *      left pointing to the start of the TNEF encapsulation.
 */

HRESULT
HrIMsgFromTextMsg(LPXPL lpxpl, LPSPropValue lpPropArray, LPMESSAGE lpMessage, LPSTREAM lpSof)
{
    SCODE sc;
    HRESULT hr = hrSuccess;
    BOOL fHaveTagAndToken = FALSE;
    TCHAR szLine[MAX_LINE];
    ULONG cbRead;
    ULONG ulTag;
    LPTSTR lpszToken;
    ULONG cValues = 0;
    LPSPropValue lpMsgProps = NULL;
    LPMYADRLIST lpMyRecipList = NULL;
    LPTSTR lpszAddrType;
    LPTSTR lpszReplyNames = NULL;
    ULONG cbReplyEntryList = 0;
    LPFLATENTRYLIST lpReplyEntryList = NULL;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;

    lpszAddrType = ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ;

    sc = lpxpl->AllocateBuffer(MAX_TXTMSG_PROPS * sizeof(SPropValue),
            &lpMsgProps);

    if (sc)
    {
        hr = ResultFromScode(sc);
        DebugTrace("Allocation failed.\n");
        goto ret;
    }

    memset(lpMsgProps, 0, MAX_TXTMSG_PROPS * sizeof(SPropValue));

    sc = lpxpl->AllocateBuffer(sizeof(MYADRLIST), &lpMyRecipList);

    if (sc)
    {
        hr = ResultFromScode(sc);
        DebugTrace("Allocation failed.\n");
        goto ret;
    }

    memset(lpMyRecipList, 0, sizeof(MYADRLIST));

    while (TRUE)
    {
        /* fHaveTagAndToken gets set only when we return from
           HrGetStreamedProp and the call actually gets
           the next tagged line and tokenizes it for us. */

        if (!fHaveTagAndToken)
        {
            hr = HrGetLine(lpSof, MAX_LINE, szLine, &cbRead);

            if (hr)
                break;

            if (szLine[0] == '\0')
                continue;
        }

        if (fHaveTagAndToken || FGetTagAndToken(szLine, &ulTag, &lpszToken))
        {
            fHaveTagAndToken = FALSE;

            /* Check our .2 second timer again. */

            sc = GetScode(HrCheckSpoolerYield(lpMAPISup, FALSE));
        
            if (sc == MAPI_W_CANCEL_MESSAGE)
            {
                DebugTrace("Cancelling message download.\n");
                goto ret;
            }

            switch (ulTag)
            {
            case tagFrom:
            case tagRepresenting:
                /* Create an addressing triplet (DisplayName, EntryID,
                   SearchKey) from this line and add these properties
                   to the array of props. */

                hr = HrBuildSenderProps(lpxpl, lpPropArray, ulTag, lpszToken,
                        lpszAddrType, lpMessage, &cValues, lpMsgProps);

                if (hr)
                {
                    DebugTrace("HrBuildSenderProps() failed.\n");
                    goto ret;
                }
                break;

            case tagReplyTo:
                hr = HrAddRecipToReplyList(lpxpl, lpszToken, lpszAddrType,
                    &lpszReplyNames, &cbReplyEntryList, &lpReplyEntryList);

                if (hr)
                    goto ret;
                break;

            case tagDate:
                lpMsgProps[cValues].ulPropTag = PR_CLIENT_SUBMIT_TIME;
                FileTimeFromSzTime(lpszToken, &lpMsgProps[cValues++].Value.ft);
                break;

            case tagTo:
            case tagCc:
                hr = HrAddRecipToAdrList(lpxpl, (LONG) ulTag - tagDate, lpszToken,
                    lpszAddrType, lpMyRecipList);
                if (hr)
                    goto ret;
                break;

            case tagSubject:
            case tagTextItem:
                hr = HrGetStreamedProp(lpxpl, lpSof, lpMessage,
                        ((ulTag == tagSubject) ? PR_SUBJECT : PR_BODY),
                        &cValues, lpMsgProps, szLine, &ulTag, &lpszToken);

                if (HR_FAILED(hr))
                    goto ret;

                if(S_OK ==GetScode(hr))
                    fHaveTagAndToken = TRUE;
                break;

            case tagPrioLow:
            case tagPrioNormal:
            case tagPrioUrgent:
                lpMsgProps[cValues].ulPropTag = PR_PRIORITY;
                lpMsgProps[cValues++].Value.l = tagPrioNormal - ulTag;
                break;

            case tagFileItem:
                goto ret;

            case tagMessage:
            case tagBcc:
            case tagContents:
            default:
                break;
            }   /* end switch() */
        }       /* end if()     */
    }           /* end while()  */

ret:
    if (lpszReplyNames && lpReplyEntryList)
    {
        lpMsgProps[cValues].ulPropTag = PR_REPLY_RECIPIENT_NAMES;
        lpMsgProps[cValues++].Value.LPSZ = lpszReplyNames;

        lpMsgProps[cValues].ulPropTag = PR_REPLY_RECIPIENT_ENTRIES;
        lpMsgProps[cValues].Value.bin.cb = cbReplyEntryList;
        lpMsgProps[cValues++].Value.bin.lpb = (LPBYTE) lpReplyEntryList;
    }

    if (cValues)
        lpMessage->lpVtbl->SetProps(lpMessage, cValues, lpMsgProps, NULL);

    if (lpMyRecipList && lpMyRecipList->lpAdrList)
    {
        hr = lpMessage->lpVtbl->ModifyRecipients(lpMessage,
            MODRECIP_ADD, lpMyRecipList->lpAdrList);

        FreeMyAdrList(lpxpl, lpMyRecipList);

        if (hr)
            DebugTrace("ModifyRecipients failed.\n");
    }
    else
        lpxpl->FreeBuffer(lpMyRecipList);

    lpxpl->FreeBuffer(lpMsgProps);
    lpxpl->FreeBuffer(lpszReplyNames);
    lpxpl->FreeBuffer(lpReplyEntryList);

    DebugTraceResult(HrIMsgFromTextMsg(), hr);

    return hr;
}


/*
 -  HrBuildSenderProps
 -
 *  Purpose:
 *      Creates the 5 identity properties: PR_***_SEARCH_KEY,
 *      PR_***_NAME, PR_***_ENTRYID, PR_***_EMAIL_ADDRESS, 
 *      PR_***_ADDRTYPE, where *** is either SENDER or
 *      SENT_REPRESENTING.
 *
 *  Parameters:
 *      lpxpl               The transports logon object
 *      lpPropArray         The session logon properties
 *      ulTag               Either tagFrom or tagRepresenting
 *      lpszToken           Display name and address for triplet
 *      lpszAddrType        This transports address type
 *      lpMessage           The spoolers IMessage object
 *      lpcValues           Count of and index into lpMsgProps
 *      lpMsgProps          Array of message properties we are building
 *
 *  Returns:
 *      hr                  Indicating Success/Failure
 */

HRESULT
HrBuildSenderProps(LPXPL lpxpl,
    LPSPropValue lpPropArray,
    ULONG ulTag,
    LPTSTR lpszToken,
    LPTSTR lpszAddrType,
    LPMESSAGE lpMessage,
    ULONG * lpcValues,
    LPSPropValue lpMsgProps)
{
    SCODE sc;
    HRESULT hr;
    LPTSTR lpszDisplayName = NULL;
    LPTSTR lpszAddress = NULL;
    LPTSTR lpsz;
    ULONG cbEntryID = 0;
    LPBYTE lpEntryID = NULL;
    LPBYTE lpb = NULL;
    ULONG cbSK;
    LPBYTE lpSearchKey;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    ULONG cValues = *lpcValues;

    lpsz = strtok(lpszToken, "[");

    sc = lpxpl->AllocateMore(lstrlen(lpsz) + 1,
        lpMsgProps, &lpszDisplayName);

    if (sc)
    {
        hr = ResultFromScode(sc);
        DebugTrace("AllocateMore failed.\n");
        goto ret;
    }

    lstrcpy(lpszDisplayName, lpsz);

    lpsz = strtok(NULL, "]");

    sc = lpxpl->AllocateMore(lstrlen(lpsz) + 1,
        lpMsgProps, &lpszAddress);

    if (sc)
    {
        hr = ResultFromScode(sc);
        DebugTrace("AllocateMore failed.\n");
        goto ret;
    }

    lstrcpy(lpszAddress, lpsz);

    /* Create OneOff Entry ID for Sender/Delegate */

    hr = lpMAPISup->lpVtbl->CreateOneOff(lpMAPISup,
        lpszDisplayName, lpszAddrType, lpszAddress, 0,
        &cbEntryID, (LPENTRYID FAR *) &lpEntryID);

    if (hr)
    {
        DebugTrace("CreateOneOff() failed.\n");
        goto ret;
    }

    /* Chain the EntryID to the lpMsgProp block */

    sc = lpxpl->AllocateMore(cbEntryID, lpMsgProps, &lpb);

    if (sc)
    {
        hr = ResultFromScode(sc);
        DebugTrace("AllocateMore failed.\n");
        goto ret;
    }

    if (cbEntryID)
        memcpy(lpb, lpEntryID, (size_t) cbEntryID);

    lpxpl->FreeBuffer(lpEntryID);
    lpEntryID = NULL;

    /* Make the PR_***_SEARCH_KEY */

    hr = HrMakeSearchKey(lpxpl, lpMsgProps, lpszAddrType,
        lpszAddress, &cbSK, &lpSearchKey);

    if (hr)
    {
        DebugTrace("HrMakeSearchKey() failed.\n");
        goto ret;
    }

    if (ulTag == tagFrom)
    {
        lpMsgProps[cValues].ulPropTag = PR_SENDER_NAME;
        lpMsgProps[cValues + 1].ulPropTag = PR_SENDER_ENTRYID;
        lpMsgProps[cValues + 2].ulPropTag = PR_SENDER_SEARCH_KEY;
        lpMsgProps[cValues + 3].ulPropTag = PR_SENDER_ADDRTYPE;
        lpMsgProps[cValues + 4].ulPropTag = PR_SENDER_EMAIL_ADDRESS;

        if (!lstrcmpi(lpszAddress,
                ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS,
                    lpPropArray).Value.LPSZ))
            SetFromMeFlag(lpxpl, lpMessage);
    }
    else
    {
        Assert(ulTag == tagRepresenting);
        lpMsgProps[cValues].ulPropTag = PR_SENT_REPRESENTING_NAME;
        lpMsgProps[cValues + 1].ulPropTag = PR_SENT_REPRESENTING_ENTRYID;
        lpMsgProps[cValues + 2].ulPropTag = PR_SENT_REPRESENTING_SEARCH_KEY;
        lpMsgProps[cValues + 3].ulPropTag = PR_SENT_REPRESENTING_ADDRTYPE;
        lpMsgProps[cValues + 4].ulPropTag = PR_SENT_REPRESENTING_EMAIL_ADDRESS;
    }

    lpMsgProps[cValues++].Value.LPSZ = lpszDisplayName;
    lpMsgProps[cValues].Value.bin.cb = cbEntryID;
    lpMsgProps[cValues++].Value.bin.lpb = lpb;
    lpMsgProps[cValues].Value.bin.cb = cbSK;
    lpMsgProps[cValues++].Value.bin.lpb = lpSearchKey;
    lpMsgProps[cValues++].Value.LPSZ = lpszAddrType;
    lpMsgProps[cValues++].Value.LPSZ = lpszAddress;

    *lpcValues = cValues;

ret:
    lpxpl->FreeBuffer(lpEntryID);

    DebugTraceResult(HrBuildSenderProps(), hr);
    return hr;
}


/*
 -  HrGetStreamedProp
 -
 *  Purpose:
 *      Reads either the PR_BODY or PR_SUBJECT from the message file and
 *      adds it to the spoolers IMessage.
 *
 *  Parameters:
 *      lpSof               The stream we are reading the message from
 *      lpMsg               The spoolers IMessage we are building up
 *      ulPropTag           Either PR_SUBJECT or PR_BODY
 *      lpcValues           Current size of the lpMsgProps array
 *      lpMsgProps          The message property array we are building
 *      lpszLine            Char array we use to read lines into
 *      lpulTag             The text file tag we return as a side effect
 *      lppszToken          The token we return as a side effect
 *
 *  Returns:
 *      hr                  Indicating Success/Failure
 *
 *  10/5/95 the functon can return S_FALSE when the call to OpenProperty fails.
 *          in this case the property still gets set using SetProps, but we don't
 *          get the next token for the caller. So S_FALSE is to inform the
 *          caller that we didn't get token for him and he has to do it himself.
 */

HRESULT
HrGetStreamedProp(LPXPL lpxpl,
    LPSTREAM lpSof,
    LPMESSAGE lpMsg,
    ULONG ulPropTag,
    ULONG * lpcValues,
    LPSPropValue lpMsgProps,
    LPTSTR lpszLine,
    ULONG * lpulTag,
    LPTSTR * lppszToken)
{
    SCODE sc;
    HRESULT hr;
    LPSTREAM lpStrm = NULL;
    LPTSTR lpsz = NULL;
    ULONG cbCRLF = lstrlen(szCRLF);
    ULONG cbRead;
    ULONG cbWritten;

    #define cbSubjMax 4096
    LPSTR szSubj = NULL;

    sc = lpxpl->AllocateBuffer(cbSubjMax, &szSubj);
    if (sc)
    {
        hr = ResultFromScode(sc);
        DebugTrace("Allocation failed.\n");
        goto ret;
    }

    *szSubj = '\0';

    hr = HrGetLine(lpSof, MAX_LINE, lpszLine, &cbRead);

    if (hr)
    {
        DebugTrace("HrGetLine failed.\n");
        goto ret;
    }

    if (ulPropTag == PR_SUBJECT)
    {
        /* Once in the context of the subject, go until we reach the
           next tag.  Then return and process the next tag and token */

        UINT cbCurrentSubj = 0;
        while (!FGetTagAndToken(lpszLine, lpulTag, lppszToken))
        {
            if(cbCurrentSubj < cbSubjMax)
            {
                cbCurrentSubj += lstrlen(lpszLine);
                
                if(cbCurrentSubj < cbSubjMax)
                    lstrcat(szSubj, lpszLine);
            }
            
            hr = HrGetLine(lpSof, MAX_LINE, lpszLine, &cbRead);
                
            if (hr)
                goto ret;
        }

        /* this is in order to get inside the 'if' clause after OpenProperty*/
        hr = 1;
    }
    else
    {
    /* If we fail to open a stream on the property, then slam
       this line into the property array and break outta here */

    hr = lpMsg->lpVtbl->OpenProperty(lpMsg, ulPropTag,
        (LPIID) &IID_IStream, 0, MAPI_CREATE | MAPI_MODIFY,
        (LPUNKNOWN *) &lpStrm);
    }

    if (hr)
    {
        LPSTR szBuf = (ulPropTag == PR_SUBJECT) ? szSubj : lpszLine;
        sc = lpxpl->AllocateMore(lstrlen(szBuf) + 1, lpMsgProps, &lpsz);

        if (sc)
        {
            hr = ResultFromScode(sc);
            DebugTrace("Allocation failed.\n");
            goto ret;
        }

        lstrcpy(lpsz, szBuf);
        lpMsgProps[*lpcValues].ulPropTag = ulPropTag;
        lpMsgProps[(*lpcValues)++].Value.LPSZ = lpsz;

        hr = (ulPropTag == PR_SUBJECT) ? hrSuccess : ResultFromScode(S_FALSE);
        goto ret;
    }

    /* Once we're in the context of the body, the only
       valid Tag is the TNEF File Item Tag.  So, we
       ignore all other message text lines that may
       contain a Tag (by chance). */

    while (TRUE)
    {
        FGetTagAndToken(lpszLine, lpulTag, lppszToken);

        if ((*lpulTag == tagFileItem) &&
            !lstrcmp(*lppszToken, "MESSAGE.TNF"))
            break;

        TraceFailedWrite(hr = lpStrm->lpVtbl->Write(lpStrm, lpszLine,
                lstrlen(lpszLine), &cbWritten), ret);

        if (cbRead < MAX_LINE - 1)
        {
            TraceFailedWrite(lpStrm->lpVtbl->Write(lpStrm,
                    szCRLF, cbCRLF, &cbWritten), ret);
        }

        hr = HrGetLine(lpSof, MAX_LINE, lpszLine, &cbRead);

        if (hr)
            break;
    }


ret:
    UlRelease(lpStrm);

    lpxpl->FreeBuffer(szSubj);

    DebugTraceResult(HrGetStreamedProp(), hr);
    return hr;
}


/*
 -  HrAddRecipToAdrList
 -
 *  Purpose:
 *      Called by HrIMsgFromTextMsg() to add a single recipient to the
 *      AdrList.  Pre-allocates space (cMaxEntries) for 10 AdrEntrys the
 *      first time called.  If all cMaxEntries slots are filled, then we
 *      ReAlloc for (cMaxEntries + cMaxEntries/2) more slots and continue
 *      adding the recipient.  New memory is allocated for the attributes
 *      passed in and chained-up to the rgProps array.
 *
 *  Parameters:
 *      lpxpl           Needed for access to support obj and mem allocators
 *      ulRecipType     MAPI_TO or MAPI_CC
 *      lpszNameAddr    recipient token (Format: Display Name[email-address] )
 *      lpszAddrType    This transports Address Type
 *      lpMyAdrList     Pointer to the Recipient List
 *
 *  Returns:
 *      hr              Indicating Suucess/Failure
 */

HRESULT
HrAddRecipToAdrList(LPXPL lpxpl, LONG lRecipType,
    LPTSTR lpszNameAddr, LPTSTR lpszAddrType, LPMYADRLIST lpMyAdrList)
{
    HRESULT hr = hrSuccess;
    SCODE sc;
    BOOL fAlloc = FALSE;
    BOOL fReAlloc = FALSE;
    ULONG cb;
    ULONG cMaxEntries;
    LPADRLIST lpAdrList = NULL;
    LPSPropValue rgProps = NULL;
    LPTSTR lpsz;
    LPTSTR lpszDisplayName = NULL;
    LPTSTR lpszAddress = NULL;
    LPTSTR lpszAddrTypeT = NULL;
    ULONG cbEntryID = 0;
    LPBYTE lpEntryID = NULL;
    LPBYTE lpb = NULL;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    enum enumRecipProps
    {
        iRecipType,
        iDisplayName,
        iAddrType,
        iAddress,
        iEntryID,
        cRecipProps
    };

    /* Determine if we need to Allocate or ReAllocate memory */

    if (!lpMyAdrList->cMaxEntries)
    {
        /* First time in; list should be NULL */
        Assert(lpMyAdrList->lpAdrList == NULL);
        fAlloc = TRUE;
        cMaxEntries = 10;
    }
    else if (lpMyAdrList->lpAdrList &&
        (lpMyAdrList->lpAdrList->cEntries == lpMyAdrList->cMaxEntries))
    {
        /* List is full; we need to ReAlloc */
        fReAlloc = TRUE;
        cMaxEntries = lpMyAdrList->cMaxEntries + lpMyAdrList->cMaxEntries / 2;
    }
    else
    {
        /* List exists and is not full; just point to it */
        Assert(lpMyAdrList->lpAdrList);
        Assert(lpMyAdrList->lpAdrList->cEntries < lpMyAdrList->cMaxEntries);
        lpAdrList = lpMyAdrList->lpAdrList;
    }

    /* If the list was NULL or full we'll Alloc/ReAlloc */

    if (fAlloc || fReAlloc)
    {
        cb = CbNewADRLIST(cMaxEntries);
        sc = lpxpl->AllocateBuffer(cb, &lpAdrList);
        if (sc)
        {
            DebugTrace("AllocateBuffer() failed in HrAddRecipToAdrList()");
            goto ret;
        }

        /* Zero-out new list */

        memset(lpAdrList, 0, (size_t) cb);

        if (fReAlloc)
        {
            /* We're ReAllocing; copy old list into new memory */

            cb = CbNewADRLIST(lpMyAdrList->lpAdrList->cEntries);
            if (cb)
                memcpy(lpAdrList, lpMyAdrList->lpAdrList, (size_t) cb);

            /* Free old list */

            lpxpl->FreeBuffer(lpMyAdrList->lpAdrList);
        }

        /* Fix-up size and pointer elements */

        lpMyAdrList->cMaxEntries = cMaxEntries;
        lpMyAdrList->lpAdrList = lpAdrList;
    }

    /* Allocate room for cRecipProps PropValues and chain memory needed
       for AdrEntry data to the rgProps block to make freeing easier. */

    sc = lpxpl->AllocateBuffer(cRecipProps * sizeof(SPropValue), &rgProps);

    if (sc)
    {
        DebugTrace("AllocateBuffer() failed in HrAddRecipToAdrList()");
        goto ret;
    }

    /* Allocate memory for AddrType */

    sc = lpxpl->AllocateMore(lstrlen(lpszAddrType) + 1, rgProps, &lpszAddrTypeT);

    if (sc)
    {
        DebugTrace("AllocateMore() failed in HrAddRecipToAdrList()");
        goto ret;
    }

    /* Copy AddrType into chained memory buffer */

    lstrcpy(lpszAddrTypeT, lpszAddrType);

    /* Break lpszNameAddr into lpszDisplayName and lpszAddress */

    lpsz = strtok(lpszNameAddr, "[");

    sc = lpxpl->AllocateMore(lstrlen(lpsz) + 1, rgProps, &lpszDisplayName);

    if (sc)
    {
        DebugTrace("AllocateMore() failed in HrAddRecipToAdrList()");
        goto ret;
    }

    /* Copy Display Name into chained memory buffer */

    lstrcpy(lpszDisplayName, lpsz);

    lpsz = strtok(NULL, "]");

    sc = lpxpl->AllocateMore(lstrlen(lpsz) + 1, rgProps, &lpszAddress);

    if (sc)
    {
        DebugTrace("AllocateMore() failed in HrAddRecipToAdrList()");
        goto ret;
    }

    /* Copy Address into chained memory buffer */

    lstrcpy(lpszAddress, lpsz);

    /* Create OneOff Entry ID */

    hr = lpMAPISup->lpVtbl->CreateOneOff(lpMAPISup,
        lpszDisplayName, lpszAddrType, lpszAddress, 0,
        &cbEntryID, (LPENTRYID FAR *) &lpEntryID);

    if (hr)
    {
        DebugTrace("CreateOneOff() failed in HrAddRecipToAdrList()");
        goto ret;
    }

    /* We need to copy the EntryID into chained memory */

    sc = lpxpl->AllocateMore(cbEntryID, rgProps, &lpb);

    if (sc)
    {
        DebugTrace("AllocateMore() failed in HrAddRecipToAdrList()");
        goto ret;
    }

    /* Copy EntryID into chained memory buffer */

    if (cbEntryID)
        memcpy(lpb, lpEntryID, (size_t) cbEntryID);

    lpxpl->FreeBuffer(lpEntryID);
    lpEntryID = NULL;

    /* Now, build the PropValue array */

    rgProps[iRecipType].ulPropTag = PR_RECIPIENT_TYPE;
    rgProps[iRecipType].Value.l = lRecipType;

    rgProps[iDisplayName].ulPropTag = PR_DISPLAY_NAME;
    rgProps[iDisplayName].Value.LPSZ = lpszDisplayName;

    rgProps[iAddrType].ulPropTag = PR_ADDRTYPE;
    rgProps[iAddrType].Value.LPSZ = lpszAddrTypeT;

    rgProps[iAddress].ulPropTag = PR_EMAIL_ADDRESS;
    rgProps[iAddress].Value.LPSZ = lpszAddress;

    rgProps[iEntryID].ulPropTag = PR_ENTRYID;
    rgProps[iEntryID].Value.bin.cb = cbEntryID;
    rgProps[iEntryID].Value.bin.lpb = lpb;

    /* It's now safe to hook in the new AdrEntry */

    lpAdrList->aEntries[lpAdrList->cEntries].cValues = cRecipProps;
    lpAdrList->aEntries[lpAdrList->cEntries++].rgPropVals = rgProps;

    return hrSuccess;

ret:
    lpxpl->FreeBuffer(rgProps);
    lpxpl->FreeBuffer(lpEntryID);

    if (lpAdrList != lpMyAdrList->lpAdrList)
        lpxpl->FreeBuffer(lpAdrList);

    if (!hr && sc)
        hr = ResultFromScode(sc);

    DebugTraceResult(HrAddRecipToAdrList()Failed !, hr);

    return hr;
}


/*
 -  HrAddRecipToReplyList
 -
 *  Purpose:
 *      Builds the PR_REPLY_RECIPIENT_NAMES and PR_REPLY_RECIPIENT_ENTRIES
 *      properties by re-allocing as new ones are added to the list.
 *
 *  Parameters:
 *      lpxpl           Points to Transport Logon object
 *      lpszToken       Contains Display Name and E-Mail Address
 *      lpszAddrType    Address Type for this transport
 *      lppszNames      Semi-colon delimited list of Display Names
 *      lpcbEIDList     Current size of EntryList
 *      lppEIDList      Pointer to current EntryList
 *
 *  Returns:
 *      hr              Indicating Suucess/Failure
 */

HRESULT
HrAddRecipToReplyList(LPXPL lpxpl, LPTSTR lpszToken, LPTSTR lpszAddrType,
    LPTSTR * lppszNames, ULONG * lpcbEIDList, LPFLATENTRYLIST * lppEIDList)
{
    SCODE sc;
    HRESULT hr = hrSuccess;
    LPTSTR lpszAddress;
    LPTSTR lpszName;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    ULONG cbEID;
    LPBYTE lpEID = NULL;
    LPFLATENTRYLIST lpOld = *lppEIDList;
    ULONG cbOld;
    LPFLATENTRYLIST lpNew = NULL;
    LPFLATENTRY lpEntry;
    ULONG cbNew;
    LPTSTR lpszNewNames = NULL;

    lpszName = strtok(lpszToken, "[");

    lpszAddress = strtok(NULL, "]");

    /* Create OneOff Entry ID for this Recipient */

    hr = lpMAPISup->lpVtbl->CreateOneOff(lpMAPISup,
        lpszName, lpszAddrType, lpszAddress, 0,
        &cbEID, (LPENTRYID FAR *) &lpEID);

    if (hr)
        goto ret;

    /* Determine size of new list and allocate memory for it.
       The "+ 3) & -4L" will round up the allocation to be a
       multiple of 4 bytes. */

    if (lpOld)
    {
        Assert(!IsBadReadPtr(lpOld, CbNewFLATENTRYLIST(0)));
        Assert(!IsBadReadPtr(lpOld->abEntries, (UINT) lpOld->cbEntries));

        cbOld = lpOld->cbEntries;
        cbNew = (cbOld + offsetof(FLATENTRY, abEntry) + cbEID + 3) & -4L;
    }
    else
    {
        cbNew = cbOld = (cbEID + offsetof(FLATENTRY, abEntry) + 3) & -4L;
    }

    sc = lpxpl->AllocateBuffer(cbNew + offsetof(FLATENTRYLIST, abEntries), &lpNew);

    if (sc)
    {
        hr = ResultFromScode(sc);
        goto ret;
    }

    /* If Re-Allocing then copy old list and new EID, else build new list */

    if (lpOld)
    {
        ULONG cbNewOff = (cbOld + 3) & -4L;

        /* Copy the old data to the new structure */

        lpNew->cEntries = lpOld->cEntries + 1;
        lpNew->cbEntries = cbNew;

        if (cbOld)
            memcpy(lpNew->abEntries, lpOld->abEntries, (size_t) cbOld);

        /* Resolve the pointer to the new FLATENTRY */

        lpEntry = (LPFLATENTRY) & lpNew->abEntries[cbNewOff];

    }
    else
    {
        lpNew->cEntries = 1;
        lpNew->cbEntries = cbNew;

        /* Resolve the pointer to the new FLATENTRY */

        lpEntry = (LPFLATENTRY) lpNew->abEntries;
    }

    /* Add in the new FLATENTRY */

    lpEntry->cb = cbEID;
    if (cbEID)
        memcpy(lpEntry->abEntry, lpEID, (size_t) cbEID);

    /* Now, build the Display Name(s) String */

    if (*lppszNames)
    {
        /* We're Re-Allocing: copy old string and cat new one */

        sc = lpxpl->AllocateBuffer(lstrlen(*lppszNames) + lstrlen(lpszName) + 3,
            &lpszNewNames);

        if (sc)
        {
            hr = ResultFromScode(sc);
            goto ret;
        }

        lstrcpy(lpszNewNames, *lppszNames);
        lstrcat(lpszNewNames, "; ");
        lstrcat(lpszNewNames, lpszName);

        lpxpl->FreeBuffer(*lppszNames);
    }
    else
    {
        /* First name; just alloc and copy... */

        sc = lpxpl->AllocateBuffer(lstrlen(lpszName) + 1, &lpszNewNames);

        if (sc)
        {
            hr = ResultFromScode(sc);
            goto ret;
        }

        lstrcpy(lpszNewNames, lpszName);
    }

    /* It's now safe to hook in the new list. */
    /* Free old list and pass back new one.   */

    lpxpl->FreeBuffer(lpOld);

    *lppEIDList = lpNew;
    *lpcbEIDList = cbNew + offsetof(FLATENTRYLIST, abEntries);
    *lppszNames = lpszNewNames;

ret:
    lpxpl->FreeBuffer(lpEID);

    if (hr)
    {
        lpxpl->FreeBuffer(lpNew);
        lpxpl->FreeBuffer(lpszNewNames);
    }
    return hr;
}

/*
 -  HrMakeSearchKey
 -
 *  Purpose:
 *      Makes a Search Key (for the PR_???_SEARCH_KEY property) from
 *      the values passed in.  Memory is chained to some parent block.
 *      SearchKeys look like: ADDRTYPE:EMAILADDRESS.
 *
 *  Parameters:
 *      lpxpl           Points to Transport Logon object
 *      lpParent        Memory block to chain Search Key to
 *      lpszAddrType    Address Type
 *      lpszAddress     E-mail Address
 *      lpcbSK          Returned size of Search Key
 *      lppSK           The returned Search Key
 *
 *  Returns:
 *      hr              Indicating Suucess/Failure
 */

HRESULT
HrMakeSearchKey(LPXPL lpxpl, LPVOID lpParent, LPTSTR lpszAddrType,
    LPTSTR lpszAddress, ULONG * lpcbSK, LPBYTE * lppSK)
{
    SCODE sc;
    HRESULT hr = hrSuccess;
    LPBYTE lpb = NULL;
    ULONG ulSize;

    /* The 2 is for the colon and the NULL terminator */

    ulSize = sizeof(TCHAR) * (2 + lstrlen(lpszAddrType) + lstrlen(lpszAddress));

    sc = lpxpl->AllocateMore(ulSize, lpParent, &lpb);

    if (sc)
    {
        hr = ResultFromScode(sc);
        goto ret;
    }

    /* We need to convert to upper case, that's the law! */

    wsprintf((LPTSTR) lpb, "%s:%s", lpszAddrType, lpszAddress);
    CharUpperBuff((LPTSTR) lpb, (UINT) (ulSize - sizeof(TCHAR)));

    *lpcbSK = ulSize;
    *lppSK = lpb;

ret:
    return hr;
}

/*
 -  HrGetLine
 -
 *  Purpose:
 *      Kind of like fgets() except it strips CR\LF pairs for us.
 *      Reads cbDest bytes from the lpSof stream or until a CR/LF
 *      pair is reached, whichever comes first.  Returns count of
 *      bytes read into lpsz.
 *
 *  Parameters:
 *      lpSof           Points to an OLE 2.0 Stream (to be read from)
 *      cbDest          Size of memory pointed to by lpsz
 *      lpsz            Points to a chunck of memory that receives the
 *                      line being read in.  Must be of size cbDest.
 *      pcbRead         Receives the count of bytes actually read in.
 *
 *  Returns:
 *      hr              Indicating Suucess/Failure
 */

HRESULT
HrGetLine(LPSTREAM lpSof, ULONG cbDest, LPTSTR lpsz, ULONG * pcbRead)
{
    HRESULT hr = S_OK;
    BOOL fCRLF = FALSE;
    TCHAR rgch1[1];
    TCHAR rgch2[1];
    ULONG cbRead;

    if (!lpSof || (cbDest == 0) || !lpsz || !pcbRead)
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);

    for (*pcbRead = 0; *pcbRead < cbDest - sizeof(TCHAR);)
    {
        /* read one TCHAR from stream */

        hr = lpSof->lpVtbl->Read(lpSof, (LPVOID) rgch1, sizeof(TCHAR), &cbRead);

        if (hr || (cbRead != sizeof(TCHAR)))
            break;

        /* Test for CR/LF pair; if not then add to line */

        if (*rgch1 == '\r')
        {
            hr = lpSof->lpVtbl->Read(lpSof, (LPVOID) rgch2, sizeof(TCHAR), &cbRead);

            if (hr)
                break;

            if (cbRead == sizeof(TCHAR))
            {
                if (*rgch2 == '\n')
                {
                    fCRLF = TRUE;
                    break;
                }
            }
            else
            {
                *lpsz++ = *rgch1;
                *lpsz++ = *rgch2;
                *pcbRead += 2 * sizeof(TCHAR);
            }
        }
        else
        {
            *lpsz++ = *rgch1;
            *pcbRead += sizeof(TCHAR);
        }
    }

    /* NULL terminate and leave */

    *lpsz = '\0';

    /* Test for the EOF case.  Since the stream
       won't return errors, we will!!!! */

    if (!fCRLF && !*pcbRead)
        hr = ResultFromScode(MAPI_E_CALL_FAILED);

    return hr;
}


/*
 -  FGetTagAndToken
 -
 *  Purpose:
 *      Breaks a line read from the input stream into Tag and Token.
 *      If no Tag is found, then returns FALSE indicating this is not
 *      a Tag'd line.
 *
 *  Parameters:
 *      lpsz            A line from the messsage file that may have
 *                      the format: 'Tag: Token'.  Must be of size MAX_LINE.
 *      pulTag          Will receive the index of lpsz's Tag in rgszTag
 *      lppszToken      Will point to the token in lpsz
 *
 *  Returns:
 *      TRUE            If lpsz starts with a valid Tag
 *      FALSE           otherwise
 */

BOOL
FGetTagAndToken(LPTSTR lpsz, ULONG * pulTag, LPTSTR * lppszToken)
{
    ULONG uli;
    TCHAR chT;
    LPTSTR lpszT;

    if (!lpsz || !pulTag || !lppszToken)
        return FALSE;

    /* Tags end with ':'  If lpsz has a ':' then it MIGHT be
       a Tag'd line, else it's definitely NOT a Tag'd line. */

    lpszT = strchr(lpsz, ':');

    if (!lpszT)
        return FALSE;

    /* Check that we're not at the MAX_LINE extent of lpsz.  If we are
       then just return, cause this can't possibly be a Tag'd line!
       The '3' accounts for the space, colon, and null terminator. */

    if ((lpszT - lpsz) > (MAX_LINE - 3))
        return FALSE;

    /* Swap *(lpszT+2) with a NULL to seperate Tag from Token */

    lpszT += 2;
    chT = *lpszT;
    *lpszT = '\0';

    /* Look-Up 'Potential' Tag in Tag Table */

    for (uli = 0; uli < NUM_TAGS; uli++)
    {
        if (!lstrcmp(lpsz, rgszTags[uli]))
        {
            /* Found!  Remember index */

            *pulTag = uli;
            break;
        }
    }

    /* Swap that NULL out.  lpszT now points to the token (maybe) */

    *lpszT = chT;

    if (uli == NUM_TAGS)
        return FALSE;           /* Tag wasn't found; it's just a line */

    *lppszToken = lpszT;

    return TRUE;
}


/*
 -  FileTimeFromSzTime
 -
 *  Purpose:
 *      Converts the textized data field in the text file format
 *      to a FILETIME struct format.  If we encounter errors in
 *      parsing the lpszDateTime string, we jump to the conversion
 *      call and will translate as much as we've filled in so far.
 *
 *  Parameters:
 *      lpszDateTime        Date/Time in the format: yyyy/mm/dd hh:mm
 *      pft                 Pointer to a FILETIME struct
 */

void
FileTimeFromSzTime(LPTSTR lpszDateTime, FILETIME * pft)
{
    SYSTEMTIME systime =
    {0, 0, 0, 0, 0, 0, 0, 0};
    LPTSTR lpsz;

    /* Feeble attempt at parameter validation! */

    if (!lpszDateTime || !pft)
        return;

    /* Grab the Year */

    lpsz = strtok(lpszDateTime, "/");
    if (!lpsz)
        goto ret;

    systime.wYear = atoi(lpsz);

    /* Grab the Month */

    lpsz = strtok(NULL, "/");
    if (!lpsz)
        goto ret;

    systime.wMonth = atoi(lpsz);

    /* Grab the Day */

    lpsz = strtok(NULL, " ");
    if (!lpsz)
        goto ret;

    systime.wDay = atoi(lpsz);

    /* Grab the Hour */

    lpsz = strtok(NULL, ":");
    if (!lpsz)
        goto ret;

    systime.wHour = atoi(lpsz);

    /* Grab the Minutes */

    lpsz = strtok(NULL, "\r\n:");
    if (!lpsz)
        goto ret;

    systime.wMinute = atoi(lpsz);

ret:
    SystemTimeToFileTime(&systime, pft);
}


/*
 -  SetFromMeFlag
 -
 *  Purpose:
 *      Sets the PR_MESSAGE_FLAGS MSGFLAG_FROMME bit to on.
 *
 */

VOID
SetFromMeFlag(LPXPL lpxpl, LPMESSAGE lpMsg)
{
    HRESULT hResult;
    LPSPropValue lpProp = NULL;

    /* Get the current state of the Message Flags */

    hResult = HrGetOneProp((LPMAPIPROP)lpMsg, PR_MESSAGE_FLAGS, &lpProp);

    if (HR_FAILED(hResult))
        goto ret;

    /* Add the FromMe bit */

    lpProp->Value.l |= MSGFLAG_FROMME;

    hResult = HrSetOneProp((LPMAPIPROP)lpMsg, lpProp);

ret:
    lpxpl->FreeBuffer(lpProp);
}
