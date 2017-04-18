/*
 *
 *		SofdecF/X Multi-Streaming Sample
 *
 */

/***************************************************************************
 *      インクルードファイル
 *      Include file
 ***************************************************************************/

#include	<shinobi.h>
#include	<sg_mw.h>
#include	<string.h>

#include	"usr.h"

/***************************************************************************
 *      定数マクロ
 *      MACRO CONSTANT
 ***************************************************************************/

/*	同時に再生するストリーム数	*/
#define	NPLY	(4)

/***************************************************************************
 *      処理マクロ
 *      Process MACRO
 ***************************************************************************/

/*	フラグON/OFFの反転		*/
/*	Turn over flag(ON/OFF)	*/
#define NOT_FLAG(flag)		(((flag) == OFF) ? ON : OFF)

/***************************************************************************
 *      変数定義
 *		Variable Declaration
 ***************************************************************************/

/*	アプリケーション構造体											*/
/*	Application structure											*/
typedef struct {
	Sint32	term_flag;				//	Application terminate flag
	Sint32	disp_flag;				//	Display information flag
	Sint32	pause_flag;				//	Pause flag
	Sint32	first_hpel_flag;		//	First halfpel flag
	char	*fname[NPLY];			//	File name
	MWPLY	ply[NPLY];				//	Player
	Sint32	vol[NPLY];				//	Volume
	MWS_PLY_CPRM_SFD cprm[NPLY];	//	Create parameter
} AP_OBJ, *AP;

/*	アプリケーションオブジェクト									*/
/*	Application Object												*/
AP_OBJ ap_obj = {
	OFF,						//	Execute App.
	ON,							//	Display Info.
	OFF,						//	not puase
	ON,
	"ANIMQ.SFD","CGQ.SFD","LIVEQ.SFD","SFDLOGOQ.SFD",
	NULL,NULL,NULL,NULL,
	0, -1000, -1000, -1000,
};

/***************************************************************************
 *      関数定義
 *      Function Declaration
 ***************************************************************************/

/***
 *			ミドルウェアの再生
 *			Playing middleware
 ***/

/*	ミドルウェアのエラー発生時に起動する関数			*/
/*	Callback function when an error occur in middleware	*/
void ap_mw_err_func(void *obj, char *errmsg)
{
	AP ap=(AP)obj;

	for (;;);
}

/*	ミドルウェアの初期化				*/
/*	Initialize Middleware				*/
void ApInitMw(AP ap,
		Sint32 mod, Sint32 frm, Sint32 cnt, Sint32 ltncy, void *vtxbuf)
{
	MWS_PLY_INIT_SFD	iprm;

	ADXT_Init();

	memset(&iprm, 0, sizeof(iprm));	/*	予約メンバのゼロ設定			*/
									/*	initialize reserved member		*/
	iprm.mode		= mod;			/*	Resolution, NTSC, PAL, VGA		*/
	iprm.frame		= frm;			/*	RGB565, ARGB8888				*/
	iprm.count		= cnt;			/*	Game period by the V-Sync count */
	iprm.latency	= ltncy;		/*	Latency (2V or 3V)				*/
#ifdef NINJA1
	mwPlyInitSofdec(&iprm);
#else
	mwPlyInitSfdFx(&iprm);
	mwPlySetVertexBuffer(vtxbuf);
#endif
	mwPlyEntryErrFunc(ap_mw_err_func, ap);
}

/*	ミドルウェアの終了					*/
/*	Finalize Middleware					*/
void ApFinishMw(AP ap)
{
	mwPlyFinishSfdFx();

	ADXT_Finish();
}

/*	アプリケーション開始処理	*/
/*	Start application		*/
void ApStart(AP ap)
{
	MWS_PLY_CPRM_SFD	*cprm[NPLY];
	Sint32				i;

	/*	ハンドルの生成	*/
	/*	Create handle	*/
	for (i=0; i<NPLY; i++) {
		cprm[i] = &ap->cprm[i];
		memset(cprm[i], 0, sizeof(MWS_PLY_CPRM_SFD));
		cprm[i]->compo_mode = MWD_PLY_COMPO_OPEQ;
		cprm[i]->ftype			= MWD_PLY_FTYPE_SFD;
		cprm[i]->dtype			= MWD_PLY_DTYPE_WND;
		cprm[i]->max_bps = 900*1024*8;
		cprm[i]->max_width = 160;
		cprm[i]->max_height = 128;
		cprm[i]->nfrm_pool_wk = 6;
		cprm[i]->wksize	= mwPlyCalcWorkCprmSfd(cprm[i]);
		cprm[i]->work = syMalloc(cprm[i]->wksize);
		ap->ply[i] = mwPlyCreateSofdec(cprm[i]);
		if ( ap->ply[i] == NULL )
			for (;;) ;

		mwPlySetDispPos(ap->ply[i], 320*(i%2), 240*(i/2));
		mwPlySetDispSize(ap->ply[i], 320, 240);
		mwPlySetFastHalfpel(ap->ply[i], ap->first_hpel_flag);

		/*	再生開始				 */
		/*	Start to play middleware */
		mwPlyStartFname(ap->ply[i], ap->fname[i]);
	}
}

/*	アプリケーション停止処理	*/
/*	Stop application		*/
void ApStop(AP ap)
{
	Sint32	i;

	for (i=0; i<NPLY; i++)
		mwPlyStop(ap->ply[i]);			/*	再生停止 					*/
										/*	Stop to play middleware		*/
	for (i=0; i<NPLY; i++) {
		mwPlyDestroy(ap->ply[i]);		/*	ハンドル消去				*/
										/*	Destroy handle				*/
		syFree(ap->cprm[i].work);
		ap->ply[i] = NULL;
		ap->cprm[i].work = NULL;
	}
}

/*	情報の表示			*/
/*	Display infomation	*/
void ap_disp_info(AP ap)
{
	Sint32	time, tunit, hh, mm, ss, ff, i;

	for (i=0; i<NPLY; i++) {
		mwPlyGetTime(ap->ply[i], &time, &tunit);
		UsrSfcnt2time(tunit, time, &hh, &mm, &ss, &ff);
		UsrPrintf(3, 3+i*2, "Time:%02d:%02d:%02d.%02d", hh, mm, ss, ff);
	}
}

/*	動画の再生					*/
/*	Playing the animation file	*/
Sint32 ApExec(AP ap)
{
	MWPLY			ply[NPLY];
	MWE_PLY_STAT	stat;
	PDS_PERIPHERAL	*per;
	Sint32			i;
	char			*fname[NPLY];

	for (i=0; i<NPLY; i++) {
		ply[i] = ap->ply[i];
		fname[i] = ap->fname[i];
	}
	per = pdGetPeripheral(PDD_PORT_A0);
	if ( per->press & PDD_DGT_ST ) {
		ap->pause_flag = NOT_FLAG(ap->pause_flag);
		mwPlyPause(ply[0], ap->pause_flag);
	}
	if ( per->press & PDD_DGT_TA )
		mwPlyStartFname(ply[0], fname[0]);
	if ( per->press & PDD_DGT_TB )
		mwPlyStartFname(ply[1], fname[1]);
	if ( per->press & PDD_DGT_TX )
		mwPlyStartFname(ply[2], fname[2]);
	if ( per->press & PDD_DGT_TY )
		mwPlyStartFname(ply[3], fname[3]);
	if ( per->press & PDD_DGT_TL)
		ap->disp_flag = NOT_FLAG(ap->disp_flag);

	if ( per->on & PDD_DGT_KU ) {
		for (i=0; i<NPLY; i++)
			ap->vol[i] = -1000;
		ap->vol[0] = 0;
	}
	if ( per->on & PDD_DGT_KD ) {
		for (i=0; i<NPLY; i++)
			ap->vol[i] = -1000;
		ap->vol[1] = 0;
	}
	if ( per->on & PDD_DGT_KL ) {
		for (i=0; i<NPLY; i++)
			ap->vol[i] = -1000;
		ap->vol[2] = 0;
	}
	if ( per->on & PDD_DGT_KR ) {
		for (i=0; i<NPLY; i++)
			ap->vol[i] = -1000;
		ap->vol[3] = 0;
	}

	/*	Checking status												*/
	for (i=0; i<NPLY; i++) {
		stat = mwPlyGetStat(ply[i]);
		if ( stat == MWE_PLY_STAT_PLAYEND )
			mwPlyStartFname(ply[i], fname[i]);
	    if ( stat == MWE_PLY_STAT_ERROR )
			for(;;);
	}

	if ( ap->disp_flag == ON )
		ap_disp_info(ap);

	for (i=0; i<NPLY; i++)
		mwPlySetOutVol(ply[i], ap->vol[i]);

	return TRUE;
}

/***
 *		メイン処理
 *		MAIN
 ***/

/*	GDファイルシステムのエラー発生時に起動する関数			*/
/*	Callback function when an error occur in GD file system	*/
void ApGdErrFunc(void *obj, Sint32 errcode)
{
	AP ap=(AP)obj;

	if ( errcode == GDD_ERR_TRAYOPEND || errcode == GDD_ERR_UNITATTENT )
		ap->term_flag = ON;			/*	アプリケーションの終了		*/
									/*	Terminate application		*/
}

/*	ユーザがV-SYNC割り込みに登録する関数	*/
/*	Callback function when V-sync interrupt	*/
void ApVsyncFunc(void)
{
	UsrCheckDoorOpen();
}

void main(void)
{
	AP ap=&ap_obj;
	void *vtxbuf;
	Sint32 mode, frame, count, latency;
	Bool ret;

#ifdef __GNUC__
	shinobi_workaround();
#endif

	/*	ミドルウェアのためのシステム初期化 (sbInitSystemの前に置く)	*/
	/*	Initialize system for middleware(call before sbInitSystem)	*/
	mwPlyPreInitSofdec();

	/*	忍ライブラリとビデオの初期化								*/
	/*	Initialize SHINOBI & Video Sysytem							*/
	vtxbuf = UsrInitVideo(&mode, &frame, &count, &latency);

	/*	GDファイルシステムエラーコールバック関数の登録				*/
	/*	Entry callback function of GD file system error				*/
	gdFsEntryErrFuncAll((void *)ApGdErrFunc, ap);

	/*	サウンドシステムの初期化									*/
	/*	Initialize sound system										*/
	UsrInitSound();

	/*	V-Sync 割り込み処理の登録									*/
	/*	Register V-Sync interrupt func								*/
	UsrSetVsyncFunc((void (*)(void))ApVsyncFunc);

	/*	ミドルウェアライブラリ初期化								*/
	/*	Initialize middleware										*/
	ApInitMw(ap, mode, frame, count, latency, vtxbuf);

	/*	Frame Work	*/
	while (ap->term_flag == OFF) {

		ApStart(ap);
		while (1) {
			mwPlyExecTexSvr();			/*	Load Texture To V-RAM			*/
			UsrBeginDraw();
			mwPlyExecDrawSvr();			/*	Draw polygons 					*/
			ret = ApExec(ap);
			UsrEndDraw();
			if ( ret == FALSE || ap->term_flag == ON )
				break;
			UsrWaitVBlank();
		}
		ApStop(ap);
	}
	/*	アプリケーション終了処理	*/
	/*	Finalize application		*/
	ApFinishMw(ap);			/*	ミドルウェアの終了					*/
							/*	Finalize Middleware					*/
	UsrFinishSound();		/*	サウンドシステムの終了処理			*/
							/*	Finalize sound system				*/
	UsrFinishVideo();		/*	忍ライブラリとビデオの終了処理		*/
							/*	Finalize SHINOBI & Video system		*/
	syBtExit();				/*	シンプルプレイヤへジャンプ			*/
							/*	Jump to Simple player				*/
}

/* End of file */