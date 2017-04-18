/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSmanage.cpp
 *
 *					== 情報操作系関数 ==
 *					SRS_Mng_Startup		: 初期情報作成
 *					SRS_Mng_UserEntry	: ユーザ登録
 *					SRS_Mng_UserDelete	: ユーザ削除
 *					SRS_Mng_LobbyEntry	: ロビー参加
 *					SRS_Mng_LobbyDefect	: ロビー脱退
 *					SRS_Mng_GroupMake	: グループ作成
 *					SRS_Mng_GroupJoin	: グループ参加
 *					SRS_Mng_GroupDefect	: グループ脱退
 *					SRS_Mng_GameJoin	: ゲーム参加
 *					SRS_Mng_GameDefect	: ゲーム脱退
 *					SRS_Mng_GameEnd		: ゲーム終了
 *					SRS_Mng_GameStart	: ゲーム開始
 *					SRS_Mng_SaveInfo	: 固有情報待避
 *
 *					== 情報参照系関数 ==
 *					SRS_Mng_AllGet		   : 全情報獲得
 *                  SRS_Mng_GetMngSize	   : 管理情報域サイズ参照
 *					SRS_Mng_GetUserByName  : ユーザＩＤ参照
 *					SRS_Mng_GetUserByID    : ユーザ情報参照
 *					SRS_Mng_GetLobbyByName : ロビーＩＤ参照
 *					SRS_Mng_GetLobbyByID   : ロビー情報参照
 *					SRS_Mng_GetGroupByName : グループＩＤ参照
 *					SRS_Mng_GetGroupByID   : グループ情報参照
 *					SRS_Mng_GetEntry  	   : 登録数参照
 *
 *                  == 共通関数 ==
 *                  SRS_Mng_GetInfo		   : 管理情報読み込み
 *                  SRS_Mng_PutInfo		   : 管理情報書き込み
 *
 *  Content:    Lobby server サーバ情報管理ライブラリ
 *
 ***************************************************************************/
/*================================
    インクルード
==================================*/
#include <windows.h>
#include <stdio.h>

#include "SRScom.h"
#include "SRSmanage.h"
#include "SRSdebug.h"
#include "SRSregistry.h"

#define ROOTZ	0	// customize flag

/*================================
    グローバル域
==================================*/
int		iUserSize = 0;
int		iLobbySize = 0;
int		iGroupSize = 0;
int		iGameSize = 0;
struct 	SRS_INFO_USER	*lpInfoUser = 0;	// ユーザ情報域
struct	SRS_INFO_LOBBY	*lpInfoLobby = 0;	// ロビー情報域
struct	SRS_INFO_GROUP	*lpInfoGroup = 0;	// グループ情報域
struct  SRS_INFO_GAME	*lpInfoGame = 0;	// ゲーム情報域

/*=============================================================================
     関数   ：初期設定（Lobbyサーバ管理テーブル群を作成する）
				ユ－ザ情報域リスト
				ゲーム情報域
				ロビー情報域
				待ち合わせ情報域
     入力   ：なし
     出力   ：なし
     戻り値 ：正常 0
              異常 -1（メモリ不足）
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_Startup( void )
{
	int		iRtn;									//
	int		iAllocSize;								// 獲得サイズ
	int		iPoint;									// ロビー名テーブルポイント
	WORD	wMaxUser;								// 最大ユーザ数
	WORD	wMaxLobby;								// 最大ロビー数
	WORD	wMaxGame;								// 最大ゲーム数
	WORD	wMaxGroup;								// 最大グループ数
	WORD	wCount;									// 参加人数
	WORD	wID;									// ＩＤ生成用
	FILE	*fFp = (FILE *)NULL;					//
	struct	SRS_REG_INFO		*lpRegInfo;			// サーバ共通情報域ポインタ
	struct	SRS_REG_INFO_LOBBY	*lpRegInfoLobby;	// ロビー固有情報域ポインタ
	struct	SRS_REG_INFO_GAME	*lpRegInfoGame;		// ゲーム固有情報域ポインタ
	char	cRegInfo[SRS_REG_INFO_SZ];				// 共通管理情報域
	char	cMsg[256];								//


	//==============================================
	//  初期化
	//==============================================
	iUserSize = 0;
	iLobbySize = 0;
	iGroupSize = 0;
	iGameSize = 0;
	lpInfoUser = 0;
	lpInfoLobby = 0;
	lpInfoGroup = 0;
	lpInfoGame = 0;
	DeleteFile( SRS_PATH_USER );
	DeleteFile( SRS_PATH_LOBBY );
	DeleteFile( SRS_PATH_GROUP );
	DeleteFile( SRS_PATH_GAME );

	//==============================================
	//  可変情報取り込み
	//==============================================
	//
	// 共通管理情報
	//
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		sprintf( cMsg, "SRS_Mng_Startup : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	wMaxUser  =	lpRegInfo->wMaxUser;			// 最大ユーザ数
	wMaxLobby = lpRegInfo->wMaxLobby;			// 最大ロビー数
	wMaxGame  = lpRegInfo->wMaxGame;			// 最大ゲーム数
	wMaxGroup = lpRegInfo->wMaxGroup;			// 最大グループ数
	//
	// ロビー固有情報獲得
	//
	iAllocSize = SRS_REG_INFO_LOBBY_SZ * wMaxLobby;
	lpRegInfoLobby = (struct SRS_REG_INFO_LOBBY *)malloc( iAllocSize );
	if( lpRegInfoLobby == 0 )
	{
		sprintf( cMsg, "??? malloc SRS_REG_INFO_LOBBY (%d) ???", iAllocSize );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	iRtn = SRS_Reg_GetLobbyInfo( (int)wMaxLobby, lpRegInfoLobby );	// ロビー固有情報獲得
	if( iRtn == -1 )
	{
		realloc( (char *)lpInfoUser, 0 );
		realloc( (char *)lpInfoLobby, 0 );
		sprintf( cMsg, "SRS_Mng_Startup : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	//
	// ゲーム固有情報獲得
	//
	iAllocSize = SRS_REG_INFO_GAME_SZ * wMaxGame;
	lpRegInfoGame = (struct SRS_REG_INFO_GAME *)malloc( iAllocSize );
	if( lpRegInfoGame == 0 )
	{
		sprintf( cMsg, "??? malloc SRS_REG_INFO_GAME (%d) ???", iAllocSize );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	iRtn = SRS_Reg_GetGameInfo( (int)wMaxGame, lpRegInfoGame );		// ゲーム固有情報獲得
	if( iRtn == -1 )
	{
		sprintf( cMsg, "SRS_Mng_Startup : SRS_Reg_GetGameInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	
	//==============================================
	//  ユーザ情報域作成
	//==============================================
	iUserSize = SRS_USER_ITEM_SZ * (wMaxUser+1);
	iUserSize = iUserSize + SRS_INFO_USER_COM_SZ;
	lpInfoUser = (struct SRS_INFO_USER *)malloc( iUserSize );
	if( lpInfoUser == 0 )
	{
		sprintf( cMsg, "??? malloc SRS_INFO_USER (%d) ???", iUserSize );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	memset( (char *)lpInfoUser, 0, iUserSize );
	lpInfoUser->US_wMaxUser = wMaxUser;			// 最大ユーザ数設定
	//
	// ユーザＩＤ設定
	//
	for( wID = 0 ; wID < wMaxUser + 1 ; wID++ )
	{
		lpInfoUser->US_info_user[wID].USI_wUserID = wID;	// ユーザＩＤ設定
	}

	//==============================================
	//  ロビー情報域作成
	//==============================================
	iLobbySize = SRS_LOBBY_ITEM_SZ * wMaxLobby;
	iLobbySize = iLobbySize + SRS_INFO_LOBBY_COM_SZ;
	lpInfoLobby = (struct SRS_INFO_LOBBY *)malloc( iLobbySize );
	if( lpInfoLobby == 0 )
	{
		sprintf( cMsg, "??? malloc SRS_INFO_LOBBY (%d) ???", iLobbySize );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	memset( (char *)lpInfoLobby, 0, iLobbySize );
	lpInfoLobby->LB_wMaxLobby = wMaxLobby;					// 最大ロビー数設定
	//
	//  ロビー情報設定
	//
	for( wID=0, iPoint=1 ; wID < wMaxLobby ; wID++ )
	{
		lpInfoLobby->LB_info_lobby[wID].LBI_wLobbyID = wID; 		// ロビーＩＤ設定
		wCount = lpRegInfoLobby->wMaxUser;							//
		lpInfoLobby->LB_info_lobby[wID].LBI_wMaxLobbyUser = wCount;	// 最大参加人数設定
		memcpy( lpInfoLobby->LB_info_lobby[wID].LBI_cLobbyName, 	// ロビー名設定
										lpRegInfoLobby->cName, SRS_MAX_NAME_LOBBY );
		lpRegInfoLobby = lpRegInfoLobby + 1;
	}

	//==============================================
	//  グループ情報域作成
	//==============================================
	iGroupSize = SRS_GROUP_ITEM_SZ * (wMaxGroup+1);
	iGroupSize = iGroupSize + SRS_INFO_GROUP_COM_SZ;
	lpInfoGroup = (struct SRS_INFO_GROUP *)malloc( iGroupSize );
	if( lpInfoGroup == 0 )
	{
		sprintf( cMsg, "??? malloc SRS_INFO_GROUP (%d) ???", iGroupSize );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	memset( (char *)lpInfoGroup, 0, iGroupSize );
	lpInfoGroup->GP_wMaxGroup = wMaxGroup;			// 最大グループ数設定
	//
	// グループＩＤ設定
	//
	for( wID = 0 ; wID < wMaxGroup + 1; wID++ )
	{
		lpInfoGroup->GP_info_group[wID].GPI_wGroupID = wID;	//グループＩＤ設定
		lpInfoGroup->GP_info_group[wID].GPI_wMaxUser = 		//グループ内最大ユーザ数設定
											SRS_MAX_GROUP_USER;
	}

	//==============================================  
	//  ゲーム情報域作成
	//==============================================
	iGameSize = SRS_GAME_ITEM_SZ * (wMaxGame+1);
	iGameSize = iGameSize + SRS_INFO_GAME_COM_SZ;
	lpInfoGame = (struct SRS_INFO_GAME *)malloc( iGameSize );
	if( lpInfoGame == 0 )
	{
		sprintf( cMsg, "??? malloc SRS_INFO_GAME (%d) ???", iGameSize );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	memset( (char *)lpInfoGame, 0, iGameSize );
	lpInfoGame->GM_wMaxGame = wMaxGame;			// 最大ゲーム数設定
	lpInfoGame->GM_wEntryGame = 0;				// 登録ゲーム数設定

	//
	// ゲームＩＤ設定 
	//
	for( wID = 1 ; wID < wMaxGame + 1 ; wID++ )
	{
		lpInfoGame->GM_info_game[wID].GMI_wGameID = wID;			// ゲームＩＤ設定
		lpInfoGame->GM_wEntryGame = lpInfoGame->GM_wEntryGame + 1;	// 登録ゲーム数更新
		wCount = lpRegInfoGame->wMaxUser;							//
		lpInfoGame->GM_info_game[wID].GMI_wMaxGameUser = wCount;	// 最大参加人数設定
		memcpy( lpInfoGame->GM_info_game[wID].GMI_cGameName,		// ゲーム名設定
										lpRegInfoGame->cName, SRS_MAX_NAME_GAME );
		lpRegInfoGame = lpRegInfoGame + 1;
	}

	//=============================================
	//  情報待避
	//=============================================
	iRtn = SRS_Mng_PutInfo( );

	sprintf( cMsg, "userinfo=%d, lobbyinfo=%d, groupinfo=%d, gameinfo=%d",
             iUserSize, iLobbySize, iGroupSize, iGameSize);
	SRS_Dbg_WriteLog( cMsg );
	return( 0 );
}

/*=============================================================================
     関数   ：ユーザ登録（Lobbyサーバ管理テーブルに新規ユーザを登録する）
     入力   ：lpIfFix   インタフェースブロック
     出力   ：なし
     戻り値 ：正常 0
              異常 -1（登録ユーザ数オーバ）
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_UserEntry( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	int		iID;									// ロビー登録用ID
	WORD	wID;									// ユーザＩＤ
	struct  SRS_IF_USER_ENTRY	*lpUserEntry;		// ユーザ登録固有域ポインタ
	struct  SRS_IF_USER_DELETE	*lpUserDelete;		// ユーザ削除固有域ポインタ
	struct	SRS_IF_FIX			*lpIfFixLocal;		// 内部用インタフェース域ポインタ
	char	cIfFixLocal[256];						// 内部用インタフェース域
	char	cMsg[256];

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_SEQERR;
		SRS_Dbg_WriteLog( "SRS_Mng_UserEntry : SRS_Mng_GetInfo error" );
		return( -1 );
	}
	//==============================================  
	//  登録位置検索
	//==============================================
	if( lpInfoUser->US_wEntryUser >= lpInfoUser->US_wMaxUser )	// 登録オーバー？
	{
		lpIfFix->IF_wResult = IF_CMP_MAXOVER;
		SRS_Dbg_WriteLog( "SRS_Mng_UserEntry : MAX OVER" );
		return( -1 );
	}
	lpUserEntry = (struct SRS_IF_USER_ENTRY *)lpIfFix->IF_cInformation;

	//==============================================
	//	２重登録チェック
	//==============================================
	for( wID = 1 ; wID < lpInfoUser->US_wMaxUser ; wID++ )
	{
		if( lpInfoUser->US_info_user[wID].USI_dwCondetion != SRS_SEQ_NOENTRY )	// 登録済？
		{
			//
			// 同一クライアント名チェック
			//
			if( (memcmp( lpInfoUser->US_info_user[wID].USI_cClientName, 	// 同一クライアント名？
						 lpUserEntry->IF_UE_cClientName, SRS_MAX_NAME_CLIENT )) == 0 )
			{
				//
				// ユーザ削除
				// （なんらかの原因で使用されていないユーザ情報が残っていると判断する）
				//
				// ユーザ削除用インタフェース域作成
				lpIfFixLocal = (struct SRS_IF_FIX *)cIfFixLocal;
				memset( (char *)lpIfFixLocal, 0, sizeof(cIfFixLocal) );
				lpIfFixLocal->IF_wRequest = IF_REQ_USER_DELETE;
				lpIfFixLocal->IF_iInformationSize = 4;
				lpUserDelete = (struct SRS_IF_USER_DELETE *)&lpIfFixLocal->IF_cInformation[0];
				lpUserDelete->IF_UD_wUserID = lpInfoUser->US_info_user[wID].USI_wUserID;

				iRtn = SRS_Mng_UserDelete( (struct SRS_IF_FIX *)lpIfFixLocal );

				lpIfFix->IF_wResult = IF_CMP_MULTI;		// ２重登録エラー
				sprintf( cMsg, "SRS_Mng_UserEntry : client multi entry %s", lpUserEntry->IF_UE_cClientName);
				SRS_Dbg_WriteLog( cMsg );
				return( -1 );
			}
			//
			// 同一ユーザ名チェック
			//
			if( (memcmp( lpInfoUser->US_info_user[wID].USI_cUserName, 	// 同一ユーザ名？
						 lpUserEntry->IF_UE_cUserName, SRS_MAX_NAME_USER )) == 0 )
			{
				lpIfFix->IF_wResult = IF_CMP_MULTI;		// ２重登録エラー
				sprintf( cMsg, "SRS_Mng_UserEntry : user multi entry %s", lpUserEntry->IF_UE_cUserName);
				SRS_Dbg_WriteLog( cMsg );
				return( -1 );
			}
		}
	}
	//==============================================  
	//  登録位置検索
	//==============================================
	for( wID = 1 ; wID < lpInfoUser->US_wMaxUser + 1 ; wID++ )
	{
		if( lpInfoUser->US_info_user[wID].USI_dwCondetion == SRS_SEQ_NOENTRY )	// 未登録域？
		{
			// 情報設定
			lpInfoUser->US_wEntryUser = lpInfoUser->US_wEntryUser + 1;		// 登録数更新
			lpInfoUser->US_info_user[wID].USI_dwCondetion = SRS_SEQ_LOBBYENTRY;	// 状態→ロビー参加
   			lpInfoUser->US_info_user[wID].USI_iIp = lpIfFix->IF_iIp;		// ＩＰアドレス設定
			memcpy( lpInfoUser->US_info_user[wID].USI_cClientName,			// クライアント名設定
			 		lpUserEntry->IF_UE_cClientName, SRS_MAX_NAME_CLIENT );
			memcpy( lpInfoUser->US_info_user[wID].USI_cUserName,			// ユーザ名設定
			 		lpUserEntry->IF_UE_cUserName, SRS_MAX_NAME_USER );

			//==============================================  
			//  メインロビー登録
			//==============================================
			if( lpInfoLobby->LB_info_lobby[0].LBI_wLobbyUser + 1 >= 
				lpInfoLobby->LB_info_lobby[0].LBI_wMaxLobbyUser )
			{
				lpIfFix->IF_wResult = IF_CMP_MAXOVER;
				SRS_Dbg_WriteLog( "SRS_Mng_UserEntry : MAX OVER in lobby" );
				return( -1 );
			}
			lpInfoLobby->LB_info_lobby[0].LBI_wLobbyUser = 					// ロビー内ユーザ数更新
							lpInfoLobby->LB_info_lobby[0].LBI_wLobbyUser + 1;
			for( iID = 0 ; iID < lpInfoUser->US_wMaxUser ; iID++ )
			{
				if( lpInfoLobby->LB_info_lobby[0].LBI_wUserID[iID] == 0 )	// 空き？
				{
					lpInfoLobby->LB_info_lobby[0].LBI_wUserID[iID] = wID;	// ユーザID設定
					//=============================================
					//  情報待避
					//=============================================
					iRtn = SRS_Mng_PutInfo( );
					lpIfFix->IF_wResult = IF_CMP_SUCCESS;					// 登録成功
					return( 0 );
				}
			}
			lpIfFix->IF_wResult = IF_CMP_ERROR;			// 登録失敗（システムエラー）
			SRS_Dbg_WriteLog( "SRS_Mng_UserEntry : client multi entry" );
			return( -1 );
		}
	}
	// 登録位置なしの場合
	lpIfFix->IF_wResult = IF_CMP_ERROR;		// システムエラー
	SRS_Dbg_WriteLog( "SRS_Mng_UserEntry : 登録位置なし" );
	return( -1 );
}

/*=============================================================================
     関数    ：ユーザ削除（Lobbyサーバ管理テーブルからユーザを削除する）
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
	 特記事項：削除するユーザがグループ参加中の場合はグループ脱退をおこなう
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_UserDelete( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	WORD	wID;									// ＩＤ
	WORD	wUserID;								// ユーザＩＤ
	WORD	wLobbyID;								// ロビーＩＤ
	struct  SRS_IF_USER_DELETE	*lpUserDelete;		// ユーザ削除固有域ポインタ
	struct	SRS_IF_GROUP_DEFECT *lpGroupDefect;		// グループ削除固有域ポインタ
	struct	SRS_IF_FIX *lpIfFixLocal;				// 内部用インタフェース域ポインタ
	char	cIfFixLocal[256];						// 内部用インタフェース域
	char	cMsg[256];

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_SEQERR;
		SRS_Dbg_WriteLog( "SRS_Mng_UserDelete : SRS_Mng_GetInfo error" );
		return( -1 );
	}

	//=============================================
	// グループ情報からユーザ削除
	//=============================================
	lpUserDelete = (struct SRS_IF_USER_DELETE *)lpIfFix->IF_cInformation;
	wUserID = lpUserDelete->IF_UD_wUserID;					
	if( wUserID > lpInfoUser->US_wMaxUser )			// 不正ＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;
		sprintf( cMsg, "SRS_Mng_UserDelete : wrong ID %d", wUserID );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	if( lpInfoUser->US_info_user[wUserID].USI_wGroupID != 0 )		// グループ参加中？
	{
		// グループ脱退用インタフェース域作成
		memset( cIfFixLocal, 0, 256 );
		lpIfFixLocal = (struct SRS_IF_FIX *)cIfFixLocal;
		lpIfFixLocal->IF_wRequest = IF_REQ_GROUP_DEFECT;
		lpIfFixLocal->IF_iInformationSize = sizeof(struct SRS_IF_GROUP_DEFECT);
		lpGroupDefect = (struct SRS_IF_GROUP_DEFECT *)lpIfFixLocal->IF_cInformation;
    	lpGroupDefect->IF_GD_wUserID = wUserID;
    	lpGroupDefect->IF_GD_wGroupID = lpInfoUser->US_info_user[wUserID].USI_wGroupID;

		iRtn = SRS_Mng_GroupDefect( lpIfFixLocal );				// グループ脱退
		//==============================================  
		//  情報展開
		//==============================================
		iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
		if( iRtn == -1 )
		{
			lpIfFix->IF_wResult = IF_CMP_SEQERR;
			SRS_Dbg_WriteLog( "SRS_Mng_UserDelete : SRS_Mng_GetInfo error after GroupDefect" );
			return( -1 );
		}
	}

	//==============================================
	// ロビー情報からユーザ削除
	//==============================================
	wLobbyID = lpInfoUser->US_info_user[wUserID].USI_wLobbyID;
	for( wID = 0 ; wID < lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wMaxLobbyUser ; wID++ )
	{
		if( wUserID == lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wUserID[wID] )
		{
			lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wUserID[wID] = 0;	// ユーザＩＤ無効
			lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wLobbyUser =       // ロビー内ユーザ数更新
				lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wLobbyUser -1;
		}
	}
	//==============================================
	// ユーザ情報初期化
	//==============================================
	lpInfoUser->US_info_user[wUserID].USI_wLobbyID = 0;					// ロビーＩＤ
	lpInfoUser->US_info_user[wUserID].USI_wGroupID = 0;					// グループＩＤ
	lpInfoUser->US_info_user[wUserID].USI_iIp = 0;						// ＩＰアドレス
	memset( lpInfoUser->US_info_user[wUserID].USI_cClientName, 0,		// クライアント名
														SRS_MAX_NAME_CLIENT );
	memset( lpInfoUser->US_info_user[wUserID].USI_cUserName, 0, 		// ユーザ名
														SRS_MAX_NAME_USER );	
	memset( lpInfoUser->US_info_user[wUserID].USI_cUserArea, 0,			// ユーザ固有域
													 	SRS_MAX_USERAREA );	
	lpInfoUser->US_info_user[wUserID].USI_dwCondetion = SRS_SEQ_NOENTRY; // 状態→未登録
	lpInfoUser->US_wEntryUser = lpInfoUser->US_wEntryUser - 1;			 // 登録数更新
	lpIfFix->IF_wResult = IF_CMP_SUCCESS;								 // 削除成功

	//=============================================
	//  情報待避
	//=============================================
	iRtn = SRS_Mng_PutInfo( );
	return( 0 );
}

/*=============================================================================
     関数    ：ロビーユーザ参加（ロビー情報にユーザを登録する）
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_LobbyEntry( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	WORD	wUserID;								// ユーザＩＤ
	WORD	wLobbyID;								// ロビーＩＤ
	WORD	wOldLobbyID;							// 元ロビーＩＤ
	WORD	wID;									// 作業用ＩＤ
	struct	SRS_IF_LOBBY_ENTRY  *lpLobbyEntry;		// ロビー参加固有域ポインタ
	struct  SRS_USER_ITEM *lpUserItem;				//
	char	cUserItem[SRS_USER_ITEM_SZ];
	char	cMsg[256];

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_SEQERR;
		SRS_Dbg_WriteLog( "SRS_Mng_LobbyEntry : SRS_Mng_GetInfo error" );
		return( -1 );
	}

	lpLobbyEntry = (struct SRS_IF_LOBBY_ENTRY *)lpIfFix->IF_cInformation;
	wUserID = lpLobbyEntry->IF_LE_wUserID;			//
	wLobbyID = lpLobbyEntry->IF_LE_wLobbyID;		//

	//
	// ユーザ情報参照
	//
	memset( cUserItem, 0, SRS_USER_ITEM_SZ );
	iRtn = SRS_Mng_GetUserByID( wUserID, cUserItem );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_SEQERR;				// シーケンスエラー
		sprintf( cMsg, "SRS_Mng_LobbyEntry : SRS_Mng_GetUserByID error ID=%d",wUserID );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	lpUserItem = (struct SRS_USER_ITEM *)cUserItem;
	wOldLobbyID = lpUserItem->USI_wLobbyID;					// 元ロビーＩＤ待避
	//==============================================
	//  参加人数チェック
	//==============================================
	if( (lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wLobbyUser + 1) >=
						lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wMaxLobbyUser )
	{
		lpIfFix->IF_wResult = IF_CMP_MAXOVER;				// 最大数オーバ
		SRS_Dbg_WriteLog( "SRS_Mng_LobbyEntry : MAX OVER" );
		return( -1 );
	}
	
	//==============================================
	//  参加ユーザＩＤ設定
	//==============================================
	for( wID = 0 ; wID < lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wMaxLobbyUser ; wID++ )
	{
		if( lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wUserID[wID] == 0 ) // ユーザＩＤ未登録？
		{
			lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wUserID[wID] = wUserID;
			lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wLobbyUser =		// 参加ユーザ数更新
                           lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wLobbyUser + 1;
			lpInfoLobby->LB_info_lobby[wLobbyID].LBI_iLockword = 0;		// 排他解除

			lpInfoUser->US_info_user[wUserID].USI_wLobbyID = wLobbyID;	// 参加ロビーＩＤ設定

			//==============================================
			//	元ロビー脱退
			//==============================================
			lpInfoLobby->LB_info_lobby[wOldLobbyID].LBI_wLobbyUser = 
								lpInfoLobby->LB_info_lobby[wOldLobbyID].LBI_wLobbyUser - 1;
			for( wID=0 ; wID < lpInfoLobby->LB_info_lobby[wOldLobbyID].LBI_wMaxLobbyUser ; wID++ )
			{
				if( lpInfoLobby->LB_info_lobby[wOldLobbyID].LBI_wUserID[wID] == wUserID )
				{
					lpInfoLobby->LB_info_lobby[wOldLobbyID].LBI_wUserID[wID] = 0;
				}
			}
			lpIfFix->IF_wResult = IF_CMP_SUCCESS;					// 参加成功

			//=============================================
			//  情報待避
			//=============================================
			iRtn = SRS_Mng_PutInfo( );
			return( 0 );
		}
	}
	// 参加位置なしの場合
	
	lpIfFix->IF_wResult = IF_CMP_ERROR;						// システムエラー
	SRS_Dbg_WriteLog( "SRS_Mng_LobbyEntry : 参加位置なし(system error)" );

	return( -1 );
}

/*=============================================================================
     関数    ：ロビーユーザ脱退（ロビー情報からユーザを削除する）
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_LobbyDefect( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	WORD	wUserID;								// ユーザＩＤ
	WORD	wLobbyID;								// ロビーＩＤ
	WORD	wID;									// 作業用ＩＤ
	struct	SRS_IF_LOBBY_DEFECT  *lpLobbyDefect;	// ロビー脱退固有域ポインタ
//	char	cMsg[256];

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_SEQERR;
		SRS_Dbg_WriteLog( "SRS_Mng_LobbyDelete : SRS_Mng_GetInfo error" );
		return( -1 );
	}

	lpLobbyDefect = (struct SRS_IF_LOBBY_DEFECT *)lpIfFix->IF_cInformation;
	wUserID = lpLobbyDefect->IF_LD_wUserID;			//
	wLobbyID = lpLobbyDefect->IF_LD_wLobbyID;		//

	//=============================================
	//  ロビー脱退
	//=============================================
	// 該当ユーザＩＤ検索
	for( wID = 0 ; wID < lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wMaxLobbyUser ; wID++ )
	{
		if( lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wUserID[wID] == wUserID ) // ＩＤ一致？
		{
			lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wUserID[wID] = 0;		// ユーザＩＤクリア
			lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wLobbyUser =			// ロビー内ユーザ数更新
						lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wLobbyUser - 1;
			lpInfoUser->US_info_user[wUserID].USI_wLobbyID = 0;				// 参加ロビーＩＤクリア
			break;
		}
	}
	if( wID >= lpInfoLobby->LB_info_lobby[wLobbyID].LBI_wMaxLobbyUser )
	{
		lpIfFix->IF_wResult = IF_CMP_MAXOVER;								// 最大オーバ
		SRS_Dbg_WriteLog( "SRS_Mng_UserDelete : MAX OVER(system error)" );
		return( -1 );
	}

	//=============================================
	//  情報待避
	//=============================================
	iRtn = SRS_Mng_PutInfo( );	// 復帰チェックなし
	return( 0 );
}

/*=============================================================================
     関数    ：グループ作成（ロビー内にグループを作成する）
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GroupMake( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	WORD	wID;									//
	WORD	wUserID;								// ユーザＩＤ
	struct  SRS_IF_GROUP_MAKE	*lpGroupMake;		// グループ作成固有域ポインタ
	char	cMsg[256];

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_SEQERR;
		SRS_Dbg_WriteLog( "SRS_Mng_GroupMake : SRS_Mng_GetInfo error" );
		return( -1 );
	}

	//==============================================
	//  登録数チェック
	//==============================================
	if( lpInfoGroup->GP_wEntryGroup >= lpInfoGroup->GP_wMaxGroup )	// 登録オーバー？
	{
		lpIfFix->IF_wResult = IF_CMP_MAXOVER;
		SRS_Dbg_WriteLog( "SRS_Mng_GroupMake : MAX OVER" );
		return( -1 );
	}
	lpGroupMake = (struct SRS_IF_GROUP_MAKE *)lpIfFix->IF_cInformation;
	wUserID = lpGroupMake->IF_GM_wUserID;

	//==============================================  
	//  同名チェック
	//==============================================
	for( wID = 1 ; wID < lpInfoGroup->GP_wMaxGroup + 1 ; wID++ )
	{
		if( (strcmp(lpGroupMake->IF_GM_cGroupName,		// 同一グループ名？
					lpInfoGroup->GP_info_group[wID].GPI_cGroupName)) == 0 )
		{
			lpIfFix->IF_wResult = IF_CMP_MULTI;
			sprintf( cMsg, "SRS_Mng_GroupMake : multi group %s",lpGroupMake->IF_GM_cGroupName );
			SRS_Dbg_WriteLog( cMsg );
			return( -1 );
		}
	}
	//==============================================  
	//  登録位置検索
	//==============================================
	for( wID = 1 ; wID < lpInfoGroup->GP_wMaxGroup + 1 ; wID++ )
	{
		if( lpInfoGroup->GP_info_group[wID].GPI_cGroupName[0] == 0 )		// 未登録？
		{
			// 新グループ登録
			lpInfoGroup->GP_info_group[wID].GPI_iLockword = (int)wUserID;	// 排他開始
			lpInfoGroup->GP_info_group[wID].GPI_wUserID[0] = wUserID;		// ユーザID設定（主催）
			lpInfoGroup->GP_info_group[wID].GPI_wEntryUser = 1;				// 参加ユーザ数設定
			memcpy( lpInfoGroup->GP_info_group[wID].GPI_cGroupName,		// グループ名設定
					 lpGroupMake->IF_GM_cGroupName, SRS_MAX_NAME_GROUP );
			lpInfoGroup->GP_info_group[wID].GPI_iLockword = 0;				// 排他解除
			lpInfoGroup->GP_wEntryGroup =  									// 登録グループ数更新
									lpInfoGroup->GP_wEntryGroup + 1;
			lpInfoUser->US_info_user[wUserID].USI_wGroupID = wID;			// グループＩＤ設定
			lpInfoUser->US_info_user[wUserID].USI_dwCondetion = 			// 状態 ← グループ参加
														SRS_SEQ_GROUPENTRY;
			lpIfFix->IF_wResult = IF_CMP_SUCCESS;							// グループ作成成功

			//=============================================
			//  情報待避
			//=============================================
			iRtn = SRS_Mng_PutInfo( );
			return( 0 );
		}
	}
	// 登録位置なしの場合
	lpInfoGroup->GP_info_group[wID].GPI_iLockword = 0;		// 排他解除
	lpIfFix->IF_wResult = IF_CMP_ERROR;					// システムエラー
	SRS_Dbg_WriteLog( "SRS_Mng_GroupMake : 登録位置なし");
	return( -1 );
}
/*=============================================================================
     関数    ：グループ参加（すでにあるグループに参加する）
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GroupJoin( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	int		iSearch;								//
	WORD	wUserID;								// ユーザＩＤ
	WORD	wGroupID;								// グループＩＤ
	struct  SRS_IF_GROUP_JOIN	*lpGroupJoin;		// グループ参加固有域ポインタ
	char	cMsg[256];

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_SEQERR;
		return( -1 );
	}

	//==============================================  
	//  ＩＤチェック
	//==============================================
	lpGroupJoin = (struct SRS_IF_GROUP_JOIN *)lpIfFix->IF_cInformation;
	wUserID = lpGroupJoin->IF_GJ_wUserID;
	wGroupID = lpGroupJoin->IF_GJ_wGroupID;

	if( wUserID > lpInfoUser->US_wMaxUser )			// 不正ユーザＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;			// システムエラー
		sprintf( cMsg, "SRS_Mng_GroupJoin : wrong User ID %d",wUserID );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	if( wGroupID > lpInfoGroup->GP_wMaxGroup )		// 不正グループＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;			// システムエラー
		sprintf( cMsg, "SRS_Mng_GroupJoin : wrong Group ID %d",wGroupID );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}

	//==============================================  
	//  参加人数チェック
	//==============================================
	if( lpInfoGroup->GP_info_group[wGroupID].GPI_wEntryUser >= 	// 定員オーバ？
		lpInfoGroup->GP_info_group[wGroupID].GPI_wMaxUser )
	{
		lpIfFix->IF_wResult = IF_CMP_MAXOVER;					// 最大数オーバ
		sprintf( cMsg, "SRS_Mng_GroupJoin : MAX OVER" );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	
	//==============================================  
	//  グループ参加
	//==============================================
	lpInfoGroup->GP_info_group[wGroupID].GPI_iLockword = wUserID;	// 排他開始

	// 参加位置検索
	for( iSearch = 1 ; iSearch < lpInfoGroup->GP_info_group[wGroupID].GPI_wMaxUser ; iSearch++ )
	{
		if( lpInfoGroup->GP_info_group[wGroupID].GPI_wUserID[iSearch] == 0 ) // 空き？
		{
			lpInfoGroup->GP_info_group[wGroupID].GPI_wUserID[iSearch] = wUserID; //ユーザＩＤ設定
			lpInfoGroup->GP_info_group[wGroupID].GPI_wEntryUser =			// 参加ユーザ数更新
					lpInfoGroup->GP_info_group[wGroupID].GPI_wEntryUser + 1;
			lpInfoGroup->GP_info_group[wGroupID].GPI_iLockword = 0;			// 排他解除

			lpInfoUser->US_info_user[wUserID].USI_wGroupID = wGroupID;		// グループＩＤ設定
			lpInfoUser->US_info_user[wUserID].USI_dwCondetion = 			// 状態 ← グループ参加
														SRS_SEQ_GROUPENTRY;
			lpIfFix->IF_wResult = IF_CMP_SUCCESS;

			//=============================================
			//  情報待避
			//=============================================	
			iRtn = SRS_Mng_PutInfo( );
			return( 0 );
		}
	}
	// 参加位置がない場合
	lpInfoGroup->GP_info_group[wGroupID].GPI_iLockword = 0;	// 排他解除
	lpIfFix->IF_wResult = IF_CMP_ERROR;					// システムエラー
	sprintf( cMsg, "SRS_Mng_GroupJoin : 参加位置なし" );
	SRS_Dbg_WriteLog( cMsg );

	return( -1 );
}
/*=============================================================================
     関数    ：グループ脱退（グループから脱退する）
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GroupDefect( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	int		iSearch;								//
	WORD	wUserID;								// ユーザＩＤ
	WORD	wGroupID;								// グループＩＤ
	struct  SRS_IF_GROUP_DEFECT	*lpGroupDefect;		// グループ脱退固有域ポインタ
	char	cMsg[256];

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_SEQERR;
		SRS_Dbg_WriteLog( "SRS_Mng_GroupDefect : SRS_Mng_GetInfo error" );
		return( -1 );
	}

	//==============================================  
	//  ＩＤチェック
	//==============================================
	lpGroupDefect = (struct SRS_IF_GROUP_DEFECT *)lpIfFix->IF_cInformation;
	wUserID = lpGroupDefect->IF_GD_wUserID;
	wGroupID = lpGroupDefect->IF_GD_wGroupID;

	if( wUserID >= lpInfoUser->US_wMaxUser )		// 不正ユーザＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;			// システムエラー
		sprintf( cMsg, "SRS_Mng_GroupDefect : wrong User ID %d",wUserID );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	if( wGroupID > lpInfoGroup->GP_wMaxGroup )		// 不正グループＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;			// システムエラー
		sprintf( cMsg, "SRS_Mng_GroupDefect : wrong Group ID %d",wGroupID );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}

	//==============================================  
	//  参加ユーザ削除
	//==============================================
	lpInfoGroup->GP_info_group[wGroupID].GPI_iLockword = wUserID;	// 排他開始
	// 削除ユーザ検索
	for( iSearch = 0 ; iSearch < lpInfoGroup->GP_info_group[wGroupID].GPI_wMaxUser ; iSearch++ )
	{
		if( lpInfoGroup->GP_info_group[wGroupID].GPI_wUserID[iSearch] == wUserID )	// ＩＤ一致？
		{
			lpInfoGroup->GP_info_group[wGroupID].GPI_wUserID[iSearch] = 0;			// ＩＤクリア
			lpInfoGroup->GP_info_group[wGroupID].GPI_wEntryUser =					// 参加人数更新
						lpInfoGroup->GP_info_group[wGroupID].GPI_wEntryUser - 1;
			if( lpInfoGroup->GP_info_group[wGroupID].GPI_wEntryUser == 0 )		// 参加ユーザなし？
			{
				//
				//	グループ削除
				//
				lpInfoGroup->GP_wEntryGroup = 								// 登録グループ数更新
												lpInfoGroup->GP_wEntryGroup - 1;
				memset( lpInfoGroup->GP_info_group[wGroupID].GPI_cGroupName,	// グループ名クリア
															 0, SRS_MAX_NAME_GROUP );
				lpInfoGroup->GP_info_group[wGroupID].GPI_wGameID = 0;		// ゲームＩＤクリア
			}
			lpInfoGroup->GP_info_group[wGroupID].GPI_iLockword = 0;			// 排他解除

			lpInfoUser->US_info_user[wUserID].USI_wGroupID = 0;				// グループＩＤクリア
			lpInfoUser->US_info_user[wUserID].USI_dwCondetion = SRS_SEQ_GAMEENTRY; // 状態 ← ゲーム選択
														
			//=============================================
			//  情報待避
			//=============================================
			iRtn = SRS_Mng_PutInfo( );
			lpIfFix->IF_wResult = IF_CMP_SUCCESS;				// グループ脱退成功
			return( 0 );
		}
	}
	// 同一ユーザＩＤがない場合
	lpInfoGroup->GP_info_group[wGroupID].GPI_iLockword = 0;		// 排他解除
	lpIfFix->IF_wResult = IF_CMP_ERROR;							// システムエラー
	sprintf( cMsg, "SRS_Mng_GroupDefect : 削除ユーザＩＤなし group=%d, user=%d",wGroupID,wUserID );
	SRS_Dbg_WriteLog( cMsg );
	return( -1 );
}

/*=============================================================================
     関数    ：全情報参照（全管理情報を通知する）
     入力    ：lpUser   ユーザ情報格納域ポインタ（情報不要の場合はNULLポインタ）
			   lpLobby	ロビー情報格納域ポインタ（情報不要の場合はNULLポインタ）
			   lpGroup	グループ情報格納域ポインタ（情報不要の場合はNULLポインタ）
			   lpGame   ゲーム情報格納域ポインタ（情報不要の場合はNULLポインタ）
     出力    ：なし
     戻り値  ：正常 0
               異常 -1

=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_AllGet( char *lpUser, char *lpLobby,
													 char *lpGroup, char *lpGame )
{
	int		iRtn;							//

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	//==============================================
	//  情報獲得
	//==============================================
	if( lpUser != NULL )		// ユーザ情報獲得？
	{
		memcpy( lpUser, lpInfoUser, iUserSize );
	}
	if( lpLobby != NULL )		// ロビー情報獲得？
	{
		memcpy( lpLobby, lpInfoLobby, iLobbySize );
	}

#if ROOTZ
	if( lpGroup != NULL )		// グループ情報獲得？
	{
		memcpy( lpGroup, lpInfoGroup, iGroupSize );
	}
	if( lpGame != NULL )		// ゲーム情報獲得？
	{
		memcpy( lpGame, lpInfoGame, iGameSize );
	}
#endif

	return( 0 );
}

/*=============================================================================
     関数    ：管理情報域サイズ参照（指定された管理情報域サイズを通知する）
     入力    ：iKind   管理情報域種別
                       SRS_MNG_USER	（ユーザ情報）
					   SRS_MNG_LOBBY（ロビー情報）
					   SRS_MNG_GROUP（グループ情報）
					   SRS_MNG_GAME	（ゲーム情報）
     出力    ：なし
     戻り値  ：正常 情報域サイズ
               異常 -1

=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GetMngSize( int iKind )
{
	int		iRtn;							//
	int		iSize;							//

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	//==============================================
	//  情報サイズ獲得
	//==============================================
	switch( iKind )	
	{
		case SRS_MNG_USER  : iSize = iUserSize;
							 break;
		case SRS_MNG_LOBBY : iSize = iLobbySize;
							 break;
		case SRS_MNG_GROUP : iSize = iGroupSize;
							 break;
		case SRS_MNG_GAME  : iSize = iGameSize;
							 break;
		default            : iSize = -1;
							 break;
	}
	return( iSize );
}

/*=============================================================================
     関数    ：ゲーム参加
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GameJoin( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	WORD	wID;									//
	struct	SRS_IF_GAME_JOIN *lpGameJoin;			//
	
	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;
		return( -1 );
	}
	//==============================================
	//  情報更新
	//==============================================
	lpGameJoin = (struct SRS_IF_GAME_JOIN *)lpIfFix->IF_cInformation;
	wID = lpGameJoin->IF_GJ_wUserID;
	if( wID >= lpInfoUser->US_wMaxUser )			// 不正ＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;			// システムエラー
		return( -1 );
	}
	lpInfoUser->US_info_user[wID].USI_wGameID = lpGameJoin->IF_GJ_wGameID;	// ゲームID設定
	lpInfoUser->US_info_user[wID].USI_dwCondetion = SRS_SEQ_GAMEENTRY;		// 状態 ← ゲーム選択
	lpIfFix->IF_wResult = IF_CMP_SUCCESS;	

	//=============================================
	//  情報待避
	//=============================================
	iRtn = SRS_Mng_PutInfo( );
	return( 0 );
}

/*=============================================================================
     関数    ：ゲーム脱退
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GameDefect( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	WORD	wID;									//
	struct	SRS_IF_GAME_DEFECT *lpGameDefect;		//
	
	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;
		return( -1 );
	}
	//==============================================
	//  情報更新
	//==============================================
	lpGameDefect = (struct SRS_IF_GAME_DEFECT *)lpIfFix->IF_cInformation;
	wID = lpGameDefect->IF_GD_wUserID;
	if( wID >= lpInfoUser->US_wMaxUser )			// 不正ＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;			// システムエラー
		return( -1 );
	}
	lpInfoUser->US_info_user[wID].USI_wGameID = 0;	// ゲームIDクリア
	lpInfoUser->US_info_user[wID].USI_dwCondetion = SRS_SEQ_LOBBYENTRY;	// 状態 ← ロビー参加
	lpIfFix->IF_wResult = IF_CMP_SUCCESS;	

	//=============================================
	//  情報待避
	//=============================================
	iRtn = SRS_Mng_PutInfo( );
	return( 0 );
}

/*=============================================================================
     関数    ：ゲーム開始
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GameStart( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	WORD	wID;									//
	struct	SRS_IF_GAME_START *lpGameStart;			//
	
	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;
		return( -1 );
	}
	//==============================================
	//  情報更新
	//==============================================
	lpGameStart = (struct SRS_IF_GAME_START *)lpIfFix->IF_cInformation;
	wID = lpGameStart->IF_GS_wUserID;
	if( wID >= lpInfoUser->US_wMaxUser )			// 不正ＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;			// システムエラー
		return( -1 );
	}
	lpInfoUser->US_info_user[wID].USI_dwCondetion = SRS_SEQ_PLAY;	// 状態 ← ゲーム中
	lpIfFix->IF_wResult = IF_CMP_SUCCESS;	

	//=============================================
	//  情報待避
	//=============================================
	iRtn = SRS_Mng_PutInfo( );
	return( 0 );
}

/*=============================================================================
     関数    ：ゲーム終了
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GameEnd( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	WORD	wID;									//
	struct	SRS_IF_GAME_END *lpGameEnd;				//
	
	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;
		return( -1 );
	}

	//==============================================
	//  情報更新
	//==============================================
	lpGameEnd = (struct SRS_IF_GAME_END *)lpIfFix->IF_cInformation;
	wID = lpGameEnd->IF_GE_wUserID;
	if( wID >= lpInfoUser->US_wMaxUser )			// 不正ＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;			// システムエラー
		return( -1 );
	}
	lpInfoUser->US_info_user[wID].USI_dwCondetion = SRS_SEQ_GROUPENTRY;	// 状態 ← グループ参加
	lpIfFix->IF_wResult = IF_CMP_SUCCESS;	

	//=============================================
	//  情報待避
	//=============================================
	iRtn = SRS_Mng_PutInfo( );
	return( 0 );
}

/*=============================================================================
     関数    ：固有情報待避
     入力    ：lpIfFix   インタフェースブロック
     出力    ：なし
     戻り値  ：正常 0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_SaveInfo( struct SRS_IF_FIX *lpIfFix )
{
	int		iRtn;									//
	WORD	wID;									//
	struct	SRS_IF_SAVE_INFO *lpSaveInfo;			//
	
	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;
		return( -1 );
	}

	//==============================================
	//  情報更新
	//==============================================
	lpSaveInfo = (struct SRS_IF_SAVE_INFO *)lpIfFix->IF_cInformation;
	wID = lpSaveInfo->IF_SI_wUserID;
	if( wID >= lpInfoUser->US_wMaxUser )			// 不正ＩＤ？
	{
		lpIfFix->IF_wResult = IF_CMP_ERROR;			// システムエラー
		return( -1 );
	}
	memcpy( lpInfoUser->US_info_user[wID].USI_cUserArea,lpSaveInfo->IF_SI_cInfo,SRS_MAX_USERAREA );

	//=============================================
	//  情報待避
	//=============================================
	iRtn = SRS_Mng_PutInfo( );
	return( 0 );
}

/*=============================================================================
     関数    ：ユーザＩＤ獲得（ユーザ名に対応するユーザＩＤを獲得する）
     入力    ：lpUserName  ユーザ名域ポインタ（２０バイト以上を保証すること）
     出力    ：なし
     戻り値  ：正常 ユーザＩＤ
               異常 SRS_WORD_ERROR (65535)
	 特記事項：ユーザ名の最後はＮＵＬＬが設定されていること
=============================================================================*/
__declspec( dllexport )WORD __stdcall SRS_Mng_GetUserByName( char *lpUserName )
{
	int		iRtn;								//
	WORD	wID;								//
//	char	cMsg[256];

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( SRS_WORD_ERROR );
	}

	//==============================================
	// 該当ユーザ検索
	//==============================================
	for( wID = 0 ; wID < lpInfoUser->US_wMaxUser ; wID++ )
	{
		if( (memcmp( lpInfoUser->US_info_user[wID].USI_cUserName,	// ユーザ名一致？
					  lpUserName, SRS_MAX_NAME_USER )) == 0 )
		{
			return( wID );
		}
	}
	return( SRS_WORD_ERROR );
}

// 千葉が追加
//
// IPからユーザIDをとって来る
__declspec( dllexport )WORD __stdcall SRS_Mng_GetUserByIP( int ip )
{
	int		iRtn;								//
	WORD	wID;								//

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( SRS_WORD_ERROR );
	}

	//==============================================
	// 該当ユーザ検索
	//==============================================
	for( wID = 0 ; wID < lpInfoUser->US_wMaxUser ; wID++ )
	{
/*
		{
			char str[64], str2[32];
			int i;
			i = lpInfoUser->US_info_user[wID].USI_iIp;
			sprintf( str2, "%d", wID );
			sprintf( str, "%d.%d.%d.%d\n%d.%d.%d.%d", (ip >> 24 & 0xff), (ip >> 16 & 0xff), (ip >> 8 & 0xff), (ip & 0xff), (i >> 24 & 0xff), (i >> 16 & 0xff), (i >> 8 & 0xff), (i & 0xff) );
			MessageBox( NULL, str, str2, MB_OK );
		}
*/
		if ( lpInfoUser->US_info_user[wID].USI_iIp == ip )	// ユーザ名一致？
		{
			return( wID );
		}
	}
	return( SRS_WORD_ERROR );
}

/*=============================================================================
     関数    ：ロビーＩＤ獲得（ロビー名に対応するロビーＩＤを獲得する）
     入力    ：lpLobbyName  ロビー名域ポインタ（１６バイト以上を保証すること）
     出力    ：なし
     戻り値  ：正常 ロビーＩＤ
               異常 SRS_WORD_ERROR(65535)
	 特記事項：ロビー名の最後はＮＵＬＬが設定されていること
=============================================================================*/
__declspec( dllexport )WORD __stdcall SRS_Mng_GetLobbyByName( char *lpLobbyName )
{
	int		iRtn;								//
	WORD	wID;								//

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( SRS_WORD_ERROR );
	}

	//==============================================
	//  該当ロビー検索
	//==============================================
	for( wID = 0 ; lpInfoLobby->LB_wMaxLobby ; wID++ )
	{
		if( (memcmp( lpInfoLobby->LB_info_lobby[wID].LBI_cLobbyName,  // ロビー名一致？
										 lpLobbyName, SRS_MAX_NAME_LOBBY )) == 0 )
		{
			return( wID );
		}
	}
	return( SRS_WORD_ERROR );
}

/*=============================================================================
     関数    ：グループＩＤ獲得（グループ名に対応するグループＩＤを獲得する）
     入力    ：lpLobbyName  グループ名域ポインタ（２０バイト以上を保証すること）
     出力    ：なし
     戻り値  ：正常 グループＩＤ
               異常 SRS_WORD_ERROR(65535)
	 特記事項：グループ名の最後はＮＵＬＬが設定されていること
=============================================================================*/
__declspec( dllexport )WORD __stdcall SRS_Mng_GetGroupByName( char *lpGroupName )
{
	int		iRtn;								//
	WORD	wID;								//

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( SRS_WORD_ERROR );
	}

	//==============================================
	//  該当グループ検索
	//==============================================
	for( wID = 0 ; lpInfoGroup->GP_wMaxGroup ; wID++ )
	{
		if( (memcmp( lpInfoGroup->GP_info_group[wID].GPI_cGroupName, 	// グループ名一致？
										 lpGroupName, SRS_MAX_NAME_GROUP )) == 0 )
		{
			return( wID );
		}
	}
	return( SRS_WORD_ERROR );
}

/*=============================================================================
     関数    ：ユーザ情報獲得（ユーザＩＤに対応するユーザ情報を獲得する）
     入力    ：wUserName  ユーザID
			   lpUserInfo ユーザ情報格納域アドレス
                         （領域有効長は SRS_USER_ITEM 構造体 以上を保証すること）
     出力    ：ユーザ情報 （指定されたユーザ情報域に情報がコピーされる）
     戻り値  ：正常  0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GetUserByID( WORD wUserID, char *lpUserInfo )
{
	int		iRtn;
	int		iItemSize;

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( -1 );
	}

	//==============================================
	//  該当ユーザ情報獲得
	//==============================================
	iItemSize  = SRS_USER_ITEM_SZ;
	memset( lpUserInfo, 0, iItemSize );
	if( wUserID >= lpInfoUser->US_wMaxUser )	// 不正ＩＤ？
	{
		return( -1 );
	}
	memcpy( lpUserInfo,
            (char *)lpInfoUser->US_info_user[wUserID].USI_cClientName,	SRS_USER_ITEM_SZ );
	return( 0 );
}

/*=============================================================================
     関数    ：ロビー情報獲得（ロビーＩＤに対応するロビー情報を獲得する）
     入力    ：wLobbyName  ロビーID
			   lpLobbyInfo ロビー情報格納域アドレス
                         （領域有効長は SRS_LOBBY_ITEM_SZ 以上を保証すること）
     出力    ：ロビー情報 （指定されたロビー情報域に情報がコピーされる）
     戻り値  ：正常  0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GetLobbyByID( WORD wLobbyID, char *lpLobbyInfo )
{
	int		iRtn;	

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( -1 );
	}

	//==============================================
	//  該当ロビー情報獲得
	//==============================================
	memset( lpLobbyInfo, 0, SRS_LOBBY_ITEM_SZ );
	if( wLobbyID >= lpInfoLobby->LB_wMaxLobby )	// 不正ＩＤ？
	{
		return( -1 );
	}
	memset( lpLobbyInfo, 0, SRS_LOBBY_ITEM_SZ );
	memcpy( lpLobbyInfo,
            (char *)&(lpInfoLobby->LB_info_lobby[wLobbyID].LBI_iLockword),	SRS_LOBBY_ITEM_SZ );

	return( 0 );
}

/*=============================================================================
     関数    ：グループ情報獲得（グループＩＤに対応するグループ情報を獲得する）
     入力    ：wLobbyName  グループID
			   lpLobbyInfo グループ情報格納域アドレス
                         （領域有効長は SRS_GROUP_ITEM_SZ 以上を保証すること）
     出力    ：グループ情報 （指定されたグループ情報域に情報がコピーされる）
     戻り値  ：正常  0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GetGroupByID( WORD wGroupID, char *lpGroupInfo )
{
	int		iRtn;


	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( -1 );
	}

	//==============================================
	//  該当グループ情報獲得
	//==============================================
	memset( lpGroupInfo, 0, SRS_GROUP_ITEM_SZ );
	if( wGroupID >= lpInfoGroup->GP_wMaxGroup )	// 不正ＩＤ？
	{
		return( -1 );
	}
	memset( lpGroupInfo, 0, SRS_GROUP_ITEM_SZ );
	memcpy( lpGroupInfo,
            (char *)&(lpInfoGroup->GP_info_group[wGroupID].GPI_iLockword),	SRS_GROUP_ITEM_SZ );

	return( 0 );
}

/*=============================================================================
     関数    ：登録数参照（該当情報の登録数を獲得する）
     入力    ：iKind  情報種別 
                      SRS_MNG_USER  登録ユーザ数
                      SRS_MNG_LOBBY 登録ロビー数
                      SRS_MNG_GROUP 登録グループ数
                      SRS_MNG_GAME  登録ゲーム数
     出力    ：なし
     戻り値  ：正常  登録数
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GetEntryNo( int iKind )
{
	int		iRtn;

	//==============================================  
	//  情報展開
	//==============================================
	iRtn = SRS_Mng_GetInfo( SRS_INFO_NO );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	//==============================================  
	//  登録数獲得
	//==============================================
	switch( iKind )
	{
		case  SRS_MNG_USER	: iRtn = (int)lpInfoUser->US_wEntryUser;
							  break;	
		case  SRS_MNG_LOBBY	: iRtn = (int)lpInfoLobby->LB_wMaxLobby;
						      break;
		case  SRS_MNG_GROUP	: iRtn = (int)lpInfoGroup->GP_wEntryGroup;
							  break;
		case  SRS_MNG_GAME	: iRtn = (int)lpInfoGame->GM_wEntryGame;
							  break;	
		default				: iRtn = 0;
							  break;	
	}
	return( iRtn );
}

/*=============================================================================
     関数    ：管理情報読み込み（各管理情報をメモリ上に展開する）
     入力    ：iMode   領域獲得モード  SRS_INFO_GET :獲得する
                                       SRS_INFO_NO  :獲得しない
     出力    ：管理情報がグローバル域にコピーされる
     戻り値  ：正常  0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_GetInfo( int iMode )
{
	int		iRtn;
	BOOL	fRtn;
	DWORD	dwRtn;
	DWORD	dwReadByte;
	WORD	wMaxUser;
	WORD	wMaxLobby;
	WORD	wMaxGroup;
	WORD	wMaxGame;
	HANDLE	hHandle;
	struct	SRS_REG_INFO	*lpRegInfo;	
	char	cRegInfo[SRS_REG_INFO_SZ];
	char	cMsg[256];

	//==============================================
	//  可変情報取り込み
	//==============================================
	// 共通管理情報
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
		sprintf( cMsg, "SRS_Mng_GetInfo : SRS_Reg_GetComInfo error" );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	wMaxUser  =	lpRegInfo->wMaxUser;			// 最大ユーザ数
	wMaxLobby = lpRegInfo->wMaxLobby;			// 最大ロビー数
	wMaxGame  = lpRegInfo->wMaxGame;			// 最大ゲーム数
	wMaxGroup = lpRegInfo->wMaxGroup;			// 最大グループ数
	//
	// 情報域設定
	//
	iUserSize  = SRS_USER_ITEM_SZ  * (wMaxUser+1);
	iUserSize  = iUserSize + SRS_INFO_USER_COM_SZ;

	iLobbySize = SRS_LOBBY_ITEM_SZ * wMaxLobby;
	iLobbySize = iLobbySize + SRS_INFO_LOBBY_COM_SZ;

	iGroupSize = SRS_GROUP_ITEM_SZ * (wMaxGroup+1);
	iGroupSize = iGroupSize + SRS_INFO_GROUP_COM_SZ;

	iGameSize  = SRS_GAME_ITEM_SZ  * (wMaxGame+1);
	iGameSize  = iGameSize + SRS_INFO_GAME_COM_SZ;

	//==============================================
	//  情報域獲得
	//==============================================
	if( iMode == SRS_INFO_GET )			// 領域獲得？
	{

		// << ユーザ情報域獲得 >>
		lpInfoUser = (struct SRS_INFO_USER *)malloc( iUserSize );
		if( lpInfoUser == 0 )
		{
			sprintf( cMsg, "??? malloc SRS_INFO_USER (%d) ???", iUserSize );
			SRS_Dbg_WriteLog( cMsg );
			return( -1 );
		}
		memset( (char *)lpInfoUser, 0, iUserSize );

		// << ロビー情報域獲得 >>
		lpInfoLobby = (struct SRS_INFO_LOBBY *)malloc( iLobbySize );
		if( lpInfoLobby == 0 )
		{
			sprintf( cMsg, "??? malloc SRS_INFO_LOBBY (%d) ???", iLobbySize );
			SRS_Dbg_WriteLog( cMsg );
			return( -1 );
		}
		memset( (char *)lpInfoLobby, 0, iLobbySize );

		// << グループ情報域獲得 >>
		lpInfoGroup = (struct SRS_INFO_GROUP *)malloc( iGroupSize );
		if( lpInfoGroup == 0 )
		{
			sprintf( cMsg, "??? malloc SRS_INFO_GROUP (%d) ???", iGroupSize );
			SRS_Dbg_WriteLog( cMsg );
			return( -1 );
		}
		memset( (char *)lpInfoGroup, 0, iGroupSize );

		// << ゲーム情報域獲得 >>
		lpInfoGame = (struct SRS_INFO_GAME *)malloc( iGameSize );
		if( lpInfoGame == 0 )
		{
			sprintf( cMsg, "??? malloc SRS_INFO_GAME (%d) ???", iGameSize );
			SRS_Dbg_WriteLog( cMsg );
			return( -1 );
		}
		memset( (char *)lpInfoGame, 0, iGameSize );

	}
	//==============================================
	//  ユーザ情報読み込み
	//==============================================
	for( ; ; )
	{
		hHandle = CreateFile( SRS_PATH_USER, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, 
								OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL );
		if( hHandle != INVALID_HANDLE_VALUE )
		{
			break;
		}
		dwRtn = GetLastError();
		sprintf( cMsg, "SRS_Mng_GetInfo : reateFile error %d %s", dwRtn, SRS_PATH_USER );
		SRS_Dbg_WriteLog( cMsg );
		if( dwRtn != ERROR_SHARING_VIOLATION )	// ファイル排他中以外？
		{
			return( -1 );
		}
		Sleep( 50 );
	}
	fRtn = 0;
	dwReadByte = (DWORD)iUserSize;
	fRtn = ReadFile( hHandle, (char *)lpInfoUser, iUserSize, &dwReadByte, NULL );
	if( fRtn == false )
	{
		dwRtn = GetLastError();
		sprintf( cMsg, "SRS_Mng_GetInfo : ReadFile error %d %s", dwRtn, SRS_PATH_USER );
		SRS_Dbg_WriteLog( cMsg );
		CloseHandle( hHandle );
		return( -1 );
	}
	fRtn = CloseHandle( hHandle );

	//==============================================
	//  ロビー情報読み込み
	//==============================================
	for( ; ; )
	{
		hHandle = CreateFile( SRS_PATH_LOBBY, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, 
								OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL );
		if( hHandle != INVALID_HANDLE_VALUE )
		{
			break;
		}
		dwRtn = GetLastError();
		sprintf( cMsg, "CreateFile error %d %s", dwRtn, SRS_PATH_LOBBY );
		SRS_Dbg_WriteLog( cMsg );
		if( dwRtn != ERROR_SHARING_VIOLATION )	// ファイル排他中以外？
		{
			return( -1 );
		}
		Sleep( 50 );
	}
	fRtn = 0;
	dwReadByte = (DWORD)iLobbySize;
	fRtn = ReadFile( hHandle, (char *)lpInfoLobby, iLobbySize, &dwReadByte, NULL );
	if( fRtn == false )
	{
		dwRtn = GetLastError();
		sprintf( cMsg, "ReadFile error %d %s", dwRtn, SRS_PATH_LOBBY );
		SRS_Dbg_WriteLog( cMsg );
		CloseHandle( hHandle );
		return( -1 );
	}
	fRtn = CloseHandle( hHandle );

#if ROOTZ
	//==============================================
	//  グループ情報読み込み
	//==============================================
	for( ; ; )
	{
		hHandle = CreateFile( SRS_PATH_GROUP, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, 
								OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL );
		if( hHandle != INVALID_HANDLE_VALUE )
		{
			break;
		}
		dwRtn = GetLastError();
		sprintf( cMsg, "CreateFile error %d %s", dwRtn, SRS_PATH_GROUP );
		SRS_Dbg_WriteLog( cMsg );
		if( dwRtn != ERROR_SHARING_VIOLATION )	// ファイル排他中以外？
		{
			return( -1 );
		}
		Sleep( 500 );
	}
	dwReadByte = (DWORD)iGroupSize;
	fRtn = ReadFile( hHandle, (char *)lpInfoGroup, iGroupSize, &dwReadByte, NULL );
	if( fRtn == false )
	{
		dwRtn = GetLastError();
		sprintf( cMsg, "ReadFile error %d %s", dwRtn, SRS_PATH_GROUP );
		SRS_Dbg_WriteLog( cMsg );
		CloseHandle( hHandle );
		return( -1 );
	}
	fRtn = CloseHandle( hHandle );

	//==============================================
	//  ゲーム情報読み込み
	//==============================================
	for( ; ; )
	{
		hHandle = CreateFile( SRS_PATH_GAME, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, 
								OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL );
		if( hHandle != INVALID_HANDLE_VALUE )
		{
			break;
		}
		dwRtn = GetLastError();
		sprintf( cMsg, "CreateFile error %d %s", dwRtn, SRS_PATH_GAME );
		SRS_Dbg_WriteLog( cMsg );
		if( dwRtn != ERROR_SHARING_VIOLATION )	// ファイル排他中以外？
		{
			return( -1 );
		}
		Sleep( 500 );
	}
	fRtn = 0;
	dwReadByte = (DWORD)iGameSize;
	fRtn = ReadFile( hHandle, (char *)lpInfoGame, iGameSize, &dwReadByte, NULL );
	if( fRtn == false )
	{
		dwRtn = GetLastError();
		sprintf( cMsg, "ReadFile error %d %s", dwRtn, SRS_PATH_GAME );
		SRS_Dbg_WriteLog( cMsg );
		CloseHandle( hHandle );
		return( -1 );
	}
	fRtn = CloseHandle( hHandle );
#endif

	return( 0 );
}

__declspec( dllexport )void __stdcall SRS_Mng_PutPort( int iPort, int wID )
{
	lpInfoUser->US_info_user[wID].USI_iPort = iPort;
}

/*=============================================================================
     関数    ：管理情報書き込み（各管理情報をファイルに待避する）
     入力    ：なし
     出力    ：管理情報がファイルにコピーされる
     戻り値  ：正常  0
               異常 -1
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Mng_PutInfo( int wID /* = 0 */ )
{
    size_t  szSize = 0;						//
    size_t  szBlock = 1;					//
	FILE	*fFp = (FILE *)NULL;			//
	DWORD	dwRtn;							//
	char	cMsg[256];

	SYSTEMTIME systime;
	GetLocalTime( &systime );
	lpInfoUser->US_info_user[wID].USI_time.wYear = systime.wYear;
	lpInfoUser->US_info_user[wID].USI_time.wMonth = systime.wMonth;
	lpInfoUser->US_info_user[wID].USI_time.wDayOfWeek = systime.wDayOfWeek;
	lpInfoUser->US_info_user[wID].USI_time.wDay = systime.wDay;
	lpInfoUser->US_info_user[wID].USI_time.wHour = systime.wHour;
	lpInfoUser->US_info_user[wID].USI_time.wMinute = systime.wMinute;
	lpInfoUser->US_info_user[wID].USI_time.wSecond = systime.wSecond;
	lpInfoUser->US_info_user[wID].USI_time.wMilliseconds = systime.wMilliseconds;

	//==========================================
	//  ファイル出力
	//==========================================
	// ユーザ情報
	for( ; ; )
	{
		fFp = fopen( SRS_PATH_USER, "wb");
		if( fFp != (FILE *)NULL )
		{
			fwrite( (char *)lpInfoUser, iUserSize, szBlock, fFp );
			fclose( fFp );
			break;
		}
		dwRtn = GetLastError();
		sprintf( cMsg, "??? fopen error user %d ???",dwRtn );
		SRS_Dbg_WriteLog( cMsg );
		if( dwRtn != ERROR_SHARING_VIOLATION )	// ファイル排他中以外？
		{
			return( -1 );
		}
		Sleep( 50 );
	}

	fwrite( (char *)lpInfoUser, (size_t)iUserSize, szBlock, fFp );
	fclose( fFp );


	// ロビー情報
	for( ; ; )
	{
		fFp = fopen( SRS_PATH_LOBBY, "wb");
		if( fFp != (FILE *)NULL )
		{
			fwrite( (char *)lpInfoLobby, iLobbySize, szBlock, fFp );
			fclose( fFp );
			break;
		}
		dwRtn = GetLastError();
		sprintf( cMsg, "??? fopen error lobby  %d ???", dwRtn );
		SRS_Dbg_WriteLog( cMsg );
		if( dwRtn != ERROR_SHARING_VIOLATION )	// ファイル排他中以外？
		{
			return( -1 );
		}
		Sleep( 50 );
	}
	fwrite( (char *)lpInfoLobby, (size_t)iLobbySize, szBlock, fFp );
	fclose( fFp );

#if ROOTZ
	// グループ情報
	for( ; ; )
	{
		fFp = fopen( SRS_PATH_GROUP, "wb");
		if( fFp != (FILE *)NULL )
		{
			fwrite( (char *)lpInfoGroup, iGroupSize, szBlock, fFp );
			fclose( fFp );
			break;
		}
		dwRtn = GetLastError();
		sprintf( cMsg, "??? fopen error group %d ???", dwRtn );
		SRS_Dbg_WriteLog( cMsg );
		if( dwRtn != ERROR_SHARING_VIOLATION )	// ファイル排他中以外？
		{
			return( -1 );
		}
		Sleep( 500 );
	}
	fwrite( (char *)lpInfoGroup, (size_t)iGroupSize, szBlock, fFp );
	fclose( fFp );


	// ゲーム情報
	for( ; ; )
	{
		fFp = fopen( SRS_PATH_GAME, "wb");
		if( fFp != (FILE *)NULL )
		{
			fwrite( (char *)lpInfoGame, iGameSize, szBlock, fFp );
			fclose( fFp );
			break;
		}
		dwRtn = GetLastError();
		sprintf( cMsg, "??? fopen error game %d ???", dwRtn );
		SRS_Dbg_WriteLog( cMsg );
		if( dwRtn != ERROR_SHARING_VIOLATION )	// ファイル排他中以外？
		{
			return( -1 );
		}
		Sleep( 500 );
	}
	fwrite( (char *)lpInfoGame, (size_t)iGameSize, szBlock, fFp );
	fclose( fFp );
#endif

	return( 0 );
}
