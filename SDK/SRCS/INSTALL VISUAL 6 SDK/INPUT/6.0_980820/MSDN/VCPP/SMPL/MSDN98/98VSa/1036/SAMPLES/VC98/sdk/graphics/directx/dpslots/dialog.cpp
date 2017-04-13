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

#include "dpslots.h"
#include "resource.h"

// constants
const UINT	TIMERID			= 1;		// timer ID to use
const UINT	TIMERINTERVAL	= 1000;		// timer interval

// structures

// server configuration information
typedef struct {
	CHAR		szServerName[MAXSTRLEN];
	CHAR		szDatabaseFile[MAXSTRLEN];
	CHAR		szSecurityProvider[MAXSTRLEN];
	BOOL		bRequireSecureLogin;
} SERVERCONFIG, *LPSERVERCONFIG;

// client login information
typedef struct {
	CHAR		szPlayerName[MAXSTRLEN];
	CHAR		szUserName[MAXSTRLEN];
	CHAR		szPassword[MAXSTRLEN];
	CHAR		szDomain[MAXSTRLEN];
} CLIENTLOGIN, *LPCLIENTLOGIN;

// prototypes
BOOL CALLBACK	ConnectWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT			CreateDirectPlayInterface(LPDIRECTPLAY3A *lplpDirectPlay3A );
BOOL FAR PASCAL DirectPlayEnumConnectionsCallback(LPCGUID lpguidSP,
							LPVOID lpConnection, DWORD dwConnectionSize,
							LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext);
HRESULT			DestroyDirectPlayInterface(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A);
HRESULT			HostSession(LPDIRECTPLAY3A lpDirectPlay3A,
							LPSERVERCONFIG lpServerConfig,
							LPDPLAYINFO lpDPInfo);
HRESULT			JoinSession(LPDIRECTPLAY3A lpDirectPlay3A,
							LPGUID lpguidSessionInstance,
							LPCLIENTLOGIN lpClientLogin,
							LPDPLAYINFO lpDPInfo);
HRESULT			EnumSessions(HWND hWnd, LPDIRECTPLAY3A lpDirectPlay3A);

HRESULT			GetConnection(HWND hWnd, LPVOID *lplpConnection);
void			DeleteConnectionList(HWND hWnd);
HRESULT			GetSessionInstanceGuid(HWND hWnd, LPGUID lpguidSessionInstance);
void			SelectSessionInstance(HWND hWnd, LPGUID lpguidSessionInstance);
void			DeleteSessionInstanceList(HWND hWnd);
BOOL			GetServerConfig(HWND hWnd, LPSERVERCONFIG lpServerConfig);
BOOL			GetClientLogin(HWND hWnd, LPCLIENTLOGIN lpClientLogin);
HRESULT			GetSessionDesc(LPDIRECTPLAY3A lpDirectPlay3A, LPDPSESSIONDESC2 *lplpSessionDesc);

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
	SERVERCONFIG			serverConfig;
	CLIENTLOGIN				clientLogin;
	LPVOID					lpConnection = NULL;
	DWORD					dwNameSize;
	HRESULT					hr;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        // save the connection info pointer
        lpDPInfo = (LPDPLAYINFO) lParam;
		lpDirectPlay3A = NULL;

		// Create an IDirectPlay3 interface
		hr = CreateDirectPlayInterface( &lpDirectPlay3A );

		if (FAILED(hr))
			goto SETUP_FAILURE;

		// set first item in the connections combo box
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_ADDSTRING, (WPARAM) 0, (LPARAM) "<Select a service provider>");
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETITEMDATA, (WPARAM) 0, (LPARAM) 0);
		SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);

		// put all the available connections in a combo box
		lpDirectPlay3A->EnumConnections(&DPSLOTS_GUID, DirectPlayEnumConnectionsCallback, hWnd, 0);

		// setup initial button state
		EnableDlgButton(hWnd, IDC_HOSTBUTTON, FALSE);
		EnableDlgButton(hWnd, IDC_JOINBUTTON, FALSE);
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
				hr = GetConnection(hWnd, &lpConnection);
				if FAILED(hr)
					goto SP_FAILURE;

				if (lpConnection)
				{
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

			// get server configuration from user
			ZeroMemory(&serverConfig, sizeof(SERVERCONFIG));
			if (!GetServerConfig(hWnd, &serverConfig))
				break;

			// host a new session on this service provider
			hr = HostSession(lpDirectPlay3A, &serverConfig, lpDPInfo);
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

			// get guid of selected session instance
			hr = GetSessionInstanceGuid(hWnd, &guidSessionInstance);
			if FAILED(hr)
				goto JOIN_FAILURE;

			// get server configuration from user
			ZeroMemory(&clientLogin, sizeof(CLIENTLOGIN));

			// use user name for player name
			dwNameSize = MAXSTRLEN;
			GetUserName(clientLogin.szPlayerName, &dwNameSize);
						
			// join this session
			hr = JoinSession(lpDirectPlay3A, &guidSessionInstance, &clientLogin, lpDPInfo);

			// need to ask user for credentials
			if (hr == DPERR_LOGONDENIED)
			{
				if (!GetClientLogin(hWnd, &clientLogin))
					break;

				// try again, this time with credentials
				hr = JoinSession(lpDirectPlay3A, &guidSessionInstance, &clientLogin, lpDPInfo);
			}

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

	// make space for Connection Shortcut
	lpConnectionBuffer = GlobalAllocPtr(GHND, dwConnectionSize);
	if (lpConnectionBuffer == NULL)
		goto FAILURE;

	// store pointer to GUID in combo box
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
					LPSERVERCONFIG lpServerConfig,
					LPDPLAYINFO lpDPInfo)
{
	DPID				dpidPlayer;
	DPSESSIONDESC2		sessionDesc;
	DPSECURITYDESC		securityDesc;
	LPDPSECURITYDESC	lpSecurityDesc;
	HRESULT				hr;

	// check for valid interface
	if (lpDirectPlay3A == NULL)
		return (DPERR_INVALIDOBJECT);

	// host a new session
	ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
	sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
    sessionDesc.guidApplication = DPSLOTS_GUID;
    sessionDesc.dwMaxPlayers = 0;
	sessionDesc.lpszSessionNameA = lpServerConfig->szServerName;
	sessionDesc.dwFlags = SESSIONFLAGS(lpServerConfig->bRequireSecureLogin);

	// assume no security descriptor will be needed
	lpSecurityDesc = NULL;

	if (lpServerConfig->bRequireSecureLogin)
	{
		// a service provider string was entered, so use it
		if (lstrlen(lpServerConfig->szSecurityProvider))
		{
			ZeroMemory(&securityDesc, sizeof(DPSECURITYDESC));
			securityDesc.dwSize = sizeof(DPSECURITYDESC);
			securityDesc.dwFlags = 0;
			securityDesc.lpszSSPIProviderA = lpServerConfig->szSecurityProvider;
			lpSecurityDesc = &securityDesc;
		}
	}

	// host the session
	hr = lpDirectPlay3A->SecureOpen(&sessionDesc, DPOPEN_CREATE, lpSecurityDesc, NULL);
	if FAILED(hr)
		goto FAILURE;

	// create a server player with no name
	hr = lpDirectPlay3A->CreatePlayer(&dpidPlayer, NULL, 
							lpDPInfo->hPlayerEvent, NULL, 0, SERVERPLAYERFLAGS);
	if FAILED(hr)
		goto FAILURE;

	// return connection info
	lpDPInfo->lpDirectPlay3A = lpDirectPlay3A;
	lpDPInfo->dpidPlayer = dpidPlayer;
	lpDPInfo->bIsHost = TRUE;
	lpDPInfo->bIsSecure = lpServerConfig->bRequireSecureLogin;

	// save database name in global
	lstrcpy(gszDatabaseName, lpServerConfig->szDatabaseFile);

	return (DP_OK);

FAILURE:
	lpDirectPlay3A->Close();
	return (hr);
}

HRESULT JoinSession(LPDIRECTPLAY3A lpDirectPlay3A,
					LPGUID lpguidSessionInstance,
					LPCLIENTLOGIN lpClientLogin,
					LPDPLAYINFO lpDPInfo)
{
    DPID                dpidPlayer;
	DPNAME				dpName;
	DPSESSIONDESC2		sessionDesc;
	LPDPSESSIONDESC2	lpSessionDesc = NULL;
	DPCREDENTIALS		credentials;
	LPDPCREDENTIALS		lpCredentials;
	HRESULT				hr;

	// check for valid interface
	if (lpDirectPlay3A == NULL)
		return (DPERR_INVALIDOBJECT);

	// join existing session
	ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
	sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
    sessionDesc.guidInstance = *lpguidSessionInstance;

	// assume no credentials are going to be used
	lpCredentials = NULL;

	// setup credentials
	ZeroMemory(&credentials, sizeof(DPCREDENTIALS));
	credentials.dwSize = sizeof(DPCREDENTIALS);
	credentials.dwFlags = 0;

	if (lstrlen(lpClientLogin->szUserName))
	{
		credentials.lpszUsernameA = lpClientLogin->szUserName;
		lpCredentials = &credentials;
	}

	if (lstrlen(lpClientLogin->szPassword))
	{
		credentials.lpszPasswordA = lpClientLogin->szPassword; 
		lpCredentials = &credentials;
	}

	if (lstrlen(lpClientLogin->szDomain))
	{
		credentials.lpszDomainA = lpClientLogin->szDomain; 
		lpCredentials = &credentials;
	}

	// join the session 
	hr = lpDirectPlay3A->SecureOpen(&sessionDesc, DPOPEN_JOIN, NULL, lpCredentials);
	
	if FAILED(hr)
		goto FAILURE;

	// fill out name structure
	ZeroMemory(&dpName, sizeof(DPNAME));
	dpName.dwSize = sizeof(DPNAME);
	dpName.lpszShortNameA = lpClientLogin->szPlayerName;
	dpName.lpszLongNameA = NULL;

	// create a player with this name
	hr = lpDirectPlay3A->CreatePlayer(&dpidPlayer, &dpName, 
							lpDPInfo->hPlayerEvent, NULL, 0, CLIENTPLAYERFLAGS);
	if FAILED(hr)
		goto FAILURE;

	// get the session desc
	hr = GetSessionDesc(lpDirectPlay3A, &lpSessionDesc);
	if FAILED(hr)
		goto FAILURE;

	// return connection info
	lpDPInfo->lpDirectPlay3A = lpDirectPlay3A;
	lpDPInfo->dpidPlayer = dpidPlayer;
	lpDPInfo->bIsHost = FALSE;

	if (lpSessionDesc->dwFlags & DPSESSION_SECURESERVER)
		lpDPInfo->bIsSecure = TRUE;
	else
		lpDPInfo->bIsSecure = FALSE;

	GlobalFreePtr(lpSessionDesc);

	return (DP_OK);

FAILURE:
	if (lpSessionDesc)
		GlobalFreePtr(lpSessionDesc);

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
	iIndex = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_ADDSTRING, 
								(WPARAM) 0, (LPARAM) lpSessionDesc->lpszSessionNameA);

	if (iIndex == LB_ERR)
		goto FAILURE;


	// make space for session instance guid
	lpGuid = (LPGUID) GlobalAllocPtr(GHND, sizeof(GUID));
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
    sessionDesc.guidApplication = DPSLOTS_GUID;

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

HRESULT GetSessionDesc(LPDIRECTPLAY3A lpDirectPlay3A, LPDPSESSIONDESC2 *lplpSessionDesc)
{
	LPDPSESSIONDESC2	lpSessionDesc = NULL;
	DWORD				dwSessionDescSize;
	HRESULT				hr;

	// get size of session desc
	hr = lpDirectPlay3A->GetSessionDesc(NULL, &dwSessionDescSize);
	if (hr != DPERR_BUFFERTOOSMALL)
		goto FAILURE;

	// make room for it
	lpSessionDesc = (LPDPSESSIONDESC2) GlobalAllocPtr(GHND, dwSessionDescSize);
	if (lpSessionDesc == NULL)
	{
		hr = DPERR_OUTOFMEMORY;
		goto FAILURE;
	}

	// get the session desc
	hr = lpDirectPlay3A->GetSessionDesc(lpSessionDesc, &dwSessionDescSize);
	if FAILED(hr)
		goto FAILURE;

	// return account description
	*lplpSessionDesc = lpSessionDesc;
	lpSessionDesc = NULL;

FAILURE:
	if (lpSessionDesc)
		GlobalFreePtr(lpSessionDesc);

	return (hr);
}

void InitializeServerConfigWindow(HWND hWnd)
{
	char		szSessionName[MAXSTRLEN];
	DWORD		dwNameSize;

	// use username for default
	dwNameSize = MAXSTRLEN;
	if (GetComputerName(szSessionName, &dwNameSize))
		SetDlgItemText(hWnd, IDC_SERVERNAMEEDIT, szSessionName);
	
	// use default name
	SetDlgItemText(hWnd, IDC_DATABASEFILEEDIT, DEFAULTDATABASE);

	// security off by default
	CheckDlgItem(hWnd, IDC_SECURECHECK, FALSE);
}

void SaveServerConfig(HWND hWnd, LPSERVERCONFIG lpServerConfig)
{
	// get strings from dialog
	GetDlgItemText(hWnd, IDC_SERVERNAMEEDIT, lpServerConfig->szServerName, MAXSTRLEN);
	GetDlgItemText(hWnd, IDC_DATABASEFILEEDIT, lpServerConfig->szDatabaseFile, MAXSTRLEN);
	GetDlgItemText(hWnd, IDC_SECURITYPROVIDEREDIT, lpServerConfig->szSecurityProvider, MAXSTRLEN);

	if (DlgItemIsChecked(hWnd, IDC_SECURECHECK))
		lpServerConfig->bRequireSecureLogin = TRUE;
	else
		lpServerConfig->bRequireSecureLogin = FALSE;
}

BOOL CALLBACK ServerConfigWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPSERVERCONFIG	lpServerConfig;

    switch(uMsg)
    {
        case WM_INITDIALOG:

			// globals are passed in lParam
			lpServerConfig = (LPSERVERCONFIG) lParam;

			// Initialize dialog with appropriate information
			InitializeServerConfigWindow(hWnd);
            break;

        case WM_DESTROY:
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
				case IDOK:
					// save changes they made
					SaveServerConfig(hWnd, lpServerConfig);
                    // Return success
                    EndDialog(hWnd, TRUE);

                    break;

				case IDCANCEL:
                    // Return failure
                    EndDialog(hWnd, FALSE);

                    break;
            }

            break;
    }

    // Allow for default processing
    return FALSE;
}

BOOL GetServerConfig(HWND hWnd, LPSERVERCONFIG lpServerConfig)
{
	// collect server config from dialog
	return (DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_SERVERCONFIGDIALOG), hWnd, (DLGPROC) ServerConfigWndProc, (LPARAM) lpServerConfig));
}

void InitializeClientLoginWindow(HWND hWnd)
{
	char		szPlayerName[MAXSTRLEN];
	DWORD		dwNameSize;

	// use user name for player name
	dwNameSize = MAXSTRLEN;
	if (GetUserName(szPlayerName, &dwNameSize))
		SetDlgItemText(hWnd, IDC_USERNAMEEDIT, szPlayerName);
}

void SaveClientLogin(HWND hWnd, LPCLIENTLOGIN lpClientLogin)
{
	// get strings from dialog
	GetDlgItemText(hWnd, IDC_USERNAMEEDIT, lpClientLogin->szUserName, MAXSTRLEN);
	GetDlgItemText(hWnd, IDC_PASSWORDEDIT, lpClientLogin->szPassword, MAXSTRLEN);
	GetDlgItemText(hWnd, IDC_DOMAINEDIT, lpClientLogin->szDomain, MAXSTRLEN);
}

BOOL CALLBACK ClientLoginWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPCLIENTLOGIN	lpClientLogin;

    switch(uMsg)
    {
        case WM_INITDIALOG:

			// globals are passed in lParam
			lpClientLogin = (LPCLIENTLOGIN) lParam;

			// Initialize dialog with appropriate information
			InitializeClientLoginWindow(hWnd);
            break;

        case WM_DESTROY:
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
				case IDOK:
					// save changes they made
					SaveClientLogin(hWnd, lpClientLogin);
                    // Return success
                    EndDialog(hWnd, TRUE);

                    break;

				case IDCANCEL:
                    // Return failure
                    EndDialog(hWnd, FALSE);

                    break;
            }

            break;
    }

    // Allow for default processing
    return FALSE;
}

BOOL GetClientLogin(HWND hWnd, LPCLIENTLOGIN lpClientLogin)
{
	// collect server config from dialog
	return (DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_CLIENTLOGINDIALOG), hWnd, (DLGPROC) ClientLoginWndProc, (LPARAM) lpClientLogin));
}
