#include "debug.h"

// local functions
BOOL WINAPI GetCmdLine (char *, char *, BOOL *);
HWND WINAPI InitEnvironment (HANDLE, char *, int);
void WINAPI InitMenu (HWND);
BOOL WINAPI IsValidFile (char *);
BOOL WINAPI CreateDebugSession (HWND, char *);
int  WINAPI NotifyUser (HWND, int, int, char *, UINT);


// entry point of this executable
int WINAPI WinMain (hInstance, hPrevInstance, lpCmdLine, nCmdShow)
    HINSTANCE hInstance;
    HINSTANCE hPrevInstance;
    LPSTR     lpCmdLine;
    int       nCmdShow;
{

    MSG      msg;
    char     *lpszBuff = NULL;
    char     *lpszCmdLine = NULL;
    char     *lpCL;
    BOOL     bSwitch;
    HWND     hClient;

    // parse and copy command line parameters to local memory
    lpCL = GetCommandLine ();
    if (lpszCmdLine = (char *)LocalAlloc (LPTR, strlen (lpCL) + 1))
	GetCmdLine (lpCL, lpszCmdLine, &bSwitch);

    // start window environment
    if (!(hClient = InitEnvironment (hInstance, lpszCmdLine, nCmdShow)))
	return FALSE;

    // free memory allocated for lpCmdLine
    if (lpszCmdLine)
	LocalFree ((HLOCAL)lpszCmdLine);

    // main window message loop
    while (GetMessage (&msg, NULL, 0, 0))
	if (!TranslateMDISysAccel (hClient, &msg))
	    {
	    TranslateMessage (&msg);
	    DispatchMessage (&msg);
	    }

    // return success of application
    return TRUE;
}



// start app
HWND WINAPI InitEnvironment (
    HANDLE    hInstance,
    char      *lpszCmdLine,
    int       nCmdShow)
    {
    WNDCLASS   wc;
    char       szClass[MAX_PATH];
    char       szTitle[MAX_PATH];
    HWND       hWnd;
    HWND       hClient;


    // register the debug window class
    LoadString (hInstance, IDS_DEBUGCLASS, szClass, sizeof (szClass));
    wc.style	     = 0;
    wc.lpfnWndProc   = (WNDPROC)DebugWndProc;
    wc.cbClsExtra    = DEBUGCXB;
    wc.cbWndExtra    = DEBUGWXB;
    wc.hInstance     = hInstance;
    wc.hIcon	     = LoadIcon (hInstance, MAKEINTRESOURCE (IDR_DEBUGICON));
    wc.hCursor	     = LoadCursor (0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = szClass;
    if (!RegisterClass (&wc) )
	return 0;


    // register the main frame window class
    LoadString (hInstance, IDS_FRAMECLASS, szClass, sizeof (szClass));
    LoadString (hInstance, IDS_CAPTION, szTitle, sizeof (szTitle));
    wc.style	     = 0;
    wc.lpfnWndProc   = (WNDPROC)FrameWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon	     = LoadIcon (hInstance, MAKEINTRESOURCE (IDR_MAINICON));
    wc.hCursor	     = LoadCursor (0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE (IDR_DEBUGMENU);
    wc.lpszClassName = szClass;
    if (!RegisterClass (&wc) )
	return FALSE;

    // create main frame window
    hWnd = CreateWindow (szClass,
			 szTitle,
			 WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
			 CW_USEDEFAULT,
			 0,
			 CW_USEDEFAULT,
			 0,
			 NULL,
			 NULL,
			 hInstance,
			 lpszCmdLine);

    if (!hWnd)
	return 0;
    else
	// retrieve the MDI client window handle
	hClient = GetWindow (hWnd, GW_CHILD);

    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);

    return hClient;
}


// main window procedure
LONG WINAPI FrameWndProc (
    HWND    hWnd,
    UINT    uMsg,
    UINT    uParam,
    LONG    lParam)
{
    LONG    lRet = 1;

    switch (uMsg)
	{
	case WM_INITMENU:
	    InitMenu (hWnd);
	    break;

	case WM_CREATE:
	    {
	    LPCREATESTRUCT	  lpcs = (LPCREATESTRUCT)lParam;
	    HCURSOR		  hOldCursor;
	    CLIENTCREATESTRUCT	  ccs;
	    char		  szMDI[MAX_PATH];


	    // put hourglass cursor up
	    hOldCursor = (HCURSOR)SetClassLong (hWnd, GCL_HCURSOR, 0);
	    SetCursor (LoadCursor (0, IDC_WAIT));

	    // fill mdi client info structure
	    ccs.idFirstChild = IDM_FIRSTCHILD;
	    ccs.hWindowMenu = GetSubMenu (GetMenu (hWnd),
					  GetMenuItemCount (GetMenu (hWnd)) - 2);

	    LoadString (GetModuleHandle (NULL), IDS_MDICLASS, szMDI, MAX_PATH);

	    // create mdi client window
	    if (!CreateWindow (szMDI,
			       "",
			       WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			       0, 0, 0, 0,
			       hWnd,
			       (HMENU)1,
			       GetModuleHandle (NULL),
			       &ccs))
		{
		PostMessage (hWnd, WM_CLOSE, 0, 0);
		break;
		}

	    // if file was passed on the command line, load it now
	    if (lpcs->lpCreateParams &&
		*((char *)(lpcs->lpCreateParams)))
		{
		if (!(IsValidFile (lpcs->lpCreateParams) &&
		      CreateDebugSession (GetWindow (hWnd, GW_CHILD), lpcs->lpCreateParams)))
		    NotifyUser (hWnd,
				IDS_ERRORCAPTION,
				IDS_CANTDBGFILE,
				lpcs->lpCreateParams,
				MB_OK | MB_ICONSTOP);
		}

	    // remove hourglass cursor
	    SetClassLong (hWnd, GCL_HCURSOR, (LONG)hOldCursor);
	    SetCursor (hOldCursor);
	    }
	    break;

	case WM_COMMAND:
	    {
	    HWND    hChild;

	    // send message to mdiclient to retrieve active child window handle
	    hChild = (HWND)SendMessage (GetWindow (hWnd, GW_CHILD), WM_MDIGETACTIVE, 0, 0);

	    switch (LOWORD (uParam))
		{
		case IDM_WINDOWTILE:
		    // tile MDI windows
		    SendMessage (GetWindow (hWnd, GW_CHILD),
				 WM_MDITILE,
				 MDITILE_VERTICAL,
				 0);
		    break;

		case IDM_WINDOWCASCADE:
		    // cascade MDI windows
		    SendMessage (GetWindow (hWnd, GW_CHILD),
				 WM_MDICASCADE,
				 MDITILE_SKIPDISABLED,
				 0);
		    break;

		case IDM_WINDOWARRANGE:
		    // arrange MDI icons
		    SendMessage (GetWindow (hWnd, GW_CHILD),
				 WM_MDIICONARRANGE,
				 0,
				 0);
		    break;

		case IDM_PROCESSEXIT:
		    SendMessage (hWnd, WM_CLOSE, 0, 0);
		    break;

		case IDM_PROCESSLOAD:
		    {
		    // allocate space for filename and path, init to null for common dialog
		    char    szFilePath[MAX_PATH] = "";

		    // call open file dialog to get filename of exe, and validate
		    if (GetFileName (hWnd, szFilePath))
			{
			if (!(IsValidFile (szFilePath) &&
			      CreateDebugSession (GetWindow (hWnd, GW_CHILD), szFilePath)))
			    NotifyUser (hWnd,
					IDS_ERRORCAPTION,
					IDS_CANTDBGFILE,
					szFilePath,
					MB_OK | MB_ICONSTOP);
			}
		    }
		    break;

		case IDM_PROCESSCLOSE:
		    SendMessage ((HWND)SendMessage (GetWindow (hWnd, GW_CHILD),
						    WM_MDIGETACTIVE, 0, 0),
				 WM_CLOSE, 0, 0);
		    break;

		default:
		    if (LOWORD (uParam) >= IDM_FIRSTCHILD)
			lRet = DefFrameProc (hWnd,
					     GetWindow (hWnd, GW_CHILD),
					     uMsg,
					     uParam,
					     lParam);

		    else if (IsWindow (hChild))
			SendMessage (hChild, uMsg, uParam, lParam);
		    break;
		}
	    }
	    break;

	case WM_CLOSE:
	case WM_QUERYENDSESSION:
	    {
	    HWND    hClient = GetWindow (hWnd, GW_CHILD);
	    HWND    hChild = (HWND)SendMessage (GetWindow (hWnd, GW_CHILD),
						WM_MDIGETACTIVE,
						0,
						0);

	    if (IsWindow (hChild))
		{
		if (NotifyUser (hWnd,
				IDS_CAPTION,
				IDS_EXITYESNO,
				NULL,
				MB_YESNO | MB_ICONQUESTION))
		    {
		    // hide the MDI client window to avoid multiple repaints
		    ShowWindow (hClient, SW_HIDE);

		    // As long as the MDI client has a child, destroy it
		    while (hChild = GetWindow (hClient, GW_CHILD))
			{
			// Skip the icon title windows
			while (hChild && GetWindow (hChild, GW_OWNER))
			    hChild = GetWindow (hChild, GW_HWNDNEXT);

			if (IsWindow (hChild))
			    SendMessage (hClient, WM_MDIDESTROY, (UINT)hChild, 0L);
			}
		    }
		else
		    // abort exit attemp
		    break;
		}

	    // destroy this window
	    DestroyWindow (hWnd);
	    }
	    break;

	case WM_DESTROY:
	    PostQuitMessage (0);
	    break;

	default:
	    // pass all unhandled messages to DefFrameProc for MDI processing
	    lRet = DefFrameProc (hWnd, GetWindow (hWnd, GW_CHILD), uMsg, uParam, lParam);
	    break;
	}

    // return 1 if handled message, 0 if not
    return lRet;
}



// start a debug window
BOOL WINAPI CreateDebugSession (
    HWND    hClient,
    char    *lpszTitle)
{
    MDICREATESTRUCT    mcs;
    char	       szDebug[MAX_PATH];

    LoadString (GetModuleHandle (NULL), IDS_DEBUGCLASS, szDebug, MAX_PATH);
    mcs.szClass = szDebug;
    mcs.szTitle = NULL;
    mcs.hOwner = GetModuleHandle (NULL);
    mcs.x = CW_USEDEFAULT;
    mcs.y = CW_USEDEFAULT;
    mcs.cx = CW_USEDEFAULT;
    mcs.cy = CW_USEDEFAULT;
    mcs.style = 0;
    mcs.lParam = (LPARAM)lpszTitle;

    // send a message to mdi to create the new debug window
    return (SendMessage (hClient, WM_MDICREATE, 0, (LONG)&mcs));
}




// validate filename as executable image
BOOL WINAPI IsValidFile (
    char    *lpszFilename)
{
    OFSTRUCT	of;
    int 	nLen;
    char	*pStr;

    // open the file for existance
    if (OpenFile (lpszFilename, &of, OF_EXIST) == -1)
	// fail validation
	return FALSE;

    // test the extension is .EXE
    nLen = strlen (lpszFilename);
    pStr = lpszFilename + nLen - 4;
    if (!stricmp (pStr, ".EXE"))
	// pass validation
	return TRUE;

    // fail validation
    return FALSE;
}




// initialize all menuitems
void WINAPI InitMenu (
    HWND    hWnd)
{
    HMENU	hMenu = GetMenu (hWnd);
    HWND	hChild =
		  (HWND)SendMessage (GetWindow (hWnd, GW_CHILD), WM_MDIGETACTIVE, 0, 0);
    LPHANDLE	hDbgEvent = (LPHANDLE)GetWindowLong (hChild, WXB_LPDBGEVENTS);
    HWND	hWndEdit;
    DWORD	dwSel;
    WORD	mfStatus;

    if (IsWindow (hChild))
	{
	hWndEdit = GetWindow (hChild, GW_CHILD);

	// enable menuitems CUT, COPY if selected text
	dwSel = SendMessage (hWndEdit, EM_GETSEL, 0, 0);
	mfStatus = (WORD)((LOWORD(dwSel) == HIWORD(dwSel))?MF_GRAYED:MF_ENABLED);
	EnableMenuItem (hMenu, IDM_EDITCUT, mfStatus);
	EnableMenuItem (hMenu, IDM_EDITCOPY, mfStatus);

	// if text allow for new file, enable menuitem
	if (SendMessage (hWndEdit, WM_GETTEXTLENGTH, 0, 0))
	    {
	    EnableMenuItem (hMenu, IDM_EDITSAVEAS, MF_ENABLED);
	    EnableMenuItem (hMenu, IDM_EDITCLEAR, MF_ENABLED);
	    }
	else
	    {
	    EnableMenuItem (hMenu, IDM_EDITSAVEAS, MF_GRAYED);
	    EnableMenuItem (hMenu, IDM_EDITCLEAR, MF_GRAYED);
	    }

	// if CF_TEXT format data is available in clipboard allow paste
	if (OpenClipboard (hWnd) & IsClipboardFormatAvailable (CF_TEXT))
	    EnableMenuItem (hMenu, IDM_EDITPASTE, MF_ENABLED);
	else
	    EnableMenuItem (hMenu, IDM_EDITPASTE, MF_GRAYED);
	CloseClipboard ();

	// enable close if loaded
	EnableMenuItem (hMenu, IDM_PROCESSCLOSE, MF_ENABLED);

	// if debugger is inactive
	if (WaitForSingleObject (hDbgEvent[DEBUGACTIVE], 1) == WAIT_TIMEOUT)
	    {
	    EnableMenuItem (hMenu, IDM_PROCESSSTART, MF_ENABLED);
	    EnableMenuItem (hMenu, IDM_PROCESSSTOP, MF_GRAYED);
	    }

	else
	    {
	    EnableMenuItem (hMenu, IDM_PROCESSSTART, MF_GRAYED);
	    EnableMenuItem (hMenu, IDM_PROCESSSTOP, MF_ENABLED);
	    }

	// allow priority if loaded
	EnableMenuItem (hMenu, IDM_PROCESSPRIORITIES, MF_ENABLED);

	// allow views when loaded
	EnableMenuItem (hMenu, IDM_VIEWPROCESS, MF_ENABLED);
	EnableMenuItem (hMenu, IDM_VIEWTHREAD, MF_GRAYED);
	}

    else
	{
	EnableMenuItem (hMenu, IDM_PROCESSCLOSE, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_PROCESSSTART, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_PROCESSSTOP, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_PROCESSPRIORITIES, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_VIEWPROCESS, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_VIEWTHREAD, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_EDITCUT, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_EDITCOPY, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_EDITPASTE, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_EDITCLEAR, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_EDITSAVEAS, MF_GRAYED);
	}

	EnableMenuItem (hMenu, IDM_HELPCONTENTS, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_HELPSEARCH, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_HELPONHELP, MF_GRAYED);
	EnableMenuItem (hMenu, IDM_HELPABOUT, MF_GRAYED);
}



// get win32 command line parameters
BOOL WINAPI GetCmdLine(
    char    *lpStr,
    char    *lpszCmdLine,
    BOOL    *bBkgnd)
{
    if (*lpStr)
	{
	// skip application name which precedes parameters
	while (*lpStr != ' ' && *lpStr != 0)
	    lpStr++;

	// skip spaces
	while (*lpStr == ' ' && *lpStr != 0)
	    lpStr++;

	// indeed command line parameter(s) present
	if (*lpStr != 0)
	    {
	    // if background switch, set flag and remove switch from command line
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
	    // maybe switch is embedded in parameter(s) somewhere
	    else
		{
		char	*pStr = lpStr;
		char	*pCmdLine = lpszCmdLine;
		int	i, nCnt;

		while (*pStr != 0)
		    {
		    // background switch is set, so prepare parameters and set flag
		    if ((*pStr == '/' || *pStr == '-') &&
			(*(pStr+1) == 'b' || *(pStr+1) == 'B'))
			{
			*bBkgnd = TRUE;

			// copy from beg. of lpStr to *pStr to lpszCmdLine
			nCnt = pStr - lpStr;
			for (i=0; i<nCnt; i++)
			    lpszCmdLine[i] = lpStr[i];
			lpszCmdLine[i] = 0;
			strcat (lpszCmdLine, (pStr+2));

			// break from loop
			break;
			}

		    pStr++;
		    }

		// no switch found, can only edit one file, remove extra parameters
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



// main window procedure
LONG WINAPI DebugWndProc (
    HWND    hWnd,
    UINT    uMsg,
    UINT    uParam,
    LONG    lParam)
{
    LONG	lRet = 1;

    switch (uMsg)
	{
	case WM_CREATE:
	    {
	    char	  *lpFilePath =
		(char *)((LPMDICREATESTRUCT)((LPCREATESTRUCT)lParam)->lpCreateParams)->lParam;
	    char	  szFilename[MAX_PATH];
	    HCURSOR	  hOldCursor;
	    DBGPROCESS	  *lpDbgProcess;
	    LPHANDLE	  lpDbgEvents;
	    RECT	  rc;
	    HWND	  hWndEdit;

	    // put hourglass cursor up
	    hOldCursor = (HCURSOR)SetClassLong (hWnd, GCL_HCURSOR, 0);
	    SetCursor (LoadCursor (0, IDC_WAIT));

	    // set window caption to application filename
	    GetFileFromPath (lpFilePath, szFilename);
	    SetWindowText (hWnd, szFilename);

	    // create edit window in client area
	    GetClientRect (hWnd, &rc);
	    hWndEdit = CreateWindow ("edit",
				     "",
				     WS_CHILD | WS_VISIBLE | DS_LOCALEDIT | WS_VSCROLL |
					 ES_AUTOHSCROLL | ES_AUTOVSCROLL |
					 ES_MULTILINE | ES_NOHIDESEL,
				     rc.left,
				     rc.top,
				     rc.right-rc.left,
				     rc.bottom-rc.top,
				     hWnd,
				     (HMENU)IDC_EDIT,
				     (HANDLE)GetModuleHandle (NULL),
				     0);

	    // allocate memory for debug events handle array
	    lpDbgEvents = (LPHANDLE)GlobalLock (GlobalAlloc (GMEM_MOVEABLE,
							     sizeof (HANDLE) * nDEBUGEVENTS));

	    // start debug thread for this process
	    if (!(lpDbgProcess = StartDebugger (lpFilePath, lpDbgEvents)))
		return FALSE;

	    // store window handle in process information for use by debugger thread
	    lpDbgProcess->hWnd = hWnd;

	    // store debug process information in window extra bytes
	    SetWindowLong (hWnd, WXB_LPDBGPROCESS, (LONG)lpDbgProcess);
	    SetWindowLong (hWnd, WXB_LPDBGEVENTS, (LONG)lpDbgEvents);

	    // remove hourglass cursor
	    SetClassLong (hWnd, GCL_HCURSOR, (LONG)hOldCursor);
	    SetCursor (hOldCursor);
	    }
	    break;

	case WM_COMMAND:
	    {
	    LPHANDLE	hDbgEvent = (LPHANDLE)GetWindowLong (hWnd, WXB_LPDBGEVENTS);

	    switch (LOWORD (uParam))
		{
		case IDM_PROCESSSTART:
		    {
		    int    nErr;
		    char   Buff[10];

		    // set DEBUGACTIVE event
		    if (!SetEvent (hDbgEvent[RESUMEDEBUGGER]))
			{
			nErr = GetLastError ();
			MessageBox (hWnd, "SetEvent failed", itoa (nErr, Buff, 10), MB_OK);
			}
		    }
		    break;

		case IDM_PROCESSSTOP:
		    {
		    int    nErr;
		    char   Buff[10];

		    // reset DEBUGACTIVE event
		    if (!SetEvent (hDbgEvent[SUSPENDDEBUGGER]))
			{
			nErr = GetLastError ();
			MessageBox (hWnd, "SetEvent failed", itoa (nErr, Buff, 10), MB_OK);
			}
		    }
		    break;

		case IDM_PROCESSPRIORITIES:
		    {
		    DBGTHREAD	  *lpDbgThread,
				  *lpDbgNewThread;
		    DBGPROCESS	  *lpDbgProcess =
					(DBGPROCESS *)GetWindowLong (hWnd, WXB_LPDBGPROCESS);
		    DBGPROCESS	  *lpDbgNewProcess;
		    int 	  nErr;
		    char	  Buff[10];

		    if (!SetEvent (hDbgEvent[SUSPENDDEBUGGER]))
			{
			nErr = GetLastError ();
			MessageBox (hWnd,
				    "SetEvent failed on SUSPENDDEBUGGER, error = ",
				    itoa (nErr, Buff, 10),
				    MB_OK);
			break;
			}

		    /* copy debug process data set */
		    if (DuplicateDebugData (lpDbgProcess, &lpDbgNewProcess))
			{
			if (DialogBoxParam (GetModuleHandle (NULL),
					    MAKEINTRESOURCE (IDR_DEBUGDIALOG),
					    hWnd,
					    PriorityDlgProc,
					    (LPARAM)lpDbgNewProcess))
			    {
			    if (!SetEvent (hDbgEvent[RESUMEDEBUGGER]))
				{
				nErr = GetLastError ();
				MessageBox (hWnd,
					    "SetEvent failed on RESUMEDEBUGGER, error = ",
					    itoa (nErr, Buff, 10),
					    MB_OK);
				}

			    /* reset process based on new process data */
			    SetPriorityClass (lpDbgNewProcess->hProcess,
					      lpDbgNewProcess->dwPriority);
			    lpDbgProcess->dwPriority = lpDbgNewProcess->dwPriority;

			    /* set each thread priority and state */
			    lpDbgThread = (DBGTHREAD *)lpDbgProcess->lpThreads;
			    lpDbgNewThread = (DBGTHREAD *)lpDbgNewProcess->lpThreads;
			    while (lpDbgThread)
				{
				SetThreadPriority (lpDbgThread->hThread,
						   lpDbgNewThread->nPriority);
				lpDbgThread->nPriority = lpDbgNewThread->nPriority;
				lpDbgThread->bfActive = lpDbgNewThread->bfActive;
				if (lpDbgThread->bfActive)
				    while (ResumeThread (lpDbgThread->hThread) > 1);
				else
				    SuspendThread (lpDbgThread->hThread);

				lpDbgThread = (DBGTHREAD *)lpDbgThread->Next;
				lpDbgNewThread = (DBGTHREAD *)lpDbgNewThread->Next;
				}
			    }
			else
			    {
			    if (!SetEvent (hDbgEvent[RESUMEDEBUGGER]))
				{
				nErr = GetLastError ();
				MessageBox (hWnd,
					    "SetEvent failed on RESUMEDEBUGGER, error = ",
					    itoa (nErr, Buff, 10),
					    MB_OK);
				}
			    }

			/* free new data set */
			FreeDebugData (lpDbgNewProcess);
			}

		    else
			if (!SetEvent (hDbgEvent[RESUMEDEBUGGER]))
			    {
			    nErr = GetLastError ();
			    MessageBox (hWnd,
					"SetEvent failed on RESUMEDEBUGGER, error = ",
					itoa (nErr, Buff, 10),
					MB_OK);
			    }
		    }
		    break;

		case IDM_EDITCUT:
		case IDM_EDITCOPY:
		    {
		    HLOCAL    hEditData, hData;
		    char      *lpEditData, *lpData;
		    DWORD     BegSel, EndSel;
		    HWND      hWndEdit = GetWindow (hWnd, GW_CHILD);

		    // get current selection
		    SendMessage (hWndEdit, EM_GETSEL, (UINT)&BegSel, (UINT)&EndSel);
		    hEditData = (HLOCAL)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0);
		    lpEditData = LocalLock (hEditData);

		    // allocate buffer to hold cipboard data
		    hData = LocalAlloc (LHND, EndSel-BegSel+1);
		    lpData = LocalLock (hData);
		    strncpy (lpData, lpEditData+BegSel, EndSel-BegSel);
		    lpData[EndSel-BegSel] = 0;

		    // copy data to clipboard
		    OpenClipboard (hWnd);
		    SetClipboardData (CF_TEXT, lpData);
		    CloseClipboard ();

		    // unlock memory and free
		    LocalUnlock (hEditData);
		    LocalUnlock (hData);
		    LocalFree (hData);
		    }

		    // if cutting, remove text
		    if (uParam == IDM_EDITCUT)
			// replace selection with null
			SendMessage (GetWindow (hWnd, GW_CHILD), EM_REPLACESEL, 0, (UINT)"");
		    break;

		case IDM_EDITCLEAR:
		    SetWindowText (GetWindow (hWnd, GW_CHILD), "");
		    break;

		case IDM_EDITPASTE:
		    SendMessage (GetWindow (hWnd, GW_CHILD), uParam, 0, 0);
		    break;

		case IDM_EDITSAVEAS:
		    SaveFile (hWnd);
		    break;

		case IDC_EDIT:
		    break;

		case IDM_VIEWPROCESS:
		    {
		    LPVOID			lpMem = 0;
		    MEMORY_BASIC_INFORMATION	pmemBuff;
		    char			szText[MAX_PATH];
		    char			szNum[20];
		    int 			nErr;
		    int 			nCnt = 0;
		    HCURSOR			hOldCursor;
		    DBGPROCESS			*lpDbgProcess =
			    (DBGPROCESS *)GetWindowLong (hWnd, WXB_LPDBGPROCESS);

		    if (!SetEvent (hDbgEvent[SUSPENDDEBUGGER]))
			{
			nErr = GetLastError ();
			MessageBox (hWnd,
				    "SetEvent failed on SUSPENDDEBUGGER, error = ",
				    itoa (nErr, szNum, 10),
				    MB_OK);
			break;
			}

		    /* put wait cursor up */
		    hOldCursor = (HCURSOR)SetClassLong (hWnd, GCL_HCURSOR, 0);
		    SetCursor (LoadCursor (0, IDC_WAIT));

		    strcpy (szText, "Process memory statistics\r\n");
		    AppendEditText (lpDbgProcess->hWnd, 0, szText);

		    /* scan entire process for contiguous blocks of memory */
		    while ((DWORD)lpMem < 0x7fff0000)
			{
			VirtualQueryEx (lpDbgProcess->hProcess,
					lpMem,
					&pmemBuff,
					sizeof (pmemBuff));

			strcpy (szText, "Base:");
			strcat (szText, itoa ((int)pmemBuff.AllocationBase, szNum, 10));
			strcat (szText, ", \tProt:");
			strcat (szText, itoa (pmemBuff.AllocationProtect, szNum, 10));
			strcat (szText, ", \tAddr:");
			strcat (szText, itoa ((int)pmemBuff.BaseAddress, szNum, 10));
			strcat (szText, ", \t");
			strcat (szText, itoa (pmemBuff.RegionSize, szNum, 10));
			strcat (szText, " bytes, \tState:");
			strcat (szText, itoa (pmemBuff.State, szNum, 10));
			strcat (szText, ", \tProt:");
			strcat (szText, itoa (pmemBuff.Protect, szNum, 10));
			strcat (szText, ", \tType:");
			strcat (szText, itoa (pmemBuff.Type, szNum, 10));
			strcat (szText, "\r\n");
			AppendEditText (lpDbgProcess->hWnd, 0, szText);

			/* increment lpMem to next region of memory */
			lpMem = (LPVOID)((DWORD)pmemBuff.BaseAddress +
					 (DWORD)pmemBuff.RegionSize);
			}

		    /* replace wait cursor with old cursor */
		    SetClassLong (hWnd, GCL_HCURSOR, (LONG)hOldCursor);
		    SetCursor (hOldCursor);

		    if (!SetEvent (hDbgEvent[RESUMEDEBUGGER]))
			{
			nErr = GetLastError ();
			MessageBox (hWnd,
				    "SetEvent failed on RESUMEDEBUGGER, error = ",
				    itoa (nErr, szNum, 10),
				    MB_OK);
			break;
			}
		    }
		    break;

		case IDM_VIEWTHREAD:
		default:
		    NotifyUser (hWnd, IDS_ERRORCAPTION, IDS_UNAVAILABLE, 0, MB_OK);
		    break;
		}
	    }
	    break;

	case WM_SIZE:
	    {
	    RECT    rc;

	    // resize the edit control to match the client area
	    GetClientRect (hWnd, &rc);
	    MoveWindow (GetWindow (hWnd, GW_CHILD),
			rc.left,
			rc.top,
			rc.right-rc.left,
			rc.bottom-rc.top,
			TRUE);
	    }
	    break;

	case WM_SETFOCUS:
	    SetFocus (GetWindow (hWnd, GW_CHILD));
	    break;

	case WM_CLOSE:
	    {
	    HANDLE    hOldCursor;
	    HANDLE    hMem = GlobalHandle ((LPSTR)GetWindowLong (hWnd, WXB_LPDBGEVENTS));
	    char      szSave[MAX_PATH];
	    char      szTitle[MAX_PATH];
	    DBGPROCESS	  *lpDbgProcess = (DBGPROCESS *)GetWindowLong (hWnd, WXB_LPDBGPROCESS);

	    if (lpDbgProcess)
		{
		// put hourglass cursor up
		hOldCursor = (HCURSOR)SetClassLong (hWnd, GCL_HCURSOR, 0);
		SetCursor (LoadCursor (0, IDC_WAIT));

		// inform debugger thread of termination
		CloseDebugger (lpDbgProcess, (LPHANDLE)GetWindowLong (hWnd, WXB_LPDBGEVENTS));

		// release debug events handle
		GlobalUnlock (hMem);
		GlobalFree (hMem);

		// remove hourglass cursor
		SetClassLong (hWnd, GCL_HCURSOR, (LONG)hOldCursor);
		SetCursor (hOldCursor);
		}

	    // inquire to save content before exiting
	    GetWindowText (hWnd, szTitle, MAX_PATH);
	    LoadString (GetModuleHandle (NULL), IDS_SAVEFILE, szSave, MAX_PATH);
	    switch (MessageBox (hWnd, szSave, szTitle, MB_YESNOCANCEL | MB_ICONQUESTION))
		{
		case IDYES:
		    SaveFile (hWnd);
		    break;

		case IDCANCEL:
		    SetWindowLong (hWnd, WXB_LPDBGPROCESS, 0);
		    goto ret;
		    break;
		}

	    // send message to MDI to destroy this window
	    SendMessage (GetParent (hWnd), WM_MDIDESTROY, (UINT)hWnd, 0);
	    }
	    break;

	default:
	    // pass all unhandled messages to DefWindowProc
	    lRet = DefMDIChildProc (hWnd, uMsg, uParam, lParam);
	    break;
	}
ret:
    // return 1 if handled message, 0 if not
    return lRet;
}



// generic message notification
int WINAPI NotifyUser (
    HWND    hWndParent,
    int     IDS_TITLE,
    int     IDS_ERROR,
    char    *lpszAppend,
    UINT    uFlags)
{
    char    szError[MAX_PATH*2];
    char    szTitle[MAX_PATH];

    LoadString (GetModuleHandle (NULL), IDS_TITLE, szTitle, MAX_PATH);
    LoadString (GetModuleHandle (NULL), IDS_ERROR, szError, MAX_PATH);

    if (lpszAppend != NULL && *lpszAppend != 0)
	strcat (szError, lpszAppend);

    if (!uFlags)
	uFlags = MB_OK;

    // return response to message box
    return (MessageBox (hWndParent, szError, szTitle, uFlags));
}



void WINAPI AppendEditText (
    HWND    hWnd,
    UINT    idString,
    char    *lpszString)
{
    HLOCAL    hEditData, hData;
    char      *lpEditData;
    char      szString[MAX_PATH];
    HWND      hWndEdit;


    // make sure hWnd is valid
    if (IsWindow (hWnd))
	hWndEdit = GetWindow (hWnd, GW_CHILD);
    else
	return;

    if (idString)
	// load edit string from resource table
	LoadString (GetModuleHandle (NULL), idString, szString, MAX_PATH);
    else if (lpszString)
	strcpy (szString, lpszString);

    // concatenate new string to existing edit control data
    hEditData = (HLOCAL)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0);
    hData = LocalReAlloc (hEditData,
			  LocalSize (hEditData) + strlen (szString),
			  LMEM_MOVEABLE);

    // if valid reallocation, append new data
    if (hData)
	{
	lpEditData = LocalLock (hData);
	strcat (lpEditData, szString);
	LocalUnlock (hData);
	SendMessage (hWndEdit, EM_SETHANDLE, (UINT)hData, 0);
	}
}
