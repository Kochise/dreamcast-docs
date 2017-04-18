/*==========================================================================;
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       spfuncs.h
 *	Content:	SP function prototypes
 *	History:
 *	Date		By		Reason
 *	====		==		======
 *	5/13/96		myronth	Created it
 *	10/30/96	myronth	Changed to DX5 Methods
 *	2/12/97		myronth	Mass DX5 changes
 *	3/12/97		myronth	Changed to DPlay3 methods
 *	3/17/97		myronth	Removed unnecessary Enum methods
 *	3/31/97		myronth	Added Send, Removed dead code
 *	4/10/97		myronth	Added GetCaps, GetPlayerCaps
 *	5/8/97		myronth	Subgroup support, GroupConnSettings, StartSession
 *	5/17/97		myronth	SendChatMessage prototype
 *	6/5/97		myronth	Added BuildParentalHeirarchy function prototype
 ***************************************************************************/
#ifndef __SPFUNCS_INCLUDED__
#define __SPFUNCS_INCLUDED__

#include <windows.h>


//--------------------------------------------------------------------------
//
//	Prototypes
//
//--------------------------------------------------------------------------

// dpldplay.c
extern HRESULT WINAPI SP_Shutdown(LPSPDATA_SHUTDOWN);

// spgroup.c
extern HRESULT WINAPI SP_AddGroupToGroup(LPSPDATA_ADDGROUPTOGROUP);
extern HRESULT WINAPI SP_AddPlayerToGroup(LPSPDATA_ADDPLAYERTOGROUP);
extern HRESULT WINAPI SP_BuildParentalHeirarchy(LPSPDATA_BUILDPARENTALHEIRARCHY);
extern HRESULT WINAPI SP_CreateGroup(LPSPDATA_CREATEGROUP);
extern HRESULT WINAPI SP_CreateGroupInGroup(LPSPDATA_CREATEGROUPINGROUP);
extern HRESULT WINAPI SP_DeleteGroupFromGroup(LPSPDATA_DELETEGROUPFROMGROUP);
extern HRESULT WINAPI SP_DeletePlayerFromGroup(LPSPDATA_DELETEPLAYERFROMGROUP);
extern HRESULT WINAPI SP_DestroyGroup(LPSPDATA_DESTROYGROUP);
extern HRESULT WINAPI SP_GetGroupConnectionSettings(LPSPDATA_GETGROUPCONNECTIONSETTINGS);
extern HRESULT WINAPI SP_GetGroupData(LPSPDATA_GETGROUPDATA);
extern HRESULT WINAPI SP_SetGroupConnectionSettings(LPSPDATA_SETGROUPCONNECTIONSETTINGS);
extern HRESULT WINAPI SP_SetGroupData(LPSPDATA_SETGROUPDATA);
extern HRESULT WINAPI SP_SetGroupName(LPSPDATA_SETGROUPNAME);
extern HRESULT WINAPI SP_StartSession(LPSPDATA_STARTSESSION);

// spplayer.c
extern HRESULT WINAPI SP_CreatePlayer(LPSPDATA_CREATEPLAYER);
extern HRESULT WINAPI SP_DestroyPlayer(LPSPDATA_DESTROYPLAYER);
extern HRESULT WINAPI SP_GetPlayerCaps(LPSPDATA_GETPLAYERCAPS);
extern HRESULT WINAPI SP_GetPlayerData(LPSPDATA_GETPLAYERDATA);
extern HRESULT WINAPI SP_Send(LPSPDATA_SEND);
extern HRESULT WINAPI SP_SendChatMessage(LPSPDATA_CHATMESSAGE);
extern HRESULT WINAPI SP_SetPlayerData(LPSPDATA_SETPLAYERDATA);
extern HRESULT WINAPI SP_SetPlayerName(LPSPDATA_SETPLAYERNAME);

// spsess.c
extern HRESULT WINAPI SP_Close(LPSPDATA_CLOSE);
extern HRESULT WINAPI SP_EnumSessions(LPSPDATA_ENUMSESSIONS);
extern HRESULT WINAPI SP_GetCaps(LPSPDATA_GETCAPS);
extern HRESULT WINAPI SP_Open(LPSPDATA_OPEN);

#endif // __SPFUNCS_INCLUDED__

