/*==========================================================================
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       LSPsession.cpp
 *
 *	Content:	Code file for session-oriented LOBBY-SP callback functions
 *
 *  Functions:  LP_Open
 *              LP_Close
 *              LP_StratSession
 *				LP_EnumSessions
 *				LP_GetCaps
 *
 *	History:	1999/09/02		Created it
 *
 *=========================================================================*/
#include <windows.h>

// include of DLPAY
#include "dplay.h"		// defined return code (DP_,DPERR_)
#include "lobbysp.h"	// defined structer (LPSPDATA_xxxxxxx)

// include of LOBBY-SP
#include "LSPlobby.h"
#include "LSPdebug.h"
#include "LSPfuncs.h"	// defined callback function

// include of original functions 
#include "SRScom.h"
#include "SRLregistry.h"
#include "SRLmanage.h"
#include "SRLsend.h"

/*==========================================================================
 *
 *  LP_Open iBuild up server connectionj
 *
 *  SPDATA_OPEN
 * 	 DWORD				dwSize;			// Size of this structure (including data)
 *	 LPDPLOBBYSP		lpISP;	    	// Pointer to an IDPLobbySP interface
 *	 LPDPSESSIONDESC2	lpsd;			// Pointer to SessionDesc of the Lobby to open
 *											 (defined dplay.h)
 *	 DWORD				dwFlags;		// Flags
 *	 LPCDPCREDENTIALS	lpCredentials;	// Pointer to a Credentials structure
 *
 *
 *	CDPCREDENTIALS
 *   DWORD dwSize;               // Size of structure
 *   DWORD dwFlags;              // Not used. Must be zero.
 *   union
 *   {                           // User name of the account
 *       LPWSTR  lpszUsername;   // Unicode
 *       LPSTR   lpszUsernameA;  // ANSI
 *   };
 *   union
 *   {                           // Password of the account
 *       LPWSTR  lpszPassword;   // Unicode
 *       LPSTR   lpszPasswordA;  // ANSI
 *   };
 *   union
 *   {                           // Domain name of the account
 *       LPWSTR  lpszDomain;     // Unicode
 *       LPSTR   lpszDomainA;    // ANSI
 *   };
 * 
 *=========================================================================*/
HRESULT WINAPI LP_Open(LPSPDATA_OPEN lpOpen)
{
	int		iPort;
	char	cServerIP[64];
	TCHAR	tcServerIP[40];
//	LPDPSESSIONDESC2 lpData;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_OPEN );

	//===============================
	//  Get server data	         
	//===============================

	memset(cServerIP,NULL,sizeof(cServerIP));
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, LSP_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_OPEN, SRL_REG_KEY_COM, LSP_REG_SERVERIP);
		return DPERR_GENERIC;
	}

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s SPDATA_OPEN size=%d DPSESSIONDESC2 size=%d \n"),
					DBG_NAME_OPEN, lpOpen->dwSize,lpOpen->lpsd->dwSize);
//	memset( cServerIP, 0, sizeof(cServerIP) );
//	memcpy( cServerIP,(char *)lpOpen->lpsd->lpszSessionName, 16 );
	memset( tcServerIP, 0, sizeof(tcServerIP) );
	mbstowcs(tcServerIP,cServerIP,strlen(cServerIP));
	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s Open serverIP len=%d IP=%s\n"),
					DBG_NAME_OPEN, strlen(cServerIP),tcServerIP );



	//===============================
	//  Set server data 		         
	//===============================
//	if( SRL_Reg_SetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
//	{
//		// Ý’èŽ¸”s
//		LSP_Dbg_Printf( DBG_LEVEL_0,
//						TEXT("%s: SRL_Reg_SetInfo(%s %s)DPERR_GENERIC return\n"),
//								DBG_NAME_OPEN, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
//		return DPERR_GENERIC;
//	}

	//===============================
	//  Send to request connection           
	//===============================
	iPort = SRL_Snd_Connect( cServerIP );
	if( iPort == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Snd_Connect(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_OPEN, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Save port number          
	//===============================
	DWORD	iSize = 4;
	if( SRL_Reg_SetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT, (LPCTSTR)&iPort,(DWORD)iSize ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, 
						TEXT("%s: SRL_Reg_SetInfoDWORD %s %s DPERR_GENERIC return\n"),
						DBG_NAME_OPEN, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}

	LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_SetInfoDWORD Success Set PortNo = %d \n"),
								DBG_NAME_OPEN,  iPort);
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_OPEN );
	return DP_OK;
}

/*==========================================================================
 *
 *  LP_Close
 *
 *  SPDATA_CLOSE
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *
 *=========================================================================*/
HRESULT WINAPI LP_Close(LPSPDATA_CLOSE lpClose)
{
	int		iPort;
	char	cServerIP[64];
	int		iRtn;
	int		iSize = 4;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_CLOSE );

	//===============================
	//  Get server data 		         
	//===============================
	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_CLOSE, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfoDWORD(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_CLOSE, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}

	//===============================
	//  Send free request           
	//===============================
	iPort = SRL_Snd_Disconnect( cServerIP, iPort );
	if( iPort == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Snd_ Disconnect DPERR_GENERIC return\n"),
								DBG_NAME_CLOSE, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_CLOSE );
	return DP_OK;
}

/*==========================================================================
 *
 *  LP_StartSession (Start session)
 *
 *  SPDATA_STARTSESSION
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwFlags;		// Flags
 *	 DWORD			dwGroupID;		// ID of the group who's session to start
 *
 *=========================================================================*/
HRESULT WINAPI LP_StartSession(LPSPDATA_STARTSESSION lpStartSession)
{
	HRESULT	hResult = DP_OK;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_STARTSESSION );

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_STARTSESSION);

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_STARTSESSION );

	return DPERR_UNSUPPORTED;		// unsuported function
}

/*==========================================================================
 *
 *  LP_EnumSessions (Get lobby sessions list)
 *
 *  SPDATA_ENUMSESSIONS
 *	 DWORD				dwSize;		// Size of this structure
 *	 LPDPLOBBYSP		lpISP;		// Pointer to an IDPLobbySP interface
 *	 LPDPSESSIONDESC2	lpsd;		// SessionDesc to enumerate on (defined dplay.h)
 *	 DWORD              dwTimeout;	// Timeout value
 *	 DWORD              dwFlags;	// Flags
 *
 *  DPSESSIONDESC2
 *   DWORD   dwSize;             // Size of structure
 *   DWORD   dwFlags;            // DPSESSION_xxx flags
 *   GUID    guidInstance;       // ID for the session instance
 *   GUID    guidApplication;    // GUID of the DirectPlay application.
 *                               // GUID_NULL for all applications.
 *   DWORD   dwMaxPlayers;       // Maximum # players allowed in session
 *   DWORD   dwCurrentPlayers;   // Current # players in session (read only)
 *   union
 *   {                           // Name of the session
 *       LPWSTR  lpszSessionName;    // Unicode
 *       LPSTR   lpszSessionNameA;   // ANSI
 *   };
 *   union
 *   {                           // Password of the session (optional)
 *       LPWSTR  lpszPassword;       // Unicode
 *       LPSTR   lpszPasswordA;      // ANSI
 *   };
 *   DWORD   dwReserved1;        // Reserved for future MS use.
 *   DWORD   dwReserved2;
 *   DWORD   dwUser1;            // For use by the application
 *   DWORD   dwUser2;
 *   DWORD   dwUser3;
 *   DWORD   dwUser4;
 *
 *=========================================================================*/
HRESULT WINAPI LP_EnumSessions(LPSPDATA_ENUMSESSIONS lpEnumSession)
{
	HRESULT							hResult;
	LPSPDATA_ENUMSESSIONSRESPONSE	lpEnumSessionResponse;
	LPDPSESSIONDESC2				lpSessionDesc2;
	char							cEnumSessionResponse[sizeof(SPDATA_ENUMSESSIONSRESPONSE)];
	char							cSessionDesc2[sizeof(DPSESSIONDESC2)];
	char							cSessionName[SRS_MAX_NAME_CLIENT];
	char							cPassword[SRS_MAX_PASSWORD];

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_ENUMSESSIONS );
//	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_ENUMSESSIONS);

	//==============================
	// Set session data
	//==============================
	memset( cSessionDesc2, 0, sizeof(DPSESSIONDESC2));
	memset( cSessionName, 0, SRS_MAX_NAME_CLIENT );
	memset( cPassword, 0, SRS_MAX_PASSWORD );

	lpSessionDesc2 = (LPDPSESSIONDESC2)cSessionDesc2;
	lpSessionDesc2->dwSize = sizeof(DPSESSIONDESC2);
	lpSessionDesc2->dwFlags = DPSESSION_CLIENTSERVER;
	lpSessionDesc2->guidInstance = lpEnumSession->lpsd->guidInstance;
	lpSessionDesc2->guidApplication = lpEnumSession->lpsd->guidApplication;
	lpSessionDesc2->dwMaxPlayers = 4;
	lpSessionDesc2->dwCurrentPlayers = 0;
	lpSessionDesc2->lpszSessionNameA = cSessionName;
	lpSessionDesc2->lpszPasswordA = cPassword;
	memcpy( cSessionName, "LobbyServer", 11 );

	//
	// notice session responce
	//
	lpEnumSessionResponse = (LPSPDATA_ENUMSESSIONSRESPONSE)cEnumSessionResponse;
	lpEnumSessionResponse->dwSize = sizeof(SPDATA_ENUMSESSIONSRESPONSE);
	lpEnumSessionResponse->lpsd = lpSessionDesc2;
	hResult = lpEnumSession->lpISP->EnumSessionsResponse( lpEnumSessionResponse );
	if( hResult != DP_OK )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, 
						TEXT("%s:EnumSessionsResponse error %08x\n" ),
						DBG_NAME_ENUMSESSIONS,hResult );
	}
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n" ),DBG_NAME_ENUMSESSIONS );
//	return DPERR_UNSUPPORTED;		// unsuported function
	return DP_OK;
}

/*==========================================================================
 *
 *  LP_GetCaps
 *
 *  SPDATA_GETCAPS
 *   DWORD			dwSize;			// Size of this structure
 * 	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwFlags;		// Flags
 *	 LPDPCAPS		lpcaps;			// Pointer to DPCAPS structure (defined dplay.h)
 *
 *=========================================================================*/
HRESULT WINAPI LP_GetCaps(LPSPDATA_GETCAPS pd)
{
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n" ),DBG_NAME_GETCAPS );

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_GETCAPS);

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n" ),DBG_NAME_GETCAPS );
	return DPERR_UNSUPPORTED;
}
