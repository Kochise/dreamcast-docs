/*==========================================================================
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       LSPplayer.cpp
 *
 *	Content:	Code file for player-oriented LOBBY-SP callback functions
 *
 *  Functions:  LP_CreatePlayer
 *              LP_DestroyPlayer
 *				LP_GetPlayerCaps
 *				LP_GetPlayerData
 *				LP_SetPlayerData
 *				LP_SetPlayerName
 *				LP_Send
 *				LP_SendChatMessage
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
#include "LSPlobby.h"

// include of original functions 
#include "SRScom.h"
#include "SRLregistry.h"
#include "SRLmanage.h"
#include "SRLsend.h"

LPLSP_PLAYERDATA lpPlayerData = 0;	// used GetPlayerData
char	*lpPlayerArea = 0;			// used GetPlayerData
/*==========================================================================
 *
 *  LP_CreatePlayer （player Reg）
 *
 *  SPDATA_CREATEPLAYER 
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwPlayerID;		// ID of the group (output parameter)
 *	 LPDPNAME		lpName;			// Pointer to DPNAME struct for group name
 *	 LPVOID			lpData;			// Pointer to group data
 *	 DWORD			dwDataSize;		// Size of the group data 
 *	 DWORD			dwFlags;		// CreateGroup flags
 *
 *  DPNAME
 *   DWORD   dwSize;             // Size of structure
 *   DWORD   dwFlags;            // Not used. Must be zero.
 *   union
 *   {                           // The short or friendly name
 *       LPWSTR  lpszShortName;  // Unicode
 *       LPSTR   lpszShortNameA; // ANSI
 *   };
 *   union
 *   {                           // The long or formal name
 *       LPWSTR  lpszLongName;   // Unicode
 *       LPSTR   lpszLongNameA;  // ANSI
 *   };
 *=========================================================================*/
HRESULT WINAPI LP_CreatePlayer(LPSPDATA_CREATEPLAYER lpCreatePlayer)
{
	DWORD	dwSize;
	int		iPort;
	int		iSleep;
	char	cClientName[SRS_MAX_NAME_CLIENT];
	char	cUserName[SRS_MAX_NAME_USER];
	char	cWait[8];
	char	cServerIP[64];
	WORD	wPlayerID;
	DWORD	iSize = 4;
	int		iRtn;
	TCHAR	tcClientName[40];
	TCHAR	tcUserName[40];

	memset(tcClientName,NULL,sizeof(tcClientName));
	memset(tcUserName,NULL,sizeof(tcUserName));
	mbstowcs(tcUserName,lpCreatePlayer->lpName->lpszShortNameA,strlen(lpCreatePlayer->lpName->lpszShortNameA));
	mbstowcs(tcClientName,lpCreatePlayer->lpName->lpszLongNameA,strlen(lpCreatePlayer->lpName->lpszLongNameA));

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry Short PlayerName=%s Long=%s \n"),DBG_NAME_CREATEPLAYER,
		tcClientName,tcUserName);

//============================================================
//  Connect lobby server
//============================================================
	//===============================
	//  Get server data 		         
	//===============================

	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfoBinary(%s %s)DPERR_GENERIC return\n"),
										DBG_NAME_CREATEPLAYER, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}


	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, LSP_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
										DBG_NAME_CREATEPLAYER, SRL_REG_KEY_COM, LSP_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Get information of user's reg           
	//===============================
	//=======================================
	//  Get client name from registry 		         
	//=======================================
	memset( cClientName, 0, SRS_MAX_NAME_CLIENT );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, LSP_REG_CLIENT, (LPCTSTR)cClientName ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
										DBG_NAME_CREATEPLAYER, SRL_REG_KEY_COM, LSP_REG_CLIENT );
		return DPERR_GENERIC;
	}
//	dwSize = strlen(lpCreatePlayer->lpName->lpszLongNameA);
//	if( dwSize == 0)
//	{
//
//		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("????? %s: cClientName NULL ERROR\n"),
//			DBG_NAME_CREATEPLAYER);
//		return DPERR_GENERIC;
//	}
	dwSize = strlen(cClientName);
	if( dwSize > SRS_MAX_NAME_CLIENT)
		dwSize = SRS_MAX_NAME_CLIENT;	
//	memcpy( cClientName, lpCreatePlayer->lpName->lpszLongNameA, dwSize );

	LSP_Dbg_Printf( DBG_LEVEL_2, TEXT("%s:SRL_Reg_SetInfo Start\n"),
		DBG_NAME_CREATEPLAYER);

	if( SRL_Reg_SetInfo( SRL_REG_KEY_COM, SRL_REG_CLIENT, (LPCTSTR)cClientName ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_SetInfo(%s %s)DPERR_GENERIC return\n"),
										DBG_NAME_CREATEPLAYER, SRL_REG_KEY_COM, SRL_REG_CLIENT );
		return DPERR_GENERIC;
	}
	LSP_Dbg_Printf( DBG_LEVEL_2, TEXT("%s:SRL_Reg_SetInfo Finished\n"),
		DBG_NAME_CREATEPLAYER);

	dwSize = strlen(lpCreatePlayer->lpName->lpszShortNameA);
//	dwSize = wcslen(lpCreatePlayer->lpName->lpszShortName);
//	dwSize = lpCreatePlayer->lpName->dwSize - 8;
	if( dwSize == 0)
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("????? %s: cUserName NULL ERROR\n"),
			DBG_NAME_CREATEPLAYER);
		return DPERR_GENERIC;
	}
	if( dwSize > SRS_MAX_NAME_USER )
		dwSize = SRS_MAX_NAME_USER;
	memset( cUserName, 0, SRS_MAX_NAME_USER );
	memcpy( cUserName, lpCreatePlayer->lpName->lpszShortNameA, dwSize );

	if( SRL_Reg_SetInfo( SRL_REG_KEY_COM, SRL_REG_USER, (LPCTSTR)cUserName ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_SetInfo(%s %s)DPERR_GENERIC return\n"),
										DBG_NAME_CREATEPLAYER, SRL_REG_KEY_COM, SRL_REG_USER );
		return DPERR_GENERIC;
	}
	//===============================
	//  Send request  		             
	//===============================

	if( SRL_Snd_UserEntry( cServerIP, iPort, (LPCTSTR)cClientName, (LPCTSTR)cUserName ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_UserEntry DPERR_GENERIC return\n"),
															DBG_NAME_CREATEPLAYER );
		return DPERR_GENERIC;
	}

	//===============================
	//  Wait to receive response
	//===============================

	if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_USERENTRY, (LPCTSTR)SRL_REG_WAIT_ON ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Reg_SetInfo %s %s DPERR_GENERIC return\n"),
									DBG_NAME_CREATEPLAYER, SRL_REG_KEY_WAIT, SRL_REG_USERENTRY );
		return DPERR_GENERIC;
	}

    // Wait receive (except timeover)
	for( iSleep = 0 ; iSleep < SRS_ANSER_WAIT_TIMER ; ) 
	{
		memset( cWait, 0, sizeof(cWait) );
 
		if( SRL_Reg_GetInfo( SRL_REG_KEY_WAIT, SRL_REG_USERENTRY, (LPCTSTR)cWait ) == -1 )
		{
			LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_CREATEPLAYER, SRL_REG_KEY_WAIT, SRL_REG_USERENTRY);
			return DPERR_GENERIC;
		}


		if( memcmp( cWait, SRL_REG_WAIT_OK, sizeof(SRL_REG_WAIT_OK) ) == 0 ) 
//		if( memcmp( cWait, SRL_REG_WAIT_OFF, sizeof(SRL_REG_WAIT_OK) ) == 0 )
		{
			//============================
			//  succeed user's reg
			//============================

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_USERENTRY, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_CREATEPLAYER, SRL_REG_KEY_WAIT, SRL_REG_USERENTRY );
				return DPERR_GENERIC;
			}

			if( SRL_Reg_SetInfo(SRL_REG_KEY_COM,SRL_REG_USER,(LPCTSTR)cUserName) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_SetInfo %s %s %s DPERR_GENERIC return\n"),
								DBG_NAME_CREATEPLAYER,SRL_REG_KEY_COM,SRL_REG_USER,cUserName);
				return DPERR_GENERIC;
			}
			// Set Player ID
			wPlayerID = SRL_Mng_GetUserByName(cUserName);
			if (wPlayerID == (WORD)-1)
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("????? %s: SRL_Mng_GetUserByName Error user=%s return\n"),
								DBG_NAME_CREATEPLAYER, cUserName);
				return DPERR_GENERIC;
			}
			lpCreatePlayer->dwPlayerID = wPlayerID;
			LSP_Dbg_Printf( DBG_LEVEL_1,
							TEXT("%s: DP_OK playerID=%d return\n"),
							DBG_NAME_CREATEPLAYER,lpCreatePlayer->dwPlayerID);
			return DP_OK;
		}
		if( memcmp( cWait, SRL_REG_WAIT_OFF, sizeof(SRL_REG_WAIT_NG) ) == 0 )
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_USERENTRY, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_CREATEPLAYER, SRL_REG_KEY_WAIT, SRL_REG_USERENTRY );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: Error Anser DPERR_GENERIC return\n"),
							DBG_NAME_CREATEPLAYER );
			return DPERR_GENERIC;
		}
		Sleep( 500 );
		iSleep = iSleep + 500;
	}
	//

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: anser timeover %d ms DPERR_TIMEOUT return\n"),
								DBG_NAME_CREATEPLAYER, SRS_ANSER_WAIT_TIMER );
	return DPERR_TIMEOUT;
}

/*==========================================================================
 *
 *  LP_DestroyPlayer （Delete player）
 *
 *  SPDATA_DESTROYPLAYER
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwPlayerID;		// ID of the player on the lobby
 *
 *=========================================================================*/
HRESULT WINAPI LP_DestroyPlayer( LPSPDATA_DESTROYPLAYER lpDestroyPlayer )
{
	int		iPort;
	int		iSleep;
	WORD	wUserID;
	char	cWait[8];
	char	cServerIP[64];
	int		iSize = 4;
	int		iRtn;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_DESTROYPLAYER );

//============================================================
//  lobby server
//============================================================
	//===============================
	//  Get server data 		         
	//===============================

	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfoBinary(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_DESTROYPLAYER, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}


	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_DESTROYPLAYER, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Get information to delete user 
	//===============================
	// User ID (Player ID)
	wUserID = (WORD)lpDestroyPlayer->dwPlayerID;
	LSP_Dbg_Printf( DBG_LEVEL_2, TEXT("%s: DestoryPlayerID=%d\n"),
												DBG_NAME_DESTROYPLAYER,wUserID );
	//===============================
	//  Send request  		             
	//===============================
	if( SRL_Snd_UserDelete( cServerIP, iPort, wUserID ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_UserDelete DPERR_GENERIC return\n"),
															DBG_NAME_DESTROYPLAYER );
		return DPERR_GENERIC;
	}

	LSP_Dbg_Printf( DBG_LEVEL_2, TEXT("\n\n####### %s: SRL_Snd_UserDelete Success DestoryPlayerID=%d\n\n"),
												DBG_NAME_DESTROYPLAYER,wUserID );
	//===============================
	//  Wait to receive response
	//===============================

	if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_USERDELETE, (LPCTSTR)SRL_REG_WAIT_ON ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Reg_SetInfo %s %s DPERR_GENERIC return\n"),
									DBG_NAME_CREATEPLAYER, SRL_REG_KEY_WAIT, SRL_REG_USERDELETE );
		return DPERR_GENERIC;
	}

    // Wait response (Except Timeover)
	for( iSleep = 0 ; iSleep < SRS_ANSER_WAIT_TIMER ; )
	{
		memset( cWait, 0, sizeof(cWait) );
		if( SRL_Reg_GetInfo( SRL_REG_KEY_WAIT, SRL_REG_USERDELETE, (LPCTSTR)cWait ) == -1 )
		{
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
									DBG_NAME_DESTROYPLAYER,SRL_REG_KEY_WAIT, SRL_REG_USERDELETE );
			return DPERR_GENERIC;
		}

		if( memcmp( cWait, SRL_REG_WAIT_OK, sizeof(SRL_REG_WAIT_OK) ) == 0 )
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_USERDELETE, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_DESTROYPLAYER, SRL_REG_KEY_WAIT, SRL_REG_USERDELETE );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: DP_OK return\n"),DBG_NAME_DESTROYPLAYER );
			return DP_OK;
		}
		if( memcmp( cWait, SRL_REG_WAIT_OFF, sizeof(SRL_REG_WAIT_NG) ) == 0 )
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_USERDELETE, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_DESTROYPLAYER, SRL_REG_KEY_WAIT, SRL_REG_USERDELETE );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_0,
							TEXT("%s: Error Anser DPERR_GENERIC return\n"),DBG_NAME_DESTROYPLAYER );
			return DPERR_GENERIC;
		}
		Sleep( 500 );
		iSleep = iSleep + 500;
	}
	//

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: anser timeover %d ms DPERR_TIMEOUT return\n"),
								DBG_NAME_CREATEPLAYER, SRS_ANSER_WAIT_TIMER );
	return DPERR_TIMEOUT;
}

/*==========================================================================
 *
 *  LP_GetPlayerCaps (Get player ability)
 *
 *  SPDATA_GETPLAYERCAPS
 *	 DWORD			dwSize;			// Size of this structure
 *   LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwFlags;		// Flags
 *	 DWORD			dwPlayerID;		// ID of the Player
 *	 LPDPCAPS		lpcaps;			// Pointer to DPCAPS structure
 *
 *=========================================================================*/
HRESULT WINAPI LP_GetPlayerCaps(LPSPDATA_GETPLAYERCAPS lpGetPlayerCaps)
{

	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("%s entry\n"),DBG_NAME_GETPLAYERCAPS );

	LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: unsuported callback function\n"),DBG_NAME_GETPLAYERCAPS);

	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("%s return\n"),DBG_NAME_GETPLAYERCAPS );

	return DPERR_UNSUPPORTED;	
}

/*==========================================================================
 *
 *  LP_GetPlayerData (Get player data)
 *
 *  SPDATA_GETPLAYERDATA
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwPlayerID;		// ID of the Player
 *	 LPDWORD		lpdwDataSize;	// Pointer to the size of the lpData buffer
 *	 LPVOID			lpData;			// Pointer to a data buffer
 *
 *=========================================================================*/
HRESULT WINAPI LP_GetPlayerData(LPSPDATA_GETPLAYERDATA lpGetPlayerData)
{
   	int				iRtn;
	int				iPort;
	int				iSleep;
	int				iSize = 4;
	int				iListSize;
	size_t			szSendSize;
	WORD			wMaxUser;
	DWORD			dwAreaSize;
	LPSRS_INFOUSER	lpUserInfo;
	LPSRS_IFFIX 	lpIfFix;
	LPSRL_REGINFO	lpRegInfo;
	char			cRegInfo[SRL_REG_INFO_SZ];
	char			cWait[8];
	char			cServerIP[64];
	char			cIfFix[256];


	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: entry\n"),DBG_NAME_GETPLAYERDATA );

	if( lpPlayerData != 0 )		
	{
		realloc( lpPlayerData, 0 );
		lpPlayerData = 0;
	}
//============================================================
//  lobby server
//============================================================
	//===============================
	//  Get server data 		         
	//===============================
	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM,SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfoBinary(%s %s)DPERR_GENERIC return\n"),
						DBG_NAME_GETPLAYERDATA,SRL_REG_KEY_COM,SRL_REG_PORT);
		return DPERR_GENERIC;
	}

	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_GETPLAYERDATA, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}
	//==========================
	//  Send to reruest of all reference information
	//==========================
	memset( cIfFix, 0, 256 );
	lpIfFix = (LPSRS_IFFIX)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_ALL;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = 0;
	lpIfFix->IF_iPortNo = iPort;

	szSendSize = (size_t)SRS_IF_FIX_SZ;
	if( SRL_Snd_Request( cServerIP, iPort, cIfFix, szSendSize ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_Request DPERR_GENERIC return\n"),
															DBG_NAME_GETPLAYERDATA );
		return DPERR_GENERIC;
	}

	//===============================
	//  Wait to receive response
	//===============================

	if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_ALLGET, (LPCTSTR)SRL_REG_WAIT_ON ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Reg_SetInfo %s %s DPERR_GENERIC return\n"),
									DBG_NAME_GETPLAYERDATA, SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
		return DPERR_GENERIC;
	}

    // Wait receive (except timeover)
	for( iSleep = 0 ; iSleep < SRS_ANSER_WAIT_TIMER ; )
	{
		memset( cWait, 0, sizeof(cWait) );
		if( SRL_Reg_GetInfo( SRL_REG_KEY_WAIT, SRL_REG_ALLGET, (LPCTSTR)cWait ) == -1 )
		{
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
									DBG_NAME_GETPLAYERDATA,SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
			return DPERR_GENERIC;
		}

		if( memcmp( cWait, SRL_REG_WAIT_OK, sizeof(SRL_REG_WAIT_OK) ) == 0 ) 
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_ALLGET, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_GETPLAYERDATA, SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
				return DPERR_GENERIC;
			}
			//==================================
			//  Get renewal result
			//==================================
			memset( cRegInfo, 0, SRL_REG_INFO_SZ );
			lpRegInfo = (LPSRL_REGINFO)cRegInfo;
			if( SRL_Reg_GetComInfo( lpRegInfo ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetComInfo DPERR_GENERIC return\n"),
								DBG_NAME_GETPLAYERDATA );
				return DPERR_GENERIC;
			}
			wMaxUser = lpRegInfo->wMaxUser;
			dwAreaSize = SRS_USER_ITEM_SZ * wMaxUser + SRS_INFO_USER_COM_SZ;
			lpUserInfo = (LPSRS_INFOUSER)malloc( dwAreaSize );
			if( lpUserInfo == NULL )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: malloc error USERITEM DPERR_OUTOFMEMORY return\n"),
								DBG_NAME_GETPLAYERDATA );
				return DPERR_OUTOFMEMORY;
			}
			lpPlayerArea = (char *)lpUserInfo;
			memset( lpPlayerArea, 0, dwAreaSize );
			if( SRL_Mng_AllGet( (char *)lpUserInfo, 0, 0, 0 ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Mng_AllGet error User DPERR_GENERIC return\n"),
																	DBG_NAME_GETPLAYERDATA );
				realloc( lpPlayerArea, 0 );
				lpPlayerArea = 0;
				return DPERR_GENERIC;
			}
			iListSize = sizeof(LSP_PLAYERDATA) + lpUserInfo->US_wEntryUser * SRS_USER_ITEM_SZ;

			*lpGetPlayerData->lpdwDataSize = iListSize;

			if (lpGetPlayerData->lpData == NULL)
			{
				LSP_Dbg_Printf( DBG_LEVEL_1, 
						TEXT("%s: Get Size = %d \n"),
          							DBG_NAME_GETPLAYERDATA,iListSize);
				realloc( lpPlayerArea, 0 );
				lpPlayerArea = 0;
				return DPERR_BUFFERTOOSMALL;
			}

			lpPlayerData = (LPLSP_PLAYERDATA)lpGetPlayerData->lpData; 
			memset( lpPlayerData, 0, iListSize );
			iRtn = LSP_MK_PlayerList( lpUserInfo, lpPlayerData, lpGetPlayerData->dwPlayerID );


			lpGetPlayerData->lpData = (void *)lpPlayerData;

			LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: DP_OK return\n"),DBG_NAME_GETPLAYERDATA );
			return DP_OK;
		}
		//============================
		//  Fail to all reference information
		//============================
		if( memcmp( cWait, SRL_REG_WAIT_OFF, sizeof(SRL_REG_WAIT_NG) ) == 0 ) 
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_ALLGET, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_GETPLAYERDATA, SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_0,
							TEXT("%s: Error Anser DPERR_GENERIC return\n"),
							DBG_NAME_GETPLAYERDATA );
			return DPERR_GENERIC;
		}
		Sleep( 500 );
		iSleep = iSleep + 500;
	}
	//
	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: anser timeover %d ms DPERR_TIMEOUT return\n"),
								DBG_NAME_GETPLAYERDATA, SRS_ANSER_WAIT_TIMER );
	return DPERR_TIMEOUT;
}

/*==========================================================================
 *
 *  LP_SetPlayerData (Set player data)
 *
 *  SPDATA_SETPLAYERDATA
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwPlayerID;		// ID of the player
 *	 LPVOID			lpData;			// Pointer to the new player data
 *	 DWORD			dwDataSize;		// Size of lpData
 *	 DWORD			dwFlags;		// Flags
 *
 *=========================================================================*/
HRESULT WINAPI LP_SetPlayerData(LPSPDATA_SETPLAYERDATA lpSetPlayerData)
{
	DWORD	dwAreaSize;
	WORD	wUserID;
	int		iPort;
	char	cServerIP[64];
	char	cSaveInfo[SRS_MAX_USERAREA];
	int		iSize = 4;
	int		iRtn;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: entry\n"),DBG_NAME_SETPLAYERDATA );

//============================================================
//  lobby server
//============================================================
	//===============================
	//  Get server data 		         
	//===============================

	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfoDWORD(%s %s)DPERR_GENERIC return\n"),
										DBG_NAME_SETPLAYERDATA, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}

	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
									DBG_NAME_SETPLAYERDATA, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Set user saving data           
	//===============================
	memset( cSaveInfo, 0, SRS_MAX_USERAREA );
	dwAreaSize = lpSetPlayerData->dwDataSize;
	if( dwAreaSize > SRS_MAX_USERAREA )
	{
		dwAreaSize = SRS_MAX_USERAREA;
	}
	memcpy( cSaveInfo, (char *)lpSetPlayerData->lpData, dwAreaSize );
	wUserID = (WORD)lpSetPlayerData->dwPlayerID;

	//===============================
	//  Send request 
	//===============================
	if( SRL_Snd_SaveInfo( cServerIP, iPort, wUserID, (LPCTSTR)cSaveInfo ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_SaveInfo DPERR_GENERIC return\n"),
																	DBG_NAME_SETPLAYERDATA );
		return DPERR_GENERIC;
	}

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: return\n"),DBG_NAME_SETPLAYERDATA );
	return DP_OK;
}

/*==========================================================================
 *
 *  LP_SetPlayerName (Set player name)
 *
 *  SPDATA_SETPLAYERNAME
 *	 DWORD			dwSize;			// Size of this structure 
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwPlayerID;		// ID of the player
 *	 LPDPNAME		lpName;			// Pointer to the new DPNAME struct
 *	 DWORD			dwFlags;		// Flags
 *
 *=========================================================================*/
HRESULT WINAPI LP_SetPlayerName(LPSPDATA_SETPLAYERNAME lpSetPlayerName)
{
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("%s: entry\n"),DBG_NAME_SETPLAYERNAME );

	LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: unsuported callback function\n"),DBG_NAME_SETPLAYERNAME);

	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("%s: return\n"),DBG_NAME_SETPLAYERNAME );

	return DPERR_UNSUPPORTED;		// unsuported function
}

/*==========================================================================
 *
 *  LP_Send (send application message) 
 *
 *  SPDATA_SEND
 * 	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwFromID;		// ID of the player from
 *	 DWORD			dwToID;			// ID of the player to
 *	 DWORD			dwFlags;		// Flags
 *	 LPVOID			lpBuffer;		// Message buffer
 *	 DWORD			dwBufSize;		// Size of the message buffer
 * 
 *  NOTE : dwToID (range of send to) 
 *           PlayerID        	      : send to Player
 *           DPID_ALLPLAYERS(value=0) : send to All Players in Group
 *           DPID_SERVERALLPLAYER(value=1) : send to All Players in Server
 *
 *=========================================================================*/
HRESULT WINAPI LP_Send(LPSPDATA_SEND lpSend)
{
	WORD	wUserID;
	WORD	wMsgCode;
	DWORD	dwBufSize;
	int		iPort;
	char	cServerIP[64];
	char	cMessage[SRS_MAX_MESSAGE];
	int		iSize = 4;
	int		iRtn;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: entry\n"),DBG_NAME_SEND );

//============================================================
//  lobby server
//============================================================
	//===============================
	//  Get server data 		         
	//===============================

	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfoDWORD(%s %s)DPERR_GENERIC return\n"),
										DBG_NAME_SEND, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}


	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
									DBG_NAME_SEND, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Send and Set message 
	//===============================
	memset( cMessage, 0, SRS_MAX_MESSAGE );
	dwBufSize = lpSend->dwBufSize;
	if( dwBufSize > SRS_MAX_MESSAGE )
	{
		dwBufSize = SRS_MAX_MESSAGE;	
	}
	memcpy( cMessage, (char *)lpSend->lpBuffer, dwBufSize );
	wUserID = (WORD)lpSend->dwFromID;
	wMsgCode = (WORD)lpSend->dwToID;

	//===============================
	//  Send request  		             
	//===============================
	if( SRL_Snd_Message( cServerIP, iPort, wUserID, wMsgCode, (LPCTSTR)cMessage ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_Message DPERR_GENERIC return\n"),
																		DBG_NAME_SEND );
		return DPERR_GENERIC;
	}

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: return\n"),DBG_NAME_SEND );
	return DP_OK;
}

/*==========================================================================
 *
 *  LP_SendChatMessage (Send chat message)
 *
 *  SPDATA_CHATMESSAGE
 *   DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwFromID;		// ID of the player from
 *	 DWORD			dwToID;			// ID of the player to
 *	 DWORD			dwFlags;		// Send Flags
 *	 LPDPCHAT		lpChat;			// Pointer to a DPCHAT structure
 *
 *  DPCHAT
 *   DWORD               dwSize;
 *   DWORD               dwFlags;
 *   union
 *   {                          // Message string
 *       LPWSTR  lpszMessage;   // Unicode
 *       LPSTR   lpszMessageA;  // ANSI
 *   };
 *
 *  NOTE : dwToID (range of send to) 
 *           PlayerID        	      : send to Player
 *           GroupID         		  : send to All Players in Group
 *           DPID_ALLPLAYERS(value=0) : send to All Players in Session(Lobby)
 *
 *=========================================================================*/
HRESULT WINAPI LP_SendChatMessage(LPSPDATA_CHATMESSAGE lpSendChatMessage)
{
	WORD						wUserID;
	WORD						wMsgCode;
	DWORD						dwSize;
	int							iPort;
	char						cServerIP[64];
	char						cMessage[SRS_MAX_MESSAGE];
	int							iSize = 4;
	int							iRtn;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: entry\n"),DBG_NAME_SENDCHATMESSAGE );

//============================================================
//
//  Lobby Server
//
//============================================================
	//===============================
	//  Get server data 		         
	//===============================

	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfoDWORD(%s %s)DPERR_GENERIC return\n"),
										DBG_NAME_SENDCHATMESSAGE, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}

	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
									DBG_NAME_SENDCHATMESSAGE, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Send and set message 
	//===============================
	memset( cMessage, 0, SRS_MAX_MESSAGE );
	dwSize = lpSendChatMessage->lpChat->dwSize;
	if( dwSize > SRS_MAX_MESSAGE )
	{
		dwSize = SRS_MAX_MESSAGE;	
	}
	memcpy( cMessage, (char *)lpSendChatMessage->lpChat->lpszMessage, dwSize );
	wUserID = (WORD)lpSendChatMessage->dwFromID;
	wMsgCode = (WORD)lpSendChatMessage->dwToID;

	//===============================
	//  Send request		             
	//===============================
	if( SRL_Snd_Message( cServerIP, iPort, wUserID, wMsgCode, (LPCTSTR)cMessage ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_Message DPERR_GENERIC return\n"),
                                                                      DBG_NAME_SENDCHATMESSAGE );
		return DPERR_GENERIC;
	}

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return"),DBG_NAME_SENDCHATMESSAGE );
	return DP_OK;
}