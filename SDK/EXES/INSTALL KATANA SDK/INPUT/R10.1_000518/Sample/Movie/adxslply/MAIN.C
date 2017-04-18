/*
 *
 *		ADXT Sample Program (Seamless Continuous Play)
 *
 */

/***************************************************************************
 *      インクルードファイル
 *      Include file
 ***************************************************************************/

#include	"shinobi.h"
#include	"sg_mw.h"
#include	"usr.h"

/***************************************************************************
 *      定数マクロ
 *      MACRO CONSTANT
 ***************************************************************************/

/*	最大チャンネル数				*/
/*	The number of maximum channels	*/
#define	MAX_CH			(2)

/*	同時再生最大CDストリーム数									*/
/*	The number of maximum CD streams playing at the same time	*/
#define	MAX_CDSTM		(1)

/*	最高サンプリング周波数		*/
/*	Maximum sampling frequency	*/
#define	MAX_SFREQ		(44100)

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
	ADXT_Init();
	ADXT_EntryErrFunc(ap_mw_err_func, ap);
}

/*	ミドルウェアの終了					*/
/*	Finalize Middleware					*/
void ApFinishMw(AP ap)
{
	ADXT_Finish();
}

/*	アプリケーション開始処理	*/
/*	Start application		*/
void ApStart(AP ap)
{
	ADXT adxt;
	adxt = ap->adxt = ADXT_Create(2, ap->adxt_work, ADXT_WKSIZE);
	ADXT_EntryFname(adxt, "smpsl1.adx");
	ADXT_EntryFname(adxt, "smpsl1.adx");
	ADXT_EntryFname(adxt, "smpsl2.adx");
	ADXT_EntryFname(adxt, "smpsl2.adx");
//	ADXT_EntryFname(adxt, "smpsl3.adx");
	ADXT_SetSeamlessLp(adxt, 1);			// シームレスループ再生の設定
	ADXT_StartSeamless(adxt);
}

/*	アプリケーション停止処理	*/
/*	Stop application		*/
void ApStop(AP ap)
{
	ADXT_Destroy(ap->adxt);
}

/*	情報の表示			*/
/*	Display infomation	*/
void ap_disp_info(AP ap)
{
	ADXT adxt=ap->adxt;
	char *ststr[6] =
		{"STOP   ", "DECINFO   ", "PREP   ", "PLAYING", "DECEND ", "PLAYEND"};
	Sint32 stat, sfreq, cnt, td;
	Sint32 hh, mm, ss, ff;
	extern Sint32 adxt_svrcnt;

	UsrPrintf(2, 1, "ADX Sample Program");
	UsrPrintf(2, 2, "   ( Seamless Continuous Play )");
	stat = ADXT_GetStat(adxt);
	UsrPrintf(2, 4, "Stat = %s", ststr[stat]);
	ADXT_GetTime(adxt, &cnt, &sfreq);
	UsrSfcnt2time(sfreq,  cnt, &hh, &mm, &ss, &ff);
	UsrPrintf(2, 5, "Time = %2d:%2d:%2d.%2d", hh, mm, ss, ff);
	UsrPrintf(2, 6, "Num Files = %d", ADXT_GetNumFiles(adxt));
	td = syTmrCountToMicro(adxt_svrcnt);
	UsrPrintf(2, 8, "CPU Load %4d %2d%%", td, td*100/16667);
}

/*	動画の再生					*/
/*	Playing the animation file	*/
Sint32 ApExec(AP ap)
{
	ADXT					adxt=ap->adxt;
	Sint32					stat;
	const PDS_PERIPHERAL	*per;

	per = pdGetPeripheral(PDD_PORT_A0);
	if (per->press & PDD_DGT_TA)
		ap->disp_flag = NOT_FLAG(ap->disp_flag);

	if (per->press & PDD_DGT_TB)
		return FALSE;

	if (per->press & PDD_DGT_ST) {
		ap->pause = NOT_FLAG(ap->pause);
		ADXT_Pause(adxt, ap->pause);	/*	一時停止解除			*/
										/*	Release pause status	*/
	}
	/*	Checking status												*/
	stat = ADXT_GetStat(adxt);
	if ( stat == ADXT_STAT_PLAYEND )
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
