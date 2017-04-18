/*==========================================================================;
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       LSPserver.h
 *	Content:	LOBBY-SP Server Access functions include
 *	History:
 *	1999/09/10	Created it
 *=========================================================================*/
#ifndef __LSPSERVER_INCLUDED__
#define __LSPSERVER_INCLUDED__

#include <windows.h>

//==========================================================================
//
//	Prototypes
//
//==========================================================================
HRESULT SRL_Open( void );
HRESULT SRL_Close( void );
HRESULT SRL_CreatePlayer( LPSPDATA_CREATEPLAYER lpCreatePlayer );
HRESULT SRL_DestroyPlayer( LPSPDATA_DESTROYPLAYER lpDestroyPlayer );
HRESULT SRL_Send( LPSPDATA_SEND lpSend );
HRESULT SRL_SendChatMessage( LPSPDATA_CHATMESSAGE lpSendChatMessage );
HRESULT SRL_CreateGroup( LPSPDATA_CREATEGROUP lpCreateGroup );
HRESULT SRL_DestroyGroup( LPSPDATA_DESTROYGROUP lpDestroyGroup );
HRESULT SRL_AddPlayerToGroup( LPSPDATA_ADDPLAYERTOGROUP lpAddPlayerToGroup );
HRESULT SRL_DeletePlayerFromGroup( LPSPDATA_DELETEPLAYERFROMGROUP lpDeletePlayerFromGroup );


#endif // __LSPSERVER_INCLUDED__

