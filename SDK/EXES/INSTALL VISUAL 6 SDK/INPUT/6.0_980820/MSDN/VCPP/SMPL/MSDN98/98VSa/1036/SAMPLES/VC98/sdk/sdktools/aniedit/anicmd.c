/****************************************************************************\
*
*     MODULE: anicmd.c
*
*     PURPOSE: Processes WM_COMMANDs for the Animated Cursor Editor
*
*     Copyright 1993-1996 Microsoft Corp.
*
*
* History:
*   21-Apr-1993 JonPa   Wrote it.
*
\****************************************************************************/

#include <windows.h>
#include <commdlg.h>
#include <search.h>
#include "anidefs.h"

static DWORD WINAPI ProcWaitThread( LPVOID lpv );
static BOOL CALLBACK ETWProc( HWND hwnd, LPARAM lParam );

BOOL gfEditFrame = FALSE;
TCHAR gszTempFile[MAX_PATH];


/****************************************************************************\
*
*     FUNCTION: void AniEndDialog( HDLG hdlg, int i )
*
*     PURPOSE:  Destroys Modless Dialogs
*
*
* History:
*   08-Sep-1995 JonPa   Created it
*
\****************************************************************************/
#define AniEndDialog( hdlg, i )         DestroyWindow( hdlg )

/****************************************************************************\
*
*     FUNCTION: void LoadAniFile(hWnd, hfCursor, szFileTitle, szFile)
*
*     PURPOSE:  Loads an ANI from the given handle, and sets up ganiAcon
*
*
* History:
*   31-May-1995 JonPa   Created it
*
\****************************************************************************/
void LoadAniFile(HWND hWnd, HANDLE hfCursor, LPTSTR szFileTitle, LPTSTR szFile)
{
    /* delete any existing ani file */
    NewAniCursor( hWnd );

    /* read in the file */
    if (!ReadAniFile( hWnd, hfCursor )) {
        FmtMessageBox( hWnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP, TRUE,
                MSG_INVALIDCURSORFILE, szFileTitle );
    } else {
        /*
         * Put the filename in the title.
         */
        lstrcpy(ganiAcon.szFile, szFile);
        SetWindowFileTitle(hWnd, szFileTitle);
        SetDlgItemInt( hWnd, DLG_MAIN_RATE, ganiAcon.anih.jifRate, FALSE);
    }

    ResumePreview(hWnd, DLG_MAIN_PREVIEW);
}

/****************************************************************************\
*
*     FUNCTION: DoCommand(HWND, unsigned, WORD, LONG)
*
*     PURPOSE:  Processes commands for the main dialog box
*
*     MESSAGES:
*
*         WM_INITDIALOG - initialize dialog box
*         WM_COMMAND    - Input received
*
*     COMMENTS:
*
*
* History:
*   21-Apr-1993 JonPa   Created it
*
\****************************************************************************/
BOOL DoCommand( HWND hWnd, UINT wParam, LONG lParam )
{
    int cmd = LOWORD(wParam);

    switch(cmd){


    case MENU_FILE_NEW:
    case DLG_MAIN_BTNNEW:
        /* If dirty, then prompt for save */
        if(!CheckDirty(hWnd))
            break;

        /* free used memory and init structures and dlg */
        NewAniCursor(hWnd);
        ResumePreview(hWnd, DLG_MAIN_PREVIEW);
        break;

    case DLG_MAIN_BTNOPEN:
    case MENU_FILE_OPEN: {
        HANDLE hfCursor;
        TCHAR szFileTitle[MAX_PATH];
        TCHAR szFile[MAX_PATH];


        szFile[0] = TEXT('\0');

        /* check for dirty file */
        if(!CheckDirty(hWnd))
            break;

        /* Put up the open file dialog and get the open handle back */
        hfCursor = PromptAndOpenFile(hWnd, MAX_PATH, szFileTitle,
                 COUNTOF(ganiAcon.szFile), szFile, gpszAniFilter);

        if (hfCursor == INVALID_HANDLE_VALUE)
            break;

        LoadAniFile(hWnd, hfCursor, szFileTitle, szFile );

        break;
    }

    case DLG_MAIN_BTNSAVE:
    case MENU_FILE_SAVE:
    case MENU_FILE_SAVEAS:
        SaveFile(hWnd, cmd == MENU_FILE_SAVEAS);
        break;

    case MENU_FILE_INSERT: {
        TCHAR szFile[MAX_PATH];

        szFile[0] = TEXT('\0');

        /* Put up the open file dialog and get the open handle back */
        if (PromptForFile(hWnd, 0, NULL,
                 MAX_PATH, szFile, gpszCurFilter, gpszImport, FALSE)) {

            /*
             * If we got a file, open it and read the icon data, linking
             * it into the frame list and maintaining the steps as well.
             */
            ganiAcon.fDirty = TRUE;
            CreateFrameFromCursorFile(hWnd, szFile, FALSE);
        }
        break;
    }

    case MENU_FILE_EXPORT: {
#if 0
        TCHAR szFile[MAX_PATH];
        szFile[0] = TEXT('\0');

        /* Put up the open file dialog and get the open handle back */
        if (PromptForFile(hWnd, 0, NULL,
                 MAX_PATH, szFile, NULL, gpszExport, TRUE)) {

            /*
             * If we got a file, open it and read the icon data, linking
             * it into the frame list and maintaining the steps as well.
             */
            ????
        }
#else
        WRITEME(hWnd);
#endif
        break;
    }

    case MENU_FILE_EXIT:
        ExitCommand(hWnd);
        break;

    case DLG_MAIN_BTNCUT:
    case MENU_EDIT_CUT:
        ganiAcon.fDirty = TRUE;

        FALLTHRU(MENU_EDIT_COPY);

    case DLG_MAIN_BTNCOPY:
    case MENU_EDIT_COPY: {
        int *piSel;
        int cSel;

        cSel = GetSelStepCount(hWnd);

        if( cSel > 0 && (piSel = AllocMem(cSel * sizeof(int))) != NULL) {
            PCLPBRDDAT pcbd, pcbdNext, *ppcbd;

            int i;

            GetCurrentSel(hWnd, DLG_MAIN_FRAMELIST, piSel, cSel, &cSel);

            /* Clear clipboard */
            for( pcbd = gpbdClipBoard; pcbd != NULL; pcbd = pcbdNext ) {
                pcbdNext = pcbd->pcbdNext;

                DestroyClpBrdDat(pcbd);
            }

            /*
             * Get the steps and put them in the clipboard in the correct order
             */
            ppcbd = &gpbdClipBoard;

            for( i = 0; i < cSel; i++ ) {
                PSTEP ps;

                ps = GetStep(hWnd, piSel[i]);

                if( IsValidPS(ps) && (pcbd = NewClpBrdDat()) != NULL) {
                    CopyStep(&(pcbd->stp), ps);
                    *ppcbd = pcbd;
                    ppcbd = &(pcbd->pcbdNext);
                }
            }

            *ppcbd = NULL;

            /*
             * If this is a cut, then yank them out of the listbox
             */
            if (cmd == MENU_EDIT_CUT || cmd == DLG_MAIN_BTNCUT) {
                qsort( piSel, cSel, sizeof(piSel[0]), RevCompInts );
                for( i = 0; i < cSel; i++ ) {
                    SendDlgItemMessage(hWnd, DLG_MAIN_FRAMELIST,
                            LB_DELETESTRING, piSel[i], 0);
                }

                FreeMem(piSel);

                ClearStepSel(hWnd);
            }
        }

        break;
    }

    case DLG_MAIN_BTNPASTE:
    case MENU_EDIT_PASTE: {
        PCLPBRDDAT pcbd;
        int iSel, cSel;

        cSel = GetSelStepCount(hWnd);

        if (cSel > 1) {
            FmtMessageBox( hWnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP,
                    TRUE, MSG_LESSEQONEFRAME);
            break;
        }

        GetCurrentSel(hWnd, DLG_MAIN_FRAMELIST, &iSel, 1, &cSel);

        if (cSel == 0)
            iSel = GetStepCount(hWnd) - 1;

        cSel = iSel;
        ganiAcon.fDirty = TRUE;

        for( pcbd = gpbdClipBoard; pcbd != NULL; pcbd = pcbd->pcbdNext ) {
            PSTEP ps = NewStep();

            if (IsValidPS(ps)) {
                CopyStep(ps, &(pcbd->stp));

                SendDlgItemMessage(hWnd, DLG_MAIN_FRAMELIST, LB_INSERTSTRING,
                    ++cSel, (LPARAM)ps);
            } else {
                FmtMessageBox( hWnd, TITL_ERROR, NULL, MB_OKCANCEL |
                        MB_ICONEXCLAMATION, TRUE, MSG_PASTEERR );
            }
        }

        /* in this case, cSel is actually an index */
        iSel += 1;
        ClearStepSel(hWnd);
        SetStepSel(hWnd, iSel, cSel);

        break;
    }

    case DLG_MAIN_DELFRAME:
    case MENU_EDIT_CLEAR: {
        int *piSel;
        int cSteps = GetSelStepCount(hWnd);
        int i;

        if (cSteps <= 0)
            //BUGBUG - should we put a message box up here?
            break;

        ganiAcon.fDirty = TRUE;

        piSel = AllocMem(cSteps * sizeof(int));
        if (piSel == NULL)
            break;

        GetCurrentSel(hWnd, DLG_MAIN_FRAMELIST, piSel, cSteps, &cSteps);

        qsort( piSel, cSteps, sizeof(piSel[0]), RevCompInts );
        for( i = 0; i < cSteps; i++ ) {
            SendDlgItemMessage(hWnd, DLG_MAIN_FRAMELIST, LB_DELETESTRING,
                    piSel[i], 0);
        }

        FreeMem(piSel);
        ClearStepSel(hWnd);

        break;
    }

    case DLG_MAIN_DUPFRAME:
    case MENU_EDIT_DUP:
        /* copy */
        /* paste */
        ganiAcon.fDirty = TRUE;
        WRITEME(hWnd);
        break;

    case DLG_MAIN_EDITFRAME:
    case MENU_EDIT_EDITFRAME:
    case DLG_MAIN_ADDFRAME:
    case MENU_EDIT_ADDFRAME: {
        BOOL fEditFrame;

        ganiAcon.fDirty = TRUE;

        fEditFrame = (cmd == MENU_EDIT_EDITFRAME ||
                    cmd == DLG_MAIN_EDITFRAME);


        EditFrame(hWnd, fEditFrame);

        break;
    }

    case DLG_MAIN_STOP:
        PausePreview(hWnd, DLG_MAIN_PREVIEW);
        break;

    case DLG_MAIN_PLAY:
        ResumePreview(hWnd, DLG_MAIN_PREVIEW);
        break;

    case MENU_HELP_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(DLG_ABOUT), hWnd, About);
        break;

    case MENU_HELP_CONTENTS:

        //WinHelp(hWnd, TEXT("RKTOOLS.HLP"), HELP_COMMAND, (DWORD)TEXT("JI(\"RKTOOLS.HLP\">\"main\",\"aniedit\")"));
        //WinHelp(hWnd, TEXT("RKTOOLS.HLP"), HELP_COMMAND, (DWORD)TEXT("JI(\"RKTOOLS.HLP\",\"aniedit\")"));
        WinHelp(hWnd, TEXT("RKTOOLS.HLP"), HELP_COMMAND, (DWORD)TEXT("JI(\"RKTOOLS.HLP>main\",\"aniedit\")"));
        break;

    case MENU_EDIT_OPTIONS:
        if (DialogBox(hInst, MAKEINTRESOURCE(DLG_OPTIONS), hWnd, OptionsProc)){
            InvalidateRect( GetDlgItem(hWnd, DLG_MAIN_PREVIEW), NULL, TRUE);
        }
        break;

    case DLG_MAIN_FRAMELIST: {
        HWND hwndLB = (HWND)lParam;

        switch(HIWORD(wParam)) {

            case LBN_SELCHANGE: {
                PSTEP ps;
                int cSel;
                LPTSTR pszText;

                cSel = SendMessage(hwndLB, LB_GETSELCOUNT, 0, 0);

                if (cSel > 1) {
                    int *piSel;
                    int i;

                    pszText = FmtSprintf( cSel == GetStepCount(hWnd) ?
                            MSG_ALLFRAMES : MSG_FRAMESSELECTED, cSel );
                    SetDlgItemText(hWnd, DLG_MAIN_FRAMEGRP, pszText);
                    FmtFree( pszText );

                    piSel = AllocMem( cSel * sizeof(int) );
                    if( piSel == NULL )
                        break;

                    GetCurrentSel(hWnd, DLG_MAIN_FRAMELIST, piSel, cSel, &cSel);
                    for( i = 0; i < cSel; i++ ) {
                        ps = GetStep(hWnd, piSel[i]);

                        if( IsValidPS(ps) ) {
                            if (i == 0) {
                                ganiAcon.anih.jifRate = ps->jif;
                            } else if(ganiAcon.anih.jifRate != ps->jif) {
                                break;
                            }
                        }
                    }

                    if (i < cSel) {
                        /* rates differ, wipe out jiffy edit control */
                        SetDlgItemText(hWnd, DLG_MAIN_RATE, "");
                    } else {
                        SetDlgItemInt(hWnd, DLG_MAIN_RATE,
                                ganiAcon.anih.jifRate, FALSE);
                    }

                    FreeMem(piSel);

                } else if (cSel == 1) {
                    int iLBSel;

                    GetCurrentSel(hWnd, DLG_MAIN_FRAMELIST, &iLBSel, 1, &cSel);

                    SetPreviewStep(hWnd, DLG_MAIN_PREVIEW, iLBSel);

                    pszText = FmtSprintf( MSG_FRAMEOFSEL, iLBSel + 1,
                            GetStepCount(hWnd) );
                    SetDlgItemText(hWnd, DLG_MAIN_FRAMEGRP, pszText);
                    FmtFree( pszText );

                    ps = (PSTEP)SendMessage(hwndLB, LB_GETITEMDATA, iLBSel, 0);

                    if (IsValidPS(ps)) {
                        SetDlgItemInt( hWnd, DLG_MAIN_RATE, ps->jif, FALSE);
                    }
                } else {
                    pszText = FmtSprintf( MSG_NOFRAMESSEL );
                    SetDlgItemText(hWnd, DLG_MAIN_FRAMEGRP, pszText);
                    FmtFree( pszText );
                    SetPreviewStep(hWnd, DLG_MAIN_PREVIEW, 0);
                }
                break;

            case LBN_DBLCLK:
                ganiAcon.fDirty = TRUE;
                EditFrame(hWnd, TRUE);
                break;
            }
        }
        break;

    }

    case DLG_MAIN_RATE: {
        static BOOL fEditCtlHasFocus = FALSE;
        static BOOL fEditCtlHasChanged = FALSE;
        int *piSel;
        int cSteps;
        int i;

        switch(HIWORD(wParam)) {
        case EN_SETFOCUS:
            fEditCtlHasFocus = TRUE;
            break;

        case EN_KILLFOCUS:
            fEditCtlHasFocus = FALSE;
            break;

        case EN_CHANGE:

            cSteps = GetSelStepCount(hWnd);

            if (fEditCtlHasFocus && cSteps >=1 &&
                    GetWindowTextLength(GetDlgItem(hWnd, DLG_MAIN_RATE)) > 0) {
                JIF jif;
                BOOL fOK;

                ganiAcon.fDirty = TRUE;
                piSel = AllocMem( cSteps * sizeof(int) );
                if (piSel == NULL) {
                    SetFocus((HWND)lParam);
                    break;
                }


                jif = GetDlgItemInt(hWnd, DLG_MAIN_RATE, &fOK, FALSE);

                if (jif == 0 || !fOK) {
                    FmtMessageBox(hWnd, MSG_LITERAL, gszWindowTitle,
                        MB_OK | MB_ICONEXCLAMATION, TRUE,
                        MSG_RATERANGE);
                    SetFocus((HWND)lParam);
                    break;
                }

                GetCurrentSel(hWnd, DLG_MAIN_FRAMELIST, piSel, cSteps,
                        &cSteps);

                for( i = 0; i < cSteps; i++ ) {
                    PSTEP ps = GetStep(hWnd, piSel[i]);

                    if (IsValidPS(ps)) {
                        ps->jif = jif;
                    }
                }
                InvalidateRect(GetDlgItem(hWnd,DLG_MAIN_FRAMELIST), NULL,TRUE);

                FreeMem( piSel );
            }
            break;
        }
        break;
    }

    default:
        return FALSE;
    }

    return TRUE;
}

/****************************************************************************\
*
*     FUNCTION: About(HWND, unsigned, WORD, LONG)
*
*     PURPOSE:  Processes messages for "About" dialog box
*
*     MESSAGES:
*
*         WM_INITDIALOG - initialize dialog box
*         WM_COMMAND    - Input received
*
*     COMMENTS:
*
*         No initialization is needed for this particular dialog box, but TRUE
*         must be returned to Windows.
*
*         Wait for user to click on "Ok" button, then close the dialog box.
*
\****************************************************************************/

BOOL APIENTRY About(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,              /* message-specific information    */
        LONG lParam)
{
    switch (message) {
        case WM_INITDIALOG:                /* message: initialize dialog box */
            return (TRUE);

        case WM_COMMAND:                      /* message: received a command */
            if (LOWORD(wParam) == IDOK        /* "OK" box selected?          */
                || LOWORD(wParam) == IDCANCEL) { /*System menu close command?*/
                EndDialog(hDlg, TRUE);        /* Exits the dialog box        */
                return (TRUE);
            }
            break;
    }
    return (FALSE);                           /* Didn't process a message    */
        UNREFERENCED_PARAMETER(lParam);
}


/****************************************************************************\
*
*     FUNCTION: OptionsProc(HWND, unsigned, WORD, LONG)
*
*     PURPOSE:  Processes messages for "Options" dialog box
*
*     MESSAGES:
*
*         WM_INITDIALOG - initialize dialog box
*         WM_COMMAND    - Input received
*
\****************************************************************************/

BOOL APIENTRY OptionsProc(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,              /* message-specific information    */
        LONG lParam)
{
    int i;
    int fRepaint = FALSE;

    switch (message) {
    case WM_INITDIALOG:                /* message: initialize dialog box */
        SendDlgItemMessage(hDlg, DLG_OPTIONS_EDITOR, EM_LIMITTEXT, MAX_PATH, 0);
        SetDlgItemText(hDlg, DLG_OPTIONS_EDITOR, gszCursorEditor);
        CheckRadioButton( hDlg,
                          DLG_OPTIONS_RADIO_DESKCOL,
                          DLG_OPTIONS_RADIO_WINCOL,
                          garadColor[giradColor].id );
        return (TRUE);

    case WM_COMMAND:                      /* message: received a command */
        switch(LOWORD(wParam)) {
        case IDOK:

            /*
             * Get the new desk color
             */
            for( i = 0; garadColor[i].id != 0; i++ ) {
                if( IsDlgButtonChecked(hDlg, garadColor[i].id) ) {
                    break;
                }
            }

            if (i != giradColor ) {
                /* new color, make new brush and repaint */
                if (ghbrPrevBackgnd != NULL)
                    DeleteObject(ghbrPrevBackgnd);

                ghbrPrevBackgnd =
                        CreateSolidBrush(GetSysColor(garadColor[i].idSys));
                giradColor = i;
                fRepaint = TRUE;
            }

            /*
             * Get new editor
             */
            GetDlgItemText(hDlg,DLG_OPTIONS_EDITOR,
                    gszCursorEditor,COUNTOF(gszCursorEditor));

            for( i = 0; i < COUNTOF(gszCursorEditor); i++ ) {

                if (gszCursorEditor[i] == TEXT('\0'))
                    break;

                if (gszCursorEditor[i] == TEXT('%') &&
                        ++i < COUNTOF(gszCursorEditor) &&
                        gszCursorEditor[i] == TEXT('1')) {
                    break;
                }
#if defined(DBCS) && !defined(UNICODE)
                if (IsDBCSLeadByte(gszCursorEditor[i])) {
                    i++;
                }
#endif
            }


            if (i >= COUNTOF(gszCursorEditor) ||
                gszCursorEditor[i] != TEXT('1')) {

                if (i >= (COUNTOF(gszCursorEditor) - 4)) {
                    i =  COUNTOF(gszCursorEditor) - 4;
                }

                lstrcpy(&gszCursorEditor[i], TEXT(" %1"));
            }

        case IDCANCEL:
            EndDialog(hDlg, fRepaint);        /* Exits the dialog box        */
            return (TRUE);

        default:
            break;
        }
        break;
    }
    return (FALSE);                           /* Didn't process a message    */
        UNREFERENCED_PARAMETER(lParam);
}


/****************************************************************************\
*
*     FUNCTION: ExitCommand(HWND)
*
*     PURPOSE:  Exit the program chekcing for dirty files etc.
*
*
\****************************************************************************/
VOID ExitCommand(HWND hWnd) {

    /* if file is dirty then prompt for save */
    if(CheckDirty(hWnd))
        AniEndDialog(hWnd, TRUE);
}

/****************************************************************************\
*
*     FUNCTION: CheckDirty(HWND)
*
*     PURPOSE:  check for dirty files and return TRUE if it is OK to continue.
*
*
\****************************************************************************/
BOOL CheckDirty(HWND hWnd) {
    int idRet;

    /* if file is dirty then prompt for save */
    if (ganiAcon.fDirty) {
        idRet = FmtMessageBox( hWnd, MSG_LITERAL, gszWindowTitle,
                MB_YESNOCANCEL | MB_ICONEXCLAMATION, TRUE, MSG_SAVEFILEQUEST,
                ganiAcon.szFile);

        switch( idRet ) {
        case IDYES:
            SaveFile(hWnd, FALSE);
            break;

        case IDNO:
            break;

        case IDCANCEL:
            return FALSE;
        }
    }

    return TRUE;
}


/****************************************************************************\
*
*     FUNCTION: HWND ExecProgram(  HWND hwndCaller, LPTSTR pszCmdLine )
*
*     PURPOSE:  Creates a process and returns the new processes main window
*
*     RETURNS: NULL if the process could not be created, otherwise the
*              processes main window handle.
*
*     SIDEEFFECT: This function will also start a thread that will block
*               on the process handle until the process terminates.  At that
*               time, the thread will post a message back to the calliers
*               window.
*
*
* History:
*   22-Apr-1993 JonPa   Created it
*
\****************************************************************************/
BOOL ExecProgram( HWND hwndCaller, LPTSTR pszCmdLine ) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HWND hwnd;
    PTHDDATA pthd;
    DWORD tid;
    HANDLE hthrd;

    /*
     * Create the monitor thread (suspened)
     */
    pthd = AllocMem(sizeof(THDDATA));

    if (pthd == NULL)
        return FALSE;

    /* set thread data to be invalid incase we have to abort */
    pthd->hprocMonitor = NULL;
    pthd->hwndCaller = hwndCaller;

    if ((hthrd = CreateThread( NULL, 0, ProcWaitThread, pthd, CREATE_SUSPENDED,
            &tid )) == NULL) {
        /* could not create the monitor thread, return error */
        FreeMem(pthd);
        return FALSE;
    }

    /*
     * Create the process
     */
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    si.wShowWindow = SW_SHOW;
    si.dwFlags = STARTF_USESHOWWINDOW;

    if (!CreateProcess( NULL, pszCmdLine, NULL, NULL, FALSE, 0, NULL, NULL,
            &si, &pi)) {
        ResumeThread(hthrd);    // make thread localfree the data and exit
        return FALSE;
    }

    DPRINT(("MT:Child IDs proc/thd: 0x%lx / 0x%lx\n", pi.dwProcessId, pi.dwThreadId));
    DPRINT(("MT:Child Hnd proc/thd: 0x%lx / 0x%lx\n", pi.hProcess, pi.hThread));

    /*
     * Wait for the main window to be created
     */
    if( WaitForInputIdle( pi.hProcess, CMS_WAIT_FOR_PROCESS ) != 0 ) {
        ResumeThread(hthrd);    // make thread localfree the data and exit
        return FALSE;
    }

    DPRINT(("MT:Child is idle\n"));

    /*
     * Enumerate the new processes main thread's windows and
     * return the main one.
     */
    hwnd = NULL;
    EnumThreadWindows( pi.dwThreadId, ETWProc, (LPARAM)&hwnd );

#if 0
    if (hwnd != NULL) {
        pthd->hprocMonitor = pi.hProcess;
        pthd->hwndMonitor = hwnd;

        SendMessage(hwndCaller, AIM_SETCHILDAPP, 0, hwnd);
    }
#else
    pthd->hprocMonitor = pi.hProcess;
    pthd->hwndMonitor = hwnd;

    if (pthd->hprocMonitor != NULL)
        SendMessage(hwndCaller, AIM_SETCHILDAPP, 0, (LPARAM)hwnd);
#endif

    ResumeThread(hthrd);
    CloseHandle(hthrd);
    CloseHandle(pi.hThread);
    return TRUE;
}


/****************************************************************************\
*
*     FUNCTION: BOOL CALLBACK ETWProc( HWND hwnd, LPARAM lParam )
*
*     PURPOSE:  Enumeration proc for ExecProgram.  It looks for the thread's
*               top level window.
*
* History:
*   22-Apr-1993 JonPa   Created it
*
\****************************************************************************/
BOOL CALLBACK ETWProc( HWND hwnd, LPARAM lParam ) {
    DWORD *pdw = (DWORD *)lParam;

    /*
     * If this window has no parent, then it is a toplevel
     * window for the thread.  Remember the last one we find since it
     * is probably the main window.
     */

    if (GetParent(hwnd) == NULL) {
        DPRINT(("MT:EnumThdWin found 0x%lx\n", (DWORD)hwnd));
        *pdw = (DWORD)hwnd;
    }

    return TRUE;
}

/****************************************************************************\
*
*     FUNCTION: DWORD ProcWaitThread( LPDWORD lpdw )
*
*     PURPOSE:  Thread to wait on a process and then post a message
*
*
* History:
*   22-Apr-1993 JonPa   Created it
*
\****************************************************************************/
DWORD WINAPI ProcWaitThread( LPVOID lpv ) {
    LPDWORD lpdw = lpv;
    PTHDDATA pthd = (PTHDDATA)lpdw;
    DWORD dwRet;

    if (pthd->hprocMonitor == NULL) {
        /* something went wrong, just exit now */
        DPRINT(("wt:Aborting\n"));
        FreeMem( lpdw );
        ExitThread(0);
    }

    DPRINT(("wt:Waiting\n"));
    dwRet = WaitForSingleObject( pthd->hprocMonitor, INFINITE );

    DPRINT(("wt:Send AIM_PROCESSTERM\n"));
    SendMessage(pthd->hwndCaller, AIM_PROCESSTERM, (dwRet == WAIT_OBJECT_0),
            (LPARAM)pthd->hwndMonitor);

    CloseHandle( pthd->hprocMonitor );
    FreeMem( lpdw );
    ExitThread(0);

    return 0;
}


/****************************************************************************\
*
*     FUNCTION: void NewAniCursor( HWND hwnd )
*
*     PURPOSE:  erase any used memory and init to a clean slate
*
*
* History:
*   22-Apr-1993 JonPa   Created it
*
\****************************************************************************/
void NewAniCursor( HWND hwnd ) {
    int i, cSteps;
    LPTSTR psz;

    PausePreview(hwnd, DLG_MAIN_PREVIEW);

    /* Step through the list box, deleting all the lb entryies and everything
     * that they point to (except the icons).
     */
    cSteps = GetStepCount(hwnd);

    if (cSteps != LB_ERR) {
        for( i = 0; i < cSteps; i++ ) {
            /*
             * Delete the top item of the list.  Note that once that item
             * (current index 0) is deleted, then the next item will move
             * up and become index 0.
             */
            SendDlgItemMessage( hwnd, DLG_MAIN_FRAMELIST, LB_DELETESTRING,0,0);
        }
    }


    /*
     * Step through the icon list deleting them.  We don't need to call
     * DestroyFrame since we are trashing the whole chain.
     */

#if 0
    pf = gpfrmFrames;
    gpfrmFrames = NULL;

    DON'T DO THIS!!! it will wipe out the clip board accidentally!

    for(; pf != NULL; pf = pfrmNext ) {
        pfrmNext = pf->pfrmNext;

        DestroyIcon( pf->hcur );
        FreeMem(pf);
    }
#endif

    /*
     * Init Ani header
     */
    ZeroMemory( &ganiAcon, sizeof(ganiAcon) );
    ganiAcon.anih.cbSizeof = sizeof(ganiAcon);
    ganiAcon.anih.cbSizeof = AF_ICON;
    ganiAcon.anih.jifRate = 10;

    SetDlgItemTextA(hwnd, DLG_MAIN_TITLE, ganiAcon.azTitle);
    SetDlgItemTextA(hwnd, DLG_MAIN_AUTHOR, ganiAcon.azCreator);

    SetDlgItemInt( hwnd, DLG_MAIN_RATE, ganiAcon.anih.jifRate, FALSE);

    PreviewCursor(hwnd, DLG_MAIN_PREVIEW);

    SetWindowFileTitle(hwnd, gpszUntitled );

    psz = FmtSprintf(MSG_NOFRAMESSEL);
    SetDlgItemText(hwnd, DLG_MAIN_FRAMEGRP, psz);
    FmtFree( psz );
}

/****************************************************************************\
*
*     FUNCTION: BOOL GetCurrentSel( HWND hwnd, int id, int * paiSel,
*                                                   int ciSel, int *pcSel );
*
*     PURPOSE:  Gets the selections and returns it's index
*
*
* History:
*   22-Apr-1993 JonPa   Created it
*
\****************************************************************************/
BOOL GetCurrentSel( HWND hwnd, int id, int * paiSel, int ciSel, int *pcSel ) {

#ifdef MULTISEL
    *pcSel = SendDlgItemMessage(hwnd,id, LB_GETSELITEMS, ciSel,(LPARAM)paiSel);

    if (*pcSel == LB_ERR) {
        *pcSel = 0;
    }
#else

    *paiSel = SendDlgItemMessage(hwnd, id, LB_GETCURSEL, 0, 0);
    *pcSel = 1;

    if (*paiSel == LB_ERR)
        *pcSel = 0;
#endif

    return TRUE;
}

/****************************************************************************\
*
*     FUNCTION: VOID SetCurrentSel( HWND hwnd, int id, BOOL fExtend, int iSel);
*
*     PURPOSE:  Sets the selections and returns it's index
*
*
* History:
*   29-Apr-1993 JonPa   Created it
*
\****************************************************************************/
VOID SetCurrentSel( HWND hwnd, int id, BOOL fExtend, int iSel) {
#ifdef MULTISEL
    if (!fExtend) {
        SendDlgItemMessage(hwnd, id, LB_SETSEL, FALSE, -1);
    }

    SendDlgItemMessage(hwnd, id, LB_SETSEL, TRUE, iSel);
#else
    SendDlgItemMessage(hwnd, id, LB_SETCURSEL, iSel, 0);
#endif

    UpdateStepSel( hwnd );
}


/****************************************************************************\
*
*     FUNCTION: VOID EditFrame(HWND hwnd, int iSel);
*
*     PURPOSE:  Runs ImagEdit on the frame indexed by iSel
*
*
* History:
*   27-Apr-1993 JonPa
*
\****************************************************************************/
VOID EditFrame(HWND hWnd, BOOL fEditFrame) {
    LPTSTR pszCmdLine = NULL;
    int cchCmdLine;
    HANDLE hf;
    DWORD cb;
    PBYTE pbIcon;
    DWORD cbIcon;
    int iSel;
    int cSel;
    BOOL fExeced;

    /* create a temp .cur file name */
    if( !GetTempCursorFileName( gszTempFile ) ) {
        FmtMessageBox( hWnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP,
                TRUE, MSG_OUTOFRESOUCES );
        return;
    }


    cSel = GetSelStepCount(hWnd);

    if ( (fEditFrame && (cSel != 1)) || cSel > 1 ) {

        FmtMessageBox( hWnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP,
                TRUE, fEditFrame ? MSG_MUSTEQONEFAME : MSG_LESSEQONEFRAME);
        return;
    }

    /* cache the currently selected item (Singluar) */
    GetCurrentSel( hWnd, DLG_MAIN_FRAMELIST, &iSel, 1, &cSel );

    /*
     * If edit, then write the frame to the file and save checksum
     * otherwise write the blank cursor to the file.
     */

    hf = CreateFile( gszTempFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL );


    if (hf == INVALID_HANDLE_VALUE) {
        FmtMessageBox( hWnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP, TRUE,
            MSG_CANTCREATEFILE, gszTempFile );
        return;
    }

    if (fEditFrame || cSel != 0) {
        PSTEP ps = GetStep(hWnd, iSel);

        if( !IsValidPS(ps) ) {
            FmtMessageBox( hWnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP,
                    TRUE, MSG_OUTOFRESOUCES );
            CloseHandle(hf);
            return;
        }


        pbIcon = ps->pfrmFrame->abIcon;
        cbIcon = ps->pfrmFrame->rtag.ckSize;

    } else {

        HRSRC hr = FindResource(hInst, MAKEINTRESOURCE(ID_BLANKCUR),
                MAKEINTRESOURCE(RCT_RAWDATA));

        if (hr == NULL || (pbIcon =LockResource(LoadResource(hInst, hr))) ==
                NULL) {
            FmtMessageBox( hWnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP,
                    TRUE, MSG_OUTOFRESOUCES );
            CloseHandle(hf);
            return;
        }

        cbIcon = SizeofResource(hInst, hr);
    }

    WriteFile(hf, pbIcon, cbIcon, &cb, NULL);

    CloseHandle(hf);

    /*
     * change .tmp to .cur
     */
    { TCHAR szOldName[MAX_PATH];

        cchCmdLine = lstrlen(gszTempFile);

        lstrcpy( szOldName, gszTempFile );
        lstrcpy( &gszTempFile[cchCmdLine - 3], gpszCUR );

        if(!MoveFile(szOldName, gszTempFile))
            lstrcpy( gszTempFile, szOldName );

        cchCmdLine = (cchCmdLine + lstrlen(gszCursorEditor) + 1 + 1) *
                sizeof(TCHAR);

        pszCmdLine = AllocMem(cchCmdLine);
    }

    if (pszCmdLine == NULL)
        return;

    {
        LPTSTR pszTempFile = gszTempFile;

        FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
                gszCursorEditor, 0, 0, pszCmdLine, cchCmdLine, (va_list *)(DWORD)&pszTempFile);
    }

    /* spawn imagedit on the file */
    fExeced = ExecProgram( hWnd, pszCmdLine );
    DPRINT(("MT:Begin Defer to child\n"));

    FreeMem(pszCmdLine);

    if ( fExeced  ) {
        gfEditFrame = fEditFrame;
    } else {
        FmtMessageBox( hWnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP,
                    TRUE, MSG_NOIMAGEDIT, gszCursorEditor );
    }
}




/****************************************************************************\
*
*     FUNCTION: PSTEP NewStep( void );
*
*
*     PURPOSE:  Creates a new step and set's its pfrmFrame to NULL;
*
*
* History:
*   29-Apr-1993 JonPa   Created it
*
\****************************************************************************/
PSTEP NewStep( void ) {
    PSTEP ps;

    ps = AllocMem(sizeof(STEP));

    if (IsValidPS(ps))
        ps->pfrmFrame = NULL;

    return ps;
}

/****************************************************************************\
*
*     FUNCTION: VOID DestroyStep( PSTEP ps );
*
*
*     PURPOSE:  Deletes a step, and derefernces its frame, deleting it if
*               necessary.
*
* History:
*   29-Apr-1993 JonPa   Created it
*
\****************************************************************************/
VOID DestroyStep( PSTEP ps ) {
    LinkStepFrame(ps, NULL);

    FreeMem(ps);
}


/****************************************************************************\
*
*     FUNCTION: VOID CopyStep( PSTEP psDst, PSTEP psSrc );
*
*
*     PURPOSE:  Copyies a step, bumping the ref count of the frame if it
*               needs it.
*
* History:
*   07-May-1993 JonPa   Created it
*
\****************************************************************************/
VOID CopyStep( PSTEP psDst, PSTEP psSrc ) {
    *psDst = *psSrc;

    if( psDst->pfrmFrame != NULL ) {
        psDst->pfrmFrame->cRef += 1;
    }
}


/****************************************************************************\
*
*     FUNCTION: VOID LinkStepFrame( PSTEP ps, PFRAME pf );
*
*
*     PURPOSE:  Unlinks a step from its frame and then links the new
*               frame in its place.  If the old frame is an orphan, it
*               gets destroyed.
*
*
* History:
*   29-Apr-1993 JonPa   Created it
*
\****************************************************************************/
VOID LinkStepFrame(PSTEP ps, PFRAME pf ) {
    PFRAME pfOld = ps->pfrmFrame;

    if (pf != NULL)
        pf->cRef++;

    if (pfOld != NULL && --(pfOld->cRef) == 0)
        DestroyFrame(pfOld);

    ps->pfrmFrame = pf;
}

/****************************************************************************\
*
*     FUNCTION: VOID DestroyFrame( PFRAME pf );
*
*
*     PURPOSE:  Unlinks a frame from the list, deletes its hcur, and
*               Frees its memory.
*
*
* History:
*   28-Apr-1993 JonPa   Created it
*
\****************************************************************************/
VOID DestroyFrame( PFRAME pf ) {
    PFRAME pfList;

    if (pf == gpfrmFrames) {
        gpfrmFrames = pf->pfrmNext;
    } else {

        for( pfList = gpfrmFrames; pfList != NULL;
                pfList = pfList->pfrmNext ) {

            if (pfList->pfrmNext == pf) {
                break;
            }
        }

        if (pfList != NULL) {
            pfList->pfrmNext = pf->pfrmNext;
        }
    }

    DestroyIcon( pf->hcur );
    FreeMem(pf);
}

/****************************************************************************\
*
*     FUNCTION: PCLPBRDDAT NewClpBrdDat( void )
*
*
*     PURPOSE:  Creates a new clip board data struct
*
*
* History:
*   29-Apr-1993 JonPa   Created it
*
\****************************************************************************/
PCLPBRDDAT NewClpBrdDat( void ) {
    PCLPBRDDAT pcbd = AllocMem( sizeof(CLPBRDDAT) );

    if (pcbd != NULL)
        pcbd->stp.pfrmFrame = NULL;

    return pcbd;
}

/****************************************************************************\
*
*     FUNCTION: VOID DestroyClpBrdDat(PCLPBRDDAT pcbd)
*
*
*     PURPOSE:  Creates a new clip board data struct
*
*
* History:
*   29-Apr-1993 JonPa   Created it
*
\****************************************************************************/
VOID DestroyClpBrdDat(PCLPBRDDAT pcbd) {
    LinkStepFrame(&(pcbd->stp), NULL);

    FreeMem(pcbd);
}

/****************************************************************************\
*
*     FUNCTION: VOID SetWindowFileTitle(HWND hWnd, LPTSTR szFileTitle)
*
*
*     PURPOSE:  Sets the file title
*
*
* History:
*   30-Apr-1993 JonPa   Created it
*
\****************************************************************************/
VOID SetWindowFileTitle(HWND hWnd, LPTSTR szFileTitle) {

    /*
     * We use LocalAlloc here instead of AllocMem because we don't really
     * char if it fails
     */
    int cch = lstrlen( gszWindowTitle ) + lstrlen(szFileTitle);
    LPTSTR pszTitle = LocalAlloc(LPTR, (cch+4) * sizeof(TCHAR) );

    if (pszTitle != NULL) {
        wsprintf( pszTitle, "%s - %s", gszWindowTitle, szFileTitle );
        SetWindowText(hWnd, pszTitle);

        LocalFree(pszTitle);
    } else {
        SetWindowText(hWnd, gszWindowTitle);
    }
}

int __cdecl RevCompInts(const void *elm1, const void *elm2) {
    return *((int *)elm2) - *((int *)elm1);
}

/****************************************************************************\
*
*     FUNCTION: ClearStepSel
*
*
*     PURPOSE:  Clears all selections from the frame list
*
*
* History:
*   02-Jul-1993 JonPa   Created it
*
\****************************************************************************/
VOID ClearStepSel( HWND hWnd )  {
    int cItems = GetStepCount(hWnd);

    if (cItems != 0) {
        SendDlgItemMessage(hWnd, DLG_MAIN_FRAMELIST,
                LB_SELITEMRANGE, (WPARAM)FALSE, MAKELPARAM(0, cItems - 1));
    }

    UpdateStepSel(hWnd);
}
