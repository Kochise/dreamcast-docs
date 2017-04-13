/*
 *  utils.c
 *  
 *  Purpose:
 *      generic utils
 *  
 *  Owner:
 *      MikeSart
 */
#define UNICODE 1

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <time.h>
#include <lm.h>
#include "netwatch.h"
#include "rcids.h"

ASSERTDATA

/*
 *	General treeview routines
 */

/*
 *	FTreeView_GetString
 *
 *	Purpose:
 *		Get the text from a treeview
 *
 *	Arguments:
 *		hItem, szText, and cchText
 *
 *	Returns:
 *		TRUE - success, FALSE - failure
 */
BOOL
FTreeView_GetString(HWND hwndTV, HTREEITEM hItem, TCHAR *szText, UINT cchTextMax)
{
	TV_ITEM	tvItem;

	Assert(IsWindow(hwndTV) && hItem);
	tvItem.mask = TVIF_TEXT;
	tvItem.hItem = hItem;
	tvItem.pszText = szText;
	tvItem.cchTextMax = cchTextMax;
	return TreeView_GetItem(hwndTV, &tvItem);
}

/*
 *	TreeView_GetRootCount
 *
 *	Purpose:
 *		Count the number of roots (computers)
 *
 *	Arguments:
 *		hwndTV
 *
 *	Returns:
 *		a number
 */
UINT
TreeView_GetRootCount(HWND hwndTV)
{
	HTREEITEM	hItem;
	UINT		cRoots = 0;

	Assert(IsWindow(hwndTV));
	hItem = TreeView_GetRoot(hwndTV);
	while(hItem)
	{
		cRoots++;
		hItem = TreeView_GetNextSibling(hwndTV, hItem);
	}

	OutputDbgStr("TreeView_GetRootCount: %ld", cRoots);
	return cRoots;
}

/*
 *	TreeView_GetRootList
 *
 *	Purpose:
 *		Construct a REG_MULTI_SZ of roots
 *
 *	Arguments:
 *		hwndTV, pcb
 *
 *	Returns:
 *		TCHAR * to your new MULTI_SZ - be sure to free it
 */
LPTSTR
TreeView_GetRootList(HWND hwndTV, DWORD *pcb)
{
	LPTSTR			pszT;
	HTREEITEM		hItem;
	LPTSTR			pszRootList;

	// Alloc enough for all the servers
	Assert(IsWindow(hwndTV));
	*pcb = (TreeView_GetRootCount(hwndTV) * (UNCLEN + 1) + 1) * sizeof(TCHAR);
	pszRootList = GlobalAllocPtr(GHND, *pcb);
	if(pszT = pszRootList)
	{
		hItem = TreeView_GetRoot(hwndTV);
		while(hItem)
		{
			TV_ITEM	tvItem;
			TCHAR	szT[UNCLEN + 1];

			// If we retrieved the text, save it
			tvItem.mask = TVIF_TEXT | TVIF_IMAGE;
			tvItem.hItem = hItem;
			tvItem.pszText = szT;
			tvItem.cchTextMax = UNCLEN + 1;
			if(TreeView_GetItem(hwndTV, &tvItem) && (szT[0] == '\\'))
			{
				// mark the first char as the image type
				szT[0] = tvItem.iImage + '0';
				// Make a REG_MULTI_SZ out of this stuff
				OutputDbgStr("Roots: '%ls'", szT);
				lstrcat(pszT, szT);
				pszT += lstrlen(szT) + 1;
			}

			hItem = TreeView_GetNextSibling(hwndTV, hItem);
		}
	}

	return pszRootList;
}

/*
 *	GetComputerImage
 *
 *	Purpose:
 *		Check the validity of a server the user is trying to add.
 *
 *	Arguments:
 *		hwnd, szServerName
 *
 *	Returns:
 *		-1 err, BMP_COMPUTER cool, BMP_COMPUTERLIMITED limited access
 */
int
GetComputerImage(HWND hwnd, TCHAR *szServerName)
{
	NET_API_STATUS	nas;
	TCHAR			chT;
	HCURSOR			hCursor;
	INT				iImage = -1;
	SHARE_INFO_2	*shi2 = NULL;
	DWORD			dwentriesread;
	DWORD			dwtotalentries;
	TCHAR			szMsg[cchErrMax];
	TCHAR			*szErrMessage = NULL;

	Assert(hwnd);

	// When we write stuff to the registry, we set the first char to be the
	// image type.
	if((chT = szServerName[0]) != '\\')
		szServerName[0] = '\\';

	// This may take a while
	hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

	CharUpper(szServerName);
	nas = NetShareEnum(szServerName, 2, (LPBYTE *)&shi2,
		MAX_PREFERRED_LENGTH, &dwentriesread, &dwtotalentries, NULL);
	OutputDbgStr("GetComputerImage: nas = 0x%08lx", nas);

	SetCursor(hCursor);
	switch(nas)
	{
		case ERROR_SUCCESS:
			iImage = BMP_COMPUTER;
			break;
		case ERROR_ACCESS_DENIED:
			wsprintf(szMsg, szFromIDS1(IDS_ERRACCESS), szServerName);
			// If iImage is already BMP_COMPUTERLIMITED, then we must have
			// restored this from the registry so don't ask the user again.
			if((chT == ('0' + BMP_COMPUTERLIMITED)) ||
				MessageBox(hwnd, szMsg, szAppName,
				MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
					iImage = BMP_COMPUTERLIMITED;
			break;
		default:
			Assert(iImage == -1);
			wsprintf(szMsg, szFromIDS1(IDS_ERRADDCOMPUTER), szServerName);
			if(szErrMessage = GetSystemErrMessage(nas))
				lstrcat(szMsg, szErrMessage);
			MessageBox(hwnd, szMsg, szAppName, MB_ICONEXCLAMATION | MB_OK);
			break;
	}

	GlobalFreeNullPtr(szErrMessage);
	NetApiBufferFree(shi2);
	return iImage;
}

/*
 *	hAddComputer
 *
 *	Purpose:
 *		Add a new computer to the hwndTV
 *
 *	Arguments:
 *		computername to add
 *
 *	Returns:
 *		hItem of existing or new rooted computername
 */
HTREEITEM
hAddComputer(HWND hwnd, HWND hwndTV, LPTSTR szComputerName,
	HTREEITEM hItemLocation)
{
	TV_INSERTSTRUCT	tvis;
	HTREEITEM		hItem;

	OutputDbgStr("hAddComputer: '%ls'", szComputerName);

	Assert(IsWindow(hwndTV));
	// Check to see if the name already exists
	hItem = TreeView_GetRoot(hwndTV);
	while(hItem)
	{
		TCHAR		szT[UNCLEN + 1];

		if(FTreeView_GetString(hwndTV, hItem, szT, UNCLEN + 1) &&
			!lstrcmpi(szComputerName, szT))
		{
			// Oooh - found one
			OutputDbgStr("'%ls' already there", szComputerName);
			TreeView_SelectItem(hwndTV, hItem);
			return hItem;
		}

		hItem = TreeView_GetNextSibling(hwndTV, hItem);
	}

	// Not found - add it
	// Check for access, computer existance, etc. here.
	tvis.item.iImage = tvis.item.iSelectedImage =
		GetComputerImage(hwnd, szComputerName);
	if(tvis.item.iImage == -1)
		return NULL;

	tvis.hParent = NULL;
	tvis.hInsertAfter = hItemLocation;
	tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvis.item.pszText = szComputerName;

	if(hItem = TreeView_InsertItem(hwndTV, &tvis))
		TreeView_SelectItem(hwndTV, hItem);
	return hItem;
}

/*
 *	RestoreServerList
 *
 *	Purpose:
 *		add initial servers to tv via command line, registry, local computer
 *
 *	Arguments:
 *		hwnd, hwndTV, REG_MULTI_SZ pszServers
 *
 *	Returns:
 *		nada
 */
VOID
RestoreServerList(HWND hwnd, HWND hwndTV, TCHAR *pszServers)
{
	DWORD		nT;
	INT			argc;
	LPTSTR		pszT;
	HTREEITEM	hItem;
	TCHAR		**argv;
	BOOL		fSuccess = FALSE;
	TCHAR		szComputerName[UNCLEN + 1];

	szComputerName[0] = szComputerName[1] = '\\';

	// Handle command line
	argv = CommandLineToArgvW(GetCommandLine(), &argc);
	while(argc-- > 1)
	{
		if(lstrlen(argv[argc]) > UNCLEN)
			argv[argc][UNCLEN] = 0;

		nT = ((argv[argc][0] == '\\') && (argv[argc][1] == '\\')) ? 0 : 2;
		lstrcpy(&szComputerName[nT], argv[argc]);
		CharUpper(szComputerName);
		if(hAddComputer(hwnd, hwndTV, szComputerName, TVI_FIRST))
			fSuccess = TRUE;
	}

	if(!fSuccess && pszServers)
	{
		// Loop through all these SZs adding em
		for(pszT = pszServers; *pszT; pszT += lstrlen(pszT) + 1)
		{
			if(hAddComputer(hwnd, hwndTV, pszT, TVI_LAST))
				fSuccess = TRUE;
			OutputDbgStr("Restoring '%ls'", pszT);
		}
	}

	// If we didn't get any servers yet, just default to this computer
	if(!fSuccess)
	{
		nT = UNCLEN - 1;
		Assert((szComputerName[0] == '\\') && (szComputerName[1] == '\\'));
		if(GetComputerName(&szComputerName[2], &nT))
			hAddComputer(hwnd, hwndTV, szComputerName, TVI_FIRST);
	}

	// Select the first item
	if(hItem = TreeView_GetRoot(hwndTV))
		TreeView_SelectItem(hwndTV, hItem);
}

/*
 *	RestoreWindowPosition
 *
 *	Purpose:
 *		Nostalgia
 *
 *	Arguments:
 *		hwnd to nostalge
 *
 *	Returns:
 *		zipola
 */
VOID
RestoreWindowPosition(HWND hwnd, HWND hwndTV)
{
	DWORD			cb;
	WINDOWPLACEMENT	wndpl;
	DWORD			fHideTitle;
	HKEY			hkey = NULL;
	DWORD			dwTopMost = 0;
	TCHAR			*pszServers = NULL;

	wndpl.showCmd = SW_SHOWNORMAL;
	if(RegOpenKeyEx(HKEY_CURRENT_USER, szFromIDS1(IDS_KEY), 0, KEY_READ, &hkey))
		goto err;

	cb = sizeof(fHideTitle);
	if(!RegQueryValueEx(hkey, szFromIDS1(IDS_HIDETITLE), 0, 0,
		(LPBYTE)&fHideTitle, &cb) && fHideTitle)
			ShowTitle(hwnd, SW_HIDE);

	cb = COUNT_CHECKMENUS * sizeof(unMenuFlags[0]);
	if(!RegQueryValueEx(hkey, szFromIDS1(IDS_MENUFLAGS), 0, 0,
		(LPBYTE)unMenuFlags, &cb))
	{
		for(cb = 0; cb < COUNT_CHECKMENUS; cb++)
		{
			CheckMenuItem(ghMenu, CHECKMENUSTART + cb,
				MF_BYCOMMAND | unMenuFlags[cb]);
		}
	}

	cb = sizeof(wndpl);
	if(!RegQueryValueEx(hkey, szFromIDS1(IDS_PLACEMENT), 0, 0,
		(LPBYTE)&wndpl, &cb))
	{
		if(wndpl.length == sizeof(wndpl))
			SetWindowPlacement(hwnd, &wndpl);
	}

	cb = sizeof(dwTimerInterval);
	RegQueryValueEx(hkey, szFromIDS1(IDS_TIMERINTERVAL), 0, 0,
		(LPBYTE)&dwTimerInterval, &cb);

	if(!RegQueryValueEx(hkey, szFromIDS1(IDS_TOPMOST), 0, 0,
		(LPBYTE)&dwTopMost, &cb) && cb && dwTopMost)
	{
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		CheckMenuItem(ghMenu, IDM_TOPMOST, MF_BYCOMMAND | MF_CHECKED);
	}

	// Get the size of the servers and any we had store away.
	cb = TreeView_GetCount(hwndTV);
	if(!cb && !RegQueryValueEx(hkey, szFromIDS1(IDS_SERVERS), 0, 0, NULL, &cb))
	{
		if(cb && (pszServers = GlobalAllocPtr(GHND, cb)))
			RegQueryValueEx(hkey, szFromIDS1(IDS_SERVERS), 0, 0,
				(LPBYTE)pszServers, &cb);
	}

	CloseHandle(hkey);

err:
	ShowWindow(hwnd, wndpl.showCmd);

	if(dwTimerInterval < 1000)
		dwTimerInterval = 1000;

	RestoreServerList(hwnd, hwndTV, pszServers);
	GlobalFreeNullPtr(pszServers);
}

/*
 *	SaveWindowPosition
 *
 *	Purpose:
 *		Put all our eggs in one basket
 *
 *	Arguments:
 *		hwnd of basket
 *
 *	Returns:
 *		zipster
 */
VOID
SaveWindowPosition(HWND hwnd, HWND hwndTV)
{
	DWORD			cb;
	WINDOWPLACEMENT	wndpl;
	HKEY			hkey;
	DWORD			dwTopMost;
	DWORD			fHideTitle;
	LPTSTR			pszRootList;

	Assert(IsWindow(hwndTV));
	wndpl.length = sizeof(wndpl);
	GetWindowPlacement(hwnd, &wndpl);
	// for some reason, GetWindowPlacement resets the length part??
	wndpl.length = sizeof(wndpl);

	if(!RegCreateKeyEx(HKEY_CURRENT_USER, szFromIDS1(IDS_KEY), 0, szFromIDS1(IDS_KEY), 0,
		KEY_READ | KEY_WRITE, 0, &hkey, NULL))
	{
		// Save away the list of computer names
		if(pszRootList = TreeView_GetRootList(hwndTV, &cb))
		{
			RegSetValueEx(hkey, szFromIDS1(IDS_SERVERS), 0, REG_MULTI_SZ,
				(LPBYTE)pszRootList, cb);
			GlobalFreePtr(pszRootList);
		}

		RegSetValueEx(hkey, szFromIDS1(IDS_PLACEMENT), 0, REG_BINARY,
			(LPBYTE)&wndpl, sizeof(wndpl));

		RegSetValueEx(hkey, szFromIDS1(IDS_MENUFLAGS), 0, REG_BINARY,
			(LPBYTE)unMenuFlags, COUNT_CHECKMENUS * sizeof(unMenuFlags[0]));

		RegSetValueEx(hkey, szFromIDS1(IDS_TIMERINTERVAL), 0, REG_DWORD,
			(LPBYTE)&dwTimerInterval, sizeof(dwTimerInterval));

		fHideTitle = GetMenu(hwnd) ? 0 : 1;
		RegSetValueEx(hkey, szFromIDS1(IDS_HIDETITLE), 0, REG_DWORD,
			(LPBYTE)&fHideTitle, sizeof(fHideTitle));

		dwTopMost = GetMenuState(ghMenu, IDM_TOPMOST, MF_BYCOMMAND) & MF_CHECKED;
		RegSetValueEx(hkey, szFromIDS1(IDS_TOPMOST), 0, REG_DWORD,
			(LPBYTE)&dwTopMost, sizeof(dwTopMost));

		CloseHandle(hkey);
	}
}

/*
 *	szFromIDS1
 *
 *	Purpose:
 *		LoadString and ids and keep it in a static buffer
 *
 *	Arguments:
 *		ids to load
 *
 *	Returns:
 *		TCHAR * to the static buffer
 */
TCHAR *
szFromIDS1(UINT unID)
{
#define cchMaxIDS		200
	static TCHAR szBuf1[cchMaxIDS];

	szBuf1[0] = '\0';
	SideAssert(LoadString(ghInst, unID, szBuf1, cchMaxIDS));
	return szBuf1;
}

/*
 *	AllocAndLoadString
 *
 *	Purpose:
 *		Alloc enough room to load an IDS
 *
 *	Arguments:
 *		ids to return
 *
 *	Returns:
 *		TCHAR *
 */
TCHAR *
AllocAndLoadString(UINT unID)
{
	TCHAR	*sz;
	TCHAR	*szT = szFromIDS1(unID);

	sz = GlobalAllocPtr(GHND, (lstrlen(szT) + 1) * sizeof(TCHAR));
	if(sz)
		lstrcpy(sz, szT);

	return sz;
}    

/*
 *	GetSystemErrMessage
 *
 *	Purpose:
 *		Format an error message string
 *
 *	Arguments:
 *		dwError
 *
 *	Returns:
 *		a TCHAR * that you must free
 */
TCHAR *
GetSystemErrMessage(DWORD dwError)
{
	LPTSTR  szErrMessage = NULL;
	HMODULE hLibrary;

	if(dwError == ERROR_INVALID_LEVEL)
	{
		// This err usually occurs when we try to view a WFW machine.
		// So, the PM decided to use our own version of the err msg.
		szErrMessage = AllocAndLoadString(IDS_ERRWFW);
	} 
	else if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, dwError, 0, (LPTSTR)&szErrMessage, 0, NULL))
	{
		szErrMessage[lstrlen(szErrMessage) - 2] = '\0'; // remove /r/n
	}
	else if(hLibrary = LoadLibrary(MESSAGE_FILENAME))
	{
		if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE,
			(LPVOID)hLibrary, dwError, 0, (LPTSTR)&szErrMessage, 0, NULL))
		{
			szErrMessage[lstrlen(szErrMessage) - 2] = '\0'; // remove /r/n
		}
		FreeLibrary(hLibrary);
	}

	return szErrMessage;
}

/*
 *	PunchTimer
 *
 *	Purpose:
 *		turn on\off timer
 *
 *	Arguments:
 *		TRUE: turn on timer
 *		FALSE: turn it off
 *
 *	Returns:
 *		nada
 */
VOID
PunchTimer(HWND hwndMain, BOOL fNewState)
{
	static BOOL fCurrentState = FALSE;

	if(fCurrentState == fNewState)
		return;

	if(fNewState)
		SetTimer(hwndMain, TIMERID, dwTimerInterval, NULL);
	else
		KillTimer(hwndMain, TIMERID);

	fCurrentState = fNewState;
}

/*
 *	ShowTitle
 *
 *	Purpose:
 *		Show\Hidle title bar
 *
 *	Arguments:
 *		hwnd, nCmdShow (SW_HIDE, SW_SHOW)
 *
 *	Returns:
 *		zip
 */
VOID
ShowTitle(HWND hwnd, int nCmdShow)
{
	DWORD			dwStyle;
	static HMENU	hMenu = NULL;

	dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	if(hMenu)
	{
		dwStyle = WS_TILEDWINDOW | dwStyle;
		SetMenu(hwnd, hMenu);
		hMenu = NULL;
	}
	else
	{
		dwStyle &= ~(WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
		hMenu = GetMenu(hwnd);
		SetMenu(hwnd, NULL);
	}

	SetWindowLong(hwnd, GWL_STYLE, dwStyle);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE |
		SWP_NOZORDER | SWP_FRAMECHANGED);

	ShowWindow(hwnd, nCmdShow);
}

/*
 *	Date\Time routines
 */

/*
 *	PutDate
 *
 *	Purpose:
 *		Convert a tm_t to '6/8/95'
 *
 *	Arguments:
 *		tm_t, str, and cchstr
 *
 *	Returns:
 *		str
 */
TCHAR *
PutDate(time_t tm_t, TCHAR *szStr, UINT cch)
{
	SYSTEMTIME  st;
	struct tm   *ptm;

	ptm = localtime(&tm_t);

	st.wYear	= ptm->tm_year + 1900;
	st.wMonth	= ptm->tm_mon + 1;
	st.wDay		= ptm->tm_mday;

	GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &st, NULL, szStr, cch);
	return szStr;
}

/*
 *	PutTime
 *
 *	Purpose:
 *		Convert a tm_t to '6:31 am'
 *
 *	Arguments:
 *		tm_t, str, and cchstr
 *
 *	Returns:
 *		str
 */
TCHAR *
PutTime(time_t tm_t, TCHAR *szStr, UINT cch)
{
	SYSTEMTIME  st;
	struct tm   *ptm;

	ptm = localtime(&tm_t);

	st.wHour			= ptm->tm_hour;
	st.wMinute			= ptm->tm_min;
	st.wSecond			= ptm->tm_sec;
	st.wMilliseconds	= 0;

	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, NULL, szStr, cch);
	return szStr;
}

/*
 *	PutCounterTime
 *
 *	Purpose:
 *		Convert a tm_t to '6:31:00'
 *
 *	Arguments:
 *		tm_t, str, and cchstr
 *
 *	Returns:
 *		str
 */
TCHAR *
PutCounterTime(DWORD dwTime, TCHAR *szStr, UINT cch)
{
	SYSTEMTIME  	st;
	TCHAR			szTimeSep[cchSzMax];
	SCONST TCHAR	szFmtCounter[] = TEXT("%02d%s%d");

	st.wHour			= (WORD)(dwTime / 3600);
	dwTime				-= (st.wHour * 3600);
	st.wMinute			= (WORD)(dwTime / 60);
	dwTime				-= (st.wMinute * 60);
	st.wSecond			= (WORD)dwTime;
	st.wMilliseconds	= 0;

	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, szTimeSep, cchSzMax);
	wsprintf(szStr, szFmtCounter, st.wHour, szTimeSep, st.wMinute);
	Assert((UINT)lstrlen(szStr) < cch);
	return szStr;
}

/*
 *  TreeView and Imagelist routines
 */

// handle to our imagelist
HIMAGELIST	hImal = NULL;

/*
 *  InitNetWatchWnd
 *  
 *  Purpose:
 *      inits listbox globals, creates listbox
 *  
 *  Arguments:
 *      HWND    main hwnd of app (parent of LB)
 *  
 *  Returns:
 *      hwnd of treeview
 */
HWND
InitNetWatchWnd(HWND hwnd)
{
	HWND			hwndTV;
	SCONST TCHAR	szWCTreeView[] = WC_TREEVIEW;

	OutputDbgStr("InitNetWatchWnd");

	// Init common controls
	InitCommonControls();

	// Create our imagelist
	hImal = ImageList_LoadBitmap(ghInst, MAKEINTRESOURCE(IDB_LB),
		BMWIDTH, 0, RGBREPLACE);
	if(!hImal)
		return NULL;

	// Create our treeview
	hwndTV = CreateWindow(szWCTreeView, NULL,
		WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_DISABLEDRAGDROP,
		0, 0, 0, 0, hwnd, (HMENU)IDD_tvwSHARES, ghInst, NULL);
	if(!hwndTV)
		return NULL;
	TreeView_SetImageList(hwndTV, hImal, 0);

	// Make sure our new tv has the focus
	SetFocus(hwndTV);
	return hwndTV;
}

/*
 *  DeInitNetWatchWnd
 *  
 *  Purpose:
 *      cleans up LB hfonts, hdc, and hbmps
 *  
 *  Arguments:
 *  
 *  Returns:
 *      hopefully
 */
VOID
DeInitNetWatchWnd(VOID)
{
	if(hImal)
	{
		ImageList_Destroy(hImal);
		hImal = NULL;
	}
}

/*
 *	BlitIcon
 *
 *	Purpose:
 *		Smack an icon onto an hdc
 *
 *	Arguments:
 *		hdc, x, y, bitmap index
 *
 *	Returns:
 *		nope
 */
VOID
BlitIcon(HDC hdc, LONG x, LONG y, int nBitmap)
{
	ImageList_Draw(hImal, nBitmap, hdc, x, y, ILD_TRANSPARENT);
}
