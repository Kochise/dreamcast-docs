/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSinitial.h
 *  Content:    Lobby server initial process include file
 ***************************************************************************/
#ifndef _SRS_INITIAL_H_
#define _SRS_INITIAL_H_

//=========================================
//   関数定義
//=========================================
int  SRS_Ini_Server( void );
int  SRS_Ini_GetPort( int iClientIp );
int  SRS_Ini_UsePort( void );
int  SRS_Ini_ReleasePort( int iPort );
int  SRS_Ini_CreateLobby( int iPort );
int  SRS_Ini_CreateProc( int iMode, LPSTR lpstrCommandLine );
int	 SRS_Ini_TermProc( int iPort );

//=========================================
//   プロセス生成モード
//=========================================
#define	SRS_CREATE_SYNC	  	0				// 同期生成プロセス
#define	SRS_CREATE_ASYNC	1 		 		// 非同期生成プロセス

//=========================================
//   ポート番号リスト
//=========================================
//  要素
struct SRS_PORT_ITEM
{
	int PI_iIp;				// 使用クライアントＩＰアドレス
	int	PI_iPort;			// ポート番号
};
#define SRS_PORT_ITEM_SZ	( sizeof(struct SRS_PORT_ITEM) )

//  リスト
struct SRS_PORT_LIST
{
	int 	PL_iItemNo;
	struct	SRS_PORT_ITEM  PL_Item[1];
};
#define SRS_PORT_LIST_SZ	( (sizeof(struct SRS_PORT_LIST) - SRS_PORT_ITEM_SZ) )

#endif
