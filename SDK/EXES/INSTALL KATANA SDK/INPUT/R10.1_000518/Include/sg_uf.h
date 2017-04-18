/*============================================================
 * Name  : sg_flash.h
 *
 * Desc  : 内蔵フラッシュメモリアクセスライブラリ
 	* Desc  : Internal Flash Memory Access Library
 *
 * prefix: uf / UFD / UFS
 *
 * $Id: sg_flash.h 1.2 1998/12/25 02:34:07 horita Exp horita $
 *
 * $Log: sg_flash.h $
 * Revision 1.2  1998/12/25 02:34:07  horita
 * エラー番号の追加
 * UFD_ERR_PERIINITFAIL,	ペリフェラルの初期化が終わっていない
 * UFD_ERR_REFRESHFAIL,		リフレッシュに失敗
 	* Adding Error Code
 	* UFD_ERR_PERIINITFAIL,	Peripheral Initialize not completed
 	* UFD_ERR_REFRESHFAIL, Fault in Flash Memory Refresh	
 *
 * Revision 1.1  1998/12/25 02:33:43  horita
 * Initial revision
 *
 * Revision 1.3  1998/12/14 05:05:34  horita
 * 終了関数(ufExitSystem)の追加
 	* Adding Exit function (ufExitSystem) 
 *
 * Revision 1.2  1998/11/17 01:16:35  horita
 * 構造体のタグ名に説明をつけた。
 	* Adding explanation to structure tag names. 
 *
 * Revision 1.1  1998/11/16 02:26:31  horita
 * Initial revision
 *
 *============================================================*/

#ifndef __SG_FLASH_H__
#define __SG_FLASH_H__
/*============================================================
  Include
  ============================================================*/
#include <sg_xpt.h>

/*============================================================
  Define
  ============================================================*/
/* PlayTime関数のモード */
	/* Mode of PlayTime function */
enum {
	UFD_SAVE, UFD_LOAD, UFD_PLAY
};

/* ChangeAutoSaveのフラグ値 */
	/* Value of the falg, ChangeAutoSave */
enum {
	UFD_OFF,
	UFD_ON,
	UFD_UNK = 255
};


/* uf_Errno のエラー番号 */
	/* Error code of uf_Errno */
typedef enum {
	UFD_ERR_USERFLAG_PARITY_ERROR = 1,				/* 共通フラグにパリティエラーがあった */
										/* Parity error in common flag */
	UFD_ERR_BANKNUMBER_ERROR,					/* バンク番号が不正 */
										/* Bunk number incorrect */
	UFD_ERR_PROTECT_COMMON_FLAG,					/* 共通フラグがアクセス禁止になっている */
										/* Common flag access prohibited */
	UFD_ERR_PROTECT_FLAG,						/* タイトルはアクセス禁止になっている */
										/* Title access prohibited */
	UFD_ERR_NO_INIT,						/* 初期化が終了していない */
										/* Initialize not completed */
	UFD_ERR_INIT_FAIL,						/* 初期化に失敗した */
										/* Initialize faulted */
	UFD_ERR_READ_FAIL,						/* 読み込みに失敗した */
										/* Read faulted */
	UFD_ERR_WRITE_FAIL,						/* 書き込みに失敗した */
										/* Write faulted  */
	UFD_ERR_NOT_FOUND,						/* 指定した商品番号は見つからなかった */
										/* Requested Product number not found */
	UFD_ERR_NO_PACKET_LEFT,						/* 追記パケットの残りが無い */
										/* No writing packet available */
	UFD_ERR_MEMORY_FAIL,						/* 処理に必要なメモリが無い */
										/* Not enough memory available*/
	UFD_ERR_PERIINITFAIL,						/* ペリフェラルの初期化が終わっていない */	
										/* Peripheral Initialize not completed */	
	UFD_ERR_REFRESHFAIL,						/* リフレッシュに失敗 */
										/* Refresh falted */
	UFD_ERR_MAX
} UFS_ERROR;

/* パケット0の定義 */
/* Packet 0 definition */
#define UFD_PLAYHIST_PACKET0  \
	Uint8	version; 						/* ライブラリのバージョン */ \
										/* Library version */ \
	Uint8	AutoSave; 						/* 自動保存フラグ */ \
										/* Auto Save Flag */ \
	Uint8	ProdNum[10]; 						/* 商品番号 */ \
										/* Product number */ \
	Uint8	ProdName[48];						/* 商品名（英語） */
										/* Product name (English) */

/* パケット1の定義 */
/* Packet 1 definition */

#define UFD_PLAYHIST_PACKET1  \
	Uint8	ProdName2[44];						/* 商品名日本語 */ \
										/* Product name (Japanese) */ \
	Uint32	Kind;							/* ゲーム種別 */ \
										/* Game genre */ \
	Uint32	FirstStartTime;						/* 初回起動日時 */ \
										/* First boot date & time */ \
	Uint16	CRC;							/* 商品番号から商品名までのCRC */ \
										/* CRC for from product number to product name */ \
	Uint8	PeriIdx[6];						/* ペリフェラル情報 */
										/* Peripheral information */


/* パケット2の定義 */
/* Packet 2 definition */
#define UFD_PLAYHIST_PACKET2  \
	Uint32	PrevStartTime;						/* 前回起動日時 */ \
										/* Previous boot day & time */ \
	Uint16	StartCount;						/* 起動回数 */ \
										/* Number of boots */ \
	Uint16	PlayTime[24];						/* プレイ時間履歴 */ \
										/* Play time history */ \
	Uint16	LoadCount;						/* ロード回数 */ \
										/* Number of loads */ \
	Uint32	Reserve_2;						/* リザーブ */
										/* Sega reserved */

/* パケット3の定義 */
/* Packet 3 definition */
#define UFD_PLAYHIST_PACKET3  \
	Uint16	SaveCount;						/* セーブ回数 */ \
										/* Number of saves */ \
	Uint8	GameEst;						/* プレイ評価 */ \
										/* Play Evaluation */ \
	Uint8	GameCarry;						/* 攻略率 */ \
										/* Play progress */ \
	Uint32	FirstNetPlay;						/* 初回ネットワークプレイ日時 */ \
										/* First network play day & time */ \
	Uint32	PrevNetPlay;						/* 前回ネットワークプレイ日時 */ \
										/* Previous network play day & time */ \
	Uint16	NetPlayCount;						/* ネットワークプレイ回数 */ \
										/* Number of network play */ \
	Uint16	NetPlayTotalTime;					/* 全ネットワークプレイ時間(分) */ \
										/* Total network play time(min.) */ \
	Uint8	FreeArea[32];						/* ユーザー開放領域 */ \
										/* User area */ \
	Uint8	Reserved2[10];						/* リザーブ */ \
										/* Sega reserved */ \
	Uint16	SaveOccur;						/* フラッシュへのセーブ回数 */
										/* Number of Flash Memory saves */

/* ワークサイズの定義 -- バイト単位 */
/* Definition of work size -- bytes */
#define	UFD_WORK1_SIZ	65536						/* 64K -- 必ず必要なバッファのサイズ */
										/* 64K -- Minimum required buffer size */
#define	UFD_WORK2_SIZ	60						/*  60 -- 必ず必要な読み込み用バッファのサイズ */
										/*  60 -- Minimum required reading buffer size */
#define UFD_WORK3_SIZ	65536						/* 64K -- セーフリフレッシュ時に必要なバッファのサイズ1 */
										/* 64K -- Required buffer size for safe refresh */
#define UFD_WORK4_SIZ	32768						/* 32K -- セーフリフレッシュ時に必要なバッファのサイズ2 */
										/* 32K -- Required buffer size for safe refresh */
#define	UFD_REQUIRED_REST_PACKET	2				/* 最低必要な追記可能パケット数 */
										/* Minimum required number of writing packet */
#define UFD_WORK_NOCHANGE	((void *)-1)				/* ufChangeWorkBuffer時にワークを変更しない時の定数 */
										/* Constant for not-changing work while ufChangeWorkBuffer */

/*============================================================
  Macro
  ============================================================*/

/*============================================================
  Structure
  ============================================================*/
/* プレイヒストリパケット 0 */
	/* Play history Packet 0 */
typedef struct tagUFS_Packet0 {
	UFD_PLAYHIST_PACKET0
} UFS_HistoryPacket0;

/* プレイヒストリパケット 1 */
	/* Play history Packet 1 */
typedef struct tag_HistoryPacket1 {
	UFD_PLAYHIST_PACKET1
} UFS_HistoryPacket1;

/* プレイヒストリパケット 2 */
	/* Play history Packet 2 */
typedef struct tagUFS_HistoryPacket2 {
	UFD_PLAYHIST_PACKET2
} UFS_HistoryPacket2;

/* プレイヒストリパケット 3 */
	/* Play history Packet 3 */
typedef struct tagUFS_HistoryPacket3 {
	UFD_PLAYHIST_PACKET3
} UFS_HistoryPacket3;

/* プレイヒストリ(パケット単位) */
	/* Play History(par Packet) */
typedef struct tagUFS_PlayHistory {
	UFS_HistoryPacket0	packet0;
	UFS_HistoryPacket1	packet1;
	UFS_HistoryPacket2	packet2;
	UFS_HistoryPacket3	packet3;
} UFS_PlayHistory;

/* プレイヒストリ */
	/* Play History */
typedef struct tagUFS_AllPlayHistory {
	UFD_PLAYHIST_PACKET0
	UFD_PLAYHIST_PACKET1
	UFD_PLAYHIST_PACKET2
	UFD_PLAYHIST_PACKET3
} UFS_AllPlayHistory;

/*============================================================
  Global
  ============================================================*/
extern UFS_ERROR ufgErrno;							/* エラー番号 */
											/* Error code */

/*============================================================
  API
  ============================================================*/
Bool ufInitSystem(void* work1, void* work2, void* work3, void* work4);		/* 初期化関数 */
											/* Initialize function */
Bool ufChangeWorkBuffer(void* work1, void* work2, void* work3, void* work4); 	/* ワークの変更 */
/* Work Change */
Sint32 ufPlayTime(Uint8 mode, Uint8 est, Uint8 carry, Uint8 param[32]);		/* プレイ時間の更新 */
											/* Updating Play time */
Bool ufSynch(void);								/* プレイデータの書き出し */
											/* Writing Play data */
Bool ufAutoSynch(Uint32 count);							/* プレイデータ更新間隔の指定 */
											/* Play data update interval */
Bool ufReadAllProduct(Uint8* Buffer);						/* タイトルリストの所得 */
											/* get Title list */ 
Bool ufReadAllHead(Uint8* ProdNum, UFS_AllPlayHistory* buff); 			/* タイトル別プレイ履歴の参照 */
											/* Refer individual Play history */
Bool ufTitleDelete(void);							/* タイトル別プレイ履歴の消去 */
											/* Erase individual Play history */
Bool ufChangeAutoSave(Uint8 Flag);						/* 自動保存フラグの変更 */
											/* Change Auto save flag */
Bool ufConnect(Uint32 time);							/* サーバ接続時のタイトルデータの更新 */
											/* Data update for network connect */
Bool ufDisConnect(void);							/* サーバ切断時のタイトルデータの更新 */
											/* Data update for network disconnect */
Bool ufSafeRefresh(void);							/* フラッシュメモリのリフレッシュ */
											/* Flash Memory refresh */
Bool ufGetControllerList(Uint32* list);						/* コントローラリストの所得 */
											/* get controller list */
Bool ufGetExtControllerList(Uint32* list);					/* 拡張コントローラリストの所得 */
											/* get extended controller list */
void ufExitSystem(void);							/* ライブラリ終了 */
											/* Exit this library */										

/*============================================================*
 *------------------------------------------------------------*
 * End of File                                                *
 *------------------------------------------------------------*
 *============================================================*/
#endif 
