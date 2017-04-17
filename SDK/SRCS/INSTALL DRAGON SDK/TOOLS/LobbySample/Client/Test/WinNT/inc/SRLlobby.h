/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRLlobby.h
 *  Description: ロビーAPI用定義ファイル
 *  Content:    Lobby Api include file
 *  Created:    1999/06/07
 *  Update:	  
 ***************************************************************************/
#ifndef _SRL_LOBBY_H_
#define _SRL_LOBBY_H_

#define LINKAGE extern "C"

#ifdef __cplusplus
extern "C" {
#endif



#ifndef __cplusplus
typedef enum { false, true } bool;
#endif

/*************************************/
/* Win32 互換用定義                   */
/*************************************/

typedef void			*LPVOID, *PVOID;
typedef const char		*LPCCHAR, *PCCHAR;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif


typedef char			*LPCHAR, *PCHAR;
typedef char			STR;

#define SRL_CLIENTNAME	"GOBOU"
/************************************/
/*   プロセス名			  */
/************************************/

/*************************************/
/* 変数定義                          */
/*************************************/
#define		SRL_OK		TRUE
#define		SRL_NG		FALSE

/*************************************/
/* API用Lobby情報領域構造体ポインタ－  */
/*************************************/
typedef	struct SRS_INFO_USER	SRLUSERLIST,*LPSRLUSERLIST;	
typedef	struct SRS_USER_ITEM	SRLUSER, *LPSRLUSER;
typedef	struct SRS_INFO_GAME	SRLGAMELIST,*LPSRLGAMELIST;
typedef	struct SRS_GAME_ITEM	SRLGAME,*LPSRLGAME;
typedef	struct SRS_INFO_LOBBY	SRLLOBBYLIST,*LPSRLLOBBYLIST;
typedef	struct SRS_LOBBY_ITEM	SRLLOBBY,*LPSRLLOBBY;
typedef	struct SRS_INFO_GROUP	SRLGROUPLIST,*LPSRLGROUPLIST;
typedef	struct SRS_GROUP_ITEM	SRLGROUP,*LPSRLGROUP;


/*************************************/
// Termination Flag for SRL_Terminate()
#define SRL_TERMINATE_COMPLETE			1
#define SRL_TERMINATE_KEEPCONNECTION	2


/****************************/
/*  ポート番号              */
/****************************/
#define SRL_CLIENT_PORTNO		8000

/****************************/
/*  ホストIPアドレス		*/
/****************************/

/*************************************/
// SRL_Proceed() Flag
#define SRL_PROCEED_NORMAL	1


/****************************/
/*  メッセージタイプ        */
/****************************/
// SRL Message Type
#define SRLMESSAGE_ANY			0
#define SRLMESSAGE_SERVER		1
#define SRLMESSAGE_INFOMESSAGE	2
#define SRLMESSAGE_CHAT			3
#define SRLMESSAGE_PRIVATE		4


/************************************************/
/*   API用構造体定義	                           */
/************************************************/


/********************************/
/*   通信デバイス情報		     */
/********************************/
#define	SRL_MAXENTRYNAME	20
#define	SRL_MAXPHONENUMBER	128
#define	SRL_MAXIPADDRESS	15
#define	SRL_MAXDEVICENAME	32
#define	SRL_MAXUSERNAME	20


typedef struct _SRL_DEVICE
{
	DWORD	DV_dwDeviceType;						// 接続タイプ
	char	DV_cEntryName[SRL_MAXENTRYNAME+1];		// エントリー名
	char	DV_cPhoneNumber[SRL_MAXPHONENUMBER+1];	// 電話番号
	char	DV_cIPAddress[SRL_MAXIPADDRESS+1];		// IPアドレス
	char	DV_cDeviceName[SRL_MAXDEVICENAME+1];	// デバイス名
	DWORD	DV_dwPortNo;							// ポート番号
} SRLDEVICE, *LPSRLDEVICE; 
/********************************/
/*   ログインアカウント情報	     */
/********************************/
typedef struct _SRL_ACCOUNT
{
	char	AC_cHostName[20];					// ロビーサーバ名
	char	AC_cClientName[SRS_MAX_NAME_CLIENT];	// クライアント名（ログインＩＤ）
	char	AC_cUserName[SRS_MAX_NAME_USER];					// ユーザ名
	char	AC_cPassword[SRS_MAX_PASSWORD];					// パスワード
	int	AC_iIPAdr;						// ＩＰアドレス
} SRLACCOUNT, *LPSRLACCOUNT;
/*******************************/
/*   接続情報		           */
/*******************************/
typedef struct _SRL_CONNECTION
{
	DWORD		CN_dwType;
	bool		CN_bConnected;
	SRLACCOUNT	CN_Account;
	SRLDEVICE	CN_SrlDevice;
}  SRLCONNECTION, *LPSRLCONNECTION;
/********************************/
/*   ユーザ登録情報				*/
/********************************/
typedef struct	_SRL_USER_ENTRY
{
	char		UE_cClientName[SRS_MAX_NAME_CLIENT];	// クライアント名
	char		UE_cUserName[SRS_MAX_NAME_USER];	// ユーザ名
} SRLUSERENTRY, *LPSRLUSERENTRY;

#define SRS_USER_ENTRY_SZ	(sizeof(struct _SRL_USER_ENTRY))

/********************************/
/*   グループ登録情報		    */
/********************************/
typedef struct	_SRL_GROUP_MAKE
{
	WORD	GM_wUserID;				// 主催ユーザID
	WORD	wReserve;				// リザーブ
	char	GM_cGroupName[SRS_MAX_NAME_GROUP];			// グループ名
}SRLGROUPMAKE,*LPSRLGROUPMAKE;
 
#define SRS_GROUP_MAKE_SZ	(sizeof(_SRL_GROUP_MAKE))

/********************************/
/*  イベントメッセージ定義      */
/********************************/
#define SRL_EVTMSG_INITIALIZED				("ロビーAPIの初期化を完了しました")
#define SRL_EVTMSG_CONNECTION_START			("ロビーサーバへ接続開始しました")
#define SRL_EVTMSG_CONNECTION_INITIALIZING	("ロビーサーバへ接続中です")
#define SRL_EVTMSG_CONNECTION_DIALING		("ロビーサーバへ電話中です")
#define SRL_EVTMSG_CONNECTION_WAITINGSERVERREPLY ("ロビーサーバからの接続応答待ちです")
#define SRL_EVTMSG_CONNECTION_ESTABLISHING	("ロビーサーバとの接続確立中です")
#define	SRL_EVTMSG_CONNECTION_CONNECTED		("ロビーサーバと接続完了しました")
#define	SRL_EVTMSG_CONNECTION_CLOSED		("ロビーサーバとの接続を切り離しました")
#define SRL_EVTMSG_MESSAGE_RECEIVED			("メッセージを受信した")
#define	SRL_EVTMSG_MESSAGE_CHAT				("チャットメッセージを受信しました")
#define SRL_EVTMSG_USER_ADDED				("新規ユーザがログインしました")
#define SRL_EVTMSG_USER_REMOVED				("既ユーザがログアウトしました")
#define SRL_EVTMSG_USER_GETLISTSTART		("ユーザリストの取得を開始しました")
#define SRL_EVTMSG_USER_GETLISTDONE			("ユーザリストの取得を完了しました")
#define SRL_EVTMSG_USER_REFRESH_START		("ユーザ情報の更新を開始しました")
#define	SRL_EVTMSG_USER_REFRESH_END			("ユーザ情報の更新を完了しました")
#define SRL_EVTMSG_SEARCHUSER_START			("ユーザ検索を開始しました")
#define SRL_EVTMSG_SEARCHUSER_END			("ユーザ検索を終了しました")
#define SRL_EVTMSG_LOBBY_JOINED				("ロビーに参加しました")
#define SRL_EVTMSG_LOBBY_LEAVE				("ロビーから離脱しました")
#define SRL_EVTMSG_LOBBY_GETLISTSTART		("ロビーリストの取得を開始しました")
#define SRL_EVTMSG_LOBBY_GETLISTDONE		("ロビーリストの取得を完了しました")

#define SRL_EVTMSG_LOBBY_REFRESH_START		("ロビー情報の更新を開始しました")
#define SRL_EVTMSG_LOBBY_REFRESH_END		("ロビー情報の更新を完了しました")
	
#define SRL_EVTMSG_GAME_LAUNCH				("ゲームを起動する準備が完了しました")
#define SRL_EVTMSG_GAME_STARTED				("ゲームが開始されました")
#define SRL_EVTMSG_GAME_FINISHED			("ゲームが終了しました")

#define SRL_EVTMSG_GAME_GETLISTSTART		("ゲーム情報の更新を開始しました")
#define SRL_EVTMSG_GAME_GETLISTDONE			("ゲーム情報の更新を完了しました")
#define SRL_EVTMSG_GROUP_JOINSTART			("チームへの参加を開始しました")
#define SRL_EVTMSG_GROUP_JOINED				("チームへの参加を完了しました")
#define SRL_EVTMSG_GROUP_LEAVE				("チームから離脱しました")
#define SRLVENT_GROUP_DESTROYED				("チームが消去しました")
#define SRL_EVTMSG_GROUP_CHANGEOWNER		("チーム主催者が替わりました")


#define SRL_EVTMSG_GROUP_REFRESH_START		("チーム情報の更新を開始しました")
#define SRL_EVTMSG_GROUP_REFRESH_END		("チーム情報の更新を完了しました")
/*
#define SRL_EVTMSG_INITIALIZED				TEXT("ロビーAPIの初期化を完了しました")
#define SRL_EVTMSG_CONNECTION_START			TEXT("ロビーサーバへ接続開始しました")
#define SRL_EVTMSG_CONNECTION_INITIALIZING	TEXT("ロビーサーバへ接続中です")
#define SRL_EVTMSG_CONNECTION_WAITINGSERVERREPLY TEXT("ロビーサーバからの接続応答待ちです")
#define SRL_EVTMSG_CONNECTION_ESTABLISHING	TEXT("ロビーサーバとの接続確立中です")
#define	SRL_EVTMSG_CONNECTION_CONNECTED		TEXT("ロビーサーバと接続完了しました")
#define	SRL_EVTMSG_CONNECTION_CLOSED		TEXT("ロビーサーバとの接続を切り離しました")
#define SRL_EVTMSG_MESSAGE_RECEIVED			TEXT("メッセージを受信した")
#define	SRL_EVTMSG_MESSAGE_CHAT				TEXT("チャットメッセージを受信しました")
#define SRL_EVTMSG_USER_ADDED				TEXT("新規ユーザがログインしました")
#define SRL_EVTMSG_USER_REMOVED				TEXT("既ユーザがログアウトしました")
#define SRL_EVTMSG_USER_GETLISTSTART		TEXT("ユーザリストの取得を開始しました")
#define SRL_EVTMSG_USER_GETLISTDONE			TEXT("ユーザリストの取得を完了しました")
#define SRL_EVTMSG_USER_REFRESH_START		TEXT("ユーザ情報の更新を開始しました")
#define	SRL_EVTMSG_USER_REFRESH_END			TEXT("ユーザ情報の更新を完了しました")
#define SRL_EVTMSG_SEARCHUSER_START			TEXT("ユーザ検索を開始しました")
#define SRL_EVTMSG_SEARCHUSER_END			TEXT("ユーザ検索を終了しました")
#define SRL_EVTMSG_LOBBY_JOINED				TEXT("ロビーに参加しました")
#define SRL_EVTMSG_LOBBY_LEAVE				TEXT("ロビーから離脱しました")
#define SRL_EVTMSG_LOBBY_GETLISTSTART		TEXT("ロビーリストの取得を開始しました")
#define SRL_EVTMSG_LOBBY_GETLISTDONE		TEXT("ロビーリストの取得を完了しました")

#define SRL_EVTMSG_LOBBY_REFRESH_START		TEXT("ロビー情報の更新を開始しました")
#define SRL_EVTMSG_LOBBY_REFRESH_END		TEXT("ロビー情報の更新を完了しました")
	
#define SRL_EVTMSG_GAME_LAUNCH				TEXT("ゲームを起動する準備が完了しました")
#define SRL_EVTMSG_GAME_STARTED				TEXT("ゲームが開始されました")
#define SRL_EVTMSG_GAME_FINISHED			TEXT("ゲームが終了しました")

#define SRL_EVTMSG_GAME_GETLISTSTART		TEXT("ゲーム情報の更新を開始しました")
#define SRL_EVTMSG_GAME_GETLISTDONE			TEXT("ゲーム情報の更新を完了しました")
#define SRL_EVTMSG_GROUP_JOINSTART			TEXT("チームへの参加を開始しました")
#define SRL_EVTMSG_GROUP_JOINED				TEXT("チームへの参加を完了しました")
#define SRL_EVTMSG_GROUP_LEAVE				TEXT("チームから離脱しました")
#define SRLVENT_GROUP_DESTROYED				TEXT("チームが消去しました")
#define SRL_EVTMSG_GROUP_CHANGEOWNER		TEXT("チーム主催者が替わりました")


#define SRL_EVTMSG_GROUP_REFRESH_START		TEXT("チーム情報の更新を開始しました")
#define SRL_EVTMSG_GROUP_REFRESH_END		TEXT("チーム情報の更新を完了しました")
*/
/******************************/
/*  エラーメッセージ定義      */
/******************************/
#define	SRL_ERRMSG_GENERIC					("汎用的エラーが発生しました")
#define	SRL_ERRMSG_COMERROR					("通信エラーが発生しました")
#define	SRL_ERRMSG_CONNECTION_FAILED		("接続が失敗しました")
#define	SRL_ERRMSG_RASDEVICE				("RAS接続失敗しました")
#define	SRL_ERRMSG_INVALIDPARAMS			("無効パラメータ")
#define	SRL_ERRMSG_NO_ANSWER				("サーバから無応答です")
#define	SRL_ERRMSG_DISCONNECTED				("接続が切り離されました")
#define	SRL_ERRMSG_SENDFAILED				("送信エラーが発生しました")
#define	SRL_ERRMSG_OVERFLOWED				("オーバフローが発生しました")
#define	SRL_ERRMSG_TIMEOUT					("タイムアウトが発生し")
#define	SRL_ERRMSG_SERVERNOTREPLY			("サーバが落ちました")
#define	SRL_ERRMSG_NOTENOUGHMEMORY			("リソースが不足しています")
#define	SRL_ERRMSG_INVALIDPASSWORD			("パスワードが無効です")
#define	SRL_ERRMSG_INVALIDACCOUNT			("アカウントが無効です")
#define	SRL_ERRMSG_NOTCONNECTED				("接続できません")
#define	SRL_ERRMSG_ALREADYCONNECTED			("すでに接続しています")
#define	SRL_ERRMSG_GAME_LAUNCHFAILED		("ゲームの起動が失敗しました")
#define	SRL_ERRMSG_CREATEGROUPFAILED		("チームを作成できません")
#define	SRL_ERRMSG_GROUP_FULL				("チーム数制限を越えました")
#define	SRL_ERRMSG_USERALREADYEXIST			("すでに同一名ユーザが存在します")
#define	SRL_ERRMSG_DUPLICATEUSERNAME		("同一名ユーザ登録を許可しません")
#define	SRL_ERRMSG_GROUP_ALREADYEXIST		("同一名チームが存在します")
#define	SRL_ERRMSG_CHAT_EMPTYMESSAGE		("空チャットメッセージは送信できません")
#define	SRL_ERRMSG_LOBBY_FULL				("ロビー内のユーザ登録が一杯です")
#define	SRL_ERRMSG_MAXMSGQUE				("メッセージキューが一杯です")
#define	SRL_ERRMSG_MAXEVENTQUE				("イベントキューが一杯です")
#define	SRL_ERRMSG_MAXERRORQUE				("エラーキューが一杯です")
/*
#define	SRL_ERRMSG_GENERIC					TEXT("汎用的エラーが発生しました")
#define	SRL_ERRMSG_COMERROR					TEXT("通信エラーが発生しました")
#define	SRL_ERRMSG_CONNECTION_FAILED			TEXT("接続が失敗しました")
#define	SRL_ERRMSG_RASDEVICE					TEXT("RAS接続失敗しました")
#define	SRL_ERRMSG_INVALIDPARAMS				TEXT("無効パラメータ")
#define	SRL_ERRMSG_NO_ANSWER					TEXT("サーバから無応答です")
#define	SRL_ERRMSG_DISCONNECTED				TEXT("接続が切り離されました")
#define	SRL_ERRMSG_SENDFAILED					TEXT("送信エラーが発生しました")
#define	SRL_ERRMSG_OVERFLOWED					 TEXT("オーバフローが発生しました")
#define	SRL_ERRMSG_TIMEOUT					TEXT("タイムアウトが発生し")
#define	SRL_ERRMSG_SERVERNOTREPLY				TEXT("サーバが落ちました")
#define	SRL_ERRMSG_NOTENOUGHMEMORY			TEXT("リソースが不足しています")
#define	SRL_ERRMSG_INVALIDPASSWORD			TEXT("パスワードが無効です")
#define	SRL_ERRMSG_INVALIDACCOUNT				TEXT("アカウントが無効です")
#define	SRL_ERRMSG_NOTCONNECTED				TEXT("接続できません")
#define	SRL_ERRMSG_ALREADYCONNECTED			TEXT("すでに接続しています")
#define	SRL_ERRMSG_GAME_LAUNCHFAILED			TEXT("ゲームの起動が失敗しました")
#define	SRL_ERRMSG_CREATEGROUPFAILED			TEXT("チームを作成できません")
#define	SRL_ERRMSG_GROUP_FULL					TEXT("チーム数制限を越えました")
#define	SRL_ERRMSG_USERALREADYEXIST			TEXT("すでに同一名ユーザが存在します")
#define	SRL_ERRMSG_DUPLICATEUSERNAME			TEXT("同一名ユーザ登録を許可しません")
#define	SRL_ERRMSG_GROUP_ALREADYEXIST			TEXT("同一名チームが存在します")
#define	SRL_ERRMSG_CHAT_EMPTYMESSAGE			TEXT("空チャットメッセージは送信できません")
#define	SRL_ERRMSG_LOBBY_FULL					TEXT("ロビー内のユーザ登録が一杯です")
#define	SRL_ERRMSG_MAXMSGQUE					TEXT("メッセージキューが一杯です")
#define	SRL_ERRMSG_MAXEVENTQUE				TEXT("イベントキューが一杯です")
#define	SRL_ERRMSG_MAXERRORQUE				TEXT("エラーキューが一杯です")
*/
/********************************************************/
/*														*/
/* API関数定義											*/
/*														*/
/*******************************************************/
// Lobby API初期化
__declspec(dllexport)  bool __stdcall SRL_Initialize( void );
__declspec(dllexport)  bool __stdcall SRL_InitializeDevice ( LPSRLDEVICE lpDevice );

// サーバとの接続処理
__declspec(dllexport)  bool __stdcall SRL_InitializeEntry ( char *cClientName, char *cUserName, char *cPassword);
__declspec(dllexport)  bool __stdcall SRL_ConnectToServer( int iServerIndex );
__declspec(dllexport)  bool __stdcall SRL_Disconnect( void );
__declspec(dllexport)  bool __stdcall SRL_Reconnect( void );
__declspec(dllexport)  bool __stdcall SRL_Terminate( DWORD dwFlag );

// 各種情報の取得

// ユーザ関連操作
__declspec(dllexport)  WORD __stdcall SRL_GetUserByName( char *lpUserName );
__declspec(dllexport)  bool __stdcall SRL_GetUserByID( WORD wUserID, LPSRLUSER lpUserInfo );
__declspec(dllexport)  bool __stdcall SRL_CreateUser( char *cClinetName, char *cUserName );
__declspec(dllexport)  bool __stdcall SRL_DestroyUser( WORD wUserID );	
__declspec(dllexport)  bool __stdcall SRL_GetUserList ( LPSRLUSERLIST	lpUserList );
__declspec(dllexport)  bool __stdcall SRL_GetUserInfo( WORD wUserID, LPSRLUSER lpUserInfo );
__declspec(dllexport)  bool __stdcall SRL_SendUserSaveData( LPCHAR lpcSaveData );


// ロビー関連操作
__declspec(dllexport)  WORD __stdcall SRL_GetLobbyByName( char *lpLobbyName );
__declspec(dllexport)  bool __stdcall SRL_GetLobbyList ( LPSRLLOBBYLIST	lpLobbyList );
__declspec(dllexport)  bool __stdcall SRL_GetLobbyInfo ( WORD	wLobbyID, LPSRLLOBBY lpLobbyInfo );
__declspec(dllexport)  bool __stdcall SRL_GetLobbyByID( WORD wLobbyID,LPSRLLOBBY lpLobbyInfo );
__declspec(dllexport)  bool __stdcall SRL_RefreshLobbyList( void );
__declspec(dllexport)  bool __stdcall SRL_JoinLobby( WORD wUserID, WORD wLobbyID );
__declspec(dllexport)  bool __stdcall SRL_LeaveLobby( WORD wUserID, WORD wLobbyID );

// ゲーム関連操作
__declspec(dllexport)  bool __stdcall SRL_GetGameList( LPSRLGAMELIST lpGameList );
__declspec(dllexport)  bool __stdcall SRL_GetGameInfo (WORD wGameID, LPSRLGAME lpGameInfo);
__declspec(dllexport)  bool __stdcall SRL_LaunchRequest( WORD wUserID );
__declspec(dllexport)  bool __stdcall SRL_StartedGame( WORD wUserID );
__declspec(dllexport)  bool __stdcall SRL_FinishedGame( WORD wUserID );

// チーム関連操作
__declspec(dllexport)  WORD __stdcall SRL_GetGroupByName( char *lpGroupName );
__declspec(dllexport)  bool __stdcall SRL_GetGroupByID( WORD wGroupID,LPSRLGROUP lpGroupInfo );
__declspec(dllexport)  bool __stdcall SRL_CreateGroup( WORD wUserID, LPSTR lpGroupName );
__declspec(dllexport)  bool __stdcall SRL_GetGroupList ( LPSRLGROUPLIST lpGroupList );
__declspec(dllexport)  bool __stdcall SRL_GetGroupInfo ( WORD wGroupID, LPSRLGROUP	lpGroupInfo);
__declspec(dllexport)  bool __stdcall SRL_JoinGroup ( WORD wUserID , LPSTR szPassword ,WORD wGroupID);
__declspec(dllexport)  bool __stdcall SRL_LeaveGroup ( WORD wUserID, WORD wGroupID );

// メッセージ送信
__declspec(dllexport)  bool __stdcall SRL_GetMsg ( LPSRLEVENTMNG lpMessageInfo );
__declspec(dllexport)  bool __stdcall SRL_SendChat (WORD wUserID,  LPSTR lpMessage );
__declspec(dllexport)  int  __stdcall SRL_GetMsgCount( void );


// イベント情報の取得( if none,  NULL )
__declspec(dllexport)  bool __stdcall SRL_GetEvent ( LPSRLEVENTMNG lpEventInfo );
__declspec(dllexport)  int  __stdcall SRL_GetEventCount( void );
__declspec(dllexport)  char * __stdcall SRL_GetEventString( int iEventId );


// エラー
__declspec(dllexport)  bool __stdcall SRL_GetError ( LPSRLEVENTMNG lpErrorInfo );
__declspec(dllexport)  int  __stdcall SRL_GetErrorCount( void );
__declspec(dllexport)  char * __stdcall SRL_GetErrorString( int iErrorId );




#ifdef __cplusplus
}
#endif


#endif // __SRLLOBBY_INCLUDED__
// End of File.
