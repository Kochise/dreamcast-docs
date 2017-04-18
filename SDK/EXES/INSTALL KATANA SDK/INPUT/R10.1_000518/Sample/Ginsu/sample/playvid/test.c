/*
 *
 *		Middleware Player Sample
 *
 */

/***************************************************************************
 *      インクルードファイル
 *      Include file
 ***************************************************************************/
#include <shinobi.h>
#include <sg_sd.h>
#include <sg_mw.h>
#include <ginsu.h>


/***************************************************************************
 *      定数マクロ
 *      MACRO CONSTANT
 ***************************************************************************/

/*	表示モード		*/
/*	Display mode	*/
#define SYS_MODE		NJD_RESOLUTION_640x480_NTSCI
#define SYS_FRAME		NJD_FRAMEBUFFER_MODE_ARGB8888
#define SYS_COUNT		1

/*	頂点バッファサイズ(1つをマイナスにすると2Vレーテンシモード)			*/
/*	Vertex buffer size(2V latency mode is when a valiable is minus.)	*/
#define SFD_VB_OP		-500000
#define SFD_VB_OM		0
#define SFD_VB_TP		20000
#define SFD_VB_TM		0
#define SFD_VB_PT		0

#define TM_VB_OP		100000
#define TM_VB_OM		0
#define TM_VB_TP		100000
#define TM_VB_TM		0
#define TM_VB_PT		0

/*
 * 音声再生の指定
 *   ON   :音声あり動画ファイルならば音声再生を行う。デフォルト。
 *   OFF  :音声再生を抑止する。音声あり動画ファイルでも映像だけを再生。
 * Setting play audio
 *   ON   :Play audio when the animation file is interleaved audio(default)
 *   OFF  :Not play audio
 */
#define AUDIO_SW		ON

/*	NINJA			*/
#define	TEX_NUM			100
#define	TEXNAME_NUM		2
#define	TEX_BUFSIZE		0x20800

/*	エラーメッセージ長		*/
/*	Length of error message	*/
#define ERRMSG_LEN		256

/*	オーディオ再生用バッファサイズ		*/
/*	Buffer size for play Audio Decoder	*/
#define	AUDIO_BUF_SIZE	MWD_PLY_CALC_AWORK(MWD_PLY_MIN_AWORK)
#define	MPA_BUF_SIZE	AUDIO_BUF_SIZE
#define WAV_BUF_SIZE	AUDIO_BUF_SIZE


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

/*	エラー発生回数		*/
/*	The number of error	*/
Sint32 errcnt = 0;

/*	エラーメッセージ	*/
/*	Error message		*/
char errmsg[ERRMSG_LEN] = "(OK)";

/*	文字列表示フラグ				*/
/*	Flag for a show of character	*/
Sint32 disp_flag = ON;

/*	ポーズ状態		*/
/*	Pause status	*/
Sint32 pause = OFF;

/*	NINJA				*/
NJS_TEXMEMLIST	tex[TEX_NUM];
NJS_TEXINFO		info[TEXNAME_NUM];
NJS_TEXNAME		texname[TEXNAME_NUM];
NJS_TEXLIST		texlist = {texname, TEXNAME_NUM};
Sint8			texbuf[TEX_BUFSIZE];
Uint16			framebuf[1024*512*2];

/*	WAVE再生用バッファ			*/
/*	Buffer for play WAVE file	*/
/* char play_wav_buf[WAV_BUF_SIZE]; */


/***************************************************************************
 *      関数定義
 *      Function Declaration
 ***************************************************************************/

/***
 *		サウンド環境の初期化
 *		Initialize sound section
 ***/

/*	サウンドドライバの転送・初期化					*/
/*	Initialize sound library and load sound driver	*/
void SoundInit(void *sndptr, void *mltptr)
{
	SDMEMBLK	memblk = NULL;

	/*	Initialize Sound library	 */
	sdLibInit(NULL, 0, 0);		/*	This api's argument is dummy now.  */

	/* 	Download and Initialize Sound driver.	 */
	/*	Create Memory block handle  */
	sdMemBlkCreate(&memblk);
	/*  Setting Memory block handle  */
	sdMemBlkSetPrm(memblk, sndptr, 0, SDD_MEMBLK_SYNC_FUNC, NULL);
	/*	Initialize Sound driver  */
	sdDrvInit(memblk);

	/*	Download and Initialize Multi unit	*/
	/*	Setting Memory block handle	*/
	sdMemBlkSetPrm(memblk, mltptr, 0, SDD_MEMBLK_SYNC_FUNC, NULL);
	sdDownloadMultiUnit(memblk);

	sdMemBlkDestroy(memblk);

	/*	Truemotion Only CPU mode	*/
#if	0
	/*	転送モードの設定		*/
	/*	Setting transfer mode	*/
	sdMemBlkSetTransferMode(SDE_MEMBLK_TRANSFER_MODE_DMA);
#endif

	return;
}

/***
 *			ユーティリティ関数
 *			Utility function
 ***/

/*	データの読み込み	*/
/*	Load data to memory	*/
void *LoadFile(char *fname, long *len)
{
	GDFS			gdfs;
	long			fsize, nsct;
	void			*dat;

	gdfs = gdFsOpen(fname, NULL);
	if (gdfs == NULL) {
		for (;;) ;
	}
	gdFsGetFileSize(gdfs, &fsize);
	nsct = (fsize + 2047) / 2048;
	dat = syMalloc(nsct * 2048);
	if (dat == NULL) {
		for (;;) ;
	}
	gdFsRead(gdfs, nsct, dat);
	gdFsClose(gdfs);
	if (len != NULL) {
		*len = fsize;
	}

	return dat;
}

/*	msec -> time(hour,min,sec,frame)	*/
void Msec2Time(long mstime, long *hh, long *mm, long *ss, long *ff)
{
	*hh = mstime / (60*60*1000);
	*mm = (mstime - *hh*60*60*1000) / (60*1000);
	*ss = (mstime - *hh*60*60*1000 - *mm*60*1000) / 1000;
	*ff = mstime % 1000;

	return;
}

/***
 *			ミドルウェアの再生
 *			Playing middleware
 ***/

/*	ミドルウェアのエラー発生時に起動する関数			*/
/*	Callback function when an error occur in middleware	*/
void UsrMwErrFunc(void *obj, char *ecode)
{
	errcnt++;
	strncpy(errmsg, ecode, ERRMSG_LEN);

	return;
}

/*	情報の表示			*/
/*	Display infomation	*/
void DispInfo(MWPLY ply, char *fname)
{
//	long			time, tunit, hh, mm, ss, ff, time_ms;
//	float			timef;
//
//	mwPlyGetTime(ply, &time, &tunit);
//	timef = ((float)time / (float)tunit) * 1000.0;
//	time_ms = (long)timef;
//	Msec2Time(time_ms, &hh, &mm, &ss, &ff);
//	ff = ff*30/1000;
//	njPrint(NJM_LOCATION(0, 3), "File: %s  Time:%02d:%02d:%02d.%02d", 
//							fname, hh, mm, ss, ff);
//	njPrint(NJM_LOCATION(0, 4), "Error%2d:%s", errcnt, errmsg);
//
	return;
}

/*	ミドルウェアの再生	*/
/*	Playing middleware	*/
void play_main(MWPLY ply, char *fname)
{
	MWE_PLY_STAT			stat;
	const PDS_PERIPHERAL	*per;

	mwPlyEntryErrFunc((void *)UsrMwErrFunc, &ply);
	mwPlyPause(ply, pause);				/*	前回再生のポーズ状態を維持		*/
										/*	Keep the last time pause status	*/
	mwPlyStartFname(ply, fname);		/*	再生開始						*/
										/*	Start to play middleware		*/
	while (1) {
		njWaitVSync();
		mwPlyStartFrame();
		per = pdGetPeripheral(PDD_PORT_A0);
		if (per->press & PDD_DGT_TA) {
			disp_flag = NOT_FLAG(disp_flag);
		}
		if (per->press & PDD_DGT_TX) {
			pause = ON;
			mwPlyPause(ply, ON);		/*	一時停止				*/
										/*	Pause					*/
		}
		if (per->press & PDD_DGT_TY) {
			pause = OFF;
			mwPlyPause(ply, OFF);		/*	一時停止解除			*/
										/*	Release pause status	*/
		}
		if (per->press & PDD_DGT_ST) {
			break;
		}
		stat = mwPlyGetStat(ply);
		if ((stat == MWE_PLY_STAT_PLAYEND) || (stat == MWE_PLY_STAT_ERROR)) {
			break;
		}
		if (disp_flag == ON) {
			DispInfo(ply, fname);
		}
		mwPlyExecServer();
	}
	mwPlyStop(ply);						/*	再生停止 					*/
										/*	Stop to play middleware		*/
	njWaitVSync();						/*	パッドの状態取得のため		*/
										/*	for getting status of PAD	*/
	mwPlyDestroy(ply);					/*	ハンドル消去				*/
										/*	Destroy handle				*/

	return;
}

/***
 *			MPEG Sofdec の再生
 *			Play MPEG Sofdec
 ***/

/*	SFDファイルの再生	*/
/*	Playing SFD file	*/
void play_sfd(char *fname)
{
	MWPLY					ply;
	MWS_PLY_CPRM_SFD		cprm;

	/*	ハンドルの生成	*/
	/*	Create handle	*/
	memset(&cprm, 0, sizeof(cprm));	/*	予約メンバのゼロ設定のために必要	*/
									/*	To initialize reserved member		*/
	cprm.ftype			= MWD_PLY_FTYPE_SFD;
	cprm.dtype			= MWD_PLY_DTYPE_AUTO;
	cprm.max_bps = 450*1024*8;
	cprm.max_width = 320;
	cprm.max_height = 480;
	cprm.nfrm_pool_wk = 3;
	cprm.wksize = mwPlyCalcWorkSofdec(
								cprm.ftype,
								cprm.max_bps,
								cprm.max_width,
								cprm.max_height,
								cprm.nfrm_pool_wk);
	cprm.work = syMalloc(cprm.wksize);
	ply = mwPlyCreateSofdec(&cprm);
	if (ply == NULL) {
		for (;;) ;
	}
	mwPlySetAudioSw(ply, AUDIO_SW);
	play_main(ply, fname);
	syFree(cprm.work);

	return;
}

/***
 *			TrueMotion の再生
 *			Play TrueMotion
 ***/

/*	AVIファイルの再生	*/
/*	Playing AVI file	*/
void play_tm(char *fname)
{
	MWPLY				ply;
	MWS_PLY_CPRM_TM		cprm;

	/*	NINJA初期化			*/
	/*	Initialize NINJA	*/
	njInitVertexBuffer(TM_VB_OP, TM_VB_OM, TM_VB_TP, TM_VB_TM, TM_VB_PT);
	njInitPrint(NULL, 0, NJD_TEXFMT_ARGB_8888);
	njPrintSize(12);
	njInitTexture(tex, TEX_NUM);
	njInitTextureBuffer(texbuf, TEX_BUFSIZE);
	njSetTextureInfo(&info[0], framebuf,
					(NJD_TEXFMT_YUV_422 | NJD_TEXFMT_STRIDE), 1024, 512);
	njSetTextureInfo(&info[1], framebuf + 1024 * 512,
					(NJD_TEXFMT_YUV_422 | NJD_TEXFMT_STRIDE), 1024, 512);
	njSetTextureName(&texname[0], &info[0], 0,
					(NJD_TEXATTR_TYPE_MEMORY | NJD_TEXATTR_GLOBALINDEX));
	njSetTextureName(&texname[1], &info[1], 1,
					(NJD_TEXATTR_TYPE_MEMORY | NJD_TEXATTR_GLOBALINDEX));
	njLoadTexture(&texlist);
	njSetTexture(&texlist);

	/*	ハンドルの生成	*/
	/*	Create handle	*/
	ply = mwPlyCreateTM(&cprm);
	if (ply == NULL) {
		for (;;) ;
	}
	play_main(ply, fname);

	/*	NINJA解放		*/
	/*	Finish NINJA	*/
	njReleaseTextureAll();
	njExitTexture();

	/*	NINJA初期化			*/
	/*	Initialize NINJA	*/
	njInitVertexBuffer(SFD_VB_OP, SFD_VB_OM, SFD_VB_TP, SFD_VB_TM, SFD_VB_PT);
	njInitPrint(NULL, 0, NJD_TEXFMT_ARGB_8888);
	njPrintSize(12);

	return;
}

/***
 *			MPEG/Audio の再生
 *			Play MPEG/Audio
 ***/

/*	MP2ファイルの再生	*/
/*	Playing MP2 file	*/
void play_mpa(char *fname)
{
	MWPLY			ply;
	MWS_PLY_CPRM	cprm;

	/*	ハンドルの生成	*/
	/*	Create handle	*/
	cprm.buf     = syMalloc(MPA_BUF_SIZE);
	cprm.size    = MPA_BUF_SIZE;
	cprm.libwork = syMalloc(MWD_MPA_CALC_WORK(1));
	ply = mwPlyCreateMpa(&cprm);
	if (ply == NULL) {
		for (;;) ;
	}
	play_main(ply, fname);
	syFree(cprm.libwork);
	syFree(cprm.buf);

	return;
}

/***
 *			WAVEの再生
 *			Play WAVE
 ***/

/*	WAVEファイルの再生	*/
/*	Playing WAVE file	*/
void play_wav(char *fname)
{
	MWPLY			ply;
	MWS_PLY_CPRM	cprm;

	/*	ハンドルの生成	*/
	/*	Create handle	*/
	cprm.buf     = syMalloc(WAV_BUF_SIZE);
	cprm.size    = WAV_BUF_SIZE;
	cprm.libwork = NULL;
	ply = mwPlyCreateWav(&cprm);
	if (ply == NULL) {
		for (;;) ;
	}
	play_main(ply, fname);
	syFree(cprm.buf);

	return;
}

/***
 *			メイン部
 *			MAIN
 ***/

/*	アプリケーション終了処理	*/
/*	Finalize application		*/
void UsrExit(void)
{
	/*	ライブラリ終了処理					*/
	/*	Finalize Middleware					*/
	mwPlyFinishSofdec();
	mwPlyFinishTM();
	mwPlyFinishMpa();
	mwPlyFinishWav();

	sbExitSystem();			/*	忍ライブラリの終了処理				*/
							/*	Finalize SHINOBI					*/
//	syBtExit();				/*	シンプルプレイヤへジャンプ			*/
							/*	Jump to Simple player				*/
}

/*	GDファイルシステムのエラー発生時に起動する関数			*/
/*	Callback function when an error occur in GD file system	*/
void UsrGdErrFunc(void *obj, Sint32 errcode)
{
	if (errcode == GDD_ERR_TRAYOPEND || errcode == GDD_ERR_UNITATTENT) {
		UsrExit();					/*	アプリケーション終了処理	*/
									/*	Finalize application		*/
	}

	return;
}

/*	ユーザがV-SYNC割り込みに登録する関数	*/
/*	Callback function when V-sync interrupt	*/
void UsrVsyncFunc(void)
{
	Sint32 dstat;

    /*	サウンドライブラリのサーバ関数		*/
	/*	Server function of sound library	*/
	sdSysServer();

	/*	ドアオープンチェック	*/
	/*	Check door open			*/
	dstat = gdFsGetDrvStat();
	if (dstat == GDD_DRVSTAT_OPEN || dstat == GDD_DRVSTAT_BUSY) {
		gdFsReqDrvStat();
	}

	return;
}

void main(void)
{
	MWS_PLY_INIT_SFD		iprm;
	void 					*snddrv;
	void					*mltfile;
	const NJS_PERIPHERAL	*per;

#ifdef __GNUC__
	shinobi_workaround();
#endif
    gsInit();
    
	/*	ミドルウェアのためのシステム初期化 (sbInitSystemの前に置く)	*/
	/*	Initialize system for middleware(call before sbInitSystem)	*/
	mwPlyPreInitSofdec();

	/*	忍ライブラリの初期化	*/
	/*	Initialize SHINOBI		*/
    njSetBorderColor(0x00000000);
    
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}


#if 0
// this line is needed if DDS is not used, ie GDFS version < 1.06
    gdFsChangeDir(gsGetBasePath());
#endif    
    
	njInitVertexBuffer(SFD_VB_OP, SFD_VB_OM, SFD_VB_TP, SFD_VB_TM, SFD_VB_PT);
	njInitPrint(NULL, 0, NJD_TEXFMT_ARGB_8888);
	njPrintSize(12);
	/*	GDファイルシステムエラーコールバック関数の登録	*/
	/*	Entry callback function of GD file system error	*/
	gdFsEntryErrFuncAll((void *)UsrGdErrFunc, NULL);

	/*	サウンドライブラリの準備	*/
	/*	Prepare sound library		*/
	snddrv  = LoadFile("manatee.drv", NULL);
	mltfile = LoadFile("stream.mlt", NULL);
	SoundInit(snddrv, mltfile);

	njSetVSyncFunction(UsrVsyncFunc);

	/*	ミドルウェアライブラリ初期化	*/
	/*	Initialize middleware			*/
	memset(&iprm, 0, sizeof(iprm));	/*	予約メンバのゼロ設定のために必要	*/
									/*	To initialize reserved member		*/

	iprm.mode		= SYS_MODE;
	iprm.frame		= SYS_FRAME;
	iprm.count		= SYS_COUNT;
	iprm.latency	= MWD_PLY_LATENCY(SFD_VB_OP, SFD_VB_OM,
											SFD_VB_TP, SFD_VB_TM, SFD_VB_PT);
	mwPlyInitSofdec(&iprm);
	mwPlyInitTM();
	mwPlyInitMpa(MWD_PLY_SVR_VSYNC);
	mwPlyInitWav(MWD_PLY_SVR_VSYNC);

    if (gsGetArgC()==3)
    {
        if (!strcmp("MPEG",gsGetArgV(2)))
        {
        	play_sfd(gsGetArgV(1));
        }
    
        if (!strcmp("DUCK",gsGetArgV(2)))
        {
        	play_tm(gsGetArgV(1));
        }
    }
    
//	for (;;) {
//		per = njGetPeripheral(NJD_PORT_A0);
//		njPrint(NJM_LOCATION(15, 3), 
//					"Middleware Player Sample No.1");
//		njPrint(NJM_LOCATION(5,  6), "A     : Play MPEG Sofdec");
//		njPrint(NJM_LOCATION(5,  8), "B     : Play TrueMotion");
//		njPrint(NJM_LOCATION(5, 10), "X     : Play MPEG/Audio");
//		njPrint(NJM_LOCATION(5, 12), "Y     : Play WAVE");
//		njPrint(NJM_LOCATION(5, 14), "START : Stop");
//		if (per->press & NJD_DGT_TA) {
//			play_sfd("SAMPLE.SFD");
//		}
//		if (per->press & NJD_DGT_TB) {
//			play_tm("SAMPLE.AVI");
//		}
//		if (per->press & NJD_DGT_TX) {
//			play_mpa("SAMPLE.MP2");
//		}
//		if (per->press & NJD_DGT_TY) {
//			play_wav("SAMPLE.WAV");
//		}
//		njWaitVSync();
//	}

	UsrExit();						/*	アプリケーション終了処理	*/
									/*	Finalize application		*/
    gsExit();
}


/* end of file */
