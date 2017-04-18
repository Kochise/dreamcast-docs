/*==========================================================================
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       LSPplayer.cpp
 *
 *	Content:	Code file for group-oriented LOBBY-SP callback functions
 *
 *  Functions:  LP_AddGroupToGroup
 *				LP_AddPlayerToGroup
 *				LP_BuildParentalHeirarchy
 *				LP_CreateGroup
 *				LP_CreateGroupInGroup
 *				LP_DeleteGroupFromGroup
 *				LP_DeletePlayerFromGroup
 *				LP_DestroyGroup
 *				LP_GetGroupConnectionSettings
 *				LP_GetGroupData
 *				LP_SetGroupConnectionSettings
 *				LP_SetGroupData
 *				LP_SetGroupName
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

LPLSP_GROUPDATA lpGroupData = 0;	// used GetGroupData
char	*lpGroupArea = 0;			// used GetGroupData
/*==========================================================================
 *
 *  LP_AddGroupToGroup （Add group shortcut）
 *
 *  SPDATA_ADDGROUPTOGROUP
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwParentID;		// ID of the parent group
 *	 DWORD			dwGroupID;		// ID of the new group to be created (output param)
 *
 *=========================================================================*/
HRESULT WINAPI LP_AddGroupToGroup(LPSPDATA_ADDGROUPTOGROUP lpAddGroupToGroup)
{
	HRESULT	hResult = DP_OK;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: entry\n"),DBG_NAME_ADDGROUPTOGROUP);

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_ADDGROUPTOGROUP);
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: return\n"),DBG_NAME_ADDGROUPTOGROUP);

	return DPERR_UNSUPPORTED;		// unsuported function
}

/*==========================================================================
 *
 *  LP_AddPlayerToGroup （entry group）
 *
 *  SPDATA_ADDPLAYERTOGROUP
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwGroupID;		// ID of the group
 *	 DWORD			dwPlayerID;		// ID of the player
 *
 *=========================================================================*/
HRESULT WINAPI LP_AddPlayerToGroup(LPSPDATA_ADDPLAYERTOGROUP lpAddPlayerToGroup)
{
	WORD		wUserID;
	WORD		wGroupID;
	WORD		wCondetion;
	int			iSleep;
	int			iPort;
	char		cWait[8];
	char		cServerIP[64];
	int			iSize = 4;
	int			iRtn;
	int			i;
	LPSRS_GROUPITEM lpGroupInfo;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: entry\n"),DBG_NAME_ADDPLAYERTOGROUP);

	//===============================
	// Get server data 		         
	//===============================
	// port number
	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfoDWORD(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_ADDPLAYERTOGROUP, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}

	// Server IP
	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_ADDPLAYERTOGROUP, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	wUserID = (WORD)lpAddPlayerToGroup->dwPlayerID;
	wGroupID = (WORD)lpAddPlayerToGroup->dwGroupID & LSP_SLIPMASK_GROUP;
	lpGroupInfo = (LPSRS_GROUPITEM)malloc(SRS_GROUP_ITEM_SZ);
	if (lpGroupInfo == NULL)
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: get memory for GROUP INFO(GID=0x%X) DPERR_OUTOFMEMORY return\n"),
								DBG_NAME_ADDPLAYERTOGROUP, wGroupID);
		return DPERR_OUTOFMEMORY;
	}
	if (SRL_Mng_GetGroupByID(wGroupID, (char *)lpGroupInfo) == 0)
	{		// Get success
		for (i = 0;i < lpGroupInfo->GPI_wEntryUser; i++)
		{
			 if (lpGroupInfo->GPI_wUserID[i] == wUserID)
			 {
				LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("%s: The Player(0x%X) already paticipated in the Group(0x%X) return\n"),
								DBG_NAME_ADDPLAYERTOGROUP, wUserID, wGroupID);
				realloc(lpGroupInfo,0);
				return DP_OK;
			 }
		}
	}
	realloc(lpGroupInfo,0);

	wCondetion = (WORD)SRS_GAME_PLAY;				// entry game

	//===============================
	//  Send request to entry for group           
	//===============================
	if( SRL_Snd_GroupJoin( cServerIP, iPort, wUserID, wGroupID, wCondetion ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_GroupJoin DPERR_GENERIC return\n"),
															DBG_NAME_ADDPLAYERTOGROUP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Wait to request response
	//===============================
	if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN, (LPCTSTR)SRL_REG_WAIT_ON ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Reg_SetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_ADDPLAYERTOGROUP, SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN );
		return DPERR_GENERIC;
	}

    // Wait response（except timeover）
	for( iSleep = 0 ; iSleep < SRS_ANSER_WAIT_TIMER ; )
	{
		memset( cWait, 0, sizeof(cWait) );
		if( SRL_Reg_GetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN, (LPCTSTR)cWait ) == -1 )
		{
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_ADDPLAYERTOGROUP,SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN );
			return DPERR_GENERIC;
		}

		if( memcmp( cWait, SRL_REG_WAIT_OK, sizeof(SRL_REG_WAIT_OK) ) == 0 ) 
		{
			// Change status
			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_ADDPLAYERTOGROUP, SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: DP_OK return\n"),DBG_NAME_ADDPLAYERTOGROUP );
			return DP_OK;
		}
		if( memcmp( cWait, SRL_REG_WAIT_OFF, sizeof(SRL_REG_WAIT_NG) ) == 0 )
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_ADDPLAYERTOGROUP, SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: Error Anser DPERR_GENERIC return\n"),
							DBG_NAME_ADDPLAYERTOGROUP );
			return DPERR_GENERIC;
		}
		Sleep( 500 );
		iSleep = iSleep + 500;
	}
	//
	//  timeout to wait recieve response
	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: anser timeover %d ms DPERR_TIMEOUT return\n"),
								DBG_NAME_ADDPLAYERTOGROUP, SRS_ANSER_WAIT_TIMER );
	return DPERR_TIMEOUT;
}

/*==========================================================================
 *
 *  LP_BuildParentalHeirarchy
 *
 *  SPDATA_BUILDPARENTALHEIRARCHY
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwGroupID;		// ID of the group to build the heirarchy for
 *	 DWORD			dwMessage;		// Message type the lobby errored on
 *	 DWORD			dwParentID;		// ID of the parent (for an AddGroupToGroup call)
 *
 *=========================================================================*/
HRESULT WINAPI LP_BuildParentalHeirarchy(LPSPDATA_BUILDPARENTALHEIRARCHY lpBuildParentalHeirarchy)
{
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: entry\n"),DBG_NAME_BUILDPARENTALHEIRARCHY );

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_BUILDPARENTALHEIRARCHY);
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: return\n"),DBG_NAME_BUILDPARENTALHEIRARCHY );

	return DPERR_UNSUPPORTED;		// unsuported function
}

/*==========================================================================
 *
 *  LP_CreateGroup (Create group)
 *
 *
 *  SPDATA_CREATEGROUP
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwGroupID;		// ID of the group (output parameter)
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
 *
 *=========================================================================*/
HRESULT WINAPI LP_CreateGroup(LPSPDATA_CREATEGROUP lpCreateGroup)
{
	WORD	wUserID;
	WORD	wGroupID;
	DWORD	dwSize;
	int		iPort;
	int		iSleep;
	char	cWait[8];
	char	cServerIP[64];
	char	cUserName[SRS_MAX_NAME_USER];
	char	cGroupName[SRS_MAX_NAME_GROUP];	
	int		iSize = 4;
	int		iRtn;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: entry\n"),DBG_NAME_CREATEGROUP );

	if ((lpCreateGroup->lpName->lpszLongName == NULL) ||
	    (lpCreateGroup->lpName->lpszShortName == NULL))
	{
		lpCreateGroup->dwGroupID = 0;
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: Name=NULL SKIP\n"),DBG_NAME_CREATEGROUP );
		return DP_OK;
	}

	//===============================
	//  Get server data 		         
	//===============================
	// port number
	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfoDWORD(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_CREATEGROUP, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}

	// Server IP
	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_CREATEGROUP, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Set information to create group
	//===============================
	memset( cGroupName, 0, SRS_MAX_NAME_GROUP );
	dwSize = lpCreateGroup->lpName->dwSize - 8;
	if( dwSize > SRS_MAX_NAME_GROUP )
		dwSize = SRS_MAX_NAME_GROUP;
	memset( cGroupName, 0, SRS_MAX_NAME_GROUP );
	memcpy( cGroupName, lpCreateGroup->lpName->lpszLongName, dwSize );

	memset( cUserName , 0, SRS_MAX_NAME_USER );

	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM,SRL_REG_USER, (LPCTSTR)cUserName ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
						DBG_NAME_CREATEGROUP, SRL_REG_KEY_COM,SRL_REG_USER );
		return DPERR_GENERIC;
	}
	TCHAR	tcDebugData[40];
	memset(tcDebugData,NULL,sizeof(tcDebugData));
	mbstowcs(tcDebugData,cUserName,strlen(cUserName));
	LSP_Dbg_Printf( DBG_LEVEL_1,
						TEXT("%s: SRL_Reg_GetInfo UserName=%s \n"),
						DBG_NAME_CREATEGROUP, tcDebugData);
	// get user ID
	wUserID = SRL_Mng_GetUserByName( cUserName );
	if( wUserID == SRS_WORD_ERROR )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Mng_GetUserByName(%s) DPERR_GENERIC return\n"),
												DBG_NAME_CREATEGROUP, tcDebugData );
		return DPERR_GENERIC;
	}
	lpCreateGroup->dwGroupID = 0;

	//===============================
	//  Send request  		             
	//===============================
	if( SRL_Snd_GroupMake( cServerIP, iPort, wUserID, (LPCTSTR)cGroupName ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_GroupMake DPERR_GENERIC return\n"),
															DBG_NAME_CREATEGROUP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Wait to receive response
	//===============================

	if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE, (LPCTSTR)SRL_REG_WAIT_ON ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Reg_SetInfo %s %s DPERR_GENERIC return\n"),
									DBG_NAME_CREATEGROUP, SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE );
		return DPERR_GENERIC;
	}

    // Wait response (Except timeover)
	for( iSleep = 0 ; iSleep < SRS_ANSER_WAIT_TIMER ; )
	{
		memset( cWait, 0, sizeof(cWait) );
		if( SRL_Reg_GetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE, (LPCTSTR)cWait ) == -1 )
		{
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
									DBG_NAME_CREATEGROUP,SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE );
			return DPERR_GENERIC;
		}

		if( memcmp( cWait, SRL_REG_WAIT_OK, sizeof(SRL_REG_WAIT_OK) ) == 0 ) 
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_CREATEGROUP, SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE );
				return DPERR_GENERIC;
			}
			//===============================
			//  Reference Group ID
			//===============================
			wGroupID = SRL_Mng_GetGroupByName( cGroupName );
			if( wGroupID == SRS_WORD_ERROR )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Mng_GetGroupByName %s DPERR_GENERIC return\n"),
								DBG_NAME_CREATEGROUP, cGroupName );
				return DPERR_GENERIC;
			}
			lpCreateGroup->dwGroupID = (DWORD)wGroupID | LSP_MASK_GROUP;	

			LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: DP_OK GID=0x%X return\n"),DBG_NAME_CREATEGROUP,
				lpCreateGroup->dwGroupID );
			return DP_OK;
		}
		if( memcmp( cWait, SRL_REG_WAIT_OFF, sizeof(SRL_REG_WAIT_NG) ) == 0 ) 
		{
			// 状態変更
			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_CREATEGROUP, SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE );
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
 *  LP_CreateGroupInGroup （Create group into group）
 *
 *  SPDATA_CREATEGROUPINGROUP
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwParentID;		// ID of the parent group
 *	 DWORD			dwGroupID;		// ID of the new group to be created (output param)
 *	 LPDPNAME		lpName;			// Pointer to DPNAME struct for group name
 *	 LPVOID			lpData;			// Pointer to group data
 *	 DWORD			dwDataSize;		// Size of the group data
 *	 DWORD			dwFlags;		// CreateGroup flags
 *
 *=========================================================================*/
HRESULT WINAPI LP_CreateGroupInGroup(LPSPDATA_CREATEGROUPINGROUP lpCreateGroupInGroup)
{
	HRESULT	hResult = DP_OK;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: entry\n"),DBG_NAME_CREATEGROUPINGROUP );

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_CREATEGROUPINGROUP);
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: return\n"),DBG_NAME_CREATEGROUPINGROUP );

	return DPERR_UNSUPPORTED;		// unsuported function
}

/*==========================================================================
 *
 *  LP_DeleteGroupFromGroup （delete group from group）
 *
 *  SPDATA_DELETEGROUPFROMGROUP
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwParentID;		// ID of the Parent Group
 *	 DWORD			dwGroupID;		// ID of the Group to be deleted
 *
 *=========================================================================*/
HRESULT WINAPI LP_DeleteGroupFromGroup(LPSPDATA_DELETEGROUPFROMGROUP lpDeleteGroupFromGroup)
{
	HRESULT	hResult = DP_OK;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_DELETEGROUPFROMGROUP );

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_DELETEGROUPFROMGROUP);

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_DELETEGROUPFROMGROUP );

	return DPERR_UNSUPPORTED;		// unsuported function
}

/*==========================================================================
 *
 *  LP_DeletePlayerFromGroup （Delete player from group）
 *
 *  SPDATA_DELETEPLAYERFROMGROUP
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwGroupID;		// ID of the Group
 *	 DWORD			dwPlayerID;		// ID of the Player
 *
 *=========================================================================*/
HRESULT WINAPI LP_DeletePlayerFromGroup(LPSPDATA_DELETEPLAYERFROMGROUP lpDeletePlayerFromGroup)
{
	WORD		wUserID;
	WORD		wGroupID;
	int			iPort;
	int			iSleep;
	char		cWait[8];
	char		cServerIP[64];
	int			iSize = 4;
	int			iRtn;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_DELETEPLAYERFROMGROUP );

	//===============================
	//  Get server data 		         
	//===============================
	// port number
	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfoDWORD(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_DELETEPLAYERFROMGROUP, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}


	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_DELETEPLAYERFROMGROUP, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	wUserID = (WORD)lpDeletePlayerFromGroup->dwPlayerID;
	wGroupID = (WORD)lpDeletePlayerFromGroup->dwGroupID & LSP_SLIPMASK_GROUP;
	//===============================
	//  Send request  		             
	//===============================
	if( SRL_Snd_GroupDefect( cServerIP, iPort, wUserID, wGroupID ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_GroupDefect DPERR_GENERIC return\n"),
															DBG_NAME_DELETEPLAYERFROMGROUP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Wait to receive response
	//===============================

	if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT, (LPCTSTR)SRL_REG_WAIT_ON ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Reg_SetInfo %s %s DPERR_GENERIC return\n"),
							DBG_NAME_DELETEPLAYERFROMGROUP, SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT);
		return DPERR_GENERIC;
	}

    // 応答待ち（タイムオーバの場合は異常扱いとする）
	for( iSleep = 0 ; iSleep < SRS_ANSER_WAIT_TIMER ; )
	{
		memset( cWait, 0, sizeof(cWait) );
		if( SRL_Reg_GetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT, (LPCTSTR)cWait ) == -1 )
		{
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
							DBG_NAME_DELETEPLAYERFROMGROUP,SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT);
			return DPERR_GENERIC;
		}

		if( memcmp( cWait, SRL_REG_WAIT_OK, sizeof(SRL_REG_WAIT_OK) ) == 0 ) 
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_DELETEPLAYERFROMGROUP,SRL_REG_KEY_WAIT,SRL_REG_GROUPDEFECT );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: DP_OK return\n"),DBG_NAME_DELETEPLAYERFROMGROUP );
			return DP_OK;
		}
		if( memcmp( cWait, SRL_REG_WAIT_OFF, sizeof(SRL_REG_WAIT_NG) ) == 0 ) 
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_DELETEPLAYERFROMGROUP,SRL_REG_KEY_WAIT,SRL_REG_GROUPDEFECT );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: Error Anser DPERR_GENERIC return\n"),
							DBG_NAME_DELETEPLAYERFROMGROUP );
			return DPERR_GENERIC;
		}
		Sleep( 500 );
		iSleep = iSleep + 500;
	}
	//
	LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: anser timeover %d ms DPERR_TIMEOUT return\n"),
								DBG_NAME_DELETEPLAYERFROMGROUP, SRS_ANSER_WAIT_TIMER );
	return DPERR_TIMEOUT;
}

/*==========================================================================
 *
 *  LP_DestroyGroup （delete group）
 *
 *  SPDATA_DESTROYGROUP
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwGroupID;		// ID of the player on the lobby
 *
 *=========================================================================*/
HRESULT WINAPI LP_DestroyGroup(LPSPDATA_DESTROYGROUP lpDestroyGroup)
{
	WORD		wUserID;
	WORD		wGroupID;
	int			iPort;
	int			iSleep;
	char		cWait[8];
	char		cServerIP[64];
	int			iSize = 4;
	int			iRtn;

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_DESTROYGROUP );

	//===============================
	//  Get server data 		         
	//===============================
	// port number
	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM, SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfoDWORD(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_DESTROYGROUP, SRL_REG_KEY_COM, SRL_REG_PORT );
		return DPERR_GENERIC;
	}


	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_DESTROYGROUP, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}

	wUserID = 0;	 
	wGroupID = (WORD)lpDestroyGroup->dwGroupID & LSP_SLIPMASK_GROUP;
	//===============================
	//  Send request  		             
	//===============================
	if( SRL_Snd_GroupDefect( cServerIP, iPort, wUserID, wGroupID ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Snd_GroupDefect DPERR_GENERIC return\n"),
															DBG_NAME_DESTROYGROUP );
		return DPERR_GENERIC;
	}

	//===============================
	//  Wait to receive response
	//===============================
	if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT, (LPCTSTR)SRL_REG_WAIT_ON ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Reg_SetInfo %s %s DPERR_GENERIC return\n"),
							DBG_NAME_DELETEPLAYERFROMGROUP, SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT);
		return DPERR_GENERIC;
	}

    // Wait response (except timeover)
	for( iSleep = 0 ; iSleep < SRS_ANSER_WAIT_TIMER ; )
	{
		memset( cWait, 0, sizeof(cWait) );
		if( SRL_Reg_GetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT, (LPCTSTR)cWait ) == -1 )
		{
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
							DBG_NAME_DELETEPLAYERFROMGROUP,SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT);
			return DPERR_GENERIC;
		}

		if( memcmp( cWait, SRL_REG_WAIT_OK, sizeof(SRL_REG_WAIT_OK) ) == 0 ) 
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_DELETEPLAYERFROMGROUP,SRL_REG_KEY_WAIT,SRL_REG_GROUPDEFECT );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: DP_OK return\n"),DBG_NAME_DELETEPLAYERFROMGROUP );
			return DP_OK;
		}
		if( memcmp( cWait, SRL_REG_WAIT_OFF, sizeof(SRL_REG_WAIT_NG) ) == 0 )
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_DELETEPLAYERFROMGROUP,SRL_REG_KEY_WAIT,SRL_REG_GROUPDEFECT );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: Error Anser DPERR_GENERIC return\n"),
							DBG_NAME_DELETEPLAYERFROMGROUP );
			return DPERR_GENERIC;
		}
		Sleep( 500 );
		iSleep = iSleep + 500;
	}
	//

	LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: anser timeover %d ms DPERR_TIMEOUT return\n"),
								DBG_NAME_DELETEPLAYERFROMGROUP, SRS_ANSER_WAIT_TIMER );
	return DPERR_TIMEOUT;
}

/*==========================================================================
 *
 *  LP_GetGroupData （Get group data）
 *
 *  SPDATA_GETGROUPDATA
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwGroupID;		// ID of the Group
 *	 LPDWORD		lpdwDataSize;	// Pointer to the size of the lpData buffer
 *	 LPVOID			lpData;			// Pointer to a data buffer
 *
 *=========================================================================*/
HRESULT WINAPI LP_GetGroupData(LPSPDATA_GETGROUPDATA lpGetGroupData)
{

   	int				iRtn;
	int				iPort;
	int				iSleep;
	int				iSize = 4;
	int				iListSize;
	size_t			szSendSize;
	WORD			wMaxGroup;
	DWORD			dwAreaSize;
	LPSRS_INFOGROUP	lpGroupInfo;
	LPSRS_IFFIX 	lpIfFix;
	LPSRL_REGINFO	lpRegInfo;
	char			cRegInfo[SRL_REG_INFO_SZ];
	char			cWait[8];
	char			cServerIP[64];
	char			cIfFix[256];

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_GETGROUPDATA );

	if( lpGroupData != 0 )
	{
		realloc( lpGroupData , 0 );
		lpGroupData  = 0;
	}
//============================================================
//  Lobby server
//============================================================
	//===============================
	//  Get server data 		         
	//===============================
	// port number
	iRtn = (int)SRL_Reg_GetInfoBinary( SRL_REG_KEY_COM,SRL_REG_PORT,(LPCTSTR)&iPort, (DWORD)iSize);
	if( iRtn == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,
						TEXT("%s: SRL_Reg_GetInfoBinary(%s %s)DPERR_GENERIC return\n"),
						DBG_NAME_GETGROUPDATA,SRL_REG_KEY_COM,SRL_REG_PORT);
		return DPERR_GENERIC;
	}


	memset( cServerIP, 0, sizeof(cServerIP) );
	if( SRL_Reg_GetInfo( SRL_REG_KEY_COM, SRL_REG_SERVERIP, (LPCTSTR)cServerIP ) == -1 )
	{

		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo(%s %s)DPERR_GENERIC return\n"),
								DBG_NAME_GETGROUPDATA, SRL_REG_KEY_COM, SRL_REG_SERVERIP );
		return DPERR_GENERIC;
	}
	//==========================
	//  Send to request about all reference information
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
															DBG_NAME_GETGROUPDATA );
		return DPERR_GENERIC;
	}

	//===============================
	//  Wait to eceive response
	//===============================

	if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_ALLGET, (LPCTSTR)SRL_REG_WAIT_ON ) == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: SRL_Reg_SetInfo %s %s DPERR_GENERIC return\n"),
									DBG_NAME_GETGROUPDATA, SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
		return DPERR_GENERIC;
	}

    // Wait response (except timeover)
	for( iSleep = 0 ; iSleep < SRS_ANSER_WAIT_TIMER ; )
	{
		memset( cWait, 0, sizeof(cWait) );
		if( SRL_Reg_GetInfo( SRL_REG_KEY_WAIT, SRL_REG_ALLGET, (LPCTSTR)cWait ) == -1 )
		{
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
									DBG_NAME_GETGROUPDATA,SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
			return DPERR_GENERIC;
		}

		if( memcmp( cWait, SRL_REG_WAIT_OK, sizeof(SRL_REG_WAIT_OK) ) == 0 ) 
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_ALLGET, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_GETGROUPDATA, SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
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
								DBG_NAME_GETGROUPDATA  );
				return DPERR_GENERIC;
			}
			wMaxGroup = lpRegInfo->wMaxGroup;
			dwAreaSize = SRS_USER_ITEM_SZ * wMaxGroup + SRS_INFO_GROUP_COM_SZ;
			lpGroupInfo = (LPSRS_INFOGROUP)malloc( dwAreaSize );
			if( lpGroupInfo == NULL )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: malloc error USERITEM DPERR_OUTOFMEMORY return\n"),
								DBG_NAME_GETGROUPDATA  );
				return DPERR_OUTOFMEMORY;
			}
			lpGroupArea = (char *)lpGroupInfo;
			memset( lpGroupArea, 0, dwAreaSize );
			if( SRL_Mng_AllGet(0, 0,(char *)lpGroupInfo,  0 ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Mng_AllGet error User DPERR_GENERIC return\n"),
																	DBG_NAME_GETGROUPDATA );
				realloc( lpGroupArea, 0 );
				lpGroupArea = 0;
				return DPERR_GENERIC;
			}
			iListSize = sizeof(LSP_GROUPDATA) + lpGroupInfo->GP_wEntryGroup * SRS_GROUP_ITEM_SZ;
	        *lpGetGroupData->lpdwDataSize = iListSize;
			if (lpGetGroupData->lpData == NULL)
			{
				LSP_Dbg_Printf( DBG_LEVEL_1, 
						TEXT("%s: Get Size = %d \n"),
          							DBG_NAME_GETGROUPDATA,iListSize);
				realloc( lpGroupArea, 0 );
				lpGroupArea = 0;
				return DPERR_BUFFERTOOSMALL;
			}

			lpGroupData = (LPLSP_GROUPDATA)lpGetGroupData->lpData; 
			memset( lpGroupData, 0, iListSize );
			iRtn = LSP_MK_GroupList( lpGroupInfo, lpGroupData, lpGetGroupData->dwGroupID );

			lpGetGroupData->lpData = (void *)lpGroupData;

			realloc( lpGroupArea, 0 );
			lpGroupArea = 0;
			LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s: DP_OK return\n"),DBG_NAME_GETGROUPDATA );
			return DP_OK;
		}
		//============================
		//  fail to all reference information
		//============================
		if( memcmp( cWait, SRL_REG_WAIT_OFF, sizeof(SRL_REG_WAIT_NG) ) == 0 )
		{

			if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_ALLGET, SRL_REG_WAIT_OFF ) == -1 )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,
								TEXT("%s: SRL_Reg_GetInfo %s %s DPERR_GENERIC return\n"),
								DBG_NAME_GETGROUPDATA, SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
				return DPERR_GENERIC;
			}
			LSP_Dbg_Printf( DBG_LEVEL_0,
							TEXT("%s: Error Anser DPERR_GENERIC return\n"),
							DBG_NAME_GETGROUPDATA );
			return DPERR_GENERIC;
		}
		Sleep( 500 );
		iSleep = iSleep + 500;
	}
	//
	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: anser timeover %d ms DPERR_TIMEOUT return\n"),
								DBG_NAME_GETGROUPDATA, SRS_ANSER_WAIT_TIMER );
	return DPERR_TIMEOUT;
}

/*==========================================================================
 *
 *  LP_SetGroupData （Set group data）
 *
 *  SPDATA_SETGROUPDATA
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwGroupID;		// ID of the group
 *	 LPVOID			lpData;			// Pointer to the new group data
 *	 DWORD			dwDataSize;		// Size of lpData
 *	 DWORD			dwFlags;		// Flags
 *
 *=========================================================================*/
HRESULT WINAPI LP_SetGroupData(LPSPDATA_SETGROUPDATA lpSetGroupData)
{
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_SETGROUPDATA );

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_SETGROUPDATA);

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_SETGROUPDATA );

	return DPERR_UNSUPPORTED;		// unsuported function
}

/*==========================================================================
 *
 *  LP_SetGroupName （Set group name）
 *
 *  SPDATA_SETGROUPNAME
 *	 DWORD			dwSize;			// Size of this structure
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwGroupID;		// ID of the group
 *	 LPDPNAME		lpName;			// Pointer to the new DPNAME struct
 *	 DWORD			dwFlags;		// Flags
 *
 *=========================================================================*/
HRESULT WINAPI LP_SetGroupName(LPSPDATA_SETGROUPNAME lpSetGroupName)
{
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_SETGROUPNAME );

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_SETGROUPNAME);

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_SETGROUPNAME );

	return DPERR_UNSUPPORTED;		// unsuported function
}

/*==========================================================================
 *
 *  LP_GetGroupConnectionSettings （Get group connection setting）
 *
 *  SPDATA_GETGROUPCONNECTIONSETTINGS
 *	 DWORD			dwSize;			// Size of this structure
 *	 DWORD			dwFlags;		// Flags
 *	 LPDPLOBBYSP	lpISP;			// Pointer to an IDPLobbySP interface
 *	 DWORD			dwGroupID;		// ID of the Group
 *	 LPDWORD		lpdwBufferSize;	// Pointer to the size of the buffer
 *	 LPVOID			lpBuffer;		// Pointer to a buffer
 *
 *=========================================================================*/
HRESULT WINAPI LP_GetGroupConnectionSettings(LPSPDATA_GETGROUPCONNECTIONSETTINGS lpGetGroupConnectionSetting)
{
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_GETGROUPCONNECTIONSETTINGS );

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_GETGROUPCONNECTIONSETTINGS);

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_GETGROUPCONNECTIONSETTINGS );

	return DPERR_UNSUPPORTED;		// unsuported function
}

/*==========================================================================
 *
 *  LP_SetGroupConnectionSettings （Set Group Connection Settings）
 *
 *  SPDATA_SETGROUPCONNECTIONSETTINGS
 *	 DWORD				dwSize;			// Size of this structure
 *	 DWORD				dwFlags;		// Flags
 *	 LPDPLOBBYSP		lpISP;			// Pointer to an IDPLobbySP interface
 * 	 DWORD				dwGroupID;		// ID of the group
 *	 LPDPLCONNECTION	lpConn;			// Pointer to a DPLCONNECTION structure
 *
 *=========================================================================*/
HRESULT WINAPI LP_SetGroupConnectionSettings(LPSPDATA_SETGROUPCONNECTIONSETTINGS lpSetGroupConnectionSetting)
{
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_SETGROUPCONNECTIONSETTINGS );

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: unsuported callback function\n"),DBG_NAME_SETGROUPCONNECTIONSETTINGS);

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_SETGROUPCONNECTIONSETTINGS );

	return DPERR_UNSUPPORTED;		// unsuported function
}
