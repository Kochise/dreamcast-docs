/*==========================================================================
 *
 *  Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       override.c
 *  Content:	Implementation of a DirectPlay launching utility
 *
 ***************************************************************************/

#define INITGUID

#include <windows.h>
#include <windowsx.h>
#include <objbase.h>
#include <cguid.h>

#include "dplay.h"
#include "dplobby.h"

#include "resource.h"

#define NAMEMAX			200			// string size
#define TIMERID			1			// timer ID to use
#define TIMERINTERVAL	1000		// timer interval

typedef struct {
	LPDIRECTPLAY3A		lpDPlay;
	GUID				guidInstance;
} STATUSCONTEXT, *LPSTATUSCONTEXT;

// guid for this application
// {126E6180-D307-11d0-9C4F-00A0C905425E}
DEFINE_GUID(OVERRIDE_GUID, 
0x126e6180, 0xd307, 0x11d0, 0x9c, 0x4f, 0x0, 0xa0, 0xc9, 0x5, 0x42, 0x5e);

// prototypes
BOOL CALLBACK		OverrideWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK		SessionsWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT				InitializeOverrideWindow(HWND hWnd, LPDIRECTPLAYLOBBY2A *lplpDPlayLobby);
void				DestroyOverrideWindow(HWND hWnd, LPDIRECTPLAY3A lpDPlay, LPDIRECTPLAYLOBBY2A lpDPlayLobby);
HRESULT				UpdateAddressInfo(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby2A);
HRESULT				DoHostOrJoin(HINSTANCE hInstance, HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby, BOOL bHost, LPDIRECTPLAY3A *lplpDPlay);
BOOL FAR PASCAL		DirectPlayEnumerateCallback(LPGUID lpSPGuid, LPTSTR lpszSPName,
						DWORD dwMajorVersion, DWORD dwMinorVersion, LPVOID lpContext);
HRESULT				GetServiceProviderGuid(HWND hWnd, LPGUID lpguidServiceProvider);
void				DeleteServiceProviderCombo(HWND hWnd);
HRESULT				FillModemComboBox(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby);
BOOL				DlgItemIsChecked(HWND hDlg, int nIDDlgItem);
void				EnableDlgButton(HWND hDlg, int nIDDlgItem, BOOL bEnable);

// ---------------------------------------------------------------------------
// WinMain
// ---------------------------------------------------------------------------
// Description:             Main windows entry point.
// Arguments:
//  HINSTANCE               [in] Standard windows stuff
//  HINSTANCE               [in]
//  LPSTR                   [in]
//  int                     [in]
// Returns:
//  int						
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				    LPSTR lpCmdLine, int nCmdShow )
{
	HRESULT		hr;
	int			iResult = 0;

	// initialize COM library
	hr = CoInitialize(NULL);
	if FAILED(hr)
		goto FAILURE;

    iResult = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_OVERRIDEDIALOG), NULL, OverrideWndProc, (LPARAM) hInstance);

FAILURE:
	// Uninitialize the COM library
	CoUninitialize();

	return (iResult);
}


// ---------------------------------------------------------------------------
// OverrideWndProc
// ---------------------------------------------------------------------------
// Description:             Message callback function for Override dialog.
// Arguments:
//  HWND                    [in] Dialog window handle.
//  UINT                    [in] Window message identifier.
//  WPARAM                  [in] Depends on message.
//  LPARAM                  [in] Depends on message.
// Returns:
//  BOOL                    TRUE if message was processed internally.
BOOL CALLBACK OverrideWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE			hInstance;
	static LPDIRECTPLAY3A		lpDPlay;
	static LPDIRECTPLAYLOBBY2A	lpDPlayLobby;
	HRESULT						hr;

    switch(uMsg)
    {
        case WM_INITDIALOG:
            // Save the instance handle
            hInstance = (HINSTANCE)lParam;
                        
			// Initialize dialog with launcher information
			lpDPlay = NULL;
			lpDPlayLobby = NULL;
			hr = InitializeOverrideWindow(hWnd, &lpDPlayLobby);
			if FAILED(hr)
					SetDlgItemText(hWnd, IDC_STATUSEDIT, "Could not initialize DirectPlay");
            break;

        case WM_DESTROY:
			// Destroy launcher information in dialog
			DestroyOverrideWindow(hWnd, lpDPlay, lpDPlayLobby);
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
				case IDC_SPCOMBO:

					switch (HIWORD(wParam))
					{
					case CBN_SELCHANGE:
						UpdateAddressInfo(hWnd, lpDPlayLobby);
						break;
					}
					break;

				case IDC_MODEMCOMBO:

					switch (HIWORD(wParam))
					{
					case CBN_SELCHANGE:
						break;
					}
					break;

                case IDC_HOSTBUTTON:

					SetDlgItemText(hWnd, IDC_STATUSEDIT, "Hosting...");
					hr = DoHostOrJoin(hInstance, hWnd, lpDPlayLobby, TRUE, &lpDPlay);
					if FAILED(hr)
						SetDlgItemText(hWnd, IDC_STATUSEDIT, "Failed to host");
					else
						SetDlgItemText(hWnd, IDC_STATUSEDIT, "Host successfull");
                    break;

                case IDC_JOINBUTTON:

					SetDlgItemText(hWnd, IDC_STATUSEDIT, "Joining...");
					hr = DoHostOrJoin(hInstance, hWnd, lpDPlayLobby, FALSE, &lpDPlay);
					if FAILED(hr)
						SetDlgItemText(hWnd, IDC_STATUSEDIT, "Failed to join");
					else
						SetDlgItemText(hWnd, IDC_STATUSEDIT, "Join successfull");
                    break;

                case IDCANCEL:
                    // Return failure
                    EndDialog(hWnd, TRUE);

                    break;
            }

            break;
    }

    // Allow for default processing
    return FALSE;
}

HRESULT InitializeOverrideWindow(HWND hWnd, LPDIRECTPLAYLOBBY2A *lplpDPlayLobby)
{
	LPDIRECTPLAYLOBBYA	lpDPlayLobbyA = NULL;
	LPDIRECTPLAYLOBBY2A	lpDPlayLobby2A = NULL;
	HRESULT				hr;
		
	// get ANSI DirectPlayLobby interface
	hr = DirectPlayLobbyCreate(NULL, &lpDPlayLobbyA, NULL, NULL, 0);
	if FAILED(hr)
		goto FAILURE;

	// get ANSI DirectPlayLobby2 interface
	hr = lpDPlayLobbyA->lpVtbl->QueryInterface(lpDPlayLobbyA,
							&IID_IDirectPlayLobby2A, (LPVOID *) &lpDPlayLobby2A);
	if FAILED(hr)
		goto FAILURE;

	// don't need DirectPlayLobby interface anymore
	lpDPlayLobbyA->lpVtbl->Release(lpDPlayLobbyA);
	lpDPlayLobbyA = NULL;

	// put all the service providers in combo box
	DirectPlayEnumerate(DirectPlayEnumerateCallback, hWnd);
	SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);

	// fill modem combo box with available modems
	FillModemComboBox(hWnd, lpDPlayLobby2A);

	// update display first service provider
	UpdateAddressInfo(hWnd, lpDPlayLobby2A);

	// return the ANSI lobby interface
	*lplpDPlayLobby = lpDPlayLobby2A;

	return (DP_OK);

FAILURE:
	if (lpDPlayLobbyA)
		lpDPlayLobbyA->lpVtbl->Release(lpDPlayLobbyA);
	if (lpDPlayLobby2A)
		lpDPlayLobby2A->lpVtbl->Release(lpDPlayLobby2A);

	return (hr);
}

void DestroyOverrideWindow(HWND hWnd, LPDIRECTPLAY3A lpDPlay, LPDIRECTPLAYLOBBY2A lpDPlayLobby)
{
	// delete combo box data items
	DeleteServiceProviderCombo(hWnd);

	// release the dplay interface
	if (lpDPlay)
		lpDPlay->lpVtbl->Release(lpDPlay);

	// release the lobby interface
	if (lpDPlayLobby)
		lpDPlayLobby->lpVtbl->Release(lpDPlayLobby);
}

// ---------------------------------------------------------------------------
// DirectPlayEnumerateCallback
// ---------------------------------------------------------------------------
// Description:             Enumeration callback called by DirectPlay.
//							Enumerates service providers registered with DirectPlay.
// Arguments:
//  LPGUID					[in] GUID of service provider
//  LPTSTR					[in] name of service provider
//  DWORD					[in] major version of DirectPlay
//  DWORD					[in] minor version of DirectPlay
//  LPVOID				    [in] user-defined context
// Returns:
//  BOOL					TRUE to continue enumerating
BOOL FAR PASCAL DirectPlayEnumerateCallback(
						LPGUID		lpSPGuid,
						LPTSTR		lpszSPName,
						DWORD		dwMajorVersion,
						DWORD		dwMinorVersion,
						LPVOID		lpContext)
{
    HWND			hWnd = lpContext;
    LRESULT			iIndex;
	LPGUID			lpGuid;

	// store service provider name in combo box
	iIndex = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_ADDSTRING, 0, (LPARAM) lpszSPName);
	if (iIndex == CB_ERR)
		goto FAILURE;

	// make space for application GUID
	lpGuid = (LPGUID) GlobalAllocPtr(GHND, sizeof(GUID));
	if (lpGuid == NULL)
		goto FAILURE;

	// store pointer to GUID in combo box
	*lpGuid = *lpSPGuid;
	SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETITEMDATA, (WPARAM) iIndex, (LPARAM) lpGuid);

FAILURE:
    return (TRUE);
}

HRESULT GetServiceProviderGuid(HWND hWnd, LPGUID lpguidServiceProvider)
{
	LONG	iIndex;

	// get guid for service provider
	iIndex = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_GETCURSEL,
								(WPARAM) 0, (LPARAM) 0);
	if (iIndex == CB_ERR)
		return (DPERR_GENERIC);

	iIndex = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_GETITEMDATA,
								(WPARAM) iIndex, (LPARAM) 0);
	if ((iIndex == CB_ERR) || (iIndex == 0))
		return (DPERR_GENERIC);

	*lpguidServiceProvider = *((LPGUID) iIndex);

	return (DP_OK);
}

void DeleteServiceProviderCombo(HWND hWnd)
{
	WPARAM	i;
	LONG	lpData;
	
	// destroy the data stored with each combo box item
	i = 0;
	while (TRUE)
	{
		// get data pointer stored with item
		lpData = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_GETITEMDATA,
									(WPARAM) i, (LPARAM) 0);
		if (lpData == CB_ERR)		// error getting data
			break;

		if (lpData)					// data to delete
			GlobalFreePtr((LPVOID) lpData);

		i += 1;
	}

	// delete all items in list
	SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_RESETCONTENT,
								(WPARAM) 0, (LPARAM) 0);
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

		if (lpData)					// data to delete
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
		if (IsEqualGUID(lpguidSessionInstance, (LPGUID) lpData))
		{
			iIndex = i;				// store index of this string
			break;
		}

		i += 1;
	}

	// select this item
	SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_SETCURSEL, (WPARAM) iIndex, (LPARAM) 0);
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

BOOL CALLBACK SessionsWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPSTATUSCONTEXT	lpContext;
	static LPDIRECTPLAY3A	lpDPlay;
	static UINT				idTimer;
	static BOOL				bInsideEnumSessions;
	DPSESSIONDESC2			sessionDesc;
	GUID					guidSessionInstance;
	LONG					iIndex;
	HRESULT					hr;

    switch(uMsg)
    {
        case WM_INITDIALOG:
			lpContext = (LPSTATUSCONTEXT) lParam;
			lpDPlay = lpContext->lpDPlay;
			bInsideEnumSessions = FALSE;

			// can't join until there is a session
			EnableDlgButton(hWnd, IDC_JOINSESSIONBUTTON, FALSE);

			// set a timer to refresh the session list
			idTimer = SetTimer(hWnd, TIMERID, TIMERINTERVAL, NULL);
            break;

        case WM_DESTROY:
			if (idTimer)
			{
				KillTimer(hWnd, idTimer); 
				idTimer = 0;
			}
			DeleteSessionInstanceList(hWnd);
            break;

		case WM_TIMER:
			// make sure we don't re-enter EnumSessions
			if (bInsideEnumSessions)
				break;

			// get guid of currently selected session
			guidSessionInstance = GUID_NULL;
			hr = GetSessionInstanceGuid(hWnd, &guidSessionInstance);

			// delete existing session list
			DeleteSessionInstanceList(hWnd);

			// enum sessions
			ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
			sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
			sessionDesc.guidApplication = OVERRIDE_GUID;

			bInsideEnumSessions = TRUE;
			hr = lpDPlay->lpVtbl->EnumSessions(lpDPlay, &sessionDesc, 0,
									EnumSessionsCallback, hWnd,
									DPENUMSESSIONS_AVAILABLE |
									DPENUMSESSIONS_ASYNC |
									DPENUMSESSIONS_RETURNSTATUS);
			bInsideEnumSessions = FALSE;

			// select the session that was previously selected
			SelectSessionInstance(hWnd, &guidSessionInstance);

			// hilite "Join" button only if there are sessions to join
			iIndex = SendDlgItemMessage(hWnd, IDC_SESSIONLIST, LB_GETCOUNT,
								   (WPARAM) 0, (LPARAM) 0);

			EnableDlgButton(hWnd, IDC_JOINSESSIONBUTTON, (iIndex > 0) ? TRUE : FALSE);

			switch (hr)
			{
			case DP_OK:
				SetDlgItemText(hWnd, IDC_SESSIONSTATUSEDIT, "Searching for sessions...");
				break;

			case DPERR_CONNECTING:
				SetDlgItemText(hWnd, IDC_SESSIONSTATUSEDIT, "Making connection...");
				break;

			case DPERR_NOCONNECTION:
				SetDlgItemText(hWnd, IDC_SESSIONSTATUSEDIT, "Connection failed");
				KillTimer(hWnd, idTimer); 
				idTimer = 0;
				break;

			default:
				SetDlgItemText(hWnd, IDC_SESSIONSTATUSEDIT, "Error making connection");
				KillTimer(hWnd, idTimer); 
				idTimer = 0;
				break;
			}
			break;
        
		case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_JOINSESSIONBUTTON:
                    // Return guid of session to join
					hr = GetSessionInstanceGuid(hWnd, &lpContext->guidInstance);
					if SUCCEEDED(hr)
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

// ---------------------------------------------------------------------------
// UpdateAddressInfo
// ---------------------------------------------------------------------------
// Description:             Updates address information elements in dialog.
//							Calls EnumAddressTypes() to determine what address
//							information should be displayed and arranges dialog
//							to display and collect the needed information.
// Arguments:
//  HWND					[in] window handle
//  LPDIRECTPLAYLOBBY2A		[in] DirectPlay Lobby interface to use
// Returns:
//  HRESULT					DP_OK if it succeedes, otherwise the error
HRESULT UpdateAddressInfo(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby2A)
{
	GUID			guidServiceProvider;
	HRESULT			hr;

	// clear and hide address dialog items
	ShowWindow(GetDlgItem(hWnd, IDC_PHONEEDIT), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_PHONEEDITLABEL), SW_HIDE);

	ShowWindow(GetDlgItem(hWnd, IDC_MODEMCOMBO), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_MODEMCOMBOLABEL), SW_HIDE);

	ShowWindow(GetDlgItem(hWnd, IDC_TCPEDIT), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_TCPEDITLABEL), SW_HIDE);

	ShowWindow(GetDlgItem(hWnd, IDC_IPXLABEL), SW_HIDE);

	ShowWindow(GetDlgItem(hWnd, IDC_SERVICEPROVIDERLABEL), SW_HIDE);

	// get currently selected service provider
	hr = GetServiceProviderGuid(hWnd, &guidServiceProvider);
	if FAILED(hr)
		goto FAILURE;

	// modem service provider
	if (IsEqualGUID(&guidServiceProvider, &DPSPGUID_MODEM))
	{
		// show edit control to collect phone number
		ShowWindow(GetDlgItem(hWnd, IDC_PHONEEDIT), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, IDC_PHONEEDITLABEL), SW_SHOW);

		// show combo box to collect modem
		ShowWindow(GetDlgItem(hWnd, IDC_MODEMCOMBO), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, IDC_MODEMCOMBOLABEL), SW_SHOW);
	}

	// internet TCP/IP service provider
	else if (IsEqualGUID(&guidServiceProvider, &DPSPGUID_TCPIP))
	{
		// show edit control to collect IP address
		ShowWindow(GetDlgItem(hWnd, IDC_TCPEDIT), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, IDC_TCPEDITLABEL), SW_SHOW);
	}

	// IPX service provider
	else if (IsEqualGUID(&guidServiceProvider, &DPSPGUID_IPX))
	{
		// no address info is needed, so just display a string
		ShowWindow(GetDlgItem(hWnd, IDC_IPXLABEL), SW_SHOW);
	}

	// anything else, let service provider collect settings, if any
	else
	{
		ShowWindow(GetDlgItem(hWnd, IDC_SERVICEPROVIDERLABEL), SW_SHOW);
	}

FAILURE:
	return (hr);
}

HRESULT	CreateServiceProviderAddress(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby,
									 LPVOID *lplpAddress, LPDWORD lpdwAddressSize)
{
	DPCOMPOUNDADDRESSELEMENT	addressElements[3];
	CHAR						szIPAddressString[NAMEMAX];
	CHAR						szPhoneNumberString[NAMEMAX];
	CHAR						szModemString[NAMEMAX];
	LPVOID						lpAddress = NULL;
	DWORD						dwAddressSize = 0;
	DWORD						dwElementCount;
	GUID						guidServiceProvider;
	HRESULT						hr;

	// get currently selected service provider
	hr = GetServiceProviderGuid(hWnd, &guidServiceProvider);
	if FAILED(hr)
		goto FAILURE;

	dwElementCount = 0;

	if (IsEqualGUID(&guidServiceProvider, &DPSPGUID_MODEM))
	{
		// Modem needs a service provider, a phone number string and a modem string

		// service provider
		addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
		addressElements[dwElementCount].dwDataSize = sizeof(GUID);
		addressElements[dwElementCount].lpData = (LPVOID) &DPSPGUID_MODEM;
		dwElementCount++;

		// add a modem string if available
		lstrcpy(szModemString, "");
		if (GetDlgItemText(hWnd, IDC_MODEMCOMBO, szModemString, NAMEMAX))
		{
			addressElements[dwElementCount].guidDataType = DPAID_Modem;
			addressElements[dwElementCount].dwDataSize = lstrlen(szModemString) + 1;
			addressElements[dwElementCount].lpData = szModemString;
			dwElementCount++;
		}

		// add phone number string
		lstrcpy(szPhoneNumberString, "");
		GetDlgItemText(hWnd, IDC_PHONEEDIT, szPhoneNumberString, NAMEMAX);
		addressElements[dwElementCount].guidDataType = DPAID_Phone;
		addressElements[dwElementCount].dwDataSize = lstrlen(szPhoneNumberString) + 1;
		addressElements[dwElementCount].lpData = szPhoneNumberString;
		dwElementCount++;
	}

	// internet TCP/IP service provider
	else if (IsEqualGUID(&guidServiceProvider, &DPSPGUID_TCPIP))
	{
		// TCP/IP needs a service provider and an IP address

		// service provider
		addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
		addressElements[dwElementCount].dwDataSize = sizeof(GUID);
		addressElements[dwElementCount].lpData = (LPVOID) &DPSPGUID_TCPIP;
		dwElementCount++;

		// IP address string
		lstrcpy(szIPAddressString, "");
		GetDlgItemText(hWnd, IDC_TCPEDIT, szIPAddressString, NAMEMAX);
		addressElements[dwElementCount].guidDataType = DPAID_INet;
		addressElements[dwElementCount].dwDataSize = lstrlen(szIPAddressString) + 1;
		addressElements[dwElementCount].lpData = szIPAddressString;
		dwElementCount++;
	}

	// IPX service provider
	else if (IsEqualGUID(&guidServiceProvider, &DPSPGUID_IPX))
	{
		// IPX just needs a service provider

		// service provider
		addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
		addressElements[dwElementCount].dwDataSize = sizeof(GUID);
		addressElements[dwElementCount].lpData = (LPVOID) &DPSPGUID_IPX;
		dwElementCount++;
	}

	// anything else, let service provider collect settings, if any
	else
	{
		// service provider
		addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
		addressElements[dwElementCount].dwDataSize = sizeof(GUID);
		addressElements[dwElementCount].lpData = (LPVOID) &guidServiceProvider;
		dwElementCount++;
	}

	// see how much room is needed to store this address
	hr = lpDPlayLobby->lpVtbl->CreateCompoundAddress(lpDPlayLobby,
						addressElements, dwElementCount,
						NULL, &dwAddressSize);
	if (hr != DPERR_BUFFERTOOSMALL)
		goto FAILURE;

	// allocate space
	lpAddress = GlobalAllocPtr(GHND, dwAddressSize);
	if (lpAddress == NULL)
	{
		hr = DPERR_NOMEMORY;
		goto FAILURE;
	}

	// create the address
	hr = lpDPlayLobby->lpVtbl->CreateCompoundAddress(lpDPlayLobby,
						addressElements, dwElementCount,
						lpAddress, &dwAddressSize);
	if FAILED(hr)
		goto FAILURE;

	// return the address info
	*lplpAddress = lpAddress;
	*lpdwAddressSize = dwAddressSize;

	return (DP_OK);

FAILURE:
	if (lpAddress)
		GlobalFreePtr(lpAddress);

	return (hr);
}

HRESULT	DoHostOrJoin(HINSTANCE hInstance, HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby, BOOL bHost, LPDIRECTPLAY3A *lplpDPlay)
{
	LPDIRECTPLAY3A	lpDPlay = NULL;
	LPVOID			lpAddress = NULL;
	DWORD			dwAddressSize = 0;
	DPSESSIONDESC2	sessionDesc;
	STATUSCONTEXT	statusContext;
	HRESULT			hr;

	// bail if we don't have a lobby interface
	if (lpDPlayLobby == NULL)
		return (DPERR_INVALIDOBJECT);

	// get service provider address from information in dialog
	hr = CreateServiceProviderAddress(hWnd, lpDPlayLobby, &lpAddress, &dwAddressSize);
	if FAILED(hr)
		goto FAILURE;

	// interface already exists, so release it
	if (*lplpDPlay)
	{
		(*lplpDPlay)->lpVtbl->Release(*lplpDPlay);
		*lplpDPlay = NULL;
	}

	// create an ANSI DirectPlay3 interface
	hr = CoCreateInstance(&CLSID_DirectPlay, NULL, CLSCTX_INPROC_SERVER, 
						  &IID_IDirectPlay3A, (LPVOID*)&lpDPlay);
	if FAILED(hr)
		goto FAILURE;

	// initialize the connection using the address
	hr = lpDPlay->lpVtbl->InitializeConnection(lpDPlay, lpAddress, 0);
	if FAILED(hr)
		goto FAILURE;

	if (bHost)
	{
		// host a new session
		ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
		sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
		sessionDesc.dwFlags = DPSESSION_MIGRATEHOST | DPSESSION_KEEPALIVE;
		sessionDesc.guidApplication = OVERRIDE_GUID;
		sessionDesc.dwMaxPlayers = 0;
		sessionDesc.lpszSessionNameA = "Override";

		// open it
		hr = lpDPlay->lpVtbl->Open(lpDPlay, &sessionDesc, DPOPEN_CREATE);
	}

	// enumerate the sessions
	else
	{
		// display status dialog and enumerate until we find a session
		statusContext.lpDPlay = lpDPlay;
		statusContext.guidInstance = GUID_NULL;

		if (!DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_SESSIONSDIALOG), hWnd, SessionsWndProc, (LPARAM) &statusContext))
		{
			hr = DPERR_USERCANCEL;
			goto FAILURE;
		}

		// open the session selected by the use
		ZeroMemory(&sessionDesc, sizeof(DPSESSIONDESC2));
		sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
		sessionDesc.guidApplication = OVERRIDE_GUID;
		sessionDesc.guidInstance = statusContext.guidInstance;

		// open it
		hr = lpDPlay->lpVtbl->Open(lpDPlay, &sessionDesc, DPOPEN_JOIN);
	}

	if FAILED(hr)
		goto FAILURE;

	// return the connected interface
	*lplpDPlay = lpDPlay;

	// set to NULL so we don't release it below
	lpDPlay = NULL;

FAILURE:
	if (lpDPlay)
	{
		lpDPlay->lpVtbl->Close(lpDPlay);
		lpDPlay->lpVtbl->Release(lpDPlay);
	}

	if (lpAddress)
		GlobalFreePtr(lpAddress);

	return (hr);
}

// ---------------------------------------------------------------------------
// EnumModemAddress
// ---------------------------------------------------------------------------
// Description:             Enumeration callback called by DirectPlayLobby.
//							Enumerates the DirectPlay address chunks. If the
//							chunk contains modem strings, add them to the control.
// Arguments:
//  REFGUID                 [in] GUID of the address type
//  DWORD					[in] size of chunk
//  LPVOID				    [in] pointer to chunk
//  LPVOID				    [in] user-defined context
// Returns:
//  BOOL					FALSE to stop enumerating after the first callback
BOOL FAR PASCAL EnumModemAddress(REFGUID lpguidDataType, DWORD dwDataSize,
							LPCVOID lpData, LPVOID lpContext)
{
	HWND	hWnd = (HWND) lpContext;
	LPSTR	lpszStr = (LPSTR) lpData;

	// modem
	if (IsEqualGUID(lpguidDataType, &DPAID_Modem))
	{
		// loop over all strings in list
		while (lstrlen(lpszStr))
		{
			// store modem name in combo box
			SendDlgItemMessage(hWnd, IDC_MODEMCOMBO, CB_ADDSTRING, 0, (LPARAM) lpszStr);

			// skip to next string
			lpszStr += lstrlen(lpszStr) + 1;
		}
	}

	return (TRUE);
}

// ---------------------------------------------------------------------------
// FillModemComboBox
// ---------------------------------------------------------------------------
// Description:             Fills combo box with modem names
// Arguments:
//  HWND                    [in]  Window handle.
//  LPDIRECTPLAYLOBBY2A     [in]  DirectPlay Lobby interface to use
//  LPGUID					[out] GUID of service provider to use
// Returns:
//  HRESULT					any error
HRESULT FillModemComboBox(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby)
{
	LPDIRECTPLAY		lpDPlay1 = NULL;
	LPDIRECTPLAY3A		lpDPlay3A = NULL;
	LPVOID				lpAddress = NULL;
	DWORD				dwAddressSize = 0;
	GUID				guidServiceProvider = DPSPGUID_MODEM;
	HRESULT				hr;

	// get a DirectPlay interface for this service provider
	hr = DirectPlayCreate(&guidServiceProvider, &lpDPlay1, NULL);
	if FAILED(hr)
		goto FAILURE;

	// query for an ANSI DirectPlay3 interface
	hr = lpDPlay1->lpVtbl->QueryInterface(lpDPlay1, &IID_IDirectPlay3A, (LPVOID *) &lpDPlay3A);
	if FAILED(hr)
		goto FAILURE;

	// get size of player address for player zero
	hr = lpDPlay3A->lpVtbl->GetPlayerAddress(lpDPlay3A, DPID_ALLPLAYERS, NULL, &dwAddressSize);
	if (hr != DPERR_BUFFERTOOSMALL)
		goto FAILURE;

	// make room for it
	lpAddress = GlobalAllocPtr(GHND, dwAddressSize);
	if (lpAddress == NULL)
	{
		hr = DPERR_NOMEMORY;
		goto FAILURE;
	}

	// get the address
	hr = lpDPlay3A->lpVtbl->GetPlayerAddress(lpDPlay3A, DPID_ALLPLAYERS, lpAddress, &dwAddressSize);
	if FAILED(hr)
		goto FAILURE;
	
	// get modem strings from address and put them in the combo box
	hr = lpDPlayLobby->lpVtbl->EnumAddress(lpDPlayLobby, EnumModemAddress, 
							 lpAddress, dwAddressSize, hWnd);
	if FAILED(hr)
		goto FAILURE;

	// select first item in list
	SendDlgItemMessage(hWnd, IDC_MODEMCOMBO, CB_SETCURSEL, (WPARAM) 0, 0);

FAILURE:
	if (lpDPlay1)
		lpDPlay1->lpVtbl->Release(lpDPlay1);
	if (lpDPlay3A)
		lpDPlay3A->lpVtbl->Release(lpDPlay3A);
	if (lpAddress)
		GlobalFreePtr(lpAddress);

	return (hr);
}

BOOL DlgItemIsChecked(HWND hDlg, int nIDDlgItem)
{
	return ((SendDlgItemMessage(hDlg, nIDDlgItem, BM_GETCHECK, (WPARAM) 0, (LPARAM) 0) == BST_CHECKED) ? TRUE : FALSE);
}

void EnableDlgButton(HWND hDlg, int nIDDlgItem, BOOL bEnable)
{
	EnableWindow(GetDlgItem(hDlg, nIDDlgItem), bEnable);
}
