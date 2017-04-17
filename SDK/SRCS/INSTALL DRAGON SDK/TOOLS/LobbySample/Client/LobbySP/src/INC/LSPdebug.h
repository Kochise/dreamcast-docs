/*==========================================================================;
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       LSPdebug.h
 *	Content:	LOBBY-SP Debug function prototypes & defined
 *	History:
 *	1999/09/02	Created it
 *=========================================================================*/
#ifndef __LSPDEBUG_INCLUDED__
#define __LSPDEBUG_INCLUDED__

#include <windows.h>
#include "winsock.h"
#include "winuser.h"

#undef  SW_HIDE
#define SW_HIDE 0

#undef  STARTF_USESHOWWINDOW
#define STARTF_USESHOWWINDOW 1

#undef  WM_COMMAND
#define WM_COMMAND WM_USER+10

//==========================================================================
//
//	Prototypes
//
//==========================================================================
__declspec( dllexport )void __stdcall LSP_Dbg_Printf(int iLevel, IN PTCHAR pszFormat,...);

//==========================================================================
//
//	Debug Level Defined 
//
//==========================================================================
#define DBG_LEVEL_0		0		// Error Message
#define DBG_LEVEL_1		1		// Entry Message
#define DBG_LEVEL_2		2  		// Debug Message
#define DBG_LEVEL_3		3		// Debug Message(details)

//==========================================================================
//
//	Server Access functions Character Defined
//
//==========================================================================
#define DBG_NAME_DPLSPINIT					TEXT("DPLSPInit")
#define DBG_NAME_SHUTDOWN 					TEXT("LP_Shutdown")
// セション系
#define DBG_NAME_OPEN						TEXT("SRL_Open")
#define DBG_NAME_CLOSE						TEXT("SRL_Close")
#define DBG_NAME_GETCAPS					TEXT("SRL_GetCaps")
#define DBG_NAME_ENUMSESSIONS				TEXT("SRL_EnumSessions")

// プレイヤ操作系
#define DBG_NAME_CREATEPLAYER				TEXT("SRL_CreatePlayer")
#define DBG_NAME_DESTROYPLAYER				TEXT("SRL_DestroyPlayer")
#define DBG_NAME_GETPLAYERCAPS				TEXT("SRL_GetPlayerCaps")
#define DBG_NAME_GETPLAYERDATA				TEXT("SRL_GetPlayerData")
#define DBG_NAME_SETPLAYERDATA				TEXT("SRL_SetPlayerData")
#define DBG_NAME_SETPLAYERNAME				TEXT("SRL_SetPlayerName")

// グループ操作系
#define DBG_NAME_CREATEGROUP 				TEXT("SRL_CreateGroup")
#define DBG_NAME_DESTROYGROUP 				TEXT("SRL_DestroyGroup")
#define DBG_NAME_ADDPLAYERTOGROUP 			TEXT("SRL_AddPlayerToGroup")
#define DBG_NAME_DELETEPLAYERFROMGROUP 		TEXT("SRL_DeletePlayerFromGroup")
#define DBG_NAME_CREATEGROUPINGROUP 		TEXT("SRL_CreateGroupInGroup")
#define DBG_NAME_DELETEGROUPFROMGROUP	 	TEXT("SRL_DeleteGroupFromGroup")
#define DBG_NAME_ADDGROUPTOGROUP 			TEXT("SRL_AddGroupToGroup")

#define DBG_NAME_GETGROUPCONNECTIONSETTINGS TEXT("SRL_GetGroupConnectionSettings")
#define DBG_NAME_SETGROUPCONNECTIONSETTINGS TEXT("SRL_SetGroupConnectionSettings")
#define DBG_NAME_GETGROUPDATA	 			TEXT("SRL_GetGroupData")
#define DBG_NAME_SETGROUPDATA 				TEXT("SRL_SetGroupData")
#define DBG_NAME_SETGROUPNAME 				TEXT("SRL_SetGroupName")
#define DBG_NAME_STARTSESSION 				TEXT("SRL_StartSession")
#define DBG_NAME_BUILDPARENTALHEIRARCHY		TEXT("SRL_BuildParentalHeirarchy")

// メッセージ送信
#define DBG_NAME_SEND						TEXT("SRL_Send")
#define DBG_NAME_SENDCHATMESSAGE			TEXT("SRL_SendChatMessage")


#endif // __LSPDEBUG_INCLUDED__

