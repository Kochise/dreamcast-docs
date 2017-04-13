
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/****************************** Module Header *******************************
* Module Name: dialogs.c
*
* Contains many of the dialogs and supporting routines used by the
* dialog box editor.
*
* Functions:
*
*    DlgBox()
*    EnteringDialog()
*    CreateTestDialog()
*    DestroyTestDialog()
*    SelectDialogDialog()
*    ArrangeSettingsDialog()
*    AboutDlgProc()
*    SelectDialogDlgProc()
*    SelectDialogInit()
*    SelectDialogFillLangList()
*    SelectDialogOK()
*    TestDlgProc()
*    TestInitDlg()
*    ArrangeSettingsDlgProc()
*
* Comments:
* 
****************************************************************************/

#include "dlgedit.h"
#include "dlgfuncs.h"
#include "dlgextrn.h"
#include "dialogs.h"
#include "dlghelp.h"


/*
 * Maximum number of characters in the Arrange Settings fields.
 */
#define CCHARRSETMAX    2

DIALOGPROC SelectDialogDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
STATICFN VOID SelectDialogInit(HWND hwnd);
STATICFN VOID SelectDialogFillLangList(HWND hwnd);
STATICFN BOOL SelectDialogOK(HWND hwnd);
DIALOGPROC TestDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
STATICFN VOID TestInitDlg(HWND hwnd);
DIALOGPROC ArrangeSettingsDlgProc(HWND hwnd, UINT msg, WPARAM wParam,
    LPARAM lParam);



/************************************************************************
* DlgBox
*
* This function basically does a DialogBox, but it does it safely
* for the dialog editor, saving some states.
*
* Arguments:
*     INT idDlg       = Ordinal name of the dialog.
*     WNDPROC lpfnDlg = Dialog procedure to use (this function will
*                       call Make/FreeProcInstance).
*
* Returns:
*     What DialogBox returned.
*
************************************************************************/

INT DlgBox(
    INT idDlg,
    WNDPROC lpfnDlg)
{
    INT nResult;
    INT idPrevDlg;

    EnteringDialog(idDlg, &idPrevDlg, TRUE);
    nResult = DialogBox(ghInst, MAKEINTRESOURCE(idDlg), ghwndMain, (DLGPROC)lpfnDlg);
    EnteringDialog(idPrevDlg, NULL, FALSE);

    return nResult;
}



/************************************************************************
* EnteringDialog
*
* This function enables or disables things based on whether we are
* going to show one of the editor's dialogs.  It must be called
* before and after showing a dialog box.
*
* Arguments:
*   INT idDlg       - Ordinal name of the dialog.
*   PINT pidPrevDlg - Points to where to save the id of the previous
*                     (current) dialog.  If fEntering is FALSE, this
*                     is not used and should be NULL.
*   BOOL fEntering  - TRUE if about ready to show the dialog.  FALSE if
*                     the dialog was just dismissed.  For the FALSE case,
*                     the idDlg should be zero, or the id of the previous
*                     dialog.
*
************************************************************************/

VOID EnteringDialog(
    INT idDlg,
    PINT pidPrevDlg,
    BOOL fEntering)
{
    /*
     * If we are entering a new dialog, save the previous dialog
     * in the place specified.
     */
    if (fEntering)
        *pidPrevDlg = gidCurrentDlg;

    gfDisabled = fEntering;
    gidCurrentDlg = idDlg;
    StatusSetEnable();

    if (ghwndToolbox)
        EnableWindow(ghwndToolbox, !fEntering);
}



/************************************************************************
* SelectDialogDialog
*
* This function saves the current dialog box in the resource in
* memory, then it puts up a dialog box with a list of dialog
* boxes in the resource.  Finally it puts up the selected dialog.
*
************************************************************************/

VOID SelectDialogDialog(VOID)
{
    if (!SynchDialogResource())
        return;

    DlgBox(DID_SELECTDIALOG, (WNDPROC)SelectDialogDlgProc);
}



/************************************************************************
* SelectDialogDlgProc
*
* This is the View Dialog dialog procedure.
*
* Arguments:
*    HWND - handle to the dialog
*    UINT - window message
*    WPARAM - message parameter 
*    LPARAM - message parameter
*
* Returns:
*    Default dialog return.
*
************************************************************************/

DIALOGPROC SelectDialogDlgProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg) {
        case WM_INITDIALOG:
            SelectDialogInit(hwnd);
            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case DID_SELECTDIALOGNAMELIST:
                    switch (HIWORD(wParam)) {
                        case LBN_SELCHANGE:
                            SelectDialogFillLangList(hwnd);
                            break;

                        case LBN_DBLCLK:
                            if (SelectDialogOK(hwnd))
                                EndDialog(hwnd, IDOK);

                            break;
                    }

                    break;

                case DID_SELECTDIALOGLANGLIST:
                    switch (HIWORD(wParam)) {
                        case LBN_DBLCLK:
                            if (SelectDialogOK(hwnd))
                                EndDialog(hwnd, IDOK);

                            break;
                    }

                    break;

                case IDOK:
                    if (SelectDialogOK(hwnd))
                        EndDialog(hwnd, IDOK);

                    break;

                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                    break;

                case IDHELPDLG:
                    WinHelp(ghwndMain, gszHelpFile, HELP_CONTEXT,
                            HELPID_SELECTDIALOG);
                    break;
            }

            return TRUE;

        default:
            return FALSE;
    }
}



/************************************************************************
* SelectDialogInit
*
* Processes the WM_INITDIALOG message for the Select Dialog dialog
* procedure.
*
* This function fills the select dialog listbox with the names or
* numbers of all the dialogs in the resource list.  If the dialog has
* a name, that is used.  If it just has an ordinal, then the decimal
* ascii string for the ordinal number is used.
*
* Arguments:
*    HWND - handle to the dialog
*
************************************************************************/

STATICFN VOID SelectDialogInit(
    HWND hwnd)
{
    HWND hwndNameLB;
    TCHAR szName[CCHTEXTMAX];
    INT i;
    INT cDlgsAdded;
    INT iSelect;
    PRESLINK prl;
    PRESLINK prl2;
    LPTSTR pszName;
    NPLABEL npLabel;

    hwndNameLB = GetDlgItem(hwnd, DID_SELECTDIALOGNAMELIST);
    cDlgsAdded = 0;

    /*
     * Insert each dialog found in the resource.
     */
    for (prl = gprlHead; prl; prl = prl->prlNext) {
        if (prl->fDlgResource) {
            /*
             * Check to be sure we have not added a dialog with this
             * name already (but perhaps a different language).
             */
            for (prl2 = gprlHead; prl2 != prl; prl2 = prl2->prlNext) {
                if (prl2->fDlgResource) {
                    if (NameOrdCmp(prl2->pszName, prl->pszName) == 0)
                        break;
                }
            }

            if (prl2 == prl) {
                /*
                 * If the name is an ordinal, display a number.  If there
                 * happens to be a define for this number, display that
                 * instead, however.
                 *
                 * Note that we do not ever show it in hex, because
                 * rc.exe does not parse hex ordinals for dialogs, so
                 * we never show it in that format.
                 */
                if (IsOrd(prl->pszName)) {
                    if (npLabel = FindID(OrdID(prl->pszName), plInclude))
                        pszName = npLabel->pszLabel;
                    else
                        pszName = itoaw(OrdID(prl->pszName), szName, 10);
                }
                else {
                    pszName = prl->pszName;
                }

                i = (INT)SendMessage(hwndNameLB, LB_ADDSTRING, 0, (DWORD)pszName);
                SendMessage(hwndNameLB, LB_SETITEMDATA, i, (DWORD)prl);
                cDlgsAdded++;
            }
        }
    }

    /*
     * If there is a current dialog, search for it and
     * make it the default selected item.
     */
    iSelect = 0;
    if (gcd.prl) {
        for (i = 0; i < cDlgsAdded; i++) {
            prl = (PRESLINK)SendMessage(hwndNameLB, LB_GETITEMDATA, i, 0L);
            if (NameOrdCmp(prl->pszName, gcd.prl->pszName) == 0) {
                iSelect = i;
                break;
            }
        }
    }

    SendMessage(hwndNameLB, LB_SETCURSEL, iSelect, 0L);

    SelectDialogFillLangList(hwnd);

    CenterWindow(hwnd);
}



/************************************************************************
* SelectDialogFillLangList
*
* Fills the listbox with the list of dialogs matching the specified name
*
* Arguments:
*    HWND - handle to the dialog editor window
*
************************************************************************/

STATICFN VOID SelectDialogFillLangList(
    HWND hwnd)
{
    TCHAR szLang[CCHTEXTMAX];
    HWND hwndNameLB;
    HWND hwndLangLB;
    PRESLINK prl;
    INT i;
    INT iSelect;
    WORD wPrimary;
    WORD wSubLang;
    INT iLang;
    INT iSubLang;
    LPTSTR pszName;
    INT cItems;

    hwndNameLB = GetDlgItem(hwnd, DID_SELECTDIALOGNAMELIST);
    hwndLangLB = GetDlgItem(hwnd, DID_SELECTDIALOGLANGLIST);

    SendMessage(hwndLangLB, LB_RESETCONTENT, 0, 0);

    if ((iSelect = (INT)SendMessage(hwndNameLB, LB_GETCURSEL, 0, 0)) == LB_ERR)
        return;

    /*
     * Get the name of the dialog selected in the Name listbox
     * (the reslink pointer is stored in the listbox items data field).
     */
    prl = (PRESLINK)SendMessage(hwndNameLB, LB_GETITEMDATA, iSelect, 0L);
    pszName = prl->pszName;

    /*
     * Insert each dialog found in the resource that matches that name.
     */
    for (prl = gprlHead; prl; prl = prl->prlNext) {
        if (prl->fDlgResource && NameOrdCmp(prl->pszName, pszName) == 0) {
            wPrimary = (WORD)PRIMARYLANGID(prl->wLanguage);
            for (iLang = 0; iLang < gcLanguages; iLang++) {
                if (gaLangTable[iLang].wPrimary == wPrimary) {
                    break;
                }
            }

            wSubLang = SUBLANGID(prl->wLanguage);
            for (iSubLang = 0;
                    iSubLang < gaLangTable[iLang].cSubLangs;
                    iSubLang++) {
                if (wSubLang == gaLangTable[iLang].asl[iSubLang].wSubLang) {
                    break;
                }
            }

            wsprintf(szLang, L"%s, %s",
                    ids(gaLangTable[iLang].idsLangDesc),
                    ids(gaLangTable[iLang].asl[iSubLang].idsSubLangDesc));

            i = (INT)SendMessage(hwndLangLB, LB_ADDSTRING, 0, (DWORD)szLang);
            SendMessage(hwndLangLB, LB_SETITEMDATA, i, (DWORD)prl);
        }
    }

    iSelect = 0;
    cItems = (INT)SendMessage(hwndLangLB, LB_GETCOUNT, 0, 0);
    if (gcd.prl && NameOrdCmp(gcd.prl->pszName, pszName) == 0) {
        for (i = 0; i < cItems; i++) {
            prl = (PRESLINK)SendMessage(hwndLangLB, LB_GETITEMDATA, i, 0);
            if (gcd.prl == prl) {
                iSelect = i;
                break;
            }
        }
    }

    SendMessage(hwndLangLB, LB_SETCURSEL, iSelect, 0L);
}



/************************************************************************
* SelectDialogOK
*
* Processes the selection of a new dialog from the Select Dialog
* dialog procedure.
*
* Arguments:
*    HWND - handle to the select dialog box
*
* Returns:
*    TRUE 
*
************************************************************************/

STATICFN BOOL SelectDialogOK(
    HWND hwnd)
{
    HWND hwndLangLB;
    INT iSelect;
    PRESLINK prl;

    hwndLangLB = GetDlgItem(hwnd, DID_SELECTDIALOGLANGLIST);

    if ((iSelect = (INT)SendMessage(hwndLangLB, LB_GETCURSEL, 0, 0)) !=
            LB_ERR) {
        /*
         * Get a pointer to the selected dialog (stored in the listbox
         * items data field).
         */
        prl = (PRESLINK)SendMessage(hwndLangLB, LB_GETITEMDATA, iSelect, 0L);

        /*
         * Is there a dialog currently being edited?
         */
        if (gfEditingDlg) {
            /*
             * If they chose the same dialog as what they are currently
             * editing, just get out without doing anything more.
             * Otherwise, delete the current dialog because we are
             * now committed to loading a new one.
             */
            if (prl == gcd.prl)
                return TRUE;
            else
                DeleteDialog(FALSE);
        }

        /*
         * Finally, load the new dialog (make it current).
         */
        ResLinkToDialog(prl);

        /*
         * Select the new dialog, if it was successfully created.
         */
        if (gfEditingDlg)
            SelectControl(gcd.npc, FALSE);
    }

    return TRUE;
}



/************************************************************************
* CreateTestDialog
*
* Creates a dialog for the test mode of the dialog editor
*
************************************************************************/

VOID CreateTestDialog(VOID)
{
    PRES pRes;
    PDIALOGBOXHEADER pdbh;

    if (!gfEditingDlg)
        return;

    CancelSelection(TRUE);

    /*
     * Save the current dialog in the resource buffer.
     */
    if (!SynchDialogResource())
        return;

    /*
     * Make a memory copy of the current dialog resource for test mode.
     */
    if (!(pRes = AllocDialogResource(TRUE, FALSE)))
        return;

    pdbh = (PDIALOGBOXHEADER)SkipResHeader(pRes);

    /*
     * Create the test dialog in a modeless loop using the test dialog proc.
     */
    ghwndTestDlg = CreateDialogIndirect(ghInst, (LPDLGTEMPLATE)pdbh,
            ghwndSubClient, TestDlgProc);

    if (ghwndTestDlg) {
        gfTestMode = TRUE;

        /*
         * Disable various top level menus.
         */
        MyEnableMenuItemByPos(ghMenuMain, MENUPOS_FILE, FALSE);
        MyEnableMenuItemByPos(ghMenuMain, MENUPOS_EDIT, FALSE);
        MyEnableMenuItemByPos(ghMenuMain, MENUPOS_ARRANGE, FALSE);
        DrawMenuBar(ghwndMain);

        ToolboxSelectTool(W_NOTHING, FALSE);
        if (gfShowToolbox)
            ToolboxShow(FALSE);

        StatusSetEnable();

        /*
         * Remove the work mode dialog from view (actually, it is now
         * hidden behind the test dialog, but we hide it in case the
         * user moves the test dialog.
         */
        ShowWindow(gcd.npc->hwnd, SW_HIDE);
    }
}



/************************************************************************
* TestDlgProc
*
* This is the dialog procedure for the dialog in Test mode.
*
************************************************************************/

DIALOGPROC TestDlgProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg) {
        case WM_INITDIALOG:
            TestInitDlg(hwnd);
            return TRUE;

        case WM_SYSCOMMAND:
            if (wParam == SC_CLOSE) {
                DestroyTestDialog();
                return TRUE;
            }

            return FALSE;

        case WM_DRAWITEM:
            return DrawOwnerDrawButton((LPDRAWITEMSTRUCT)lParam);

        case WM_DESTROY:
            gfTestMode = FALSE;

            ShowWindow(gcd.npc->hwnd, SW_SHOWNA);

            /*
             * Enable various top level menus.
             */
            MyEnableMenuItemByPos(ghMenuMain, MENUPOS_FILE, TRUE);
            MyEnableMenuItemByPos(ghMenuMain, MENUPOS_EDIT, TRUE);
            MyEnableMenuItemByPos(ghMenuMain, MENUPOS_ARRANGE, TRUE);
            DrawMenuBar(ghwndMain);

            if (gfShowToolbox)
                ToolboxShow(TRUE);

            StatusSetEnable();

            return TRUE;

        default:
            return FALSE;
    }
}



/************************************************************************
* TestInitDlg
*
* This function handles the initialization of the test dialog.
*
* Arguments:
*     HWND hwnd = The test dialog window handle.
*
************************************************************************/

STATICFN VOID TestInitDlg(
    HWND hwnd)
{
    register INT i;
    TCHAR szBuf[CCHTEXTMAX];
    HWND hwndCtrl;
    LPTSTR pszTextEnd;
    TCHAR szClass[32];
    INT iClass;

    /*
     * The following will fill some controls with sample text lines.
     */
    lstrcpy(szBuf, ids(IDS_DEFLBTEXT));
    pszTextEnd = szBuf + lstrlen(szBuf);
    hwndCtrl = GetWindow(hwnd, GW_CHILD);
    while (hwndCtrl) {
        GetClassName(hwndCtrl, szClass, sizeof(szClass));

        switch (iClass = GetiClass(szClass)) {
            case IC_LISTBOX:
            case IC_COMBOBOX:
                /*
                 * Fill listboxes and comboboxes with some sample lines.
                 */
                for (i = 1; i <= CLBTESTLINES; i++) {
                    itoaw(i, pszTextEnd, 10);
                    SendMessage(hwndCtrl,
                            (WORD)((iClass == IC_LISTBOX) ?
                            LB_INSERTSTRING : CB_INSERTSTRING),
                            (WPARAM)-1, (DWORD)szBuf);
                }

                break;
        }

        hwndCtrl = GetWindow(hwndCtrl, GW_HWNDNEXT);
    }
}



/************************************************************************
* DestroyTestDialog
*
* Destroys the test dialog window.
************************************************************************/

VOID DestroyTestDialog(VOID)
{
    DestroyWindow(ghwndTestDlg);
    ghwndTestDlg = NULL;
}



/************************************************************************
* ArrangeSettingsDialog
*
* This function displays the Arrange Settings dialog box.
*
************************************************************************/

VOID ArrangeSettingsDialog(VOID)
{
    DlgBox(DID_ARRSETTINGS, (WNDPROC)ArrangeSettingsDlgProc);
}



/************************************************************************
* ArrangeSettingsDlgProc
*
* This is the Arrange Settings dialog procedure.
*
************************************************************************/

DIALOGPROC ArrangeSettingsDlgProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg) {
        case WM_INITDIALOG:
            SendDlgItemMessage(hwnd, DID_ARRSETCXGRID, EM_LIMITTEXT,
                    CCHARRSETMAX, 0L);
            SendDlgItemMessage(hwnd, DID_ARRSETCYGRID, EM_LIMITTEXT,
                    CCHARRSETMAX, 0L);
            SetDlgItemInt(hwnd, DID_ARRSETCXGRID, gcxGrid, TRUE);
            SetDlgItemInt(hwnd, DID_ARRSETCYGRID, gcyGrid, TRUE);

            SendDlgItemMessage(hwnd, DID_ARRSETXMARGIN, EM_LIMITTEXT,
                    CCHARRSETMAX, 0L);
            SendDlgItemMessage(hwnd, DID_ARRSETYMARGIN, EM_LIMITTEXT,
                    CCHARRSETMAX, 0L);
            SetDlgItemInt(hwnd, DID_ARRSETXMARGIN, gxMargin, TRUE);
            SetDlgItemInt(hwnd, DID_ARRSETYMARGIN, gyMargin, TRUE);

            SendDlgItemMessage(hwnd, DID_ARRSETXSPACE, EM_LIMITTEXT,
                    CCHARRSETMAX, 0L);
            SendDlgItemMessage(hwnd, DID_ARRSETYSPACE, EM_LIMITTEXT,
                    CCHARRSETMAX, 0L);
            SetDlgItemInt(hwnd, DID_ARRSETXSPACE, gxSpace, TRUE);
            SetDlgItemInt(hwnd, DID_ARRSETYSPACE, gySpace, TRUE);

            SendDlgItemMessage(hwnd, DID_ARRSETXMINPUSHSPACE, EM_LIMITTEXT,
                    CCHARRSETMAX, 0L);
            SendDlgItemMessage(hwnd, DID_ARRSETXMAXPUSHSPACE, EM_LIMITTEXT,
                    CCHARRSETMAX, 0L);
            SendDlgItemMessage(hwnd, DID_ARRSETYPUSHSPACE, EM_LIMITTEXT,
                    CCHARRSETMAX, 0L);
            SetDlgItemInt(hwnd, DID_ARRSETXMINPUSHSPACE, gxMinPushSpace, TRUE);
            SetDlgItemInt(hwnd, DID_ARRSETXMAXPUSHSPACE, gxMaxPushSpace, TRUE);
            SetDlgItemInt(hwnd, DID_ARRSETYPUSHSPACE, gyPushSpace, TRUE);

            CenterWindow(hwnd);

            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                INT cxGridNew;
                INT cyGridNew;
                INT xMarginNew;
                INT yMarginNew;
                INT xSpaceNew;
                INT ySpaceNew;
                INT xMinPushSpaceNew;
                INT xMaxPushSpaceNew;
                INT yPushSpaceNew;
                BOOL fTranslated1;
                BOOL fTranslated2;
                BOOL fTranslated3;

                case IDOK:
                    cxGridNew = GetDlgItemInt(hwnd, DID_ARRSETCXGRID,
                            &fTranslated1, TRUE);
                    cyGridNew = GetDlgItemInt(hwnd, DID_ARRSETCYGRID,
                            &fTranslated2, TRUE);

                    if (!fTranslated1 || !fTranslated2 ||
                            cxGridNew <= 0 || cyGridNew <= 0) {
                        Message(MSG_GTZERO, ids(IDS_GRID));
                        SetFocus(GetDlgItem(hwnd, DID_ARRSETCXGRID));
                        break;
                    }

                    xMarginNew = GetDlgItemInt(hwnd, DID_ARRSETXMARGIN,
                            &fTranslated1, TRUE);
                    yMarginNew = GetDlgItemInt(hwnd, DID_ARRSETYMARGIN,
                            &fTranslated2, TRUE);

                    if (!fTranslated1 || !fTranslated2 ||
                            xMarginNew < 0 || yMarginNew < 0) {
                        Message(MSG_POSITIVENUM, ids(IDS_MARGIN));
                        SetFocus(GetDlgItem(hwnd, DID_ARRSETXMARGIN));
                        break;
                    }

                    xSpaceNew = GetDlgItemInt(hwnd, DID_ARRSETXSPACE,
                            &fTranslated1, TRUE);
                    ySpaceNew = GetDlgItemInt(hwnd, DID_ARRSETYSPACE,
                            &fTranslated2, TRUE);

                    if (!fTranslated1 || !fTranslated2 ||
                            xSpaceNew < 0 || ySpaceNew < 0) {
                        Message(MSG_POSITIVENUM, ids(IDS_CTRLSPACING));
                        SetFocus(GetDlgItem(hwnd, DID_ARRSETXSPACE));
                        break;
                    }

                    xMinPushSpaceNew = GetDlgItemInt(hwnd,
                            DID_ARRSETXMINPUSHSPACE, &fTranslated1, TRUE);
                    xMaxPushSpaceNew = GetDlgItemInt(hwnd,
                            DID_ARRSETXMAXPUSHSPACE, &fTranslated2, TRUE);
                    yPushSpaceNew = GetDlgItemInt(hwnd, DID_ARRSETYPUSHSPACE,
                            &fTranslated3, TRUE);

                    if (!fTranslated1 || !fTranslated2 || !fTranslated3 ||
                            xMinPushSpaceNew < 0 || xMaxPushSpaceNew < 0 ||
                            yPushSpaceNew < 0) {
                        Message(MSG_POSITIVENUM, ids(IDS_PUSHSPACING));
                        SetFocus(GetDlgItem(hwnd, DID_ARRSETXMINPUSHSPACE));
                        break;
                    }

                    if (xMinPushSpaceNew > xMaxPushSpaceNew) {
                        Message(MSG_MINGTMAXSPACE);
                        SetFocus(GetDlgItem(hwnd, DID_ARRSETXMINPUSHSPACE));
                        break;
                    }

                    gcxGrid = cxGridNew;
                    gcyGrid = cyGridNew;
                    gxMargin = xMarginNew;
                    gyMargin = yMarginNew;
                    gxSpace = xSpaceNew;
                    gySpace = ySpaceNew;
                    gxMinPushSpace = xMinPushSpaceNew;
                    gxMaxPushSpace = xMaxPushSpaceNew;
                    gyPushSpace = yPushSpaceNew;

                    EndDialog(hwnd, LOWORD(wParam));
                    break;

                case DID_ARRSETDEFAULTS:
                    SetDlgItemInt(hwnd, DID_ARRSETCXGRID,
                            DEFCXGRID, TRUE);
                    SetDlgItemInt(hwnd, DID_ARRSETCYGRID,
                            DEFCYGRID, TRUE);

                    SetDlgItemInt(hwnd, DID_ARRSETXMARGIN,
                            DEFXMARGIN, TRUE);
                    SetDlgItemInt(hwnd, DID_ARRSETYMARGIN,
                            DEFYMARGIN, TRUE);

                    SetDlgItemInt(hwnd, DID_ARRSETXSPACE,
                            DEFXSPACE, TRUE);
                    SetDlgItemInt(hwnd, DID_ARRSETYSPACE,
                            DEFYSPACE, TRUE);

                    SetDlgItemInt(hwnd, DID_ARRSETXMINPUSHSPACE,
                            DEFXMINPUSHSPACE, TRUE);
                    SetDlgItemInt(hwnd, DID_ARRSETXMAXPUSHSPACE,
                            DEFXMAXPUSHSPACE, TRUE);
                    SetDlgItemInt(hwnd, DID_ARRSETYPUSHSPACE,
                            DEFYPUSHSPACE, TRUE);

                    break;

                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                    break;

                case IDHELPDLG:
                    WinHelp(ghwndMain, gszHelpFile, HELP_CONTEXT,
                            HELPID_ARRSETTINGS);
                    break;
            }

            return TRUE;

        default:
            return FALSE;
    }
}



/************************************************************************
* AboutDlgProc
*
* This is the About Box dialog procedure.
*
************************************************************************/

DIALOGPROC AboutDlgProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg) {
        case WM_INITDIALOG:
            {
                TCHAR szVersion[CCHTEXTMAX];

                lstrcpy(szVersion, ids(IDS_APPVERSION));
                lstrcat(szVersion, ids(IDS_APPVERSIONMINOR));

                SetDlgItemText(hwnd, DID_ABOUTVERSION, szVersion);
                CenterWindow(hwnd);
            }

            return TRUE;

        case WM_COMMAND:
            EndDialog(hwnd, IDOK);
            return TRUE;

        default:
            return FALSE;
    }
}
