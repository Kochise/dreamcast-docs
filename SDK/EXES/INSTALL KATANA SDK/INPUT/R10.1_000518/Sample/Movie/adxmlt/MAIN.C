/*
 *
 *		ADX Sample Program (Playing Multi-streams)
 *
 */

/***************************************************************************
 *      インクルードファイル
 *      Include file
 ***************************************************************************/

#include	"shinobi.h"
#include	"cri_adxf.h"
#include	"cri_adxt.h"
#include	"usr.h"

/***************************************************************************
 *      定数マクロ
 *      MACRO CONSTANT
 ***************************************************************************/

/*	The number of ADXT handles	*/
#define	NADXT		(4)

/*	最大チャンネル数				*/
/*	The number of maximum channels	*/
#define	MAX_CH		(2)

/*	同時再生最大CDストリーム数									*/
/*	The number of maximum CD streams playing at the same time	*/
#define	MAX_CDSTM	(NADXT)

/*	最高サンプリング周波数		*/
/*	Maximum sampling frequency	*/
#define	MAX_SFREQ		(44100)

/*	ファイル再生用ワーク領域の大きさ	*/
/*	Work area size of CD stream play	*/
#define	WKSIZE		(ADXT_CALC_WORK(MAX_CH, 1, MAX_CDSTM, MAX_SFREQ))

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
	ADXT	adxt[NADXT];			//	ADXT handle
	char	*fname[NADXT];			//	File name
	char	work[NADXT][WKSIZE];	//	Work area
} AP_OBJ, *AP;

/*	アプリケーションオブジェクト									*/
/*	Application Object												*/
AP_OBJ ap_obj = {
	OFF,						//	Execute App.
	ON,							//	Display Info.
	OFF,						//	not puase
	NULL, NULL, NULL, NULL,		//	ADXT handle
	"music4.adx","ambi.adx","ambi2.adx","speech.adx",
};

/***************************************************************************
 *      関数定義
 *      Function Declaration
 ***************************************************************************/

/***
 *			サンプルプログラム
 *			Sample program
 ***/

/*	GDファイルシステムのエラー発生時に起動する関数			*/
/*	Callback function when an error occur in GD file system	*/
void ApGdErrFunc(void *obj, Sint32 errcode)
{
	AP ap = (AP)obj;
	
	if (errcode == GDD_ERR_TRAYOPEND || errcode == GDD_ERR_UNITATTENT)
		ap->term_flag = ON;			/*	アプリケーションの終了		*/
									/*	Terminate application		*/
}

/*	ADXTエラー発生時に起動する関数					*/
/*	Callback function when an error occur in ADXT	*/
void ap_adx_err_func(void *obj, char *msg)
{
	/*	
	 *	ADXで、エラーが発生するとこの関数が呼び出されます。
	 *	msg にエラーメッセージが渡されます。
	 *	msgは、R5レジスタに格納されているので、R5レジスタのアドレスを
	 *	ダンプすることによってエラーメッセージを知ることができます。
	 *	この関数は、V-Sync割り込みから呼び出されることがありますので、
	 *	Ninjaの関数は使用しないでください。
	 *	また、アプリケーションをリリースするときは、何もせずに戻るような
 	 *	関数にしてください。
	 *	This function call when error occur in ADX library.
	 *	Error message is put into 'msg' variable.
	 *	'msg' house R5 register. You can look error message in address of 
	 *	R5 register.
	 *	You cannot call Ninja function because this function is called 
	 *	from V-Int.
	 *	You must change this to no operation function when you release 
	 *	the application.
	 */

	for (;;);		/*	リリース時には無くす					*/
					/*	Delete when you release application.	*/
}

/*	ミドルウェアの初期化				*/
/*	Initialize Middleware				*/
void ApInitMw(AP ap)
{
	/*	ADXライブラリ初期化		*/
	/*	Initialize ADX library	*/
	ADXT_Init();
	
	/*	エラーコールバック関数の登録		*/
	/*	Entry ADX error callback function	*/
	ADXT_EntryErrFunc(ap_adx_err_func, NULL);
}

/*	アプリケーション開始処理	*/
/*	Start application		*/
void ApStart(AP ap)
{
	long	i;

	/*	ADXT ハンドルの生成	*/
	/*	Create ADXT handle	*/
	for (i=0; i<NADXT; i++)
		if ( (ap->adxt[i]=ADXT_Create(2, ap->work[i], WKSIZE)) == NULL )
			for (;;);
	
	/*	再生開始		*/
	/*	Start to play	*/
	for (i=0; i<NADXT; i++)
		ADXT_StartFname(ap->adxt[i], ap->fname[i]);
}

/*	アプリケーション停止処理	*/
/*	Stop application		*/
void ApStop(AP ap)
{
	long	i;

	/*	ADXT ハンドルの消去	*/
	/*	Destroy ADXT handle	*/
	for (i=0; i<NADXT; i++) {
		ADXT_Destroy(ap->adxt[i]);
		ap->adxt[i] = NULL;
	}
}

/*	情報の表示			*/
/*	Display infomation	*/
void ap_disp_info(AP ap)
{
	char *ststr[6] =
		{"STOP   ", "DECINFO", "PREP   ", "PLAYING", "DECEND ", "PLAYEND"};
	long		stat, sfreq, cnt, td, i, vol;
	long		hh, mm, ss, ff;
	extern long	adxt_svrcnt;

	UsrPrintf(3, 2, "ADX Sample Program");
	UsrPrintf(3, 3, "   ADX Playing Multi-Stream from GD-ROM");
	for (i=0; i<NADXT; i++) {
		stat = ADXT_GetStat(ap->adxt[i]);
		UsrPrintf(3, 5+i*2, "ADXT%2d: Stat=%s", i, ststr[stat]);
		ADXT_GetTime(ap->adxt[i], &cnt, &sfreq);
		UsrSfcnt2time(sfreq,  cnt, &hh, &mm, &ss, &ff);
		vol = ADXT_GetOutVol(ap->adxt[i]);
		UsrPrintf(24, 5+i*2, "Time=%d:%02d:%02d.%02d %s",
								hh, mm, ss, ff, (vol == 0) ? "ON  " : "MUTE");
		
	}
	td = syTmrCountToMicro(adxt_svrcnt);
	UsrPrintf(3, 15, "CPU Load = %4d (%2d p.c.)", td, td*100/16667);
}

/*	ADFXの再生			*/
/*	Playing the ADXT	*/
Sint32 ApExec(AP ap)
{
	long					i;
	const PDS_PERIPHERAL	*per;

	per = pdGetPeripheral(PDD_PORT_A0);
	if (per->press & PDD_DGT_ST) {
		ap->pause_flag = NOT_FLAG(ap->pause_flag);
		for (i=0; i<NADXT; i++)
			ADXT_Pause(ap->adxt[i], ap->pause_flag);/* 一時停止解除         */
													/* Release pause status */
	}
	if (per->press & PDD_DGT_TA)
		ADXT_StartFname(ap->adxt[0], ap->fname[0]);
	if (per->press & PDD_DGT_TB)
		ADXT_StartFname(ap->adxt[1], ap->fname[1]);
	if (per->press & PDD_DGT_TX)
		ADXT_StartFname(ap->adxt[2], ap->fname[2]);
	if (per->press & PDD_DGT_TY)
		ADXT_StartFname(ap->adxt[3], ap->fname[3]);

	if (per->press & PDD_DGT_KU) {
		for (i=0; i<NADXT; i++)
			ADXT_SetOutVol(ap->adxt[i], -999);
		ADXT_SetOutVol(ap->adxt[0], 0);
	}
	if (per->press & PDD_DGT_KD) {
		for (i=0; i<NADXT; i++)
			ADXT_SetOutVol(ap->adxt[i], -999);
		ADXT_SetOutVol(ap->adxt[1], 0);
	}
	if (per->press & PDD_DGT_KL) {
		for (i=0; i<NADXT; i++)
			ADXT_SetOutVol(ap->adxt[i], -999);
		ADXT_SetOutVol(ap->adxt[2], 0);
	}
	if (per->press & PDD_DGT_KR) {
		for (i=0; i<NADXT; i++)
			ADXT_SetOutVol(ap->adxt[i], -999);
		ADXT_SetOutVol(ap->adxt[3], 0);
	}
	if (per->press & PDD_DGT_TR) {
		for (i=0; i<NADXT; i++)
			ADXT_SetOutVol(ap->adxt[i], 0);
	}
	if (per->press & PDD_DGT_TL) {
		for (i=0; i<NADXT; i++)
			ADXT_Stop(ap->adxt[i]);
	}
	/*	情報の表示			*/
	/*	Display infomation	*/
	ap_disp_info(ap);
	
	return TRUE;
}

/*	ミドルウェアの終了					*/
/*	Finalize Middleware					*/
void ApFinishMw(AP ap)
{
	ADXT_Finish();
}

/*	ユーザがV-SYNC割り込みに登録する関数	*/
/*	Callback function when V-sync interrupt	*/
void ApVsyncFunc(void)
{
	UsrCheckDoorOpen();
}

/***
 *		メイン処理
 *		MAIN
 ***/
void main(void)
{
	AP 		ap = &ap_obj;
	void	*vtxbuf;
	Sint32	mode, frame, count, latency;
	Bool	ret;

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
	ApInitMw(ap);

	/*	Frame Work	*/
	while ( ap->term_flag == OFF ) {
		ApStart(ap);
		for (;;) {
			UsrBeginDraw();
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
	ApFinishMw(ap);		/*	ミドルウェアの終了					*/
							/*	Finalize Middleware					*/
	UsrFinishSound();		/*	サウンドシステムの終了処理			*/
							/*	Finalize sound system				*/
	UsrFinishVideo();		/*	忍ライブラリとビデオの終了処理		*/
							/*	Finalize SHINOBI & Video system		*/
	syBtExit();				/*	シンプルプレイヤへジャンプ			*/
							/*	Jump to Simple player				*/
}

/* End of file */
