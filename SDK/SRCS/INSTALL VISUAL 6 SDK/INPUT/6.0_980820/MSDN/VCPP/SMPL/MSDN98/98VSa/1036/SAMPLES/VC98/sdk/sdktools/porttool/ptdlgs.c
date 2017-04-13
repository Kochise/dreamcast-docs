#include "porttool.h"
#include "port.h"

int DLGOFFSET = 100;

RESULT	rIssue;

HANDLE    hBkFileHeap;
extern HWND    hDlgPort;
extern HWND    hDlgPortStatus;


/* function prototypes for helper functions */
void WINAPI GrowDialog (HWND, BOOL);
BOOL WINAPI GetHelpFileName (char *);
BOOL WINAPI BuildFileList (char *, LPBKFILELIST *);
BOOL WINAPI AddFile (char *, char *, BKFILELIST *);
BOOL WINAPI RemoveFile (char *, LPBKFILELIST *);
BOOL WINAPI FreeFileList (BKFILELIST *);

BOOL MySetEvent (HWND hWnd, HANDLE hEvent);
BOOL MyResetEvent (HWND hWnd, HANDLE hEvent);

/* port options dialog */
BOOL WINAPI OptionsDlgProc (
    HWND    hDlg,
    UINT    uMsg,
    UINT    uParam,
    LONG    lParam)
{
	BOOL       bRet = TRUE;
static  DWORD      *dwPTFlags;
static  HFONT      hStrikeoutFont;
static  HFONT      hSystemFont;
	LOGFONT    lf;

    switch (uMsg)
	{
	case WM_INITDIALOG:
	    /* create strikeout font for ignored tokens */
	    hSystemFont = GetStockObject (SYSTEM_FONT);
	    GetObject (hSystemFont, sizeof (LOGFONT), &lf);
	    lf.lfStrikeOut = TRUE;
	    hStrikeoutFont = CreateFontIndirect (&lf);

	    /* initialize token control with stock system font */
	    SendMessage (GetDlgItem (hDlg, IDC_CURTOKEN),
			 WM_SETFONT,
			 (UINT)hSystemFont,
			 FALSE);

	    /* save dwPTFlags from lParam */
	    dwPTFlags = (DWORD *)lParam;

	    /* initialize current token if any */
	    if (*(WORD *)rIssue.lpszToken != MAXTOKENLEN)
		SetDlgItemText (hDlg, IDC_CURTOKEN, rIssue.lpszToken);
	    else
		EnableWindow (GetDlgItem (hDlg, IDC_IGNORETOKEN), FALSE);

	    /* initialize search flag check boxes */
	    CheckDlgButton (hDlg, IDC_NOAPIS, (*dwPTFlags & PT_NOAPIS));
	    CheckDlgButton (hDlg, IDC_NOMESSAGES, (*dwPTFlags & PT_NOMESSAGES));
	    CheckDlgButton (hDlg, IDC_NOSTRUCTURES, (*dwPTFlags & PT_NOSTRUCTURES));
	    CheckDlgButton (hDlg, IDC_NOMACROS, (*dwPTFlags & PT_NOMACROS));
	    CheckDlgButton (hDlg, IDC_NOCONSTANTS, (*dwPTFlags & PT_NOCONSTANTS));
	    CheckDlgButton (hDlg, IDC_NOTYPES, (*dwPTFlags & PT_NOTYPES));
	    CheckDlgButton (hDlg, IDC_NOCUSTOM, (*dwPTFlags & PT_NOCUSTOM));
	    CheckDlgButton (hDlg, IDC_IGNORECASE, (*dwPTFlags & PT_IGNORECASE));

	    /* set focus to first check box, return FALSE */
	    SetFocus (GetDlgItem (hDlg, IDC_NOAPIS));
	    bRet = FALSE;
	    break;

	case WM_COMMAND:
	    switch (LOWORD (uParam))
		{
		case IDOK:
		    /* get check box states and return as FLAGS in UM_PORT message */
		    *dwPTFlags = (*dwPTFlags & ~PT_IGNORECASE) ^
			(IsDlgButtonChecked (hDlg, IDC_IGNORECASE) ? PT_IGNORECASE : 0);
		    *dwPTFlags = (*dwPTFlags & ~PT_NOAPIS) ^
			(IsDlgButtonChecked (hDlg, IDC_NOAPIS) ? PT_NOAPIS : 0);
		    *dwPTFlags = (*dwPTFlags & ~PT_NOMESSAGES) ^
			(IsDlgButtonChecked (hDlg, IDC_NOMESSAGES) ? PT_NOMESSAGES : 0);
		    *dwPTFlags = (*dwPTFlags & ~PT_NOSTRUCTURES) ^
			(IsDlgButtonChecked (hDlg, IDC_NOSTRUCTURES) ? PT_NOSTRUCTURES : 0);
		    *dwPTFlags = (*dwPTFlags & ~PT_NOMACROS) ^
			(IsDlgButtonChecked (hDlg, IDC_NOMACROS) ? PT_NOMACROS : 0);
		    *dwPTFlags = (*dwPTFlags & ~PT_NOCONSTANTS) ^
			(IsDlgButtonChecked (hDlg, IDC_NOCONSTANTS) ? PT_NOCONSTANTS : 0);
		    *dwPTFlags = (*dwPTFlags & ~PT_NOTYPES) ^
			(IsDlgButtonChecked (hDlg, IDC_NOTYPES) ? PT_NOTYPES : 0);
		    *dwPTFlags = (*dwPTFlags & ~PT_NOCUSTOM) ^
			(IsDlgButtonChecked (hDlg, IDC_NOCUSTOM) ? PT_NOCUSTOM : 0);

		case IDCANCEL:
		    SendMessage (GetDlgItem (hDlg, IDC_CURTOKEN), WM_SETFONT, 0, FALSE);
		    DeleteObject (hStrikeoutFont);
		    EndDialog (hDlg, LOWORD (uParam) == IDOK);
		    break;

		case IDC_IGNORETOKEN:
		    /* toggle ignore bit */
		    *dwPTFlags ^= PT_IGNORETOKEN;

		    /* have control draw in strikeout if ignored */
		    if (*dwPTFlags & PT_IGNORETOKEN)
			SendMessage (GetDlgItem (hDlg, IDC_CURTOKEN),
				     WM_SETFONT,
				     (UINT)hStrikeoutFont,
				     TRUE);
		    /* else draw in system font */
		    else
			SendMessage (GetDlgItem (hDlg, IDC_CURTOKEN),
				     WM_SETFONT,
				     (UINT)hSystemFont,
				     TRUE);
		    break;
		}
	    break;

	default:
	    bRet = FALSE;
	    break;
	}

    /* return (message was processed); */
    return bRet;
}



/* port options dialog */
BOOL WINAPI PortDlgProc (
    HWND    hDlg,
    UINT    uMsg,
    UINT    uParam,
    LONG    lParam)
{
	BOOL    bRet = TRUE;
static  DWORD   dwPTFlags;
static  BOOL    bSearching = TRUE;
static  BOOL    bHelpActive = FALSE, bIsHelpFile = FALSE;
static  HBRUSH  hBkBrush;
static  HWND    hWndEdit;
static  HANDLE  hEditData = NULL;
static  int     nIssues = 0;
static  int     iLineNo, iStartPos;
static  HLOCAL  hToken, hHelp, hIssue, hSuggest;
static  HLOCAL  hEditLine;

static  UINT    uLen = 0;


    switch (uMsg)
	{
	case WM_INITDIALOG:
	    {
	    char    lpszTitle[MAX_PATH];
	    char    lpszFilename[MAX_PATH];
	    RECT    rc;

	    HDC     hDC;
	    HFONT   hFont;
	    TEXTMETRIC tm;

	    hFont = GetStockObject(SYSTEM_FONT);
	    hDC = GetDC(NULL);
	    hFont = SelectObject(hDC, hFont);
	    GetTextMetrics(hDC, &tm);
	    SelectObject(hDC, hFont);
	    ReleaseDC(NULL, hDC);
	    DLGOFFSET = tm.tmHeight * 5;

	    /* reposition self on bottom of screen */
	    GetWindowRect (hDlg, &rc);
	    SetWindowPos (hDlg,
			  NULL,
			  rc.left,
			  GetSystemMetrics (SM_CYSCREEN) -
			   (rc.bottom - rc.top + DLGOFFSET),
			  rc.right-rc.left,
			  rc.bottom-rc.top,
			  SWP_NOZORDER | SWP_NOSIZE);

	    /* set help available flag */
	    if (GetHelpFileName (lpszTitle))
		{
		EnableWindow (GetDlgItem (hDlg, IDC_HELPM), TRUE);
		bIsHelpFile = TRUE;
		}

	    /* allocate strings for Issue struct from local heap to reduce stack overhead */
	    if (!(rIssue.lpszToken = LocalLock (hToken = LocalAlloc (LHND, MAXTOKENLEN))) ||
		!(rIssue.lpszHelpStr = LocalLock (hHelp = LocalAlloc (LHND, MAXHELPLEN))) ||
		!(rIssue.lpszIssue = LocalLock (hIssue = LocalAlloc (LHND, MAXISSUELEN))) ||
		!(rIssue.lpszSuggest = LocalLock (hSuggest = LocalAlloc (LHND, MAXSUGGESTLEN))))
		{
		ErrorNotify (hDlg, IDS_MEMORYFAILED);
		PostMessage (hDlg, WM_COMMAND, IDC_DONE, 0);
		break;
		}
	    /* initialize line and token offset position stuff */
	    iLineNo = 0;
	    iStartPos = 0;
	    rIssue.nPosToken = 0;

	    /* initialize background brush for use in WM_CTLCOLOR message */
	    hBkBrush = (HBRUSH)GetClassLong (hDlg, GCL_HBRBACKGROUND);

	    /* set initial search flags to default */
	    dwPTFlags = 0;

	    /* initialize filename in caption */
	    LoadString (GetModuleHandle (NULL), IDS_PORTFILE, lpszTitle, MAX_PATH);
	    GetFileFromPath (lpszFilePath, lpszFilename);
	    strcat (lpszTitle, lpszFilename);
	    SetWindowText (hDlg, lpszTitle);

	    /* IDC_SUGGESTION to SW_HIDE */
	    ShowWindow (GetDlgItem (hDlg, IDC_SUGGESTION), SW_HIDE);
	    ShowWindow (GetDlgItem (hDlg, IDC_SUGGESTLABEL), SW_HIDE);

	    /* get edit window and data handle */
	    hWndEdit = (HWND)GetWindowLong (GetParent (hDlg), WL_HWNDEDIT);

#if !defined (WIN32)

	    hEditData = (HANDLE)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0);

#else
	    {
		char    *lpEditData;
		char    sz[80];
		MEMORYSTATUS memstat;

		uLen = GetWindowTextLength (hWndEdit);
		hEditData = LocalAlloc (LHND, uLen+1);
		if (hEditData == NULL) {
		    memstat.dwLength = sizeof(MEMORYSTATUS);
		    GlobalMemoryStatus (&memstat);
		    wsprintf (sz, "Failed Allocation: %u | %u (%u%%)", (UINT)uLen+1, (UINT)memstat.dwAvailPhys, memstat.dwMemoryLoad);
		    //MessageBox (GetFocus(), sz, "PortTool", MB_OK);
		    uLen = 500000;
		    while (hEditData == NULL && uLen > 1000) {
			uLen -= 1000;
			hEditData = LocalAlloc (LHND, uLen+1);
		    }
		    wsprintf (sz, "hEditData = %u : uLen = %u", (UINT)hEditData, (UINT)uLen);
		    //MessageBox (GetFocus(), sz, "PortTool", MB_OK);
		}
		lpEditData = LocalLock (hEditData);
		if (lpEditData == NULL) {
		    MessageBox (GetFocus(), "Unalble To Lock Memory!", "PortTool", MB_OK);
		} else {
		    UINT i;
		    i = GetWindowText (hWndEdit, lpEditData, uLen+1);
		    wsprintf (sz, "length: %u", i);
		    //MessageBox (GetFocus(), sz, "PortTool", MB_OK);
		}
		LocalUnlock (hEditData);
	    }
#endif

	    /* allocate here, reallocate later when needed */
	    hEditLine = LocalAlloc (LHND, 1);

	    /* post message to start ball rolling */
	    PostMessage (hDlg, WM_COMMAND, (UINT)IDC_CONTINUE, 0);

	    /* don't worry about focus here since were going to drive the search anyway */
	    bRet = TRUE;
	    }
	    //MessageBox (GetFocus(), "End Of Init", "PortTool", MB_OK);
	    break;

	case WM_COMMAND:
	    switch (LOWORD (uParam))
		{
		case IDC_CONTINUE:
		    {
		    int     iLastLine, nCharOffset, nLineLen;
		    MSG     msg;
		    char    lpszBuff[MAXTOKENLEN];
		    char    *lpszLine;
		    char    *lpLine;
		    char    *lpEditData;

		    /* disable continue button */
		    EnableWindow (GetDlgItem (hDlg, IDC_CONTINUE), FALSE);
		    EnableWindow (GetDlgItem (hDlg, IDC_OPTIONS), FALSE);
		    EnableWindow (GetDlgItem (hDlg, IDCANCEL), TRUE);

		    /* set IDC_SEARCHFOUND to green searching */
		    LoadString (GetModuleHandle (NULL), IDS_SEARCHING,
				lpszBuff,
				sizeof (lpszBuff));
		    SetWindowText (GetDlgItem (hDlg, IDC_SEARCHFOUND), lpszBuff);
		    bSearching = TRUE;

		    /* set last line */
		    iLastLine = (int)SendMessage (hWndEdit, EM_GETLINECOUNT, 0, 0);

		    /* find next port issue */
		    while (TRUE)
			{
			if (iLineNo >= iLastLine)
			    {
			    /* no more issues found, so clean up and go away */
			    ErrorNotify (hDlg, IDS_NOMOREPORTISSUES);

			    /* nullify any selection in line edit control */
			    SendMessage (GetDlgItem (hDlg, IDC_LINE), EM_SETSEL, 0, 0);
			    break;
			    }

			/* increment line no */
			SetWindowText (GetDlgItem (hDlg, IDC_LINENO),
				       itoa (iLineNo, lpszBuff, 10));

			/* get length and number of edit line */
			nCharOffset = SendMessage (hWndEdit, EM_LINEINDEX, iLineNo, 0);
			if ((nLineLen = SendMessage (hWndEdit, EM_LINELENGTH, nCharOffset, 0)) <= 2)
			    goto NEXT_LINE;

			/* allocate enough memory for edit line */
			if (!(hEditLine = LocalReAlloc (hEditLine,
							nLineLen+1,
							LHND)))
			    {
			    /* no more issues found, so clean up and go away */
			    ErrorNotify (hDlg, IDS_MEMORYFAILED);
			    PostMessage (hDlg, WM_COMMAND, IDC_DONE, 0);
			    break;
			    }

			/* get line from edit control, and null terminate */

			/* get edit window and data handle */

			lpEditData = LocalLock (hEditData);

			lpLine = lpszLine = LocalLock (hEditLine);

			strncpy (lpszLine, lpEditData+nCharOffset, nLineLen);
			lpszLine[nLineLen] = 0;

			/* increment the token position for multiple errors in a line */
			lpLine += iStartPos;
			LocalUnlock (hEditData);

			/* initialize line and hilight token */
			SetWindowText (GetDlgItem (hDlg, IDC_LINE), lpszLine);

			/* reinitialize rIssue strings lengths */
			*(WORD *)rIssue.lpszToken = MAXTOKENLEN;
			*(WORD *)rIssue.lpszHelpStr = MAXHELPLEN;
			*(WORD *)rIssue.lpszIssue = MAXISSUELEN;
			*(WORD *)rIssue.lpszSuggest = MAXSUGGESTLEN;

			/* search next line */
			if (CheckString (lpLine, dwPTFlags, &rIssue))
			    {
			    /* set SEARCHFOUND string to found */
			    LoadString (GetModuleHandle (NULL),
					IDS_FOUND,
					lpszBuff,
					sizeof (lpszBuff));
			    strcat (lpszBuff, rIssue.lpszToken);
			    SetWindowText (GetDlgItem (hDlg, IDC_SEARCHFOUND), lpszBuff);

			    /* reenable options button */
			    EnableWindow (GetDlgItem (hDlg, IDC_OPTIONS), TRUE);

			    /* set searching flag off */
			    bSearching = FALSE;

			    /* increment issue cnt */
			    SetWindowText (GetDlgItem (hDlg, IDC_ISSUECNT),
					   itoa (++nIssues, lpszBuff, 10));

			    /* initialize Issue */
			    SetWindowText (GetDlgItem (hDlg, IDC_ISSUE), rIssue.lpszIssue);

			    /* if help, enble button */
			    EnableWindow (GetDlgItem (hDlg, IDC_HELPM),
					  ((*(rIssue.lpszSuggest) != 0) && bIsHelpFile));

			    /* if suggest, show suggestion */
			    if (*(rIssue.lpszSuggest))
				{
				SetWindowText (GetDlgItem (hDlg, IDC_SUGGESTION),
					       rIssue.lpszSuggest);
				if (!IsWindowVisible (GetDlgItem (hDlg, IDC_SUGGESTION)))
				    GrowDialog (hDlg, TRUE);
				}

			    else if (IsWindowVisible (GetDlgItem (hDlg, IDC_SUGGESTION)))
				GrowDialog (hDlg, FALSE);

			    /* scroll parent edit control and select offending text */
			    SendMessage (hWndEdit, EM_LINESCROLL, 0, iLineNo -
			    SendMessage (hWndEdit, EM_GETFIRSTVISIBLELINE, 0, 0));
			    SendMessage (hWndEdit,
					 EM_SETSEL,
					 iStartPos + nCharOffset + rIssue.nPosToken,
					 iStartPos + nCharOffset + rIssue.nPosToken +
					     strlen (rIssue.lpszToken));

			    /* select text in line edit control */
			    SendMessage (GetDlgItem (hDlg, IDC_LINE),
					 EM_SETSEL,
					 iStartPos + rIssue.nPosToken,
					 iStartPos + rIssue.nPosToken +
					     strlen (rIssue.lpszToken));

			    /* reset nPosToken to check rest of line */
			    iStartPos += (rIssue.nPosToken + strlen (rIssue.lpszToken));
			    LocalUnlock (hEditLine);
			    break;
			    }

			/* call peek message to let user cancel if they choose */
			if (PeekMessage (&msg,
					 GetDlgItem (hDlg, IDCANCEL),
					 WM_LBUTTONDOWN,
					 WM_LBUTTONDOWN,
					 PM_REMOVE))
			    {
			    /* reset appropriate buttons */
			    EnableWindow (GetDlgItem (hDlg, IDCANCEL), FALSE);
			    EnableWindow (GetDlgItem (hDlg, IDC_HELPM), FALSE);
			    EnableWindow (GetDlgItem (hDlg, IDC_OPTIONS), TRUE);

			    /* break to let message get delivered */
			    break;
			    }

			/* also let the user exit from searching */
			if (PeekMessage (&msg,
					 GetDlgItem (hDlg, IDC_DONE),
					 WM_LBUTTONDOWN,
					 WM_LBUTTONDOWN,
					 PM_REMOVE))
			    {
			    PostMessage (hDlg, WM_COMMAND, IDC_DONE, 0);
			    break;
			    }

			/* unlock local edit line */
			LocalUnlock (hEditLine);

			/* reset token position */
			rIssue.nPosToken = 0;
			iStartPos = 0;
NEXT_LINE:
			/* increment line and continue */
			iLineNo++;
			}

		    /* enable continue button unless at end of file */
		    if (iLineNo < iLastLine)
			{
			EnableWindow (GetDlgItem (hDlg, IDC_CONTINUE), TRUE);
			SetFocus (GetDlgItem (hDlg, IDC_CONTINUE));
			}
		    else
			{
			EnableWindow (GetDlgItem (hDlg, IDC_CONTINUE), FALSE);
			EnableWindow (GetDlgItem (hDlg, IDCANCEL), FALSE);
			SetFocus (GetDlgItem (hDlg, IDC_DONE));
			}
		    }
		    break;

		case WM_CLOSE:
		case IDC_DONE:
		    {
		    char    lpszFile[MAX_PATH];

		    if (bHelpActive &&
			GetHelpFileName (lpszFile))
			WinHelp (hDlg, lpszFile, HELP_QUIT, 0);

		    /* clean up and go away */
		    LocalUnlock (hToken); LocalFree (hToken);
		    LocalUnlock (hHelp); LocalFree (hHelp);
		    LocalUnlock (hIssue); LocalFree (hIssue);
		    LocalUnlock (hSuggest); LocalFree (hSuggest);
		    LocalFree (hEditLine);
			DestroyWindow (hDlg);
			hDlgPort = NULL;

		    }
		    break;

		case IDC_OPTIONS:
		    {
		    DWORD    dwOptions = dwPTFlags;

		    /* call dialog to start port process */
		    if (DialogBoxParam (GetModuleHandle (NULL),
					IDD_OPTIONSDLG,
					hDlg,
					OptionsDlgProc,
					(LPARAM)&dwOptions))
			{
			dwPTFlags = dwOptions;

			/* if PT_IGNORETOKEN, call CheckString */
			if (dwOptions & PT_IGNORETOKEN)
			    {
			    CheckString (rIssue.lpszToken, dwPTFlags, NULL);
			    dwPTFlags ^= PT_IGNORETOKEN;
			    }
			}

		    }
		    break;

		case IDC_HELPM:
		    {
		    char    lpszFile[MAX_PATH];

		    if (bIsHelpFile && GetHelpFileName (lpszFile))
			{
			WinHelp (hDlg, lpszFile, HELP_KEY, (DWORD)rIssue.lpszHelpStr);
			bHelpActive = TRUE;
			}
		    }
		    break;

		case IDC_RESTART:
		    iLineNo = 0;
		    rIssue.nPosToken = 0;
		    iStartPos = 0;
		    PostMessage (hDlg, WM_COMMAND, IDC_CONTINUE, 0);
		    break;
		}
	    break;

	default:
	    bRet = FALSE;
	    break;
	}

    /* return (message was processed); */
    return bRet;
}




/* background porting status dialog */
BOOL WINAPI BkPortDlgProc (
    HWND    hDlg,
    UINT    uMsg,
    UINT    uParam,
    LONG    lParam)
{
	  BOOL          bRet = TRUE;
	  char          szFileName[MAX_PATH];
	  char          szFilePath[MAX_PATH];
static    BKFILELIST    *lpbkFiles;
static    int           iCurThread;
static    BOOL          bStarted = FALSE;
	  BKFILELIST    *lpNode;

	//	char szDebug[80];

	// wsprintf (szDebug, "%i : [0x%X - 0x%X]", uMsg, uParam, lParam);
	// OutputDebugString (szDebug);

    switch (uMsg)
	{
	case WM_INITDIALOG:
	    {
	    HWND          hIssues = GetDlgItem (hDlg, IDC_ISSUES);
	    HWND          hLines = GetDlgItem (hDlg, IDC_LINES);
	    HWND          hComplete = GetDlgItem (hDlg, IDC_COMPLETE);

	    /* set background icon to porttool background icon and start minimized */
	    SetClassLong (hDlg,
			  GCL_HICON,
			  (LONG)LoadIcon (GetModuleHandle (NULL), IDBkPort));

	    lpbkFiles = NULL;
	    iCurThread = -1;

	    /* build list of files to port from lParam */
	    if (lParam)
		{
		if (!BuildFileList ((char *)lParam, &lpbkFiles))
		    {
		    lpbkFiles = NULL;
		    break;
		    }
		}

	    else
		{
		/* get file from user first */
		*szFileName = 0;
		*szFilePath = 0;

		GetFileName (hDlg, szFileName, szFilePath);
		if (!BuildFileList (szFilePath, &lpbkFiles))
		    {
		    lpbkFiles = NULL;
		    break;
		    }
		}

	    lpNode = lpbkFiles;
	    /* initialize each file in list */
	    while (lpNode)
		{
		/* add filename to listbox */
		SendMessage (GetDlgItem (hDlg, IDC_FILELIST),
			     LB_ADDSTRING,
			     0,
			     (LPARAM)lpNode->bkFile.szFile);

		/* initialize some stuff */
		lpNode->bkFile.hDlg = hDlg;
		lpNode->bkFile.dwPTFlags = PT_DEFAULT;

		/* start background thread on each file */
		if (!StartBkPortThread (&lpNode->bkFile)) {
		    MessageBox(GetFocus(), "Failed to spawn background porting thread", "PortTool", MB_OK);
		}

		/* traverse list */
		lpNode = lpNode->Next;
		}

	    /* select first thread in listbox */
	    SendMessage (GetDlgItem (hDlg, IDC_FILELIST), LB_SETCURSEL, 0, 0);
	    SetDlgItemText (hDlg, IDC_FILEPATH, lpbkFiles->bkFile.szFilePath);

	    /* if started with /b switch */
	    if (!GetParent (hDlg))
		ShowWindow (hDlg, SW_SHOWMINIMIZED);
	    else
		MySetEvent (hDlg, lpbkFiles->hEvents[BKPORT_STATUS]);

	    iCurThread = 0;
	    bStarted = TRUE;
		}
	    break;

	case WM_SHOWWINDOW:
	    if (bStarted)
		{
		int    i = 0;

		lpNode = lpbkFiles;
		while (i++ < iCurThread)
		    lpNode = lpNode->Next;

		if (!uParam && lpNode)
		    MyResetEvent (hDlg, lpNode->hEvents[BKPORT_STATUS]);
		else if(lpNode)
		    MySetEvent (hDlg, lpNode->hEvents[BKPORT_STATUS]);
		}
	    break;

	case WM_SIZE:
	    if (bStarted) {
		    int    i = 0;

    		lpNode = lpbkFiles;
    
    		while (i++ < iCurThread) {
    		    lpNode = lpNode->Next;
    		}

    		if (uParam == SIZEICONIC && lpNode) {
    		    MyResetEvent (hDlg, lpNode->hEvents[BKPORT_STATUS]);
    		} else if(lpNode) {
    		    MySetEvent (hDlg, lpNode->hEvents[BKPORT_STATUS]);
    		}
	    }
	    break;

	case UM_STATUSUPDATE:
	    {
	    char    Buff[10];

	    /* update status info controls */
	    SetDlgItemText (hDlg, IDC_ISSUES, itoa (LOWORD (uParam), Buff, 10));
	    SetDlgItemText (hDlg, IDC_COMPLETE, itoa (HIWORD (uParam), Buff, 10));
	    SetDlgItemText (hDlg, IDC_LINES, itoa (lParam, Buff, 10));
	    }
	    break;

	case UM_THREADCOMPLETE:
	    {
	    int    iThread = 0;

	    /* find handle in list */
	    lpNode = lpbkFiles;
	    while (lpNode)
		{
		if ((HANDLE)uParam == lpNode->bkFile.hThread)
		    break;
		lpNode = lpNode->Next;
		iThread++;
		}

	    if (lpNode)
		{
		/* remove file list item */
		RemoveFile (lpNode->bkFile.szFilePath, &lpbkFiles);

		/* remove item from list box */
		SendMessage (GetDlgItem (hDlg, IDC_FILELIST),
			     LB_DELETESTRING,
			     iThread,
			     0);

		/* if current thread ended and more threads exist */
		if (iThread == iCurThread &&
		    lpbkFiles             &&
		    SendMessage (GetDlgItem (hDlg, IDC_FILELIST), LB_GETCOUNT, 0, 0))
		    {
		    SendMessage (GetDlgItem (hDlg, IDC_FILELIST), LB_SETCURSEL, 0, 0);
		    MySetEvent (hDlg, lpbkFiles->hEvents[BKPORT_STATUS]);
		    iCurThread = 0;
		    }

		else if (iThread == iCurThread)
		    {
		    iCurThread = -1;
		    PostMessage (hDlg, WM_COMMAND, IDC_BKDONE, 0);
		    }

		/* clean up controls */
		SetDlgItemText (hDlg, IDC_FILEPATH, "");
		PostMessage (hDlg, UM_STATUSUPDATE, 0, 0);
		}

	    else
		{
                CHAR szBuf[MAX_PATH];
                LoadString((HANDLE)GetModuleHandle(NULL),
                    IDS_ERR_INVALID_THREADHND,
                    szBuf,sizeof(szBuf));
		MessageBox (hDlg, szBuf, NULL, MB_ICONSTOP | MB_OK);
		ExitProcess (FALSE);
		}

	    }
	    break;

	case WM_COMMAND:
	    switch (LOWORD (uParam))
		{
		case IDC_FILELIST:
		    /* if new file selected change update signal to active thread */
		    if (HIWORD (uParam) == LBN_SELCHANGE)
			{
			int    i = 0;
			int    iNewThread = SendMessage (GetDlgItem (hDlg, IDC_FILELIST),
							 LB_GETCURSEL,
							 0,
							 0);

			/* reset current thread */
			lpNode = lpbkFiles;
			while (lpNode)
			    {
			    if (i == iCurThread)
				MyResetEvent (hDlg, lpNode->hEvents[BKPORT_STATUS]);

			    if (i == iNewThread)
				{
				MySetEvent (hDlg, lpNode->hEvents[BKPORT_STATUS]);
				SetDlgItemText (hDlg,
						IDC_FILEPATH,
						lpNode->bkFile.szFilePath);
				}

			    lpNode = lpNode->Next;
			    i++;
			    }

			iCurThread = iNewThread;
			}
		    break;

		case IDC_ABORTFILE:
		    {
		    int        i = 0;
		    HCURSOR    hOldCursor;

		    /* reset current thread */
		    lpNode = lpbkFiles;
		    while (lpNode)
			{
			if (i == iCurThread)
			    {
			    /* put hourglass cursor up */
			    hOldCursor = (HCURSOR)SetClassLong (hDlg, GCL_HCURSOR, 0);
			    SetCursor (LoadCursor (NULL, IDC_WAIT));

			    /* abort porting file where it is */
			    MySetEvent (hDlg, lpNode->hEvents[BKPORT_ABORT]);

			    /* remove file from list when thread is dead */
			    WaitForSingleObject (lpNode->bkFile.hThread, INFINITE);
			    RemoveFile (lpNode->bkFile.szFilePath, &lpbkFiles);

			    /* replace original cursor */
			    SetClassLong (hDlg, GCL_HCURSOR, (LONG)hOldCursor);
			    SetCursor (hOldCursor);

			    /* update listbox */
			    SendMessage (GetDlgItem (hDlg, IDC_FILELIST),
					 LB_DELETESTRING,
					 iCurThread,
					 0);

			    /* select new event if any in listbox */
			    if (SendMessage (GetDlgItem (hDlg, IDC_FILELIST),
					     LB_GETCOUNT,
					     0,
					     0))
				{
				SendMessage (GetDlgItem (hDlg, IDC_FILELIST),
					     LB_SETCURSEL,
					     0,
					     0);
				MySetEvent (hDlg, lpbkFiles->hEvents[BKPORT_STATUS]);
				iCurThread = 0;
				}

			    else
				{
				iCurThread = -1;
				PostMessage (hDlg, WM_COMMAND, IDC_DONE, 0);
				}

			    /* clean up controls */
			    SetDlgItemText (hDlg, IDC_FILEPATH, "");
			    PostMessage (hDlg, UM_STATUSUPDATE, 0, 0);
			    break;
			    }

			lpNode = lpNode->Next;
			i++;
			}
		    }
		    break;

		case IDC_ADDFILE:
		    {
		    /* get file from user first */
		    *szFileName = 0;
		    *szFilePath = 0;

		    /* add a file to the list */
		    if (GetFileName (hDlg, szFileName, szFilePath))
			{
			/* if new list */
            if (!lpbkFiles)
            {
                if (!BuildFileList (szFilePath, &lpbkFiles))
                {
                    lpbkFiles = NULL;
                    break;
                }
            }
			else if (!AddFile (szFilePath, szFileName, lpbkFiles))
			    break;

			/* find node in list */
			lpNode = lpbkFiles;
			while (lpNode)
			    {
			    if (!strcmp (lpNode->bkFile.szFilePath, szFilePath))
				break;
			    lpNode = lpNode->Next;
			    }

			if (lpNode)
			    {
			    /* add filename to listbox */
			    SendMessage (GetDlgItem (hDlg, IDC_FILELIST),
					 LB_ADDSTRING,
					 0,
					 (LPARAM)lpNode->bkFile.szFile);

			    /* initialize some stuff */
			    lpNode->bkFile.hDlg = hDlg;
			    lpNode->bkFile.dwPTFlags = PT_DEFAULT;

			    /* start background thread on this file */
			    StartBkPortThread (&lpNode->bkFile);

			    /* if first thread */
			    if (iCurThread == -1 ||
				SendMessage (GetDlgItem (hDlg, IDC_FILELIST),
					     LB_GETCOUNT, 0, 0) == 1)
				{
				iCurThread = 0;
				SendMessage (GetDlgItem (hDlg, IDC_FILELIST),
					     LB_SETCURSEL,
					     0,
					     0);
				SendMessage (hDlg,
					     WM_COMMAND,
					     MAKELONG (IDC_FILELIST, LBN_SELCHANGE),
					     0);
				}
			    }
			}
		    }
		    break;

		case IDC_CHANGEOPTIONS:
		    {
		    DWORD    dwFlags;

			dwFlags = 0L;
		    dwFlags = (dwFlags & ~PT_IGNORECASE) ^
			(IsDlgButtonChecked (hDlg, IDC_BKIGNORECASE) ? PT_IGNORECASE : 0);
		    dwFlags = (dwFlags & ~PT_NOAPIS) ^
			(IsDlgButtonChecked (hDlg, IDC_BKNOAPIS) ? PT_NOAPIS : 0);
		    dwFlags = (dwFlags & ~PT_NOMESSAGES) ^
			(IsDlgButtonChecked (hDlg, IDC_BKNOMESSAGES) ? PT_NOMESSAGES : 0);
		    dwFlags = (dwFlags & ~PT_NOSTRUCTURES) ^
			(IsDlgButtonChecked (hDlg, IDC_BKNOSTRUCTURES) ? PT_NOSTRUCTURES : 0);
		    dwFlags = (dwFlags & ~PT_NOMACROS) ^
			(IsDlgButtonChecked (hDlg, IDC_BKNOMACROS) ? PT_NOMACROS : 0);
		    dwFlags = (dwFlags & ~PT_NOCONSTANTS) ^
			(IsDlgButtonChecked (hDlg, IDC_BKNOCONSTANTS) ? PT_NOCONSTANTS : 0);
		    dwFlags = (dwFlags & ~PT_NOTYPES) ^
			(IsDlgButtonChecked (hDlg, IDC_BKNOTYPES) ? PT_NOTYPES : 0);
		    dwFlags = (dwFlags & ~PT_NOCUSTOM) ^
			(IsDlgButtonChecked (hDlg, IDC_BKNOCUSTOM) ? PT_NOCUSTOM : 0);

		    /* change the options for the file being ported */
		    lpbkFiles->bkFile.dwPTFlags = dwFlags;
		    }
		    break;

		case IDCANCEL:
		    {
		    HCURSOR    hOldCursor;
		    HANDLE     hThreads[MAXBKTHREADS];
		    int        i = 0;
                    CHAR       szText[MAX_PATH]; // for LoadString()
                    CHAR       szTitle[MAX_PATH]; // for LoadString()
                    HMODULE    hModule = GetModuleHandle(NULL);

		    /* put up confirm message */
                    LoadString((HANDLE)hModule,
                        IDS_CANCEL_BKGND_PROCESS,
                        szText,sizeof(szText));
                    LoadString((HANDLE)hModule,
                        IDS_ABORT_TITLE,
                        szTitle,sizeof(szTitle));
		    if (MessageBox (hDlg,
				    szText, szTitle,
				    MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
			{
			/* put hourglass cursor up */
			hOldCursor = (HCURSOR)SetClassLong (hDlg, GCL_HCURSOR, 0);
			SetCursor (LoadCursor (NULL, IDC_WAIT));

			/* if any files in list */
			if (lpbkFiles)
			    {
			    /* abort all background threads and build thread handle array */
			    lpNode = lpbkFiles;
			    while (lpNode)
				{
				MySetEvent (hDlg, lpNode->hEvents[BKPORT_ABORT]);
				hThreads[i++] = lpNode->bkFile.hThread;
				lpNode = lpNode->Next;
				}

			    /* wait on completion of background threads */
			    WaitForMultipleObjects (i, hThreads, TRUE, INFINITE);

			    /* free background port resources */
			    FreeFileList (lpbkFiles);
			    }

			SetClassLong (hDlg, GCL_HCURSOR, (LONG)hOldCursor);
			SetCursor (hOldCursor);
			DestroyWindow (hDlg);
			hDlgPortStatus = NULL;

			}
		    }
		    break;

		case IDC_BKDONE:
		    /* if file list post message to cancel */
		    if (lpbkFiles)
			PostMessage (hDlg, WM_COMMAND, IDCANCEL, 0);
		    else
			DestroyWindow (hDlg);
			hDlgPortStatus = NULL;
		    break;

		default:
		    bRet = FALSE;
		    break;
		}
	    break;

	case WM_DESTROY:
	    /* if no parent, post quit message */
	    if (GetParent (hDlg) == NULL)
		PostQuitMessage (1);
	    break;

	default:
	    bRet = FALSE;
	    break;
	}

    return bRet;
}



/* funtion retrieves the help filename from the ini file */
BOOL WINAPI GetHelpFileName (
    char    *lpszFile)
{
    char        szAppName[30];
    char        szWinHelp[30];
    char        szDefault[] = "Default";
    OFSTRUCT    of;

    /* get help filename from ini file */
    LoadString (GetModuleHandle (NULL), IDS_APPNAME, szAppName, 30);
    LoadString (GetModuleHandle (NULL), IDS_WINHELP, szWinHelp, 30);
    GetPrivateProfileString (szAppName,
			     szWinHelp,
			     szDefault,
			     lpszFile,
			     MAX_PATH,
				 lpszPortIniFilePath);

    /* test to see if help file exists */
    return (OpenFile (lpszFile, &of, OF_EXIST) != -1);
}




/* rearrange dialog and controls */
void WINAPI GrowDialog (
    HWND    hDlg,
    BOOL    bBigger)
{
    RECT    rc;
    int     nChange = (bBigger ? DLGOFFSET : -DLGOFFSET);

    /* grow main dialog */
    GetWindowRect (hDlg, &rc);
    SetWindowPos (hDlg,
		  NULL,
		  rc.left,
		  rc.top,
		  rc.right-rc.left,
		  rc.bottom-rc.top + nChange,
		  SWP_NOMOVE | SWP_NOZORDER);

    /* move stop button down */
    GetWindowRect (GetDlgItem (hDlg, IDCANCEL), &rc);
    ScreenToClient (hDlg, (LPPOINT)&rc);
    ScreenToClient (hDlg, (LPPOINT)&rc.right);
    SetWindowPos (GetDlgItem (hDlg, IDCANCEL),
		  NULL,
		  rc.left,
		  rc.top + nChange,
		  rc.right-rc.left,
		  rc.bottom-rc.top,
		  SWP_NOSIZE | SWP_NOZORDER);

    /* move CONTINUE button down */
    GetWindowRect (GetDlgItem (hDlg, IDC_CONTINUE), &rc);
    ScreenToClient (hDlg, (LPPOINT)&rc);
    ScreenToClient (hDlg, (LPPOINT)&rc.right);
    SetWindowPos (GetDlgItem (hDlg, IDC_CONTINUE),
		  NULL,
		  rc.left,
		  rc.top + nChange,
		  rc.right-rc.left,
		  rc.bottom-rc.top,
		  SWP_NOSIZE | SWP_NOZORDER);

    /* move restart button down */
    GetWindowRect (GetDlgItem (hDlg, IDC_RESTART), &rc);
    ScreenToClient (hDlg, (LPPOINT)&rc);
    ScreenToClient (hDlg, (LPPOINT)&rc.right);
    SetWindowPos (GetDlgItem (hDlg, IDC_RESTART),
		  NULL,
		  rc.left,
		  rc.top + nChange,
		  rc.right-rc.left,
		  rc.bottom-rc.top,
		  SWP_NOSIZE | SWP_NOZORDER);

    /* move options button down */
    GetWindowRect (GetDlgItem (hDlg, IDC_OPTIONS), &rc);
    ScreenToClient (hDlg, (LPPOINT)&rc);
    ScreenToClient (hDlg, (LPPOINT)&rc.right);
    SetWindowPos (GetDlgItem (hDlg, IDC_OPTIONS),
		  NULL,
		  rc.left,
		  rc.top + nChange,
		  rc.right-rc.left,
		  rc.bottom-rc.top,
		  SWP_NOSIZE | SWP_NOZORDER);

    /* move help button down */
    GetWindowRect (GetDlgItem (hDlg, IDC_HELPM), &rc);
    ScreenToClient (hDlg, (LPPOINT)&rc);
    ScreenToClient (hDlg, (LPPOINT)&rc.right);
    SetWindowPos (GetDlgItem (hDlg, IDC_HELPM),
		  NULL,
		  rc.left,
		  rc.top + nChange,
		  rc.right-rc.left,
		  rc.bottom-rc.top,
		  SWP_NOSIZE | SWP_NOZORDER);

    /* move done button down */
    GetWindowRect (GetDlgItem (hDlg, IDC_DONE), &rc);
    ScreenToClient (hDlg, (LPPOINT)&rc);
    ScreenToClient (hDlg, (LPPOINT)&rc.right);
    SetWindowPos (GetDlgItem (hDlg, IDC_DONE),
		  NULL,
		  rc.left,
		  rc.top + nChange,
		  rc.right-rc.left,
		  rc.bottom-rc.top,
		  SWP_NOSIZE | SWP_NOZORDER);

    /* show suggestion edit control and label when appropriate */
    ShowWindow (GetDlgItem (hDlg, IDC_SUGGESTION), (bBigger ? SW_SHOW : SW_HIDE));
    ShowWindow (GetDlgItem (hDlg, IDC_SUGGESTLABEL), (bBigger ? SW_SHOW : SW_HIDE));
}




BOOL WINAPI BuildFileList (
    char          *lpFileList,
    LPBKFILELIST  *lpList)
{
    char        *lpFile;
    char        szFilePath[MAX_PATH];
    char        szFile[MAX_PATH];
    HFILE       hFile;
    OFSTRUCT    of;
    BOOL        bList = FALSE;

    /* create heap for up to 50 files at a time */
    if (!(hBkFileHeap = HeapCreate (HEAP_NO_SERIALIZE,
				    sizeof (BKFILELIST),
				    MAXBKTHREADS * sizeof (BKFILELIST))))
	return FALSE;

    /* allocate first node in list */
    *lpList = (BKFILELIST *)HeapAlloc (hBkFileHeap, 0, sizeof (BKFILELIST));
    (*lpList)->hEvents[BKPORT_ABORT] = NULL;

    /* parse first file in list */
    lpFile = strtok (lpFileList, " ");

    /* loop through all files in list */
    while (lpFile)
	{
	strcpy (szFilePath, lpFile);

	/* if no path, add current directory as path */
	if (!GetFileFromPath (szFilePath, szFile))
	    {
	    strcpy (szFile, szFilePath);
	    GetCurrentDirectory (MAX_PATH, szFilePath);
	    strcat (szFilePath, "\\");
	    strcat (szFilePath, szFile);
	    }

	/* verify file is available */
	hFile = OpenFile (szFilePath, &of, OF_READWRITE);
	if (hFile != -1)
	    {
	    /* added at least one file */
	    bList = TRUE;

	    /* close file */
	    CloseHandle ((HANDLE)hFile);

	    /* add file to list */
	    AddFile (szFilePath, szFile, *lpList);
	    }

	/* get next file in list */
	lpFile = strtok (NULL, " ");
	}

    /* if no valid files, cleanup */
    if (!bList)
	{
	HeapDestroy (hBkFileHeap);
	return FALSE;
	}

    return TRUE;
}




BOOL WINAPI AddFile (
    char        *lpFilePath,
    char        *lpFile,
    BKFILELIST  *lpbkFiles)
{
    BKFILELIST    *lpNode;


    /* if first item in list don't need to allocate */
    if (!lpbkFiles->hEvents[BKPORT_ABORT])
	lpNode = lpbkFiles;
    else
	{
	lpNode = (BKFILELIST *)HeapAlloc (hBkFileHeap, 0, sizeof (BKFILELIST));
	if (!lpNode)
	    return FALSE;

	/* find end of list then add new node */
	while (lpbkFiles->Next)
	    lpbkFiles = lpbkFiles->Next;
	lpbkFiles->Next = lpNode;
	}

    /* initialize node structure */
    strcpy (lpNode->bkFile.szFile, lpFile);
    strcpy (lpNode->bkFile.szFilePath, lpFilePath);
    CreateEvents (lpNode->hEvents, &lpNode->bkFile);
    lpNode->Next = NULL;

    return TRUE;
}




BOOL WINAPI RemoveFile (
    char          *lpFilePath,
    LPBKFILELIST  *lpbkFiles)
{
    BKFILELIST    *pHead = *lpbkFiles;
    BKFILELIST    *pTail = *lpbkFiles;

    /* loop thru list until file name matches */
    while (pHead)
	{
	if (!strcmp (lpFilePath, pHead->bkFile.szFilePath))
	    {
	    /* special case remove first node */
	    if (pTail == pHead)
		{
		*lpbkFiles = pHead->Next;
		DestroyEvents (pHead->hEvents);
		HeapFree (hBkFileHeap, 0, (char *)(pHead));

		/* if no more nodes, destroy heap */
		if (!*lpbkFiles)
		    HeapDestroy (hBkFileHeap);
		}

	    else
		{
		pTail->Next = pHead->Next;
		DestroyEvents (pHead->hEvents);
		HeapFree (hBkFileHeap, 0, (char *)pHead);
		}

	    return TRUE;
	    }

	pTail = pHead;
	pHead = pHead->Next;
	}

    return FALSE;
}




BOOL WINAPI FreeFileList (
    BKFILELIST  *lpbkFiles)
{
    /* loop thru each list item */
    while (lpbkFiles)
	{
	/* destroy event handles */
	DestroyEvents (lpbkFiles->hEvents);

	lpbkFiles = lpbkFiles->Next;
	}

    /* release entire heap */
    HeapDestroy (hBkFileHeap);

    return TRUE;
}


BOOL MySetEvent (HWND hWnd, HANDLE hEvent)
{
    if (SetEvent(hEvent)) {
	return TRUE;
    } else {
	return PostMessage (hWnd, (UINT)hEvent, 0, 0L);
    }
}

BOOL MyResetEvent (HWND hWnd, HANDLE hEvent)
{
    MSG msg;

    if (ResetEvent(hEvent)) {
	return TRUE;
    } else {
	PeekMessage (&msg, hWnd, (UINT)hEvent, (UINT)hEvent, TRUE);
	return TRUE;
    }
}
