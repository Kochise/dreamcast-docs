/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSlobbyReq.cpp
 *               	SRS_Lby_ReqAll 			(全情報参照要求)
 *					SRS_Lby_ReqUserEntry	(ユーザ登録要求)
 *					SRS_Lby_ReqUserDelete	(ユーザ削除要求)
 *	 				SRS_Lby_ReqLobbyEntry	(ロビー登録要求)
 *	 				SRS_Lby_ReqLobbyDefect	(ロビー脱退要求)
 *	 				SRS_Lby_ReqGroupMake	(グループ作成要求)
 *	 				SRS_Lby_ReqGroupJoin	(グループ参加要求)
 *	 				SRS_Lby_ReqGroupDefect	(グループ脱退要求)
 *	 				SRS_Lby_ReqGameJoin	    (ゲーム参加要求)
 *	 				SRS_Lby_ReqGameDefect	(ゲーム脱退要求)
 *	 				SRS_Lby_ReqGameStart	(ゲーム開始要求)
 *	 				SRS_Lby_ReqGameEnd		(ゲーム終了要求)
 *	 				SRS_Lby_ReqSendMsg		(メッセージ送信要求)
 *	 				SRS_Lby_ReqSaveInfo		(固有情報待避要求)
 *	 				SRS_Lby_ReqSeqError		(要求シーケンスエラー)
 *	 				SRS_Lby_ReqResultSend	(要求応答送信)
 *
 *  Content:    Lobby Server  Lobbyクライアント要求処理プロセス
 *
 ***************************************************************************/
/*================================
    インクルード
==================================*/
#include <windows.h>
#include <stdio.h>

#include "SRScom.h"
#include "SRSdebug.h"
#include "SRSmanage.h"
#include "SRSlobby.h"
#include "SRSnetwork.h"
#include "SRSregistry.h"

//
//	チャットログ出力先
#define	FILE_CHATLOG		"..\\Log\\Chat%02d%02d%02d.log"

/*================================
    グローバル域
==================================*/
/*====================================================================
 *	ローカル関数
 ====================================================================*/
int SRS_Dbg_GetRegChatlog( char *lpBuff );

WORD	wUserID = 0;					// ユーザＩＤ
/*=============================================================================
     関数    ：全情報参照要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqAll( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;							//
	int		iClientIP;						//
	int		iUserSize;						//
	int		iLobbySize;						//
	int		iGroupSize;						//
	int		iGameSize;						//
	int		iPoint;							//
	size_t	szSendSize;						//
	struct	SRS_IF_FIX *lpSendFix;			//
	struct	SRS_IF_RENEWAL *lpIfRenewal;	// 更新情報域ポインタ
	struct	SRS_REG_INFO *lpRegInfo;		// 共通情報域ポインタ
	char	*lpSendData;					//
	char	*lpUserInfo;					//
	char	*lpLobbyInfo;					//
	char	*lpGroupInfo;					//
	char	*lpGameInfo;					//
	char	cRegInfo[SRS_REG_INFO_SZ];		// 共通情報域
	char	cMsg[256];


	//=======================================
	//  情報域サイズ算出
	//=======================================
	sprintf( cMsg, "SRS_Lby_ReqAll : 全情報参照 0x%04x",lpIfFix->IF_wRequest );
	SRS_Dbg_WriteLog( cMsg );

	iClientIP = lpIfFix->IF_iIp;
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		lpIfFix->IF_wRequest = IF_REQ_ALL;		// 要求設定
		lpIfFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpIfFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpIfFix, (size_t)SRS_IF_FIX_SZ );
		sprintf( cMsg, "SRS_Lby_ReqAll : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	iUserSize = SRS_Mng_GetMngSize( SRS_MNG_USER );		// ユーザ情報域サイズ
	iLobbySize = SRS_Mng_GetMngSize( SRS_MNG_LOBBY );	// ロビー情報域サイズ
	iGroupSize = SRS_Mng_GetMngSize( SRS_MNG_GROUP );	// グループ情報域サイズ
	iGameSize = SRS_Mng_GetMngSize( SRS_MNG_GAME );		// ゲーム情報域サイズ
	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + 	// 全情報サイズ
							iUserSize + iLobbySize + iGroupSize + iGameSize );

	//=======================================
	//  情報獲得
	//=======================================
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )	// 獲得失敗？
	{
		lpIfFix->IF_wRequest = IF_REQ_ALL;		// 要求設定
		lpIfFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpIfFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpIfFix, (size_t)SRS_IF_FIX_SZ );
		sprintf( cMsg, "SRS_Lby_ReqAll : Cannot malloc information data area" );
		SRS_Dbg_WriteLog( cMsg );
		return( 0 );
	}
	memset( lpSendData, 0, szSendSize );
	//=======================================
	//  応答作成
	//=======================================
	//
	// 固有域設定
	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
    lpSendFix->IF_wRequest = IF_REQ_ALL;							// 要求設定
	lpSendFix->IF_wResult = IF_CMP_SUCCESS;							// 結果正常
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;	//
	lpSendFix->IF_iPortNo = lpIfFix->IF_iPortNo;					// ポート番号コピー
	lpSendFix->IF_iIp = lpIfFix->IF_iIp;							// IPアドレスコピー

	//
	// 更新情報域設定
	lpIfRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpIfRenewal->IF_RE_wUserInfoNo  = lpRegInfo->wMaxUser + 1;	// 最大ユーザ数設定
	lpIfRenewal->IF_RE_wLobbyInfoNo = lpRegInfo->wMaxLobby;		// 最大ロビー数設定
	lpIfRenewal->IF_RE_wGroupInfoNo = lpRegInfo->wMaxGroup + 1;	// 最大グループ数設定
	lpIfRenewal->IF_RE_wGameInfoNo  = lpRegInfo->wMaxGame + 1;	// 最大ゲーム数設定

	// ユーザ情報
	lpUserInfo = (char *)malloc( iUserSize );
	if( lpUserInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		sprintf( cMsg, "SRS_Lby_ReqAll : Cannot malloc user information data" );
		SRS_Dbg_WriteLog( cMsg );
		return( 0 );
	}
	
	// ロビー情報域
	lpLobbyInfo = (char *)malloc( iLobbySize );
	if( lpLobbyInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		sprintf( cMsg, "SRS_Lby_ReqAll : Cannot malloc lobby information data" );
		SRS_Dbg_WriteLog( cMsg );
		return( 0 );
	}

	// グループ情報域
	lpGroupInfo = (char *)malloc( iGroupSize );
	if( lpGroupInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		sprintf( cMsg, "SRS_Lby_ReqAll : Cannot malloc gouup information data" );
		SRS_Dbg_WriteLog( cMsg );
		return( 0 );
	}

	// ゲーム情報域
	lpGameInfo = (char *)malloc( iGameSize );
	if( lpGameInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		realloc( lpGroupInfo, 0 );
		sprintf( cMsg, "SRS_Lby_ReqAll : Cannot malloc game information data" );
		SRS_Dbg_WriteLog( cMsg );
		return( 0 );
	}

	//
	// 全情報獲得
	sprintf( cMsg, "SRS_Lby_ReqAll : Call SRS_Mng_AllGet()" );
	SRS_Dbg_WriteLog( cMsg );

	iRtn = SRS_Mng_AllGet( lpUserInfo, lpLobbyInfo, lpGroupInfo, lpGameInfo );
	if( iRtn == -1 )							// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_SEQERR;	// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		realloc( lpGroupInfo, 0 );
		realloc( lpGameInfo, 0 );
		sprintf( cMsg, "SRS_Lby_ReqAll : SRS_Mng_AllGet() FALSE" );
		SRS_Dbg_WriteLog( cMsg );
		return( 0 );
	}
	

	// 管理情報設定
	iPoint = 0;
	memcpy( (char *)&lpIfRenewal->IF_RE_cInfo[iPoint], lpUserInfo, iUserSize );
	iPoint = iUserSize;
	memcpy( (char *)&lpIfRenewal->IF_RE_cInfo[iPoint], lpLobbyInfo, iLobbySize );
	iPoint = iUserSize + iLobbySize;
	memcpy( (char *)&lpIfRenewal->IF_RE_cInfo[iPoint], lpGroupInfo, iGroupSize );
	iPoint = iUserSize + iLobbySize + iGroupSize;
	memcpy( (char *)&lpIfRenewal->IF_RE_cInfo[iPoint], lpGameInfo, iGameSize );

	//=======================================
	//  応答送信
	//=======================================
	SRS_Dbg_WriteData( "SRS_Lby_ReqAll : 全情報参照 応答", lpSendData, szSendSize, "ab" );
	iRtn = SRS_Net_SendReq( iClientIP, lpSendData, (size_t)szSendSize );

	realloc( lpUserInfo, 0 );
	realloc( lpLobbyInfo, 0 );
	realloc( lpGroupInfo, 0 );
	realloc( lpGameInfo, 0 );
	realloc( lpSendData, 0 );

	return( iRtn );
}

/*=============================================================================
     関数    ：ユーザ登録要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqUserEntry( struct SRS_IF_FIX *lpIfFix )
{
	WORD	wLobbyID;
	int		iRtn;							//
	int		iClientIP;						//
	int		iUserSize;						//
	int		iLobbySize;						//
	int		iGroupSize;						//
	int		iGameSize;						//
	int		iPoint;							//
	size_t	szSendSize;						//
	struct	SRS_IF_FIX 		*lpSendFix;		//
	struct	SRS_IF_USER_ENTRY *lpUserEntry;	//
	struct	SRS_IF_RENEWAL 	*lpSendRenewal;	// 更新情報域ポインタ
	struct	SRS_REG_INFO	*lpRegInfo;		// 共通情報域ポインタ
	struct	SRS_INFO_USER	*lpSendUser;	//
	struct	SRS_INFO_LOBBY	*lpSendLobby;	//
	char	*lpSendData;					//
	char	*lpUserInfo;					//
	char	*lpLobbyInfo;					//
	char	*lpGroupInfo;					//
	char	*lpGameInfo;					//
	char	cRegInfo[SRS_REG_INFO_SZ];		// 共通情報域
	char	cIfFix[SRS_IF_FIX_SZ + SRS_IF_USER_ENTRY_SZ];	// ユーザ登録情報域
	char	cSendMode[4];
	char	cMsg[256];

	sprintf( cMsg, "SRS_Lby_ReqUserEntry : ユーザ登録 0x%04x",lpIfFix->IF_wRequest);
	SRS_Dbg_WriteLog( cMsg );

	memset( cIfFix, 0, SRS_IF_FIX_SZ + SRS_IF_USER_ENTRY_SZ );
	memcpy( cIfFix, (char *)lpIfFix, SRS_IF_FIX_SZ + SRS_IF_USER_ENTRY_SZ );
	lpSendFix = (struct SRS_IF_FIX *)cIfFix;
	iClientIP = lpIfFix->IF_iIp;

	iRtn = SRS_Mng_UserEntry( lpSendFix );	// ユーザ登録
	if( iRtn == -1 )						// ユーザ登録失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_ENTRY;
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}

	//=======================================
	//  情報域サイズ算出
	//=======================================
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_ENTRY;	// ユーザ登録
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		sprintf( cMsg, "SRS_Lby_ReqUserEntry : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( -1 );
	}
	iUserSize  = SRS_Mng_GetMngSize( SRS_MNG_USER );			// ユーザ情報域サイズ
	iLobbySize = SRS_Mng_GetMngSize( SRS_MNG_LOBBY );	    	// ロビー情報域サイズ
	iGroupSize = SRS_Mng_GetMngSize( SRS_MNG_GROUP );   		// グループ情報域サイズ
	iGameSize  = SRS_Mng_GetMngSize( SRS_MNG_GAME );		    // ゲーム情報域サイズ
	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + 	// 全情報サイズ
							iUserSize + iLobbySize + iGroupSize + iGameSize );
	//=======================================
	//  情報獲得
	//=======================================
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_ENTRY;		// 要求設定
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( 0 );
	}
	memset( lpSendData, 0, szSendSize );
	//=======================================
	//  応答作成
	//=======================================
	//
	// 固有域設定
	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
    lpSendFix->IF_wRequest = IF_REQ_USER_ENTRY;						// 要求設定
	lpSendFix->IF_wResult = IF_CMP_SUCCESS;							// 結果正常
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;	//
	lpSendFix->IF_iPortNo = lpIfFix->IF_iPortNo;					// ポート番号コピー
	lpSendFix->IF_iIp = lpIfFix->IF_iIp;							// IPアドレスコピー

	//
	// 更新情報域設定
	lpSendRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpSendRenewal->IF_RE_wUserInfoNo  = lpRegInfo->wMaxUser + 1;	// ユーザ数設定
	lpSendRenewal->IF_RE_wLobbyInfoNo = lpRegInfo->wMaxLobby;		// ロビー数設定
	lpSendRenewal->IF_RE_wGroupInfoNo = lpRegInfo->wMaxGroup + 1;	// グループ数設定
	lpSendRenewal->IF_RE_wGameInfoNo  = lpRegInfo->wMaxGame + 1;	// ゲーム数設定

	// ユーザ情報
	lpUserInfo = (char *)malloc( iUserSize );
	if( lpUserInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		return( 0 );
	}
	
	// ロビー情報域
	lpLobbyInfo = (char *)malloc( iLobbySize );
	if( lpLobbyInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		return( 0 );
	}

	// グループ情報域
	lpGroupInfo = (char *)malloc( iGroupSize );
	if( lpGroupInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		return( 0 );
	}

	// ゲーム情報域
	lpGameInfo = (char *)malloc( iGameSize );
	if( lpGameInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		realloc( lpGroupInfo, 0 );
		return( 0 );
	}

	//
	// 全情報獲得
	iRtn = SRS_Mng_AllGet( lpUserInfo, lpLobbyInfo, lpGroupInfo, lpGameInfo );
	if( iRtn == -1 )							// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_SEQERR;	// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		realloc( lpGroupInfo, 0 );
		realloc( lpGameInfo, 0 );
		return( 0 );
	}

	// 管理情報設定
	iPoint = 0;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpUserInfo, iUserSize );
	iPoint = iUserSize;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpLobbyInfo, iLobbySize );
	iPoint = iUserSize + iLobbySize;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpGroupInfo, iGroupSize );
	iPoint = iUserSize + iLobbySize + iGroupSize;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpGameInfo, iGameSize );

	//=======================================
	//  応答送信
	//=======================================
	sprintf( cMsg, "SRS_Lby_UserEntry : 応答送信 %d bytes", szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( cMsg, lpSendData, szSendSize, "ab" );

	iRtn = SRS_Net_SendReq( iClientIP, lpSendData, (size_t)szSendSize );

	//=======================================
	//  更新情報配信
	//=======================================
	realloc( lpSendData, 0 );
	realloc( lpGroupInfo, 0 );
	realloc( lpGameInfo, 0 );
	strcpy( cSendMode, SRS_SEND_MODE_NO );
	iRtn = SRS_Reg_GetInfo( SRS_REG_KEY_COM, SRS_REG_SEND, cSendMode );
	if( (strncmp(cSendMode, SRS_SEND_MODE_NO, sizeof(SRS_SEND_MODE_NO))) == 0 )	// 配信なし？
	{
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		realloc( lpSendData, 0 );
		return( 0 );
	}
	//
    // 配信情報作成
	//
	SRS_Dbg_WriteLog( "SRS_Lby_ReqUserEntry : 更新情報配信開始" );
	szSendSize = SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + SRS_INFO_USER_SZ + SRS_INFO_LOBBY_SZ;
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )
	{
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		realloc( lpSendData, 0 );
		SRS_Dbg_WriteLog( "SRS_Lby_ReqUserEntry : malloc error" );
		return( -1 );
	}
	memset( lpSendData, 0, szSendSize );

	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
	lpSendFix->IF_wRequest = IF_REQ_RENEWAL;
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;
	lpSendRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpSendRenewal->IF_RE_wUserInfoNo  = 1;		// 更新ユーザ数設定
	lpSendRenewal->IF_RE_wLobbyInfoNo = 1;		// 更新ロビー数設定
	//
	// 管理情報設定
	//
	lpSendUser 	= (struct SRS_INFO_USER *)lpUserInfo;
	lpSendLobby = (struct SRS_INFO_LOBBY *)lpLobbyInfo;
	lpUserEntry = (struct SRS_IF_USER_ENTRY *)lpIfFix->IF_cInformation;

	wUserID = SRS_Mng_GetUserByName( lpUserEntry->IF_UE_cUserName );
	if( wUserID == SRS_WORD_ERROR )
	{
		sprintf( cMsg, "SRS_Lby_ReqUserEntry : SRS_Mng_GetUserByName error");
		SRS_Dbg_WriteLog( cMsg );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		realloc( lpSendData, 0 );
		return( -1 );
	}

	wLobbyID = SRS_ID_MAINLOBBY;
	iPoint = 0;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpUserInfo, SRS_INFO_USER_COM_SZ );
	iPoint = SRS_INFO_USER_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
             lpSendUser->US_info_user[wUserID].USI_cClientName, SRS_USER_ITEM_SZ );
	iPoint = iPoint + SRS_USER_ITEM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpLobbyInfo, SRS_INFO_LOBBY_COM_SZ );
	iPoint = iPoint + SRS_INFO_LOBBY_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
            (char *)&lpSendLobby->LB_info_lobby[wLobbyID].LBI_iLockword, SRS_LOBBY_ITEM_SZ );

	// 情報配信
	sprintf( cMsg, "SRS_Lby_UserEntry : 更新情報配信 %d bytes",szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	iRtn = SRS_Lby_SendInfo( wUserID, wLobbyID, lpSendData, (size_t)szSendSize );

	realloc( lpUserInfo, 0 );
	realloc( lpLobbyInfo, 0 );
	realloc( lpSendData, 0 );
	return( 0 );
}

/*=============================================================================
     関数    ：ユーザ削除要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqUserDelete( struct SRS_IF_FIX *lpIfFix )
{
	WORD	wLobbyID;
	int		iRtn;							//
	int		iClientIP;						//
	int		iUserSize;						//
	int		iLobbySize;						//
	int		iPoint;							//
	size_t	szSendSize;						//
	struct	SRS_IF_FIX 		*lpSendFix;		//
	struct	SRS_IF_USER_DELETE *lpUserDelete;
	struct	SRS_IF_RENEWAL 	*lpSendRenewal;	// 更新情報域ポインタ
	struct	SRS_REG_INFO	*lpRegInfo;		// 共通情報域ポインタ
	struct	SRS_INFO_USER	*lpSendUser;	//
	struct	SRS_INFO_LOBBY	*lpSendLobby;	//
	struct	SRS_USER_ITEM	*lpUserItem;	//
	char	*lpSendData;					//
	char	*lpUserInfo;					//
	char	*lpLobbyInfo;					//
	char	cRegInfo[SRS_REG_INFO_SZ];		// 共通情報域
	char	cIfFix[SRS_IF_FIX_SZ + SRS_IF_USER_DELETE_SZ];	// ユーザ削除情報域
	char	cSendMode[4];
	char	cUserItem[SRS_USER_ITEM_SZ];
	char	cMsg[256];


	sprintf( cMsg, "SRS_Lby_ReqUserDelete : ユーザ削除 0x%04x",lpIfFix->IF_wRequest);
	SRS_Dbg_WriteLog( cMsg );

	memset( cIfFix, 0, SRS_IF_FIX_SZ + SRS_IF_USER_DELETE_SZ );
	memcpy( cIfFix, (char *)lpIfFix, SRS_IF_FIX_SZ + SRS_IF_USER_DELETE_SZ );
	lpSendFix = (struct SRS_IF_FIX *)cIfFix;
	iClientIP = lpIfFix->IF_iIp;

	//=======================================
	//  ユーザ削除
	//=======================================
	lpUserDelete = (struct SRS_IF_USER_DELETE *)lpIfFix->IF_cInformation;
	wUserID  = lpUserDelete->IF_UD_wUserID;			// ユーザＩＤ設定
	iRtn = SRS_Mng_GetUserByID( wUserID, cUserItem );
	if( iRtn == -1 )
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;
		lpSendFix->IF_wResult = IF_CMP_SEQERR;		// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}
	lpUserItem = (struct SRS_USER_ITEM *)cUserItem;
	wLobbyID = lpUserItem->USI_wLobbyID;			// ロビーＩＤ設定

	iRtn = SRS_Mng_UserDelete( lpSendFix );	// ユーザ削除
	if( iRtn == -1 )						// ユーザ削除失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}

	//=======================================
	//  情報域サイズ算出
	//=======================================
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;	// ユーザ削除
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		sprintf( cMsg, "SRS_Lby_ReqUserDelete : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( -1 );
	}
	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + 	// 情報サイズ
						  SRS_INFO_USER_SZ + SRS_INFO_LOBBY_SZ );

	//=======================================
	//  情報獲得
	//=======================================
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;		// 要求設定
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;			// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( 0 );
	}
	memset( lpSendData, 0, szSendSize );
	//=======================================
	//  応答作成
	//=======================================
	//
	// 固有域設定
	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
    lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;					// 要求設定
	lpSendFix->IF_wResult = IF_CMP_SUCCESS;							// 結果正常
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;	//
	lpSendFix->IF_iPortNo = lpIfFix->IF_iPortNo;					// ポート番号コピー
	lpSendFix->IF_iIp = lpIfFix->IF_iIp;							// IPアドレスコピー

	//
	// 更新情報域設定
	lpSendRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpSendRenewal->IF_RE_wUserInfoNo  = 1;		// ユーザ数設定
	lpSendRenewal->IF_RE_wLobbyInfoNo = 1;		// ロビー数設定

	iUserSize  = SRS_Mng_GetMngSize( SRS_MNG_USER );			// ユーザ情報域サイズ
	iLobbySize = SRS_Mng_GetMngSize( SRS_MNG_LOBBY );	    	// ロビー情報域サイズ
	// ユーザ情報
	lpUserInfo = (char *)malloc( iUserSize );
	if( lpUserInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		return( 0 );
	}
	
	// ロビー情報域
	lpLobbyInfo = (char *)malloc( iLobbySize );
	if( lpLobbyInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		return( 0 );
	}

	//
	// 全情報獲得
	iRtn = SRS_Mng_AllGet( lpUserInfo, lpLobbyInfo, 0, 0 );
	if( iRtn == -1 )							// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_SEQERR;	// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		return( 0 );
	}

	// 管理情報設定
	lpSendUser 	= (struct SRS_INFO_USER *)lpUserInfo;
	lpSendLobby = (struct SRS_INFO_LOBBY *)lpLobbyInfo;
	iPoint = 0;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpSendUser, SRS_INFO_USER_COM_SZ );
	iPoint = SRS_INFO_USER_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
             lpSendUser->US_info_user[wUserID].USI_cClientName, SRS_USER_ITEM_SZ );
	iPoint = iPoint + SRS_USER_ITEM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpLobbyInfo, SRS_INFO_LOBBY_COM_SZ );
	iPoint = iPoint + SRS_INFO_LOBBY_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
            (char *)&lpSendLobby->LB_info_lobby[wLobbyID].LBI_iLockword, SRS_LOBBY_ITEM_SZ );

	//=======================================
	//  応答送信
	//=======================================
	sprintf( cMsg, "SRS_Lby_UserDelete : 応答送信 %d bytes", szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( cMsg, lpSendData, szSendSize, "ab" );

	iRtn = SRS_Net_SendReq( iClientIP, lpSendData, (size_t)szSendSize );
	realloc( lpUserInfo, 0 );
	realloc( lpLobbyInfo, 0 );

	//=======================================
	//  更新情報配信
	//=======================================
    lpSendFix->IF_wRequest = IF_REQ_RENEWAL;					// 要求設定
	strcpy( cSendMode, SRS_SEND_MODE_NO );
	iRtn = SRS_Reg_GetInfo( SRS_REG_KEY_COM, SRS_REG_SEND, cSendMode );
	if( (strncmp(cSendMode, SRS_SEND_MODE_NO, sizeof(SRS_SEND_MODE_NO))) == 0 )	// 配信なし？
	{
		realloc( lpSendData, 0 );
		return( 0 );
	}
	//
    // 配信情報作成
	//
	sprintf( cMsg, "SRS_Lby_UserDelete : 更新情報配信 %d bytes",szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	iRtn = SRS_Lby_SendInfo( wUserID, wLobbyID, lpSendData, (size_t)szSendSize );

	realloc( lpSendData, 0 );
	return( 0 );
}

/*=============================================================================
     関数    ：ロビー参加要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqLobbyEntry( struct SRS_IF_FIX *lpIfFix )
{
	WORD	wLobbyID;							// ロビーＩＤ
	int		iRtn;								// 
	int		iClientIP;							// 送信クライントＩＰ
	int		iUserSize;							// ユーザ情報域サイズ
	int		iLobbySize;							// ロビー情報域サイズ
	int		iPoint;								//
	size_t	szSendSize;							// 送信サイズ
	struct	SRS_IF_FIX 		*lpSendFix;			// インタフェース域ポインタ
	struct	SRS_IF_LOBBY_ENTRY *lpLobbyEntry;	// ロビー参加情報域
	struct	SRS_REG_INFO	*lpRegInfo;			// 共通情報域ポインタ
	struct	SRS_IF_RENEWAL 	*lpSendRenewal;		// 送信用更新情報域ポインタ
	struct	SRS_INFO_USER	*lpSendUser;		// 送信用ユーザ管理情報域ポインタ
	struct	SRS_INFO_LOBBY	*lpSendLobby;		// 送信用ロビー管理情報域ポインタ
	char	*lpSendData;						// 送信データ域ポインタ
	char	*lpUserInfo;						// ユーザ管理情報域ポインタ
	char	*lpLobbyInfo;						// ロビー管理情報域ポインタ
	char	cRegInfo[SRS_REG_INFO_SZ];			// 共通情報域
	char	cIfFix[SRS_IF_FIX_SZ + SRS_IF_LOBBY_ENTRY_SZ];	// ロビー参加情報域
	char	cSendMode[4];
	char	cMsg[256];


	sprintf( cMsg, "SRS_Lby_ReqLobbyEntry : ロビー参加 0x%04x",lpIfFix->IF_wRequest);
	SRS_Dbg_WriteLog( cMsg );

	memset( cIfFix, 0, SRS_IF_FIX_SZ + SRS_IF_LOBBY_ENTRY_SZ );
	memcpy( cIfFix, (char *)lpIfFix, SRS_IF_FIX_SZ + SRS_IF_LOBBY_ENTRY_SZ );
	lpSendFix = (struct SRS_IF_FIX *)cIfFix;
	iClientIP = lpIfFix->IF_iIp;

	//=======================================
	//  ロビー参加
	//=======================================
	lpLobbyEntry = (struct SRS_IF_LOBBY_ENTRY *)lpIfFix->IF_cInformation;
	wUserID  = lpLobbyEntry->IF_LE_wUserID;			// ユーザＩＤ設定
	wLobbyID = lpLobbyEntry->IF_LE_wLobbyID;		// ロビーＩＤ設定（参加後）

	iRtn = SRS_Mng_LobbyEntry( lpSendFix );			// ロビー参加
	if( iRtn == -1 )								// ロビー参加失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_LOBBY_ENTRY;
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}

	//=======================================
	//  情報域サイズ算出
	//=======================================
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_LOBBY_ENTRY;	// 
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		sprintf( cMsg, "SRS_Lby_ReqLobbyEntry : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( -1 );
	}
	iUserSize  = SRS_Mng_GetMngSize( SRS_MNG_USER );			// ユーザ情報域サイズ
	iLobbySize = SRS_Mng_GetMngSize( SRS_MNG_LOBBY );			// ロビー情報域サイズ

	// 通知情報＝１ユーザ情報＋全ロビー情報
	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + 	// 情報サイズ
						  SRS_INFO_USER_SZ + iLobbySize );

	//=======================================
	//  情報獲得
	//=======================================
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_LOBBY_ENTRY;		// 要求設定
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;			// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( 0 );
	}
	memset( lpSendData, 0, szSendSize );
	//=======================================
	//  応答作成
	//=======================================
	//
	// 固有域設定
	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
    lpSendFix->IF_wRequest = IF_REQ_LOBBY_ENTRY;					// 要求設定
	lpSendFix->IF_wResult = IF_CMP_SUCCESS;							// 結果正常
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;	//
	lpSendFix->IF_iPortNo = lpIfFix->IF_iPortNo;					// ポート番号コピー
	lpSendFix->IF_iIp = lpIfFix->IF_iIp;							// IPアドレスコピー

	//
	// 更新情報域設定
	lpSendRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpSendRenewal->IF_RE_wUserInfoNo  = 1;						// ユーザ数設定
	lpSendRenewal->IF_RE_wLobbyInfoNo = lpRegInfo->wMaxLobby;	// 最大ロビー数設定

	// ユーザ情報域獲得
	lpUserInfo = (char *)malloc( iUserSize );
	if( lpUserInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		return( 0 );
	}
	
	// ロビー情報域獲得
	lpLobbyInfo = (char *)malloc( iLobbySize );
	if( lpLobbyInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		return( 0 );
	}

	//
	// 全情報獲得
	iRtn = SRS_Mng_AllGet( lpUserInfo, lpLobbyInfo, 0, 0 );
	if( iRtn == -1 )							// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_SEQERR;	// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		return( 0 );
	}

	// 管理情報設定
	lpSendUser 	= (struct SRS_INFO_USER *)lpUserInfo;
	lpSendLobby = (struct SRS_INFO_LOBBY *)lpLobbyInfo;
	iPoint = 0;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpSendUser, SRS_INFO_USER_COM_SZ );
	iPoint = SRS_INFO_USER_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
             lpSendUser->US_info_user[wUserID].USI_cClientName, SRS_USER_ITEM_SZ );
	iPoint = iPoint + SRS_USER_ITEM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpLobbyInfo, iLobbySize );

	//=======================================
	//  応答送信
	//=======================================
	sprintf( cMsg, "SRS_Lby_LobbyEntry : 応答送信 %d bytes", szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( cMsg, lpSendData, szSendSize, "ab" );

	iRtn = SRS_Net_SendReq( iClientIP, lpSendData, (size_t)szSendSize );

	realloc( lpUserInfo, 0 );
	realloc( lpLobbyInfo, 0 );
	//=======================================
	//  更新情報配信
	//=======================================
	strcpy( cSendMode, SRS_SEND_MODE_NO );
	iRtn = SRS_Reg_GetInfo( SRS_REG_KEY_COM, SRS_REG_SEND, cSendMode );
	if( (strncmp(cSendMode, SRS_SEND_MODE_NO, sizeof(SRS_SEND_MODE_NO))) == 0 )	// 配信なし？
	{
		realloc( lpSendData, 0 );
		return( 0 );
	}
	//
    // 配信情報作成
	//
    lpSendFix->IF_wRequest = IF_REQ_RENEWAL;					// 要求設定
	sprintf( cMsg, "SRS_Lby_LobbyEntry : 更新情報配信 %d bytes",szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	iRtn = SRS_Lby_SendInfo( wUserID, wLobbyID, lpSendData, (size_t)szSendSize );

	realloc( lpSendData, 0 );
	return( 0 );
}

/*=============================================================================
     関数    ：ロビー脱退要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqLobbyDefect( struct SRS_IF_FIX *lpIfFix )
{
	WORD	wLobbyID;							// ロビーＩＤ
	int		iRtn;								// 
	int		iClientIP;							// 送信クライントＩＰ
	int		iUserSize;							// ユーザ情報域サイズ
	int		iLobbySize;							// ロビー情報域サイズ
	int		iPoint;								//
	size_t	szSendSize;							// 送信サイズ
	struct	SRS_IF_FIX 		*lpSendFix;			// インタフェース域ポインタ
	struct	SRS_IF_LOBBY_DEFECT *lpLobbyDefect;	// ロビー脱退情報域
	struct	SRS_REG_INFO	*lpRegInfo;			// 共通情報域ポインタ
	struct	SRS_IF_RENEWAL 	*lpSendRenewal;		// 送信用更新情報域ポインタ
	struct	SRS_INFO_USER	*lpSendUser;		// 送信用ユーザ管理情報域ポインタ
	struct	SRS_INFO_LOBBY	*lpSendLobby;		// 送信用ロビー管理情報域ポインタ
	char	*lpSendData;						// 送信データ域ポインタ
	char	*lpUserInfo;						// ユーザ管理情報域ポインタ
	char	*lpLobbyInfo;						// ロビー管理情報域ポインタ
	char	cRegInfo[SRS_REG_INFO_SZ];			// 共通情報域
	char	cIfFix[SRS_IF_FIX_SZ + SRS_IF_LOBBY_DEFECT_SZ];	// ロビー脱退情報域
	char	cSendMode[4];
	char	cMsg[256];


	sprintf( cMsg, "SRS_Lby_ReqLobbyDefect : ロビー脱退 0x%04x",lpIfFix->IF_wRequest);
	SRS_Dbg_WriteLog( cMsg );

	memset( cIfFix, 0, SRS_IF_FIX_SZ + SRS_IF_LOBBY_DEFECT_SZ );
	memcpy( cIfFix, (char *)lpIfFix, SRS_IF_FIX_SZ + SRS_IF_LOBBY_DEFECT_SZ );
	lpSendFix = (struct SRS_IF_FIX *)cIfFix;
	iClientIP = lpIfFix->IF_iIp;

	//=======================================
	//  ロビー脱退
	//=======================================
	lpLobbyDefect = (struct SRS_IF_LOBBY_DEFECT *)lpIfFix->IF_cInformation;
	wUserID  = lpLobbyDefect->IF_LD_wUserID;		// ユーザＩＤ設定
	wLobbyID = lpLobbyDefect->IF_LD_wLobbyID;		// ロビーＩＤ設定
	iRtn = SRS_Mng_LobbyDefect( lpSendFix );		// ロビー脱退
	if( iRtn == -1 )								// ロビー脱退失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_LOBBY_DEFECT;
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}

	//=======================================
	//  情報域サイズ算出
	//=======================================
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_LOBBY_DEFECT;	// ロビー脱退
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		sprintf( cMsg, "SRS_Lby_ReqLobbyDefect : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( -1 );
	}
	iUserSize  = SRS_Mng_GetMngSize( SRS_MNG_USER );			// ユーザ情報域サイズ
	iLobbySize = SRS_Mng_GetMngSize( SRS_MNG_LOBBY );			// ロビー情報域サイズ

	// 通知情報＝１ユーザ情報＋全ロビー情報
	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + 	// 情報サイズ
						  SRS_INFO_USER_SZ + iLobbySize );

	//=======================================
	//  情報獲得
	//=======================================
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_LOBBY_DEFECT;		// 要求設定
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;			// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( 0 );
	}
	memset( lpSendData, 0, szSendSize );
	//=======================================
	//  応答作成
	//=======================================
	//
	// 固有域設定
	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
    lpSendFix->IF_wRequest = IF_REQ_LOBBY_DEFECT;					// 要求設定
	lpSendFix->IF_wResult = IF_CMP_SUCCESS;							// 結果正常
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;	//
	lpSendFix->IF_iPortNo = lpIfFix->IF_iPortNo;					// ポート番号コピー
	lpSendFix->IF_iIp = lpIfFix->IF_iIp;							// IPアドレスコピー

	//
	// 更新情報域設定
	lpSendRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpSendRenewal->IF_RE_wUserInfoNo  = 1;							// ユーザ数設定
	lpSendRenewal->IF_RE_wLobbyInfoNo = lpRegInfo->wMaxLobby;	// 最大ロビー数設定

	// ユーザ情報域獲得
	lpUserInfo = (char *)malloc( iUserSize );
	if( lpUserInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		return( 0 );
	}
	
	// ロビー情報域獲得
	lpLobbyInfo = (char *)malloc( iLobbySize );
	if( lpLobbyInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		return( 0 );
	}

	//
	// 全情報獲得
	iRtn = SRS_Mng_AllGet( lpUserInfo, lpLobbyInfo, 0, 0 );
	if( iRtn == -1 )							// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_SEQERR;	// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		return( 0 );
	}

	// 管理情報設定
	lpSendUser 	= (struct SRS_INFO_USER *)lpUserInfo;
	lpSendLobby = (struct SRS_INFO_LOBBY *)lpLobbyInfo;
	iPoint = 0;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpSendUser, SRS_INFO_USER_COM_SZ );
	iPoint = SRS_INFO_USER_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
             lpSendUser->US_info_user[wUserID].USI_cClientName, SRS_USER_ITEM_SZ );
	iPoint = iPoint + SRS_USER_ITEM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpLobbyInfo, iLobbySize );

	//=======================================
	//  応答送信
	//=======================================
	sprintf( cMsg, "SRS_Lby_LobbyDefect : 応答送信 %d bytes", szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( cMsg, lpSendData, szSendSize, "ab" );

	iRtn = SRS_Net_SendReq( iClientIP, lpSendData, (size_t)szSendSize );

	realloc( lpUserInfo, 0 );
	realloc( lpLobbyInfo, 0 );
	//=======================================
	//  更新情報配信
	//=======================================
    lpSendFix->IF_wRequest = IF_REQ_RENEWAL;					// 要求設定
	strcpy( cSendMode, SRS_SEND_MODE_NO );
	iRtn = SRS_Reg_GetInfo( SRS_REG_KEY_COM, SRS_REG_SEND, cSendMode );
	if( (strncmp(cSendMode, SRS_SEND_MODE_NO, sizeof(SRS_SEND_MODE_NO))) == 0 )	// 配信なし？
	{
		realloc( lpSendData, 0 );
		return( 0 );
	}
	//
    // 配信情報作成
	//
	if( wLobbyID == SRS_ID_MAINLOBBY )		// メインロビー脱退？
	{
		return( 0 );
	}
	sprintf( cMsg, "SRS_Lby_LobbyDefect : 更新情報配信 %d bytes",szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	iRtn = SRS_Lby_SendInfo( wUserID, wLobbyID, lpSendData, (size_t)szSendSize );
	iRtn = SRS_Lby_SendInfo( wUserID, (WORD)SRS_ID_MAINLOBBY, lpSendData, (size_t)szSendSize );
	realloc( lpSendData, 0 );
	return( 0 );
}

/*=============================================================================
     関数    ：グループ作成要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqGroupMake( struct SRS_IF_FIX *lpIfFix )
{
	WORD	wLobbyID;							// ロビーＩＤ
	int		iRtn;								// 
	int		iClientIP;							// 送信クライントＩＰ
	int		iUserSize;							// ユーザ情報域サイズ
	int		iLobbySize;							// ロビー情報域サイズ
	int		iGroupSize;							// グループ情報域サイズ
	int		iPoint;								//
	size_t	szSendSize;							// 送信サイズ
	struct	SRS_IF_FIX 		*lpSendFix;			// インタフェース域ポインタ
	struct	SRS_IF_GROUP_MAKE *lpGroupMake;		// グループ作成情報域
	struct	SRS_REG_INFO	*lpRegInfo;			// 共通情報域ポインタ
	struct	SRS_IF_RENEWAL 	*lpSendRenewal;		// 送信用更新情報域ポインタ
	struct	SRS_INFO_USER	*lpSendUser;		// 送信用ユーザ管理情報域ポインタ
	struct	SRS_INFO_LOBBY	*lpSendLobby;		// 送信用ロビー管理情報域ポインタ
	struct  SRS_INFO_GROUP  *lpSendGroup;		// 送信用グループ管理情報域ポインタ
	struct	SRS_USER_ITEM   *lpUserItem;		// ユーザ情報域ポインタ
	char	*lpSendData;						// 送信データ域ポインタ
	char	*lpUserInfo;						// ユーザ管理情報域ポインタ
	char	*lpLobbyInfo;						// ロビー管理情報域ポインタ
	char	*lpGroupInfo;						// グループ管理情報域ポインタ
	char	cRegInfo[SRS_REG_INFO_SZ];			// 共通情報域
	char	cUserItem[SRS_USER_ITEM_SZ];		// ユーザ情報域
	char	cIfFix[SRS_IF_FIX_SZ + SRS_IF_GROUP_MAKE_SZ];	// グループ作成情報域
	char	cSendMode[4];
	char	cMsg[256];


	sprintf( cMsg, "SRS_Lby_ReqGroupMake : グループ作成 0x%04x",lpIfFix->IF_wRequest);
	SRS_Dbg_WriteLog( cMsg );

	memset( cIfFix, 0, SRS_IF_FIX_SZ + SRS_IF_GROUP_MAKE_SZ );
	memcpy( cIfFix, (char *)lpIfFix, SRS_IF_FIX_SZ + SRS_IF_GROUP_MAKE_SZ );
	lpSendFix = (struct SRS_IF_FIX *)cIfFix;
	iClientIP = lpIfFix->IF_iIp;

	//=======================================
	//  グループ作成
	//=======================================
	lpGroupMake = (struct SRS_IF_GROUP_MAKE *)lpIfFix->IF_cInformation;
	wUserID  = lpGroupMake->IF_GM_wUserID;			// ユーザＩＤ設定
	iRtn = SRS_Mng_GetUserByID( wUserID, cUserItem );
	if( iRtn == -1 )
	{
		SRS_Dbg_WriteLog( "SRS_Lby_GroupMake : SRS_Mng_GetUserByID error" );
		lpSendFix->IF_wRequest = IF_REQ_GROUP_MAKE;
		lpSendFix->IF_wResult = IF_CMP_SEQERR;		// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}
	lpUserItem = (struct SRS_USER_ITEM *)cUserItem;
	wLobbyID = lpUserItem->USI_wLobbyID;			// ロビーＩＤ設定

	iRtn = SRS_Mng_GroupMake( lpSendFix );			// グループ作成
	if( iRtn == -1 )								// グループ作成失敗？
	{
		sprintf( cMsg, "SRS_Lby_GroupMake : SRS_Mng_GroupMake error %04x",lpSendFix->IF_wResult );
		SRS_Dbg_WriteLog( cMsg );
		lpSendFix->IF_wRequest = IF_REQ_GROUP_MAKE;
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}

	//=======================================
	//  情報域サイズ算出
	//=======================================
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_GROUP_MAKE;
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		sprintf( cMsg, "SRS_Lby_ReqGroupMake : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( -1 );
	}
	iUserSize  = SRS_Mng_GetMngSize( SRS_MNG_USER );			// ユーザ情報域サイズ
	iLobbySize = SRS_Mng_GetMngSize( SRS_MNG_LOBBY );			// ロビー情報域サイズ
	iGroupSize = SRS_Mng_GetMngSize( SRS_MNG_GROUP );			// グループ情報域サイズ

	// 通知情報＝１ユーザ情報＋全ロビー情報＋全グループ情報
	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + 	// 情報サイズ
						  SRS_INFO_USER_SZ + iLobbySize + iGroupSize );

	//=======================================
	//  送信情報域獲得（応答／配信用）
	//=======================================
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )	// 獲得失敗？
	{
		sprintf( cMsg,"SRS_Lby_GroupMake : malloc(lpSendData) error %d",szSendSize );
		SRS_Dbg_WriteLog( cMsg );
		lpSendFix->IF_wRequest = IF_REQ_GROUP_MAKE;		// 要求設定
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( 0 );
	}
	memset( lpSendData, 0, szSendSize );
	//=======================================
	//  応答作成
	//=======================================
	//
	// 固有域設定
	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
    lpSendFix->IF_wRequest = IF_REQ_GROUP_MAKE;						// 要求設定
	lpSendFix->IF_wResult = IF_CMP_SUCCESS;							// 結果正常
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;	//
	lpSendFix->IF_iPortNo = lpIfFix->IF_iPortNo;					// ポート番号コピー
	lpSendFix->IF_iIp = lpIfFix->IF_iIp;							// IPアドレスコピー

	//
	// 更新情報域設定
	lpSendRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpSendRenewal->IF_RE_wUserInfoNo  = 1;							// ユーザ数設定
	lpSendRenewal->IF_RE_wLobbyInfoNo = lpRegInfo->wMaxLobby;		// 最大ロビー数設定
	lpSendRenewal->IF_RE_wGroupInfoNo = lpRegInfo->wMaxGroup + 1;	// 最大グループ数設定

	// ユーザ情報域獲得
	lpUserInfo = (char *)malloc( iUserSize );
	if( lpUserInfo == NULL )	// 獲得失敗？
	{
		sprintf( cMsg,"SRS_Lby_GroupMake : malloc(lpUserInfo) error %d",iUserSize );
		SRS_Dbg_WriteLog( cMsg );
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		return( 0 );
	}
	
	// ロビー情報域獲得
	lpLobbyInfo = (char *)malloc( iLobbySize );
	if( lpLobbyInfo == NULL )	// 獲得失敗？
	{
		sprintf( cMsg,"SRS_Lby_GroupMake : malloc(lpLobbyInfo) error %d",iLobbySize );
		SRS_Dbg_WriteLog( cMsg );
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		return( 0 );
	}

	// グループ情報域獲得
	lpGroupInfo = (char *)malloc( iGroupSize );
	if( lpGroupInfo == NULL )	// 獲得失敗？
	{
		sprintf( cMsg,"SRS_Lby_GroupMake : malloc(lpGroupInfo) error %d",iGroupSize );
		SRS_Dbg_WriteLog( cMsg );

		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		return( 0 );
	}

	//
	// 全情報獲得
	iRtn = SRS_Mng_AllGet( lpUserInfo, lpLobbyInfo, lpGroupInfo, 0 );
	if( iRtn == -1 )							// 獲得失敗？
	{
		SRS_Dbg_WriteLog( "SRS_Lby_GroupMake : SRS_Mng_AllGet error" );

		lpSendFix->IF_wResult = IF_CMP_SEQERR;	// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		realloc( lpGroupInfo, 0 );
		return( 0 );
	}

	// 管理情報設定
	lpSendUser 	= (struct SRS_INFO_USER *)lpUserInfo;
	lpSendLobby = (struct SRS_INFO_LOBBY *)lpLobbyInfo;
	lpSendGroup = (struct SRS_INFO_GROUP *)lpGroupInfo;

	iPoint = 0;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpSendUser, SRS_INFO_USER_COM_SZ );
	iPoint = SRS_INFO_USER_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
             lpSendUser->US_info_user[wUserID].USI_cClientName, SRS_USER_ITEM_SZ );
	iPoint = iPoint + SRS_USER_ITEM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpLobbyInfo, iLobbySize );
	
	sprintf( cMsg, "GroupMake: %d lobbyinfo", iPoint);
	SRS_Dbg_WriteLog( cMsg );
	iPoint = iPoint + iLobbySize;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpGroupInfo, iGroupSize );
	sprintf( cMsg, "GroupMake: %d Groupinfo", iPoint);
	SRS_Dbg_WriteLog( cMsg );

	//=======================================
	//  応答送信
	//=======================================
	sprintf( cMsg, "SRS_Lby_GroupMake : 応答送信 %d bytes", szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( cMsg, lpSendData, szSendSize, "ab" );

	iRtn = SRS_Net_SendReq( iClientIP, lpSendData, (size_t)szSendSize );

	realloc( lpUserInfo, 0 );
	realloc( lpLobbyInfo, 0 );
	realloc( lpGroupInfo, 0 );
	
	//=======================================
	//  更新情報配信
	//=======================================
    lpSendFix->IF_wRequest = IF_REQ_RENEWAL;					// 要求設定
	strcpy( cSendMode, SRS_SEND_MODE_NO );
	iRtn = SRS_Reg_GetInfo( SRS_REG_KEY_COM, SRS_REG_SEND, cSendMode );
	if( (strncmp(cSendMode, SRS_SEND_MODE_NO, sizeof(SRS_SEND_MODE_NO))) == 0 )	// 配信なし？
	{
		realloc( lpSendData, 0 );
		return( 0 );
	}
	//
    // 配信情報作成
	//
	sprintf( cMsg, "SRS_Lby_GroupMake : 更新情報配信 %d bytes",szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	iRtn = SRS_Lby_SendInfo( wUserID, wLobbyID, lpSendData, (size_t)szSendSize );

	realloc( lpSendData, 0 );
	return( 0 );
}

/*=============================================================================
     関数    ：グループ参加要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqGroupJoin( struct SRS_IF_FIX *lpIfFix )
{
	WORD	wLobbyID;							// ロビーＩＤ
	WORD	wGroupID;							// グループＩＤ
	int		iRtn;								// 
	int		iClientIP;							// 送信クライントＩＰ
	int		iUserSize;							// ユーザ情報域サイズ
	int		iGroupSize;							// グループ情報域サイズ
	int		iPoint;								//
	size_t	szSendSize;							// 送信サイズ
	struct	SRS_IF_FIX 		*lpSendFix;			// インタフェース域ポインタ
	struct	SRS_IF_GROUP_JOIN *lpGroupJoin;		// グループ参加情報域
	struct	SRS_REG_INFO	*lpRegInfo;			// 共通情報域ポインタ
	struct	SRS_IF_RENEWAL 	*lpSendRenewal;		// 送信用更新情報域ポインタ
	struct	SRS_INFO_USER	*lpSendUser;		// 送信用ユーザ管理情報域ポインタ
	struct  SRS_INFO_GROUP  *lpSendGroup;		// 送信用グループ管理情報域ポインタ
	struct	SRS_USER_ITEM   *lpUserItem;		// ユーザ情報域ポインタ
	char	*lpSendData;						// 送信データ域ポインタ
	char	*lpUserInfo;						// ユーザ管理情報域ポインタ
	char	*lpGroupInfo;						// グループ管理情報域ポインタ
	char	cRegInfo[SRS_REG_INFO_SZ];			// 共通情報域
	char	cUserItem[SRS_USER_ITEM_SZ];		// ユーザ情報域
	char	cIfFix[SRS_IF_FIX_SZ + SRS_IF_GROUP_JOIN_SZ];	// グループ参加情報域
	char	cSendMode[4];
	char	cMsg[256];


	sprintf( cMsg, "SRS_Lby_ReqGroupJoin : グループ参加 0x%04x",lpIfFix->IF_wRequest);
	SRS_Dbg_WriteLog( cMsg );

	memset( cIfFix, 0, SRS_IF_FIX_SZ + SRS_IF_GROUP_JOIN_SZ );
	memcpy( cIfFix, (char *)lpIfFix, SRS_IF_FIX_SZ + SRS_IF_GROUP_JOIN_SZ );
	lpSendFix = (struct SRS_IF_FIX *)cIfFix;
	iClientIP = lpIfFix->IF_iIp;

	//=======================================
	//  グループ参加
	//=======================================
	lpGroupJoin = (struct SRS_IF_GROUP_JOIN *)lpIfFix->IF_cInformation;
	wUserID  = lpGroupJoin->IF_GJ_wUserID;			// ユーザＩＤ設定
	wGroupID  = lpGroupJoin->IF_GJ_wGroupID;		// グループＩＤ設定
	iRtn = SRS_Mng_GetUserByID( wUserID, cUserItem );
	if( iRtn == -1 )
	{
		lpSendFix->IF_wRequest = IF_REQ_GROUP_JOIN;
		lpSendFix->IF_wResult = IF_CMP_SEQERR;		// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}
	lpUserItem = (struct SRS_USER_ITEM *)cUserItem;
	wLobbyID = lpUserItem->USI_wLobbyID;			// ロビーＩＤ設定

	iRtn = SRS_Mng_GroupJoin( lpSendFix );			// グループ参加
	if( iRtn == -1 )								// グループ参加失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_GROUP_JOIN;
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}

	//=======================================
	//  情報域サイズ算出
	//=======================================
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_GROUP_JOIN;
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		sprintf( cMsg, "SRS_Lby_ReqGroupJoin : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( -1 );
	}
	iUserSize  = SRS_Mng_GetMngSize( SRS_MNG_USER );			// ユーザ情報域サイズ
	iGroupSize = SRS_Mng_GetMngSize( SRS_MNG_GROUP );			// グループ情報域サイズ

	// 通知情報＝１ユーザ情報＋参加グループ情報
	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + 	// 情報サイズ
						  SRS_INFO_USER_SZ + SRS_INFO_GROUP_SZ );

	//=======================================
	//  送信情報域獲得（応答／配信用）
	//=======================================
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_GROUP_JOIN;		// 要求設定
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( 0 );
	}
	memset( lpSendData, 0, szSendSize );
	//=======================================
	//  応答作成
	//=======================================
	//
	// 固有域設定
	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
    lpSendFix->IF_wRequest = IF_REQ_GROUP_JOIN;						// 要求設定
	lpSendFix->IF_wResult = IF_CMP_SUCCESS;							// 結果正常
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;	//
	lpSendFix->IF_iPortNo = lpIfFix->IF_iPortNo;					// ポート番号コピー
	lpSendFix->IF_iIp = lpIfFix->IF_iIp;							// IPアドレスコピー

	//
	// 更新情報域設定
	lpSendRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpSendRenewal->IF_RE_wUserInfoNo  = 1;			// ユーザ数設定
	lpSendRenewal->IF_RE_wGroupInfoNo = 1;			// グループ数設定

	// ユーザ情報域獲得
	lpUserInfo = (char *)malloc( iUserSize );
	if( lpUserInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		return( 0 );
	}
	
	// グループ情報域獲得
	lpGroupInfo = (char *)malloc( iGroupSize );
	if( lpGroupInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		return( 0 );
	}

	//
	// 全情報獲得
	iRtn = SRS_Mng_AllGet( lpUserInfo, 0, lpGroupInfo, 0 );
	if( iRtn == -1 )							// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_SEQERR;	// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpGroupInfo, 0 );
		return( 0 );
	}

	// 管理情報設定
	lpSendUser 	= (struct SRS_INFO_USER *)lpUserInfo;
	lpSendGroup = (struct SRS_INFO_GROUP *)lpGroupInfo;

	iPoint = 0;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpSendUser, SRS_INFO_USER_COM_SZ );
	iPoint = SRS_INFO_USER_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
             lpSendUser->US_info_user[wUserID].USI_cClientName, SRS_USER_ITEM_SZ );
	iPoint = iPoint + SRS_USER_ITEM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpSendGroup, SRS_INFO_GROUP_COM_SZ );
	iPoint = iPoint + SRS_INFO_GROUP_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
            (char *)&lpSendGroup->GP_info_group[wGroupID].GPI_iLockword, SRS_GROUP_ITEM_SZ );

	//=======================================
	//  応答送信
	//=======================================
	sprintf( cMsg, "SRS_Lby_GroupJoin : 応答送信 %d bytes", szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( cMsg, lpSendData, szSendSize, "ab" );

	iRtn = SRS_Net_SendReq( iClientIP, lpSendData, (size_t)szSendSize );

	realloc( lpUserInfo, 0 );
	realloc( lpGroupInfo, 0 );
	
	//=======================================
	//  更新情報配信
	//=======================================
    lpSendFix->IF_wRequest = IF_REQ_RENEWAL;					// 要求設定
	strcpy( cSendMode, SRS_SEND_MODE_NO );
	iRtn = SRS_Reg_GetInfo( SRS_REG_KEY_COM, SRS_REG_SEND, cSendMode );
	if( (strncmp(cSendMode, SRS_SEND_MODE_NO, sizeof(SRS_SEND_MODE_NO))) == 0 )	// 配信なし？
	{
		realloc( lpSendData, 0 );
		return( 0 );
	}
	//
    // 配信情報作成
	//
	sprintf( cMsg, "SRS_Lby_GroupJoin : 更新情報配信 %d bytes",szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	iRtn = SRS_Lby_SendInfo( wUserID, wLobbyID, lpSendData, (size_t)szSendSize );

	realloc( lpSendData, 0 );
	return( 0 );
}

/*=============================================================================
     関数    ：グループ脱退要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqGroupDefect( struct SRS_IF_FIX *lpIfFix )
{
	WORD	wLobbyID;							// ロビーＩＤ
	WORD	wGroupID;							// グループＩＤ
	int		iRtn;								// 
	int		iClientIP;							// 送信クライントＩＰ
	int		iUserSize;							// ユーザ情報域サイズ
	int		iLobbySize;							// ロビー情報域サイズ
	int		iGroupSize;							// グループ情報域サイズ
	int		iPoint;								//
	size_t	szSendSize;							// 送信サイズ
	struct	SRS_IF_FIX 		*lpSendFix;			// インタフェース域ポインタ
	struct	SRS_IF_GROUP_DEFECT *lpGroupDefect;	// グループ脱退情報域
	struct	SRS_REG_INFO	*lpRegInfo;			// 共通情報域ポインタ
	struct	SRS_IF_RENEWAL 	*lpSendRenewal;		// 送信用更新情報域ポインタ
	struct	SRS_INFO_USER	*lpSendUser;		// 送信用ユーザ管理情報域ポインタ
	struct	SRS_INFO_LOBBY	*lpSendLobby;		// 送信用ロビー管理情報域ポインタ
	struct  SRS_INFO_GROUP  *lpSendGroup;		// 送信用グループ管理情報域ポインタ
	struct	SRS_USER_ITEM   *lpUserItem;		// ユーザ情報域ポインタ
	char	*lpSendData;						// 送信データ域ポインタ
	char	*lpUserInfo;						// ユーザ管理情報域ポインタ
	char	*lpLobbyInfo;						// ロビー管理情報域ポインタ
	char	*lpGroupInfo;						// グループ管理情報域ポインタ
	char	cRegInfo[SRS_REG_INFO_SZ];			// 共通情報域
	char	cUserItem[SRS_USER_ITEM_SZ];		// ユーザ情報域
	char	cIfFix[SRS_IF_FIX_SZ + SRS_IF_GROUP_DEFECT_SZ];	// グループ脱退情報域
	char	cSendMode[4];
	char	cMsg[256];


	sprintf( cMsg, "SRS_Lby_ReqGroupDefect : グループ脱退 0x%04x",lpIfFix->IF_wRequest);
	SRS_Dbg_WriteLog( cMsg );

	memset( cIfFix, 0, SRS_IF_FIX_SZ + SRS_IF_GROUP_DEFECT_SZ );
	memcpy( cIfFix, (char *)lpIfFix, SRS_IF_FIX_SZ + SRS_IF_GROUP_DEFECT_SZ );
	lpSendFix = (struct SRS_IF_FIX *)cIfFix;
	iClientIP = lpIfFix->IF_iIp;

	//=======================================
	//  グループ脱退
	//=======================================
	lpGroupDefect = (struct SRS_IF_GROUP_DEFECT *)lpIfFix->IF_cInformation;
	wUserID  = lpGroupDefect->IF_GD_wUserID;			// ユーザＩＤ設定
	wGroupID  = lpGroupDefect->IF_GD_wGroupID;			// グループＩＤ設定
	iRtn = SRS_Mng_GetUserByID( wUserID, cUserItem );
	if( iRtn == -1 )
	{
		lpSendFix->IF_wRequest = IF_REQ_GROUP_DEFECT;
		lpSendFix->IF_wResult = IF_CMP_SEQERR;			// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}
	lpUserItem = (struct SRS_USER_ITEM *)cUserItem;
	wLobbyID = lpUserItem->USI_wLobbyID;				// ロビーＩＤ設定

	iRtn = SRS_Mng_GroupDefect( lpSendFix );			// グループ脱退
	if( iRtn == -1 )									// グループ脱退失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_GROUP_DEFECT;
		lpSendFix->IF_iInformationSize = 0;
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}

	//=======================================
	//  情報域サイズ算出
	//=======================================
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_GROUP_DEFECT;	// 
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		sprintf( cMsg, "SRS_Lby_ReqGroupDefect : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( -1 );
	}
	iUserSize  = SRS_Mng_GetMngSize( SRS_MNG_USER );			// ユーザ情報域サイズ
	iLobbySize = SRS_Mng_GetMngSize( SRS_MNG_LOBBY );			// ロビー情報域サイズ
	iGroupSize = SRS_Mng_GetMngSize( SRS_MNG_GROUP );			// グループ情報域サイズ

	// 通知情報＝１ユーザ情報＋１ロビー情報＋１グループ情報
	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + 	// 情報サイズ
						  SRS_INFO_USER_SZ + SRS_INFO_LOBBY_SZ + SRS_INFO_GROUP_SZ );

	//=======================================
	//  送信情報域獲得（応答／配信用）
	//=======================================
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_GROUP_DEFECT;	// 要求設定
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( 0 );
	}
	memset( lpSendData, 0, szSendSize );
	//=======================================
	//  応答作成
	//=======================================
	//
	// 固有域設定
	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
    lpSendFix->IF_wRequest = IF_REQ_GROUP_DEFECT;					// 要求設定
	lpSendFix->IF_wResult = IF_CMP_SUCCESS;							// 結果正常
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;	//
	lpSendFix->IF_iPortNo = lpIfFix->IF_iPortNo;					// ポート番号コピー
	lpSendFix->IF_iIp = lpIfFix->IF_iIp;							// IPアドレスコピー

	//
	// 更新情報域設定
	lpSendRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpSendRenewal->IF_RE_wUserInfoNo  = 1;							// ユーザ数設定
	lpSendRenewal->IF_RE_wLobbyInfoNo = lpRegInfo->wMaxLobby + 1;	// ロビー数設定
	lpSendRenewal->IF_RE_wGroupInfoNo = 1;							// グループ数設定

	// ユーザ情報域獲得
	lpUserInfo = (char *)malloc( iUserSize );
	if( lpUserInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		return( 0 );
	}
	
	// ロビー情報域獲得
	lpLobbyInfo = (char *)malloc( iLobbySize );
	if( lpLobbyInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		return( 0 );
	}

	// グループ情報域獲得
	lpGroupInfo = (char *)malloc( iGroupSize );
	if( lpGroupInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		return( 0 );
	}

	//
	// 全情報獲得
	iRtn = SRS_Mng_AllGet( lpUserInfo, lpLobbyInfo, lpGroupInfo, 0 );
	if( iRtn == -1 )							// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_SEQERR;	// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		realloc( lpGroupInfo, 0 );
		return( 0 );
	}

	// 管理情報設定
	lpSendUser 	= (struct SRS_INFO_USER *)lpUserInfo;
	lpSendLobby = (struct SRS_INFO_LOBBY *)lpLobbyInfo;
	lpSendGroup = (struct SRS_INFO_GROUP *)lpGroupInfo;

	// ユーザ情報設定（１ユーザ）
	iPoint = 0;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpSendUser, SRS_INFO_USER_COM_SZ );
	iPoint = SRS_INFO_USER_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
             lpSendUser->US_info_user[wUserID].USI_cClientName, SRS_USER_ITEM_SZ );
	iPoint = iPoint + SRS_USER_ITEM_SZ;

	// ロビー情報設定（１ロビー）
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpLobbyInfo, SRS_INFO_LOBBY_COM_SZ );
	iPoint = iPoint + SRS_INFO_LOBBY_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
            (char *)&lpSendLobby->LB_info_lobby[wLobbyID].LBI_iLockword, SRS_LOBBY_ITEM_SZ );
	iPoint = iPoint + SRS_LOBBY_ITEM_SZ;

	// グループ情報設定（１グループ）
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpGroupInfo, SRS_INFO_GROUP_COM_SZ );
	iPoint = iPoint + SRS_INFO_GROUP_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
            (char *)&lpSendGroup->GP_info_group[wGroupID].GPI_iLockword, SRS_GROUP_ITEM_SZ );

	//=======================================
	//  応答送信
	//=======================================
	sprintf( cMsg, "SRS_Lby_GroupDefect : 応答送信 %d bytes", szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( cMsg, lpSendData, szSendSize, "ab" );

	iRtn = SRS_Net_SendReq( iClientIP, lpSendData, (size_t)szSendSize );

	realloc( lpUserInfo, 0 );
	realloc( lpLobbyInfo, 0 );
	realloc( lpGroupInfo, 0 );
	
	//=======================================
	//  更新情報配信
	//=======================================
    lpSendFix->IF_wRequest = IF_REQ_RENEWAL;					// 要求設定
	strcpy( cSendMode, SRS_SEND_MODE_NO );
	iRtn = SRS_Reg_GetInfo( SRS_REG_KEY_COM, SRS_REG_SEND, cSendMode );
	if( (strncmp(cSendMode, SRS_SEND_MODE_NO, sizeof(SRS_SEND_MODE_NO))) == 0 )	// 配信なし？
	{
		realloc( lpSendData, 0 );
		return( 0 );
	}
	//
    // 配信情報作成
	//
	sprintf( cMsg, "SRS_Lby_GroupDefect : 更新情報配信 %d bytes",szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	iRtn = SRS_Lby_SendInfo( wUserID, wLobbyID, lpSendData, (size_t)szSendSize );

	realloc( lpSendData, 0 );
	return( 0 );
}

/*=============================================================================
     関数    ：ゲーム参加要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqGameJoin( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;							//
	int		iRtnMng;						//
	int		iClientIP;						//
	struct	SRS_IF_FIX *lpSendIfFix;		//
	char	cIfFix[256];					//
	char	cMsg[256];						//

	sprintf( cMsg, "SRS_Lby_ReqGameJoin : ゲーム参加 0x%04x",lpIfFix->IF_wRequest );
	SRS_Dbg_WriteLog( cMsg );
	memset( cIfFix, 0, 256 );
	memcpy( cIfFix, (char *)lpIfFix, SRS_MAX_RCV );
	iRtnMng = SRS_Mng_GameJoin( (struct SRS_IF_FIX *)cIfFix );

	// 応答送信
	iClientIP = lpIfFix->IF_iIp;
	lpSendIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpSendIfFix->IF_iInformationSize = 0;
	iRtn = SRS_Net_SendReq( iClientIP, cIfFix, (size_t)SRS_IF_FIX_SZ );
	return( iRtn );
}

/*=============================================================================
     関数    ：ゲーム脱退要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqGameDefect( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;							//
	int		iRtnMng;						//
	int		iClientIP;						//
	struct	SRS_IF_FIX *lpSendIfFix;		//
	char	cIfFix[256];					//
	char	cMsg[256];						//

	sprintf( cMsg, "SRS_Lby_ReqGameDefect : ゲーム脱退 0x%04x",lpIfFix->IF_wRequest );
	SRS_Dbg_WriteLog( cMsg );
	memset( cIfFix, 0, 256 );
	memcpy( cIfFix, (char *)lpIfFix, SRS_MAX_RCV );
	iRtnMng = SRS_Mng_GameDefect( (struct SRS_IF_FIX *)cIfFix );

	// 応答送信
	iClientIP = lpIfFix->IF_iIp;
	lpSendIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpSendIfFix->IF_iInformationSize = 0;
	iRtn = SRS_Net_SendReq( iClientIP, cIfFix, (size_t)SRS_IF_FIX_SZ );
	return( iRtn );
}

/*=============================================================================
     関数    ：ゲーム開始要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqGameStart( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;							//
	int		iRtnMng;						//
	int		iClientIP;						//
	struct	SRS_IF_FIX *lpSendIfFix;		//
	char	cIfFix[256];					//
	char	cMsg[256];						//

	sprintf( cMsg, "SRS_Lby_ReqGameStart : ゲーム開始 0x%04x",lpIfFix->IF_wRequest );
	SRS_Dbg_WriteLog( cMsg );
	memset( cIfFix, 0, 256 );
	memcpy( cIfFix, (char *)lpIfFix, SRS_MAX_RCV );
	iRtnMng = SRS_Mng_GameStart( (struct SRS_IF_FIX *)cIfFix );

	// 応答送信
	iClientIP = lpIfFix->IF_iIp;
	lpSendIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpSendIfFix->IF_iInformationSize = 0;
	iRtn = SRS_Net_SendReq( iClientIP, cIfFix, (size_t)SRS_IF_FIX_SZ );
	return( iRtn );
}

/*=============================================================================
     関数    ：ゲーム終了要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqGameEnd( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;							//
	int		iRtnMng;						//
	int		iClientIP;						//
	struct	SRS_IF_FIX *lpSendIfFix;		//
	char	cIfFix[256];					//
	char	cMsg[256];						//

	sprintf( cMsg, "SRS_Lby_ReqGameEnd : ゲーム終了 0x%04x",lpIfFix->IF_wRequest );
	SRS_Dbg_WriteLog( cMsg );
	memset( cIfFix, 0, 256 );
	memcpy( cIfFix, (char *)lpIfFix, SRS_MAX_RCV );
	iRtnMng = SRS_Mng_GameEnd( (struct SRS_IF_FIX *)cIfFix );

	// 応答送信
	iClientIP = lpIfFix->IF_iIp;
	lpSendIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpSendIfFix->IF_iInformationSize = 0;
	iRtn = SRS_Net_SendReq( iClientIP, cIfFix, (size_t)SRS_IF_FIX_SZ );
	return( iRtn );
}

/*=============================================================================
     関数    ：固有情報待避要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqSaveInfo( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;							//
	char	cMsg[256];

	sprintf( cMsg, "SRS_Lby_ReqSaveInfo : 固有情報待避 0x%04x",lpIfFix->IF_wRequest );
	SRS_Dbg_WriteLog( cMsg );
	iRtn = SRS_Mng_SaveInfo( lpIfFix );

	return( iRtn );
}

/*=============================================================================
     関数    ：メッセージ送信要求
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqSendMsg( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;							//
	int		iDstIP;						// クライアントＩＰアドレス
	int		iSrcIP;
	size_t	szSize;							//
	WORD	wUserID;						// 送信元ユーザＩＤ
	struct	SRS_IF_FIX *lpLocalFix;			// ローカルインタフェース域ポインタ
	struct	SRS_IF_MESSAGE *lpIfMessage;	// メッセ－ジ域ポインタ
	struct	SRS_USER_ITEM *lpUserItem;		// ユーザ情報域ポインタ
	char	cIfFix[256];					// ローカルインタフェース域
	char	cUserItem[SRS_LOBBY_ITEM_SZ];	// ユーザ情報域
	char	cMsg[256];						


	iSrcIP = (int)lpIfFix->IF_iIp;
	//================================
	// ロビー内ユーザ情報獲得
	//================================
	sprintf( cMsg, "SRS_Lby_ReqSendMsg : メッセージ送信 0x%04x",lpIfFix->IF_wRequest );
	SRS_Dbg_WriteLog( cMsg );

	lpIfMessage = (struct SRS_IF_MESSAGE *)lpIfFix->IF_cInformation;
	wUserID = lpIfMessage->IF_MS_wUserID;
	iRtn = SRS_Mng_GetUserByID( wUserID, cUserItem );		// ユーザ情報獲得
	if( iRtn == -1 )										// 獲得失敗？
	{
		sprintf( cMsg, "SRS_Lby_ReqSendMsg : SRS_Mng_GetUserByID error ID=%04x",wUserID );
		SRS_Dbg_WriteLog( cMsg );
		return( 0 );
	}
	lpUserItem = (struct SRS_USER_ITEM *)cUserItem;
	iDstIP = lpUserItem->USI_iIp;							// 送信先IPアドレス

	//===============================
	// 要求作成
	//===============================
	szSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_MESSAGE_SZ);
	memset( cIfFix, 0, 256 );
	memcpy( cIfFix, (char *)lpIfFix, szSize );	// メッセージコピー
	lpLocalFix = (struct SRS_IF_FIX *)cIfFix;

	iRtn = SRS_Net_SendReq( iDstIP, (char *)cIfFix, szSize );

	//  チャットログ出力
	SRS_Lby_ChatLog( iSrcIP, iDstIP, lpIfMessage->IF_MS_cMessage );

	return( 0 );
}

/*=============================================================================
     関数    ：要求シーケンスエラー
     入力    ：lpIfFix  (インタフェース域ポインタ)
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (通信異常)

==============================================================================*/
int	 SRS_Lby_ReqSeqError( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;							//
	int		iClientIP;						//
	struct	SRS_IF_FIX	*lpSendIfFix;		//
	char	cIfFix[256];
	char	cMsg[256];						

	//=========================================
	//  応答作成＆送信（要求シーケンスエラー）
	//=========================================
	sprintf( cMsg, "SRS_Lby_ReqSeqError : ??? 0x%04x",lpIfFix->IF_wRequest );
	SRS_Dbg_WriteLog( cMsg );
	iClientIP = lpIfFix->IF_iIp;
	memcpy( cIfFix, (char *)lpIfFix, SRS_MAX_RCV );
	lpSendIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpSendIfFix->IF_wResult = IF_CMP_SEQERR;
	lpSendIfFix->IF_iInformationSize = 0;
	iRtn = SRS_Net_SendReq( iClientIP, cIfFix, (size_t)SRS_IF_FIX_SZ );
	return( iRtn );
}

/*=============================================================================
     関数    ：更新情報配信（ロビー内ユーザに更新情報を配信する）
     入力    ：wUserID   （更新元ユーザＩＤ)
			   wLobbyID	 （配信ロビーＩＤ）
               lpSendData（送信情報）
			   szSendSize（送信情報長）
     出力    ：なし
     戻り値  ： 0 (正常)
               -1 (異常)

==============================================================================*/
int	 SRS_Lby_SendInfo( WORD wUserID, WORD wLobbyID, char *lpSendData, size_t szSendSize )
{
	int		iRtn;								//
	int		iClientIP;							//
	WORD	wId;								//
	WORD	wSendUserID;						// 送信先ユーザID
	struct	SRS_USER_ITEM  *lpUserItem;			//
	struct	SRS_LOBBY_ITEM *lpLobbyItem;		//
	char	cLobbyItem[SRS_LOBBY_ITEM_SZ];		// ロビー情報格納域
	char	cUserItem[SRS_USER_ITEM_SZ];		// ユーザ情報格納域
	char	cMsg[256];

	sprintf( cMsg, "SRS_Lby_SendInfo start" );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( cMsg, lpSendData, szSendSize, "ab" );

	iRtn = SRS_Mng_GetLobbyByID( wLobbyID, cLobbyItem );	// ロビー情報獲得
	if( iRtn == -1 )
	{
		sprintf( cMsg, "SRS_Lby_SendInfo : SRS_Mng_GetLobbyByID error ID=%d",wLobbyID );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}

	//=========================================
	//  更新情報送信
	//=========================================
	lpLobbyItem = (struct SRS_LOBBY_ITEM *)cLobbyItem;
	lpUserItem = (struct SRS_USER_ITEM *)cUserItem;
	for( wId = 0 ; wId < lpLobbyItem->LBI_wMaxLobbyUser ; wId++ )
	{
		if( (lpLobbyItem->LBI_wUserID[wId] != 0) &&  		// ユーザＩＤ有効 ＆
            (lpLobbyItem->LBI_wUserID[wId] != wUserID) ) 	// 更新元ユーザ以外？
		{
			wSendUserID = lpLobbyItem->LBI_wUserID[wId];			// ユーザID設定
			iRtn = SRS_Mng_GetUserByID( wSendUserID, cUserItem );	// ユーザ情報獲得
			if( iRtn == 0 )
			{
				iClientIP = lpUserItem->USI_iIp;				// 送信先クライアントIP
				sprintf( cMsg, "SRS_Lby_SendInfo : Send UserID %d",lpLobbyItem->LBI_wUserID[wId] );
	    		SRS_Dbg_WriteLog( cMsg );
				iRtn = SRS_Net_SendReq( iClientIP, lpSendData, szSendSize );	// 情報送信
			}
		}
	}
	return( iRtn );
}


/*====================================================================
     関数   ：チャットログ出力

     入力   ：lpstrMsg    チャットメッセージ
     出力   ：なし
     戻り値 ：なし
====================================================================*/
void SRS_Lby_ChatLog(int SrcIP, int DstIP, LPSTR lpstrMsg)
{
	int			iRtn;
    FILE        *fFp = (FILE *)NULL;
    SYSTEMTIME  lpst;                    /* システム時間構造体のアドレス */
	char        cLogfile[256];
    char        cDate[64];
    char        cBuff[16];
	unsigned char *lpSaddr = (unsigned char *)&SrcIP;
	unsigned char *lpDaddr = (unsigned char *)&DstIP;



	memset( cBuff, 0, sizeof(cBuff) );
	iRtn = SRS_Dbg_GetRegChatlog( cBuff );			// チャットログ情報参照
	if( strcmp(cBuff, SRS_DBG_CHATLOG_OFF) == 0 )	// 出力なし？
	{
		return;
	}

	//
	GetLocalTime(&lpst);
	
	//
	//	ログファイルの作成
	//	１日単位でログファイルを作成する
	sprintf(cLogfile, FILE_CHATLOG, lpst.wYear % 100, lpst.wMonth, lpst.wDay);
    if ((fFp = fopen(cLogfile, "a")) == NULL)
		return;
	
	//	ログフォーマット
	//	hh:mm:ss.mmm 255.255.255.0 to 255.255.255.0 <メッセージ>
	//	  送信時間     送信元IP         送信先IP
#if 0
	sprintf(cDate, "%02d:%02d:%02d.%03d %d.%d.%d.%d to %d.%d.%d.%d",
	               lpst.wHour, lpst.wMinute, lpst.wSecond, lpst.wMilliseconds,
	               lpSaddr[0], lpSaddr[1], lpSaddr[2], lpSaddr[3],
	               lpDaddr[0], lpDaddr[1], lpDaddr[2], lpDaddr[3] );
#endif
	wsprintf(cDate, "%02d:%02d:%02d.%03d from %d.%d.%d.%d to %d.%d.%d.%d : %s\n" ,
	               lpst.wHour, lpst.wMinute, lpst.wSecond, lpst.wMilliseconds,
	               lpSaddr[0], lpSaddr[1], lpSaddr[2], lpSaddr[3],
	               lpDaddr[0], lpDaddr[1], lpDaddr[2], lpDaddr[3], lpstrMsg );
	fputs(cDate, fFp);

//	wsprintf(cDate, "%02d:%02d:%02d.%03d %x to %x : %s\n" ,
//	               lpst.wHour, lpst.wMinute, lpst.wSecond, lpst.wMilliseconds, SrcIP, DstIP, lpstrMsg );
//	fputs(cDate, fFp);
//	fputs(lpstrMsg, fFp);
//	fputc('\n', fFp);
	
	fclose( fFp );

	return;
}


/*=============================================================================
     関数   ：チャットログ情報参照
			（レジストリ内のチャットログ情報を参照する）

     入力   ：lpBuff  （結果格納域ポインタ）

     出力   ：lpRegBuff（参照結果）

     戻り値 ：正常 0
              異常 -1

==============================================================================*/
int SRS_Dbg_GetRegChatlog( char *lpBuff )
{
    LONG    lRtn;                       // 
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwSize;                     // レジストリ参照用パラメタ

    //===========================================
    // 指定キーオープン
    //===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, SRS_REG_KEY_CHATLOG, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS )     // オープン失敗？
    {
        return( -1 );
    }
    dwSize = 256;
    //===========================================
    // 指定項目参照 
    //===========================================
    lRtn = RegQueryValueEx( hKey, SRS_REG_CHATLOG_MODE, NULL, NULL, (unsigned char *)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        return( -1 );
    }
    RegCloseKey( hKey );

    return( 0 );
}






int	 SRS_Lby_ReqUserDeleteEX( struct SRS_IF_FIX *lpIfFix )
{
	WORD	wLobbyID;
	int		iRtn;							//
	int		iClientIP;						//
	int		iUserSize;						//
	int		iLobbySize;						//
	int		iPoint;							//
	size_t	szSendSize;						//
	struct	SRS_IF_FIX 		*lpSendFix;		//
	struct	SRS_IF_USER_DELETE *lpUserDelete;
	struct	SRS_IF_RENEWAL 	*lpSendRenewal;	// 更新情報域ポインタ
	struct	SRS_REG_INFO	*lpRegInfo;		// 共通情報域ポインタ
	struct	SRS_INFO_USER	*lpSendUser;	//
	struct	SRS_INFO_LOBBY	*lpSendLobby;	//
	struct	SRS_USER_ITEM	*lpUserItem;	//
	char	*lpSendData;					//
	char	*lpUserInfo;					//
	char	*lpLobbyInfo;					//
	char	cRegInfo[SRS_REG_INFO_SZ];		// 共通情報域
	char	cIfFix[SRS_IF_FIX_SZ + SRS_IF_USER_DELETE_SZ];	// ユーザ削除情報域
	char	cSendMode[4];
	char	cUserItem[SRS_USER_ITEM_SZ];
	char	cMsg[256];


	sprintf( cMsg, "SRS_Lby_ReqUserDelete : ユーザ削除 0x%04x",lpIfFix->IF_wRequest);
	SRS_Dbg_WriteLog( cMsg );

	memset( cIfFix, 0, SRS_IF_FIX_SZ + SRS_IF_USER_DELETE_SZ );
	memcpy( cIfFix, (char *)lpIfFix, SRS_IF_FIX_SZ + SRS_IF_USER_DELETE_SZ );
	lpSendFix = (struct SRS_IF_FIX *)cIfFix;
	iClientIP = lpIfFix->IF_iIp;

	SRS_Dbg_WriteLog( "Step 1" );
	//=======================================
	//  ユーザ削除
	//=======================================
	lpUserDelete = (struct SRS_IF_USER_DELETE *)lpIfFix->IF_cInformation;
	wUserID  = lpUserDelete->IF_UD_wUserID;			// ユーザＩＤ設定
	iRtn = SRS_Mng_GetUserByID( wUserID, cUserItem );
	if( iRtn == -1 )
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;
		lpSendFix->IF_wResult = IF_CMP_SEQERR;		// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
//		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}
	lpUserItem = (struct SRS_USER_ITEM *)cUserItem;
	wLobbyID = lpUserItem->USI_wLobbyID;			// ロビーＩＤ設定

	iRtn = SRS_Mng_UserDelete( lpSendFix );	// ユーザ削除
	if( iRtn == -1 )						// ユーザ削除失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;
		lpSendFix->IF_iInformationSize = 0;
//		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( iRtn );
	}

	SRS_Dbg_WriteLog( "Step 2" );
	//=======================================
	//  情報域サイズ算出
	//=======================================
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;	// ユーザ削除
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;		// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		sprintf( cMsg, "SRS_Lby_ReqUserDelete : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
//		iRtn = SRS_Net_SendReq( iClientIP, (char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( -1 );
	}
	szSendSize = (size_t)(SRS_IF_FIX_SZ + SRS_IF_RENEWAL_SZ + 	// 情報サイズ
						  SRS_INFO_USER_SZ + SRS_INFO_LOBBY_SZ );

	SRS_Dbg_WriteLog( "Step 3" );
	//=======================================
	//  情報獲得
	//=======================================
	lpSendData = (char *)malloc( szSendSize );
	if( lpSendData == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;		// 要求設定
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;			// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
//		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		return( 0 );
	}
	memset( lpSendData, 0, szSendSize );

	SRS_Dbg_WriteLog( "Step 4" );
	//=======================================
	//  応答作成
	//=======================================
	//
	// 固有域設定
	lpSendFix = (struct SRS_IF_FIX *)lpSendData;
    lpSendFix->IF_wRequest = IF_REQ_USER_DELETE;					// 要求設定
	lpSendFix->IF_wResult = IF_CMP_SUCCESS;							// 結果正常
	lpSendFix->IF_iInformationSize = szSendSize - SRS_IF_FIX_SZ;	//
	lpSendFix->IF_iPortNo = lpIfFix->IF_iPortNo;					// ポート番号コピー
	lpSendFix->IF_iIp = lpIfFix->IF_iIp;							// IPアドレスコピー

	//
	// 更新情報域設定
	lpSendRenewal = (struct SRS_IF_RENEWAL *)lpSendFix->IF_cInformation;
	lpSendRenewal->IF_RE_wUserInfoNo  = 1;		// ユーザ数設定
	lpSendRenewal->IF_RE_wLobbyInfoNo = 1;		// ロビー数設定

	iUserSize  = SRS_Mng_GetMngSize( SRS_MNG_USER );			// ユーザ情報域サイズ
	iLobbySize = SRS_Mng_GetMngSize( SRS_MNG_LOBBY );	    	// ロビー情報域サイズ
	// ユーザ情報
	lpUserInfo = (char *)malloc( iUserSize );
	if( lpUserInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
//		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		return( 0 );
	}
	
	// ロビー情報域
	lpLobbyInfo = (char *)malloc( iLobbySize );
	if( lpLobbyInfo == NULL )	// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_AREAOVER;	// 領域不足
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
//		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		return( 0 );
	}

	//
	// 全情報獲得
	iRtn = SRS_Mng_AllGet( lpUserInfo, lpLobbyInfo, 0, 0 );
	if( iRtn == -1 )							// 獲得失敗？
	{
		lpSendFix->IF_wResult = IF_CMP_SEQERR;	// 要求シーケンスエラー
		lpSendFix->IF_iInformationSize = 0;
		//
		// 応答送信（エラー）
//		iRtn = SRS_Net_SendReq( iClientIP,(char *)lpSendFix, (size_t)SRS_IF_FIX_SZ );
		realloc( lpSendData, 0 );
		realloc( lpUserInfo, 0 );
		realloc( lpLobbyInfo, 0 );
		return( 0 );
	}

	// 管理情報設定
	lpSendUser 	= (struct SRS_INFO_USER *)lpUserInfo;
	lpSendLobby = (struct SRS_INFO_LOBBY *)lpLobbyInfo;
	iPoint = 0;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpSendUser, SRS_INFO_USER_COM_SZ );
	iPoint = SRS_INFO_USER_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
             lpSendUser->US_info_user[wUserID].USI_cClientName, SRS_USER_ITEM_SZ );
	iPoint = iPoint + SRS_USER_ITEM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint], lpLobbyInfo, SRS_INFO_LOBBY_COM_SZ );
	iPoint = iPoint + SRS_INFO_LOBBY_COM_SZ;
	memcpy( (char *)&lpSendRenewal->IF_RE_cInfo[iPoint],
            (char *)&lpSendLobby->LB_info_lobby[wLobbyID].LBI_iLockword, SRS_LOBBY_ITEM_SZ );

	//=======================================
	//  応答送信
	//=======================================
	sprintf( cMsg, "SRS_Lby_UserDeleteEX : 応答送信 %d bytes", szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( cMsg, lpSendData, szSendSize, "ab" );

//	iRtn = SRS_Net_SendReq( iClientIP, lpSendData, (size_t)szSendSize );
	realloc( lpUserInfo, 0 );
	realloc( lpLobbyInfo, 0 );

	//=======================================
	//  更新情報配信
	//=======================================
    lpSendFix->IF_wRequest = IF_REQ_RENEWAL;					// 要求設定
	strcpy( cSendMode, SRS_SEND_MODE_NO );
	iRtn = SRS_Reg_GetInfo( SRS_REG_KEY_COM, SRS_REG_SEND, cSendMode );
	if( (strncmp(cSendMode, SRS_SEND_MODE_NO, sizeof(SRS_SEND_MODE_NO))) == 0 )	// 配信なし？
	{
		realloc( lpSendData, 0 );
		return( 0 );
	}
	//
    // 配信情報作成
	//
	sprintf( cMsg, "SRS_Lby_UserDeleteEX : 更新情報配信 %d bytes",szSendSize );
	SRS_Dbg_WriteLog( cMsg );
	iRtn = SRS_Lby_SendInfo( wUserID, wLobbyID, lpSendData, (size_t)szSendSize );

	realloc( lpSendData, 0 );
	return( 0 );
}
