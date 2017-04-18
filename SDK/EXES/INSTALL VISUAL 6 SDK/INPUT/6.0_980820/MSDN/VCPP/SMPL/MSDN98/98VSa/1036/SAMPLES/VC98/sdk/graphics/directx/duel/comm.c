 /*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       comm.c
 *  Content:    DirectPlay related code
 *
 *
 ***************************************************************************/
#include "comm.h"
#include "lobby.h"

/*
 * Externals
 */
extern LPGUID						glpGuid;			// duel's guid
extern LPDPLCONNECTION				glpdplConnection;	// connection settings

/*
 * Globals
 */
LPDPSESSIONDESC2					glpdpSD;			// current session description
LPDIRECTPLAY2						glpDP	= NULL;		// directplay object pointer
LPDIRECTPLAY3A						glpDP3A	= NULL;

/*
 * DPlayClose
 *
 * Wrapper for DirectPlay Close API
 */
HRESULT DPlayClose(void)
{
	HRESULT hr=E_FAIL;

	if (glpDP) 
		hr = IDirectPlay2_Close(glpDP);
	
	return hr;
}

/*
 * DPlayCreate
 *
 * Wrapper for DirectPlay Create API. Retrieves a DirectPlay2/DirectPlay2A interface
 * based on the UNICODE flag
 * 
 */
HRESULT DPlayCreate(LPVOID lpCon)
{
	HRESULT			hr		= E_FAIL;
	LPDIRECTPLAY3	lpDP3	= NULL;

	hr = CoCreateInstance(	&CLSID_DirectPlay, NULL, CLSCTX_INPROC_SERVER,
							&IID_IDirectPlay3A, (LPVOID *) &glpDP3A );
	
	if ( DP_OK == hr )
	{
		if (lpCon)
		{
			hr = IDirectPlay3_InitializeConnection( glpDP3A, lpCon, 0);
		}

		// query for a DirectPlay2(A) interface
#ifdef UNICODE
		hr = IDirectPlay_QueryInterface(glpDP3A,&IID_IDirectPlay2,(LPVOID *)&glpDP);
#else
		hr = IDirectPlay_QueryInterface(glpDP3A,&IID_IDirectPlay2A,(LPVOID *)&glpDP);
#endif

	}

	return hr;
}

/*
 * DPlayCreatePlayer
 *
 * Wrapper for DirectPlay CreatePlayer API. 
 */

HRESULT DPlayCreatePlayer(LPDPID lppidID, LPTSTR lptszPlayerName, HANDLE hEvent, 
						  LPVOID lpData, DWORD dwDataSize)
{
	HRESULT hr=E_FAIL;
	DPNAME name;
	
	ZeroMemory(&name,sizeof(name));
	name.dwSize = sizeof(DPNAME);

#ifdef UNICODE
	name.lpszShortName = lptszPlayerName;
#else
	name.lpszShortNameA = lptszPlayerName;
#endif

	if (glpDP)
		hr = IDirectPlay2_CreatePlayer(glpDP, lppidID, &name, hEvent, lpData, 
									  dwDataSize, 0);
									
	return hr;
}

/*
 * DPlayCreateSession
 *
 * Wrapper for DirectPlay CreateSession API.Uses the global application guid (glpGuid).
 */
HRESULT DPlayCreateSession(LPTSTR lptszSessionName)
{
	HRESULT hr = E_FAIL;
	DPSESSIONDESC2 dpDesc;

    ZeroMemory(&dpDesc, sizeof(dpDesc));
    dpDesc.dwSize = sizeof(dpDesc);
	dpDesc.dwFlags = DPSESSION_MIGRATEHOST | DPSESSION_KEEPALIVE;

#ifdef UNICODE
	dpDesc.lpszSessionName = lptszSessionName;
#else
	dpDesc.lpszSessionNameA = lptszSessionName;
#endif

	// set the application guid
	if (glpGuid)
		dpDesc.guidApplication = *glpGuid;

	if (glpDP)
		hr = IDirectPlay2_Open(glpDP, &dpDesc, DPOPEN_CREATE);

	return hr;
}

/*
 * DPlayDestroyPlayer
 * 
 * Wrapper for DirectPlay DestroyPlayer API. 
 */
HRESULT DPlayDestroyPlayer(DPID pid)
{
	HRESULT hr=E_FAIL;
	
    if (glpDP)
		hr = IDirectPlay2_DestroyPlayer(glpDP, pid);

	return hr;
}

/*
 * DPlayEnumPlayers
 *
 * Wrapper for DirectPlay API EnumPlayers
 */
HRESULT DPlayEnumPlayers(LPGUID lpSessionGuid, LPDPENUMPLAYERSCALLBACK2 lpEnumCallback, 
						 LPVOID lpContext, DWORD dwFlags)
{
	HRESULT hr=E_FAIL;

	if (glpDP)
		hr = IDirectPlay2_EnumPlayers(glpDP, lpSessionGuid, lpEnumCallback, lpContext, dwFlags);

	return hr;
}

/*
 * DPlayEnumSessions
 *
 * Wrapper for DirectPlay EnumSessions API.
 */
HRESULT DPlayEnumSessions(DWORD dwTimeout, LPDPENUMSESSIONSCALLBACK2 lpEnumCallback, 
						  LPVOID lpContext, DWORD dwFlags)
{
	HRESULT hr = E_FAIL;
    DPSESSIONDESC2 dpDesc;

	ZeroMemory(&dpDesc, sizeof(dpDesc));
	dpDesc.dwSize = sizeof(dpDesc);
	if (glpGuid)
		dpDesc.guidApplication = *glpGuid;

	if (glpDP)
		hr = IDirectPlay2_EnumSessions(glpDP, &dpDesc, dwTimeout, lpEnumCallback,
										lpContext, dwFlags);


	return hr;
}

/*
 * DPlayGetPlayerData
 * 
 * Wrapper for DirectPlay GetPlayerData API.
 */
HRESULT DPlayGetPlayerData(DPID pid, LPVOID lpData, LPDWORD lpdwDataSize, DWORD dwFlags)
{
	HRESULT hr=E_FAIL;

	if (glpDP) 
		hr = IDirectPlay2_GetPlayerData(glpDP, pid, lpData, lpdwDataSize, dwFlags);

	return hr;
}

/*
 * DPlayGetSessionDesc
 *
 * Wrapper for DirectPlay GetSessionDesc API. 
 */
HRESULT DPlayGetSessionDesc(void)
{
	HRESULT hr=E_FAIL;
	DWORD dwSize;

	// free old session desc, if any
	if (glpdpSD)
	{
		free(glpdpSD);
		glpdpSD = NULL;
	}

	if (glpDP)
	{
		// first get the size for the session desc
		if ((hr = IDirectPlay2_GetSessionDesc(glpDP, NULL, &dwSize)) == DPERR_BUFFERTOOSMALL)
		{
			// allocate memory for it
			glpdpSD = (LPDPSESSIONDESC2) malloc(dwSize);
			if (glpdpSD)
			{
				// now get the session desc
				hr = IDirectPlay2_GetSessionDesc(glpDP, glpdpSD, &dwSize);
			}
			else
			{
				hr = E_OUTOFMEMORY;
			}
		}
	}

	return hr;
}

/*
 * IsDPlay
 *
 * Returns TRUE if a DirectPlay interface exists, otherwise FALSE.
 */
BOOL IsDPlay(void)
{
	return (glpDP ? TRUE:FALSE);
}

/*
 * DPlayOpenSession
 *
 * Wrapper for DirectPlay OpenSession API. 
 */
HRESULT DPlayOpenSession(LPGUID lpSessionGuid)
{
	HRESULT hr = E_FAIL;
	DPSESSIONDESC2 dpDesc;

    ZeroMemory(&dpDesc, sizeof(dpDesc));
    dpDesc.dwSize = sizeof(dpDesc);

	// set the session guid
	if (lpSessionGuid)
		dpDesc.guidInstance = *lpSessionGuid;
	// set the application guid
	if (glpGuid)
		dpDesc.guidApplication = *glpGuid;

	// open it
	if (glpDP)
		hr = IDirectPlay2_Open(glpDP, &dpDesc, DPOPEN_JOIN);

	return hr;
}


/*
 * DPlayReceive
 *
 * Wrapper for DirectPlay Receive API
 */
HRESULT DPlayReceive(LPDPID lpidFrom, LPDPID lpidTo, DWORD dwFlags, LPVOID lpData, LPDWORD lpdwDataSize)
{
	HRESULT hr = E_FAIL;

	if (glpDP)
		hr = IDirectPlay2_Receive(glpDP, lpidFrom, lpidTo, dwFlags, lpData, lpdwDataSize);
	
	return hr;
}

/*
 * DPlayRelease
 *
 * Wrapper for DirectPlay Release API.
 */
HRESULT DPlayRelease(void)
{
	HRESULT hr = E_FAIL;

	if (glpDP)
	{
		// free session desc, if any
		if (glpdpSD) 
		{
			free(glpdpSD);
			glpdpSD = NULL;
		}

		// free connection settings structure, if any (lobby stuff)
		if (glpdplConnection)
		{
			free(glpdplConnection);
			glpdplConnection = NULL;
		}
		// release dplay
		hr = IDirectPlay2_Release(glpDP);
		glpDP = NULL;
	}

	if (glpDP3A)
	{
		hr = IDirectPlay3_Release(glpDP3A);
		glpDP3A = NULL;
	}

	return hr;
}

/*
 * DPlaySend
 * 
 * Wrapper for DirectPlay Send API.
 */
HRESULT DPlaySend(DPID idFrom, DPID idTo, DWORD dwFlags, LPVOID lpData, DWORD dwDataSize)
{
	HRESULT hr = E_FAIL;

	if (glpDP)
		hr = IDirectPlay2_Send(glpDP, idFrom, idTo, dwFlags, lpData, dwDataSize);
	
	return hr;
}

/*
 * DPlaySetPlayerData
 *
 * Wrapper for DirectPlay SetPlayerData API
 */
HRESULT DPlaySetPlayerData(DPID pid, LPVOID lpData, DWORD dwSize, DWORD dwFlags)
{
	HRESULT hr=E_FAIL;

	if (glpDP)
		hr = IDirectPlay2_SetPlayerData(glpDP, pid, lpData, dwSize, dwFlags);
	
	return hr;
}

