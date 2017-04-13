
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-96 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include "porttool.h"
#include "port.h"

/* forward declarations of helper functions in this module */
HWND   WINAPI StartInteractive (HANDLE, char *, int);
HANDLE WINAPI StartBackground (HANDLE, HWND, char *);
VOID   WINAPI InitializeMenu (HWND, HANDLE);
LONG   WINAPI CommandHandler (HWND, UINT, LONG);
int    WINAPI SetWrap (HWND);
BOOL   WINAPI GetCmdLine (char *, char *, BOOL *, char *);
int    WINAPI Save_YNC (HWND);
VOID   WINAPI SetWindowTitle (HWND, char*);
VOID   WINAPI GetEditSubString (HWND, PUINT, PUINT, char *);

UINT    uSearchMsg;
HWND    hDlgPortStatus;
HWND    hDlgPort;

DWORD   dwVersion=0; // Global variable to store current system version info


/* test case static variables for background porting */
HANDLE              hEvents[nBKPORTEVENTS];
BKPORTFILESTRUCT    BkPort;



/* entry point ot this executable */
int WINAPI WinMain (hInstance, hPrevInstance, lpCmdLine, nCmdShow)
    HANDLE hInstance;
    HANDLE hPrevInstance;
    LPSTR  lpCmdLine;
    int    nCmdShow;
{
    MSG        msg;
    HWND       hWnd;
    HANDLE     hAccel;
    BOOL       bBkgnd = 0;
    char       *lpszBuff = NULL;
    char       *lpszCmdLine = NULL;
    char       *lpCL;


    /* previous instances do not exist in Win32 */
    if (hPrevInstance)
	return 0;

    /* Get OS version info, and store in a global variable */
	dwVersion = GetVersion();

	lpszPortIniFilePath[0] = 0;

    /* parse and copy command line parameters to local memory */
    lpCL = GetCommandLine ();
    if (lpszCmdLine = (char *)LocalAlloc (LPTR, strlen (lpCL) + 1))
	GetCmdLine (lpCL, lpszCmdLine, &bBkgnd, lpszPortIniFilePath);

    /* if /b switch, start background porting session */
    if (bBkgnd)
	{
	/* invoke background port status dialog */
	// MessageBox(NULL, "Backgroud Porting Disabled","Porttool",MB_OK);

	if (lpszPortIniFilePath[0] == 0 )
	{
	   ErrorNotify (NULL, IDS_PORTFILEBACKMSG);
	   return FALSE;
	}
	else if ( ! InitPortData(lpszPortIniFilePath) )
	   ErrorNotify (NULL, IDS_PORTINITFAILED);

	if (!(hDlgPortStatus = StartBackground (hInstance, NULL, lpszCmdLine)))
		return FALSE;
	}

    /* start interactive porting session */
    else
	{
	if (!(hWnd = StartInteractive (hInstance, lpszCmdLine, nCmdShow)))
	    return FALSE;
	}

    /* free memory allocated for pCmdLine */
    if (lpszCmdLine)
	LocalFree ((HLOCAL)lpszCmdLine);

    /* load main accelerator table */
    hAccel = LoadAccelerators (hInstance, MAKEINTRESOURCE (IDA_PORTTOOL));

    /* main window message loop */
    while (GetMessage (&msg, NULL, 0, 0))
	{
	if ((!hDlgSearch     || !IsDialogMessage (hDlgSearch, &msg))     &&
	    (!hDlgPort       || !IsDialogMessage (hDlgPort, &msg))       &&
	    (!hDlgPortStatus || !IsDialogMessage (hDlgPortStatus, &msg)) &&
	    (!hAccel         || !TranslateAccelerator (hWnd, hAccel, &msg)))
	    {
	    TranslateMessage (&msg);
	    DispatchMessage (&msg);
	    }
	}

    /* return success of application */
    return TRUE;
}


//
// Used only on FE versions to screen out vertical fonts
//

BOOL APIENTRY ChooseFontHookProc(
    HWND hDlg,              /* window handle of the dialog box */
    UINT message,           /* type of message                 */
    WPARAM wParam,          /* message-specific information    */
    LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
        {
            LOGFONT lf;
            char szFaceName[LF_FACESIZE];
            UINT uiId, uiCount;

            uiCount = SendDlgItemMessage(hDlg, cmb1, CB_GETCOUNT, 0, 0L);
            /* Delete vertical font */
            for (uiId = 0; uiId < uiCount; uiId++) {
                SendDlgItemMessage(hDlg, cmb1, CB_GETLBTEXT,
                                   uiId, (LPARAM)(LPSTR)szFaceName);
                if (szFaceName[0] == '@') {
                    SendDlgItemMessage(hDlg, cmb1, CB_DELETESTRING, uiId, 0L);
                    uiId--;
                    uiCount--;
                }
            }
            /* Set selection current selected facename */
            SendMessage(hDlg, WM_CHOOSEFONT_GETLOGFONT, 0, (LPARAM)(LPSTR)&lf);
            uiId = SendDlgItemMessage(hDlg, cmb1, CB_FINDSTRING,
                                     0, (LPARAM)(LPSTR)lf.lfFaceName);
            SendDlgItemMessage(hDlg, cmb1, CB_SETCURSEL, uiId, 0L);
        }
        return (TRUE);
        break;
    }
    return (FALSE);
}



/* start background port status dialog */
HANDLE WINAPI StartBackground (
    HANDLE    hModule,
    HWND      hWndParent,
    char      *lpszCmdLine)
{
    return (CreateDialogParam (hModule,
			       IDD_BKPORTDIALOG,
			       hWndParent,
			       BkPortDlgProc,
			       (LPARAM)lpszCmdLine));
}


/* start interactive version of app */
HWND WINAPI StartInteractive (
    HANDLE    hInstance,
    char      *lpszCmdLine,
    int       nCmdShow)
    {
    WNDCLASS   wc;
    char       lpszClass[MAX_PATH];
    HWND       hWnd;
	char	   lpszFileName[MAX_PATH];

    /* load resources strings */
    LoadString (hInstance, IDS_APPNAME, lpszClass, sizeof (lpszClass));

    /* Register the frame class */
    wc.style         = 0;
    wc.lpfnWndProc   = (WNDPROC)MainWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = CBWNDEXTRA;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (hInstance, IDPortTool);
    wc.hCursor       = LoadCursor (NULL,IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = IDPortTool;
    wc.lpszClassName = lpszClass;

    if (!RegisterClass (&wc) )
	return FALSE;

    /* Create the frame */
    hWnd = CreateWindow (lpszClass,
			 "Win32 Port",
			 WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | DS_LOCALEDIT,
			 CW_USEDEFAULT,
			 0,
			 CW_USEDEFAULT,
			 0,
			 NULL,
			 NULL,
			 hInstance,
			 (*lpszCmdLine ? lpszCmdLine : 0));

    /* make sure window was created */
    if (!hWnd)
	return FALSE;

    /* register search/replace message for common dialog use */
    uSearchMsg = RegisterWindowMessage ((char *)FINDMSGSTRING);

    /* show and update main window */
    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);

	/* Ask for Port Information File */
	if (lpszPortIniFilePath[0] == 0 )
	   if ( !GetPortIniFileName (hWnd, lpszFileName, lpszPortIniFilePath) )
		  return FALSE;

	if ( ! InitPortData(lpszPortIniFilePath) )
	   ErrorNotify (hWnd, IDS_PORTINITFAILED);

    return hWnd;
}

/* main window procedure */
LONG WINAPI MainWndProc (
    HWND    hWnd,
    UINT    uMsg,
    UINT    uParam,
    LONG    lParam)
{
	LONG    lRet = 1;
	int     nResult;
	RECT    rc;

    switch (uMsg)
	{
	case WM_CREATE:
	    {
	    HWND              hWndEdit;
	    LPCREATESTRUCT    lpcs = (LPCREATESTRUCT)lParam;
	    char              lpszBuff[MAX_PATH];
	    LOGFONT           lfEditFont;
	    HFONT             hFont;
	    HCURSOR           hOldCursor;

	    /* put hourglass cursor up */
	    hOldCursor = (HCURSOR)SetClassLong (hWnd, GCL_HCURSOR, 0);
	    SetCursor (LoadCursor (NULL, IDC_WAIT));

	    /* Create an edit control */
	    GetClientRect (hWnd, &rc);
	    hWndEdit = CreateWindow ("edit",
				     " ",
				     WS_CHILD | WS_VISIBLE |
					 WS_HSCROLL | WS_VSCROLL |
					 ES_AUTOHSCROLL | ES_AUTOVSCROLL |
					 ES_MULTILINE,
				     rc.left,
				     rc.top,
				     rc.right-rc.left,
				     rc.bottom-rc.top,
				     hWnd,
				     (HMENU)IDC_EDIT,
				     (HANDLE)GetModuleHandle (NULL),
				     0);

	    /* if edit control failed, abort aplication */
	    if (!IsWindow (hWndEdit))
		{
		ErrorNotify (hWnd, IDS_EDITWNDFAILED);
		return FALSE;
		}

	    /* increase edit control max character limit beyond 30,000 default */
	    SendMessage (hWndEdit, EM_LIMITTEXT, 0x0FFFFFFF, 0);

	    /* save edit window handle and init state variables */
	    SetWindowLong (hWnd, WL_HWNDEDIT, (LONG) hWndEdit);
	    SetWindowWord (hWnd, WW_SCROLL, TRUE);
	    SetWindowWord (hWnd, WW_UNTITLED, TRUE);
	    SetWindowWord (hWnd, WW_SEARCHCASE, TRUE);
	    SetWindowWord (hWnd, WW_SEARCHDN, TRUE);
	    SetWindowLong (hWnd, WL_HPTRDEVNAMES, 0);

	    /* get printer configuration */
	    if (!GetPrinterConfig (hWnd))
		ErrorNotify (hWnd, IDS_PTRCONFIGFAILED);

	    /* if initialization file passed, load file now */
	    if (lpcs->lpCreateParams)
		{
		/* load filename passed at initialization */
		if ((nResult = LoadFile (hWnd, lpcs->lpCreateParams)) > 0)
		    {
		    /* save filename and path in global string */
		    strcpy (lpszFilePath, lpcs->lpCreateParams);

		    /* The file has a title, so reset the UNTITLED flag. */
		    SetWindowWord(hWnd, WW_UNTITLED, FALSE);

		    /* extract filename from path */
		    GetFileFromPath (lpszFilePath, lpszBuff);

		    /* set window text title to be "AppName - filename" */
		    SetWindowTitle (hWnd, lpszBuff);
		    }
		else
		    {
		    /* notify user of error */
			ErrorNotify (hWnd, 0-nResult);

		    /* set window title to "AppName - Untitled" */
		    LoadString ((HANDLE)GetModuleHandle (NULL),
				IDS_UNTITLED,
				lpszBuff,
				sizeof (lpszBuff));
		    SetWindowTitle (hWnd, lpszBuff);
		    }
		}
	    else
		{
		/* set window title to "AppName - Untitled" */
		LoadString ((HANDLE)GetModuleHandle (NULL),
			    IDS_UNTITLED,
			    lpszBuff,
			    sizeof (lpszBuff));
		SetWindowTitle (hWnd, lpszBuff);

		/* set global file and path variables to null */
		*lpszFilePath = 0;
		}

        //
        // Use system font if Japanese system,
        //  may want to add other DBCS languages later
        //
        if (PRIMARYLANGID(GetUserDefaultLangID ()) == LANG_JAPANESE) {
          GetObject(GetStockObject(SYSTEM_FIXED_FONT),
                        sizeof(LOGFONT), &lfEditFont);

        } else {
          /* create fixed pitch font as default font */
          lfEditFont.lfHeight = 16;
          lfEditFont.lfWidth = 0;
          lfEditFont.lfEscapement = 0;
          lfEditFont.lfOrientation = 0;
          lfEditFont.lfWeight = 400;
          lfEditFont.lfItalic = FALSE;
          lfEditFont.lfUnderline = FALSE;
          lfEditFont.lfStrikeOut = FALSE;
          lfEditFont.lfCharSet = ANSI_CHARSET;
          lfEditFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
          lfEditFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
          lfEditFont.lfQuality = DEFAULT_QUALITY;
          lfEditFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
          *lfEditFont.lfFaceName = 0;
        }

	    /* make scroll bars initially visible */
	    SetScrollRange (hWndEdit, SB_VERT, 0, 100, TRUE);
	    SetScrollRange (hWndEdit, SB_HORZ, 0, 100, TRUE);

	    /* create the logical font */
	    if (hFont = CreateFontIndirect (&lfEditFont))
		SendMessage (hWndEdit, WM_SETFONT, (UINT)hFont, 0);
	    else
		ErrorNotify (hWnd, IDS_FONTFAILEDTOCREATE);

	    /* remove hourglass cursor */
	    SetClassLong (hWnd, GCL_HCURSOR, (LONG)hOldCursor);
	    SetCursor (hOldCursor);

	    // Is there anything specific we need to do on different platforms?
#if defined (WIN32)
	    if (dwVersion < 0x80000000) {
		// Windows NT
	    } else if (LOBYTE(LOWORD(dwVersion))<4) {
		// Win32s
		// Threads aren't available, so disable background porting:
		EnableMenuItem (GetMenu(hWnd), IDM_PORTBKGND, MF_GRAYED);
	    } else {
		// Windows 95
	    }
#else
		// Win16
#endif

	    /* set focus to edit window */
	    SetFocus (hWndEdit);
	    }
	    break;

	case WM_SIZE:
	    {
	    HWND    hWndEdit;

	    /* resize the edit control to match the client area */
	    hWndEdit = (HWND)GetWindowLong (hWnd, WL_HWNDEDIT);
        InvalidateRect(hWndEdit, (LPRECT)NULL, TRUE);
	    MoveWindow (hWndEdit,
			0,
			0,
			LOWORD(lParam),
			HIWORD(lParam),
			TRUE);
	    }
	    break;

	case WM_SETFOCUS:
	    SetFocus ((HWND)GetWindowLong (hWnd, WL_HWNDEDIT));
	    break;

	case WM_INITMENU:
	    /* initialize menuitems */
	    InitializeMenu (hWnd, (HMENU)uParam);
	    break;

	case WM_WININICHANGE:
	case WM_DEVMODECHANGE:
	    /* get printer configuration */
	    GetPrinterConfig (hWnd);
	    break;

	case WM_COMMAND:
	    /* handle all command messages in a localized function */
	    lRet = CommandHandler (hWnd, uParam, lParam);
	    break;

	case WM_CLOSE:
	case WM_QUERYENDSESSION:
	    {
	    HWND    hWndEdit = (HWND)GetWindowLong (hWnd, WL_HWNDEDIT);

	    /* check if there are changes to the edit contents, and offer to save first */
	    if (SendMessage (hWndEdit, EM_GETMODIFY, 0, 0))
		{
		switch (Save_YNC (hWnd))
		    {
		    case IDCANCEL:
			/* abort exit */
			return FALSE;
		    case IDYES:
			/* save data then continue */
			if (!SendMessage (hWnd, WM_COMMAND, (UINT)UM_SAVEFILE, 0))
			    return FALSE;
		    case IDNO:
			/* just fall through */
			break;
		    }
		}

	    /* call destroy window to cleanup and go away */
	    DestroyWindow (hWnd);
	    }
	    break;

	case WM_DESTROY:
	    {
	    HFONT    hFont = (HFONT)SendMessage ((HWND)GetWindowLong (hWnd, WL_HWNDEDIT),
						 WM_GETFONT,
						 0,
						 0);

	    /* destroy font handle from edit control if exists */
	    if (hFont)
		DeleteObject (hFont);

	    PostQuitMessage (0);
	    }
	    break;

	default:
	    /* process common dialog search message here, then break */
	    if (uMsg == uSearchMsg)
		{
		LPFINDREPLACE    lpfr = (LPFINDREPLACE)lParam;

		if (lpfr->Flags & FR_DIALOGTERM)
		    {
		    /* save case and direction */
		    SetWindowWord (hWnd, WW_SEARCHCASE, (WORD)(lpfr->Flags & FR_MATCHCASE));
		    SetWindowWord (hWnd, WW_SEARCHDN, (WORD)(lpfr->Flags & FR_DOWN));
		    hDlgSearch = NULL;
		    }

		else if (lpfr->Flags & FR_FINDNEXT)
		    if (!LocateText (hWnd,
				     (WORD)(lpfr->Flags & FR_MATCHCASE),
				     (WORD)(lpfr->Flags & FR_DOWN),
				     lpszSearch))
			ErrorNotify (hWnd, IDS_STRINGNOTFOUND);
		break;
		}

	    /* pass all unhandled messages to DefWindowProc */
	    lRet = DefWindowProc (hWnd, uMsg, uParam, lParam);
	    break;
	}

    /* return 1 if handled message, 0 if not */
    return lRet;
}


/* about box dialog procedure */
BOOL WINAPI AboutDlgProc (
    HWND    hwnd,
    UINT    uMsg,
    UINT    uParam,
    LONG    lParam)
{
    BOOL    bRet = TRUE;
    static  HFONT hfontDlg;
    char szVersion[80];

    switch (uMsg)
	{
	case WM_INITDIALOG:  // message: initialize dialog box

	    // Create a font to use
	    hfontDlg = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_SWISS, "");

	    SendMessage (GetDlgItem (hwnd, IDC_SYSTEM), WM_SETFONT, (UINT)hfontDlg, TRUE);
	    SendMessage (GetDlgItem (hwnd, IDC_APP), WM_SETFONT, (UINT)hfontDlg, TRUE);
	    SendMessage (GetDlgItem (hwnd, IDC_VERSION), WM_SETFONT, (UINT)hfontDlg, TRUE);
	    SendMessage (GetDlgItem (hwnd, IDC_COPYRIGHT), WM_SETFONT, (UINT)hfontDlg, TRUE);
	    //SendMessage (GetDlgItem (hwnd, IDC_OSVERSION), WM_SETFONT, (UINT)hfontDlg, TRUE);


	    //dwVersion = GetVersion();
#if defined (WIN32)
	    if (dwVersion < 0x80000000) {
		// Windows NT
		wsprintf (szVersion, "Microsoft WindowsNT %u.%u (Build: %u)",
		    (DWORD)(LOBYTE(LOWORD(dwVersion))),
		    (DWORD)(HIBYTE(LOWORD(dwVersion))),
		    (DWORD)(HIWORD(dwVersion)));
	    } else if (LOBYTE(LOWORD(dwVersion))<4) {
		// Win32s
		wsprintf (szVersion, "Microsoft Win32s %u.%u (Build: %u)",
		    (DWORD)(LOBYTE(LOWORD(dwVersion))),
		    (DWORD)(HIBYTE(LOWORD(dwVersion))),
		    (DWORD)(HIWORD(dwVersion) & ~0x8000));
	    } else {
		// Windows 95
		wsprintf (szVersion, "Microsoft Windows 95 %u.%u",
		    (DWORD)(LOBYTE(LOWORD(dwVersion))),
		    (DWORD)(HIBYTE(LOWORD(dwVersion))));
	    }

#else
	    wsprintf (szVersion, " Windows %u.%u - DOS %u.%u",
		(DWORD)(LOBYTE(LOWORD(dwVersion))),
		(DWORD)(HIBYTE(LOWORD(dwVersion))),
		(DWORD)(HIBYTE(HIWORD(dwVersion))),
		(DWORD)(LOBYTE(HIWORD(dwVersion))));

	  
#endif
	    SetWindowText (GetDlgItem(hwnd, IDC_OSVERSION), szVersion);


	    return (TRUE);

	case WM_COMMAND:
	    switch (LOWORD (uParam))
		{
		/* end dialog with TRUE or FALSE for OK or CANCEL */
		case IDOK:
		case IDCANCEL:
		    EndDialog(hwnd, (LOWORD (uParam) == IDOK));
		    break;

		default:
		    bRet = FALSE;
		}
	    break;

	default:
	    bRet =  FALSE;
	    break;
	}
    return bRet;
}



/* initialize menu function */
VOID WINAPI InitializeMenu (
    HWND    hWnd,
    HANDLE  hMenu)
{
    WORD    mfStatus;
    DWORD   dwSel;
    HWND    hWndEdit = (HWND)GetWindowLong (hWnd, WL_HWNDEDIT);
    WORD    wScroll;

    /* see if edit control can undo last command */
    if (SendMessage (hWndEdit, EM_CANUNDO, 0, 0L))
	mfStatus = MF_ENABLED;
    else
	mfStatus = MF_GRAYED;
    EnableMenuItem (hMenu, IDM_EDITUNDO, mfStatus);

    /* enable menuitems CUT, COPY and CLEAR if selected text */
    dwSel = SendMessage (hWndEdit, EM_GETSEL, 0, 0);
    mfStatus = (WORD)((LOWORD(dwSel) == HIWORD(dwSel))?MF_GRAYED:MF_ENABLED);
    EnableMenuItem (hMenu, IDM_EDITCUT, mfStatus);
    EnableMenuItem (hMenu, IDM_EDITCOPY, mfStatus);
    EnableMenuItem (hMenu, IDM_EDITCLEAR, mfStatus);

    /* if text allow for new file, enable menuitem */
    if (SendMessage (hWndEdit, WM_GETTEXTLENGTH, 0, 0))
	EnableMenuItem (hMenu, IDM_FILENEW, MF_ENABLED);
    else
	EnableMenuItem (hMenu, IDM_FILENEW, MF_GRAYED);

    /* if CF_TEXT format data is available in clipboard */
    if (OpenClipboard (hWnd) & IsClipboardFormatAvailable (CF_TEXT))
	EnableMenuItem (hMenu, IDM_EDITPASTE, MF_ENABLED);
    else
	EnableMenuItem (hMenu, IDM_EDITPASTE, MF_GRAYED);
    CloseClipboard ();

    /* set the scroll bars menuitem */
    wScroll = GetWindowWord (hWnd, WW_SCROLL);
    CheckMenuItem (hMenu, IDM_EDITSCROLL, (UINT)(wScroll ? MF_CHECKED : MF_UNCHECKED));

    /* set the word wrap state for the window */
    dwSel = GetWindowLong (hWndEdit, GWL_STYLE);
    CheckMenuItem (hMenu,
		   IDM_EDITWRAP,
		   (UINT)((dwSel & ES_AUTOHSCROLL) ? MF_UNCHECKED : MF_CHECKED));

    /* enable search menuitems if a search string exists */
    if (*lpszSearch)
	{
	EnableMenuItem (hMenu, IDM_SEARCHNEXT, MF_ENABLED);
	EnableMenuItem (hMenu, IDM_SEARCHPREV, MF_ENABLED);
	}
    else
	{
	EnableMenuItem (hMenu, IDM_SEARCHNEXT, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_SEARCHPREV, MF_GRAYED);
	}

    /* enable Print menuitems if a printer is available */
    if (GetWindowLong (hWnd, WL_HPTRDEVNAMES))
	{
	EnableMenuItem (hMenu, IDM_FILEPRINT, MF_ENABLED);
	EnableMenuItem ( hMenu, IDM_FILESETUP, MF_ENABLED);
	}
    else
	{
	EnableMenuItem (hMenu, IDM_FILEPRINT, MF_GRAYED);
	EnableMenuItem ( hMenu, IDM_FILESETUP, MF_GRAYED);
	}

    /* menuitems that are always enabled */
    EnableMenuItem(hMenu, IDM_EDITSCROLL, MF_ENABLED);
    EnableMenuItem(hMenu, IDM_EDITSELECT, MF_ENABLED);
    EnableMenuItem(hMenu, IDM_EDITWRAP, MF_ENABLED);
    EnableMenuItem(hMenu, IDM_SEARCHFIND, MF_ENABLED);
}



/* handle all WM_COMMAND messages here */
LONG WINAPI CommandHandler (
    HWND    hWnd,
    UINT    uParam,
    LONG    lParam)
{
    int     nResult;
    HWND    hWndEdit = (HWND)GetWindowLong (hWnd, WL_HWNDEDIT);

    switch (LOWORD(uParam))
	{
	case IDM_FILENEW:
	    {
	    char    lpszMsg[MAX_PATH];

	    /* check if there are changes, and offer to save first */
	    if (SendMessage (hWndEdit, EM_GETMODIFY, 0, 0))
		{
		switch (Save_YNC (hWnd))
		    {
		    case IDCANCEL:
			/* abort operation */
			return FALSE;
		    case IDYES:
			/* save data then continue if successful */
			if (!SendMessage (hWnd, WM_COMMAND, (UINT)UM_SAVEFILE, 0))
			    return FALSE;
		    case IDNO:
			/* just fall through */
			break;
		    }

		/* reset edit changes flag */
		SendMessage (hWndEdit, EM_SETMODIFY, FALSE, 0);
		}

	    /* clear edit control */
	    SetWindowText (hWndEdit, "");

	    /* set window title to "Untitled" */
	    LoadString ((HANDLE)GetModuleHandle (NULL),
			IDS_UNTITLED,
			lpszMsg,
			sizeof (lpszMsg));
	    SetWindowTitle (hWnd, lpszMsg);
	    SetWindowWord (hWnd, WW_UNTITLED, TRUE);

	    /* reset caret position by sending WM_KILLFOCUS/WM_SETFOCUS messages */
	    SetFocus (NULL);
	    SetFocus (hWndEdit);
	    }
	    break;

	case IDM_FILEOPEN:
	    {
	    char    lpszFileName[MAX_PATH];
	    int     nResult;

	    /* if changes to current file, ask to save first */
	    if (SendMessage (hWndEdit, EM_GETMODIFY, 0, 0))
		{
		switch (Save_YNC (hWnd))
		    {
		    case IDCANCEL:
			/* abort operation */
			return FALSE;
		    case IDYES:
			/* save data then continue */
			if (!SendMessage (hWnd, WM_COMMAND, (UINT)UM_SAVEFILE, 0))
			    return FALSE;
		    case IDNO:
			/* just fall through */
			break;
		    }

		/* reset edit changes flag */
		SendMessage (hWndEdit, EM_SETMODIFY, FALSE, 0);
		}

	    /* get new filename and load into edit control */
	    if (GetFileName (hWnd, lpszFileName, lpszFilePath))
		{
		if ((nResult = LoadFile (hWnd, lpszFilePath)) < 0)
		    /* notify user of error */
			ErrorNotify (hWnd, 0-nResult);
		else
		    {
		    /* update window text */
		    SetWindowTitle (hWnd, lpszFileName);
		    SetWindowWord (hWnd, WW_UNTITLED, FALSE);
		    }
		}
	    else
		return FALSE;
	    }
	    break;

	case IDM_FILESAVEAS:
	    {
	    char    lpszFileTitle[MAX_PATH];
	    int     nResult;

	    /* get a valid filename and path */
	    if (SaveAsFileName (hWnd, lpszFileTitle, lpszFilePath))
		{
		/* if file saves okay */
		if ((nResult = SaveFile (hWnd, lpszFilePath)) > 0)
		    {
		    /* reset changed flag, and window title */
		    SendMessage (hWndEdit, EM_SETMODIFY, FALSE, 0);
		    SetWindowTitle (hWnd, lpszFileTitle);
		    SetWindowWord (hWnd, WW_UNTITLED, FALSE);
		    }
		else
		    {
		    /* unable to save file, return error */
		    ErrorNotify (hWnd, nResult);
		    return FALSE;
		    }
		}
	    else
		return FALSE;
	    }
	    break;

	case IDM_FILESAVE:
	    {
	    char    lpszFileTitle[MAX_PATH];
	    int     nResult;

        /* if called from menu, check to see if file modified */
        if (!lParam && !SendMessage (hWndEdit, EM_GETMODIFY, 0, 0))
          return FALSE;

	/* user defined msg is sent from Exit, Open and New menuitems */
	case UM_SAVEFILE:

	    /* if untitled, get new name */
	    if (GetWindowWord (hWnd, WW_UNTITLED) &&
		!(SaveAsFileName(hWnd, lpszFileTitle, lpszFilePath)))
		{
		/* make sure no name was saved */
		*lpszFilePath = 0;
		return FALSE;
		}

        /* save buffer and reset flag */
        if ((nResult = SaveFile (hWnd, lpszFilePath)) > 0)
        {
        // get lpszFileTitle
        char szDrive[_MAX_DRIVE], szDir[_MAX_DIR], szExt[_MAX_EXT];
        _splitpath(lpszFilePath,szDrive,szDir,lpszFileTitle,szExt);
        lstrcat(lpszFileTitle,szExt);

        /* if new file name, set window title */
        if (*lpszFileTitle)
            {
            SetWindowTitle (hWnd, lpszFileTitle);
            SetWindowWord (hWnd, WW_UNTITLED, FALSE);
            }
        SendMessage (hWndEdit, EM_SETMODIFY, FALSE, 0);
        }
        else
        {
        /* unable to save file, return error */
        ErrorNotify (hWnd, nResult);
        return FALSE;
        }
        }
        break;

	case IDM_FILEPRINT:
	    {
	    int    nRes;

	    /* print the file */
	    if ((nRes = PrintFile (hWnd)) < 0)
		ErrorNotify (hWnd, nRes);
	    }
	    break;

	case IDM_FILESETUP:
	    {
	    int    nRes;

	    /* set up the printer environment */
	    if ((nRes = PrinterSetup (hWnd)) < 0)
		ErrorNotify (hWnd, nRes);
	    }
	    break;

	case IDM_FILEEXIT:
	    /* exit application */
	    PostMessage (hWnd, WM_CLOSE, 0, 0L);
	    break;

	case IDM_FILEABOUT:
	    /* call about dialog box */
	    DialogBox ((HANDLE)GetModuleHandle (NULL),
		       (LPSTR)IDD_ABOUT,
		       hWnd,
		       AboutDlgProc);
	    break;

	case IDM_EDITUNDO:
	    SendMessage (hWndEdit, EM_UNDO, 0, 0);
	    break;

	case IDM_EDITCUT:
        SendMessage (hWndEdit, WM_CUT, 0, 0);
        break;

	case IDM_EDITCOPY:
        SendMessage (hWndEdit, WM_COPY, 0, 0);
        break;

	case IDM_EDITCLEAR:
        SendMessage (hWndEdit, WM_CLEAR, 0, 0);
        break;

	case IDM_EDITPASTE:
        SendMessage (hWndEdit, WM_PASTE, 0, 0L);
        break;

	case IDM_EDITSELECT:
	    /* 0, -1 selects the entire string */
	    SendMessage (hWndEdit, EM_SETSEL, 0, (LONG)(int)-1);
	    break;

	case IDM_EDITSCROLL:
	    {
	    WORD    wScroll = !GetWindowWord (hWnd, WW_SCROLL);

	    /* toggle vertical scroll bar */
	    SetScrollRange (hWndEdit, SB_VERT, 0, (int)(wScroll ? 100 : 0), TRUE);

	    /* if not word wrap, toggle horizontal scroll */
	    if (ES_AUTOHSCROLL & GetWindowLong (hWndEdit, GWL_STYLE))
		SetScrollRange (hWndEdit, SB_HORZ, 0, (int)(wScroll ? 100 : 0), TRUE);

	    /* set scroll flag */
	    SetWindowWord (hWnd, WW_SCROLL, wScroll);
	    }
	    break;

	case IDM_EDITWRAP:
	    /* change edit control */
	    if ((nResult = SetWrap (hWnd)) < 0)
		/* notify user of error */
		ErrorNotify (hWnd, nResult);
	    break;

	case IDM_EDITFONT:
	    {
	    CHOOSEFONT    cf;
	    LOGFONT       lfEditFont;
	    HFONT         hEditFont;

	    /* get logical font structure from current font */
	    if (hEditFont = (HFONT)SendMessage (hWndEdit, WM_GETFONT, 0, 0))
		{
		GetObject (hEditFont, sizeof (lfEditFont), &lfEditFont);
		cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
		}
	    else
		cf.Flags = CF_SCREENFONTS;

        /* call common dialog to select a font */
        cf.lStructSize    = sizeof (CHOOSEFONT);
        cf.hwndOwner      = hWnd;
        cf.hDC            = NULL;
        cf.lpLogFont      = &lfEditFont;
        cf.iPointSize     = 0;
        cf.rgbColors      = 0;
        cf.lCustData      = 0;

        //
        // On Japanese system set font filter proc,
        //  may want to add other DBCS languages later
        //
        if (PRIMARYLANGID(GetUserDefaultLangID ()) == LANG_JAPANESE) {
          cf.lpfnHook = (LPCFHOOKPROC)MakeProcInstance(ChooseFontHookProc, NULL);
          cf.Flags |= CF_ENABLEHOOK;
        } else {
          cf.lpfnHook       = NULL;
        }

        cf.lpTemplateName = NULL;
        cf.hInstance      = NULL;
        cf.lpszStyle      = NULL;
        cf.nFontType      = SCREEN_FONTTYPE;
        cf.nSizeMin       = 0;
        cf.nSizeMax       = 0;

	    if (ChooseFont (&cf))
		{
		/* create new font and put in edit control */
		SendMessage (hWndEdit,
			     WM_SETFONT,
			     (UINT)CreateFontIndirect
			     (&lfEditFont),
			     TRUE);

		if (hEditFont)
		    DeleteObject (hEditFont);
		}
	    }
	    break;

	case IDM_SEARCHFIND:
	    {
	    UINT    uBegSel, uEndSel;
	    WORD    wCase = GetWindowWord (hWnd, WW_SEARCHCASE);
	    WORD    wDir = GetWindowWord (hWnd, WW_SEARCHDN);

	    /* if selected text, replace global search string */
	    SendMessage (hWndEdit, EM_GETSEL, (UINT)&uBegSel, (UINT)&uEndSel);
	    if (uBegSel != uEndSel)
		GetEditSubString (hWndEdit, &uBegSel, &uEndSel, lpszSearch);

	    /* Put up the find dialog box */
	    if (!FindDialog (hWnd, wCase, wDir, lpszSearch))
		ErrorNotify (hWnd, IDS_SEARCHDLGFAILED);
	    }
	    break;

	case IDM_SEARCHNEXT:
	    /* locate next search string in edit control */
	    if (!LocateText (hWnd,
			     GetWindowWord (hWnd, WW_SEARCHCASE),
			     TRUE,
			     lpszSearch))
		ErrorNotify (hWnd, IDS_STRINGNOTFOUND);
	    break;

	case IDM_SEARCHPREV:
	    /* locate previous search string in edit control */
	    if (!LocateText (hWnd,
			     GetWindowWord (hWnd, WW_SEARCHCASE),
			     FALSE,
			     lpszSearch))
		ErrorNotify (hWnd, IDS_STRINGNOTFOUND);
	    break;

	case IDM_PORTCURFILE:
	    /* if untitled, save first */
	    if (GetWindowWord (hWnd, WW_UNTITLED) &&
		!SendMessage (hWnd, WM_COMMAND, IDM_FILEOPEN, 0))
		{
		ErrorNotify (hWnd, IDS_NOFILETOPORT);
		break;
		}

	    /* start port dialog with flags */
	    hDlgPort = CreateDialog (GetModuleHandle (NULL),
				     IDD_PORTDIALOG,
				     hWnd,
				     PortDlgProc);
	    break;

	case IDM_PORTBKGND:
	    if (IsWindow (hDlgPortStatus))
		ShowWindow (hDlgPortStatus, SW_SHOWNORMAL);
	    else if (!(hDlgPortStatus = StartBackground (GetModuleHandle (NULL),
							 hWnd,
							 NULL)))
		ErrorNotify (hWnd, IDS_BKPORTSTARTFAILED);
	    break;

    default:
        return FALSE;
	}
    return TRUE;
}



/* change the word wrapping in an edit control */
int WINAPI SetWrap (
    HWND    hWnd)

{
    DWORD   dwStyle;
	HANDLE	hNewData;
	char	*lpNewData;
    HWND    hWndOld = (HWND)GetWindowLong (hWnd, WL_HWNDEDIT);
    HWND    hWndNew;
    RECT    rc;
    UINT    uLen;
    UINT    uBegSel, uEndSel;
    WORD    wScroll = GetWindowWord (hWnd, WW_SCROLL);
	HFONT	hEditFont = (HFONT)SendMessage (hWndOld, WM_GETFONT, 0, 0);

#ifndef WIN32
	HANDLE	hOldData;
	char	*lpOldData;
#endif

    char sz[40]; // temporary string for error messages


    /* turn off scroll bars if currently present */
    if (wScroll)
	{
	SetScrollRange (hWndOld, SB_VERT, 0, 0, FALSE);
	SetScrollRange (hWndOld, SB_HORZ, 0, 0, FALSE);
	}

    /* new edit style = old style XOR ES_AUTOHSCROLL */
    dwStyle = ES_AUTOHSCROLL ^ (DWORD)GetWindowLong (hWndOld, GWL_STYLE);

    /* save text selection */
    SendMessage (hWndOld, EM_GETSEL, (UINT)&uBegSel, (UINT)&uEndSel);

    /* create a new edit control with the new style */
    GetClientRect (hWnd, &rc);
    hWndNew = CreateWindow ("edit",
			    "",
			    dwStyle,
			    rc.left,
			    rc.top,
			    rc.right-rc.left,
			    rc.bottom-rc.top,
			    hWnd,
			    (HMENU)IDC_EDIT,
			    (HANDLE)GetModuleHandle (NULL),
			    0);

    /* check for window created */
    if (!IsWindow (hWndNew))
	return IDS_EDITWNDFAILED;

    /* reset to no format lines */
    if (dwStyle & ES_AUTOHSCROLL)
        SendMessage (hWndOld, EM_FMTLINES, FALSE, 0);

#if defined (WIN32)
    uLen = GetWindowTextLength (hWndOld);

    hNewData = LocalAlloc (LHND, uLen+1);
    if (hNewData == NULL) {
	wsprintf (sz, "Unable to allocate %u bytes", uLen+1);
	MessageBox (GetFocus, sz, "PORTTOOL::SetWrap", MB_OK);
	DestroyWindow(hWndNew);
	return IDS_GETHANDLEFAILED;
    }

    lpNewData = LocalLock (hNewData);
    if (lpNewData == NULL) {
	MessageBox (GetFocus, "Unable to lock memory", "PORTTOOL::SetWrap", MB_OK);
	DestroyWindow(hWndNew);
	LocalFree (hNewData);
	return IDS_GETHANDLEFAILED;
    }

    GetWindowText (hWndOld, lpNewData, uLen+1);
    SetWindowText (hWndNew, lpNewData);
    LocalUnlock (hNewData);

#else
    /* get the data handle of the old control */
    if (!(hOldData = (HANDLE)SendMessage (hWndOld, EM_GETHANDLE, 0, 0)))
	{
	/* delete new edit window and return error */
	DestroyWindow (hWndNew);
	return IDS_GETHANDLEFAILED;
	}

    /* increase edit control max character limit beyond 30,000 default */
    SendMessage (hWndNew, EM_LIMITTEXT, 0x0FFFFFFF, 0);

    /* get data handle to new edit control and reallocate to size of old edit text */
    hNewData = (HANDLE)SendMessage (hWndNew, EM_GETHANDLE, 0, 0);
    uLen = GetWindowTextLength (hWndOld);
    if (LocalReAlloc(hNewData, uLen+1, LHND) == NULL)
	{
	/* abort, clean up and return error */
	DestroyWindow (hWndNew);
	return IDS_REALLOCFAILED;
	}

    lpOldData = LocalLock (hOldData);
    lpNewData = LocalLock (hNewData);
    lpNewData[uLen+1] = 0;

    /* copy from one buffer to the other */
    while (uLen-- > 0)
	lpNewData[uLen] = lpOldData[uLen];

    /* unlock and release data buffers */
    LocalUnlock (hOldData);
    LocalUnlock (hNewData);

#endif

    /* swap windows */
    SetWindowLong (hWnd, WL_HWNDEDIT, (LONG)hWndNew);
    DestroyWindow (hWndOld);

#if !defined(WIN32)
    SendMessage (hWndNew, EM_SETHANDLE, (UINT)hNewData, 0);
#endif

    /* set line formatting */
    if (dwStyle & ES_AUTOHSCROLL)
        SendMessage (hWndNew, EM_FMTLINES, FALSE, 0);

    /* replace font in new edit control */
    if (hEditFont)
	SendMessage (hWndNew, WM_SETFONT, (UINT)hEditFont, 0);

    /* set scroll bars if appropriate */
    if (wScroll)
	{
	SetScrollRange (hWndNew, SB_VERT, 0, 100, TRUE);
	SetScrollRange (hWndNew, SB_HORZ, 0, (ES_AUTOHSCROLL & dwStyle ? 100 : 0), TRUE);
	}

    /* Set limit to greater than 30K */
    SendMessage (hWndNew, EM_LIMITTEXT, 0x0FFFFFFF, 0);

    /* restore text selection, repaint and set focus */
    InvalidateRect (hWndNew, NULL, TRUE);
    UpdateWindow (hWndNew);
    SendMessage (hWndNew, EM_SETSEL, uBegSel, uEndSel);
    SetFocus (hWndNew);

#if defined(WIN32)
    LocalFree (hNewData);
#endif

    /* return success */
    return TRUE;
}



/* get win32 command line parameters */
BOOL WINAPI GetCmdLine(
    char    *lpStr,
    char    *lpszCmdLine,
	BOOL	*bBkgnd,
	char	*lpszPortFileName)
{
    if (*lpStr)
    {
    /* skip application name which precedes parameters */
    while (*lpStr != ' ' && *lpStr != 0)
        lpStr = CharNext(lpStr);;

	/* skip spaces */
	while (*lpStr == ' ' && *lpStr != 0)
	    lpStr++;

	/* indeed command line parameter(s) present */
	if (*lpStr != 0)
	    {
	    /* if background switch, set flag and remove switch from command line */
	    if ((*lpStr == '/' || *lpStr == '-') &&
		(*(lpStr+1) == 'b' || *(lpStr+1) == 'B'))
		{
		*bBkgnd = TRUE;
		lpStr += 2;

		if (*lpStr == 0)
		    *lpszCmdLine = 0;
		else
		    strcpy (lpszCmdLine, lpStr);
		}
	    /* maybe switch is embedded in parameter(s) somewhere */
	    else
		{
		char    *pStr = lpStr;
		char	*pCmdLine  = lpszCmdLine;
		char	*pPortFile = lpszPortFileName;
		int     i, nCnt;

		while (*pStr != 0)
		    {
		    /* background switch is set, so prepare parameters and set flag */
		    if ((*pStr == '/' || *pStr == '-') &&
			(*(pStr+1) == 'b' || *(pStr+1) == 'B'))
			{
			*bBkgnd = TRUE;

			/* copy from beg. of lpStr to *pStr to lpszCmdLine */
			nCnt = pStr - lpStr;
			for (i=0; i<nCnt; i++)
			    lpszCmdLine[i] = lpStr[i];
			lpszCmdLine[i] = 0;
			strcat (lpszCmdLine, (pStr+2));

			/* break from loop */
			break;
			}
			else if ((*pStr == '/' || *pStr == '-') &&
			(*(pStr+1) == 'i' || *(pStr+1) == 'I'))
			{
			  pStr = lpStr;

			  while (*pStr != ' ' && *pStr != 0)
			  {
				pStr++;
				lpStr++;
			  }

			  while (*pStr == ' ' && *pStr != 0)
			  {
				pStr++;
				lpStr++;
			  }

			  while (*pStr != ' ' && *pStr != 0)
			  {
				*pPortFile = *pStr;
				pPortFile++;
				pStr++;
				lpStr++;
			  }
			  *pPortFile = 0;
			}

		    pStr++;
		    }

		/* no switch found, can only edit one file, remove extra parameters */
		if (*pStr == 0)
		    {
		    pStr = lpStr;

		    while (*pStr != ' ' && *pStr != 0)
			pStr++;

		    if (*pStr == ' ')
			*pStr = 0;

		    strcpy (lpszCmdLine, lpStr);
		    }
		}
	    }
	else
	    return FALSE;
	}
    else
	return FALSE;

    return TRUE;
}



/* display a Save, Yes|No|Cancel message box */
int WINAPI Save_YNC (
    HWND    hWnd)
{
    char    lpszMsg[MAX_PATH];
    char    lpszAppName[MAX_PATH];

    /* load string to prompt user */
    LoadString ((HANDLE)GetModuleHandle (NULL),
		IDS_DATACHANGED,
		lpszMsg,
		sizeof (lpszMsg));
    LoadString ((HANDLE)GetModuleHandle (NULL),
		IDS_APPNAME,
		lpszAppName,
		sizeof (lpszAppName));

    /* return user response */
    return (MessageBox (hWnd,
			lpszMsg,
			lpszAppName,
			MB_YESNOCANCEL | MB_ICONQUESTION));
}



/* error notification routine */
VOID WINAPI ErrorNotify (
    HWND    hWnd,
    int     nErrorString)
{
    char    lpszAppName[MAX_PATH];
    char    lpszErrStr[MAX_PATH];
    char    szNum[10];

    LoadString ((HANDLE)GetModuleHandle (NULL),
		IDS_APPNAME,
		lpszAppName,
		sizeof (lpszAppName));
    if (!LoadString ((HANDLE)GetModuleHandle (NULL),
             nErrorString,
             lpszErrStr,
             sizeof (lpszErrStr)))
    {
    LoadString((HANDLE)GetModuleHandle(NULL),
          IDS_UNKNOWN_ERROR,
          lpszErrStr,
          sizeof (lpszErrStr));
    strcat (lpszErrStr, itoa (nErrorString, szNum, 10));
    }

    MessageBox (NULL, lpszErrStr, lpszAppName, MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
}



VOID WINAPI SetWindowTitle (
    HWND    hWnd,
    char    *lpszFile)
{
    char    lpszAppName[MAX_PATH];

    if (LOBYTE(LOWORD(dwVersion))>=4) {
	// On Windows 95, only put up the filename
	SetWindowText (hWnd, lpszFile);
    } else {
	/* load AppName and Window title string into window text */
	LoadString ((HANDLE)GetModuleHandle (NULL),
	    IDS_PRINTJOB,
	    lpszAppName,
	    sizeof (lpszAppName));
	strcat (lpszAppName, lpszFile);
	SetWindowText (hWnd, lpszAppName);
    }
}



/* extract a substring from the edit controls data buffer */
VOID WINAPI GetEditSubString (
    HWND    hWndEdit,
    PUINT   puStart,
    PUINT   puEnd,
    char    *lpszString)
{
    HANDLE    hEditData;
    char      *lpEditData;
    UINT      i;

    char sz[40]; // temporary string for error reporting

    /* maximum search string length is MAXSEARCHSTRING characters */
    if ((*puEnd - *puStart) > MAXSEARCHSTRING)
	*puEnd = *puStart + MAXSEARCHSTRING;

#if defined(WIN32)

    i = GetWindowTextLength(hWndEdit);
    hEditData = LocalAlloc (LHND, i+1);
    if (hEditData == NULL) {
	wsprintf (sz, "Unable to allocate %u bytes", i+1);
	MessageBox (GetFocus, sz, "PORTTOOL::GetEditSubString", MB_OK);
    }

    lpEditData = LocalLock (hEditData);
    if (lpEditData == NULL) {
	MessageBox (GetFocus, "Unable to lock memory", "PORTTOOL::GetEditSubString", MB_OK);
    } else {
	GetWindowText (hWndEdit, lpEditData, i+1);
    }

#else

    /* get edit data handle and lock */
    hEditData = (HANDLE)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0);
    lpEditData = (char *)LocalLock (hEditData);

#endif

    if (lpEditData != NULL) {
	/* copy characters to string and terminate */
	for (i=*puStart; i<*puEnd; i++)
	    lpszString[i-*puStart] = lpEditData[i];
	lpszString[i-*puStart] = 0;
    }

    /* unlock and return edit handle */
    LocalUnlock (hEditData);

#if defined(WIN32)

    LocalFree (hEditData);

#endif

}


/****************************************************************************
    My_mbschr:  strchr() DBCS version
****************************************************************************/
unsigned char * _CRTAPI1 My_mbschr(
    unsigned char *psz, unsigned short uiSep)
{
    while (*psz != '\0' && *psz != uiSep) {
        psz = CharNext(psz);
    }
    if (*psz == '\0' && uiSep != '\0') {
        return NULL;
    } else {
        return psz;
    }
}
/****************************************************************************
    My_mbstok:  strtok() DBCS version
****************************************************************************/
unsigned char * _CRTAPI1 My_mbstok(
    unsigned char *pszSrc, unsigned char *pszSep)
{
    static char *pszSave = NULL;
    char *pszHead;
    char *psz;

    if (pszSrc == NULL) {
        if (pszSave == NULL) {
            return NULL;
        } else {
            psz = pszSave;
        }
    } else {
        psz = pszSrc;
    }

    /*********************************************/
    /* Skip delimiters to find a head of a token */
    /*********************************************/
    while (*psz) {
        if (IsDBCSLeadByte(*psz)) {
            break;
        } else if (NULL == My_mbschr(pszSep, *psz)) {
            break;
        }
        psz++;
    }
    if (*psz == '\0') {
        //No more token
        return (pszSave = NULL);
    }
    pszHead = psz;

    /******************************/
    /* Search a Tail of the token */
    /******************************/
    while (*psz) {
        if (IsDBCSLeadByte(*psz)) {
            psz += 2;
            continue;
        } else if (NULL != My_mbschr(pszSep, *psz)) {
            break;
        }
        psz++;
    }
    if (*psz == '\0') {
        pszSave = NULL;
    } else {
        //Found next delimiter
        pszSave = psz + 1;
        *psz = '\0';
    }
    return pszHead;
}
/****************************************************************************
    My_mbsncpy:
****************************************************************************/
unsigned char * _CRTAPI1 My_mbsncpy(
    unsigned char *psz1, const unsigned char *psz2, size_t nLength)
{
    int nLen = (int)nLength;
    unsigned char *pszSv = psz1;

    while (0 < nLen) {
        if (*psz2 == '\0') {
            *psz1++ = '\0';
            nLen--;
        } else if (IsDBCSLeadByte(*psz2)) {
            if (nLen == 1) {
                *psz1 = '\0';
            } else {
                *psz1++ = *psz2++;
                *psz1++ = *psz2++;
            }
            nLen -= 2;
        } else {
            *psz1++ = *psz2++;
            nLen--;
        }
    }
    return pszSv;
}
