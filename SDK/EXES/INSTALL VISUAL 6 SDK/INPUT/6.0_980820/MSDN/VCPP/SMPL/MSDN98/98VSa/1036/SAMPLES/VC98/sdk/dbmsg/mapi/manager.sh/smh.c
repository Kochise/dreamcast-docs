/*
 *  S M H . C
 *  
 *  Sample mail handling hook
 *  
 *  Purpose:
 *  
 *      The sample mail handling (SMH) hook illustrates the use of the
 *      MAPI Spooler Hook Provider Interface (ISpoolerHook) and those
 *      parts of the general MAPI API that are available to a spooler
 *      hook implementation.
 *  
 *      Specifically, SMH illusttrates the operation of both an inbound
 *      message hook as well as outbound.  SMH also has examples of the
 *      configuration of a spooler hook provider via calls to SMH's
 *      ServiceEntry() and/or through calls from the Profile Wizard.
 *  
 *  Features:
 *  
 *    Sent Mail:
 *  
 *      SMH allows the archiving of outbound messages (sent mail), into a
 *      well defined set of subfolders in the default stores sent mail
 *      folder.  The archive folders are comprised of monthly archive
 *      folders.  The monthly folders can be, optionally, created under a
 *      year based folder in the sent mail folder.  Thus in a typical
 *      message store, a fully archived sent mail folder might have a
 *      hierarchy that looks similar to the following:
 *  
 *          Sent Mail
 *              |
 *              |-- 1994
 *              |    |
 *              |    |-- 10 October
 *              |    |-- 11 November
 *              |    |-- 12 December
 *              |
 *              |-- 1995
 *                   |
 *                   |-- 01 January
 *  
 *      This allows for a mail user to organize their outgoing mail in
 *      a managible fashion.
 *  
 *    Deleted Mail:
 *  
 *      SMH allows the archiving of deleted mail in the same fashion as
 *      sent mail can be archived.  This feature helps people who choose
 *      keep their 'deleted' mail accessible.  It should be noted here
 *      that this feature does not make use of the ISpoolerHook
 *      interface, but is an example of what all can be done with spooler
 *      hook providers.
 *  
 *    Incoming Mail:
 *  
 *      SMH can also 'filter' incoming messages and route the message
 *      directly to folders, other than the default stores inbox, based
 *      on message content.  The user can define any number of filters
 *      that can help organize and manage the email.  Additionally, the
 *      user can specify a sound scheme to be used on message delivery.
 *      This allows the user to specify specific sounds based on message
 *      content and priority.
 *  
 *    Unread Search Folders:
 *  
 *      Because SMH can filter unread messages deep into a message store
 *      folder hierarchy, SMH can also create a search folder in the root
 *      of the IPM_SUBTREE that searches the entire subtree for unread
 *      messages.
 *  
 *    Out-of-office Processing:
 *  
 *      SMH can generate OOF notifications for incomming mail.  It will
 *      do it's best to not send multiple OOF's to any single recipient
 *      over the period in which the OOF processing is enabled.  The OOF
 *      engine supports full rich-text.
 *  
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"

extern SPropTagArray sptRule;
extern SPropTagArray sptConfigProps;

/*
 *  sptMessageProps
 *
 *  These are the properties that are required to check filters against
 *  messages.
 */
const static SizedSPropTagArray (cpMsgPrps, sptMsgPrps) =
{
    cpMsgPrps,
    {
        PR_MESSAGE_FLAGS,
        PR_SUBJECT,
        PR_SENT_REPRESENTING_NAME,
        PR_SENT_REPRESENTING_EMAIL_ADDRESS,
        PR_IMPORTANCE
    }
};

/*
 *  vtblSMH
 *
 *  This is the SMH object's vtable.  The table and its functions are
 *  defined by MAPI's ISpoolerHook interface.
 */
static const SMH_Vtbl vtblSMH =
{
    SMH_QueryInterface,
    SMH_AddRef,
    SMH_Release,
    SMH_InboundMsgHook,
    SMH_OutboundMsgHook
};

/*
 *  lpCtl3D
 *  
 *  Holds context for the 3D control DLL.
 */

LPVOID lpCtl3D = NULL;

/*
 *  HrInitUnreadSearch()
 *
 *  Purpose:
 *
 *      Inits/creates an 'Unread Messages' search folder in the root of
 *      the given store's IPM_SUBTREE hierarchy.
 *
 *  Arguments:
 *
 *      lpsmh           the sample mail handler object
 *      lpmdb           the store getting the search folder
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrInitUnreadSearch (LPSMH lpsmh)
{
    HRESULT hr;
    ENTRYLIST el = {0};
    LPMAPIFOLDER lpfldr = NULL;
    LPMAPIFOLDER lpfldrUM = NULL;
    LPMDB lpmdb = NULL;
    LPSPropValue lpval = NULL;
    SRestriction res = {0};
    ULONG ulType = 0;
    UINT cerr = 0;
    UINT i;

    for (i = 0; i < lpsmh->lpstotbl->cSto; i++)
    {
        hr = HrOpenStoEntry (lpsmh->lpsess, &lpsmh->lpstotbl->aSto[i], &lpmdb);
        if (!HR_FAILED (hr))
        {
            hr = HrGetOneProp ((LPMAPIPROP)lpmdb, PR_IPM_SUBTREE_ENTRYID, &lpval);
            if (!HR_FAILED (hr))
            {
                hr = lpmdb->lpVtbl->OpenEntry (lpmdb,
                                        lpval->Value.bin.cb,
                                        (LPENTRYID)lpval->Value.bin.lpb,
                                        NULL,
                                        MAPI_MODIFY,
                                        &ulType,
                                        (LPUNKNOWN FAR *)&lpfldr);
                if (!HR_FAILED (hr))
                {
                    hr = lpfldr->lpVtbl->CreateFolder (lpfldr,
                                        FOLDER_SEARCH,
                                        "Unread Messages",
                                        "Simple Mail Handler: unread message search",
                                        NULL,
                                        MAPI_MODIFY | OPEN_IF_EXISTS,
                                        &lpfldrUM);
                    if (!HR_FAILED (hr))
                    {
                        el.cValues = 1;
                        el.lpbin = &lpval->Value.bin;
                        res.rt = RES_BITMASK;
                        res.res.resBitMask.relBMR = BMR_EQZ;
                        res.res.resBitMask.ulPropTag = PR_MESSAGE_FLAGS;
                        res.res.resBitMask.ulMask = MSGFLAG_READ;
                        hr = lpfldrUM->lpVtbl->SetSearchCriteria (lpfldrUM,
                                        &res,
                                        &el,
                                        RECURSIVE_SEARCH | BACKGROUND_SEARCH | RESTART_SEARCH);
                        UlRelease (lpfldrUM);
                        lpfldrUM = NULL;
                    }
                    UlRelease (lpfldr);
                    lpfldr = NULL;
                }
                (*lpsmh->lpfnFree) (lpval);
                lpval = NULL;
            }
        }
        if (HR_FAILED (hr))
        {
            DebugTrace ("SMH: WARNING: failed to init unread search (store:%d)\n", i);
            cerr++;
        }
    }

    hr = ResultFromScode (cerr ? MAPI_W_ERRORS_RETURNED : S_OK);
    DebugTraceResult (HrInitUnreadSearch(), hr);
    return hr;
}


/*
 *  LpszFindChar()
 *
 *  Purpose:
 *
 *      Finds the given character in the passed in string.  This is an
 *      exact matching model so strings should be normalized to either
 *      upper or lower case if case insensitvity is required.
 *
 *  Arguments:
 *
 *      lpszSrc         source string
 *      ch              character to find
 *
 *  Returns:
 *
 *      NULL iff the char was not found, otherwise, the return is a
 *      pointer to the character in the source string.
 */
LPTSTR
LpszFindChar (LPTSTR lpszSrc, TCHAR ch)
{
    LPTSTR lpsz = lpszSrc;

    if (lpszSrc)
        while (*lpsz && (*lpsz != ch))
            lpsz++;

    return ((lpsz && *lpsz) ? lpsz : NULL);
}


/*
 *  HrCheckExclusions()
 *
 *  Purpose:
 *
 *      Checks the message class against the list of message classes
 *      excluded from filtering.
 *
 *  Arguments:
 *
 *      lpsmh           the smh parent object
 *      lpmsg           the message to check for exclusion
 *
 *  Returns:
 *
 *      (HRESULT)       If the message is to be excluded, then hrSuccess
 *                      is returned, otherwize MAPI_E_NOT_ME indicates it
 *                      is OK to filter the message
 */
HRESULT
HrCheckExclusions (LPSMH lpsmh, LPMESSAGE lpmsg)
{
    SCODE sc = S_OK;
    UINT isz = 0;
    LPSPropValue lpval = NULL;

    if (lpsmh->valEx.ulPropTag == PR_SMH_EXCLUSIONS)
    {
        if (!HR_FAILED (HrGetOneProp ((LPMAPIPROP)lpmsg, PR_MESSAGE_CLASS, &lpval)))
        {
            /*  See if this is in the list of exclusions */

            for (isz = 0; isz < lpsmh->valEx.Value.MVSZ.cValues; isz++)
                if (FLpszContainsLpsz (lpval->Value.LPSZ, lpsmh->valEx.Value.MVSZ.LPPSZ[isz]))
                    break;

            (*lpsmh->lpfnFree) (lpval);
        }
        sc = ((isz == lpsmh->valEx.Value.MVSZ.cValues) ? S_OK : MAPI_E_NOT_ME);
    }

    DebugTraceSc (HrCheckExclusions(), sc);
    return ResultFromScode (sc);
}


/*
 *  HrCheckRule()
 *  
 *  Purpose:
 *  
 *      Examines a message to see if the current rule applies to the
 *      message. 
 *  
 *      IMPORTANT: If a rule is of type RL_SUBJECT, RL_FROM, or
 *      RL_ATTACH, then the set of properties required to check for
 *      matches with the message are retained and passed back to the
 *      caller such that subsequent calls to HrCheckRule() will not have
 *      to get those props a second time.  THEREFORE the caller is
 *      responsible for cleaning up any returned property values.
 *  
 *  Arguments:
 *  
 *      lprl            pointer to the rule
 *      lpmsg           pointer to the message to examine
 *      lppval  [OUT]   buffer containing the target entryid value struct
 *  
 *  Returns:
 *  
 *      (HRESULT)       If the rule does apply, hrSuccess is returned and
 *                      the lppval parameter will point to a lpval struct
 *                      containing the entryid of the target folder.
 *  
 *                      If the rule does not apply, the return value is
 *                      an HRESULT with MAPI_E_NOT_ME as the SCODE.
 *  
 *                      Otherwise normal error codes apply.
 */
HRESULT
HrCheckRule (LPSMH lpsmh, LPRULE lprl, LPMESSAGE lpmsg, LPSPropValue FAR * lppval)
{
    HRESULT hr;
    LPMAPITABLE lptbl = NULL;
    LPSPropValue lpval = *lppval;
    LPSPropValue lpvalT = NULL;
    ULONG cval;

    if (!lpval)
    {
        hr = lpmsg->lpVtbl->GetProps (lpmsg,
                                (LPSPropTagArray)&sptMsgPrps,
                                0,
                                &cval,
                                &lpval);
        if (HR_FAILED (hr))
            goto ret;
    }

    /*  Init for failure */

    hr = ResultFromScode (MAPI_E_NOT_ME);

    if ((lprl->rlTyp == RL_TO_RECIP) ||
        (lprl->rlTyp == RL_CC_RECIP) ||
        (lprl->rlTyp == RL_BCC_RECIP) ||
        (lprl->rlTyp == RL_ANY_RECIP))
    {
        hr = lpmsg->lpVtbl->GetRecipientTable (lpmsg, 0, &lptbl);
        if (HR_FAILED (hr))
            goto ret;

        hr = lptbl->lpVtbl->FindRow (lptbl, lprl->lpres, BOOKMARK_BEGINNING, 0);
        UlRelease (lptbl);
        if (HR_FAILED (hr) && (GetScode (hr) == MAPI_E_NOT_FOUND))
            hr = ResultFromScode (MAPI_E_NOT_ME);
    }
    else if (lprl->rlTyp == RL_SUBJECT)
    {
        if (lpval[ipMsgSubj].ulPropTag == PR_SUBJECT)
            if (FLpszContainsLpsz (lpval[ipMsgSubj].Value.LPSZ, lprl->lpszData))
                hr = hrSuccess;
    }
    else if (lprl->rlTyp == RL_SENDER)
    {
        if (lpval[ipMsgSentRep].ulPropTag == PR_SENT_REPRESENTING_NAME)
            if (FLpszContainsLpsz (lpval[ipMsgSentRep].Value.LPSZ, lprl->lpszData))
                hr = hrSuccess;

        if (HR_FAILED (hr))
            if (lpval[ipMsgSentRepEA].ulPropTag == PR_SENT_REPRESENTING_EMAIL_ADDRESS)
                if (FLpszContainsLpsz (lpval[ipMsgSentRepEA].Value.LPSZ, lprl->lpszData))
                    hr = hrSuccess;
    }
    else if (lprl->rlTyp == RL_HAS_ATTACH)
    {
        if (lpval[ipMsgFlgs].ulPropTag == PR_MESSAGE_FLAGS)
            if (lpval[ipMsgFlgs].Value.l & MSGFLAG_HASATTACH)
                hr = hrSuccess;
    }
    else if (lprl->rlTyp == RL_BODY)
    {
        if (!HR_FAILED (HrGetOneProp ((LPMAPIPROP)lpmsg, PR_BODY, &lpvalT)))
        {
            if (FLpszContainsLpsz (lpvalT->Value.LPSZ, lprl->lpszData))
                hr = hrSuccess;

            (*lpsmh->lpfnFree) (lpvalT);
        }
    }
    else if (lprl->rlTyp == RL_MSG_CLASS)
    {
        if (!HR_FAILED (HrGetOneProp ((LPMAPIPROP)lpmsg, PR_MESSAGE_CLASS, &lpvalT)))
        {
            if (FLpszContainsLpsz (lpvalT->Value.LPSZ, lprl->lpszData))
                hr = hrSuccess;

            (*lpsmh->lpfnFree) (lpvalT);
        }
    }

    if (lprl->ulFlags & RULE_NOT)
    {
        if (GetScode (hr) == MAPI_E_NOT_ME)
            hr = hrSuccess;
        else if (hr == hrSuccess)
            hr = ResultFromScode (MAPI_E_NOT_ME);
    }
    
ret:

    *lppval = lpval;
    DebugTraceResult (HrCheckRule(), hr);
    return hr;
}


/*
 *  HrFolderFromPath()
 *
 *  Purpose:
 *
 *      Takes a IPM root-based path string and returns a folder
 *      corresponding to the path given.  The '\' character is the path
 *      separator.  And non-existing folders are created as a psrt of the
 *      process.
 *
 *  Arguments:
 *
 *      lpsmh               pointer to smh parent object
 *      lpmdb               store in which the path is to exist
 *      lpszPath            the root-based path to use
 *      lppfldr     [OUT]   buffer to place target folder
 *      lppvalEid   [OUT]   buffer for target entryid value struct pointer
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrFolderFromPath (LPSMH lpsmh,
    LPMDB lpmdb,
    LPTSTR lpszPath,
    LPMAPIFOLDER FAR * lppfldr,
    LPSPropValue FAR * lppvalEid)
{
    HRESULT hr;
    LPMAPIFOLDER lpfldr = NULL;
    LPMAPIFOLDER lpfldrT = NULL;
    LPSPropValue lpval = NULL;
    LPTSTR lpch;
    TCHAR rgch[MAX_PATH];
    ULONG ulType;

    if (!LoadString (lpsmh->hinst, SMH_FolderComment, rgch, sizeof(rgch)))
        rgch[0] = 0;

    hr = HrGetOneProp ((LPMAPIPROP)lpmdb, PR_IPM_SUBTREE_ENTRYID, &lpval);
    if (!HR_FAILED (hr))
    {
        hr = lpmdb->lpVtbl->OpenEntry (lpmdb,
                            lpval->Value.bin.cb,
                            (LPENTRYID)lpval->Value.bin.lpb,
                            NULL,
                            MAPI_MODIFY,
                            &ulType,
                            (LPUNKNOWN FAR *)&lpfldr);

        (*lpsmh->lpfnFree) (lpval);
        lpval = NULL;

        if (!HR_FAILED (hr))
        {
            do
            {
                if (lpch = LpszFindChar (lpszPath, '\\'))
                    *lpch = 0;

                Assert (lstrlen (lpszPath));
                hr = lpfldr->lpVtbl->CreateFolder (lpfldr,
                            FOLDER_GENERIC,
                            lpszPath,
                            rgch,
                            NULL,
                            MAPI_MODIFY | OPEN_IF_EXISTS,
                            &lpfldrT);
                if (HR_FAILED (hr))
                {
#ifdef  DEBUG
                    LPMAPIERROR lperr = NULL;
                    lpfldr->lpVtbl->GetLastError (lpfldr, hr, 0, &lperr);
                    DebugTrace ("SMH: WARNING: unable to open/create folder: '%s' in %s\n",
                        lperr->lpszError, lperr->lpszComponent);
                    (*lpsmh->lpfnFree) (lperr);
#endif
                    break;
                }

                UlRelease (lpfldr);
                lpfldr = lpfldrT;
                lpfldrT = NULL;

                lpszPath = (lpch ? ++lpch : NULL);

            } while (lpszPath);
        }
        if (!HR_FAILED (hr))
        {
            hr = HrGetOneProp ((LPMAPIPROP)lpfldr, PR_ENTRYID, &lpval);
            if (!HR_FAILED (hr))
            {
                *lppfldr = lpfldr;
                *lppvalEid = lpval;
                lpfldr = NULL;
                lpval = NULL;
            }
        }
    }

    (*lpsmh->lpfnFree) (lpval);
    UlRelease (lpfldr);

    DebugTraceResult (HrFolderFromPath(), hr);
    return hr;
}


/*
 *  HrBuildRule()
 *
 *  Purpose:
 *
 *      Takes a profile section and builds a rule structure that
 *      corresponds to the properties in the profile section.
 *
 *  Arguments:
 *
 *      lpsmh           pointer to smh parent object
 *      lpmuid          profile section UID
 *      lpprl   [OUT]   buffer for the newly created rule pointer
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrBuildRule (LPSMH lpsmh, LPMAPIUID lpmuid, LPRULE FAR * lpprl)
{
    SCODE sc;
    HRESULT hr;
    LPMAPISESSION lpsess = lpsmh->lpsess;
    LPPROFSECT lpprof = NULL;
    LPRULE lprl = NULL;
    LPSPropValue lpval = NULL;
    LPSPropValue lpvalEid = NULL;
    LPSPropValue lpvalT;
    LPSRestriction lpres = NULL;
    ULONG cval;
    ULONG ulType;
    UINT cb;
    UINT i;

    sc = (*lpsmh->lpfnAlloc) (sizeof(RULE), &lprl);
    if (FAILED (sc))
    {
        hr = ResultFromScode (sc);
        goto ret;
    }
    memset (lprl, 0, sizeof(RULE));
    memcpy (&lprl->muid, lpmuid, sizeof(MAPIUID));
    hr = lpsess->lpVtbl->OpenProfileSection (lpsess,
                            lpmuid,
                            NULL,
                            MAPI_MODIFY,
                            &lpprof);
    if (HR_FAILED (hr))
        goto ret;

    hr = lpprof->lpVtbl->GetProps (lpprof,
                            (LPSPropTagArray)&sptRule,
                            0,
                            &cval,
                            &lpval);
    if (HR_FAILED (hr))
        goto ret;

    if ((lpval[ipRLType].ulPropTag != PR_RULE_TYPE) ||
        (lpval[ipRLData].ulPropTag != PR_RULE_DATA) ||
        (lpval[ipRLFlags].ulPropTag != PR_RULE_FLAGS) ||
        (!(lpval[ipRLFlags].Value.l & (RULE_DELETE | RULE_NO_MOVE)) &&
          (lpval[ipRLType].ulPropTag != PR_RULE_TYPE) ||
          (lpval[ipRLPath].ulPropTag != PR_RULE_TARGET_PATH) ||
          (lpval[ipRLStore].ulPropTag != PR_RULE_STORE_DISPLAY_NAME)))
    {
        /*  Something very important is missing */

        hr = ResultFromScode (MAPI_E_UNCONFIGURED);
        goto ret;
    }
    lprl->rlTyp = (UINT)lpval[ipRLType].Value.l;
    lprl->ulFlags = lpval[ipRLFlags].Value.l;

    /*  Get the filter value */

    sc = (*lpsmh->lpfnAllocMore) (lpval[ipRLData].Value.bin.cb, lprl, &lprl->lpszData);
    if (FAILED (sc))
    {
        hr = ResultFromScode (sc);
        goto ret;
    }
    memcpy (lprl->lpszData,
        lpval[ipRLData].Value.bin.lpb,
        (UINT)lpval[ipRLData].Value.bin.cb);

    /*  Get the sounds */

    if (lpval[ipRLFlags].Value.l & RULE_PLAY_SOUNDS)
    {
        for (i = 0; i < csndMax; i++)
        {
            if ((lpval[ipRLLoPri + i].ulPropTag == sptRule.aulPropTag[ipRLLoPri + i]) &&
                (cb = lstrlen (lpval[ipRLLoPri + i].Value.lpszA)))
            {
                cb += sizeof(TCHAR);
                sc = (*lpsmh->lpfnAllocMore) (cb, lprl, (LPVOID FAR *)&lprl->rgszSnd[i]);
                if (FAILED (sc))
                {
                    hr = ResultFromScode (sc);
                    goto ret;
                }
                lstrcpy (lprl->rgszSnd[i], lpval[ipRLLoPri + i].Value.lpszA);
            }
        }
    }

    /*  Fill in the auto response */

    if (lpval[ipRLFlags].Value.l & RULE_AUTO_RESPONSE)
    {
        if (lpval[ipRLRepFwdRTF].ulPropTag == PR_RULE_REP_FWD_RTF)
        {
            sc = (*lpsmh->lpfnAllocMore) (lpval[ipRLRepFwdRTF].Value.bin.cb,
                                          lprl,
                                          (LPVOID FAR *)&lprl->lpbRTF);
            if (FAILED (sc))
            {
                hr = ResultFromScode (sc);
                goto ret;
            }
            lprl->cbRTF = lpval[ipRLRepFwdRTF].Value.bin.cb;
            memcpy (lprl->lpbRTF, lpval[ipRLRepFwdRTF].Value.bin.lpb, (UINT)lprl->cbRTF);
        }
        else if (lpval[ipRLRepFwd].ulPropTag == PR_RULE_REP_FWD_TEXT)
        {
            cb = lstrlen (lpval[ipRLRepFwd].Value.lpszA) + sizeof(TCHAR);
            sc = (*lpsmh->lpfnAllocMore) (cb, lprl, (LPVOID FAR *)&lprl->lpszAnno);
            if (FAILED (sc))
            {
                hr = ResultFromScode (sc);
                goto ret;
            }
            lstrcpy (lprl->lpszAnno, lpval[ipRLRepFwd].Value.lpszA);
        }

        if (lpval[ipRLFlags].Value.l & RULE_AUTO_FORWARD)
        {
            if (lpval[ipRLFwdEid].ulPropTag != PR_RULE_FORWARD_RECIP_ENTRYID)
            {
                hr = ResultFromScode (MAPI_E_UNCONFIGURED);
                goto ret;
            }
            else
            {
                sc = (*lpsmh->lpfnAlloc) (sizeof(SPropValue), &lprl->lpvalRecip);
                if (!FAILED (sc))
                {
                    sc = (*lpsmh->lpfnAllocMore) (lpval[ipRLFwdEid].Value.bin.cb,
                        lprl->lpvalRecip,
                        &lprl->lpvalRecip[0].Value.bin.lpb);
                    if (!FAILED (sc))
                    {
                        lprl->lpvalRecip[0].ulPropTag = PR_ENTRYID;
                        lprl->lpvalRecip[0].Value.bin.cb = lpval[ipRLFwdEid].Value.bin.cb;
                        memcpy (lprl->lpvalRecip[0].Value.bin.lpb,
                                lpval[ipRLFwdEid].Value.bin.lpb,
                                lpval[ipRLFwdEid].Value.bin.cb);
                    }
                }
            }
            if (FAILED (sc))
            {
                hr = ResultFromScode (sc);
                goto ret;
            }
        }
    }

    /*  See if we are not going to delete the message */
    
    if (!(lpval[ipRLFlags].Value.l & (RULE_DELETE | RULE_NO_MOVE)))
    {
        /*  Find the target folder */

        hr = HrOpenMdbFromName (lpsmh, lpval[ipRLStore].Value.LPSZ, &lprl->lpmdb);
        if (HR_FAILED (hr))
            goto ret;

        if ((lpval[ipRLEid].ulPropTag != PR_RULE_TARGET_ENTRYID) ||
            (HR_FAILED (lpsess->lpVtbl->OpenEntry (lpsess,
                            lpval[ipRLEid].Value.bin.cb,
                            (LPENTRYID)lpval[ipRLEid].Value.bin.lpb,
                            NULL,
                            MAPI_MODIFY,
                            &ulType,
                            (LPUNKNOWN FAR *)&lprl->lpfldr))))
        {
            hr = HrFolderFromPath (lpsmh,
                            lprl->lpmdb,
                            lpval[ipRLPath].Value.LPSZ,
                            &lprl->lpfldr,
                            &lpvalEid);
            if (HR_FAILED (hr))
                goto ret;

            lpvalEid->ulPropTag = PR_RULE_TARGET_ENTRYID;
            HrSetOneProp ((LPMAPIPROP)lpprof, lpvalEid);
            lprl->lpvalEid = lpvalEid;
        }
        else
        {
            hr = HrGetOneProp ((LPMAPIPROP)lprl->lpfldr, PR_ENTRYID, &lprl->lpvalEid);
            if (HR_FAILED (hr))
                goto ret;
        }
    }

    if ((lpval[ipRLType].Value.l == RL_TO_RECIP) ||
        (lpval[ipRLType].Value.l == RL_CC_RECIP) ||
        (lpval[ipRLType].Value.l == RL_BCC_RECIP) ||
        (lpval[ipRLType].Value.l == RL_ANY_RECIP))
    {
        cb = (sizeof(SRestriction) * cresMax) + (sizeof(SPropValue) * cvMax);
        sc = (*lpsmh->lpfnAllocMore) (cb, lprl, &lpres);
        if (FAILED (sc))
        {
            hr = ResultFromScode (sc);
            goto ret;
        }
        lpvalT = (LPSPropValue)&lpres[cresMax];

        lpres[iresAnd].rt = RES_AND;
        lpres[iresAnd].res.resAnd.cRes = 2;
        lpres[iresAnd].res.resAnd.lpRes = &lpres[iresRecip];

        lpvalT[ivRecip].ulPropTag = PR_RECIPIENT_TYPE;
        lpvalT[ivRecip].Value.l = ((lpval[ipRLType].Value.l == RL_TO_RECIP)
                                    ? MAPI_TO
                                    : ((lpval[ipRLType].Value.l == RL_CC_RECIP)
                                        ? MAPI_CC
                                        : ((lpval[ipRLType].Value.l == RL_BCC_RECIP)
                                            ? MAPI_BCC
                                            : 0)));
        lpres[iresRecip].rt = RES_PROPERTY;
        lpres[iresRecip].res.resProperty.relop = RELOP_EQ;
        lpres[iresRecip].res.resContent.ulPropTag = PR_RECIPIENT_TYPE;
        lpres[iresRecip].res.resContent.lpProp = &lpvalT[ivRecip];

        lpres[iresOr].rt = RES_OR;
        lpres[iresOr].res.resOr.cRes = 2;
        lpres[iresOr].res.resOr.lpRes = &lpres[iresEmail];

        lpvalT[ivEmail].ulPropTag = PR_EMAIL_ADDRESS;
        lpvalT[ivEmail].Value.LPSZ = (LPTSTR)lprl->lpszData;
        lpres[iresEmail].rt = RES_CONTENT;
        lpres[iresEmail].res.resContent.ulFuzzyLevel = FL_SUBSTRING | FL_IGNORECASE;
        lpres[iresEmail].res.resContent.ulPropTag = PR_EMAIL_ADDRESS;
        lpres[iresEmail].res.resContent.lpProp = &lpvalT[ivEmail];

        lpvalT[ivDispNm].ulPropTag = PR_DISPLAY_NAME;
        lpvalT[ivDispNm].Value.LPSZ = (LPTSTR)lprl->lpszData;
        lpres[iresDispNm].rt = RES_CONTENT;
        lpres[iresDispNm].res.resContent.ulFuzzyLevel = FL_SUBSTRING | FL_IGNORECASE;
        lpres[iresDispNm].res.resContent.ulPropTag = PR_DISPLAY_NAME;
        lpres[iresDispNm].res.resContent.lpProp = &lpvalT[ivDispNm];

        if ((lpval[ipRLType].Value.l == RL_TO_RECIP) ||
            (lpval[ipRLType].Value.l == RL_CC_RECIP) ||
            (lpval[ipRLType].Value.l == RL_BCC_RECIP))
            lprl->lpres = &lpres[iresAnd];
        else
            lprl->lpres = &lpres[iresOr];
    }

ret:

    (*lpsmh->lpfnFree) (lpval);

    UlRelease (lpprof);
    if (HR_FAILED (hr))
    {
        (*lpsmh->lpfnFree) (lprl->lpvalRecip);
        (*lpsmh->lpfnFree) (lprl->lpvalEid);
        (*lpsmh->lpfnFree) (lprl);
        lprl = NULL;
    }
    *lpprl = lprl;

    DebugTraceResult (HrBuildRule(), hr);
    return hr;
}


/*
 *  ReleaseBkit()
 *
 *  Purpose:
 *
 *      Cleans up all resources held by a bucket structure and wipes the
 *      structure clean.
 *
 *  Arguments:
 *
 *      lpsmh           pointer to the smh object (uses allocation fn's)
 *      lpbkit          pointer to the bucket needing cleaning
 *
 */
VOID
ReleaseBkit (LPSMH lpsmh, LPBKIT lpbkit)
{
    UlRelease (lpbkit->lpfldr);
    UlRelease (lpbkit->lpfldrYr);
    UlRelease (lpbkit->lpfldrParent);
    (*lpsmh->lpfnFree) (lpbkit->lpeid);
    (*lpsmh->lpfnFree) (lpbkit->lpeidYr);
    (*lpsmh->lpfnFree) (lpbkit->lpeidParent);
    memset (lpbkit, 0, sizeof(BKIT));
    return;
}


HRESULT
HrInitSMH (LPSMH lpsmh)
{
    HRESULT hr;
    LPPROFSECT lpprof = NULL;
    LPRULE lprl;
    LPSPropValue lpval = NULL;
    LPSPropValue lpvalOld;
    UINT crl;
    ULONG cval;
    
    /*  Get options from the profile */

    hr = lpsmh->lpsess->lpVtbl->OpenProfileSection (lpsmh->lpsess,
                            &lpsmh->muid,
                            NULL,
                            MAPI_MODIFY,
                            &lpprof);
    if (HR_FAILED (hr))
        goto ret;

    hr = lpprof->lpVtbl->GetProps (lpprof,
                            (LPSPropTagArray)&sptConfigProps,
                            0,
                            &cval,
                            &lpval);
    if (HR_FAILED (hr))
        goto ret;

    /*  Check to see if we are configured */

    if (lpval[ipFlags].ulPropTag != PR_SMH_FLAGS)
    {
        hr = ResultFromScode (MAPI_E_UNCONFIGURED);
        goto ret;
    }

    /*  Check that the rules are stored in the correct format */
    
    if (lpval[ipRules].ulPropTag != PR_SMH_RULES)
    {
        hr = HrGetOneProp ((LPMAPIPROP)lpprof,
                    CHANGE_PROP_TYPE(PR_SMH_RULES, PT_BINARY),
                    &lpvalOld);
        if (!HR_FAILED (hr))
        {
            /*  The rules are stored in the wrong format */

            hr = HrUpdateProfileFormat (lpsmh->lpsess,
                            lpsmh->lpsess->lpVtbl->OpenProfileSection,
                            lpsmh->lpfnAllocMore,
                            lpsmh->lpfnFree,
                            lpval,
                            lpvalOld);
            (*lpsmh->lpfnFree) (lpvalOld);
            if (HR_FAILED (hr))
                goto ret;

            /*  Save out anything we got back */

            lpprof->lpVtbl->SetProps (lpprof, cpMax, lpval, NULL);
        }
    }
    UlRelease (lpprof);
    lpprof = NULL;

    /*  Grab the exclusions list */

    hr = ResultFromScode (PropCopyMore (&lpsmh->valEx,
                            &lpval[ipExc],
                            lpsmh->lpfnAllocMore,
                            lpsmh));
    if (HR_FAILED (hr))
        goto ret;

    /*  Init the stores table */

    hr = HrInitStoresTable (lpsmh, lpsmh->lpsess);
    if (HR_FAILED (hr))
        goto ret;

    /*  Store the values */

    lpsmh->fAtp = !!(lpval[ipFlags].Value.l & SMH_ADD_TO_PAB);
    lpsmh->fCatSm = !!(lpval[ipFlags].Value.l & SMH_FILTER_SENTMAIL);
    lpsmh->fCatSmByYr = !!(lpval[ipFlags].Value.l & SMH_FILTER_SENTMAIL_YR);

    /*  If we are archiving deleted mail, init the filters */
    
    if (lpval[ipFlags].Value.l & SMH_FILTER_DELETED)
    {
        HrInitDeletedMailFilter (lpsmh);
        lpsmh->fCatWb = !!(lpval[ipFlags].Value.l & SMH_FILTER_DELETED_YR);
    }
    
    /*  If the unread folder is desired, make sure it is there */
    
    if (!!(lpval[ipFlags].Value.l & SMH_UNREAD_VIEWER))
        HrInitUnreadSearch (lpsmh);

    /*  Setup the oof text */
    
    if ((lpval[ipOofEnabled].ulPropTag == PR_SMH_OOF_ENABLED) &&
        lpval[ipOofEnabled].Value.b)
    {
        lpsmh->fOof = !HR_FAILED (HrInitOof (lpsmh,
                                        &lpval[ipOof],
                                        &lpval[ipOofRtf]));
    }

    /*  Build the rules if need be */
    
    if ((lpval[ipFlags].Value.l & SMH_FILTER_INBOUND) &&
        (lpval[ipRules].ulPropTag == PR_SMH_RULES) &&
        (lpval[ipRules].Value.MVbin.cValues != 0))
    {
        crl = (UINT)lpval[ipRules].Value.MVbin.cValues;
        while (crl--)
        {
            hr = HrBuildRule (lpsmh,
                    (LPMAPIUID)lpval[ipRules].Value.MVbin.lpbin[crl].lpb,
                    &lprl);
            if (!HR_FAILED (hr))
            {
                lprl->rlNext = lpsmh->lstRl;
                lpsmh->lstRl = lprl;
            }
        }
        hr = hrSuccess;
    }

ret:

    UlRelease (lpprof);
    (*lpsmh->lpfnFree) (lpval);

    DebugTraceResult (HrInitSMH(), hr);
    return hr;
}


VOID
DeinitSMH (LPSMH lpsmh)
{
    LPRULE lprl;
    LPRULE lprlT;
    LPWB lpwb;
    LPWB lpwbT;
    
    ReleaseBkit (lpsmh, &lpsmh->bkitSm);
    memset (&lpsmh->bkitSm, 0, sizeof(BKIT));

    for (lpwb = lpsmh->lstWb; lpwb; lpwb = lpwbT)
    {
        lpwbT = lpwb->wbNext;
        lpwb->lptbl->lpVtbl->Unadvise (lpwb->lptbl, lpwb->ulAdvz);

#ifdef  _WIN32
        if (lpwb->ht)
        {
            lpwb->fBail = TRUE;
            WaitForSingleObject (lpwb->ht, INFINITE);
        }
#endif

        ReleaseBkit (lpsmh, &lpwb->bkit);
        UlRelease (lpwb->lptbl);
        UlRelease (lpwb->lpfldr);

        (*lpsmh->lpfnFree) (lpwb->lpvalEid);
        (*lpsmh->lpfnFree) (lpwb);

    }
    lpsmh->lstWb = NULL;
    for (lprl = lpsmh->lstRl; lprl; lprl = lprlT)
    {
        lprlT = lprl->rlNext;
        ReleaseBkit (lpsmh, &lprl->bkit);
        UlRelease (lprl->lpfldr);
        (*lpsmh->lpfnFree) (lprl->lpvalEid);
        (*lpsmh->lpfnFree) (lprl->lpvalRecip);
        (*lpsmh->lpfnFree) (lprl);
    }
    lpsmh->lstRl = NULL;

    UlRelease (lpsmh->oof.lptad);
    UlRelease (lpsmh->oof.lptbl);
    (*lpsmh->lpfnFree) (lpsmh->oof.lpbRTF);
    (*lpsmh->lpfnFree) (lpsmh->oof.lpszBody);
    memset (&lpsmh->oof, 0, sizeof(OOF));

    ReleaseStoresTable (lpsmh);
    return;
}


/*
 *  SMH Object Methods
 *
 *  SMH_QueryInterface      (See OLE IUnknown object methods)
 *  SMH_AddRef              (See OLE IUnknown object methods)
 *  SMH_Release             (See OLE IUnknown object methods)
 *  SMH_InboundMsgHook      Filters inbound messages
 *  SMH_OutboundMsgHook     Filters sent mail messages
 *
 */
STDMETHODIMP
SMH_QueryInterface (LPSMH lpsmh, REFIID lpiid, LPVOID FAR * lppv)
{
    if (IsBadWritePtr (lpsmh, sizeof(SMH)) ||
        IsBadReadPtr (lpiid, sizeof(IID)) ||
        IsBadWritePtr (lppv, sizeof(LPVOID)))
        return ResultFromScode (MAPI_E_INVALID_PARAMETER);

    if (!memcmp (lpiid, &IID_ISpoolerHook, sizeof(IID)) ||
        !memcmp (lpiid, &IID_IUnknown, sizeof(IID)))
    {
        *lppv = (LPVOID)lpsmh;
        lpsmh->lcInit++;
        return hrSuccess;
    }
    DebugTraceSc (SMH_QueryInterface(), MAPI_E_INTERFACE_NOT_SUPPORTED);
    return ResultFromScode (MAPI_E_INTERFACE_NOT_SUPPORTED);
}

STDMETHODIMP_ (ULONG)
SMH_AddRef (LPSMH lpsmh)
{
    if (IsBadWritePtr (lpsmh, sizeof(SMH)))
        return 0;

    return ++lpsmh->lcInit;
}

STDMETHODIMP_ (ULONG)
SMH_Release (LPSMH lpsmh)
{
    if (IsBadWritePtr (lpsmh, sizeof(SMH)))
        return 0;

    if (--lpsmh->lcInit)
        return lpsmh->lcInit;

    DeinitSMH (lpsmh);
    
    CloseHandle (lpsmh->hevtCfg);
    UlRelease (lpsmh->lpsess);
    (*lpsmh->lpfnFree) (lpsmh);
    if (lpCtl3D)
    {
        CTL3D_Uninitialize (lpCtl3D);
        lpCtl3D = NULL;
    }
    return 0;
}

/*
 *  SMH_InboundMsgHook()
 *
 *  Purpose:
 *
 *      The purpose of this filter is to match inbound messages to
 *      individual rules from the profile and re-route the messages based
 *      on the results of the comparisons.
 *
 *  Arguments:
 *
 *      lpsmh           this filter hook obj
 *      lpmsg           the message to be filtered
 *      lpfldrDef       owning folder of message
 *      lpmdbDef        owning store of message
 *      lpulFlags       flags returned by filter
 *      lpcbeid         cb for entryid of default target for message
 *      lppbeid         pb for entryid of default target for message
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
 *      lpulFlags   [out]   set HOOK_CANCEL if this is the last hook
 *      lpcbeid     [out]   the size of the returned EntryID
 *      lppbeid     [out]   the data of the returned EntryID
 *
 */
STDMETHODIMP
SMH_InboundMsgHook (LPSMH lpsmh,
    LPMESSAGE lpmsg,
    LPMAPIFOLDER lpfldrDef,
    LPMDB lpmdbDef,
    ULONG FAR * lpulFlags,
    ULONG FAR * lpcbeid,
    LPBYTE FAR * lppeid)
{
    HRESULT hr = hrSuccess;
    LPRULE lprl;
    LPBYTE lpeid;
    LPSPropValue lpval = NULL;

    /*  Quick and dirty parameter check */

    if (IsBadWritePtr (lpsmh, sizeof(SMH)) ||
        IsBadWritePtr (lpcbeid, sizeof(ULONG)) ||
        IsBadWritePtr (lppeid, sizeof(LPBYTE)) ||
        IsBadWritePtr (*lppeid, (UINT)(*lpcbeid)))
        return ResultFromScode (MAPI_E_INVALID_PARAMETER);

#ifdef  _WIN32
    if (FConfigChanged (lpsmh->hevtCfg))
    {
        /*  reconfiguration required */
        
        DeinitSMH (lpsmh);
        hr = HrInitSMH (lpsmh);
        if (HR_FAILED (hr))
            return hr;
        
        ResetEvent (lpsmh->hevtCfg);
    }
#endif  // _WIN32
    
    if (lprl = lpsmh->lstRl)    /*  Yup '=' */
    {
        hr = HrCheckExclusions (lpsmh, lpmsg);
        if (!HR_FAILED (hr))
        {
            /*  We have not been excluded */

            for (; lprl; lprl = lprl->rlNext)
            {
                hr = HrCheckRule (lpsmh, lprl, lpmsg, &lpval);
                if (!HR_FAILED (hr))
                {
                    /*  We have a match. What do we do, filter or delete? */
                    
                    if (!(lprl->ulFlags & (RULE_DELETE | RULE_NO_MOVE)))
                    {
                        /*  Filter the critter */

                        hr = ResultFromScode ((*lpsmh->lpfnAlloc) (lprl->lpvalEid->Value.bin.cb, &lpeid));
                        if (!HR_FAILED (hr))
                        {
                            memcpy (lpeid, lprl->lpvalEid->Value.bin.lpb,
                                (UINT)lprl->lpvalEid->Value.bin.cb);

                            (*lpsmh->lpfnFree) (*lppeid);
                            *lpcbeid = lprl->lpvalEid->Value.bin.cb;
                            *lppeid = lpeid;

                            if (lprl->ulFlags & RULE_ARCHIVED)
                            {
                                hr = HrArchiveMessage (lpsmh,
                                            lpmsg,
                                            lpfldrDef,
                                            lpmdbDef,
                                            &lprl->bkit,
                                            !!(lprl->ulFlags & RULE_ARCHIVED_BY_YEAR),
                                            lpcbeid,
                                            lppeid);
                                
                                if (lprl->ulFlags & RULE_TERMINAL)
                                    *lpulFlags = HOOK_CANCEL;
                            }
                        }

                        /*  Play the sound */

                        if ((lpval[ipPriority].Value.l < 3) &&
                            lprl->rgszSnd[lpval[ipPriority].Value.l])
                            sndPlaySound (lprl->rgszSnd[lpval[ipPriority].Value.l], SND_ASYNC);
                    }
                    else
                    {
                        if (lprl->ulFlags & RULE_DELETE)
                            *lpulFlags |= HOOK_DELETE;
                                          
                        *lpulFlags |= HOOK_CANCEL;
                    }

                    /*  Check for an auto-forward\reply */

                    if (lprl->ulFlags & RULE_AUTO_RESPONSE)
                    {
                        /*  We have a response that needs to
                         *  be created, and sent on.
                         */
                        hr = HrGenerateResponse (lpsmh, lprl, lpfldrDef, lpmsg);
                    }
                    break;
                }
                else if (GetScode (hr) != MAPI_E_NOT_ME)
                {
                    /*  We have a failure that is not really
                     *  expected, we need to bail.  Also, this
                     *  should cancel any further hooking
                     */
                    *lpulFlags = HOOK_CANCEL;
                    break;
                }
                else
                    hr = hrSuccess;
            }
        }
    }
    
    if (lpsmh->fOof)
    {
        /*  OOF'ing is done by calling HrGenerateResponse()
         *  and passing in a NULL for the rule.
         */
        hr = HrGenerateResponse (lpsmh, NULL, lpfldrDef, lpmsg);
    }

    (*lpsmh->lpfnFree) (lpval);
    DebugTraceResult (SMH_InboundMsgHook(), hr);
    return hrSuccess;
}


/*
 *  SMH_OutboundMsgHook()
 *
 *  Purpose:
 *
 *      The purpose of this filter is to "hash" a users sent mail
 *      processing based on date.  The most obvious bucket size is
 *      monthly but there is no reason not to make this an option the
 *      user could confiigure.
 *
 *  Arguments:
 *
 *      lpsmh           this filter hook obj
 *      lpmsg           the message to be filtered
 *      lpfldrDef       owning folder of message
 *      lpmdbDef        owning store of message
 *      lpulFlags       flags returned by filter
 *      lpcbeid         cb for entryid of default target for message
 *      lppbeid         pb for entryid of default target for message
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
 *      lpulFlags   [out]   set HOOK_CANCEL if this is the last hook
 *      lpcbeid     [out]   the size of the returned EntryID
 *      lppbeid     [out]   the data of the returned EntryID
 *
 */
STDMETHODIMP
SMH_OutboundMsgHook (LPSMH lpsmh,
    LPMESSAGE lpmsg,
    LPMAPIFOLDER lpfldrDef,
    LPMDB lpmdbDef,
    ULONG FAR * lpulFlags,
    ULONG FAR * lpcbeid,
    LPBYTE FAR * lppeid)
{
    HRESULT hr = hrSuccess;

    /*  Quick and dirty parameter check */

    if (IsBadWritePtr (lpsmh, sizeof(SMH)) ||
        IsBadWritePtr (lpcbeid, sizeof(ULONG)) ||
        IsBadWritePtr (lppeid, sizeof(LPBYTE)) ||
        IsBadWritePtr (*lppeid, (UINT)(*lpcbeid)))
        return ResultFromScode (MAPI_E_INVALID_PARAMETER);

#ifdef  _WIN32
    if (FConfigChanged (lpsmh->hevtCfg))
    {
        /*  reconfiguration required */
        
        DeinitSMH (lpsmh);
        hr = HrInitSMH (lpsmh);
        if (HR_FAILED (hr))
            return hr;
        
        ResetEvent (lpsmh->hevtCfg);
    }
#endif  // _WIN32

    if (lpsmh->fAtp)
        (void) HrAddEntriesToPab (lpsmh, lpmsg);

    if (lpsmh->fCatSm)
        hr = HrArchiveMessage (lpsmh,
                lpmsg,
                lpfldrDef,
                lpmdbDef,
                &lpsmh->bkitSm,
                lpsmh->fCatSmByYr,
                lpcbeid,
                lppeid);

    DebugTraceResult (SMH_OutboundMsgHook(), hr);
    return hrSuccess;
}


/*
 *  SMH_Init()
 *
 *  Purpose:
 *
 *      Spooler's entry into the sample mail handler.  This function is
 *      equivilent to a provider logon in that it returns an object to
 *      the spooler that will be used to make any additional calls into
 *      the handler.
 *
 *  Arguments:
 *
 *      lpsess          the session this handler relates to
 *      hinst           hinst of the SMH dll
 *      lpfnAlloc       pointer to MAPIAllocateBuffer()
 *      lpfnAllocMore   pointer to MAPIAllocateMore()
 *      lpfnFree        pointer to MAPIFreeBuffer()
 *      lpmuid          pointer to profile section muid
 *      ulFlags         flags
 *      lppHook         buffer to hold handler object
 *
 *  Returns:
 *
 *      (HRESULT)
 *      lpphook     [OUT]   holds the returned handler object iff successful
 */
STDINITMETHODIMP
SMH_Init (LPMAPISESSION lpsess,
    HINSTANCE hinst,
    LPALLOCATEBUFFER lpfnAlloc,
    LPALLOCATEMORE lpfnAllocMore,
    LPFREEBUFFER lpfnFree,
    LPMAPIUID lpmuid,
    ULONG ulFlags,
    LPSPOOLERHOOK FAR * lppHook)
{
    SCODE sc;
    LPSMH lpsmh = NULL;
    HRESULT hr;

    sc = (*lpfnAlloc) (sizeof(SMH), &lpsmh);
    if (FAILED (sc))
        return ResultFromScode (sc);
    memset (lpsmh, 0, sizeof(SMH));

    hr = lpsess->lpVtbl->QueryInterface (lpsess,
                            &IID_IMAPISession,
                            &lpsmh->lpsess);
    if (!HR_FAILED (hr))
    {
        /*  Fill in all fields of the object */

        lpsmh->lpVtbl = (SMH_Vtbl FAR *)&vtblSMH;
        lpsmh->lcInit = 1;
        lpsmh->hinst = hinst;
        lpsmh->lpsess = lpsess;
        lpsmh->lpfnAlloc = lpfnAlloc;
        lpsmh->lpfnAllocMore = lpfnAllocMore;
        lpsmh->lpfnFree = lpfnFree;
        memcpy (&lpsmh->muid, lpmuid, sizeof(MAPIUID));

#ifdef  _WIN32
        /*  Setup listening for configuration changes */

        (void)HrGetConfigEvent (&lpsmh->hevtCfg);
#endif

        /*  Fill out the rest of the structure */
        
        hr = HrInitSMH (lpsmh);
    }

    if (HR_FAILED (hr))
    {
        UlRelease (lpsmh);
        lpsmh = NULL;
    }
    *lppHook = (LPSPOOLERHOOK)lpsmh;
    DebugTraceResult (SMH_Init(), hr);
    return hr;
}
