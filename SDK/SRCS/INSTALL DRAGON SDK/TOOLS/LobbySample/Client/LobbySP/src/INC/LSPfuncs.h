/*==========================================================================;
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       LSPfuncs.h
 *	Content:	LOBBY-SP Callback function prototypes
 *	History:
 *	1999/09/02	Created it
 *           10/06      Update ( Add MakeList Function prototypes)
 *=========================================================================*/
#ifndef __LSPFUNCS_INCLUDED__
#define __LSPFUNCS_INCLUDED__

#include <windows.h>
#include "LSPlobby.h"


//--------------------------------------------------------------------------
//
//	Prototypes
//
//--------------------------------------------------------------------------

// LSPdplay.c
HRESULT WINAPI LP_Shutdown(LPSPDATA_SHUTDOWN);

// LSPgroup.c
HRESULT WINAPI LP_AddGroupToGroup(LPSPDATA_ADDGROUPTOGROUP);
HRESULT WINAPI LP_AddPlayerToGroup(LPSPDATA_ADDPLAYERTOGROUP);
HRESULT WINAPI LP_BuildParentalHeirarchy(LPSPDATA_BUILDPARENTALHEIRARCHY);
HRESULT WINAPI LP_CreateGroup(LPSPDATA_CREATEGROUP);
HRESULT WINAPI LP_CreateGroupInGroup(LPSPDATA_CREATEGROUPINGROUP);
HRESULT WINAPI LP_DeleteGroupFromGroup(LPSPDATA_DELETEGROUPFROMGROUP);
HRESULT WINAPI LP_DeletePlayerFromGroup(LPSPDATA_DELETEPLAYERFROMGROUP);
HRESULT WINAPI LP_DestroyGroup(LPSPDATA_DESTROYGROUP);
HRESULT WINAPI LP_GetGroupConnectionSettings(LPSPDATA_GETGROUPCONNECTIONSETTINGS);
HRESULT WINAPI LP_GetGroupData(LPSPDATA_GETGROUPDATA);
HRESULT WINAPI LP_SetGroupConnectionSettings(LPSPDATA_SETGROUPCONNECTIONSETTINGS);
HRESULT WINAPI LP_SetGroupData(LPSPDATA_SETGROUPDATA);
HRESULT WINAPI LP_SetGroupName(LPSPDATA_SETGROUPNAME);

// LSPplayer.c
HRESULT WINAPI LP_CreatePlayer(LPSPDATA_CREATEPLAYER);
HRESULT WINAPI LP_DestroyPlayer(LPSPDATA_DESTROYPLAYER);
HRESULT WINAPI LP_GetPlayerCaps(LPSPDATA_GETPLAYERCAPS);
HRESULT WINAPI LP_GetPlayerData(LPSPDATA_GETPLAYERDATA);
HRESULT WINAPI LP_Send(LPSPDATA_SEND);
HRESULT WINAPI LP_SendChatMessage(LPSPDATA_CHATMESSAGE);
HRESULT WINAPI LP_SetPlayerData(LPSPDATA_SETPLAYERDATA);
HRESULT WINAPI LP_SetPlayerName(LPSPDATA_SETPLAYERNAME);

// LSPsession.c
HRESULT WINAPI LP_Open(LPSPDATA_OPEN);
HRESULT WINAPI LP_Close(LPSPDATA_CLOSE);
HRESULT WINAPI LP_StartSession(LPSPDATA_STARTSESSION);
HRESULT WINAPI LP_EnumSessions(LPSPDATA_ENUMSESSIONS);
HRESULT WINAPI LP_GetCaps(LPSPDATA_GETCAPS);

// LSPmakelist.c
__declspec( dllexport )int __stdcall LSP_MK_PlayerList( LPSRS_INFOUSER lpInfoUser, LPLSP_PLAYERDATA lpPlayerData, DWORD dwPlayerID );
__declspec( dllexport )int __stdcall LSP_MK_GroupList( LPSRS_INFOGROUP lpInfoGroup, LPLSP_GROUPDATA lpGroupData, DWORD dwGroupID );

#endif // __LSPFUNCS_INCLUDED__

