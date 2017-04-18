/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRScom.h
 *  Content:    Lobby server & Lobby client common tools 
 ***************************************************************************/
#ifndef _SRS_COM_H_
#define _SRS_COM_H_

/***************************************************************************
 *
 *  共通定義
 *
 ***************************************************************************/
//=========================================
// ポート番号
//=========================================
#define	SRS_PORT_SERVER		7000			// サーバ接続要求用ポート番号
#define	SRS_PORT_CLIENT		6000			// クライアント接続要求用ポート番号

//=========================================
//   プロセス名
//=========================================
#define	SRS_PROC_INITIAL	"SRSinitial"		// サーバ要求待ちプロセス
#define	SRS_PROC_LOG		"SRSlog.exe"		// ログ表示プロセス
#define	SRS_PROC_LOBBY		"SRSlobby"		// サーバLobbyプロセス
#define SRL_PROC_RCV		"SRLreceive.exe"	// クライアント受信プロセス
#define SRL_PROC_SEND		"SRLsend.exe"	    // クライアント送信プロセス

//=========================================
//   メッセージ番号
//=========================================
#define SRS_MSG_LOG		WM_USER + 1					// 接続ログ通知用

//=========================================
//   メッセージ番号
//=========================================
#define SRS_WORD_ERROR		65535					// WORD型エラー復帰値

/***************************************************************************
 *
 *  Ｌｏｂｂｙサーバ管理情報域
 *
 ***************************************************************************/
//  ユーザ状態
#define	SRS_SEQ_NOENTRY		(DWORD)0x000000	// 未登録
#define	SRS_SEQ_LOBBYENTRY	(DWORD)0x010000	// ロビー参加、ゲーム未選択
#define	SRS_SEQ_GAMEENTRY	(DWORD)0x011000	// ゲーム選択、グループ未参加
#define	SRS_SEQ_GROUPENTRY	(DWORD)0x011100	// グループ参加
#define	SRS_SEQ_PLAY		(DWORD)0x011110	// ゲーム参加中

//  最大値 
#define SRS_MAX_LOBBY_USER		64			// ロビー内最大参加ユーザ数
#define SRS_MAX_LOBBY_GROUP		32			// ロビー内最大作成グループ数
#define SRS_MAX_GROUP_USER    	64			// グループ内最大参加ユーザ数

#define SRS_MAX_NAME_CLIENT		16			// 最大クライアント名域  
#define SRS_MAX_NAME_USER		40			// 最大ユーザ名域  
#define SRS_MAX_NAME_GAME		40			// 最大ゲーム名域  
#define SRS_MAX_NAME_GROUP		40			// 最大グループ名域
#define SRS_MAX_NAME_LOBBY		40			// 最大ロビー名域  

#define SRS_MAX_PASSWORD		40			// パスワード域    
#define SRS_MAX_USERAREA		40			// ユーザ固有域    
#define SRS_MAX_MESSAGE			128			// 最大メッセージ文字数
#define SRS_MAX_LOGMSG			256			// 最大ロギングメッセージ文字数

//  管理ID
#define	SRS_ID_MAINLOBBY	(WORD)0			// メインロビーＩＤ

//  ゲーム参加条件
#define SRS_GAME_PLAY		(WORD)0			// ゲーム参加
#define SRS_GAME_WATCH		(WORD)1			// ゲーム観戦

//====================================
//  ユーザ情報域
//====================================
//
// ユーザ情報域
//
struct	SRS_USER_ITEM
{
	char	USI_cClientName[SRS_MAX_NAME_CLIENT];	// クライアント名
	char	USI_cUserName[SRS_MAX_NAME_USER];		// ユーザ名
	char	USI_cPassword[SRS_MAX_PASSWORD];		// パスワード
	int		USI_iIp;								// ＩＰアドレス
	int		USI_iPort;								// 使用ポート番号
	WORD	USI_wUserID;							// ユーザＩＤ
	WORD	USI_wGameID;							// 参加ゲームＩＤ
	WORD	USI_wLobbyID;							// 参加ロビーＩＤ
	WORD	USI_wGroupID;							// 参加グループＩＤ
	DWORD	USI_dwCondetion;						// 状態
	char	USI_cUserArea[SRS_MAX_USERAREA];		// ユーザ固有域
	SYSTEMTIME	USI_time;							// ユーザ時間情報	2000.1 千葉が付け足しました
};				
#define SRS_USER_ITEM_SZ	(sizeof(struct SRS_USER_ITEM))

//
// 管理情報域
//
struct  SRS_INFO_USER
{
	WORD	US_wMaxUser;						// 最大ユーザ数
	WORD	US_wEntryUser;						// 登録ユーザ数
	struct  SRS_USER_ITEM US_info_user[1];		// ユーザ情報域群
};
#define SRS_INFO_USER_SZ		(sizeof(struct SRS_INFO_USER))
#define SRS_INFO_USER_COM_SZ	(SRS_INFO_USER_SZ - SRS_USER_ITEM_SZ)	// 共通域サイズ
//====================================
//  ゲーム情報域
//====================================
//
// ゲーム情報域
//
struct	SRS_GAME_ITEM
{
	int		GMI_iLockword;						// ロックワード
	char	GMI_cGameName[SRS_MAX_NAME_GAME];	// ゲーム名
	WORD	GMI_wGameID;						// ゲームＩＤ
	WORD	GMI_wMaxGameUser;					// 最大参加人数
	DWORD	GMI_Reserve;						// リザーブ
};
#define SRS_GAME_ITEM_SZ	(sizeof(struct SRS_GAME_ITEM))

//
// 管理情報域
//
struct	SRS_INFO_GAME
{
	WORD	GM_wMaxGame;						// 最大ゲーム数
	WORD	GM_wEntryGame;						// 登録ゲーム数
	struct  SRS_GAME_ITEM  GM_info_game[1];		// ゲーム情報域群
};
#define SRS_INFO_GAME_SZ		(sizeof(struct SRS_INFO_GAME))
#define SRS_INFO_GAME_COM_SZ	(SRS_INFO_GAME_SZ - SRS_GAME_ITEM_SZ)	// 共通域サイズ

//====================================
//  ロビー情報域
//====================================
//
// ロビー情報域
//
struct	SRS_LOBBY_ITEM
{
	int		LBI_iLockword;						// ロックワード
	char	LBI_cLobbyName[SRS_MAX_NAME_LOBBY];	// ロビー名
	WORD	LBI_wLobbyID;						// ロビーＩＤ
	WORD	LBI_Reserve;						// リザーブ
	WORD	LBI_wMaxLobbyUser;					// 最大参加人数
	WORD	LBI_wLobbyUser;						// ロビー内ユーザ数
	WORD	LBI_wUserID[SRS_MAX_LOBBY_USER];	// 参加ユーザＩＤ
	WORD	LBI_wGroupID[SRS_MAX_LOBBY_GROUP];	// 作成グループＩＤ
};
#define SRS_LOBBY_ITEM_SZ	(sizeof(SRS_LOBBY_ITEM))

//
// 管理情報域
//
struct	SRS_INFO_LOBBY
{
	WORD	LB_wMaxLobby;						// ロビー数
	WORD	LB_Reserved;						// リザーブ
	struct  SRS_LOBBY_ITEM LB_info_lobby[1];	// ロビー情報域群
};
#define SRS_INFO_LOBBY_SZ		(sizeof(struct SRS_INFO_LOBBY))
#define SRS_INFO_LOBBY_COM_SZ	(SRS_INFO_LOBBY_SZ - SRS_LOBBY_ITEM_SZ)	// 共通域サイズ

//====================================
//	グループ情報域
//====================================
//
// グループ情報要素
//
struct	SRS_GROUP_ITEM
{
	int		GPI_iLockword;						// ロックワード
	char	GPI_cGroupName[SRS_MAX_NAME_GROUP];	// グループ名
	WORD	GPI_wGroupID;						// グループＩＤ
	WORD	GPI_wGameID;						// ゲームＩＤ
	WORD	GPI_wEntryUser;						// 参加ユーザ数
	WORD   	GPI_wMaxUser;						// 最大参加人数
	WORD	GPI_wUserID[SRS_MAX_GROUP_USER];	// 参加ユーザＩＤ
}; 
#define SRS_GROUP_ITEM_SZ	(sizeof(SRS_GROUP_ITEM))

//
// 管理情報域
//
struct	SRS_INFO_GROUP
{
	WORD	GP_wMaxGroup;						// 最大グループ数
	WORD	GP_wEntryGroup;						// 登録グループ数
	struct  SRS_GROUP_ITEM	GP_info_group[1];	// グループ情報域群
};
#define SRS_INFO_GROUP_SZ		(sizeof(struct SRS_INFO_GROUP))
#define SRS_INFO_GROUP_COM_SZ	(SRS_INFO_GROUP_SZ - SRS_GROUP_ITEM_SZ)	// 共通域サイズ

/***************************************************************************
 *
 *  Ｌｏｂｂｙサーバ－クライアント間インタフェース域
 *
 ***************************************************************************/
//==============================
//  要求コード
//==============================
//
//  クライアント → サーバ 要求
//
#define IF_REQ_CONNECT		0x0001		// 接続要求
#define IF_REQ_DISCONNECT	0x0002		// 解放要求
#define IF_REQ_LOGMSG		0x0003		// ロギングメッセージ通知

#define	IF_REQ_ALL			0x0101		// 全情報参照
#define IF_REQ_USER_ENTRY	0x0111		// ユーザ登録
#define IF_REQ_USER_DELETE	0x0112		// ユーザ削除
#define IF_REQ_LOBBY_ENTRY	0x0121		// ロビーユーザ参加
#define IF_REQ_LOBBY_DEFECT	0x0122		// ロビーユーザ脱退
#define IF_REQ_GROUP_MAKE	0x0131		// グループ作成
#define IF_REQ_GROUP_JOIN	0x0132		// グループ参加
#define IF_REQ_GROUP_DEFECT	0x0133		// グループ脱退
#define IF_REQ_GAME_JOIN	0x0141		// ゲーム参加
#define IF_REQ_GAME_DEFECT	0x0142		// ゲーム脱退
#define IF_REQ_GAME_START	0x0143		// ゲーム開始
#define IF_REQ_GAME_END		0x0144		// ゲーム終了
#define IF_REQ_SENDMSG		0x0151		// メッセージ送信
#define IF_REQ_SAVE_INFO	0x0161		// 固有情報待避

//
// サーバ → クライアント 要求
//
#define IF_REQ_RENEWAL		0x0201		// 情報更新
#define IF_REQ_RCVMSG		0x0202		// メッセージ受信

//
// コマンド → サーバ 要求
//
#define IF_REQ_TERMINATE	0xFFFF		// 終了要求

//================================
//  結果コード
//================================
#define IF_CMP_SUCCESS		0x0000		// 成功
#define IF_CMP_MAXOVER		0xFF01		// 最大値オーバ
#define IF_CMP_MULTI		0xFF02		// ２重登録
#define IF_CMP_AREAOVER		0xFF03		// 資源不足
#define IF_CMP_SEQERR		0xFF04		// 要求シーケンスエラー
#define IF_CMP_PROCERR		0xFF05		// Lobbyプロセス起動エラー
#define IF_CMP_ERROR		0xFFFF		// システム（プログラム）エラー

//====================================
//  インタフェースブロック
//====================================
//
//  固定域
//
struct  SRS_IF_FIX
{
	WORD	IF_wRequest;			// 要求コード
	WORD	IF_wResult;				// 結果コード
	int		IF_iInformationSize;	// 情報域長
	int		IF_iPortNo;				// サーバ通信用ポート番号
	int		IF_iIp;					// クライアントIPアドレス
	char	IF_cInformation[4];		// 情報域
};
#define	SRS_IF_FIX_SZ	(sizeof(struct SRS_IF_FIX) - 4)

//====================================
//  情報域（要求）
//====================================
//=========================
//  接続要求 
//=========================
struct	SRS_IF_CONNECT
{
	WORD	IF_CN_wMaxUser;			// 最大ユーザ数
	WORD	IF_CN_wMaxLobby;		// 最大ロビー数
	WORD	IF_CN_wMaxGroup;		// 最大グループ数
	WORD	IF_CN_wMaxGame;			// 最大ゲーム数
	char	IF_CN_cMessage[SRS_MAX_MESSAGE];
};
#define	SRS_IF_CONNECT_SZ 		(sizeof(struct SRS_IF_CONNECT))

//========================
//  ロギングメッセージ
//========================
struct	SRS_IF_LOGMSG
{
	char	IF_LM_cMessage[SRS_MAX_LOGMSG];		// 表示メッセージ
};
#define	SRS_IF_LOGMSG_SZ 		(sizeof(struct SRS_IF_LOGMSG))

//========================
//  ユーザ登録 
//========================
struct	SRS_IF_USER_ENTRY
{
	char	IF_UE_cClientName[SRS_MAX_NAME_CLIENT];	// クライアント名
	char	IF_UE_cUserName[SRS_MAX_NAME_USER];		// ユーザ名
};
#define SRS_IF_USER_ENTRY_SZ	(sizeof(struct SRS_IF_USER_ENTRY))

//========================
// == ユーザ削除 ==
//========================
struct	SRS_IF_USER_DELETE
{
	WORD	IF_UD_wUserID;			// ユーザＩＤ
	WORD	IF_UD_wReserved;		// リザーブ
};
#define SRS_IF_USER_DELETE_SZ	(sizeof(struct SRS_IF_USER_DELETE))

//========================
//  ロビーユーザ参加 
//========================
struct	SRS_IF_LOBBY_ENTRY
{
	WORD	IF_LE_wUserID;			// 参加ユーザＩＤ
	WORD	IF_LE_wLobbyID;			// 参加ロビーＩＤ
};
#define SRS_IF_LOBBY_ENTRY_SZ	(sizeof(struct SRS_IF_LOBBY_ENTRY))

//========================
//  ロビーユーザ脱退 
//========================
struct	SRS_IF_LOBBY_DEFECT
{
	WORD	IF_LD_wUserID;			// 脱退ユーザＩＤ
	WORD	IF_LD_wLobbyID;			// 脱退ロビーＩＤ
};
#define SRS_IF_LOBBY_DEFECT_SZ	(sizeof(struct SRS_IF_LOBBY_DEFECT))

//========================
//  グループ作成 
//========================
struct	SRS_IF_GROUP_MAKE
{
	WORD	IF_GM_wUserID;							// 主催ユーザＩＤ
	WORD	IF_GMwReserved;							// リザーブ
	char	IF_GM_cGroupName[SRS_MAX_NAME_GROUP];	// 作成グループ名
};
#define SRS_IF_GROUP_MAKE_SZ	(sizeof(struct SRS_IF_GROUP_MAKE))

//========================
//  グループ参加 
//========================
struct	SRS_IF_GROUP_JOIN
{
	WORD	IF_GJ_wUserID;			// 参加ユーザＩＤ
	WORD	IF_GJ_wGroupID;			// 参加グループＩＤ
	WORD	IF_GJ_wCondition;		// 参加条件
	WORD	IF_GJ_wReserved;		// リザーブ
};
#define SRS_IF_GROUP_JOIN_SZ	(sizeof(struct SRS_IF_GROUP_JOIN))

//========================
//  グループ脱退 
//========================
struct	SRS_IF_GROUP_DEFECT
{
	WORD	IF_GD_wUserID;			// 脱退ユーザＩＤ
	WORD	IF_GD_wGroupID;			// 脱退グループＩＤ
};
#define SRS_IF_GROUP_DEFECT_SZ	(sizeof(struct SRS_IF_GROUP_DEFECT))

//========================
//  ゲーム参加 
//========================
struct	SRS_IF_GAME_JOIN
{
	WORD	IF_GJ_wUserID;			// 参加ユーザＩＤ
	WORD	IF_GJ_wGameID;			// 参加ゲームＩＤ
	WORD	IF_GJ_wCondition;		// 参加条件
	WORD	IF_GJ_wReserved;		// リザーブ
};
#define SRS_IF_GAME_JOIN_SZ	(sizeof(struct SRS_IF_GAME_JOIN))

//========================
//  ゲーム脱退 
//========================
struct	SRS_IF_GAME_DEFECT
{
	WORD	IF_GD_wUserID;			// 脱退ユーザＩＤ
	WORD	IF_GD_wGameID;			// 脱退ゲームＩＤ
};
#define SRS_IF_GAME_DEFECT_SZ	(sizeof(struct SRS_IF_GAME_DEFECT))

//========================
//  ゲーム開始 
//========================
struct	SRS_IF_GAME_START
{
	WORD	IF_GS_wUserID;			// ユーザＩＤ
	WORD	Reserve;				// リザーブ
};
#define SRS_IF_GAME_START_SZ	(sizeof(struct SRS_IF_GAME_START))

//========================
//  ゲーム終了 
//========================
struct	SRS_IF_GAME_END
{
	WORD	IF_GE_wUserID;			// ユーザＩＤ
	WORD	IF_GE_Reserve;			// リザーブ
};
#define SRS_IF_GAME_END_SZ	(sizeof(struct SRS_IF_GAME_END))

//========================
//  固有情報待避 
//========================
struct	SRS_IF_SAVE_INFO
{
	WORD	IF_SI_wUserID;					// ユーザＩＤ
	WORD	IF_SI_Reserve;					// リザーブ
	char	IF_SI_cInfo[SRS_MAX_USERAREA];	// 固有情報
};
#define SRS_IF_SAVE_INFO_SZ	(sizeof(struct SRS_IF_SAVE_INFO))

//========================
//  情報更新 
//========================
struct	SRS_IF_RENEWAL
{
	WORD	IF_RE_wUserInfoNo;		// 更新ユーザ情報数
	WORD	IF_RE_wLobbyInfoNo;		// 更新ロビー情報数
	WORD	IF_RE_wGroupInfoNo;		// 更新グループ情報数
	WORD	IF_RE_wGameInfoNo;		// 更新ゲーム情報数
	char	IF_RE_cInfo[4];			// 管理情報域
};
#define SRS_IF_RENEWAL_SZ	(sizeof(struct SRS_IF_RENEWAL) - 4 )

//========================
// メッセージ送信／受信 
//========================
struct	SRS_IF_MESSAGE
{
	WORD	IF_MS_wUserID;						// 送信元ユーザＩＤ
	WORD	IF_MS_wMessageCode;					// メッセージコード
	char	IF_MS_cMessage[SRS_MAX_MESSAGE];	// メッセージ本文
};
#define SRS_IF_MESSAGE_SZ	(sizeof(struct SRS_IF_MESSAGE))

#endif
