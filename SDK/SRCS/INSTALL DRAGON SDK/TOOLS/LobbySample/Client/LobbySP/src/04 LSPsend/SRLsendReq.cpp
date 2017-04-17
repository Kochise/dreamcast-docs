/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File: SRLsendReq
 *			    SRL_Snd_UserEntry
 *				SRL_Snd_UserDelete
 *				SRL_Snd_UserDelete
 *				SRL_Snd_LobbyEntry
 *				SRL_Snd_LobbyDefect
 *				SRL_Snd_GroupMake
 *				SRL_Snd_GroupJoin
 *				SRL_Snd_GroupDefect
 *				SRL_Snd_GameStart
 *				SRL_Snd_GameJoin
 *				SRL_Snd_GameDefect
 *				SRL_Snd_GameEnd
 *				SRL_Snd_SaveInfo
 *				SRL_Snd_AllGet
 *				SRL_Snd_Message
 *
 *
 ***************************************************************************/
#include <windows.h>
#include <stdio.h>

#include "SRScom.h"
#include "LSPdebug.h"
#include "SRLsend.h"

/*=============================================================================
     Function : SRL_Snd_UserEntry
     Input    : lpServerIP  
			    iPort       
                lpClientName
                lpUserName  
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_UserEntry( char *lpServerIP, int iPort, LPCTSTR lpClientName, LPCTSTR lpUserName )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_USER_ENTRY *lpIfUserEntry;
	char	cIfFix[256];

	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("#### SRL_Snd_UserEntry : Start User logon client = %s user = %s \n"), 
				lpClientName, lpUserName );
	memset( cIfFix, 0, sizeof(cIfFix) );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_USER_ENTRY;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_USER_ENTRY_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfUserEntry = (struct SRS_IF_USER_ENTRY *)lpIfFix->IF_cInformation;
	memset( lpIfUserEntry->IF_UE_cClientName, 0, SRS_MAX_NAME_CLIENT );
	memcpy( lpIfUserEntry->IF_UE_cClientName, lpClientName, SRS_MAX_NAME_CLIENT );
	memset( lpIfUserEntry->IF_UE_cUserName, 0, SRS_MAX_NAME_USER );
	memcpy( lpIfUserEntry->IF_UE_cUserName, lpUserName, SRS_MAX_NAME_USER );	

//	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_UserEntry : User logon client = %s user = %s \n"), 
//				lpIfUserEntry->IF_UE_cClientName, lpIfUserEntry->IF_UE_cUserName );

	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_USER_ENTRY_SZ);
	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_UserEntry : SRL_Snd_Request sendSize=%d\n"), 
				szSendSize );
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_UserDelete
     Input    : lpServerIP  
			    iPort     
                wUserID
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_UserDelete( char *lpServerIP, int iPort, WORD wUserID )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_USER_DELETE *lpIfUserDelete;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_USER_DELETE;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_USER_DELETE_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfUserDelete = (struct SRS_IF_USER_DELETE *)lpIfFix->IF_cInformation;
	lpIfUserDelete->IF_UD_wUserID = wUserID;	

	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_UserDelete : User delete userID = %d port =%d \n"), 
					wUserID ,iPort);

	szSendSize = (size_t)SRS_IF_FIX_SZ + SRS_IF_USER_DELETE_SZ;
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_LobbyEntry
     Input    : lpServerIP 
			    iPort       
                wUserID     
                wLobbyID    
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_LobbyEntry( char *lpServerIP, int iPort, WORD wUserID, WORD wLobbyID )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_LOBBY_ENTRY *lpIfLobbyEntry;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_LOBBY_ENTRY;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_LOBBY_ENTRY_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfLobbyEntry = (struct SRS_IF_LOBBY_ENTRY *)lpIfFix->IF_cInformation;
	lpIfLobbyEntry->IF_LE_wUserID = wUserID;	
	lpIfLobbyEntry->IF_LE_wLobbyID = wLobbyID;	

	szSendSize = (size_t)SRS_IF_FIX_SZ + SRS_IF_LOBBY_ENTRY_SZ;
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_LobbyDefect
     Input    : lpServerIP
			    iPort    
                wUserID  
                wLobbyID 
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_LobbyDefect( char *lpServerIP, int iPort, WORD wUserID, WORD wLobbyID )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_LOBBY_DEFECT *lpIfLobbyDefect;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_LOBBY_DEFECT;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_LOBBY_DEFECT_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfLobbyDefect = (struct SRS_IF_LOBBY_DEFECT *)lpIfFix->IF_cInformation;
	lpIfLobbyDefect->IF_LD_wUserID = wUserID;	
	lpIfLobbyDefect->IF_LD_wLobbyID = wLobbyID;	

	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_LobbyDefect : leave lobby userID = %d, lobbyID = %d \n"), wUserID,wLobbyID );

	szSendSize = (size_t)SRS_IF_FIX_SZ + SRS_IF_LOBBY_DEFECT_SZ;
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_GroupMake
     Input    : lpServerIP  
			    iPort       
                wUserID     
                lpGroupName 
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_GroupMake( char *lpServerIP, int iPort, WORD wUserID, LPCTSTR lpGroupName )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_GROUP_MAKE *lpIfGroupMake;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_GROUP_MAKE;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_GROUP_MAKE_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfGroupMake = (struct SRS_IF_GROUP_MAKE *)lpIfFix->IF_cInformation;
	lpIfGroupMake->IF_GM_wUserID = wUserID;			
	memcpy( lpIfGroupMake->IF_GM_cGroupName, lpGroupName, SRS_MAX_NAME_GROUP );

	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_GroupMake : Create group userID = %d, Group = %s \n"), wUserID,lpIfGroupMake->IF_GM_cGroupName );

	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_GROUP_MAKE_SZ );
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_GroupJoin
     Input    : lpServerIP  
			    iPort       
                wUserID     
                wGroupID    
			    wCondition  
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_GroupJoin( char *lpServerIP, int iPort, WORD wUserID, WORD wGroupID, WORD wCondition )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_GROUP_JOIN *lpIfGroupJoin;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_GROUP_JOIN;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_GAME_JOIN_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfGroupJoin = (struct SRS_IF_GROUP_JOIN *)lpIfFix->IF_cInformation;
	lpIfGroupJoin->IF_GJ_wUserID = wUserID;			
	lpIfGroupJoin->IF_GJ_wGroupID = wGroupID;		
	lpIfGroupJoin->IF_GJ_wCondition = wCondition;	

	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_GroupJoin : Enter group userID = %d, GroupID = %d \n"), wUserID, wGroupID );

	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_GAME_JOIN_SZ );
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_GroupDefect
     Input    : lpServerIP  
			    iPort       
                wUserID     
                wGroupID    
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_GroupDefect( char *lpServerIP, int iPort, WORD wUserID, WORD wGroupID )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_GROUP_DEFECT *lpIfGroupDefect;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_GROUP_DEFECT;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_GROUP_DEFECT_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfGroupDefect = (struct SRS_IF_GROUP_DEFECT *)lpIfFix->IF_cInformation;
	lpIfGroupDefect->IF_GD_wUserID = wUserID;	
	lpIfGroupDefect->IF_GD_wGroupID = wGroupID;	

	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_GroupDefect : Leave group userID = %d, GroupID = %d \n"), wUserID, wGroupID );

	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_GROUP_DEFECT_SZ );
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_GameStart
     Input    : lpServerIP  
			    iPort       
                wUserID     
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_GameStart( char *lpServerIP, int iPort, WORD wUserID )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_GAME_START *lpIfGameStart;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_GAME_START;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_GAME_START_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfGameStart = (struct SRS_IF_GAME_START *)lpIfFix->IF_cInformation;
	lpIfGameStart->IF_GS_wUserID = wUserID;	

	szSendSize = (size_t)SRS_IF_FIX_SZ + SRS_IF_GAME_START_SZ;
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_GameEnd
     Input    : lpServerIP  
			    iPort       
                wUserID     
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_GameEnd( char *lpServerIP, int iPort, WORD wUserID )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_GAME_END *lpIfGameEnd;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_GAME_END;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_GAME_END_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfGameEnd = (struct SRS_IF_GAME_END *)lpIfFix->IF_cInformation;
	lpIfGameEnd->IF_GE_wUserID = wUserID;

	szSendSize = (size_t)SRS_IF_FIX_SZ + SRS_IF_GAME_END_SZ;
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_GameJoin
     Input    : lpServerIP 
			    iPort      
                wUserID    
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_GameJoin( char *lpServerIP, int iPort, WORD wUserID )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_GAME_JOIN *lpIfGameJoin;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_GAME_JOIN;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_GAME_JOIN_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfGameJoin = (struct SRS_IF_GAME_JOIN *)lpIfFix->IF_cInformation;
	lpIfGameJoin->IF_GJ_wUserID = wUserID;	

	szSendSize = (size_t)SRS_IF_FIX_SZ + SRS_IF_GAME_JOIN_SZ;
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_GameDefect
     Input    : lpServerIP  
			    iPort       
                wUserID     
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_GameDefect( char *lpServerIP, int iPort, WORD wUserID )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_GAME_DEFECT *lpIfGameDefect;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_GAME_DEFECT;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_GAME_DEFECT_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfGameDefect = (struct SRS_IF_GAME_DEFECT *)lpIfFix->IF_cInformation;
	lpIfGameDefect->IF_GD_wUserID = wUserID;

	szSendSize = (size_t)SRS_IF_FIX_SZ + SRS_IF_GAME_DEFECT_SZ;
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_Message
     Input    : lpServerIP  
			    iPort       
			    wUserID     
			    wMessageCode
                lpMessage   
     Output   : no
     Return   : True   0
                False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_Message( char *lpServerIP, int iPort, WORD wUserID, WORD wMessageCode, LPCTSTR lpMessage )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_MESSAGE *lpIfMessage;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_SENDMSG;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_MESSAGE_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfMessage = (struct SRS_IF_MESSAGE *)lpIfFix->IF_cInformation;
	lpIfMessage->IF_MS_wUserID = wUserID;	
	lpIfMessage->IF_MS_wMessageCode = wMessageCode;
	memset( lpIfMessage->IF_MS_cMessage, 0, SRS_MAX_MESSAGE );
	memcpy( lpIfMessage->IF_MS_cMessage, lpMessage, SRS_MAX_MESSAGE );

	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_MESSAGE_SZ );
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_AllGet
     Input    : lpServerIP
			    iPort    
     Output   : no
     Return   : True   0
                False -1
==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_AllGet( char *lpServerIP, int iPort )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_ALL;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = 0;
	lpIfFix->IF_iPortNo = iPort;

	szSendSize = (size_t)SRS_IF_FIX_SZ;
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}

/*=============================================================================
     Function : SRL_Snd_SaveInfo
     Input    : lpServerIP 
			    iPort      
			    wUserID    
                lpSaveInfo 
     Output   : ‚È‚µ
     Return   : True   0
                False -1
==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_SaveInfo( char *lpServerIP, int iPort, WORD wUserID, LPCTSTR lpSaveInfo )
{
	int		iRtn;
	size_t	szSendSize;
	struct	SRS_IF_FIX *lpIfFix;
	struct	SRS_IF_SAVE_INFO *lpIfSaveInfo;
	char	cIfFix[256];

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = IF_REQ_SAVE_INFO;
	lpIfFix->IF_wResult = 0;
	lpIfFix->IF_iInformationSize = SRS_IF_SAVE_INFO_SZ;
	lpIfFix->IF_iPortNo = iPort;

	lpIfSaveInfo = (struct SRS_IF_SAVE_INFO *)lpIfFix->IF_cInformation;
	lpIfSaveInfo->IF_SI_wUserID = wUserID;
	memcpy( lpIfSaveInfo->IF_SI_cInfo, lpSaveInfo, SRS_MAX_USERAREA );

	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_SAVE_INFO_SZ );
	iRtn = SRL_Snd_Request( lpServerIP, iPort, cIfFix, szSendSize );
	return( iRtn );
}
