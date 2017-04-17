/*==========================================================================
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       LSPmakelist.cpp
 *
 *	Content:	Code file for session-oriented LOBBY-SP callback functions
 *
 *  Functions:  LSP_MK_PlayerList
 *              LSP_MK_GroupList
 *
 *	History:	1999/10/04		Created it
 *
 *=========================================================================*/
#include <windows.h>

#include "LSPlobby.h"

/*=============================================================================
     Function: Create player list
     Input   ：lpUserInfo
	       lpPlayerData
	       dwPlayerID
     Output  ：no
     Return  ：True 0
               False -1

==============================================================================*/
__declspec( dllexport )int __stdcall LSP_MK_PlayerList( LPSRS_INFOUSER lpInfoUser, 
														LPLSP_PLAYERDATA lpPlayerData,
														DWORD dwPlayerID)
{
	WORD	wEntryUser;
	WORD	wInfoUser;
	WORD	wPlayerList;

	//==============================
	//  Copy valied information 
	//==============================
	wEntryUser = 0;
	wInfoUser = 0;
	wPlayerList = 0;
	lpPlayerData->dwPlayerCount = (DWORD)lpInfoUser->US_wEntryUser;
	lpPlayerData->dwPlayerID = dwPlayerID;

	for( ; wEntryUser < lpInfoUser->US_wEntryUser ; )
	{
		if( lpInfoUser->US_info_user[wInfoUser].USI_cUserName[0] != 0 )
		{
			memcpy( (char *)&(lpPlayerData->useritem[wPlayerList]),
					(char *)&(lpInfoUser->US_info_user[wInfoUser]),
 					SRS_USER_ITEM_SZ );
			wEntryUser++;
			wPlayerList++;
		}
		wInfoUser++;
	}
	return( 0 );
}

/*=============================================================================
     Function ：Create group list
     Input    ：lpInfoGroup
              ：lpGroupData
              ：dwGroupID
     Output   ：no
     Return   ：True  0
                False -1
=============================================================================*/
__declspec( dllexport )int __stdcall LSP_MK_GroupList( LPSRS_INFOGROUP lpInfoGroup, 
												       LPLSP_GROUPDATA lpGroupData,
                                                       DWORD dwGroupID )
{
	WORD	wEntryGroup;
	WORD	wInfoGroup;
	WORD	wGroupList;

	//==============================
	//  Copy valied information
	//==============================
	wEntryGroup = 0;
	wInfoGroup = 0;
	wGroupList = 0;
	lpGroupData->dwGroupCount = (DWORD)lpInfoGroup->GP_wEntryGroup;
	lpGroupData->dwGroupID = dwGroupID;

	for( ; wEntryGroup < lpInfoGroup->GP_wEntryGroup ; )
	{
		if( lpInfoGroup->GP_info_group[wInfoGroup].GPI_cGroupName[0] != 0 )
		{
			memcpy( (char *)&(lpGroupData->groupitem[wGroupList]),
					(char *)&(lpInfoGroup->GP_info_group[wInfoGroup]),
 					SRS_GROUP_ITEM_SZ );
			wEntryGroup++;
			wGroupList++;
		}
		wInfoGroup++;
	}
	return( 0 );
}
