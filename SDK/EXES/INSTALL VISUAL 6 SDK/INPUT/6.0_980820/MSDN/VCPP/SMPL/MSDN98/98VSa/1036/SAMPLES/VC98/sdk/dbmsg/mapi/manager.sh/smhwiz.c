/*
 *  S M H W I Z . C
 *
 *  Sample mail handling hook configuration wizard
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"

extern SPropTagArray sptConfigProps;

/*
 *  Wizard global and external variables
 */
static LPMAPIPROP lpmpWiz = NULL;
static LPSPropValue lpvalWiz = NULL;
static UINT ipgCur = (UINT)(-1);

/*
 *  MAPI Initialization structure.
 *
 *  By initializing MAPI, the wizard can allocate and/or free memory
 *  using MAPIAllocateBuffer(), MAPIAllocateMore(), and MAPIFreeBuffer()
 */
static const MAPIINIT mapiinit = { MAPI_INIT_VERSION, 0 };

/* Wizard page enumeration */

enum {ipgSentMail, ipgDeleted, ipgInbound, ipgUnread, cpgMax};


/*
 *  TogglePage()
 *
 *  Purpose:
 *
 *      Toggles the state of the current page to be either enabled and
 *      visible or disabled and hidden.
 *
 *      IMPORTANT: This function relies on the dialog control IDs as
 *      defined in _SMH.RH.  Each page exists in a certain range and all
 *      controls in each page must have contiguous IDs starting at the
 *      page ID value.
 *
 *  Arguments:
 *
 *      hdlg            the dialog
 *      ipg             the page index (0 - cpgMax)
 *      fEnable         boolean used to either enable for disable the page
 */
VOID
TogglePage (HWND hdlg, UINT ipg, BOOL fEnable)
{
    UINT ictl = 0;
    HANDLE hctl;

    if (ipg >= cpgMax)
        return;

    while (hctl = GetDlgItem (hdlg, (WIZ_BASE + (ipg * PAGE_INC) + ictl++)))
    {
        EnableWindow (hctl, fEnable);
        ShowWindow (hctl, (fEnable ? SW_SHOW : SW_HIDE));
    }
}


/*
 *  EnablePage()
 *
 *  Purpose:
 *
 *      Toggles the state of the current page controls to be either
 *      enabled or disabled.
 *
 *      IMPORTANT: This function relies on the dialog control IDs as
 *      defined in _SMH.RH.  Each page exists in a certain range and all
 *      controls in each page must have contiguous IDs starting at the
 *      page ID value.
 *
 *  Arguments:
 *
 *      hdlg            the dialog
 *      ipg             the page index (0 - cpgMax)
 *      fEnable         boolean used to either enable for disable the page
 */
VOID
EnablePage (HWND hdlg, UINT ipg, BOOL fEnable)
{
    UINT ictl = 0;
    HANDLE hctl;

    if (ipg >= cpgMax)
        return;

    while (hctl = GetDlgItem (hdlg, (WIZ_BASE + (ipg * PAGE_INC) + ictl++)))
        EnableWindow (hctl, fEnable);
}


/*
 *  ShowPage()
 *
 *  Purpose:
 *
 *      Toggles the state of the current page controls to be either
 *      visible or hidden.
 *
 *      IMPORTANT: This function relies on the dialog control IDs as
 *      defined in _SMH.RH.  Each page exists in a certain range and all
 *      controls in each page must have contiguous IDs starting at the
 *      page ID value.
 *
 *  Arguments:
 *
 *      hdlg            the dialog
 *      ipg             the page index (0 - cpgMax)
 *      fEnable         boolean used to either show or hide the page
 */
VOID
ShowPage (HWND hdlg, UINT ipg, BOOL fEnable)
{
    UINT ictl = 0;
    HANDLE hctl;

    if (ipg >= cpgMax)
        return;

    while (hctl = GetDlgItem (hdlg, (WIZ_BASE + (ipg * PAGE_INC) + ictl++)))
        ShowWindow (hctl, (fEnable ? SW_SHOW : SW_HIDE));
}


/*
 *  WizardPage_INITDIALOG()
 *
 *  Purpose:
 *
 *      Responds to the WM_INITDIALOG message.
 *
 *  Returns:
 *
 *      TRUE iff the initialization was successful
 */
BOOL
WizardPage_INITDIALOG (HWND hdlg, HWND hwndFocus, LPARAM lParam)
{
    ULONG cval;
    ULONG ulFlags;

    if (!FAILED (MAPIInitialize ((LPMAPIINIT)&mapiinit)) &&
        !HR_FAILED (lpmpWiz->lpVtbl->GetProps (lpmpWiz,
                                        (LPSPropTagArray)&sptConfigProps,
                                        0,
                                        &cval,
                                        &lpvalWiz)))
    {
        ulFlags = (lpvalWiz[ipFlags].ulPropTag == PR_SMH_FLAGS)
            ? lpvalWiz[ipFlags].Value.l
            : 0;

        CheckDlgButton (hdlg, ID_SentMail, !!(ulFlags & SMH_FILTER_SENTMAIL));
        CheckDlgButton (hdlg, ID_SentMailYr, !!(ulFlags & SMH_FILTER_SENTMAIL_YR));
        CheckDlgButton (hdlg, ID_Deleted, !!(ulFlags & SMH_FILTER_DELETED));
        CheckDlgButton (hdlg, ID_DeletedYr, !!(ulFlags & SMH_FILTER_DELETED_YR));
        CheckDlgButton (hdlg, ID_Inbound, !!(ulFlags & SMH_FILTER_INBOUND));
        CheckDlgButton (hdlg, ID_Unread, !!(ulFlags & SMH_UNREAD_VIEWER));
        lpvalWiz[ipFlags].ulPropTag = PR_SMH_FLAGS;
        lpvalWiz[ipFlags].Value.l = ulFlags;
        DebugTrace ("SMH: wizard initialized\n");
        return TRUE;
    }
    else
    {
        DebugTrace ("SMH: wizard initializion failed\n");
        return FALSE;
    }
}


/*
 *  WizardPage_COMMAND()
 *
 *  Purpose:
 *
 *      Responds to the WM_COMMAND message.
 *
 *      IMPORTANT: This function relies on the dialog control IDs as
 *      defined in _SMH.RH.  Each page exists in a certain range and all
 *      controls in each page must have contiguous IDs starting at the
 *      page ID value.
 *
 *  Returns:
 *
 *      TRUE iff the command was processed by the wizard page
 */
BOOL
WizardPage_COMMAND (HWND hdlg, UINT id, HWND hwndCtl, UINT codeNotify)
{
    UINT cpgJmp = 1;

    switch (id)
    {
      case ID_SentMail:
      case ID_Deleted:

        /* Check/uncheck the companion checkbox */

        EnableWindow (GetDlgItem (hdlg, id + 1), !!IsDlgButtonChecked (hdlg, id));
        break;

      case WIZ_PREV:

        cpgJmp = (UINT)(-((INT)cpgJmp));

        /* Fall through! */

      case WIZ_NEXT:

        DebugTrace ("SMH: PREV/NEXT'd from pg %d to pg %d\n", ipgCur, ipgCur + cpgJmp);

        /* Disable/hide the current page and enable target page */
        TogglePage (hdlg, ipgCur, FALSE);
        EnablePage (hdlg, ipgCur += cpgJmp, TRUE);

        switch (ipgCur)
        {
          case ipgSentMail:

            EnableWindow (GetDlgItem (hdlg, ID_SentMailYr),
                !!IsDlgButtonChecked (hdlg, ID_SentMail));
            break;

          case ipgDeleted:

            EnableWindow (GetDlgItem (hdlg, ID_DeletedYr),
                !!IsDlgButtonChecked (hdlg, ID_Deleted));
            break;

          case ipgInbound:
          case ipgUnread:

            break;

          case cpgMax:

            if (IsDlgButtonChecked (hdlg, ID_SentMail))
            {
                lpvalWiz[ipFlags].Value.l |= SMH_FILTER_SENTMAIL;
                if (IsDlgButtonChecked (hdlg, ID_SentMailYr))
                    lpvalWiz[ipFlags].Value.l |= SMH_FILTER_SENTMAIL_YR;
                else
                    lpvalWiz[ipFlags].Value.l &= ~SMH_FILTER_SENTMAIL_YR;
            }
            else
                lpvalWiz[ipFlags].Value.l &= ~(SMH_FILTER_SENTMAIL | SMH_FILTER_SENTMAIL_YR);

            if (IsDlgButtonChecked (hdlg, ID_Deleted))
            {
                lpvalWiz[ipFlags].Value.l |= SMH_FILTER_DELETED;
                if (IsDlgButtonChecked (hdlg, ID_DeletedYr))
                    lpvalWiz[ipFlags].Value.l |= SMH_FILTER_DELETED_YR;
                else
                    lpvalWiz[ipFlags].Value.l &= ~SMH_FILTER_DELETED_YR;
            }
            else
                lpvalWiz[ipFlags].Value.l &= ~(SMH_FILTER_DELETED | SMH_FILTER_DELETED_YR);

            if (IsDlgButtonChecked (hdlg, ID_Inbound))
                lpvalWiz[ipFlags].Value.l |= SMH_FILTER_INBOUND;
            else
                lpvalWiz[ipFlags].Value.l &= ~SMH_FILTER_INBOUND;

            if (IsDlgButtonChecked (hdlg, ID_Unread))
                lpvalWiz[ipFlags].Value.l |= SMH_UNREAD_VIEWER;
            else
                lpvalWiz[ipFlags].Value.l &= ~SMH_UNREAD_VIEWER;

            lpmpWiz->lpVtbl->SetProps (lpmpWiz, cpMax, lpvalWiz, NULL);
            lpmpWiz->lpVtbl->SaveChanges (lpmpWiz, KEEP_OPEN_READWRITE);
            break;
        }

        /* Unhide the target page */

        ShowPage (hdlg, ipgCur, TRUE);
        return (BOOL)cpgJmp;

      default:

        return FALSE;
    }

    return TRUE;
}


/*
 *  SMH_WizProc()
 *
 *  Purpose:
 *
 *      The wizard page dialog proceedure.
 *
 *  Arguments:
 *
 *      hdlg        the dialog
 *      wMsgID      the message
 *      wParam
 *      lParam
 */
BOOL STDAPICALLTYPE
SMH_WizProc (HWND hdlg,
    UINT wMsgID,
    WPARAM wParam,
    LPARAM lParam)
{
    //static UINT ipgCur = (UINT)(-1);
    static LPSPropValue lpval = NULL;

    switch (wMsgID)
    {
      case WM_INITDIALOG:

        return (BOOL)FHandleWm (WizardPage, hdlg, INITDIALOG, wParam, lParam);

      case WIZ_QUERYNUMPAGES:

        DebugTrace ("SMH: wizard page count %d\n", cpgMax);
        return (BOOL)cpgMax;

      case WM_CLOSE:

        DebugTrace ("SMH: wizard closed\n");

        ipgCur = (UINT)(-1);
        MAPIFreeBuffer (lpvalWiz);
        MAPIUninitialize ();
        lpvalWiz = NULL;

        UlRelease (lpmpWiz);
        lpmpWiz = NULL;
        break;

      case WM_COMMAND:

        return (BOOL)FHandleWm (WizardPage, hdlg, COMMAND, wParam, lParam);

      default:

        return FALSE;
    }

    return TRUE;
}

/*
 *  WizardEntry()
 *
 *  Purpose:
 *
 *      This is the initial entrypoint for the MAPI 1.0 configuration
 *      wizard.  This function tells the wizard DLL how many pages the
 *      configuration for this service requires as well as the dialog
 *      procedure to call for each individual event.
 *
 *  Arguments:
 *
 *      hInstance       the instance of my dll, this can be used to
 *                      retrieve resources out of my DLL, etc.
 *
 *      lpszRsrcName    [OUT]   on return, this buffer is filled with
 *                              the full name of the dialog resource ID.
 *                              Note that this requires the name to be a
 *                              text value and not something generated
 *                              with the MAKEINTRESOURCE() macro
 *
 *      lpfnDlgProc     [OUT]   on return, holds a function pointer to
 *                              the dialog proc to call for each event
 *
 *      lpMapiProp      the pointer to a IMAPIProp object that is my
 *                      interface to the profile.
 *
 *  Returns:
 *
 *      (SCODE)         S_OK
 */
ULONG STDAPICALLTYPE
SMH_WizEntry (HINSTANCE hInstance,
    LPTSTR FAR * lppszRsrcName,
    DLGPROC FAR * lpfnDlgProc,
    LPMAPIPROP lpMapiProp,
    LPVOID lpsup)
{
    Unreferenced (lpsup);
    
    /*  Stash the MAPIPROP object in global for use in the
     *  configuration wizard
     */
    lpmpWiz = lpMapiProp;
    UlAddRef (lpmpWiz);

    /*  tell the configuration wizard the dialog template name
     *  and the window proceedure to use
     */
    *lppszRsrcName = (LPTSTR)szWizardDialog;
    *lpfnDlgProc = (DLGPROC)SMH_WizProc;

    return S_OK;
}
