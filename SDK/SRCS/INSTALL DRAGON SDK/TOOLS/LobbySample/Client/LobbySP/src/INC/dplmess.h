/*==========================================================================;
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       dplmess.h
 *	Content:	DPLobby messages header file
 *	History:
 *	Date		By		Reason
 *	====		==		======
 *	5/15/96		myronth	Created it
 *	11/20/96	myronth	Implemented Logon/LogoffServer
 *	2/12/97		myronth	Mass DX5 changes
 *	2/18/97		myronth	Implemented GetObjectCaps
 *	3/17/97		myronth	Create/DestroyGroup/Player
 *	3/20/97		myronth	AddPlayerToGroup, DeletePlayerFromGroup
 *	3/21/97		myronth	SetGroup/PlayerName, Get/SetGroup/PlayerData
 *	3/31/97		myronth	Send, AddPlayerToGroupWithNames, CreateGroupWithID,
 *						Removed dead code
 *	4/4/97		myronth	Changed format of all server-pushed messages to
 *						include the word "Remote" and include PlayerTo
 *	5/8/97		myronth	Subgroup support, GroupConnSettings, StartSession
 *	5/17/97		myronth	Added Chat message structure
 *	5/22/97		myronth	Added MSG_GENERALRESPONSEDATA struct and response
 *						messages for Delete's, Destroy's, and Set's
 *	5/23/97		myronth	Removed dwPlayerTo from messages
 *	6/3/97		myronth	Added dwPlayerFlags to MSG_ADDREMOTEPLAYERTOGROUPDATA
 *	6/5/97		myronth	Added dwGroupFlags and dwAnchorID to MSG_ADDREMOTE-
 *						GROUPTOGROUP, Added MSG_BUILDPARENTALHEIRARCHY
 ***************************************************************************/
#ifndef __DPLMESS_INCLUDED__
#define __DPLMESS_INCLUDED__

#include <windows.h>


//--------------------------------------------------------------------------
//
//	Definitions
//
//--------------------------------------------------------------------------

// {CFF8A100-AE8F-11cf-A024-00AA006157AC}
DEFINE_GUID(GUID_DirectPlayLobby, 0xcff8a100, 0xae8f, 0x11cf, 0xa0, 0x24, 0x0, 0xaa, 0x0, 0x61, 0x57, 0xac);

#define SZ_LobbyServerPlayerName	TEXT("LobbyServerPlayer#####")

//--------------------------------------------------------------------------
//
//	Message Codes
//
//--------------------------------------------------------------------------
#define MSG_CREATEGROUP					0x01
#define MSG_CREATEGROUPRESPONSE			0x02
#define MSG_ENUMGROUPS					0x03
#define MSG_ENUMGROUPSRESPONSE			0x04
#define MSG_CREATEPLAYER				0x05
#define MSG_CREATEPLAYERRESPONSE		0x06
#define MSG_DESTROYGROUP				0x07
#define MSG_DESTROYPLAYER				0x08
#define MSG_ADDPLAYERTOGROUP			0x09
#define MSG_ADDPLAYERTOGROUPRESPONSE	0x10
#define MSG_DELETEPLAYERFROMGROUP		0x11
#define MSG_SETGROUPNAME				0x12
#define MSG_SETPLAYERNAME				0x13
#define MSG_SETGROUPDATA				0x14
#define MSG_SETPLAYERDATA				0x15
#define MSG_GETGROUPDATA				0x16
#define MSG_GETGROUPDATARESPONSE		0x17
#define MSG_GETPLAYERDATA				0x18
#define MSG_GETPLAYERDATARESPONSE		0x19
#define MSG_SEND						0x20
#define MSG_ADDGROUPTOGROUP				0x21
#define MSG_ADDGROUPTOGROUPRESPONSE		0x22
#define MSG_CREATEGROUPINGROUP			0x23
#define MSG_CREATEGROUPINGROUPRESPONSE	0x24
#define MSG_DELETEGROUPFROMGROUP		0x25

#define MSG_ADDREMOTEPLAYERTOGROUP		0x30
#define MSG_CREATEREMOTEGROUP			0x31
#define MSG_DELETEREMOTEPLAYERFROMGROUP	0x32
#define MSG_DESTROYREMOTEGROUP			0x33
#define MSG_SETREMOTEGROUPNAME			0x34
#define MSG_SETREMOTEPLAYERNAME			0x35
#define MSG_ADDREMOTEGROUPTOGROUP		0x36
#define MSG_CREATEREMOTEGROUPINGROUP	0x37
#define MSG_DELETEREMOTEGROUPFROMGROUP	0x38
#define MSG_GETGROUPCONNECTIONSETTINGS	0x39
#define MSG_GETGROUPCONNECTIONSETTINGSRESPONSE	0x40
#define MSG_SETGROUPCONNECTIONSETTINGS	0x41
#define MSG_STARTSESSION				0x42
#define MSG_STARTSESSIONCOMMAND			0x43
#define MSG_SENDCHATMESSAGE				0x44
#define MSG_DESTROYGROUPRESPONSE		0x45
#define MSG_DESTROYPLAYERRESPONSE		0x46
#define MSG_DELETEPLAYERFROMGROUPRESPONSE		0x47
#define MSG_DELETEGROUPFROMGROUPRESPONSE		0x48
#define MSG_SETGROUPCONNECTIONSETTINGSRESPONSE	0x49
#define MSG_SETGROUPDATARESPONSE		0x50
#define MSG_SETGROUPNAMERESPONSE		0x51
#define MSG_SETPLAYERDATARESPONSE		0x52
#define MSG_SETPLAYERNAMERESPONSE		0x53
#define MSG_STARTSESSIONRESPONSE		0x54
#define MSG_BUILDPARENTALHEIRARCHY		0x55
#define MSG_BUILDPARENTALHEIRARCHYRESPONSE		0x56

//--------------------------------------------------------------------------
//
//	Message Structures
//
//--------------------------------------------------------------------------
typedef struct MSG_GENERALDATA
{
	DWORD			msg;
} MSG_GENERALDATA, * LPMSG_GENERALDATA;

typedef struct MSG_GENERALRESPONSEDATA
{
	DWORD			msg;
	HRESULT			hr;
} MSG_GENERALRESPONSEDATA, * LPMSG_GENERALRESPONSEDATA;

// AddPlayerToGroup, AddGroupToGroup
typedef struct MSG_ADDGROUPTOGROUPDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwParentID;
	DWORD			dwGroupID;
} MSG_ADDGROUPTOGROUPDATA, * LPMSG_ADDGROUPTOGROUPDATA;

typedef struct MSG_ADDPLAYERTOGROUPDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwGroupID;
	DWORD			dwPlayerID;
} MSG_ADDPLAYERTOGROUPDATA, * LPMSG_ADDPLAYERTOGROUPDATA;

typedef struct MSG_ADDREMOTEGROUPTOGROUPDATA
{
	DWORD			msg;
	DWORD			dwTotalSize;
	DWORD			dwAnchorID;
	DWORD			dwGroupID;
	DWORD			dwParentID;
	DWORD			dwGroupFlags;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
} MSG_ADDREMOTEGROUPTOGROUPDATA, * LPMSG_ADDREMOTEGROUPTOGROUPDATA;

typedef struct MSG_ADDREMOTEPLAYERTOGROUPDATA
{
	DWORD			msg;
	DWORD			dwTotalSize;
	DWORD			dwGroupID;
	DWORD			dwPlayerID;
	DWORD			dwPlayerFlags;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
} MSG_ADDREMOTEPLAYERTOGROUPDATA, * LPMSG_ADDREMOTEPLAYERTOGROUPDATA;

// BuildParentalHeirarchy
typedef struct MSG_BUILDPARENTALHEIRARCHYDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwGroupID;
	DWORD			dwMessage;
	DWORD			dwParentID;
} MSG_BUILDPARENTALHEIRARCHYDATA, * LPMSG_BUILDPARENTALHEIRARCHYDATA;

// CreateGroup
typedef struct MSG_CREATEGROUPDATA
{
	DWORD			msg;
	DWORD			dwFlags;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwDataSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
	DWORD			dwDataOffset;
} MSG_CREATEGROUPDATA, * LPMSG_CREATEGROUPDATA;

typedef struct MSG_CREATEGROUPRESPONSEDATA
{
	DWORD			msg;
	DWORD			dwGroupID;
	HRESULT			hr;
} MSG_CREATEGROUPRESPONSEDATA, * LPMSG_CREATEGROUPRESPONSEDATA;

typedef struct MSG_CREATEGROUPINGROUPDATA
{
	DWORD			msg;
	DWORD			dwFlags;
	DWORD			dwParentID;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwDataSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
	DWORD			dwDataOffset;
} MSG_CREATEGROUPINGROUPDATA, * LPMSG_CREATEGROUPINGROUPDATA;

typedef struct MSG_CREATEGROUPINGROUPRESPONSEDATA
{
	DWORD			msg;
	DWORD			dwGroupID;
	HRESULT			hr;
} MSG_CREATEGROUPINGROUPRESPONSEDATA, * LPMSG_CREATEGROUPINGROUPRESPONSEDATA;

typedef struct MSG_CREATEREMOTEGROUPDATA
{
	DWORD			msg;
	DWORD			dwFlags;
	DWORD			dwGroupID;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwDataSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
	DWORD			dwDataOffset;
} MSG_CREATEREMOTEGROUPDATA, * LPMSG_CREATEREMOTEGROUPDATA;

typedef struct MSG_CREATEREMOTEGROUPINGROUPDATA
{
	DWORD			msg;
	DWORD			dwFlags;
	DWORD			dwParentID;
	DWORD			dwGroupID;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwDataSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
	DWORD			dwDataOffset;
} MSG_CREATEREMOTEGROUPINGROUPDATA, * LPMSG_CREATEREMOTEGROUPINGROUPDATA;

// CreatePlayer
typedef struct MSG_CREATEPLAYERDATA
{
	DWORD			msg;
	DWORD			dwFlags;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwDataSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
	DWORD			dwDataOffset;
} MSG_CREATEPLAYERDATA, * LPMSG_CREATEPLAYERDATA;

typedef struct MSG_CREATEPLAYERRESPONSEDATA
{
	DWORD			msg;
	DWORD			dwPlayerID;
	HRESULT			hr;
} MSG_CREATEPLAYERRESPONSEDATA, * LPMSG_CREATEPLAYERRESPONSEDATA;

// DeleteGroupFromGroup
typedef struct MSG_DELETEGROUPFROMGROUPDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwParentID;
	DWORD			dwGroupID;
} MSG_DELETEGROUPFROMGROUPDATA, * LPMSG_DELETEGROUPFROMGROUPDATA;

typedef struct MSG_DELETEREMOTEGROUPFROMGROUPDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwParentID;
	DWORD			dwGroupID;
} MSG_DELETEREMOTEGROUPFROMGROUPDATA, * LPMSG_DELETEREMOTEGROUPFROMGROUPDATA;

// DeletePlayerFromGroup
typedef struct MSG_DELETEPLAYERFROMGROUPDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwGroupID;
	DWORD			dwPlayerID;
} MSG_DELETEPLAYERFROMGROUPDATA, * LPMSG_DELETEPLAYERFROMGROUPDATA;

typedef struct MSG_DELETEREMOTEPLAYERFROMGROUPDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwGroupID;
	DWORD			dwPlayerID;
} MSG_DELETEREMOTEPLAYERFROMGROUPDATA, * LPMSG_DELETEREMOTEPLAYERFROMGROUPDATA;

// DestroyGroup
typedef struct MSG_DESTROYGROUPDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwGroupID;
} MSG_DESTROYGROUPDATA, * LPMSG_DESTROYGROUPDATA;

typedef struct MSG_DESTROYREMOTEGROUPDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwGroupID;
} MSG_DESTROYREMOTEGROUPDATA, * LPMSG_DESTROYREMOTEGROUPDATA;

// DestroyPlayer
typedef struct MSG_DESTROYPLAYERDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwPlayerID;
} MSG_DESTROYPLAYERDATA, * LPMSG_DESTROYPLAYERDATA;

// GetGroupConnectionSettings
typedef struct MSG_GETGROUPCONNECTIONSETTINGSDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwGroupID;
	DWORD			dwBufferSize;
} MSG_GETGROUPCONNECTIONSETTINGSDATA, * LPMSG_GETGROUPCONNECTIONSETTINGSDATA;

typedef struct MSG_GETGROUPCONNECTIONSETTINGSRESPONSEDATA
{
	DWORD			msg;
	HRESULT			hr;
	DWORD			dwSize;
	DWORD			dwConnOffset;
} MSG_GETGROUPCONNECTIONSETTINGSRESPONSEDATA, * LPMSG_GETGROUPCONNECTIONSETTINGSRESPONSEDATA;

// GetGroupData
typedef struct MSG_GETGROUPDATADATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwGroupID;
	DWORD			dwDataSize;
} MSG_GETGROUPDATADATA, * LPMSG_GETGROUPDATADATA;

typedef struct MSG_GETGROUPDATARESPONSEDATA
{
	DWORD			msg;
	HRESULT			hr;
	DWORD			dwTotalSize;
	DWORD			dwDataSize;
	DWORD			dwDataOffset;
} MSG_GETGROUPDATARESPONSEDATA, * LPMSG_GETGROUPDATARESPONSEDATA;

// GetPlayerData
typedef struct MSG_GETPLAYERDATADATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwPlayerID;
	DWORD			dwDataSize;
} MSG_GETPLAYERDATADATA, * LPMSG_GETPLAYERDATADATA;

typedef struct MSG_GETPLAYERDATARESPONSEDATA
{
	DWORD			msg;
	HRESULT			hr;
	DWORD			dwTotalSize;
	DWORD			dwDataSize;
	DWORD			dwDataOffset;
} MSG_GETPLAYERDATARESPONSEDATA, * LPMSG_GETPLAYERDATARESPONSEDATA;

// Send
typedef struct MSG_SENDDATA
{
	DWORD			msg;
	DWORD			dwFromID;
	DWORD			dwToID;
	DWORD			dwBufferSize;
	DWORD			dwBufferOffset;
} MSG_SENDDATA, * LPMSG_SENDDATA;

// SendChatMessage
typedef struct MSG_SENDCHATMESSAGEDATA
{
	DWORD			msg;
	DWORD			dwFromID;
	DWORD			dwToID;
	DWORD			dwFlags;
	DWORD			dwMessageOffset;
} MSG_SENDCHATMESSAGEDATA, * LPMSG_SENDCHATMESSAGEDATA;

// SetGroupConnectionSettings
typedef struct MSG_SETGROUPCONNECTIONSETTINGSDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwGroupID;
	DWORD			dwConnOffset;
} MSG_SETGROUPCONNECTIONSETTINGSDATA, * LPMSG_SETGROUPCONNECTIONSETTINGSDATA;

// SetGroupData
typedef struct MSG_SETGROUPDATADATA
{
	DWORD			msg;
	DWORD			dwTotalSize;
	DWORD			dwGroupID;
	DWORD			dwDataSize;
	DWORD			dwDataOffset;
} MSG_SETGROUPDATADATA, * LPMSG_SETGROUPDATADATA;

// SetGroupName
typedef struct MSG_SETGROUPNAMEDATA
{
	DWORD			msg;
	DWORD			dwGroupID;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
} MSG_SETGROUPNAMEDATA, * LPMSG_SETGROUPNAMEDATA;

typedef struct MSG_SETREMOTEGROUPNAMEDATA
{
	DWORD			msg;
	DWORD			dwGroupID;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
} MSG_SETREMOTEGROUPNAMEDATA, * LPMSG_SETREMOTEGROUPNAMEDATA;

// SetPlayerData
typedef struct MSG_SETPLAYERDATADATA
{
	DWORD			msg;
	DWORD			dwTotalSize;
	DWORD			dwPlayerID;
	DWORD			dwDataSize;
	DWORD			dwDataOffset;
} MSG_SETPLAYERDATADATA, * LPMSG_SETPLAYERDATADATA;

// SetPlayerName
typedef struct MSG_SETPLAYERNAMEDATA
{
	DWORD			msg;
	DWORD			dwPlayerID;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
} MSG_SETPLAYERNAMEDATA, * LPMSG_SETPLAYERNAMEDATA;

typedef struct MSG_SETREMOTEPLAYERNAMEDATA
{
	DWORD			msg;
	DWORD			dwPlayerID;
	DWORD			dwShortNameSize;
	DWORD			dwLongNameSize;
	DWORD			dwShortNameOffset;
	DWORD			dwLongNameOffset;
} MSG_SETREMOTEPLAYERNAMEDATA, * LPMSG_SETREMOTEPLAYERNAMEDATA;

// StartSession
typedef struct MSG_STARTSESSIONDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwFlags;
	DWORD			dwGroupID;
} MSG_STARTSESSIONDATA, * LPMSG_STARTSESSIONDATA;

typedef struct MSG_STARTSESSIONCOMMANDDATA
{
	DWORD			msg;
	DWORD			dwSize;
	DWORD			dwFlags;
	DWORD			dwGroupID;
	DWORD			dwHostID;
	DWORD			dwConnOffset;
	DWORD			dwConnSizeUnicode;
	DWORD			dwConnSizeAnsi;
} MSG_STARTSESSIONCOMMANDDATA, * LPMSG_STARTSESSIONCOMMANDDATA;


#endif // __DPLMESS_INCLUDED__

