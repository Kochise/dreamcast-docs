/*
 *  S M H P S . C
 *
 *  Sample mail handling hook configuration property sheets
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"
#ifndef WIN16
#include <commctrl.h>
#endif

extern LPTSTR lpszConfigEvt;
extern SPropTagArray sptRule;
extern SPropTagArray sptConfigProps;

typedef struct _FILTER
{
    LPSCD               lpscd;              /* back-pointer to config struct */
    
    TCHAR               rgch[cchNameMax];   /* filter name */
    MAPIUID             muid;               /* muid of filter profile section */
    LPPROFSECT          lpsec;              /* profile section object */
    LPSPropValue        lpval;              /* filter property values */

    SCODE               sc;

} FILTER, FAR * LPFILTER;



/*  sptDelete
 *
 *  This is the set of properties that need to be deleted from a rule
 *  profile section any time the rule is edited.  Otherwise, changes in
 *  target folders may not be retained across edits.
 */
const static SizedSPropTagArray (2, sptDelete) =
{
    2,
    {
        PR_RULE_TARGET_ENTRYID,
        PR_RULE_STORE_ENTRYID
    }
};

enum {ipMsgSto, ipDefSto, cpStoTblMax};
const static SizedSPropTagArray (cpStoTblMax, sptStoTbl) =
{
    cpStoTblMax,
    {
        PR_DISPLAY_NAME,
        PR_DEFAULT_STORE
    }
};
            
/*
 *  Common Dialog Functions ---------------------------------------------------
 */

/*
 *  SizeODButtons()
 *
 *  Purpose:
 *
 *      Set the control size for the two owner-draw buttons in the filter
 *      page of the configuration property sheets.
 *
 *  Arguments:
 *
 *      hinst       the DLL instance
 *      hdlg        the dialog in which the buttons will be drawn
 *      id          the dialog ID identifying which buttons to size
 */
VOID
SizeODButtons (HINSTANCE hInst, HWND hdlg, UINT id)
{
    BITMAP  bitmap;
    HBITMAP hbmp;

    if (!(hbmp = LoadBitmap (hInst, MAKEINTRESOURCE(ID_UpArrow))))
        return;
    GetObject (hbmp, sizeof(BITMAP), &bitmap);

    if (id == SMH_FilterPage)
    {
        SetWindowPos (GetDlgItem (hdlg, ID_FilterUp), NULL, 0, 0, bitmap.bmWidth,
            bitmap.bmHeight, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
        SetWindowPos (GetDlgItem (hdlg, ID_FilterDown), NULL, 0, 0, bitmap.bmWidth,
            bitmap.bmHeight, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
    }
    DeleteBitmap (hbmp);
}


/*
 *  DrawODButton()
 *
 *  Purpose:
 *
 *      Draws the button control for either of the two owner-draw buttons
 *      in the filter page of the configuration property sheets.
 *
 *  Arguments:
 *
 *      hinst       the DLL instance
 *      pdi         the DRAWITEMSTRUCT info for drawing the button
 */
VOID
DrawODButton (HINSTANCE hInst, DRAWITEMSTRUCT FAR * lpdi, BOOL fDrawFocus)
{
    HDC hDC;
    HBITMAP hbmpOld;
    HBITMAP hbmpArw;
    WORD wBtnRes;
    BITMAP bitmap;

    Assert (lpdi->CtlType == ODT_BUTTON);
    if (!(hDC = CreateCompatibleDC (lpdi->hDC)))
        return;

    /*  Get the bitmap */

    if (lpdi->itemState & ODS_SELECTED)
        wBtnRes = (lpdi->CtlID == ID_FilterUp) ? ID_UpArrowInv : ID_DownArrowInv;
    else if (lpdi->itemState & ODS_DISABLED)
        wBtnRes = (lpdi->CtlID == ID_FilterUp) ? ID_UpArrowDis : ID_DownArrowDis;
    else
        wBtnRes = (lpdi->CtlID == ID_FilterUp) ? ID_UpArrow : ID_DownArrow;

    /*  blit the bitmap */

    if (!(hbmpArw = CreateMappedBitmap (hInst, wBtnRes, FALSE, NULL, 0)))
        goto ret;
    hbmpOld = SelectObject (hDC, hbmpArw);
    BitBlt (lpdi->hDC, 0, 0, lpdi->rcItem.right - lpdi->rcItem.left,
        lpdi->rcItem.bottom - lpdi->rcItem.top, hDC, 0, 0, SRCCOPY);

    /*  Draw a focus rectangle if the button has the focus */

    if(fDrawFocus && (lpdi->itemState & ODS_FOCUS))
    {
        GetObject (hbmpArw, sizeof(BITMAP), &bitmap);
        lpdi->rcItem.right = bitmap.bmWidth;
        lpdi->rcItem.bottom = bitmap.bmHeight;
        InflateRect (&lpdi->rcItem, -3, -3);
        if (lpdi->itemState & ODS_SELECTED)
            OffsetRect (&lpdi->rcItem, 1, 1);
        DrawFocusRect (lpdi->hDC, &lpdi->rcItem);
    }

    SelectObject (hDC, hbmpOld);
    DeleteBitmap (hbmpArw);
ret:
    DeleteDC (hDC);
}


/*
 *  RTF Stream Callbacks ------------------------------------------------------
 */

DWORD CALLBACK
WriteRTFToBuffer (DWORD dwCookie, LPBYTE lpb, LONG cb, LONG FAR * lpcb)
{
    LPBYTE lpbT = NULL;
    LPRTFS lprtfs = (LPRTFS)dwCookie;

    if ((lprtfs->cb + cb) > lprtfs->cbMax)
    {
        if (!FAILED ((*lprtfs->lpfnAlloc) (lprtfs->cb + (cb * 2), &lpbT)))
        {
            memcpy (lpbT, lprtfs->lpb, (UINT)lprtfs->cb);
            (*lprtfs->lpfnFree) (lprtfs->lpb);
            lprtfs->lpb = lpbT;
            lprtfs->cbMax = lprtfs->cb + (cb * 2);
        }
        else
            return (DWORD)E_FAIL;
    }

    memcpy (lprtfs->lpb + lprtfs->cb, lpb, (UINT)cb);
    lprtfs->cb += cb;
    *lpcb = cb;

    return (DWORD)NOERROR;
}


DWORD CALLBACK
ReadRTFFromBuffer (DWORD dwCookie, LPBYTE lpb, LONG cb, LONG FAR * lpcb)
{
    LPRTFS lprtfs = (LPRTFS)dwCookie;

    cb = min (lprtfs->cb + cb, lprtfs->cbMax) - lprtfs->cb;
    memcpy (lpb, lprtfs->lpb + lprtfs->cb, (UINT)cb);
    lprtfs->cb += cb;
    *lpcb = cb;

    return NOERROR;
}

/*
 *  Store listbox support -----------------------------------------------------
 */
VOID
FillStoresListbox (LPSCD lpscd, HWND hdlg)
{
    HRESULT hr = hrSuccess;
    CHAR rgch[MAX_PATH] = {0};
    HWND hctrl = GetDlgItem (hdlg, ID_Store);
    LPMAPISESSION lpsess;
    LPMAPITABLE lptbl = NULL;
    LPSRowSet lprws = NULL;
    UINT iDef;
    UINT irw;
    
    /*  Logon to the profile for access to the stores table */
    
    if (!(lpsess = lpscd->lpsess))
    {
        hr = MAPILogonEx ((ULONG)GetParent (hdlg),
                    lpscd->lpval[ipProfile].Value.lpszA,
                    NULL,
                    MAPI_NEW_SESSION            |
                         MAPI_EXPLICIT_PROFILE  |
                         MAPI_EXTENDED          |
                         MAPI_NO_MAIL           |
                         MAPI_PASSWORD_UI       |
                         MAPI_TIMEOUT_SHORT,
                    &lpsess);
    }
    if (HR_FAILED (hr))
        goto ret;

    hr = lpsess->lpVtbl->GetMsgStoresTable (lpsess, 0, &lptbl);
    if (HR_FAILED (hr))
        goto ret;

    hr = lptbl->lpVtbl->SetColumns (lptbl, (LPSPropTagArray)&sptStoTbl, 0);
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
            ComboBox_AddString (hctrl,
                lprws->aRow[irw].lpProps[ipMsgSto].Value.lpszA);

            if (lprws->aRow[irw].lpProps[ipDefSto].Value.b)
                lstrcpy (rgch, lprws->aRow[irw].lpProps[ipMsgSto].Value.lpszA);
                    
            /*  Free the row data */
            
            (*lpscd->lpfnFree) (lprws->aRow[irw].lpProps);
        }
        
        (*lpscd->lpfnFree) (lprws);
        lprws = NULL;
    }
    (*lpscd->lpfnFree) (lprws);
    lprws = NULL;

    iDef = ComboBox_FindString (hctrl, -1, rgch);
    ComboBox_SetCurSel (hctrl, iDef == CB_ERR ? 0 : iDef);
    
ret:
    
    lpscd->lpsess = lpsess;
    UlRelease (lptbl);
    return;
}


SCODE
ScPickResponseRecip (HWND hdlg, LPFILTER lpfltr)
{
    HRESULT hr;
    SCODE sc = S_OK;
    ADRPARM adrparm = {0};
    CHAR rgch[cchNameMax];
    LPADRBOOK lpab = NULL;
    LPADRLIST lpadr = NULL;
    LPSCD lpscd = lpfltr->lpscd;
    LPSPropValue lpval = lpfltr->lpval;
    LPSPropValue lpvalT;
    LPTSTR rglpszDestTitles[] = { "To" };
    ULONG rgulDestComps[] = { MAPI_TO };
    UINT ip;

    hr = lpscd->lpsess->lpVtbl->OpenAddressBook (lpscd->lpsess,
                                        0,
                                        NULL,
                                        AB_NO_DIALOG,
                                        &lpab);
    if (!HR_FAILED (hr))
    {
        /*  Iniitalize the adrparm structure */

        wsprintf (rgch, "Auto-Forward Recipient for '%s'", lpfltr->rgch);

        adrparm.ulFlags = ADDRESS_ONE | DIALOG_MODAL | AB_RESOLVE;
        adrparm.lpszCaption = rgch;
        adrparm.lpszNewEntryTitle = rgch;
        adrparm.lpszDestWellsTitle = "Auto-Forward Recipient";
        adrparm.lppszDestTitles = rglpszDestTitles;
        adrparm.lpulDestComps = rgulDestComps;
        adrparm.lpContRestriction = NULL;
        hr = lpab->lpVtbl->Address (lpab, (ULONG FAR*)&hdlg, &adrparm, &lpadr);
        if (!HR_FAILED (hr))
        {
            /*  Zip though and copy out the display name and the
             *  entryid
             */
            lpvalT = lpadr->aEntries[0].rgPropVals;
            for (ip = 0; ip < lpadr->aEntries[0].cValues; lpvalT++, ip++)
            {
                if (lpvalT->ulPropTag == PR_DISPLAY_NAME)
                {
                    sc = (*lpscd->lpfnAllocMore) (lstrlen (lpvalT->Value.LPSZ) + 1,
                        lpval, &(lpval[ipRLFwdRecip].Value.lpszA));
                    if (FAILED (sc))
                        goto ret;

                    lpval[ipRLFwdRecip].ulPropTag = PR_RULE_FORWARD_RECIP;
                    lstrcpy (lpval[ipRLFwdRecip].Value.lpszA,
                        lpvalT->Value.lpszA);
                }
                else if (lpvalT->ulPropTag == PR_ENTRYID)
                {
                    sc = (*lpscd->lpfnAllocMore) (lpvalT->Value.bin.cb, lpval,
                        &(lpval[ipRLFwdEid].Value.bin.lpb));
                    if (FAILED (sc))
                        goto ret;

                    lpval[ipRLFwdEid].ulPropTag = PR_RULE_FORWARD_RECIP_ENTRYID;
                    lpval[ipRLFwdEid].Value.bin.cb = lpvalT->Value.bin.cb;
                    memcpy (lpval[ipRLFwdEid].Value.bin.lpb,
                        lpvalT->Value.bin.lpb,
                        lpvalT->Value.bin.cb);
                }
            }
ret:
            (*lpscd->lpfnFree) (lpadr->aEntries[0].rgPropVals);
            (*lpscd->lpfnFree) (lpadr);
            hr = ResultFromScode (sc);
        }
        UlRelease (lpab);
    }

    DebugTraceResult (ScPickResponseRecip(), hr);
    return GetScode (hr);
}


SCODE
ScResolveResponseRecip (HWND hdlg, LPFILTER lpfltr, LPTSTR lpszRecip)
{
    SCODE sc = S_OK;
    HRESULT hr;
    CHAR rgch[cchNameMax];
    CHAR rgch2[256];
    BOOL fCtl3d = FALSE;
    LPADRBOOK lpab = NULL;
    LPADRLIST lpadr = NULL;
    LPSCD lpscd = lpfltr->lpscd;
    LPSPropValue lpval = lpfltr->lpval;
    LPSPropValue lpvalT;
    UINT ip;

    hr = lpscd->lpsess->lpVtbl->OpenAddressBook (lpscd->lpsess,
                                        0,
                                        NULL,
                                        AB_NO_DIALOG,
                                        &lpab);
    if (HR_FAILED (hr))
        goto ret;

    if (FAILED (sc = (*lpscd->lpfnAlloc) (sizeof(SPropValue), &lpvalT)) ||
        FAILED (sc = (*lpscd->lpfnAlloc) (CbNewADRLIST(1), &lpadr)))
    {
        hr = ResultFromScode (sc);
        goto ret;
    }

    lpadr->cEntries = 1;
    lpadr->aEntries[0].cValues = 1;
    lpadr->aEntries[0].rgPropVals = lpvalT;
    lpvalT[0].ulPropTag = PR_DISPLAY_NAME;
    lpvalT[0].Value.LPSZ = lpszRecip;
    wsprintf (rgch, "Auto-Forward Recipient for '%s'", lpszRecip);
    hr = lpab->lpVtbl->ResolveName (lpab, 0, 0, rgch, lpadr);
    if (HR_FAILED (hr))
    {
        wsprintf (rgch2,
            "Recipient '%s' for auto-forward filter '%s' is ambiguous.\n"
            "Please select a recipient from the Check Names dialog.",
            lpszRecip, lpfltr->rgch);
            
        if (CTL3D_GetVer(lpCtl3D) >= 0x220 && !CTL3D_IsAutoSubclass(lpCtl3D))
            CTL3D_AutoSubclass (lpCtl3D, lpscd->hinst, &fCtl3d);
        MessageBox (hdlg, rgch2, rgch, MB_TASKMODAL | MB_OK | MB_ICONINFORMATION);
        CTL3D_CeaseAutoSubclass(lpCtl3D, fCtl3d);
        
        hr = lpab->lpVtbl->ResolveName (lpab, (ULONG)hdlg, MAPI_DIALOG, rgch, lpadr);
    }

    if (!HR_FAILED (hr))
    {
        /*  Zip though and copy out the display name and the
         *  entryid
         */
        lpvalT = lpadr->aEntries[0].rgPropVals;
        for (ip = 0; ip < lpadr->aEntries[0].cValues; lpvalT++, ip++)
        {
            if (lpvalT->ulPropTag == PR_DISPLAY_NAME)
            {
                sc = (*lpscd->lpfnAllocMore) (lstrlen (lpvalT->Value.LPSZ) + 1,
                    lpval, &(lpval[ipRLFwdRecip].Value.lpszA));
                if (FAILED (sc))
                {
                    hr = ResultFromScode (sc);
                    goto ret;
                }

                lpval[ipRLFwdRecip].ulPropTag = PR_RULE_FORWARD_RECIP;
                lstrcpy (lpval[ipRLFwdRecip].Value.lpszA,
                         lpvalT->Value.lpszA);
            }
            else if (lpvalT->ulPropTag == PR_ENTRYID)
            {
                sc = (*lpscd->lpfnAllocMore) (lpvalT->Value.bin.cb, lpval,
                    &(lpval[ipRLFwdEid].Value.bin.lpb));
                if (FAILED (sc))
                {
                    hr = ResultFromScode (sc);
                    goto ret;
                }

                lpval[ipRLFwdEid].ulPropTag = PR_RULE_FORWARD_RECIP_ENTRYID;
                lpval[ipRLFwdEid].Value.bin.cb = lpvalT->Value.bin.cb;
                memcpy (lpval[ipRLFwdEid].Value.bin.lpb,
                        lpvalT->Value.bin.lpb,
                        lpvalT->Value.bin.cb);
            }
        }
    }

ret:
    
    if (lpadr)
    {
        (*lpscd->lpfnFree) (lpadr->aEntries[0].rgPropVals);
        (*lpscd->lpfnFree) (lpadr);
    }

    UlRelease (lpab);
    DebugTraceResult (ScResolveResponseRecip(), hr);
    return GetScode (hr);
}


/*
 *  Filter Description Property Sheet Page ------------------------------------
 *  
 *  The Filter description page of the configuration property sheets
 *  provides access to the many flags that are available to the SMH
 *  service.
 */

/*
 *  FilterDescriptionPage_INITDAILOG()
 *
 *  Purpose:
 *
 *      Handles the WM_INITDIALOG message for the filter description dialog
 */
BOOL
FilterDescriptionPage_INITDIALOG (HWND hdlg, HWND hwndFocus, LPARAM lParam)
{
    LPFILTER lpfltr = (LPFILTER)(((PROPSHEETPAGE *)lParam)->lParam);
    LPSPropValue lpval;
    HWND hctrl;
    UINT iSto;

    /*  Setup the dialog */

    CTL3D_Subclass (lpCtl3D, hdlg, CTL3D_ALL);
    SetWindowLong (hdlg, DWL_USER, ((PROPSHEETPAGE *)lParam)->lParam);

    Edit_LimitText (GetDlgItem (hdlg, ID_Name), cchNameMax);

    if (lpval = lpfltr->lpval)
    {
        /*  Fill in the display name */
        
        Assert (!IsBadReadPtr (lpval, sizeof(SPropValue) * cpRLMax));
        if (lpval[ipRLDisp].ulPropTag == PR_DISPLAY_NAME)
            Edit_SetText (GetDlgItem (hdlg, ID_Name),
                    lpval[ipRLDisp].Value.LPSZ);

        /*  Check the corresponding rule type.  Note that the rule type
         *  enumeration follows the same order as the corresponding control
         *  ID's such that calculating the rule type is a simple addition to
         *  the base control ID.
         */
        if (lpval[ipRLType].ulPropTag == PR_RULE_TYPE)
            CheckRadioButton (hdlg,
                    ID_AnyRecip,
                    ID_ToRecip,
                    (UINT)(ID_AnyRecip + lpval[ipRLType].Value.l - 1));
            
        /*  Setup the rule data */
        
        if (lpval[ipRLData].ulPropTag == PR_RULE_DATA)
            Edit_SetText (GetDlgItem (hdlg, ID_Value),
                    lpval[ipRLData].Value.bin.lpb);

        /*  Setup the message store display name.  Note that an empty or
         *  missing value here implies uses the default store.
         */
        FillStoresListbox (lpfltr->lpscd, hdlg);
        if (lpval[ipRLStore].ulPropTag == PR_RULE_STORE_DISPLAY_NAME)
        {
            hctrl = GetDlgItem (hdlg, ID_Store);
            iSto = ComboBox_FindString (hctrl, -1, lpval[ipRLStore].Value.lpszA);
            ComboBox_SetCurSel (hctrl, iSto == CB_ERR ? 0 : iSto);
        }

        /*  Setup the target folder path */
        
        if (lpval[ipRLPath].ulPropTag == PR_RULE_TARGET_PATH)
            Edit_SetText (GetDlgItem (hdlg, ID_Folder),
                    lpval[ipRLPath].Value.LPSZ);

        /*  Check the boxes indicated by the rule flags */
        
        if (lpval[ipRLFlags].ulPropTag == PR_RULE_FLAGS)
        {
            CheckDlgButton (hdlg, ID_NotMatch,
                    !!(lpval[ipRLFlags].Value.l & RULE_NOT));
            CheckDlgButton (hdlg, ID_ArchTarg,
                    !!(lpval[ipRLFlags].Value.l & RULE_ARCHIVED));
            CheckDlgButton (hdlg, ID_ArchTargYr,
                    !!(lpval[ipRLFlags].Value.l & RULE_ARCHIVED_BY_YEAR));
            EnableWindow (GetDlgItem (hdlg, ID_ArchTargYr),
                    !!(lpval[ipRLFlags].Value.l & RULE_ARCHIVED));

            if (lpval[ipRLFlags].Value.l & RULE_DELETE)
            {
                CheckRadioButton (hdlg, ID_DeleteMsg, ID_FilterMsg, ID_DeleteMsg);
                EnableWindow (GetDlgItem (hdlg, ID_ArchTarg), FALSE);
                EnableWindow (GetDlgItem (hdlg, ID_ArchTargYr), FALSE);
                EnableWindow (GetDlgItem (hdlg, ID_Folder), FALSE);
                EnableWindow (GetDlgItem (hdlg, ID_ReplyFwd), FALSE);
                EnableWindow (GetDlgItem (hdlg, ID_Store), FALSE);
                EnableWindow (GetDlgItem (hdlg, ID_Txt3), FALSE);
                EnableWindow (GetDlgItem (hdlg, ID_Txt4), FALSE);
            }
            else if (lpval[ipRLFlags].Value.l & RULE_NO_MOVE)
                CheckRadioButton (hdlg, ID_DeleteMsg, ID_FilterMsg, ID_LeaveMsg);
            else
                CheckRadioButton (hdlg, ID_DeleteMsg, ID_FilterMsg, ID_FilterMsg);
        }
        else
        {
            Button_Enable (GetDlgItem (hdlg, ID_ArchTargYr), FALSE);
            CheckRadioButton (hdlg, ID_FilterMsg, ID_DeleteMsg, ID_FilterMsg);
            lpval[ipRLFlags].ulPropTag = PR_RULE_FLAGS;
            lpval[ipRLFlags].Value.l = 0;
        }
    }
    
    return TRUE;
}

/*
 *  FilterDescriptionPage_NOTIFY()
 *
 *  Purpose:
 *
 *      Handles the WM_NOTIFY message for the filter description dialog.
 *      On PSN_APPLY, SMHFlags is recomputed from the checkbox states.
 */
BOOL
FilterDescriptionPage_NOTIFY (HWND hdlg, UINT id, NMHDR FAR * lpnmhdr)
{
    SCODE sc;
    HRESULT hr;
    HWND hctrl;
    LPFILTER lpfltr = (LPFILTER)GetWindowLong (hdlg, DWL_USER);
    LPSCD lpscd = lpfltr->lpscd;
    LPSPropValue lpval = lpfltr->lpval;
    UINT cb;
    UINT i;

    switch (lpnmhdr->code)
    {
      case PSN_KILLACTIVE:
        if (IsDlgButtonChecked (hdlg, ID_FilterMsg) &&
            Edit_GetTextLength (GetDlgItem(hdlg, ID_Folder)) == 0)
        {
            MessageBox(hdlg, "You have to enter folder name", 
                        "Sample Spooler Hook", 
                        MB_TASKMODAL | MB_OK | MB_ICONSTOP);
            SetWindowLong(hdlg, DWL_MSGRESULT, TRUE);
            return TRUE;
        }  
        break;

      case PSN_RESET:
      case PSN_SETACTIVE:
      default:

        break;

      case PSN_APPLY:
                
        /*  Turn off any flags we may be setting down the road */

        lpval[ipRLFlags].Value.l &= ~(RULE_ARCHIVED |
                                      RULE_ARCHIVED_BY_YEAR |
                                      RULE_NOT |
                                      RULE_DELETE |
                                      RULE_NO_MOVE);

        /*  Get the rule name */

        hctrl = GetDlgItem (hdlg, ID_Name);
        cb = Edit_GetTextLength (hctrl) + 1;
        if(cb != 1)
        {
            Edit_GetText (hctrl, lpfltr->rgch, cb);

            lpval[ipRLDisp].ulPropTag = PR_DISPLAY_NAME;
            lpval[ipRLDisp].Value.LPSZ = lpfltr->rgch;
        }

        /*  Rule type */

        lpval[ipRLType].ulPropTag = PR_RULE_TYPE;
        for (i = RL_ANY_RECIP; i < RL_TYPE_MAX; i++)
        {
            if (IsDlgButtonChecked (hdlg, ID_AnyRecip + i - 1))
            {   
                lpval[ipRLType].Value.l = i;
                break;
            }
        }

        /*  Rule data */

        hctrl = GetDlgItem (hdlg, ID_Value);
        cb = Edit_GetTextLength (hctrl) + 1;
        sc = (*lpscd->lpfnAllocMore) (cb, lpval, &lpval[ipRLData].Value.bin.lpb);
        if (FAILED (sc))
            goto ret;

        lpval[ipRLData].ulPropTag = PR_RULE_DATA;
        lpval[ipRLData].Value.bin.cb = (ULONG)cb;
        Edit_GetText (hctrl, lpval[ipRLData].Value.bin.lpb, cb);

        /*  Target store EID */

        lpval[ipRLSEid].ulPropTag = PR_NULL;

        /*  Target store */

        hctrl = GetDlgItem (hdlg, ID_Store);
        cb = ComboBox_GetTextLength (hctrl) + 1;
        sc = (*lpscd->lpfnAllocMore) (cb, lpval, &(lpval[ipRLStore].Value.lpszA));
        if (FAILED (sc))
            goto ret;

        lpval[ipRLStore].ulPropTag = PR_RULE_STORE_DISPLAY_NAME;
        ComboBox_GetText (hctrl, lpval[ipRLStore].Value.LPSZ, cb);

        /*  Target folder EID */

        lpval[ipRLEid].ulPropTag = PR_NULL;

        /*  Target folder */

        hctrl = GetDlgItem (hdlg, ID_Folder);
        cb = Edit_GetTextLength (hctrl) + 1;
        sc = (*lpscd->lpfnAllocMore) (cb, lpval, &(lpval[ipRLPath].Value.lpszA));
        if (FAILED (sc))
            goto ret;

        lpval[ipRLPath].ulPropTag = PR_RULE_TARGET_PATH;
        Edit_GetText (hctrl, lpval[ipRLPath].Value.LPSZ, cb);

        /*  Flags */

        if (IsDlgButtonChecked (hdlg, ID_ArchTarg))
        {
            lpval[ipRLFlags].Value.l |= RULE_ARCHIVED;
            if (IsDlgButtonChecked (hdlg, ID_ArchTargYr))
                lpval[ipRLFlags].Value.l |= RULE_ARCHIVED_BY_YEAR;
        }
        if (IsDlgButtonChecked (hdlg, ID_NotMatch))
            lpval[ipRLFlags].Value.l |= RULE_NOT;
        if (IsDlgButtonChecked (hdlg, ID_DeleteMsg))
            lpval[ipRLFlags].Value.l |= RULE_DELETE;
        if (IsDlgButtonChecked (hdlg, ID_LeaveMsg))
            lpval[ipRLFlags].Value.l |= RULE_NO_MOVE;

        /*  Delete the folder and store entryid's properties */

        lpfltr->lpsec->lpVtbl->DeleteProps (lpfltr->lpsec,
                                    (LPSPropTagArray)&sptDelete,
                                    NULL);
            
        /*  Set the values and save changes on the profile section */

        hr = lpfltr->lpsec->lpVtbl->SetProps (lpfltr->lpsec,
                                            cpRLMax,
                                            lpval,
                                            NULL);
        if (FAILED (sc = GetScode (hr)))
            goto ret;

        hr = lpfltr->lpsec->lpVtbl->SaveChanges (lpfltr->lpsec, KEEP_OPEN_READWRITE);
        if (FAILED (sc = GetScode (hr)))
            goto ret;

ret:        
        /*  Set error code into filter */
    
        lpfltr->sc = sc;
        return !FAILED (sc);

      case PSN_HELP:

        return TRUE;
    }

    return FALSE;
}


/*
 *  FilterDescriptionPage_COMMAND()
 *
 *  Purpose:
 *
 *      Handles the WM_COMMAND message for the filter description dialog
 *
 *      IMPORTANT: This function relies on the dialog control IDs as
 *      defined in _SMH.RH.  The yearly archive checkboxes must have an
 *      ID that is one greater than the companion checkbox.
 */
BOOL
FilterDescriptionPage_COMMAND (HWND hdlg, UINT id, HWND hwndCtl, UINT codeNotify)
{
    BOOL fCheck;
    
    switch (id)
    {
      case ID_LeaveMsg:
      case ID_FilterMsg:
      case ID_DeleteMsg:

        /*  Enable windows based on the check state of the ID_FilterMsg */
        
        fCheck = IsDlgButtonChecked (hdlg, ID_FilterMsg);
        EnableWindow (GetDlgItem (hdlg, ID_ArchTarg), fCheck);
        EnableWindow (GetDlgItem (hdlg, ID_ArchTargYr),
            fCheck && IsDlgButtonChecked (hdlg, ID_ArchTarg));
        EnableWindow (GetDlgItem (hdlg, ID_Folder), fCheck);
        EnableWindow (GetDlgItem (hdlg, ID_Store), fCheck);
        EnableWindow (GetDlgItem (hdlg, ID_Txt3), fCheck);
        EnableWindow (GetDlgItem (hdlg, ID_Txt4), fCheck);
        break;

      case ID_ArchTarg:

        /*  Enable yearly sub-archive button when the archiving is enabled */
        
        EnableWindow (GetDlgItem (hdlg, ID_ArchTargYr),
            IsDlgButtonChecked (hdlg, ID_ArchTarg));
        
        break;

      default:

        return TRUE;
    }
    
    PropSheet_Changed (GetParent (hdlg), hdlg);
    return TRUE;
}


/*
 *  FilterDescriptionPageProc()
 *
 *  Purpose:
 *
 *      Dispatches window messages to the proper function for processing
 */
BOOL CALLBACK
FilterDescriptionPageProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
      case WM_INITDIALOG:

        FHandleWm (FilterDescriptionPage, hdlg, INITDIALOG, wParam, lParam);
        return TRUE;

      case WM_COMMAND:

        FHandleWm (FilterDescriptionPage, hdlg, COMMAND, wParam, lParam);
        break;

      case WM_NOTIFY:

        return FHandleWm (FilterDescriptionPage, hdlg, NOTIFY, wParam, lParam);
    }

    return FALSE;
}


BOOL
ResponsePage_INITDIALOG (HWND hdlg, HWND hwndFocus, LPARAM lParam)
{
    EDITSTREAM es = {0};
    LPFILTER lpfltr = (LPFILTER)(((PROPSHEETPAGE *)lParam)->lParam);
    LPFORMATBAR lpfb;
    LPSCD lpscd = lpfltr->lpscd;
    LPSPropValue lpval;
    RTFS rtfs = {0};
    
    /*  Set the user data component to point to the SCD structure */
    
    CTL3D_Subclass (lpCtl3D, hdlg, CTL3D_ALL);
    SetWindowLong (hdlg, DWL_USER, ((PROPSHEETPAGE *)lParam)->lParam);

    /*  Setup the toolbar for the annotation */

    if (!FAILED (ScCreateToolbar (lpscd, hdlg, ID_Annotation, FALSE, &lpfb)) &&
        !FAILED (ScNewRicheditCallback (lpfb,
                                lpscd->lpfnAlloc,
                                lpscd->lpfnAllocMore,
                                lpscd->lpfnFree,
                                &lpfb->lpreoc)))
    {
        SendMessage (GetDlgItem (hdlg, ID_Annotation),
            EM_SETOLECALLBACK,
            0,
            (LPARAM)lpfb->lpreoc);
    }

    /*  Init the dialog fields */

    if (lpval = lpfltr->lpval)
    {
        /*  Fill in the display name */
        
        Assert (!IsBadReadPtr (lpval, sizeof(SPropValue) * cpRLMax));

        CheckDlgButton (hdlg, ID_ReplyFwd,
            !!(lpval[ipRLFlags].Value.l & RULE_AUTO_RESPONSE));
        
        /*  Check the boxes indicated by the rule flags */
        
        if (!(lpval[ipRLFlags].Value.l & RULE_AUTO_FORWARD))
        {
            CheckRadioButton (hdlg, ID_Reply, ID_Forward, ID_Reply);
            EnableWindow (GetDlgItem (hdlg, ID_Recip), FALSE);
            EnableWindow (GetDlgItem (hdlg, ID_PickRecip), FALSE);
        }
        else
            CheckRadioButton (hdlg, ID_Reply, ID_Forward, ID_Forward);

        /*  Setup the fowarding recipient */
        
        if (lpval[ipRLFwdRecip].ulPropTag == PR_RULE_FORWARD_RECIP)
            Edit_SetText (GetDlgItem (hdlg, ID_Recip),
                    lpval[ipRLFwdRecip].Value.LPSZ);

        /*  How 'bout the RTF */
        
        if (lpval[ipRLRepFwdRTF].ulPropTag == PR_RULE_REP_FWD_RTF)
        {
            rtfs.cbMax = lpval[ipRLRepFwdRTF].Value.bin.cb;
            rtfs.lpb = lpval[ipRLRepFwdRTF].Value.bin.lpb;
            es.pfnCallback = ReadRTFFromBuffer;
            es.dwCookie = (DWORD)&rtfs;
            SendMessage (GetDlgItem (hdlg, ID_Annotation),
                EM_STREAMIN,
                SF_RTF | SFF_SELECTION | SFF_PLAINRTF,
                (LPARAM)&es);
        }
        else if (lpval[ipRLRepFwd].ulPropTag == PR_RULE_REP_FWD_TEXT)
            Edit_SetText (GetDlgItem (hdlg, ID_Annotation),
                lpval[ipRLRepFwd].Value.LPSZ);
    }
    
    return TRUE;
}


BOOL
ResponsePage_NOTIFY (HWND hdlg, UINT id, NMHDR FAR * lpnmhdr)
{
    SCODE sc = S_OK;
    HRESULT hr;
    CHAR rgch[cchNameMax];
    EDITSTREAM es = {0};
    HWND hctrl;
    LPFILTER lpfltr = (LPFILTER)GetWindowLong (hdlg, DWL_USER);
    LPSCD lpscd = lpfltr->lpscd;
    LPSPropValue lpval = lpfltr->lpval;
    RTFS rtfs = {0};
    SizedSPropTagArray (1, spt) = {1, { PR_RULE_FORWARD_RECIP_ENTRYID }};
    UINT cb;
    
    switch (lpnmhdr->code)
    {
      case PSN_KILLACTIVE:
      case PSN_RESET:
      case PSN_SETACTIVE:
      default:

        break;

      case PSN_APPLY:

        if (lpval = lpfltr->lpval)
        {
            /*  Turn off any flags we may be setting down the road */

            lpval[ipRLFlags].Value.l &= ~(RULE_AUTO_RESPONSE |
                                          RULE_AUTO_APPEND_ORIG |
                                          RULE_AUTO_REPLY |
                                          RULE_AUTO_FORWARD);
            
            /*  See if we are enabled */
            
            if (IsDlgButtonChecked (hdlg, ID_ReplyFwd))
                lpval[ipRLFlags].Value.l |= RULE_AUTO_RESPONSE;

            /*  Grab the annotation in both plain text and RTF */

            hctrl = GetDlgItem (hdlg, ID_Annotation);
            cb = Edit_GetTextLength (hctrl) + 1;
            sc = (*lpscd->lpfnAllocMore) (cb, lpval, &lpval[ipRLRepFwd].Value.LPSZ);
            if (FAILED (sc))
                goto ret;
        
            lpval[ipRLRepFwd].ulPropTag = PR_RULE_REP_FWD_TEXT;
            Edit_GetText (hctrl, lpval[ipRLRepFwd].Value.LPSZ, cb);

            rtfs.cb = 0;
            rtfs.cbMax = 0;
            rtfs.lpfnAlloc = lpscd->lpfnAlloc;
            rtfs.lpfnFree = lpscd->lpfnFree;
            es.pfnCallback = WriteRTFToBuffer;
            es.dwCookie = (DWORD)&rtfs;
            SendMessage (hctrl, EM_STREAMOUT, SF_RTF | SFF_PLAINRTF, (LPARAM)&es);
            if (!es.dwError)
            {
                /* make a copy of the RTF data for long term storage */

                sc = (*lpscd->lpfnAllocMore) (rtfs.cb,
                                lpval,
                                &lpval[ipRLRepFwdRTF].Value.bin.lpb);
                if (!FAILED (sc))
                {
                    lpval[ipRLRepFwdRTF].ulPropTag = PR_RULE_REP_FWD_RTF;
                    lpval[ipRLRepFwdRTF].Value.bin.cb = rtfs.cb;
                    memcpy (lpval[ipRLRepFwdRTF].Value.bin.lpb, rtfs.lpb, (UINT)rtfs.cb);
                }
                else
                    lpval[ipRLRepFwdRTF].ulPropTag = PR_NULL;
            }

            (*lpscd->lpfnFree) (rtfs.lpb);

            /*  Delete props that need to be recalc'd */
            
            lpval[ipRLFwdEid].ulPropTag = PR_NULL;
            lpfltr->lpsec->lpVtbl->DeleteProps (lpfltr->lpsec,
                (LPSPropTagArray)&spt, NULL);
            
            /*  Grab the recipient information */

            hctrl = GetDlgItem (hdlg, ID_Recip);
            hctrl = GetDlgItem (hdlg, ID_Recip);
            cb = Edit_GetTextLength (hctrl) + 1;
            Edit_GetText (hctrl, rgch, cb);

            /*  See if what we have cached will work */

            if (IsDlgButtonChecked (hdlg, ID_ReplyFwd) &&
                IsDlgButtonChecked (hdlg, ID_Forward))
            {
                if ((lpval[ipRLFwdEid].ulPropTag != PR_RULE_FORWARD_RECIP_ENTRYID) ||
                    (lpval[ipRLFwdRecip].ulPropTag != PR_RULE_FORWARD_RECIP) ||
                    lstrcmp (lpval[ipRLFwdRecip].Value.lpszA, rgch))
                {
                    /*  We do not have a resolved recipient */

                    (void) ScResolveResponseRecip (GetParent (hdlg), lpfltr, rgch);
                }
            }

            /*  Set the response type */

            lpval[ipRLFlags].Value.l |= RULE_AUTO_APPEND_ORIG |
                (IsDlgButtonChecked (hdlg, ID_Reply)
                     ? RULE_AUTO_REPLY
                     : RULE_AUTO_FORWARD);

            /*  Set the values and save changes on the profile section */

            hr = lpfltr->lpsec->lpVtbl->SetProps (lpfltr->lpsec,
                                            cpRLMax,
                                            lpval,
                                            NULL);
            if (FAILED (sc = GetScode (hr)))
                goto ret;

            hr = lpfltr->lpsec->lpVtbl->SaveChanges (lpfltr->lpsec, KEEP_OPEN_READWRITE);
            if (FAILED (sc = GetScode (hr)))
                goto ret;
        }
ret:
        lpfltr->sc = sc;
        return !FAILED(sc);

      case PSN_HELP:

        return TRUE;
    }

    return FALSE;
}


BOOL
ResponsePage_COMMAND (HWND hdlg, UINT id, HWND hwndCtl, UINT codeNotify)
{
    BOOL fCheck = FALSE;
    LPFILTER lpfltr = (LPFILTER)GetWindowLong (hdlg, DWL_USER);

    if (FDoRTFCommand (GetDlgItem (hdlg, ID_Frame), id, codeNotify))
        return TRUE;
    
    switch (id)
    {
      case ID_Forward:
        
        fCheck = TRUE;

        /*  Fall through */
        
      case ID_Reply:

        EnableWindow (GetDlgItem (hdlg, ID_Recip), fCheck);
        EnableWindow (GetDlgItem (hdlg, ID_PickRecip), fCheck);
        break;

      case ID_PickRecip:

        if (!FAILED (ScPickResponseRecip (GetParent (hdlg), lpfltr)))
        {
            Edit_SetText (GetDlgItem (hdlg, ID_Recip),
                    lpfltr->lpval[ipRLFwdRecip].Value.LPSZ);
        }
    }

    PropSheet_Changed (GetParent (hdlg), hdlg);
    return TRUE;
}


BOOL CALLBACK
ResponsePageProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
      case WM_INITDIALOG:

        FHandleWm (ResponsePage, hdlg, INITDIALOG, wParam, lParam);
        return TRUE;

      case WM_COMMAND:

        FHandleWm (ResponsePage, hdlg, COMMAND, wParam, lParam);
        break;

      case WM_NOTIFY:

        return FHandleWm (ResponsePage, hdlg, NOTIFY, wParam, lParam);
    }

    return FALSE;
}


BOOL
SoundsPage_INITDIALOG (HWND hdlg, HWND hwndFocus, LPARAM lParam)
{
    LPFILTER lpfltr = (LPFILTER)(((PROPSHEETPAGE *)lParam)->lParam);
    LPSPropValue lpval;
    UINT i;
    
    /*  Set the user data component to point to the SCD structure */
    
    CTL3D_Subclass (lpCtl3D, hdlg, CTL3D_ALL);
    SetWindowLong (hdlg, DWL_USER, ((PROPSHEETPAGE *)lParam)->lParam);

    /*  Init the dialog fields */

    if (lpval = lpfltr->lpval)
    {
        /*  See if we are enabled */
        
        CheckDlgButton (hdlg, ID_Sound,
            !!(lpval[ipRLFlags].Value.l & RULE_PLAY_SOUNDS));
        
        /*  Fill in the display name */
        
        Assert (!IsBadReadPtr (lpval, sizeof(SPropValue) * cpRLMax));
        Edit_SetText (GetDlgItem (hdlg, ID_Name), ((LPSCD)lParam)->rgch);

        /*  Setup the sound entries */

        for (i = 0; i < csndMax; i++)
        {
            if (lpval[ipRLLoPri + i].ulPropTag == sptRule.aulPropTag[ipRLLoPri + i])
            {
                Edit_SetText (GetDlgItem (hdlg, ID_LoPri + i),
                    lpval[ipRLLoPri + i].Value.LPSZ);
            }
        }
    }

    return TRUE;
}


BOOL
SoundsPage_NOTIFY (HWND hdlg, UINT id, NMHDR FAR * lpnmhdr)
{
    SCODE sc = S_OK;
    HRESULT hr;
    HWND hctrl;
    LPFILTER lpfltr = (LPFILTER)GetWindowLong (hdlg, DWL_USER);
    LPSCD lpscd = lpfltr->lpscd;
    LPSPropValue lpval;
    UINT cb;
    UINT i;
    
    switch (lpnmhdr->code)
    {
      case PSN_KILLACTIVE:
      case PSN_RESET:
      case PSN_SETACTIVE:
      default:

        break;

      case PSN_APPLY:

        if (lpval = lpfltr->lpval)
        {
            /*  Turn off any flags we may be setting down the road */

            lpval[ipRLFlags].Value.l &= ~RULE_PLAY_SOUNDS;

            /*  See if we are enabled */
            
            if (IsDlgButtonChecked (hdlg, ID_Sound))
                lpval[ipRLFlags].Value.l |= RULE_PLAY_SOUNDS;
            
            /*  Grab the sounds */

            for (i = 0; i < csndMax; i++)
            {
                hctrl = GetDlgItem (hdlg, ID_LoPri + i);
                cb = Edit_GetTextLength (hctrl) + 1;
                sc = (*lpscd->lpfnAllocMore) (cb, lpval, &(lpval[ipRLLoPri + i].Value.lpszA));
                if (FAILED (sc))
                    break;

                lpval[ipRLLoPri + i].ulPropTag = sptRule.aulPropTag[ipRLLoPri + i];
                Edit_GetText (hctrl, lpval[ipRLLoPri + i].Value.LPSZ, cb);
            }
            
            /*  Set the values and save changes on the profile section */

            hr = lpfltr->lpsec->lpVtbl->SetProps (lpfltr->lpsec,
                                            cpRLMax,
                                            lpval,
                                            NULL);
            if (!FAILED (sc = GetScode (hr)))
            {
                hr = lpfltr->lpsec->lpVtbl->SaveChanges (lpfltr->lpsec, KEEP_OPEN_READWRITE);
                sc = GetScode (hr);
            }
        }

        lpfltr->sc = sc;
        return !FAILED(sc);

      case PSN_HELP:

        return TRUE;
    }

    return FALSE;
}


BOOL
SoundsPage_COMMAND (HWND hdlg, UINT id, HWND hwndCtl, UINT codeNotify)
{
    PropSheet_Changed (GetParent (hdlg), hdlg);
    return TRUE;
}


BOOL CALLBACK
SoundsPageProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
      case WM_INITDIALOG:

        FHandleWm (SoundsPage, hdlg, INITDIALOG, wParam, lParam);
        return TRUE;

      case WM_COMMAND:

        FHandleWm (SoundsPage, hdlg, COMMAND, wParam, lParam);
        break;

      case WM_NOTIFY:

        return FHandleWm (SoundsPage, hdlg, NOTIFY, wParam, lParam);
    }

    return FALSE;
}


/*
 *  HrEditFilterProperties()
 *
 *  Purpose:
 *
 *      Brings up the filter description dialog for the rule properties
 *      found in the profile section muid passed in.
 *
 *  Arguments:
 *
 *      lpscd       SMH dialog structure
 *      hdlg        parent dialog for the filter description
 *      fEdit       indicates lpscd->muid contains a section to edit
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrEditFilterProperties (LPFILTER lpfltr, HWND hdlg, BOOL fEdit)
{
    HRESULT hr = hrSuccess;
    ULONG cval;
    UINT ipg;
    PROPSHEETPAGE psp[] =
    {
        {
            sizeof(PROPSHEETPAGE),
            PSP_USETITLE,
            lpfltr->lpscd->hinst,
            MAKEINTRESOURCE(SMH_PropertiesPage),
            NULL,
            MAKEINTRESOURCE(SMH_GeneralTab),
            FilterDescriptionPageProc,
            0,
            NULL,
            NULL
        },
        {
            sizeof(PROPSHEETPAGE),
            PSP_USETITLE,
            lpfltr->lpscd->hinst,
            MAKEINTRESOURCE(SMH_ResponsePage),
            NULL,
            MAKEINTRESOURCE(SMH_ResponseTab),
            ResponsePageProc,
            0,
            NULL,
            NULL
        },
        {
            sizeof(PROPSHEETPAGE),
            PSP_USETITLE,
            lpfltr->lpscd->hinst,
            MAKEINTRESOURCE(SMH_SoundsPage),
            NULL,
            MAKEINTRESOURCE(SMH_SoundsTab),
            SoundsPageProc,
            0,
            NULL,
            NULL
        },
    };
    PROPSHEETHEADER psh =
    {
        sizeof(PROPSHEETHEADER),
        PSH_PROPSHEETPAGE | PSH_PROPTITLE,
        GetParent (hdlg),
        lpfltr->lpscd->hinst,
        NULL,
        NULL,
        sizeof(psp) / sizeof(PROPSHEETPAGE),
        0,
        (LPCPROPSHEETPAGE)&psp
    };

    /*  If we are creating a new entry, then we first need to create
     *  new profile section UID.
     */
    if (!fEdit)
    {
        lstrcpy (lpfltr->rgch, "Untitled");
        hr = lpfltr->lpscd->lpsup->lpVtbl->NewUID (lpfltr->lpscd->lpsup, &lpfltr->muid);
        if (HR_FAILED (hr))
            goto ret;
    }

    /*  Open the rules profile section */
    
    hr = lpfltr->lpscd->lpadmin->lpVtbl->OpenProfileSection (lpfltr->lpscd->lpadmin,
                                        &lpfltr->muid,
                                        NULL,
                                        MAPI_MODIFY,
                                        &lpfltr->lpsec);
    if (HR_FAILED (hr))
        goto ret;

    /*  Get the set of properties describing the rule */

    hr = lpfltr->lpsec->lpVtbl->GetProps (lpfltr->lpsec,
                                        (LPSPropTagArray)&sptRule,
                                        0,
                                        &cval,
                                        &lpfltr->lpval);
    if (HR_FAILED (hr))
        goto ret;

    /*  set property sheet data */

    psh.pszCaption = lpfltr->rgch;
    for (ipg = 0; ipg < psh.nPages; ipg++)
        psp[ipg].lParam = (LPARAM)lpfltr;

    switch (PropertySheet (&psh))
    {
      case -1:

        hr = ResultFromScode (MAPI_E_CALL_FAILED);
        break;

      case 0:

        hr = ResultFromScode (MAPI_E_USER_CANCEL);
        break;
    }

ret:

    /*  On success, the profile sub-section has been updated and
     *  committed.  We can now release the resources held for access
     *  to the section.
     */
    (*lpfltr->lpscd->lpfnFree) (lpfltr->lpval);
    UlRelease (lpfltr->lpsec);
    lpfltr->lpval = NULL;
    lpfltr->lpsec = NULL;

    DebugTraceResult (HrEditFilterProperties(), hr);
    return hr;
}


/*
 *  Filters Property Sheet Page -----------------------------------------------
 *  
 *  The filters page of the configuration property sheets provides a list
 *  of the exisitng filter AND the order in which they are processed.  The 
 *  page allows the user to delete, edit or create rules as well as customize
 *  the order in which the rules are processed.
 *  
 *  The list is based on the profile section property PR_SMH_RULES.  This
 *  property is a multi-valued binary property that contains rule section
 *  muids.  These muids are paired with the values from PR_SMH_RULE_NAMES.
 *  
 *  Furthermore, there exists an additional property, PR_SMH_ORPHANED_RULES,   
 *  that is used to maintain references to rules that have been deleted.
 *  
 *  When page processing is complete -- when either OK, APPLY or CANCEL
 *  is chosen, the properties related to this page are set in the profile
 *  and the changes are saved.  Note that switching out of the filters
 *  page to another page includes an implicit APPLY before switching
 *  pages.
 */

/*
 *  EnableFilterPageCtrls()
 *
 *  Purpose:
 *
 *      Enables the set of buttons on the filter page based on the
 *      current selection in the filter list dialog
 */
VOID
EnableFilterPageCtrls (HWND hdlg)
{
    BOOL fDelete;
    BOOL fEdit;
    BOOL fDown = FALSE;
    BOOL fUp = FALSE;
    HWND hctrl = GetDlgItem (hdlg, ID_FilterOrderLB);
    UINT isel = ListBox_GetCurSel (hctrl);

    if (fDelete = fEdit = (isel != LB_ERR))
    {
        /*  If we are at the top, "move up" is not very realistic */

        fUp = (isel != 0);

        /*  If we are at the bottom, "move down" is not very realistic */

        fDown = (isel != (UINT)(ListBox_GetCount (hctrl) - 1));
    }

    /*  Enable the controls */

    Button_Enable (GetDlgItem (hdlg, ID_FilterUp), fUp);
    Button_Enable (GetDlgItem (hdlg, ID_FilterDown), fDown);
    Button_Enable (GetDlgItem (hdlg, ID_EditFilter), fEdit);
    Button_Enable (GetDlgItem (hdlg, ID_RmvFilter), fDelete);
    return;
}


/*
 *  FilterPage_INITDIALOG()
 *
 *  Purpose:
 *
 *      Handles the WM_INITDIALOG message for the filter description
 *      dialog.
 *
 *      The current list of filters are processed and the name is
 *      retrieved for use in the dialog.
 */
BOOL
FilterPage_INITDIALOG (HWND hdlg, HWND hwndFocus, LPARAM lParam)
{
    SCODE sc = S_OK;
    BOOL fInit;
    HWND hctrl;
    LPBYTE lpmuid;
    LPSCD lpscd = (LPSCD)(((PROPSHEETPAGE *)lParam)->lParam);
    LPSPropValue lpval;
    LPTSTR lpsz;
    UINT cb;
    UINT crl;
    UINT irl = 0;

    /*  Setup the dialog */

    CTL3D_Subclass(lpCtl3D, hdlg, CTL3D_ALL);
    SizeODButtons (lpscd->hinst, hdlg, SMH_FilterPage);
    SetWindowLong (hdlg, DWL_USER, ((PROPSHEETPAGE *)lParam)->lParam);

    /*  Load the filter LBX and create the mapping */

    if ((lpval = lpscd->lpval) && (lpval[ipRules].ulPropTag == PR_SMH_RULES))
    {
        hctrl = GetDlgItem (hdlg, ID_FilterOrderLB);

        crl = (UINT)lpval[ipRules].Value.MVbin.cValues;
        Assert (crl == lpval[ipNames].Value.MVbin.cValues);
        
        if (fInit = !lpscd->lpbin)
        {
            /*  As we fill the listbox we are going to make a copy of the
             *  of the multi-valued arrays for use while editing
             */
            
            cb = (crl + GROW_SIZE) * sizeof(LPTSTR);
            if (FAILED (sc = (*lpscd->lpfnAlloc) (cb, (LPVOID FAR *)&lpscd->lppsz)))
                goto ret;

            cb = (crl + GROW_SIZE) * sizeof(SBinary);
            if (FAILED (sc = (*lpscd->lpfnAlloc) (cb, &lpscd->lpbin)))
                goto ret;

            lpscd->crlMax = crl + GROW_SIZE;
        }
        
        for (irl = 0; irl < crl; irl++)
        {
            if (fInit)
            {
                /*  Allocate space (linked) for the copy */
                
                lpsz = lpval[ipNames].Value.MVSZ.lppszA[irl];
                lpmuid = lpval[ipRules].Value.MVbin.lpbin[irl].lpb;
                cb = lstrlen (lpval[ipNames].Value.MVSZ.lppszA[irl]) + 1;
                if (FAILED (sc = (*lpscd->lpfnAlloc) (cb, &lpscd->lppsz[irl])) ||
                    FAILED (sc = (*lpscd->lpfnAlloc) (sizeof(MAPIUID), &lpscd->lpbin[irl].lpb)))
                    break;
            }
            else
                lpsz = lpscd->lppsz[irl];

            /*  Add the item to the list and copy it local (maybe) */
            
            if ((ListBox_AddString (hctrl, lpsz) != LB_ERRSPACE) &&
                (ListBox_SetItemData (hctrl, irl, irl) != LB_ERR) &&
                fInit)
            {
                lstrcpy (lpscd->lppsz[irl], lpsz);
                lpscd->lpbin[irl].cb = sizeof(MAPIUID);
                memcpy (lpscd->lpbin[irl].lpb, lpmuid, sizeof(MAPIUID));
            }
        }

        /*  Set the selection to the first filter in the list */

        ListBox_SetCurSel (hctrl, 0);
    }
    else
        sc = MAPI_E_UNCONFIGURED;

ret:
    
    EnableFilterPageCtrls (hdlg);
    lpscd->crl = irl;
    lpscd->sc = sc;
    return TRUE;
}


/*
 *  FilterPage_NOTIFY()
 *
 *  Purpose:
 *
 *      Handles the WM_NOTIFY message for the filter description dialog.
 *      On PSN_APPLY, the filter order is computed and set in PR_SMH_RULES.
 */
BOOL
FilterPage_NOTIFY (HWND hdlg, UINT id, NMHDR FAR * lpnmhdr)
{
    HRESULT hr;
    LPSCD lpscd;
    SPropValue rgval[2];

    switch (lpnmhdr->code)
    {
      case PSN_KILLACTIVE:
      case PSN_RESET:
      case PSN_SETACTIVE:
      default:

        break;

      case PSN_APPLY:

        DebugTrace ("SMH: saving contents of filter page\n");

        /*  Setup and save out the new properties */

        lpscd = (LPSCD)GetWindowLong (hdlg, DWL_USER);
        
        if(lpscd->crl)
        {
            rgval[0].ulPropTag = PR_SMH_RULES;
            rgval[0].Value.MVbin.cValues = lpscd->crl;
            rgval[0].Value.MVbin.lpbin = lpscd->lpbin;
            rgval[1].ulPropTag = PR_SMH_RULE_NAMES;
            rgval[1].Value.MVSZ.cValues = lpscd->crl;
            rgval[1].Value.MVSZ.lppszA = lpscd->lppsz;
            
            hr = lpscd->lpsec->lpVtbl->SetProps (lpscd->lpsec, 2, rgval, NULL);
        }
        else
        {
            SizedSPropTagArray(2, taga) = {2, {PR_SMH_RULES, PR_SMH_RULE_NAMES}};
            LPSPropProblemArray pProbl = NULL;

            hr = lpscd->lpsec->lpVtbl->DeleteProps(lpscd->lpsec, 
                                            (LPSPropTagArray)&taga, &pProbl);
            if (!hr)
            {
                if(pProbl)
                {
                    DebugTraceProblems("SMH: DeleteProps :", pProbl);
                    MAPIFreeBuffer(pProbl);
                }
            }
        }

        if (!HR_FAILED (hr))
            hr = lpscd->lpsec->lpVtbl->SaveChanges (lpscd->lpsec, KEEP_OPEN_READWRITE);

        lpscd->sc = GetScode (hr);
        return TRUE;

      case PSN_HELP:

        return TRUE;
    }

    return FALSE;
}


/*
 *  FilterPage_COMMAND()
 *
 *  Purpose:
 *
 *      Handles the WM_COMMAND message for the filter description dialog.
 */
BOOL
FilterPage_COMMAND (HWND hdlg, UINT id, HWND hwndCtl, UINT codeNotify)
{
    SCODE sc;
    FILTER fltr = {0};
    HWND hctrl = GetDlgItem (hdlg, ID_FilterOrderLB);
    LPBYTE lpb;
    LPSBinary lpbin;
    LPSCD lpscd = (LPSCD)GetWindowLong (hdlg, DWL_USER);
    LPTSTR FAR * lppsz;
    LPTSTR lpsz;
    UINT cb;
    UINT irl = 0;
    INT nAdj;

    irl = ListBox_GetCurSel (hctrl);
    switch (id)
    {
      case ID_NewFilter:

        if (lpscd->crl == lpscd->crlMax)
        {
            /*  We need to make room for new entries */

            cb = (lpscd->crl + GROW_SIZE) * sizeof(LPVOID);
            if (FAILED (sc = (*lpscd->lpfnAlloc) (cb, (LPVOID FAR *)&lppsz)))
                break;
            memcpy (lppsz, lpscd->lppsz, lpscd->crl * sizeof(LPTSTR));
                
            cb = (lpscd->crl + GROW_SIZE) * sizeof(SBinary);
            if (FAILED (sc = (*lpscd->lpfnAlloc) (cb, &lpbin)))
                break;
            memcpy (lpbin, lpscd->lpbin, lpscd->crl * sizeof(SBinary));

            /*  Swap out the old for the new */

            (*lpscd->lpfnFree) (lpscd->lppsz);
            (*lpscd->lpfnFree) (lpscd->lpbin);
            lpscd->crlMax += GROW_SIZE;
            lpscd->lppsz = lppsz;
            lpscd->lpbin = lpbin;

        }
        irl = lpscd->crl;

        /*  Get the new filter */

        fltr.lpscd = lpscd;
        if (!FAILED (sc = GetScode (HrEditFilterProperties (&fltr, hdlg, FALSE))))
        {
            /*  Allocate space for the new rule identifiers */
            
            if (!FAILED (sc = (*lpscd->lpfnAlloc) (lstrlen (fltr.rgch) + 1, &lpscd->lppsz[irl])) &&
                !FAILED (sc = (*lpscd->lpfnAlloc) (sizeof(MAPIUID), &lpscd->lpbin[irl].lpb)))
            {
                if ((ListBox_AddString (hctrl, fltr.rgch) != LB_ERR) &&
                    (ListBox_SetItemData (hctrl, irl, irl) != LB_ERR))
                {
                    /*  Copy the identifiers across */
                    
                    lstrcpy (lpscd->lppsz[irl], fltr.rgch);
                    memcpy (lpscd->lpbin[irl].lpb, &fltr.muid, sizeof(MAPIUID));
                    lpscd->lpbin[irl].cb = sizeof(MAPIUID);

                    ListBox_SetCurSel (hctrl, irl);
                    PropSheet_Changed (GetParent (hdlg), hdlg);
                    lpscd->crl++;
                }
                else
                    sc = MAPI_E_CALL_FAILED;
            }
        }
        lpscd->sc = sc;
        break;

      case ID_FilterOrderLB:

        if (codeNotify != LBN_DBLCLK)
            break;

        /*  Fall through to edit */
             
      case ID_EditFilter:

        /*  Copy the muid out for use in the dialog */

        fltr.lpscd = lpscd;
        lstrcpy (fltr.rgch, lpscd->lppsz[irl]);
        memcpy (&fltr.muid, lpscd->lpbin[irl].lpb, sizeof(MAPIUID));
        if (!FAILED (sc = GetScode (HrEditFilterProperties (&fltr, hdlg, TRUE))))
        {
            /*  The name may have changed.  If so, update it */

            if (lstrcmp (fltr.rgch, lpscd->lppsz[irl]))
            {
                /*  See if we need a bigger buffer and alloc one */

                if ((cb = lstrlen (fltr.rgch)) > (UINT)lstrlen (lpscd->lppsz[irl]))
                {
                    if (!FAILED (sc = (*lpscd->lpfnAlloc) (cb + 1, &lpsz)))
                    {
                        (*lpscd->lpfnFree) (lpscd->lppsz[irl]);
                        lstrcpy (lpsz, fltr.rgch);
                        lpscd->lppsz[irl] = lpsz;
                    }
                    else
                        break;
                }
                else
                    lstrcpy (lpscd->lppsz[irl], fltr.rgch);
                
                if ((ListBox_DeleteString (hctrl, irl) == LB_ERR) ||
                    (ListBox_InsertString (hctrl, irl, fltr.rgch) == LB_ERRSPACE) ||
                    (ListBox_SetItemData (hctrl, irl, irl) == LB_ERR))
                    sc = MAPI_E_NOT_ENOUGH_MEMORY;

                ListBox_SetCurSel (hctrl, irl);
            }
            PropSheet_Changed (GetParent (hdlg), hdlg);
        }
        lpscd->sc = sc;
        break;

      case ID_RmvFilter:

        /*  Remove the string and collapse the local copies */

        if ((irl != LB_ERR) && (ListBox_DeleteString (hctrl, irl) != LB_ERR))
        {
            (*lpscd->lpfnFree) (lpscd->lpbin[irl].lpb);
            (*lpscd->lpfnFree) (lpscd->lppsz[irl]);
            lpscd->crl -= 1;
            if (irl != lpscd->crl)
            {
                memcpy (&lpscd->lppsz[irl], &lpscd->lppsz[irl + 1],
                    (lpscd->crl - irl) * sizeof(LPTSTR));
                memcpy (&lpscd->lpbin[irl], &lpscd->lpbin[irl + 1],
                    (lpscd->crl - irl) * sizeof(SBinary));
            }
        }
        else
            MessageBeep (0);

        ListBox_SetCurSel (hctrl, irl);
        PropSheet_Changed (GetParent (hdlg), hdlg);
        break;

      case ID_FilterUp:
      case ID_FilterDown:

        /*  Ensure we really have something to move */
        
        if (id == ID_FilterUp)
        {
            nAdj = -1;
            if ((irl == LB_ERR) || (irl == 0))
                break;
        }
        else
        {
            nAdj = 1;
            if ((irl == LB_ERR) || (irl == (UINT)(ListBox_GetCount (hctrl) - 1)))
                break;
        }

        /*  Move it */

        if ((ListBox_DeleteString (hctrl, irl + nAdj) == LB_ERR) ||
            (ListBox_InsertString (hctrl, irl, lpscd->lppsz[irl + nAdj]) == LB_ERRSPACE))
        {
            ListBox_ResetContent (hctrl);
            lpscd->sc = MAPI_E_CALL_FAILED;
            break;
        }
        else
            ListBox_SetItemData (hctrl, irl, irl);

        /*  Move it in the local copies */

        lpsz = lpscd->lppsz[irl + nAdj];
        lpscd->lppsz[irl + nAdj] = lpscd->lppsz[irl];
        lpscd->lppsz[irl] = lpsz;
        
        lpb = lpscd->lpbin[irl + nAdj].lpb;
        lpscd->lpbin[irl + nAdj].lpb = lpscd->lpbin[irl].lpb;
        lpscd->lpbin[irl].lpb = lpb;

        /*  Set the selection to the new position */
        
        ListBox_SetCurSel (hctrl, irl + nAdj);
        PropSheet_Changed (GetParent (hdlg), hdlg);
        break;

      case ID_Export:

        ScExportFilters (lpscd, GetParent (hdlg));
        break;

      case ID_Import:

        ScImportFilters (lpscd, GetParent (hdlg), hctrl);
        PropSheet_Changed (GetParent (hdlg), hdlg);
        break;

      default:
        break;
    }

    EnableFilterPageCtrls (hdlg);
    return TRUE;
}


/*
 *  FilterPageProc()
 *
 *  Purpose:
 *
 *      Dispatches window messages to the proper function for processing
 */
BOOL CALLBACK
FilterPageProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
      case WM_INITDIALOG:

        FHandleWm (FilterPage, hdlg, INITDIALOG, wParam, lParam);
        return TRUE;

      case WM_COMMAND:

        FHandleWm (FilterPage, hdlg, COMMAND, wParam, lParam);
        return TRUE;

      case WM_DRAWITEM:

        DrawODButton (((LPSCD)GetWindowLong (hdlg, DWL_USER))->hinst,
            (DRAWITEMSTRUCT FAR *)lParam, TRUE);
        break;

      case WM_NOTIFY:

        return FHandleWm (FilterPage, hdlg, NOTIFY, wParam, lParam);
    }

    return FALSE;
}


/*
 *  General Property Sheet Page -----------------------------------------------
 *  
 *  The general page of the configuration property sheets provides access
 *  to the many flags that are available to the SMH service.  The dialog
 *  is used to set the value for PR_SMH_FLAGS.
 */

/*
 *  GeneralPage_INITDAILOG()
 *
 *  Purpose:
 *
 *      Handles the WM_INITDIALOG message for the filter description dialog
 */
BOOL
GeneralPage_INITDIALOG (HWND hdlg, HWND hwndFocus, LPARAM lParam)
{
    LPSCD lpscd = (LPSCD)(((PROPSHEETPAGE *)lParam)->lParam);
    LPSPropValue lpval = lpscd->lpval;
    ULONG ulFlags;

    CTL3D_Subclass(lpCtl3D, hdlg, CTL3D_ALL);
    SetWindowLong (hdlg, DWL_USER, ((PROPSHEETPAGE *)lParam)->lParam);

    ulFlags = (lpval[ipFlags].ulPropTag == PR_SMH_FLAGS)
                ? lpval[ipFlags].Value.l
                : 0;

    /*  Enable/check the checkboxes based on SMH flags */

    CheckDlgButton (hdlg, ID_AddToPab, !!(ulFlags & SMH_ADD_TO_PAB));
    CheckDlgButton (hdlg, ID_Deleted, !!(ulFlags & SMH_FILTER_DELETED));
    CheckDlgButton (hdlg, ID_DeletedYr, !!(ulFlags & SMH_FILTER_DELETED_YR));
    CheckDlgButton (hdlg, ID_Inbound, !!(ulFlags & SMH_FILTER_INBOUND));
    CheckDlgButton (hdlg, ID_SentMail, !!(ulFlags & SMH_FILTER_SENTMAIL));
    CheckDlgButton (hdlg, ID_SentMailYr, !!(ulFlags & SMH_FILTER_SENTMAIL_YR));
    CheckDlgButton (hdlg, ID_Unread, !!(ulFlags & SMH_UNREAD_VIEWER));
    EnableWindow (GetDlgItem (hdlg, ID_DeletedYr), !!(ulFlags & SMH_FILTER_DELETED));
    EnableWindow (GetDlgItem (hdlg, ID_SentMailYr), !!(ulFlags & SMH_FILTER_SENTMAIL));
    lpval[ipFlags].ulPropTag = PR_SMH_FLAGS;
    lpval[ipFlags].Value.l = ulFlags;
    return TRUE;
}

/*
 *  GeneralPage_NOTIFY()
 *
 *  Purpose:
 *
 *      Handles the WM_NOTIFY message for the filter description dialog.
 *      On PSN_APPLY, SMHFlags is recomputed from the checkbox states.
 */
BOOL
GeneralPage_NOTIFY (HWND hdlg, UINT id, NMHDR FAR * lpnmhdr)
{
    HRESULT hr;
    LPSCD lpscd = (LPSCD)GetWindowLong (hdlg, DWL_USER);
    SPropValue val = {0};

    switch (lpnmhdr->code)
    {
      case PSN_KILLACTIVE:
      case PSN_RESET:
      case PSN_SETACTIVE:
      default:

        break;

      case PSN_APPLY:

        DebugTrace ("SMH: saving contents of general page\n");
        
        /*  Calc the value for PR_SMH_FLAGS */

        if (IsDlgButtonChecked (hdlg, ID_SentMail))
        {
            val.Value.l |= SMH_FILTER_SENTMAIL;
            if (IsDlgButtonChecked (hdlg, ID_SentMailYr))
                val.Value.l |= SMH_FILTER_SENTMAIL_YR;
            else
                val.Value.l &= ~SMH_FILTER_SENTMAIL_YR;
        }
        else
            val.Value.l &= ~(SMH_FILTER_SENTMAIL | SMH_FILTER_SENTMAIL_YR);

        if (IsDlgButtonChecked (hdlg, ID_Deleted))
        {
            val.Value.l |= SMH_FILTER_DELETED;
            if (IsDlgButtonChecked (hdlg, ID_DeletedYr))
                val.Value.l |= SMH_FILTER_DELETED_YR;
            else
                val.Value.l &= ~SMH_FILTER_DELETED_YR;
        }
        else
            val.Value.l &= ~(SMH_FILTER_DELETED | SMH_FILTER_DELETED_YR);

        if (IsDlgButtonChecked (hdlg, ID_Inbound))
            val.Value.l |= SMH_FILTER_INBOUND;
        else
            val.Value.l &= ~SMH_FILTER_INBOUND;

        if (IsDlgButtonChecked (hdlg, ID_Unread))
            val.Value.l |= SMH_UNREAD_VIEWER;
        else
            val.Value.l &= ~SMH_UNREAD_VIEWER;

        if (IsDlgButtonChecked (hdlg, ID_AddToPab))
            val.Value.l |= SMH_ADD_TO_PAB;
        else
            val.Value.l &= ~SMH_ADD_TO_PAB;

        val.ulPropTag = PR_SMH_FLAGS;
        hr = lpscd->lpsec->lpVtbl->SetProps (lpscd->lpsec,
                                        1,
                                        &val,
                                        NULL);
        if (!HR_FAILED (hr))
            hr = lpscd->lpsec->lpVtbl->SaveChanges (lpscd->lpsec, KEEP_OPEN_READWRITE);
        
        lpscd->sc = GetScode (hr);
        return TRUE;

      case PSN_HELP:

        return TRUE;
    }

    return FALSE;
}


/*
 *  GeneralPage_COMMAND()
 *
 *  Purpose:
 *
 *      Handles the WM_COMMAND message for the filter description dialog
 *
 *      IMPORTANT: This function relies on the dialog control IDs as
 *      defined in _SMH.RH.  The yearly archive checkboxes must have an
 *      ID that is one greater than the companion checkbox.
 */
BOOL
GeneralPage_COMMAND (HWND hdlg, UINT id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
      case ID_SentMail:
      case ID_Deleted:

        EnableWindow (GetDlgItem (hdlg, id + 1),
                    !!IsDlgButtonChecked (hdlg, id));
        break;

      case ID_SentMailYr:
      case ID_DeletedYr:
      case ID_Inbound:
      case ID_Unread:
      case ID_AddToPab:

        break;

      default:

        return TRUE;
    }
    PropSheet_Changed (GetParent (hdlg), hdlg);
    return TRUE;
}


/*
 *  GeneralPageProc()
 *
 *  Purpose:
 *
 *      Dispatches window messages to the proper function for processing
 */
BOOL CALLBACK
GeneralPageProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
      case WM_INITDIALOG:

        FHandleWm (GeneralPage, hdlg, INITDIALOG, wParam, lParam);
        return TRUE;

      case WM_COMMAND:

        FHandleWm (GeneralPage, hdlg, COMMAND, wParam, lParam);
        break;

      case WM_NOTIFY:

        return FHandleWm (GeneralPage, hdlg, NOTIFY, wParam, lParam);
    }

    return FALSE;
}


/*
 *  Exclussion Edit Dialog ----------------------------------------------------
 *  
 *  The exclusion edit dialog alows the user to input a single entry into
 *  the list of excluded message classes.
 *  
 *  All information is passed via the SCD structure.
 *  
 *      lpscd->rgch     [IN\OUT]    contains the message class to exclude
 *  
 *  The caller is responsible for merging the new value into the
 *  exclusion list.
 */

/*
 *  ExclusionEdit_INITDIALOG()
 *
 *  Purpose:
 *
 *      Handles the WM_INITDIALOG message for the filter description dialog
 */
BOOL
ExclusionEdit_INITDIALOG (HWND hdlg, HWND hwndFocus, LPARAM lParam)
{
    CTL3D_Subclass(lpCtl3D, hdlg, CTL3D_ALL);
    SetWindowLong (hdlg, DWL_USER, lParam);

    /*  Enable/limit the exclusion edit */

    Edit_LimitText (GetDlgItem (hdlg, ID_ExclusionClass), cchNameMax - 1);
    Button_Enable (GetDlgItem (hdlg, IDOK), FALSE);
    return TRUE;
}


/*
 *  ExclusionEdit_COMMAND()
 *
 *  Purpose:
 *
 *      Handles the WM_COMMAND message for the filter description dialog
 */
BOOL ExclusionEdit_COMMAND (HWND hdlg, UINT id, HWND hwndCtl, UINT codeNotify)
{
    LPSCD lpscd = (LPSCD)GetWindowLong (hdlg, DWL_USER);
    HWND hctrl = GetDlgItem (hdlg, ID_ExclusionClass);

    switch (id)
    {
      case IDOK:

        Edit_GetText (hctrl, lpscd->rgch, cchNameMax);
        break;

      case IDCANCEL:

        break;

      default:

        return FALSE;
    }

    EndDialog (hdlg, id);
    return TRUE;
}


/*
 *  ExclusionEditProc()
 *
 *  Purpose:
 *
 *      Dispatches window messages to the proper function for processing
 */
BOOL CALLBACK
ExclusionEditProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND hctrl = GetDlgItem (hdlg, ID_ExclusionClass);

    switch (msg)
    {
      case WM_INITDIALOG:

        FHandleWm (ExclusionEdit, hdlg, INITDIALOG, wParam, lParam);
        return TRUE;

      case WM_COMMAND:

        FHandleWm (ExclusionEdit, hdlg, COMMAND, wParam, lParam);
        break;
    }
    Button_Enable (GetDlgItem (hdlg, IDOK), !!Edit_GetTextLength (hctrl));
    return FALSE;
}


/*
 *  Exclussion Page Property Sheet --------------------------------------------
 *  
 *  The exclusions page exposes the list of message classes that are
 *  excluded from inbound filtering.  The property that correlates to 
 *  the list is PR_SMH_EXCLUSIONS.  Any actions required against this
 *  property are processed within the context of this property sheet.
 */

/*
 *  ExclusionPage_INITDIALOG()
 *
 *  Purpose:
 *
 *      Handles the WM_INITDIALOG message for the filter description dialog
 */
BOOL
ExclusionPage_INITDIALOG (HWND hdlg, HWND hwndFocus, LPARAM lParam)
{
    LPSCD lpscd = (LPSCD)(((PROPSHEETPAGE *)lParam)->lParam);
    HWND hctrl = GetDlgItem (hdlg, ID_ExclusionLB);
    UINT isz;

    CTL3D_Subclass(lpCtl3D, hdlg, CTL3D_ALL);
    SetWindowLong (hdlg, DWL_USER, ((PROPSHEETPAGE *)lParam)->lParam);

    /*  Populate the exclusion listbox */

    if (lpscd->lpval[ipExc].ulPropTag == PR_SMH_EXCLUSIONS)
        for (isz = 0; isz < lpscd->lpval[ipExc].Value.MVSZ.cValues; isz++)
            ListBox_AddString (hctrl, lpscd->lpval[ipExc].Value.MVSZ.LPPSZ[isz]);

    return TRUE;
}


/*
 *  ExclusionPage_NOTIFY()
 *
 *  Purpose:
 *
 *      Handles the WM_NOTIFY message for the filter description dialog
 */
BOOL
ExclusionPage_NOTIFY (HWND hdlg, UINT id, NMHDR FAR * lpnmhdr)
{
    SCODE sc;
    LPSCD lpscd = (LPSCD)GetWindowLong (hdlg, DWL_USER);
    HWND hctrl = GetDlgItem (hdlg, ID_ExclusionLB);
    LPSPropValue lpval;
    LPTSTR FAR * lppsz = NULL;
    SizedSPropTagArray (1, spt) = {1, { PR_SMH_EXCLUSIONS }};
    UINT cex;
    UINT iex;

    switch (lpnmhdr->code)
    {
      case PSN_KILLACTIVE:
      case PSN_RESET:
      case PSN_SETACTIVE:
      default:

        break;

      case PSN_APPLY:

        DebugTrace ("SMH: saving contents of exclusions page\n");

        /*  Assemble a new PR_SMH_EXCLUSIONS property value */

        lpval = &lpscd->lpval[ipExc];
        cex = ListBox_GetCount (hctrl);
        if (cex)
        {
            sc = (*lpscd->lpfnAllocMore) (cex * sizeof(LPTSTR),
                                    lpscd->lpval,
                                    (LPVOID FAR *)&lppsz);
            if (!FAILED (sc))
            {
                lpval->ulPropTag = PR_SMH_EXCLUSIONS;
                lpval->Value.MVSZ.LPPSZ = lppsz;
                for (iex = 0; iex < cex; iex++, lppsz++)
                {
                    sc = (*lpscd->lpfnAllocMore) (ListBox_GetTextLen (hctrl, iex) + 1,
                                        lpscd->lpval,
                                        lppsz);
                    if (FAILED (sc))
                        break;

                    ListBox_GetText (hctrl, iex, *lppsz);
                }
                lpval->Value.MVSZ.cValues = iex;

                /*  Set the new value */

                sc = GetScode (lpscd->lpsec->lpVtbl->SetProps (lpscd->lpsec,
                                                        1,
                                                        lpval,
                                                        NULL));
                if (!FAILED (sc))
                    sc = GetScode (lpscd->lpsec->lpVtbl->SaveChanges (lpscd->lpsec,
                                                        KEEP_OPEN_READWRITE));
            }
            lpscd->sc = sc;
        }
        else
        {
            lpval->ulPropTag = PR_NULL;
            lpscd->lpsec->lpVtbl->DeleteProps (lpscd->lpsec, (LPSPropTagArray)&spt, NULL);
        }
        return TRUE;

      case PSN_HELP:

        return TRUE;
    }

    return FALSE;
}


/*
 *  ExclusionPage_COMMAND()
 *
 *  Purpose:
 *
 *      Handles the WM_COMMAND message for the filter description dialog
 */
BOOL
ExclusionPage_COMMAND (HWND hdlg, UINT id, HWND hwndCtl, UINT codeNotify)
{
    LPSCD lpscd = (LPSCD)GetWindowLong (hdlg, DWL_USER);
    HWND hctrl = GetDlgItem (hdlg, ID_ExclusionLB);
    UINT iex;

    switch (id)
    {
      case ID_NewExclusion:

        id = DialogBoxParam (lpscd->hinst,
                    MAKEINTRESOURCE (SMH_ExclusionEdit),
                    GetParent(hdlg),
                    ExclusionEditProc,
                    (LPARAM)lpscd);
        if (id == IDOK)
            ListBox_SetCurSel (hctrl, ListBox_AddString (hctrl, lpscd->rgch));

        PropSheet_Changed (GetParent (hdlg), hdlg);
        break;

      case ID_RmvExclusion:

        iex = ListBox_GetCurSel (hctrl);
        ListBox_DeleteString (hctrl, iex);
        ListBox_SetCurSel (hctrl, iex);
        PropSheet_Changed (GetParent (hdlg), hdlg);
        break;

      default:

        break;
    }
    return TRUE;
}


/*
 *  ExclusionPageProc()
 *
 *  Purpose:
 *
 *      Dispatches window messages to the proper function for processing
 */
BOOL CALLBACK
ExclusionPageProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
      case WM_INITDIALOG:

        FHandleWm (ExclusionPage, hdlg, INITDIALOG, wParam, lParam);
        return TRUE;

      case WM_COMMAND:

        FHandleWm (ExclusionPage, hdlg, COMMAND, wParam, lParam);
        return TRUE;

      case WM_NOTIFY:

        return FHandleWm (ExclusionPage, hdlg, NOTIFY, wParam, lParam);
    }

    return FALSE;
}


/*
 *  Out-Of-Office Page Property Sheet -----------------------------------------
 *  
 *  The Out-of-office page exposes access to the OOF utility of SMH.  
 *  The enabling and message text are both modified via this page.
 *  The corresponding properties are stored in PR_SMH_OOF_ENABLED,
 *  PR_SMH_OOF_TEXT and PR_SMH_OOF_RTF.
 *  
 *  The RTF component of the OOF message uses the RICHEDIT implementation
 *  that is available as a part of the WIN95 system.
 */

/*
 *  OofPage_INITDIALOG()
 *
 *  Purpose:
 *
 *      Handles the WM_INITDIALOG message for the filter description dialog
 */
BOOL
OofPage_INITDIALOG (HWND hdlg, HWND hwndFocus, LPARAM lParam)
{
    EDITSTREAM es = {0};
    LPSCD lpscd = (LPSCD)(((PROPSHEETPAGE *)lParam)->lParam);
    LPFORMATBAR lpfb;
    RTFS rtfs = {0};

    CTL3D_Subclass(lpCtl3D, hdlg, CTL3D_ALL);
    SetWindowLong (hdlg, DWL_USER, ((PROPSHEETPAGE *)lParam)->lParam);

    if (!FAILED (ScCreateToolbar (lpscd, hdlg, ID_OofText, TRUE, &lpfb)) &&
        !FAILED (ScNewRicheditCallback (lpfb,
                                lpscd->lpfnAlloc,
                                lpscd->lpfnAllocMore,
                                lpscd->lpfnFree,
                                &lpfb->lpreoc)))
    {
        SendMessage (GetDlgItem (hdlg, ID_OofText),
            EM_SETOLECALLBACK,
            0,
            (LPARAM)lpfb->lpreoc);
    }

    if (lpscd->lpval[ipOofRtf].ulPropTag == PR_SMH_OOF_RTF)
    {
        rtfs.cbMax = lpscd->lpval[ipOofRtf].Value.bin.cb;
        rtfs.lpb = lpscd->lpval[ipOofRtf].Value.bin.lpb;
        es.pfnCallback = ReadRTFFromBuffer;
        es.dwCookie = (DWORD)&rtfs;
        SendMessage (GetDlgItem (hdlg, ID_OofText),
            EM_STREAMIN,
            SF_RTF | SFF_SELECTION | SFF_PLAINRTF,
            (LPARAM)&es);
    }
    else if (lpscd->lpval[ipOof].ulPropTag == PR_SMH_OOF_TEXT)
        Edit_SetText (GetDlgItem (hdlg, ID_OofText), lpscd->lpval[ipOof].Value.LPSZ);

    if (lpscd->lpval[ipOofEnabled].ulPropTag == PR_SMH_OOF_ENABLED)
        CheckDlgButton (hdlg, ID_OofEnabled, lpscd->lpval[ipOofEnabled].Value.b);
    
    return TRUE;
}


/*
 *  OofPage_NOTIFY()
 *
 *  Purpose:
 *
 *      Handles the WM_NOTIFY message for the filter description dialog
 */
BOOL
OofPage_NOTIFY (HWND hdlg, UINT id, NMHDR FAR * lpnmhdr)
{
    SCODE sc;
    HWND hctrl;
    EDITSTREAM es = {0};
    LPSCD lpscd = (LPSCD)GetWindowLong (hdlg, DWL_USER);
    RTFS rtfs = {0};
    SPropValue rgval[3];
    UINT cb;

    switch (lpnmhdr->code)
    {
      case PSN_KILLACTIVE:
      case PSN_RESET:
      case PSN_SETACTIVE:
      default:

        break;

      case PSN_APPLY:

        DebugTrace ("SMH: saving contents of out-of-office page\n");

        hctrl = GetDlgItem (hdlg, ID_OofText);
        cb = Edit_GetTextLength (hctrl) + 1;
        sc = (*lpscd->lpfnAllocMore) (cb,
                            lpscd->lpval,
                            &lpscd->lpval[ipOof].Value.LPSZ);
        if (!FAILED (sc))
        {
            lpscd->lpval[ipOof].ulPropTag = PR_SMH_OOF_TEXT;
            Edit_GetText (hctrl, lpscd->lpval[ipOof].Value.LPSZ, cb);
            DebugTrace ("SMH: OOF: text size: %d\n", lstrlen (lpscd->lpval[ipOof].Value.LPSZ));

            lpscd->lpval[ipOofEnabled].ulPropTag = PR_SMH_OOF_ENABLED;
            lpscd->lpval[ipOofEnabled].Value.b =
                IsDlgButtonChecked (hdlg, ID_OofEnabled);

            /*  Grab the RTF */

            rtfs.cbMax = (FAILED ((*lpscd->lpfnAlloc) (cb * 2, &rtfs.lpb))) ? 0 : cb * 2;
            rtfs.lpfnAlloc = lpscd->lpfnAlloc;
            rtfs.lpfnFree = lpscd->lpfnFree;
            es.pfnCallback = WriteRTFToBuffer;
            es.dwCookie = (DWORD)&rtfs;
            SendMessage (hctrl, EM_STREAMOUT, SF_RTF | SFF_PLAINRTF, (LPARAM)&es);
            if (!es.dwError)
            {
                lpscd->lpval[ipOofRtf].ulPropTag = PR_SMH_OOF_RTF;
                lpscd->lpval[ipOofRtf].Value.bin.cb = rtfs.cb;
                lpscd->lpval[ipOofRtf].Value.bin.lpb = rtfs.lpb;
                DebugTrace ("SMH: OOF: RTF size: %ld\n", lpscd->lpval[ipOofRtf].Value.bin.cb);
            }

            rgval[0] = lpscd->lpval[ipOof];
            rgval[1] = lpscd->lpval[ipOofEnabled];
            rgval[2] = lpscd->lpval[ipOofRtf];
            sc = GetScode (lpscd->lpsec->lpVtbl->SetProps (lpscd->lpsec,
                                                        3,
                                                        rgval,
                                                        NULL));
            if (!FAILED (sc))
                    sc = GetScode (lpscd->lpsec->lpVtbl->SaveChanges (lpscd->lpsec,
                                                        KEEP_OPEN_READWRITE));
            (*lpscd->lpfnFree) (rtfs.lpb);
        }
        return TRUE;

      case EN_SELCHANGE:

        /*  Update the format bar */

        UpdateFormatBar (GetDlgItem (hdlg, ID_Frame));

        return FALSE;

      case PSN_HELP:

        return TRUE;
    }

    return FALSE;
}


/*
 *  OofPage_COMMAND()
 *
 *  Purpose:
 *
 *      Handles the WM_COMMAND message for the filter description dialog
 */
BOOL
OofPage_COMMAND (HWND hdlg, UINT id, HWND hwndCtl, UINT codeNotify)
{
    LPSCD lpscd = (LPSCD)GetWindowLong (hdlg, DWL_USER);

    if (!FDoRTFCommand (GetDlgItem (hdlg, ID_Frame), id, codeNotify))
    {
        switch (id)
        {
          case ID_OofText:
          case ID_OofEnabled:

            PropSheet_Changed (GetParent (hdlg), hdlg);
            break;
        }
    }
    return TRUE;
}


/*
 *  OofPageProc()
 *
 *  Purpose:
 *
 *      Dispatches window messages to the proper function for processing
 */
BOOL CALLBACK
OofPageProc (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
      case WM_INITDIALOG:

        FHandleWm (OofPage, hdlg, INITDIALOG, wParam, lParam);
        return TRUE;

      case WM_COMMAND:

        FHandleWm (OofPage, hdlg, COMMAND, wParam, lParam);
        return TRUE;

      case WM_NOTIFY:

        return FHandleWm (OofPage, hdlg, NOTIFY, wParam, lParam);
    }

    return FALSE;
}


/*
 *  HrDisplayPropSheets()
 *
 *  Purpose:
 *
 *      Brings up the SMH property sheets.
 *
 *  Returns:
 *
 *      (HRESULT)
 */
HRESULT
HrDisplayPropSheets (HINSTANCE hinst,
    HWND hwnd,
    LPSCD lpscd)
{
    HRESULT hr = hrSuccess;
    CHAR rgch[60] = {0};
    HINSTANCE hlib;
    UINT ipg;
    PROPSHEETPAGE psp[] =
    {
        {
            sizeof(PROPSHEETPAGE),
            PSP_USETITLE,
            hinst,
            MAKEINTRESOURCE(SMH_GeneralPage),
            NULL,
            MAKEINTRESOURCE(SMH_GeneralTab),
            GeneralPageProc,
            0,
            NULL,
            NULL
        },
        {
            sizeof(PROPSHEETPAGE),
            PSP_USETITLE,
            hinst,
            MAKEINTRESOURCE(SMH_FilterPage),
            NULL,
            MAKEINTRESOURCE(SMH_FilterTab),
            FilterPageProc,
            0,
            NULL,
            NULL
        },
        {
            sizeof(PROPSHEETPAGE),
            PSP_USETITLE,
            hinst,
            MAKEINTRESOURCE(SMH_OofPage),
            NULL,
            MAKEINTRESOURCE(SMH_OofTab),
            OofPageProc,
            0,
            NULL,
            NULL
        },
        {
            sizeof(PROPSHEETPAGE),
            PSP_USETITLE,
            hinst,
            MAKEINTRESOURCE(SMH_ExclusionPage),
            NULL,
            MAKEINTRESOURCE(SMH_ExclusionTab),
            ExclusionPageProc,
            0,
            NULL,
            NULL
        }
    };
    PROPSHEETHEADER psh =
    {
        sizeof(PROPSHEETHEADER),
        PSH_PROPSHEETPAGE | PSH_PROPTITLE,
        hwnd,
        hinst,
        NULL,
        NULL,
        sizeof(psp) / sizeof(PROPSHEETPAGE),
        0,
        (LPCPROPSHEETPAGE)&psp
    };

    /*  set property sheet data */

    for (ipg = 0; ipg < psh.nPages; ipg++)
        psp[ipg].lParam = (LPARAM)lpscd;

    hlib = LoadLibrary (RICHEDIT_LIB);

    if (LoadString (hinst, SMH_ProviderName, rgch, sizeof(rgch)))
    {
        if (!lpCtl3D)
            lpCtl3D = CTL3D_Initialize (hinst);
        
        psh.pszCaption = rgch;

        switch (PropertySheet (&psh))
        {
          case -1:

            hr = ResultFromScode (MAPI_E_CALL_FAILED);
            break;

          case 0:

            hr = ResultFromScode (MAPI_E_USER_CANCEL);
            break;
        }
        
        if (lpCtl3D)
        {
            CTL3D_Uninitialize (lpCtl3D);
            lpCtl3D = NULL;
        }
        
        UlRelease (lpscd->lpsess);
        lpscd->lpsess = NULL;
    }
    else
        hr = ResultFromScode (MAPI_E_CALL_FAILED);

    FreeLibrary (hlib);
    DebugTraceResult (HrDisplayPropSheets(), hr);
    return hr;
}
