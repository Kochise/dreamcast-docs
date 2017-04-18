/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSregistly.h
 *  Content:    Lobby server registry access include file
 ***************************************************************************/
#ifndef _SRS_REGISTRY_H_
#define _SRS_REGISTRY_H_

//=========================================
//   関数定義
//=========================================
__declspec( dllexport )int __stdcall SRS_Reg_GetComInfo( struct SRS_REG_INFO *lpRegInfo );
__declspec( dllexport )int __stdcall SRS_Reg_GetLobbyInfo( int iCount, struct SRS_REG_INFO_LOBBY *lpRegInfoLobby );
__declspec( dllexport )int __stdcall SRS_Reg_GetGameInfo( int iCount, struct SRS_REG_INFO_GAME *lpRegInfoGame );
__declspec( dllexport )int __stdcall SRS_Reg_GetInfo( char *lpRegKey, char *lpReg, char *lpBuff );
__declspec( dllexport )int __stdcall SRS_Reg_SetInfo( char *lpRegKey, char *lpReg,char *lpBuff );
__declspec( dllexport )int __stdcall SRS_Reg_SetInfoBinary( char *lpRegKey, char *lpReg, char *lpBuff, DWORD dwSize );
__declspec( dllexport )int __stdcall SRS_Reg_GetInfoBinary( char *lpRegKey, char *lpReg, char *lpBuff, DWORD dwSize );
__declspec( dllexport )int __stdcall SRS_Reg_SetInfoDWORD( char *lpRegKey, char *lpReg, DWORD dwInfo );
__declspec( dllexport )DWORD __stdcall SRS_Reg_GetInfoDWORD( char *lpRegKey,char *lpReg );
__declspec( dllexport )int __stdcall SRS_Reg_Log( char *lpLog );

//=========================================
// レジストリキー
//=========================================
//  固定
#define	SRS_REG_KEY_COM			"SOFTWARE\\LOBBY SERVER"			// サーバ共通情報
#define	SRS_REG_KEY_LOBBY		"SOFTWARE\\LOBBY SERVER\\lobby"		// ロビー固有情報
#define	SRS_REG_KEY_GAME		"SOFTWARE\\LOBBY SERVER\\game"		// ゲーム固有情報
#define	SRS_REG_KEY_DEBUG		"SOFTWARE\\LOBBY SERVER\\debug"		// デバッグ情報
#define	SRS_REG_KEY_LOGGING		"SOFTWARE\\LOBBY SERVER\\logging"	// ロギング情報
#define	SRS_REG_KEY_CHATLOG		"SOFTWARE\\LOBBY SERVER\\chatlog"	// チャットログ情報

//=========================================
// レジストリ項目
//=========================================
//  SOFTWARE\\LOBBY SERVER
#define	SRS_REG_CLIENTPORT	"client port"		// クライント割当て先頭ポート番号
#define	SRS_REG_SEND		"send mode"			// 更新情報配信要否
#define	SRS_REG_MAXUSER		"max user"			// 最大登録ユーザ数
#define	SRS_REG_MAXLOBBY	"max lobby"			// 最大登録ロビー数
#define	SRS_REG_MAXGAME		"max game"			// 最大登録ゲーム数
#define	SRS_REG_MAXGROUP	"max group"			// 最大登録グループ数
#define	SRS_REG_LOGHANDLE	"logging handle"	// ロギングウィンドウハンドル
#define	SRS_REG_LOGMSG		"logging message"	// ロギングメッセージ


//  SOFTWARE\\LOBBY SERVER\\lobby & SOFTWARE\\LOBBY SERVER\\game
#define	SRS_REG_MAXENTRY	"max entry"			// 最大参加人数（ロビー＆ゲーム）
#define	SRS_REG_NAME  	    "name"				// 名前（ロビー＆ゲーム）

//  SOFTWARE\\LOBBY SERVER\\debug
#define	SRS_REG_MODE  	    "mode"				// デバッグモード

//  SOFTWARE\\LOBBY SERVER\\chatlog				
#define	SRS_REG_CHATLOG_MODE "mode"				// チャットログモード

//  チャットログモード定義値
#define	SRS_DBG_CHATLOG_OFF		"0"				// 出力なし
#define	SRS_DBG_CHATLOG_ON		"1"				// 全出力

//  配信要否 定義値
#define	SRS_SEND_MODE_NO	"0"					// 配信しない
#define	SRS_SEND_MODE_NEED	"1"					// 配信する

//  デバッグモード定義値
#define	SRS_DBG_MODE_NO		"0"					// 出力なし
#define	SRS_DBG_MODE_MSG	"1"					// 全出力（ファイル出力、メッセージ表示）
#define	SRS_DBG_MODE_FILE	"2"					// トレース＆ダンプ出力
#define	SRS_DBG_MODE_TRC	"3"					// トレース出力のみ

//=========================================
// レジストリ情報域
//=========================================

// 共通管理情報
struct	SRS_REG_INFO
{
	WORD	wMaxUser;				// 最大登録ユーザ数
	WORD	wMaxLobby;				// 最大登録ロビー数
	WORD	wMaxGame;				// 最大登録ゲーム数
	WORD	wMaxGroup;				// 最大登録グループ数
};
#define	SRS_REG_INFO_SZ		(sizeof(struct SRS_REG_INFO))

// 固有ロビー情報
struct	SRS_REG_INFO_LOBBY
{
	WORD	wMaxUser;					// 最大参加ユーザ数
	WORD	wReserve;					// リザーブ
	char	cName[SRS_MAX_NAME_LOBBY];	// ロビー名
};
#define	SRS_REG_INFO_LOBBY_SZ		(sizeof(struct SRS_REG_INFO_LOBBY))

// 固有ゲーム情報
struct	SRS_REG_INFO_GAME
{
	WORD	wMaxUser;					// 最大参加ユーザ数
	WORD	wReserve;					// リザーブ
	char	cName[SRS_MAX_NAME_GAME];	// ゲーム名
};
#define	SRS_REG_INFO_GAME_SZ		(sizeof(struct SRS_REG_INFO_GAME))

#endif
