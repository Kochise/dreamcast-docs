/*
 *
 *		SofdecF/X Sample (Playing GD stream)
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

/*	最大チャンネル数				*/
/*	The number of maximum channels	*/
#define	MAX_CH			2

/*	同時再生最大CDストリーム数									*/
/*	The number of maximum CD streams playing at the same time	*/
#define	MAX_CDSTM		2

/*	最高サンプリング周波数		*/
/*	Maximum sampling frequency	*/
#define	MAX_SFREQ		44100

/*	ADX再生用作業領域の大きさ	*/
/*	Work area size of ADX play	*/
#define	ADXT_WKSIZE		ADXT_CALC_WORK(MAX_CH, 1, MAX_CDSTM, MAX_SFREQ)

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
	Sint32	pause;					//	Pause flag
	MWPLY	ply;					//	Sofdec Player
	MWS_PLY_CPRM_SFD cprm;			//	Create parameter
	Float	endtime;				//	End time of current playing
	ADXT 	adxt;					//	ADXT Player
	char	adxt_work[ADXT_WKSIZE];	//	Work area for ADXT
} AP_OBJ, *AP;

/*	アプリケーションオブジェクト									*/
/*	Application Object												*/
AP_OBJ ap_obj = {
	OFF,							//	Execute App.
	ON,								//	Display Info.
	OFF,							//	not puase
	NULL,							//	Player
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
#ifdef	NINJA1
	mwPlyFinishSofdec();
#else
	mwPlyFinishSfdFx();
#endif
	ADXT_Finish();
}

/*	アプリケーション開始処理	*/
/*	Start application		*/
void ApStart(AP ap)
{
	MWS_PLY_CPRM_SFD		*cprm=&ap->cprm;

	/*	ADXT ハンドルの生成と再生　			*/
	/*	Create ADXT handle and play music	*/
	ap->adxt=ADXT_Create(2, ap->adxt_work, ADXT_WKSIZE);
	ADXT_SetAutoRcvr(ap->adxt, ADXT_RMODE_REPLAY);
	ADXT_StartFname(ap->adxt, "LOOPSMP.ADX");

	/*	SFD ハンドルの生成	*/
	/*	Create SFD handle	*/
	memset(cprm, 0, sizeof(cprm));		/*	予約メンバのゼロ設定			*/
										/*	To initialize reserved member	*/
	cprm->compo_mode	= MWD_PLY_COMPO_OPEQ;
	cprm->ftype			= MWD_PLY_FTYPE_MPV;
	cprm->dtype			= MWD_PLY_DTYPE_AUTO;
	cprm->max_bps		= 600*1024*8;
	cprm->max_width		= 640;
	cprm->max_height	= 480;
	cprm->nfrm_pool_wk	= 3;
	cprm->wksize		= mwPlyCalcWorkCprmSfd(cprm);
	cprm->work			= syMalloc(cprm->wksize);
	ap->ply = mwPlyCreateSofdec(cprm);
	if (ap->ply == NULL) {
		for (;;) ;
	}
	mwPlyEntryFname(ap->ply, "LC01FM.M1V");	/*	ストリームの登録			*/
											/*	Entry stream				*/
	ap->endtime = 3.0f;						/*	LC01FM.M1V is 3 sec			*/
	mwPlyStartSeamless(ap->ply);			/*	再生開始					*/
											/*	Start to play middleware	*/
}

/*	アプリケーション停止処理	*/
/*	Stop application		*/
void ApStop(AP ap)
{
	mwPlyStop(ap->ply);					/*	再生停止 					*/
										/*	Stop to play middleware		*/
	mwPlyDestroy(ap->ply);				/*	ハンドル消去				*/
										/*	Destroy handle				*/
	ap->ply = NULL;
	syFree(ap->cprm.work);				/*	作業領域の開放				*/
										/*	Release work area			*/
	ap->cprm.work = NULL;

	ADXT_Stop(ap->adxt);
	ADXT_Destroy(ap->adxt);
	ap->adxt = NULL;
}

/*	情報の表示			*/
/*	Display infomation	*/
void ap_disp_info(AP ap)
{
	Sint32	time, tunit, hh, mm, ss, ff;

	mwPlyGetTime(ap->ply, &time, &tunit);
	UsrSfcnt2time(tunit, time, &hh, &mm, &ss, &ff);
	UsrPrintf(0, 0, "Seamless play sample");
	UsrPrintf(0, 1, "Time:%02d:%02d:%02d.%02d", hh, mm, ss, ff);
	UsrPrintf(2, 2, "Please push X button or Y button");

}

/*	動画の再生					*/
/*	Playing the animation file	*/
Sint32 ApExec(AP ap)
{
	MWPLY					ply=ap->ply;
	MWE_PLY_STAT			stat;
	const PDS_PERIPHERAL	*per;
	Float					nowtime;
	Sint32					time, tunit;

	per = pdGetPeripheral(PDD_PORT_A0);
	if (per->press & PDD_DGT_TA) {
		ap->disp_flag = NOT_FLAG(ap->disp_flag);
	}
	if (per->press & PDD_DGT_TB)
		return FALSE;

	mwPlyGetTime(ply, &time, &tunit);
	nowtime = (float)time/(float)(tunit);
		
	/*	ムービー再生時間が残り1秒を切ったら再エントリする 				*/
	/*	If remain time is less than 1 sec, 'LC01FM.M1V' is entried		*/
	if ( ap->endtime - nowtime < 1.0f ) {
		mwPlyEntryFname(ply, "LC01FM.M1V");
		ap->endtime += 3.0f;			/*	LC01FM.M1V is 3 sec			*/
	}
	if (per->press & PDD_DGT_TX) {
		mwPlyEntryFname(ply, "LC02FM.M1V");
		ap->endtime += 2.0f;			/*	LC02FM.M1V is 2 sec			*/
	}
	if (per->press & PDD_DGT_TY) {
		mwPlyEntryFname(ply, "LC03FM.M1V");
		ap->endtime += 3.0f;			/*	LC03FM.M1V is 3 sec			*/
	}
	if (per->press & PDD_DGT_ST) {
		ap->pause = NOT_FLAG(ap->pause);
		mwPlyPause(ply, ap->pause);		/*	一時停止解除			*/
										/*	Release pause status	*/
	}

	/*	Checking status												*/
	stat = mwPlyGetStat(ply);
	if ((stat == MWE_PLY_STAT_PLAYEND) || (stat == MWE_PLY_STAT_ERROR))
		return FALSE;
	if ( ap->disp_flag == ON )
		ap_disp_info(ap);

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
	if (errcode == GDD_ERR_TRAYOPEND || errcode == GDD_ERR_UNITATTENT)
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
	while ( ap->term_flag == OFF ) {
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
