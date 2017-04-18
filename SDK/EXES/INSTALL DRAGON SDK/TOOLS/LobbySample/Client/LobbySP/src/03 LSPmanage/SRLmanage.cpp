/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRLmanage.cpp
 *
 *					== Information Set function ==
 *					SRL_Mng_Startup		   
 *					SRL_Mng_Renewal		   
 *					SRL_Mng_Shutdown	   
 *
 *					== Information Get function  ==
 *					SRL_Mng_AllGet		   
 *					SRL_Mng_GetUserByName  
 *					SRL_Mng_GetUserByID    
 *					SRL_Mng_GetLobbyByName 
 *					SRL_Mng_GetLobbyByID   
 *					SRL_Mng_GetGroupByName 
 *					SRL_Mng_GetGroupByID   
 *					SRL_Mng_GetEntryNo 	   
 *
 *                  == Common function ==
 *                  SRL_Mng_GetInfo		   
 *                  SRL_Mng_PutInfo		   
 *
 *  Content:    Lobby client/server user information lib
 *
 ***************************************************************************/
/*================================
    Include
==================================*/
#include <windows.h>
#include <stdio.h>

#include "LSPdebug.h"
#include "SRScom.h"
#include "SRLmanage.h"
#include "SRLregistry.h"

/*================================
    Global area	
==================================*/
int		iUserSize  = 0;
int		iLobbySize = 0;
int		iGroupSize = 0;
int		iGameSize  = 0;
struct 	SRS_INFO_USER	*lpInfoUser  = 0;	// User information
struct	SRS_INFO_LOBBY	*lpInfoLobby = 0;	// Lobby information
struct	SRS_INFO_GROUP	*lpInfoGroup = 0;	// Group Information
struct  SRS_INFO_GAME	*lpInfoGame  = 0;	// Game Information

/*=============================================================================
     Function ：SRL_Mng_Startup（Init the server manegement table)
	 			User information list
				Game information list
				Lobby information list
     Input    ：no
     Output   ：no
     Return   ：True  0
                False -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRL_Mng_Startup( void )
{
	int		iRtn;
	int		iItem;
	WORD	wMaxUser;								
	WORD	wMaxLobby;								
	WORD	wMaxGame;								
	WORD	wMaxGroup;								
	WORD	wItem;
	FILE	*fFp = (FILE *)NULL;					
	struct	SRL_REG_INFO	*lpRegInfo;				
	char	cRegInfo[SRL_REG_INFO_SZ];				
	char	cUserInfo[SRS_INFO_USER_COM_SZ];
	char	cLobbyInfo[SRS_INFO_LOBBY_COM_SZ];
	char	cGroupInfo[SRS_INFO_GROUP_COM_SZ];
	char	cGameInfo[SRS_INFO_GAME_COM_SZ];
	char	cUserItem[SRS_USER_ITEM_SZ];
	char	cLobbyItem[SRS_LOBBY_ITEM_SZ];
	char	cGroupItem[SRS_GROUP_ITEM_SZ];
	char	cGameItem[SRS_GAME_ITEM_SZ];
	char	cRegName[32];

	//==============================================
	//  Init
	//==============================================
	LSP_Dbg_Printf(1, TEXT("SRL_Mng_Startup : Initializing\n" ));

	iUserSize = 0;
	iLobbySize = 0;
	iGroupSize = 0;
	iGameSize = 0;
	lpInfoUser = 0;
	lpInfoLobby = 0;
	lpInfoGroup = 0;
	lpInfoGame = 0;

	//==============================================
	//  Reg init
	//==============================================
	memset(	cUserInfo,0,SRS_INFO_USER_COM_SZ );
	memset(	cLobbyInfo,0,SRS_INFO_LOBBY_COM_SZ );
	memset(	cGroupInfo,0,SRS_INFO_GROUP_COM_SZ );
	memset(	cGameInfo,0,SRS_INFO_GAME_COM_SZ );
	memset(	cUserItem,0,SRS_USER_ITEM_SZ );
	memset(	cLobbyItem,0,SRS_LOBBY_ITEM_SZ );
	memset(	cGroupItem,0,SRS_GROUP_ITEM_SZ );
	memset(	cGameItem,0,SRS_GAME_ITEM_SZ );

	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGUSER, (LPCTSTR)SRL_REG_USERMASK, SRL_REG_MASK_OFF );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGLOBBY, (LPCTSTR)SRL_REG_LOBBYMASK, SRL_REG_MASK_OFF );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGROUP, (LPCTSTR)SRL_REG_GROUPMASK, SRL_REG_MASK_OFF );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGAME, (LPCTSTR)SRL_REG_GAMEMASK, SRL_REG_MASK_OFF );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	//==============================================
	//  Get common information
	//==============================================
	lpRegInfo = (struct SRL_REG_INFO *)cRegInfo;
	iRtn = SRL_Reg_GetComInfo( lpRegInfo );		// Get common information
	if( iRtn == -1)
	{
		LSP_Dbg_Printf(0,TEXT("SRL_Mng_Startup : SRL_Reg_GetComInfo error \n"));
		return( -1 );
	}
	wMaxUser  =	lpRegInfo->wMaxUser;			// Max user value
	wMaxLobby = lpRegInfo->wMaxLobby;			// Max lobby value
	wMaxGame  = lpRegInfo->wMaxGame;			// Max game value
	wMaxGroup = lpRegInfo->wMaxGroup;			// Max group value
	
	//==============================================
	//  Create User list area
	//==============================================
	iItem = (int)wMaxUser + 1;
	iUserSize = SRS_USER_ITEM_SZ * iItem;
	iUserSize = iUserSize + SRS_INFO_USER_COM_SZ;
	lpInfoUser = (struct SRS_INFO_USER *)malloc( iUserSize );
	if( lpInfoUser == 0 )
	{
		LSP_Dbg_Printf(0,TEXT("??? malloc SRS_INFO_USER (%d) ??? \n"), iUserSize );
		return( -1 );
	}
	memset( (char *)lpInfoUser, 0, iUserSize );
	lpInfoUser->US_wMaxUser = wMaxUser;			// Set max user
	
	//==============================================
	//  Init Reg value
	//==============================================
	iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGUSER, SRL_REG_USERINFO,
								 (LPCTSTR)cUserInfo, SRS_INFO_USER_COM_SZ );
	for( wItem=0 ; wMaxUser+1 > wItem ; wItem++ )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"), SRL_REG_USERITEM, wItem );
		iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGUSER, SRL_REG_USERITEM,
										 (LPCTSTR)cUserItem, SRS_USER_ITEM_SZ );
	}
	//==============================================
	//  Create lobby list area
	//==============================================
	iLobbySize = SRS_LOBBY_ITEM_SZ * wMaxLobby;
	iLobbySize = iLobbySize + SRS_INFO_LOBBY_COM_SZ;
	lpInfoLobby = (struct SRS_INFO_LOBBY *)malloc( iLobbySize );
	if( lpInfoLobby == 0 )
	{
		LSP_Dbg_Printf(0,TEXT("??? malloc SRS_INFO_LOBBY (%d) ??? \n"), iLobbySize );
		return( -1 );
	}
	memset( (char *)lpInfoLobby, 0, iLobbySize );
	lpInfoLobby->LB_wMaxLobby = wMaxLobby;		// Set max lobby

	//==============================================
	//  Init Reg value
	//==============================================
	iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYINFO,
								 (LPCTSTR)cLobbyInfo, SRS_INFO_LOBBY_COM_SZ );
	for( wItem=0 ; wMaxLobby > wItem ; wItem++ )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"), SRL_REG_LOBBYITEM, wItem );
		iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYITEM,
										 (LPCTSTR)cLobbyItem, SRS_LOBBY_ITEM_SZ );
	}

	//==============================================
	//  Create group list area
	//==============================================
	iItem = (int)wMaxGroup + 1;
	iGroupSize = SRS_GROUP_ITEM_SZ * iItem;
	iGroupSize = iGroupSize + SRS_INFO_GROUP_COM_SZ;
	lpInfoGroup = (struct SRS_INFO_GROUP *)malloc( iGroupSize );
	if( lpInfoGroup == 0 )
	{
		LSP_Dbg_Printf(0,TEXT("??? malloc SRS_INFO_GROUP (%d) ??? \n"), iGroupSize );
		return( -1 );
	}
	memset( (char *)lpInfoGroup, 0, iGroupSize );
	lpInfoGroup->GP_wMaxGroup = wMaxGroup;		// Set max group
	
	//==============================================
	//  Init Reg value
	//==============================================
	iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGGROUP, SRL_REG_GROUPINFO,
								 (LPCTSTR)cGroupInfo, SRS_INFO_GROUP_COM_SZ );
	for( wItem=0 ; wMaxGroup+1 > wItem ; wItem++ )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"), SRL_REG_GROUPITEM, wItem );
		iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGGROUP, SRL_REG_GROUPITEM,
										 (LPCTSTR)cGroupItem, SRS_GROUP_ITEM_SZ );
	}

	//==============================================
	//  Create game list area
	//==============================================
	iItem = (int)wMaxGame + 1;
	iGameSize = SRS_GAME_ITEM_SZ * iItem;
	iGameSize = iGameSize + SRS_INFO_GAME_COM_SZ;
	lpInfoGame = (struct SRS_INFO_GAME *)malloc( iGameSize );
	if( lpInfoGame == 0 )
	{
		LSP_Dbg_Printf(0,TEXT("??? malloc SRS_INFO_GAME (%d) ??? \n"), iGameSize );
		return( -1 );
	}
	memset( (char *)lpInfoGame, 0, iGameSize );
	lpInfoGame->GM_wMaxGame = wMaxGame;			// Set max game
	lpInfoGame->GM_wEntryGame = 0;				// Set game 
	
	//==============================================
	//  Init Reg value
	//==============================================
	iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEINFO,
								 (LPCTSTR)cGameInfo, SRS_INFO_GAME_COM_SZ );
	for( wItem=0 ; wMaxGame > wItem ; wItem++ )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"), SRL_REG_GAMEITEM, wItem );
		iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEITEM,
										 (LPCTSTR)cGameItem, SRS_GAME_ITEM_SZ );
	}

	//==============================================
	//  information backup
	//==============================================
	iRtn = SRL_Mng_PutInfo( );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(0, TEXT("SRL_Mng_Startup : ERROR\n" ));
		return( -1 );
	}
	return( 0 );
}

/*=============================================================================
     Function: SRL_Mng_Renewal
     Input   ：lpRenewal
	 Output  ：no
     Return  ：True   0
               False -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRL_Mng_Renewal( char *lpRenewal )
{
	int		iRtn;								//
	WORD	wRenewalCount;						// 
	WORD	wID;								//
	char	*lpData;							//
	struct	SRS_IF_RENEWAL	*lpIfRenewal;		//
	struct	SRS_INFO_USER	*lpUser;			//
	struct	SRS_INFO_LOBBY	*lpLobby;			//
	struct	SRS_INFO_GROUP	*lpGroup;			//
	struct	SRS_INFO_GAME	*lpGame;			//
	struct	SRS_USER_ITEM	*lpUserItem;		//
	struct	SRS_LOBBY_ITEM	*lpLobbyItem;		//
	struct	SRS_GROUP_ITEM	*lpGroupItem;		//
	struct	SRS_GAME_ITEM	*lpGameItem;		//

	//==============================================  
	//  Get information
	//==============================================
	LSP_Dbg_Printf(1, TEXT("SRL_Mng_Renewal\n" ));
	iRtn = SRL_Mng_GetInfo( );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(0, TEXT("SRL_Mng_Renewal : SRL_Mng_GetInfo error\n" ));
		return( -1 );
	}

	//===========================================
	//  User information renewal
	//===========================================
	lpIfRenewal = (struct SRS_IF_RENEWAL *)lpRenewal;
	lpData = lpIfRenewal->IF_RE_cInfo;
	LSP_Dbg_Printf(2,TEXT("IF_RE_wUserInfoNo = %d \n"), lpIfRenewal->IF_RE_wUserInfoNo );
	if( lpIfRenewal->IF_RE_wUserInfoNo != 0 )				// User info renewal ？
	{
		lpUser = (struct SRS_INFO_USER *)lpData;
		lpInfoUser->US_wEntryUser = lpUser->US_wEntryUser;	
		wRenewalCount = lpIfRenewal->IF_RE_wUserInfoNo;
		lpUserItem = (struct SRS_USER_ITEM *)&lpUser->US_info_user[0];
		for( ; wRenewalCount > 0 ; wRenewalCount-- )
		{
			wID = lpUserItem->USI_wUserID;		
			memcpy( (char *)&lpInfoUser->US_info_user[wID], // User renewal
					(char *)lpUserItem, SRS_USER_ITEM_SZ );
			lpUserItem = lpUserItem + 1;
		}
		lpData = (char *)lpUserItem;
	}
	
	//===========================================
	//  Lobby information renewal
	//===========================================
	LSP_Dbg_Printf(2,TEXT("IF_RE_wLobbyInfoNo = %d \n"), lpIfRenewal->IF_RE_wLobbyInfoNo );
	if( lpIfRenewal->IF_RE_wLobbyInfoNo != 0 )				// Lobby info renwewal ？
	{
		lpLobby = (struct SRS_INFO_LOBBY *)lpData;
		wRenewalCount = lpIfRenewal->IF_RE_wLobbyInfoNo;
		lpLobbyItem = (struct SRS_LOBBY_ITEM *)&lpLobby->LB_info_lobby[0];
		for( ; wRenewalCount != 0 ; wRenewalCount-- )
		{
			wID = lpLobbyItem->LBI_wLobbyID;		
			memcpy( (char *)&lpInfoLobby->LB_info_lobby[wID], // lobby renewal
					(char *)lpLobbyItem, SRS_LOBBY_ITEM_SZ );
			lpLobbyItem = lpLobbyItem + 1;
		}
		lpData = (char *)lpLobbyItem;
	}

	//===========================================
	//  Group information renewal
	//===========================================
	LSP_Dbg_Printf(2,TEXT("IF_RE_wGroupInfoNo = %d \n"), lpIfRenewal->IF_RE_wGroupInfoNo );
	if( lpIfRenewal->IF_RE_wGroupInfoNo != 0 )				// Group renewal？
	{
		lpGroup = (struct SRS_INFO_GROUP *)lpData;
		lpInfoGroup->GP_wEntryGroup = lpGroup->GP_wEntryGroup;
		wRenewalCount = lpIfRenewal->IF_RE_wGroupInfoNo;
		lpGroupItem = (struct SRS_GROUP_ITEM *)&lpGroup->GP_info_group[0];
		for( ; wRenewalCount != 0 ; wRenewalCount-- )
		{
			wID = lpGroupItem->GPI_wGroupID;		
			memcpy( (char *)&lpInfoGroup->GP_info_group[wID], // Group renewal
					(char *)lpGroupItem, SRS_GROUP_ITEM_SZ );
			lpGroupItem = lpGroupItem + 1;
		}
		lpData = (char *)lpGroupItem;
	}

	//===========================================
	//  Game information renewal
	//===========================================
	LSP_Dbg_Printf(2,TEXT("IF_RE_wGameInfoNo = %d \n"), lpIfRenewal->IF_RE_wGameInfoNo );
	if( lpIfRenewal->IF_RE_wGameInfoNo != 0 )				// Game info renewal？
	{
		lpGame = (struct SRS_INFO_GAME *)lpData;
		lpInfoGame->GM_wEntryGame = lpGame->GM_wEntryGame;
		wRenewalCount = lpIfRenewal->IF_RE_wGameInfoNo;
		lpGameItem = (struct SRS_GAME_ITEM *)&lpGame->GM_info_game[0];
		for( ; wRenewalCount != 0 ; wRenewalCount-- )
		{
			wID = lpGameItem->GMI_wGameID;		
			memcpy( (char *)&lpInfoGame->GM_info_game[wID], // Game renewal
					(char *)lpGameItem, SRS_GAME_ITEM_SZ );
			lpGameItem = lpGameItem + 1;
		}
		lpData = (char *)lpGameItem;
	}

	//==============================================  
	//  information backup
	//==============================================
	iRtn = SRL_Mng_PutInfo( );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(1, TEXT("SRL_Mng_Renewal : SRL_Mng_PutInfo error\n" ));
		return( -1 );
	}
	return( 0 );
}

/*=============================================================================
     Function：SRL_Mng_AllGet
	 Input   ：lpUser   Pointer for user list area or NULL
	 		   lpLobby	Pointer for lobby list area or NULL
			   lpGroup	Pointer for group list area or NULL
			   lpGame   Pointer for game list area or NULL
     Output  ：no
     Return  ：True   0
               False -1

=============================================================================*/
__declspec( dllexport )int __stdcall SRL_Mng_AllGet( char *lpUser, char *lpLobby,
													 char *lpGroup, char *lpGame )
{
	int		iRtn;						

	//==============================================  
	//  Information development
	//==============================================
	iRtn = SRL_Mng_GetInfo( );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	
	//==============================================
	//  Get management data
	//==============================================
	if( lpUser != NULL )		// User list？
	{
		LSP_Dbg_Printf(1,TEXT("SRL_Mng_AllGet : Get User INFO \n"));
		memcpy( lpUser, lpInfoUser, iUserSize );
		LSP_Dbg_Printf(2,TEXT("SRL_Mng_AllGet : lpUser->US_wEntryUser=%d \n"),
			(struct SRS_INFO_USER *)lpInfoUser->US_wEntryUser);
	}
	if( lpLobby != NULL )		// Lobby list？
	{
		LSP_Dbg_Printf(1,TEXT("SRL_Mng_AllGet : Get Lobby INFO \n"));
		memcpy( lpLobby, lpInfoLobby, iLobbySize );
	}
	if( lpGroup != NULL )		// Group list？
	{
		LSP_Dbg_Printf(1,TEXT("SRL_Mng_AllGet : Get Group INFO \n"));
		memcpy( lpGroup, lpInfoGroup, iGroupSize );
	}
	if( lpGame != NULL )		// Game list？
	{
		LSP_Dbg_Printf(1,TEXT("SRL_Mng_AllGet : Get Game INFO \n"));
		memcpy( lpGame, lpInfoGame, iGameSize );
	}
	return( 0 );
}

/*=============================================================================
     Function：SRL_Mng_GetUserByName
     Input   ：lpUserName  Pointer for user name area（Over SRS_MAX_NAME_USER)
	Output  ：no
     Return  ：True  User ID
	           False SRS_WORD_ERROR(65535)
	 Other   ：The end of user name is NULL
=============================================================================*/
__declspec( dllexport )WORD __stdcall SRL_Mng_GetUserByName( char *lpUserName )
{
	int		iRtn;								//
	WORD	wID;								//

	//==============================================  
	//  Information development
	//==============================================
	iRtn = SRL_Mng_GetInfo( );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(0,TEXT("SRL_Mng_GetUserByName : SRL_Mng_GetInfo error\n"));
		return( SRS_WORD_ERROR );
	}

	//==============================================
	// Looking for User name
	//==============================================
	if( lpInfoUser->US_wMaxUser == 0 )
	{
		LSP_Dbg_Printf(0, TEXT("SRL_Mng_GetUserByName : No information of user\n" ));
		return( SRS_WORD_ERROR );
	}
	for( wID = 0 ; wID < lpInfoUser->US_wMaxUser + 1; wID++ )
	{
		if( (memcmp( lpInfoUser->US_info_user[wID].USI_cUserName, lpUserName, SRS_MAX_NAME_USER )) == 0 )
		{
			return( wID );
		}
	}
	LSP_Dbg_Printf(0, TEXT("SRL_Mng_GetUserByName : Not a valid user\n" ));
	return( SRS_WORD_ERROR );
}

/*=============================================================================
     Function：SRL_Mng_GetLobbyByName
	 Inout   ：lpLobbyName  Pointer for Lobby name（Need over 16 byte)
	 Output  ：no
     Return  ：True  Lobby ID
	           False SRS_WORD_ERROR(65535)
	 Other   : The end of lobby name is NULL
=============================================================================*/
__declspec( dllexport )WORD __stdcall SRL_Mng_GetLobbyByName( char *lpLobbyName )
{
	int		iRtn;								//
	WORD	wID;								//

	//==============================================  
	//  Information development
	//==============================================
	iRtn = SRL_Mng_GetInfo( );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(0,TEXT("SRL_Mng_GetLobbyByName : SRL_Mng_GetInfo error\n"));
		return( SRS_WORD_ERROR );
	}

	//==============================================
	// Looking for Lobby
	//==============================================
	if( lpInfoLobby->LB_wMaxLobby == 0 )
	{
		LSP_Dbg_Printf(0, TEXT("SRL_Mng_GetLobbyByName : No information of Lobby\n" ));
		return( SRS_WORD_ERROR );
	}
	for( wID = 0 ; wID < lpInfoLobby->LB_wMaxLobby ; wID++ )
	{
		if( (memcmp( lpInfoLobby->LB_info_lobby[wID].LBI_cLobbyName, lpLobbyName, SRS_MAX_NAME_LOBBY )) == 0 )
		{
			return( wID );
		}
	}
	LSP_Dbg_Printf(0, TEXT("SRL_Mng_GetLobbyByName : Not a valid Lobby\n" ));
	return( SRS_WORD_ERROR );
}

/*=============================================================================
     Function：SRL_Mng_GetGroupByName
     Input   ：lpLobbyName  Pointer for group name. need over 20 bytes
	 Output  ：no
     Return  ：True  Group ID
	           False SRS_WORD_ERROR(65535)
	 Other   : The end of gourp name is NULL
=============================================================================*/
__declspec( dllexport )WORD __stdcall SRL_Mng_GetGroupByName( char *lpGroupName )
{
	int		iRtn;								//
	WORD	wID;								//

	//==============================================  
	//  Information development
	//==============================================
	iRtn = SRL_Mng_GetInfo( );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(0,TEXT("SRL_Mng_GetGroupByName : SRL_Mng_GetInfo error\n"));
		return( SRS_WORD_ERROR );
	}

	//==============================================
	//  Looking for group
	//==============================================
	if( lpInfoGroup->GP_wMaxGroup == 0 )
	{
		LSP_Dbg_Printf(0, TEXT("SRL_Mng_GetGroupByName : No information of Group\n" ));
		return( SRS_WORD_ERROR );
	}
	for( wID = 0 ; wID < lpInfoGroup->GP_wMaxGroup + 1; wID++ )
	{
		if( (memcmp( lpInfoGroup->GP_info_group[wID].GPI_cGroupName, lpGroupName, SRS_MAX_NAME_GROUP )) == 0 )
		{
			return( wID );
		}
	}
	LSP_Dbg_Printf(0, TEXT("SRL_Mng_GetGroupByName : Not a valid group\n" ));
	return( SRS_WORD_ERROR );
}

/*=============================================================================
     SRL_Mng_GetUserByID
     Input   ：wUserName  Pointer for group name. need over 20 bytes
			   lpUserInfo 
	 Output  ：User information
     Return  ：True  0
	           False -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRL_Mng_GetUserByID( WORD wUserID, char *lpUserInfo )
{
	int		iRtn;
	int		iItemSize;

	//==============================================  
	//  Information development
	//==============================================
	iRtn = SRL_Mng_GetInfo( );
	if( iRtn == -1 )
	{
		return( -1 );
	}

	//==============================================
	//  Get User information
	//==============================================
	iItemSize  = SRS_USER_ITEM_SZ;
	memset( lpUserInfo, 0, iItemSize );
	if( wUserID >= lpInfoUser->US_wMaxUser )
	{
		return( -1 );
	}
	memcpy( lpUserInfo, (char *)lpInfoUser->US_info_user[wUserID].USI_cClientName,	SRS_USER_ITEM_SZ );
	return( 0 );
}

/*=============================================================================
     Function : SRL_Mng_GetLobbyByID
     Input   ：wLobbyName lobby ID
	 		   lpLobbyInfo Pointer for group name. need over SRS_LOBBY_ITEM_SZ bytes
	 Output  ：lobby information
     Return  ：True  0
	           False -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRL_Mng_GetLobbyByID( WORD wLobbyID, char *lpLobbyInfo )
{
	int		iRtn;	

	//==============================================  
	//  Information development
	//==============================================
	iRtn = SRL_Mng_GetInfo( );
	if( iRtn == -1 )
	{
		return( -1 );
	}

	//==============================================
	//  Get Lobby information
	//==============================================
	memset( lpLobbyInfo, 0, SRS_LOBBY_ITEM_SZ );
	if( wLobbyID >= lpInfoLobby->LB_wMaxLobby )
	{
		return( -1 );
	}
	memset( lpLobbyInfo, 0, SRS_LOBBY_ITEM_SZ );
	memcpy( lpLobbyInfo,
            (char *)&(lpInfoLobby->LB_info_lobby[wLobbyID].LBI_iLockword),	SRS_LOBBY_ITEM_SZ );

	return( 0 );
}

/*=============================================================================
     Function :SRL_Mng_GetGroupByID
     Input    :wGroupID lobby ID
	 		   lpGroupInfo Pointer for group name. need over SRS_GROUP_ITEM_SZ bytes
	 Output   :lobby information
     Return   :True  0
	           False -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRL_Mng_GetGroupByID( WORD wGroupID, char *lpGroupInfo )
{
	int		iRtn;


	//==============================================  
	//  Information development
	//==============================================
	iRtn = SRL_Mng_GetInfo( );
	if( iRtn == -1 )
	{
		return( -1 );
	}

	//==============================================
	//  Get gourp information
	//==============================================
	memset( lpGroupInfo, 0, SRS_GROUP_ITEM_SZ );
	if( wGroupID >= lpInfoGroup->GP_wMaxGroup )
	{
		return( -1 );
	}
	memset( lpGroupInfo, 0, SRS_GROUP_ITEM_SZ );
	memcpy( lpGroupInfo,
            (char *)&(lpInfoGroup->GP_info_group[wGroupID].GPI_iLockword),	SRS_GROUP_ITEM_SZ );

	return( 0 );
}

/*=============================================================================
     Function :SRL_Mng_GetEntryNo
     Input    :iKind 
	 Output   :no
     Return   :True  Entry count
	           False -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRL_Mng_GetEntryNo( int iKind )
{
	int		iRtn;

	//==============================================  
	//  Information development
	//==============================================
	iRtn = SRL_Mng_GetInfo( );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	//==============================================  
	//  Get entry information
	//==============================================
	switch( iKind )
	{
		case  SRL_MNG_USER	: iRtn = (int)lpInfoUser->US_wEntryUser;
							  break;	
		case  SRL_MNG_LOBBY	: iRtn = (int)lpInfoLobby->LB_wMaxLobby;
						      break;
		case  SRL_MNG_GROUP	: iRtn = (int)lpInfoGroup->GP_wEntryGroup;
							  break;
		case  SRL_MNG_GAME	: iRtn = (int)lpInfoGame->GM_wMaxGame;
							  break;	
		default				: iRtn = 0;
							  break;	
	}
	return( iRtn );
}

/*=============================================================================
     Function :SRL_Mng_GetInfo
     Input    :iMode	
						SRS_INFO_GET
						SRS_INFO_NO
	 Output   :Copy the management information to global area.
     Return   :True   0
	           False -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRL_Mng_GetInfo( void )
{
	int		iRtn;
	int		iItem;
	WORD	wRegItem;
	WORD	wMaxUser;
	WORD    wMaxLobby;
	WORD	wMaxGroup;
	WORD	wMaxGame;
	char	cRegName[32];
	char	cMask[8];

	LSP_Dbg_Printf(2,TEXT("SRL_Mng_GetInfo : %d %d %d %d \n"),
 							 iUserSize, iLobbySize, iGroupSize, iGameSize);
	//==============================================
	//  Read user information
	//==============================================
	for( ; ; )
	{
		memset( cMask, 0, 8 );
		iRtn = SRL_Reg_GetInfo( SRL_REG_KEY_MNGUSER, SRL_REG_USERMASK, (LPCTSTR)cMask );
		if( iRtn == -1 )
		{
			return( -1 );
		}
		if( memcmp(cMask, SRL_REG_MASK_OFF, sizeof(SRL_REG_MASK_OFF)) == 0 )
		{	
			iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGUSER, SRL_REG_USERMASK, SRL_REG_MASK_ON );
			break;
		}
		Sleep( 1000 );
	}

	//================================
	//  Get Reg info
	//================================
	iRtn = SRL_Reg_GetInfoBinary(SRL_REG_KEY_MNGUSER,SRL_REG_USERINFO,
                              (LPCTSTR)lpInfoUser,(DWORD)SRS_INFO_USER_COM_SZ );
	if( iRtn == -1 )
	{
		iRtn = 
		SRL_Reg_SetInfo( SRL_REG_KEY_MNGUSER, SRL_REG_USERMASK, SRL_REG_MASK_OFF );
		return( -1 );
	}
	wMaxUser = lpInfoUser->US_wMaxUser;
	
	for( iItem=0, wRegItem=0 ; wMaxUser+1 > wRegItem ; )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"),SRL_REG_USERITEM,wRegItem );
		iRtn = SRL_Reg_GetInfoBinary(SRL_REG_KEY_MNGUSER,(LPCTSTR)cRegName,
               (LPCTSTR)&(lpInfoUser->US_info_user[iItem]),(DWORD)SRS_USER_ITEM_SZ );
		if( iRtn == -1 )
		{
			iRtn = 
			SRL_Reg_SetInfo( SRL_REG_KEY_MNGUSER, SRL_REG_USERMASK, SRL_REG_MASK_OFF );
			return( -1 );
		}
		wRegItem++;
		iItem++;
	}
	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGUSER, SRL_REG_USERMASK, SRL_REG_MASK_OFF );

	//==============================================
	//  Read lobby information
	//==============================================
	for( ; ; )
	{
		memset( cMask, 0, 8 );
		iRtn = SRL_Reg_GetInfo( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYMASK, (LPCTSTR)cMask );
		if( iRtn == -1 )
		{
			return( -1 );
		}
		if( memcmp(cMask, SRL_REG_MASK_OFF, sizeof(SRL_REG_MASK_OFF)) == 0 ) 
		{	
			iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYMASK, SRL_REG_MASK_ON );
			break;
		}
		Sleep( 1000 );
	}

	//================================
	//  Get Reg info
	//================================
	iRtn = SRL_Reg_GetInfoBinary(SRL_REG_KEY_MNGLOBBY,SRL_REG_LOBBYINFO,
                              (LPCTSTR)lpInfoLobby,(DWORD)SRS_INFO_LOBBY_COM_SZ );
	if( iRtn == -1 )
	{
		iRtn = 
		SRL_Reg_SetInfo( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYMASK, SRL_REG_MASK_OFF );
		return( -1 );
	}
	wMaxLobby = lpInfoLobby->LB_wMaxLobby;
	
	for( iItem=0, wRegItem=0 ; wMaxLobby > wRegItem ; )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"),SRL_REG_LOBBYITEM,wRegItem );
		iRtn = SRL_Reg_GetInfoBinary(SRL_REG_KEY_MNGLOBBY,(LPCTSTR)cRegName,
               (LPCTSTR)&(lpInfoLobby->LB_info_lobby[iItem]),(DWORD)SRS_LOBBY_ITEM_SZ );
		if( iRtn == -1 )
		{
			iRtn = 
			SRL_Reg_SetInfo( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYMASK, SRL_REG_MASK_OFF );
			return( -1 );
		}
		wRegItem++;
		iItem++;
	}
	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYMASK, SRL_REG_MASK_OFF );

	//==============================================
	//  Read group information
	//==============================================
	for( ; ; )
	{
		memset( cMask, 0, 8 );
		iRtn = SRL_Reg_GetInfo( SRL_REG_KEY_MNGGROUP, SRL_REG_GROUPMASK, (LPCTSTR)cMask );
		if( iRtn == -1 )
		{
			return( -1 );
		}
		if( memcmp(cMask, SRL_REG_MASK_OFF, sizeof(SRL_REG_MASK_OFF)) == 0 ) 
		{	
			iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGROUP, SRL_REG_GROUPMASK, SRL_REG_MASK_ON );
			break;
		}
		Sleep( 1000 );
	}

	//================================
	//  Get Reg info
	//================================
	iRtn = SRL_Reg_GetInfoBinary(SRL_REG_KEY_MNGGROUP,SRL_REG_GROUPINFO,
                              (LPCTSTR)lpInfoGroup,(DWORD)SRS_INFO_GROUP_COM_SZ );
	if( iRtn == -1 )
	{
		iRtn = 
		SRL_Reg_SetInfo( SRL_REG_KEY_MNGGROUP, SRL_REG_GROUPMASK, SRL_REG_MASK_OFF );
		return( -1 );
	}
	wMaxGroup = lpInfoGroup->GP_wMaxGroup;
	
	for( iItem=0, wRegItem=0 ; wMaxGroup+1 > wRegItem ; )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"),SRL_REG_GROUPITEM,wRegItem );
		iRtn = SRL_Reg_GetInfoBinary(SRL_REG_KEY_MNGGROUP,(LPCTSTR)cRegName,
               (LPCTSTR)&(lpInfoGroup->GP_info_group[iItem]),(DWORD)SRS_GROUP_ITEM_SZ );
		if( iRtn == -1 )
		{
			iRtn = 
			SRL_Reg_SetInfo( SRL_REG_KEY_MNGGROUP, SRL_REG_GROUPMASK, SRL_REG_MASK_OFF );
			return( -1 );
		}
		wRegItem++;
		iItem++;
	}
	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGROUP, SRL_REG_GROUPMASK, SRL_REG_MASK_OFF );

	//==============================================
	//  read game information
	//==============================================
	for( ; ; )
	{
		memset( cMask, 0, 8 );
		iRtn = SRL_Reg_GetInfo( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEMASK, (LPCTSTR)cMask );
		if( iRtn == -1 )
		{
			return( -1 );
		}
		if( memcmp(cMask, SRL_REG_MASK_OFF, sizeof(SRL_REG_MASK_OFF)) == 0 )  
		{	
			iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEMASK, SRL_REG_MASK_ON );
			break;
		}
		Sleep( 1000 );
	}

	//================================
	//  Get Reg info
	//================================
	iRtn = SRL_Reg_GetInfoBinary(SRL_REG_KEY_MNGGAME,SRL_REG_GAMEINFO,
                              (LPCTSTR)lpInfoGame,(DWORD)SRS_INFO_GAME_COM_SZ );
	if( iRtn == -1 )
	{
		iRtn = 
		SRL_Reg_SetInfo( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEMASK, SRL_REG_MASK_OFF );
		return( -1 );
	}
	wMaxGame = lpInfoGame->GM_wMaxGame;
	
	for( iItem=0, wRegItem=0 ; wMaxGame+1 > wRegItem ; )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"),SRL_REG_GAMEITEM,wRegItem );
		iRtn = SRL_Reg_GetInfoBinary(SRL_REG_KEY_MNGGAME,(LPCTSTR)cRegName,
               (LPCTSTR)&(lpInfoGame->GM_info_game[iItem]),(DWORD)SRS_GAME_ITEM_SZ );
		if( iRtn == -1 )
		{
			iRtn = 
			SRL_Reg_SetInfo( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEMASK, SRL_REG_MASK_OFF );
			return( -1 );
		}
		wRegItem++;
		iItem++;
	}
	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEMASK, SRL_REG_MASK_OFF );

	return( 0 );
}

/*=============================================================================
     Function :SRL_Mng_PutInfo
     Input    :no
	 Output   :Write management data to Reg
	 Return   :True   0
	           False -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRL_Mng_PutInfo( void )
{
	int		iRtn;
	WORD	wItem;
	char	cRegName[32];
	unsigned char 	cMask[8];
	
	//==========================================
	//  Backup user info
	//==========================================
	for( ; ; )
	{
		memset( cMask, 0, 8 );
		iRtn = SRL_Reg_GetInfo( SRL_REG_KEY_MNGUSER, (LPCTSTR)SRL_REG_USERMASK, (LPCTSTR)cMask );
		if( iRtn == -1 )
		{
			return( -1 );
		}
		if(  memcmp( cMask, SRL_REG_MASK_OFF, sizeof(SRL_REG_MASK_OFF) ) == 0 )	
		{	
			iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGUSER, SRL_REG_USERMASK, SRL_REG_MASK_ON );
			break;
		}
		Sleep( 1000 );
	}

	LSP_Dbg_Printf(1, TEXT("Set user information\n" ));
	//
	//  Backup Management info 
	//
 	iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGUSER,SRL_REG_USERINFO,
                                  (LPCTSTR)lpInfoUser,(DWORD)SRS_INFO_USER_COM_SZ );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(0,TEXT("SRL_Mng_PutInfo : SRL_Reg_SetInfoBinary error %s %s \n"), 
                                                   SRL_REG_KEY_MNGUSER,SRL_REG_USERINFO );
		iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGUSER, SRL_REG_USERMASK, SRL_REG_MASK_OFF );
		return( -1 );
	}
	//
	//  Backup User info
	//
	for( wItem=0 ; lpInfoUser->US_wMaxUser+1 > wItem ; wItem++ )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"), SRL_REG_USERITEM, wItem );
		iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGUSER, (LPCTSTR)cRegName, 
                                  (LPCTSTR)&(lpInfoUser->US_info_user[wItem]), SRS_USER_ITEM_SZ );
	}
	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGUSER, SRL_REG_USERMASK, SRL_REG_MASK_OFF );
	
	//==============================================
	//  Backup lobby information
	//==============================================
	for( ; ; )
	{
		iRtn = SRL_Reg_GetInfo( SRL_REG_KEY_MNGLOBBY, (LPCTSTR)SRL_REG_LOBBYMASK, (LPCTSTR)cMask );
		if( iRtn == -1 )
		{
			return( -1 );
		}
		if(  memcmp(cMask,SRL_REG_MASK_OFF, sizeof(SRL_REG_MASK_OFF)) == 0 )
		{	
			iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYMASK, SRL_REG_MASK_ON );
			break;
		}
		Sleep( 1000 );
	}

	LSP_Dbg_Printf(1, TEXT("Set Lobby information\n" ));
	//
	//  Backup management information
	//
 	iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGLOBBY,SRL_REG_LOBBYINFO,
                                  (LPCTSTR)lpInfoLobby,(DWORD)SRS_INFO_LOBBY_COM_SZ );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(0,TEXT("SRL_Mng_PutInfo : SRL_Reg_SetInfoBinary error %s %s \n"), 
                                                   SRL_REG_KEY_MNGLOBBY,SRL_REG_LOBBYINFO );
		iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYMASK, SRL_REG_MASK_OFF );
		return( -1 );
	}
	
	//
	//  backup lobby info
	//
	for( wItem=0 ; lpInfoLobby->LB_wMaxLobby > wItem ; wItem++ )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"), SRL_REG_LOBBYITEM, wItem );
		iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGLOBBY, (LPCTSTR)cRegName, 
                             (LPCTSTR)&(lpInfoLobby->LB_info_lobby[wItem]), SRS_LOBBY_ITEM_SZ );
	}

	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGLOBBY, SRL_REG_LOBBYMASK, SRL_REG_MASK_OFF );

	//==============================================
	//  Get group info
	//==============================================
	for( ; ; )
	{
		iRtn = SRL_Reg_GetInfo( SRL_REG_KEY_MNGGROUP, (LPCTSTR)SRL_REG_GROUPMASK, (LPCTSTR)cMask );
		if( iRtn == -1 )
		{
			return( -1 );
		}
		if(  memcmp(cMask,SRL_REG_MASK_OFF, sizeof(SRL_REG_MASK_OFF)) == 0 )
		{	
			iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGROUP, SRL_REG_GROUPMASK, SRL_REG_MASK_ON );
			break;
		}
		Sleep( 1000 );
	}

	LSP_Dbg_Printf(1, TEXT("Set Group information\n" ));

	//
	//  Backup management info
	//
 	iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGGROUP,SRL_REG_GROUPINFO,
                                  (LPCTSTR)lpInfoGroup,(DWORD)SRS_INFO_GROUP_COM_SZ );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(0,TEXT("SRL_Mng_PutInfo : SRL_Reg_SetInfoBinary error %s %s \n"), 
                                                   SRL_REG_KEY_MNGGROUP,SRL_REG_GROUPINFO );
		iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGROUP, SRL_REG_GROUPMASK, SRL_REG_MASK_OFF );
		return( -1 );
	}
	//
	//  Backup group info
	//
	for( wItem=0 ; lpInfoGroup->GP_wMaxGroup+1 > wItem ; wItem++ )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"), SRL_REG_GROUPITEM, wItem );
		iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGGROUP, (LPCTSTR)cRegName, 
                             (LPCTSTR)&(lpInfoGroup->GP_info_group[wItem]), SRS_GROUP_ITEM_SZ );
	}

	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGROUP,SRL_REG_GROUPMASK,SRL_REG_MASK_OFF );

	//==============================================
	//  Backup Game info
	//==============================================
	for( ; ; )
	{
		iRtn = SRL_Reg_GetInfo( SRL_REG_KEY_MNGGAME, (LPCTSTR)SRL_REG_GAMEMASK, (LPCTSTR)cMask );
		if( iRtn == -1 )
		{
			return( -1 );
		}
		if(  memcmp(cMask,SRL_REG_MASK_OFF, sizeof(SRL_REG_MASK_OFF)) == 0 )
		{	
			iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEMASK, SRL_REG_MASK_ON );
			break;
		}
		Sleep( 1000 );
	}
	
	LSP_Dbg_Printf(1, TEXT("Set Game information\n" ));

	//
	//  Backup management info
	//
 	iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGGAME,SRL_REG_GAMEINFO,
                                  (LPCTSTR)lpInfoGame,(DWORD)SRS_INFO_GAME_COM_SZ );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf(0,TEXT("SRL_Mng_PutInfo : SRL_Reg_SetInfoBinary error %s %s \n"), 
                                                   SRL_REG_KEY_MNGGAME,SRL_REG_GAMEINFO );
		iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEMASK, SRL_REG_MASK_OFF );
		return( -1 );
	}
	//
	//  Backup game info
	//
	for( wItem=0 ; lpInfoGame->GM_wMaxGame+1 > wItem ; wItem++ )
	{
		memset( cRegName, 0, sizeof(cRegName) );
		wsprintf( (LPTSTR)cRegName, TEXT("%s%04d"), SRL_REG_GAMEITEM, wItem );
		iRtn = SRL_Reg_SetInfoBinary( SRL_REG_KEY_MNGGAME, (LPCTSTR)cRegName, 
                             (LPCTSTR)&(lpInfoGame->GM_info_game[wItem]), SRS_GAME_ITEM_SZ );
	}

	iRtn = SRL_Reg_SetInfo( SRL_REG_KEY_MNGGAME, SRL_REG_GAMEMASK, SRL_REG_MASK_OFF );
	
	return( 0 );
}

/*=============================================================================
     Function :SRL_Mng_Shutdown
     Input    :no
	 Output   :Free the connom area
	 Return   :True   0
	           False -1
=============================================================================*/
_declspec( dllexport )int __stdcall SRL_Mng_Shutdown( void )
{

//=====================
#ifdef MEMTEST
	int		*iadr;
	iadr = (int *)malloc(4000);
	SRL_Dbg_DebugPrintf(0,TEXT("**************** SRL_Mng_Shutdown : Start Get ADR=0X%X ******\n"), 
                                                 iadr);
	free(iadr);
#endif
//=====================

	iUserSize  = 0;
	iLobbySize = 0;
	iGroupSize = 0;
	iGameSize  = 0;


	if (lpInfoUser  != 0) 
	{
		free(lpInfoUser);
		lpInfoUser = 0;
	}
	if (lpInfoLobby  != 0) 
	{
		free(lpInfoLobby);
		lpInfoLobby = 0;
	}
	if (lpInfoGroup  != 0)
	{
		free(lpInfoGroup);
		lpInfoGroup = 0;
	}
	if (lpInfoGame  != 0) 
	{
		free(lpInfoGame);
		lpInfoGame = 0;
	}

//=====================
#ifdef MEMTEST
	iadr = (int *)malloc(4000);
	SRL_Dbg_DebugPrintf(0,TEXT("**************** SRL_Mng_Shutdown : Finished Get ADR=0X%X ******\n"), 
                                                 iadr);
	free(iadr);
#endif
//=====================
	return 0;
}
