/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       wizard.c
 *  Content:    User input (setup wizard) related code
 *
 *
 ***************************************************************************/
#include <windows.h>
#include "prsht.h"
#include "wizard.h"
#include "util.h"
#include "comm.h"
#include "gameproc.h"

/*
 * Externals
 */
extern HINSTANCE				ghinst;				// program instance
extern HWND						ghWndMain;			// main window
extern BOOL						gbIsHost;			// is the user hosting/joining a game
extern DPID						gOurID;				// player id
extern LPGUID					glpGuid;			// duel's guid
extern LPDIRECTPLAY3			glpDP3A;				// An IDirectPlay3 interface.

/*
 * Globals to this module
 */
static HFONT					ghTitleFont;		// font for titles on setup wizard
static HFONT					ghHeadingFont;		// font for headings on setup wizard
static int						gnSession,gnPlayer; // indexes for tree view images
static HKEY						ghDuelKey=NULL;		// duel registry key handle
static DWORD					gdwDuelDisp;		// key created or opened
static HTREEITEM				ghtiSession;		// points to a visible session item in tree control
													//  used for inserting players into tree control
static HWND						ghWndSPCtl;			// handle to service provider control

/*
 * SetupFonts
 *
 * Initializes font structures (used for wizard controls)
 */
void SetupFonts(HDC hDC)
{
	LOGFONT lf;
	TCHAR tszFontName[MAX_FONTNAME];

	LoadString(ghinst, IDS_WIZARD_FONTNAME, tszFontName, MAX_FONTNAME);

	ZeroMemory(&lf,sizeof(lf));
	lf.lfHeight = -MulDiv(11,GetDeviceCaps(hDC, LOGPIXELSY),72);
	lf.lfWeight = 500;
	lf.lfItalic = TRUE;
	_tcscpy(lf.lfFaceName,tszFontName);
	ghTitleFont = CreateFontIndirect(&lf);

	ZeroMemory(&lf,sizeof(lf));
	lf.lfHeight = -MulDiv(11,GetDeviceCaps(hDC, LOGPIXELSY),72);
	lf.lfWeight = 500;
	_tcscpy(lf.lfFaceName,tszFontName);
	ghHeadingFont = CreateFontIndirect(&lf);
}

/*
 * CleanupFonts
 *
 * Cleans up font structures
 */
void CleanupFonts(void)
{
	if (ghTitleFont) DeleteObject(ghTitleFont);
	if (ghHeadingFont) DeleteObject(ghHeadingFont);
}

/*
 * RegSet
 *
 * Stores a data value in the registry
 */
LONG RegSet(LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize)
{
#ifdef UNICODE
	dwSize *= 2; // calc number of bytes
#endif
	return RegSetValueEx(ghDuelKey, lptszName, 0, REG_SZ, lpData, dwSize);
}

/*
 * RegSetA
 *
 * Stores data as an ascii string in the registry
 */
LONG RegSetA(LPCTSTR lptszName, CONST BYTE * lpData, DWORD dwSize)
{
	return RegSetValueEx(ghDuelKey, lptszName, 0, REG_SZ, lpData, dwSize);
}

/*
 * RegGet
 *
 * Queries a value from the registry
 */
LONG RegGet(LPCTSTR lptszName, LPBYTE lpData, LPDWORD lpdwDataSize)
{
	DWORD dwType;

	return RegQueryValueEx(ghDuelKey, lptszName, NULL, &dwType, lpData, lpdwDataSize);
}

/*
 * DoWizard
 *
 * Creates and launches a wizard (property sheets) for user input
 */
DWORD WINAPI DoWizard(LPVOID pv)
{
	PROPSHEETPAGE psp[4];
    PROPSHEETHEADER psh;
	TCHAR tszTitle1[MAX_WINDOWTITLE];
	TCHAR tszTitle2[MAX_WINDOWTITLE];
	TCHAR tszTitle3[MAX_WINDOWTITLE];
	TCHAR tszTitle4[MAX_WINDOWTITLE];
	TCHAR tszTitle5[MAX_WINDOWTITLE];
    HDC hDC;

	CoInitialize( NULL );
	
	LoadString(ghinst, IDS_WIZARD_TITLE_SP, tszTitle1, MAX_WINDOWTITLE); 
	LoadString(ghinst, IDS_WIZARD_TITLE_GS, tszTitle2, MAX_WINDOWTITLE); 
	LoadString(ghinst, IDS_WIZARD_TITLE_JS, tszTitle3, MAX_WINDOWTITLE); 
	LoadString(ghinst, IDS_WIZARD_TITLE_HS, tszTitle4, MAX_WINDOWTITLE); 
	LoadString(ghinst, IDS_WIZARD_TITLE, tszTitle5, MAX_WINDOWTITLE); 

    psp[0].dwSize = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags = PSP_USETITLE;
    psp[0].hInstance = ghinst;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_CHOOSEPROVIDER);
    psp[0].pszIcon = NULL; 
    psp[0].pfnDlgProc = DlgProcChooseProvider;
    psp[0].pszTitle = tszTitle1;
    psp[0].lParam = 0;
    psp[0].pfnCallback = NULL;

    psp[1].dwSize = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags = PSP_USETITLE;
    psp[1].hInstance = ghinst;
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_GAMESETUP);
    psp[1].pszIcon = NULL; 
    psp[1].pfnDlgProc = DlgProcGameSetup;
    psp[1].pszTitle = tszTitle2;
    psp[1].lParam = 0;
    psp[1].pfnCallback = NULL;

    psp[2].dwSize = sizeof(PROPSHEETPAGE);
    psp[2].dwFlags = PSP_USETITLE;
    psp[2].hInstance = ghinst;
    psp[2].pszTemplate = MAKEINTRESOURCE(IDD_JOINSESSION);
    psp[2].pszIcon = NULL; 
    psp[2].pfnDlgProc = DlgProcJoinSession;
    psp[2].pszTitle = tszTitle3;
    psp[2].lParam = 0;
    psp[2].pfnCallback = NULL;

    psp[3].dwSize = sizeof(PROPSHEETPAGE);
    psp[3].dwFlags = PSP_USETITLE;
    psp[3].hInstance = ghinst;
    psp[3].pszTemplate = MAKEINTRESOURCE(IDD_HOSTSESSION);
    psp[3].pszIcon = NULL; 
    psp[3].pfnDlgProc = DlgProcHostSession;
    psp[3].pszTitle = tszTitle4;
    psp[3].lParam = 0;
    psp[3].pfnCallback = NULL;
	
	psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_PROPSHEETPAGE | PSH_WIZARD;
    psh.hwndParent = ghWndMain;
    psh.hInstance = ghinst;
    psh.pszIcon = NULL;
    psh.pszCaption = tszTitle5;
    psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
    psh.nStartPage = 0;
    psh.ppsp = (LPCPROPSHEETPAGE) &psp;
    psh.pfnCallback = NULL;

	// open/create duel registry key 
    if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER,
					                    DUEL_KEY,
					                    0,
					                    NULL,					
					                    REG_OPTION_NON_VOLATILE,
					                    KEY_ALL_ACCESS,
					                    NULL,
					                    &ghDuelKey,
				                        &gdwDuelDisp
					                    ))
    {
        goto ABORT;
    }

    hDC = GetDC(ghWndMain);
    if (!hDC)
    {
        goto ABORT;
    }

	// setup fonts
	SetupFonts(hDC);

	// launch the wizard
    PropertySheet(&psh);

	// was communication initialized correctly ?
	if (!IsDPlay())
	{
        goto ABORT;
	}

	// cleanup
	CleanupFonts();
    ReleaseDC(ghWndMain, hDC);

	CoUninitialize();
    // success
	PostMessage( ghWndMain, UM_LAUNCH, 0, 0 );
    return 0;

ABORT:
    // failure
    CleanupFonts();
    if (hDC) 
    {
        ReleaseDC(ghWndMain, hDC);
    }
    PostMessage( ghWndMain, UM_ABORT, 0, 0 );
	return 1;
}

/*
 * DPEnumConnectionsCallback
 *
 * creates SP list box entries and associates connection data with them
 */
BOOL FAR PASCAL DPEnumConnectionsCallback(
						LPCGUID			lpguidSP,
						LPVOID			lpConnection,
						DWORD			dwSize,
						LPCDPNAME		lpName,
						DWORD			dwFlags,
						LPVOID			lpContext)
{

    HWND			hWnd = (HWND) lpContext;
    LRESULT			iIndex;
	LPVOID			lpConnectionBuffer;

	// store service provider name in combo box
	iIndex = SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM) lpName->lpszShortNameA);

	if (iIndex == CB_ERR)
		goto FAILURE;

	// make space for Connection Shortcut
	lpConnectionBuffer = GlobalAllocPtr(GHND, dwSize);
	if (lpConnectionBuffer == NULL)
		goto FAILURE;

	// store pointer to GUID in combo box
	memcpy(lpConnectionBuffer, lpConnection, dwSize);

	if (iIndex != LB_ERR)
		SendMessage(hWnd, LB_SETITEMDATA, iIndex, (LPARAM) lpConnectionBuffer);

FAILURE:
    return (TRUE);
}

/*
 * DlgProcChooseProvider
 *
 * Dialog procedure for the choose service provider dialog
 */
BOOL CALLBACK DlgProcChooseProvider(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LPVOID	lpCon = NULL;
    static  LONG    iIndex;
    static  HWND hWndCtl;
    HRESULT hr;

    switch (msg)
    {
	case WM_NOTIFY:
		switch (((NMHDR FAR *) lParam)->code) 
		{
		case PSN_SETACTIVE:
			PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_NEXT);
			return(TRUE);

		case PSN_WIZNEXT: 
			// Release previously selected DPlay object, if any.
			DPlayRelease();
			if (iIndex != LB_ERR)
			{
				lpCon = (LPVOID) SendMessage(hWndCtl, LB_GETITEMDATA, iIndex, 0);
				
				if (lpCon)
				{
					// create directplay object
					if ((hr = DPlayCreate(lpCon)) == DP_OK)
                    {
					    return(TRUE);
                    }
                    else
                    {
                        ShowError(IDS_DPLAY_ERROR_IDC);
                    }
				}
			}
			SetWindowLong(hDlg, DWL_MSGRESULT, -1);
			return(TRUE);

		case PSN_QUERYCANCEL:
			ReleaseSPData();
			DPlayRelease();
			return(TRUE);
		}
		break;

    case WM_INITDIALOG:
		SendDlgItemMessage(hDlg, IDC_SP_TITLE, WM_SETFONT, (WPARAM)ghTitleFont, MAKELPARAM(TRUE,0));

        hWndCtl = GetDlgItem(hDlg, IDC_SERVICEPROVIDERS);
        if (hWndCtl == NULL) return(TRUE);

		// remember the service provider control. used later in freeing sp information.
		ghWndSPCtl = hWndCtl;

		if ((hr = DPlayCreate(lpCon)) != DP_OK)
        {
			// class not available, so tell them to get DirectX 5 or later
			if ((hr == REGDB_E_CLASSNOTREG) || (hr == REGDB_E_IIDNOTREG))
				ShowError(IDS_DPLAY_ERROR_CLSID);
			else
				ShowError(IDS_DPLAY_ERROR_IDC);
			SetWindowLong(hDlg, DWL_MSGRESULT, -1);
			PostQuitMessage(-1);
			return(TRUE);
        }

		//Insert all available connections into the connection listbox.
        IDirectPlay3_EnumConnections( glpDP3A, glpGuid, DPEnumConnectionsCallback, hWndCtl, 0);
        SetFocus(hWndCtl);

        SendMessage(hWndCtl, LB_SETCURSEL, iIndex, 0);
        iIndex = SendMessage(hWndCtl, LB_GETCURSEL, 0, 0);
        return(TRUE);

    case WM_COMMAND:
        if ( HIWORD(wParam) == LBN_SELCHANGE)
        {
            iIndex = SendMessage(hWndCtl, LB_GETCURSEL, 0, 0);
			
			return(TRUE);
        }
		break;
    }
    return (FALSE);
}


/*
 * DlgProcGameSetup
 *
 * Dialog procedure for the Game Setup Dialog.
 */
BOOL CALLBACK DlgProcGameSetup (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
	case WM_NOTIFY:
		switch (((NMHDR FAR *) lParam)->code) 
		{
			case PSN_SETACTIVE:
				PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK | PSWIZB_NEXT);
				return(TRUE);
			
			case PSN_WIZNEXT: 
				if (gbIsHost)
					SetWindowLong(hDlg, DWL_MSGRESULT, IDD_HOSTSESSION);
				return(TRUE);

			case PSN_QUERYCANCEL:
				ReleaseSPData();
				DPlayRelease();
				return(TRUE);
		}
		break;

    case WM_INITDIALOG:
		// setup title fonts
		SendDlgItemMessage(hDlg, IDC_GAMESETUP_TITLE, WM_SETFONT, (WPARAM)ghTitleFont, MAKELPARAM(TRUE,0));
		SendDlgItemMessage(hDlg, IDC_JOINSESSION, WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0));
		SendDlgItemMessage(hDlg, IDC_HOSTSESSION, WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0));
		// host by default
		SendDlgItemMessage(hDlg, IDC_HOSTSESSION, BM_SETCHECK, 1, 0);
		SendDlgItemMessage(hDlg, IDC_JOINSESSION, BM_SETCHECK, 0, 0);
		gbIsHost = TRUE;
        return(TRUE);

    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED)
			switch (LOWORD(wParam))
			{
			case IDC_HOSTSESSION:
				if (SendDlgItemMessage(hDlg, IDC_HOSTSESSION, BM_GETCHECK, 1, 0) == 1)
				{
					gbIsHost = TRUE;
				}
				return(TRUE);
			case IDC_JOINSESSION:
				if (SendDlgItemMessage(hDlg, IDC_JOINSESSION, BM_GETCHECK, 1, 0) == 1)
				{
					gbIsHost = FALSE;
				}
				return(TRUE);
			}
		break;
	}
    return(FALSE);
}

/*
 * EnumPlayer
 *
 * EnumeratePlayer callback. Inserts player information into the passed in tree view control.
 */
BOOL WINAPI EnumPlayer(DPID pidID, DWORD dwPlayerType, LPCDPNAME lpName,
	DWORD dwFlags, LPVOID lpContext)
{
    HWND hWnd = (HWND) lpContext;
	HTREEITEM hItem;

#ifdef UNICODE
	hItem = AddItemToTree(hWnd, lpName->lpszShortName, 0, -1);
#else
	hItem = AddItemToTree(hWnd, lpName->lpszShortNameA, 0, -1);
#endif

    return(TRUE);
}

/*
 * EnumSession
 *
 * EnumSessions callback. Inserts session description information in the passed in 
 * tree view control.
 */
BOOL WINAPI EnumSession(LPCDPSESSIONDESC2 lpDPSessionDesc, LPDWORD lpdwTimeOut, DWORD dwFlags, 
						LPVOID lpContext)
{
    HWND hWnd = (HWND) lpContext;
	HTREEITEM hItem;
	LPTREEDATA lpdata;

    if(dwFlags & DPESC_TIMEDOUT) return FALSE;       // don't try again

	if (hWnd == NULL) return FALSE;

	// allocate memory to remember the guid
	lpdata = (LPTREEDATA) malloc(sizeof(TREEDATA));
	if (!lpdata) return FALSE;

	lpdata->guid = lpDPSessionDesc->guidInstance;
	lpdata->dwRefresh = 1;
	
#ifdef UNICODE
	hItem = AddItemToTree(hWnd, lpDPSessionDesc->lpszSessionName, (DWORD)lpdata, 1);
#else
	hItem = AddItemToTree(hWnd, lpDPSessionDesc->lpszSessionNameA, (DWORD)lpdata, 1);
#endif

	if (hItem)
	{
		// it was new
		TreeView_SelectItem(hWnd, hItem);		
		// enumerate players for new session
		DPlayEnumPlayers((LPGUID)&lpDPSessionDesc->guidInstance, EnumPlayer, (LPVOID) hWnd, DPENUMPLAYERS_SESSION);
	}
	else 
	{
		// it was already in the tree
		free(lpdata);	
	}


    return(TRUE);
}


void ResetTreeRefresh(HWND hwndTV)
{
	TV_ITEM item;
    HTREEITEM hItem;
    LPTREEDATA psearchdata;

	memset(&item,0,sizeof(item));
    
    // get the first app item (child of the running apps item)
    hItem = (HTREEITEM)SendMessage( hwndTV, TVM_GETNEXTITEM, TVGN_ROOT,(LPARAM) NULL);    
	
    while (hItem)
    {
		// gets its data
    	item.mask = TVIF_PARAM;
    	item.hItem = hItem;
		SendMessage( hwndTV, TVM_GETITEM, 0, (LPARAM)&item );
		// set the dwRefresh to 0
		psearchdata = (LPTREEDATA)item.lParam;
		if (psearchdata) psearchdata->dwRefresh = 0;
    	SendMessage( hwndTV, TVM_SETITEM, 0, (LPARAM)&item );

		// get the next one
    	hItem = (HTREEITEM)SendMessage( hwndTV, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem );    
    }    
	
	return ;
}  // ResetTreeRefresh  	

void RemoveStaleSessions(HWND hwndTV)
{
	TV_ITEM item;
    HTREEITEM hItem,hItemNext;
    LPTREEDATA psearchdata;

	memset(&item,0,sizeof(item));
    
    // get the first app item (child of the running apps item)
    hItem = (HTREEITEM)SendMessage( hwndTV, TVM_GETNEXTITEM, TVGN_ROOT,(LPARAM) NULL);    
	
    while (hItem)
    {
		// get the next one
    	hItemNext = (HTREEITEM)SendMessage( hwndTV, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem );    
		
		// gets its data
    	item.mask = TVIF_PARAM;
    	item.hItem = hItem;
		SendMessage( hwndTV, TVM_GETITEM, 0, (LPARAM)&item );

		// if dwRefresh is still 0, it wasn't enum'ed
		psearchdata = (LPTREEDATA)item.lParam;
		if (psearchdata && (0 == psearchdata->dwRefresh))
		{
			free(psearchdata);
			SendMessage( hwndTV, TVM_DELETEITEM, 0, (LPARAM)hItem );
		}

		hItem = hItemNext;
    }    
	
	return ;
	
}  // RemoveStaleSessions  	

/*
 * DlgProcJoinSession
 *
 * Dialog procedure for Join Session Dialog
 */
BOOL CALLBACK DlgProcJoinSession (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static  NM_TREEVIEW nmtv;
    static  HWND hWndCtl;
	static  TCHAR tszPlayerName[MAX_PLAYERNAME+1];
	static  HANDLE	dphEvent = NULL;
	TV_ITEM tvItem;
	TCHAR	tszSessionName[MAX_SESSIONNAME+1];
	DWORD   dwPNameSize;
    HRESULT hr;
	HTREEITEM htiCur, htiNext;
	LPGUID  lpGuid;

    switch (msg)
    {
	case WM_NOTIFY:
		switch (((NMHDR FAR *) lParam)->code) 
		{
			case PSN_SETACTIVE:
				if (hWndCtl) TreeView_DeleteAllItems(hWndCtl);

				// enum sessions and let dplay decide the timeout
				hr = DPlayEnumSessions(0, EnumSession, (LPVOID) hWndCtl, DPENUMSESSIONS_ASYNC);

				if (FAILED(hr))
				{
					return (FALSE);
				}

				// enumerate players for all sessions
				ghtiSession = TreeView_GetFirstVisible(hWndCtl);
		
				while (ghtiSession)
				{
					// delete previous players from display
					if ((htiNext = htiCur = TreeView_GetChild(hWndCtl, ghtiSession)) 
						!= (HTREEITEM)0)
					{
						do
						{
							htiNext = TreeView_GetNextSibling(hWndCtl, htiCur);
							TreeView_DeleteItem(hWndCtl, htiCur);
							htiCur = htiNext;
						} while (htiNext);
					}

					tvItem.hItem = ghtiSession;
					tvItem.pszText = tszSessionName;
					tvItem.cchTextMax = MAX_SESSIONNAME;
					TreeView_GetItem(hWndCtl, &tvItem);
					// enumerate players for selected session
					DPlayEnumPlayers((LPGUID)tvItem.lParam, EnumPlayer, (LPVOID) hWndCtl, DPENUMPLAYERS_SESSION);
					ghtiSession = TreeView_GetNextItem(hWndCtl, ghtiSession, TVGN_NEXTVISIBLE);
				}

				// set Finish button highlite
				if (GetDlgItemText(hDlg, IDC_JOIN_PLAYERNAME, tszPlayerName, MAX_PLAYERNAME) && 
					(htiCur = TreeView_GetSelection(hWndCtl)))
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_FINISH);
				}
				else
				{
					PropSheet_SetWizButtons(GetParent(hDlg),PSWIZB_BACK|PSWIZB_DISABLEDFINISH);
				}

				SetFocus(hWndCtl);
				
				// start up timer
                SetTimer(hDlg, ENUM_TIMER_ID, ENUM_TIMEOUT, NULL);
		
				return(TRUE);

			case PSN_WIZFINISH:
                KillTimer(hDlg, ENUM_TIMER_ID);
							
				// add user selections to registry
				if (ghDuelKey) 
				{
					RegSet(TEXT("PlayerName"), (CONST BYTE *)tszPlayerName, 
							sizeof(tszPlayerName));
				}
	
				// get the session guid
				if (nmtv.itemNew.lParam)
				{
					// user selected a session item, so just grab its lParam
					lpGuid = (LPGUID)nmtv.itemNew.lParam;
				}
				else
				{
					// user selected a player item, so grab its parent's (session) lParam
					htiCur = TreeView_GetParent(hWndCtl, nmtv.itemNew.hItem);
					if (!htiCur)
					{
						// fail finish
						ShowError(IDS_WIZARD_ERROR_GSG);
						SetWindowLong(hDlg, DWL_MSGRESULT, -1);
						return (TRUE);
					}

					tvItem.hItem = htiCur;
					tvItem.pszText = tszSessionName;
					tvItem.cchTextMax = MAX_SESSIONNAME;
					TreeView_GetItem(hWndCtl, &tvItem);					
					lpGuid = (LPGUID)tvItem.lParam;
				}

				// open session
				if ((hr = DPlayOpenSession(lpGuid)) != DP_OK)
				{
					// fail finish
					ShowError(IDS_DPLAY_ERROR_JS);
					SetWindowLong(hDlg, DWL_MSGRESULT, -1);
					return (TRUE);
				}

				// create player
				if ((hr = DPlayCreatePlayer(&gOurID, tszPlayerName, NULL, NULL, 0)) != DP_OK)
				{
					// fail finish
					ShowError(IDS_DPLAY_ERROR_CP);
					SetWindowLong(hDlg, DWL_MSGRESULT, -1);
					return (TRUE);
				}

				// everything went well, release allocated memory and finish
				ReleaseSessionData(hWndCtl);
				ReleaseSPData();				
				return(TRUE);

			case PSN_QUERYCANCEL:
                KillTimer(hDlg, ENUM_TIMER_ID);
				ReleaseSPData();
				ReleaseSessionData(hWndCtl);
				DPlayRelease();
				return(TRUE);

			case PSN_WIZBACK:
                KillTimer(hDlg, ENUM_TIMER_ID);
				ReleaseSessionData(hWndCtl);
				return(TRUE);

			case TVN_SELCHANGING:
				nmtv = *((NM_TREEVIEW *) lParam);

				// set Finish button status 
				if (GetDlgItemText(hDlg, IDC_JOIN_PLAYERNAME, tszPlayerName, MAX_PLAYERNAME) && 
					(htiCur = TreeView_GetSelection(hWndCtl)))
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_FINISH);
				}
				else
				{
					PropSheet_SetWizButtons(GetParent(hDlg),PSWIZB_BACK|PSWIZB_DISABLEDFINISH);
				}
				return(FALSE);

			case NM_CLICK:
				return(FALSE);
		}
		break;
    case WM_INITDIALOG:
		// setup title fonts
		SendDlgItemMessage(hDlg, IDC_JOIN_SESSION_TITLE, WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0));
		SendDlgItemMessage(hDlg, IDC_JOIN_PLAYER_TITLE, WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0));

		// setup user's previous data
		dwPNameSize = MAX_PLAYERNAME+1;
		tszPlayerName[0]=0;
		if (ghDuelKey && (RegGet(TEXT("PlayerName"),(LPBYTE)tszPlayerName,&dwPNameSize) == ERROR_SUCCESS))	
			SetDlgItemText(hDlg, IDC_JOIN_PLAYERNAME, tszPlayerName);

        hWndCtl = GetDlgItem(hDlg, IDC_JOIN_SESSION);
        if (hWndCtl == NULL) return(TRUE);
		InitTreeViewImageLists(hWndCtl);
        return(TRUE);
		
	case WM_TIMER:

		ResetTreeRefresh(hWndCtl);
		// enum sessions and let dplay decide the timeout
		DPlayEnumSessions(0, EnumSession, (LPVOID) hWndCtl, DPENUMSESSIONS_ASYNC);

		RemoveStaleSessions(hWndCtl);
		
			// set Finish button highlite
		if (GetDlgItemText(hDlg, IDC_JOIN_PLAYERNAME, tszPlayerName, MAX_PLAYERNAME) && 
			(htiCur = TreeView_GetSelection(hWndCtl)))
		{
			PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_FINISH);
		}
		else
		{
			PropSheet_SetWizButtons(GetParent(hDlg),PSWIZB_BACK|PSWIZB_DISABLEDFINISH);
		}
		
		break;
		
    case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDC_JOIN_PLAYERNAME:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				// set Finish button status 
				if (GetDlgItemText(hDlg, IDC_JOIN_PLAYERNAME, tszPlayerName, MAX_PLAYERNAME) && 
					(htiCur = TreeView_GetSelection(hWndCtl)))
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_FINISH);
				}
				else
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_DISABLEDFINISH);
				}
			}
			break;
		}
		break;
    }
    return (FALSE);
}

/*
 * DlgProcHostSession
 *
 * Dialog proc for Host Session Dialog
 */
BOOL CALLBACK DlgProcHostSession(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static	TCHAR tszSessionName[MAX_SESSIONNAME+1], tszPlayerName[MAX_PLAYERNAME+1];
	HRESULT hr;
	DWORD	dwPNameSize, dwSNameSize;

	switch (msg) {
	case WM_NOTIFY:
		switch (((NMHDR FAR *) lParam)->code) 
		{
			case PSN_SETACTIVE:
				if (GetDlgItemText(hDlg, IDC_HOST_SESSIONNAME, tszSessionName, MAX_SESSIONNAME) && 
					GetDlgItemText(hDlg, IDC_HOST_PLAYERNAME, tszPlayerName, MAX_PLAYERNAME))
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_FINISH);
				}
				else
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_DISABLEDFINISH);
				}
				return(TRUE);
	
			case PSN_WIZFINISH:
				// add user selections to registry
				if (ghDuelKey) 
				{
					RegSet(TEXT("PlayerName"), (CONST BYTE *)tszPlayerName, sizeof(tszPlayerName));
					RegSet(TEXT("SessionName"), (CONST BYTE *)tszSessionName, sizeof(tszSessionName));
				}

				// create session
				if ((hr = DPlayCreateSession(tszSessionName)) != DP_OK)
				{
					// fail finish
					ShowError(IDS_DPLAY_ERROR_CS);
					SetWindowLong(hDlg, DWL_MSGRESULT, -1);
					return (TRUE);
				}

				// create player
				if ((hr = DPlayCreatePlayer(&gOurID, tszPlayerName, NULL, NULL, 0)) != DP_OK)
				{
					ShowError(IDS_DPLAY_ERROR_CP);
					SetWindowLong(hDlg, DWL_MSGRESULT, -1);
					return (TRUE);
				}

				// everything went well, release allocated memory and finish
				ReleaseSPData();
				return(TRUE);
			
			case PSN_WIZBACK:
				SetWindowLong(hDlg, DWL_MSGRESULT, IDD_GAMESETUP);
				return(TRUE);

			case PSN_QUERYCANCEL:
				// release allocated memory
				ReleaseSPData();
				// release dplay
				DPlayRelease();
				return(TRUE);
		}
		break;
	case WM_INITDIALOG:
		// setup title font
		SendDlgItemMessage(hDlg, IDC_HOST_TITLE, WM_SETFONT, (WPARAM)ghTitleFont, MAKELPARAM(TRUE,0));
		SendDlgItemMessage(hDlg, IDC_HOST_SESSION_TITLE, WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0));
		SendDlgItemMessage(hDlg, IDC_HOST_PLAYER_TITLE, WM_SETFONT, (WPARAM)ghHeadingFont, MAKELPARAM(TRUE,0));

		dwPNameSize = MAX_PLAYERNAME+1;
		dwSNameSize = MAX_SESSIONNAME+1;
		tszPlayerName[0]=0;
		tszSessionName[0]=0;
		if (ghDuelKey)
		{
			if (RegGet(TEXT("PlayerName"), (LPBYTE)tszPlayerName, &dwPNameSize) == ERROR_SUCCESS)	
				SetDlgItemText(hDlg, IDC_HOST_PLAYERNAME, tszPlayerName);
			if (RegGet(TEXT("SessionName"), (LPBYTE)tszSessionName, &dwSNameSize) == ERROR_SUCCESS)	
				SetDlgItemText(hDlg, IDC_HOST_SESSIONNAME, tszSessionName);
		}
		
		return(TRUE);

    case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_HOST_SESSIONNAME:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				if (GetDlgItemText(hDlg, IDC_HOST_SESSIONNAME, tszSessionName, MAX_SESSIONNAME) && 
					GetDlgItemText(hDlg, IDC_HOST_PLAYERNAME, tszPlayerName, MAX_PLAYERNAME))
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_FINISH);
				}
				else
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_DISABLEDFINISH);
				}

				return TRUE;
			}
			break;

		case IDC_HOST_PLAYERNAME:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				if (GetDlgItemText(hDlg, IDC_HOST_SESSIONNAME, tszSessionName, MAX_SESSIONNAME) && 
					GetDlgItemText(hDlg, IDC_HOST_PLAYERNAME, tszPlayerName, MAX_PLAYERNAME))
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_FINISH);
				}
				else
				{
					PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK|PSWIZB_DISABLEDFINISH);
				}
			}
			break;
		}
		break;
    }

	return(FALSE);
}

/*
 * InitTreeViewImageLists - creates an image list, adds three bitmaps to 
 *     it, and associates the image list with a tree-view control. 
 * Returns TRUE if successful or FALSE otherwise. 
 * hwndTV - handle of the tree-view control 
 *
 * Global variables and constants 
 *     gnSession, and gnPlayer - integer variables for 
 *         indexes of the images 
 *     CX_BITMAP and CY_BITMAP - width and height of an icon 
 *     NUM_BITMAPS - number of bitmaps to add to the image list 
 */
BOOL InitTreeViewImageLists(HWND hwndTV) 
{ 
    HIMAGELIST himl;  // handle of image list 
    HBITMAP hbmp;     // handle of bitmap 
 
    // Create the image list. 
    if ((himl = ImageList_Create(CX_BITMAP, CY_BITMAP, 
            FALSE, NUM_BITMAPS, 0)) == NULL) 
        return FALSE; 
 
    // Add the session and player bitmaps. 
    hbmp = LoadBitmap(ghinst, MAKEINTRESOURCE(IDB_CLOSED_SESSION)); 
    gnSession = ImageList_Add(himl, hbmp, (HBITMAP) NULL); 
    DeleteObject(hbmp); 
 
    hbmp = LoadBitmap(ghinst, MAKEINTRESOURCE(IDB_PLAYER)); 
    gnPlayer = ImageList_Add(himl, hbmp, (HBITMAP) NULL); 
    DeleteObject(hbmp); 
 
    // Fail if not all of the images were added. 
    if (ImageList_GetImageCount(himl) < 2) 
        return FALSE; 
 
    // Associate the image list with the tree-view control. 
    TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL); 
 
    return TRUE; 
} 
   
HTREEITEM FindItemInTree(HWND hwndTV,LPTREEDATA pdata)
{
	TV_ITEM item;
    HTREEITEM hItem;
    LPTREEDATA psearchdata;
	   
    memset(&item,0,sizeof(item));
    
    // get the first app item (child of the running apps item)
    hItem = (HTREEITEM)SendMessage( hwndTV, TVM_GETNEXTITEM, TVGN_ROOT,(LPARAM) NULL);    
	
    while (hItem)
    {
		// gets its data
    	item.mask = TVIF_PARAM;
    	item.hItem = hItem;
		SendMessage( hwndTV, TVM_GETITEM, 0, (LPARAM)&item );
		// is this the one?
		psearchdata = (LPTREEDATA)item.lParam;
		if (IsEqualGUID(&(psearchdata->guid),&(pdata->guid))) 
		{
			// mark the item as seen
			psearchdata->dwRefresh = 1;
	    	SendMessage( hwndTV, TVM_SETITEM, 0, (LPARAM)&item );
			return hItem;
		}
		// try the next one
    	hItem = (HTREEITEM)SendMessage( hwndTV, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem );    
    }    
	
    return NULL;
    	

	
} // FindItemInTree

/*
 * AddItemToTree - adds items to a tree-view control. 
 * Returns the handle of the newly added item. 
 * hwndTV - handle of the tree-view control 
 * lpszItem - text of the item to add 
 * nLevel - level at which to add the item 
 */
HTREEITEM AddItemToTree(HWND hwndTV, LPTSTR lptszItem, DWORD dwData, int nLevel) 
{ 
    TV_ITEM tvi; 
    TV_INSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    static HTREEITEM hPrevRootItem = NULL; 
    static HTREEITEM hPrevLev2Item = NULL; 
	HTREEITEM hItem;
	
	if (1 == nLevel)
	{
		hItem = FindItemInTree(hwndTV,(LPTREEDATA)dwData);	
		if (hItem) return NULL;
	}
	memset(&tvi,0,sizeof(tvi));
	memset(&tvins,0,sizeof(tvins));

    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	
 	// Set the state
	if (nLevel == 1) 
	{
		tvi.mask |= TVIF_STATE; 
		tvi.state = TVIS_SELECTED;
	}

    // Set the text of the item. 
    tvi.pszText = lptszItem; 
 
   // Set the image
	if (nLevel == 1)
	{
	    tvi.iImage = gnSession; 
		tvi.iSelectedImage = gnSession; 
	}
	else
	{
		tvi.iImage = gnPlayer; 
		tvi.iSelectedImage = gnPlayer; 
	}
 

    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM) dwData; 
 
    tvins.item = tvi; 
    tvins.hInsertAfter = hPrev; 
 
    // Set the parent item based on the specified level. 
    if (nLevel == -1)
		tvins.hParent = hPrevRootItem;
    else if (nLevel == 1) 
        tvins.hParent = TVI_ROOT; 
    else if (nLevel == 2) 
        tvins.hParent = hPrevRootItem; 
	else
        tvins.hParent = hPrevLev2Item; 
 
    // Add the item to the tree-view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTV_INSERTSTRUCT) &tvins); 
 
    // Save the handle of the item. 
    if (nLevel == 1) 
        hPrevRootItem = hPrev; 
    else if (nLevel == 2) 
        hPrevLev2Item = hPrev; 
 
    return hPrev; 
} 
 
/*
 * ReleaseSessionData
 *
 * Releases the memory allocated for session guids
 */
void ReleaseSessionData(HWND hWndCtl)
{
	HTREEITEM htiSession;
	TV_ITEM tvItem;
	TCHAR tszSessionName[MAX_SESSIONNAME+1];


	htiSession = TreeView_GetRoot(hWndCtl);
	while (htiSession)
	{
		tvItem.hItem = htiSession;
		tvItem.pszText = tszSessionName;
		tvItem.cchTextMax = MAX_SESSIONNAME;
		TreeView_GetItem(hWndCtl, &tvItem);
		if (tvItem.lParam) free((LPVOID)tvItem.lParam);
		htiSession = TreeView_GetNextSibling(hWndCtl, htiSession);
	}
}

/*
 * ReleaseSPData
 *
 * Releases the memory allocated for service provider guids
 * depends on global variable ghWndSPControl
 */
void ReleaseSPData(void)
{
	LPVOID lpCon = NULL;
	int count,index;

	if (ghWndSPCtl)
	{
		count = SendMessage(ghWndSPCtl, LB_GETCOUNT, 0, 0);
		for (index = 0; index < count; index++)
		{
			lpCon = (LPVOID) SendMessage(ghWndSPCtl, LB_GETITEMDATA, index, 0);
			if (lpCon) GlobalFreePtr(lpCon);
		}
	}
}
