/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSlobby.h
 *  Content:    Lobby process include file 
 ***************************************************************************/
#ifndef _SRS_LOBBY_H_
#define _SRS_LOBBY_H_

//=========================================
//   関数定義
//=========================================
void SRS_Lby_Term( int iPort );
int	 SRS_Lby_ReqAll( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqUserEntry( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqUserDelete( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqUserDeleteEX( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqLobbyEntry( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqLobbyDefect( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqGroupMake( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqGroupJoin( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqGroupDefect( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqGameJoin( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqGameDefect( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqGameStart( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqGameEnd( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqSendMsg( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqSaveInfo( struct SRS_IF_FIX *lpIfFix );
int	 SRS_Lby_ReqSeqError( struct SRS_IF_FIX *lpIfFix );
int  SRS_Lby_ReqResultSend( char *lpSenddata, size_t szSendSize );
int	 SRS_Lby_SendInfo( WORD wUserID, WORD wLobbyID, char *lpSendData, size_t szSendSize );
void SRS_Lby_ChatLog(int sIP, int dIP, LPSTR lpstrMsg);

//=========================================
//   最大値定義
//=========================================
#define	SRS_MAX_RCV		256			// 最大要求情報長

//=========================================
//   ロギング種別
//=========================================
#define	SRS_LMG_INFO	1			// ”情報”メッセージ
#define	SRS_LMG_ERROR	2			// ”エラー”メッセージ
#define	SRS_LMG_WARNING	3			// ”警告”メッセージ


#endif
