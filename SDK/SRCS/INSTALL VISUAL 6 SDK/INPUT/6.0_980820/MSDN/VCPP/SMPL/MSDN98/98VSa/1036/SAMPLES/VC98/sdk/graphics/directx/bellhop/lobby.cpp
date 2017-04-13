/*==========================================================================
 *
 *  Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       lobby.cpp
 *  Content:	Uses information from the lobby to establish a connection.
 *
 ***************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <dplobby.h>

#include "bellhop.h"

HRESULT ConnectUsingLobby(LPDPLAYINFO lpDPInfo)
{
	LPDIRECTPLAY2A		lpDirectPlay2A = NULL;
	LPDIRECTPLAY3A		lpDirectPlay3A = NULL;
	LPDIRECTPLAYLOBBY2A	lpDirectPlayLobby2A = NULL;
	LPDPLCONNECTION		lpConnectionSettings = NULL;
	DPID				dpidPlayer;
	DWORD				dwSize;
	HRESULT				hr;

	// get an ANSI DirectPlay lobby interface
	hr = CreateDirectPlayLobbyInterface(&lpDirectPlayLobby2A );
	if FAILED(hr)
		goto FAILURE;

    // get connection settings from the lobby
	// if this routine returns DPERR_NOTLOBBIED, then a lobby did not
	// launch this application and the user needs to configure the connection.

	// pass in a NULL pointer to just get the size of the connection setttings
	hr = lpDirectPlayLobby2A->GetConnectionSettings(0, NULL, &dwSize);
	if (DPERR_BUFFERTOOSMALL != hr)
		goto FAILURE;

	// allocate memory for the connection setttings
	lpConnectionSettings = (LPDPLCONNECTION) GlobalAllocPtr(GHND, dwSize);
	if (NULL == lpConnectionSettings)
	{
		hr = DPERR_OUTOFMEMORY;
		goto FAILURE;
	}

	// get the connection settings
	hr = lpDirectPlayLobby2A->GetConnectionSettings(0, lpConnectionSettings, &dwSize);
	if FAILED(hr)
		goto FAILURE;

	// before connecting, the game should configure the session description
	// with any settings it needs

	// set flags and max players used by the game
    lpConnectionSettings->lpSessionDesc->dwFlags = DPSESSION_MIGRATEHOST | 
												   DPSESSION_KEEPALIVE;
    lpConnectionSettings->lpSessionDesc->dwMaxPlayers = MAXPLAYERS;

    // store the updated connection settings
    hr = lpDirectPlayLobby2A->SetConnectionSettings(0, 0, lpConnectionSettings);
	if FAILED(hr)
		goto FAILURE;

	// connect to the session - returns an ANSI IDirectPlay2A interface
	hr = lpDirectPlayLobby2A->Connect(0, &lpDirectPlay2A, NULL);
	if FAILED(hr)
		goto FAILURE;

	// Obtain an IDirectPlay3A interface, the IDirectPlay2A interface will
	// be released at the end of the function
	hr = IDirectPlay2_QueryInterface(lpDirectPlay2A, IID_IDirectPlay3A, (LPVOID *) &lpDirectPlay3A);
	if FAILED(hr)
		goto FAILURE;

	// create a player with the name returned in the connection settings
	hr = IDirectPlay3_CreatePlayer(lpDirectPlay3A, &dpidPlayer,
							lpConnectionSettings->lpPlayerName, 
							lpDPInfo->hPlayerEvent, NULL, 0, 0);
	if FAILED(hr)
		goto FAILURE;

	// return connection info
	lpDPInfo->lpDirectPlay3A = lpDirectPlay3A;
	lpDPInfo->lpDirectPlayLobby2A = lpDirectPlayLobby2A;

	lpDPInfo->dpidPlayer = dpidPlayer;
	if (lpConnectionSettings->dwFlags & DPLCONNECTION_CREATESESSION)
		lpDPInfo->bIsHost = TRUE;
	else
		lpDPInfo->bIsHost = FALSE;

	// set our interfaces to NULL here 
	// so they won't be released below

	lpDirectPlay3A = NULL;
	lpDirectPlayLobby2A = NULL;

FAILURE:
	if (lpDirectPlay2A)
		IDirectPlay2_Release(lpDirectPlay2A);

	if (lpDirectPlay3A)
		IDirectPlay3_Release(lpDirectPlay3A);

	if (lpDirectPlayLobby2A)
		IDirectPlayLobby_Release(lpDirectPlayLobby2A);

	if (lpConnectionSettings)
		GlobalFreePtr(lpConnectionSettings);

	return (hr);
}
