/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       lobby.c
 *  Content:    DirectPlayLobby related code
 *
 *
 ***************************************************************************/
#include "lobby.h"

/*
 * Externals
 */
extern LPDIRECTPLAY2				glpDP;			 		// directplay object pointer

/*
 * Globals
 */
LPDPLCONNECTION						glpdplConnection;		// connection settings

/*
 * Statics
 */
static LPDIRECTPLAYLOBBY			glpDPL;					// lobby object pointer



/*
 * DPLobbyCreate
 *
 * Wrapper for DirectPlayLobby DirectPlayLobbyCreate API.
 */
HRESULT DPLobbyCreate(void)
{
	HRESULT hr=E_FAIL;

	hr = DirectPlayLobbyCreate(NULL, &glpDPL, NULL, NULL, 0);	

	return hr;
}

/*
 * DPLobbyConnect
 *
 * Wrapper for DirectPlayLobby Connect API.
 */
HRESULT DPLobbyConnect(void)
{
	HRESULT hr=E_FAIL;

	hr = IDirectPlayLobby_Connect(glpDPL, 0, &glpDP, NULL) ;	

	return hr;
}

/*
 * DPLobbyGetConnectionSettings
 *
 * Wrapper for DirectPlayLobby GetConnectionSettings API
 */
HRESULT DPLobbyGetConnectionSettings(void)
{
	HRESULT hr=E_FAIL;
	DWORD dwSize;

	if (glpDPL)
	{
		// get size for the connection settings structure
		hr = IDirectPlayLobby_GetConnectionSettings(glpDPL, 0, NULL, &dwSize);
		if (DPERR_BUFFERTOOSMALL == hr)
		{ 
			// if we already have one, free it
			if (glpdplConnection)
			{
				free(glpdplConnection);
				glpdplConnection = NULL;
			}

			// allocate memory for the new one
			glpdplConnection = (LPDPLCONNECTION) malloc(dwSize);

			// get the connection settings
			if (glpdplConnection)
				hr = IDirectPlayLobby_GetConnectionSettings(glpDPL, 0, glpdplConnection, &dwSize);
		}
	}

	return hr;
}

/*
 * DPLobbyRelease
 *
 * Wrapper for DirectPlayLobby Release API
 */
HRESULT DPLobbyRelease(void)
{
	HRESULT hr=E_FAIL;

	// free our connection settings
	if (glpdplConnection)
	{
		free(glpdplConnection);
		glpdplConnection = NULL;
	}

	// release the lobby object
	if (glpDPL)
	{
		hr = IDirectPlayLobby_Release(glpDPL);
		glpDPL = NULL;
	}
	return hr;
}

/*
 * DPLobbySetConnectionSettings
 *
 * Wrapper for DirectPlayLobby SetConnectionSettings API
 */
HRESULT DPLobbySetConnectionSettings(void)
{
	HRESULT hr=E_FAIL;

    hr = IDirectPlayLobby_SetConnectionSettings(glpDPL, 0, 0, glpdplConnection);

	return hr;
}

