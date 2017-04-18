/*==========================================================================
 *
 *  Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dialog.cpp
 *  Content:	Creates a dialog to query the user for connection settings
 *				and establish a connection.
 *
 ***************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <cguid.h>

#include "bellhop.h"
#include "resource.h"

// constants
const DWORD MAXNAMELEN		= 200;		// max size of a session or player name
const UINT	TIMERID			= 1;		// timer ID to use
const UINT	TIMERINTERVAL	= 1000;		// timer interval

// prototypes
BOOL CALLBACK	ConnectWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK	SecurityCredentialsWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT			CreateDirectPlayInterface(LPDIRECTPLAY3A *lplpDirectPlay3A );
HRESULT			CreateDirectPlayLobbyInterface(LPDIRECTPLAYLOBBY2A *lplpDirectPlayLobby2A );
BOOL FAR PASCAL DirectPlayEnumConnectionsCallback(LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwSize, LPCDPNAME lpName, 
												  DWORD dwFlags, LPVOID lpContext);
HRESULT			DestroyDirectPlayInterface(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A);
HRESULT			DestroyDirectPlayLobbyInterface(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDirectPlayLobby2A);
HRESULT JoinSession(HWND hWnd,
					LPDIRECTPLAY3A lpDirectPlay3A,
					LPDIRECTPLAYLOBBY2A lpDirectPlayLobby2A,
					LPGUID lpguidSessionInstance,
					DWORD	dwSessionFlags,
					LPSTR lpszPlayerName,
					DWORD	dwPlayerFlags,
					LPDPLAYINFO lpDPInfo);

HRESULT			EnumSessions(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A);

HRESULT			GetConnection(HWND hWnd,  int idCombo, LPVOID *lplpConnection);
HRESULT			GetConnectionSPGuid(HWND hWnd, int idCombo, GUID *lpGuidSP);
void			DeleteConnectionList(HWND hWnd);
HRESULT			GetSessionInfo(HWND hWnd, LPGUID lpguidSessionInstance, LPDWORD lpdwFlags);
void			SelectSessionInstance(HWND hWnd, LPGUID lpguidSessionInstance);
void			DeleteSessionInstanceList(HWND hWnd);
void			EnableDlgButton(HWND hDlg, int nIDDlgItem, BOOL bEnable);


///////////////////////////////////////////////////////////////////////////////////////
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


///////////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK ConnectWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPDPLAYINFO			lpDPInfo;
	static LPDIRECTPLAY3A		lpDirectPlay3A;
	static LPDIRECTPLAYLOBBY2A	lpDirectPlayLobby2A;
	static UINT					idTimer;
	GUID						guidSessionInstance;
	char						szPlayerName[MAXNAMELEN];
	DWORD						dwNameSize;
	HRESULT						hr;
	LPVOID						lpConnection = NULL;
	ENUMCONNSTRUCT				enStruct;
	DWORD						dwSessionFlags;
	DWORD						dwPlayerFlags = NULL;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        // save the connection info pointer
        lpDPInfo = (LPDPLAYINFO) lParam;
		lpDirectPlay3A = NULL;
		lpDirectPlayLobby2A = NULL;

		// Create an IDirectPlay3 interface
		hr = CreateDirectPlayInterface(&lpDirectPlay3A);
		if FAILED(hr)
			goto SETUP_FAILURE;

		// Create an IDirectLobby2 interface
		hr = CreateDirectPlayLobbyInterface(&lpDirectPlayLobby2A);
		if FAILED(hr)
			goto SETUP_FAILURE;

		// set first item in the connections combo box
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_ADDSTRING, (WPARAM) 0, (LPARAM) "<Select a lobby provider>");
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETITEMDATA, (WPARAM) 0, (LPARAM) 0);
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);

		// put all the available connections in a combo box
		enStruct.hWnd = hWnd;
		enStruct.idCombo = IDC_SPCOMBO;

		IDirectPlay3_EnumConnections(lpDirectPlay3A, &BELLHOP_GUID, DirectPlayEnumConnectionsCallback,
				&enStruct, DPCONNECTION_DIRECTPLAYLOBBY);

		// setup initial button state
		EnableDlgButton(hWnd, IDC_JOINBUTTON, FALSE);
		EnableDlgButton(hWnd, IDC_SPECTATORBUTTON, FALSE);
		break;

	SETUP_FAILURE:
		ErrorBox("Could not create DirectPlay object because of error 0x%08X", hr);
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
				hr = GetConnection(hWnd, IDC_SPCOMBO, &lpConnection);
				if FAILED(hr)
					goto SP_FAILURE;

				if (lpConnection)
				{
				  // Create a new DPlay interface.
					hr = CreateDirectPlayInterface(&lpDirectPlay3A);

					if ((FAILED(hr)) || (NULL == lpDirectPlay3A))
						goto SP_FAILURE;

					// initialize the connection
					hr = IDirectPlay3_InitializeConnection(lpDirectPlay3A, lpConnection, 0);
					if FAILED(hr)
						goto SP_FAILURE;

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
					EnableDlgButton(hWnd, IDC_JOINBUTTON, FALSE);
					EnableDlgButton(hWnd, IDC_SPECTATORBUTTON, FALSE);
				}
				break;
			}
			break;

		SP_FAILURE:
			if (hr != DPERR_USERCANCEL)
				ErrorBox("Could not select service provider because of error 0x%08X", hr);
			break;


        case IDC_SPECTATORBUTTON:
			// Joining as a spectator is the same as a regular join
			// just with different flags.
			dwPlayerFlags = DPPLAYER_SPECTATOR;
			// Fall through to case IDC_JOINBUTTON:
        case IDC_JOINBUTTON:

			// should have an interface by now
			if (lpDirectPlay3A == NULL)
				break;

		    KillTimer(hWnd, idTimer ); 
			// get guid of selected session instance

			hr = GetSessionInfo(hWnd, &guidSessionInstance, &dwSessionFlags);
			if FAILED(hr)
				goto JOIN_FAILURE;

			// use computer name for player name
			dwNameSize = MAXNAMELEN;
			if (!GetComputerName(szPlayerName, &dwNameSize))
				lstrcpy(szPlayerName, "unknown");
			_strlwr(szPlayerName);

			// join this session
			hr = JoinSession(	hWnd,
								lpDirectPlay3A,
								 lpDirectPlayLobby2A, 
								 &guidSessionInstance,
								 dwSessionFlags,
								 szPlayerName, 
								 dwPlayerFlags,
								 lpDPInfo);

			if FAILED(hr)
				goto JOIN_FAILURE;

			// dismiss dialog if we succeeded in joining
			EndDialog(hWnd, TRUE);
            break;

		JOIN_FAILURE:
			ErrorBox("Could not join session because of error 0x%08X", hr);
			break;


        case IDCANCEL:
			// delete any interface created if cancelling
			KillTimer(hWnd, idTimer ); 
			hr = DestroyDirectPlayInterface(hWnd, lpDirectPlay3A);
			lpDirectPlay3A = NULL;

			hr = DestroyDirectPlayLobbyInterface(hWnd, lpDirectPlayLobby2A);
			lpDirectPlayLobby2A = NULL;

			EndDialog(hWnd, FALSE);
            break;
        }

        break;
    }

    // Allow for default processing
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////
BOOL FAR PASCAL DirectPlayEnumConnectionsCallback(
						LPCGUID			lpguidSP,
						LPVOID			lpConnection,
						DWORD			dwSize,
						LPCDPNAME		lpName,
						DWORD			dwFlags,
						LPVOID			lpContext)
{
	LPENUMCONNSTRUCT	lp = (LPENUMCONNSTRUCT) lpContext;
    LRESULT			iIndex;
	LPCONNECTIONINFO	lpConnectionBuffer = NULL;

	// store service provider name in combo box
	iIndex = SendDlgItemMessage(lp->hWnd, lp->idCombo, CB_ADDSTRING, 0, 
									(LPARAM) lpName->lpszShortNameA);
	if (iIndex == CB_ERR)
		goto FAILURE;

	// make space for Connection Shortcut
	lpConnectionBuffer = (LPCONNECTIONINFO) GlobalAllocPtr(GHND, dwSize+sizeof(CONNECTIONINFO));
	if (lpConnectionBuffer == NULL)
		goto FAILURE;

	// store pointer to GUID in combo box
	memcpy(lpConnectionBuffer->Connection, lpConnection, dwSize);
	lpConnectionBuffer->guidSP = *lpguidSP;
	SendDlgItemMessage(lp->hWnd, lp->idCombo, CB_SETITEMDATA, (WPARAM) iIndex, 
									(LPARAM) lpConnectionBuffer);

FAILURE:
    return (TRUE);
}


///////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CreateDirectPlayLobbyInterface( LPDIRECTPLAYLOBBY2A *lplpDirectPlayLobby2A )
{
	HRESULT				hr;
	LPDIRECTPLAYLOBBY2A		lpDirectPlayLobby2A = NULL;

	// Create an IDirectPlay3 interface
	hr = CoCreateInstance(	CLSID_DirectPlayLobby, NULL, CLSCTX_INPROC_SERVER, 
							IID_IDirectPlayLobby2A, (LPVOID*)&lpDirectPlayLobby2A);

	// return interface created
	*lplpDirectPlayLobby2A = lpDirectPlayLobby2A;

	return (hr);
}


///////////////////////////////////////////////////////////////////////////////////////
HRESULT DestroyDirectPlayInterface(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A)
{
	HRESULT		hr = DP_OK;

	if (lpDirectPlay3A)
	{
		DeleteSessionInstanceList(hWnd);
		EnableDlgButton(hWnd, IDC_JOINBUTTON, FALSE);
		EnableDlgButton(hWnd, IDC_SPECTATORBUTTON, FALSE);

		hr = IDirectPlay3_Release(lpDirectPlay3A);
	}

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT DestroyDirectPlayLobbyInterface(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDirectPlayLobby2A)
{
	HRESULT		hr = DP_OK;

	if (lpDirectPlayLobby2A)
	{
		hr = lpDirectPlayLobby2A->Release();
	}

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT JoinSession(HWND hWnd,
					LPDIRECTPLAY3A lpDirectPlay3A,
					LPDIRECTPLAYLOBBY2A lpDirectPlayLobby2A,
					LPGUID lpguidSessionInstance,
					DWORD	dwSessionFlags,
					LPSTR lpszPlayerName,
					DWORD	dwPlayerFlags,
					LPDPLAYINFO lpDPInfo)
{
	DPID				dpidPlayer;
	DPNAME				dpName;
	DPSESSIONDESC2		sessionDesc;
	HRESULT				hr;

	// check for valid interface
	if (lpDirectPlay3A == NULL)
		return (DPERR_INVALIDOBJECT);

	// Spectator or regular player
	lpDPInfo->dwPlayerFlags = dwPlayerFlags;

	// prepare a session description
	ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
	sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
    sessionDesc.guidInstance = *lpguidSessionInstance;
	sessionDesc.dwFlags = dwSessionFlags;

	if (DPSESSION_SECURESERVER & dwSessionFlags )
	{
		hr = IDirectPlay3_SecureOpen(	lpDirectPlay3A,
										&sessionDesc,
										DPOPEN_JOIN,
										NULL,
										NULL );

		if ( DPERR_LOGONDENIED == hr )
		{

			// we need to collect security credentials
			// and try again.

			if (DialogBoxParam( ghInstance, 
								MAKEINTRESOURCE(IDD_SECURITYCREDENTIALSDIALOG), 
								hWnd,
								(DLGPROC) SecurityCredentialsWndProc, 
								(LPARAM) &lpDPInfo))
			{

				DPCREDENTIALS dpcr;
				dpcr.dwSize = sizeof(DPCREDENTIALS);
				dpcr.dwFlags = 0;
				dpcr.lpszUsernameA = lpDPInfo->szSecureName;
				dpcr.lpszPasswordA = lpDPInfo->szSecurePassword;
				dpcr.lpszDomainA = lpDPInfo->szSecureDomain;

				hr = IDirectPlay3_SecureOpen(	lpDirectPlay3A,
												&sessionDesc,
												DPOPEN_JOIN,
												NULL,
												&dpcr );
				if (FAILED(hr))
				{
					// Conceivably, we could cycle back and try to get credentials again
					// but in this sample, we'll just drop out on the error.
					goto OPEN_FAILURE;
				}

				lpDPInfo->bSecureSession = TRUE;
			}
			else
			{
				// abort. user clicked cancel.
				goto OPEN_FAILURE;
			}
		}
	}
	else
	{
		// Session does not require security
		hr = IDirectPlay3_Open(lpDirectPlay3A, &sessionDesc, DPOPEN_JOIN);
		if FAILED(hr)
			goto OPEN_FAILURE;
	}

	// fill out name structure
	ZeroMemory(&dpName, sizeof(DPNAME));
	dpName.dwSize = sizeof(DPNAME);
	dpName.lpszShortNameA = lpszPlayerName;
	dpName.lpszLongNameA = NULL;

	// create a player with this name
	hr = IDirectPlay3_CreatePlayer(lpDirectPlay3A, &dpidPlayer, &dpName, 
							lpDPInfo->hPlayerEvent,
							NULL, 0, dwPlayerFlags );
	if FAILED(hr)
		goto CREATEPLAYER_FAILURE;

	// return connection info
	lpDPInfo->lpDirectPlay3A = lpDirectPlay3A;
	lpDPInfo->lpDirectPlayLobby2A = lpDirectPlayLobby2A;

	lpDPInfo->dpidPlayer = dpidPlayer;
	lpDPInfo->bIsHost = FALSE;

	return (DP_OK);

CREATEPLAYER_FAILURE:
OPEN_FAILURE:
	IDirectPlay3_Close(lpDirectPlay3A);
	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
BOOL FAR PASCAL EnumSessionsCallback(
						LPCDPSESSIONDESC2	lpSessionDesc,
						LPDWORD				lpdwTimeOut,
						DWORD				dwFlags,
						LPVOID				lpContext)
{
	HWND				hWnd = (HWND) lpContext;
	LONG				iIndex;
	char				szBuffer[256];
	LPSESSIONINFO	lpSessionInfo = NULL;

	// see if last session has been enumerated
    if (dwFlags & DPESC_TIMEDOUT)
		return (FALSE);						

	wsprintf(	szBuffer, 
				(DPSESSION_SECURESERVER & lpSessionDesc->dwFlags ? "%s (SECURE)" : "%s" ),
				lpSessionDesc->lpszSessionNameA );

	// store session name in list
	iIndex = SendDlgItemMessage( hWnd, IDC_SESSIONLIST, LB_ADDSTRING, 
								(WPARAM) 0, (LPARAM) szBuffer);

	if (iIndex == LB_ERR)
		goto FAILURE;


	// make space for session instance guid
	lpSessionInfo = (LPSESSIONINFO) GlobalAllocPtr( GHND, sizeof(SESSIONINFO) );
	if (lpSessionInfo == NULL)
		goto FAILURE;

	// Extract the data we need from the session description
	lpSessionInfo->guidInstance = lpSessionDesc->guidInstance;
	lpSessionInfo->dwFlags = lpSessionDesc->dwFlags;

	// store pointer to guid in list
	SendDlgItemMessage( hWnd, IDC_SESSIONLIST, LB_SETITEMDATA, (WPARAM) iIndex, (LPARAM) lpSessionInfo);

FAILURE:
    return (TRUE);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT EnumSessions(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A)
{
	DPSESSIONDESC2	sessionDesc;
	GUID			guidSessionInstance;
	DWORD			dwFlags;
	LONG			iIndex;
	HRESULT			hr;

	// check for valid interface
	if (lpDirectPlay3A == NULL)
		return (DPERR_INVALIDOBJECT);

	// get guid of currently selected session
	guidSessionInstance = GUID_NULL;
	hr = GetSessionInfo(hWnd, &guidSessionInstance, &dwFlags);

	// delete existing session list
	DeleteSessionInstanceList(hWnd);

	// add sessions to session list
	ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
	sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
    sessionDesc.guidApplication = BELLHOP_GUID;

	hr = IDirectPlay3_EnumSessions(lpDirectPlay3A, &sessionDesc, 0, EnumSessionsCallback,
									  hWnd, DPENUMSESSIONS_AVAILABLE | DPENUMSESSIONS_ASYNC);

	// select the session that was previously selected
	SelectSessionInstance(hWnd, &guidSessionInstance);

	// hilite "Join" button only if there are sessions to join
	iIndex = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_GETCOUNT,
						   (WPARAM) 0, (LPARAM) 0);

	EnableDlgButton(hWnd, IDC_JOINBUTTON, (iIndex > 0) ? TRUE : FALSE);
	EnableDlgButton(hWnd, IDC_SPECTATORBUTTON, (iIndex > 0) ? TRUE : FALSE);

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT GetConnection(HWND hWnd, int idCombo, LPVOID *lplpConnection)
{
	LONG	iIndex;

	// get index of the item currently selected in the combobox
	iIndex = SendDlgItemMessage(hWnd,  idCombo, CB_GETCURSEL,
								(WPARAM) 0, (LPARAM) 0);
	if (iIndex == CB_ERR)
		return (DPERR_GENERIC);

	// get the pointer to the connection shortcut associated with
	// the item
	iIndex = SendDlgItemMessage(hWnd, idCombo, CB_GETITEMDATA,
								(WPARAM) iIndex, (LPARAM) 0);

	if ((CB_ERR == iIndex) || ( NULL == iIndex ))
		return (DPERR_GENERIC);

	*lplpConnection = &((LPCONNECTIONINFO) iIndex)->Connection;

	return (DP_OK);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT GetConnectionSPGuid(HWND hWnd, int idCombo, GUID *lpGuidSP)
{
	LONG	iIndex;

	// get index of the item currently selected in the combobox
	iIndex = SendDlgItemMessage(hWnd,  idCombo, CB_GETCURSEL,
								(WPARAM) 0, (LPARAM) 0);
	if (iIndex == CB_ERR)
		return (DPERR_GENERIC);

	// get the pointer to the connection shortcut associated with
	// the item
	iIndex = SendDlgItemMessage(hWnd, idCombo, CB_GETITEMDATA,
								(WPARAM) iIndex, (LPARAM) 0);

	if ((iIndex == CB_ERR) || (iIndex == NULL ))
		return (DPERR_GENERIC);

	*lpGuidSP = ((LPCONNECTIONINFO) iIndex)->guidSP;

	return (DP_OK);
}

///////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////
HRESULT GetSessionInfo(HWND hWnd, LPGUID lpguidSessionInstance, LPDWORD lpdwFlags)
{
	LONG			iIndex;
	LPSESSIONINFO	lp;

	// get guid for session
	iIndex = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_GETCURSEL,
								(WPARAM) 0, (LPARAM) 0);
	if (iIndex == LB_ERR)
		return (DPERR_GENERIC);

	iIndex = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_GETITEMDATA,
								(WPARAM) iIndex, (LPARAM) 0);
	if ((iIndex == LB_ERR) || (iIndex == 0))
		return (DPERR_GENERIC);

	lp = (LPSESSIONINFO) iIndex;
	*lpguidSessionInstance = lp->guidInstance;
	*lpdwFlags = lp->dwFlags;

	return (DP_OK);
}

///////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////
void EnableDlgButton(HWND hDlg, int nIDDlgItem, BOOL bEnable)
{
	EnableWindow(GetDlgItem(hDlg, nIDDlgItem), bEnable);
}

///////////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK SecurityCredentialsWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPDPLAYINFO			lpDPInfo;
	HWND				hwndName		= NULL,
						hwndPassword	= NULL,
						hwndDomain		= NULL;


    switch(uMsg)
    {
    case WM_INITDIALOG:
        lpDPInfo = (LPDPLAYINFO) lParam;
		break;

    case WM_COMMAND:

      switch(LOWORD(wParam))
        {
		case IDOK:
			hwndName = GetDlgItem( hWnd, IDC_SECURENAME );
			hwndPassword = GetDlgItem( hWnd, IDC_SECUREPASSWORD );
			hwndDomain = GetDlgItem( hWnd, IDC_SECUREDOMAIN );

			Edit_GetText(hwndName, lpDPInfo->szSecureName, 256);
			Edit_GetText(hwndPassword, lpDPInfo->szSecurePassword, 256);
			Edit_GetText(hwndDomain, lpDPInfo->szSecureDomain, 256);
			EndDialog(hWnd, TRUE);
			break;

        case IDCANCEL:
			EndDialog(hWnd, FALSE);
            break;
        }

        break;
    }

    // Allow for default processing
    return FALSE;
}

