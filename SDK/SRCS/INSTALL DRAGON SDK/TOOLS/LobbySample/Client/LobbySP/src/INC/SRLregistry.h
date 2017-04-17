/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRLcom.h
 *  Content:    Lobby client registry access include file
 *              99/11/29 修正 ＣＥ用レジストリＭＡＸ　４Ｋまで書き込み可の対応
 ***************************************************************************/
#ifndef _SRL_REGISTRY_H_
#define _SRL_REGISTRY_H_

//=========================================
//   関数定義
//=========================================
__declspec( dllexport )int __stdcall SRL_Reg_GetComInfo( struct SRL_REG_INFO *lpRegInfo );
__declspec( dllexport )void __stdcall SRL_Reg_Delete( void );
__declspec( dllexport )int __stdcall SRL_Reg_SetInfo( LPCTSTR lpRegKey, LPCTSTR lpReg, LPCTSTR lpBuff );
__declspec( dllexport )int __stdcall SRL_Reg_GetInfo( LPCTSTR lpRegKey,LPCTSTR lpReg, LPCTSTR lpBuff );
__declspec( dllexport )int __stdcall SRL_Reg_SetInfoBinary( LPCTSTR lpRegKey, LPCTSTR lpReg, LPCTSTR lpBuff, DWORD dwSize );
__declspec( dllexport )int __stdcall SRL_Reg_GetInfoBinary( LPCTSTR lpRegKey,LPCTSTR lpReg, LPCTSTR lpBuff, DWORD dwSize );
__declspec( dllexport )int __stdcall SRL_Reg_SetInfoDWORD( LPCTSTR lpRegKey,LPCTSTR lpReg, DWORD dwInfo );
__declspec( dllexport )DWORD __stdcall SRL_Reg_GetInfoDWORD( LPCTSTR lpRegKey,LPCTSTR lpReg );

//=========================================
// レジストリキー
//=========================================
//  固定
#define	SRL_REG_KEY_COM			TEXT("SOFTWARE\\LOBBY CLIENT")			// 共通情報
#define	SRL_REG_KEY_DEBUG		TEXT("SOFTWARE\\LOBBY CLIENT\\debug")	// デバッグ情報
#define	SRL_REG_KEY_TRACE		TEXT("SOFTWARE\\LOBBY CLIENT\\trace")	// TRACE情報
#define	SRL_REG_KEY_MNGUSER		TEXT("SOFTWARE\\LOBBY CLIENT\\manage\\user")  // ユーザ情報
#define	SRL_REG_KEY_MNGLOBBY	TEXT("SOFTWARE\\LOBBY CLIENT\\manage\\lobby") // ロビー情報
#define	SRL_REG_KEY_MNGGROUP	TEXT("SOFTWARE\\LOBBY CLIENT\\manage\\group") // グループ情報
#define	SRL_REG_KEY_MNGGAME		TEXT("SOFTWARE\\LOBBY CLIENT\\manage\\game")  // ゲーム情報
#define	SRL_REG_KEY_EVENT		TEXT("SOFTWARE\\LOBBY CLIENT\\event")	// イベントキュー情報
#define	SRL_REG_KEY_HANDLE		TEXT("SOFTWARE\\LOBBY CLIENT\\handle")	// ウィンドウハンドル
#define	SRL_REG_KEY_USER		TEXT("SOFTWARE\\LOBBY CLIENT\\user")	// ユーザ登録状態
#define SRL_REG_KEY_WAIT		TEXT("SOFTWARE\\LOBBY CLIENT\\wait")	// 応答待ち状態

//=========================================
// レジストリ項目
//=========================================
//  共通情報（SOFTWARE\\LOBBY CLIENT）
#define	SRL_REG_SERVERIP		TEXT("server address")		// サーバアドレス
#define	SRL_REG_CLIENT			TEXT("client name")			// クライアント名
#define SRL_REG_PORT			TEXT("port")				// 使用サーバポート番号
#define	SRL_REG_USER			TEXT("user name")			// ユーザ名
#define	SRL_REG_MODE			TEXT("mode")				// デバッグモード
#define	SRL_REG_MAXUSER			TEXT("max user")			// 最大登録ユーザ数
#define	SRL_REG_MAXLOBBY		TEXT("max lobby")			// 最大登録ロビー数
#define	SRL_REG_MAXGAME			TEXT("max game")			// 最大登録ゲーム数
#define	SRL_REG_MAXGROUP		TEXT("max group")			// 最大登録グループ数
#define	SRL_REG_EVENTQUE		TEXT("event que")			// イベントキュー
#define	SRL_REG_ERRORQUE		TEXT("error que")			// エラーキュー
#define	SRL_REG_MESSAGEQUE		TEXT("message que")			// メッセージキュー
#define	SRL_REG_MESSAGEMASK		TEXT("message mask")		// メッセージキューマスク
#define	SRL_REG_ERRORMASK		TEXT("error mask")			// エラーキューマスク
#define	SRL_REG_EVENTMASK		TEXT("event mask")			// イバントキューマスク
#define	SRL_REG_EVENTHANDLE		TEXT("event handle")		// イベント管理（要求受信用）ハンドル
#define	SRL_REG_EVENTREQMASK	TEXT("event request mask")	// イベント通知マスク
#define	SRL_REG_EVENTREQ		TEXT("event request")		// イベント通知情報
#define	SRL_REG_EVENTANS		TEXT("event answer")		// イベント応答情報
#define	SRL_REG_STATUS			TEXT("user status")		    // ユーザ状態
//
//  要求応答待ち情報（SOFTWARE\\LOBBY CLIENT\\WAIT）
//
#define	SRL_REG_USERENTRY		TEXT("UserEntry")			// ユーザ登録
#define	SRL_REG_USERDELETE		TEXT("UserDelete")			// ユーザ削除
#define	SRL_REG_GROUPMAKE		TEXT("GroupMake")			// グループ作成
#define	SRL_REG_GROUPJOIN		TEXT("GroupJoin")			// グループ参加
#define	SRL_REG_GROUPDEFECT		TEXT("GroupDefect")			// グループ脱退
#define SRL_REG_ALLGET			TEXT("AllGet")				// 全情報参照

//  SOFTWARE\\LOBBY CLIENT\\manage\\user
#define	SRL_REG_USERMASK		TEXT("user mask")			// ユーザ情報マスク
#define	SRL_REG_USERINFO		TEXT("user info")			// ユーザ管理情報
#define	SRL_REG_USERITEM		TEXT("user")			    // ユーザ情報

//  SOFTWARE\\LOBBY CLIENT\\manage\\lobby
#define	SRL_REG_LOBBYMASK		TEXT("lobby mask")			// ロビー情報マスク
#define	SRL_REG_LOBBYINFO		TEXT("lobby info")			// ロビー管理情報
#define	SRL_REG_LOBBYITEM		TEXT("lobby")			    // ロビー情報

//  SOFTWARE\\LOBBY CLIENT\\manage\\group
#define	SRL_REG_GROUPMASK		TEXT("group mask")			// グループ情報マスク
#define	SRL_REG_GROUPINFO		TEXT("group info")			// グループ管理情報
#define	SRL_REG_GROUPITEM		TEXT("group")			    // グループ情報

//  SOFTWARE\\LOBBY CLIENT\\manage\\game
#define	SRL_REG_GAMEMASK		TEXT("game mask")			// ゲーム情報マスク
#define	SRL_REG_GAMEINFO		TEXT("game info")			// ゲーム管理情報
#define	SRL_REG_GAMEITEM		TEXT("game")			    // ゲーム情報


//=========================================
// 項目値
//=========================================
// マスク情報
#define	SRL_REG_MASK_OFF	TEXT("0")					// 参照可能
#define	SRL_REG_MASK_ON		TEXT("1")					// 参照不可

// デバッグモード
#define SRL_REG_MODE_NO		TEXT("0")					// 出力なし
#define SRL_REG_MODE_MSG	TEXT("1")					// メッセージ表示あり
#define SRL_REG_MODE_FILE	TEXT("2")					// ファイル出力のみ（トレース＆ダンプ）
#define SRL_REG_MODE_TRC	TEXT("3")					// トレース出力のみ

// ユーザ状態
#define	SRL_REG_USER_OFF	TEXT("0")					// 未登録
#define	SRL_REG_USER_ON		TEXT("1")					// 登録

// 応答待ち状態
#define SRL_REG_WAIT_ON			TEXT("1")				// 応答待ち状態
#define SRL_REG_WAIT_OFF		TEXT("0")				// 要求なし
#define SRL_REG_WAIT_OK			TEXT("O")				// 要求正常完了
#define SRL_REG_WAIT_NG			TEXT("N")				// 要求異常完了
//#define SRL_REG_WAIT_OK			TEXT("OK")				// 要求正常完了
//#define SRL_REG_WAIT_NG			TEXT("NG")				// 要求異常完了

//=========================================
// レジストリ情報域
//=========================================

// 共通管理情報
typedef struct	SRL_REG_INFO
{
	WORD	wMaxUser;				// 最大登録ユーザ数
	WORD	wMaxLobby;				// 最大登録ロビー数
	WORD	wMaxGame;				// 最大登録ゲーム数
	WORD	wMaxGroup;				// 最大登録グループ数
} SRL_REGINFO, * LPSRL_REGINFO;
#define	SRL_REG_INFO_SZ		(sizeof(struct SRL_REG_INFO))


#endif
