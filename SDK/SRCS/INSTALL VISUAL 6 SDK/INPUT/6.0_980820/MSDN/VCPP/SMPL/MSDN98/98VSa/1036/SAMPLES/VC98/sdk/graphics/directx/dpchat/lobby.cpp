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

#include "dpchat.h"

HRESULT ConnectUsingLobby(LPDPLAYINFO lpDPInfo)
{
	LPDIRECTPLAY2A		lpDirectPlay2A = NULL;
	LPDIRECTPLAY3A		lpDirectPlay3A = NULL;
	LPDIRECTPLAYLOBBYA	lpDirectPlayLobbyA = NULL;
	LPDPLCONNECTION		lpConnectionSettings = NULL;
	DPID				dpidPlayer;
	DWORD				dwSize;
	HRESULT				hr;

	// get an ANSI DirectPlay lobby interface
	hr = DirectPlayLobbyCreate(NULL, &lpDirectPlayLobbyA, NULL, NULL, 0);
	if FAILED(hr)
		goto FAILURE;

    // get connection settings from the lobby
	// if this routine returns DPERR_NOTLOBBIED, then a lobby did not
	// launch this application and the user needs to configure the connection.

	// pass in a NULL pointer to just get the size of the connection setttings
	hr = lpDirectPlayLobbyA->GetConnectionSettings(0, NULL, &dwSize);
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
	hr = lpDirectPlayLobbyA->GetConnectionSettings(0, lpConnectionSettings, &dwSize);
	if FAILED(hr)
		goto FAILURE;

	// before connecting, the game should configure the session description
	// with any settings it needs

	// set flags and max players used by the game
    lpConnectionSettings->lpSessionDesc->dwFlags = DPSESSION_MIGRATEHOST | 
												   DPSESSION_KEEPALIVE;
    lpConnectionSettings->lpSessionDesc->dwMaxPlayers = MAXPLAYERS;

    // store the updated connection settings
    hr = lpDirectPlayLobbyA->SetConnectionSettings(0, 0, lpConnectionSettings);
	if FAILED(hr)
		goto FAILURE;

	// connect to the session - returns an ANSI IDirectPlay2A interface
	hr = lpDirectPlayLobbyA->Connect(0, &lpDirectPlay2A, NULL);
	if FAILED(hr)
		goto FAILURE;

	// Obtain an IDirectPlay3A interface, the IDirectPlay2A interface will
	// be released at the end of the function
	hr = lpDirectPlay2A->QueryInterface(IID_IDirectPlay3A, (LPVOID *) &lpDirectPlay3A);
	if FAILED(hr)
		goto FAILURE;

	// create a player with the name returned in the connection settings
	hr = lpDirectPlay3A->CreatePlayer(&dpidPlayer,
							lpConnectionSettings->lpPlayerName, 
							lpDPInfo->hPlayerEvent, NULL, 0, 0);
	if FAILED(hr)
		goto FAILURE;

	// return connection info
	lpDPInfo->lpDirectPlay3A = lpDirectPlay3A;
	lpDPInfo->dpidPlayer = dpidPlayer;
	if (lpConnectionSettings->dwFlags & DPLCONNECTION_CREATESESSION)
		lpDPInfo->bIsHost = TRUE;
	else
		lpDPInfo->bIsHost = FALSE;

	lpDirectPlay3A = NULL;	// set to NULL here so it won't release below

FAILURE:
	if (lpDirectPlay2A)
		lpDirectPlay2A->Release();

	if (lpDirectPlay3A)
		lpDirectPlay3A->Release();

	if (lpDirectPlayLobbyA)
		lpDirectPlayLobbyA->Release();

	if (lpConnectionSettings)
		GlobalFreePtr(lpConnectionSettings);

	return (hr);
}
