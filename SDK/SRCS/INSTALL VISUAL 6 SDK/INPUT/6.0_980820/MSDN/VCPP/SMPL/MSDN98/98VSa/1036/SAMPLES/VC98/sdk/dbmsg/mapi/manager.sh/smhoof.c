/*
 *  S M H O O F . C
 *
 *  Sample mail handling hook
 *  Out of office management
 *
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"
#include <mapiutil.h>
#include <cindex.h>
#include <limits.h>

#ifdef _WIN32
#define szPlatform "32"
#else
#define szPlatform
#endif

enum { ipOofRId, ipOofREid, cpOofMax };
enum { icrgFrom, icrgSubmit, icrgTo, icrgCC, icrgSubj, icrgImp, icrgSen, ccrgMax };

enum
{
    ipRespSen,
    ipRespConvKey,
    ipRespConvIdx,
    ipRespConvTopic,
    ipRespReportTag,
    ipRespOrigAuthEid,
    ipRespOrigAuthorName,
    ipRespOrigAuthorSKey,
    ipRespOrigSubmitTime,
    ipRespPriority,
    ipRespImportance,
    ipRespSubject,
    ipRespSubjectPrefix,
    ipRespDelAfterSub,
    ipRespMessageClass,
    ipRespMessageFlags,
    cpTargetResponseMax
};

enum
{
    ipRespRecipName,
    ipRespRecipAdrType,
    ipRespRecipEmail,
    ipRespRecipType,
    ipRespRecipEid,
    ipRespRecipSKey,
    cpTargetRecipMax
};

enum
{
    ipMsgClass,
    ipMsgFlags,
    ipRecipMe,
    ipNSubj,
    ipSndrEid,
    ipSndrNm,
    ipSndrType,
    ipSndrEmail,
    ipSndrSKey,
    ipConvIndex,
    ipConvTopic,
    ipConvKey,
    ipOrigPriority,
    ipReportTag,
    ipOrigAuthorEid,
    ipOrigAuthorName,
    ipOrigAuthorSKey,
    ipOrigSubmitTime,
    ipSentRepName,
    ipSentRepType,
    ipSentRepEmail,
    ipSentRepSKey,
    ipStoreSupport,
    ipSubmitTime,
    ipDisplayTo,
    ipDisplayCc,
    ipOofSubj,
    ipImportance,
    ipSensitivity,
    cpResponseMax
};

const static SizedSPropTagArray (cpResponseMax, sptResponse) =
{
    cpResponseMax,
    {
        PR_MESSAGE_CLASS,
        PR_MESSAGE_FLAGS,
        PR_MESSAGE_RECIP_ME,
        PR_NORMALIZED_SUBJECT,
        PR_SENDER_ENTRYID,
        PR_SENDER_NAME,
        PR_SENDER_ADDRTYPE,
        PR_SENDER_EMAIL_ADDRESS,
        PR_SENDER_SEARCH_KEY,
        PR_CONVERSATION_INDEX,
        PR_CONVERSATION_TOPIC,
        PR_CONVERSATION_KEY,
        PR_PRIORITY,
        PR_REPORT_TAG,
        PR_ORIGINAL_AUTHOR_ENTRYID,
        PR_ORIGINAL_AUTHOR_NAME,
        PR_ORIGINAL_AUTHOR_SEARCH_KEY,
        PR_ORIGINAL_SUBMIT_TIME,
        PR_SENT_REPRESENTING_NAME,
        PR_SENT_REPRESENTING_ADDRTYPE,
        PR_SENT_REPRESENTING_EMAIL_ADDRESS,
        PR_SENT_REPRESENTING_SEARCH_KEY,
        PR_STORE_SUPPORT_MASK,
        PR_CLIENT_SUBMIT_TIME,
        PR_DISPLAY_TO,                  
        PR_DISPLAY_CC,
        PR_SUBJECT,
        PR_IMPORTANCE,
        PR_SENSITIVITY,
    }
};

enum { ipDispNm, ipAdrTyp, ipEmail, ipSKey, cpUserMax };
const static SizedSPropTagArray (cpUserMax, sptUser) =
{
    cpUserMax,
    {
        PR_DISPLAY_NAME,
        PR_ADDRTYPE,
        PR_EMAIL_ADDRESS,
        PR_SEARCH_KEY,
    }
};

enum { ropOof, ropForward, ropReply };
static const LPTSTR rgszSubjPrfx[] =
{
    "OOF: ",
    "FW: ",
    "RE: "
};

enum
{
    ivHdrSndrName,
    ivHdrSndrType,
    ivHdrSndrEmail,
    ivHdrSentRepName,
    ivHdrSentRepType,
    ivHdrSentRepEmail,
    ivHdrSubmitTime,
    ivDisplayTo,
    ivDisplayCc,
    ivSubject,
    ivImportance,
    ivSensitivity,
    cvHeader
};

static const SizedSPropTagArray (cvHeader, sptHeader) = 
{
    cvHeader,
    {
        PR_SENDER_NAME,
        PR_SENDER_ADDRTYPE,
        PR_SENDER_EMAIL_ADDRESS,
        PR_SENT_REPRESENTING_NAME,
        PR_SENT_REPRESENTING_ADDRTYPE,
        PR_SENT_REPRESENTING_EMAIL_ADDRESS,
        PR_CLIENT_SUBMIT_TIME,
        PR_DISPLAY_TO,                  
        PR_DISPLAY_CC,
        PR_SUBJECT,
        PR_IMPORTANCE,
        PR_SENSITIVITY
    }
};

static const SizedSPropTagArray (1, sptForward) =
{
    1,
    {
        PR_MESSAGE_ATTACHMENTS,
    }
};

enum { ipAttPos, ipAttNum, ipAttMeth, ipAttName, cpTaggingMax };
static const SizedSPropTagArray (cpTaggingMax, sptTagging) =
{
    cpTaggingMax,
    {
        PR_RENDERING_POSITION,
        PR_ATTACH_NUM,
        PR_ATTACH_METHOD,
        PR_ATTACH_FILENAME
    }
};

static const LPTSTR rgszHeaderField[] =
{
    "Sent:",
    "To:",
    "Cc:",
    "Subject:",
    "Importance:",
    "Sensitivity:"
};

static const LPTSTR rgszImportance[] = 
{
    "Low",
    "Normal",
    "High"
};

static const LPTSTR rgszSensitivity[] =
{
    "Normal",
    "Personal",
    "Private",
    "Confidential"
};

static const TCHAR * rgszDay[] =
{
    TEXT ("Sunday"),
    TEXT ("Monday"),
    TEXT ("Tuesday"),
    TEXT ("Wednesday"),
    TEXT ("Thursday"),
    TEXT ("Friday"),
    TEXT ("Saturday")
};
extern TCHAR FAR * rgtstrMonthFull[];


LONG
CchInsertSz (HWND hwnd, LPTSTR lpsz)
{
    SendMessage (hwnd, EM_REPLACESEL, 0, (LPARAM) lpsz);
    return lstrlen (lpsz);
}


VOID
FileTimeToDateTimeSz (FILETIME FAR * lpft, LPTSTR rgch, UINT cb)
{
    SYSTEMTIME st;

    if (FileTimeToSystemTime (lpft, &st))
    {
        wsprintf (rgch,
            "%s, %s %02d, %4d %d:%02d %s",
            rgszDay[st.wDayOfWeek],
            rgtstrMonthFull[st.wMonth - 1],
            st.wDay,
            st.wYear,
            st.wHour & 12,
            st.wMinute,
            (st.wHour > 11) ? "PM" : "AM");
    }
    else
        lstrcpy (rgch, "Unavailable");
}

HRESULT
HrCopyOriginalBody (LPSMH lpsmh,
    HWND hwnd,
    LPMESSAGE lpmsg,
    LONG FAR * lpcch)
{
    HRESULT hr;
    CHARRANGE chrg = {0};
    EDITSTREAM es = {0};
    LPSTREAM lpstm = NULL;
    LPSTREAM lpstmT = NULL;

    *lpcch = 0;
    hr = lpmsg->lpVtbl->OpenProperty (lpmsg,
                                PR_RTF_COMPRESSED,
                                &IID_IStream,
                                0, 0,
                                (LPUNKNOWN FAR *)&lpstmT);
    if (!HR_FAILED (hr))
    {
        hr = WrapCompressedRTFStream (lpstmT, 0, &lpstm);
        if (!HR_FAILED (hr))
        {
            es.pfnCallback = (EDITSTREAMCALLBACK)lpstm->lpVtbl->Read;
            es.dwCookie = (DWORD)lpstm;
            
            /*  Stuff a newline into the edit
             *  control such that whatever preceeds
             *  the body will be separated from the
             *  the text of the original message
             */
            SendMessage (hwnd, EM_EXGETSEL, 0, (LPARAM) &chrg);
            CchInsertSz (hwnd, "\r\n");

            /*  Do the body now */
            
            SendMessage (hwnd,
                EM_STREAMIN,
                SF_RTF | SFF_SELECTION | SFF_PLAINRTF,
                (LPARAM)&es);

            /*  Calculate the size of the body in characters */
            
            Edit_SetSel (hwnd, chrg.cpMin, INT_MAX);
            SendMessage (hwnd, EM_EXGETSEL, 0, (LPARAM) &chrg);
            *lpcch = chrg.cpMax - chrg.cpMin;

            /*  Reset the selection to the begining
             *  of the edit control such that all
             *  additions occur before the original
             *  body
             */
            Edit_SetSel (hwnd, 0, 0);
        }
    }

    UlRelease (lpstm);
    UlRelease (lpstmT);
    DebugTraceResult (HrCopyOriginalBody(), hr);
    return hr;
}


HRESULT
HrInsertOriginalHeader (LPSMH lpsmh,
    HWND hwnd,
    LPSPropValue lpval,
    CHARFORMAT FAR * lpcf,
    LONG FAR * lpcch)
{
    CHAR rgch[MAX_PATH];
    CHARRANGE chrg = {0};
    CHARRANGE chrgHdr = {0};
    CHARRANGE rgchrg[ccrgMax] = {0};
    LONG cp;
    LPTSTR lpsz;
    UINT icrg = 0;
    UINT ip;
    
    /*  Stuff a newline into the edit
     *  control such that whatever preceeds
     *  the body will be separated from the
     *  the text of the original message
     */
    SendMessage (hwnd, EM_EXGETSEL, 0, (LPARAM) &chrgHdr);
    CchInsertSz (hwnd, "\r\n");

    /*  Mark the begining of the header */
    
    SendMessage (hwnd, EM_EXGETSEL, 0, (LPARAM) &chrg);
    
    cp = chrg.cpMin;
    cp += CchInsertSz (hwnd, "\r\n----------\r\n");

    /*  Insert the "From: xxxx" line */
    
    if ((lpval[ipSndrNm].ulPropTag == PR_SENDER_NAME) &&
        (lpval[ipSndrNm].Value.LPSZ != NULL) &&
        (*lpval[ipSndrNm].Value.LPSZ != 0))
    {
        rgchrg[icrg].cpMin = cp;
        cp += CchInsertSz (hwnd, "From:");
        rgchrg[icrg].cpMax = cp;
        icrg++;
        
        cp += CchInsertSz (hwnd, "\t");
        cp += CchInsertSz (hwnd, lpval[ipSndrNm].Value.LPSZ);

        /*  If we were representing someone else... */

        if ((lpval[ipSentRepName].ulPropTag == PR_SENT_REPRESENTING_NAME) &&
            (lpval[ipSentRepName].Value.LPSZ != NULL) &&
            (*lpval[ipSentRepName].Value.LPSZ != 0))
        {
            if ((lpval[ipSndrSKey].ulPropTag != PR_SENDER_SEARCH_KEY) ||
                (lpval[ipSentRepSKey].ulPropTag != PR_SENT_REPRESENTING_SEARCH_KEY) ||
                (lpval[ipSndrSKey].Value.bin.cb != lpval[ipSentRepSKey].Value.bin.cb) ||
                memcmp (lpval[ipSndrSKey].Value.bin.lpb,
                    lpval[ipSentRepSKey].Value.bin.lpb,
                    lpval[ipSndrSKey].Value.bin.cb))
            {
                cp += CchInsertSz (hwnd, " on behalf of ");
                cp += CchInsertSz (hwnd, lpval[ipSentRepName].Value.LPSZ);
            }
            cp += CchInsertSz (hwnd, TEXT("\r\n"));
        }

        /*  Insert the remaining lines */
        
        for (ip = ipSubmitTime; ip < cpResponseMax; ip++)
        {
            lpsz = NULL;
            switch (PROP_TYPE (lpval[ip].ulPropTag))
            {
              case PT_TSTRING:

                /*  Strings are strings */
                  
                lpsz = lpval[ip].Value.LPSZ;
                break;

              case PT_SYSTIME:

                /*  Convertt the date to a string */
                  
                FileTimeToDateTimeSz (&lpval[ip].Value.ft, rgch, sizeof(rgch));
                lpsz = rgch;
                break;

              case PT_LONG:

                /*  Importance and Sensitivity use a look-up to
                 *  find the proper string to insert.  If the value
                 *  equates to the "normal" level of a given message,
                 *  then no value is displayed.
                 */
                if ((lpval[ip].ulPropTag == PR_IMPORTANCE) &&
                    (lpval[ip].Value.l != IMPORTANCE_NORMAL))
                    lpsz = rgszImportance[lpval[ip].Value.l];
                else if ((lpval[ip].ulPropTag == PR_SENSITIVITY) &&
                    (lpval[ip].Value.l != SENSITIVITY_NONE))
                    lpsz = rgszSensitivity[lpval[ip].Value.l];
                break;
            }

            if (lpsz && *lpsz)
            {
                rgchrg[icrg].cpMin = cp;
                cp += CchInsertSz (hwnd, rgszHeaderField[ip - ipSubmitTime]);
                rgchrg[icrg].cpMax = cp;
                icrg++;
                
                cp += CchInsertSz (hwnd, "\t");
                cp += CchInsertSz (hwnd, lpsz);
                cp += CchInsertSz (hwnd, TEXT("\r\n"));
            }
        }
        cp += CchInsertSz (hwnd, TEXT("\r\n"));

        /*  Ensure that the text is formated in the
         *  charformat passed in.  Such that we can
         *  manipulate the rest with no worries
         */
        chrg.cpMin += 2;
        chrg.cpMax = cp;
        SendMessage (hwnd, EM_EXSETSEL, 0, (LPARAM) &chrg);
        SendMessage (hwnd, EM_SETCHARFORMAT, SCF_SELECTION|SCF_WORD, (LPARAM)lpcf);

        /*  Run through all the field headers and make them bold */
        
        lpcf->cbSize = sizeof(CHARFORMAT);
        lpcf->dwMask = CFM_BOLD;
        lpcf->dwEffects = CFE_BOLD;

        while (icrg)
        {
            chrg = rgchrg[--icrg];
            SendMessage (hwnd, EM_EXSETSEL, 0, (LPARAM)&chrg);
            SendMessage (hwnd, EM_SETCHARFORMAT, SCF_SELECTION|SCF_WORD, (LPARAM)lpcf);
        }

        /*  Calculate the size of the header */
        
        *lpcch = cp - chrgHdr.cpMin;
        Edit_SetSel (hwnd, 0, 0);
    }
    
    DebugTraceResult (HrInsertOriginalHeader(), hrSuccess);
    return hrSuccess;
}


HRESULT
HrInsertAnnotation (LPSMH lpsmh,
    HWND hwnd,
    UINT rop,
    LPRULE lprl,
    LONG FAR * lpcch)
{
    CHARRANGE chrg = {0};
    EDITSTREAM es = {0};
    LPBYTE lpb;
    RTFS rtfs = {0};
    ULONG cb;
    
    /*  Setup which annotation to use */
    
    if (rop != ropOof)
    {
        cb = lprl->cbRTF;
        lpb = lprl->lpbRTF;
    }
    else
    {
        cb = lpsmh->oof.cbRTF;
        lpb = lpsmh->oof.lpbRTF;
    }

    /*  Stream the bad boy in */
    
    rtfs.cb = 0;
    rtfs.cbMax = cb;
    rtfs.lpb = lpb;
    es.pfnCallback = ReadRTFFromBuffer;
    es.dwCookie = (DWORD)&rtfs;
    SendMessage (hwnd,
        EM_STREAMIN,
        SF_RTF | SFF_SELECTION | SFF_PLAINRTF,
        (LPARAM)&es);

    /*  Calculate the size of what we just streamed in */
    
    SendMessage (hwnd, EM_EXGETSEL, 0, (LPARAM) &chrg);
    *lpcch = chrg.cpMax;

    DebugTraceResult (HrInsertAnnotation(), hrSuccess);
    return hrSuccess;
}


HRESULT
HrTagAttachments (LPSMH lpsmh,
    HWND hwnd,
    LONG dch,
    LPMESSAGE lpmsg)
{
    HRESULT hr;
    CHAR rgch[MAX_PATH] = {0};
    LONG ichPos;
    LPATTACH lpatt = NULL;
    LPMAPITABLE lptbl = NULL;
    LPMESSAGE lpmsgT = NULL;
    LPSPropValue lpval = NULL;
    LPSRowSet lprws = NULL;
    UINT irw;

    hr = lpmsg->lpVtbl->GetAttachmentTable (lpmsg, 0, &lptbl);
    if (HR_FAILED (hr))
        goto ret;

    hr = lptbl->lpVtbl->SetColumns (lptbl, (LPSPropTagArray)&sptTagging, 0);
    if (HR_FAILED (hr))
        goto ret;

    while (TRUE)
    {
        hr = lptbl->lpVtbl->QueryRows (lptbl, 64, 0, &lprws);
        if (HR_FAILED (hr))
            goto ret;

        if (lprws->cRows == 0)
            break;

        for (irw = 0; irw < lprws->cRows; irw++)
        {
            switch (lprws->aRow[irw].lpProps[ipAttMeth].Value.l)
            {
              case ATTACH_OLE:

                lstrcpy (rgch, "<<OLE Object: unknown>>");
                break;

              case ATTACH_EMBEDDED_MSG:

                hr = lpmsg->lpVtbl->OpenAttach (lpmsg,
                                        lprws->aRow[irw].lpProps[ipAttNum].Value.l,
                                        NULL,
                                        0,
                                        &lpatt);
                if (!HR_FAILED (hr))
                {
                    hr = lpatt->lpVtbl->OpenProperty (lpatt,
                                        PR_ATTACH_DATA_OBJ,
                                        &IID_IMessage,
                                        0, 0,
                                        (LPUNKNOWN FAR *)&lpmsgT);
                    if (!HR_FAILED (hr))
                    {
                        /*  Get the subject of the embedded message
                         *  as the tag identifier
                         */
                        hr = HrGetOneProp ((LPMAPIPROP)lpmsgT, PR_SUBJECT, &lpval);
                    }
                }

                wsprintf (rgch, "<<Message: %s>>",
                    HR_FAILED (hr) ? "" : lpval->Value.LPSZ);
                
                (*lpsmh->lpfnFree) (lpval);
                UlRelease (lpmsgT);
                UlRelease (lpatt);
                lpmsgT = NULL;
                lpval = NULL;
                lpatt = NULL;
                break;

              default:
              case ATTACH_BY_VALUE:
              case ATTACH_BY_REFERENCE:

                /*  Use the filename for the attachment tag */

                wsprintf (rgch, "<<File: %s>>",
                    (lprws->aRow[irw].lpProps[ipAttName].ulPropTag == PR_ATTACH_FILENAME)
                          ? lprws->aRow[irw].lpProps[ipAttName].Value.LPSZ
                          : "");
                break;
            }

            /*  Setup the selection such that we replace the attachment
             *  place holder wiht the attachment tag
             */
            ichPos = lprws->aRow[irw].lpProps[ipAttPos].Value.l;
            if (ichPos == -1)
                Edit_SetSel (hwnd, INT_MAX, INT_MAX);
            else
                Edit_SetSel (hwnd, ichPos + dch - 1, ichPos + dch);

            /*  Insert the tag and adjust the offset
             *  of the next attachment tag posiiton.
             */
            dch += CchInsertSz (hwnd, rgch) - 1;

            /*  Free the row data */
            
            (*lpsmh->lpfnFree) (lprws->aRow[irw].lpProps);
        }
        
        hr = hrSuccess;
        (*lpsmh->lpfnFree) (lprws);
        lprws = NULL;
    }
    (*lpsmh->lpfnFree) (lprws);
    lprws = NULL;

ret:
    
    UlRelease (lptbl);
    
    DebugTraceResult (HrTagAttachments(), hr);
    return hr;
}


HRESULT
HrOffsetAttachments (LPSMH lpsmh,
    LONG dch,
    LPMESSAGE lpmsg)
{
    HRESULT hr;
    LPATTACH lpatt = NULL;
    LPMAPITABLE lptbl = NULL;
    LPSRowSet lprws = NULL;
    UINT irw;

    hr = lpmsg->lpVtbl->GetAttachmentTable (lpmsg, 0, &lptbl);
    if (HR_FAILED (hr))
        goto ret;

    hr = lptbl->lpVtbl->SetColumns (lptbl, (LPSPropTagArray)&sptTagging, 0);
    if (HR_FAILED (hr))
        goto ret;

    while (TRUE)
    {
        hr = lptbl->lpVtbl->QueryRows (lptbl, 64, 0, &lprws);
        if (HR_FAILED (hr))
            goto ret;

        if (lprws->cRows == 0)
            break;

        for (irw = 0; irw < lprws->cRows; irw++)
        {
            /*  If the rendering position is not -1, we
             *  want to adjust the positioning by the value
             *  passed in dch
             */
            if (lprws->aRow[irw].lpProps[ipAttPos].Value.l != -1)
            {
                /*  Adjust the positioning, and set in into the attachment */
                
                lprws->aRow[irw].lpProps[ipAttPos].Value.l += dch;

                hr = lpmsg->lpVtbl->OpenAttach (lpmsg,
                                            lprws->aRow[irw].lpProps[ipAttNum].Value.l,
                                            NULL,
                                            MAPI_MODIFY,
                                            &lpatt);
                if (!HR_FAILED (hr))
                {
                    hr = lpatt->lpVtbl->SetProps (lpatt,
                                            1,
                                            &lprws->aRow[irw].lpProps[ipAttPos],
                                            NULL);
                    if (!HR_FAILED (hr))
                    {
                        /*  Save out the new positioning */
                        
                        hr = lpatt->lpVtbl->SaveChanges (lpatt, 0);
                        
                    }
                    UlRelease (lpatt);
                    lpatt = NULL;
                }
                hr = hrSuccess;
            }

            /*  Free the row data */
            
            (*lpsmh->lpfnFree) (lprws->aRow[irw].lpProps);
        }
        
        (*lpsmh->lpfnFree) (lprws);
        lprws = NULL;
    }
    (*lpsmh->lpfnFree) (lprws);
    lprws = NULL;

ret:
    
    UlRelease (lptbl);
    
    DebugTraceResult (HrOffsetAttachments(), hr);
    return hr;
}


HRESULT
HrInsertBody (LPSMH lpsmh,
    HWND hwnd,
    LPSPropValue lpval,
    LPMESSAGE lpmsg)
{
    HRESULT hr = hrSuccess;
    BOOL fUpdated;
    EDITSTREAM es = {0};
    LPSTREAM lpstm = NULL;
    LPSTREAM lpstmRTF = NULL;
    SPropValue val;
    ULONG ulFlags = 0;

    /*  Do PR_BODY iff the store is not RTF_AWARE */
    
    if ((lpval[ipStoreSupport].ulPropTag != PR_STORE_SUPPORT_MASK) ||
        !(lpval[ipStoreSupport].Value.l & STORE_RTF_OK))
    {
        hr = lpmsg->lpVtbl->OpenProperty (lpmsg,
                                PR_BODY,
                                &IID_IStream,
                                0,
                                MAPI_CREATE | MAPI_MODIFY,
                                (LPUNKNOWN FAR *)&lpstm);
        if (HR_FAILED (hr))
            goto ret;

        es.dwCookie = (DWORD)lpstm;
        es.pfnCallback = (EDITSTREAMCALLBACK)lpstm->lpVtbl->Write;
        SendMessage (hwnd, EM_STREAMOUT, SF_TEXT, (LPARAM)&es);
        UlRelease (lpstm);
        lpstm = NULL;

        if (!es.dwError)
            ulFlags |= RTF_SYNC_BODY_CHANGED;
    }

    /*  Add in PR_COMPRESSED_RTF */
    
    hr = lpmsg->lpVtbl->OpenProperty (lpmsg,
                                PR_RTF_COMPRESSED,
                                &IID_IStream,
                                0,
                                MAPI_CREATE | MAPI_MODIFY,
                                (LPUNKNOWN FAR *)&lpstm);
    if (HR_FAILED (hr))
        goto ret;
    
    hr = WrapCompressedRTFStream (lpstm,
                MAPI_MODIFY | (lpval[ipStoreSupport].Value.l & STORE_UNCOMPRESSED_RTF),
                &lpstmRTF);
    if (HR_FAILED (hr))
        goto ret;

    es.dwCookie = (DWORD)lpstmRTF;
    es.pfnCallback = (EDITSTREAMCALLBACK)lpstmRTF->lpVtbl->Write;
    SendMessage (hwnd, EM_STREAMOUT, SF_RTF | SFF_PLAINRTF, (LPARAM)&es);

    hr = lpstmRTF->lpVtbl->Commit (lpstmRTF, 0);
    if (HR_FAILED (hr))
        goto ret;
    
    if (!es.dwError)
        ulFlags |= RTF_SYNC_RTF_CHANGED;

    /*  Sync the RTF and the body iff the store is not RTF aware */

    if ((lpval[ipStoreSupport].ulPropTag != PR_STORE_SUPPORT_MASK) ||
        !(lpval[ipStoreSupport].Value.l & STORE_RTF_OK))
    {
        /*  We are not aware, so we better do a full sync */
        
        hr = RTFSync (lpmsg, ulFlags, &fUpdated);
    }
    else
    {
        /*  If we are aware, then we want to tell the
         *  store that we are completely in sync.  Otherwise,
         *  we could loose our attachment positioning on
         *  RTF aware stores.  And that would be bad.
         */
        val.ulPropTag = PR_RTF_IN_SYNC;
        val.Value.b = TRUE;
        lpmsg->lpVtbl->SetProps (lpmsg, 1, &val, NULL);
    }

ret:

    UlRelease (lpstm);
    UlRelease (lpstmRTF);

    DebugTraceResult (HrInsertBody(), hr);
    return hr;
}


HRESULT
HrBuildRecipient (LPSMH lpsmh,
    LPSPropValue lpval,
    LPMESSAGE lpmsg)
{
    SCODE sc;
    HRESULT hr;
    LPADRLIST lpadr = NULL;
    LPMAPIPROP lpusr = NULL;
    LPSPropValue lpvalUsr = NULL;
    LPSPropValue rgval = NULL;
    UINT cval = 0;
    ULONG ulT;

    /*  Open the recipient up */
    
    hr = lpsmh->lpsess->lpVtbl->OpenEntry (lpsmh->lpsess,
                            lpval->Value.bin.cb,
                            (LPENTRYID)lpval->Value.bin.lpb,
                            NULL, 0,
                            &ulT,
                            (LPUNKNOWN FAR *)&lpusr);
    if (HR_FAILED (hr))
        goto ret;

    /*  Get the properties we need */
    
    hr = lpusr->lpVtbl->GetProps (lpusr,
                            (LPSPropTagArray)&sptUser,
                            0,
                            &ulT,
                            &lpvalUsr);
    if (HR_FAILED (hr))
        goto ret;

    /*  Allocate the adrlist */
    
    if (FAILED (sc = (*lpsmh->lpfnAlloc) (CbNewADRLIST (1), &lpadr)) ||
        FAILED (sc = (*lpsmh->lpfnAlloc) (cpTargetRecipMax * sizeof(SPropValue), &rgval)))
    {
        hr = ResultFromScode (sc);
        goto ret;
    }

    /*  Stuff the properties and add the recipient */
    
    rgval[cval].ulPropTag = PR_ENTRYID;
    rgval[cval].Value = lpval->Value;
    cval++;

    rgval[cval].ulPropTag = PR_DISPLAY_NAME;
    rgval[cval].Value.LPSZ = lpvalUsr[ipDispNm].Value.LPSZ;
    cval++;
    
    if (lpvalUsr[ipAdrTyp].ulPropTag == PR_ADDRTYPE)
    {
        rgval[cval].ulPropTag = PR_ADDRTYPE;
        rgval[cval].Value.LPSZ = lpvalUsr[ipAdrTyp].Value.LPSZ;
        cval++;
    }
    
    if (lpvalUsr[ipEmail].ulPropTag == PR_EMAIL_ADDRESS)
    {
        rgval[cval].ulPropTag = PR_EMAIL_ADDRESS;
        rgval[cval].Value.LPSZ = lpvalUsr[ipEmail].Value.LPSZ;
        cval++;
    }

    if (lpvalUsr[ipSKey].ulPropTag == PR_SEARCH_KEY)
    {
        rgval[cval].ulPropTag = PR_SEARCH_KEY;
        rgval[cval].Value = lpvalUsr[ipSKey].Value;
        cval++;
    }
    
    rgval[cval].ulPropTag = PR_RECIPIENT_TYPE;
    rgval[cval].Value.l = MAPI_TO;
    cval++;
    
    lpadr->cEntries = 1;
    lpadr->aEntries[0].cValues = cval;
    lpadr->aEntries[0].rgPropVals = rgval;
    hr = lpmsg->lpVtbl->ModifyRecipients (lpmsg, MODRECIP_ADD, lpadr);
    if (HR_FAILED (hr))
        goto ret;

ret:
    
    if (lpadr)
    {
        (*lpsmh->lpfnFree) (lpadr->aEntries[0].rgPropVals);
        (*lpsmh->lpfnFree) (lpadr);
    }
    (*lpsmh->lpfnFree) (lpvalUsr);
    UlRelease (lpusr);

    DebugTraceResult (HrBuildRecipient(), hr);
    return hr;
}


HRESULT
HrCreateResponse (LPSMH lpsmh,
    LPRULE lprl,
    LPMAPIFOLDER lpfldr,
    LPMESSAGE lpmsgOrig,
    LPSPropValue lpval,
    LPMESSAGE FAR * lppmsg)
{
    SCODE sc;
    HRESULT hr;
    CHARFORMAT cf = {0};
    HINSTANCE hlib = NULL;
    HWND hwnd = NULL;
    LONG cch = 0;
    LONG cchHdr = 0;
    LPBYTE lpbConvIndex = NULL;
    LPMESSAGE lpmsg = NULL;
    LPREOC lpreoc = NULL;
    LPSPropValue rgval = NULL;
    PARAFORMAT pf = {0};
    TCHAR rgchClass[MAX_PATH];
    TCHAR rgchSubj[MAX_PATH];
    UINT rop;
    ULONG cval = 0;

    *lppmsg = NULL;
    
    /*  Calculate the response operation based on
     *  the supplied rule.  If no rule is supplied
     *  then the response is an out-of-office msg.
     */
    if (lprl)
    {
        Assert (lprl->ulFlags & RULE_AUTO_RESPONSE);
        if (lprl->ulFlags & RULE_AUTO_FORWARD)
        {
            Assert (!(lprl->ulFlags & RULE_AUTO_REPLY));
            rop = ropForward;
        }
        else
        {
            Assert (!(lprl->ulFlags & RULE_AUTO_FORWARD));
            rop = ropReply;
        }
    }
    else
        rop = ropOof;

    /*  Create the response message */
    
    hr = lpfldr->lpVtbl->CreateMessage (lpfldr, NULL, 0, &lpmsg);
    if (HR_FAILED (hr))
        goto ret;

    /*  Create and initialized the RTF edit control */

    hlib = LoadLibrary (RICHEDIT_LIB);
    hwnd = CreateWindow (RICHEDIT_CLASS,
                        "",
                        WS_BORDER|ES_MULTILINE,
                        CW_USEDEFAULT, CW_USEDEFAULT, INT_MAX, INT_MAX,
                        NULL,
                        NULL,
                        lpsmh->hinst,
                        NULL);
    if (!hwnd)
    {
        hr = ResultFromScode (MAPI_E_CALL_FAILED);
        goto ret;
    }

    /*  Create the richedit OLE callback.  If this
     *  fails, it is non-fatal.  It just means that
     *  any OLE objects in the annotation will not
     *  be preserved in then response message.
     */
    if (!FAILED (ScNewRicheditCallback (NULL,
                        lpsmh->lpfnAlloc,
                        lpsmh->lpfnAllocMore,
                        lpsmh->lpfnFree,
                        &lpreoc)))
    {
        /*  We have an OLE callback that we need
         *  to hand off to the richedit control.
         *  Although, the richedit control should
         *  be AddRef()ing the object, we will hold
         *  our reference until we are through with
         *  the edit control.
         */
        SendMessage (hwnd, EM_SETOLECALLBACK, 0, (LPARAM)lpreoc);
    }

    /*  Setup the default character format */
    
    cf.cbSize = sizeof(CHARFORMAT);
    cf.dwMask = CFM_FACE | CFM_SIZE | CFM_COLOR | CFM_BOLD |
                CFM_ITALIC | CFM_UNDERLINE | CFM_STRIKEOUT |
                CFM_OFFSET | CFM_CHARSET;
    cf.dwEffects = CFE_AUTOCOLOR;
    cf.yHeight = 160;
    lstrcpy (cf.szFaceName, "MS Sans Serif");
    cf.bCharSet = DEFAULT_CHARSET;
    SendMessage (hwnd, EM_SETCHARFORMAT, 0, (LPARAM)&cf);

    /*  Copy over the original body if it makes sense to do so */

    if ((rop != ropOof) && (lprl->ulFlags & RULE_AUTO_APPEND_ORIG))
    {
        hr = HrCopyOriginalBody (lpsmh, hwnd, lpmsgOrig, &cch);
        if (HR_FAILED (hr) && (rop == ropForward))
            goto ret;
        
        hr = hrSuccess;
    }

    /*  Create and insert the original message header */

    hr = HrInsertOriginalHeader (lpsmh, hwnd, lpval, &cf, &cchHdr);
    if (HR_FAILED (hr))
        goto ret;

    /*  If this response is not a forward, we will want to
     *  indent the header (and maybe the body) such that they
     *  are offset from the annotation.
     */
    if (rop != ropForward)
    {
        /*  Skip indenting the blankline */
        
        Edit_SetSel (hwnd, 2, INT_MAX);
        pf.cbSize = sizeof(PARAFORMAT);
        pf.dwMask = PFM_STARTINDENT | PFM_RIGHTINDENT | PFM_ALIGNMENT |
                    PFM_OFFSET | PFM_TABSTOPS | PFM_NUMBERING;
        pf.dxOffset = 1440;
        pf.cTabCount = 1;
        pf.rgxTabs[0] = 1440;
        pf.wAlignment = PFA_LEFT;
        pf.dxStartIndent = 1440 / 4;
        SendMessage (hwnd, EM_SETPARAFORMAT, 0, (LPARAM)&pf);
        Edit_SetSel (hwnd, 0, 0);
    }

    /*  Copy over the annotation */

    hr = HrInsertAnnotation (lpsmh, hwnd, rop, lprl, &cch);
    if (HR_FAILED (hr))
        goto ret;

    /*  Tag the attachments for replies */

    if (rop == ropReply)
    {
        hr = HrTagAttachments (lpsmh, hwnd, cchHdr + cch + 3, lpmsgOrig);
        if (HR_FAILED (hr))
            goto ret;
    }

    /*  Allocate space for the new message properties */

    sc = (*lpsmh->lpfnAlloc) (cpTargetResponseMax * sizeof(SPropValue), &rgval);
    if (FAILED (sc))
    {
        hr = ResultFromScode (sc);
        goto ret;
    }

    /*  Build the response subject */

    lstrcpy (rgchSubj, rgszSubjPrfx[rop]);
    lstrcat (rgchSubj, lpval[ipNSubj].Value.LPSZ);
    rgval[cval].ulPropTag = PR_SUBJECT;
    rgval[cval].Value.LPSZ = rgchSubj;
    cval++;

    rgval[cval].ulPropTag = PR_SUBJECT_PREFIX;
    rgval[cval].Value.LPSZ = rgszSubjPrfx[rop];
    cval++;
        
    /*  Build the response message class */

    if (rop == ropOof)
        wsprintf (rgchClass, "Report.%s.OOF", lpval[ipMsgClass].Value.LPSZ);
    else if (rop == ropReply)
        lstrcpy (rgchClass, "IPM.Note.AutoReply");
    else
        lstrcpy (rgchClass, lpval[ipMsgClass].Value.LPSZ);
    rgval[cval].ulPropTag = PR_MESSAGE_CLASS;
    rgval[cval].Value.LPSZ = rgchClass;
    cval++;

    /*  Compose the set of remaining properties */

    rgval[cval].ulPropTag = PR_DELETE_AFTER_SUBMIT;
    rgval[cval].Value.b = TRUE;
    
#ifdef  DEBUG
    rgval[cval].Value.b = GetPrivateProfileInt ("SMH", "DeleteResponses", 1, "MAPIDBG.INI");
#endif

    cval++;

    /*  Tell the store that the message has not
     *  been sent.  Otherwise, since the spooler
     *  is the creater of the message, the store
     *  will treat the message as if it has been
     *  delivered into the store by a transport.
     */
    rgval[cval].ulPropTag = PR_MESSAGE_FLAGS;
    rgval[cval].Value.l = MSGFLAG_UNSENT;
    cval++;
    
    /*  Create appropriate conversation topic and indexes */
    
    if (lpval[ipConvKey].ulPropTag == PR_CONVERSATION_KEY)
        rgval[cval++] = lpval[ipConvKey];
    else
    {
        rgval[cval].ulPropTag = PR_CONVERSATION_TOPIC;
        rgval[cval].Value.LPSZ = lpval[ipNSubj].Value.LPSZ;
        cval++;
    }

    if (lpval[ipConvTopic].ulPropTag == PR_CONVERSATION_TOPIC)
        rgval[cval++] = lpval[ipConvTopic];
    else
    {
        rgval[cval].ulPropTag = PR_CONVERSATION_TOPIC;
        rgval[cval].Value.LPSZ = lpval[ipNSubj].Value.LPSZ;
        cval++;
    }

    if (lpval[ipConvIndex].ulPropTag == PR_CONVERSATION_INDEX)
    {
        sc = ScAddConversationIndex (lpval[ipConvIndex].Value.bin.cb,
                            lpval[ipConvIndex].Value.bin.lpb,
                            &rgval[cval].Value.bin.cb,
                            &lpbConvIndex);
    }
    else
    {
        sc = ScAddConversationIndex (0,
                            NULL,
                            &rgval[cval].Value.bin.cb,
                            &lpbConvIndex);
    }
    if (!FAILED (sc))
    {
        rgval[cval].ulPropTag = PR_CONVERSATION_INDEX;
        rgval[cval].Value.bin.lpb = lpbConvIndex;
        cval++;
    }

    /*  Report tag */
    
    if (lpval[ipReportTag].ulPropTag == PR_REPORT_TAG)
        rgval[cval++] = lpval[ipReportTag];

    /*  Sensitivity */

    if (lpval[ipSensitivity].ulPropTag == PR_SENSITIVITY)
        rgval[cval++] = lpval[ipSensitivity];

    /*  Build response specific properties */
    
    if (rop == ropForward)
    {
        /*  Importance */

        if (lpval[ipImportance].ulPropTag == PR_IMPORTANCE)
            rgval[cval++] = lpval[ipImportance];
        
        /*  Priority */

        if (lpval[ipOrigPriority].ulPropTag == PR_PRIORITY)
            rgval[cval++] = lpval[ipOrigPriority];
        
        /*  Original author */

        if (lpval[ipOrigAuthorName].ulPropTag == PR_ORIGINAL_AUTHOR_NAME)
            rgval[cval++] = lpval[ipOrigAuthorName];
        
        if (lpval[ipOrigAuthorEid].ulPropTag == PR_ORIGINAL_AUTHOR_ENTRYID)
            rgval[cval++] = lpval[ipOrigAuthorEid];
        
        if (lpval[ipOrigAuthorSKey].ulPropTag == PR_ORIGINAL_AUTHOR_SEARCH_KEY)
            rgval[cval++] = lpval[ipOrigAuthorSKey];
        
        /*  Original submit time */

        if (lpval[ipOrigSubmitTime].ulPropTag == PR_ORIGINAL_SUBMIT_TIME)
            rgval[cval++] = lpval[ipOrigSubmitTime];
    }
    
    /*  Set the properties */

    hr = lpmsg->lpVtbl->SetProps (lpmsg, cval, rgval, NULL);
    if (HR_FAILED (hr))
        goto ret;
    
    /*  Insert the body into the mesage directly */

    hr = HrInsertBody (lpsmh, hwnd, lpval, lpmsg);
    if (HR_FAILED (hr))
        goto ret;

    /*  Copy the attachment across in the case of a forward */
    
    if (rop == ropForward)
    {
        hr = lpmsgOrig->lpVtbl->CopyProps(lpmsgOrig,
                        (LPSPropTagArray)&sptForward,
                        0,
                        NULL,
                        (LPIID) &IID_IMessage,
                        lpmsg,
                        0,
                        NULL);
        if (HR_FAILED (hr))
            goto ret;

        hr = HrOffsetAttachments (lpsmh, cchHdr + cch + 2, lpmsg);
        if (HR_FAILED (hr))
            goto ret;
    }

    /*  Do the recipient */

    hr = HrBuildRecipient (lpsmh,
                    (rop == ropForward)
                        ? lprl->lpvalRecip
                        : &lpval[ipSndrEid],
                    lpmsg);
    if (HR_FAILED (hr))
        goto ret;

ret:
    
    if (hwnd)
        DestroyWindow (hwnd);
    
    if (HR_FAILED (hr))
    {
        UlRelease (lpmsg);
        lpmsg = NULL;
    }
    
    if (hlib)
        FreeLibrary (hlib);

    (*lpsmh->lpfnFree) (lpbConvIndex);
    (*lpsmh->lpfnFree) (rgval);
    UlRelease (lpreoc);
    
    *lppmsg = lpmsg;

    DebugTraceResult (HrCreateResponse(), hr);
    return hr;
}


BOOL
FOofRecip (LPOOF lpoof, LPSPropValue lpvalEid)
{
    BOOL fOof = TRUE;
    LPMAPITABLE lptbl = lpoof->lptbl;
    SPropValue val;
    SRestriction res;

    if (lptbl)
    {
#ifdef  DEBUG
        if (!GetPrivateProfileInt ("SMH", "OofAlways", 0, "MAPIDBG.INI"))
#endif
        {
            val.ulPropTag = PR_ENTRYID;
            val.Value = lpvalEid->Value;

            res.rt = RES_PROPERTY;
            res.res.resProperty.relop = RELOP_EQ;
            res.res.resProperty.ulPropTag = PR_ENTRYID;
            res.res.resProperty.lpProp = &val;
            fOof = HR_FAILED (lptbl->lpVtbl->FindRow (lptbl, &res, BOOKMARK_BEGINNING, 0L));
        }
    }
    return fOof;
}


HRESULT
HrRegOofRecip (LPSMH lpsmh, LPOOF lpoof, LPSPropValue lpvalEid)
{
    HRESULT hr;
    LPTABLEDATA lptad = lpoof->lptad;
    SizedSPropTagArray (cpOofMax, sptOofTbl) = {cpOofMax, { PR_ROWID, PR_ENTRYID }};
    SPropValue rgval[cpOofMax];
    SRow rw;

    if (!lptad)
    {
        //  This is the first OOF recip so we need to create the
        //  table of recips
        //
        hr = ResultFromScode (CreateTable ((LPIID)&IID_IMAPITableData,
                            lpsmh->lpfnAlloc,
                            lpsmh->lpfnAllocMore,
                            lpsmh->lpfnFree,
                            NULL,
                            TBLTYPE_DYNAMIC,
                            PR_ROWID,
                            (LPSPropTagArray)&sptOofTbl,
                            (LPTABLEDATA FAR *)&lptad));
        if (HR_FAILED (hr))
            goto ret;
        
        hr = lptad->lpVtbl->HrGetView (lptad, NULL, NULL, 0, &lpoof->lptbl);
        if (HR_FAILED (hr))
        {
            UlRelease (lptad);
            goto ret;
        }
        lpoof->lptad = lptad;
    }

    rgval[ipOofRId].ulPropTag = PR_ROWID;
    rgval[ipOofRId].Value.l = lpoof->cRecips++;
    rgval[ipOofREid].ulPropTag = PR_ENTRYID;
    rgval[ipOofREid].Value = lpvalEid->Value;
    
    rw.cValues = cpOofMax;
    rw.lpProps = rgval; 
    hr = lptad->lpVtbl->HrModifyRow (lptad, &rw);
    if (HR_FAILED (hr))
        goto ret;

ret:

    DebugTraceResult (HrRegOofRecip(), hr);
    return hr;
}


HRESULT
HrGenerateResponse (LPSMH lpsmh, LPRULE lprl, LPMAPIFOLDER lpfldr, LPMESSAGE lpmsg)
{
    HRESULT hr;
    LPSPropValue lpval = NULL;
    LPMESSAGE lpmsgRep = NULL;
    ULONG cval;
    
    hr = lpmsg->lpVtbl->SaveChanges (lpmsg, KEEP_OPEN_READONLY);
    if (HR_FAILED (hr))
        goto ret;
    
    hr = lpmsg->lpVtbl->GetProps (lpmsg, 
                            (LPSPropTagArray)&sptResponse,
                            0,
                            &cval,
                            &lpval);
    if (HR_FAILED (hr))
        goto ret;

    hr = ResultFromScode (MAPI_E_NOT_ME);
    
    if ((lpval[ipMsgClass].ulPropTag == PR_MESSAGE_CLASS) &&
        (lpval[ipMsgClass].Value.LPSZ != NULL) &&
        FLpszContainsLpsz (lpval[ipMsgClass].Value.LPSZ, "Report."))
        goto ret;

    if ((lpval[ipFlags].ulPropTag == PR_MESSAGE_FLAGS) &&
        (lpval[ipFlags].Value.l == MSGFLAG_FROMME))
        goto ret;

    /*  If there is no rule, then we must be OOF'ing */
    if (!lprl && !FOofRecip (&lpsmh->oof, &lpval[ipSndrEid]))
        goto ret;

    if ((lpval[ipRecipMe].ulPropTag == PR_MESSAGE_RECIP_ME) &&
        (lpval[ipRecipMe].Value.b))
    {
        DebugTrace ("SMH: generating response message\n");
        
        if (!lprl)
        {
            /*  Register the OOF recipient */
            
            hr = HrRegOofRecip (lpsmh, &lpsmh->oof, &lpval[ipSndrEid]);
            if (HR_FAILED (hr))
                goto ret;
        }

        /*  Create the response and submit it */
        
        hr = HrCreateResponse (lpsmh,
                        lprl,
                        lpfldr,
                        lpmsg,
                        lpval,
                        &lpmsgRep);
        if (!HR_FAILED (hr))
            hr = lpmsgRep->lpVtbl->SubmitMessage (lpmsgRep, 0);
        
        UlRelease (lpmsgRep);
    }

ret:

    (*lpsmh->lpfnFree) (lpval);
    DebugTraceResult (HrGenerateResponse(), hr);
    return hr;
}


HRESULT
HrInitOof (LPSMH lpsmh, LPSPropValue lpvalAnno, LPSPropValue lpvalRTF)
{
    SCODE sc = MAPI_E_UNCONFIGURED;

    if (lpvalRTF->ulPropTag == PR_SMH_OOF_RTF)
    {
        if (!FAILED (sc = (*lpsmh->lpfnAlloc) (lpvalRTF->Value.bin.cb,
                                    (LPVOID FAR *)&lpsmh->oof.lpbRTF)))
        {
            lpsmh->oof.cbRTF = lpvalRTF->Value.bin.cb;
            memcpy (lpsmh->oof.lpbRTF,
                lpvalRTF->Value.bin.lpb,
                (UINT)lpvalRTF->Value.bin.cb);
        }
    }
    if (lpvalAnno->ulPropTag == PR_SMH_OOF_TEXT)
    {
        if (!FAILED (sc = (*lpsmh->lpfnAlloc) (lstrlen (lpvalAnno->Value.LPSZ) + sizeof(TCHAR),
                                    (LPVOID FAR *)&lpsmh->oof.lpszBody)))
            lstrcpy (lpsmh->oof.lpszBody, lpvalAnno->Value.LPSZ);
    }

    DebugTraceSc (HrInitOof(), sc);
    return ResultFromScode (sc);
}
