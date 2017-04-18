/*
 *
 *		ADXT Sample Program (Playing from memory & memory index)
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
/*	最大チャンネル数				*/
/*	The number of maximum channels	*/
#define	MAX_ADXT			(4)

/*	最大チャンネル数				*/
/*	The number of maximum channels	*/
#define	MAX_CH			(2)

/*	同時再生最大CDストリーム数									*/
/*	The number of maximum CD streams playing at the same time	*/
#define	MAX_CDSTM		(1)

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
	void 	*adxdat;				//	ADX data pointer
	void 	*acxdat;				//	ACX data pointar
	ADXT	adxt[MAX_ADXT];			//	ADXT handle
	char	work[MAX_ADXT][WKSIZE];	//	Work area
} AP_OBJ, *AP;

/*	アプリケーションオブジェクト1									*/
/*	Application Object												*/
AP_OBJ ap_obj = {
	OFF,						//	Execute App.
	ON,							//	Display Info.
	OFF,						//	not puase
	NULL,						//	ADX data pointer
	NULL,						//	ACX data pointar
	{NULL, NULL, NULL, NULL}	//	ADXT handle
};

/***************************************************************************
 *      関数定義
 *      Function Declaration
 ***************************************************************************/

/***
 *			ミドルウェアの再生
 *			Playing middleware
 ***/

/*	GDファイルシステムのエラー発生時に起動する関数			*/
/*	Callback function when an error occur in GD file system	*/
void ApGdErrFunc(void *obj, Sint32 errcode)
{
	AP	ap=(AP)obj;
	
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

/*	ミドルウェアの終了					*/
/*	Finalize Middleware					*/
void ApFinishMw(AP ap)
{
	ADXT_Finish();
}

/*	アプリケーション開始処理	*/
/*	Start application			*/
void ApStart(AP ap)
{
	long	i;

	/*	ADX データの読み込み	*/
	/*	Load ADX data			*/
	ap->adxdat = UsrLoadFile("SAMPLE.ADX", NULL);
	/*	ACX データの読み込み	*/
	/*	Load ACX data			*/
	ap->acxdat = UsrLoadFile("SMPL_MEM.ACX", NULL);


	/*	ADXT ハンドルの生成	*/
	/*	Create ADXT handle	*/
	for (i=0; i<MAX_ADXT; i++) 
		if ( (ap->adxt[i]=ADXT_Create(2, ap->work[i], WKSIZE)) == NULL )
			for (;;) 

	/*	パンの設定		*/
	/*	Ppanpot setting	*/
	ADXT_SetOutPan(ap->adxt[2], 0, ADXT_PAN_LEFT);
	ADXT_SetOutPan(ap->adxt[3], 0, ADXT_PAN_RIGHT);
}

/*	アプリケーション停止処理	*/
/*	Stop application		*/
void ApStop(AP ap)
{
	long	i;

	/*	ADXT ハンドルの消去	*/
	/*	Destroy ADXT handle	*/
	for (i=0; i<MAX_ADXT; i++) {
		ADXT_Destroy(ap->adxt[i]);
		ap->adxt[i] = NULL;
	}

	/*	ADX/ACXデータの解放	*/
	/*	Free ADX/ACX datas	*/
	syFree(ap->adxdat);
	syFree(ap->acxdat);

}

/*	情報の表示			*/
/*	Display infomation	*/
void ap_disp_info(AP ap)
{
	char *ststr[6] =
		{"STOP   ", "DECINFO   ", "PREP   ", "PLAYING", "DECEND ", "PLAYEND"};
	long 		i, stat, sfreq, cnt, td;
	long 		hh, mm, ss, ff;
	extern long	adxt_svrcnt;

	UsrPrintf(3, 2, "ADX Sample Program");
	UsrPrintf(3, 3, "   ADX Playing Multi-Stream from Memory");
	for (i=0; i<MAX_ADXT; i++) {
		stat = ADXT_GetStat(ap->adxt[i]);
		UsrPrintf(3, 5+i*2, "ADXT%2d: Stat=%s", i, ststr[stat]);
		ADXT_GetTime(ap->adxt[i], &cnt, &sfreq);
		UsrSfcnt2time(sfreq,  cnt, &hh, &mm, &ss, &ff);
		UsrPrintf(26, 5+i*2, "Time=%2d:%02d:%02d.%02d", hh, mm, ss, ff);
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
	/*	メモリ再生					*/
	/*	Start to memory play		*/
	if (per->press & PDD_DGT_TA)
		ADXT_StartMem(ap->adxt[0], ap->adxdat);
	/*	メモリインデックス再生			*/
	/*	Start to memory index play		*/
	if (per->press & PDD_DGT_TB)
		ADXT_StartMemIdx(ap->adxt[0], ap->acxdat, 0);
	if (per->press & PDD_DGT_TX)
		ADXT_StartMemIdx(ap->adxt[1], ap->acxdat, 1);
	if (per->press & PDD_DGT_TY)
		ADXT_StartMemIdx(ap->adxt[1], ap->acxdat, 2);
	if (per->press & PDD_DGT_KR)
		ADXT_StartMemIdx(ap->adxt[2], ap->acxdat, 3);
	if (per->press & PDD_DGT_KL)
		ADXT_StartMemIdx(ap->adxt[2], ap->acxdat, 4);
	if (per->press & PDD_DGT_KD)
		ADXT_StartMemIdx(ap->adxt[3], ap->acxdat, 5);
	if (per->press & PDD_DGT_KU)
		ADXT_StartMemIdx(ap->adxt[3], ap->acxdat, 6);
	if (per->press & PDD_DGT_ST)
		for (i=0; i<MAX_ADXT; i++) ADXT_Stop(ap->adxt[i]);

	/*	情報の表示			*/
	/*	Display infomation	*/
	ap_disp_info(ap);

	return TRUE;
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
	AP 		ap=&ap_obj;
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
