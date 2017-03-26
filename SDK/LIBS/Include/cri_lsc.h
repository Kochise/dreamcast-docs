#ifndef	_CRI_LSC_H_INCLUDED
#define	_CRI_LSC_H_INCLUDED
/****************************************************************************/
/*																			*/
/*			$title$ 連結ストリームコントローラ ライブラリ					*/
/*				LSC (Linking Stream Controller) Library						*/
/*																			*/
/*			Copyright (c) 1999 CSK Research Institute						*/
/*				1998.7.12		written by S.Hosaka							*/
/*																			*/
/****************************************************************************/

/****************************************************************************/
/*	インクルードファイル													*/
/****************************************************************************/

#include	<sj.h>

/****************************************************************************/
/*	定数マクロ																*/
/****************************************************************************/

/*	Version No.					*/
#define	LSC_VER				"1.02"

/*	最大ストリーム数			*/
#define	LSC_STM_MAX			(16)

/*	ハンドルの個数				*/
#define	LSC_OBJ_MAX			(8)

/*	ファイル名の最大文字数		*/
#define	LSC_FNAME_MAX		(32)

/*	動作状態					*/
#define	LSC_STAT_STOP		(0)
#define	LSC_STAT_WAIT		(1)
#define	LSC_STAT_EXEC		(2)
#define	LSC_STAT_ERR		(3)

/*	ストリーム読み込みの状態	*/
#define	LSC_STM_STAT_WAIT	(0)
#define	LSC_STM_STAT_READ	(1)
#define	LSC_STM_STAT_END	(2)

/****************************************************************************/
/*	列挙定数																*/
/****************************************************************************/

/****************************************************************************/
/*	処理マクロ																*/
/****************************************************************************/

/****************************************************************************/
/*	データ型																*/
/****************************************************************************/

/*	エラー登録関数				*/
typedef void (*LSC_ERRFN)(void *obj, char *msg);
typedef void (*LSC_STATFN)(void *obj1, void *obj2);

/*	ストリーム情報				*/
#ifndef LSC_SINFO_DEFINED
#define LSC_SINFO_DEFINED
typedef struct _lsc_sinfo {
	long		sid;						/*	ストリームID				*/
	char		fname[LSC_FNAME_MAX];		/*	ファイル名					*/
	long		stat;						/*	ストリームの読み込み状態	*/
	long		rdsct;						/*	読み込みセクタ数			*/
} LSC_SINFO;
#endif

#ifndef LSC_FP_DEFINED
#define LSC_FP_DEFINED
typedef void	*LSC_FP;
#endif

/*	ハンドル					*/
#ifndef LSC_DEFINED
#define LSC_DEFINED
typedef struct _lsc_obj {
	char		used;						/*	使用中か否か				*/
	char		stat;						/*	ハンドル状態				*/
	char		rdflg;
	char		lpflg;
	char		pause;
	char		rsv1;
	short		rsv2;
	SJ			sj;							/*	ストリームジョイント		*/
	SJCK		ck;
	long		bufmin;						/*	バッファ流量下限値			*/
	long		bsize;
	long		wpos;
	long		rpos;
	long		nstm;						/*	登録ストリーム数			*/
	LSC_FP		fp;
	long		fsct;
	long		reqsct;
	LSC_SINFO	sinfo[LSC_STM_MAX];			/*	読み込み中のストリーム情報	*/
} LSC_OBJ;
typedef LSC_OBJ *LSC;
#endif

/****************************************************************************/
/*	変数宣言																*/
/****************************************************************************/

/****************************************************************************/
/*	関数宣言																*/
/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*	初期化					*/
void LSC_Init(void);

/*	終了処理				*/
void LSC_Finish(void);

/*	エラー処理関数の登録	*/
void LSC_EntryErrFunc(LSC_ERRFN errfn, void *obj);

/*	ハンドルの生成			*/
LSC LSC_Create(SJ sj);

/*	ハンドルの消去			*/
void LSC_Destroy(LSC lsc);

/*	ストリームの登録		*/
long LSC_EntryFname(LSC lsc, char *fname);

/*	読み込み開始			*/
void LSC_Start(LSC lsc);

/*	読み込み停止			*/
void LSC_Stop(LSC lsc);

/*	ポーズ・ポーズ解除		*/
void LSC_Pause(LSC lsc, long sw);

/*	サーバ関数				*/
void LSC_ExecServer(void);

/*	ハンドル状態の取得		*/
long LSC_GetStat(LSC lsc);

/*	登録ストリーム数の取得	*/
long LSC_GetNumStm(LSC lsc);

/*	読み込み中のストリームIDの取得	*/
long LSC_GetStmId(LSC lsc, long no);

/*	ファイル名の取得	*/
char *LSC_GetStmFname(LSC lsc, long sid);

/*	ストリーム読み込みの状態取得	*/
long LSC_GetStmStat(LSC lsc, long sid);

/*	読み込んだデータサイズの取得(sector)	*/
long LSC_GetStmRdSct(LSC lsc, long sid);

/*	バッファ流量下限値の設定	*/
void LSC_SetFlowLimit(LSC lsc, long min);

/*	バッファ流量下限値の取得	*/
long LSC_GetFlowLimit(LSC lsc);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif	/* _CRI_LSC_H_INCLUDED */
