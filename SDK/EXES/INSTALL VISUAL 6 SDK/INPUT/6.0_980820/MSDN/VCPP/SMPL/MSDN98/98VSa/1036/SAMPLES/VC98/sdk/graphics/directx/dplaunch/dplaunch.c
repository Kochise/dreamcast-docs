/*==========================================================================
 *
 *  Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dplaunch.c
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

// constants
#define NAMEMAX			200			// maximum size of a string name
#define ADDRESSTYPEMAX	10			// maximum no. address types

// GUID for sessions this application creates
// {D559FC00-DC12-11cf-9C4E-00A0C905425E}
DEFINE_GUID(MY_SESSION_GUID, 
0xd559fc00, 0xdc12, 0x11cf, 0x9c, 0x4e, 0x0, 0xa0, 0xc9, 0x5, 0x42, 0x5e);

// structures

// list of address types
typedef struct {
	DWORD	dwCount;
	GUID	guidAddressTypes[ADDRESSTYPEMAX];
} ADDRESSTYPELIST, *LPADDRESSTYPELIST;

// prototypes
BOOL CALLBACK		LauncherWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT				InitializeLauncherWindow(HWND hWnd, LPDIRECTPLAYLOBBY2A *lplpDPlayLobby);
HRESULT				UpdateAddressInfo(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby);
void				DestroyLauncherWindow(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby);
void				LaunchDirectPlayApplication(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby);
HRESULT				GetComboBoxGuid(HWND hWnd, LONG iDialogItem, LPGUID lpguidServiceProvider);
HRESULT				FillModemComboBox(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby, LPGUID lpguidServiceProvider);


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
    return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_LAUNCHERDIALOG), NULL, LauncherWndProc, (LPARAM) hInstance);
}


// ---------------------------------------------------------------------------
// LauncherWndProc
// ---------------------------------------------------------------------------
// Description:             Message callback function for Launcher dialog.
// Arguments:
//  HWND                    [in] Dialog window handle.
//  UINT                    [in] Window message identifier.
//  WPARAM                  [in] Depends on message.
//  LPARAM                  [in] Depends on message.
// Returns:
//  BOOL                    TRUE if message was processed internally.
BOOL CALLBACK LauncherWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE			hInst;
	static LPDIRECTPLAYLOBBY2A	lpDPlayLobby;
	HRESULT						hr;

    switch(uMsg)
    {
        case WM_INITDIALOG:
            // Save the instance handle
            hInst = (HINSTANCE)lParam;
                        
			// Initialize dialog with launcher information
			lpDPlayLobby = NULL;
			hr = InitializeLauncherWindow(hWnd, &lpDPlayLobby);
            break;

        case WM_DESTROY:
			// Destroy launcher information in dialog
			DestroyLauncherWindow(hWnd, lpDPlayLobby);

            // Return failure
            EndDialog(hWnd, FALSE);

            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
				case IDC_SPCOMBO:

					switch (HIWORD(wParam))
					{
					case CBN_SELCHANGE:
						// update the address info display
						UpdateAddressInfo(hWnd, lpDPlayLobby);
						break;
					}
					break;

                case IDC_RUNAPPBUTTON:
					// get settings and launch application
                    LaunchDirectPlayApplication(hWnd, lpDPlayLobby);

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

// ---------------------------------------------------------------------------
// EnumApp
// ---------------------------------------------------------------------------
// Description:             Enumeration callback called by DirectPlay.
//							Enumerates the applications registered with DirectPlay.
// Arguments:
//  LPDPLAPPINFO            [in] information about the application
//  LPVOID				    [in] user-defined context
//  DWORD					[in] flags
// Returns:
//  BOOL					TRUE to continue enumerating
BOOL FAR PASCAL EnumApp(LPCDPLAPPINFO lpAppInfo, LPVOID lpContext, DWORD dwFlags)
{
    HWND			hWnd = lpContext;
    LRESULT			iIndex;
	LPGUID			lpGuid;

	// store application name in combo box
	iIndex = SendDlgItemMessage(hWnd, IDC_APPCOMBO, CB_ADDSTRING, 0, (LPARAM) lpAppInfo->lpszAppNameA);
	if (iIndex == LB_ERR)
		goto Failure;

	// make space for application GUID
	lpGuid = (LPGUID) GlobalAllocPtr(GHND, sizeof(GUID));
	if (lpGuid == NULL)
		goto Failure;

	// store pointer to GUID in combo box
	*lpGuid = lpAppInfo->guidApplication;
	SendDlgItemMessage(hWnd, IDC_APPCOMBO, CB_SETITEMDATA, (WPARAM) iIndex, (LPARAM) lpGuid);

Failure:
    return (TRUE);
}

// ---------------------------------------------------------------------------
// EnumSP
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
BOOL FAR PASCAL EnumSP(LPGUID lpSPGuid, LPTSTR lptszDesc, DWORD dwMajorVersion,
			       DWORD dwMinorVersion, LPVOID lpContext)
{
    HWND			hWnd = lpContext;
    LRESULT			iIndex;
	LPGUID			lpGuid;

	// store service provider name in combo box
	iIndex = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_ADDSTRING, 0, (LPARAM) lptszDesc);
	if (iIndex == LB_ERR)
		goto Failure;

	// make space for service provider GUID
	lpGuid = (LPGUID) GlobalAllocPtr(GHND, sizeof(GUID));
	if (lpGuid == NULL)
		goto Failure;

	// store pointer to GUID in combo box
	*lpGuid = *lpSPGuid;
	SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETITEMDATA, (WPARAM) iIndex, (LPARAM) lpGuid);

Failure:
    return (TRUE);
}

// ---------------------------------------------------------------------------
// InitializeLauncherWindow
// ---------------------------------------------------------------------------
// Description:             Initializes the window for the Launcher.
// Arguments:
//  HWND                    [in] Window handle.
//  LPDIRECTPLAYLOBBY2A		[out] IDirectPlayLobby interface.
// Returns:
//  HRESULT					any errors initializing the window
HRESULT InitializeLauncherWindow(HWND hWnd, LPDIRECTPLAYLOBBY2A *lplpDPlayLobby)
{
	LPDIRECTPLAYLOBBYA	lpDPlayLobbyA = NULL;
	LPDIRECTPLAYLOBBY2A	lpDPlayLobby2A = NULL;
	HRESULT				hr;
		
	// get ANSI DirectPlayLobby interface
	hr = DirectPlayLobbyCreate(NULL, &lpDPlayLobbyA, NULL, NULL, 0);
	if FAILED(hr)
		goto Failure;

	// get ANSI DirectPlayLobby2 interface
	hr = lpDPlayLobbyA->lpVtbl->QueryInterface(lpDPlayLobbyA,
							&IID_IDirectPlayLobby2A, (LPVOID *) &lpDPlayLobby2A);
	if FAILED(hr)
		goto Failure;

	// don't need DirectPlayLobby interface anymore
	lpDPlayLobbyA->lpVtbl->Release(lpDPlayLobbyA);
	lpDPlayLobbyA = NULL;

	// put all the DirectPlay applications in a combo box
	lpDPlayLobby2A->lpVtbl->EnumLocalApplications(lpDPlayLobby2A, EnumApp, hWnd, 0);

	// put all the service providers in a combo box
	DirectPlayEnumerate(EnumSP, hWnd);

	// initialize the controls
	SendDlgItemMessage(hWnd, IDC_APPCOMBO, CB_SETCURSEL, (WPARAM) 0, 0);
	SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_SETCURSEL, (WPARAM) 0, 0);
	SendDlgItemMessage(hWnd, IDC_HOSTRADIO, BM_SETCHECK, (WPARAM) BST_CHECKED, 0);

	// update the address info display
	hr = UpdateAddressInfo(hWnd, lpDPlayLobby2A);

	// return the ANSI lobby interface
	*lplpDPlayLobby = lpDPlayLobby2A;

	return (DP_OK);

Failure:
	if (lpDPlayLobbyA)
		lpDPlayLobbyA->lpVtbl->Release(lpDPlayLobbyA);
	if (lpDPlayLobby2A)
		lpDPlayLobby2A->lpVtbl->Release(lpDPlayLobby2A);

	return (hr);
}

// ---------------------------------------------------------------------------
// DestroyLauncherWindow
// ---------------------------------------------------------------------------
// Description:             Destroys the launcher window.
// Arguments:
//  HWND                    [in] Window handle.
//  LPDIRECTPLAYLOBBY2A      [in] DirectPlay Lobby interface to destroy
// Returns:
//  Nothing
void DestroyLauncherWindow(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby)
{
	WPARAM	index;
	LRESULT	lpData;

	// destroy the GUID's stored with each app name
	index = 0;
	while (TRUE)
	{
		lpData = SendDlgItemMessage(hWnd, IDC_APPCOMBO, CB_GETITEMDATA, (WPARAM) index, 0);
		if ((lpData == CB_ERR) || (lpData == 0))
			break;

		GlobalFreePtr((LPVOID) lpData);
		index += 1;
	}

	// destroy the GUID's stored with each service provider name
	index = 0;
	while (TRUE)
	{
		lpData = SendDlgItemMessage(hWnd, IDC_SPCOMBO, CB_GETITEMDATA, (WPARAM) index, 0);
		if ((lpData == CB_ERR) || (lpData == 0))
			break;

		GlobalFreePtr((LPVOID) lpData);
		index += 1;
	}

	// release the lobby interface
	if (lpDPlayLobby)
		lpDPlayLobby->lpVtbl->Release(lpDPlayLobby);
}

// ---------------------------------------------------------------------------
// EnumAddressTypes
// ---------------------------------------------------------------------------
// Description:             Enumeration callback called by DirectPlayLobby.
//							Enumerates the address types supported by the
//							given Service Provider and returns them in a list.
// Arguments:
//  REFGUID                 [in] GUID of the address type
//  LPVOID				    [in] user-defined context
//  DWORD					[in] flags
// Returns:
//  BOOL					FALSE to stop enumerating after the first callback
BOOL FAR PASCAL EnumAddressTypes(REFGUID guidAddressType, LPVOID lpContext,
								DWORD dwFlags)
{
	LPADDRESSTYPELIST	lpAddressTypes = (LPADDRESSTYPELIST) lpContext;

	// make sure there is room
	if (lpAddressTypes->dwCount < ADDRESSTYPEMAX)
	{
		// save the address type guid in the list
		lpAddressTypes->guidAddressTypes[lpAddressTypes->dwCount] = *guidAddressType;
		lpAddressTypes->dwCount++;
	}

	return (TRUE);
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
HRESULT UpdateAddressInfo(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby)
{
	GUID			guidServiceProvider, guidAddressType;
	ADDRESSTYPELIST	addressTypeList;
	DWORD			i;
	HRESULT			hr;

	// get guid of currently selected service provider
	hr = GetComboBoxGuid(hWnd, IDC_SPCOMBO, &guidServiceProvider);
	if FAILED(hr)
		goto Failure;

	// get the list of address types for this service provider
	ZeroMemory(&addressTypeList, sizeof(ADDRESSTYPELIST));
	hr = lpDPlayLobby->lpVtbl->EnumAddressTypes(lpDPlayLobby,
			EnumAddressTypes, &guidServiceProvider, &addressTypeList, 0L);
	if FAILED(hr)
		goto Failure;

	// clear and hide address dialog items
	SendDlgItemMessage(hWnd, IDC_ADDRESSCOMBO, CB_RESETCONTENT,
								(WPARAM) 0, (LPARAM) 0);
	ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSCOMBO), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSCOMBOLABEL), SW_HIDE);

	SetDlgItemText(hWnd, IDC_ADDRESSEDIT, "");
	ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSEDIT), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSEDITLABEL), SW_HIDE);

	// loop over the address types
	for (i = 0; i < addressTypeList.dwCount; i++)
	{
		guidAddressType = addressTypeList.guidAddressTypes[i];

		// phone number
		if (IsEqualGUID(&guidAddressType, &DPAID_Phone))
		{
			SetDlgItemText(hWnd, IDC_ADDRESSEDITLABEL, "Phone number");
			ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSEDIT), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSEDITLABEL), SW_SHOW);
		}

		// modem
		else if (IsEqualGUID(&guidAddressType, &DPAID_Modem))
		{
			SetDlgItemText(hWnd, IDC_ADDRESSCOMBOLABEL, "Modem");
			ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSCOMBO), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSCOMBOLABEL), SW_SHOW);
			FillModemComboBox(hWnd, lpDPlayLobby, &guidServiceProvider);
		}

		// internet address
		else if (IsEqualGUID(&guidAddressType, &DPAID_INet))
		{
			SetDlgItemText(hWnd, IDC_ADDRESSEDITLABEL, "IP address");
			ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSEDIT), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, IDC_ADDRESSEDITLABEL), SW_SHOW);
		}
	}

Failure:
	return (hr);
}

// ---------------------------------------------------------------------------
// CreateAddress
// ---------------------------------------------------------------------------
// Description:             Creates a DPADDRESS using the address information
//							from the dialog.
// Arguments:
//  HWND					[in] window handle
//  LPDIRECTPLAYLOBBY2A      [in] DirectPlay Lobby interface to use
//  LPGUID					[in] GUID of servicer provider to create address for
//  LPVOID*					[out] pointer to return address in
//  LPDWORD					[out] pointer to return address size in
// Returns:
//  HRESULT					any error creating the address
HRESULT CreateAddress(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby,
					  LPGUID lpguidServiceProvider,
					  LPVOID *lplpAddress, LPDWORD lpdwAddressSize)
{
	GUID						guidAddressType;
	ADDRESSTYPELIST				addressTypeList;
	DPCOMPOUNDADDRESSELEMENT	addressElements[1 + ADDRESSTYPEMAX];
	CHAR						szPhoneNumberString[NAMEMAX];
	CHAR						szModemString[NAMEMAX];
	CHAR						szIPAddressString[NAMEMAX];
	LPVOID						lpAddress = NULL;
	DWORD						dwAddressSize = 0;
	DWORD						i, dwElementCount;
	HRESULT						hr;

	// get the list of address types for this service provider
	ZeroMemory(&addressTypeList, sizeof(ADDRESSTYPELIST));
	hr = lpDPlayLobby->lpVtbl->EnumAddressTypes(lpDPlayLobby,
			EnumAddressTypes, lpguidServiceProvider, &addressTypeList, 0L);
	if FAILED(hr)
		goto Failure;

	dwElementCount = 0;

	// all DPADDRESS's must have a service provider chunk
	addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
	addressElements[dwElementCount].dwDataSize = sizeof(GUID);
	addressElements[dwElementCount].lpData = lpguidServiceProvider;
	dwElementCount++;

	// loop over the address types
	for (i = 0; i < addressTypeList.dwCount; i++)
	{
		guidAddressType = addressTypeList.guidAddressTypes[i];

		// phone number
		if (IsEqualGUID(&guidAddressType, &DPAID_Phone))
		{
			// add a phone number chunk
			GetDlgItemText(hWnd, IDC_ADDRESSEDIT, szPhoneNumberString, NAMEMAX);
			addressElements[dwElementCount].guidDataType = DPAID_Phone;
			addressElements[dwElementCount].dwDataSize = lstrlen(szPhoneNumberString) + 1;
			addressElements[dwElementCount].lpData = szPhoneNumberString;
			dwElementCount++;
		}

		// modem
		else if (IsEqualGUID(&guidAddressType, &DPAID_Modem))
		{
			// add a modem chunk
			GetDlgItemText(hWnd, IDC_ADDRESSCOMBO, szModemString, NAMEMAX);
			addressElements[dwElementCount].guidDataType = DPAID_Modem;
			addressElements[dwElementCount].dwDataSize = lstrlen(szModemString) + 1;
			addressElements[dwElementCount].lpData = szModemString;
			dwElementCount++;
		}

		// internet address
		else if (IsEqualGUID(&guidAddressType, &DPAID_INet))
		{
			// add an IP address chunk
			GetDlgItemText(hWnd, IDC_ADDRESSEDIT, szIPAddressString, NAMEMAX);
			addressElements[dwElementCount].guidDataType = DPAID_INet;
			addressElements[dwElementCount].dwDataSize = lstrlen(szIPAddressString) + 1;
			addressElements[dwElementCount].lpData = szIPAddressString;
			dwElementCount++;
		}
	}

	// bail if no address data is available
	if (dwElementCount == 1)
		return (DPERR_GENERIC);
	
	// see how much room is needed to store this address
	hr = lpDPlayLobby->lpVtbl->CreateCompoundAddress(lpDPlayLobby,
						addressElements, dwElementCount,
						NULL, &dwAddressSize);
	if (hr != DPERR_BUFFERTOOSMALL)
		goto Failure;

	// allocate space
	lpAddress = GlobalAllocPtr(GHND, dwAddressSize);
	if (lpAddress == NULL)
	{
		hr = DPERR_NOMEMORY;
		goto Failure;
	}

	// create the address
	hr = lpDPlayLobby->lpVtbl->CreateCompoundAddress(lpDPlayLobby,
						addressElements, dwElementCount,
						lpAddress, &dwAddressSize);
	if FAILED(hr)
		goto Failure;

	// return the address info
	*lplpAddress = lpAddress;
	*lpdwAddressSize = dwAddressSize;

	return (DP_OK);

Failure:
	if (lpAddress)
		GlobalFreePtr(lpAddress);

	return (hr);
}

// ---------------------------------------------------------------------------
// RunApplication
// ---------------------------------------------------------------------------
// Description:             Wrapper for the IDirectPlayLobby::RunApplication() method.
// Arguments:
//  LPDIRECTPLAYLOBBY2A		[in] DirectPlay Lobby interface to use
//  LPGUID					[in] GUID of application to launch
//  LPGUID					[in] GUID of session to host with
//  LPSTR					[in] GUID of service provider to connect with
//  LPVOID					[in] service-provider address to connect to
//  DWORD					[in] length of address
//  LPSTR					[in] name of session to host
//  LPSTR					[in] name of our player
//  BOOL					[in] TRUE to host session, FALSE to join
// Returns:
//  HRESULT					any error running the application
HRESULT RunApplication(LPDIRECTPLAYLOBBY2A lpDPlayLobby,
					   LPGUID lpguidApplication,
					   LPGUID lpguidInstance,
					   LPGUID lpguidServiceProvider,
					   LPVOID lpAddress,
					   DWORD  dwAddressSize,
					   LPSTR  lpszSessionName,
					   LPSTR  lpszPlayerName,
					   BOOL	  bHostSession)
{
	DWORD				appID;
	DPSESSIONDESC2		sessionInfo;
	DPNAME				playerName;
	DPLCONNECTION		connectInfo;
	HRESULT				hr;

	if (lpDPlayLobby == NULL)
		return (DPERR_NOINTERFACE);

	// fill out session description
	ZeroMemory(&sessionInfo, sizeof(DPSESSIONDESC2));
    sessionInfo.dwSize = sizeof(DPSESSIONDESC2);	// Size of structure
	sessionInfo.dwFlags = 0;						// DPSESSION_xxx flags
    sessionInfo.guidInstance = *lpguidInstance;		// ID for the session instance
    sessionInfo.guidApplication = *lpguidApplication;// GUID of the DirectPlay application.
    sessionInfo.dwMaxPlayers = 0;					// Maximum # players allowed in session
    sessionInfo.dwCurrentPlayers = 0;				// Current # players in session (read only)
	sessionInfo.lpszSessionNameA = lpszSessionName;	// ANSI name of the session
	sessionInfo.lpszPasswordA = NULL;				// ANSI password of the session (optional)
	sessionInfo.dwReserved1 = 0;					// Reserved for future MS use.
    sessionInfo.dwReserved2 = 0;
    sessionInfo.dwUser1 = 0;						// For use by the application
    sessionInfo.dwUser2 = 0;
    sessionInfo.dwUser3 = 0;
    sessionInfo.dwUser4 = 0;

	// fill out player name
	ZeroMemory(&playerName, sizeof(DPNAME));
	playerName.dwSize = sizeof(DPNAME);				// Size of structure
    playerName.dwFlags = 0;							// Not used. Must be zero.
	playerName.lpszShortNameA = lpszPlayerName;		// ANSI short or friendly name
	playerName.lpszLongNameA = lpszPlayerName;		// ANSI long or formal name
	
	// fill out connection description
	ZeroMemory(&connectInfo, sizeof(DPLCONNECTION));
	connectInfo.dwSize = sizeof(DPLCONNECTION);		// Size of this structure
	if (bHostSession)
		connectInfo.dwFlags = DPLCONNECTION_CREATESESSION; // Create a new session
	else
		connectInfo.dwFlags = DPLCONNECTION_JOINSESSION; // Join existing session
	connectInfo.lpSessionDesc = &sessionInfo;		// Pointer to session desc to use on connect
	connectInfo.lpPlayerName = &playerName;			// Pointer to Player name structure
	connectInfo.guidSP = *lpguidServiceProvider;	// GUID of the DPlay SP to use
	connectInfo.lpAddress = lpAddress;				// Address for service provider
	connectInfo.dwAddressSize = dwAddressSize;		// Size of address data

	// launch and connect the game
	hr = lpDPlayLobby->lpVtbl->RunApplication(lpDPlayLobby,
										0,			// Flags
										&appID,		// App ID
										&connectInfo,	// Connection data
										NULL);		// Connect event
	return (hr);
}

// ---------------------------------------------------------------------------
// LaunchDirectPlayApplication
// ---------------------------------------------------------------------------
// Description:             Gathers information from the dialog and runs the application.
// Arguments:
//  HWND                    [in] Window handle.
//  LPDIRECTPLAYLOBBY2A      [in] DirectPlay Lobby interface to use
// Returns:
//  Nothing
void LaunchDirectPlayApplication(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby)
{
	GUID				guidApplication, guidSession, guidServiceProvider;
	LPSTR				lpPlayerName, lpSessionName;
	LPVOID				lpAddress = NULL;
	DWORD				dwAddressSize = 0;
	CHAR				szPlayerName[NAMEMAX], szSessionName[NAMEMAX];
	LRESULT				iHost;
	HRESULT				hr;

	SetDlgItemText(hWnd, IDC_STATUSEDIT, "Launching...");

	// get guid of application to launch
	hr = GetComboBoxGuid(hWnd, IDC_APPCOMBO, &guidApplication);
	if FAILED(hr)
		goto Failure;

	// get guid of service provider to use
	hr = GetComboBoxGuid(hWnd, IDC_SPCOMBO, &guidServiceProvider);
	if FAILED(hr)
		goto Failure;

	// get address to use with this service provider
	hr = CreateAddress(hWnd, lpDPlayLobby, &guidServiceProvider,
					   &lpAddress, &dwAddressSize);
	// ignore the error because lpAddress will just be null

	// get guid of session to create.
	guidSession = MY_SESSION_GUID;
	
	// get name of our player
	GetDlgItemText(hWnd, IDC_PLAYEREDIT, szPlayerName, NAMEMAX);
	lpPlayerName = szPlayerName;

	// get host vs. join flag
	iHost = SendDlgItemMessage(hWnd, IDC_HOSTRADIO, BM_GETCHECK, (WPARAM) 0, 0);
	if (iHost == BST_CHECKED)
	{
		iHost = TRUE;			// we are hosting a session

		// get name of session
		GetDlgItemText(hWnd, IDC_SESSIONEDIT, szSessionName, NAMEMAX);
		lpSessionName = szSessionName;
	}
	else
	{
		iHost = FALSE;			// we are joining an existing session
		lpSessionName = NULL;	// don't need a session name if we are joining
	}

	// launch the application
	hr = RunApplication(lpDPlayLobby,
						&guidApplication,
						&guidSession,
						&guidServiceProvider,
						lpAddress, dwAddressSize,
						lpSessionName, lpPlayerName,
						iHost);
	if FAILED(hr)
		goto Failure;

	SetDlgItemText(hWnd, IDC_STATUSEDIT, "Launch successful");

	if (lpAddress)
		GlobalFreePtr(lpAddress);
	return;

Failure:
	if (lpAddress)
		GlobalFreePtr(lpAddress);

	SetDlgItemText(hWnd, IDC_STATUSEDIT, "Launch failed");

	return;
}

// ---------------------------------------------------------------------------
// GetComboBoxGuid
// ---------------------------------------------------------------------------
// Description:             Returns GUID stored with a combo box item
// Arguments:
//  HWND                    [in]  Window handle.
//  LONG					[in]  Dialog box item ID of combo box
//  LPGUID					[out] GUID stored with item in combo box
// Returns:
//  HRESULT					any error getting the GUID
HRESULT GetComboBoxGuid(HWND hWnd, LONG iDialogItem, LPGUID lpguidReturn)
{
	LONG	iIndex;

	// get index of selected item
	iIndex = SendDlgItemMessage(hWnd, iDialogItem, CB_GETCURSEL,
								(WPARAM) 0, (LPARAM) 0);
	if (iIndex == CB_ERR)
		return (DPERR_GENERIC);

	// get data associated with this item
	iIndex = SendDlgItemMessage(hWnd, iDialogItem, CB_GETITEMDATA,
								(WPARAM) iIndex, (LPARAM) 0);
	if ((iIndex == CB_ERR) || (iIndex == 0))
		return (DPERR_GENERIC);

	// data is a pointer to a guid
	*lpguidReturn = *((LPGUID) iIndex);

	return (DP_OK);
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
			SendDlgItemMessage(hWnd, IDC_ADDRESSCOMBO, CB_ADDSTRING, 0, (LPARAM) lpszStr);

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
HRESULT FillModemComboBox(HWND hWnd, LPDIRECTPLAYLOBBY2A lpDPlayLobby, LPGUID lpguidServiceProvider)
{
	LPDIRECTPLAY		lpDPlay1 = NULL;
	LPDIRECTPLAY3A		lpDPlay3A = NULL;
	LPVOID				lpAddress = NULL;
	DWORD				dwAddressSize = 0;
	HRESULT				hr;

	// get a DirectPlay interface for this service provider
	hr = DirectPlayCreate(lpguidServiceProvider, &lpDPlay1, NULL);
	if FAILED(hr)
		goto Failure;

	// query for an ANSI DirectPlay3 interface
	hr = lpDPlay1->lpVtbl->QueryInterface(lpDPlay1, &IID_IDirectPlay3A, (LPVOID *) &lpDPlay3A);
	if FAILED(hr)
		goto Failure;

	// get size of player address for player zero
	hr = lpDPlay3A->lpVtbl->GetPlayerAddress(lpDPlay3A, DPID_ALLPLAYERS, NULL, &dwAddressSize);
	if (hr != DPERR_BUFFERTOOSMALL)
		goto Failure;

	// make room for it
	lpAddress = GlobalAllocPtr(GHND, dwAddressSize);
	if (lpAddress == NULL)
	{
		hr = DPERR_NOMEMORY;
		goto Failure;
	}

	// get the address
	hr = lpDPlay3A->lpVtbl->GetPlayerAddress(lpDPlay3A, DPID_ALLPLAYERS, lpAddress, &dwAddressSize);
	if FAILED(hr)
		goto Failure;
	
	// get modem strings from address and put them in the combo box
	hr = lpDPlayLobby->lpVtbl->EnumAddress(lpDPlayLobby, EnumModemAddress, 
							 lpAddress, dwAddressSize, hWnd);
	if FAILED(hr)
		goto Failure;

	// select first item in list
	SendDlgItemMessage(hWnd, IDC_ADDRESSCOMBO, CB_SETCURSEL, (WPARAM) 0, 0);

Failure:
	if (lpDPlay1)
		lpDPlay1->lpVtbl->Release(lpDPlay1);
	if (lpDPlay3A)
		lpDPlay3A->lpVtbl->Release(lpDPlay3A);
	if (lpAddress)
		GlobalFreePtr(lpAddress);

	return (hr);
}

