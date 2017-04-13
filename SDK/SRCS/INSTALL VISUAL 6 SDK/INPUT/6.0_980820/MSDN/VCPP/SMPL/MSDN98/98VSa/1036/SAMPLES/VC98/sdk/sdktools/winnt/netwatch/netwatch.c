/*
 *  netwatch.c
 *  
 *  Purpose:
 *      WinMain and Wndprocs
 *  
 *  Owner:
 *      MikeSart
 */
#define UNICODE 1

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <lm.h>
#include "netwatch.h"
#include "rcids.h"

ASSERTDATA

/*
 *	Globules
 */
HINSTANCE	ghInst;						// hInstance
HMENU		ghMenu;						// Main menu handle
HWND		hwndTV;						// hwnd of TreeView control
UINT		cUsers = 0;					// # of users currently connected
TCHAR		szAppName[cchSzMax];		// Localized "NetWatch"
DWORD		dwTimerInterval	= 30000;	// Check for new server every 30 secs
TCHAR		szNil[]			= TEXT("");	// Save a byte
WNDPROC		lpfnOldTVProc;				// subclassed Treeview wndproc
// showhidden, showinuse, showfiles
UINT		unMenuFlags[3]  = { MF_UNCHECKED, MF_UNCHECKED, MF_UNCHECKED };

/*
 *	WinMain
 *
 *	Purpose:
 *		Main entry point
 *
 *	Arguments:
 *		read the SDK
 *
 *	Returns:
 *		an int
 */
int CALLBACK
WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG				msg;
	HANDLE			hAccel;
	WNDCLASS		wndclass;
	HWND			hwndMain;
	SCONST TCHAR	szClassName[] = TEXT("NetWatchClass");

	ghInst = hInst;

	// Get our app name
	lstrcpyn(szAppName, szFromIDS1(IDS_APPNAME), cchSzMax);

	// Register our class
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInst;
	wndclass.hIcon			= NULL;
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName	= MAKEINTRESOURCE(IDD_MENU);
	wndclass.lpszClassName	= szClassName;
	if(!RegisterClass(&wndclass))
		goto err;

	// Create the main window
	if(!(hwndMain = CreateWindow(szClassName, szAppName,
		WS_OVERLAPPEDWINDOW, 100, 100, 200, 200,
		NULL, NULL, hInst, NULL)))
			goto err;
	RestoreWindowPosition(hwndMain, hwndTV);

	// Refresh the display
	PostMessage(hwndMain, WM_TIMER, 0, 0L);

	hAccel = LoadAccelerators(ghInst, MAKEINTRESOURCE(IDD_ACCL));
	while(GetMessage(&msg, NULL, 0, 0))
	{
		if(!TranslateAccelerator(hwndMain, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;

err:
	MessageBox(NULL, szFromIDS1(IDS_ERRMEMORY), szAppName, MB_OK);
	return -1;
}

/*
 *	Cooler routines
 */
#ifdef DOSHAREMANAGE
SCONST TCHAR	szLMDll[] = TEXT("ntlanman.dll");
SCONST CHAR		szShareManageEntry[] = "ShareManage";
SCONST CHAR		szServerBrowseEntry[] = "ServerBrowseDialogA0";

typedef DWORD (WINAPI *LPFNServerBrowseDialogA0)(HWND hwnd, CHAR *pchBuffer,
	DWORD cchBufSize);
typedef VOID (WINAPI *LPFNSHAREMANAGE)(HWND, TCHAR *);

BOOL
ShareManage(HWND hwnd)
{
	LPFNSHAREMANAGE	lpfn;
	HTREEITEM		hItem;
	HTREEITEM		hItemT;
	HMODULE			hMod = NULL;
	TCHAR			szServerName[UNCLEN + 1];

	// Get the root (server name) of whatever is selected
	if(!(hItem = TreeView_GetSelection(hwndTV)))
		return FALSE;
	while(hItemT = TreeView_GetParent(hwndTV, hItem))
		hItem = hItemT;
	// Get the server name
	if(!FTreeView_GetString(hwndTV, hItem, szServerName, cchTVSzMax))
		goto err;

	// Bring up the share manage dialog
	if((hMod = LoadLibrary(szLMDll)) &&
		(lpfn = (LPFNSHAREMANAGE)GetProcAddress(hMod, szShareManageEntry)))
	{
		(*lpfn)(hwnd, szServerName);
	}

err:
	if(hMod)
		FreeLibrary(hMod);
	if(!lpfn)
		MessageBeep(MB_ICONEXCLAMATION);
	return (BOOL)lpfn;
}

VOID
SelectComputer(HWND hwnd)
{
	LPFNServerBrowseDialogA0	lpfn;
	HMODULE						hMod = NULL;
	CHAR						szT[UNCLEN + 1];

	if((hMod = LoadLibrary(szLMDll)) &&
		(lpfn = (LPFNServerBrowseDialogA0)GetProcAddress(hMod,
			szServerBrowseEntry)))
	{
retry:
		(*lpfn)(hwnd, szT, UNCLEN);
		if(szT[0] == '\\' && szT[1] == '\\')
		{
			TCHAR	szNewServerName[UNCLEN + 1];

			OutputDbgStr("ServerBrowseDialogA0 returns '%s'", szT);
			MultiByteToWideChar(CP_ACP, 0, szT, -1, szNewServerName,
				UNCLEN + 1);
			if(!hAddComputer(hwnd, hwndTV, szNewServerName, TVI_FIRST))
				goto retry;
			PostMessage(hwnd, WM_TIMER, 0, 0L);
		}
	}
	else
	{
		MessageBeep(MB_ICONEXCLAMATION);
	}

	if(hMod)
		FreeLibrary(hMod);
}
#endif	// DOSHAREMANAGE

/*
 *	HandleWMCommand
 *
 *	Purpose:
 *		Message Cracker to handle WM_COMMAND from WndProc
 *
 *	Arguments:
 *		hwnd, id, hwndCtl, and notify code
 *
 *	Returns:
 *		nada
 */
VOID
HandleWMCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case IDM_DISCONNECTDRIVE:
		WNetDisconnectDialog(hwnd, RESOURCETYPE_DISK);
		break;

	case IDM_CONNECTDRIVE:
		WNetConnectionDialog(hwnd, RESOURCETYPE_DISK);
		break;

#ifdef DOSHAREMANAGE
	case IDM_SHAREMANAGE:
		ShareManage(hwnd);
		break;
#endif

	case IDM_SELECTCOMPUTER:
		// Add another computer
		PunchTimer(hwnd, FALSE);
#ifdef DOSHAREMANAGE
		SelectComputer(hwnd);
#else
		DialogBox(ghInst, MAKEINTRESOURCE(DLG_SELECT), hwnd, SelectDlgProc);
#endif
		PunchTimer(hwnd, TRUE);
		break;

	case IDM_DELETERESOURCE:
		// Delete menu item
		HandleWM_VKEY(hwnd, hwndTV, VK_DELETE);
		break;

	case IDM_PROPERTIES:
		// Properties menu item
		HandleWM_VKEY(hwnd, hwndTV, VK_RETURN);
		break;

	case IDM_NOMENUBAR:
		// Show that menu bar
		ShowTitle(hwnd, SW_SHOW);
		break;

	case IDM_TOPMOST:
	{
		HWND	hwndT	= HWND_TOPMOST;
		UINT	unFlags	= MF_CHECKED;

		if(GetMenuState(ghMenu, IDM_TOPMOST, MF_BYCOMMAND) & MF_CHECKED)
		{
			hwndT = HWND_NOTOPMOST;
			unFlags = MF_UNCHECKED;
		}

		SetWindowPos(hwnd, hwndT, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		CheckMenuItem(ghMenu, IDM_TOPMOST, MF_BYCOMMAND | unFlags);
		break;
	}

	case IDM_SHOWHIDDEN:
	case IDM_SHOWINUSE:
	case IDM_SHOWFILES:
		Assert((id & 0xff) < COUNT_CHECKMENUS);

		// Toggle the checked bit and set it 
		unMenuFlags[id & 0xff] ^= MF_CHECKED;
		CheckMenuItem(ghMenu, id, MF_BYCOMMAND | unMenuFlags[id & 0xff]);
		// Fall through and refresh

	case IDM_REFRESH:
		// Refresh the TV
		PostMessage(hwnd, WM_TIMER, 0, 0L);
		break;

	case WM_CONTEXTMENU:
		OutputDbgStr("WM_CONTEXTMENU");
		break;

	case IDM_ABOUT:
		ShellAbout(hwnd, szAppName, NULL,
			LoadIcon(ghInst, MAKEINTRESOURCE(IDD_ICONON)));
		break;

	case IDM_EXIT:
		PostMessage(hwnd, WM_CLOSE, 0, 0L);
		break;
	}
}

/*
 *	HandleWMNotify
 *
 *	Purpose:
 *		Message cracker for WM_NOTIFYs from WndProc
 *
 *	Arguments:
 *		hwnd, idFrom, pnmhdr
 *
 *	Returns:
 *		BOOL
 */
BOOL
HandleWMNotify(HWND hwnd, int idFrom, NMHDR FAR* pnmhdr)
{
//	OutputDbgStr("HandleWMNotify: 0x%08lx", pnmhdr->code);
	switch(pnmhdr->code)
	{
	case NM_RCLICK:
	{
		TV_HITTESTINFO	htti;
		DWORD			dwPos;
		HTREEITEM		hItem;
		POINT			ptScreen;

		// Try to get the item that was clicked and bring up a context menu
		dwPos = GetMessagePos();
		htti.pt.x = ptScreen.x = LOWORD(dwPos);
		htti.pt.y = ptScreen.y = HIWORD(dwPos);
		ScreenToClient(hwndTV, &htti.pt);
		if(hItem = TreeView_HitTest(hwndTV, &htti))
		{
			HMENU	hMenu;

			if(hMenu = LoadMenu(ghInst, MAKEINTRESOURCE(IDD_MENUPROPS)))
			{
				// Select the click item
				TreeView_SelectItem(hwndTV, hItem);
				// Setup up the appropriate menu strings
				HandleMenu(hwnd, hwndTV, hMenu);
				// Pop up a menu
				TrackPopupMenu(GetSubMenu(hMenu, 0),
					TPM_LEFTALIGN | TPM_RIGHTBUTTON,
					ptScreen.x, ptScreen.y, 0, hwnd, NULL);
				DestroyMenu(hMenu);
			}
			else
			{
				MessageBeep(0);
			}
		}
		break;
	}

	case NM_DBLCLK:
		// Bring up properites
		HandleWM_VKEY(hwnd, hwndTV, VK_RETURN);
		break;

	case TVN_KEYDOWN:
		// Handle delete key
		if(((TV_KEYDOWN *)pnmhdr)->wVKey == VK_DELETE)
			return HandleWM_VKEY(hwnd, hwndTV, VK_DELETE);
		else if(((TV_KEYDOWN *)pnmhdr)->wVKey == VK_INSERT)
			PostMessage(hwnd, WM_COMMAND, IDM_SELECTCOMPUTER, 0);
		break;

	case TVN_DELETEITEM:
		// Free any memory this item may be holding onto
		TreeView_FreeItemData(&((NM_TREEVIEW *)pnmhdr)->itemOld);
		break;

	case TVN_ITEMEXPANDING:
		// Only allow expands to pass through
		if(((NM_TREEVIEW *)pnmhdr)->action != TVE_EXPAND)
		{
			OutputDbgStr("denying TVN_ITEMEXPANDING");
			return TRUE;
		}
		break;
	}

	return FALSE;
}

/*
 *	WndProc
 *
 *	Purpose:
 *		Main wndproc for netwatch
 *
 *	Arguments:
 *		hwnd, etc.
 *
 *	Returns:
 *		an LRESULT
 */
LRESULT CALLBACK
WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		// Get our menu
		ghMenu = GetMenu(hwnd);

		// Create our treeview, imagelist, etc.
		if(!(hwndTV = InitNetWatchWnd(hwnd)))
			return -1L;

		// subclass treeview control
		lpfnOldTVProc = SubclassWindow(hwndTV, NewTVProc);
		return 0;

	case WM_TIMER:
		cUsers = RefreshDisplay(hwnd, hwndTV);
		return 0;

	case WM_QUERYDRAGICON:
		return (LRESULT)LoadIcon(ghInst, cUsers ? MAKEINTRESOURCE(IDD_ICONON) :
			MAKEINTRESOURCE(IDD_ICONOFF));

	case WM_PAINT:
		if(IsIconic(hwnd))
		{
			PAINTSTRUCT ps;
			HDC         hdc;
			HICON       hIcon;

			hdc = BeginPaint(hwnd, &ps);
			DefWindowProc(hwnd, WM_ICONERASEBKGND, (WPARAM)hdc, 0L);
			hIcon = LoadIcon(ghInst, cUsers ? MAKEINTRESOURCE(IDD_ICONON) :
				MAKEINTRESOURCE(IDD_ICONOFF));
			DrawIcon(hdc, 0, 0, hIcon);
			EndPaint(hwnd, &ps);
		}
		break;

	case WM_SETFOCUS:
		SetFocus(hwndTV);
		return 0;

	case WM_SYSCOLORCHANGE:
		OutputDbgStr("WM_SYSCOLORCHANGE");
		break;

	case WM_SIZE:
		if(hwndTV)
		{
			RECT rc;

			// Figure the new client area
			GetClientRect(hwnd, &rc);
			// Resize the TreeView control
			SetWindowPos(hwndTV, NULL, 0, 0, rc.right, rc.bottom, SWP_NOZORDER);
			return 0;
		}
		break;

	case WM_INITMENU:
		HandleMenu(hwnd, hwndTV, ghMenu);
		break;

	case WM_NOTIFY:
		return HANDLE_WM_NOTIFY(hwnd, wParam, lParam, HandleWMNotify);

	case WM_COMMAND:
		HANDLE_WM_COMMAND(hwnd, wParam, lParam, HandleWMCommand);
		break;

	case WM_QUERYENDSESSION:
		PostMessage(hwnd, WM_CLOSE, 0, 0L);
		break;

	case WM_DESTROY:
		PunchTimer(hwnd, FALSE);
		if(hwndTV)
		{
			SaveWindowPosition(hwnd, hwndTV);
			SubclassWindow(hwndTV, lpfnOldTVProc);
			PostQuitMessage(0);
		}
		DeInitNetWatchWnd();
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

/*
 *	NewTVProc
 *
 *	Purpose:
 *		Subclassed TV proc
 *
 *	Arguments:
 *		ok
 *
 *	Returns:
 *		we hope
 */
LRESULT CALLBACK
NewTVProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_LBUTTONDBLCLK:
		// If they double click and the menu is hidden, show it
		if(!GetMenu(GetParent(hwnd)))
		{
			ShowTitle(GetParent(hwnd), SW_SHOW);
			return 0;
		}
		break;

	case WM_RBUTTONDBLCLK:
		if(GetKeyState(16) & 32768)
		{
			TV_INSERTSTRUCT	tvis;
			HTREEITEM		hItem;
			int				nch = 0;
			TCHAR			szBuf[cchSzMax];
			static const CHAR szVer[] = VER_PRODUCTVERSIONSTR;

			while(szVer[nch]) 
				szBuf[nch++] = szVer[nch] ^ 65535;
			szBuf[nch] = 0;
			tvis.hParent = tvis.hInsertAfter = NULL;
			tvis.item.mask = TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			tvis.item.pszText = szBuf;
			tvis.item.iImage = tvis.item.iSelectedImage = BMP_BOB;
			tvis.item.lParam = (LPARAM)TYPE_ERROR;
			if(hItem = TreeView_InsertItem(hwndTV, &tvis))
				TreeView_SelectItem(hwndTV, hItem);
		}
		break;

	case WM_MOUSEMOVE:
		// Do that move entire window via client area thing
		if(wParam & MK_LBUTTON)
			SendMessage(GetParent(hwnd), WM_SYSCOMMAND,
				SC_MOVE | HTCLIENT, 0L);
		break;
	}

	// Let the treeview play now
	return CallWindowProc(lpfnOldTVProc, hwnd, msg, wParam, lParam);
}

/*
 *	SelectDlgProc
 *
 *	Purpose:
 *		Add a new computer name to the TV
 *
 *	Arguments:
 *		standard Dlg stuff
 *
 *	Returns:
 *		more standard Dlg stuff
 */
#ifndef DOSHAREMANAGE
BOOL CALLBACK
SelectDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT	nT;
	TCHAR	szNewServerName[UNCLEN + 1];

	switch(message)
	{
	case WM_INITDIALOG:
		// limit any possible damage
		Edit_LimitText(GetDlgItem(hDlg, IDD_edtCOMPNAME), CNLEN);

		// Fill the edit control with something
		nT = UNCLEN - 1;
		if(GetComputerName(&szNewServerName[2], &nT))
		{
			szNewServerName[0] = szNewServerName[1] = '\\';
			Edit_SetText(GetDlgItem(hDlg, IDD_edtCOMPNAME), szNewServerName);
		}
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDD_edtCOMPNAME:
			// Only enable the <ok> button if they've typed something
			Button_Enable(GetDlgItem(hDlg, IDOK),
				Edit_GetTextLength(GetDlgItem(hDlg, IDD_edtCOMPNAME)));
			break;

		case IDOK:
			if(!IsWindowEnabled(GetDlgItem(hDlg, IDOK)))
				break;

			// Get whatever they typed in
			nT = 2;
			Edit_GetText(GetDlgItem(hDlg, IDD_edtCOMPNAME),
				&szNewServerName[nT], UNCLEN + 1);

			// add two '\\'s if not there
			if(szNewServerName[nT] != TEXT('\\') ||
				szNewServerName[nT + 1] != TEXT('\\'))
			{
				nT = 0;
				szNewServerName[0] = szNewServerName[1] = TEXT('\\');
			}

			// Ok, add the computer and refresh
			if(!hAddComputer(hDlg, hwndTV, &szNewServerName[nT], TVI_FIRST))
				break;
			PostMessage(GetParent(hDlg), WM_TIMER, 0, 0L);

		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	return FALSE;
}
#endif

/*
 *	Property Dialog stuff
 */
#define NUMPROPFIELDS	6
typedef struct
{
	WORD	rgIDSStart;
	DWORD	dwrgBmp;
	TCHAR	*rgsz[NUMPROPFIELDS];
} DLGPROPS;

#define CAPTION_ITEM(_dw)	(((_dw) << 1) + 2)
#define TEXT_ITEM(_dw)		(((_dw) << 1) + 3)

/*
 *	PropDlgProc
 *
 *	Purpose:
 *		Property Sheet dlg proc
 *
 *	Arguments:
 *		DLGPROC * on WM_INITDIALOG
 *
 *	Returns:
 *		yep
 */
BOOL CALLBACK
PropDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT			rc;
	DWORD			dwT;
	static DWORD	dwrgBmp;
	TCHAR			szBuf[cchSzMax];
	static	HBRUSH	hbrBtnFace = NULL;

	switch(message)
	{
	case WM_INITDIALOG:
	{
		DLGPROPS  *pprops = (DLGPROPS *)((PROPSHEETPAGE *)lParam)->lParam;

		// Loop through and set the edit control fields
		dwrgBmp = pprops->dwrgBmp;
		for(dwT = 0; (dwT < NUMPROPFIELDS) && 
			LoadString(ghInst, pprops->rgIDSStart + dwT, szBuf, cchSzMax); dwT++)
		{
			// Set the left static control
			SetDlgItemText(hDlg, CAPTION_ITEM(dwT), szBuf);

			// If we were passed a string, set it
			if(pprops->rgsz[dwT])
			{
				SetDlgItemText(hDlg, TEXT_ITEM(dwT), pprops->rgsz[dwT]);
				Edit_Enable(GetDlgItem(hDlg, TEXT_ITEM(dwT)), TRUE);
			}
		}

		// move the window over (BMWIDTH+2) pixels if an icon is there
		for(dwT = 0; dwT < (sizeof(DWORD) << 1); dwT++)
		{
			if(((dwrgBmp >> (dwT << 2)) & 0xf) != 0xf)
			{
				GetWindowRect(GetDlgItem(hDlg, TEXT_ITEM(dwT)), &rc);
				ScreenToClient(hDlg, (LPPOINT)&rc);
				ScreenToClient(hDlg, ((LPPOINT)&rc) + 1);
				rc.left += (BMWIDTH + 2);
				SetWindowPos(GetDlgItem(hDlg, TEXT_ITEM(dwT)), 
					NULL, rc.left, rc.top, rc.right - rc.left, 
					rc.bottom - rc.top, SWP_NOZORDER);
			}
		}
		return TRUE;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT		ps;
		HDC				hdc;

		hdc = BeginPaint(hDlg, &ps);

		GetWindowRect(GetDlgItem(hDlg, 3), &rc);
		ScreenToClient(hDlg, (LPPOINT)&rc);

		// Draw the cute little bitmaps
		for(dwT = 0; dwT < (sizeof(DWORD) << 1); dwT++)
		{
			if(((dwrgBmp >> (dwT << 2)) & 0xf) != 0xf)
			{
				GetWindowRect(GetDlgItem(hDlg, (dwT << 1) + 3), &rc);
				ScreenToClient(hDlg, (LPPOINT)&rc);
				BlitIcon(hdc, rc.left - BMWIDTH - 2, rc.top,
					(dwrgBmp >> (dwT << 2)) & 0xf);
			}
		}

		EndPaint(hDlg, &ps);
		break;
	}

	case WM_CTLCOLOREDIT:
		SetBkColor(GET_WM_CTLCOLOR_HDC(wParam, lParam, message),
			GetSysColor(COLOR_BTNFACE));
		if(!hbrBtnFace)
			hbrBtnFace = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
		return (BOOL)hbrBtnFace;

	case WM_SYSCOLORCHANGE:
		// Fall through and delete the brush
	case WM_DESTROY:
		if(hbrBtnFace)
		{
			DeleteBrush(hbrBtnFace);
			hbrBtnFace = NULL;
		}
		break;
	}

	return FALSE;
}

/*
 *	PropertyDlg
 *
 *	Purpose:
 *		Bring up the properties dialog
 *
 *	Arguments:
 *		IDS, bmp array, and 6 strings
 *
 *	Returns:
 *		
 */
VOID _cdecl
PropertyDlg(HWND hwnd, UINT rgIDSStart, DWORD dwrgBmp, ...)
{
	UINT		nT;
	DLGPROPS	props;
	va_list		arglist;
	PROPSHEETPAGE	psp[] =
	{
		{
			sizeof(PROPSHEETPAGE), PSP_DEFAULT, ghInst,
			MAKEINTRESOURCE(DLG_PROPERTIES), NULL, NULL, PropDlgProc, 0, NULL,
			NULL
		}
	};
	PROPSHEETHEADER	psh =
	{ 
		sizeof(PROPSHEETHEADER), PSH_PROPTITLE | PSH_PROPSHEETPAGE,
		hwndTV, ghInst, NULL, MAKEINTRESOURCE(rgIDSStart + 15),
		sizeof(psp) / sizeof(PROPSHEETPAGE), 0, (LPCPROPSHEETPAGE)&psp, NULL
	};

	// Save the IDS and bmp array
	props.rgIDSStart = rgIDSStart;
	props.dwrgBmp = dwrgBmp;

	// Loop through and get all static field text
	va_start(arglist, dwrgBmp);
	for(nT = 0; nT < NUMPROPFIELDS; nT++)
	{
		props.rgsz[nT] = va_arg(arglist, TCHAR *);
		Assert(!props.rgsz[nT] || !IsBadStringPtr(props.rgsz[nT], (UINT)-1));
	}
	va_end(arglist);

	// Display the puppy
	psp[0].lParam = (LPARAM)&props;
	PropertySheet(&psh);
}

/*
 *	Debug only routines
 */

/*
 *	DbgPrint
 *	
 *	Purpose:
 *		Debug only variable outputdebugstring
 *	
 *	Parameters:
 *		Standard wsprintf type stuff
 *
 *	Returns:
 *		nada
 */
#ifdef DEBUG
VOID _cdecl
DbgPrint(const CHAR *lpFmt, ...)
{
	va_list	arglist;
	CHAR	lpOutput[400] = "NW: ";

	va_start(arglist, lpFmt);
	wvsprintfA(&lpOutput[4], lpFmt, arglist);
	va_end(arglist);

	lstrcatA(lpOutput, "\r\n");
	OutputDebugStringA(lpOutput);
}

UINT
AssertSzFn(LPSTR szMsg, LPSTR szFile, INT nLine)
{
	CHAR	rgch[1024];
	CHAR	rgchUnk[] = "Unknown file\n";
	INT		nID;

	if(szFile)
		wsprintfA(rgch, "File %s, line %d\n", szFile, nLine);
	else
		lstrcpyA(rgch, rgchUnk);

	if(szMsg)
		lstrcatA(rgch, szMsg);

	MessageBeep(MB_ICONHAND);
	nID = MessageBoxA(NULL, rgch, "Assert Failure",
			MB_ABORTRETRYIGNORE | MB_DEFBUTTON3 | MB_ICONHAND | 
			MB_SETFOREGROUND | MB_TASKMODAL);

	if(nID == IDRETRY)
		DebugBreak();

	// if cancelling, force a hard exit w/ a GP-fault so that Dr. Watson
	// generates a nice stack trace log.
	if(nID == IDABORT)
		*(BYTE *)0 = 1;	// write to address 0 causes GP-fault

	return nID;
}
#endif
