#ifndef _SG_SM_H_INCLUDED
#define _SG_SM_H_INCLUDED
/***********************************************************************
 *
 *				V-Syncカウンタライブラリヘッダ
 *				（忍ライブラリサンプル）
 *
 *      Copyright(c) SEGA ENTERPRISES, LTD., 1998
 *      Ver.1.00	(1998-2-15) 	Written by mOshimi
 *----------------------------------------------------------------------
 *		Note:
 ************************************************************************/

/*
	■ V-Syncカウンタライブラリ
	　本ライブラリは、忍ライブラリのためのひな型です。これに準拠することにより
	オーバレイに対応することができます。
	V-syncカウンタライブラリは、V-Syncの起きた回数を取得するためのライブラリ
	です。ハンドル内部にカウンタ変数を持ち、V-Sync割り込みの起きた回数を
	カウントします。初期化時に、V-Sync割り込みルーチンにVCNT_ExecServer関数を
	登録します。VCNT_ExecServer関数は、割り込みによって呼び出され、ステータス
	が実行中の場合はカウンタ変数を１インクリメントします。
	また、VCNT_Start関数によってカウントをスタートし、VCNT_Stop関数で停止
	します。ステータスは、VCNT_GetStat関数で取得できます。

	＜インタフェース関数＞　グローバル関数呼び出すための関数
	void smVcntInit(void);
	void smVcntFinish(void);
	void smVcntExecServer(void);
	SmVcnt smVcntCreate(Sint32 cntmax);
	＜グローバル関数＞　グローバル変数・スタティック変数をアクセスする関数
	void smVcntInitG(void);
	void smVcntFinishG(void);
	void smVcntExecServerG(void);
	SmVcnt smVcntCreateG(Sint32 cntmax);
	＜ハンドル関数＞　　ハンドル内部の変数のみアクセスする関数
	SmVcnt smVcntDestroy(SmVcnt vcnt);
	Sint32 smVcntGetStat(SmVcnt vcnt);
	void smVcntStart(SmVcnt vcnt);
	void smVcntStop(SmVcnt vcnt);
	Sint32 smVcntGetCnt(SmVcnt vcnt);
	void smVcntSetCnt(SmVcnt vcnt, Sint32 cnt);
*/

#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif

#ifdef _NON_NINJA_
#include	<sg_xpt.h>
#endif
#include	<sg_ov.h>

/*	ライブラリIDの定義												*/
#define SmVcntD_LID { \
	0x211b2800, 0xa6a9, 0x11d1, 0x8f, 0x3f, 0x00, 0x60, 0x08, 0x94, 0x48, 0xbc\
}\

EXTERN_C const UUID SmVcntLID;


/*  ライブラリのバージョン													*/
#define	SmVcntD_VERSION_NO	(0x01)		/*  バージョン番号					*/
#define	SmVcntD_REVISION_NO	(0x00)		/*  リビジョン番号					*/

/*	V-Syncカウンタハンドルの最大数											*/
#define SmVcntD_MAX	(16)

/*	V-Syncカウンタハンドルの動作状態										*/
enum {
	SmVcntE_STAT_STOP=0,				/*	カウント停止中					*/
	SmVcntE_STAT_EXEC					/*	カウント実行中					*/
};

/*	V-Sync カウンタ用クリティカルセクション変数								*/
/*	（実際は、割り込みマスクレベル)											*/
typedef Sint32 SmVcntCs;

/*	V-Syncカウンタハンドル	*/
typedef struct {
	Uint8	used;						/*	使用中か否か					*/
	Uint8	stat;						/*	動作状態						*/
	Sint16	rsv2;						/*	予約領域						*/
	Sint32	max;						/*	カウンタの上限値				*/
	Sint32	cnt;						/*	V カウンタ						*/
} SmVcntObj;
typedef SmVcntObj *SmVcnt;

/*	各ライブラリが必ず作成するライブラリインタフェース関数  				*/
typedef struct {
	void	(*QueryInterface)();		/*	for COM compatibility			*/
	void	(*AddRef)();				/*	for COM compatibility			*/
	void	(*Release)();				/*	for COM compatibility			*/
	void	(*Init)(OvLib ovl);			/*	初期化							*/
	void	(*Finish)(OvLib ovl);		/*	終了処理						*/
	void	(*Exec)(void);				/*	実行(サーバ関数)				*/
	SmVcnt	(*Create)(Sint32 cntmax);	/*	V-Syncハンドルの生成			*/
} SmVcntLif;
typedef SmVcntLif *SmVcntI;

/*	ライブラリハンドル	*/
extern SmVcntLif SmVcntG_lif;

/***
*		ユーザ関数プロトタイプ
***/

/*	ライブラリの初期化	*/
void smVcntInit(void);
/*	ライブラリの終了	*/
void smVcntFinish(void);
/*	Vカウンタハンドルの生成	*/
SmVcnt smVcntCreate(Sint32 cntmax);
/*	Vカウンタハンドルの消去	*/
void smVcntDestroy(SmVcnt vcnt);
/*	動作状態の取得	*/
Sint32 smVcntGetStat(SmVcnt vcnt);
/*	カウントの開始	*/
void smVcntStart(SmVcnt vcnt);
/*	カウントの停止	*/
void smVcntStop(SmVcnt vcnt);
/*	カウント値の取得	*/
Sint32 smVcntGetCnt(SmVcnt vcnt);
/*	カウント値の設定	*/
void smVcntSetCnt(SmVcnt vcnt, Sint32 cnt);
/*	サーバ関数（通常はユーザは使用しない）	*/
void smVcntExecServer(void);

/***
*		内部関数
***/

/*	クリティカルセクションへの進入	*/
void smVcntLockCs(SmVcntCs *cs);
/*	クリティカルセクションからの脱出	*/
void SmVcntUnlockCs(SmVcntCs *cs);

/*	ライブラリの初期化	(グローバル関数)	*/
void smVcntInitG(OvLib ovl);
/*	ライブラリの終了	(グローバル関数)	*/
void smVcntFinishG(OvLib ovl);
/*	V カウンタハンドルの生成	(グローバル関数)	*/
SmVcnt smVcntCreateG(Sint32 cntmax);
/*	サーバ関数	(グローバル関数)	*/
void smVcntExecServerG(void);

#endif		/*	#ifndef _SM_H_INCLUDED		*/
