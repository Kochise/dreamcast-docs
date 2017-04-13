/*==========================================================================
 *
 *  Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dialog.cpp
 *  Content:	Creates a dialog to query the user for connection settings
 *				and establish a connection.
 *
 ***************************************************************************/

#define INITGUID
#include <windows.h>
#include <windowsx.h>
#include <cguid.h>

#include "dpchat.h"
#include "resource.h"

// constants
const DWORD MAXNAMELEN		= 200;		// max size of a session or player name
const UINT	TIMERID			= 1;		// timer ID to use
const UINT	TIMERINTERVAL	= 1000;		// timer interval

// prototypes
BOOL CALLBACK	ConnectWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT			CreateDirectPlayInterface(LPDIRECTPLAY3A *lplpDirectPlay3A );
BOOL FAR PASCAL DirectPlayEnumConnectionsCallback(LPCGUID lpguidSP,
							LPVOID lpConnection, DWORD dwConnectionSize,
							LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext);
HRESULT			DestroyDirectPlayInterface(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A);
HRESULT			HostSession(LPDIRECTPLAY3A lpDirectPlay3A,
							LPSTR lpszSessionName, LPSTR lpszPlayerName,
							LPDPLAYINFO lpDPInfo);
HRESULT			JoinSession(LPDIRECTPLAY3A lpDirectPlay3A,
							LPGUID lpguidSessionInstance, LPSTR lpszPlayerName,
							LPDPLAYINFO lpDPInfo);
HRESULT			EnumSessions(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A);

HRESULT			GetConnection(HWND hWnd, LPVOID *lplpConnection);
void			DeleteConnectionList(HWND hWnd);
HRESULT			GetSessionInstanceGuid(HWND hWnd, LPGUID lpguidSessionInstance);
void			SelectSessionInstance(HWND hWnd, LPGUID lpguidSessionInstance);
void			DeleteSessionInstanceList(HWND hWnd);
void			EnableDlgButton(HWND hDlg, int nIDDlgItem, BOOL bEnable);

HRESULT ConnectUsingDialog(HINSTANCE hInstance, LPDPLAYINFO lpDPInfo)
{
	// ask user for connection settings
	if (DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_CONNECTDIALOG),
					   NULL, (DLGPROC) ConnectWndProc, (LPARAM) lpDPInfo))
	{
		return (DP_OK);
	}
	else
	{
		return (DPERR_USERCANCEL);
	}
}

BOOL CALLBACK ConnectWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPDPLAYINFO		lpDPInfo;
	static LPDIRECTPLAY3A	lpDirectPlay3A;
	static UINT				idTimer;
	GUID					guidSessionInstance;
	char					szSessionName[MAXNAMELEN];
	char					szPlayerName[MAXNAMELEN];
	DWORD					dwNameSize;
	HRESULT					hr;
	LPVOID					lpConnection = NULL;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        // save the connection info pointer
        lpDPInfo = (LPDPLAYINFO) lParam;
		lpDirectPlay3A = NULL;

		// Create an IDirectPlay3 interface
		hr = CreateDirectPlayInterface(&lpDirectPlay3A);
		if (FAILED(hr))
			goto SETUP_FAILURE;

		// set first item in the connections combo box
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_ADDSTRING, (WPARAM) 0, (LPARAM) "<Select a service provider>");
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETITEMDATA, (WPARAM) 0, (LPARAM) 0);
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);

		// put all the available connections in a combo box
		lpDirectPlay3A->EnumConnections(&DPCHAT_GUID, DirectPlayEnumConnectionsCallback, hWnd, 0);

		// setup initial button state
		EnableDlgButton(hWnd, IDC_HOSTBUTTON, FALSE);
		EnableDlgButton(hWnd, IDC_JOINBUTTON, FALSE);
		break;

	SETUP_FAILURE:
		MessageBox(NULL, "This application requires DirectX 5 or later.", NULL, MB_OK);
		EndDialog(hWnd, FALSE);
		break;

    case WM_DESTROY:
		// delete information stored along with the lists
		DeleteConnectionList(hWnd);
		DeleteSessionInstanceList(hWnd);
        break;

	case WM_TIMER:
		// refresh the session list
		hr = EnumSessions(hWnd, lpDirectPlay3A);
		break;

    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
		case IDC_SPCOMBO:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				// service provider changed, so rebuild display and
				// delete any existing DirectPlay interface
				KillTimer(hWnd, idTimer ); 
				hr = DestroyDirectPlayInterface(hWnd, lpDirectPlay3A);
				lpDirectPlay3A = NULL;

				// get pointer to the selected connection
				hr = GetConnection(hWnd, &lpConnection);
				if FAILED(hr)
					goto SP_FAILURE;

				if (lpConnection)
				{
					/*
					 * Create a new DPlay interface.
					 */

					hr = CreateDirectPlayInterface( &lpDirectPlay3A );

					if ((FAILED(hr)) || (NULL == lpDirectPlay3A))
						goto SP_FAILURE;

					// initialize the connection
					hr = lpDirectPlay3A->InitializeConnection(lpConnection, 0);
					if FAILED(hr)
						goto SP_FAILURE;

					// OK to host now
					EnableDlgButton(hWnd, IDC_HOSTBUTTON, TRUE);

					// start enumerating the sessions
					hr = EnumSessions(hWnd, lpDirectPlay3A);
					if FAILED(hr)
						goto SP_FAILURE;

					// set a timer to refresh the session list
					idTimer = SetTimer(hWnd, TIMERID, TIMERINTERVAL, NULL);
				}
				else
				{
					// They've selected the generic option "<Select a service provider>"
					EnableDlgButton(hWnd, IDC_HOSTBUTTON, FALSE);
					EnableDlgButton(hWnd, IDC_JOINBUTTON, FALSE);
				}
				break;
			}
			break;

		SP_FAILURE:
			if (hr != DPERR_USERCANCEL)
				ErrorBox("Could not select service provider because of error 0x%08X", hr);
			break;


		case IDC_HOSTBUTTON:
				// should have an interface by now
			if (lpDirectPlay3A == NULL)
				break;

			KillTimer(hWnd, idTimer ); 
			// use computer name for session name
			dwNameSize = MAXNAMELEN;
			if (!GetComputerName(szSessionName, &dwNameSize))
				lstrcpy(szSessionName, "Session");

			// use user name for player name
			dwNameSize = MAXNAMELEN;
			if (!GetUserName(szPlayerName, &dwNameSize))
				lstrcpy(szPlayerName, "unknown");

			// host a new session on this service provider
			hr = HostSession(lpDirectPlay3A, szSessionName, szPlayerName, lpDPInfo);
			if FAILED(hr)
				goto HOST_FAILURE;

			// dismiss dialog if we succeeded in hosting
			EndDialog(hWnd, TRUE);
			break;

		HOST_FAILURE:
			ErrorBox("Could not host session because of error 0x%08X", hr);
			break;

        case IDC_JOINBUTTON:

			// should have an interface by now
			if (lpDirectPlay3A == NULL)
				break;

			KillTimer(hWnd, idTimer ); 
			// get guid of selected session instance
			hr = GetSessionInstanceGuid(hWnd, &guidSessionInstance);
			if FAILED(hr)
				goto JOIN_FAILURE;

			// use user name for player name
			dwNameSize = MAXNAMELEN;
			if (!GetUserName(szPlayerName, &dwNameSize))
				lstrcpy(szPlayerName, "unknown");

			// join this session
			hr = JoinSession(lpDirectPlay3A, &guidSessionInstance, szPlayerName, lpDPInfo);

			if FAILED(hr)
				goto JOIN_FAILURE;

			// dismiss dialog if we succeeded in joining
			EndDialog(hWnd, TRUE);
            break;

		JOIN_FAILURE:
			ErrorBox("Could not join session because of error 0x%08X", hr);
			break;


        case IDCANCEL:
			KillTimer(hWnd, idTimer ); 
			// delete any interface created if cancelling
			hr = DestroyDirectPlayInterface(hWnd, lpDirectPlay3A);
			lpDirectPlay3A = NULL;

			EndDialog(hWnd, FALSE);
            break;
        }

        break;
    }

    // Allow for default processing
    return FALSE;
}

BOOL FAR PASCAL DirectPlayEnumConnectionsCallback(
						LPCGUID     lpguidSP,
						LPVOID		lpConnection,
						DWORD		dwConnectionSize,
						LPCDPNAME   lpName,
						DWORD 		dwFlags,
						LPVOID 		lpContext)
{

    HWND			hWnd = (HWND) lpContext;
    LRESULT			iIndex;
	LPVOID			lpConnectionBuffer;

	// store service provider name in combo box
	iIndex = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_ADDSTRING, 0, 
									(LPARAM) lpName->lpszShortNameA);
	if (iIndex == CB_ERR)
		goto FAILURE;

	// make space for connection shortcut
	lpConnectionBuffer = GlobalAllocPtr(GHND, dwConnectionSize);
	if (lpConnectionBuffer == NULL)
		goto FAILURE;

	// store pointer to connection shortcut in combo box
	memcpy(lpConnectionBuffer, lpConnection, dwConnectionSize);
	SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETITEMDATA, (WPARAM) iIndex, 
									(LPARAM) lpConnectionBuffer);

FAILURE:
    return (TRUE);
}


HRESULT CreateDirectPlayInterface( LPDIRECTPLAY3A *lplpDirectPlay3A )
{
	HRESULT				hr;
	LPDIRECTPLAY3A		lpDirectPlay3A = NULL;

	// Create an IDirectPlay3 interface
	hr = CoCreateInstance(	CLSID_DirectPlay, NULL, CLSCTX_INPROC_SERVER, 
							IID_IDirectPlay3A, (LPVOID*)&lpDirectPlay3A);

	// return interface created
	*lplpDirectPlay3A = lpDirectPlay3A;

	return (hr);
}


HRESULT DestroyDirectPlayInterface(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A)
{
	HRESULT		hr = DP_OK;

	if (lpDirectPlay3A)
	{
		DeleteSessionInstanceList(hWnd);
		EnableDlgButton(hWnd, IDC_JOINBUTTON, FALSE);

		hr = lpDirectPlay3A->Release();
	}

	return (hr);
}

HRESULT HostSession(LPDIRECTPLAY3A lpDirectPlay3A,
					LPSTR lpszSessionName, LPSTR lpszPlayerName,
					LPDPLAYINFO lpDPInfo)
{
	DPID				dpidPlayer;
	DPNAME				dpName;
	DPSESSIONDESC2		sessionDesc;
	HRESULT				hr;

	// check for valid interface
	if (lpDirectPlay3A == NULL)
		return (DPERR_INVALIDOBJECT);

	// host a new session
	ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
	sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
    sessionDesc.dwFlags = DPSESSION_MIGRATEHOST | DPSESSION_KEEPALIVE;
    sessionDesc.guidApplication = DPCHAT_GUID;
    sessionDesc.dwMaxPlayers = MAXPLAYERS;
	sessionDesc.lpszSessionNameA = lpszSessionName;

	hr = lpDirectPlay3A->Open(&sessionDesc, DPOPEN_CREATE);
	if FAILED(hr)
		goto OPEN_FAILURE;

	// fill out name structure
	ZeroMemory(&dpName, sizeof(DPNAME));
	dpName.dwSize = sizeof(DPNAME);
	dpName.lpszShortNameA = lpszPlayerName;
	dpName.lpszLongNameA = NULL;

	// create a player with this name
	hr = lpDirectPlay3A->CreatePlayer(&dpidPlayer, &dpName, 
							lpDPInfo->hPlayerEvent, NULL, 0, 0);
	if FAILED(hr)
		goto CREATEPLAYER_FAILURE;

	// return connection info
	lpDPInfo->lpDirectPlay3A = lpDirectPlay3A;
	lpDPInfo->dpidPlayer = dpidPlayer;
	lpDPInfo->bIsHost = TRUE;

	return (DP_OK);

CREATEPLAYER_FAILURE:
OPEN_FAILURE:
	lpDirectPlay3A->Close();
	return (hr);
}

HRESULT JoinSession(LPDIRECTPLAY3A lpDirectPlay3A,
					LPGUID lpguidSessionInstance, LPSTR lpszPlayerName,
					LPDPLAYINFO lpDPInfo)
{
	DPID				dpidPlayer;
	DPNAME				dpName;
	DPSESSIONDESC2		sessionDesc;
	HRESULT				hr;

	// check for valid interface
	if (lpDirectPlay3A == NULL)
		return (DPERR_INVALIDOBJECT);

	// join existing session
	ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
	sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
    sessionDesc.guidInstance = *lpguidSessionInstance;

	hr = lpDirectPlay3A->Open(&sessionDesc, DPOPEN_JOIN);
	if FAILED(hr)
		goto OPEN_FAILURE;

	// fill out name structure
	ZeroMemory(&dpName, sizeof(DPNAME));
	dpName.dwSize = sizeof(DPNAME);
	dpName.lpszShortNameA = lpszPlayerName;
	dpName.lpszLongNameA = NULL;

	// create a player with this name
	hr = lpDirectPlay3A->CreatePlayer(&dpidPlayer, &dpName, 
							lpDPInfo->hPlayerEvent, NULL, 0, 0);
	if FAILED(hr)
		goto CREATEPLAYER_FAILURE;

	// return connection info
	lpDPInfo->lpDirectPlay3A = lpDirectPlay3A;
	lpDPInfo->dpidPlayer = dpidPlayer;
	lpDPInfo->bIsHost = FALSE;

	return (DP_OK);

CREATEPLAYER_FAILURE:
OPEN_FAILURE:
	lpDirectPlay3A->Close();
	return (hr);
}

BOOL FAR PASCAL EnumSessionsCallback(
						LPCDPSESSIONDESC2	lpSessionDesc,
						LPDWORD				lpdwTimeOut,
						DWORD				dwFlags,
						LPVOID				lpContext)
{
	HWND			hWnd = (HWND) lpContext;
	LPGUID			lpGuid;
	LONG			iIndex;

	// see if last session has been enumerated
    if (dwFlags & DPESC_TIMEDOUT)
		return (FALSE);						

	// store session name in list
	iIndex = SendDlgItemMessage( hWnd, IDC_SESSIONLIST, LB_ADDSTRING, 
								(WPARAM) 0, (LPARAM) lpSessionDesc->lpszSessionNameA);

	if (iIndex == LB_ERR)
		goto FAILURE;


	// make space for session instance guid
	lpGuid = (LPGUID) GlobalAllocPtr( GHND, sizeof(GUID) );
	if (lpGuid == NULL)
		goto FAILURE;

	// store pointer to guid in list
	*lpGuid = lpSessionDesc->guidInstance;
	SendDlgItemMessage( hWnd, IDC_SESSIONLIST, LB_SETITEMDATA, (WPARAM) iIndex, (LPARAM) lpGuid);

FAILURE:
    return (TRUE);
}

HRESULT EnumSessions(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A)
{
	DPSESSIONDESC2	sessionDesc;
	GUID			guidSessionInstance;
	LONG			iIndex;
	HRESULT			hr;

	// check for valid interface
	if (lpDirectPlay3A == NULL)
		return (DPERR_INVALIDOBJECT);

	// get guid of currently selected session
	guidSessionInstance = GUID_NULL;
	hr = GetSessionInstanceGuid(hWnd, &guidSessionInstance);

	// delete existing session list
	DeleteSessionInstanceList(hWnd);

	// add sessions to session list
	ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
	sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
    sessionDesc.guidApplication = DPCHAT_GUID;

	hr = lpDirectPlay3A->EnumSessions(&sessionDesc, 0, EnumSessionsCallback,
									  hWnd, DPENUMSESSIONS_AVAILABLE | DPENUMSESSIONS_ASYNC);

	// select the session that was previously selected
	SelectSessionInstance(hWnd, &guidSessionInstance);

	// hilite "Join" button only if there are sessions to join
	iIndex = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_GETCOUNT,
						   (WPARAM) 0, (LPARAM) 0);

	EnableDlgButton(hWnd, IDC_JOINBUTTON, (iIndex > 0) ? TRUE : FALSE);

	return (hr);
}

HRESULT GetConnection(HWND hWnd, LPVOID *lplpConnection)
{
	LONG	iIndex;

	// get index of the item currently selected in the combobox
	iIndex = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_GETCURSEL,
								(WPARAM) 0, (LPARAM) 0);
	if (iIndex == CB_ERR)
		return (DPERR_GENERIC);

	// get the pointer to the connection shortcut associated with
	// the item
	iIndex = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_GETITEMDATA,
								(WPARAM) iIndex, (LPARAM) 0);
	if (iIndex == CB_ERR)
		return (DPERR_GENERIC);

	*lplpConnection = (LPVOID) iIndex;

	return (DP_OK);
}

void DeleteConnectionList(HWND hWnd)
{
	WPARAM	i;
	LONG	lpData;
	
	// destroy the GUID's stored with each service provider name
	i = 0;
	while (TRUE)
	{
		// get data pointer stored with item
		lpData = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_GETITEMDATA,
									(WPARAM) i, (LPARAM) 0);
		if (lpData == CB_ERR)		// error getting data
			break;

		if (lpData != 0)			// no data to delete
			GlobalFreePtr((LPVOID) lpData);

		i += 1;
	}

	// delete all items in combo box
	SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_RESETCONTENT,
								(WPARAM) 0, (LPARAM) 0);
}

HRESULT GetSessionInstanceGuid(HWND hWnd, LPGUID lpguidSessionInstance)
{
	LONG	iIndex;

	// get guid for session
	iIndex = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_GETCURSEL,
								(WPARAM) 0, (LPARAM) 0);
	if (iIndex == LB_ERR)
		return (DPERR_GENERIC);

	iIndex = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_GETITEMDATA,
								(WPARAM) iIndex, (LPARAM) 0);
	if ((iIndex == LB_ERR) || (iIndex == 0))
		return (DPERR_GENERIC);

	*lpguidSessionInstance = *((LPGUID) iIndex);

	return (DP_OK);
}

void DeleteSessionInstanceList(HWND hWnd)
{
	WPARAM	i;
	LONG	lpData;
	
	// destroy the GUID's stored with each session name
	i = 0;
	while (TRUE)
	{
		// get data pointer stored with item
		lpData = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_GETITEMDATA,
									(WPARAM) i, (LPARAM) 0);
		if (lpData == CB_ERR)		// error getting data
			break;

		if (lpData == 0)			// no data to delete
			continue;

		GlobalFreePtr((LPVOID) lpData);
		i += 1;
	}

	// delete all items in list
	SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_RESETCONTENT,
								(WPARAM) 0, (LPARAM) 0);
}

void SelectSessionInstance(HWND hWnd, LPGUID lpguidSessionInstance)
{
	WPARAM	i, iIndex;
	LONG	lpData;
	
	// loop over the GUID's stored with each session name
	// to find the one that matches what was passed in
	i = 0;
	iIndex = 0;
	while (TRUE)
	{
		// get data pointer stored with item
		lpData = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_GETITEMDATA,
									(WPARAM) i, (LPARAM) 0);
		if (lpData == CB_ERR)		// error getting data
			break;

		if (lpData == 0)			// no data to compare to
			continue;

		// guid matches
		if (IsEqualGUID(*lpguidSessionInstance, *((LPGUID) lpData)))
		{
			iIndex = i;				// store index of this string
			break;
		}

		i += 1;
	}

	// select this item
	SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_SETCURSEL, (WPARAM) iIndex, (LPARAM) 0);
}

void EnableDlgButton(HWND hDlg, int nIDDlgItem, BOOL bEnable)
{
	EnableWindow(GetDlgItem(hDlg, nIDDlgItem), bEnable);
}
