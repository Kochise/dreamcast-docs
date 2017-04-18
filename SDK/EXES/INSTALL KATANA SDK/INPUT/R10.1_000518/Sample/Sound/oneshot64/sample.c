/****************************************************
 *													*
 *	Dreamcast Sound Library							*
 *			Sample Program							*
 *													*
 *		Copyright 1997-1999 (C)SEGA Enterprises		*
 *			Programmed By T.Jokagi					*
 *													*
 ****************************************************/

/********************************************************************
 *
 *	サンプル名	ワンショット再生．
 *	内容		サウンドシステムの初期化を行いワンショットを再生．
 *	備考		
 *
 */

#include	<shinobi.h>
#include	<ninja.h>
#include	"sg_sd.h"

/*
 *	このサンプルで使用するファイル
 */
#define	SMPD_SND_DRV_FILE_NAME	"MANATEE.DRV"
#define	SMPD_MLT_FILE_NAME		"ONESHOT64.MLT"

/*
 *	各音源ごとに設定したい最大発音数
 */
#define	SMPD_MIDI_SLOT_MAX	(0)
#define	SMPD_SHOT_SLOT_MAX	(64)
#define	SMPD_PSTM_SLOT_MAX	(0)

/*
 *	実際に使用できる最大ポート数
 *	MIDI
 *		MIDI音源は最大発音数に関係なくSDD_MIDI_PORT_MAXポート使用出来る．
 *	OneShot
 *		OneShot音源は1スロット=1ポートなので最大発音数=最大ポート数になる．
 *	PCM Stream
 *		PCM Stream音源は1ポートにつき4スロットまで使用できる．これは1ポートに
 *		沢山のスロットを割り当てるほど同時に使用できる最大ポート数が減ることになる
 *		（つまり使用法により一定ではない）
 */
#define	SMPD_MIDI_PORT_MAX	( SDD_MIDI_PORT_MAX)
#define	SMPD_SHOT_PORT_MAX	( SMPD_SHOT_SLOT_MAX)
#define	SMPD_PSTM_PORT_MAX	( SMPD_PSTM_SLOT_MAX)

Uint32	gSpeedCount;
Uint32	gFrameCount;
Uint32	gVintCount;
Bool	gNjUserMainLoopFlg;

SDSHOT	gShotHandle[ SMPD_SHOT_PORT_MAX];
Sint32	gShotHandleCounter;

Void	njUserInit( Void);
Sint32	njUserMain( Void);
Void	njUserFinish( Void);
Void	VintFunction( Void);
Void	Peripheral( Void);

/********************************************************************
 *
 *	関数	Sint32 njUserMain( Void);
 *	機能	プログラムの初期化処理．
 *	引数	
 *	返り値	
 *	備考	
 *
 */
Void	njUserInit( Void)
{
	Sint32	i;

	gFrameCount = 0;
	gVintCount = 0;
	gSpeedCount = 120;
	gNjUserMainLoopFlg = true;

    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
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
    njSetBorderColor( 0x00000000 ) ;
    njInitVertexBuffer( 1000000, 0, 200000, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor( 0x00000000, 0x00000000, 0x0000C060);

	for ( i = 0; i < SMPD_SHOT_PORT_MAX; i++)
		gShotHandle[ i] = NULL;
	gShotHandleCounter = 0;

	njSetVSyncFunction( VintFunction);

	/*
	 *	サウンドシステムの初期化
	 */
	/*	サウンドライブラリの初期化  */
	sdLibInit( NULL, 0, 0);

	/*	サウンドドライバファイルの読み込み  */
	sdDrvDownloadFromFile( SMPD_SND_DRV_FILE_NAME, SDD_MEMBLK_LOCAL_ALLOCATE);
	/*	SDD_MEMBLK_LOCAL_ALLOCATEはAPI内部でsyMallocを使用します．注意してください  */

	/*
	 *	マルチユニットファイルの読み込み
	 */
	/*	マルチユニットファイルの読み込み  */
	sdMultiUnitDownloadFromFile( SMPD_MLT_FILE_NAME, SDD_MEMBLK_LOCAL_ALLOCATE);
	/*	SDD_MEMBLK_LOCAL_ALLOCATEはAPI内部でsyMallocを使用します．注意してください  */

	/*	各音源ごとの最大音数の設定．サウンドドライバのダウンロードのあとに実行しなければならない  */
	sdSysSetSlotMax( SMPD_MIDI_SLOT_MAX, SMPD_SHOT_PORT_MAX, SMPD_PSTM_SLOT_MAX);

	for ( i = 0; i < SMPD_SHOT_PORT_MAX; i++)
		sdShotOpenPort( &gShotHandle[ i]);

}

/********************************************************************
 *
 *	関数	Sint32 njUserMain( Void);
 *	機能	プログラムの中核．
 *	引数	
 *	返り値	作業を続けるならNJD_USER_CONTINUE．終了するならNJD_USER_EXIT．
 *	備考	
 *
 */
Sint32 njUserMain( Void)
{
	static Bool	flg = false;
	gFrameCount++;

	Peripheral();


	/*	gSpeedCount値 V-int ごとに再生  */
	if ( ( gFrameCount % gSpeedCount) == 0){
		sdShotPlay( gShotHandle[ gShotHandleCounter], 0, 0, 0);
//		gShotHandleCounter++ = gShotHandleCounter % SMPD_SHOT_PORT_MAX;
		gShotHandleCounter++;
		gShotHandleCounter = gShotHandleCounter % SMPD_SHOT_PORT_MAX;
	}

/* Display Contents */
	njPrintC( NJM_LOCATION(  0, 1), "V-Int        :          (  :  :  )");
	njPrintH( NJM_LOCATION( 14, 1), gVintCount, 8);
	njPrintD( NJM_LOCATION( 25, 1), ( gVintCount / ( 60 * 60)) % 60, 2);
	njPrintD( NJM_LOCATION( 28, 1), ( gVintCount / 60        ) % 60, 2);
	njPrintD( NJM_LOCATION( 31, 1), ( gVintCount             ) % 60, 2);

	sdLibShowStat( 0, 2, 0xFFFFFFFF);
	sdDrvShowStat( 0, 3, 0xFFFFFFFF);

	njPrintC( NJM_LOCATION(  0, 7), "Shot Port Num:");
	njPrintH( NJM_LOCATION( 14, 7), gShotHandleCounter, 8);
	sdShotShowStat( gShotHandle[ gShotHandleCounter], 0, 8, 0xFFFFFFFF);

	njPrintC( NJM_LOCATION(  0, 16), "Shot Speed   :        v-int");
	njPrintD( NJM_LOCATION( 14, 16), gSpeedCount, 8);

	return gNjUserMainLoopFlg == true? NJD_USER_CONTINUE: NJD_USER_EXIT;
}

/********************************************************************
 *
 *	関数	Void	njUserExit( Void);
 *	機能	プログラムの終了．
 *	引数	
 *	返り値	
 *	備考	
 *
 */
Void	njUserExit( Void)
{
	Sint32	i;

	for ( i = 0; i < SMPD_SHOT_PORT_MAX; i++)
		sdShotClosePort( gShotHandle[ i]);

	set_imask(15);
	sdSysFinish();
	njExitTexture();
	sbExitSystem();
}

/********************************************************************
 *
 *	関数	Void	VintFunction( Void);
 *	機能	V割り込みの処理．
 *	引数	
 *	返り値	
 *	備考	
 *
 */
Void	VintFunction( Void)
{
	gVintCount++;
	sdSysServer();
}

/********************************************************************
 *
 *	関数	Void	Peripheral( Void);
 *	機能	パッドでのコントロール．
 *	引数	
 *	返り値	
 *	備考	
 *
 */
Void	Peripheral( Void)
{
	PDS_PERIPHERAL	*per;

	per = pdGetPeripheral( NJD_PORT_A0);

	/*
	 *	[A][B][X][Y][START]でのリセット
	 */
	if ( per->on & PDD_DGT_TA
	  && per->on & PDD_DGT_TB
	  && per->on & PDD_DGT_TX
	  && per->on & PDD_DGT_TY
	  && per->on & PDD_DGT_ST)
		gNjUserMainLoopFlg = false;

	if ( per->on & PDD_DGT_KU ){
		if(gSpeedCount <= 300){
			gSpeedCount++;
		}
	}
	if ( per->on & PDD_DGT_KD ){
		if(gSpeedCount > 0){
			gSpeedCount--;
		}
	}

}

/*EOF*/
