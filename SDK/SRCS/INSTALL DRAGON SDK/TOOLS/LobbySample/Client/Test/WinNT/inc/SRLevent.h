/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRLevent.h
 *  Content:    Lobby client event manage include
 *                                           
 ***************************************************************************/

#ifndef _SRLevent_H
#define _SRLevent_H

//////////////////////////////////////////////
//           マイクロ宣言

//*********************************************
//*	ロビーAPIイベントコード（動作イベント）
//*********************************************
enum SRLEVENT_E
{
	SRLEVENT_NOTHING = 1000,				// 未使用
	SRLEVENT_INITIALIZED,					// ロビーAPI初期化完了

	SRLEVENT_CONNECTION_START,				// ロビーサーバへの接続開始
	SRLEVENT_CONNECTION_INITIALIZING,		// ロビーサーバへの接続中
	SRLEVENT_CONNECTION_DIALING,			// ロビーサーバへの電話中
	SRLEVENT_CONNECTION_WAITINGSERVERREPLY,	// ロビーサーバからの接続応答待ち
	SRLEVENT_CONNECTION_ESTABLISHING,		// ロビーサーバとの接続確立中
	SRLEVENT_CONNECTION_CONNECTED,			// ロビーサーバへの接続完了
	SRLEVENT_CONNECTION_CLOSED,				// ロビーサーバとの接続を切り離し

	SRLEVENT_USER_ADDED,					// 新規ユーザがログインした
	SRLEVENT_USER_REMOVED,					// 10 既ユーザがログアウトした

	SRLEVENT_USER_GETLISTSTART,				// ユーザリストの取得を開始した
	SRLEVENT_USER_GETLISTDONE,				// ユーザリストの取得を完了した 

	SRLEVENT_USER_REFRESH_START,			// ユーザ情報の更新を開始した
	SRLEVENT_USER_REFRESH_END,				// ユーザ情報の更新を完了した 

	SRLEVENT_SEARCHUSER_START,				// ユーザ検索を開始した
	SRLEVENT_SEARCHUSER_END,				// ユーザ検索を終了した

	SRLEVENT_LOBBY_JOINED,					// ロビーに参加した
	SRLEVENT_LOBBY_LEAVE,					// ロビーから離脱した

	SRLEVENT_LOBBY_GETLISTSTART,			// ロビーリストの取得を開始した
	SRLEVENT_LOBBY_GETLISTDONE,				// ロビーリストの取得を完了した 

	SRLEVENT_LOBBY_REFRESH_START,			// ロビー情報の更新を開始した
	SRLEVENT_LOBBY_REFRESH_END,				// ロビー情報の更新を完了した 
	
	SRLEVENT_GAME_LAUNCH,					// ゲームを起動する準備完了
	SRLEVENT_GAME_STARTED,					// ゲームが開始された
	SRLEVENT_GAME_FINISHED,					// ゲームが終了した
	SRLEVENT_GAME_JOINED,					// ゲームに参加した
	SRLEVENT_GAME_LEAVE,					// ゲームから脱退した

	SRLEVENT_GAME_GETLISTSTART,				// ゲーム情報の更新を開始した
	SRLEVENT_GAME_GETLISTDONE,				// ゲーム情報の更新を完了した
	
	SRLEVENT_GROUP_ADDED,					// 30 チームを作成した
	SRLEVENT_GROUP_JOINSTART,				// チームへの参加を開始した
	SRLEVENT_GROUP_JOINED,					// チームへの参加を完了した
	SRLEVENT_GROUP_LEAVE,					// チームから離脱した
	SRLEVENT_GROUP_DESTROYED,				// チームが消去した
	SRLEVENT_GROUP_CHANGEOWNER,				// チーム主催者が替わった


	SRLEVENT_GROUP_REFRESH_START,			// チーム情報の更新を開始した
	SRLEVENT_GROUP_REFRESH_END,				// チーム情報の更新を完了した

	SRLEVENT_RENEWAL,						// ユーザ情報が更新された
	SRLEVENT_TERMINATE,						// プロセス終了イベント

	SRLEVENT_GROUP_GETLISTSTART,			// チーム情報の取得を開始した
	SRLEVENT_GROUP_GETLISTDONE,				// チーム情報の取得を完了した

};

//****************************************************
//*	ロビーAPIイベントコード（メッセージイベント）
//****************************************************
enum SRLMESSAGE_E
{
	SRLMESSAGE_NOTHING = 2000,		// 未使用
	SRLMESSAGE_RECEIVED,			// メッセージを受信した
	SRLMESSAGE_CHAT,				// チャットメッセージを受信した
};

//****************************************************
//*	ロビーAPIイベントコード	(エラーイベント）
//****************************************************
enum SRLERROR_E
{
	SRLERROR_NOTHING = 3000,		// 未使用
	SRLERROR_GENERIC,				// 汎用的エラー
	SRLERROR_COMERROR,				// 通信エラー
	SRLERROR_CONNECTION_FAILED,		// 接続失敗
	SRLERROR_RASDEVICE,				// RAS接続失敗
	SRLERROR_INVALIDPARAMS,			// 無効パラメータ
	SRLERROR_NO_ANSWER,				// サーバから無応答
	SRLERROR_DISCONNECTED,			// 接続が切り離された
	SRLERROR_SENDFAILED,			// 送信エラー
	SRLERROR_OVERFLOWED,			// オーバフロー
	SRLERROR_TIMEOUT,				// タイムアウト
	SRLERROR_SERVERNOTREPLY,		// サーバが落ちた
	SRLERROR_NOTENOUGHMEMORY,		// リソースが不足
	SRLERROR_INVALIDPASSWORD,		// パスワードが無効
	SRLERROR_INVALIDACCOUNT,		// アカウントが無効
	SRLERROR_NOTCONNECTED,			// 接続できない
	SRLERROR_ALREADYCONNECTED,		// すでに接続している
	SRLERROR_GAME_LAUNCHFAILED,		// ゲームの起動失敗
	SRLERROR_CREATEGROUPFAILED,		// チームを作成できない
	SRLERROR_GROUP_FULL,			// チーム数制限を越えた
	SRLERROR_USERALREADYEXIST,		// すでに同一名ユーザが存在する
	SRLERROR_DUPLICATEUSERNAME,		// 同一名ユーザ登録を許可しない
	SRLERROR_GROUP_ALREADYEXIST,	// 同一名チームが存在する
	SRLERROR_CHAT_EMPTYMESSAGE,		// 空チャットメッセージは送信できない
	SRLERROR_LOBBY_FULL,			// ロビー内のユーザ登録が一杯です
	SRLERROR_MAXMSGQUE,				// メッセージキューが一杯です
	SRLERROR_MAXEVENTQUE,			// イベントキューが一杯です
	SRLERROR_MAXERRORQUE			// エラーキューが一杯です
};


#define SRL_QUE_EVENT 	TEXT("SRLevent.que")
#define SRL_QUE_ERROR 	TEXT("SRLerror.que")
#define SRL_QUE_MESSAGE TEXT("SRLmessage.que")

/********************************/
/*	イベントキュー構造体		*/
/********************************/
#define SRL_MAXEVENTCOUNT	    100
#define SRL_EVENTQUE_NOTUSED    0
#define SRL_EVENTQUE_ADD	    1
#define SRL_EVENTQUE_READ	    2
#define SRL_EVENTQUE_DELETE	    3

/********************************/
/*	イベントキューモデル		*/
/********************************/
#define SRL_EVENTMODE_EVENT     0  //イベント
#define SRL_EVENTMODE_ERROR     1  //エラー
#define SRL_EVENTMODE_MESSAGE   2  //メッセージ


//////////////////////////////////////////////
//           構造体宣言

/********************************/
/*	イベントキュー構造体		*/
/********************************/

// インタフェース域
// イベント情報域
typedef struct _SRL_EVENTMNG{
	DWORD	EM_dwEventID;
	char	EM_cMessage[SRS_MAX_MESSAGE];
} SRLEVENTMNG,*LPSRLEVENTMNG; 
#define SRLEVENTMNG_SZ  (sizeof(SRLEVENTMNG))

// イベント情報管理域
typedef struct _SRL_EVENTQUE{
	int					iEventQueCount;
	LONG				lEventQueTop;
	LONG				lEventQueEnd;
}SRLEVENTQUE, *LPSRLEVENTQUE;
#define SRLEVENTQUE_SZ  (sizeof(SRLEVENTQUE))


//////////////////////////////////////////////
//           関数宣言

//int SRL_Evt_Initial( HINSTANCE hInstance );
int SRL_Evt_PutInfo( LPSTR lpInfoName, LPSTR lpGetBuff, size_t szGetSize );
int SRL_Evt_GetInfo( LPSTR lpInfoName, LPSTR lpGetBuff, size_t szGetSize );

__declspec( dllexport )int __stdcall SRL_Evt_Initial( void);
__declspec( dllexport )int __stdcall SRL_Evt_GetEventCount( int nEventMode );
//BOOL SRL_Evt_GetEventCount( int nEventMode , int *pCount );
__declspec( dllexport )BOOL __stdcall SRL_Evt_GetEvent ( int nEventMode, LPSRLEVENTMNG lpEvent );
__declspec( dllexport )BOOL __stdcall SRL_Evt_SetEvent( int nEventMode, LPSRLEVENTMNG lpEvent );
//BOOL SRL_REQProc(SRLEVENT sRecvData, LPSRLSENDDATA pSendData);
#endif
