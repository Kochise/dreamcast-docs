/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRLcom.h
 *  Content:    Lobby client registry access include file
 ***************************************************************************/
#ifndef _SRL_REGISTRY_H_
#define _SRL_REGISTRY_H_

//=========================================
//   関数定義
//=========================================
__declspec( dllexport )int __stdcall SRL_Reg_GetComInfo( struct SRL_REG_INFO *lpRegInfo );
__declspec( dllexport )void __stdcall SRL_Reg_Delete( void );
__declspec( dllexport )int __stdcall SRL_Reg_SetInfo( LPSTR lpRegKey, LPSTR lpReg, LPSTR lpBuff );
__declspec( dllexport )int __stdcall SRL_Reg_GetInfo( LPSTR lpRegKey,LPSTR lpReg, LPSTR lpBuff );
__declspec( dllexport )int __stdcall SRL_Reg_SetInfoBinary( LPSTR lpRegKey, LPSTR lpReg, LPSTR lpBuff, DWORD dwSize );
__declspec( dllexport )int __stdcall SRL_Reg_GetInfoBinary( LPSTR lpRegKey,LPSTR lpReg, LPSTR lpBuff, DWORD dwSize );
__declspec( dllexport )int __stdcall SRL_Reg_SetInfoDWORD( LPSTR lpRegKey,LPSTR lpReg, DWORD dwInfo );
__declspec( dllexport )DWORD __stdcall SRL_Reg_GetInfoDWORD( LPSTR lpRegKey,LPSTR lpReg );

//=========================================
// レジストリキー
//=========================================
//  固定
#define	SRL_REG_KEY_COM			"SOFTWARE\\LOBBY CLIENT"			// 共通情報
#define	SRL_REG_KEY_DEBUG		"SOFTWARE\\LOBBY CLIENT\\debug"	// デバッグ情報
#define	SRL_REG_KEY_TRACE		"SOFTWARE\\LOBBY CLIENT\\trace"	// TRACE情報
#define	SRL_REG_KEY_MANAGE		"SOFTWARE\\LOBBY CLIENT\\manage"	// 管理情報
#define	SRL_REG_KEY_EVENT		"SOFTWARE\\LOBBY CLIENT\\event"	// イベントキュー情報
#define	SRL_REG_KEY_HANDLE		"SOFTWARE\\LOBBY CLIENT\\handle"	// ウィンドウハンドル
#define	SRL_REG_KEY_USER		"SOFTWARE\\LOBBY CLIENT\\user"	// ユーザ登録状態

//=========================================
// レジストリ項目
//=========================================
//  SOFTWARE\\LOBBY CLIENT
#define	SRL_REG_SERVERIP		"server address"		// サーバアドレス
#define	SRL_REG_CLIENT			"client name"			// クライアント名
#define	SRL_REG_USER			"user name"			// ユーザ名
#define	SRL_REG_MODE			"mode"				// デバッグモード
#define	SRL_REG_MAXUSER			"max user"			// 最大登録ユーザ数
#define	SRL_REG_MAXLOBBY		"max lobby"			// 最大登録ロビー数
#define	SRL_REG_MAXGAME			"max game"			// 最大登録ゲーム数
#define	SRL_REG_MAXGROUP		"max group"			// 最大登録グループ数
#define	SRL_REG_USERINFO		"user info"			// ユーザ情報
#define	SRL_REG_LOBBYINFO		"lobby info"			// ロビー情報
#define	SRL_REG_GROUPINFO		"group info"			// グループ情報
#define	SRL_REG_GAMEINFO		"game info"			// ゲーム情報
#define	SRL_REG_USERMASK		"user mask"			// ユーザ情報マスク
#define	SRL_REG_LOBBYMASK		"lobby mask"			// ロビー情報マスク
#define	SRL_REG_GROUPMASK		"group mask"			// グループ情報マスク
#define	SRL_REG_GAMEMASK		"game mask"			// ゲーム情報マスク
#define	SRL_REG_EVENTQUE		"event que"			// イベントキュー
#define	SRL_REG_ERRORQUE		"error que"			// エラーキュー
#define	SRL_REG_MESSAGEQUE		"message que"			// メッセージキュー
#define	SRL_REG_MESSAGEMASK		"message mask"		// メッセージキューマスク
#define	SRL_REG_ERRORMASK		"error mask"			// エラーキューマスク
#define	SRL_REG_EVENTMASK		"event mask"			// イバントキューマスク
#define	SRL_REG_EVENTHANDLE		"event handle"		// イベント管理（要求受信用）ハンドル
#define	SRL_REG_EVENTREQMASK	"event request mask"	// イベント通知マスク
#define	SRL_REG_EVENTREQ		"event request"		// イベント通知情報
#define	SRL_REG_EVENTANS		"event answer"		// イベント応答情報
#define	SRL_REG_STATUS			"user status"		    // ユーザ状態

//=========================================
// 項目値
//=========================================
// マスク情報
#define	SRL_REG_MASK_OFF	"0"					// 参照可能
#define	SRL_REG_MASK_ON		"1"					// 参照不可

// デバッグモード
#define SRL_REG_MODE_NO		"0"					// 出力なし
#define SRL_REG_MODE_MSG	"1"					// メッセージ表示あり
#define SRL_REG_MODE_FILE	"2"					// ファイル出力のみ（トレース＆ダンプ）
#define SRL_REG_MODE_TRC	"3"					// トレース出力のみ

// ユーザ状態
#define	SRL_REG_USER_OFF	"0"					// 未登録
#define	SRL_REG_USER_ON		"1"					// 登録

//=========================================
// レジストリ情報域
//=========================================

// 共通管理情報
struct	SRL_REG_INFO
{
	WORD	wMaxUser;				// 最大登録ユーザ数
	WORD	wMaxLobby;				// 最大登録ロビー数
	WORD	wMaxGame;				// 最大登録ゲーム数
	WORD	wMaxGroup;				// 最大登録グループ数
};
#define	SRL_REG_INFO_SZ		(sizeof(struct SRL_REG_INFO))


#endif
